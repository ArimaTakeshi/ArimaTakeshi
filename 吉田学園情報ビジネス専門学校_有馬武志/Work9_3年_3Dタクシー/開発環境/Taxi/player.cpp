//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 佐藤安純 Sato_Asumi
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "camerabace.h"
#include "scene.h"
#include "model.h"
#include "motion.h"
#include "loadText.h"
#include "tire.h"
#include "wall.h"
#include "incline.h"
#include "taillamp.h"
#include "sound.h"
#include "car.h"
#include "smokeeffect.h"
#include "sparkeffect .h"
#include "tutorial.h"
#include "ground.h"
#include "loadEffect.h"
#include "gamecamera.h"
#include "object.h"
#include "combo.h"
#include "score.h"
#include "time.h"
#include "customer.h"
#include "grasseffect.h"
#include "addcoin.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define VECTOR_ZERO		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				//ベクトルの初期化
#define FAILE_NAME		("data\\TEXT\\Player\\PlayerState.txt")		//読み込むファイル名
#define FILE_TEXTURE	("data\\TEXTURE\\modeltex\\carup.jpg")		//テクスチャの読み込み
#define LEFT_FRONT_POS	(D3DXVECTOR3(-26.0f, 3.0f, 45.0f))			//左前タイヤ位置
#define LEFT_BACK_POS	(D3DXVECTOR3(-26.0f, 3.0f, -40.0f))			//左後ろタイヤ位置
#define RIGHT_FRONT_POS	(D3DXVECTOR3(26.0f, 3.0f, 45.0f))			//右前タイヤ位置
#define RIGHT_BACK_POS	(D3DXVECTOR3(26.0f, 3.0f, -40.0f))			//右後ろタイヤ位置
#define ACCLE_TIME		(60.0f * 4)									//加速させる時間
#define AVERAGE			(2.0f)										//平均する値
#define ROLLOVER_STOP	(0.6f)										//横転防止角度
#define GRAVITY_FRONT	(0.5f)										//前方の重力
#define GRAVITY_BACK	(0.2f)										//後方の重力
#define DECELERATION	(0.5f)										//減速の割合
#define START_ENGINE	(200)										//エンジン音の再生時間
#define START_GEARCHANGE (300)										//スタート時のギア切替時間

//車体の角度
#define SHAKE_X			(0.007f)									//X軸の揺れ
#define INPULS_X		(0.01f)										//X軸に加える角度
#define SHAKE_Z			(0.02f)										//Z軸の揺れ
#define SHAKE_DRIFT		(0.005f)										//ドリフト時の角度加算
#define SHAKE_BRAK		(0.01f)										//ブレーキ時の角度

//タイヤの番号
#define LEFT_FRONT		(0)											//左前タイヤ
#define LEFT_BACK		(1)											//左後ろタイヤ
#define RIGHT_FRONT		(2)											//右前タイヤ
#define RIGHT_BACK		(3)											//右後ろタイヤ

#define RIVER_SOUND_RANGE		(1000.0f)							// 川の音が聞こえる範囲
#define FOUNTAIN_SOUND_RANGE	(1000.0f)							// 噴水の音が聞こえる範囲

// コンボ時のスコア加算
#define JUMP_ADD_SCORE	(100)										// ジャンプ時のスコア加算量
#define JUMP_FREAM_TIME	(25)										// ジャンプ時のスコア加算時間
#define DRIFT_COMBO_TIME (25)										// ドリフト時のスコア加算時間
#define THROUGH_COMBO_TIME	(1)									// すれすれ時のスコア加算時間
#define DRIFT_SPACE_SMALL	(10)
#define DRIFT_SPACE_BIG		(250)
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CModel * CPlayer::m_pModel = NULL;	//モデルのパーツポインタ
int	CPlayer::m_nMaxModel = 0;
int CPlayer::m_nMaxParts = 0;
int CPlayer::m_nMaxMotion = 0;
D3DXVECTOR3 CPlayer::m_pos = VECTOR_ZERO;
CMotion::MOTION_INFO * CPlayer::m_pMotionInfo = NULL;
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
bool CPlayer::m_bCustomrStop = false;

//=============================================================================
// 生成処理
//=============================================================================
CPlayer * CPlayer::Create(const D3DXVECTOR3 pos)
{
	//インスタンスの生成
	CPlayer * pPlayer;
	pPlayer = new CPlayer;

	//初期化処理
	pPlayer->Init();

	//設定処理
	pPlayer->Set(pos, VECTOR_ZERO);
	return pPlayer;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer() : CScene(3, OBJTYPE_PLAYER) {}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer() {}

//=============================================================================
// Xファイルの読み込み
//=============================================================================
void CPlayer::LoadModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		FILE_TEXTURE,
		&m_pTexture);

	//モーション情報の取得
	CLoadTextMotion * pLoadTextMotion = NULL;
	CManager::MODE mode = CManager::GetMode();

	if (mode == CManager::MODE_GAME)
	{//ゲーム
		pLoadTextMotion = CGame::GetPlayerMotion();
	}
	else if (mode == CManager::MODE_TUTORIAL)
	{//チュートリアル
		pLoadTextMotion = CTutorial::GetPlayerMotion();
	}

	m_pMotionInfo = pLoadTextMotion->GetMotionInfo();					//モーション情報の取得
	m_nMaxMotion = pLoadTextMotion->GetMaxMotion();						//モーションの最大数の取得

	//モデル情報を取得
	CLoadTextMotion::MODEL_INFO ModelInfo = pLoadTextMotion->GetModelInfo();
	m_nMaxModel = ModelInfo.nMaxModel;	//モデルの最大数の取得
	m_nMaxParts = ModelInfo.nMaxParts;	//モデルのパーツ最大数の取得

	//モデルの生成
	for (int nCntParts = 0; nCntParts < ModelInfo.nMaxParts; nCntParts++)
	{
		m_pModel = CModel::Create(ModelInfo.pOfSetPos[nCntParts], &ModelInfo.paFileName[nCntParts][0]);

		//テクスチャの割当て
		if (m_pModel != NULL) { m_pModel->BindTexture(m_pTexture); }
	}

	//モデルの親設定
	for (int nCntParts = 0; nCntParts < ModelInfo.nMaxParts; nCntParts++)
	{
		if (nCntParts == 0)
		{
			m_pModel->SetParent(NULL);
			break;
		}
	}
}

