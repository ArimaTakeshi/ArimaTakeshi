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
#include "game.h"			//背景
#include "player.h"			//プレイヤー
#include "bullet.h"			//弾
#include "explosion.h"		//爆発
#include "enemy.h"			//敵
#include "bg.h"				//背景
#include "score.h"			//スコア
#include "effect.h"			//エフェクト
#include "minibossenemy.h"	//中ボス
#include "ranking.h"		//ランキング
#include "fade.h"			//フェード	
#include "bossenemy.h"		//ボス
#include "sound.h"			//サウンド
#include "warning.h"		//ワーニング
#include "input.h"			//キーボード処理
#include "pause.h"			//ポーズ
#include "life.h"			//ライフ
#include "time.h"			//時間

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
GAMESTATE g_gameState = GAMESTATE_NORMAL;	//ゲーム状態
int g_nCounterGameState;					//状態カウンター
bool g_bPause;								//ポーズ

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitGame(void)
{
	//背景初期化処理
	InitBG();

	//ボスの初期化処理
	InitBossEnemy();

	//中ボスの初期化処理
	InitMiniBossEnemy();

	//敵の初期化処理
	InitEnemy();
	
	SetEnemy(D3DXVECTOR3(200, 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(300, 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(400, 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500, 100, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(600, 100, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(700, 100, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(800, 100, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(900, 100, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(1000, 100, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(1100, 100, 0.0f), 3);
	//２列目
	SetEnemy(D3DXVECTOR3(200, 200, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(300, 200, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(400, 200, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(500, 200, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(600, 200, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(700, 200, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(800, 200, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(900, 200, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(1000, 200, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(1100, 200, 0.0f), 0);
	//３列目
	SetEnemy(D3DXVECTOR3(200, 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(300, 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(400, 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(500, 300, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(600, 300, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(700, 300, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(800, 300, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(900, 300, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(1000, 300, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(1100, 300, 0.0f), 1);

	//エフェクトの初期化処理
	InitEffect();

	//プレイヤー初期化処理
	InitPlayer();

	//爆発の初期化処理
	InitExplosion();

	//弾の初期化処理
	InitBullet();

	//ワーニングの初期化処理
	InitWarning();

	//スコアの初期化処理
	InitScore();
	
	//ライフの初期化処理
	InitLife();

	//時間の初期化処理
	InitTime();

	//ポーズの初期化処理
	InitPause();

	
	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	g_nCounterGameState = 0;

	g_bPause = false;
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBG();
	
	//敵の終了処理
	UninitEnemy();

	//ボスの終了処理
	UninitBossEnemy();

	//中ボスの終了処理
	UninitMiniBossEnemy();

	//エフェクトの終了処理
	UninitEffect();

	//プレイヤーの終了処理
	UninitPlayer();

	//爆発の終了処理
	UninitExplosion();

	//弾の終了処理
	UninitBullet();

	//ワーニングの終了処理
	UninitWarning();

	//スコアの終了処理
	UninitScore();

	//ライフの終了処理
	UninitLife();

	//時間の終了処理
	UninitTime();

	//ポーズの終了処理
	UninitPause();

}
//=========================================================================================================================
// 背景更新処理
//=========================================================================================================================
void UpdateGame(void)
{
	//ポーズの処理
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;

		if (g_bPause == false)
		{
			//開く音
			PlaySound(SOUND_LABEL_SE_OPEN000);
		}
		else
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DOWN000);
		}
	}
	if (g_bPause == false)
	{

		//背景の更新処理
		UpdateBG();

		//エフェクトの更新処理
		UpdateEffect();

		//敵の更新処理
		UpdateEnemy();

		//ボスの更新処理
		UpdateBossEnemy();

		//中ボスの更新処理
		UpdateMiniBossEnemy();

		//爆発の更新処理
		UpdateExplosion();

		//弾の更新処理
		UpdateBullet();

		//ワーニングの更新処理
		UpdateWarning();

		//プレイヤーの更新処理
		UpdatePlayer();

		//スコアの更新処理
		UpdateScore();

		//ライフの更新処理
		UpdateLife();

		//時間の更新処理
		UpdateTime();
	}
	else
	{
		//ポーズ
		UpdatePause();
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{
			// = GAMESTATE_NONE;

			//画面（モード）の設定
			SetFade(MODE_RESULT);
		}
	}
}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//エフェクトの描画処理
	DrawEffect();

	//ボスの描画処理
	DrawBossEnemy();

	//敵の描画処理
	DrawEnemy();
	
	//BOSS敵の描画処理
	DrawMiniBossEnemy();

	//プレイヤーの描画
	DrawPlayer();

	//爆発の描画処理
	DrawExplosion();

	//弾の描画処理
	DrawBullet();

	//ワーニングの描画処理
	DrawWarning();
	
	//スコアの描画処理
	DrawScore();

	//ライフの描画処理
	DrawLife();

	//時間の描画処理
	DrawTime();

	if (g_bPause == true)
	{
		//ポーズの描画処理
		DrawPause();
	}
}
//=========================================================================================================================
// ゲーム状態の設定
//=========================================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=========================================================================================================================
// ゲーム状態の設定
//=========================================================================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=========================================================================================================================
// ゲーム状態の取得
//=========================================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

