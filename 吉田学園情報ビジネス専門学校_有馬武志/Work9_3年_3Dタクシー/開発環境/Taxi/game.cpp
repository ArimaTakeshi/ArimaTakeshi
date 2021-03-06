//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "pause.h"
#include "logo.h"
#include "sound.h"
#include "billboord.h"
#include "meshfield.h"
#include "object.h"
#include "fade.h"
#include "effect.h"
#include "time.h"
#include "wall.h"
#include "shadow.h"
#include "loadText.h"
#include "customer.h"
#include "tire.h"
#include "totalscore.h"
#include "score.h"
#include "satisfactionlevel.h"
#include "destination.h"
#include "customer.h"
#include "numberdisplay.h"
#include "combo.h"
#include "arrow.h"
#include "car.h"
#include "texture.h"
#include "humanbace.h"
#include "car.h"
#include "car_point.h"
#include "gamecamera.h"
#include "humannpc.h"
#include "mark.h"
#include "shadermgr.h"
#include "effectmgr.h"
#include "smokeeffect.h"
#include "sparkeffect .h"
#include "policelamp.h"
#include "ground.h"
#include "particlebillboad.h"
#include "effecttool.h"
#include "objbillboad.h"
#include "LCDpanel.h"
#include "grasseffect.h"
#include "addcoin.h"
#include "select.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXT_OBJECTNAME1		"data\\TEXT\\ステージ6\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME1		"data\\TEXT\\ステージ6\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME1			"data\\TEXT\\ステージ6\\wall.txt"			// 読み込むテキストファイル
#define TEXT_PLAYER_MOTION		"data\\TEXT\\Player\\Player.txt"			// プレイヤーのモーションファイル
#define TEXT_BOY_MOTION			"data\\TEXT\\お客さん\\motion_boy.txt"		// 男性モーションファイル
#define TEXT_GIRL_MOTION		"data\\TEXT\\お客さん\\motion_girl.txt"		// 女性モーションファイル
#define TEXT_CUSTOMER_SUMMER	"data\\TEXT\\お客さん\\Summer2.txt"			// お客さんの情報（夏）
#define TEXT_CUSTOMER_HARD		"data\\TEXT\\お客さん\\Summer.txt"			// お客さんの情報 (ハード)
#define TEXT_HUMAN_NPC			"data\\TEXT\\HumanNPC.txt"					// 人NPCの情報
#define VECTOR_ZERO				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
#define TEXT_POINTNAME1			"data\\TEXT\\ステージ6\\point.txt"			// 車のポイント情報
#define TEXT_ROUTENAME1			"data\\TEXT\\ステージ6\\route.txt"			// 車のルート情報
#define TEXT_EFFECT				"data\\TEXT\\particle.txt"					// エフェクト情報
#define TEXT_EFFECT_TOOL		"data\\TEXT\\Particle.txt"					// エフェクト情報
#define TEXT_OBJBILL			"data\\TEXT\\ステージ6\\objbillboad.txt"	// オブジェクトビルボード情報

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CNumber *CGame::m_pNumber = NULL;
CBillBoord *CGame::m_pBillBoord = NULL;
CPolygon3D *CGame::m_pPolygon3D = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CObject *CGame::m_pObject = NULL;
CCarBase *CGame::m_pCar = NULL;
CPause *CGame::m_pPause = NULL;
CModel *CGame::m_pModel = NULL;
CWall *CGame::m_pWall = NULL;
CShadow *CGame::m_pShadow = NULL;
CLoadTextMotion * CGame::m_pPlayerMotion = NULL;
CLoadTextMotion * CGame::m_pBoyMotion = NULL;
CLoadTextMotion * CGame::m_pGirlMotion = NULL;
CSatisfaction * CGame::m_pSatisfaction = NULL;
CGameCamera * CGame::m_pGameCamera = NULL;
CShaderMgr * CGame::m_pShaderMgr = NULL;
CPoliceLamp *CGame::m_pPoliceLamp = NULL;
CGround * CGame::m_pGround = NULL;
CLoadTextEffect * CGame::m_pLoadTextEffect = NULL;
CLogo *CGame::m_pScoreUI[MAX_SCORE_UI] = {};