//=============================================================================
// Xファイルの破棄
//=============================================================================
void CPlayer::UnloadModel(void)
{
	if (m_pModel != NULL)
	{
		delete m_pModel;
		m_pModel = NULL;
	}

	//モーションデータの破棄
	if (m_pMotionInfo != NULL)
	{
		m_pMotionInfo = NULL;
	}

	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//変数の初期化
	m_pos = VECTOR_ZERO;					//中心座標
	m_OldPos = VECTOR_ZERO;					//前回の座標
	m_move = VECTOR_ZERO;					//移動
	m_rot = VECTOR_ZERO;					//向き
	m_OldDiffuse = VECTOR_ZERO;				//前回の差分
	m_MoveMotion = VECTOR_ZERO;				//モーションの移動
	m_vtxMaxModel = VECTOR_ZERO;			//モデルの頂点最大値
	m_vtxMinModel = VECTOR_ZERO;			//モデルの頂点最小値
	m_pMotion = NULL;						//モーションポインタ
	m_pText = NULL;							//プレイヤーのテキストポインタ
	m_state = STATE_DRIVE;					//状態設定
	m_StateSpeed = STATE_SPEED_STOP;		//スピードの状態設定
	m_StateHandle = HANDLE_MAX;				//ハンドルの状態
	m_PlayerInfo.nCountTime = 0;			//カウンター
	m_PlayerInfo.fAccel = 1.0f;				//加速値
	m_PlayerInfo.fBraks = 0.00f;			//減速値
	m_PlayerInfo.fAddRot = 0.00f;			//加える回転値
	m_PlayerInfo.fDistance = 0.0f;			//距離
	m_PlayerInfo.fWindy = 0.0f;				//風圧
	m_PlayerInfo.FirstPos = VECTOR_ZERO;	//初期位置
	m_bJump = false;						//ジャンプ状態
	m_bControl = true;						//コントローラーフラグ
	m_bPutin = false;						//乗車状態フラグ
	m_nCountJumpTime = 0;					//ジャンプ状態の時間を加算
	m_fvtxMaxY = 0.0f;						//モデル頂点の最大値（Y）
	m_fMass = 200.0f;						// 質量
	m_nCountTime = 0;						// 時間カウンター
	m_bSmoke = true;						// 煙のエフェクトオンオフ
	m_bCrcleCarIn = false;
	m_bHazardlamp = false;
	m_pLoadEffect = NULL;					// エフェクトツールポインタ
	m_pCombo = NULL;
	m_nCntCombo = 0;
	m_nCntShake = 0;
	m_bShake = true;
	m_posFountain = VECTOR_ZERO;
	m_bFountainSound = false;
	m_bComboFlag = false;
	m_bFlagIn = false;
	m_nCntFlag = 0;
	m_bDirive = true;
	m_bCustomerMove = false;
	m_nCountSound = 0;			//フェンスの音カウンター
	m_nCountLeaf = 0;			//葉の音のカウンター
	m_nCountWood = 0;			//木の音のカウンター
	m_bGrassEffect = false;		//草エフェクトの生成フラグ

	//タイヤのポインタを初期化
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		m_pTire[nCntTire] = NULL;
	}

	CreateTire();			//タイヤの生成

	if (m_pMotion == NULL)	//モーションの生成
	{
		m_pMotion = CMotion::Create();

		if (m_pMotion != NULL)
		{
			//モデルデータの設定
			m_pMotion->SetModel(&m_pModel);			//モーションデータにモデル情報を渡す
			m_pMotion->SetMaxModel(m_nMaxParts);	//モデルパーツの最大数を渡す

			//モーションデータの設定
			m_pMotion->SetMotion(m_pMotionInfo);	//モーション情報の取得
			m_pMotion->SetMaxMotion(m_nMaxMotion);	//モーションの最大数の取得

			//初期化処理
			m_pMotion->Init();
		}
	}

	for (int nCntTailLamp = 0; nCntTailLamp < 2; nCntTailLamp++)
	{// テールランプの生成
		m_apTailLamp[nCntTailLamp] = CTailLamp::Create(D3DXVECTOR3(22.0f - (nCntTailLamp * 44.0f), 35.0f, -85.0f), D3DXVECTOR2(10.0f, 10.0f), &m_mtxWorld);
	}

	// エフェクトツールを生成
	if (m_pLoadEffect == NULL){ m_pLoadEffect = CLoadEffect::Create(7, m_pos, 6); }

	//モデルの最小値・最大値の取得
	m_vtxMaxModel = m_pModel->GetVtxMax();
	m_vtxMinModel = m_pModel->GetVtxMin();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//モーションの破棄
	if (m_pMotion != NULL)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//タイヤモデルの破棄
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		if (m_pTire[nCntTire] != NULL)
		{
			m_pTire[nCntTire]->Uninit();
			delete m_pTire[nCntTire];
			m_pTire[nCntTire] = NULL;
		}
	}

	//テキストの破棄
	if (m_pText != NULL)
	{
		m_pText->Uninit();
		delete m_pText;
		m_pText = NULL;
	}

	if (m_pLoadEffect != NULL)
	{// エフェクトツールの破棄
		m_pLoadEffect->Uninit();
		delete m_pLoadEffect;
		m_pLoadEffect = NULL;
	}

	if (m_pCombo != NULL)
	{	// コンボの破棄
		m_pCombo->Uninit();
		m_pCombo = NULL;
	}

	//死亡フラグを立てる
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	//変数宣言
	D3DXVECTOR3 TirePos[MAX_TIRE];
	CManager::MODE mode = CManager::GetMode();
	CGameCamera * pGameCamera = NULL;
	CGameCamera::MODECAMERA pCameraMode = {};
	m_bShake = true;

	if (mode == CManager::MODE_GAME)
	{
		pGameCamera = CGame::GetGameCamera();
		pCameraMode = pGameCamera->GetModeCamera();
		CGameCamera::DIRECTING pCameraDirecting = pGameCamera->GetDirecting();
		if (pCameraMode == CGameCamera::MODE_START)
		{
			//タイヤの更新処理
			for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
			{
				if (m_pTire[nCntTire] == NULL) { continue; }

				if ((nCntTire % 2) == 0)
				{
					m_pTire[nCntTire]->Update(nCntTire, GRAVITY_FRONT);
				}
				else
				{
					m_pTire[nCntTire]->Update(nCntTire, GRAVITY_BACK);
				}

				TirePos[nCntTire] = m_pTire[nCntTire]->GetWorldPos();
			}

			CarCalculate(TirePos);	// 車体の高さ・角度設定
			UpdateMove();			// 移動処理

			m_nCountTime++;			//時間の可算

			if (pCameraDirecting == CGameCamera::DIRECTING_END)
			{
				m_nCountTime = START_GEARCHANGE;
			}

			if (m_nCountTime == START_ENGINE)
			{
				CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENGINESTART); //エンジンのスタート音再生
				m_state = STATE_REVERSE;			// ギアの切替
				CScore::SetType(CScore::TYPE_USE);	// スコアの色切替
			}
			if (m_nCountTime > START_ENGINE) { UpdateShake(); }	//車の揺れの処理
			if (m_nCountTime == START_GEARCHANGE)
			{
				m_state = STATE_DRIVE;						// ギア切替
				CScore::SetType(CScore::TYPE_NOT_USE);		// スコアの色切替
			}
			return;
		}
	}


	if (m_bControl)
	{//コントロールキー
		ControlKey();
	}
	else
	{//ハンドルを握っていない状態にする
		SetStateHandle(HANDLE_MAX);
	}

	//タイヤの更新処理
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		if (m_pTire[nCntTire] == NULL) { continue; }

		if ((nCntTire % 2) == 0)
		{
			m_pTire[nCntTire]->Update(nCntTire, GRAVITY_FRONT);
		}
		else
		{
			m_pTire[nCntTire]->Update(nCntTire, GRAVITY_BACK);
		}

		TirePos[nCntTire] = m_pTire[nCntTire]->GetWorldPos();
	}

	CarCalculate(TirePos);	// 車体の高さ・角度設定

	//タイムアップ状態なら以降は更新しない
	if (CTime::GetTime() == 0 && CManager::MODE_GAME == CManager::GetMode()) { return; }

	UpdateMove();			// 移動処理
	UpdateStateJump();		// ジャンプ状態の更新処理
	RiverInfluence();		// 川による影響

	CollisionObject();		// オブジェクトとの当たり判定
	UpdateShake();			//車の揺れの処理
	//CollisitionWall();	// 壁との当たり判定
	UpdateSmoke(TirePos);	//煙の更新処理
	UpdateGrass(TirePos);	//草エフェクトの更新処理

	m_nCntCombo++;

	// コンボ数
	if (m_pCombo != NULL && m_pCombo->GetFream() == 0)
	{	// NULLチェック & フレームが0の場合
		m_nCntCombo = 0;
		m_pCombo->Uninit();
		m_pCombo = NULL;
	}

	DebugProc();		// デバック表示
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	//レンダリングクラスを取得
	CRenderer * pRenderer = NULL;
	pRenderer = CManager::GetRenderer();

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX		  mtxRot, mtxTrans;			// 計算用マトリックス

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

	//モデルの描画
	if (m_pModel != NULL)
	{
		//描画する
		m_pModel->Draw(1.0f);
	}

	//タイヤの描画
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		if (m_pTire[nCntTire] != NULL) { m_pTire[nCntTire]->Draw(1.0); }
	}
}

