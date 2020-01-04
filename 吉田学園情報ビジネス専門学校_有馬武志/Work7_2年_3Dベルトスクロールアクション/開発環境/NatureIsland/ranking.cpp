//---------------------------------------------------------------------
// ランキング処理 [ranking.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ranking.h"
#include "manager.h"
#include "scene.h"
#include "fade.h"
#include "time.h"
#include "number.h"
#include "logo.h"
#include "player.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"
#include "wall.h"
#include "ground.h"
#include "billboord.h"
#include "effect.h"
#include "item.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RANKINGLOGO_TEXTURENAME		"data\\TEXTURE\\Ranking.png"		//テクスチャのファイル名
#define RANK1_TEXTURENAME			"data\\TEXTURE\\rank1.png"		//テクスチャのファイル名
#define RANK2_TEXTURENAME			"data\\TEXTURE\\rank2.png"		//テクスチャのファイル名
#define RANK3_TEXTURENAME			"data\\TEXTURE\\rank3.png"		//テクスチャのファイル名
#define RANK4_TEXTURENAME			"data\\TEXTURE\\rank4.png"		//テクスチャのファイル名
#define RANK5_TEXTURENAME			"data\\TEXTURE\\rank5.png"		//テクスチャのファイル名

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer		*CRanking::m_pPlayer = NULL;
CBillBoord	*CRanking::m_pBillBoord = NULL;
CPolygon3D	*CRanking::m_pPolygon3D = NULL;
CMeshField	*CRanking::m_pMeshField = NULL;
CObject		*CRanking::m_pObject = NULL;
CModel		*CRanking::m_pModel = NULL;
CEffect		*CRanking::m_pEffect = NULL;
CWall		*CRanking::m_pWall = NULL;
CGround		*CRanking::m_pGround = NULL;
CItem		*CRanking::m_pItem = NULL;

//--------------------------------------------
//ランキングクラス コンストラクタ
//--------------------------------------------
CRanking::CRanking(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nCntTimer = 0;
	m_nCntCor = 0;
}

