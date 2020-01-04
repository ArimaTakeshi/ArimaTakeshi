//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 有馬武志　/ 目黒
//
//=============================================================================
#include "scene.h"
#include "player.h"
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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_SPEED     (1.0f)
#define JUMP_POWER		(26.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH	CPlayer::m_pMesh[MAX_PARTS] = {};		//メッシュ情報へのポインタ
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PARTS] = {};	//マテリアルの情報へのポインタ
DWORD CPlayer::m_nNumMat[MAX_PARTS] = {};			//マテリアルの情報数
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CPlayer::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//--------------------------------------------
//グローバル変数
//--------------------------------------------
int g_nNumModel;
char g_aFileNameModel[MAX_PARTS][256];


//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CPlayer::CPlayer(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	//値の初期化
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_apModel[nCount] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//過去の位置

	CGame::GetPlayer() = this;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向き
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//過去の位置
	m_bJump = true;											//ジャンプの状態
	m_bLand = true;											//着地の状態
	m_bInvincible = false;
	m_bMotionEnd = true;
	m_nAnimnow = PLAYERANIM_NEUTRAL;
	m_nAttackDelay = 0;
	//プレイヤー情報の読み込み
	FileLoad();

	//影の描画
	CShadow::Create(m_pos, 25.0f, 25.0f, 0);

	CManager::MODE pMode = CManager::GetMode();

	if (pMode == CManager::MODE_RESULT)
	{
		m_nAnimnow = PLAYERANIM_RESULTUP;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
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
void CPlayer::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	CSound *pSound = CManager::GetSound();
	CManager::MODE pMode = CManager::GetMode();

	//ゲームだったら
	if (pMode == CManager::MODE_GAME)
	{
		//前回の位置を保存
		m_posOld = m_pos;

		//壁のあたり判定
		if (m_pos.z >= 280)
		{
			m_pos.z = 280;
		}
		if (m_pos.z <= -280)
		{
			m_pos.z = -280;
		}
		if (m_pos.x >= 11480)
		{
			m_pos.x = 11480;
		}
		if (m_pos.x <= -280)
		{
			m_pos.x = -280;
		}


		//============================
		//     視点の左右前後移動
		//============================
		if (m_bAttack == false)
		{

			//移動処理
			if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
			{//矢印の上							↓上移動
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_MOVE;
				}
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.25f) * MODEL_SPEED;
					m_move.z += cosf(D3DX_PI * 0.25f) * MODEL_SPEED;
					m_rot.y = ((D3DX_PI * -0.75f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.25f) * MODEL_SPEED;
					m_move.z += cosf(-D3DX_PI * 0.25f) * MODEL_SPEED;
					m_rot.y = ((D3DX_PI * 0.75f));
				}
				else
				{
					m_move.x += sinf(D3DX_PI * 0.0f) * MODEL_SPEED;
					m_move.z += cosf(D3DX_PI * 0.0f) * MODEL_SPEED;
					m_rot.y = ((D3DX_PI * -1.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
			{//矢印の下							 ↓上移動
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_MOVE;
				}
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.75f) * MODEL_SPEED;
					m_move.z += cosf(D3DX_PI * 0.75f) * MODEL_SPEED;
					m_rot.y = ((D3DX_PI * -0.25f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.75f) * MODEL_SPEED;
					m_move.z += cosf(-D3DX_PI * 0.75f) * MODEL_SPEED;
					m_rot.y = ((D3DX_PI * 0.25f));
				}
				else
				{
					m_move.x += sinf(-D3DX_PI * 1.0f) * MODEL_SPEED;
					m_move.z += cosf(-D3DX_PI * 1.0f) * MODEL_SPEED;
					m_rot.y = ((D3DX_PI * 0.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
			{//矢印の右							↓ 右移動
				m_move.x += sinf(D3DX_PI * 0.5f) * MODEL_SPEED;
				m_move.z += cosf(D3DX_PI * 0.5f) * MODEL_SPEED;
				m_rot.y = ((D3DX_PI * -0.5f));
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_MOVE;
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
			{//矢印の左							 ↓ 左移動
				m_move.x += sinf(-D3DX_PI * 0.5f) * MODEL_SPEED;
				m_move.z += cosf(-D3DX_PI * 0.5f) * MODEL_SPEED;
				m_rot.y = ((D3DX_PI * 0.5f));
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_MOVE;
				}
			}
			else if (pCInputJoyPad->GetPress(CInputJoypad::STICK_L_UP) == true || pCInputJoyPad->GetPress(CInputJoypad::STICK_L_DOWN) == true
				|| pCInputJoyPad->GetPress(CInputJoypad::STICK_L_RIGHT) == true || pCInputJoyPad->GetPress(CInputJoypad::STICK_L_LEFT) == true)
			{//ジョイコン
				CDebugProc::Print("反応している\n");
				m_move.x += sinf(pCInputJoyPad->GetLeftAxiz()) * MODEL_SPEED;
				m_move.z -= cosf(pCInputJoyPad->GetLeftAxiz()) * MODEL_SPEED;
				//向き
				m_rot.y = (-D3DX_PI * (pCInputJoyPad->GetLeftAxiz() / D3DX_PI));
				if ((m_bJump || m_bLand))
				{
					m_nAnimnow = PLAYERANIM_MOVE;
				}
			}
			else
			{
				if ((m_bJump || m_bLand) && m_bAttack == false && m_bResult == false)
				{
					//待機モーション
					m_nAnimnow = PLAYERANIM_NEUTRAL;
				}
			}



			if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_SPACE) == true && (m_bJump || m_bLand)
				|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_A) == true && (m_bJump || m_bLand))
			{// ジャンプ
				m_move.y = cosf(D3DX_PI) * -JUMP_POWER;
				//ジャンプモーション
				m_nKey = 0;
				m_nAnimnow = PLAYERANIM_JUMP;
				m_bJump = false;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_JUMP);
			}
		}

		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_V) == true && (m_bJump || m_bLand) && m_bAttack == false
			|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_B) == true && (m_bJump || m_bLand) && m_bAttack == false)
		{
			//攻撃モーション
			m_nKey = 0;
			m_nAnimnow = PLAYERANIM_ATTACK;
			m_bAttack = true;
		}

