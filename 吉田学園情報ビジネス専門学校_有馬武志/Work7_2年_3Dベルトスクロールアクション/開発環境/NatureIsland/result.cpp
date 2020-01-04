//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 有馬　武志 & 荒谷 由朗
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "serect.h"
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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer		*CResult::m_pPlayer		= NULL;
CSerect		*CResult::m_pSerect		= NULL;
CBillBoord	*CResult::m_pBillBoord	= NULL;
CPolygon3D	*CResult::m_pPolygon3D	= NULL;
CMeshField	*CResult::m_pMeshField	= NULL;
CObject		*CResult::m_pObject		= NULL;
CModel		*CResult::m_pModel		= NULL;
CEffect		*CResult::m_pEffect		= NULL;
CWall		*CResult::m_pWall		= NULL;
CGround		*CResult::m_pGround		= NULL;
CItem		*CResult::m_pItem		= NULL;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResult::CResult()
{
	m_nCnt = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init()
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//===================================
	//		 Loadの読み込み場所
	//===================================
	//フェードのテクスチャの読み込み
	CFade::Load();

	//セレクトのテクスチャの読み込み
	m_pSerect->Load();

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

	//===================================
	//		 生成
	//===================================
	//セレクトの生成
	m_pSerect = CSerect::Create();

	CreateStage();
	CreateObject();

	//現在のゲーム状況
	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//ゲームクリアした場合

	}
	else if (GameStateNow == CGame::GAMESTATE_OVER)
	{//ゲームオーバーした場合

	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//===================================
	//	　　UnLoadの破棄する場所
	//===================================
	//メッシュフィールドテクスチャの破棄
	m_pMeshField->UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//セレクトのテクスチャの破棄
	m_pSerect->UnLoad();

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
	m_pMeshField->Uninit();
	m_pMeshField = NULL;

	//セレクトの削除
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

	//フェード以外を削除
	CScene::NotFadeReleseAll();
}
//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//現在どんな状況か
	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	if (GameStateNow == CGame::GAMESTATE_OVER)
	{//ゲームオーバーした場合

	}
	else if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//ゲームクリアした場合

	}

	if (m_nCnt == 600)
	{//５秒後に何もしてない場合戻る
		//CFade::Create(CManager::MODE_RANKING);
	}

	m_nCnt++;
}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

}
//=============================================================================
// ステージの生成を一括管理
//=============================================================================
void CResult::CreateStage(void)
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
void CResult::CreateObject(void)
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
void CResult::SetTree(D3DXVECTOR3 pos)
{
	//木の幹
	m_pObject = CObject::Create(pos, 0.0f, 3, 4, CObject::MOVETYPE_NOT, 0);
	m_pObject = CObject::Create(pos, 0.0f, 2, 3, CObject::MOVETYPE_NOT, 0);
}