//--------------------------------------------
//ランキングクラス デストラクタ
//--------------------------------------------
CRanking::~CRanking()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CRanking *CRanking::Create(void)
{
	//タイトルのポインタ
	CRanking *pRanking;
	pRanking = new CRanking;
	//タイトルの初期化
	pRanking->Init();
	//タイトルの情報を返す
	return pRanking;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	//===================================
	//		 Loadの読み込み場所
	//===================================
	CNumber::Load();

	CLogo::Load();

	//フェードのテクスチャの読み込み
	CFade::Load();

	//プレイヤーのテクスチャの読み込み
	m_pPlayer->Load();

	//メッシュフィールドのテクスチャの読み込み
	m_pMeshField->Load();

	//ビルボードテクスチャの読み込み
	m_pBillBoord->Load();

	//オブジェクトのテクスチャの読み込み
	m_pObject->Load();

	//エフェクトのテクスチャの読み込み
	m_pEffect->Load();

	//地面のテクスチャの読み込み
	m_pGround->Load();

	//壁のテクスチャの読み込み
	m_pWall->Load();

	//アイテムのテクスチャ読み込み
	m_pItem->Load();

	//影のテクスチャ読み込み
	m_pShadow->Load();

	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		RANKINGLOGO_TEXTURENAME,
		&m_pTexture[0]);
	// 順位テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		RANK1_TEXTURENAME,
		&m_pTextureRank[0]);
	// 順位テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		RANK2_TEXTURENAME,
		&m_pTextureRank[1]);
	// 順位テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		RANK3_TEXTURENAME,
		&m_pTextureRank[2]);
	// 順位テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		RANK4_TEXTURENAME,
		&m_pTextureRank[3]);
	// 順位テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		RANK5_TEXTURENAME,
		&m_pTextureRank[4]);


	//===================================
	//		 生成する場所
	//===================================
	CreateStage();
	CreateObject();
	//メッシュフィールド川の生成 Create(位置,分割数X,分割数Z,範囲X,範囲Z,テクスチャタイプ,メッシュの種類)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-700.0f, -50.0f, 700.0f), 14, 14, 1400.0f, 1400.0f,0.0f,0.0f,0.0f,0.0f, 1, 0);

	//シーン2Dのロゴ
	m_pScene2DLogo = CScene2D::Create();
	m_pScene2DLogo->BindTexture(m_pTexture[0]);
	m_pScene2DLogo->SetPosSize(D3DXVECTOR3(600, 100, 0), D3DXVECTOR2(200, 50));

	//ランキング用スコア
	int aScore[MAX_RANKING] = {};

	//タイムテクスチャ用変数
	int nAnswer = 0;
	int nKeisan = 1;

	//ナンバーとロゴの生成
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{	//nCnt番のタイムを取得する
		aScore[nCnt] = *CManager::GetRankingScore(nCnt);
		//タイムテクスチャ用変数初期化
		nAnswer = 0;
		nKeisan = 1;

		for (int nCntNum = 0; nCntNum < TIME_MAX; nCntNum++)
		{	//タイム生成
			m_RankTime[nCnt][nCntNum] = new CNumber;
			m_RankTime[nCnt][nCntNum]->Init(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - (nCntNum * 30.0f), 200.0f + (nCnt * 80.0f), 0));
			//テクスチャの値を求める 1の位から100の位まで
			nAnswer = aScore[nCnt] % (nKeisan * 10) / nKeisan;
			nKeisan *= 10;
			// テクスチャに反映
			m_RankTime[nCnt][nCntNum]->SetNumber(nAnswer);
		}
		//順位のロゴ
		m_pScene2DRank[nCnt] = CScene2D::Create();
		m_pScene2DRank[nCnt]->BindTexture(m_pTextureRank[nCnt]);
		m_pScene2DRank[nCnt]->SetPosSize(D3DXVECTOR3(750.0f, 200.0f + (nCnt * 80), 0), D3DXVECTOR2(30, 30));
	}

	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 200.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 280.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 440.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 1.35f - 30.0f, 520.0f, 0.0f), D3DXVECTOR2(100.0f, 30.0f), 1);


	return S_OK;
}

//=============================================================================
// ランキングクラス 終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//===================================
	//	　　UnLoadの破棄する場所
	//===================================
	CLogo::UnLoad();

	//メッシュフィールドテクスチャの破棄
	m_pMeshField->UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//ビルボードテクスチャの破棄
	m_pBillBoord->UnLoad();

	//オブジェクトのテクスチャの破棄
	m_pObject->UnLoad();

	//プレイヤーのテクスチャの破棄
	m_pPlayer->UnLoad();

	//エフェクトのテクスチャの破棄
	m_pEffect->UnLoad();

	//地面のテクスチャの破棄
	m_pGround->UnLoad();

	//壁のテクスチャの破棄
	m_pWall->UnLoad();

	//影のテクスチャ読み込み
	m_pShadow->UnLoad();

	//メッシュフィールドの破棄
	if (m_pMeshField != NULL)
	{
		m_pMeshField = NULL;
	}
	//オブジェクトの破棄
	if (m_pObject != NULL)
	{
		m_pObject = NULL;
	}

	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTextureRank[nCnt] != NULL)
		{
			m_pTextureRank[nCnt]->Release();
			m_pTextureRank[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCntNum = 0; nCntNum < TIME_MAX; nCntNum++)
		{
			if (m_RankTime[nCnt][nCntNum] != NULL)
			{
				//ナンバー(タイム) 破棄  ※CScene派生ではない物
				m_RankTime[nCnt][nCntNum]->Uninit();
				m_RankTime[nCnt][nCntNum] = NULL;
			}
		}
	}

	//シーン派生の自分を削除
	CScene::Release();
	CScene::Delete();
	//フェード以外削除
	CScene::NotFadeReleseAll();
}

