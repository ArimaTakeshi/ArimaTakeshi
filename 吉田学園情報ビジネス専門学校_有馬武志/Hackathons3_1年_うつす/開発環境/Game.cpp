//=========================================================================================================================
//
// ゲームの処理 [game.cpp]
// Author : 有馬　武志　＆　内山
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
#include "effect.h"			//エフェクト
#include "light.h"			//ライト
#include "camera.h"			//カメラ
#include "sound.h"			//サウンド
#include "time.h"			//タイム
#include "camera.h"			//カメラ
#include "frame.h"			//枠
#include "wall.h"
#include "objectnot.h"
#include "enemy.h"			//鬼
#include "window.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
GAMESTATE g_gameState;			//ゲーム状態
int g_nCounterGameState;		//状態カウンター
bool g_bPause;					//ポーズ
bool g_bMenu;					//メニュー

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitGame(void)
{
	//カメラのぽいんた　
	Camera *pCamera = GetCamera();
	StopSound();
	g_gameState = GAMESTATE_NONE;	//ゲーム状態
	g_nCounterGameState = 0;

	// ポリゴンの初期化処理
	//InitPolygon();

	// カメラの初期化処理
	InitCamera();

	// ライトの初期化処理
	InitLight();
	SetLight(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.8f));

	//背景の初期化処理
	InitMeshBg();
	InitWindow();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//壁の初期化処理
	InitWall();

	//影の初期化処理
	InitShadow();

	//モデルの初期化処理
	InitPlayer();

	//鬼の初期化処理
	InitEnemy();

	//オブジェクトの初期化処理
	InitObject();

	InitObjectNot();

	//ビルボードの初期化処理
	InitBillBoord();

	//エフェクトの初期化処理
	InitEffect();

	//爆発の初期化処理
	InitExplosion();

	InitTime();

	//画面に出す画像の初期化処理
	InitFrame();


	//ポーズの初期化処理
	InitPause();

#if 1
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
#endif

	//壁の配置
	//上
	SetWall(D3DXVECTOR3(2000, 0, 250), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f));
	//右
	SetWall(D3DXVECTOR3(4250, 0, -2000), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f));
	//下
	SetWall(D3DXVECTOR3(2000, 0, -4250), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f));
	//左
	SetWall(D3DXVECTOR3(-250, 0, -2000), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f));

	//アイテムの設置
	//SetItem(D3DXVECTOR3(-1000, 70, -300), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEM_GASOLINE, 0);

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

	// ポリゴンの終了処理
	//UninitPolygon();

	//背景の終了処理
	UninitMeshBg();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//壁の終了処理
	UninitWall();

	//モデルの終了処理
	UninitPlayer();

	//鬼の終了処理
	UninitEnemy();

	//オブジェクトの終了処理
	UninitObject();

	UninitObjectNot();

	//影の終了処理
	UninitShadow();

	//エフェクトの終了処理
	UninitEffect();

	//ビルボードの終了処理
	UninitBillBoord();

	//爆発の終了処理
	UninitExplosion();

	//時間の終了処理
	UninitTime();

	//画面に出す画像の終了処理
	UninitFrame();

	UninitWindow();

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
			PlaySound(SOUND_LABEL_SE_PBUTTUN);
		}
		else
		{//決定音
			PlaySound(SOUND_LABEL_SE_ENTER);
		}
	}
	if (g_bPause == false && g_bMenu == false)
	{//普段はfalseにしている
		/*if (GetKeyboardTrigger(DIK_H) == true)
		{
			SetFade(MODE_RESULT);
		}*/
		//カメラの更新処理
		UpdateCamera();

		//ライトの更新処理
		UpdateLight();

		//爆発の更新処理
		UpdateExplosion();

		// ポリゴンの更新処理
		//UpdatePolygon();

		//背景の更新処理
		UpdateMeshBg();

		//メッシュフィールドの更新処理
		UpdateMeshField();

		//壁の更新処理
		UpdateWall();

		//モデルの更新処理
		UpdatePlayer();

		//鬼の初期化処理
		UpdateEnemy();

		//オブジェクトの更新処理
		UpdateObject();

		//あたり判定のないオブジェクトの更新処理
		UpdateObjectNot();

		//影の更新処理
		UpdateShadow();

		//ビルボードの更新処理
		UpdateBillBoord();

		//エフェクトの更新処理
		UpdateEffect();

		//爆発の更新処理
		UpdateExplosion();

		//タイムの更新処理
		UpdateTime();
	
		//画面に出す画像の更新処理
		UpdateFrame();

		UpdateWindow();
	}
	else if (g_bPause == true)
	{//trueになったらポーズを更新する
		//ポーズの更新処理
		UpdatePause();
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		//g_nCounterGameState = 0;

		break;
	case GAMESTATE_CLEAR:
		
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState == 30)
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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//画面のクリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(210, 210, 255, 0), 1.0f, 0);

	//ビューポートの取得
	D3DVIEWPORT9 ViewPortDef;
	pDevice->GetViewport(&ViewPortDef);

	for (int nCount = 0; nCount < 2; nCount++)
	{
		// カメラの設定
		SetCamera(CAMERA_TYPE_GAME, nCount);

		//背景の描画処理
		DrawMeshBg();

		//メッシュフィールドの描画処理
		DrawMeshField();

		//壁の描画処理
		DrawWall();

		if (nCount != 0)
		{
			//モデルの描画処理
			DrawPlayer();
		}

		//オブジェクトの描画処理
		DrawObject();

		//あたり判定のないオブジェクトの描画処理
		DrawObjectNot();

		//影の描画処理
		DrawShadow();

		//ビルボードの描画処理
		DrawBillBoord();

		if (nCount != 0)
		{
			//エフェクトの描画処理
			DrawEffect();
		}
		//爆発の描画処理

		//画面に出す画像の描画処理
		DrawFrame();
		DrawWindow();
		DrawExplosion();

		DrawTime();
	}
	//戻す
	pDevice->SetViewport(&ViewPortDef);


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