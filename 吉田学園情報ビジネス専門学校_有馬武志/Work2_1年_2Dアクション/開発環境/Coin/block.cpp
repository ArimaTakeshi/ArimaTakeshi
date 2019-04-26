//=========================================================================================================================
//
// ブロック処理 [block.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "block.h"		//ブロック
#include "item.h"		//アイテム
#include "player.h"		//プレイヤー
#include "score.h"		//スコア
#include "sound.h"		//サウンド
#include "life.h"		//ライフ

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define BLOCK_TEXTURE_NAME			"data\\TEXTURE\\block000.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME1			"data\\TEXTURE\\block001.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME2			"data\\TEXTURE\\block002.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME3			"data\\TEXTURE\\ベルトコンベアー.png"		//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME4			"data\\TEXTURE\\ベルトコンベアー2.png"		//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME5			"data\\TEXTURE\\block005.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME6			"data\\TEXTURE\\block004.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME7			"data\\TEXTURE\\block003.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME8			"data\\TEXTURE\\床土部分.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME9			"data\\TEXTURE\\たたいた後のブロック.jpg"	//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME10		"data\\TEXTURE\\お金箱.jpg"					//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME11		"data\\TEXTURE\\横壁.jpg"					//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME12		"data\\TEXTURE\\毒.jpg"						//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME13		"data\\TEXTURE\\両方押す.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME14		"data\\TEXTURE\\両側押す偽.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME15		"data\\TEXTURE\\block0031.jpg"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME16		"data\\TEXTURE\\ゴールドブロック.jpg"		//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME17		"data\\TEXTURE\\説明.png"					//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME18		"data\\TEXTURE\\アイテム説明.png"			//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME19		"data\\TEXTURE\\操作説明.png"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME20		"data\\TEXTURE\\とげ.png"					//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME21		"data\\TEXTURE\\とげかべ.png"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME22		"data\\TEXTURE\\とげかべ.png"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_NAME23		"data\\TEXTURE\\ルール説明.png"				//読み込むテクスチャファイル
#define BLOCK_TEXTURE_UV_U			(1.0f)										//ブロックアニメーションU範囲
#define BLOCK_TEXTURE_UV_V			(1.0f)										//ブロックアニメーションV範囲
#define MAX_TYPE_BLOCK				(24)										//ブロックの種類
#define MAX_BLOCK_TEX				(24)										//画像の枚数

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TYPE_BLOCK] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;					//頂点バッファへのポインタ
Block g_aBlock[MAX_BLOCK];										//ブロックの情報
int g_nCntBlock = 0;                                            //ブロックカウント
int g_nCntBlockt = 0;                                            //ブロックカウント
int g_nCount1;
int g_nCount2;

