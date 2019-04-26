//=============================================================================
//
// 爆発の処理 [explosion.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1					"data\\TEXTURE\\explosion000.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_2					"data\\TEXTURE\\explosion001.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_3					"data\\TEXTURE\\explosion002.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_4					"data\\TEXTURE\\explosion004.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_5					"data\\TEXTURE\\explosion005.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_6					"data\\TEXTURE\\explosion006.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_7					"data\\TEXTURE\\explosion007.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_8					"data\\TEXTURE\\explosion008.png"	//読み込むテクスチャファイル
#define EXPLOSION_TEXTURE_SPEED			(6)									//テクスチャアニメーションスピード
#define EXPLOSION_TEXTURE_PATTERN		(8)									//テクスチャアニメーションパターン数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CExplosion::CExplosion() : CScene2D(4)//優先優位イニシャライズ
{
	m_nCounterAnim = 0;
	m_nPatteunAnim = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
}
//===============================================================================
//　デストラクタ
//===============================================================================
CExplosion::~CExplosion()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init(void)
{	
	CScene2D::Init();

	D3DXVECTOR2 uv[4];

	uv[0] = D3DXVECTOR2(0.0f,0.0f);
	uv[1] = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_PATTERN, 0.0f);
	uv[2] = D3DXVECTOR2(0.0f, 1.0f);
	uv[3] = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_PATTERN, 1.0f);

	//オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_EXPLOSION);

	CScene2D::SetBg(&uv[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	//初期値設定
	D3DXVECTOR3 pos;
	pos = CExplosion::GetPosition();

	CScene2D::Set(pos, m_Size);

	m_nCounterAnim++;		//カウンター加算

	if ((m_nCounterAnim % EXPLOSION_TEXTURE_SPEED) == 0)
	{//アニメーション速度

		m_nPatteunAnim = (m_nPatteunAnim + 1) % EXPLOSION_TEXTURE_PATTERN;		//パターンNo.更新

		CScene2D::SetAnim(D3DXVECTOR2(0.125f, 1.0f), m_nPatteunAnim);

		if (m_nPatteunAnim == EXPLOSION_TEXTURE_PATTERN - 1)
		{//アニメーションが最後までいった場合
			CExplosion::Uninit();
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size, int nType)
{
	CExplosion *pExplosion = NULL;

	//NULLチェック
	if (pExplosion == NULL)
	{//メモリの動的確保

		pExplosion = new CExplosion;

		if (pExplosion != NULL)
		{
			//オブジェクトクラスの生成
			pExplosion->Init();
			//種類の割り当て
			pExplosion->m_nType = nType;
			//テクスチャを割り当てる
			pExplosion->BindTexture(m_pTexture[nType]);
			//弾を設置
			pExplosion->SetPosition(pos);
			//サイズの割り当て
			pExplosion->m_Size = size;

		}
	}
	return pExplosion;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CExplosion::Load(void)
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

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CExplosion::UnLoad(void)
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