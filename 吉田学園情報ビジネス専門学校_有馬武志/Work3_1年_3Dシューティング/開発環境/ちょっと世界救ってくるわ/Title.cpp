//=========================================================================================================================
//
// タイトルの処理 [TITLE.cpp]
// Author : 有馬　武志
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
#include "enter.h"		//エンター
#include "frame.h"		//テクスチャ

//*************************************************************************************************************************
// マクロ定義
//**************************************************************************************************************************
#define TITLE_TEXTURE_NAME		"data\\TEXTURE\\タイトルロゴ02.png"	//読み込むテクスチャファイル
#define MAX_TEX					(1)									//テクスチャの最大数
#define	TITLE_SIZE_X			(500)
#define	TITLE_SIZE_Y			(400)

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ
Title g_Title;										//タイトルの情報
int g_nCounterGameState1;
int g_nCountTimer;
int g_nCntFadeTimer;

//=========================================================================================================================
// タイトル初期化処理
//=========================================================================================================================
void InitTitle(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//ポリゴンの中心値
	g_Title.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 20, 430, 0.0f);
	//ポリゴン移動値
	g_Title.move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	g_Title.nCounterAnim = 0;
	g_Title.nPatteunAnim = 0;
	g_nCounterGameState1 = 0;
	g_nCountTimer = 0;
	g_nCntFadeTimer = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//1枚目の画像
		pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTitle[0]
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEX ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffTitle->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{//全テクスチャのカウント
			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_Title.pos.x - TITLE_SIZE_X, g_Title.pos.y - TITLE_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Title.pos.x + TITLE_SIZE_X, g_Title.pos.y - TITLE_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Title.pos.x - TITLE_SIZE_X, g_Title.pos.y + TITLE_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Title.pos.x + TITLE_SIZE_X, g_Title.pos.y + TITLE_SIZE_Y, 0.0f);

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

			//テクスチャ設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//頂点ずらし
		pVtx += 4;
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

	//ビルボードの初期化処理
	InitBillBoord();

	//エフェクトの初期化処理
	InitEffect();

	//オブジェクトの初期化処理
	InitObject();

	//エンターの初期化処理
	InitEnter();

	//フレームの初期化処理
	InitFrame();

	SetObject(D3DXVECTOR3(40, 0, -95), D3DXVECTOR3(0, 0, 0));

	if (g_nCountTimer >= 0 && g_nCountTimer <= 299)
	{
		//雪のエフェクト
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
	}
	if (g_nCountTimer >= 300 && g_nCountTimer <= 599)
	{
		//雨のエフェクト
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
	}
	if (g_nCountTimer == 600)
	{
		g_nCountTimer = 0;
	}
	g_nCountTimer++;

	//ビルボードオブジェクト
	//SetBillBoord(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 0);//中心
}

//=========================================================================================================================
// タイトル終了処理
//=========================================================================================================================
void UninitTitle(void)
{

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
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

	//フィールドの終了処理
	UninitMeshField();

	//ビルボードの終了処理
	UninitBillBoord();

	//エフェクトの終了処理
	UninitEffect();

	//フレームの終了処理
	UninitFrame();

	//オブジェクトの初期化処理
	//UninitObject();

	//エンターの初期化処理
	UninitEnter();
}

//=========================================================================================================================
// タイトル更新処理
//=========================================================================================================================
void UpdateTitle(void)
{
	//フェードのポインタ
	FADE pFade = *GetFade();

	g_nCntFadeTimer++;

	//タイトルの動きを追加
	g_Title.pos.y += g_Title.move.y;

	//タイトル動かない！
	if (g_Title.pos.y >= 200)
	{
		g_Title.move.y = 0;
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetMouseTrigger(0) == true)
		{//エンターキーが押されたら
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_TUTORIAL);
		}
		else if ((g_nCntFadeTimer % 1000) == 0)
		{//１０秒後にランキングへ行く
			SetFade(MODE_RANKING);
		}
	}

	//ライトの更新処理
	UpdateLight();

	//カメラの更新処理
	UpdateCamera();

	//シリンダーの更新処理
	UpdateMeshBg();

	//フィールドの更新処理
	UpdateMeshField();

	//ビルボードの更新処理
	UpdateBillBoord();

	//エフェクトの更新処理
	UpdateEffect();

	//フレームの更新処理
	UpdateFrame();

	//オブジェクトの初期化処理
	UpdateObject();

	//エンターの初期化処理
	UpdateEnter();

}

//=========================================================================================================================
// タイトル描画処理
//=========================================================================================================================
void DrawTitle(void)
{
	//カメラの描画処理
	SetCamera(CAMERA_TYPE_DEMO);

	//フィールドの描画処理
	DrawMeshField();

	//オブジェクトの初期化処理
	DrawObject();

	//ビルボードの描画処理
	DrawBillBoord();

	//シリンダーの描画処理
	DrawMeshBg();

	//エフェクトのの描画処理
	DrawEffect();

	//エンターの初期化処理
	DrawEnter();

	//フレームの描画処理
	DrawFrame();

	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice= GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}

}