//=============================================================================
// ランキングクラス 更新処理
//=============================================================================
void CRanking::Update(void)
{
	//キーボード情報を取得
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンド情報を取得
	CSound *pSound = CManager::GetSound();

	int GameScore = 0;
	int RankingScore = 0;
	//色変えカウント
	m_nCntCor++;

	//切り替え処理
	//フェードのポイント
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true || pCInputMouse->GetMouseTrigger(0) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true)
	{//タイトルからゲームへ
	 //フェードが始まったら
		if (pFade == CFade::FADE_NONE)
		{
			//ポーズの選択の決定音
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
			CFade::Create(CManager::MODE_TITLE);
		}
	}
	//切り替え処理(タイマー)
	m_nCntTimer++;
	if (m_nCntTimer >= 600 && CFade::GetFade() == CFade::FADE_NONE)
	{

		CFade::Create(CManager::MODE_TITLE);
		m_nCntTimer = 0;
	}
}

//=============================================================================
// ランキングクラス 描画処理
//=============================================================================
void CRanking::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{
			m_RankTime[nCnt][nCntTime]->Draw();
		}
	}
}
//=============================================================================
// ステージの生成を一括管理
//=============================================================================
void CRanking::CreateStage(void)
{
	//===================================
	//		 地面を生成する場所
	//===================================
#if 1
	//メッシュフィールドの生成 Create(位置,分割数X,分割数Z,範囲X,範囲Z,テクスチャタイプ,メッシュの種類)
	m_pMeshField = CMeshField::Create(D3DXVECTOR3(-750.0f, 0.0f, 500.0f), 4, 4, 1500.0f, 1000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 0);

	//壁の生成
	m_pWall = CWall::Create(D3DXVECTOR3(750.0f, -200.0f, 0.0f), D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);		// 右
	m_pWall = CWall::Create(D3DXVECTOR3(-750.0f, -200.0f, 0.0f), D3DXVECTOR2(500.0f, 200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), 0);	// 左
	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -200.0f, -500.0f), D3DXVECTOR2(750.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);	// 手前

	m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 500.0f), D3DXVECTOR2(1000.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 6);		// 背景
#endif

																																	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-70.0f, 0.0f, -300.0f));
}
//=============================================================================
// ステージの生成を一括管理
//=============================================================================
void CRanking::CreateObject(void)
{
#if 1	// 家(仮)
	m_pObject = CObject::Create(D3DXVECTOR3(-150.0f, 0.0f, 0.0f), 0.0f, 15, 13, CObject::MOVETYPE_HOUSE, 1);
#endif
#if 1	// 木
	SetTree(D3DXVECTOR3(-470.0f, 0.0f, 150.0f));
	SetTree(D3DXVECTOR3(-450.0f, 0.0f, -100.0f));
	SetTree(D3DXVECTOR3(-410.0f, 0.0f, 320.0f));
	SetTree(D3DXVECTOR3(-370.0f, 0.0f, -20.0f));
	SetTree(D3DXVECTOR3(-350.0f, 0.0f, 200.0f));
	SetTree(D3DXVECTOR3(-290.0f, 0.0f, 400.0f));
	SetTree(D3DXVECTOR3(-130.0f, 0.0f, 270.0f));
	SetTree(D3DXVECTOR3(-10.0f, 0.0f, 400.0f));
	SetTree(D3DXVECTOR3(90.0f, 0.0f, 350.0f));
	SetTree(D3DXVECTOR3(140.0f, 0.0f, 150.0f));
	SetTree(D3DXVECTOR3(160.0f, 0.0f, 450.0f));
	SetTree(D3DXVECTOR3(220.0f, 0.0f, 20.0f));
	SetTree(D3DXVECTOR3(240.0f, 0.0f, 280.0f));
	SetTree(D3DXVECTOR3(270.0f, 0.0f, -180.0f));
	SetTree(D3DXVECTOR3(410.0f, 0.0f, -50.0f));
	SetTree(D3DXVECTOR3(390.0f, 0.0f, 350.0f));
	SetTree(D3DXVECTOR3(380.0f, 0.0f, 100.0f));
#endif
}
//=============================================================================
// 木の生成
//=============================================================================
void CRanking::SetTree(D3DXVECTOR3 pos)
{
	//木の幹
	m_pObject = CObject::Create(pos, 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(pos, 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
}