//=============================================================================
// コントロールキー
//=============================================================================
void CPlayer::ControlKey(void)
{
	CInputKeyBoard * pInputKeyboard = CManager::GetInput();		//キーボードの取得
	CXInput * pInputJoypad = CManager::GetXInput();				//ジョイパットの取得

	if (!CCustomer::GetPutIn())
	{
		if (pInputKeyboard->GetKeyboardTrigger(DIK_Q) == true || pInputJoypad->GetTrigger(CXInput::XIJS_BUTTON_1))
		{// ハザードランプ点灯or消灯
			m_bHazardlamp = m_bHazardlamp ? false : true;

			// ハザードランプ点灯フラグによって変える
			if (m_bHazardlamp) { SetTailLampType(CTailLamp::TYPE_HAZARD_LAMP); }
			else { SetTailLampType(CTailLamp::TYPE_NONE); }
		}

		//前進後退の設定
		if (m_bDirive)
		{
			if ((pInputKeyboard->GetKeyboardTrigger(DIK_W) == true) || (pInputJoypad->GetTrigger(CXInput::XIJS_BUTTON_11) == true))
			{
				SetState(STATE_DRIVE);		//前進状態に設定
			}
			if ((pInputKeyboard->GetKeyboardTrigger(DIK_S) == true) || (pInputJoypad->GetTrigger(CXInput::XIJS_BUTTON_10) == true))
			{
				SetState(STATE_REVERSE);	//後退状態に設定
			}
		}

		//向きの設定
		if (m_StateSpeed != STATE_SPEED_STOP)
		{
			if ((pInputKeyboard->GetKeyboardPress(DIK_A) == true) || pInputJoypad->GetPress(CXInput::XIJS_BUTTON_18))
			{ //左ハンドル状態
				SetStateHandle(HANDLE_LEFT);
			}
			else if ((pInputKeyboard->GetKeyboardPress(DIK_D) == true) || pInputJoypad->GetPress(CXInput::XIJS_BUTTON_19))
			{//右ハンドル状態
				SetStateHandle(HANDLE_RIGHT);
			}
			else
			{//ハンドルを触っていない状態
				SetStateHandle(HANDLE_MAX);
			}
		}
		else
		{
			SetStateHandle(HANDLE_MAX);
		}

		//ブレーキ
		if ((pInputKeyboard->GetKeyboardPress(DIK_K) == true) ||
			(pInputJoypad->GetPress(CXInput::XIJS_BUTTON_14) == true) ||
			(pInputJoypad->GetPress(CXInput::XIJS_BUTTON_8) == true))
		{//ブレーキ状態
			if (m_bJump == false) { SetStateSpeed(STATE_SPEED_BRAKS); }
		}
		else if ((pInputKeyboard->GetKeyboardPress(DIK_L) != true) &&
			(pInputJoypad->GetPress(CXInput::XIJS_BUTTON_15) != true) &&
			(pInputJoypad->GetPress(CXInput::XIJS_BUTTON_9) != true))
		{//減速状態
			SetStateSpeed(STATE_SPEED_DOWN);
		}
		else
		{
			//アクセル
			if ((pInputKeyboard->GetKeyboardPress(DIK_L) == true) ||
				(pInputJoypad->GetPress(CXInput::XIJS_BUTTON_15) == true) ||
				(pInputJoypad->GetPress(CXInput::XIJS_BUTTON_9) == true))
			{ //アクセルを状態
				SetStateSpeed(STATE_SPEED_ACCEL);
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_K) != true || pInputKeyboard->GetKeyboardPress(DIK_L) != true)
			{//減速状態
				SetStateSpeed(STATE_SPEED_DOWN);
			}
		}
	}

	CSound *pSound = CManager::GetSound();

	if ((pInputKeyboard->GetKeyboardPress(DIK_N) == true) || (pInputJoypad->GetPress(CXInput::XIJS_BUTTON_0) == true))
	{
		pSound->SetVolume(CSound::SOUND_LABEL_SE_KLAXON, 1.5f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_KLAXON);
	}
}

