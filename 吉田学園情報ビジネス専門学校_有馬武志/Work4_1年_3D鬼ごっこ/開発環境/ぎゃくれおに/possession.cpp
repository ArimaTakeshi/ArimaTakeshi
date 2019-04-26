//-----------------------------------------------------------------------------
//
//所有物の処理[possession.cpp]
//Author : 有馬武志　＆　加藤
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "possession.h"
#include "length.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define	TEXTURE_POSSESSION  "data/TEXTURE/frame_Item.png" //読み込むテクスチャファイル名
#define	TEXTURE_POSSESSION2 "data/TEXTURE/ガソリン.png"	  //読み込むテクスチャファイル名
#define POSSESSION_SIZE		(70)						  //所有物の横幅(テクスチャの数字)
#define	GASORIN_X			(50)
#define MAX_TEXTURE			(2)							  //テクスチャの最大数
#define MAX_ITEM			(256)						  //アイテムの最大数(GetItem用)

//-----------------------------------------------------------------------------
//グローバル変数宣言
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTexturePossession[MAX_TEXTURE] = {};   //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPossession			  = NULL; //頂点バッファへのポインタ
int						g_nPossession;							  //所有物のの数値
D3DXVECTOR3				g_posPossession;						  //所有物のの中心座標
D3DXVECTOR3				g_posFramePossession;					  //フレームの中心座標

//-----------------------------------------------------------------------------
//所有物の初期化処理
//-----------------------------------------------------------------------------
void InitPossession(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
	int				  nCntPossession;		 //所有物のカウント
	VERTEX_2D		  *pVtx;				 //頂点情報を設定

	//所有物の初期化
	g_posPossession		 = D3DXVECTOR3(150, SCREEN_HEIGHT - 90, 0.0f);  //所有物の初期座標
	g_posFramePossession = D3DXVECTOR3(150, SCREEN_HEIGHT - 100, 0.0f); //フレームの初期座標

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice, 
		TEXTURE_POSSESSION, 
		&g_pTexturePossession[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice, 
		TEXTURE_POSSESSION2,
		&g_pTexturePossession[1]
	);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPossession,
								NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPossession->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPossession = 0; nCntPossession < MAX_TEXTURE; nCntPossession++)
	{
		if (nCntPossession == 0)
		{
			//フレームの頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_posFramePossession.x - (POSSESSION_SIZE + 70), g_posFramePossession.y - (POSSESSION_SIZE + 20), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posFramePossession.x + (POSSESSION_SIZE + 70), g_posFramePossession.y - (POSSESSION_SIZE + 20), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posFramePossession.x - (POSSESSION_SIZE + 70), g_posFramePossession.y + (POSSESSION_SIZE + 20), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posFramePossession.x + (POSSESSION_SIZE + 70), g_posFramePossession.y + (POSSESSION_SIZE + 20), 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if(nCntPossession == 1)
		{
			//数字の頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_posPossession.x - GASORIN_X, g_posPossession.y - GASORIN_X, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posPossession.x + GASORIN_X, g_posPossession.y - GASORIN_X, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posPossession.x - GASORIN_X, g_posPossession.y + GASORIN_X, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posPossession.x + GASORIN_X, g_posPossession.y + GASORIN_X, 0.0f);

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
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//所有物のの桁の幅
			g_posPossession.x += 50;
		}

		pVtx += 4; //頂点データのポインタを4つ進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPossession->Unlock();
}

//-----------------------------------------------------------------------------
//所有物の終了処理
//-----------------------------------------------------------------------------
void UninitPossession(void)
{
	//ローカル変数宣言
	int nCntPossession; //カウント

	//テクスチャの破棄
	for (nCntPossession = 0; nCntPossession < MAX_TEXTURE; nCntPossession++)
	{
		if (g_pTexturePossession[nCntPossession] != NULL)
		{
			g_pTexturePossession[nCntPossession]->Release();
			g_pTexturePossession[nCntPossession] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPossession != NULL)
	{
		g_pVtxBuffPossession->Release();
		g_pVtxBuffPossession = NULL;
	}
}

//-----------------------------------------------------------------------------
//所有物の更新処理
//-----------------------------------------------------------------------------
void UpdatePossession(void)
{
	//ローカル変数宣言
	int	   pItemPossession	= *GetItemPossession(); //プレイヤーの所持数を取得
	Player pPlayer = *GetPlayer();					//プレイヤーの情報を所得
	Item   pItem = *GetItem();

	if (pItemPossession == 1 && GetKeyboardTrigger(DIK_E) == true)
	{
		pItemPossession = 0;
		SetItem(D3DXVECTOR3(pPlayer.pos.x, 0.0f, pPlayer.pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEM_GASOLINE, pItemPossession);
		AddLength(10, LengthTex_HIL);
	}
}

//-----------------------------------------------------------------------------
//所有物の描画処理
//-----------------------------------------------------------------------------
void DrawPossession(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice		  = GetDevice();		  //デバイスの取得
	int				  nCntPossession;						  //所有物のカウント
	int				  pItemPossession = *GetItemPossession(); //

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPossession, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPossession = 0; nCntPossession < MAX_TEXTURE; nCntPossession++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePossession[nCntPossession]);

		//テクスチャの描画
		if (nCntPossession == 0)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPossession, 2);
		}
		else if (nCntPossession == 1 && pItemPossession == 1)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPossession, 2);
		}
	}
}