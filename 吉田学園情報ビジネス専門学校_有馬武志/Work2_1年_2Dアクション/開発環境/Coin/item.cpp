//=========================================================================================================================
//
// アイテム処理 [items.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "item.h"		//アイテム
#include "score.h"		//スコア
#include "player.h"		//プレイヤー
#include "fade.h"		//フェード
#include "itemcount.h"	//アイテムカウント
#include "time.h"		//タイム
#include "sound.h"		//サウンド
#include "Game.h"		//ゲーム
#include "player.h"		//プレイヤー
#include "life.h"		//ライフ
#include "explosion.h"	//爆発
#include "input.h"		//キーボード
#include "Game.h"		//ゲーム

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_ITEM					(256)								//アイテムの最大数
#define MAX_ITEM_TYPE				(10)								//タイプの種類
#define ITEM_TEXTURE_NAME			"data\\TEXTURE\\coin001.png"		//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME1			"data\\TEXTURE\\磁石.png"			//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME2			"data\\TEXTURE\\時計1.png"			//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME3			"data\\TEXTURE\\空いた宝箱.png"		//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME4			"data\\TEXTURE\\お金の袋.png"		//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME5			"data\\TEXTURE\\枠付きコイン.png"	//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME6			"data\\TEXTURE\\骨付き肉.png"		//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME7			"data\\TEXTURE\\ゲート2.png"		//読み込むテクスチャファイル
#define ITEM_TEXTURE_NAME8			"data\\TEXTURE\\SHOP.png"			//読み込むテクスチャファイル
#define ITEM_COIN_WID				(20)								//コインの幅
#define ITEM_COIN_HEI				(35)								//コインの高さ
#define ITEM_MAGNET_WID				(25)								//磁石の幅
#define ITEM_MAGNET_HEI				(25)								//磁石の幅
#define ITEM_GATE_WID				(30)								//ゲートの幅
#define ITEM_GATE_HEI				(50)								//ゲートの高さ
#define ITEM_SHOP_WID				(100)								//ショップの幅
#define ITEM_SHOP_HEI				(100)								//ショップの高さ
#define ITEM_TIME_WID				(30)								//タイムの幅
#define ITEM_TIME_HEI				(30)								//タイムの幅
#define ITEM_TEXTURE_SPEED			(10)								//テクスチャアニメーションスピード
#define ITEM_TEXTURE_SPEED1			(20)								//テクスチャアニメーションスピード
#define ITEM_TEXTURE_SPEED2			(40)								//テクスチャアニメーションスピード
#define ITEM_TEXTURE_PATTERN		(4)									//テクスチャアニメーションパターン数
#define ITEM_TEXTURE_UV_U			(0.25f)								//テクスチャアニメーションU範囲
#define ITEM_TEXTURE_UV_V			(1.0f)								//テクスチャアニメーションV範囲
#define ITEM_TEXTURE_UV_U1			(1.0f)								//テクスチャアニメーションU範囲
#define ITEM_TEXTURE_UV_V1			(1.0f)								//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_ITEM_TYPE] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;				//頂点バッファへのポインタ
Item					g_aItem[MAX_ITEM];					//アイテムの情報
int						g_NumItem;							//ナムカウント用

