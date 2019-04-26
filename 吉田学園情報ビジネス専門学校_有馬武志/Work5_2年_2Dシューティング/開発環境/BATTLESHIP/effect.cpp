//=============================================================================
//
// エフェクトの処理 [effect.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\effect001.jpg"			//読み込むテクスチャファイル
#define TEXTURE_NAME_2	"data\\TEXTURE\\effect002.jpg"			//読み込むテクスチャファイル
#define BULLET_X		(30)									//横の大きさ
#define	BULLET_Y		(30)									//縦の大きさ
#define DAMAGE			(1)										//ダメージ量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[MAX_DATA] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CEffect::CEffect() : CScene2D(2)//優先優位イニシャライズ
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_fRadius = 0.0f;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	//m_posを代入
	D3DXVECTOR3 Effectpos = CScene2D::GetPosition();

	//エフェクトの位置とサイズ
	CScene2D::Set(Effectpos, D3DXVECTOR2(m_Size.x, m_Size.y));

	switch (m_Type)
	{
	case EFFECTTYPE_NOLMAL:
		//半径を大きくしていく
		m_fRadius--;

		//半径の更新
		CScene2D::SetRadius(Effectpos, m_fRadius);
		break;
	case EFFECTTYPE_RIPPLE:
		//半径を大きくしていく
		m_fRadius--;

		//半径の更新
		CScene2D::SetRadius(Effectpos, m_fRadius);
		break;
	}

	//ライフを減らしていく
	m_nLife--;

	if (m_nLife <= 0)
	{//ライフが0以下の場合
		//エフェクトの終了処理
		CEffect::Uninit(); return;
	}
	else if (Effectpos.y < m_Size.y || Effectpos.y > SCREEN_HEIGHT - m_Size.y || Effectpos.x < m_Size.x || Effectpos.x > SCREEN_WIDTH - m_Size.x)
	{//画面外の場合
	 //エフェクトの終了処理
		CEffect::Uninit(); return;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();
	
	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===============================================================================
//　クリエイト
//===============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,float fRadiusint,int nLife,EFFECTTYPE nType,int nTexType)
{
	CEffect *pEffect = NULL;

	//NULLチェック
	if (pEffect == NULL)
	{//メモリの動的確保

		pEffect = new CEffect;

		if (pEffect != NULL)
		{
			//オブジェクトクラスの生成
			pEffect->Init();
			//テクスチャを割り当てる
			pEffect->BindTexture(m_pTexture[nTexType]);
			//ライフを代入
			pEffect->m_nLife = nLife;
			//サイズの保持
			pEffect->m_Size = size;
			//半径の割り当て
			pEffect->m_fRadius = fRadiusint;
			//種類の代入
			pEffect->m_Type = nType;
			//エフェクトのを設置
			pEffect->SetPosition(pos);
		}
	}
	return pEffect;
}

//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CEffect::Load(void)
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

	return S_OK;
}

//===============================================================================
// テクスチャの破棄
//===============================================================================
void CEffect::UnLoad(void)
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