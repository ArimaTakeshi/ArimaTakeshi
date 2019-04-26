//-----------------------------------------------------------------------------
//
//所有物の処理[frame.cpp]
//Author : 有馬武志
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "frame.h"
#include "camera.h"
#include "game.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define	TEXTURE_FRAME1 "data/TEXTURE/bunkatu.png"		//読み込むテクスチャファイル名
#define	TEXTURE_FRAME2 "data/TEXTURE/日出まで.png"		//読み込むテクスチャファイル名
#define FRAME_SIZE_X	(640)							//枠の横幅
#define FRAME_SIZE_Y	(360)							//枠の縦幅
#define HINODE_SIZE_X	(95)							//枠の横幅
#define HINODE_SIZE_Y	(65)							//枠の縦幅
#define MAX_TEXTURE		(2)								//テクスチャの最大数

//-----------------------------------------------------------------------------
//グローバル変数宣言
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTextureFrame[MAX_TEXTURE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;					//頂点バッファへのポインタ
int						g_nFrame;								//枠の数値
D3DXVECTOR3				g_posFrame;								//フレームの中心座標
D3DXVECTOR3				g_posHinode;							//日出の中心座標

//-----------------------------------------------------------------------------
//所有物の初期化処理
//-----------------------------------------------------------------------------
void InitFrame(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	Camera pCamera = *GetCamera();				//カメラのデバイスの取得						
	MODE pMode = *GetMode();					//モードのポインタ
	int				  nCntFrame;				//所有物のカウント
	VERTEX_2D		  *pVtx;					//頂点情報を設定

	//所有物の初期化
	g_posFrame = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);		//枠の初期座標
	g_posHinode = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 -24, 0.0f);		//枠の初期座標

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//枠
		pDevice,
		TEXTURE_FRAME1,
		&g_pTextureFrame[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//日出
		pDevice,
		TEXTURE_FRAME2,
		&g_pTextureFrame[1]
	);


	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		if (pMode != MODE_TITLE)
		{
			if (nCntFrame == 0)
			{//枠
			 //枠の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posFrame.x - (FRAME_SIZE_X), g_posFrame.y - (FRAME_SIZE_Y), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posFrame.x + (FRAME_SIZE_X), g_posFrame.y - (FRAME_SIZE_Y), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posFrame.x - (FRAME_SIZE_X), g_posFrame.y + (FRAME_SIZE_Y), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posFrame.x + (FRAME_SIZE_X), g_posFrame.y + (FRAME_SIZE_Y), 0.0f);

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
			else if (nCntFrame == 1)
			{//枠
			 //枠の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posHinode.x - (HINODE_SIZE_X), g_posHinode.y - (HINODE_SIZE_Y), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posHinode.x + (HINODE_SIZE_X), g_posHinode.y - (HINODE_SIZE_Y), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posHinode.x - (HINODE_SIZE_X), g_posHinode.y + (HINODE_SIZE_Y), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posHinode.x + (HINODE_SIZE_X), g_posHinode.y + (HINODE_SIZE_Y), 0.0f);

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
		}
		pVtx += 4; //頂点データのポインタを4つ進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffFrame->Unlock();
}

//-----------------------------------------------------------------------------
//所有物の終了処理
//-----------------------------------------------------------------------------
void UninitFrame(void)
{
	//ローカル変数宣言
	int nCntFrame; //カウント

				   //テクスチャの破棄
	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//-----------------------------------------------------------------------------
//所有物の更新処理
//-----------------------------------------------------------------------------
void UpdateFrame(void)
{

}

//-----------------------------------------------------------------------------
//所有物の描画処理
//-----------------------------------------------------------------------------
void DrawFrame(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	MODE pMode = *GetMode();
	int	nCntFrame;						//所有物のカウント

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureFrame[nCntFrame]);

		//テクスチャの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntFrame, 2);
	}
}