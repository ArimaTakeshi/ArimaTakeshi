//=========================================================================================================================
//
// ゲームの処理 [game.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "player.h"			//プレイヤー
#include "bullet.h"			//弾
#include "explosion.h"		//爆発
#include "enemy.h"			//敵
#include "effect.h"			//エフェクト
#include "fade.h"			//フェード	
#include "sound.h"			//サウンド
#include "input.h"			//キーボード処理
#include "pause.h"			//ポーズ
#include "playtutorial.h"	//チュートリアル

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define PLAYTUTORIAL_TEXTURE_NAME	"data\\TEXTURE\\チュートリアル.png"			//読み込むテクスチャファイル
#define PLAYTUTORIAL_POS_X			(0)								//背景の左上X座標
#define PLAYTUTORIAL_POS_Y			(0)								//背景の左上Y座標
#define PLAYTUTORIAL_WIDTH			(SCREEN_WIDTH)					//背景の幅
#define PLAYTUTORIAL_HEIGHT			(SCREEN_HEIGHT)					//背景の高さ
#define PLAYTUTORIAL_TEXTURE_UV_U	(1.0f)							//テクスチャアニメーションU範囲
#define PLAYTUTORIAL_TEXTURE_UV_V	(1.0f)							//テクスチャアニメーションV範囲
#define PLAYTUTORIAL_BACKTEXTURE_UV_V	(1.0f)							//前テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
PLAYTUTORIALSTATE g_PlayTutorialState = PLAYTUTORIALSTATE_NORMAL;	//ゲーム状態
int g_nCounterPlayTutorialState;									//状態カウンター
LPDIRECT3DTEXTURE9 g_pTexturePLAYTUTORIAL = NULL;								//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPLAYTUTORIAL = NULL;						//頂点バッファへのポインタ
D3DXVECTOR3 g_posPLAYTUTORIAL;												//背景の位置
D3DXVECTOR3 g_movePLAYTUTORIAL;												//背景の移動

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitPlayTutorial(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_posPLAYTUTORIAL = D3DXVECTOR3((PLAYTUTORIAL_POS_X + PLAYTUTORIAL_WIDTH) / 2, (PLAYTUTORIAL_POS_Y + PLAYTUTORIAL_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		PLAYTUTORIAL_TEXTURE_NAME,
		&g_pTexturePLAYTUTORIAL
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPLAYTUTORIAL,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffPLAYTUTORIAL->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(PLAYTUTORIAL_POS_X, PLAYTUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYTUTORIAL_WIDTH, PLAYTUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYTUTORIAL_POS_X, PLAYTUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYTUTORIAL_WIDTH, PLAYTUTORIAL_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(PLAYTUTORIAL_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, PLAYTUTORIAL_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(PLAYTUTORIAL_TEXTURE_UV_U, PLAYTUTORIAL_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffPLAYTUTORIAL->Unlock();


	//敵の初期化処理
	InitEnemy();

	//チュートリアルの敵
	SetEnemy(D3DXVECTOR3(SCREEN_WIDTH / 2, 150, 0.0f), 0);

	//エフェクトの初期化処理
	InitEffect();

	//プレイヤー初期化処理
	InitPlayer();

	//爆発の初期化処理
	InitExplosion();

	//弾の初期化処理
	InitBullet();

	//ポーズの初期化処理
	InitPause();

	g_PlayTutorialState = PLAYTUTORIALSTATE_NORMAL;		//通常状態に設定
	g_nCounterPlayTutorialState = 0;
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitPlayTutorial(void)
{

	//敵の終了処理
	UninitEnemy();

	//エフェクトの終了処理
	UninitEffect();

	//プレイヤーの終了処理
	UninitPlayer();

	//爆発の終了処理
	UninitExplosion();

	//弾の終了処理
	UninitBullet();

	//ポーズの終了処理
	UninitPause();

	//テクスチャーの破棄
	if (g_pTexturePLAYTUTORIAL != NULL)
	{
		g_pTexturePLAYTUTORIAL->Release();
		g_pTexturePLAYTUTORIAL = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPLAYTUTORIAL != NULL)
	{
		g_pVtxBuffPLAYTUTORIAL->Release();
		g_pVtxBuffPLAYTUTORIAL = NULL;
	}
}
//=========================================================================================================================
// 背景更新処理
//=========================================================================================================================
void UpdatePlayTutorial(void)
{
	//フェード
	FADE pFade;
	pFade = *GetFade();

	//エフェクトの更新処理
	UpdateEffect();

	//敵の更新処理
	UpdateEnemy();

	//爆発の更新処理
	UpdateExplosion();

	//弾の更新処理
	UpdateBullet();

	//プレイヤーの更新処理
	UpdatePlayer();

	if (pFade == FADE_NONE)
	{
		//設定キー（ENTERキー）が押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//モード設定
			SetFade(MODE_GAME);
		}
	}

}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawPlayTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffPLAYTUTORIAL,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTexturePLAYTUTORIAL);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//エフェクトの描画処理
	DrawEffect();

	//敵の描画処理
	DrawEnemy();

	//プレイヤーの描画
	DrawPlayer();

	//爆発の描画処理
	DrawExplosion();

	//弾の描画処理
	DrawBullet();
}