//=========================================================================================================================
// ブロック初期化処理
//=========================================================================================================================
void InitBlock(void)
{	
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;	

	int nCntBlock;

	//デバイスの取得
	pDevice = GetDevice();

	//ブロックの情報の初期化
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//初期値
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	
		g_aBlock[nCntBlock].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aBlock[nCntBlock].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].BlockWidth = 0;
		g_aBlock[nCntBlock].BlockHeight = 0;
	}
	g_nCount1 = 0;
	g_nCount2 = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１枚目
		pDevice,
		BLOCK_TEXTURE_NAME,
		&g_pTextureBlock[0]		
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２枚目
		pDevice,
		BLOCK_TEXTURE_NAME1,
		&g_pTextureBlock[1]		
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像３枚目
		pDevice,
		BLOCK_TEXTURE_NAME2,
		&g_pTextureBlock[2]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像４枚目
		pDevice,
		BLOCK_TEXTURE_NAME3,
		&g_pTextureBlock[3]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像５枚目
		pDevice,
		BLOCK_TEXTURE_NAME4,
		&g_pTextureBlock[4]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像６枚目
		pDevice,
		BLOCK_TEXTURE_NAME5,
		&g_pTextureBlock[5]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像７枚目
		pDevice,
		BLOCK_TEXTURE_NAME6,
		&g_pTextureBlock[6]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像８枚目
		pDevice,
		BLOCK_TEXTURE_NAME7,
		&g_pTextureBlock[7]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像９枚目
		pDevice,
		BLOCK_TEXTURE_NAME8,
		&g_pTextureBlock[8]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１０枚目
		pDevice,
		BLOCK_TEXTURE_NAME9,
		&g_pTextureBlock[9]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１１枚目
		pDevice,
		BLOCK_TEXTURE_NAME10,
		&g_pTextureBlock[10]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１２枚目
		pDevice,
		BLOCK_TEXTURE_NAME11,
		&g_pTextureBlock[11]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１３枚目
		pDevice,
		BLOCK_TEXTURE_NAME12,
		&g_pTextureBlock[12]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１４枚目
		pDevice,
		BLOCK_TEXTURE_NAME13,
		&g_pTextureBlock[13]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１５枚目
		pDevice,
		BLOCK_TEXTURE_NAME14,
		&g_pTextureBlock[14]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１６枚目
		pDevice,
		BLOCK_TEXTURE_NAME15,
		&g_pTextureBlock[15]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１７枚目
		pDevice,
		BLOCK_TEXTURE_NAME16,
		&g_pTextureBlock[16]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１８枚目
		pDevice,
		BLOCK_TEXTURE_NAME17,
		&g_pTextureBlock[17]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１９枚目
		pDevice,
		BLOCK_TEXTURE_NAME18,
		&g_pTextureBlock[18]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２０枚目
		pDevice,
		BLOCK_TEXTURE_NAME19,
		&g_pTextureBlock[19]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２１枚目
		pDevice,
		BLOCK_TEXTURE_NAME20,
		&g_pTextureBlock[20]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２２枚目
		pDevice,
		BLOCK_TEXTURE_NAME21,
		&g_pTextureBlock[21]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２３枚目
		pDevice,
		BLOCK_TEXTURE_NAME22,
		&g_pTextureBlock[22]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２４枚目
		pDevice,
		BLOCK_TEXTURE_NAME23,
		&g_pTextureBlock[23]
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;	

	//頂点バッファをロック
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//ブロックの情報の初期化
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックをカウント
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BLOCK_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, BLOCK_TEXTURE_UV_V);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================================
// ブロック終了処理
//=========================================================================================================================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK_TEX; nCntBlock++)
	{//全ブロックのカウント
		//テクスチャーの破棄
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBlock!= NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock= NULL;
	}
}

