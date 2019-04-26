//=============================================================================
//
// ライフ処理 [lenght.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "length.h"
#include "player.h"
#include "input.h"
#include "time.h"
#include "fade.h"
#include "frame.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LENGTH		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_LENGTH1		"data/TEXTURE/Length.png"		// 読み込むテクスチャファイル名
#define MAX_POLYGON			(122)							//スコアの最大桁数
#define MAX_TEXTURE			(2)								//スコアの最大桁数
#define MAX_LENGTH_TEX		(120)							//スコアの最大桁数
#define MAX_LENGTH_NUM		(2)								//スコアの最大桁数

#define LENGTH_SIZE			(15)
#define TEXLENGTH_SIZE_X	(1)
#define TEXLENGTH_SIZE_Y	(20)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLength(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLength[MAX_TEXTURE] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLength = NULL;				// 頂点バッファへのポインタ
int						g_nLength;								// スコア
D3DXVECTOR3				g_posLength;
D3DXVECTOR3				g_posTexLength;
bool					g_bLengthTex[MAX_LENGTH_TEX];

//=============================================================================
// 初期化処理
//=============================================================================
void InitLength(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//数値
	g_posLength = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	//ゲージ
	g_posTexLength = D3DXVECTOR3(SCREEN_WIDTH / 2 - 57, SCREEN_HEIGHT / 2, 0.0f);

	for (int nCount = 0; nCount < MAX_LENGTH_TEX; nCount++)
	{
		g_bLengthTex[nCount] = true;
	}

	// スコアの初期化
	g_nLength = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
							TEXTURE_LENGTH,			// ファイルの名前
							&g_pTextureLength[0]);	// テクスチャへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
							TEXTURE_LENGTH1,		// ファイルの名前
							&g_pTextureLength[1]);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLength(pDevice);

	//初期化処理
	AddLength(120, LengthTex_Init);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLength(void)
{
	int nCountTex;
	// テクスチャの開放
	for (nCountTex = 0; nCountTex < MAX_TEXTURE; nCountTex++)
	{
		if (g_pTextureLength[nCountTex] != NULL)
		{
			g_pTextureLength[nCountTex] -> Release();
			g_pTextureLength[nCountTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffLength != NULL)
	{
		g_pVtxBuffLength->Release();
		g_pVtxBuffLength = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLength(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLength(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCountTex;
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLength, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	for (nCountTex = 0; nCountTex < MAX_POLYGON; nCountTex++)
	{
		if (nCountTex < MAX_LENGTH_NUM)
		{
			pDevice->SetTexture(0, g_pTextureLength[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex, 2);
		}
		else if (g_bLengthTex[nCountTex - MAX_LENGTH_NUM] == true)
		{
			pDevice->SetTexture(0, g_pTextureLength[1]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex , 2);
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLength(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLength;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLength,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLength->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLength = 0; nCntLength < MAX_POLYGON; nCntLength++)
	{
		if (nCntLength < MAX_LENGTH_NUM)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posLength.x - LENGTH_SIZE, g_posLength.y - LENGTH_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posLength.x + LENGTH_SIZE, g_posLength.y - LENGTH_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posLength.x - LENGTH_SIZE, g_posLength.y + LENGTH_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posLength.x + LENGTH_SIZE, g_posLength.y + LENGTH_SIZE, 0.0f);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			g_posLength.x += 28;
		}
		else
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posTexLength.x - TEXLENGTH_SIZE_X, g_posTexLength.y - TEXLENGTH_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTexLength.x + TEXLENGTH_SIZE_X, g_posTexLength.y - TEXLENGTH_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTexLength.x - TEXLENGTH_SIZE_X, g_posTexLength.y + TEXLENGTH_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTexLength.x + TEXLENGTH_SIZE_X, g_posTexLength.y + TEXLENGTH_SIZE_Y, 0.0f);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_posTexLength.x += 1;
		}
		
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//色を変える処理
		if (nCntLength >= MAX_POLYGON - 60)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		}
		else if (nCntLength >= MAX_POLYGON - 90)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.15f, 0.15f, 1.0f, 1.0f);
		}
		else if (nCntLength >= MAX_POLYGON - 110)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f);
		}
		else
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.25f, 0.25f, 1.0f, 1.0f);
		}

		pVtx += 4;	//頂点データのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLength->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddLength(int nLength, LENGTHTEX Length)
{
	// 頂点情報を設定
	VERTEX_2D *pVtx;

	Time *pTime = GetTime();

	int nCntLength = 0;
	int aNumber[MAX_LENGTH_NUM];
	int nCntDeleteLeg = 0;

	//入ってきた文距離に入れる
	g_nLength += nLength;

	if (Length == LengthTex_DAMAGE)
	{
		//画像を時間分無くしていく
		g_bLengthTex[pTime->Lenght] = false;
	}
	//回復する場合
	if (Length == LengthTex_HIL)
	{
		for (int nCount = 11; nCount >= 0; nCount--)
		{
			if (g_bLengthTex[nCount] == false)
			{
				g_bLengthTex[nCount] = true;

				//テクスチャの増加
				g_bLengthTex[pTime->Lenght + g_bLengthTex[nCount]];
			}
		}
	}
	//ガソリンが切れた場合
	if (g_nLength == 0)
	{
		SetFade(MODE_RESULT);
	}
	
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLength->Lock(0, 0, (void**)&pVtx, 0);

	/*aNumber[0] = g_nLength % 100 / 10;
	aNumber[1] = g_nLength % 10;*/

	for (nCntLength = 0; nCntLength < MAX_LENGTH_NUM; nCntLength++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntLength] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntLength] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntLength] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntLength] * 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLength->Unlock();
}