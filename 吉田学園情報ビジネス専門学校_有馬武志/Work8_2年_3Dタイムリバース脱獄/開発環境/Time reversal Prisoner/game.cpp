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
#include "bullet.h"
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
#include "ground.h"
#include "item.h"
#include "shadow.h"
#include "enemy.h"
#include "life.h"
#include "gauge.h"
#include "distance.h"
#include "guide.h"
#include "action2D.h"
#include "blood.h"
#include "serect.h"
#include "spotlight.h"
#include "objectshadow.h"
#include "help.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//ステージ１
#define TEXT_OBJECTNAME1		"data\\TEXT\\ステージ1\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME1		"data\\TEXT\\ステージ1\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME1			"data\\TEXT\\ステージ1\\wall.txt"			// 読み込むテキストファイル

//ステージ２
#define TEXT_OBJECTNAME2		"data\\TEXT\\ステージ2\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME2		"data\\TEXT\\ステージ2\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME2			"data\\TEXT\\ステージ2\\wall.txt"			// 読み込むテキストファイル

//ステージ３
#define TEXT_OBJECTNAME3		"data\\TEXT\\ステージ3\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME3		"data\\TEXT\\ステージ3\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME3			"data\\TEXT\\ステージ3\\wall.txt"			// 読み込むテキストファイル

//ステージ４
#define TEXT_OBJECTNAME4		"data\\TEXT\\ステージ4\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME4		"data\\TEXT\\ステージ4\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME4			"data\\TEXT\\ステージ4\\wall.txt"			// 読み込むテキストファイル

//ステージ５
#define TEXT_OBJECTNAME5		"data\\TEXT\\ステージ5\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME5		"data\\TEXT\\ステージ5\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME5			"data\\TEXT\\ステージ5\\wall.txt"			// 読み込むテキストファイル

//ステージ６
#define TEXT_OBJECTNAME6		"data\\TEXT\\ステージ6\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME6		"data\\TEXT\\ステージ6\\meshfield.txt"		// 読み込むテキストファイル
#define TEXT_WALLNAME6			"data\\TEXT\\ステージ6\\wall.txt"			// 読み込むテキストファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBullet *CGame::m_pBullet = NULL;
CNumber *CGame::m_pNumber = NULL;
CBillBoord *CGame::m_pBillBoord = NULL;
CPolygon3D *CGame::m_pPolygon3D = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CObject *CGame::m_pObject = NULL;
CPause *CGame::m_pPause = NULL;
CHelp *CGame::m_pHelp = NULL;
CModel *CGame::m_pModel = NULL;
CEffect *CGame::m_pEffect = NULL;
CWall *CGame::m_pWall = NULL;
CGround *CGame::m_pGround = NULL; 
CShadow *CGame::m_pShadow = NULL;
CSpotLight *CGame::m_pSpotLight = NULL;
CItem *CGame::m_pItem = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CDummyEnemy *CGame::m_pDummyEnemy = NULL;
CDummyPlayer *CGame::m_pDummyPlayer = NULL;
CObjectShadow *CGame::m_pObjectShadow = NULL;

