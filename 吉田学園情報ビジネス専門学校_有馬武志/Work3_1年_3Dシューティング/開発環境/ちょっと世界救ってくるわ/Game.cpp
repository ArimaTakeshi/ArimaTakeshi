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
#include "pause.h"			//ポーズ
#include "explosion.h"		//爆発
#include "meshbg.h"			//メッシュシリンダー
#include "meshfield.h"		//メッシュフィールド
#include "wall.h"			//壁
#include "shadow.h"			//影
#include "object.h"			//オブジェクト
#include "billboord.h"		//ビルボード
#include "bullet.h"			//バレット
#include "effect.h"			//エフェクト
#include "light.h"			//ライト
#include "camera.h"			//カメラ
#include "sound.h"			//サウンド
#include "score.h"			//スコア
#include "time.h"			//タイム
#include "camera.h"			//カメラ
#include "herimodel.h"		//ヘリモデル
#include "frame.h"			//枠
#include "length.h"			//エンジン
#include "item.h"			//アイテム
#include "possession.h"		//持ち物
#include "Blood.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
GAMESTATE g_gameState;						//ゲーム状態
int g_nCounterGameState;					//状態カウンター
bool g_bPause;								//ポーズ
bool g_bMenu;								//メニュー

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitGame(void)
{
	//カメラのぽいんた　
	Camera *pCamera = GetCamera();
	g_gameState = GAMESTATE_NONE;	//ゲーム状態
	g_nCounterGameState = 0;

	// ポリゴンの初期化処理
	//InitPolygon();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();

	//背景の初期化処理
	InitMeshBg();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//壁の初期化処理
	InitWall();

	//影の初期化処理
	InitShadow();

	//モデルの初期化処理
	//InitPlayer();

	//ヘリモデルの初期化
	InitPlayer2();

	//オブジェクトの初期化処理
	InitObject();

	//ビルボードの初期化処理
	InitBillBoord();

	//弾の初期化処理
	InitBullet();

	// 血の初期化処理
	InitBlood();

	//エフェクトの初期化処理
	InitEffect();

	//爆発の初期化処理
	InitExplosion();

	//スコアの初期化処理
	InitScore();

	//タイムの初期化処理
	InitTime();

	//距離の初期化処理
	InitLength();

	//枠の初期化処理
	InitFrame();

	//ポーズの初期化処理
	InitPause();

	//スコアの表示
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 580, SCREEN_HEIGHT / 2 - 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 50);