#if 0
		//リザルトの動き確認用
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_R) == true)
		{
			//モードリザルト
			m_bResult = true;
		}
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_G) == true)
		{
			//リザルトモーション
			m_nAnimnow = PLAYERANIM_RESULTUP;
		}
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_B) == true)
		{
			//リザルトモーション
			m_nAnimnow = PLAYERANIM_RESULTDOWN;
		}
#endif

		if (m_bInvincible)
		{
			if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
			{//矢印の上							↓上移動
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.25f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.25f) * 3.0f;
					m_rot.y = ((D3DX_PI * -0.75f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 0.25f) * 3.0f;
					m_rot.y = ((D3DX_PI * 0.75f));
				}
				else
				{
					m_move.x += sinf(D3DX_PI * 0.0f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.0f) * 3.0f;
					m_rot.y = ((D3DX_PI * -1.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
			{//矢印の下							 ↓上移動
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.75f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.75f) * 3.0f;
					m_rot.y = ((D3DX_PI * -0.25f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 0.75f) * 3.0f;
					m_rot.y = ((D3DX_PI * 0.25f));
				}
				else
				{
					m_move.x += sinf(-D3DX_PI * 1.0f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 1.0f) * 3.0f;
					m_rot.y = ((D3DX_PI * 0.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
			{//矢印の右							↓ 右移動
				m_move.x += sinf(D3DX_PI * 0.5f) * 3.0f;
				m_move.z += cosf(D3DX_PI * 0.5f) * 3.0f;
				m_rot.y = ((D3DX_PI * -0.5f));
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
			{//矢印の左							 ↓ 左移動
				m_move.x += sinf(-D3DX_PI * 0.5f) * 3.0f;
				m_move.z += cosf(-D3DX_PI * 0.5f) * 3.0f;
				m_rot.y = ((D3DX_PI * 0.5f));
			}

			if (pCInputKeyBoard->GetKeyboardPress(DIK_Q) == true)
			{// プレイヤーの上昇
				m_pos.y += 5.0f;
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_E) == true)
			{// プレイヤーの下降
				m_pos.y -= 5.0f;
			}
		}
#ifdef _DEBUG

		if (pCInputKeyBoard->GetKeyboardPress(DIK_Z) == true && pCInputKeyBoard->GetKeyboardTrigger(DIK_X) == true)
		{
			m_bInvincible = m_bInvincible ? false : true;
		}
#endif
		if (m_bInvincible == false)
		{
			// 重力
			m_move.y -= cosf(0) * 2.0f;
		}

		//位置を移動に代入
		m_pos += m_move;

		//慣性をつける
		m_move.x += (0.0f - m_move.x) * 0.2f;
		m_move.z += (0.0f - m_move.z) * 0.2f;


		//影の高さを保持しておく
		float fMeshHeight = CShadow::GetShadowHeight();

		if (m_bJump == false)
		{
			CShadow::SetPositionShadow(D3DXVECTOR3(m_pos.x, fMeshHeight, m_pos.z));
		}
		if (m_bLand == true)
		{
			CShadow::SetPositionShadow(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z));
		}

		if (m_bInvincible == false)
		{
			// 地面の高さを取得
			CollisitionMesh();
			//床の当たり判定
			CollisitionGround();
			// 壁の当たり判定
			CollisitionWall();
			// オブジェクトの当たり判定
			CollisitionObject3D(&m_pos, &m_posOld, &m_move);
			// アイテムの当たり判定
			CollisitionItem();
		}

		//高さを上げる
		if (pCInputKeyBoard->GetKeyboardPress(DIK_Y) == true)
		{
			CGame::GetMeshField()->SetHeight(m_pos, 1.0f, 100.0f);
		}
		//高さを上げる
		if (pCInputKeyBoard->GetKeyboardPress(DIK_H) == true)
		{
			CGame::GetMeshField()->SetHeight(m_pos, -1.0f, 100.0f);
		}

		//モデルのデバック位置
		CDebugProc::Print("プレイヤーposの位置 :【%.1f】【%.1f】【%.1f】\n", m_pos.x, m_pos.y, m_pos.z);
		CDebugProc::Print("%s\n", m_bInvincible ? "true" : "false");
	}
	else if (pMode == CManager::MODE_RESULT)
	{//リザルトだったら
		//選択している番号を取得
		int SelectNum = CSerect::Get();
		if (SelectNum == 0 && m_nAnimnow != PLAYERANIM_RESULTUP)
		{
			//上
			m_nAnimnow = PLAYERANIM_RESULTUP;
		}
		else if (SelectNum == 1 && m_nAnimnow != PLAYERANIM_RESULTDOWN)
		{
			//下
			m_nAnimnow = PLAYERANIM_RESULTDOWN;
		}
	}
	else if (pMode == CManager::MODE_RANKING)
	{//ランキングだったら
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_SPACE) == true
			|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_A) == true)
		{// ジャンプ
			if (m_nAnimnow != PLAYERANIM_BAKUTEN)
			{	//バンザイ

				//m_nAnimnow = PLAYERANIM_BAKUTEN;
				//m_bMotionEnd = false;
			}
		}
		else if (m_nAnimnow != PLAYERANIM_BANZAI && m_bMotionEnd == true)
		{	//バンザイ
			m_nAnimnow = PLAYERANIM_BANZAI;
		}
	}
	m_nMotionType = m_nAnimnow;
	//モーション更新
	UpdateMotion();
}
//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

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
			m_apModel[nCount]->Draw();
		}
	}
}
//=============================================================================
//	メッシュの当たり判定
//=============================================================================
void CPlayer::CollisitionMesh(void)
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
						CShadow::SetPositionShadow(m_pos);
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
void CPlayer::CollisitionWall(void)
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
void CPlayer::CollisitionGround(void)
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
void CPlayer::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//変数宣言
	bool bLand = false;

	//bLandの初期化処理
	m_bLand = false;

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
void CPlayer::CollisitionItem(void)
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
//===============================================================================
//　クリエイト
//===============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{//メモリの動的確保

		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			//オブジェクトクラスの生成
			pPlayer->Init();
			//位置を代入
			pPlayer->SetPos(pos);
		}
	}

	return pPlayer;
}
//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CPlayer::UnLoad(void)
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
void CPlayer::UpdateMotion(void)
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
			if (m_nAnimnow == PLAYERANIM_ATTACK)
			{//攻撃モーション
				m_nAttackDelay++;
				if (m_nAttackDelay > 20)
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
void CPlayer::FileLoad(void)
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
						//D3DXVECTOR3 posFile[MAX_PARTS] = {};
						//D3DXVECTOR3 rotFile[MAX_PARTS] = {};

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
				g_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
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
						strcpy(&g_aFileNameModel[nCntModel][0], aStr);

						// Xファイルの読み込み
						D3DXLoadMeshFromX(&g_aFileNameModel[nCntModel][0],
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
										m_pos.z + m_aKayOffset[nIndex].fposZ), m_rot);
*/
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
char *CPlayer::ReadLine(FILE *pFile, char *pDst)
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
char * CPlayer::GetLineTop(char * pStr)
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
int CPlayer::PopString(char * pStr, char * pDest)
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
