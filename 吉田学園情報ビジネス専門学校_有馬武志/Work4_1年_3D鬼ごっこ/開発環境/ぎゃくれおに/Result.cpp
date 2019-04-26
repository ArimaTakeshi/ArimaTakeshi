//=========================================================================================================================
//
// リザルトの処理 [result.cpp]
// Author :  有馬　武志　＆　箱崎
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "result.h"		//リザルト
#include "input.h"		//入力
#include "fade.h"		//フェード
#include "Game.h"		//ゲーム
#include "sound.h"		//サウンド
#include "enter.h"		//エンター
#include "camera.h"
#include "object.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define RESULT_TEXTURE_WIN		"data\\TEXTURE\\player_win.png"//読み込むテクスチャファイル
#define RESULT_TEXTURE_NOTWIN	"data\\TEXTURE\\oni_win2.png"//読み込むテクスチャファイル
#define RESULT_POS_X			(0)							//リザルトの左上X座標
#define RESULT_POS_Y			(0)							//リザルトの左上Y座標
#define RESULT_WIDTH			(SCREEN_WIDTH)				//リザルトの幅
#define RESULT_HEIGHT			(SCREEN_HEIGHT)				//リザルトの高さ
#define RESULT_MAX				(2)							//リザルトの高さ
#define RESULT_TEXTURE_SPEED	(5)							//テクスチャアニメーションスピード
#define RESULT_TEXTURE_PATTERN	(10)						//テクスチャアニメーションパターン数
#define RESULT_TEXTURE_UV_U		(1.0f)						//テクスチャアニメーションU範囲
#define RESULT_TEXTURE_UV_V		(1.0f)						//テクスチャアニメーションV範囲
#define RESULT_BACKTEXTURE_UV_U	(1.0f)						//前テクスチャアニメーションU範囲
#define RESULT_BACKTEXTURE_UV_V	(1.0f)						//前テクスチャアニメーションV範囲
#define RESULT_SPEED			(0.003f)					//リザルトスピード

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファへのポインタ
D3DXVECTOR3 g_posResult;							//リザルトの位置
D3DXVECTOR3 g_moveResult;							//リザルトの移動

//=========================================================================================================================
// リザルト初期化処理
//=========================================================================================================================
void InitResult(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	Camera *pCamera = GetCamera();

	Object *pObject = GetObject();

	//デバイスの取得
	pDevice = GetDevice();

	g_posResult = D3DXVECTOR3((RESULT_POS_X + RESULT_WIDTH) / 2, (RESULT_POS_Y + RESULT_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値
	g_moveResult = D3DXVECTOR3(0.0f, RESULT_SPEED, 0.0f);		//ポリゴン移動値

	GAMESTATE GameStateNow = GetGameState();
	
	//勝利と敗北
	//テクスチャの読み込み
	if (GameStateNow == GAMESTATE_CLEAR)
	{
		D3DXCreateTextureFromFile
		(
			pDevice,
			RESULT_TEXTURE_WIN,
			&g_pTextureResult
		);

		//ニワトリの声
		PlaySound(SOUND_LABEL_SE_CHICEN);
	}
	else
	{
		D3DXCreateTextureFromFile
		(
			pDevice,
			RESULT_TEXTURE_NOTWIN,
			&g_pTextureResult
		);
	}

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffResult->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RESULT_POS_X, RESULT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RESULT_WIDTH, RESULT_HEIGHT, 0.0f);
	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(RESULT_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RESULT_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(RESULT_TEXTURE_UV_U, RESULT_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffResult->Unlock();

	InitEnter();
}

//=========================================================================================================================
// リザルト終了処理
//=========================================================================================================================
void UninitResult(void)
{
	//テクスチャーの破棄
	if (g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();
		g_pTextureResult = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	UninitEnter();
}

//=========================================================================================================================
// リザルト更新処理
//=========================================================================================================================
void UpdateResult(void)
{
	FADE	  pFade = GetFade();  //　フェードのポインタ

	static int nCount = 0;

	nCount++;

	if (pFade == FADE_NONE)
	{
		//設定キー（ENTERキー）が押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true || (nCount % 190) == 0)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_TITLE);
		}
	}

	UpdateEnter();
}

//=========================================================================================================================
// リザルト描画処理
//=========================================================================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffResult,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureResult);

	//リザルトの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	DrawEnter();
}