//=========================================================================================================================
// ブロック更新処理
//=========================================================================================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//モードのポインタ
	MODE pMode = *GetMode();

	//プレイヤーのポインタ
	Player *pPlayer = GetPlayer();

	//頂点バッファをロック
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	//上下の、下から上にあがるときに落ちるから、ブロックの過去の位置をposに代入
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//全ブロックカウント
		//代入
		g_aBlock[nCntBlock].posold = g_aBlock[nCntBlock].pos;
	}
	//移動系の床の設定
	for(int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//全ブロックのカウント
		//タイプ１
		if (g_aBlock[nCntBlock].nType == 1)
		{//横に動く移動床
			if (g_aBlock[nCntBlock].pos.x >= 810)
			{//横右810まで行ったら
				//移動                                        ↓角度　 ↓スピード
				g_aBlock[nCntBlock].move.x += sinf(-D3DX_PI * 0.5f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].pos.x <= 440)
			{//横左440まで行ったら
				//移動                                       ↓角度　 ↓スピード
				g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].move.x == 0)
			{//移動のスタート
				//移動                                       ↓角度　 ↓スピード
				g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 1.0f;
			}
		}
		//タイプ２
		if (g_aBlock[nCntBlock].nType == 2)
		{//縦に動く移動床
			if (g_aBlock[nCntBlock].pos.y <= 200)
			{//上180まで行ったら
				//移動                                       ↓角度　 ↓スピード
				g_aBlock[nCntBlock].move.y += cosf(D3DX_PI * 0.0f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].pos.y >= 370)
			{//下480まで行ったら
				//移動                                       ↓角度　 ↓スピード
				g_aBlock[nCntBlock].move.y += cosf(D3DX_PI * 1.0f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].move.y == 0)
			{//移動のスタート
				//移動                                       ↓角度　 ↓スピード
				g_aBlock[nCntBlock].move.y += cosf(D3DX_PI * 0.0f) * 1.0f;
			}
		}
		//タイプ２１
		if (g_aBlock[nCntBlock].nType == 21)
		{//横に動く移動床
			g_nCount2++;
			if ((g_nCount2 % 60) == 0)
			{
				if (g_aBlock[nCntBlock].pos.x >= 1040)
				{//横右810まで行ったら
				 //移動                                        ↓角度　 ↓スピード
					g_aBlock[nCntBlock].move.x += sinf(-D3DX_PI * 0.5f) * 2.0f;
					g_aBlock[nCntBlock].move.x = 0;
					g_nCount2 = 0;
				}
				else if (g_aBlock[nCntBlock].move.x == 0)
				{//移動のスタート
				 //移動                                       ↓角度　 ↓スピード
					g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 2.0f;
				}
			}
		}
		//タイプ２２
		if (g_aBlock[nCntBlock].nType == 22)
		{//横に動く移動床
			g_nCount1 ++;
			if ((g_nCount1 == 600))
			{
				if (g_aBlock[nCntBlock].pos.x >= 1320)
				{//横左440まで行ったら
				 //移動                                       ↓角度　 ↓スピード
					g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 2.3f;
					g_aBlock[nCntBlock].move.x = 0;
					g_nCount1 = 0;
				}
				else if (g_aBlock[nCntBlock].move.x == 0)
				{//移動のスタート
				 //移動                                       ↓角度　 ↓スピード
					g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 2.0f;
				}
			}
		}
		
		//moveをposに代入ｘ
		g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
		//moveをposに代入y
		g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;

		//頂点カラー設定
		pVtx[nCntBlock * 4].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		pVtx[nCntBlock * 4 + 1].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		pVtx[nCntBlock * 4 + 2].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		pVtx[nCntBlock * 4 + 3].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		//頂点設定
		pVtx[nCntBlock * 4].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[nCntBlock * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[nCntBlock * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);
		pVtx[nCntBlock * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);

	}

	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================================
