//=============================================================================
//
// 数字の処理 [number.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "number.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "score.h"
#include <string>
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME1			"data\\TEXTURE\\number000.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME2			"data\\TEXTURE\\number001.png"	//読み込むテクスチャファイル
#define MAX_KILL_SIZE_X			(20)							//テクスチャ縦サイズ
#define MAX_KILL_SIZE_Y			(30)							//テクスチャ横サイズ
#define MAX_DAMAGE_SIZE_X		(8)								//テクスチャ縦サイズ
#define MAX_DAMAGE_SIZE_Y		(16)							//テクスチャ横サイズ
#define MAX_SCORE_SIZE_X		(20)							//テクスチャ縦サイズ
#define MAX_SCORE_SIZE_Y		(30)							//テクスチャ横サイズ
#define MAX_NONE_SIZE_X			(20)							//テクスチャ縦サイズ
#define MAX_NONE_SIZE_Y			(30)							//テクスチャ横サイズ
#define BG_TEXTURE_UV_U			(1.0f)							//テクスチャアニメーションU範囲
#define BG_TEXTURE_UV_V			(1.0f)							//テクスチャアニメーションV範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture[MAX_NUMBER_TEXTURE] = {};
int CNumber::m_nType = TYPE_NONE;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber()
{

}
//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME1, &m_pTexture[0]);

	//テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &m_pTexture[1]);
	
	return S_OK;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	m_pos = pos;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_nType)
	{
	case TYPE_SCORE:
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_SCORE_SIZE_X, m_pos.y - MAX_SCORE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_SCORE_SIZE_X, m_pos.y - MAX_SCORE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_SCORE_SIZE_X, m_pos.y + MAX_SCORE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_SCORE_SIZE_X, m_pos.y + MAX_SCORE_SIZE_Y, 0.0f);
		break;
	case TYPE_DAMAGE:
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_DAMAGE_SIZE_X, m_pos.y - MAX_DAMAGE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_DAMAGE_SIZE_X, m_pos.y - MAX_DAMAGE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_DAMAGE_SIZE_X, m_pos.y + MAX_DAMAGE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_DAMAGE_SIZE_X, m_pos.y + MAX_DAMAGE_SIZE_Y, 0.0f);
		break;
	case TYPE_KILL:
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_KILL_SIZE_X, m_pos.y - MAX_KILL_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_KILL_SIZE_X, m_pos.y - MAX_KILL_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_KILL_SIZE_X, m_pos.y + MAX_KILL_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_KILL_SIZE_X, m_pos.y + MAX_KILL_SIZE_Y, 0.0f);
		break;
	default:
		// 頂点情報を設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_NONE_SIZE_X, m_pos.y - MAX_NONE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_NONE_SIZE_X, m_pos.y - MAX_NONE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_NONE_SIZE_X, m_pos.y + MAX_NONE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_NONE_SIZE_X, m_pos.y + MAX_NONE_SIZE_Y, 0.0f);
		break;
	}

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//色の設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分自身の破棄
	//Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CNumber::Update(void)
{


}
//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_NUMBER_TEXTURE; nCount++)
	{
		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture[nCount]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//=============================================================================
// クリエイト
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos)
{
	//インスタンス
	CNumber *pNumber = {};

	if (pNumber == NULL)
	{
		//メモリを動的確保
		pNumber = new CNumber;

		if (pNumber != NULL)
		{
			// ポリゴンの初期化処理
			pNumber->Init(pos);
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULLじゃないです", "警告", MB_OK);

	}

	return pNumber;
}
//=============================================================================
// テクスチャの開放処理
//=============================================================================
void CNumber::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER_TEXTURE; nCount++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
// テクスチャの設置処理
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2((nNumber % 10) * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumber % 10) * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nNumber % 10) * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumber % 10) * 0.1f + 0.1f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

