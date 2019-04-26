//=============================================================================
//
// 枠の処理 [fram.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "fram.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\fram000.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_2		"data\\TEXTURE\\fram001.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_3		"data\\TEXTURE\\fram002.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_4		"data\\TEXTURE\\BbFram.jpg"		//読み込むテクスチャファイル
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
LPDIRECT3DTEXTURE9 CFram::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CFram::CFram() : CScene2D(4)//優先優位イニシャライズ
{
	m_nCnt = 0;
	m_nType = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CFram::~CFram()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFram::Init(void)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_FRAM);

	D3DXVECTOR3 VtxPos[4];
	D3DXCOLOR Color[4];

	if (m_nType == 0)
	{//表示武器の囲い
		VtxPos[0] = D3DXVECTOR3(990.0f, 400.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH - 10.0f, 400.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(990.0f, SCREEN_HEIGHT - 10.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH - 10.0f, SCREEN_HEIGHT - 10.0f, 0.0f);
	}
	else if (m_nType == 1)
	{//キルアイコン
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	}
	else if (m_nType == 2)
	{//HPのバーのフレーム
		VtxPos[0] = D3DXVECTOR3(10.0f, 640.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(280.0f, 640.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(10.0f, 700.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(280.0f, 700.0f, 0.0f);
	}
	//両サイドのフレーム
	else if (m_nType == 3)
	{//右のフレーム
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(300.0f, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 4)
	{//左のフレーム
		VtxPos[0] = D3DXVECTOR3(980.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(980.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}

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
void CFram::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFram::Update(void)
{
	D3DXVECTOR2 UV[4];

	UV[0] = D3DXVECTOR2(0.0f, 0.0f);
	UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f);
	UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V);
	UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V);

	//背景のUV
	CScene2D::SetBg(&UV[0]);
}
//=============================================================================
// 描画処理
//=============================================================================
void CFram::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CFram * CFram::Create(int nType)
{
	CFram *pFram = NULL;

	//NULLチェック
	if (pFram == NULL)
	{//メモリの動的確保

		pFram = new CFram;

		if (pFram != NULL)
		{
			//種類を割り当てる
			pFram->m_nType = nType;
			//オブジェクトクラスの生成
			pFram->Init();
			//テクスチャを割り当てる
			pFram->BindTexture(m_pTexture[nType]);
		}
	}

	return pFram;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CFram::Load(void)
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
		TEXTURE_NAME_4,
		&m_pTexture[3]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_4,
		&m_pTexture[4]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CFram::UnLoad(void)
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