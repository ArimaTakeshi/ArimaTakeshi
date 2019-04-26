//=========================================================================================================================
//
// タイトルの処理 [TITLE.cpp]
// Author :  有馬武志　＆　加藤　＆　内山
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "Title.h"		//タイトル
#include "input.h"		//入力
#include "fade.h"		//フェード
#include "camera.h"		//カメラ
#include "light.h"		//ライト
#include "meshbg.h"		//メッシュシリンダー
#include "meshfield.h"	//メッシュフィールド
#include "sound.h"		//サウンド
#include "billboord.h"	//ビルボード
#include "wall.h"		//ウォール
#include "effect.h"		//エフェクト
#include "object.h"		//オブジェクト
#include "objectnot.h"	//あたり判定のないオブジェクト
#include "enter.h"		//エンター
#include "frame.h"		//テクスチャ

//*************************************************************************************************************************
// マクロ定義
//**************************************************************************************************************************
#define TITLE_TEXTURE_NAME	   "data/TEXTURE/表示.png" //読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME_GI  "data/TEXTURE/ぎ.png"   //読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME_XYA "data/TEXTURE/ゃ.png"   //読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME_KU  "data/TEXTURE/く.png"   //読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME_RE  "data/TEXTURE/れ.png"   //読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME_O   "data/TEXTURE/お.png"   //読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME_NI  "data/TEXTURE/に.png"   //読み込むテクスチャファイル
#define MAX_TEXTURE			   (7)					   //テクスチャの最大数
#define MAX_TITLE			   (6)					   //タイトル文字の最大数
#define TITLE_POS_X			   (10)					   //タイトルの左上X座標
#define TITLE_POS_Y			   (-250)				   //タイトルの左上Y座標
#define TITLE_WIDTH			   (250)				   //タイトルの幅
#define TITLE_HEIGHT		   (250)				   //タイトルの高さ
#define TITLE2_POS_X		   (300)				   //指示表示の左上X座標
#define TITLE2_POS_Y		   (600)				   //指示表示の左上Y座標
#define TITLE2_WIDTH		   (1000)				   //指示表示の幅
#define TITLE2_HEIGHT		   (700)				   //指示表示の高さ
#define TITLE_SPEED			   (5.0f)				   //タイトルのスピード

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTitle[MAX_TEXTURE] = {};  //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//頂点バッファへのポインタ
int						g_nCntTimeTitle = 0;				//カウンター
float					g_nColor = 1.0f;					//指示表示の透明度
Title					g_aTitle[MAX_TITLE];				//タイトルの情報
int						g_nCountTimer;