//=========================================================================================================================
// アイテム初期化処理
//=========================================================================================================================
void InitItem(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;	

	//アイテムカウント
	int nCntItem;					
	
	//デバイスの取得
	pDevice = GetDevice();

	//アイテムの情報の初期化
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//アイテムをカウント
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].fHeight = 0;
		g_aItem[nCntItem].fWidth = 0;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatteunAnim = 0;
		g_aItem[nCntItem].ItemState = ITEM_STATE_APPER;
		g_aItem[nCntItem].bUse = false;
		g_NumItem = 0;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//1枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME,
		&g_pTextureItem[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//2枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME1,
		&g_pTextureItem[1]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//3枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME,
		&g_pTextureItem[2]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//4枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME2,
		&g_pTextureItem[3]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//5枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME3,
		&g_pTextureItem[4]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//6枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME4,
		&g_pTextureItem[5]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//7枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME5,
		&g_pTextureItem[6]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//8枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME6,
		&g_pTextureItem[7]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//9枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME7,
		&g_pTextureItem[8]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//10枚目の画像
		pDevice,
		ITEM_TEXTURE_NAME8,
		&g_pTextureItem[9]
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;	

	//頂点バッファをロック
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//アイテムの情報の初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//アイテムをカウント

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================================
// アイテム終了処理
//=========================================================================================================================
void UninitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM_TYPE; nCntItem++)
	{//アイテムをカウント
		//テクスチャーの破棄
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem] ->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem ->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=========================================================================================================================
// アイテム更新処理
//=========================================================================================================================
void UpdateItem(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;	

	//アイテムカウント
	int nCntItem;
	//カウントと初期化
	int nCount = 0;

	//プレイヤーのポインタ
	Player *pPlayer;
	pPlayer = GetPlayer();//ポインターの使い方を間違っていたので、修正。　pPlayerのまえに＊をつける

	// デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//アイテムをカウント
		if (g_aItem[nCntItem].bUse == true)
		{//アイテムが使用されている場合

			switch (g_aItem[nCntItem].ItemState)
			{
			case ITEM_STATE_APPER:
				break;
			case ITEM_STATE_NORMAL:
				//タイプ０====================================================================================
				if (g_aItem[nCntItem].nType == 0)
				{//タイプ０　普通のコイン
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0 && g_aItem[nCntItem].nType == 0)
					{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//パターンNo.更新
						//頂点設定
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						//頂点カラー設定
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//テクスチャ設定
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				/*	case ITEM_MAGNET:*/
				//タイプ１====================================================================================
				if (g_aItem[nCntItem].nType == 1)
				{//タイプ１　磁石
				 //頂点設定
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					//頂点カラー設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//テクスチャ設定
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);

				}
				//タイプ２====================================================================================
				if (g_aItem[nCntItem].nType == 2)
				{//タイプ２　赤コイン
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0 && g_aItem[nCntItem].nType == 2)
					{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//パターンNo.更新

																															//頂点設定
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						//頂点カラー設定
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//テクスチャ設定
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);

					}
				}
				//タイプ３====================================================================================
				if (g_aItem[nCntItem].nType == 3)
				{//タイプ３　時計
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED1) == 0 && g_aItem[nCntItem].nType == 3)
					{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//パターンNo.更新
																															//頂点設定
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						//頂点カラー設定
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//テクスチャ設定
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				//タイプ４====================================================================================
				if (g_aItem[nCntItem].nType == 4)
				{//タイプ4   宝箱
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED2) == 0 && g_aItem[nCntItem].nType == 4)
					{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % 2;		//パターンNo.更新
																										//頂点設定
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						//頂点カラー設定
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//テクスチャ設定
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim + 0.5f, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim + 0.5f, ITEM_TEXTURE_UV_V);
					}
					if (pPlayer->pos.y - pPlayer->PlayerHeight < g_aItem[nCntItem].pos.y && pPlayer->pos.y + pPlayer->PlayerHeight > g_aItem[nCntItem].pos.y && pPlayer->pos.x + pPlayer->PlayerWidth > g_aItem[nCntItem].pos.x && pPlayer->pos.x - pPlayer->PlayerWidth < g_aItem[nCntItem].pos.x)
					{//宝箱をとったらのあたり判定
					 //宝箱をとったらfalseにする
						g_aItem[nCntItem].bUse = false;		//使用していない状態
					}
				}
				//タイプ５====================================================================================
				if (g_aItem[nCntItem].nType == 5)
				{//タイプ5　お金の袋
				 //頂点設定
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					//頂点カラー設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//テクスチャ設定
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);
				}
				//タイプ６====================================================================================
				if (g_aItem[nCntItem].nType == 6)
				{//タイプ７　模型のコイン
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED1) == 0 && g_aItem[nCntItem].nType == 6)
					{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//パターンNo.更新
																															//頂点設定
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						//頂点カラー設定
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//テクスチャ設定
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				//タイプ７====================================================================================
				if (g_aItem[nCntItem].nType == 7)
				{//タイプ７　骨付き肉
				 //頂点設定
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					//頂点カラー設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//テクスチャ設定
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);
				}
				//タイプ８====================================================================================
				if (g_aItem[nCntItem].nType == 8)
				{//タイプ８　
				 //頂点設定
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0 && g_aItem[nCntItem].nType == 8)
					{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//パターンNo.更新
																															//頂点設定
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_GATE_WID, g_aItem[nCntItem].pos.y - ITEM_GATE_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_GATE_WID, g_aItem[nCntItem].pos.y - ITEM_GATE_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_GATE_WID, g_aItem[nCntItem].pos.y + ITEM_GATE_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_GATE_WID, g_aItem[nCntItem].pos.y + ITEM_GATE_HEI, 0.0f);
						//頂点カラー設定
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//テクスチャ設定
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				//タイプ９====================================================================================
				if (g_aItem[nCntItem].nType == 9)
				{//タイプ9　SHOP
					//頂点設定
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_SHOP_WID, g_aItem[nCntItem].pos.y - ITEM_SHOP_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_SHOP_WID, g_aItem[nCntItem].pos.y - ITEM_SHOP_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_SHOP_WID, g_aItem[nCntItem].pos.y + ITEM_SHOP_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_SHOP_WID, g_aItem[nCntItem].pos.y + ITEM_SHOP_HEI, 0.0f);
					//頂点カラー設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//テクスチャ設定
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);
				}
				break;
			case ITEM_STATE_DELETE:			
				break;
			}
			//カウンター加算
			g_aItem[nCntItem].nCounterAnim++;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================================
