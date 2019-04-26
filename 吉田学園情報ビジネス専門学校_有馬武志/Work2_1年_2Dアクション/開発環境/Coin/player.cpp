//=========================================================================================================================
//
// ポリゴンの処理 [polygon.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "player.h"		//ポリゴン
#include "input.h"		//入力
#include <stdlib.h>		//lib
#include <time.h>		//time
#include "fade.h"		//フェード
#include "block.h"		//ブロック
#include "life.h"		//ライフ
#include "item.h"		//アイテム
#include "sound.h"		//サウンド

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define PLAYER_TEXTURE_NAME		"data\\TEXTURE\\player000.png"			//読み込むテクスチャファイル
#define PLAYER_TEXTURE_UV_U		(0.25f)									//テクスチャアニメーションU範囲
#define PLAYER_TEXTURE_UV_V		(0.5f)									//テクスチャアニメーションV範囲
#define PLAYER_HEIGHT			(60)									//プレイヤーの身長
#define PLAYER_WIDTH			(30)									//プレイヤーの横幅
#define PLAYER_LIFE				(3)										//プレイヤーのHP
//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//頂点バッファへのポインタ
Player g_player;
//カウント変数初期化
int g_nCount;
//=========================================================================================================================
	// ポリゴン初期化処理
//=========================================================================================================================
void InitPlayer(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	g_player.nCounterAnim = 0;		//カウンターを初期化
	g_player.nPatternAnim = 0;		//パターンを初期化
	g_player.TexT  = 0;				//テクスチャのタテ移動		
	//開始位置
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 600/*+ 300*/, 0.0f);
	g_player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_player.bJump = true;
	g_player.PlayerHeight = PLAYER_HEIGHT;
	g_player.PlayerWidth = PLAYER_WIDTH;
	g_player.nLife = PLAYER_LIFE;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;
	g_player.bUse = true;
	g_nCount = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		PLAYER_TEXTURE_NAME,
		&g_pTexturePlayer
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffPlayer->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, PLAYER_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, PLAYER_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();
}

