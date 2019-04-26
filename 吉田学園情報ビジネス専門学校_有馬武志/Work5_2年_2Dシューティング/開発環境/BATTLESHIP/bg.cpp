//=============================================================================
//
// 背景の処理 [bg.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\海.jpg"			//読み込むテクスチャファイル
#define TEXTURE_NAME_2		"data\\TEXTURE\\海１.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_3		"data\\TEXTURE\\影雲.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_4		"data\\TEXTURE\\海.jpg"			//読み込むテクスチャファイル
#define TEXTURE_NAME_5		"data\\TEXTURE\\Clear000.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_6		"data\\TEXTURE\\Over000.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_7		"data\\TEXTURE\\mountain000.png"//読み込むテクスチャファイル
#define TEXTURE_NAME_8		"data\\TEXTURE\\sky.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_9		"data\\TEXTURE\\海波.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_10		"data\\TEXTURE\\砂浜.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_11		"data\\TEXTURE\\海.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_12		"data\\TEXTURE\\konku.jpg"		//読み込むテクスチャファイル
#define BG_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define BG_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CBg::CBg() : CScene2D(1)//優先優位イニシャライズ
{
	m_nCnt = 0;
	m_nType = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CBg::~CBg()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(void)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BG);

	D3DXVECTOR3 VtxPos[4];
	D3DXCOLOR Color[4];

	//デフォルトテクスチャ設定
	VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	if (m_nType == 3)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 6)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 330.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 330.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f);
	}
	else if (m_nType == 7)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f);
	}
	else if (m_nType == 8)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 475.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 475.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 9)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 455.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 455.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, 600.0f, 0.0f);
	}
	else if (m_nType == 10)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 11)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 12)
	{//テクスチャ設定
		VtxPos[0] = D3DXVECTOR3(0.0f, 570.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 570.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}

	//色の設定
	if (m_nType == 1)
	{//テクスチャ設定
		Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else if (m_nType == 2)
	{//テクスチャ設定
		Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
	}
	else if (m_nType == 8)
	{//テクスチャ設定
		Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	}
	else
	{//それ以外の場合すべての初期化
		for (int nCount = 0; nCount < 4; nCount++)
		{
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	CScene2D::SetVtxPos(&VtxPos[0]);
	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	D3DXVECTOR2 UV[4];
	D3DXVECTOR3 VtxPos[4];
	D3DXVECTOR3 move;

	m_nCnt++;

	if (m_nType == 0)
	{//テクスチャ設定 縦スクロール用
		UV[0] = D3DXVECTOR2(0.0f, 0.0f + (m_nCnt * 0.0007f));
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f + (m_nCnt * 0.0007f));
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V + (m_nCnt * 0.0007f));
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V + (m_nCnt * 0.0007f));
	}
	else if (m_nType == 1)
	{//テクスチャ設定 縦スクロール用
		UV[0] = D3DXVECTOR2(0.0f, 0.0f - (m_nCnt * 0.0004f));
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f - (m_nCnt * 0.0004f));
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V - (m_nCnt * 0.0004f));
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V - (m_nCnt * 0.0004f));
	}
	else if (m_nType == 2)
	{//テクスチャ設定 縦スクロール用
		UV[0] = D3DXVECTOR2(0.0f, 0.0f - (m_nCnt * 0.0002f));
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f - (m_nCnt * 0.0002f));
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V - (m_nCnt * 0.0002f));
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V - (m_nCnt * 0.0002f));
	}
	else if (m_nType == 3)
	{//テクスチャ設定 横スクロール用
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), 0.0f );
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), 0.0f );
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V );
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V );
	}
	else if (m_nType == 6)
	{//テクスチャ設定 横スクロール用
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 7)
	{//テクスチャ設定 横スクロール用
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00002f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00002f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00002f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00002f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 8)
	{//テクスチャ設定 横スクロール用
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 9)
	{//テクスチャ設定 横スクロール用
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 10)
	{
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0007f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0007f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0007f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0007f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 11)
	{
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0004f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0004f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0004f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0004f), BG_TEXTURE_UV_V);
	}
	else 
	{//テクスチャ設定
		UV[0] = D3DXVECTOR2(0.0f, 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f);
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V);
	}

	//プレイヤーの位置とサイズ
	CScene2D::SetMove(move);
	//背景のUV
	CScene2D::SetBg(&UV[0]);
}
//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CBg * CBg::Create(int nType)
{
	CBg *pBg = NULL;

	//NULLチェック
	if (pBg == NULL)
	{//メモリの動的確保

		pBg = new CBg;

		if (pBg != NULL)
		{
			//種類を割り当てる
			pBg->m_nType = nType;
			//オブジェクトクラスの生成
			pBg->Init();
			//テクスチャを割り当てる
			pBg->BindTexture(m_pTexture[nType]);
		}
	}

	return pBg;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[1]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_3,
		&m_pTexture[2]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[3]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_5,
		&m_pTexture[4]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_6,
		&m_pTexture[5]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_7,
		&m_pTexture[6]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_8,
		&m_pTexture[7]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_9,
		&m_pTexture[8]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_10,
		&m_pTexture[9]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_11,
		&m_pTexture[10]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[11]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_12,
		&m_pTexture[12]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CBg::UnLoad(void)
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