//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "score.h"		//スコア
#include "Game.h"		//ゲーム

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SCORE	"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_SCORE	(8)									//スコアの最大桁数
#define SCORE_SIZE	(25)								//スコアの縦の幅、横の幅
#define MAX_SET		(6)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
Score g_nScore[MAX_SET];
SCORESTATE g_ScoreState;
GETCOINSTATE g_GetCoinState;
//=============================================================================
// 初期化処理
//=============================================================================
void InitScore(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SET; nCntScore++)
	{//スコアの桁数分カウント
		g_nScore[nCntScore].pos = D3DXVECTOR3(0, 0, 0);
		g_nScore[nCntScore].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_nScore[nCntScore].ScoreHeight = 0;
		g_nScore[nCntScore].ScoreWidth = 0;
		g_nScore[nCntScore].bUse = false;
	//	g_nScore[nCntScore].nNumScore = 0;
	}
	g_GetCoinState = GETCOIN_NORMAL;
	g_ScoreState = SCORE_NONE;
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&g_pTextureScore);	// テクスチャへのポインタ
	// 頂点情報の作成
	MakeVertexScore(pDevice);

}

//=============================================================================
// 終了処理
//=============================================================================
void UninitScore(void)
{
	// テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawScore(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (int nCntScore = 0; nCntScore < MAX_SET; nCntScore++)
	{//スコア表示分
		if (g_nScore[nCntScore].bUse == true)
		{//スコアがtrueなら
			for (int nCntScore2 = 0; nCntScore2 < MAX_SCORE; nCntScore2++)
			{//スコアの桁数分カウント
			 // ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore2 + MAX_SCORE * 4 * nCntScore, 2);
			}
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	//カウントスコア
	int nCntScore;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORE * MAX_SET),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < (MAX_SCORE * MAX_SET); nCntScore++)
	{//スコア表示分＊スコア桁数文
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//頂点データのポインタを4つ進める
		pVtx += 4;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddScore(int nValue ,SCORESTATE state)
{
	//カウントスコア
	int nCntScore;

	//桁数の入れ物
	int aNumber[MAX_SCORE];

	int nScoreDate;

	g_ScoreState = state;

	MODE pMode = *GetMode();
	GAMESTATE pGame = GetGameState();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	if (pGame == GAMESTATE_CLEAR || pGame == GAMESTATE_OVER)
	{//クリアかオーバーだったら
		for (int nCount = 0; nCount < MAX_SET - 1; nCount++)
		{//表示枚数
			for (int nCount2 = nCount + 1; nCount2 < MAX_SET; nCount2++)
			{//スコアの桁数文
				if (g_nScore[nCount].nNumScore < g_nScore[nCount2].nNumScore)
				{//降順に入れ替え
					nScoreDate = g_nScore[nCount2].nNumScore;
					g_nScore[nCount2].nNumScore = g_nScore[nCount].nNumScore;
					g_nScore[nCount].nNumScore = nScoreDate;
				}
			}
		}
	}
	//for (nCntData = 0; nCntData < MAX_DATA - 1; nCntData++)
	//{	//比較の繰り返し
	//	for (nCntData2 = nCntData + 1; nCntData2 < MAX_DATA; nCntData2++)
	//	{	//比較対象の繰り返し
	//		if (pData[nCntData] < pData[nCntData2])
	//		{	//値の比較	（降順並び替え < ）(昇順並び替え > )
	//			//値の格納
	//			nData = pData[nCntData2];

	//			//値の入れ替え
	//			pData[nCntData2] = pData[nCntData];
	//			pData[nCntData] = nData;
	//		}
	//	}
	//}

	for (int nCount = 0; nCount < MAX_SET; nCount++)
	{
		if (g_nScore[nCount].bUse == true)
		{
			if (pGame == GAMESTATE_NORMAL)
			{
				//スコアに加算
				if (g_ScoreState == SCORE_COIN && g_GetCoinState == GETCOIN_X2)
				{
					nValue *= 2;
				}
				g_nScore[nCount].nNumScore += nValue;
			}

			if (pGame == GAMESTATE_NORMAL ||
				((pGame == GAMESTATE_CLEAR || pGame == GAMESTATE_OVER) && pMode == MODE_RANKING))
			{
				//計算式
				aNumber[7] = g_nScore[nCount].nNumScore / 10000000;
				aNumber[6] = g_nScore[nCount].nNumScore % 10000000 / 1000000;
				aNumber[5] = g_nScore[nCount].nNumScore % 1000000 / 100000;
				aNumber[4] = g_nScore[nCount].nNumScore % 100000 / 10000;
				aNumber[3] = g_nScore[nCount].nNumScore % 10000 / 1000;
				aNumber[2] = g_nScore[nCount].nNumScore % 1000 / 100;
				aNumber[1] = g_nScore[nCount].nNumScore % 100 / 10;
				aNumber[0] = g_nScore[nCount].nNumScore % 10;

				for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
				{//スコアの桁数分カウント
				 //テクスチャ座標
					pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 1.0f);

					//頂点データのポインタを4つ進める
					pVtx += 4;
				}
			}
		}
		else
		{
			//頂点データのポインタを4つ進める
			pVtx += (4 * MAX_SCORE);
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// セットスコア
//=============================================================================
void SetScore(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	//スコアのカウント
	int nCntScore;

	GAMESTATE pGame = GetGameState();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore = 0; nCntScore < MAX_SET; nCntScore++)
	{//スコアの表示分
		if (g_nScore[nCntScore].bUse == false)
		{//ブロックが使用されていない場合
			g_nScore[nCntScore].pos = pos;				//pos値代入
			g_nScore[nCntScore].col = col;				//カラー
			g_nScore[nCntScore].bUse = true;			//使用している状態にする
			g_nScore[nCntScore].ScoreHeight = fHeight;	//ブロックの高さ
			g_nScore[nCntScore].ScoreWidth = fWidth;	//ブロックの幅

			if (pGame == GAMESTATE_NONE)
			{//ゲーム状態がnoneだったら
				g_nScore[MAX_SET - 1].nNumScore = g_nScore[nCntScore].nNumScore;
				//初期化
				g_nScore[nCntScore].nNumScore = 0;
			}
			for (int nCntScore2 = 0; nCntScore2 < MAX_SCORE; nCntScore2++)
			{//スコアの桁数分カウント
				//頂点設定
				pVtx[nCntScore2 * 4].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y, 0.0f);
				pVtx[nCntScore2 * 4 + 1].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x + g_nScore[nCntScore].ScoreWidth - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y, 0.0f);
				pVtx[nCntScore2 * 4 + 2].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y + g_nScore[nCntScore].ScoreHeight, 0.0f);
				pVtx[nCntScore2 * 4 + 3].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x + g_nScore[nCntScore].ScoreWidth - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y + g_nScore[nCntScore].ScoreHeight, 0.0f);
				//頂点カラー設定
				pVtx[nCntScore2 * 4].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
				pVtx[nCntScore2 * 4 + 1].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
				pVtx[nCntScore2 * 4 + 2].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
				pVtx[nCntScore2 * 4 + 3].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
			}
			break;
		}
		pVtx += (4 * MAX_SCORE);
	}
	//頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
//
//=============================================================================
void SetCoinState(GETCOINSTATE state)
{
	g_GetCoinState = state;
}
//=============================================================================
// スコアのゲット
//=============================================================================
Score *GetScore(void)
{
	return &g_nScore[0];
}