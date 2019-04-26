//=============================================================================
//
// チュートリアルの処理 [tutorial.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "tutorial.h"
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
#include "logo.h"
#include "2Dobject.h"
#include "pause.h"
#include "string.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_HP		(100)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CTutorial::m_pPlayer = NULL;
CBullet *CTutorial::m_pBullet = NULL;
CExplosion *CTutorial::m_pExplosion = NULL;
CEnemy *CTutorial::m_pEnemy = NULL;
CGan *CTutorial::m_pGan = NULL;
CBg *CTutorial::m_pBg = NULL;
CFram *CTutorial::m_pFram = NULL;
CNumber *CTutorial::m_pNumber = NULL;
C2DObject *CTutorial::m_p2DObject = NULL;
//CString *CTutorial::m_pString = NULL;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	CTutorial::GetPlayer() = NULL;
	m_EnemyCnt = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init()
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

	//チュートリアルの画像
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 40.0f, 0.0f), D3DXVECTOR2(170.0f, 35.0f), 13);
	CLogo::Create(D3DXVECTOR3(150.0f, 200.0f, 0.0f), D3DXVECTOR2(140.0f, 140.0f), 14);
	CLogo::Create(D3DXVECTOR3(150.0f, 490.0f, 0.0f), D3DXVECTOR2(140.0f, 140.0f), 15);
	CLogo::Create(D3DXVECTOR3(1400.0f, 130.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 16);
	CLogo::Create(D3DXVECTOR3(1130.0f, 295.0f, 0.0f), D3DXVECTOR2(140.0f, 100.0f), 30);

	//プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR2(25, 85), PLAYER_HP);

	//クロスヘア
	CLogo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 31);

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

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
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

	//ロゴのテクスチャの破棄
	CLogo::UnLoad();

	//体力のテクスチャの破棄
	CLife::UnLoad();

	//ポリゴンのテクスチャの破棄
	CPolygon::UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//エフェクトのテクスチャの破棄
	CEffect::UnLoad();

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
void CTutorial::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//m_pString->Update();

	//CEnemy::Create(位置・動き・サイズ・敵の種類・体力・攻撃する1 攻撃しない0以外・追尾する1 追尾しない0);
	//敵の生成  ENEMYTYPE_SHIP 戦艦0  : ENEMYTYPE_DIGHTER 戦闘機1  : ENEMYTYPE_SUBMARINE 潜水艦2  : ENEMTTYPE_CARRIER  空母3
	if (m_EnemyCnt == 0)
	{
		CEnemy::Create(D3DXVECTOR3(380.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1,0);
		CEnemy::Create(D3DXVECTOR3(440.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1, 0);
		CEnemy::Create(D3DXVECTOR3(500.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1, 0);
	}
	else if (m_EnemyCnt == 60)
	{
		CEnemy::Create(D3DXVECTOR3(620.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(10, 35), CEnemy::ENEMYTYPE_SUBMARINE, 50, 1, 0);
	}
	else if (m_EnemyCnt == 120)
	{
		CEnemy::Create(D3DXVECTOR3(750.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(25, 85), CEnemy::ENEMYTYPE_SHIP, 30, 1, 0);
	}
	else if (m_EnemyCnt == 180)
	{
		CEnemy::Create(D3DXVECTOR3(860.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(25, 85), CEnemy::ENEMYTYPE_SHIP, 30, 1, 0);
	}
	m_EnemyCnt++;

	//チュートリアルスキップの処理
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_N) == true)
	{//Hキーが押されたら
		CFade::Create(CManager::MODE_GAME);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{
	//m_pString->Draw();
}