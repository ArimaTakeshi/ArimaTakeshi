//=========================================================================================================================
//
// プレイヤーの処理 [playe.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "player.h"		//プレイヤー
#include "bullet.h"		//弾
#include "input.h"		//入力処理
#include <stdlib.h>		//lib
#include <time.h>		//time
#include "explosion.h"	//爆発処理
#include "fade.h"		//フェード
#include "life.h"		//ライフ
#include "minibossenemy.h"
#include "bossenemy.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define PLAYER_TEXTURE_NAME		"data\\TEXTURE\\ニワトリ.png"			//読み込むテクスチャファイル
#define PLAYER_POS_X			(SCREEN_WIDTH / 2 - 25)					//プレイヤーの左上X座標
#define PLAYER_POS_Y			(SCREEN_HEIGHT - 100)					//プレイヤーの左上Y座標
#define PLAYER_WIDTH			(SCREEN_WIDTH / 2 + 25)					//プレイヤーの幅
#define PLAYER_HEIGHT			(SCREEN_HEIGHT - 50)					//プレイヤーの高さ
#define PLAYER_G_POS_X			(25)									//g_posからのX距離
#define PLAYER_G_POS_Y			(35)									//g_posからのY距離
#define PLAYER_TEXTURE_SPEED	(10)									//テクスチャアニメーションスピード
#define PLAYER_TEXTURE_PATTERN	(10)									//テクスチャアニメーションパターン数
#define PLAYER_TEXTURE_UV_U		(1.0f)									//テクスチャアニメーションU範囲
#define PLAYER_TEXTURE_UV_V		(1.0f)									//テクスチャアニメーションV範囲
#define PLAYER_UPSPEED			(1.0f)									//プレイヤー加速スピード
#define PLAYER_DOWNSPEED		(0.125f)								//プレイヤー減速スピード
#define SINCOS_ANGLE_135		(0.75f)									//sin,cos角度（0.75）				
#define SINCOS_ANGLE_90			(0.5f)									//sin,cos角度（0.5）
#define SINCOS_ANGLE_45			(0.25f)									//sin,cos角度（0.25）
#define SINCOS_ANGLE_0			(0.0f)									//sin,cos角度（0.0）

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureplayer = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;			//頂点バッファへのポインタ
int g_nCounterAnim;										//アニメーションカウンター
int g_nPatternAnim;										//アニメーションパターンNo.
Player g_player;

//=========================================================================================================================
// プレイヤー初期化処理
//=========================================================================================================================
void InitPlayer(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_nCounterAnim = 0;		//カウンターを初期化
	g_nPatternAnim = 0;		//パターンを初期化

	g_player.pos = D3DXVECTOR3((PLAYER_POS_X + PLAYER_WIDTH) / 2, (PLAYER_POS_Y + PLAYER_HEIGHT) / 2, 0.0f);	//プレイヤー中心値
	g_player.move = D3DXVECTOR3(0, 0, 0.0f);																	//プレイヤー移動値
	g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);															//プレイヤーの色
	MODE *pMode;
	pMode = GetMode();

	if (*pMode == MODE_PLAYTUTORIAL)
	{//チュートリアル時のプレイヤー体力
		g_player.nLife = 100000;
	}
	else if(*pMode == MODE_GAME)
	{//ゲームモード時のプレイヤー体力
		g_player.nLife = 20;
	}
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;
	g_player.bUse = true;


	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		PLAYER_TEXTURE_NAME,
		&g_pTextureplayer
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL
	);
	
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffplayer->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH, PLAYER_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f);
	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, PLAYER_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, PLAYER_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffplayer->Unlock();
}

//=========================================================================================================================
// プレイヤー終了処理
//=========================================================================================================================
void UninitPlayer(void)
{
	//テクスチャーの破棄
	if (g_pTextureplayer != NULL)
	{
		g_pTextureplayer->Release();
		g_pTextureplayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}
}