// ブロック描画処理
//=========================================================================================================================
void DrawBlock(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;	

	//ブロックカウント
	int nCntBlock;					

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffBlock, 
		0, 
		sizeof(VERTEX_2D)
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//ポリゴンの描画
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックをカウント
		if (g_aBlock[nCntBlock].bUse == true)
		{//ブロックがある場合
			 //テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}
//=========================================================================================================================
// ブロックの設定処理
//=========================================================================================================================
void SetBlock(D3DXVECTOR3 pos,D3DXCOLOR col, int nType, float fHeight, float fWidth)
{	
	//ブロックカウント
	int nCntBlock;		

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;		

	//頂点バッファをロック
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//ブロックをカウント
		if (g_aBlock[nCntBlock].bUse == false)
		{//ブロックが使用されていない場合
			g_aBlock[nCntBlock].pos = pos;				//pos値代入
			g_aBlock[nCntBlock].col = col;				//カラー
			g_aBlock[nCntBlock].bUse = true;			//使用している状態にする
			g_aBlock[nCntBlock].nType = nType;			//ブロックタイpu
			g_aBlock[nCntBlock].BlockHeight = fHeight;	//ブロックの高さ
			g_aBlock[nCntBlock].BlockWidth = fWidth;	//ブロックの幅
	
			//頂点設定
			pVtx[nCntBlock * 4].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);
			pVtx[nCntBlock * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);
			//頂点カラー設定
			pVtx[nCntBlock * 4].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			pVtx[nCntBlock * 4 + 1].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			pVtx[nCntBlock * 4 + 2].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			pVtx[nCntBlock * 4 + 3].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			break;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}
//=========================================================================================================================
// ブロックのあたり判定
//=========================================================================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove , float *fWidth, float *fHeight)
{	
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;		

	//頂点バッファをロック
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	int nCount = 0;

	bool bLand = false;	//差地したかどう

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//全ブロックのカウント                                         ↓ここで/3をしないと空中浮遊する                          ↓ここで/3をしないと空中浮遊する
		if (g_aBlock[nCntBlock].bUse == true && (pPos->x + *fWidth / 3) >= g_aBlock[nCntBlock].pos.x && (pPos->x - *fWidth / 3) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth)
		{	//上から乗っかる　                      ↓ブロックの現在位置
			if (pPosOld->y <= g_aBlock[nCntBlock].posold.y && pPos->y >= g_aBlock[nCntBlock].pos.y)
			{//上のあたり判定
				bLand = true;
				pPos->y = g_aBlock[nCntBlock].pos.y; //プレイヤーの位置(高さ)を更新

//***************************
//	いろいろ要素がある床
//***************************
				//タイプ３　右用ベルトコンベアー
				if (g_aBlock[nCntBlock].nType == 3)
				{//ブロックの上に載っているとき
					//プレイヤーのmove値xを1.5fにする(右)
					pMove->x = 1.0f;
				}
				//タイプ４　左用ベルトコンベアー
				else if (g_aBlock[nCntBlock].nType == 4)
				{//ブロックの上に載っているとき
					//プレイヤーのmove値xを-1.5fにする(左)
					pMove->x = -1.0f;
				}
				//そうじゃなかった場合
				else
				{//ブロックから落ちて、地面についた場合
					 //プレイヤーのmove値xを0にする
					pMove->x = 0.0f;
				}

				//タイプ６	落ちる床
				if (g_aBlock[nCntBlock].nType == 6)
				{//ブロックの上に載っているとき
					//落ちる音
					PlaySound(SOUND_LABEL_SE_FALL);
					g_aBlock[nCntBlock].move.y = 6.0f;
				}
				if (g_aBlock[nCntBlock].nType == 12)
				{//ブロックの上に載っているとき
					//毒ブロック
						HitPlayer(3);
				}
				if (g_aBlock[nCntBlock].nType == 20)
				{//ブロックの上に載っているとき
				 //とげ
				 //if (nCount % 240 == 0)
				 //{
						HitPlayer(3);
				 //}
				}
//***************************

				//プレイヤーのmove値yを0にする
				pMove->y = 0.0f;

				////ブロックのmoveの値をプレイヤーに代入し、プレイヤーが落ちないようにする
				pPos->x += g_aBlock[nCntBlock].move.x;
			}
			//下から突き上げる         ↓頂点座標を頭の位置まで上げる（ｙだけプレイヤーの身長分を差し引く）　　　      　　　　　↓これも同じ                                                 ↓ブロックの高さ分あたり判定
			else if ((pPosOld->y - *fHeight) >= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight) && (pPos->y - *fHeight) <= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight))
			{//下のあたり判定                                                              ↓めり込みを押し返す(プレイヤーの身長分)
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight + *fHeight; //プレイヤーの位置(高さ)を更新

//***************************
//　いろいろ要素がある床
//***************************
				//タイプ５　壊せる床
				if (g_aBlock[nCntBlock].nType == 5)
				{//ブロックの下からあたった場合
					//壊すときの音
					PlaySound(SOUND_LABEL_SE_BREAK);
					//ブロックの下に当たったら、bUseをfalseにする
					g_aBlock[nCntBlock].bUse = false;
				}
				//タイプ９　透明なブロック
 				if (g_aBlock[nCntBlock].nType == 9)
				{//ブロックの下からあたった場合
					g_aBlock[nCntBlock].col.a = 1.0f;
					//発見音
					PlaySound(SOUND_LABEL_SE_FOUND);
					//ブロックをたたいた回数+
					if (g_nCntBlockt == 0)
					{
						//発見音を１回のみにする
						StopSound(SOUND_LABEL_SE_FOUND);

						//アイテム「お金の袋」
						SetItem(D3DXVECTOR3(60, 660, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5);
					}
					g_nCntBlockt = 1;
					
					//透明ブロック
					//SetBlock(D3DXVECTOR3(40, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);
					
				}
				if (g_aBlock[nCntBlock].nType == 10)
				{//ブロックの下からあたった場合
					
				}
//***************************
				//プレイヤーのmove値を0にする
				pMove->y = 0.0f;
			}
			//横からぶつかる
			else if (pPos->y >= g_aBlock[nCntBlock].pos.y && (pPos->y - *fHeight) <= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight))
			{//横の当たり判定
				if (pPosOld->x >= pPos->x)
				{//右壁のあたり判定　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　 ↓めり込みを押し返す(プレイヤーの半分の横幅分)
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth + *fWidth / 2; //プレイヤーの位置(高さ)を更新

//****************************
//	いろいろ要素がある床
//****************************
					//タイプ１４　押すことができる床
					if (g_aBlock[nCntBlock].nType == 14)
					{//ブロックを右から押しているとき
						//押してる音
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x += 2;
					}
					//タイプ１５　押すことができる床
					if (g_aBlock[nCntBlock].nType == 15)
					{//ブロックを右から押しているとき
					 //押してる音
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x -= 2;
					}
					if (g_aBlock[nCntBlock].nType == 21)
					{
						HitPlayer(3);
					}
					if (g_aBlock[nCntBlock].nType == 22)
					{
						HitPlayer(3);
					}
//****************************
					//プレイヤーのmove値を0にする
					pMove->x = 0.0f;
				}
				else if (pPosOld->x < pPos->x)
				{//左壁のあたり判定　　　　　　　　　　　　　　　  ↓めり込みを押し返す(プレイヤーの半分の横幅分)
					pPos->x = g_aBlock[nCntBlock].pos.x - *fWidth / 2;	//プレイヤーの位置(高さ)を更新

//*****************************
// いろいろ要素がある床
//*****************************
					//タイプ７	押すことができる床
					if (g_aBlock[nCntBlock].nType == 7)
					{//ブロックを左から押しているとき
						//押してる時の音
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x += 2;
					}
					//タイプ１４　押すことができる偽床
					if (g_aBlock[nCntBlock].nType == 14)
					{//ブロックを右から押しているとき
					 //押してる音
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x -= 2;
					}
//******************************
					//プレイヤーのmove値を0にする
					pMove->x = 0.0f;
				}
			}
		}
	}
	return bLand;

	//頂点バッファをアンロック
	g_pVtxBuffBlock->Unlock();
}
//=========================================================================================================================
// ブロックの取得処理
//=========================================================================================================================
Block *GetBlock(void)
{
	return &g_aBlock[0];
}
//==========================================================================================================================
//ブロックの初期化
//==========================================================================================================================
void DeleteBlock(void)
{
	//ブロックの情報の初期化
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//初期値
		if (g_aBlock[nCntBlock].bUse == true)
		{//trueだったら
			g_aBlock[nCntBlock].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			g_aBlock[nCntBlock].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].bUse = false;
			g_aBlock[nCntBlock].nType = 0;
			g_aBlock[nCntBlock].BlockWidth = 0;
			g_aBlock[nCntBlock].BlockHeight = 0;
		}
	}
}