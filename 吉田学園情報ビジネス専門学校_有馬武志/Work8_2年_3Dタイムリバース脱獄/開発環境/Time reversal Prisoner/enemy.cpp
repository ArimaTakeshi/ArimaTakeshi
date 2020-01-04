//=============================================================================
//
// エネミーの処理 [enemy.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "enemy.h"
#include "manager.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "object.h"
#include "game.h"
#include "wall.h"
#include "ground.h"
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "serect.h"
#include "meshorbit.h"
#include "player.h"
#include "effect.h"
#include "billboord.h"
#include "dummyenemy.h"
#include "gauge.h"
#include "spotlight.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_SPEED			(1.0f)
#define JUMP_POWER			(26.0f)
#define SEARCH_RANGE		(200.0f) 
#define SEARCH_RANGE_2		(350.0f) 
#define BULLET_SPEED		(12.0f)
#define MOVE_WALK			(2.5f) 
#define LIGHT_LENGTH		(100.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH	CEnemy::m_pMesh[MAX_PARTS] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER CEnemy::m_pBuffMat[MAX_PARTS] = {};	//マテリアルの情報へのポインタ
DWORD CEnemy::m_nNumMat[MAX_PARTS] = {};			//マテリアルの情報数
CMeshOrbit *CEnemy::m_MeshOrbit = NULL;