//=============================================================================
// 移動処理
//=============================================================================
void CPlayer::UpdateMove(void)
{
	m_OldPos = m_pos;	//前回の位置を保存する

	RemakeAngle(&m_rot.y);

	if (m_bCustomerMove)
	{// 客が迫っているとき
		return;
	}


	//状態ごとの更新処理
	switch (m_StateSpeed)
	{
	case STATE_SPEED_ACCEL:	//アクセル状態

		//ジャンプ状態なら
		if (m_bJump == true) { break; }

			CDebugProc::Print("初速加速あり\n");
			//速度を上げる
			m_PlayerInfo.nCountTime++;
			if (m_move.x < 3.0f && m_move.z < 3.0f &&m_move.x > -3.0f && m_move.z > -3.0f)
			{
				m_PlayerInfo.nCountTime = m_PlayerInfo.nCountTime*1.03f;
				CDebugProc::Print("初速UP状態 [1段階]\n");
			}
			else if (m_move.x < 6.0f && m_move.z < 6.0f &&m_move.x > -6.0f && m_move.z > -6.0f)
			{
				m_PlayerInfo.nCountTime = m_PlayerInfo.nCountTime*1.04f;
				CDebugProc::Print("初速UP状態 [2段階]\n");
			}
			else if (m_move.x < 9.0f && m_move.z < 9.0f &&m_move.x > -9.0f && m_move.z > -9.0f)
			{
				m_PlayerInfo.nCountTime = m_PlayerInfo.nCountTime*1.065f;
				CDebugProc::Print("初速UP状態 [3段階]\n");
			}

			//加速値を求める
			m_PlayerInfo.fAccel = (m_fMaxSpeed / ACCLE_TIME) * m_PlayerInfo.nCountTime;

			//減速させる
			if (m_state == STATE_DRIVE)
			{
				if (m_PlayerInfo.fAccel > m_fMaxSpeed) { m_PlayerInfo.fAccel = m_fMaxSpeed; }
			}
			else if (m_state == STATE_REVERSE)
			{
				if (m_PlayerInfo.fAccel < m_fMaxSpeed) { m_PlayerInfo.fAccel = m_fMaxSpeed; }
			}


		//進行方向の設定
		m_move.x += sinf(m_rot.y) * (m_PlayerInfo.fAccel);
		m_move.z += cosf(m_rot.y) * (m_PlayerInfo.fAccel);
		break;

	case STATE_SPEED_BRAKS: //ブレーキ状態

		//ジャンプ状態なら
		if (m_bJump == true) { break; }

		//速度を下げる
		m_PlayerInfo.fAccel -= m_PlayerInfo.fBraks;

		if (m_state == STATE_DRIVE)
		{
			if (m_PlayerInfo.fAccel < 0.0f) { m_PlayerInfo.fAccel = 0.0f; }
		}
		else
		{
			if (m_PlayerInfo.fAccel > 0.0f) { m_PlayerInfo.fAccel = 0.0f; }
		}

		//進行方向の設定
		m_move.x += sinf(m_rot.y) * m_PlayerInfo.fAccel;
		m_move.z += cosf(m_rot.y) * m_PlayerInfo.fAccel;

		//テールランプの表示
		SetTailLampType(CTailLamp::TYPE_BREAKING);

		//揺れを無効にする
		m_bShake = false;
		break;

	case STATE_SPEED_DOWN:  //減速状態
		m_PlayerInfo.nCountTime = 0;
		if (m_apTailLamp[0]->GetType() != CTailLamp::TYPE_HAZARD_LAMP) { SetTailLampType(CTailLamp::TYPE_NONE); }
		break;
	}

	CDebugProc::Print("アクセル : %1f\n", m_PlayerInfo.fAccel);
	CDebugProc::Print("スピード : %1f  %1f  %1f\n", m_move.x , m_move.y , m_move.z);

	//ハンドルの状態更新
	if (m_StateHandle == HANDLE_LEFT)
	{
		m_rot.y -= m_PlayerInfo.fAddRot;
		m_rot.z -= SHAKE_Z;
	}
	else if (m_StateHandle == HANDLE_RIGHT)
	{
		m_rot.y += m_PlayerInfo.fAddRot;
		m_rot.z += SHAKE_Z;
	}

	// 重力
	if (m_bShake == true)
	{
		m_move.y -= cosf(0) * 0.4f;
	}

	//中心座標更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	//減速
	m_PlayerInfo.fAccel += (0.0f - m_PlayerInfo.fAccel) * m_PlayerInfo.fWindy;
	if (!m_bJump)
	{
		m_move.x += (0.0f - m_move.x) * m_PlayerInfo.fWindy;
		m_move.z += (0.0f - m_move.z) * m_PlayerInfo.fWindy;
	}

	//停止判定
	D3DXVECTOR3 fDiffuse = m_pos - m_OldPos;

	if (fDiffuse.x < 0.10f && fDiffuse.x > -0.10f)
	{
		if (fDiffuse.z < 0.10f && fDiffuse.z > -0.10f)
		{
			SetStateSpeed(STATE_SPEED_STOP);
		}
	}

	//煙の表示
	if ((fDiffuse.x < 1.5f) && (fDiffuse.x > -1.5f))
	{
		if ((fDiffuse.z < 1.5f) && (fDiffuse.z > -1.5f))
		{
			m_bSmoke = false;
			m_bGrassEffect = false;		//草エフェクト非表示
		}
		else
		{
			m_bSmoke = true;
		}
	}
	else
	{
		m_bSmoke = true;
	}

	//お客さんを乗せるための停止判定
	if ((fDiffuse.x < 1.0f) && (fDiffuse.x > -1.0f))
	{
		if ((fDiffuse.z < 1.0f) && (fDiffuse.z > -1.0f))
		{
			m_bCustomrStop = true;
		}
		else
		{
			m_bCustomrStop = false;
		}
	}
	else
	{
		m_bCustomrStop = false;
	}

	if ((m_StateSpeed == STATE_SPEED_BRAKS) && (m_bSmoke == true))
	{
		//角度を変える
		m_rot.x += SHAKE_BRAK;
	}
}

//=============================================================================
// 揺れの更新処理
//=============================================================================
void CPlayer::UpdateShake(void)
{
	if (!m_bShake) { return; }

	m_nCntShake++;	//カウンターの加算

	if ((m_nCntShake % 8) == 0)
	{//車体を揺らす
		m_rot.x += SHAKE_X;

		if (((m_nCntShake % 24) == 0) && (m_state != STATE_SPEED_STOP))
		{
			int nRand = rand() % 5;

			if (nRand == 0)
			{
				m_rot.x += INPULS_X;
			}
		}
	}
}

//=============================================================================
// 状態の設定
//=============================================================================
void CPlayer::SetState(CPlayer::STATE state)
{
	//値の反転
	if (m_state != state)
	{
		m_PlayerInfo.fAccel *= -0.5f;
		m_PlayerInfo.fBraks *= -1;
		m_fMaxSpeed *= -1;

		CSound *pSound = CManager::GetSound();

		if (STATE_REVERSE == state)
		{// バック音
			pSound->StopSound(CSound::SOUND_LABEL_SE_ACCEL);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_BACK);

			if (STATE_SPEED_STOP != m_StateSpeed)
			{// テールランプをバック用に点灯
				SetTailLampType(CTailLamp::TYPE_BACK);
			}
		}
		else if (STATE_DRIVE == state)
		{
			pSound->StopSound(CSound::SOUND_LABEL_SE_BACK);
			pSound->SetVolume(CSound::SOUND_LABEL_SE_ACCEL, 0.7f);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ACCEL);

			//テールランプを消す
			if (m_apTailLamp[0]->GetType() != CTailLamp::TYPE_HAZARD_LAMP) { SetTailLampType(CTailLamp::TYPE_NONE); }
		}
	}

	//状態の設定
	m_state = state;
}