//=========================================================================================================================
// タイトル初期化処理
//=========================================================================================================================
void InitTitle(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
	VERTEX_2D		  *pVtx;				 //頂点情報へのポインタ
	int				  nCntTitle;			 //タイトルの文字のカウント
	int				  nInterval;			 //間隔

	g_nCntTimeTitle = 0;	 //カウンターの初期化

	//初期化
	for (nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
		g_aTitle[nCntTitle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME, &g_pTextureTitle[0]);	 //指示表示
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_GI, &g_pTextureTitle[1]);  //タイトル1
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_XYA, &g_pTextureTitle[2]); //タイトル2
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_KU, &g_pTextureTitle[3]);  //タイトル3
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_RE, &g_pTextureTitle[4]);  //タイトル4
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_O, &g_pTextureTitle[5]);   //タイトル5
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_NI, &g_pTextureTitle[6]);  //タイトル6

	//頂点バッファ生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	//頂点バッファをロック
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	////指示表示の頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(TITLE2_POS_X, TITLE2_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(TITLE2_WIDTH, TITLE2_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(TITLE2_POS_X, TITLE2_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(TITLE2_WIDTH, TITLE2_HEIGHT, 0.0f);

	////指示表示の頂点カラー設定
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);

	////1.0fで固定
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////指示表示のテクスチャ設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//タイトルの文字
	for (nCntTitle = 0, nInterval = 0; nCntTitle < MAX_TITLE; nCntTitle++, nInterval += 200)
	{
		pVtx += 4;	//頂点データのポインタを4つ進める
		//タイトルの頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);

		//タイトルの頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//タイトルのテクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	//カメラの初期化処理
	InitCamera();

	//カメラの初期化処理
	InitLight();

	//の初期化処理
	InitMeshBg();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//エフェクトの初期化処理
	InitEffect();

	//オブジェクトの初期化処理
	InitObject();

	//あたり判定のないオブジェクトの初期化処理
	InitObjectNot();

	//エンターの初期化処理
	InitEnter();

	//================================================================================
	//当たり判定のあるオブジェクト
	//================================================================================
	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//400
	SetObject(D3DXVECTOR3(1000.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//600
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//信号(下)
	SetObject(D3DXVECTOR3(1200.0f, 0.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//街灯
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ダンボール
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	//トラック
	SetObject(D3DXVECTOR3(4200.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//木
	SetObject(D3DXVECTOR3(0.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//自販機
	SetObject(D3DXVECTOR3(1400.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//ゴミ箱
	SetObject(D3DXVECTOR3(1220.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//滑り台
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------5---------------

	SetObject(D3DXVECTOR3(900.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//------------10---------------

	//200
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------15---------------

	//200
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------20---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------25---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------30---------------

	//200
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------35---------------

	//200
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(900.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-100.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------40---------------

	//200
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------45---------------

	//200
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------50---------------

	//200
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------55---------------

	//200
	SetObject(D3DXVECTOR3(2700.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3100.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -3300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------60---------------

	//200
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -4100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------65---------------

	//200
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------69---------------


	//------------73---------------

	//400

	//------------81---------------

	//200
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -3900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------85---------------

	//200
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------90---------------

	//200
	SetObject(D3DXVECTOR3(2500.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------95---------------

	//200
	SetObject(D3DXVECTOR3(4100.0f, 0.0f, -1900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -900.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------100---------------


	//200
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3700.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------105---------------

	//200
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3100.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//------------107---------------

	//400
	SetObject(D3DXVECTOR3(200.0f, 0.0f, -1600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4000.0f, 0.0f, -2600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3800.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.0f, -1800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.0f, -1400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//600
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.0f, -1100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.0f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//信号(下)
	SetObject(D3DXVECTOR3(1200.0f, 0.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1600.0f, 0.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1600.0f, 0.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//街灯
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(400.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//街灯
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(400.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	//ダンボール
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1350.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1450.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, -0.0f, 0.0f));

	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.1f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(550.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(750.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.3f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.6f, 0.0f));
	SetObject(D3DXVECTOR3(1300.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1700.0f, 0.1f, -3200.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1800.0f, 0.1f, -3300.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3750.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -3800.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3750.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2750.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2750.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -200.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(3900.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));

	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	SetObject(D3DXVECTOR3(2750.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));

	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));
	SetObject(D3DXVECTOR3(2550.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(2550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -50.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2900.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2950.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3500.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3550.0f, 0.1f, -3450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	//
	SetObject(D3DXVECTOR3(4100.0f, 0.1f, -3900.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(4150.0f, 0.1f, -3900.0f), D3DXVECTOR3(0.0f, 0.4f, 0.0f));
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 1.2f, 0.0f));

	SetObject(D3DXVECTOR3(900.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));//単体配置
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));//単体配置
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));//単体配置
	SetObject(D3DXVECTOR3(700.0f, 0.1f, -350.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(750.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(300.0f, 0.1f, -1100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -1100.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(250.0f, 0.1f, -1150.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1450.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(3350.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(3400.0f, 0.1f, -1250.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(3200.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -1400.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));
	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.8f, 0.0f));
	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2000.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -4100.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2050.0f, 0.1f, -3650.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2700.0f, 0.1f, -3500.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	SetObject(D3DXVECTOR3(1900.0f, 0.1f, -1950.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));//ダンボール後で使う
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));//重ね置き中
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -2600.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));//
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));//
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2600.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));//

	SetObject(D3DXVECTOR3(2500.0f, 50.0f, -300.0f), D3DXVECTOR3(0.0f, 0.9f, 0.0f));
	SetObject(D3DXVECTOR3(2520.0f, 20.0f, -300.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 80.0f, -300.0f), D3DXVECTOR3(0.0f, 1.1f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 20.0f, -340.0f), D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 50.1f, -340.0f), D3DXVECTOR3(0.0f, 0.7f, 0.0f));

	//トラック
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -300.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));//重ね置き中

																				   //木(下)
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(250.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(750.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2850.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3050.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3150.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3450.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3650.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1750.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(750.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2350.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2850.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3050.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3150.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3450.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3650.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3950.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObject(D3DXVECTOR3(1550.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1550.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//-----------------------------------------------------ここかれあ
	SetObject(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObject(D3DXVECTOR3(2200.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2400.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2600.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2500.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//--------------------
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//木かさねおきちゅう
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//-------------------

																				 //自販機
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1100.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(1200.0f, 0.1f, -3250.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(50.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2100.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(3000.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(200.0f, 0.1f, -2810.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3300.0f, 0.1f, -1500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObject(D3DXVECTOR3(3600.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObject(D3DXVECTOR3(4000.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//ゴミ箱
	SetObject(D3DXVECTOR3(100.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObject(D3DXVECTOR3(2220.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3020.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(330.0f, 0.1f, -3120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(1520.0f, 0.1f, -3120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(4020.0f, 0.1f, -2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(1820.0f, 0.1f, -3620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(320.0f, 0.1f, -4120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3520.0f, 0.1f, -1120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(3520.0f, 0.1f, 80.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(2220.0f, 0.1f, -620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObject(D3DXVECTOR3(2300.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//================================================================================
	//当たり判定のないオブジェクト
	//================================================================================
	//
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//信号
	SetObjectNot(D3DXVECTOR3(1600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	//街灯
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	//木
	SetObjectNot(D3DXVECTOR3(0.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	//草原
	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	//車道
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -975.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -1625.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2925.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));// -3575.0f


	SetObjectNot(D3DXVECTOR3(325.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(975.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1625.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2275.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2925.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3700.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//歩道

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -1325.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3620.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2025.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1400.0f, 0.1f, -2375.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(325.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(780.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(780.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2020.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2675.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3700.0f, 0.1f, -3000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//信号
	SetObjectNot(D3DXVECTOR3(1200.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1200.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	//街灯
	SetObjectNot(D3DXVECTOR3(100.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2700.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3300.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3600.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3900.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	//街灯
	SetObjectNot(D3DXVECTOR3(100.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2700.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3000.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3300.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3600.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3900.0f, 0.1f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));

	//
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -100.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1300.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1600.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1900.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2200.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2500.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2800.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3400.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3700.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -4000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));

	//木
	SetObjectNot(D3DXVECTOR3(150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(250.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1750.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(750.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(950.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1950.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2350.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2850.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3050.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(3150.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3250.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3450.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3650.0f, 20.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3950.0f, 10.0f, -2850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(250.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1750.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(750.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(950.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1950.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2350.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2850.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3050.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(3150.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3250.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3450.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3650.0f, 20.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(3950.0f, 10.0f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1250.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -450.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -750.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -1850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2250.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -2550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3550.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -3850.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(1550.0f, 0.1f, -4050.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//-----------------------------------------------------ここかれあ
	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2200.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2300.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2400.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2500.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2600.0f, 0.1f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2500.0f, 0.1f, -2700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//--------------------
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//木かさねおきちゅう
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(450.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	SetObjectNot(D3DXVECTOR3(0.0f, 0.1f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(150.0f, 0.1f, -700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(350.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.1f, -500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));//-------------------

																					//草原
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));


	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -700.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -800.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(-100.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(0.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(100.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(200.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(300.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(400.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(500.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(600.0f, 0.2f, -900.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));

	SetObjectNot(D3DXVECTOR3(2250.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2350.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2550.0f, 0.2f, -2500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2250.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2350.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2450.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	SetObjectNot(D3DXVECTOR3(2550.0f, 0.2f, -2600.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=========================================================================================================================
// タイトル終了処理
//=========================================================================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount] ->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//シリンダーの終了処理
	UninitMeshBg();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//エフェクトの終了処理
	UninitEffect();

	//オブジェクトの終了処理
	UninitObject();

	//あたり判定のないオブジェクトの終了処理
	UninitObjectNot();

	//エンターの終了処理
	UninitEnter();
}

//=========================================================================================================================
// タイトル更新処理
//=========================================================================================================================
void UpdateTitle(void)
{
	//ローカル変数宣言
	VERTEX_2D *pVtx;			   //頂点情報へのポインタ
	FADE	  pFade = GetFade();  //フェードのポインタ
	int		  nCntTitle;		   //タイトルの文字のカウント
	int		  nInterval;		   //間隔(位置)
	int		  nFrame = 15;		   //間隔(時間)

	g_nCntTimeTitle++; //時間のカウント

	//頂点バッファをロック
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCntTimeTitle % 10) == 0) //60フレーム毎
	{//指示表示の点滅
		g_nColor -= 0.05f;

		if (g_nColor <= 0.2f)
		{//一定時間薄くなる
			g_nColor = 1.0f;
		}
	}

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor);

	//タイトル文字の集合
	for (nCntTitle = 0, nInterval = 0; nCntTitle < MAX_TITLE; nCntTitle++, nInterval += 200)
	{
		//移動
		if (nCntTitle == 0)
		{//「ぎ」右から
			if (g_aTitle[0].pos.y < 150)
			{
				g_aTitle[0].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				g_aTitle[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 1 && g_nCntTimeTitle >= nFrame)
		{//「ゃ」上から
			if (g_aTitle[1].pos.y < 150)
			{
				g_aTitle[1].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				g_aTitle[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 2 && g_nCntTimeTitle >= (nFrame * 2))
		{//「く」左から
			if (g_aTitle[2].pos.y < 150)
			{
				g_aTitle[2].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				g_aTitle[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 3 && g_nCntTimeTitle >= (nFrame * 3))
		{//「れ」右から
			if (g_aTitle[3].pos.y < 150)
			{
				g_aTitle[3].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				g_aTitle[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 4 && g_nCntTimeTitle >= (nFrame * 4))
		{//「お」上から
			if (g_aTitle[4].pos.y < 150)
			{
				g_aTitle[4].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				g_aTitle[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else if (nCntTitle == 5 && g_nCntTimeTitle >= (nFrame * 5))
		{//「に」左から
			if (g_aTitle[5].pos.y < 150)
			{
				g_aTitle[5].move = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				g_aTitle[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		//位置を更新(移動)
		g_aTitle[nCntTitle].pos.x += g_aTitle[nCntTitle].move.x;
		g_aTitle[nCntTitle].pos.y += g_aTitle[nCntTitle].move.y;

		pVtx += 4;	//頂点データのポインタを4つ進める

		//タイトルの頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nCntTitle].pos.x + TITLE_WIDTH + nInterval, g_aTitle[nCntTitle].pos.y + TITLE_HEIGHT, 0.0f);
	}

	if (pFade == FADE_NONE)
	{
		//設定キー(Enter)が押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
		{
			if (g_aTitle[5].pos.y == 150)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_DECIDE);
				//モード固定
				SetFade(MODE_SERECT);
			}

			//エンターを押したときに無理やり位置をずらす
			g_aTitle[0].pos.y = 150;
			g_aTitle[1].pos.y = 150;
			g_aTitle[2].pos.y = 150;
			g_aTitle[3].pos.y = 150;
			g_aTitle[4].pos.y = 150;
			g_aTitle[5].pos.y = 150;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	//ライトの更新処理
	UpdateLight();

	//カメラの更新処理
	UpdateCamera();

	//シリンダーの更新処理
	UpdateMeshBg();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//エフェクトの更新処理
	UpdateEffect();

	//オブジェクトの更新処理
	UpdateObject();

	//あたり判定のないオブジェクトの更新処理
	UpdateObjectNot();

	//エンターの更新処理
	UpdateEnter();
}

//=========================================================================================================================
// タイトル描画処理
//=========================================================================================================================
void DrawTitle(void)
{
	SetCamera(CAMERA_TYPE_DEMO,5);

	//メッシュフィールドの描画処理
	DrawMeshField();

	//シリンダーの描画処理
	DrawMeshBg();

	//エフェクトの描画処理
	DrawEffect();

	//オブジェクトの描画処理
	DrawObject();

	//あたり判定のないオブジェクトの描画処理
	DrawObjectNot();

	//エンターの描画処理
	DrawEnter();


	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
	int				  nCnt;					 //カウント

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTitle[nCnt]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
	}
}