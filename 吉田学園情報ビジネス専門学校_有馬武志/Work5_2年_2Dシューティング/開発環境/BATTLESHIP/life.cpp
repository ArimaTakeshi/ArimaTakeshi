//=============================================================================
//
// 体力の処理 [life.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\Life001.png"	//読み込むテクスチャファイル
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
LPDIRECT3DTEXTURE9 CLife::m_pTexture[NUM_TEXTURE_LIFE] = {};
LPDIRECT3DVERTEXBUFFER9 CLife::m_pVtxBuff = NULL;
int CLife::m_nCntSubtraction = 0;
CLife::Life CLife::m_Life[NUM_POLYGON_LIFE] = {};
int CLife::m_nMaxLife = 0;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CLife::CLife() : CScene(4)//優先優位イニシャライズ
{
	for (int nCount = 0; nCount < NUM_POLYGON_LIFE; nCount++)
	{
		m_Life[nCount] = {};					//ライフの構造体
	}
	m_nCntSubtraction = 0;						//バーを減らし始めるカウンタ
}
//===============================================================================
//　デストラクタ
//===============================================================================
CLife::~CLife()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLife::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 枠
	m_Life[0].pos = D3DXVECTOR3(15.0f, 645.0f, 0.0f);
	m_Life[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_Life[0].nLife = MAX_LIFE;							// ライフを最大にする
	m_Life[0].fLength = BAR_WIDTH_LIFE;					// バーの長さを設定
	m_Life[0].nType = -1;								// テクスチャのON(0)OFF(-1)

	// バー
	for (int nCntLife = 1; nCntLife < NUM_POLYGON_LIFE; nCntLife++)
	{
		m_Life[nCntLife].pos = D3DXVECTOR3(15.0f, 645.0f, 0.0f);
		m_Life[nCntLife].nLife = MAX_LIFE;				// ライフを最大にする
		m_Life[nCntLife].fLength = BAR_WIDTH_LIFE;		// バーの長さを設定
		m_Life[nCntLife].nType = 0;						// テクスチャのON(0)OFF(-1)
	}

	m_Life[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_Life[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_Life[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	// バーを減らし始めるカウンタ
	m_nCntSubtraction = 0;

	// 頂点情報の作成
	CLife::MakeVertexLife(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLife::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLife::Update(void)
{
	/*	g_Life[3].fLength == 現在のライフ					（最前面に来るバー）			*/
	/*	g_Life[2].fLength == ダメージを受けて減った分のバー	（最前面から一つ後ろに来るバー）*/
	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		if (m_Life[2].fLength > m_Life[3].fLength)
		{// ライフと同じ値になるまで後ろのゲージを減らす
			m_nCntSubtraction++;								// ダメージバーを減らし始めるためのカウント

			if (m_nCntSubtraction >= SUBTRACT_TIME)
			{// 一定時間経過
				m_Life[2].fLength -= BAR_WIDTH_LIFE * 0.01f;	// ダメージバーの長さを1％ずつ減らす

				VERTEX_2D *pVtx;

				// 頂点バッファをロックし、頂点情報へのポインタを取得
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//頂点座標の設定
				pVtx[(2 * 4) + 1].pos = D3DXVECTOR3(m_Life[2].pos.x + m_Life[2].fLength, m_Life[2].pos.y, 0.0f);
				pVtx[(2 * 4) + 3].pos = D3DXVECTOR3(m_Life[2].pos.x + m_Life[2].fLength, m_Life[2].pos.y + BAR_HEIGHT_LIFE, 0.0f);

				// 頂点バッファをアンロックする
				m_pVtxBuff->Unlock();
			}
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CLife::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLife = 0; nCntLife < NUM_POLYGON_LIFE; nCntLife++)
	{
		// テクスチャの設定
		if (m_Life[nCntLife].nType >= 0)
		{// テクスチャの指定
			pDevice->SetTexture(0, m_pTexture[m_Life[nCntLife].nType]);
		}
		else
		{// 0より低いとテクスチャを張らない
			pDevice->SetTexture(0, NULL);
		}

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CLife * CLife::Create()
{
	CLife *pLife = NULL;

	//NULLチェック
	if (pLife == NULL)
	{//メモリの動的確保

		pLife = new CLife;

		if (pLife != NULL)
		{
			//オブジェクトクラスの生成
			pLife->Init();
		}
	}

	return pLife;
}
//=============================================================================
// 体力の増減
//=============================================================================
void CLife::AddLife(int nValue)
{
	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();

	//m_nMaxLife = pPlayer->GetMaxLife();

	m_Life[3].nLife += nValue;		// ライフを増減させる
	float fLife;

	if (m_Life[3].nLife > 0)
	{// ライフが0より大きいとき
		fLife = (BAR_WIDTH_LIFE * 1.0f) / ((MAX_LIFE * 1.0f) / m_Life[3].nLife);	// バーの元の長さを100%としてライフを増減させる
	}
	else
	{// ライフが0以下のとき
		fLife = 0;
	}

	if (m_Life[3].nLife >= MAX_LIFE)
	{// 最大値を超えたら戻す
		m_Life[3].nLife = MAX_LIFE;
		fLife = BAR_WIDTH_LIFE;
	}

	m_Life[3].fLength = fLife;	// 現在のライフバーの長さ

	m_nCntSubtraction = 0;		// ダメージバーの長さを減らし始めるためのカウンタを初期化

	//頂点情報の設定
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//現在のライフ
	pVtx[(3 * 4) + 1].pos = D3DXVECTOR3(m_Life[3].pos.x + m_Life[3].fLength, m_Life[3].pos.y, 0.0f);
	pVtx[(3 * 4) + 3].pos = D3DXVECTOR3(m_Life[3].pos.x + m_Life[3].fLength, m_Life[3].pos.y + BAR_HEIGHT_LIFE, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CLife::UnLoad(void)
{
	for (int nCount = 0; nCount < NUM_TEXTURE_LIFE; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void CLife::MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLife;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_POLYGON_LIFE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_POLYGON_LIFE; nCntLife++)
	{
		//頂点座標の設定
		pVtx[(nCntLife * 4) + 0].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x, m_Life[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 1].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x + BAR_WIDTH_LIFE, m_Life[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 2].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x, m_Life[nCntLife].pos.y + BAR_HEIGHT_LIFE, 0.0f);
		pVtx[(nCntLife * 4) + 3].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x + BAR_WIDTH_LIFE, m_Life[nCntLife].pos.y + BAR_HEIGHT_LIFE, 0.0f);

		//1.0fで固定
		pVtx[(nCntLife * 4) + 0].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 1].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 2].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 3].rhw = 1.0f;

		//頂点カラー
		pVtx[(nCntLife * 4) + 0].col = m_Life[nCntLife].col;
		pVtx[(nCntLife * 4) + 1].col = m_Life[nCntLife].col;
		pVtx[(nCntLife * 4) + 2].col = m_Life[nCntLife].col;
		pVtx[(nCntLife * 4) + 3].col = m_Life[nCntLife].col;

		//テクスチャ座標
		pVtx[(nCntLife * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCntLife * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCntLife * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCntLife * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}