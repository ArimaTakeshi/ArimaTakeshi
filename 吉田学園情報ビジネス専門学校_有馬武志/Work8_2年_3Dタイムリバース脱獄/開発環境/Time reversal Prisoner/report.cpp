//=============================================================================
//
// 報告の処理 [report.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "report.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\ゲームクリア\\W脱.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_2		"data\\TEXTURE\\ゲームクリア\\W獄.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_3		"data\\TEXTURE\\ゲームクリア\\W成.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_4		"data\\TEXTURE\\ゲームクリア\\W功.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_5		"data\\TEXTURE\\ゲームオーバー\\L脱.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_6		"data\\TEXTURE\\ゲームオーバー\\L獄.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_7		"data\\TEXTURE\\ゲームオーバー\\L失.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_8		"data\\TEXTURE\\ゲームオーバー\\L敗.png"	//読み込むテクスチャファイル
#define REPORT_MIN_POS		(200.0f)									//最低位置
#define REPORT_MAX_SIZE_X	(90.0f)										//X最大のサイズ
#define REPORT_MAX_SIZE_Y	(120.0f)									//Y最大のサイズ
#define REPORT_DOWNSPD		(5.0f)										//落下スピード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CReport::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CReport::CReport() : CScene2D(4)//優先優位イニシャライズ
{
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//　デストラクタ
//===============================================================================
CReport::~CReport()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CReport::Init(void)
{
	CScene2D::Init();

	D3DXCOLOR Color[4];

	for (int nCount = 0; nCount < 4; nCount++)
	{//それ以外の場合すべての初期化
		Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CReport::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CReport::Update(void)
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();

	//ゲームの状態の確認
	CGame::GAMESTATE GameState = CGame::GetGameState();

	//デバック用　終わったらこの文を消すこと！　Managerの始まりもTITLEに戻すこと！ 
	//クリア　GAMESTATE_CLEAR　オーバー  GAMESTATE_OVER
	//GameState = CGame::GAMESTATE_CLEAR;

	//移動量の割り当て
	D3DXVECTOR3 move;
	move = GetMove();

	//位置の割り当て
	D3DXVECTOR3 pos;
	pos = GetPosition();

	if (m_size.x > REPORT_MAX_SIZE_X)
	{// 目的の大きさより大きければ
		// 縮小させる
		m_size -= D3DXVECTOR2(5.0f, 5.0f);
	}

	//位置を更新(移動)
	pos.x += move.x;
	pos.y += move.y;

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//報告の位置とサイズ
	CScene2D::SetPosSize(pos, m_size);
	//報告の位置とサイズ
	CScene2D::SetMove(move);
}
//=============================================================================
// 描画処理
//=============================================================================
void CReport::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CReport * CReport::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CReport *pReport = NULL;

	//NULLチェック
	if (pReport == NULL)
	{//メモリの動的確保

		pReport = new CReport;

		if (pReport != NULL)
		{
			//種類を割り当てる
			pReport->m_nType = nType;
			//オブジェクトクラスの生成
			pReport->Init();
			//テクスチャを割り当てる
			pReport->BindTexture(m_pTexture[nType]);
			//位置を割り当てる
			pReport->SetPosition(pos);
			//サイズの割り当て
			pReport->m_size = size;
		}
	}

	return pReport;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CReport::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_2,&m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_3,&m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_4,&m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_8, &m_pTexture[7]);
	
	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CReport::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}