//=========================================================================================================================
// ポリゴン終了処理
//=========================================================================================================================
void UninitPlayer(void)
{
	//テクスチャーの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=========================================================================================================================
// ポリゴン更新処理
//=========================================================================================================================
void UpdatePlayer(void)
{		
		//頂点情報へのポインタ
		VERTEX_2D *pVtx;	

		//パターン数の更新
		g_player.nCounterAnim++;	

		//前回の位置を保存
		g_player.posOld = g_player.pos;


		//頂点バッファをロック
		g_pVtxBuffPlayer->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		switch (g_player.state)
		{//プレイヤーの状態
		//通常状態
		case PLAYERSTATE_NORMAL:		
			break;
		//ダメージ状態
		case PLAYERSTATE_DAMAGE:		
			g_player.nCounterState--;	//状態をカウント

			if (g_player.nCounterState <= 0)
			{//状態カウント終了
				//色変更
				g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//状態変化
				g_player.state = PLAYERSTATE_NORMAL;
			}

			break;
		//プレイヤーが死ぬとき
		case PLAYERSTATE_DEAHT:
			//カウントを--し０以下にする
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				SetFadeMode(MODE_RESULT);
			}
			return;
			break;
		}

		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{//左に行く
			//g_player.move.x -= 3.0f;
				g_player.pos.x += sinf(-D3DX_PI * 0.5f) * 5.0f;
				g_player.pos.y += cosf(-D3DX_PI * 0.5f) * 5.0f;

				//フレームパターン
				if ((g_player.nCounterAnim % 5) == 0 && g_player.bJump == false)
				{
					//アニメーションのパターンNo.を初期値に戻す
					g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
				}
				//左方向
				g_player.TexT = 1;
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{//右に行く
			//g_player.move.x += 3.0f;

				g_player.pos.x += sinf(D3DX_PI * 0.5f) * 5.0f;
				g_player.pos.y += cosf(D3DX_PI * 0.5f) * 5.0f;

				//フレームパターン
				if ((g_player.nCounterAnim % 5) == 0 && g_player.bJump == false)
				{
					//アニメーションのパターンNo.を初期値に戻す
					g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
				}
				//右方向
				g_player.TexT = 0;
		}
		else
		{//キーボードを押してないとき
			if ((g_player.nCounterAnim % 5) == 0 && g_player.bJump == false)
			{
				//パターンを初期化
				g_player.nPatternAnim = 0;
				g_player.nCounterAnim = 0;
			}
		}
		

		//ポリゴンがエリア外の場合
		if (g_player.pos.x - PLAYER_WIDTH < PLAYER_WIDTH * -1)
		{//画面反対側に移動（左）
			g_player.pos.x = SCREEN_WIDTH;
		}
		else if (g_player.pos.x + PLAYER_WIDTH > SCREEN_WIDTH + PLAYER_WIDTH)
		{//画面反対側に移動（右）
			g_player.pos.x = 0;
		}
		if (g_player.pos.y - PLAYER_HEIGHT < 0)
		{//画面の上に出られない
			g_player.pos.y = PLAYER_HEIGHT;
			//天井に当たった場合moveを0にする
			g_player.move.y = 0.0f;
		}
		if (g_player.pos.y  > SCREEN_HEIGHT)
		{//穴に落ちたら初期値にもどる
			g_nCount++;
			//１秒たったら
			if ((g_nCount % 60) == 0)
			{
				//初期値に戻す
				g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 630/*+ 300*/, 0.0f);
				g_player.posOld = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 630/*+ 300*/, 0.0f);
				//敵や穴に落ちたらHPを減らしていく
				HitPlayer(1);

				g_nCount = 0;
			}
		}
		
		//ジャンプ	
		if (GetKeyboardTrigger(DIK_SPACE) == true && g_player.bJump == false)
		{
			//ジャンプ音
			PlaySound(SOUND_LABEL_SE_JAMP);
			//ジャンプの高さ
			g_player.move.y = -15.0f;

			//ジャンプ中足を開く
			g_player.nPatternAnim = 1;

			g_player.bJump = true;
		}
		else if (GetKeyboardTrigger(DIK_W) == true && g_player.bJump == false)
		{
			//ジャンプ音
			PlaySound(SOUND_LABEL_SE_JAMP);
			//ジャンプの高さ
			g_player.move.y = -15.0f;

			//ジャンプ中足を開く
			g_player.nPatternAnim = 1;

			g_player.bJump = true;
		}
		//重力の値　補足:この値が、１に近づくごとに重力がなくなる
		g_player.move.y += 0.5f;

		g_player.pos.y += g_player.move.y;

		//アイテムのあたり判定
		CollisionItem(&g_player.pos,&g_player.posOld,&g_player.move,&g_player.PlayerWidth,&g_player.PlayerHeight);

		//着地したら
		if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.PlayerWidth, &g_player.PlayerHeight) == true)
		{
			g_player.bJump = false;
		}
		else
		{//ここで、trueにしないと、落下時空中ジャンプができるようになる
			g_player.bJump = true;	
		}

		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V);
		pVtx[1].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V);
		pVtx[2].tex = D3DXVECTOR2(0.0f + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V + PLAYER_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V + PLAYER_TEXTURE_UV_V);

		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y, 0.0f);

		//頂点バッファをアンロック
		g_pVtxBuffPlayer->Unlock();	
}

//=========================================================================================================================
// ポリゴン描画処理
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
		g_pVtxBuffPlayer,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	if (g_player.bUse == true)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//ポリゴンの描画
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

	//ライフが減少
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{//ライフが0以下になった場合
		g_player.nLife = 0;
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEAHT;
		g_player.nCounterState = 60;
		g_player.bUse = false;
	
		//敵に当たったらHPを減らしていく
		AddLife(-nDamage, LifeTex_DAMAGE);
	}
	else
	{//ライフが1以上の場合
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;

		//敵や穴に落ちたらHPを減らしていく
		AddLife(-nDamage, LifeTex_DAMAGE);

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

//============================================
//
//============================================
void DeletePlayer(void)
{
	if (g_player.bUse == true)
	{
		//初期化
		g_player.nCounterAnim = 0;		//カウンターを初期化
		g_player.nPatternAnim = 0;		//パターンを初期化
		g_player.TexT = 0;				//テクスチャのタテ移動		
		//開始位置
		g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 600/*+ 300*/, 0.0f);
		g_player.move = D3DXVECTOR3(0, 0, 0.0f);
		g_player.bJump = true;
		g_player.state = PLAYERSTATE_NORMAL;
		g_player.nCounterState = 0;
	}
}