//=========================================================================================================================
// プレイヤー更新処理
//=========================================================================================================================
void UpdatePlayer(void)
{
	//変数宣言
	float nPlayerSpeed = PLAYER_UPSPEED;	//プレイヤー速度
	static int nSelectSpeed = 1;			//弾速変更 
	static int nSelectAngle = 2;			//弾道変更
	static int nSelectColNum = 0;			//弾食変更
	static BULLETTYPE Type = BULLETTYPE_PLAYER;
	static D3DXVECTOR3 nSelectMove(0.0f, 0.0f, 0.0f);		//弾移動値
	static D3DXCOLOR nSelectColor(1.0f, 1.0f, 1.0f, 1.0f);	//弾色変更
	static float nAngleSpeed = 0.05f;		//角度
	static float nAngle = nAngleSpeed;		//角度2
	float nSpeed = 5.0f;					//速度

	nAngle += nAngleSpeed;

	g_nCounterAnim++;	//カウンター加算

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffplayer->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
		switch (g_player.state)
		{//敵状態
		case PLAYERSTATE_NORMAL:			//通常状態
			break;
		case PLAYERSTATE_DAMAGE:		//ダメージ状態
			g_player.nCounterState--;	//状態をカウント

			if (g_player.nCounterState <= 0)
			{//状態カウント終了
				 //色変更
				g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//状態変化
				g_player.state = PLAYERSTATE_NORMAL;
			}

			break;
		case PLAYERSTATE_DEAHT:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				SetFade(MODE_RESULT);
			}
			return;
			break;
		}


		//移動速度変更



		if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true)
		{//任意のキー（SHIFTキー）を押した場合
			nPlayerSpeed = PLAYER_UPSPEED - 0.7f;
			nPlayerSpeed = PLAYER_UPSPEED - 0.7f;
		}
		else if (GetKeyboardRelease(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true)
		{//任意のキー（SHIFTキー）を離した場合
			nPlayerSpeed = PLAYER_UPSPEED;
			nPlayerSpeed = PLAYER_UPSPEED;
		}


		//移動方向処理
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{//任意のキー（Aキー、左キー）を押した場合
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{//上同時入力
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{//下同時入力
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;

				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//左のみ
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{//任意のキー（Dキー、右キー）を押した場合
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{//上同時入力
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{//下同時入力
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//右のみ
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{//任意のキー（Wキー、上キー）を押した場合
			if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
			{//左同時入力
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
			{//右同時入力
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//上のみ
				g_player.move.x += sinf(D3DX_PI) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI) * nPlayerSpeed;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{//任意のキー（Dキー、下キー）を押した場合
			if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
			{//左同時入力
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
			{//右同時入力
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//下のみ
				g_player.move.x += sinf(SINCOS_ANGLE_0) * nPlayerSpeed;
				g_player.move.y += cosf(SINCOS_ANGLE_0) * nPlayerSpeed;
			}
		}

		//移動処理
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		//減速処理
		g_player.move.x += (0.0f - g_player.move.x) * PLAYER_DOWNSPEED;
		g_player.move.y += (0.0f - g_player.move.y) * PLAYER_DOWNSPEED;

		//プレイヤーがエリア外の場合
		if (g_player.pos.x - 20 < 0)
		{//画面反対側に移動（左）
			g_player.pos.x = 20;
		}
		if (g_player.pos.x + 20 > SCREEN_WIDTH)
		{//画面反対側に移動（右）
			g_player.pos.x = SCREEN_WIDTH - 20;
		}
		if (g_player.pos.y - 20 < 0)
		{//画面反対側に移動（上）
			g_player.pos.y = 20;
		}
		if (g_player.pos.y + 20 > SCREEN_HEIGHT)
		{//画面反対側に移動（下） 
			g_player.pos.y = SCREEN_HEIGHT - 20;
		}

		//初期位置に戻る
		if (GetKeyboardPress(DIK_NUMPAD0) == true)
		{//任意のキー（0キー）を押した場合
			g_player.pos = D3DXVECTOR3((PLAYER_POS_X + PLAYER_WIDTH) / 2, (PLAYER_POS_Y + PLAYER_HEIGHT) / 2, 0.0f);
		}

		//弾速変更
		if (GetKeyboardPress(DIK_NUMPAD1) == true)
		{//任意のキー（1キー）を押した場合
			nSelectSpeed = 1;
		}
		//else if (GetKeyboardPress(DIK_NUMPAD2) == true)
		//{//任意のキー（2キー）を押した場合
		//	nSelectSpeed = 3;
		//}
		//else if (GetKeyboardPress(DIK_NUMPAD3) == true)
		//{//任意のキー（3キー）を押した場合
		//	nSelectSpeed = 1;
		//}

		////弾道変更
		//if (GetKeyboardPress(DIK_Z) == true || GetKeyboardPress(DIK_NUMPAD4) == true)
		//{//任意のキー（Zキー、4キー）を押した場合
		//	nSelectAngle = 1;
		//}
		//else if (GetKeyboardPress(DIK_X) == true || GetKeyboardPress(DIK_NUMPAD5) == true)
		//{//任意のキー（Xキー、5キー）を押した場合
		//	nSelectAngle = 2;
		//}
		//else if (GetKeyboardPress(DIK_C) == true || GetKeyboardPress(DIK_NUMPAD6) == true)
		//{//任意のキー（Cキー、6キー）を押した場合
		//	nSelectAngle = 3;
		//}
		else if (GetKeyboardPress(DIK_V) == true || GetKeyboardPress(DIK_NUMPAD8) == true)
		{//任意のキー（Vキー、8キー）を押した場合
			nSelectAngle = 4;
		}

		//任意のキー（ENTERキー）を押した場合
		if (GetKeyboardTrigger(DIK_C) == true)
		{//弾色変更
			nSelectColNum = (nSelectColNum + 1) % 2;
			//nDistance = nSelectColNum;	//特定色の距離変化

			if (nSelectColNum == 0)
			{//色変更（白）
				nSelectColor.r = 1.0f;
				nSelectColor.g = 1.0f;
				nSelectColor.b = 1.0f;
				nSelectColor.a = 1.0f;
			}
			else if (nSelectColNum == 1)
			{//色変更（緑）
				nSelectColor.r = 0.0f;
				nSelectColor.g = 0.0f;
				nSelectColor.b = 1.0f;
				nSelectColor.a = 1.0f;
			}
		}

		//弾発射処理
		if (GetKeyboardPress(DIK_SPACE) == true)
		{//任意のキー（SPACEキー）を押した場合
			if (nSelectSpeed == 1)
			{//速度調整（１）
				if ((g_nCounterAnim % PLAYER_TEXTURE_SPEED) == 0)
				{//値（５）
					if (nSelectAngle == 1)
					{//左右弾道
						//左前
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右前
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左後
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 2)
					{//中央弾道
						//前
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//前
						nSelectMove.x = sinf(D3DX_PI * 0.9f) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * 0.9f) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//前
						nSelectMove.x = sinf(D3DX_PI * -0.9f) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * -0.9f) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 3)
					{//十字弾道
						//前
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 4)
					{//回転弾道
						//前
						nSelectMove.x = sinf(D3DX_PI + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆ 右　左　前　後　★☆★☆★☆★☆★☆★☆★☆★☆★☆★
											//前
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
				}
			}
			else if (nSelectSpeed == 2)
			{//速度調整（２）
				if ((g_nCounterAnim % (PLAYER_TEXTURE_SPEED - 2)) == 0)
				{//値（３）
					if (nSelectAngle == 1)
					{//左右弾道
					 //左前
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右前
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左後
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 2)
					{//中央弾道
						//前
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 3)
					{//右前弾道
						//前
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 4)
					{//回転弾道
					 //前
						nSelectMove.x = sinf(D3DX_PI + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
				}
			}
			else if (nSelectSpeed == 3)
			{//速度調整（３）
				if ((g_nCounterAnim % (PLAYER_TEXTURE_SPEED - 5)) == 0)
				{//値（１）
					if (nSelectAngle == 1)
					{//左右弾道
					 //左前
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右前
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左後
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 2)
					{//中央弾道
						//前
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 3)
					{//右前弾道
						//前
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;//前
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 4)
					{//回転弾道
					 //前
						nSelectMove.x = sinf(D3DX_PI + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆ 右　左　前　後　★☆★☆★☆★☆★☆★☆★☆★☆★☆★

											//前
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆ 右上　左上　前下　後下　★☆★☆★☆★☆★☆★☆★☆★☆★☆★

											//前
						nSelectMove.x = sinf(D3DX_PI * 0.375f + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * 0.375f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * 0.125f + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * 0.125f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * 0.375f + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * 0.375f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(-D3DX_PI * 0.125f + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * 0.125f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆ 右上/2　左上/2　前下/2　後下/2　★☆★☆★☆★☆★☆★☆★☆★☆★☆★

											//反対周り=====================================================
											//前
						nSelectMove.x = sinf(D3DX_PI - nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//後
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 - nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//左
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//右
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//★☆★☆★☆★☆★☆★☆★☆★☆★☆★☆ 右反対　左反対　前反対　後反対　★☆★☆★☆★☆★☆★☆★☆★☆★☆★
					}
				}
			}
		}
//頂点設定
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y + 20, 0.0f);
	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	pVtx[1].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	pVtx[2].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	pVtx[3].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	//頂点バッファをアンロック
	g_pVtxBuffplayer->Unlock();
}

//=========================================================================================================================
// プレイヤー描画処理
//=========================================================================================================================
void DrawPlayer(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffplayer,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureplayer);

	// ポリゴンの描画
	if (g_player.bUse == true)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureplayer);
		//プレイヤーの描画 
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=========================================================================================================================
// プレイヤーのダメージ処理
//=========================================================================================================================
void HitPlayer(int nDamage)
{
	//変数宣言
	/*int nCount = 0;*/

	MODE *pMode;
	pMode = GetMode();

	MiniBossEnemy *pMiniBossEnemy;
	pMiniBossEnemy = GetMiniBossEnemy();

	BossEnemy *pBossEnemy;
	pBossEnemy = GetBossEnemy();

	//ライフが減少
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{//ライフが0以下になった場合
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEAHT;
		g_player.nCounterState = 60;

		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f));
		g_player.bUse = false;
		
		pMiniBossEnemy->bUse = false;

		pBossEnemy->bUse = false;

		if (*pMode == MODE_GAME)
		{
			//弾が当たったらHPを減らしていく
			AddLife(-1, LifeTex_DAMAGE);
		}

	}
	else
	{//ライフが1以上の場合
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;

		if (*pMode == MODE_GAME)
		{
			//弾が当たったらHPを減らしていく
			AddLife(-1, LifeTex_DAMAGE);
		}
		//色変更
		g_player.col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	}
}
//=========================================================================================================================
// プレイヤーの取得処理
//=========================================================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}