//=============================================================================
// スピードの状態設定
//=============================================================================
void CPlayer::SetStateSpeed(CPlayer::STATE_SPEED state)
{
	//数値の設定
	if (m_StateSpeed != state)
	{
		m_PlayerInfo.nCountTime = 0;

		CSound *pSound = CManager::GetSound();

		if (STATE_SPEED_ACCEL == state && STATE_DRIVE == m_state)
		{// アクセル音
			pSound->SetVolume(CSound::SOUND_LABEL_SE_ACCEL, 0.7f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ACCEL);
		}
		else if (STATE_SPEED_BRAKS == state)
		{// ブレーキ音
			if (m_move.x >= 0.1f || m_move.x <= -0.1f || m_move.z >= 0.1f || m_move.z <= -0.1f)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_BRAKING);
				pSound->StopSound(CSound::SOUND_LABEL_SE_ACCEL);
			}
		}
	}

	//状態の設定
	m_StateSpeed = state;
}

//=============================================================================
// 設定処理
//=============================================================================
void CPlayer::Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_pos = pos;
}

//=============================================================================
// タイヤの生成
//=============================================================================
void CPlayer::CreateTire(void)
{
	//タイヤの位置を設定
	D3DXVECTOR3 TirePos[MAX_TIRE];

	TirePos[LEFT_FRONT] = LEFT_FRONT_POS;
	TirePos[LEFT_BACK] = LEFT_BACK_POS;
	TirePos[RIGHT_FRONT] = RIGHT_FRONT_POS;
	TirePos[RIGHT_BACK] = RIGHT_BACK_POS;

	//タイヤの生成
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		m_pTire[nCntTire] = NULL;
		m_pTire[nCntTire] = CTire::Create(TirePos[nCntTire]);

		if (m_pTire[nCntTire] != NULL) { m_pTire[nCntTire]->SetParent(m_pModel); }	//親子関係の設定
	}
}

//=============================================================================
// テキストの読み込み
//=============================================================================
void CPlayer::LoadText(void)
{
	if (m_pText == NULL) { m_pText = CLoadTextPlayer::Create(FAILE_NAME); }	//プレイヤーの情報を読み込む
	m_PlayerInfo = m_pText->GetPlayerInfo();								//読み込んだ情報を取得する

	//プレイヤー情報を設定する
	m_pos = m_PlayerInfo.FirstPos;
	m_fMaxSpeed = m_PlayerInfo.fAccel;	//アクセル最大値の取得
	m_PlayerInfo.fAccel = 0.0f;
}

//=============================================================================
// オブジェクトとの当たり判定
//=============================================================================
void CPlayer::CollisionObject(void)
{
	CSound *pSound = CManager::GetSound();
	CScene *pScene;

	//吹っ飛ば差ないオブジェクト番号の登録
	int anUpdateType[UPDATE_TYPE_NUM + HIGHT_OBJ_NUM + 2] = { TYPE_TREE00, TYPE_TREE01, TYPE_BILL00, TYPE_BILL01,
														 TYPE_BILL02, TYPE_TVBILL, TYPE_FLOWER, TYPE_TANUKI,
														 TYPE_OCLOCK, TYPE_REDBILL, TYPE_TREE02,  TYPE_CORN2,
														 TYPE_STATION, TYPE_ESTA, TYPE_DAIMAL, TYPE_APIA,
														 TYPE_TOWER, TYPE_FOUNTAIN, TYPE_FERRISWGEEL,
														 TYPE_STREETLIGHT, TYPE_TRAFFICLIGHT00, TYPE_TRAFFICLIGHT01, TYPE_ROAD , TYPE_TAPIOCA, TYPE_HOSPITAL };
	bool bType = false;	//タイプのフラグ

	for (int nCntPriority = CAR_PRIOTITY; nCntPriority <= OBJECT_PRIOTITY; nCntPriority++)
	{
		// プライオリティーチェック
		pScene = CScene::GetTop(nCntPriority);
		while (pScene != NULL)
		{// プライオリティー内のリスト構造を最後まで見る
			CScene *pSceneNext = pScene->GetNext();		// 次のオブジェクトを保存

			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{// タイプが障害物だったら
				CObject *pObject = (CObject*)pScene;	// オブジェクトクラスのポインタ変数にする
				int nType = pObject->GetType();		// 障害物の種類を取得
				if (nType != 19)
				{// 壁以外
					if (pObject->Collision(m_pos, m_pModel[0].GetVtxMax(), m_pModel[0].GetVtxMin(), m_move))
					{// 衝突した
						for (int nCntObj = 0; nCntObj < UPDATE_TYPE_NUM + HIGHT_OBJ_NUM + 2; nCntObj++) {//タイプ判定
							if (nType == anUpdateType[nCntObj])
							{
								bType = true;
								break;
							}
						}

						if (bType == false)
						{// 指定した障害物だったら吹き飛ばす
							if (m_pCombo != NULL) { m_pCombo->ResetCombo(); }
							if (!m_bJump) { m_move = pObject->BlowOff(m_pos, m_move, m_fMass); }		// オブジェクトを吹き飛ばす

							//音の再生処理
							PlaySoundObj(nType, pSound);
						}
						if (nType == 30 || nType == 33)
						{// 噴水 || 消火栓
							m_move = pObject->Fountain(m_pos, m_move);
							m_bJump = true;
							m_pos.y += m_move.y;
						}
					}
				}
				else if (19 == nType)
				{// 壁
					if (pObject->CollisionObject(&m_pos, &m_OldPos, &m_move))
					{
						if (m_pCombo != NULL) { m_pCombo->ResetCombo(); }
					}
				}
			}
			else if (pScene->GetObjType() == OBJTYPE_CAR)
			{// タイプがNPC車だったら
				CCarBase *pCar = (CCarBase*)pScene;		// オブジェクトクラスのポインタ変数にする

				if (pCar->Collision(m_pos, m_pModel[0].GetVtxMax(), m_pModel[0].GetVtxMin(), m_move))
				{// 衝突した
					if (m_pCombo != NULL) { m_pCombo->ResetCombo(); }
					m_bComboFlag = true;		//コンボを入らない状態にする
					m_bFlagIn = false;
					if (pCar->GetType() == 9)
					{//	警察
						m_move = pCar->BlowOff(m_pos, m_move, m_fMass) * 1.55f;		// オブジェクトを吹き飛ばす
					}
					else
					{//それ以外の車
						if (D3DXVec3Length(&m_move) > 25.0f)
						{// 移動量が一定以上で転がす
							pCar->SetStateRoll(true);
						}
						m_move = pCar->BlowOff(m_pos, m_move, m_fMass);		// オブジェクトを吹き飛ばす
					}
					pSound->SetVolume(CSound::SOUND_LABEL_SE_CRASH_CAR, 1.2f);
					pSound->PlaySound(CSound::SOUND_LABEL_SE_CRASH_CAR);
				}

				//	プレイヤーとの距離
				D3DXVECTOR3 CarPos = pCar->GetPosition();
				float fLengthPlayer = sqrtf((CarPos.x - m_pos.x)* (CarPos.x - m_pos.x) + (CarPos.z - m_pos.z)*(CarPos.z - m_pos.z));

				if (fLengthPlayer < 300)
				{//	範囲内処理
					m_bCrcleCarIn = true;
				}

				// コンボ判定(すれすれの場合)
				if ((fLengthPlayer < DRIFT_SPACE_BIG) && (fLengthPlayer > DRIFT_SPACE_SMALL))
				{//	範囲内処理
					m_bFlagIn = true;
					if (m_bFlagIn == true)
					{
						m_nCntFlag++;
						if (m_nCntFlag > 2)
						{
							if (m_bComboFlag == false)
							{//コンボが入る状態ならコンボ追加
								SetCombo(0, false, THROUGH_COMBO_TIME);
								m_nCntFlag = 0;
							}
						}
					}
				}
				else { m_nCntFlag = 0; }
			}
			// Nextに次のSceneを入れる
			pScene = pSceneNext;
		}
	}

	//デバック表示
	if (m_bCrcleCarIn == true)
	{
		CDebugProc::Print("入っている\n");
	}
	else if (m_bCrcleCarIn == false)
	{
		CDebugProc::Print("入っていない\n");
	}
}

