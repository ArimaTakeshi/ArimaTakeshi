//=============================================================================
//
// タイムの処理 [time.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "time.h"
#include "game.h"
#include "sound.h"
#include "length.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define TEXTURE_TIME			"data/TEXTURE/number000.png"	//読み込むテクスチャファイル名
#define MAX_TIME				(3)								//桁数
#define TIMERIMIT				(60 * 60)						//制限時間
#define	LENGTH_TIME				(60)

//=============================================================================
// プロトタイプ宣言
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// グローバル変数
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;				// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;				// 頂点バッファへのポインタ
int g_nTime;												// スコア
int g_aTimeData[MAX_TIME];									//桁
TIMESTATE g_TimeState = TIMESTATE_NONE;						//タイムの状態の管理
Time g_TimeLeg;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;

	// タイムの初期化
	 g_nTime = TIMERIMIT;
	 g_TimeLeg.Lenght = LENGTH_TIME;
	 g_TimeState = TIMESTATE_NORMAL;

	 //タイムの桁、初期化処理
	 for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	 {
		 g_aTimeData[nCntTime] = 0;
	 }

	 AddTime();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,				// デバイスへのポインタ
		TEXTURE_TIME,			// ファイルの名前
		&g_pTextureTime			// テクスチャへのポインタ
	);							

	// 頂点情報の作成
	MakeVertexTime(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntTime;

	switch (g_TimeState)
	{
	case TIMESTATE_NORMAL:
		break;
	case TIMESTATE_END:
		g_nTime = 0;
		g_TimeState = TIMESTATE_NONE;
		SetGameState(GAMESTATE_CLEAR);
		break;
	}
	if (g_TimeState == TIMESTATE_NORMAL)
	{
		g_nTime--;

		if ((g_nTime % 60) == 0)
		{
			g_TimeLeg.Lenght -= 1;
			AddLength(-1, LengthTex_DAMAGE);
			AddTime();
		}

		//頂点バッファをロックし、頂点データへのポインタを取得
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{
			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCntTime] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCntTime] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aTimeData[nCntTime] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (g_aTimeData[nCntTime] * 0.1f), 1.0f);

			pVtx += 4;	//頂点データのポインタを4つ分進める
		}

		//頂点バッファをアンロックする
		g_pVtxBuffTime->Unlock();

		if (g_nTime == 0)
		{
			g_TimeState = TIMESTATE_END;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCntTime;

	// 頂点バッファをデータストリームに設定
    pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	// ポリゴンの描画
	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX_2D * pVtx;		//頂点情報へのポインタ
	int nCntTime;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	//タイムの座標設定
	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		pVtx[0].pos = D3DXVECTOR3(760.0f + (45.0f * nCntTime), 5.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(810.0f + (45.0f * nCntTime), 5.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(760.0f + (45.0f * nCntTime), 65.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(810.0f + (45.0f * nCntTime), 65.0f, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//タイムの色設定
		pVtx[0].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[1].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[2].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
		pVtx[3].col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// タイムの加算
//=============================================================================
void AddTime(void)
{
	//変数宣言
	int nNum = 1000;
	int nNum1 = 100;
	int nCntTime;
	int nTime;

	nTime = g_nTime / 60;	//1フレームの計算

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		g_aTimeData[nCntTime] = (nTime %  nNum) / nNum1;
		nNum = nNum / 10;
		nNum1 = nNum1 / 10;
	}
}
//=========================================================================================================================
// プレイヤーの取得処理
//=========================================================================================================================
Time *GetTime(void)
{
	return &g_TimeLeg;
}