// アイテム描画処理
//=========================================================================================================================
void DrawItem(void)
{	
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//アイテムカウント
	int nCntItem;				

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffItem,
		0, 
		sizeof(VERTEX_2D)
	);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for(nCntItem = 0; nCntItem< MAX_ITEM; nCntItem++)
	{//アイテムをカウント

		if (g_aItem[nCntItem].bUse == true)
		{//アイテムがある場合
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);
		
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//=========================================================================================================================
// アイテムの設定処理
//=========================================================================================================================
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col, int nType)
{
	//アイテムカウント
	int nCntItem;			

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;			

	//頂点バッファをロック
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntItem = 0; nCntItem< MAX_ITEM; nCntItem++)
	{//アイテムをカウント
		if (g_aItem[nCntItem].bUse == false)
		{//アイテムが使用されていない
			g_aItem[nCntItem].pos = pos;		//pos値代入
			g_aItem[nCntItem].col = col;		//move値代入
			g_aItem[nCntItem].nCounterAnim = 0;	//カウンター初期値設定
			g_aItem[nCntItem].nPatteunAnim = 0;	//パターンNo.初期値設定
			g_aItem[nCntItem].ItemState = ITEM_STATE_NORMAL;
			g_aItem[nCntItem].nType = nType;	//タイプ
			g_aItem[nCntItem].bUse = true;		//使用している状態にする

			//頂点カラー設定
			pVtx[nCntItem * 4].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);
			pVtx[nCntItem * 4 + 1].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);
			pVtx[nCntItem * 4 + 2].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);
			pVtx[nCntItem * 4 + 3].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);

			if (g_aItem[nCntItem].nType != 8 && g_aItem[nCntItem].nType != 9)
			{
				g_aItem[nCntItem].fHeight = ITEM_COIN_HEI;
				g_aItem[nCntItem].fWidth = ITEM_COIN_WID;
				if (g_aItem[nCntItem].nType == 0)
				{//普通のコイン
					//爆発
					//SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_NumItem++;
				}
				if (g_aItem[nCntItem].nType == 2)
				{//赤いコイン
					
					g_NumItem++;
				}
			}
			if (g_aItem[nCntItem].nType == 8)
			{
				g_aItem[nCntItem].fHeight = ITEM_GATE_HEI;
				g_aItem[nCntItem].fWidth = ITEM_GATE_WID;
			}
			else if (g_aItem[nCntItem].nType == 9)
			{
				g_aItem[nCntItem].fHeight = ITEM_SHOP_HEI;
				g_aItem[nCntItem].fWidth = ITEM_SHOP_WID;
			}
			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}