//=============================================================================
// 壁との当たり判定
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
				bool bTouch = ((CWall*)pScene)->CollisionWall(&m_pos, &m_OldPos, &m_move, 20.0f);

				if (bTouch)
				{ //当たっているなら減速する
					m_PlayerInfo.fAccel = m_PlayerInfo.fAccel * DECELERATION;
					m_PlayerInfo.nCountTime = 0;
					break;
				}
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//=============================================================================
// 車体の角度を求める
//=============================================================================
void CPlayer::CarCalculate(D3DXVECTOR3 * TirePos)
{
	if (m_bJump) { return; }
	//変数宣言
	float fHight = 0.0f;
	float fTireHight = 0.0f;
	bool bDecisionAngle = false;

	//タイヤの高さの合計値を求める
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		fTireHight += TirePos[nCntTire].y - m_pTire[0]->TIRE_HIGHT;
	}

	//車体の高さを求める
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		if (true == m_pTire[nCntTire]->GetLand())
		{
			fHight = fTireHight / (float)MAX_TIRE;
			m_pos.y = fHight;
			bDecisionAngle = true;
			break;
		}
	}

	//車体の角度を求める
	if (!bDecisionAngle) { return; }

	//----------------------
	// X軸の角度を求める
	//----------------------
	float fHight00 = TirePos[LEFT_FRONT].y - TirePos[LEFT_BACK].y;			//左右の高さを求める
	float fHight01 = TirePos[RIGHT_FRONT].y - TirePos[RIGHT_BACK].y;

	float fLength00 = GetLength(TirePos[LEFT_FRONT], TirePos[LEFT_BACK]);		//２頂点の長さを求める
	float fLength01 = GetLength(TirePos[RIGHT_FRONT], TirePos[RIGHT_BACK]);

	float fAngleLeft = fHight00 / fLength00;		//角度を求める
	float fAngleRight = fHight01 / fLength01;
	RemakeAngle(&fAngleLeft);						//角度修正
	RemakeAngle(&fAngleRight);

	//平均値を求める
	float fAngleX = (fAngleLeft + fAngleRight) / AVERAGE;
	RemakeAngle(&fAngleX);

	//----------------------
	// Z軸の角度を求める
	//----------------------
	fHight00 = TirePos[LEFT_FRONT].y - TirePos[RIGHT_FRONT].y;			//前後の高さを求める
	fHight01 = TirePos[LEFT_BACK].y - TirePos[RIGHT_BACK].y;

	fLength00 = GetLength(TirePos[LEFT_FRONT], TirePos[RIGHT_FRONT]);		//２頂点の長さを求める
	fLength01 = GetLength(TirePos[LEFT_BACK], TirePos[RIGHT_BACK]);

	float fAngleFront = fHight00 / fLength00;		//角度を求める
	float fAngleBack = fHight01 / fLength01;
	RemakeAngle(&fAngleFront);						//角度修正
	RemakeAngle(&fAngleBack);

	//平均値を求める
	float fAngleZ = (fAngleFront + fAngleBack) / AVERAGE;
	RemakeAngle(&fAngleZ);

	//-------------------------
	// 向きの値修正(横転防止)
	//-------------------------
	fAngleX *= -1;
	fAngleZ *= -1;
	RemakeCarRot(&fAngleX);
	RemakeCarRot(&fAngleZ);

	//向きを設定する
	m_rot.x = fAngleX;
	m_rot.z = fAngleZ;

	//CDebugProc::Print("LEFT : %.2f, RIGHT : %.2f\n", fAngleLeft, fAngleRight);
	//CDebugProc::Print("FRONT : %.2f, BACK : %.2f\n", fAngleFront, fAngleBack);
	//CDebugProc::Print("ANGLE : X %.2f, Z %.2f\n", fAngleX, fAngleZ);
}

//=============================================================================
// ジャンプ状態の更新処理
//=============================================================================
void CPlayer::UpdateStateJump(void)
{
	if (m_bJump)
	{//ジャンプ状態の時間を加算
		m_nCountJumpTime++;
		SetCombo(1, true, JUMP_FREAM_TIME);

		//X軸の角度制限
		if (m_rot.x > 0.5f)
		{
			m_rot.x = 0.5f;
		}
		else if (m_rot.x < -0.5f)
		{
			m_rot.x = -0.5f;
		}

		//Z軸の角度制限
		if (m_rot.z > 0.5f)
		{
			m_rot.z = 0.5f;
		}
		else if (m_rot.z < -0.5f)
		{
			m_rot.z = -0.5f;
		}
		return;
	}
	m_nCountJumpTime = 0;
}

//=============================================================================
// 辺の長さを求める
//=============================================================================
float CPlayer::GetLength(D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos)
{
	D3DXVECTOR3 Distance = StartPos - EndPos;
	float fLength = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

	return fLength;
}

//=============================================================================
// 車の角度修正
//=============================================================================
void CPlayer::RemakeCarRot(float * pAngle)
{
	if (*pAngle > ROLLOVER_STOP)
	{
		*pAngle = ROLLOVER_STOP;
	}
	else if (*pAngle < -ROLLOVER_STOP)
	{
		*pAngle = -ROLLOVER_STOP;
	}
}

