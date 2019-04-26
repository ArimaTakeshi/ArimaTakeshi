//=============================================================================
//
// タイム処理 [time.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "time.h"		//タイム
#include "game.h"		//ゲーム
#include "fade.h"		//フェード
#include "score.h"		//スコア
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	//読み込むテクスチャファイル名
#define MAX_TIME			(3)								//タイムの最大桁数
#define TIME_SIZE			(25)							//時間の幅
#define TIME				(6000)							//最初の時間 //１秒１００

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3				g_posTime;					//タイムの位置
Time					g_nTime;					//タイムの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//タイムの初期座標
	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, 40, 0.0f);

	//タイムの初期化
	g_nTime.nTime = TIME;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				//デバイスへのポインタ
							TEXTURE_TIME,			//ファイルの名前
							&g_pTextureTime);		//テクスチャへのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ進める
		//桁の幅
		g_posTime.x += 50;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

	//AddTime(180);
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

	//頂点バッファの破棄
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
	//何桁目の情報か
	int aNumber[MAX_TIME];
	//秒数カウント
	int nCount = 0;

	//頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//３桁目までの計算
	aNumber[0] = g_nTime.nTime % 100000 / 10000;
	aNumber[1] = g_nTime.nTime % 10000 / 1000;
	aNumber[2] = g_nTime.nTime % 1000 / 100;

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{//全タイムの桁数分カウント
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntTime] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntTime] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntTime] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntTime] * 0.1f, 1.0f);

		if (g_nTime.nTime <= 600)
		{//特定の秒数を切った場合、赤くする
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		//頂点データのポインタを4つ進める
		pVtx += 4;	
	} 
	//時間が０になったら終了！
	if (g_nTime.nTime <= 0)
	{
		//モードのポインタ
		MODE pMode;
		pMode = *GetMode();

		//タイムが０になったらリザルトに行く
		if ((nCount % 250) == 0)
		{
			SetGameState(GAMESTATE_OVER);
		}
	}
	//タイムを引いていく、++にすると上がっていく
	if (g_nTime.nTime >= 0)
	{
		g_nTime.nTime--;
		g_nTime.nTime--;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{//全タイムの桁数文カウント
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}
//=========================================================================================================================
// タイムの取得処理
//=========================================================================================================================
Time *GetTime(void)
{
	return &g_nTime;
}
//=========================================================================================================================
// ブロックの取得処理
//=========================================================================================================================
void DeleteTime(void)
{
	//タイムの初期座標
	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, 40, 0.0f);

	//頂点情報を設定
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();

	//タイムの初期化
	g_nTime.nTime = TIME;
}
