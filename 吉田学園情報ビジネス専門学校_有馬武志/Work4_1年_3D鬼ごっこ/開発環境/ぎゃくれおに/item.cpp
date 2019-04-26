//-----------------------------------------------------------------------------
//
//アイテムの処理[item.cpp]
//Author : 有馬武志　＆　加藤　＆　箱崎
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "item.h"
#include "bullet.h"

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define TEXTURE_NAME  "data/TEXTURE/ガソリン.png"	//読み込むテクスチャの名前
#define MAX_ITEM	  (256)							//アイテムの最大数
#define ITEM_WIDTH    (30.0f)						//アイテムの幅
#define ITEM_HEIGHT	  (30.0f)						//アイテムの高さ
#define ITEM_U		  (1.0f)						//テクスチャU範囲
#define ITEM_V		  (1.0f)						//テクスチャV範囲

//-----------------------------------------------------------------------------
//プロトタイプ宣言
//-----------------------------------------------------------------------------
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice); //頂点作成

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTextureItem		= NULL; //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem		= NULL; //頂点バッファへのポインタ
Item					g_aItem[MAX_ITEM];			//アイテムの向き
int						g_nItem;					//アイテムの個数
int						g_nPlayerPossession = 0;	//プレイヤーの所持数

//-----------------------------------------------------------------------------
//アイテムの初期化処理
//-----------------------------------------------------------------------------
void InitItem(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得

	// 頂点情報の作成
	MakeVertexItem(pDevice);
}

//-----------------------------------------------------------------------------
//アイテムの終了処理
//-----------------------------------------------------------------------------
void UninitItem(void)
{
	//テクスチャーの破棄
	if (g_pTextureItem != NULL)
	{
		g_pTextureItem->Release();
		g_pTextureItem = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//-----------------------------------------------------------------------------
//アイテムの更新処理
//-----------------------------------------------------------------------------
void UpdateItem(void)
{
	//ローカル変数宣言
	Player	  g_player = *GetPlayer(); //プレイヤーの取得
	Bullet *pBullet = GetBullet();
	VERTEX_3D *pVtx;				   //頂点情報へのポインタ
	int		  nCntItem;				   //アイテムのカウント

	//頂点バッファをロック
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntBullet = 0; nCntBullet < 100; nCntBullet++)
	{
		for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
		{//位置の更新
			if (pBullet[nCntBullet].bUse == true)
			{
				if (g_aItem[nCntItem].bUse == true)
				{//アイテムが使用されている
					switch (g_aItem[nCntItem].state)
					{
					case ITEM_GASOLINE:					  //コインの場合
						//アイテムのあたり判定
						if (g_nPlayerPossession == 0 &&
							pBullet[nCntBullet].posBullet.z < g_aItem[nCntItem].pos.z + g_aItem[nCntItem].fHeight && pBullet[nCntBullet].posBullet.z > g_aItem[nCntItem].pos.z &&
							pBullet[nCntBullet].posBullet.x > g_aItem[nCntItem].pos.x && pBullet[nCntBullet].posBullet.x < g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth &&
							pBullet[nCntBullet].posBullet.y > g_aItem[nCntItem].pos.y && pBullet[nCntBullet].posBullet.y < g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fWidth)
						{//アイテムを所持していないプレイヤーがアイテムの範囲内
							g_aItem[nCntItem].bUse = false;				//使用していない状態に変更
							DeleteShadow(g_aItem[nCntItem].nIdxShadow); //影を消去
							g_nItem--;									//アイテムの個数を減少
							g_nPlayerPossession++;						//プレイヤーがアイテムを取得

							//if (g_nItem <= 0)
							//{//個数がなくなったら
							//	SetFade(MODE_RESULT); //結果画面へ遷移
							//}
						}
						break;
					}

					//影の位置更新
					SetPositionShadow(g_aItem[nCntItem].nIdxShadow, g_aItem[nCntItem].pos, g_aItem[nCntItem].rot);
				}
			}
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}

//-----------------------------------------------------------------------------
//アイテムの描画処理
//-----------------------------------------------------------------------------
void DrawItem(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
	D3DXMATRIX		  mtxView, mtxTrans;	 //計算用マトリックス
	int				  nCntItem;				 //カウント

	//アルファテスト処理
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);	  //アルファテスト処理を有効にする
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);				  //条件の比較対象・基準値			0←透明色
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); //テストの条件・比較方法

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aItem[nCntItem].mtxWorld);

		//アイテムを反映
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		g_aItem[nCntItem].mtxWorld._11 = mtxView._11; //カメラの逆行列を設定
		g_aItem[nCntItem].mtxWorld._12 = mtxView._21;
		g_aItem[nCntItem].mtxWorld._13 = mtxView._31;
		g_aItem[nCntItem].mtxWorld._21 = mtxView._12;
		g_aItem[nCntItem].mtxWorld._22 = mtxView._22;
		g_aItem[nCntItem].mtxWorld._23 = mtxView._32;
		g_aItem[nCntItem].mtxWorld._31 = mtxView._13;
		g_aItem[nCntItem].mtxWorld._32 = mtxView._23;
		g_aItem[nCntItem].mtxWorld._33 = mtxView._33;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, g_aItem[nCntItem].pos.z); //x,y,zの順
		D3DXMatrixMultiply(&g_aItem[nCntItem].mtxWorld, &g_aItem[nCntItem].mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aItem[nCntItem].mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureItem);

		//アイテムの描画
		if (g_aItem[nCntItem].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}

	//アルファテスト処理(元に戻す)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//-----------------------------------------------------------------------------