//--------------------------------------------
//グローバル変数
//--------------------------------------------
int g_nNumEnemyModel;
char g_aFileNameEnemyModel[MAX_PARTS][256];

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CEnemy::CEnemy(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	//値の初期化
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_apModel[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//過去の位置
	m_bTarget = false;								//追尾時間の状態
	m_bInLength = false;							//発見した状態を
	m_bLightIn = false;								//ライトに入った状態
	m_bMoveType = false;							//移動の種類
	m_nPattern = 0;									//行動パターン
}
//===============================================================================
//　デストラクタ
//===============================================================================
CEnemy::~CEnemy()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//過去の位置
	m_bJump = true;								//ジャンプの状態
	m_bLand = true;								//着地の状態
	m_bInLength = false;						//見つけた後の状態
	m_bStartMotion = false;						//モーションの始まり
	m_bMotionEnd = true;						//モーションの終わり
	m_nAnimnow = ENEMYANIM_NEUTRAL;				//モーションの初期化
	m_MoveList = MOVE_NONE;						//移動方法の初期化
	m_nAttackCount = 0;							//攻撃までの時間
	m_nAttackDelay = 0;
	m_nCntTime = 0;								//状態の時間
	m_nWaitTime = 0;							//待機時間
	m_bReturn = false;							//戻すための変数
	m_bTitle = false;							//タイトル時の動き
	m_nPattern = 0;								//行動パターン
	m_nCountMoveX = 0;
	m_nCountMoveZ = 0;

	//プレイヤー情報の読み込み
	FileLoad();

	//影の描画
	m_pShadow = CShadow::Create(m_pos, 25.0f, 25.0f, 0);
	
	//ライトの描画
	m_pSpotLight = CSpotLight::Create(m_pos, 70.0f, 70.0f, 0,this);

	//ビルボード生成
	m_pBillboord = CBillBoord::Create(m_pos, D3DXVECTOR2(30, 30),0);

	//目印敵の読み込み
	m_pDummyEnemy->Load();

	//テクスチャの読み込み
	//CMeshOrbit::Load();

	//軌跡の生成
	//m_MeshOrbit = CMeshOrbit::Create();

	//プレイヤーのワールドマトリックスの反映
	//m_MeshOrbit->SetMatRarent(&m_apModel[15]->GetMtxWorld());

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	//テクスチャの破棄
	CMeshOrbit::UnLoad();

	//目印の敵を破棄
	m_pDummyEnemy->UnLoad();

	//影を破棄
	m_pShadow->Uninit();

	m_pBillboord->Uninit();
	
	//スポットライトを破棄
	m_pSpotLight->Uninit();

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//3DモデルのUninit
			m_apModel[nCount]->Uninit();
			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	CSound *pSound = CManager::GetSound();
	CManager::MODE pMode = CManager::GetMode();
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

	//回転の値を保存
	m_rotDest = m_rot;

	//タイトルだったら
	if (pMode == CManager::MODE_TITLE)
	{
		if (m_bTitle == false)
		{
			//ニュートラルモーション
			m_nAnimnow = ENEMYANIM_MOVE;

			m_move.z += cosf(D3DX_PI * -1.0f) * 0.13f;
			m_rotDest.y = ((D3DX_PI * 0.0f));

			//位置を移動に代入
			m_pos += m_move;

			if (m_pos.z <= 25.0f)
			{
				m_bTitle = true;
			}
		}
		else if (m_bTitle == true)
		{
			if (m_nCntTime <= 180)
			{
				//ニュートラルモーション
				m_nAnimnow = ENEMYANIM_NEUTRAL;
				//移動を止める
				m_move.z = 0.0f;

			}
			else if (m_pos.z <= 350.0f)
			{
				//ニュートラルモーション
				m_nAnimnow = ENEMYANIM_MOVE;

				m_move.z -= cosf(D3DX_PI * 1.0f) * 0.13f;
				m_rotDest.y = ((D3DX_PI * -1.0f));

				//位置を移動に代入
				m_pos += m_move;
			}
			
			if (m_pos.z >= 350.0f)
			{
				m_bTitle = false;

				m_nCntTime = 0;
			}

			m_nCntTime++;
		}

		//慣性をつける
		m_move.x += (0.0f - m_move.x) * 0.2f;
		m_move.z += (0.0f - m_move.z) * 0.2f;

		//目標をチェック
		if (m_rotDest.y > D3DX_PI)
		{
			m_rotDest.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rotDest.y < -D3DX_PI)
		{
			m_rotDest.y += (D3DX_PI * 2.0f);
		}

		float fRotDest = (m_rotDest.y - m_rot.y);

		//差分をチェック
		if (fRotDest > D3DX_PI)
		{
			fRotDest -= (D3DX_PI * 2.0f);
		}
		else if (fRotDest < -D3DX_PI)
		{
			fRotDest += (D3DX_PI * 2.0f);
		}

		m_rot.y += (fRotDest) * 0.2f;

		//向きをチェック
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += (D3DX_PI * 2.0f);
		}

		//影の高さを保持しておく
		float fMeshHeight = m_pShadow->GetShadowHeight();

		//ライトの高さを保持しておく
		float fMeshSpotLight = m_pSpotLight->GetSpotLightHeight();

		//地面に足がついている場合
		if (m_bLand == true)
		{
			m_pShadow->SetPositionShadow(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
			m_pSpotLight->SetPositionSpotLight(D3DXVECTOR3(m_pos.x + sinf(m_rot.y - D3DX_PI) * LIGHT_LENGTH, fMeshSpotLight, m_pos.z + cosf(m_rot.y - D3DX_PI) * LIGHT_LENGTH));
		}
	}
	//ゲームだったら
	else if (pMode == CManager::MODE_GAME)
	{
		//前回の位置を保存
		m_posOld = m_pos;

		m_pBillboord->SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 140.0f, m_pos.z));

		//========================================
		//      ステージが変わった際
		//========================================
		if (CPlayer::GetCancelStageNext() == true)
		{
			if (m_nPattern != 1)
			{
				//NULLチェック
				if (m_pDummyEnemy != NULL)
				{
					//目印プレイヤーの削除
					m_pDummyEnemy->Uninit();
					m_pDummyEnemy = NULL;
				}
			}
		}

		//========================================
		//      ゲージを使い切った際
		//========================================
		if (CGauge::GetTired() == true)
		{
			if (m_nPattern != 1)
			{
				//NULLチェック
				if (m_pDummyEnemy != NULL)
				{
					//目印プレイヤーの削除
					m_pDummyEnemy->Uninit();
					m_pDummyEnemy = NULL;
				}
			}
		}


		//========================================
		//      プレイヤーがスキル使用
		//========================================
		if (CPlayer::GetEnemyFuture() == true)
		{
			if (m_nPattern != 1)
			{
				//目印の敵の生成
				m_pDummyEnemy = CDummyEnemy::Create(m_pos, m_rot, m_nAnimnow);
			}

			//ライトの状態を保存
			m_bLightInPast = m_bLightIn;

			//過去のX方向に移動中
			m_nCountMoveXPast = m_nCountMoveX;

			//過去のZ方向に移動中
			m_nCountMoveZPast = m_nCountMoveZ;

			//過去の移動の方法
			m_bMoveTypePast = m_bMoveType;

			//移動方法を保存
			m_MoveListPast = m_MoveList;

			//過去の位置を保存
			m_posPast = m_pos;

			//過去の向きを保存
			m_rotPast = m_rot;

			//過去のアニメーションを保存
			m_nAnimnowPast = m_nAnimnow;

			//過去の索敵状態を保存
			m_bInLengthPast = m_bInLength;

			//過去の見た時間を保存
			m_nCntLookPast = m_nCntLook;

			//過去の攻撃状態を保存
			m_bAttackPast = m_bAttack;

			//過去のカウンターを保存
			m_nCntTimePast = m_nCntTime;

			//過去の発見状態を保存
			m_bReturnPast = m_bReturn;

			//過去の行動パターンを保存
			m_nPatternPast = m_nPattern;
		}

		//========================================
		// プレイヤーがスキルをキャンセルした場合
		//========================================
		if (CPlayer::GetEnemyFuture() == false && CPlayer::GetEnemyFutureSukill() == true)
		{
			if (m_nPattern != 1)
			{
				if (m_pDummyEnemy != NULL)
				{
					//目印敵の削除
					m_pDummyEnemy->Uninit();
					m_pDummyEnemy = NULL;
				}
			}

			if (m_nPatternPast == 1 && m_bReturnPast == false && m_bInLengthPast == false)
			{
				//見失った時の反応
				m_pBillboord->SetState(CBillBoord::BILLBOORD_NONE);
			}

			//過去のX方向に移動中
			m_nCountMoveX = m_nCountMoveXPast;

			//過去のZ方向に移動中
			m_nCountMoveZ = m_nCountMoveZPast;
			
			//過去の移動の方法
			m_bMoveType = m_bMoveTypePast;
			
			//過去のライトの状態
			m_bLightIn = m_bLightInPast;

			//移動方法を入れる
			m_MoveList = m_MoveListPast;

			//過去の位置
			m_pos = m_posPast;

			//過去の向き
			m_rot = m_rotPast;

			//過去のアニメーション
			m_nAnimnow = m_nAnimnowPast;

			//過去の索敵状態
			m_bInLength = m_bInLengthPast;

			//過去の見た状態
			m_nCntLook = m_nCntLookPast;

			//攻撃状態を入れる
			m_bAttack = m_bAttackPast;

			//カウンターに過去の値を入れる
			m_nCntTime = m_nCntTimePast;

			//発見状態を過去の発見状態にする
			m_bReturn = m_bReturnPast;

			//過去の行動パターンを保存
			m_nPattern = m_nPatternPast;
		}

		//移動方法
		switch (m_MoveList)
		{
			//止まっている状態
		case MOVE_STOP:

			//指定された動きが登録されてる場合のみ
			if (m_bMoveType == false)
			{
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//どんな動きをするかが入っている
				m_bMoveType = false;
			}
			break;
			//横に動いている状態
		case MOVE_X_R:
			//指定された動きが登録されてる場合のみ
			if (m_bMoveType == false)
			{
				if (m_nCountMoveX >= 720)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_nCountMoveX = 0;
				}
				else if (m_nCountMoveX >= 660)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.x = 0.0f;
				}
				else if (m_nCountMoveX >= 360)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.x -= 0.2f;
					m_rotDest.y = ((D3DX_PI * 0.5f));
				}
				else if (m_nCountMoveX >= 300)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.x = 0.0f;
				}
				else if (m_nCountMoveX >= 0)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.x += 0.2f;
					m_rotDest.y = ((-D3DX_PI * 0.5f));
				}

				//どんな動きをするかが入っている
				m_bMoveType = false;

				//カウントを増加
				m_nCountMoveX++;
			}
			break;
		//縦に動いている状態
		case MOVE_Z_G:
			//指定された動きが登録されてる場合のみ
			if (m_bMoveType == false)
			{
				if (m_nCountMoveZ >= 720)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_nCountMoveZ = 0;
				}
				else if (m_nCountMoveZ >= 660)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.z = 0.0f;
				}
				else if (m_nCountMoveZ >= 360)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.z -= 0.2f;
					m_rotDest.y = ((D3DX_PI * 0.0f));
				}
				else if (m_nCountMoveZ >= 300)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.z = 0.0f;
				}
				else if (m_nCountMoveZ >= 0)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.z += 0.2f;
					m_rotDest.y = ((D3DX_PI * 1.0f));
				}

				//どんな動きをするかが入っている
				m_bMoveType = false;

				//カウントを増加
				m_nCountMoveZ++;
			}
			break;
		case MOVE_X_L:
			//指定された動きが登録されてる場合のみ
			if (m_bMoveType == false)
			{
				if (m_nCountMoveX >= 720)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_nCountMoveX = 0;
				}
				else if (m_nCountMoveX >= 660)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.x = 0.0f;
				}
				else if (m_nCountMoveX >= 360)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.x += 0.2f;
					m_rotDest.y = ((-D3DX_PI * 0.5f));
				}
				else if (m_nCountMoveX >= 300)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.x = 0.0f;
				}
				else if (m_nCountMoveX >= 0)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.x -= 0.2f;
					m_rotDest.y = ((D3DX_PI * 0.5f));
				}

				//どんな動きをするかが入っている
				m_bMoveType = false;

				//カウントを増加
				m_nCountMoveX++;
			}
			break;
		//縦に動いている状態
		case MOVE_Z_B:
			//指定された動きが登録されてる場合のみ
			if (m_bMoveType == false)
			{
				if (m_nCountMoveZ >= 720)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_nCountMoveZ = 0;
				}
				else if (m_nCountMoveZ >= 660)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.z = 0.0f;
				}
				else if (m_nCountMoveZ >= 360)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.z += 0.2f;
					m_rotDest.y = ((D3DX_PI * 1.0f));
				}
				else if (m_nCountMoveZ >= 300)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.z = 0.0f;
				}
				else if (m_nCountMoveZ >= 0)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.z -= 0.2f;
					m_rotDest.y = ((D3DX_PI * 0.0f));
				}

				//どんな動きをするかが入っている
				m_bMoveType = false;

				//カウントを増加
				m_nCountMoveZ++;
			}
			break;
		//ランダムに動いている状態
		case MOVE_RAND:
			//指定された動きが解除された場合
			if (m_bMoveType == true)
			{
				if (m_nCountMoveZ >= 720)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_nCountMoveZ = 0;
				}
				else if (m_nCountMoveZ >= 660)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.z = 0.0f;
				}
				else if (m_nCountMoveZ >= 360)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.z += 0.2f;
					m_rotDest.y = ((D3DX_PI * 1.0f));
				}
				else if (m_nCountMoveZ >= 300)
				{
					m_nAnimnow = ENEMYANIM_NEUTRAL;
					m_move.z = 0.0f;
				}
				else if (m_nCountMoveZ >= 0)
				{
					m_nAnimnow = ENEMYANIM_MOVE;
					m_move.z -= 0.2f;
					m_rotDest.y = ((D3DX_PI * 0.0f));
				}

				//カウントを増加
				m_nCountMoveZ++;
			}
			break;
		}

		//============================
		//     プレイヤーの移動
		//============================
		if (m_bAttack == false && m_nPattern != 1 || m_nPattern == 2)
		{//攻撃中ではない　また　行動パターンが1以外の場合
			//	//軌跡の描画するかどうか
			//	m_MeshOrbit->SetOrbitOn(false);
			if (CPlayer::GetCancelStageNext() == false)
			{
				if (m_bLightIn == true || m_nPattern == 2)
				{
					//モーションの始まりを解除
					m_bStartMotion = true;

					m_nWaitTime = 0;
					//発見した状態
					m_bInLength = true;

					//指定された動きを解除
					m_bMoveType = true;

					//カウンターの初期化
					if (m_bReturn == false)
					{
						//2周目は入らないように
						m_bReturn = true;
						//状態のカウンターを初期化
						m_nCntTime = 0;
						//モーションのキーを初期化
						m_nKey = 0;
					}

					if (m_nCntTime >= 0 && m_nCntTime <= 30)
					{
						//発見した時の反応
						m_pBillboord->SetState(CBillBoord::BILLBOORD_EXCLAMATION);
					}
					else if (m_nCntTime >= 30)
					{
						//追尾時の反応
						m_pBillboord->SetState(CBillBoord::BILLBOORD_ATTACK);
					}

					//移動量に0を入れる
					m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

					//プレイヤーのほうに向く
					m_rotDest = D3DXVECTOR3(0.0f, atan2f(-m_pos.x - -PlayerPos.x, -m_pos.z - -PlayerPos.z) + D3DX_PI, 0.0f);

					//止まる
					if (m_nAnimnow != ENEMYANIM_HOLDAGAN && m_bTarget == true)
					{
						//周りを見渡すモーション
						m_nAnimnow = ENEMYANIM_LOOKAROUND;
					}
					//銃を撃つモーションではないとき
					if (m_nAnimnow != ENEMYANIM_SHOT && m_bTarget == false)
					{
						//モーションを銃を構えるモーションに
						m_nAnimnow = ENEMYANIM_HOLDAGAN;

						m_bTarget = true;
					}
					//カウンターが目的のフレーム数になった時
					if (m_nAttackCount == 160)
					{
						//攻撃のカウンターを戻す
						m_nAttackCount = 0;
						//モーションのキーを初期化
						m_nKey = 0;

						if (CPlayer::GetDie() == false)
						{
							//攻撃モーション
							m_nAnimnow = ENEMYANIM_SHOT;
							//攻撃状態
							m_bAttack = true;
							//撃つ音
							pSound->PlaySound(CSound::SOUND_LABEL_SE_SHOOT);
							//銃の弾を撃つ
							CBullet::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 70.0f, m_pos.z/* +55.0f*/), m_rot, D3DXVECTOR3(sinf(m_rot.y - D3DX_PI) * BULLET_SPEED, 0.0f, cosf(m_rot.y - D3DX_PI) * BULLET_SPEED), D3DXVECTOR2(2, 2), 0);
						}
					}

					//攻撃のカウンター
					m_nAttackCount++;
					//状態カウンター
					m_nCntTime++;
				}
				else if (m_bInLength == true)
				{//発見した時

					//追尾時の反応
					m_pBillboord->SetState(CBillBoord::BILLBOORD_ATTACK);

					//待機時間
					if (m_nWaitTime >= 0 && m_nWaitTime <= 59 && m_bTarget == true)
					{
						//攻撃モーション
						m_nAnimnow = ENEMYANIM_LOOKAROUND;
					}
					//待機時間が１秒を超えたら動く
					if (m_nWaitTime >= 60)
					{
						if (m_pos.x <= PlayerPos.x + SEARCH_RANGE_2 && m_pos.x >= PlayerPos.x - SEARCH_RANGE_2 && m_pos.z <= PlayerPos.z + SEARCH_RANGE_2 && m_pos.z >= PlayerPos.z - SEARCH_RANGE_2 && m_move.y <= 0.1f)
						{
							//ニュートラルではない場合
							if (m_nAnimnow != ENEMYANIM_NEUTRAL || m_nAnimnow != ENEMYANIM_LOOKAROUND)
							{
								//攻撃モーション
								m_nAnimnow = ENEMYANIM_HOLDAGANWALK;
								//プレイヤーの位置に向かって移動する
								m_move = D3DXVECTOR3(sinf(atan2f(-m_pos.x - -PlayerPos.x, -m_pos.z - -PlayerPos.z)) * MOVE_WALK, 0.0f, cosf(atan2f(-m_pos.x - -PlayerPos.x, -m_pos.z - -PlayerPos.z)) * MOVE_WALK);
								//プレイヤーのほうに向く
								m_rotDest = D3DXVECTOR3(0.0f, atan2f(-m_pos.x - -PlayerPos.x, -m_pos.z - -PlayerPos.z) + D3DX_PI, 0.0f);
							}
						}
						else
						{
							//見えたカウンターを初期化
							m_nCntLook = 0;
							//見失った状態
							m_bInLength = false;
							//状態のカウンターを初期化
							m_nCntTime = 0;
						}
						//状態カウンターを加算
						m_nCntTime++;
					}
					//待機カウンターを加算
					m_nWaitTime++;
				}
				else if (m_bInLength == false && m_bStartMotion == true)
				{
					if (m_nCntTime >= 0 && m_nCntTime <= 120)
					{
						//ニュートラルじゃない場合
						if (m_nAnimnow != ENEMYANIM_NEUTRAL)
						{
							//見失った時の反応
							m_pBillboord->SetState(CBillBoord::BILLBOORD_QUESTION);
							m_bReturn = false;
							m_nWaitTime = 0;
							m_bTarget = false;
						}
					}
					else if (m_nCntTime >= 121)
					{
						//見失った時の反応
						m_pBillboord->SetState(CBillBoord::BILLBOORD_NONE);
					}

					//見失った状態
					m_bInLength = false;
					m_bLightIn = false;
					//保険でカウンターを初期化
					m_nAttackCount = 0;

					//ニュートラルじゃない場合
					if (m_nAnimnow != ENEMYANIM_NEUTRAL)
					{
						//モーションを銃を構えるモーションに
						m_nAnimnow = ENEMYANIM_LOOKAROUND;
					}

					if (m_nCntLook >= 280)
					{
						//ニュートラルモーション
						m_nAnimnow = ENEMYANIM_NEUTRAL;
					}
					else if (m_nCntLook >= 150)
					{
						//ニュートラルじゃない場合
						if (m_nAnimnow != ENEMYANIM_NEUTRAL)
						{
							//銃をしまうモーション
							m_nAnimnow = ENEMYANIM_TAKEGAN;
						}
					}
					else if (m_nCntLook == 149)
					{
						//モーションのキーを初期化
						m_nKey = 0;
					}

					m_nCntLook++;
					m_nCntTime++;
				}
			}
		}



		// 重力
		m_move.y -= cosf(0) * 2.0f;

		//位置を移動に代入
		m_pos += m_move;

		//慣性をつける
		m_move.x += (0.0f - m_move.x) * 0.2f;
		m_move.z += (0.0f - m_move.z) * 0.2f;

		//目標をチェック
		if (m_rotDest.y > D3DX_PI)
		{
			m_rotDest.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rotDest.y < -D3DX_PI)
		{
			m_rotDest.y += (D3DX_PI * 2.0f);
		}

		float fRotDest = (m_rotDest.y - m_rot.y);

		//差分をチェック
		if (fRotDest > D3DX_PI)
		{
			fRotDest -= (D3DX_PI * 2.0f);
		}
		else if (fRotDest < -D3DX_PI)
		{
			fRotDest += (D3DX_PI * 2.0f);
		}

		m_rot.y += (fRotDest) * 0.2f;

		//向きをチェック
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += (D3DX_PI * 2.0f);
		}

		// 地面の高さを取得
		CollisitionMesh();
		//床の当たり判定
		//CollisitionGround();
		// 壁の当たり判定
		CollisitionWall();
		// オブジェクトの当たり判定
		CollisitionObject3D(&m_pos, &m_posOld, &m_move);
		// アイテムの当たり判定
		CollisitionItem();

		//影の高さを保持しておく
		float fMeshHeight = m_pShadow->GetShadowHeight();

		//ライトの高さを保持しておく
		float fMeshSpotLight = m_pSpotLight->GetSpotLightHeight();

		//地面に足がついている場合
		if (m_bLand == true)
		{
			m_pShadow->SetPositionShadow(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
			m_pSpotLight->SetPositionSpotLight(D3DXVECTOR3(m_pos.x + sinf(m_rot.y - D3DX_PI) * LIGHT_LENGTH, fMeshSpotLight, m_pos.z + cosf(m_rot.y - D3DX_PI) * LIGHT_LENGTH));
		}
	}

	m_nMotionType = m_nAnimnow;

	//モーション更新
	UpdateMotion();
}
//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//計算洋間鳥kk数

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//モデルの描画
			m_apModel[nCount]->Draw(1.0f);
		}
	}
}
//=============================================================================
//	メッシュの当たり判定
//=============================================================================
void CEnemy::CollisitionMesh(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(MESH_PRIOTITY);

	//ジャンプをfalseに
	m_bJump = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがメッシュだったら
			if (pScene->GetObjType() == OBJTYPE_MESH)
			{
				//プレイヤーのHightを入れる
				if (((CMesh*)pScene)->GetHeight(m_pos))
				{
					//ジャンプしている状態にする
					m_bJump = true;
					//落ちたときにmoveを初期化する
					m_move.y = 0.0f;

					if (m_bJump == true)
					{
						m_pShadow->SetPositionShadow(m_pos);
						m_pSpotLight->SetPositionSpotLight(m_pos);
					}
				}
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
//	壁の当たり判定
//=============================================================================
void CEnemy::CollisitionWall(void)
{
	CScene *pScene;
	//プライオリティーチェック
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_WALL)
			{
				((CWall*)pScene)->CollisionWall(&m_pos, &m_posOld, &m_move, 20.0f);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
//	床の当たり判定
//=============================================================================
void CEnemy::CollisitionGround(void)
{
	CScene *pScene;
	bool bWater = false;

	//プライオリティーチェック
	pScene = CScene::GetTop(GROUND_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプが床だったら
			if (pScene->GetObjType() == OBJTYPE_GROUND)
			{
				((CGround*)pScene)->CollisionGround(&m_pos, &m_posOld, &m_move);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
//	オブジェクトの当たり判定
//=============================================================================
void CEnemy::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//変数宣言
	bool bLand = false;

	//bLandの初期化処理
	//m_bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがメッシュだったら
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				//オブジェクトのあたる判定
				bLand = ((CObject*)pScene)->CollisionObject(pPos, pPosOld, pMove);

				//着地を共有する
				if (bLand)
				{
					m_bLand = bLand;
				}
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
//	アイテムの当たり判定
//=============================================================================
void CEnemy::CollisitionItem(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(4);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがアイテムだったら
			if (pScene->GetObjType() == OBJTYPE_ITEM)
			{
				//当たり判定
				if (((CItem*)pScene)->CollisionItem(&m_pos, &m_posOld, &m_move))
				{
					pScene->Uninit();
				}
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
//	位置を初期化
//=============================================================================
void CEnemy::DeleteEnemy(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(2);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_ENEMY)
			{
				pScene->Uninit();
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nPattern, MoveList movelist)
{
	CEnemy *pEnemy = NULL;

	//NULLチェック
	if (pEnemy == NULL)
	{//メモリの動的確保

		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{
			//オブジェクトクラスの生成
			pEnemy->Init();
			//位置の反映
			pEnemy->m_pos = pos;
			//向きの反映
			pEnemy->m_rot = rot;
			//敵の行動パターン
			pEnemy->m_nPattern = nPattern;
			//移動パターン
			pEnemy->m_MoveList = movelist;
		}
	}

	return pEnemy;
}
//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// メッシュの開放
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}
//=============================================================================
// プレイヤーのモーション
//=============================================================================
void CEnemy::UpdateMotion(void)
{
	//モーション
	KEY *pKey, *pNextKey;
	float fRateMotion;
	float fDiffMotion;
	D3DXVECTOR3 rotmotion;
	D3DXVECTOR3 posmotion;
	//D3DXVECTOR3 posParent;


	//キーが最大数を上回らないように
	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	//モーション更新
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apModel[nCntParts] != NULL)
		{
			//現在のキーを取得
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
			//次のキーを取得
			pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

			//現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
			fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

			//ROT
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->frotX - pKey->frotX;
			//相対値を差分を使って各要素の値を算出
			rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

			//POS
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->fposX - pKey->fposX;
			//相対値を差分を使って各要素の値を算出
			posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);


			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->frotY - pKey->frotY;
			//相対値を差分を使って各要素の値を算出
			rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
			//POS
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->fposY - pKey->fposY;
			//相対値を差分を使って各要素の値を算出
			posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);


			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->frotZ - pKey->frotZ;
			//相対値を差分を使って各要素の値を算出
			rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
			//POS
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->fposZ - pKey->fposZ;
			//相対値を差分を使って各要素の値を算出
			posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);


			//パーツを動かす
			m_apModel[nCntParts]->Setrot(rotmotion);

			//POS
			m_apModel[nCntParts]->SetPos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x,
				m_OffSetPos[nCntParts].y + posmotion.y,
				m_OffSetPos[nCntParts].z + posmotion.z));

		}
	}

	//ループの判定
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{
	case true:
		//ループする
		//フレームを進める
		m_nCountFlame++;
		//キーの更新
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
			{
				m_nKey = 0;
			}
			else
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}

		break;
	case false:
		//ループしない
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//フレームを進める
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{
			if (m_nAnimnow == ENEMYANIM_SHOT)
			{//攻撃モーション
				m_nAttackDelay++;
				if (m_nAttackDelay > 26)
				{
					m_bAttack = false;
					m_nAttackDelay = 0;
				}
			}
			m_bMotionEnd = true;
		}
		//キーの更新
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}
		break;
	}