//=========================================================================================================================
// 消すアイテム
//=========================================================================================================================
void DeleteItem(int nCntItem)
{
	//変数宣言
	int nCount = 0;

	//プレイヤーのポインタ
	Player *pPlayer = GetPlayer();

	//タイマーのポインタ
	Time *pTime= GetTime();

	STAGENUM pStageNum = GetNumState();

	if (g_aItem[nCntItem].nType != 8 && g_aItem[nCntItem].nType != 6 && g_aItem[nCntItem].nType != 9)
	{	
		//使用していない状態
		g_aItem[nCntItem].bUse = false;		

		if (g_aItem[nCntItem].nType == 0)
		{//タイプ０　コイン
			//コインをとる音
			PlaySound(SOUND_LABEL_SE_GETCOIN);
			//コインのスコア
			AddScore(1000, SCORE_COIN);
			//コインの枚数
			AddItemCount(1);
			//とったら枚数を減らしていく
			g_NumItem--;

			SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//g_aItem[g_aItem[nCount].nType == 2].bUse = false;

			//コインを全部取ったら
			if (g_NumItem <= 0)
			{
				if ((nCount % 180) == 0)
				{//クリア画面に行く時間　約３秒
					if (pStageNum == STAGENUM_1)
					{
						SetNumGame(STAGENUM_2);
					}
					else if (pStageNum == STAGENUM_2)
					{
						SetNumGame(STAGENUM_3);
					}
					else if (pStageNum == STAGENUM_3)
					{
						SetNumGame(STAGENUM_4);
					}
					else if (pStageNum == STAGENUM_4)
					{
						SetNumGame(STAGENUM_5);
					}
					else if (pStageNum == STAGENUM_5)
					{
						SetNumGame(STAGENUM_6);
						//SetGameState(GAMESTATE_CLEAR);
					}
					else if (pStageNum == STAGENUM_6)
					{
						SetGameState(GAMESTATE_CLEAR);
					}
				}
			}
		}
		else if (g_aItem[nCntItem].nType == 1)
		{//タイプ１　磁石
			//磁石をとったらfalseにする
			g_aItem[nCntItem].bUse = false;		//使用していない状態
		}
		else if (g_aItem[nCntItem].nType == 2)
		{//タイプ２　赤コイン
			//赤コインをとった時の音
			PlaySound(SOUND_LABEL_SE_GETMONEY);
			//コインのスコア
			AddScore(3000,SCORE_COIN);
			//コインの枚数
			AddItemCount(3);
			//とったら枚数を減らしていく
			g_NumItem--;
			//爆発
			SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//コインを全部取ったら
			if (g_NumItem <= 0)
			{
				if ((nCount % 180) == 0)
				{//クリア画面に行く時間　約３秒
					if (pStageNum == STAGENUM_1)
					{
						SetNumGame(STAGENUM_2);
					}
					else if (pStageNum == STAGENUM_2)
					{
						SetNumGame(STAGENUM_3);
					}
					else if (pStageNum == STAGENUM_3)
					{
						SetNumGame(STAGENUM_4);
					}
					else if (pStageNum == STAGENUM_4)
					{
						SetNumGame(STAGENUM_5);
					}
					else if (pStageNum == STAGENUM_5)
					{
						SetNumGame(STAGENUM_6);
						//SetGameState(GAMESTATE_CLEAR);
					}
					else if (pStageNum == STAGENUM_6)
					{
						SetGameState(GAMESTATE_CLEAR);
					}
				}
			}
		}
		else if (g_aItem[nCntItem].nType == 3)
		{//タイプ３　時計
			//時計をとる音
			PlaySound(SOUND_LABEL_SE_TIME);
			//得点の減点
			AddScore(-5000,SCORE_TIMER);
			//コインの枚数を得点分引く
			AddItemCount(-5);
			//タイムを増加
			pTime->nTime += 1000;
		}
		else if (g_aItem[nCntItem].nType == 4)
		{//タイプ４　宝箱
		}
		else if (g_aItem[nCntItem].nType == 5)
		{//タイプ５　お金の袋
			//お金の袋をとった時の音
			PlaySound(SOUND_LABEL_SE_GETMONEY);
			//お金の袋のスコア
			AddScore(10000,SCORE_MENIYBOX);
		}
		else if (g_aItem[nCntItem].nType == 7)
		{//タイプ７　骨付き肉
			//骨付き肉をとったらのあたり判定
			if (pPlayer->nLife < 3)
			{
				pPlayer->nLife += 1;
				AddLife(1, LifeTex_HIL);
			}
		}
	}
	else if (g_aItem[nCntItem].nType == 6)
	{//見本
	}
	else if (g_aItem[nCntItem].nType == 8)
	{//ゲート
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//タイトルに戻る
			SetFadeMode(MODE_TITLE);
		}
	}
	else if (g_aItem[nCntItem].nType == 9)
	{//ショップ
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetMenuState(true);
			//ショップの曲
			PlaySound(SOUND_LABEL_BGM004);
		}
	
	}
}
//=========================================================================================================================
// アイテムのあたり判定
//=========================================================================================================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWidth, float *fHeight)
{
	//カウント
	int nCount = 0;
	//カウント
	int nCntItem;

	//プレイヤーのポインタ
	Player *pPlayer = GetPlayer();

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//アイテムをカウント
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPlayer->pos.y - pPlayer->PlayerHeight < g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight && pPlayer->pos.y > g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight  && pPlayer->pos.x + pPlayer->PlayerWidth  > g_aItem[nCntItem].pos.x /*- g_aItem[nCntItem].fWidth*/ && pPlayer->pos.x - pPlayer->PlayerWidth < g_aItem[nCntItem].pos.x /*+ g_aItem[nCntItem].fWidth*/)
			{//あたり判定
				DeleteItem(nCntItem);
			}
		}
	}
}
//=========================================================================================================================
// アイテムのあたり判定
//=========================================================================================================================
void DeleteItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//アイテムをカウント
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem[nCntItem].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aItem[nCntItem].fHeight = 0;
			g_aItem[nCntItem].fWidth = 0;
			g_aItem[nCntItem].nType = 0;
			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatteunAnim = 0;
			g_aItem[nCntItem].ItemState = ITEM_STATE_APPER;
			g_aItem[nCntItem].bUse = false;
		}
	}
	g_NumItem = 0;
}