//=============================================================================
// 角度修正
//=============================================================================
void CPlayer::RemakeAngle(float * pAngle)
{
	//目的の角度修正
	if (*pAngle < -D3DX_PI)
	{
		*pAngle += D3DX_PI * 2.0f;
	}
	if (*pAngle > D3DX_PI)
	{
		*pAngle -= D3DX_PI * 2.0f;
	}
}

//=============================================================================
// デバック表示
//=============================================================================
void CPlayer::DebugProc(void)
{
	//状態の表示
	if (m_state == STATE_DRIVE)
	{
		CDebugProc::Print("状態 : STATE_DRIVE\n");
	}
	else
	{
		CDebugProc::Print("状態 : STATE_REVERSE\n");
	}

	//走行状態の標示
	if (m_StateSpeed == STATE_SPEED_STOP)
	{
		CDebugProc::Print("停止状態\n");
	}

	//位置表示
	CDebugProc::Print("位置 : X %.2f, Y %.2f, Z %.2f\n", m_pos.x, m_pos.y, m_pos.z);

	//タイヤの位置
	for (int nCntTire = 0; nCntTire < MAX_TIRE; nCntTire++)
	{
		CDebugProc::Print("タイヤ[ %d ] : X %.2f, Y %.2f, Z %.2f\n", nCntTire, m_pTire[nCntTire]->GetPos().x, m_pTire[nCntTire]->GetPos().y, m_pTire[nCntTire]->GetPos().z);
	}

	CDebugProc::Print("ジャンプ：%s\n", m_bJump ? "〇" : "×");
}

//=============================================================================
// テールランプの種類の設定
//=============================================================================
void CPlayer::SetTailLampType(CTailLamp::TYPE type)
{
	for (int nCntTailLamp = 0; nCntTailLamp < 2; nCntTailLamp++)
	{// テールランプの数分ループ
		if (NULL != m_apTailLamp[nCntTailLamp])
		{// テールランプを透明にする
			m_apTailLamp[nCntTailLamp]->SetType(type);
		}
	}
}

//=============================================================================
// 川による影響
//=============================================================================
void CPlayer::RiverInfluence(void)
{
	//現在のモードを取得する
	CManager::MODE mode = CManager::GetMode();
	CGround * pRiver = NULL;

	if (mode == CManager::MODE_GAME)
	{//ゲーム
		pRiver = CGame::GetRiver();
	}
	else if (mode == CManager::MODE_TUTORIAL)
	{//チュートリアル
		pRiver = CTutorial::GetRiver();
	}

	if (m_pos.y <= -190.0f)
	{
		if (m_pos.x >= -19200.0f && m_pos.x <= 19200.0f &&
			m_pos.z >= 8800.0f && m_pos.z <= 9200.0f)
		{// 川の範囲内
			if (m_move.x > 0)
			{// 流れに逆らう
				m_move += pRiver->RiverMove() * 1.5f;
			}
			else
			{// 流れに沿う
				m_move += pRiver->RiverMove();
			}

			if ((m_move.x > 0.5f || m_move.x < -0.5f || m_move.z > 0.5f || m_move.z < -0.5f) && m_pos.y <= -200.0f)
			{// 水しぶきエフェクトを出す
				if (m_pLoadEffect != NULL)
				{
					m_pLoadEffect->SetPos(m_pos);
					m_pLoadEffect->Update();
				}
			}
		}
	}

	if (m_pos.x + RIVER_SOUND_RANGE >= -19200.0f && m_pos.x - RIVER_SOUND_RANGE <= 19200.0f &&
		m_pos.z + RIVER_SOUND_RANGE >= 8800.0f && m_pos.z - RIVER_SOUND_RANGE <= 9200.0f)
	{// 川の音を再生
		pRiver->Sound(true);

		// 川の位置
		D3DXVECTOR3 posRiver = D3DXVECTOR3(m_pos.x, 0.0f, 9000.0f);
		if (m_pos.z < 8800.0f) { posRiver.z -= RIVER_SOUND_RANGE; }
		else { posRiver.z += RIVER_SOUND_RANGE; }

		// X軸が川の外
		if (m_pos.x < -19200.0f) { posRiver.x = -19200.0f; }
		else if (m_pos.x > 19200.0f) { posRiver.x = 19200.0f; }

		// プレイヤーと川の距離を求める
		float fLength = sqrtf(powf(m_pos.x - posRiver.x, 2.0f) + powf(m_pos.z - posRiver.z, 2.0f));

		// 音量の設定
		float fVolume = RIVER_SOUND_RANGE - fLength;									 // 距離による音量の変化
		D3DXVECTOR2 volume = D3DXVECTOR2(fVolume, fLength);								 // 正規化するために「D3DXVECTOR2」に値を入れる
		D3DXVec2Normalize(&volume, &volume);											 // 正規化
		CManager::GetSound()->SetVolume(CSound::SOUND_LABEL_SE_RIVER, volume.y * 4.0f);  // 音量の設定
		pRiver->SetDraw(true);															 // 見える状態にする
	}
	else
	{// 音を消す
		pRiver->Sound(false);
		pRiver->SetDraw(false);	//見えない状態にする
	}
}

//=============================================================================
// 噴水の音
//=============================================================================
void CPlayer::FountainSound(void)
{
	CSound *pSound = CManager::GetSound();

	// 噴水の位置を取得
	CScene *pScene = CScene::GetTop(OBJECT_PRIOTITY);
	while (pScene != NULL)
	{// プライオリティー内のリスト構造を最後まで見る
		CScene *pSceneNext = pScene->GetNext();		// 次のオブジェクトを保存

		if (pScene->GetObjType() == OBJTYPE_OBJECT)
		{// タイプが障害物だったら
			CObject *pObject = (CObject*)pScene;	// オブジェクトクラスのポインタ変数にする
			int nType = pObject->GetType();			// 障害物の種類を取得
			if (30 == nType)
			{// 噴水
				m_posFountain = pObject->GetPosition();
				break;
			}
		}

		// Nextに次のSceneを入れる
		pScene = pSceneNext;
	}

	// プレイヤーと川の距離を求める
	float fLength = sqrtf(powf(m_posFountain.x - m_pos.x, 2.0f) + powf(m_posFountain.z - m_pos.z, 2.0f));

	if (fLength < FOUNTAIN_SOUND_RANGE && fLength > -FOUNTAIN_SOUND_RANGE)
	{// 範囲内
		if (!m_bFountainSound)
		{// 噴水の音を再生
			m_bFountainSound = true;
			pSound->PlaySound(CSound::SOUND_LABEL_SE_FOUNTAIN);
		}

		// 音量の設定
		float fVolume = FOUNTAIN_SOUND_RANGE - fLength;						// 距離による音量の変化
		D3DXVECTOR2 volume = D3DXVECTOR2(fVolume, fLength);					// 正規化するために「D3DXVECTOR2」に値を入れる
		D3DXVec2Normalize(&volume, &volume);								// 正規化
		pSound->SetVolume(CSound::SOUND_LABEL_SE_RIVER, volume.y * 4.0f);	// 音量の設定
	}
	else
	{// 音を消す
		if (m_bFountainSound)
		{
			m_bFountainSound = false;
			pSound->StopSound(CSound::SOUND_LABEL_SE_FOUNTAIN);
		}
	}
}