#if 1

	{//正面3番目右側の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(855, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(855, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(855, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(855, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(855, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(855, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//正面2番目右側の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(445, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(445, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(445, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(445, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(445, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(445, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//正面1番目右側の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(159, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(159, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(159, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(159, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(159, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(159, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//真ん中の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-59, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-59, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-59, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-59, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-59, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-59, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//正面3地番左側の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-1059, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-1059, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-1059, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-1059, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//正面2番目左側の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-759, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-759, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-759, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-759, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-759, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-759, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//正面1番目左側の大通り
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-465, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-465, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-465, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-465, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-465, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//ビルボード
			SetBillBoord(D3DXVECTOR3(-465, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	//ゾンビ縦列
#if 1
	//
	//左２
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, -985.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, -930.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, -950.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, -970.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//左１
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, -485.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, -430.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, -450.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, -470.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//中心
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, 20.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, 65.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, 40.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, 60.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//右１
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, 520.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, 565.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, 540.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, 560.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//右２
	//
	//ゾンビ
	for (int nCount = 0; nCount < 20; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1080.0f + nCount * 90.0f + rand() % (2 * 5), 0, 1020.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1000.0f + nCount * 70.0f + rand() % (2 * 5), 0, 1065.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 25; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1050.0f + nCount * 80.0f + rand() % (2 * 5), 0, 1040.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1100.0f + nCount * 70.0f + rand() % (2 * 5), 0, 1060.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
#endif
	//ゾンビ横列
#if 1
	//
	//左４
	//
	//ゾンビ
	for (int nCount = 0; nCount < 25; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(1170.0f + rand() % (2 * 5), 0, -900.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(1190.0f + rand() % (2 * 5), 0, -850.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(1210.0f + rand() % (2 * 5), 0, -890.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(1240.0f + rand() % (2 * 5), 0, -900.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//左３
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(870.0f + rand() % (2 * 5), 0, -1200.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(890.0f + rand() % (2 * 5), 0, -1150.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(910.0f + rand() % (2 * 5), 0, -1190.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(940.0f + rand() % (2 * 5), 0, -1200.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//左２
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(470.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(490.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(510.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(540.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//左１
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(170.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(190.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(210.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(240.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//中央
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-70.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-90.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-110.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-140.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//右１
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-470.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-490.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-510.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-540.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//右２
	//
	//ゾンビ
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-770.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-790.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-810.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-840.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//右３
	//
	//ゾンビ
	for (int nCount = 0; nCount < 25; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1070.0f + rand() % (2 * 5), 0, -1000.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1140.0f + rand() % (2 * 5), 0, -1000.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1110.0f + rand() % (2 * 5), 0, -990.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1090.0f + rand() % (2 * 5), 0, -950.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
#endif
#endif

	//オブジェクト
	SetObject(D3DXVECTOR3(40,0,-95),D3DXVECTOR3(0,0,0));
	SetObject(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, 0, 0));

	g_gameState = GAMESTATE_NORMAL;		//通常状態に設定

	//ポーズを使用してない状態にする
	g_bPause = false;

	g_bMenu = false;
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitGame(void)
{
	// カメラの終了処理
	UninitCamera();

	// ライトの終了処理
	UninitLight();

	//爆発の終了処理
	UninitExplosion();

	//背景の終了処理
	UninitMeshBg();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//壁の終了処理
	UninitWall();

	//ヘリモデルの初期化
	UninitPlayer2();

	//オブジェクトの終了処理
	UninitObject();

	//影の終了処理
	UninitShadow();

	//弾の終了処理
	UninitBullet();

	//血の終了処理
	UninitBlood();

	//エフェクトの終了処理
	UninitEffect();

	//ビルボードの終了処理
	UninitBillBoord();

	//爆発の終了処理
	UninitExplosion();

	//スコアの終了処理
	UninitScore();

	//タイムの終了処理
	UninitTime();

	//距離の終了処理
	UninitLength();

	//枠の終了処理
	UninitFrame();

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
		//カメラの更新処理
		UpdateCamera();

		//ライトの更新処理
		UpdateLight();

		//爆発の更新処理
		UpdateExplosion();

		//背景の更新処理
		UpdateMeshBg();

		//メッシュフィールドの更新処理
		UpdateMeshField();

		//壁の更新処理
		UpdateWall();

		//モデルの更新処理
		//UpdatePlayer();

		//ヘリモデルの初期化
		UpdatePlayer2();

		//オブジェクトの更新処理
		UpdateObject();

		//影の更新処理
		UpdateShadow();

		//ビルボードの更新処理
		UpdateBillBoord();

		//弾の更新処理
		UpdateBullet();

		//エフェクトの更新処理
		UpdateEffect();

		//爆発の更新処理
		UpdateExplosion();

		//血の更新処理
		UpdateBlood();

		//タイムの更新処理
		UpdateTime();

		//距離の更新処理
		UpdateLength();

		//枠の更新処理
		UpdateFrame();

		//スコアの更新処理
		UpdateScore();
	}
	else if (g_bPause == true)
	{//trueになったらポーズを更新する
		//ポーズの更新処理
		UpdatePause();
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 120)
		{
			// = GAMESTATE_NONE;
			//画面（モード）の設定
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawGame(void)
{
	//カメラの描画処理
	SetCamera(CAMERA_TYPE_GAME);

	//背景の描画処理
	DrawMeshBg();

	//メッシュフィールドの描画処理
	DrawMeshField();

	//壁の描画処理
	DrawWall();

	//ヘリモデルの初期化
	DrawPlayer2();

	//オブジェクトの描画処理
	DrawObject();

	//血の描画処理
	DrawBlood();

	//影の描画処理
	DrawShadow();

	//ビルボードの描画処理
	DrawBillBoord();

	//弾の描画処理
	DrawBullet();

	//エフェクトの描画処理
	DrawEffect();

	//爆発の描画処理
	DrawExplosion();

	//枠の描画処理
	DrawFrame();

	//距離の描画処理
	DrawLength();

	//スコアの描画処理
	DrawScore();

	if (g_bPause == true)
	{//ポーズがtrueだったら
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