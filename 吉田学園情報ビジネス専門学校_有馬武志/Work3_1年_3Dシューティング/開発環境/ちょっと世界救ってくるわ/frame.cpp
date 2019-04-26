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
#include "score.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define	TEXTURE_FRAME1 "data/TEXTURE/枠.png"			//読み込むテクスチャファイル名
#define	TEXTURE_FRAME2 "data/TEXTURE/銃弾.png"			//読み込むテクスチャファイル名
#define	TEXTURE_FRAME3 "data/TEXTURE/クロスヘア.png"	//読み込むテクスチャファイル名
#define	TEXTURE_FRAME4 "data/TEXTURE/kill.png"			//読み込むテクスチャファイル名
#define	TEXTURE_FRAME5 "data/TEXTURE/time.png"			//読み込むテクスチャファイル名
#define	TEXTURE_FRAME6 "data/TEXTURE/エンジン枠.png"	//読み込むテクスチャファイル名
#define	TEXTURE_FRAME7 "data/TEXTURE/Engine.png"		//読み込むテクスチャファイル名
#define	TEXTURE_FRAME8 "data/TEXTURE/zonnbi1.png"		//読み込むテクスチャファイル名
#define	TEXTURE_FRAME9 "data/TEXTURE/zonnbi2.png"		//読み込むテクスチャファイル名
#define	TEXTURE_FRAME10 "data/TEXTURE/tumeato.png"		//読み込むテクスチャファイル名
#define FRAME_SIZE_X	(1280)							//枠の横幅
#define FRAME_SIZE_Y	(70)							//枠の縦幅
#define BULE_SIZE		(70)							//銃弾横幅
#define XHER_SIZE		(50)							//クロスヘア
#define KILL_SIZE_X		(50)							//キルの横幅
#define KILL_SIZE_Y		(30)							//キルの縦幅
#define TIME_SIZE_X		(50)							//時間の横幅
#define TIME_SIZE_Y		(30)							//時間の縦幅
#define TIME_ENGINE_FRAME_X		(440)					//エンジンの枠の横幅
#define TIME_ENGINE_FRAME_Y		(30)					//エンジンの枠の縦幅
#define TIME_ENGINE_X	(70)							//エンジンの横幅
#define TIME_ENGINE_Y	(30)							//エンジンの縦幅
#define KILL_100_X		(70)							//killの横幅
#define KILL_100_Y		(30)							//killの縦幅
#define ZONNBI1_X		(120)							//zonbi1の横幅
#define ZONNBI1_Y		(250)							//zonbi1の縦幅
#define ZONNBI2_X		(100)							//zonbi1の横幅
#define ZONNBI2_Y		(250)							//zonbi1の縦幅
#define TUMEATO_X		(200)							//tumeatoの横幅
#define TUMEATO_Y		(240)							//tumeatoの縦幅
#define TIZU_X			(100)							//市街地の横幅
#define TIZU_Y			(100)							//市街地の縦幅
#define MAX_TEXTURE		(10)							//テクスチャの最大数