//=============================================================================
// コンボの設定
//=============================================================================
void CPlayer::SetCombo(int nType, bool bJump, int nFrame)
{
	if (m_bJump == bJump && m_bPutin == true)
	{	// ジャンプ時の判定が同 & お客さんが乗っている場合
		if (m_pCombo == NULL && m_nCntCombo >= 60)
		{
			m_pCombo = CCombo::Create((CCombo::TYPE)nType);
			CScore::AddScore(JUMP_ADD_SCORE);
			m_nCntCombo = 0;
			CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_COMBO);
			CAddCoin::Create();		//コインの表示
		}

		m_nCntCombo++;

		if ((m_nCntCombo % nFrame) == 0)
		{	// コンボ加算 & スコア加算
			if (m_pCombo != NULL)
			{
				if (m_pCombo->GetType() != (CCombo::TYPE)nType)
				{
					m_pCombo->SetType((CCombo::TYPE)nType);
				}
				m_pCombo->AddCombo(1);
				CManager::GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_COMBO);
				CScore::AddScore(JUMP_ADD_SCORE + (11 * m_pCombo->GetCombo()));
				CAddCoin::Create();		//コインの表示
			}
		}
	}

}

//=============================================================================
// 煙エフェクトの更新
//=============================================================================
void CPlayer::UpdateSmoke(D3DXVECTOR3 * TirePos)
{
	if ((m_state == STATE_DRIVE) && (m_StateSpeed == STATE_SPEED_BRAKS) && (m_bSmoke == true))
	{//ブレーキ時のエフェクト

		m_nCountTime++;

		if ((m_nCountTime % 2) == 0)
		{
			float fRandPos = (float)((rand() % 60) - 30);
			D3DXVECTOR3	RandPos = D3DXVECTOR3(fRandPos, 0.0f, fRandPos);
			CSmokeEffect::Create(TirePos[LEFT_BACK] + RandPos);	//左後ろタイヤ
			CSmokeEffect::Create(TirePos[RIGHT_BACK] + RandPos);	//右後ろタイヤ
		}

		for (int nCntEffect = 0; nCntEffect < 4; nCntEffect++)
		{
			//火花エフェクトの生成
			CSparkEffect::Create(TirePos[LEFT_BACK]);
			CSparkEffect::Create(TirePos[RIGHT_BACK]);
		}

		if (m_StateHandle == HANDLE_LEFT)
		{// ドリフト時のコンボ
			SetCombo(2, false, DRIFT_COMBO_TIME);
			m_rot.z -= SHAKE_DRIFT;
		}
		else if (m_StateHandle == HANDLE_RIGHT)
		{
			SetCombo(2, false, DRIFT_COMBO_TIME);
			m_rot.z += SHAKE_DRIFT;
		}

	}
	else if ((m_state == STATE_DRIVE) && (m_StateHandle != HANDLE_MAX) && (m_bSmoke == true))
	{//カーブ時のエフェクト
		float fRandPos = (float)((rand() % 20) - 10);
		D3DXVECTOR3	RandPos = D3DXVECTOR3(fRandPos, 0.0f, fRandPos);
		CSmokeEffect::Create(TirePos[LEFT_BACK] + RandPos);	//左後ろタイヤ
		CSmokeEffect::Create(TirePos[RIGHT_BACK] + RandPos);	//右後ろタイヤ
	}
}

//=============================================================================
// 草エフェクトの更新処理
//=============================================================================
void CPlayer::UpdateGrass(D3DXVECTOR3 * TirePos)
{
	if ((m_bGrassEffect) && (m_StateSpeed != STATE_SPEED_STOP) && (m_StateSpeed != STATE_SPEED_BRAKS))
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			float fRandPos = (float)((rand() % 60) - 30);
			D3DXVECTOR3	RandPos = D3DXVECTOR3(fRandPos, 0.0f, fRandPos);
			CGrassEffect::Create(TirePos[LEFT_BACK] + RandPos, (rand() % MAX_PATTERN));	//左後ろタイヤ
			CGrassEffect::Create(TirePos[RIGHT_BACK] + RandPos, (rand() % MAX_PATTERN));	//右後ろタイヤ
		}
	}
}

//=============================================================================
// 音の再生
//=============================================================================
void CPlayer::PlaySoundObj(int nType, CSound * pSound)
{
	switch (nType)
	{
	case TYPE_PHONEBOX: pSound->PlaySoundA(CSound::SOUND_LABEL_SE_STEAL); break;
	case TYPE_CARDBORD: pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SMALLBOX); break;
	case TYPE_CORN:
		pSound->SetVolume(CSound::SOUND_LABEL_SE_SMALLBOX, 0.5f);
		pSound->PlaySoundA(CSound::SOUND_LABEL_SE_SMALLBOX);
		break;
	case TYPE_LEAF:
		if ((m_nCountLeaf % 2) == 0) { m_nCountLeaf = 0; }	//カウンターのリセット

		//音の再生
		if (m_nCountLeaf == 0)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_LEAF, 2.5f);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_LEAF);
		}
		else if(m_nCountLeaf == 1)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_LEAF1, 5.0f);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_LEAF1);
		}

		//カウンターの加算
		m_nCountLeaf++;
		break;
	case TYPE_FENCE:
		if ((m_nCountSound % 5) == 0) { m_nCountSound = 0; }

		if (m_nCountSound == 0)
		{//フェンス00
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FANCE00);
		}
		else if (m_nCountSound == 1)
		{//フェンス01
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FANCE00);
		}
		else if (m_nCountSound == 2)
		{//フェンス02
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FANCE00);
		}
		else if (m_nCountSound == 3)
		{//フェンス02
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FANCE00);
		}
		else if (m_nCountSound == 4)
		{//フェンス02
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_FANCE00);
		}

		m_nCountSound++;	//カウンターの加算
		break;
		
	case TYPE_BENCH:
		if ((m_nCountWood % 2) == 0) { m_nCountWood = 0; }	//カウンターをリセットする

		//音の再生
		if (m_nCountWood == 0)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_WOOD00, 2.0f);
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WOOD00);
		}
		else if (m_nCountWood)
		{
			pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WOOD01);
		}

		//カウンターの加算
		m_nCountWood++;
		break;

	case TYPE_SIGNBOARD: pSound->PlaySoundA(CSound::SOUND_LABEL_SE_WOOD01); break;
	}
}