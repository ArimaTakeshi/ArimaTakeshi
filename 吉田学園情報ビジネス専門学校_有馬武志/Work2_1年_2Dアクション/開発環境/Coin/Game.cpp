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
#include "game.h"			//ゲーム
#include "player.h"			//プレイヤー
#include "fade.h"			//フェード
#include "input.h"			//キーボード処理
#include "time.h"			//時間
#include "bg.h"				//背景
#include "block.h"			//ブロック
#include "score.h"			//スコア
#include "item.h"			//アイテム
#include "time.h"			//タイマー
#include "pause.h"			//ポーズ
#include "itemcount.h"		//アイテムカウント
#include "sound.h"			//サウンド
#include "life.h"			//ライフ
#include "explosion.h"		//爆発
#include "enemy.h"			//敵
#include "ranking.h"		//ランキング
#include "menu.h"			//メニュー
#include "effect.h"			//えふぇくtp
//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void SetStage(void);

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
GAMESTATE g_gameState;	//ゲーム状態
STAGENUM g_StageState;						// ステージ状態
int g_nCounterGameState;					//状態カウンター
bool g_bPause;								//ポーズ
bool g_bMenu;								//メニュー
int	g_nCntSetStage;							// ステージセットカウンタ

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NONE;	//ゲーム状態
	g_nCounterGameState = 0;

	//背景の初期化処理
	InitBG();

	//爆発の初期化処理
	InitExplosion();

	//プレイヤー初期化処理
	InitPlayer();

	//ブロックの初期化処理
	InitBlock();

	//敵の初期化処理
	InitEnemy();

	//スコアの初期化処理
	InitScore();

	//アイテムカウントの初期化処理
	InitItemCount();

	//アイテムの初期化処理
	InitItem();

	//ライフの初期化処理
	InitLife();

	//タイムの初期化処理
	InitTime();

	//ポーズの初期化処理
	InitPause();

	//メニューの初期化処理
	InitMenu();

	InitEffect();

	//スコアの表示
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 530,SCREEN_HEIGHT / 2 - 350,0.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),50,50);

	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定
	//g_nCounterGameState = 0;
	g_nCntSetStage = 0;					// カウンタ初期化
	//開始ステージ
	g_StageState = STAGENUM_1;			// ステージ状態

	//ポーズを使用してない状態にする
	g_bPause = false;

	g_bMenu = false;
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitGame(void)
{
	//背景の終了処理
	UninitBG();

	//爆発の終了処理
	UninitExplosion();

	//プレイヤーの終了処理
	UninitPlayer();

	//ブロックの終了処理
	UninitBlock();

	//敵の終了処理
	UninitEnemy();

	//スコアの終了処理
	UninitScore();

	//メニューの終了処理
	UninitMenu();

	//アイテムカウントの終了処理
	UninitItemCount();

	//アイテムの終了処理
	UninitItem();

	//ライフの終了処理
	UninitLife();

	//タイムの終了処理
	UninitTime();

	//ポーズの終了処理
	UninitPause();

	UninitEffect();
}
//=========================================================================================================================
// 背景更新処理
//=========================================================================================================================
void UpdateGame(void)
{
	//ポーズの処理
	if (GetKeyboardTrigger(DIK_P) == true)
	{//Pキーが押されたら
		g_bPause = g_bPause ? false : true;

		if (g_bPause == false)
		{//開く音
			PlaySound(SOUND_LABEL_SE_OPEN000);
		}
		else
		{//決定音
			PlaySound(SOUND_LABEL_SE_DOWN000);
		}
	}
	if (g_bPause == false && g_bMenu == false)
	{//普段はfalseにしている
		//背景の更新処理
		UpdateBG();

		//爆発の更新処理
		UpdateExplosion();

		//プレイヤーの更新処理
		UpdatePlayer();

		//ブロックの更新処理
		UpdateBlock();

		//敵の更新処理
		UpdateEnemy();

		//スコアの更新処理
		UpdateScore();

		//アイテムカウントの更新処理
		UpdateItemCount();

		//ライフの更新処理
		UpdateLife();

		//アイテムの更新処理
		UpdateItem();

		//タイムの更新処理
		UpdateTime();

		UpdateEffect();

		//ステージ設定
		SetStage();
	}
	else if (g_bPause == true)
	{//trueになったらポーズを更新する
		//ポーズの更新処理
		UpdatePause();
	}
	else if(g_bMenu == true)
	{
		//メニューの更新処理
		UpdateMenu();
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 120)
		{
			// = GAMESTATE_NONE;
			//画面（モード）の設定
			SetFadeMode(MODE_RESULT);
		}
		break;
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 120)
		{
			// = GAMESTATE_NONE;
			//画面（モード）の設定
			SetFadeMode(MODE_RESULT);
		}
		break;
	}
}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawGame(void)
{
	//背景の描画処理
	DrawBG();

	//爆発の描画処理
	DrawExplosion();

	//ブロックの描画処理
	DrawBlock();

	//敵の描画処理
	DrawEnemy();

	//スコアの描画処理
	DrawScore();

	//アイテムカウントの描画処理
	DrawItemCount();

	//アイテムの描画処理
	DrawItem();

	//プレイヤーの描画処理
	DrawPlayer();

	//ライフの描画処理
	DrawLife();

	//タイムの描画処理
	DrawTime();

	DrawEffect();

	if (g_bPause == true)
	{//ポーズがtrueだったら
		//ポーズの描画処理
		DrawPause();
	}
	if(g_bMenu == true)
	{//ポーズがtrueだったら

		//メニューの描画処理
		DrawMenu();

		//アイテムカウントの描画処理
		DrawItemCount();

		//スコアの描画処理
		DrawScore();

		//ライフの描画処理
		DrawLife();

		//************************************
		// アイテム「見本コイン」の配置
		//************************************

		////検証用見本コイン
		SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

	}
}
//=========================================================================================================================
// ゲーム状態の設定
//=========================================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

}
//=========================================================================================================================
// ゲーム状態の設定
//=========================================================================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=========================================================================================================================
// ゲーム状態の設定
//=========================================================================================================================
void SetMenuState(bool bMenu)
{
	g_bMenu = bMenu;
}
//=========================================================================================================================
// ゲーム状態の取得
//=========================================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//=========================================================================================================================
// ゲーム状態の取得
//=========================================================================================================================
STAGENUM GetNumState(void)
{
	return  g_StageState;
}
//=========================================================================================================================
// ゲーム設定処理
//=========================================================================================================================
void SetStageState(STAGENUM stage)
{
	if (g_StageState != stage)
	{
		DeleteItem();
		DeleteBlock();
		DeleteEnemy();
		DeletePlayer();
		DeleteTime();
	}

		if (g_StageState == STAGENUM_1)
		{

		}
		else if (g_StageState == STAGENUM_2)
		{

		}
		else if (g_StageState == STAGENUM_3)
		{

		}
		else if (g_StageState == STAGENUM_4)
		{

		}
		else if (g_StageState == STAGENUM_5)
		{

		}
		else if (g_StageState == STAGENUM_6)
		{

		}
		/*else if (g_StageState == STAGENUM_7)
		{

		}*/

	g_StageState = stage;			// 状態を記憶
	g_nCntSetStage = 0;
}

