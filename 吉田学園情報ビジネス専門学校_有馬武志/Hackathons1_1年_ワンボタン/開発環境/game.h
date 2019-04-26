#pragma once
//=========================================================================================================//
//
// ポリゴン：プロトタイプ宣言 [Scan.h]
// Author : Ryo Sugimoto
//
//=========================================================================================================//
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"main.h"

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define PLAYER_POSX			(SCREEN_GAMEX / 2 - 22)					//画像のX
#define PLAYER_POSY			(SCREEN_HEIGHT / 4 * 3)					//画像のY
#define PLAYER_POSX2			(SCREEN_GAMEX / 2 + 22)					//画像のX2
#define PLAYER_POSY2			(SCREEN_HEIGHT / 4 * 3 + 44)			//画像のY2
#define PLAYER_POSX3			(80)	//画像のXの幅 / 2
#define PLAYER_POSY3			(80)	//画像のYの幅 / 2
#define POSPLAYERX				((PLAYER_POSX + PLAYER_POSX2) / 2)	//Xの中心
#define POSPLAYERY				((PLAYER_POSY + PLAYER_POSY2) / 2)	//Yの中心

#define BULLET_ATKTYPE0			(0)										//通常弾
#define BULLET_ATKTYPE1			(1)										//光線
#define BULLET_ATKTYPE50		(50)									//装飾
#define BULLET_ATKTYPE99		(99)									//ナイフ！
#define KNIFE_TIME				(BULLET_ATKTYPE99 + 6)					//ナイフの有効時間

#define HALF_EXPLOSION			(30)									//爆発の幅高さ
#define GUARD_BREAK				(481)			//GUARD発動までの時間

#define MAX_SCORE		(5 * 4)		//5位*難易度分
#define RANK_SCORE		(5)			//ランキングに使われているスコア

#define	MAX_BULLET			(3840)				// 弾の最大数
#define BULLET_SLIP			(0.15f)				//弾の滑り
#define BULLET_DELETE		(200)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
	GAMESTATE_PAUSE

}GAMESTATE;

typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

typedef struct
{
	GAMESTATE now;		//現在の状態
	MODE CHANGE;		//変えるモード
	int nCntGameState;	//カウント用

}GAME;

typedef struct
{
	D3DXVECTOR3 pos;	//ポリゴンの位置
	D3DXVECTOR3 move;	//ポリゴンの移動量
	int nCntAnim;		//カウント用
	int nPtnAnim;		//パターン数
	int nLevel;			//Level
	int nHP;			//HP
	int nMAX_HP;
	int nAttack;		//攻撃
	int nDefense;		//防御
	int nJump;			//Jump
	int nMeter;			//進んだ距離
	int nMAX_EXP;		//次のレベルまでの経験値
	int nEXP;			//取得した経験値
	int nGold;			//お金
	int nScore;
	float fAngle;		//角度
	bool bMove;			//背景を動かすかどうか
	bool bUse;			//生存 or 死亡

}PLAYER;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 move;		// 移動値の残り火
	D3DXCOLOR col;			// 色
	float fSteep;			//角度
	float fSpeed;
	float fRadius;			// 半径(大きさ)
	bool bUse;				// 使用しているかどうか

} EFFECT;

//*********************************************************************************************************//
// プロトタイプ宣言　Game
//*********************************************************************************************************//
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAME *GetGameState(void);
void SetGameState(GAMESTATE game, MODE mode, int nCntGameState);

//*********************************************************************************************************//
// プロトタイプ宣言　ポリゴン
//*********************************************************************************************************//
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
bool HitAim(D3DXVECTOR3 aim, int nLength);
void EnemyAppears(void);
void HitPlayer(int nAtk);

//*****************************************************************************
// プロトタイプ宣言  window
//*****************************************************************************
void InitGameWindow(void);
void UninitGameWindow(void);
void UpdateGameWindow(void);
void DrawGameWindow(void);
void SetGameWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, WINDOWSTATE state, WINDOWUSE use);
void BreakGameWindow(void);
void BackGameWindow(int nNumber);
void ChangeGameWindow(int nNumber, WINDOWSTATE state);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
EFFECT *GetEffect(void);

#endif