//アイテムの設定
//-----------------------------------------------------------------------------
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEMSTATE state, int nItemPossession)
{
	//ローカル変数宣言
	int nCntItem; //カウント

	g_nPlayerPossession = nItemPossession; //受け取る

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].bUse		 = true;													//使用している状態にする
			g_aItem[nCntItem].pos		 = pos;														//pos値代入
			g_aItem[nCntItem].rot		 = rot;														//rot値を代入
			g_aItem[nCntItem].state		 = state;													//アイテムの種類
			g_nItem++;																				//アイテムの個数をカウント

			break;
		}
	}
}

//-----------------------------------------------------------------------------
//頂点情報の作成
//-----------------------------------------------------------------------------
void MakeVertexItem(LPDIRECT3DDEVICE9 pDevice)
{
	//ローカル変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	int		  nCntItem; //カウント

	g_nItem = 0; //アイテム個数の初期化

	//アイテムの情報の初期化
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f); //アイテムの中心初期座標
		g_aItem[nCntItem].rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f); //アイテムの向き
		g_aItem[nCntItem].bUse				= false;						 //使用していない
		g_aItem[nCntItem].state				= ITEM_GASOLINE;				 //アイテムの状態(種類)
		g_aItem[nCntItem].fWidth			= ITEM_WIDTH;					 //アイテムの幅
		g_aItem[nCntItem].fHeight			= ITEM_HEIGHT;					 //アイテムの高さ
		g_aItem[nCntItem].nIdxShadow		= 0;							 //影の番号
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureItem);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_ITEM,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffItem,
								NULL);

	//頂点バッファをロック
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	//配置
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-5.0f, ITEM_HEIGHT, 0);
		pVtx[1].pos = D3DXVECTOR3(ITEM_WIDTH, ITEM_HEIGHT, 0);
		pVtx[2].pos = D3DXVECTOR3(-5.0f, 0.0f, 0);
		pVtx[3].pos = D3DXVECTOR3(ITEM_WIDTH, 0.0f, 0);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4; //頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffItem->Unlock();
}

//-------------------------------------------------------------------------------------------------------------------------
//アイテムの取得処理
//-------------------------------------------------------------------------------------------------------------------------
Item *GetItem(void)
{
	return &g_aItem[0];
}

//-------------------------------------------------------------------------------------------------------------------------
//アイテムの取得(所持数)処理
//-------------------------------------------------------------------------------------------------------------------------
int *GetItemPossession(void)
{
	return &g_nPlayerPossession;
}