//==================================================================================================
// ステージ設定
//==================================================================================================
void SetStage(void)
{
	if (g_nCntSetStage == 0)
	{
//=================================================================================
//	ステージ1
//=================================================================================
		if (g_StageState == STAGENUM_1)
		{
			//噴火エフェクト
			//SetParticleEffect(D3DXVECTOR3(50, 0, 0), EFFECTTYPE_ERUPTION, 10, 3, 500, 0);

			//煙エフェクト
			SetParticleEffect(D3DXVECTOR3(100.0f, -50.0f, 0.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
			//SetParticleEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);

			//炎エフェクト
			//SetParticleEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);

			//火の粉エフェクト
			//SetParticleEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), EFFECTTYPE_POWDER, 3, 1, 50, 0);


			//************************************
			// ブロックの配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
			}
			*/
			for (int nCount = 0; nCount < 32; nCount++)
			{//  １段目床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目床左
				SetBlock(D3DXVECTOR3(40 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目床左
				SetBlock(D3DXVECTOR3(320 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目床右
				SetBlock(D3DXVECTOR3(760 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目床右
				SetBlock(D3DXVECTOR3(1040 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 320, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 320, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  ４段目床中央
				SetBlock(D3DXVECTOR3(320 + nCount * 40.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  ４段目床中央
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			//************************************
			// ブロックの配置「土部分の床」
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//左の壁替わり
				SetBlock(D3DXVECTOR3(0, 480 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//右の壁替わり
				SetBlock(D3DXVECTOR3(1240, 480 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//左移動床下
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//左移動床下
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// ブロックの配置「落ちる床」
			//************************************

			////検証用落ちる床（上に乗っかった時）
			SetBlock(D3DXVECTOR3(520, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(560, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(680, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(720, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);

			//************************************
			// ブロックの配置「壊せるブロック」
			//************************************

			////検証用壊せる床（下からの頭突き）
			SetBlock(D3DXVECTOR3(600, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);
			SetBlock(D3DXVECTOR3(640, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);

			//************************************
			// ブロックの配置「動かせる床」
			//************************************

			////検証用動かせる床左に押す
			SetBlock(D3DXVECTOR3(1080, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 120, 40);

			//************************************
			// ブロックの配置「動かせる床」
			//************************************
			////検証用動かせる床右に押す
			SetBlock(D3DXVECTOR3(160, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 15, 120, 40);

			//************************************
			// ブロックの配置「移動床」
			//************************************

			//検証用縦移動床左
			SetBlock(D3DXVECTOR3(240, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
			SetBlock(D3DXVECTOR3(280, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

			////検証用縦移動床右
			SetBlock(D3DXVECTOR3(960, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
			SetBlock(D3DXVECTOR3(1000, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

			//************************************
			// ブロックの配置「ベルトコンベアー」
			//************************************

			//右に押される
			SetBlock(D3DXVECTOR3(440, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 50, 160);
			//左に押される
			SetBlock(D3DXVECTOR3(680, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 50, 160);

			//************************************
			// ブロックの配置「透明なブロック」
			//************************************
			////検証用透明ブロック
			SetBlock(D3DXVECTOR3(1240, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);

			//************************************
			// アイテム「コイン」の配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(始まる位置 + カウント * コインとの横幅 , 設置の高さ , 0.0f ),D3DXCOLOR(RGBカラー),タイプ);
			}
			*/
			for (int nCount = 0; nCount < 8; nCount++)
			{//１段目コイン
				SetItem(D3DXVECTOR3(220.0f + nCount * 120, 630, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目破壊ブロックの下
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 560.0f + nCount * 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//２段目押せる床の左
				SetItem(D3DXVECTOR3(60 + nCount * 40.0f, 450, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//２段目押せる床の左
				SetItem(D3DXVECTOR3(60 + nCount * 40.0f, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//３段目押せる床の左
				SetItem(D3DXVECTOR3(60 + nCount * 40.0f, 280, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//２段目押せる床の右
				SetItem(D3DXVECTOR3(1140 + nCount * 40.0f, 450, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//２段目押せる床の右
				SetItem(D3DXVECTOR3(1140 + nCount * 40.0f, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//３段目押せる床の右
				SetItem(D3DXVECTOR3(1140 + nCount * 40.0f, 280, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 7; nCount++)
			{//４段目コイン
				SetItem(D3DXVECTOR3(340.0f + nCount * 100, 160, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}

			//************************************
			// アイテム「赤コイン」の配置
			//************************************

			////検証用赤コイン
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 220, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// アイテム「時計」の配置
			//************************************

			////検証用時計
			SetItem(D3DXVECTOR3(40, 140, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

			//************************************
			// アイテム「見本コイン」の配置
			//************************************

			////検証用見本コイン
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//g_StageState = STAGENUM_2;		// ステージ2に移行
			////SetNumStage(g_StageState);	// ステージ番号表示

		}
//=================================================================================
//	ステージ２
//=================================================================================
		else if (g_StageState == STAGENUM_2)
		{
			//************************************
			// ブロックの配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
			}
			*/
			for (int nCount = 0; nCount < 5; nCount++)
			{//  １段目床右
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//  １段目床左
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  １段目床左
				SetBlock(D3DXVECTOR3(680 + nCount * 560.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//　小さい山１段目左
				SetBlock(D3DXVECTOR3(200 + nCount * 120.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//　小さい山２段目左
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 600, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//　小さい山１段目右
				SetBlock(D3DXVECTOR3(920 + nCount * 120.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//　小さい山２段目右
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 600, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  ２段目床右
				SetBlock(D3DXVECTOR3(40 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目中央左
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目床左
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 11; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 1; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(520 + nCount * 40.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目上階段
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 220 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}

			//************************************
			// ブロックの配置「横壁」
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//  横壁
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 680, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  横壁
				SetBlock(D3DXVECTOR3(560 + nCount * 120.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 460, 40);
			}

			//************************************
			// ブロックの配置「土部分の床」
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//  １段目
				SetBlock(D3DXVECTOR3(200 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  １段目
				SetBlock(D3DXVECTOR3(920 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  小さい山の中
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  小さい山の中
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目上階段　草の下
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 260 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  ２段目上階段　土の下
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 300 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  ２段目上階段　土の下
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 340 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ２段目上階段　土の下
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 380 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 1; nCount++)
			{//  ２段目上階段　土の下
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 420 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// ブロックの配置「壊せるブロック」
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//  ２段目の壊せる床
				SetBlock(D3DXVECTOR3(200 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);
			}

			//************************************
			// ブロックの配置「落ちる床」
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//	２段目の落ちる床
				SetBlock(D3DXVECTOR3(920 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}

			//************************************
			// ブロックの配置「動かせる床」
			//************************************
			//　２段目上の動かせる床
			SetBlock(D3DXVECTOR3(400, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 160, 40);

			//************************************
			// ブロックの配置「ベルトコンベアー」
			//************************************

			//右に押される
			SetBlock(D3DXVECTOR3(1080, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 50, 120);
			//左に押される
			SetBlock(D3DXVECTOR3(760, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 50, 160);

			//************************************
			// アイテム「コイン」の配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(始まる位置 + カウント * コインとの横幅 , 設置の高さ , 0.0f ),D3DXCOLOR(RGBカラー),タイプ);
			}
			*/
			for (int nCount = 0; nCount < 4; nCount++)
			{//１段目山上のコイン
				SetItem(D3DXVECTOR3(220.0f + nCount * 40, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目上山上のコイン
				SetItem(D3DXVECTOR3(220.0f + nCount * 120, 610, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目上山上のコイン
				SetItem(D3DXVECTOR3(180.0f + nCount * 200, 610, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目上山上のコイン
				SetItem(D3DXVECTOR3(180.0f + nCount * 200, 655, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//２段目左上のコイン
				SetItem(D3DXVECTOR3(80.0f + nCount * 40, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//２段目左上のコイン
				SetItem(D3DXVECTOR3(80.0f + nCount * 40, 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//３段目に上がるときのコイン
				SetItem(D3DXVECTOR3(480.0f, 270.0f + nCount * 60, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//３段目上のコイン
				SetItem(D3DXVECTOR3(70.0f + nCount * 100, 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//３段目上のコイン
				SetItem(D3DXVECTOR3(120.0f + nCount * 100, 140, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  ２段目上階段
				SetItem(D3DXVECTOR3(740.0f + nCount * 40.0f, 190 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//	２段目落ちる床の下
				SetItem(D3DXVECTOR3(940.0f + nCount * 40.0f, 500, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目のベルトコンベヤーの左上
				SetItem(D3DXVECTOR3(800 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目のベルトコンベヤーの右上
				SetItem(D3DXVECTOR3(1120 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//１段目穴に落ちる時にとれるコイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f + nCount * 90.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//************************************
			// アイテム「赤コイン」の配置
			//************************************

			//中央飛び越えのところのコイン
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// ブロックの配置「透明なブロック」
			//************************************

			//１段目の上
			SetBlock(D3DXVECTOR3(520, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);

			//************************************
			// アイテム「時計」の配置
			//************************************

			//２段目右端
			SetItem(D3DXVECTOR3(1190, 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);


			//************************************
			// アイテム「骨付き肉」の配置
			//************************************

			//SetItem(D3DXVECTOR3(1190, 250, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7);

			//************************************
			// アイテム「見本コイン」の配置
			//************************************

			////検証用見本コイン
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);



			////検証用敵
			//SetEnemy(D3DXVECTOR3(200, 100, 0.0f), 0);

			//g_StageState = STAGENUM_3;		// ステージ3に移行
			//SetNumStage(g_StageState);		// ステージ番号表示
		}
//=================================================================================
//	ステージ３
//=================================================================================
		else if (g_StageState == STAGENUM_3)
		{
			//************************************
			// ブロックの配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
			}
			*/
			for (int nCount = 0; nCount < 10; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 10; nCount++)
			{//１段目右底床
				SetBlock(D3DXVECTOR3(880 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 11; nCount++)
			{//２段目右床
				SetBlock(D3DXVECTOR3(850 + nCount * 40.0f, 520, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 11; nCount++)
			{//２段目左床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 520, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 16; nCount++)
			{//３段目中央床
				SetBlock(D3DXVECTOR3(320 + nCount * 40.0f, 310, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//３段目中左床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//３段目中右床
				SetBlock(D3DXVECTOR3(1120 + nCount * 40.0f, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 13; nCount++)
			{//４段目右床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 140, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 13; nCount++)
			{//４段目左床
				SetBlock(D3DXVECTOR3(770 + nCount * 40.0f, 140, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40); /*(13 * 40 = 520) 520 + 520 = 1040 - 1280 = 140 + 520 = 660 + 110 = 770*/
			}
			//************************************
			// ブロックの配置「土部分の床」
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(0, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(1240, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// ブロックの配置「落ちる床」
			//************************************

			////検証用落ちる床（上に乗っかった時）
			SetBlock(D3DXVECTOR3(1040, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(1080, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);

			//************************************
			// ブロックの配置「壊せるブロック」
			//************************************

			////検証用壊せる床（下からの頭突き）
			SetBlock(D3DXVECTOR3(160, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);
			SetBlock(D3DXVECTOR3(200, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);

			//************************************
			// ブロックの配置「動かせる床」
			//************************************

			////検証用動かせる床
			SetBlock(D3DXVECTOR3(950, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 120, 50);

			//************************************
			// ブロックの配置「移動床」
			//************************************

			////検証用横移動床
			//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2, 520, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 40, 40);
			//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2, 640, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 40, 40);

			////検証用縦移動床左
//			SetBlock(D3DXVECTOR3(240, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
	//		SetBlock(D3DXVECTOR3(280, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

		//	////検証用縦移動床右
			//SetBlock(D3DXVECTOR3(960, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
			//SetBlock(D3DXVECTOR3(1000, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

			//************************************
			// ブロックの配置「ベルトコンベアー」
			//************************************

			//右に押される
			SetBlock(D3DXVECTOR3(400, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 50, 200);
			//左に押される
			SetBlock(D3DXVECTOR3(680, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 50, 200);

			//************************************
			// ブロックの配置「透明なブロック」
			//************************************

			////検証用透明ブロック
			SetBlock(D3DXVECTOR3(40, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);

			//************************************
			// ブロックの配置「お金箱」
			//************************************

			////検証用お金箱
			//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 10, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 40, 40);
			//SetBlock(D3DXVECTOR3(60,540, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 40, 40);

			//************************************
			// アイテム「コイン」の配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(始まる位置 + カウント * コインとの横幅 , 設置の高さ , 0.0f ),D3DXCOLOR(RGBカラー),タイプ);
			}
			*/
			for (int nCount = 0; nCount < 7; nCount++)
			{//１段目中央床上コイン
				SetItem(D3DXVECTOR3(460.0f + nCount * 60, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//１段目右端コイン
				SetItem(D3DXVECTOR3(1090.0f + nCount * 40, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
				SetItem(D3DXVECTOR3(1090.0f + nCount * 40, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//2段目左床上コイン
				SetItem(D3DXVECTOR3(30.0f + nCount * 60, 480, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//2段目中央コイン
				SetItem(D3DXVECTOR3(490.0f + nCount * 100, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//2段目右床上コイン
				SetItem(D3DXVECTOR3(1070.0f + nCount * 60, 480, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//上下移動床の上床上コイン
				SetItem(D3DXVECTOR3(280, 270.0f + nCount * 60, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//上下移動床の上床上コイン
				SetItem(D3DXVECTOR3(1000, 270.0f + nCount * 60, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 7; nCount++)
			{//3段目中央床上コイン
				SetItem(D3DXVECTOR3(430.0f + nCount * 70, 270, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//4段目右床コイン
				SetItem(D3DXVECTOR3(50.0f + nCount * 100, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//4段目左床コイン
				SetItem(D3DXVECTOR3(840.0f + nCount * 100, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//************************************
			// アイテム「磁石」の配置
			//************************************

			////検証用磁石
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);

			//************************************
			// アイテム「赤コイン」の配置
			//************************************

			////検証用赤コイン
			SetItem(D3DXVECTOR3(30, 220, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// アイテム「時計」の配置
			//************************************

			////検証用時計
			SetItem(D3DXVECTOR3(1230, 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

			//************************************
			// アイテム「宝箱」の配置
			//************************************

			////検証用宝箱
			//SetItem(D3DXVECTOR3(150, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);

			//************************************
			// アイテム「見本コイン」の配置
			//************************************

			////検証用見本コイン
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//g_StageState = STAGENUM_4;		// ステージ4に移行
			//SetNumStage(g_StageState);		// ステージ番号表示
		}
		else if (g_StageState == STAGENUM_4)
		{// ステージ４
			//************************************
			// ブロックの配置
			//************************************
			/*
			 for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
				SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
			}
			*/
			for (int nCount = 0; nCount < 32; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}

			//************************************
			// ブロックの配置「ゴールドブロック」
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 80 + nCount * 40.0f , 120, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 120 + nCount * 200.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 160 + nCount * 280.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 160 + nCount * 280.0f, 240, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 160, 280 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 120 + nCount * 200.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 40 + nCount * 40.0f, 520, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 120, 400 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//ボーナスブロック！
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40 + nCount * 40.0f,360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}

			// ブロックの配置「横壁」
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//  横壁
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 680, 40);
			}

			//************************************
			// アイテム「コイン」の配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(始まる位置 + カウント * コインとの横幅 , 設置の高さ , 0.0f ),D3DXCOLOR(RGBカラー),タイプ);
			}
			*/
			for (int nCount = 0; nCount < 4; nCount++)
			{//１段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 60 + nCount * 40.0f, 180, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//２段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//３段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 260, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//４段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 300, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//５段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 340, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//６段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 380, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//７段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//８段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 460, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//９段目コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 60 + nCount * 40.0f, 500, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//************************************
			// アイテム「赤コイン」の配置
			//************************************
			////検証用赤コイン
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// アイテム「見本コイン」の配置
			//************************************

			////検証用見本コイン
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//************************************
			// アイテム「ショップ」の配置
			//************************************

			////検証用時計
			SetItem(D3DXVECTOR3(250, 580, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 9);

			//g_StageState = STAGENUM_5;		// ステージ5に移行
			//SetNumStage(g_StageState);		// ステージ番号表示
		}
		else if (g_StageState == STAGENUM_5)
		{// ステージ５
		 //************************************
		 // ブロックの配置
		 //************************************
		 /*
		 for (カウント初期化; カウント回数 < ブロック個数; カウント++)
		 {
		 SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
		 }
		 */
		 //初期リスポーン落ちないように
			SetBlock(D3DXVECTOR3(160, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			for (int nCount = 0; nCount < 7; nCount++)
			{//  １段目床左
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//  １段目床中央
				SetBlock(D3DXVECTOR3(360 + nCount * 120.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 7; nCount++)
			{//  １段目床右
				SetBlock(D3DXVECTOR3(1000 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 14; nCount++)
			{//  ２段目床右
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(560, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			for (int nCount = 0; nCount < 2; nCount++)
			{//  ２段目床毒との間
				SetBlock(D3DXVECTOR3(760 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  ２段目床毒との間
				SetBlock(D3DXVECTOR3(880 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ２段目床毒との間
				SetBlock(D3DXVECTOR3(1000 + nCount * 80.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ２段目床右
				SetBlock(D3DXVECTOR3(1200 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ３段目床右左　落ちる床との間　
				SetBlock(D3DXVECTOR3(760 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  ３段目床右中　落ちる床との間
				SetBlock(D3DXVECTOR3(880 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 1; nCount++)
			{//  ３段目床右右　落ちる床との間
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ３段目床右右　落ちる床との間
				SetBlock(D3DXVECTOR3(1200 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 13; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 9; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(120 + nCount * 40.0f, 280, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(640, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			SetBlock(D3DXVECTOR3(680, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			//************************************
			// ブロックの配置「横壁」
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//  横壁
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 440, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 240, 40);
			}
			//真ん中の仕切り
			SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 40, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 400, 40);
			for (int nCount = 0; nCount < 2; nCount++)
			{//  横壁
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 200, 40);
			}

			//************************************
			// ブロックの配置「土部分の床」
			//************************************
			//草ブロックのした
			for (int nCount = 0; nCount < 3; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(560 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  ３段目床左
				SetBlock(D3DXVECTOR3(480, 200 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// ブロックの配置「押せる壁」
			//************************************
			//両方押せる逆方向偽床
			SetBlock(D3DXVECTOR3(1000, 560, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 14, 120, 80);

			//************************************
			// ブロックの配置「動かせる床」
			//************************************
			////検証用動かせる床右
			SetBlock(D3DXVECTOR3(160, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 80, 40);

			//************************************
			// ブロックの配置「動かせる床」
			//************************************
			////検証用動かせる床左
			SetBlock(D3DXVECTOR3(440, 320, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 15, 80, 40);

			//************************************
			// ブロックの配置「毒」
			//************************************
			//for (int nCount = 0; nCount < 2; nCount++)
			//{//毒の床
			//	SetBlock(D3DXVECTOR3(720 + nCount * 120.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 40, 40);
			//}
			//毒の床
			//SetBlock(D3DXVECTOR3(1040, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 40, 40);

			//************************************
			// ブロックの配置「落ちる床」
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//下に落ちる床　下には毒
				SetBlock(D3DXVECTOR3(720 + nCount * 120.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//下に落ちる床　下には毒
				SetBlock(D3DXVECTOR3(1120 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			//下に落ちる床　下には毒
			SetBlock(D3DXVECTOR3(1040, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);

			//************************************
			// アイテム「コイン」の配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(始まる位置 + カウント * コインとの横幅 , 設置の高さ , 0.0f ),D3DXCOLOR(RGBカラー),タイプ);
			}
			*/
			for (int nCount = 0; nCount < 7; nCount++)
			{//１段目ジャンプ１段目コイン
				SetItem(D3DXVECTOR3(260.0f + nCount * 120, 630, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//１段目ジャンプ２段目コイン
				SetItem(D3DXVECTOR3(320.0f + nCount * 120, 470, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目ジャンプ２段目コイン
				SetItem(D3DXVECTOR3(1100.0f + nCount * 30, 630, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//２段目毒上１段目コイン
				SetItem(D3DXVECTOR3(740.0f + nCount * 80, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//２段目から３段目のジャンプコイン
				SetItem(D3DXVECTOR3(660, 220 + nCount * 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//少しずらしたコイン　ジャンプの軌道
			SetItem(D3DXVECTOR3(695, 175, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);

			for (int nCount = 0; nCount < 2; nCount++)
			{//３段目落ちるブロックの上
				SetItem(D3DXVECTOR3(740.0f + nCount * 120.0f, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//３段目落ちるブロックの上
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40.0f, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//３段目落ちるブロックの上
			SetItem(D3DXVECTOR3(1060, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);

			for (int nCount = 0; nCount < 6; nCount++)
			{//３段目左上
				SetItem(D3DXVECTOR3(60.0f + nCount * 80.0f, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//３段目左下
				SetItem(D3DXVECTOR3(80.0f + nCount * 80.0f, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//３段目左中央
				SetItem(D3DXVECTOR3(230.0f + nCount * 52.0f, 240, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}

			//************************************
			// アイテム「見本コイン」の配置
			//************************************

			////検証用見本コイン
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//************************************
			// アイテム「赤コイン」の配置
			//************************************

			////検証用赤コイン
			SetItem(D3DXVECTOR3(440, 240, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// アイテム「時計」の配置
			//************************************

			////検証用時計
			SetItem(D3DXVECTOR3(1210, 240, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

			//************************************
			// アイテム「骨付き肉」の配置
			//************************************

			////検証用時計
			SetItem(D3DXVECTOR3(1210, 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7);

			//g_StageState = STAGENUM_6;		// ステージ6に移行
			//SetNumStage(g_StageState);		// ステージ番号表示
		}
		else if (g_StageState == STAGENUM_6)
		{// ステージ６
		 //************************************
		 // ブロックの配置
		 //************************************
			 /*
			 for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			 {
				 SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
			 }
			 */
			for (int nCount = 0; nCount < 5; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//１段目中央ジャンプ
				SetBlock(D3DXVECTOR3(320 + nCount * 160.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目右床
				SetBlock(D3DXVECTOR3(1120 + nCount * 40.0f, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 8; nCount++)
			{//２段目床
				SetBlock(D3DXVECTOR3(200 + nCount * 120.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(1080, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			for (int nCount = 0; nCount < 6; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(40 + nCount * 40.0f, nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 200 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(560 + nCount * 120.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(1240, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

		//************************************
		// ブロックの「とげ」配置
		//************************************
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(200 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(520 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(680 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(1000 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}

		//************************************
		// ブロックの配置「横壁」
		//************************************
			SetBlock(D3DXVECTOR3(0, 440, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 240, 40);
			SetBlock(D3DXVECTOR3(1240, 240, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 360, 40);


		//************************************
		// ブロックの配置「動く壁」
		//************************************

			////検証用動く壁
			SetBlock(D3DXVECTOR3(0, 440, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 21, 240, 40);

		//************************************
		// ブロックの配置「動く壁」
		//************************************

			////検証用動く壁早いやつ
			SetBlock(D3DXVECTOR3(0, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 22, 200, 40);

		//************************************
		// ブロックの配置「土部分の床」
		//************************************
			//草ブロックのした
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目右床
				SetBlock(D3DXVECTOR3(1160 + nCount * 40.0f, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目右床
				SetBlock(D3DXVECTOR3(1200 + nCount * 40.0f, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			SetBlock(D3DXVECTOR3(1240, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);

			for (int nCount = 0; nCount < 5; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 240 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 280 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 320 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//3段目床
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 360 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			SetBlock(D3DXVECTOR3(0, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);

		//************************************
		// ブロックの「毒」配置
		//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(480 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(600 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}

		//************************************
		// ブロックの配置「落ちる床」
		//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(480 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(600 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目左底床
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}

			//************************************
			// アイテム「見本コイン」の配置
			//************************************

			////検証用見本コイン
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//************************************
			// アイテム「コイン」の配置
			//************************************
			/*
			for (カウント初期化; カウント回数 < ブロック個数; カウント++)
			{
			SetBlock(D3DXVECTOR3(始まる位置 + カウント * コインとの横幅 , 設置の高さ , 0.0f ),D3DXCOLOR(RGBカラー),タイプ);
			}
			*/
			SetItem(D3DXVECTOR3(1140.0f , 670, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);

			for (int nCount = 0; nCount < 2; nCount++)
			{//１段目山上のコイン
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 620, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目山上のコイン
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 570, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目山上のコイン
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 520, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目山上のコイン
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 470, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//１段目山上のコイン
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 8; nCount++)
			{//２段目山上のコイン
				SetItem(D3DXVECTOR3(220 + nCount * 120.0f, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 9; nCount++)
			{//２段目山上のコイン
				SetItem(D3DXVECTOR3(230 + nCount * 120.0f, 110, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}


			////************************************
			//// アイテム「赤コイン」の配置
			////************************************
			for (int nCount = 0; nCount < 7; nCount++)
			{
				////検証用赤コイン
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 4  + nCount * 110.0f, 230, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);
			}

			//************************************
			// アイテム「時計」の配置
			//************************************

			////検証用時計
			SetItem(D3DXVECTOR3(1210, 240, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

		}
		//else if (g_StageState == STAGENUM_7)
		//{// ステージ７
		// //************************************
		// // ブロックの配置
		// //************************************
		//	/*
		//	 for (カウント初期化; カウント回数 < ブロック個数; カウント++)
		//	{
		//	 SetBlock(D3DXVECTOR3(カウント * ブロックの横幅 , 設置の高さ , 0) タイプ , 高さ , 幅);
		//	 }
		//	*/

		//	for (int nCount = 0; nCount < 32; nCount++)
		//	{//  １段目床左
		//		SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
		//	}
		//}
		g_nCntSetStage = 1;
	}
}

