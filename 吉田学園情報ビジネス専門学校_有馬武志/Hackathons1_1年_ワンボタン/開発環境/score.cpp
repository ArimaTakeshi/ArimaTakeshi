//=========================================================================================================================
// 
// スコア処理 [score.cpp]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#define _CRT_SECURE_NO_WARNINGS				// scanfエラー解除
#include <stdio.h>
#include "score.h"		// スコア
#include "input.h"		// キーボード

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MAX_SCORE_SET		(5)								// スコアの最大数
#define MAX_SCORE_NUMBER	(6)								// スコアの最大桁数
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	SCORE_FILE			"data/SAVE/scoreranking.bin"	// 読み込むスコアテキストファイル名
#define SCORE_SPEED			(15.0f)							// スコアの移動速度

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9			g_pTextureScore = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffScore = NULL;		// 頂点バッファへのポインタ
Score						g_Score[MAX_SCORE_SET];		// スコア情報
int							g_nScoreRanking[MAX_SCORE_SET + 1];		// スコア格納
int							g_nScoreRankIn;
int							g_nSetScore;

//=========================================================================================================================
// スコア初期化処理
//=========================================================================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	int nCntSet;					// セットカウンタ
	float nCntScore;				// スコアカウンタ
	float nScorePos;				// スコア位置

									// スコアの初期化
	for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
	{// セットをカウント
		g_Score[nCntSet].nScore = 0;								// スコアを初期化 
		g_Score[nCntSet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// スコア中心値
		g_Score[nCntSet].posmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// スコア間隔値
		g_Score[nCntSet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// スコア色
		g_Score[nCntSet].bUse = false;								// 使用しているかどうか
	}
	for (nCntSet = 0; nCntSet <= MAX_SCORE_SET; nCntSet++)
	{// セットをカウント
		g_nScoreRanking[nCntSet] = 0;	//スコア初期化
	}
	g_nScoreRankIn = 6;
	g_nSetScore = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_SCORE,
		&g_pTextureScore
	);

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * (MAX_SCORE_NUMBER * MAX_SCORE_SET),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL
	);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロック
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
	{// セットをカウント
		for (nCntScore = 0, nScorePos = 1200; nCntScore < MAX_SCORE_NUMBER; nCntScore++, nScorePos -= 30)
		{// 桁数とカウント
		 // 頂点設定
			pVtx[0].pos = D3DXVECTOR3(nScorePos, 30.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(nScorePos + 30.0f, 30.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(nScorePos, 80.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(nScorePos + 30.0f, 80.0f, 0.0f);
			// 1.0fで固定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;
			// 頂点カラー設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			pVtx += 4;	// 頂点データのポインタを４つ分進める
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//=========================================================================================================================
// スコア終了処理
//=========================================================================================================================
void UninitScore(void)
{
	// テクスチャーの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=========================================================================================================================
// スコア更新処理
//=========================================================================================================================
void UpdateScore(void)
{
	// 変数宣言
	int nCntSet;		// セットカウンタ
	int nCntScore;		// スコアカウンタ
	int nScoreData;		// スコア格納

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロック
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	if (g_nSetScore == 0)
	{
		MODE *mode = GetMode();		// モードを取得

		if (mode[0] == MODE_RESULT)
		{
			AddScore(SCORETYPE_RNKING_NO1, g_nScoreRanking[0]);
			AddScore(SCORETYPE_RNKING_NO2, g_nScoreRanking[1]);
			AddScore(SCORETYPE_RNKING_NO3, g_nScoreRanking[2]);
			AddScore(SCORETYPE_RNKING_NO4, g_nScoreRanking[3]);
			AddScore(SCORETYPE_RNKING_NO5, g_nScoreRanking[4]);

			for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
			{// セットカウンタ

				if (g_nScoreRanking[nCntSet] == g_nScoreRanking[5])
				{
					g_nScoreRankIn = nCntSet;
				}
			}
		}

		g_nSetScore = 1;
	}

	for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
	{// セットをカウント
		if (g_Score[nCntSet].bUse == true)
		{// スコアが使用されている場合
			nScoreData = g_Score[nCntSet].nScore;	// スコアを格納

			for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
			{// スコアカウント
			 // テクスチャ設定
				pVtx[nCntScore * 4].tex = D3DXVECTOR2((nScoreData % 10) * 0.1f, 0.0f);
				pVtx[nCntScore * 4 + 1].tex = D3DXVECTOR2((nScoreData % 10) * 0.1f + 0.1f, 0.0f);
				pVtx[nCntScore * 4 + 2].tex = D3DXVECTOR2((nScoreData % 10) * 0.1f, 1.0f);
				pVtx[nCntScore * 4 + 3].tex = D3DXVECTOR2((nScoreData % 10) * 0.1f + 0.1f, 1.0f);

				if (nCntSet == g_nScoreRankIn && g_nScoreRanking[5] != 0)
				{
					// 頂点カラー設定
					pVtx[nCntScore * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Score[nCntSet].col.a);
					pVtx[nCntScore * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Score[nCntSet].col.a);
					pVtx[nCntScore * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Score[nCntSet].col.a);
					pVtx[nCntScore * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Score[nCntSet].col.a);
				}

				nScoreData /= 10;		// 桁を進める
			}
		}
		pVtx += (MAX_SCORE_NUMBER * 4);		// 頂点データのポインタ進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//=========================================================================================================================
// スコア描画処理
//=========================================================================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	int nCntSet;		// セットカウンタ
	int nCntScore;		// スコアカウンタ

						// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffScore,
		0,
		sizeof(VERTEX_2D)
	);

	// 頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ設定
	pDevice->SetTexture(0, g_pTextureScore);

	// スコアの描画
	for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
	{// セットをカウント
		if (g_Score[nCntSet].bUse == true)
		{// 使用している場合
			for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
			{// スコアカウント
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4 + nCntSet * (MAX_SCORE_NUMBER * 4), 2);
			}
		}
	}
}

//=========================================================================================================================
// スコア設定処理
//=========================================================================================================================
void SetScore(D3DXVECTOR3 pos, D3DXVECTOR3 nRadius, D3DXCOLOR col)
{
	int nCntSet;		// セットカウンタ
	int nCntScore;		// スコアカウンタ
	D3DXVECTOR3 nPos;	// 位置を格納

	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

								// 頂点バッファをロック
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
	{// セットをカウント
		if (g_Score[nCntSet].bUse == false)
		{// 使用されている場合
			g_Score[nCntSet].pos = pos;							// 位置
			g_Score[nCntSet].posmove = g_Score[nCntSet].pos;	// 移動値
			nPos = g_Score[nCntSet].pos;						// 位置を格納
			g_Score[nCntSet].nRadius = nRadius;					// 大きさ
			g_Score[nCntSet].col = col;							// 色
			g_Score[nCntSet].bUse = true;						// 使用している状態

			for (nCntScore = 0; nCntScore < MAX_SCORE_NUMBER; nCntScore++)
			{// スコアをカウント
			 // 頂点設定
				pVtx[nCntScore * 4].pos = D3DXVECTOR3(nPos.x, nPos.y - g_Score[nCntSet].nRadius.y, 0.0f);
				pVtx[nCntScore * 4 + 1].pos = D3DXVECTOR3(nPos.x + g_Score[nCntSet].nRadius.x, nPos.y - g_Score[nCntSet].nRadius.y, 0.0f);
				pVtx[nCntScore * 4 + 2].pos = D3DXVECTOR3(nPos.x, nPos.y + g_Score[nCntSet].nRadius.y, 0.0f);
				pVtx[nCntScore * 4 + 3].pos = D3DXVECTOR3(nPos.x + g_Score[nCntSet].nRadius.x, nPos.y + g_Score[nCntSet].nRadius.y, 0.0f);
				// 頂点カラー設定
				pVtx[nCntScore * 4].col = D3DXCOLOR(g_Score[nCntSet].col.r, g_Score[nCntSet].col.g, g_Score[nCntSet].col.b, g_Score[nCntSet].col.a);
				pVtx[nCntScore * 4 + 1].col = D3DXCOLOR(g_Score[nCntSet].col.r, g_Score[nCntSet].col.g, g_Score[nCntSet].col.b, g_Score[nCntSet].col.a);
				pVtx[nCntScore * 4 + 2].col = D3DXCOLOR(g_Score[nCntSet].col.r, g_Score[nCntSet].col.g, g_Score[nCntSet].col.b, g_Score[nCntSet].col.a);
				pVtx[nCntScore * 4 + 3].col = D3DXCOLOR(g_Score[nCntSet].col.r, g_Score[nCntSet].col.g, g_Score[nCntSet].col.b, g_Score[nCntSet].col.a);

				nPos.x -= g_Score[nCntSet].nRadius.x;	//位置をずらす
			}

			break;
		}
		pVtx += (MAX_SCORE_NUMBER * 4); 	// 頂点データのポインタ進める
	}

	// 頂点バッファをアンロック
	g_pVtxBuffScore->Unlock();
}

//=========================================================================================================================
// スコアの取得処理
//=========================================================================================================================
Score GetScore(void)
{
	return g_Score[0];		// 値を返す
}

//=========================================================================================================================
// スコアの加算処理
//=========================================================================================================================
void AddScore(SCORETYPE Type, int nValue)
{
	MODE *mode = GetMode();		// モードを取得

	if (mode[0] != MODE_TUTORIAL)
	{// チュートリアル以外の場合
	//	if (g_Score[Type].bUse == true)
		{// 使用している場合
			g_Score[Type].nScore += nValue;		// スコアを代入
		}
	}
}

//=========================================================================================================================
// スコアのセーブ処理
//=========================================================================================================================
void SaveScore(SCORETYPE Type)
{
	// 変数宣言
	FILE *pFile;		// ファイルポインタ
	int nCntSet;		// セットカウンタ
	int nCntSetSort;	// 整列
	int nScoreData;		// 値を格納

	g_nScoreRanking[5] = g_Score[Type].nScore;	// 配列に格納

												// ファイル設定
	pFile = fopen(SCORE_FILE, "wb");

	if (pFile != NULL)
	{// ファイルが開けた場合
		for (nCntSet = 0; nCntSet < MAX_SCORE_SET; nCntSet++)
		{// セットをカウント
			for (nCntSetSort = nCntSet + 1; nCntSetSort < MAX_SCORE_SET + 1; nCntSetSort++)
			{// 比較対象
				if (g_nScoreRanking[nCntSet] < g_nScoreRanking[nCntSetSort])
				{// 降順に整列
					nScoreData = g_nScoreRanking[nCntSetSort];	// 値を格納

					g_nScoreRanking[nCntSetSort] = g_nScoreRanking[nCntSet];	// 値の入れ替え
					g_nScoreRanking[nCntSet] = nScoreData;		// 値の入れ替え
				}
			}
		}
		g_nScoreRanking[5] = g_Score[Type].nScore;	// 配列に格納
		/*
		g_nScoreRanking[0] = 0;
		g_nScoreRanking[1] = 0;
		g_nScoreRanking[2] = 0;
		g_nScoreRanking[3] = 0;
		g_nScoreRanking[4] = 0;
		g_nScoreRanking[5] = 0;
		*/
		fwrite(&g_nScoreRanking, sizeof(int), MAX_SCORE_SET + 1, pFile);		// 書き込み

		fclose(pFile);	// ファイルを閉じる
	}
	else
	{// ファイルが開けない場合
		MessageBox(0, "セーブファイルのチェックに失敗！", "警告！", MB_ICONWARNING);
	}

}

//=========================================================================================================================
// スコアのロード処理
//=========================================================================================================================
void LoadScore(void)
{
	// 変数宣言
	FILE *pFile;	// ファイルポインタ

	// ファイル設定
	pFile = fopen(SCORE_FILE, "rb");

	if (pFile != NULL)
	{// ファイルが開けた場合
		fread(&g_nScoreRanking, sizeof(int), MAX_SCORE_SET + 1, pFile);		// 読み込み

		fclose(pFile);				//ファイルを閉じる
	}
	else
	{// ファイルが開けない場合
		MessageBox(0, "ロードファイルのチェックに失敗！", "警告！", MB_ICONWARNING);
	}
}