bool CGame::m_bHelp = false;
bool CGame::m_bPause = false;
CGame::GAMESTATE CGame::m_gameState = GAMESTATE_NONE;
int	CGame::m_nCntSetStage = 0;								// ステージセットカウンタ
CGame::STAGENUM CGame::m_StageState = STAGENUM_1;			// ステージ状態

CGame::Route CGame::m_Route = {};
CGame::Point CGame::m_Point = {};

int CGame::m_nStopRoute = 0;
int CGame::m_nGameCounter = 0;

//ウォークスルー用
bool CGame::m_bDrawUI = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame()
{
	m_gameState = GAMESTATE_NONE;
	m_nCounterGameState = 0;
	m_NowGameState = GAMESTATE_NONE;
	CGame::GetPlayer() = NULL;
	m_StageState = STAGENUM_1;			// ステージ状態
	m_nCntSetStage = 0;
	m_bPause = false;
	m_nEnemyCount = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGame::~CGame(){}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init()
{
	//===================================
	//		 Loadの読み込み場所
	//===================================
	//フェードのテクスチャの読み込み
	CFade::Load();

	//メッシュフィールドのテクスチャの読み込み
	m_pMeshField->Load();

	//ビルボードテクスチャの読み込み
	m_pBillBoord->Load();

	//オブジェクトのテクスチャの読み込み
	m_pObject->Load();

	//NPCのモデルとテクスチャの読み込み
	m_pCar->Load();

	//壁のテクスチャの読み込み
	m_pWall->Load();

	//影のテクスチャ読み込み
	m_pShadow->Load();

	//タイヤのテクスチャ読み込み
	CTire::LoadTexture();

	//矢印の読み込み
	CArrow::Load();

	//マークモデルの読み込み
	CMark::LoadModel();

	//エフェクトテクスチャの読み込み
	CEffectMgr::LoadTex();

	//煙テクスチャの読み込み
	CSmokeEffect::LoadTex();

	//火花テクスチャの読み込み
	CSparkEffect::LoadTex();

	//	警察のランプのテクスチャの読み込み
	m_pPoliceLamp->Load();

	// 川テクスチャの読み込み
	CGround::Load();

	// エフェクトの読み込み
	m_pLoadTextEffect = CLoadTextEffect::Create(TEXT_EFFECT_TOOL);
	CEffectTool::LoadEffect();
	CParticleBillboad::LoadTexture();		//テクスチャの読み込み

	//オブジェクトビルボードのテクスチャを読み込み
	CObjBillboad::LoadTexture();

	// 液晶広告テクスチャの読み込み
	CLCDpanel::Load();

	//草テクスチャの読み込み
	CGrassEffect::LoadTex();

	//コインのテクスチャ読み込み
	CAddCoin::LoadTex();

	//===================================
	//		Create
	//===================================
	//シェーダーマネージャーの生成
	//if (m_pShaderMgr == NULL) { m_pShaderMgr = CShaderMgr::Create(); }

	if (m_pPlayerMotion == NULL) { m_pPlayerMotion = CLoadTextMotion::Create(TEXT_PLAYER_MOTION); }	//プレイヤーのモーション読み込み
	CPlayer::LoadModel();	//モデルの読み込み

	if (m_pBoyMotion == NULL) { m_pBoyMotion = CLoadTextMotion::Create(TEXT_BOY_MOTION); }		//男性モーション読み込み
	if (m_pGirlMotion == NULL) { m_pGirlMotion = CLoadTextMotion::Create(TEXT_GIRL_MOTION); }	//女性モーション読み込み
	CHumanBace::LoadModel();	//人モデルの読み込み

	//タイマーの生成
	CTime::Create(D3DXVECTOR3(150.0f, 70.0f, 0.0f));

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f));
	m_pPlayer->LoadText();

	//お客さんの生成
	if (CSelect::GetSelectLevel() == 0)
	{	// 難易度Easy
		CLoadTextCustomer::Create(TEXT_CUSTOMER_SUMMER); //イージー用
	}
	else if (CSelect::GetSelectLevel() == 1)
	{	// 難易度Hard
		CLoadTextCustomer::Create(TEXT_CUSTOMER_HARD); //ハード用
	}

	//人のNPC生成
	//CLoadTextHumanNPC::Create(TEXT_HUMAN_NPC);

	// UI
	CLogo::Create(D3DXVECTOR3(1200.0f, 650.0f, 0.0f), D3DXVECTOR2(60.0f, 60.0f), CTexture::TYPE_GEARCHANGE, 0, CLogo::TYPE_LOGO);		// ギア切替
	CLogo::Create(D3DXVECTOR3(1200.0f, 560.0f, 0.0f), D3DXVECTOR2(60.0f, 30.0f), CTexture::TYPE_BOARDING, 0, CLogo::TYPE_LOGO);		// 空車 or 乗車
	m_pScoreUI[0] = CLogo::Create(D3DXVECTOR3(1080.0f, 95.0f, 0.0f), D3DXVECTOR2(160.0f, 25.0f), CTexture::TYPE_FREAME, 0, CLogo::TYPE_LOGO);			// トータルスコアの枠
	m_pScoreUI[1] = CLogo::Create(D3DXVECTOR3(1080.0f, 155.0f, 0.0f), D3DXVECTOR2(150.0f, 25.0f), CTexture::TYPE_FREAME, 0, CLogo::TYPE_LOGO);			// スコアの枠
	m_pScoreUI[2] = CLogo::Create(D3DXVECTOR3(1080.0f, 60.0f, 0.0f), D3DXVECTOR2(180.0f, 15.0f), CTexture::TYPE_TOTALSCORELOGO, 0, CLogo::TYPE_LOGO);	// トータルスコア
	m_pScoreUI[3] = CLogo::Create(D3DXVECTOR3(1080.0f, 120.0f, 0.0f), D3DXVECTOR2(160.0f, 15.0f), CTexture::TYPE_SCORELOGO, 0, CLogo::TYPE_LOGO);		// スコア
	m_pScoreUI[4] = CLogo::Create(D3DXVECTOR3(950.0f, 95.0f, 0.0f), D3DXVECTOR2(13.0f, 13.0f), CTexture::TYPE_MONEY_TEN, 0, CLogo::TYPE_LOGO);			// \マーク表示(トータルスコア)
	m_pScoreUI[5] = CLogo::Create(D3DXVECTOR3(958.0f, 155.0f, 0.0f), D3DXVECTOR2(13.0f, 13.0f), CTexture::TYPE_MONEY_TEN, 0, CLogo::TYPE_LOGO);		// \マーク表示(スコア)

	// 満足度の生成
	m_pSatisfaction = CSatisfaction::Create(D3DXVECTOR3(30.0f, 650.0f, 0.0f), D3DXVECTOR2(15.0f, 35.0f), 3);

	// トータルスコアの生成
	CTotalScore::Create(D3DXVECTOR3(1205.0f, 95.0f, 0.0f));

	// スコアの生成
	CScore::Create(D3DXVECTOR3(1200.0f, 156.0f, 0.0f));

	// 川の生成
	m_pGround = CGround::Create(D3DXVECTOR3(0.0f, -185.0f, 9000.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20000.0f, 300.0f), 0);

	// 液晶広告の生成
	CLCDpanel::Create(D3DXVECTOR3(8100.0f, 450.0f, -5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3.5f);
	CLCDpanel::Create(D3DXVECTOR3(8100.0f, 450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3.5f);
	CLCDpanel::Create(D3DXVECTOR3(8100.0f, 450.0f, 5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 3.5f);

	CLCDpanel::Create(D3DXVECTOR3(12854.0f, 450.0f, 1750.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 4.5f);
	CLCDpanel::Create(D3DXVECTOR3(12550.0f, 450.0f, 2008.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 4.5f);

	CLCDpanel::Create(D3DXVECTOR3(-14705.0f, 400.0f, -1754.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 4.5f);
	CLCDpanel::Create(D3DXVECTOR3(-14456.0f, 400.0f, -2007.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 4.5f);

	//ゲームカメラの生成
	if (m_pGameCamera == NULL)
	{
		m_pGameCamera = new CGameCamera;

		if (m_pGameCamera != NULL) { m_pGameCamera->Init(); }
	}

	//===================================
	//		変数の初期化
	//===================================
	m_gameState = GAMESTATE_NORMAL;		//通常状態に
	m_nCntSetStage = 0;					//どこのステージから開始するか
	m_nEnemyCount = 0;					//敵の数初期化
	m_StageState = STAGENUM_1;			// ステージ状態
	m_bPause = false;					//ポーズを初期化
	m_nGameCounter = 0;					//カウンターの初期化

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//ポーズ削除
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	// トータルスコアと満足度の設定
	if (m_pSatisfaction != NULL)
	{
		CResult::SetGrades(CTotalScore::GetScore(), m_pSatisfaction->GetLevel());
		CRanking::RankingSave(CTotalScore::GetScore(), m_pSatisfaction->GetLevel());
	}

	//===================================
	//	　　UnLoadの破棄する場所
	//===================================
	//メッシュフィールドテクスチャの破棄
	m_pMeshField->UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//ビルボードテクスチャの破棄
	m_pBillBoord->UnLoad();

	//オブジェクトのテクスチャの破棄
	m_pObject->UnLoad();

	//NPCのモデルとテクスチャの破棄
	m_pCar->UnLoad();

	//壁のテクスチャの破棄
	m_pWall->UnLoad();

	//影のテクスチャの破棄
	m_pShadow->UnLoad();

	//タイヤのテクスチャ破棄
	CTire::UnloadTexture();

	// 矢印の破棄
	CArrow::UnLoad();

	//マークモデルの破棄
	CMark::UnloadModel();

	//エフェクトテクスチャの破棄
	CEffectMgr::UnloadTex();

	//煙テクスチャの破棄
	CSmokeEffect::Unload();

	//火花テクスチャの破棄
	CSparkEffect::Unload();

	//	警察のランプの破棄
	m_pPoliceLamp->UnLoad();

	// 川テクスチャの破棄
	CGround::UnLoad();

	//エフェクトテクスチャの破棄
	CParticleBillboad::UnloadTexture();

	// エフェクトの破棄
	CEffectTool::UnloadEffect();

	//オブジェクトテクスチャの破棄
	CObjBillboad::UnloadTexture();

	// 液晶広告テクスチャの破棄
	CLCDpanel::Unload();

	//草テクスチャの破棄
	CGrassEffect::Unload();

	//コインテクスチャの破棄
	CAddCoin::UnloadTex();

	//===================================
	//	　　クラスの破棄
	//===================================
	//メッシュフィールドの破棄
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	// スタート合図の破棄
	m_pGameCamera->UninitSignal();

	// UIの破棄
	for (int nCnt = 0; nCnt < MAX_SCORE_UI; nCnt++)
	{
		if (m_pScoreUI[nCnt] != NULL)
		{
			m_pScoreUI[nCnt]->Uninit();
			m_pScoreUI[nCnt] = NULL;
		}
	}

	// オブジェクトの破棄
	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		m_pObject = NULL;
	}

	// 壁の破棄
	if (m_pWall != NULL)
	{
		m_pWall->Uninit();
		m_pWall = NULL;
	}

	// 車の破棄
	if (m_pCar != NULL)
	{
		m_pCar->Uninit();
		m_pCar = NULL;
	}

	// テールランプ(警察)の破棄
	if (m_pPoliceLamp != NULL)
	{
		m_pPoliceLamp->Uninit();
		m_pPoliceLamp = NULL;
	}

	// ビルボードの破棄
	if (m_pBillBoord != NULL)
	{
		m_pBillBoord->Uninit();
		m_pBillBoord = NULL;
	}
	
	//フェード以外の破棄
	CScene::NotFadeReleseAll();

	//プレイヤーのモーションの破棄
	if (m_pPlayerMotion != NULL)
	{
		m_pPlayerMotion->Uninit();
		delete m_pPlayerMotion;
		m_pPlayerMotion = NULL;
	}

	//男性のモーション破棄
	if (m_pBoyMotion != NULL)
	{
		m_pBoyMotion->Uninit();
		delete m_pBoyMotion;
		m_pBoyMotion = NULL;
	}

	//女性モーションの破棄
	if (m_pGirlMotion != NULL)
	{
		m_pGirlMotion->Uninit();
		delete m_pGirlMotion;
		m_pGirlMotion = NULL;
	}

	//プレイヤーモデルの破棄
	CPlayer::UnloadModel();

	//人モデルの破棄
	CHumanBace::UnloadModel();

	//カメラの破棄
	if (m_pGameCamera != NULL)
	{
		m_pGameCamera->Uninit();
		delete m_pGameCamera;
		m_pGameCamera = NULL;
	}

	//シェーダーマネージャーの破棄
	if (m_pShaderMgr != NULL)
	{
		m_pShaderMgr->Uninit();
		delete m_pShaderMgr;
		m_pShaderMgr = NULL;
	}

	//読み込んだエフェクトの破棄
	if (m_pLoadTextEffect != NULL)
	{
		m_pLoadTextEffect->Uninit();
		delete m_pLoadTextEffect;
		m_pLoadTextEffect = NULL;
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CXInput *pCInputJoypad = CManager::GetXInput();

	//	カウンター進める
	m_nGameCounter++;

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true)
	{
		m_bDrawUI = m_bDrawUI ? false : true;
	}

	if (m_pPause == false)
	{//開く音
		//現在の状態を保存
		m_NowGameState = GetGameState();

		//カメラの更新処理
		if (m_pGameCamera != NULL) { m_pGameCamera->Update(); }

		switch (m_NowGameState)
		{
		case GAMESTATE_NORMAL:	//通常の状態

			//ステージ設定
			SetStage();

			break;
		case GAMESTATE_CLEAR:	//ゲームをクリアした状態
			m_nCounterGameState++;

			if (m_nCounterGameState >= 60)
			{//画面（モード）の設定
				CFade::Create(CManager::MODE_RESULT);
			}
			break;
		case GAMESTATE_OVER:	//ゲームで負けたときの状態
			m_nCounterGameState++;

			if (m_nCounterGameState >= 60)
			{//画面（モード）の設定
				CFade::Create(CManager::MODE_RESULT);
			}
			break;
		}
	}

	if (CTime::GetTime() == 0) { return; }
	//ポーズの処理
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_P) == true || pCInputJoypad->GetTrigger(CXInput::XIJS_BUTTON_4))
	{//Pキーが押されたら
		int nType = 0;
		if (pCInputJoypad->GetTrigger(CXInput::XIJS_BUTTON_4)) { nType = 1; }
		m_bPause = m_bPause ? false : true;

		switch (m_bPause)
		{
		case true:
			if (m_pPause == NULL)
			{
				//ポーズを開く音
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_OPEN);

				//ポーズの生成
				m_pPause = CPause::Create();
				m_pPause->SetTexType(nType);

				//ポーズとフェードだけ回す
				CScene::SetUpdatePri(7);
			}
			break;
		case false:
			if (m_pPause != NULL)
			{
				if (CPause::GetbPause() == false)
				{
					//ポーズを閉じる音
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_CLOSE);

					//ポーズを削除
					m_pPause->Uninit();
					m_pPause = NULL;

					//アップデート順番をすべて回す
					CScene::SetUpdatePri(0);
				}
			}
		}
	}

	if (CManager::GetInput()->GetKeyboardTrigger(DIK_5))
	{
		m_pSatisfaction->AddLevel(1);
	}
	else if (CManager::GetInput()->GetKeyboardTrigger(DIK_6))
	{
		m_pSatisfaction->Subtraction(1);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
	//カメラの設定
	if (m_pGameCamera != NULL) { m_pGameCamera->SetCamera(); }
}

//=============================================================================
// ポーズを押したかどうか
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;

	switch (m_bPause)
	{
	case true:
		if (m_pPause == NULL)
		{
			//ポーズの生成
			m_pPause = CPause::Create();

			CScene::SetUpdatePri(7);
		}
		break;
	case false:
		if (m_pPause != NULL)
		{
			m_pPause->Uninit();
			m_pPause = NULL;

			CScene::SetUpdatePri(0);
		}
	}
}
//=============================================================================
// ステージ状態
//=============================================================================
void CGame::SetNumState(STAGENUM stagenum)
{
	m_StageState = stagenum;
}

//=============================================================================
// ゲーム設定処理
//=============================================================================
void CGame::SetStageState(STAGENUM stage)
{
	//削除する処理
	if (m_StageState != stage)
	{
		m_pWall->DeleteWall();
		m_pObject->DeleteObject();
		m_pBillBoord->ResetBillboord();
		m_pMeshField->DeleteMeshField();
	}

	//状態を記憶
	m_StageState = stage;

	//削除する処理
	if (m_StageState == stage)
	{
		//m_pPlayer->ResetPlayer();
	}
	m_nCntSetStage = 0;
}
//=============================================================================
// ステージ設定
//=============================================================================
void CGame::SetStage(void)
{
	//サウンドのポインタ
	CSound *pSound = CManager::GetSound();

	if (m_nCntSetStage == 0)
	{
		//=====================================================================
		//	ステージ1
		//=====================================================================
		if (m_StageState == STAGENUM_1)
		{
			//マップを読み込む
			TextLoad(6);
			WallTextLoad(6);
			MeshTextLoad(6);
			NpcTextLoad(6);
			PointTextLoad(6);
			RouteLoad(6);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, m_Map[nCount].m_scale,0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}

			//オブジェクトビルボードの生成
			CLoadTextObjBill::Create(TEXT_OBJBILL);

			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//フィールドの生成
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fTexXUV, m_Mesh[nCount].m_fTexYUV,
					m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength,
					m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
			for (int nCount = 0; nCount < m_nSetNpcNum; nCount++)
			{
				//車の生成
				m_pCar = CCarBase::Create(m_aNpc[nCount].m_pos, m_aNpc[nCount].m_rot, m_aNpc[nCount].m_scale, m_aNpc[nCount].m_nTexType,
					m_aNpc[nCount].m_nType, m_aNpc[nCount].m_nCollision, m_aNpc[nCount].m_nRoute, m_aNpc[nCount].bLoop);
			}
		}

		m_nCntSetStage = 1;
	}
}
//===============================================================================
// ファイルからロード
//===============================================================================
void CGame::TextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	//ファイルポインタの初期化処理
	pFile = NULL;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_OBJECTNAME1, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "OBJECT_SETNUM = ", strlen("OBJECT_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("OBJECT_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetObjectNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetObjectNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "OBJECT_START", strlen("OBJECT_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//種類のを読み込み
					if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Map[nCntObject].m_nType = atoi(pStrcur);
					}
					//種類のを読み込み
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURETYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Map[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//当たり判定を読み込み
					if (memcmp(pStrcur, "COLLISION = ", strlen("COLLISION = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("COLLISION = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Map[nCntObject].m_nCollision = atoi(pStrcur);
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
						m_Map[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_pos.z = (float)atof(pStrcur);

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
						m_Map[nCntObject].m_rot.x = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_rot.y = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_rot.z = (float)atof(pStrcur);
					}
					//SIZを読み込み
					if (memcmp(pStrcur, "SIZ = ", strlen("SIZ = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("SIZ = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_scale.x = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_scale.y = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_scale.z = (float)atof(pStrcur);
					}
					else if (memcmp(pStrcur, "OBJECT_END", strlen("OBJECT_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}

	//m_pMarkObject->SetObjectNum(CMarkObject::GetObjectNum() + m_nSetObjectNum);
}
//===============================================================================
// メッシュフィールドをファイルからロード
//===============================================================================
void CGame::MeshTextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

						//ファイルポインタの初期化処理
	pFile = NULL;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_MESHFIELDNAME1, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "MESHFIELD_SETNUM = ", strlen("MESHFIELD_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("MESHFIELD_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetMeshFieldNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetMeshFieldNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "MESHFIELD_START", strlen("MESHFIELD_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//種類のを読み込み
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURETYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//横の分割数を読み込み
					if (memcmp(pStrcur, "X_DIVIDE = ", strlen("X_DIVIDE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("X_DIVIDE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_nWidthDivide = atoi(pStrcur);
					}
					//縦の分割数を読み込み
					if (memcmp(pStrcur, "Z_DIVIDE = ", strlen("Z_DIVIDE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("Z_DIVIDE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_nDepthDivide = atoi(pStrcur);
					}
					//横のテクスチャ座標を読み込み
					if (memcmp(pStrcur, "X_TEXUV = ", strlen("X_TEXUV = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("X_TEXUV = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fTexXUV = (float)atoi(pStrcur);
					}
					//縦のテクスチャ座標を読み込み
					if (memcmp(pStrcur, "Y_TEXUV = ", strlen("Y_TEXUV = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("Y_TEXUV = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fTexYUV = (float)atoi(pStrcur);
					}
					//横の長さを読み込み
					if (memcmp(pStrcur, "X_LENGTH = ", strlen("X_LENGTH = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("X_LENGTH = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fWidthLength = (float)atoi(pStrcur);
					}
					//縦の長さを読み込み
					if (memcmp(pStrcur, "Z_LENGTH = ", strlen("Z_LENGTH = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("Z_LENGTH = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fDepthLength = (float)atoi(pStrcur);
					}
					//１頂点の高さ
					if (memcmp(pStrcur, "VTX0_HEIGHT = ", strlen("VTX0_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX0_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No0 = (float)atoi(pStrcur);
					}
					//２頂点の高さ
					if (memcmp(pStrcur, "VTX1_HEIGHT = ", strlen("VTX1_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX1_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No1 = (float)atoi(pStrcur);
					}
					//３頂点の高さ
					if (memcmp(pStrcur, "VTX2_HEIGHT = ", strlen("VTX2_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX2_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No2 = (float)atoi(pStrcur);
					}
					//４頂点の高さ
					if (memcmp(pStrcur, "VTX3_HEIGHT = ", strlen("VTX3_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX3_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No3 = (float)atoi(pStrcur);
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
						m_Mesh[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Mesh[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Mesh[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					else if (memcmp(pStrcur, "MESHFIELD_END", strlen("MESHFIELD_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}

	//m_pMarkMeshField->SetMeshFieldNum(CMarkMeshField::GetMeshFieldNum() + m_nSetMeshFieldNum);
}

//===============================================================================
// 壁をファイルからロード
//===============================================================================
void CGame::WallTextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	//ファイルポインタの初期化処理
	pFile = NULL;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_WALLNAME1, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "WALL_SETNUM = ", strlen("WALL_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("WALL_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetWallNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetWallNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "WALL_START", strlen("WALL_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

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
						m_aWall[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_pos.z = (float)atof(pStrcur);

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
						m_aWall[nCntObject].m_rot.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_rot.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_rot.z = (float)atof(pStrcur);

					}
					//WIDTHを読み込み
					if (memcmp(pStrcur, "WIDTH = ", strlen("WIDTH = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("WIDTH = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_fWidthDivide = (float)atof(pStrcur);
					}
					//HIGHTを読み込み
					if (memcmp(pStrcur, "HIGHT = ", strlen("HIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("HIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_fHightDivide = (float)atof(pStrcur);
					}
					//HIGHTを読み込み
					if (memcmp(pStrcur, "TEXTURE = ", strlen("TEXTURE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_nTexType = (int)atof(pStrcur);
					}
					else if (memcmp(pStrcur, "WALL_END", strlen("WALL_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}

	//m_pMarkWall->SetWallNum(CMarkWall::GetWallNum() + m_nSetWallNum);
}
//===============================================================================
// ファイルからロード
//===============================================================================
void CGame::NpcTextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

						//ファイルを開く 読み込み
	pFile = fopen(TEXT_CARNAME, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "NPC_SETNUM = ", strlen("NPC_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("NPC_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetNpcNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetNpcNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "NPC_START", strlen("NPC_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//種類のを読み込み
					if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aNpc[nCntObject].m_nType = atoi(pStrcur);
					}
					//種類のを読み込み
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURETYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aNpc[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//当たり判定を読み込み
					if (memcmp(pStrcur, "COLLISION = ", strlen("COLLISION = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("COLLISION = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aNpc[nCntObject].m_nCollision = atoi(pStrcur);
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
						m_aNpc[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_pos.z = (float)atof(pStrcur);

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
						m_aNpc[nCntObject].m_rot.x = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_rot.y = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_rot.z = (float)atof(pStrcur);
					}
					//SIZを読み込み
					if (memcmp(pStrcur, "SIZ = ", strlen("SIZ = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("SIZ = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_scale.x = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_scale.y = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_scale.z = (float)atof(pStrcur);
					}
					//ポイントの番号読み込み
					if (memcmp(pStrcur, "ROUTE = ", strlen("ROUTE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("ROUTE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aNpc[nCntObject].m_nRoute = (int)atof(pStrcur);

					}
					//ポイントの番号読み込み
					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("LOOP = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);

						//文字列変換
						if ((int)atof(pStrcur) == 0) {
							(bool)m_aNpc[nCntObject].bLoop = false;
						}
						else if ((int)atof(pStrcur) == 1) {
							(bool)m_aNpc[nCntObject].bLoop = true;
						}
						else { (bool)m_aNpc[nCntObject].bLoop = false; }

					}
					else if (memcmp(pStrcur, "NPC_END", strlen("NPC_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}
}

//===============================================================================
// ファイルからロード
//===============================================================================
void CGame::PointTextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

						//	変数の初期設定
	m_Point.nCount = 0;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_POINTNAME1, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		while (memcmp(pStrcur, "POINT_START", strlen("POINT_START")) == 0)
		{
			while (1)
			{
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);

				//番号のを読み込み
				if (memcmp(pStrcur, "NUM = ", strlen("NUM = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("NUM = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					m_Point.nNum[m_Point.nCount] = atoi(pStrcur);
				}
				//POSを読み込み
				else if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POS = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					m_Point.pos[m_Point.nCount].x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					m_Point.pos[m_Point.nCount].y = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					m_Point.pos[m_Point.nCount].z = (float)atof(pStrcur);

				}
				else if (memcmp(pStrcur, "POINT_END", strlen("POINT_END")) == 0)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);
					break;
				}
			}
			m_Point.nCount++;		//	カウンター進める
		}
	}
	fclose(pFile);
}

//===============================================================================
//	経路のパターンの読み込み
//===============================================================================
void CGame::RouteLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

						//	変数の初期設定
	for (int nCount = 0; nCount < MAX_MAP_ROUTE; nCount++)
	{
		m_Route.nPointCount[nCount] = 0;
	}
	m_Route.nRouteCount = 0;


	//ファイルを開く 読み込み
	pFile = fopen(TEXT_ROUTENAME1, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		while (memcmp(pStrcur, "ROUTE_START", strlen("ROUTE_START")) == 0)
		{
			while (1)
			{
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);

				//ポイントのを読み込み
				if (memcmp(pStrcur, "POINT = ", strlen("POINT = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POINT = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					m_Route.nIndexPoint[m_Route.nRouteCount][m_Route.nPointCount[m_Route.nRouteCount]] = atoi(pStrcur);
					m_Route.nPointCount[m_Route.nRouteCount]++;	//	カウンター進める
				}
				else if (memcmp(pStrcur, "ROUTE_END", strlen("ROUTE_END")) == 0)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);
					break;
				}
			}
			m_Route.nRouteCount++;	//	カウンター進める
		}
	}
	fclose(pFile);
}

//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CGame::ReadLine(FILE *pFile, char *pDst)
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
char *CGame::GetLineTop(char * pStr)
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
int CGame::PopString(char * pStr, char * pDest)
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