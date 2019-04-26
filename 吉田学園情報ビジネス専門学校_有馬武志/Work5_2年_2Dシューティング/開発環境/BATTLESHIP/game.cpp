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
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "gan.h"
#include "number.h"
#include "score.h"
#include "effect.h"
#include "time.h"
#include "polygon.h"
#include "fade.h"
#include "life.h"
#include "fram.h"
#include "2Dobject.h"
#include "pause.h"
#include "string.h"
#include "pause.h"
#include "logo.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_HP		(200)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBullet *CGame::m_pBullet = NULL;
CExplosion *CGame::m_pExplosion = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CGan *CGame::m_pGan = NULL;
CBg *CGame::m_pBg = NULL;
CFram *CGame::m_pFram = NULL;
CNumber *CGame::m_pNumber = NULL;
C2DObject *CGame::m_p2DObject = NULL;
//CString *CGame::m_pString = NULL;
CGame::GAMESTATE CGame::m_gameState = GAMESTATE_NONE;
CPause *CGame::m_pPause = NULL;
bool CGame::m_bPause = false;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGame::CGame()
{
	m_gameState = GAMESTATE_NONE;
	m_nCounterGameState = 0;
	m_NowGameState = GAMESTATE_NONE;
	CGame::GetPlayer() = NULL;
	m_bPause = false;
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
	////NULLチェック
	//if (m_pString == NULL)
	//{
	//	//Stiringの動的確保
	//	m_pString = new CString;

	//	if (m_pString != NULL)
	//	{
	//		m_pString->Init();
	//	}
	//}

	//プレイヤーのテクスチャの読み込み
	m_pPlayer->Load();

	m_pEnemy->Load();

	//弾のテクスチャの読み込み
	m_pBullet->Load();

	//爆発のテクスチャの読み込み
	m_pExplosion->Load();

	//背景のテクスチャの読み込み
	m_pBg->Load();

	//銃のテクスチャの読み込み
	m_pGan->Load();

	//枠のテクスチャの読み込み
	m_pFram->Load();

	//数字のテクスチャの読み込み
	m_pNumber->Load();

	//オブジェクトのテクスチャの読み込み
	m_p2DObject->Load();

	//ポーズのテクスチャの読み込み
	m_pPause->Load();

	//エフェクトのテクスチャ読み込み
	CEffect::Load();

	//ポリゴンのテクスチャ読み込み
	CPolygon::Load();

	//フェードのテクスチャの読み込み
	CFade::Load();

	//体力のテクスチャの読み込み
	CLife::Load();

	//ロゴのテクスチャの読み込み
	CLogo::Load();

	//オブジェクトの生成
	//C2DObject::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0, 20);

	//枠生成
	CFram::Create(4);
	CFram::Create(3);
	CFram::Create(2);
	CFram::Create(1);
	CFram::Create(0);

	//背景生成
	CBg::Create(0);
	CBg::Create(1);
	CBg::Create(2);

	//体力の生成
	CLife::Create();

	//スコアの生成
	CScore::Create();

	//タイムの生成
	CTime::Create();

	//現在の銃の表示
	CGan::Create(D3DXVECTOR2(100.0f, 120.0f), CGan::GANTYPE_PLAYER, CGan::GAN_CANNON, 1);

	//船長の画像
	CLogo::Create(D3DXVECTOR3(1400.0f, 130.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 18);
	CLogo::Create(D3DXVECTOR3(1450.0f, 295.0f, 0.0f), D3DXVECTOR2(140.0f, 100.0f), 20);

	//クロスヘア
	CLogo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 31);

	//プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR2(25, 85), PLAYER_HP);
	//CDamage::Create();

	//敵の生成
	CEnemy::CreateEnemy();

	////SetString("入力する文字",rect { X, Y ,幅, 高さ},0,カラー);
	//m_pString->SetString("プレイヤー前移動", { 10,10,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("プレイヤー後移動", { 10,30,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("プレイヤー左移動", { 10,50,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("プレイヤー右移動", { 10,70,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("大砲", { 10,90,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("対空砲", { 10,110,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("魚雷", { 10,130,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	////SetString("入力する文字",rect { X, Y ,幅, 高さ},0,カラー);
	//m_pString->SetString(":  [ W ]", { 110,10,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ S ]", { 110,30,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ A ]", { 110,50,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ D ]", { 110,70,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ 1 ]", { 110,90,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ 2 ]", { 110,110,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ 3 ]", { 110,130,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_gameState = GAMESTATE_NORMAL;	//通常状態に

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

	//プレイヤーテクスチャの破棄
	m_pPlayer->UnLoad();

	//敵のテクスチャの破棄
	m_pEnemy->UnLoad();

	//弾のテクスチャの破棄
	m_pBullet->UnLoad();

	//爆発のテクスチャの破棄
	m_pExplosion->UnLoad();

	//背景のテクスチャの破棄
	m_pBg->UnLoad();

	//枠のテクスチャの破棄
	m_pFram->UnLoad();

	//オブジェクトのテクスチャの破棄
	m_p2DObject->UnLoad();

	//銃のテクスチャの破棄
	m_pGan->UnLoad();

	//数字のテクスチャの破棄
	m_pNumber->UnLoad();

	//ポーズのテクスチャの破棄
	m_pPause->UnLoad();

	//体力のテクスチャの破棄
	CLife::UnLoad();

	//ポリゴンのテクスチャの破棄
	CPolygon::UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//エフェクトのテクスチャの破棄
	CEffect::UnLoad();

	//ロゴのテクスチャの破棄
	CLogo::UnLoad();

	//描画優先の1番最初以外のすべてを削除
	for (int nCnPri = 0; nCnPri < NUM_PRIORITY - 1; nCnPri++)
	{
		//オブジェクトの総数を確認
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene *pScene = CScene::GetScene(nCnPri, nCntScene);

			if (pScene != NULL)
			{
				pScene->Uninit();
			}
		}
	}

	////文字の終了処理
	//if (m_pString != NULL)
	//{
	//	m_pString->Uninit();
	//	delete m_pString;
	//	m_pString = NULL;
	//}
}
//=============================================================================
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//m_pString->Update();

	//ポーズの処理
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_P) == true)
	{//Pキーが押されたら

		m_bPause = m_bPause ? false : true;

		switch (m_bPause)
		{
		case true:
			if (m_pPause == NULL)
			{
				//ポーズを開く音
				pSound->PlaySound(CSound::SOUND_LABEL_PAUSE000);

				//ポーズの生成
				m_pPause = CPause::Create();

				//ポーズとフェードだけ回す
				CScene::SetUpdatePri(7);
			}
			break;
		case false:
			if (m_pPause != NULL)
			{
				//ポーズを閉じる音
				pSound->PlaySound(CSound::SOUND_LABEL_PAUSE001);

				//ポーズを削除
				m_pPause->Uninit();
				m_pPause = NULL;

				//アップデート順番をすべて回す
				CScene::SetUpdatePri(0);
			}
		}
	}
	if (m_pPause == false)
	{//開く音
	 //現在の状態を保存
		m_NowGameState = GetGameState();

		switch (m_NowGameState)
		{
		case GAMESTATE_NORMAL:	//通常の状態
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
}
//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{
	//m_pString->Draw();
}
//=============================================================================
//
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
