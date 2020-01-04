//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 有馬武志
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
#include "meshorbit.h"
#include "life.h"
#include "gauge.h"
#include "action2D.h"
#include "fade.h"
#include "blood.h"
#include "serect.h"
#include "guide.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_WALK			(0.2f)
#define MODEL_RAN			(1.0f)
#define MODEL_SQUAT			(0.1f)
#define MODEL_SNEAK			(0.1f)
#define JUMP_POWER			(26.0f)
#define TIRED_TIME_START	(120)
#define TIRED_TIME_END		(121)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH	CPlayer::m_pMesh[MAX_PARTS] = {};					//メッシュ情報の初期化
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PARTS] = {};				//マテリアルの情報の初期化
DWORD CPlayer::m_nNumMat[MAX_PARTS] = {};						//マテリアルの情報数の初期化
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
D3DXVECTOR3 CPlayer::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きの初期化
D3DXVECTOR3 CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動の初期化
CMeshOrbit *CPlayer::m_MeshOrbit = NULL;						//軌跡の初期化
CSerect *CPlayer::m_pSerect = NULL;								//セレクトのポインタ
bool CPlayer::m_bFuture = false;								//未来の状態の初期化
bool CPlayer::m_bFutureCancel = false;							//未来の状態のキャンセルの初期化
bool CPlayer::m_bCancelHeal = false;							//キャンセル時の回復の初期化
bool CPlayer::m_bActionFade = false;							//アクションフェードの起動の初期化
bool CPlayer::m_bEnemyFuture = false;							//敵の未来の初期化
bool CPlayer::m_bEnemyFutureSukill = false;						//敵の未来中にスキルキャンセルの初期化
bool CPlayer::m_bLifeFuture = false;							//未来の体力の初期化
bool CPlayer::m_bLifeFutureSukill = false;						//体力の未来中にスキルキャンセルの初期化
bool CPlayer::m_bDie = false;									//死んだ状態
bool CPlayer::m_bDieSukill = false;								//死んだ状態
bool CPlayer::m_bStageNext = false;								//ステージが変わった際の初期化
bool CPlayer::m_bOverResult = false;							//死んだ後のリザルト

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

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//過去の位置
	m_fSpeedMove = 0.0f;
	m_fStageNext = false;
	m_bStageReset = false;
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

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//過去の位置
	m_bJump = true;										//ジャンプの状態
	m_bLand = true;										//着地の状態
	m_bInvincible = false;								//チートの状態
	m_fStageNext = false;								//次のステージ
	m_bMotionEnd = true;								//モーション終了
	m_nAnimnow = PLAYERANIM_NEUTRAL;					//ニュートラル状態
	m_nAttackDelay = 0;									//攻撃
	m_bSukillActivate = false;							//スキルを使用したかどうか
	m_bGaugeOnOff = false;								//ゲージを使用したかしていないかの状態
	m_nDieTimer = 0;									//死んだ後の待機時間
	m_nDieSukillTimer = 0;								//スキル中に死んだ後の経過時間
	m_bSukillDie = false;

	//プレイヤー情報の読み込み
	FileLoad();

	CManager::MODE pMode = CManager::GetMode();

	//テクスチャの読み込み
	CMeshOrbit::Load();

	//血のテクスチャの読み込み
	m_pBlood->Load();

	//セレクトのテクスチャの読み込み
	m_pSerect->Load();

	//目印プレイヤーの読み込み
	m_pDummyPlayer->Load();

	//軌跡の生成
	//m_MeshOrbit = CMeshOrbit::Create();

	//プレイヤーのワールドマトリックスの反映
	//m_MeshOrbit->SetMatRarent(&m_apModel[0]->GetMtxWorld());

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//テクスチャの破棄
	CMeshOrbit::UnLoad();

	//セレクトのテクスチャの破棄
	m_pSerect->UnLoad();

	//目印プレイヤーの破棄
	m_pDummyPlayer->UnLoad();

	//血のテクスチャの破棄
	m_pBlood->UnLoad();

	m_bFuture = false;			//未来の状態を初期化
	m_bFutureCancel = false;	//未来の状態のキャンセル
	m_bCancelHeal = false;		//キャンセル時の回復
	m_bActionFade = false;		//フェードを削除
	m_bDie = false;				//生死の状態を初期化
	m_bOverResult = false;		//死んだ後のリザルト画面

	//セレクトの削除
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

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
	CObject *pObject = CGame::Get3DObject();
	CCamera *pCamera = CManager::GetCamera();
	CEnemy *pEnemy = CGame::GetEnemy();
	m_bEnemyFuture = false;
	m_bEnemyFutureSukill = false;

	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//回転の値を保存
	m_rotDest = m_rot;

	if (pMode == CManager::MODE_TITLE)
	{
		//移動モーション
		m_nAnimnow = PLAYERANIM_SIT;

		m_rot.y = ((D3DX_PI * -0.5f));
	}
	//ゲームだったら
	else if (pMode == CManager::MODE_GAME)
	{
		//前回の位置を保存
		m_posOld = m_pos;

		//============================
		//    未来予知スキル使用
		//============================
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_G) == true && CGauge::GetGaugeDownOn() == false && m_bDie == false && m_bStageNext == false || 
			pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_X) == true && CGauge::GetGaugeDownOn() == false && m_bDie == false && m_bStageNext == false)
		{
			//スキル音
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILL);

			//スキルを発動
			m_bSukillActivate = true;

			//ゲージを減らすモードに入る
			m_bGaugeOnOff = true;

			//ゲームの状態を渡す
			CGauge::SetGaugeOnOff(m_bGaugeOnOff);

			//現在の位置を未来に入れる
			m_posFuture = m_pos;
			//現在の向きを未来に入れる
			m_rotFuture = m_rot;

			//生死の状態を入れる
			m_bDieSukill = m_bDie;

			//敵の未来を実行
			m_bEnemyFuture = true;

			//未来のHP
			m_bLifeFuture = true;

			//トラップの状態を保存
			m_bTrapSukill = CGround::GetTrap();

			//未来のフェード
			CAction2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);

			//目印を生成
			m_pDummyPlayer = CDummyPlayer::Create(m_pos,m_rot,m_nAnimnow);
		}

		CDebugProc::Print("m_bFutureCancel = %s\n", m_bFutureCancel ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bCancelHeal = %s\n", m_bCancelHeal ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bActionFade = %s\n", m_bActionFade ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bStageNext = %s\n", m_bStageNext ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bStageNext = %s\n", m_bStageNext ? "TRUE" : "FALSE"); 
		CDebugProc::Print("m_bEnemyFuture = %s\n", m_bEnemyFuture ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bEnemyFutureSukill = %s\n", m_bEnemyFutureSukill ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bSukillActivate = %s\n", m_bSukillActivate ? "TRUE" : "FALSE");

		//============================
		// 未来予知スキルのキャンセル
		//============================
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_G) == true && CGauge::GetGaugeDownOn() == true && m_bFutureCancel == false && m_bCancelHeal == false && m_bStageNext == false ||
			pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_X) == true && CGauge::GetGaugeDownOn() == true && m_bFutureCancel == false && m_bCancelHeal == false && m_bStageNext == false || m_bSukillDie == true)
		{
			//スキルキャンセル音
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILLCANCEL);

			m_bSukillDie = false;

			//血を削除
			if (m_pBlood != NULL)
			{
				m_nDieSukillTimer = 0;
				m_pBlood->Uninit();
				m_pBlood = NULL;
			}

			//スキルを無効化
			m_bSukillActivate = false;

			//未来のキャンセル
			m_bFutureCancel = true;

			//未来の時間回復を実行
			m_bCancelHeal = true;

			//アクションフェードを実行
			m_bActionFade = true;

			//敵の未来を実行
			m_bEnemyFuture = false;

			//敵の未来中にキャンセル実行
			m_bEnemyFutureSukill = true;

			//体力の未来中にキャンセル実行
			m_bLifeFutureSukill = true;

			//生死の状態を入れる
			m_bDie = m_bDieSukill;

			//過去のトラップの状態を入れる
			CGround::SetTrap(m_bTrapSukill);

			//NULLチェック
			if (m_pDummyPlayer != NULL)
			{
				//目印の削除
				m_pDummyPlayer->Uninit();
				m_pDummyPlayer = NULL;
			}

			//未来予知のリキャストタイム
			CGauge::SetRecastTime(0);
		}

		//キャンセルが入った場合
		if (m_bFutureCancel == true && m_bStageNext == false)
		{
			//過去の位置に戻す
			m_pos = m_posFuture;

			//過去の向きに戻す
			m_rot = m_rotFuture;

			if (m_bDie == true)
			{
				//ニュートラルモーションに戻す
				m_nAnimnow = PLAYERANIM_DIE;
			}
			else if (m_bDie == false)
			{
				//アニメーションを疲れ状態にする
				m_nAnimnow = PLAYERANIM_TIRED;
			}

			//3秒の待機時間を設ける
			if (m_nFutureStandTime <= TIRED_TIME_END&& m_nFutureStandTime >= TIRED_TIME_START)
			{
				//動けなくする
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//待機時間の初期化処理
				m_nFutureStandTime = 0;

				//未来のキャンセルを戻す
				m_bFutureCancel = false;

				//未来の時間回復を実行
				m_bCancelHeal = true;

				//ニュートラルモーションに戻す
				m_nAnimnow = PLAYERANIM_NEUTRAL;
			}

			//カウントの増加
			m_nFutureStandTime++;
		}

		//============================
		// ステージが切り替わった時のみ
		//============================
		if (m_bStageNext == true)
		{
			//スキルの発動を無効化
			m_bSukillActivate = false;

			//未来のキャンセルを戻す
			m_bFutureCancel = false;

			//未来の時間回復を実行
			m_bCancelHeal = true;

			//アクションフェードを実行
			m_bActionFade = true;

			//NULLチェック
			if (m_pDummyPlayer != NULL)
			{
				//目印の削除
				m_pDummyPlayer->Uninit();
				m_pDummyPlayer = NULL;
			}
		}

		//============================
		// 　ゲージがなくなった際
		//============================
		if (CGauge::GetTired() == true && m_bStageNext == false)
		{
			//スキルキャンセル音
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILLCANCEL);

			//スキルの発動を無効化
			m_bSukillActivate = false; 

			if (m_bDie == true)
			{
				//ニュートラルモーションに戻す
				m_nAnimnow = PLAYERANIM_DIE;
			}
			else if (m_bDie == false)
			{
				//アニメーションを疲れ状態にする
				m_nAnimnow = PLAYERANIM_TIRED;
			}

			//NULLチェック
			if (m_pDummyPlayer != NULL)
			{
				//目印の削除
				m_pDummyPlayer->Uninit();
				m_pDummyPlayer = NULL;
			}

			//3秒の待機時間を設ける
			if (m_nFutureStandTime <= TIRED_TIME_END && m_nFutureStandTime >= TIRED_TIME_START)
			{
				//ニュートラルモーションに戻す
				m_nAnimnow = PLAYERANIM_NEUTRAL;

				m_nFutureStandTime = 0;

				CGauge::SetTired(false);
			}
			//カウントの増加
			m_nFutureStandTime++;
		}

		//============================
		//     プレイヤーの移動
		//============================
		if (m_bAttack == false && m_nAnimnow != PLAYERANIM_TIRED)
		{
			//軌跡の描画するかどうか
			//m_MeshOrbit->SetOrbitOn(true);

			//デバック用
			if (pCInputKeyBoard->GetKeyboardPress(DIK_K) == true)
			{
				CGauge::AddGauge(150);
			}

			//モーション時のスピード
			if (m_nAnimnow == PLAYERANIM_WALK)
			{
				m_fSpeedMove = MODEL_WALK;
			}
			else if (m_nAnimnow == PLAYERANIM_RUN)
			{
				m_fSpeedMove = MODEL_RAN;
			}
			else if (m_nAnimnow == PLAYERANIM_SNEAK)
			{
				m_fSpeedMove = MODEL_SNEAK;
			}
			else if (m_nAnimnow == PLAYERANIM_SQUAT)
			{
				m_fSpeedMove = MODEL_SQUAT;
			}

			if (pCamera->GetCameraPosV() != D3DXVECTOR3(59.0f, 146.0f, 568.0f) && pCamera->GetCameraPosV() != D3DXVECTOR3(905.0f, 190.0f, 540.0f)
				&& pCamera->GetCameraPosV() != D3DXVECTOR3(470.0f, 240.0f, 660.0f) && pCamera->GetCameraPosV() != D3DXVECTOR3(-1040.0f, 170.0f, 400.0f) && m_bDie == false)
			{
				//移動処理
				if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
				{//矢印の上							↓上移動
					if ((m_bJump || m_bLand))
					{
						//移動モーション
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//走るモーション
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//しゃがむモーション
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}

					if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
					{
						m_move.x += sinf(D3DX_PI * 0.25f) * m_fSpeedMove;
						m_move.z += cosf(D3DX_PI * 0.25f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * -0.75f));
					}
					else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
					{
						m_move.x += sinf(-D3DX_PI * 0.25f) * m_fSpeedMove;
						m_move.z += cosf(-D3DX_PI * 0.25f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * 0.75f));
					}
					else
					{
						m_move.x += sinf(D3DX_PI * 0.0f) * m_fSpeedMove;
						m_move.z += cosf(D3DX_PI * 0.0f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * -1.0f));
					}
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
				{//矢印の下							 ↓上移動
					if ((m_bJump || m_bLand))
					{
						//移動モーション
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//走るモーション
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//しゃがむモーション
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
					if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
					{
						m_move.x += sinf(D3DX_PI * 0.75f) * m_fSpeedMove;
						m_move.z += cosf(D3DX_PI * 0.75f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * -0.25f));
					}
					else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
					{
						m_move.x += sinf(-D3DX_PI * 0.75f) * m_fSpeedMove;
						m_move.z += cosf(-D3DX_PI * 0.75f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * 0.25f));
					}
					else
					{
						m_move.x += sinf(-D3DX_PI * 1.0f) * m_fSpeedMove;
						m_move.z += cosf(-D3DX_PI * 1.0f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * 0.0f));
					}
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{//矢印の右							↓ 右移動
					m_move.x += sinf(D3DX_PI * 0.5f) * m_fSpeedMove;
					m_move.z += cosf(D3DX_PI * 0.5f) * m_fSpeedMove;
					m_rotDest.y = ((D3DX_PI * -0.5f));
					if ((m_bJump || m_bLand))
					{
						//移動モーション
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//走るモーション
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//しゃがむモーション
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{//矢印の左							 ↓ 左移動
					m_move.x += sinf(-D3DX_PI * 0.5f) * m_fSpeedMove;
					m_move.z += cosf(-D3DX_PI * 0.5f) * m_fSpeedMove;
					m_rotDest.y = ((D3DX_PI * 0.5f));

					if ((m_bJump || m_bLand))
					{
						//移動モーション
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//走るモーション
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//しゃがむモーション
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
				}
				else if (pCInputJoyPad->GetPress(CInputJoypad::STICK_L_UP) == true || pCInputJoyPad->GetPress(CInputJoypad::STICK_L_DOWN) == true
					|| pCInputJoyPad->GetPress(CInputJoypad::STICK_L_RIGHT) == true || pCInputJoyPad->GetPress(CInputJoypad::STICK_L_LEFT) == true)
				{//ジョイコン
					CDebugProc::Print("反応している\n");

					m_move.x -= sinf(pCamera->GetRot() - pCInputJoyPad->GetLeftAxiz()) * m_fSpeedMove;
					m_move.z -= cosf(pCamera->GetRot() - pCInputJoyPad->GetLeftAxiz()) * m_fSpeedMove;

					//向き
					m_rotDest.y = (pCamera->GetRot() - pCInputJoyPad->GetLeftAxiz());

					if ((m_bJump || m_bLand))
					{
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_RB) == true)
						{
							//走るモーション
							m_nAnimnow = PLAYERANIM_RUN;
						}

						if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_A) == true)
						{
							//しゃがむモーション
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
						else if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_LB) == true)
						{
							//しゃがむモーション
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
				}
				else if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_LB) == true)
				{
					//走るモーション
					m_nAnimnow = PLAYERANIM_SQUAT;
				}
				else if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_A) == true)
				{
					//しゃがむモーション
					m_nAnimnow = PLAYERANIM_SQUAT;
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
				{
					//しゃがむモーション
					m_nAnimnow = PLAYERANIM_SQUAT;
				}
				else
				{
					if ((m_bJump || m_bLand) && m_bAttack == false && m_bResult == false)
					{
						//待機モーション
						m_nAnimnow = PLAYERANIM_NEUTRAL;
					}
				}
			}
			else if(m_bDie == true)
			{
				m_nAnimnow = PLAYERANIM_DIE;
			}
			//============================
			//     ステージの遷移
			//============================
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(59.0f, 146.0f, 568.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * -1.0f));
			}
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(905.0f, 190.0f, 540.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * 0.5f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * 0.5f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * -0.5f));
			}
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(470.0f, 240.0f, 660.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * -1.0f));
			}
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(-1040.0f, 170.0f, 400.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//移動モーション
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * -0.5f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * -0.5f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * 0.5f));
			}
		}

		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_V) == true && (m_bJump || m_bLand) && m_bAttack == false
			|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_B) == true && (m_bJump || m_bLand) && m_bAttack == false)
		{
			//攻撃モーション
			//m_nKey = 0;
			//m_nAnimnow = PLAYERANIM_ATTACK;
			//m_bAttack = true;

			//軌跡の描画を開始する
			//m_MeshOrbit->SetOrbitOn(true);
		}

		if (m_bDie == true && m_bSukillActivate == false)
		{
			if (m_nDieTimer >= 22 && m_nDieTimer <= 22)
			{
				//NULLチェック
				if (m_pBlood == NULL)
				{
					//ダメージ時の声
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

					//血の生成
					m_pBlood = CBlood::Create(m_pos, 30.0f, 30.0f, 0);
				}
			}
			if (m_nDieTimer == 180)
			{
				//ゲームオーバー
				//CGame::SetGameState(CGame::GAMESTATE_OVER);

				//死んだ時のリザルト
				m_bOverResult = true;

				//Rewind time を出す
				CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 110.0f, 0.0f), D3DXVECTOR2(250.0f, 50.0f), 11);

				//セレクトを出す
				m_pSerect = CSerect::Create(1);


				//m_nDieTimer = 0;
			}
			
			m_nDieTimer++;
		}
		else if (m_bDie == true && m_bSukillActivate == true)
		{
			if (m_nDieSukillTimer == 22)
			{
				//NULLチェック
				if (m_pBlood == NULL)
				{
					//ダメージ時の声
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

					//血の生成
					m_pBlood = CBlood::Create(m_pos, 30.0f, 30.0f, 0);
				}
			}
			else if (m_nDieSukillTimer >= 60)
			{
				m_bSukillDie = true;
			}

			m_nDieSukillTimer++;
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

		if (m_bInvincible == true)
		{
			if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
			{//矢印の上							↓上移動
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.25f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.25f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * -0.75f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 0.25f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * 0.75f));
				}
				else
				{
					m_move.x += sinf(D3DX_PI * 0.0f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.0f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * -1.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
			{//矢印の下							 ↓上移動
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.75f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.75f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * -0.25f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 0.75f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * 0.25f));
				}
				else
				{
					m_move.x += sinf(-D3DX_PI * 1.0f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 1.0f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * 0.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
			{//矢印の右							↓ 右移動
				m_move.x += sinf(D3DX_PI * 0.5f) * 3.0f;
				m_move.z += cosf(D3DX_PI * 0.5f) * 3.0f;
				m_rotDest.y = ((D3DX_PI * -0.5f));
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
			{//矢印の左							 ↓ 左移動
				m_move.x += sinf(-D3DX_PI * 0.5f) * 3.0f;
				m_move.z += cosf(-D3DX_PI * 0.5f) * 3.0f;
				m_rotDest.y = ((D3DX_PI * 0.5f));
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
		//チートのオンオフ
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

		//チートがOFFの状態　かつ　未来から帰る際当たり判定に当たってしまうため、Fururesukillをfalseにする必要がある
		if (m_bInvincible == false && m_bEnemyFutureSukill == false)
		{
			// 地面の高さを取得
			CollisitionMesh();
			//床の当たり判定
			CollisitionGround();
			//ライトの当たり判定
			CollisitionSpotLight();
			// 壁の当たり判定
			CollisitionWall();
			// オブジェクトの当たり判定
			CollisitionObject3D(&m_pos, &m_posOld, &m_move);
			//弾の当たり判定
			CollisitionBullet();
			// アイテムの当たり判定
			CollisitionItem();
		}

		//モデルのデバック位置
		CDebugProc::Print("プレイヤーposの位置 :【%.1f】【%.1f】【%.1f】\n", m_pos.x, m_pos.y, m_pos.z);
		CDebugProc::Print("%s\n", m_bInvincible ? "true" : "false");
	}
	else if (pMode == CManager::MODE_RESULT)
	{//リザルトだったら
		//選択している番号を取得
		int SelectNum = CSerect::Get();
		
		m_nAnimnow = PLAYERANIM_RUN;

		m_pos.z -= 4.0f;
	}
	else if (pMode == CManager::MODE_RANKING)
	{//ランキングだったら
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_SPACE) == true
			|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_A) == true)
		{// ジャンプ
			//if (m_nAnimnow != PLAYERANIM_BAKUTEN)
			{	//バンザイ

				//m_nAnimnow = PLAYERANIM_BAKUTEN;
				//m_bMotionEnd = false;
			}
		}
		//else if (m_nAnimnow != PLAYERANIM_BANZAI && m_bMotionEnd == true)
		{	//バンザイ
			//m_nAnimnow = PLAYERANIM_BANZAI;
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

	//// ライトを無効にする
	//pDevice->LightEnable(0, FALSE);
	//pDevice->LightEnable(1, FALSE);
	//pDevice->LightEnable(2, FALSE);

	////影
	//D3DXMATRIX	mtxShadow;		//シャドウマトリックス
	//D3DXPLANE	planeFielld;
	//D3DXVECTOR4 vecLight;
	//D3DXVECTOR3 pos, normal;

	//// シャドウマトリックスの初期化
	//D3DXMatrixIdentity(&mtxShadow);

	//// 一番強いライトの位置
	//vecLight = D3DXVECTOR4(-0.22f, 0.87f, -0.44f, 0.0f);

	//// 影の位置
	//pos = D3DXVECTOR3(0.0f, m_pos.y + 1.0f, 0.0f);

	//// 法線の向き
	//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//// 平面を作る
	//D3DXPlaneFromPointNormal(&planeFielld, &pos, &normal);

	//D3DXMatrixShadow(&mtxShadow, &vecLight, &planeFielld);

	////マトリックスを掛け合わせる       ↓反対にすると影が方向までついてくる
	//D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//モデルの描画
	//		m_apModel[nCount]->Draw(1.0f);
	//	}
	//}

	//// ライトを有効にする
	//pDevice->LightEnable(0, TRUE);
	//pDevice->LightEnable(1, TRUE);
	//pDevice->LightEnable(2, TRUE);

	//// ワールドマトリックスの設定
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
//	弾の当たり判定
//=============================================================================
void CPlayer::CollisitionBullet(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(BULLET_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプが銃弾だったら
			if (pScene->GetObjType() == OBJTYPE_BULLET)
			{
				//当たり判定
				if (((CBullet*)pScene)->CollisitionBullet(&m_pos,20.0f))
				{
					if (m_bStageNext == false)
					{
						//ライフゲージから減らす
						CLife::AddLife(-200);
					}
					pScene->Uninit();
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
//	ライトの当たり判定
//=============================================================================
void CPlayer::CollisitionSpotLight(void)
{
	CScene *pScene;
	bool bWater = false;

	//プライオリティーチェック
	pScene = CScene::GetTop(SPOTLIGHT_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプが床だったら
			if (pScene->GetObjType() == OBJTYPE_SPOTLIGHT)
			{
				((CSpotLight*)pScene)->CollisionSpotLight(&m_pos, &m_posOld, &m_move);
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
//=========================================================================================================================
// マップ移動の際のプレイヤーの初期化
//=========================================================================================================================
void CPlayer::ResetPlayer(void)
{
	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2 || pStageNum == CGame::STAGENUM_3 || pStageNum == CGame::STAGENUM_5)
	{
		m_pos = D3DXVECTOR3(0.0f, 0.0f, -350.0f);		//位置
		m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);			//向き

		m_bStageReset = true;							//ステージが変わった際
	}
	if (pStageNum == CGame::STAGENUM_4)
	{
		m_pos = D3DXVECTOR3(-60.0f, 0.0f, -200.0f);		//位置
		m_rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);		//向き

		m_bStageReset = true;							//ステージが変わった際
	}
	if (pStageNum == CGame::STAGENUM_6)
	{
		m_pos = D3DXVECTOR3(-40.0f, 0.0f, 1280.0f);		//位置
		m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);			//向き

		m_bStageReset = true;							//ステージが変わった際
	}

	if (m_bStageReset == true)
	{
		m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//過去の位置
		m_bJump = true;									//ジャンプの状態
		m_bLand = true;									//着地の状態
		m_bInvincible = false;							//チートモード
		m_fStageNext = false;							//ステージ切り替え
		m_bMotionEnd = true;							//モーション終了
		m_nAnimnow = PLAYERANIM_NEUTRAL;				//モーション初期化
		m_nAttackDelay = 0;								//攻撃

		m_bStageReset = false;							//ステージが変わった際
	}
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
			//if (m_nAnimnow == PLAYERANIM_ATTACK)
			//{//攻撃モーション
			//	m_nAttackDelay++;
			//	if (m_nAttackDelay > 20)
			//	{
			//		m_bAttack = false;
			//		m_nAttackDelay = 0;
			//	}
			//}
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

	D3DXVECTOR3 ParentPos;	//親の位置情報を取得
#if 1
							//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME_PRISONER, "r");
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