//-----------------------------------------------------------------------------
//グローバル変数宣言
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTextureFrame[MAX_TEXTURE] = {};		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame			  = NULL;		//頂点バッファへのポインタ
int						g_nFrame;								//枠の数値
D3DXVECTOR3				g_posBulletCount;						//弾の中心座標
D3DXVECTOR3				g_posFrame;								//フレームの中心座標
D3DXVECTOR3				g_posXher;								//クロスヘアの中心座標
D3DXVECTOR3				g_posKill;								//キルの中心座標
D3DXVECTOR3				g_posTime;								//タイムの中心座標
D3DXVECTOR3				g_posEngineFrame;						//エンジンの枠の中心座標
D3DXVECTOR3				g_posEngine;							//エンジンの中心座標
D3DXVECTOR3				g_pos100kill;
D3DXVECTOR3				g_posZonnbi1;
D3DXVECTOR3				g_posZonnbi2;
D3DXVECTOR3				g_posTumeato;
float					g_Xhetrot;

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
	Score *pScore = GetScore();

	//所有物の初期化
	g_posBulletCount = D3DXVECTOR3(1160, SCREEN_HEIGHT - 90, 0.0f);				//弾の初期座標
	g_posFrame = D3DXVECTOR3(0, 5, 0.0f);										//枠の初期座標
	g_posKill = D3DXVECTOR3(1000, 35, 0.0f);									//キル数の初期座標
	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, 35, 0.0f);					//時間数の初期座標
	g_posEngineFrame = D3DXVECTOR3(460, 35, 0.0f);								//エンジンの枠の初期座標
	g_posEngine = D3DXVECTOR3(90, 35, 0.0f);									//エンジンの初期座標
	g_posZonnbi1 = D3DXVECTOR3(150, 400, 0.0f);
	g_posZonnbi2 = D3DXVECTOR3(1100, 400, 0.0f);
	g_posTumeato = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60, 0.0f);
	//g_posTizu = D3DXVECTOR3(120, 600, 0.0f);
	g_Xhetrot = 0.0f;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//枠
		pDevice,
		TEXTURE_FRAME1,
		&g_pTextureFrame[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//銃弾
		pDevice,
		TEXTURE_FRAME2,
		&g_pTextureFrame[1]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//クロスヘア
		pDevice,
		TEXTURE_FRAME3,
		&g_pTextureFrame[2]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//キル
		pDevice,
		TEXTURE_FRAME4,
		&g_pTextureFrame[3]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//時間
		pDevice,
		TEXTURE_FRAME5,
		&g_pTextureFrame[4]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//エンジンの枠
		pDevice,
		TEXTURE_FRAME6,
		&g_pTextureFrame[5]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//エンジン
		pDevice,
		TEXTURE_FRAME7,
		&g_pTextureFrame[6]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//zonnbi1
		pDevice,
		TEXTURE_FRAME8,
		&g_pTextureFrame[7]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//zonnbi2
		pDevice,
		TEXTURE_FRAME9,
		&g_pTextureFrame[8]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//tumeato
		pDevice,
		TEXTURE_FRAME10,
		&g_pTextureFrame[9]
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
			{//弾
				//弾の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posBulletCount.x - BULE_SIZE, g_posBulletCount.y - BULE_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posBulletCount.x + BULE_SIZE, g_posBulletCount.y - BULE_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posBulletCount.x - BULE_SIZE, g_posBulletCount.y + BULE_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posBulletCount.x + BULE_SIZE, g_posBulletCount.y + BULE_SIZE, 0.0f);

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
				g_posBulletCount.x += 50;
			}
			else if (nCntFrame == 2)
			{//弾
			 //弾の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posXher.x - XHER_SIZE, g_posXher.y - XHER_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posXher.x + XHER_SIZE, g_posXher.y - XHER_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posXher.x - XHER_SIZE, g_posXher.y + XHER_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posXher.x + XHER_SIZE, g_posXher.y + XHER_SIZE, 0.0f);

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
			else if (nCntFrame == 3)
			{//弾
			 //弾の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posKill.x - KILL_SIZE_X, g_posKill.y - KILL_SIZE_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posKill.x + KILL_SIZE_X, g_posKill.y - KILL_SIZE_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posKill.x - KILL_SIZE_X, g_posKill.y + KILL_SIZE_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posKill.x + KILL_SIZE_X, g_posKill.y + KILL_SIZE_Y, 0.0f);

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
			//else if (nCntFrame == 4)
			//{//弾
			// //弾の頂点設定
			//	pVtx[0].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE_X, g_posTime.y - TIME_SIZE_Y, 0.0f);
			//	pVtx[1].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE_X, g_posTime.y - TIME_SIZE_Y, 0.0f);
			//	pVtx[2].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE_X, g_posTime.y + TIME_SIZE_Y, 0.0f);
			//	pVtx[3].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE_X, g_posTime.y + TIME_SIZE_Y, 0.0f);

			//	//1.0fで固定
			//	pVtx[0].rhw = 1.0f;
			//	pVtx[1].rhw = 1.0f;
			//	pVtx[2].rhw = 1.0f;
			//	pVtx[3].rhw = 1.0f;

			//	//頂点カラー
			//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	//テクスチャ座標
			//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			//}
			else if (nCntFrame == 5)
			{//弾
			 //弾の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posEngineFrame.x - TIME_ENGINE_FRAME_X, g_posEngineFrame.y - TIME_ENGINE_FRAME_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posEngineFrame.x + TIME_ENGINE_FRAME_X, g_posEngineFrame.y - TIME_ENGINE_FRAME_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posEngineFrame.x - TIME_ENGINE_FRAME_X, g_posEngineFrame.y + TIME_ENGINE_FRAME_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posEngineFrame.x + TIME_ENGINE_FRAME_X, g_posEngineFrame.y + TIME_ENGINE_FRAME_Y, 0.0f);

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
			else if (nCntFrame == 6)
			{//エンジン
				//弾の頂点設定
				pVtx[0].pos = D3DXVECTOR3(g_posEngine.x - TIME_ENGINE_X, g_posEngine.y - TIME_ENGINE_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posEngine.x + TIME_ENGINE_X, g_posEngine.y - TIME_ENGINE_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posEngine.x - TIME_ENGINE_X, g_posEngine.y + TIME_ENGINE_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posEngine.x + TIME_ENGINE_X, g_posEngine.y + TIME_ENGINE_Y, 0.0f);

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
			//else if (nCntFrame == 10)
			//{//地図
			// //弾の頂点設定
			//	pVtx[0].pos = D3DXVECTOR3(g_posTizu.x - TIZU_X, g_posTizu.y - TIZU_Y, 0.0f);
			//	pVtx[1].pos = D3DXVECTOR3(g_posTizu.x + TIZU_X, g_posTizu.y - TIZU_Y, 0.0f);
			//	pVtx[2].pos = D3DXVECTOR3(g_posTizu.x - TIZU_X, g_posTizu.y + TIZU_Y, 0.0f);
			//	pVtx[3].pos = D3DXVECTOR3(g_posTizu.x + TIZU_X, g_posTizu.y + TIZU_Y, 0.0f);

			//	//1.0fで固定
			//	pVtx[0].rhw = 1.0f;
			//	pVtx[1].rhw = 1.0f;
			//	pVtx[2].rhw = 1.0f;
			//	pVtx[3].rhw = 1.0f;

			//	//頂点カラー
			//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	//テクスチャ座標
			//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			//}
		}
		else if (nCntFrame == 7)
		{//エンジン
		 //弾の頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_posZonnbi1.x - ZONNBI1_X, g_posZonnbi1.y - ZONNBI1_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posZonnbi1.x + ZONNBI1_X, g_posZonnbi1.y - ZONNBI1_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posZonnbi1.x - ZONNBI1_X, g_posZonnbi1.y + ZONNBI1_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posZonnbi1.x + ZONNBI1_X, g_posZonnbi1.y + ZONNBI1_Y, 0.0f);

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
		else if (nCntFrame == 8)
		{//エンジン
		 //弾の頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_posZonnbi2.x - ZONNBI2_X, g_posZonnbi2.y - ZONNBI2_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posZonnbi2.x + ZONNBI2_X, g_posZonnbi2.y - ZONNBI2_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posZonnbi2.x - ZONNBI2_X, g_posZonnbi2.y + ZONNBI2_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posZonnbi2.x + ZONNBI2_X, g_posZonnbi2.y + ZONNBI2_Y, 0.0f);

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
		else if (nCntFrame == 9)
		{//エンジン
		 //弾の頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_posTumeato.x - TUMEATO_X, g_posTumeato.y - TUMEATO_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTumeato.x + TUMEATO_X, g_posTumeato.y - TUMEATO_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTumeato.x - TUMEATO_X, g_posTumeato.y + TUMEATO_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTumeato.x + TUMEATO_X, g_posTumeato.y + TUMEATO_Y, 0.0f);

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
	//マウスの情報
	DIMOUSESTATE2 pMouse = GetMousePointer();

	Camera *pCamera = GetCamera();

	Score *pScore = GetScore();

	g_Xhetrot += -pMouse.lY / 30.0f;

	g_posXher = pCamera->posR;

	//モデルをカメラに代入
	g_posXher = pCamera->posV;

	//カメラの向きをオブジェクトに代入
	g_posXher = pCamera->rot;
	g_Xhetrot += (pMouse.lY / 500.0f);
	g_posXher.y += (g_Xhetrot);
}

//-----------------------------------------------------------------------------
//所有物の描画処理
//-----------------------------------------------------------------------------
void DrawFrame(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice		  = GetDevice();	//デバイスの取得
	MODE pMode = *GetMode();
	int				  nCntFrame;						//所有物のカウント

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