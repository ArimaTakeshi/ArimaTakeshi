//=========================================================================================================================
//
// ランキングの処理 [ranking.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "ranking.h"	//ランキング
#include "input.h"		//キーボード
#include "fade.h"		//フィールド
#include "sound.h"		//サウンド
#include "score.h"		//スコア
#include "meshbg.h"		//メッシュシリンダー
#include "meshfield.h"	//メッシュフィールド
#include "camera.h"		//カメラ
#include "light.h"		//ライト
#include "wall.h"		//壁
#include "object.h"		//オブジェクト
#include "enter.h"		//エンター
#include "herimodel.h"	//ヘリ

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define RANKING_TEXTURE_NAME		"data\\TEXTURE\\順位.png"		//読み込むテクスチャファイル
#define RANKING_SIZE_X				(60)							//背景の左上X座標
#define RANKING_SIZE_Y				(305)							//背景の左上Y座標
#define RANKING_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define RANKING_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRANKING = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRANKING = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posRanking;								//背景の位置

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitRanking(void)
{
	//ヘリコプター
	Player2 pPlayer2 = *GetPlayer2();

	PlaySound(SOUND_LABEL_SE_HERI);

	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//初期値
	g_posRanking = D3DXVECTOR3(SCREEN_WIDTH / 2 + 220,SCREEN_HEIGHT / 2,0.0f);		//ポリゴンの中心値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		RANKING_TEXTURE_NAME,
		&g_pTextureRANKING
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRANKING,
		NULL
	);

	//頂点バッファをロック
	g_pVtxBuffRANKING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//弾の頂点設定
	pVtx[0].pos = D3DXVECTOR3(g_posRanking.x - RANKING_SIZE_X, g_posRanking.y - RANKING_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posRanking.x + RANKING_SIZE_X, g_posRanking.y - RANKING_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posRanking.x - RANKING_SIZE_X, g_posRanking.y + RANKING_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posRanking.x + RANKING_SIZE_X, g_posRanking.y + RANKING_SIZE_Y, 0.0f);

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

	//頂点バッファをアンロック
	g_pVtxBuffRANKING->Unlock();


	InitCamera();

	InitLight();

	InitMeshBg();

	InitMeshField();

	InitWall();

	InitObject();

	InitEnter();

	InitPlayer2();

	SetObject(D3DXVECTOR3(40, 0, -95), D3DXVECTOR3(0, 0, 0));

	//スコアの初期化
	InitScore();

	//************************************
	// ランキング表示
	//************************************
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 290, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 160, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 + 90, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 + 220, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);

	AddScore(0,SCORE_RAKING);
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitRanking(void)
{
	//テクスチャーの破棄
	if (g_pTextureRANKING != NULL)
	{
		g_pTextureRANKING->Release();
		g_pTextureRANKING = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRANKING != NULL)
	{
		g_pVtxBuffRANKING->Release();
		g_pVtxBuffRANKING = NULL;
	}

	//スコアの終了処理
	UninitScore();

	UninitCamera();

	UninitLight();

	UninitMeshBg();

	UninitMeshField();

	UninitWall();

	UninitObject();

	UninitEnter();

	UninitPlayer2();
}

//=========================================================================================================================
// 背景更新処理
//=========================================================================================================================
void UpdateRanking(void)
{

	//フェードのポインタ
	FADE pFade = *GetFade();

	static int nCount = 0;

	nCount++;
	if (pFade == FADE_NONE)
	{
		//設定キー（ENTERキー）が押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetMouseTrigger(0) == true || (nCount % 650) == 0)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_TITLE);
		}
	}
	//スコアの更新処理
	UpdateScore();

	UpdateLight();

	UpdateCamera();

	UpdateMeshBg();

	UpdateMeshField();

	UpdateObject();

	UpdateWall();

	UpdateEnter();

	UpdatePlayer2();
}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawRanking(void)
{

	SetCamera(CAMERA_TYPE_RANKING_DEMO);

	DrawWall();

	DrawMeshBg();

	DrawMeshField();

	DrawObject();

	DrawScore();

	DrawEnter();

	DrawPlayer2();

	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ
									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffRANKING,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureRANKING);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