#ifdef  _DEBUG
	CDebugProc::Print(" Numキー  : (%d)\n", m_nKey);
	CDebugProc::Print(" m_nCountFlame  : (%d)\n", m_nCountFlame);

#endif

}

//=============================================================================
// ファイル読み込み
//=============================================================================
void CEnemy::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	D3DXVECTOR3 ParentPos;	//親の位置情報を取得
#if 1
	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; )
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				g_nNumEnemyModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumEnemyModel; nCntModel++)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り戻す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("MODEL_FILENAME = ");

						//文字列を設定
						strcpy(aStr, pStrcur);

						//必要な文字列の最後の文字までの文字数を数える
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//文字列を取り戻す
						strcpy(aStr, pStrcur);

						//最後の文字にNULL文字を入れる
						aStr[nNullNum - 1] = '\0';

						//対象の文字列から抜き出し
						strcpy(&g_aFileNameEnemyModel[nCntModel][0], aStr);

						// Xファイルの読み込み
						D3DXLoadMeshFromX(&g_aFileNameEnemyModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMat[nCntModel],
							NULL,
							&m_nNumMat[nCntModel],
							&m_pMesh[nCntModel]);
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}


			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_PARTS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEXを読み込み
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("INDEX = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								nIndex = atoi(pStrcur);
							}
							//PARENTを読み込み
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("PARENT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							//POSを読み込み
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("POS = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							//ROTを読み込み
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("ROT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);
							}
							//パーツセット終了
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{
								//NULLチェック
								if (m_apModel[nIndex] == NULL)
								{//動的確保
									m_apModel[nIndex] = new CModel;
									//NULLチェック
									if (m_apModel[nIndex] != NULL)
									{
										//モデルの生成
										m_apModel[nIndex]->BindModel(m_pMesh[nIndex], m_pBuffMat[nIndex], m_nNumMat[nIndex]);
										m_apModel[nIndex]->Init();
									}
								}

								//モデルを生成	オフセット設定
								/*m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
										m_pos.y + m_aKayOffset[nIndex].fposY,
										m_pos.z + m_aKayOffset[nIndex].fposZ), m_rot);*/

								m_apModel[nIndex]->SetPos(D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
									m_pos.y + m_aKayOffset[nIndex].fposY,
									m_pos.z + m_aKayOffset[nIndex].fposZ));

								//posを代入
								ParentPos = m_apModel[nIndex]->GetPos();
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//モデルを割り当て
								m_apModel[nIndex]->BindModel(m_pMesh[nIndex], m_pBuffMat[nIndex], m_nNumMat[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{
									//モデルの親を指定
									m_apModel[nIndex]->SetParent(NULL);
									ParentPos = m_apModel[nIndex]->GetPos();
								}
								else
								{
									//モデルの親を指定
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}

								break;
							}
						}
					}
					//キャラクターセット終了
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}

			//モーション読み込み
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MOTIONSET");

				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("LOOP = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
					}
					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_KEY = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
						//文字列を取り出す
						strcpy(aStr, pStrcur);
					}

					//キーの設定
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{
							//頭出し
							pStrcur += strlen("KEYSET");
							//文字列の先頭を設定
							strcpy(aStr, pStrcur);
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("FRAME = ");

								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);

								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
							}

							//パーツ分回す
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);

									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{
										//頭出し
										pStrcur += strlen("POS = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									//ROTを読み込み
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{
										//頭出し
										pStrcur += strlen("ROT = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{
										//頭出し
										pStrcur += strlen("END_KEY");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
										//パーツのカウントを進める
										nCntParts++;
									}
								}
								else
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
								//カウントを進める
								nCntKey++;
							}
						}
						else
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						//モーションの情報をセット
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						nCntMotion++;
						break;
					}
				}
			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//ファイルが開けなかった
		printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
#endif

}

//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CEnemy::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CEnemy::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CEnemy::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += (int)strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += (int)strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}