bool CGame::m_bHelp = false;
bool CGame::m_bPause = false;
CGame::GAMESTATE CGame::m_gameState = GAMESTATE_NONE;
int	CGame::m_nCntSetStage = 0;								// ステージセットカウンタ
CGame::STAGENUM CGame::m_StageState = STAGENUM_1;			// ステージ状態

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
CGame::~CGame()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init()
{
	//===================================
	//		 Loadの読み込み場所
	//===================================
	//2D画像テクスチャの読み込み
	CLogo::Load();

	//フェードのテクスチャの読み込み
	CFade::Load();

	//ライフのテクスチャの読み込み
	CLife::Load();

	//ゲージのテクスチャの読み込み
	CGauge::Load();

	//案内のテクスチャの読み込み
	CGuide::Load();

	//アクションスキル使用時のテクスチャの読み込み
	CAction2D::Load();

	//セレクトのテクスチャの読み込み
	m_pPause->Load();

	//ヘルプのテクスチャの読み込み
	m_pHelp->Load();

	//メッシュフィールドのテクスチャの読み込み
	m_pMeshField->Load();

	//ビルボードテクスチャの読み込み
	m_pBillBoord->Load();

	//弾のテクスチャの読み込み
	m_pBullet->Load();

	//オブジェクトのテクスチャの読み込み
	m_pObject->Load();

	//プレイヤーのテクスチャの読み込み
	//m_pPlayer->Load();

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

	//スポットライトンの読み込み
	m_pSpotLight->Load();

	//ステンシルシャドウの読み込み
	m_pObjectShadow->Load();

	//距離の生成　ヒープ壊れてる
	//CDistance::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//ゲージ用枠
	CLogo::Create(D3DXVECTOR3(310.0f, 30.0f, 0.0f), D3DXVECTOR2(183.0f, 17.0f), 4, 1);
	CLogo::Create(D3DXVECTOR3(265.0f, 60.0f, 0.0f), D3DXVECTOR2(197.0f * 0.8f, 17.0f* 0.8f), 4, 1);

	//ゲージの生成
	CGauge::Create(D3DXVECTOR3(122.0f, 50.0f, 0.0f));

	//ライフの生成
	CLife::Create(D3DXVECTOR3(140.0f, 15.0f, 0.0f));

	//ロゴを表示
	CLogo::Create(D3DXVECTOR3(1180.0f, 100.0f, 0.0f), D3DXVECTOR2(90.0f, 90.0f), 4, 0);
	CLogo::Create(D3DXVECTOR3(1180.0f, 100.0f, 0.0f), D3DXVECTOR2(80.0f, 80.0f), 0, 0);
	CLogo::Create(D3DXVECTOR3(1180.0f, 163.0f, 0.0f), D3DXVECTOR2(80.0f, 20.0f), 5, 0);
	CLogo::Create(D3DXVECTOR3(160.0f, 620.0f, 0.0f), D3DXVECTOR2(160.0f, 90.0f), 9, 0);

	//マップ
	CGuide::Create(D3DXVECTOR3(1180.0f, 500.0f, 0.0f), D3DXVECTOR2(90.0f, 200.0f), 7);
	CGuide::Create(D3DXVECTOR3(1180.0f, 270.0f, 0.0f), D3DXVECTOR2(80.0f, 30.0f), 8);
	CGuide::Create(D3DXVECTOR3(1130.0f, 665.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 9);
	CGuide::Create(D3DXVECTOR3(77.0f, 68.0f, 0.0f), D3DXVECTOR2(80.0f, 68.0f), 10);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f));

	//オブジェクト影の生成		
	m_pObjectShadow = CObjectShadow::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, CModel3D::MOVETYPE_NOT, 0);

	//ビルボード生成
	//m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30,30),0);

	//アイテムの生成
	//m_pItem = CItem::Create(D3DXVECTOR3(0, 50.0f, 600.0f), 0);

	//通常状態に
	m_gameState = GAMESTATE_NORMAL;	

	//どこのステージから開始するか
	m_nCntSetStage = 0;			

	//敵の数初期化
	m_nEnemyCount = 0;

	//開始ステージ
	m_StageState = STAGENUM_1;			// ステージ状態

	//ポーズを初期化
	m_bPause = false;

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

	if (m_pHelp != NULL)
	{
		m_pHelp->Uninit();
		m_pHelp = NULL;
	}

	//===================================
	//	　　UnLoadの破棄する場所
	//===================================
	//セレクトのテクスチャの破棄
	m_pPause->UnLoad();

	m_pHelp->UnLoad();

	//メッシュフィールドテクスチャの破棄
	m_pMeshField->UnLoad();

	//2D画像テクスチャの破棄
	CLogo::UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//ライフのテクスチャの破棄
	CLife::UnLoad();

	//ゲージのテクスチャの破棄
	CGauge::UnLoad();

	//案内のテクスチャの破棄
	CGuide::UnLoad();

	//アクションスキル使用時のテクスチャの破棄
	CAction2D::UnLoad();

	//ビルボードテクスチャの破棄
	m_pBillBoord->UnLoad();

	//弾のテクスチャの破棄
	m_pBullet->UnLoad();

	//オブジェクトのテクスチャの破棄
	m_pObject->UnLoad();

	//プレイヤーのテクスチャの破棄
	//m_pPlayer->UnLoad();

	//エフェクトのテクスチャの破棄
	m_pEffect->UnLoad();

	//地面のテクスチャの破棄
	m_pGround->UnLoad();

	//壁のテクスチャの破棄
	m_pWall->UnLoad();

	//アイテムのテクスチャ破棄
	m_pItem->UnLoad();

	//影のテクスチャの破棄
	m_pShadow->UnLoad();

	//スポットライトンの破棄
	m_pSpotLight->UnLoad();

	//ステンシルシャドウの破棄
	m_pObjectShadow->UnLoad();

	//メッシュフィールドの破棄
	m_pMeshField->Uninit();
	m_pMeshField = NULL;

	//フェード以外の破棄
	CScene::NotFadeReleseAll();
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	if (m_StageState == 1)
	{
		CDebugProc::Print("現在のステージ = 1\n");
	}
	else if (m_StageState == 2)
	{
		CDebugProc::Print("現在のステージ = 2\n");
	}
	else if (m_StageState == 3)
	{
		CDebugProc::Print("現在のステージ = 3\n");
	}
	else if (m_StageState == 4)
	{
		CDebugProc::Print("現在のステージ = 4\n");
	}
	else if (m_StageState == 5)
	{
		CDebugProc::Print("現在のステージ = 5\n");
	}
	else if (m_StageState == 6)
	{
		CDebugProc::Print("現在のステージ = 6\n");
	}


	if (m_pPause == false || m_pPause == false)
	{//開く音
		//現在の状態を保存
		m_NowGameState = GetGameState();

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

	//ポーズの処理
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_P) == true && m_pPlayer->GetDie() == false || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_START) == true && m_pPlayer->GetDie() == false && CPause::GetPauseEnd() == false && CSerect::GetSelectEnd() == false)
	{//Pキーが押されたら

		m_bPause = m_bPause ? false : true;

		switch (m_bPause)
		{
		case true:
			if (m_pPause == NULL)
			{
				if (CPlayer::GetCancelStageNext() == false)
				{
					//ポーズを開く音
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_OPEN);

					//ポーズの生成
					m_pPause = CPause::Create();

					//ポーズとフェードだけ回す
					CScene::SetUpdatePri(7);
				}
			}
			break;
		case false:
			if (m_pPause != NULL)
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
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
	
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
// ヘルプの表示
//=============================================================================
void CGame::SetHelp(bool bHelp)
{
	m_bHelp = bHelp;

	switch (m_bHelp)
	{
	case true:
		if (m_pHelp == NULL)
		{
			//ポーズの生成
			m_pHelp = CHelp::Create();

			CScene::SetUpdatePri(7);
		}
		break;
	case false:
		if (m_pHelp != NULL)
		{
			m_pHelp->Uninit();
			m_pHelp = NULL;

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
	CCamera *pCamera = CManager::GetCamera();

	//削除する処理
	if (m_StageState != stage)
	{
		//m_pPlayer->ResetPlayer();
		pCamera->DeleteCamera();
		m_pWall->DeleteWall();
		m_pObject->DeleteObject();
		m_pEnemy->DeleteEnemy();
		m_pBillBoord->ResetBillboord();
		m_pMeshField->DeleteMeshField();
		m_pGround->DeleteGround();
	}

	//状態を記憶
	m_StageState = stage;

	//削除する処理
	if (m_StageState == stage)
	{
		m_pPlayer->ResetPlayer();
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
		//	ステージ1 第3収容所
		//=====================================================================
		if (m_StageState == STAGENUM_1)
		{
			//ヘルプの表示
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//案内の表示
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 1);

			//道案内
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3,1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//案内用
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//チュートリアル
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 10, 0);

			//マップを読み込む
			TextLoad(1);
			WallTextLoad(1);
			MeshTextLoad(1);

			//敵の生成
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-125.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), 0);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(120.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_G);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-120.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_B);
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(125.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f));

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//フィールドの生成		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//====================================================================
		//	ステージ2 全階層食堂
		//====================================================================
		else if (m_StageState == STAGENUM_2)
		{
			//ヘルプの表示
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//案内の表示
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 2);

			//道案内
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//案内用
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//チュートリアル
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 11, 0);

			//マップを読み込む
			TextLoad(2);
			MeshTextLoad(2);
			WallTextLoad(2);

			//敵の生成
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, 300.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_X_R);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(370.0f, 0.0f, 100.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_Z_B);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-370.0f, 0.0f, -100.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_Z_G);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//オブジェクトの生成		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
		}
		//=======================================================================
		//	ステージ3　囚人用廊下
		//=======================================================================
		else if (m_StageState == STAGENUM_3)
		{
			//ヘルプの表示
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//案内の表示
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 3);

			//案内用
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//チュートリアル
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 12, 0);

			//道案内
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, -130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(400.0f, 5.0f, 70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(400.0f, 5.0f, 610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(750.0f, 65.0f, 590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//マップを読み込む
			TextLoad(3);
			WallTextLoad(3);
			MeshTextLoad(3);

			//敵の生成
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 600.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_Z_B);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 730.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_X_L);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//フィールドの生成		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//=======================================================================
		//	ステージ4　囚人審査路
		//=======================================================================
		else if (m_StageState == STAGENUM_4)
		{
			//ヘルプの表示
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//案内の表示
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 4);

			//道案内
			m_pGround = CGround::Create(D3DXVECTOR3(100.0f, 5.0f, -200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(400.0f, 5.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(900.0f, 5.0f, -170.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(880.0f, 5.0f, 420.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(506.0f, 112.0f, 455.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//案内用
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//チュートリアル
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 13, 0);

			//マップを読み込む
			TextLoad(4);
			WallTextLoad(4);
			MeshTextLoad(4);

			//敵の生成
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(320.0f, 0.0f, 5.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(657.0f, 0.0f, -42.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1040.0f, 0.0f, 17.0f),  D3DXVECTOR3(0.0f,-1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(936.0f, 0.0f, 510.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);

			//危険場所
			m_pGround = CGround::Create(D3DXVECTOR3(350.0f, 2.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(145.0f, 50.0f), 0, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(640.0f, 2.0f, -165.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(145.0f, 50.0f), 0, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(645.0f, 2.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(140.0f, 65.0f), 0, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(925.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(165.0f, 70.0f), 0, 0);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//フィールドの生成		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//=======================================================================
		//	ステージ5　玄関
		//=======================================================================
		else if (m_StageState == STAGENUM_5)
		{
			//ヘルプの表示
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//案内の表示
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 5);

			//道案内
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-160.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-160.0f, 5.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-760.0f, 5.0f, 290.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);
		
			//案内用
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//マップを読み込む
			TextLoad(5);
			WallTextLoad(5);
			MeshTextLoad(5);

			//敵の生成
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-730.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f,1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-760.0f, 0.0f, 520.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(240.0f, 0.0f, 400.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-340.0f, 0.0f, 200.0f),  D3DXVECTOR3(0.0f,-1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-400.0f, 0.0f, -100.0f),  D3DXVECTOR3(0.0f,1.57f,0.0f), 1, CEnemy::MOVE_STOP);

			//危険場所
			m_pGround = CGround::Create(D3DXVECTOR3(-350.0f, 2.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 380.0f), 0, 0);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//フィールドの生成		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//=======================================================================
		//	ステージ6　運動所
		//=======================================================================
		else if (m_StageState == STAGENUM_6)
		{
			//ヘルプの表示
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//案内の表示
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 6);

			//道案内
			m_pGround = CGround::Create(D3DXVECTOR3(-265.0f, 5.0f, 1240.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-340.0f, 5.0f, 950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-470.0f, 5.0f, 950.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-480.0f, 5.0f, -1170.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//案内用
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//チュートリアル
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 14, 0);

			//マップを読み込む
			TextLoad(6);
			WallTextLoad(6);
			MeshTextLoad(6);

			//隠れるゾーン
			m_pGround = CGround::Create(D3DXVECTOR3(-550.0f, 2.0f, 75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-454.0f, 2.0f, 385.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(60.0f, 50.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-454.0f, 2.0f, 670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(60.0f, 50.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-477.5f, 2.0f, -275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(85.0f, 20.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-527.5f, 2.0f, -585.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(135.0f, 20.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-507.5f, 2.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(135.0f, 20.0f), 1, 0);

			//ライトゾーン
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, -1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);

			//敵の生成
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-900.0f, 0.0f, 1250.0f),  D3DXVECTOR3(0.0f,-1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-895.0f, 0.0f, 1080.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-680.0f, 0.0f, 530.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_G);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-800.0f, 0.0f, 190.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_B);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-700.0f, 0.0f, -440.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-630.0f, 0.0f, -1190.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-645.0f, 0.0f, 1080.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_X_R);
			
			//むずすぎるためコメントアウト
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-410.0f, 0.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_G);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//オブジェクトの生成		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//壁の生成		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//フィールドの生成		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
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

	//どのステージを読み込むか
	int nStageLoadNumber = nLoadNumber;

	//ファイルの読み込み先を変更
	switch (nStageLoadNumber)
	{
	case 1:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_OBJECTNAME1, "r");
		break;
	case 2:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_OBJECTNAME2, "r");
		break;
	case 3:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_OBJECTNAME3, "r");
		break;
	case 4:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_OBJECTNAME4, "r");
		break;
	case 5:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_OBJECTNAME5, "r");
		break;
	case 6:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_OBJECTNAME6, "r");
		break;
	}

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

	//どのステージを読み込むか
	int nStageLoadNumber = nLoadNumber;

	//ファイルの読み込み先を変更
	switch (nStageLoadNumber)
	{
	case 1:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_MESHFIELDNAME1, "r");
		break;
	case 2:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_MESHFIELDNAME2, "r");
		break;
	case 3:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_MESHFIELDNAME3, "r");
		break;
	case 4:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_MESHFIELDNAME4, "r");
		break;
	case 5:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_MESHFIELDNAME5, "r");
		break;
	case 6:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_MESHFIELDNAME6, "r");
		break;
	}

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

	//どのステージを読み込むか
	int nStageLoadNumber = nLoadNumber;

	//ファイルの読み込み先を変更
	switch (nStageLoadNumber)
	{
	case 1:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_WALLNAME1, "r");
		break;
	case 2:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_WALLNAME2, "r");
		break;
	case 3:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_WALLNAME3, "r");
		break;
	case 4:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_WALLNAME4, "r");
		break;
	case 5:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_WALLNAME5, "r");
		break;
	case 6:
		//ファイルを開く 読み込み
		pFile = fopen(TEXT_WALLNAME6, "r");
		break;
	}
	
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