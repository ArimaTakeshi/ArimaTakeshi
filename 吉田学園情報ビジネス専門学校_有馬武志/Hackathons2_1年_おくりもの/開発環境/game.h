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
#define PLAYER_POSX3			(60)	//画像のXの幅 / 2
#define PLAYER_POSY3			(45)	//画像のYの幅 / 2
#define PLAYER_CollisionX		(18)	//画像のXのあたり判定
#define PLAYER_CollisionY		(28)	//画像のYのあたり判定
#define FIELD					(60)

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

typedef struct
{
	GAMESTATE now;		//現在の状態
	MODE CHANGE;		//変えるモード
	int nCntGameState;	//カウント用

}GAME;

typedef enum
{//アニメーションの使用状態
	EXPLOSIONSTATE_PHIT,		//プレイヤーにあたり判定のある爆発
	EXPLOSIONSTATE_PHITMINUS,	//プレイヤーにあたり判定のある爆発 判定の小さい
	EXPLOSIONSTATE_EHIT,		//敵にあたり判定のある爆発
	EXPLOSIONSTATE_EFFECT,		//あたり判定無し
	EXPLOSIONSTATE_DELETE,		//消えていく
}EXPLOSIONSTATE;
typedef enum
{//プレイヤーか敵か
	USETYPE_PLAYER = 0,		//自機
	USETYPE_PLAYERANIM,		//自機のAnimation
	USETYPE_ENEMY,			//敵
	USETYPE_IGNORE,			//無視
	USETYPE_MAX,

}USETYPE;
typedef enum
{
	PLAYERANGLE_RIGHT = 0,
	PLAYERANGLE_LEFT,

}PLAYERANGLE;
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_INVINCBLE,		//無敵状態
	PLAYERSTATE_DNORMAL,		//しゃがみ後ジャンプが一回しかできないのを防ぐ
	PLAYERSTATE_FALL,			//すり抜け状態
	PLAYERSTATE_ATTACK,			//攻撃状態　連打中
	PLAYERSTATE_SATTACK,		//空中攻撃状態　連打中
	PLAYERSTATE_SKYATTACK,		//攻撃状態への移行　回転中
	PLAYERSTATE_WAIT,			//攻撃状態への待機　回転後
	PLAYERSTATE_CATCH,			//崖つかまり状態
	PLAYERSTATE_CLIMBR,			//崖を上っている状態
	PLAYERSTATE_CLIMBL,			//崖を上っている状態
	PLAYERSTATE_BACK,			//ノックバック状態
	PLAYERSTATE_DOWN,			//しゃがみ状態
	PLAYERSTATE_KNOCKBACK,		//ノックバック状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態

}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 respawn;	//ポリゴンの位置
	D3DXVECTOR3 pos;	//ポリゴンの位置
	D3DXVECTOR3 posold;	//ポリゴンの位置
	D3DXVECTOR3 move;	//ポリゴンの移動量
	D3DXCOLOR col;
	PLAYERSTATE state;	//状態
	int nCntState[2];	//状態の管理用
	int nVibration;		//ゲージが振動する時間
	int nScore;			//スコア
	int nTime[2];		//時間カウント
	int nJump;			//ジャンプ数
	int nPtnAnim;		//画像のパターン
	int nCntAnim;		//画像のカウンター
	int nAnimSpeed;		//アニメーションSPEED
	int nAngle;			//向き
	int nLengthX;
	int nLengthY;
	int nCollisionX;
	int nCollisionY;
	int nLevel;
	int nLevelold;
	int nEXP;
	int nMAXEXP;
	int nEXPold;
	int nMAXEXPold;
	int nLife;
	int nLifeold;
	int nMaxLife;
	int nAttack;
	int nDefense;
	int nPresent[3];
	int nClear;
	float fSkyWait;
	float fSteep;		//ポリゴンの角度
	float fRide;		//乗っているものからの移動値
	float fMove;		//空中の時の移動値
	bool bPowerUP[10];	//パワーアップ素材取得情報
	bool bClock[10];	//時計取得情報
	bool bPowerUPold[10];	//パワーアップ素材取得情報
	bool bClockold[10];		//時計取得情報
	bool bRun;			//走っているかどうか
	bool bFall;			//落ちたか飛んだか
	bool bUse;			//生存 or 死亡

}PLAYER;

typedef enum
{
	BLOCKSTATE_NONE = 0,	//何もないブロック
	BLOCKSTATE_THIN,		//上判定しかないブロック
	BLOCKSTATE_THIN0,		//煙突
	BLOCKSTATE_THIN1,		//無限煙突
	BLOCKSTATE_THIN2,		//使用済み煙突
	BLOCKSTATE_MOVE,		//動くブロック
	BLOCKSTATE_BREAK,		//壊れるブロック
	BLOCKSTATE_DAMAGE,		//ダメージを与えるブロック
	BLOCKSTATE_DESS,		//当たると死亡
	BLOCKSTATE_OUT,			//場外判定　当たると死亡
	BLOCKSTATE_FADE,		//自機に当たると消え、当たっていないと黒くなる
	BLOCKSTATE_BG,			//あたり判定のないブロック
	BLOCKSTATE_BOARD,		//あたり判定のないブロック
	BLOCKSTATE_CLEAR,		//クリアブロック

}BLOCKSTATE;

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

typedef enum
{
	ANIMTYPE_COIN = 0,	//コイン
	ANIMTYPE_CHECK0,		//復活地点更新
	ANIMTYPE_CHECK1,		//使用済み復活地点
	ANIMTYPE_POWERUP,		//パワーアップItem
	ANIMTYPE_HEEL,			//回復
	ANIMTYPE_ALLHEEL,		//全回復
	ANIMTYPE_CLOCK,			//時計
	ANIMTYPE_BOARD,		//看板
	ANIMTYPE_MESSAGE,	//看板から出るメッセージ
	ANIMTYPE_NONE,		//スクロールしないもの

}ANIMTYPE;
typedef enum
{//アニメーションの使用状態
	ANIMATION_NORMAL = 0,
	ANIMATION_LOOP,
	ANIMATION_PLAYER,			//プレイヤーのパターンに応じて変更
	ANIMATION_MAX,

}ANIMATION;

typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_EFFECT,

}BULLETTYPE;
typedef enum
{
	BULLETSTATE_NONE = 0,		//何もなし
	BULLETSTATE_NORMAL,			//何もなし
	BULLETSTATE_NOT,			//使用していない
	BULLETSTATE_START,			//開始のみ加速
	BULLETSTATE_ACCELERATOR,	//加速し続ける
	BULLETSTATE_DELETE,			//消えていく
	BULLETSTATE_SINGLE,			//1Fだけの命
	BULLETSTATE_THIRD,			//3Fだけの命
	BULLETSTATE_FIFTH,			//5Fだけの命
	BULLETSTATE_GRAVITY,		//重力

}BULLETSTATE;
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//位置
	D3DXVECTOR3 move;	//移動
	D3DXCOLOR col;
	BULLETSTATE state;	//弾の状態
	int nCntState;	//弾の状態用 STOP等の時間も保存
	int nLengthX;		//幅X
	int nLengthY;		//幅Y
	int nType;			//画像の種類
	BULLETTYPE nShot;			//誰が撃ったか
	int nAtk;			//攻撃力
	int nCntEnemy;		//敵だってナイフ振りたいんです！
	float steep;		//傾き
	float fCurve;		//角度変化用
	float fSpeed;		//弾のスピード
	bool bUse;			//使用or不使用
}Bullet;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 initpos;//初期位置
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posold;	//位置
	D3DXVECTOR3 col;	//色
	int nLengthX;		//Xの長さ
	int nLengthY;		//Yの長さ
	int nCntAnim;		//Animationのカウント
	int nPtnAnim;		//指定された座標で表示
	int nPtnHeight;		//画像の縦の分割数
	int nPtnWide;		//画像の横の分割数
	int nPtnSpeed;		//Animation速度
	int nType;			//画像の指定
	int nCntState;
	ANIMATION anim;		//アニメーションの使い方
	ANIMTYPE type;	//種類
	bool bUse;
}Animation;

//*********************************************************************************************************//
// 構造体定義
//*********************************************************************************************************//
typedef enum
{//スコアの状態
	DIGITALSTATE_NONE = 0,
	DIGITALSTATE_WAVE,
	DIGITALSTATE_DAMAGE,		//斜め右下にスライド
	DIGITALSTATE_HEEL,			//斜め左上にスライド
	DIGITALSTATE_WAVE0,

}DIGITALSTATE;
typedef struct
{//スコアの構造体
	D3DXVECTOR3 pos;			//場所
	D3DXVECTOR3 move;			//加速値
	D3DXCOLOR	col;			//カラー
	int			nDigital;		// 数字
	int			nLengthX;
	int			nLengthY;
	float		fHeight;
	DIGITALSTATE	state;		//状態
	int		nCntstate;			//状態管理用
	bool		bUse;			//使ってるか使ってないか

}DIGITAL;

//*********************************************************************************************************//
// プロトタイプ宣言　Game
//*********************************************************************************************************//
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void InitGame0(void);
GAME *GetGameState(void);
void SetGameState(GAMESTATE game, MODE mode, int nCntGameState);

//*********************************************************************************************************//
// プロトタイプ宣言　ポリゴン
//*********************************************************************************************************//
void InitPlayer(void);
void InitPlayer0(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SettingPlayer(void);
PLAYER *GetPlayer(void);
void HitPlayer(int nAtk, float fAngle, int nCntEnemy);
//bool HitAim(D3DXVECTOR3 aim, int nLength);

//*****************************************************************************
// プロトタイプ宣言　弾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXCOLOR col, BULLETSTATE state, float steep, float fCurve, int nLengthX, int nLengthY, int nType, int nAtk, float fSpeed, BULLETTYPE nShot, int nCntEnemy);
void StartBullet(int nCntEnemy, int nCntAtk);
void BreakBullet(void);
void BreakBullet(int nCntEnemy);
bool HitAim(D3DXVECTOR3 MyPos, int nMyLengthX, int nMyLengthY, float fMyAngle, D3DXVECTOR3 aim, int nLength);
void BulletScroll(D3DXVECTOR3 move);
Bullet *GetBullet(void);

//*****************************************************************************
// プロトタイプ宣言  window
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(bool bBG);
void SettingBlock(void);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float *fRide, bool bRide, PLAYERSTATE *state, int nLengthX, int nLengthY, int nCntEnemy, USETYPE type);
bool HitBullet(Bullet pBullet);
bool SafetynBlock(D3DXVECTOR3 *pPos, int nLengthX, int nLengthY);
void SetBlock(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, float fSteep, float fCurve, float fmoveSteep, float fSpeed, BLOCKSTATE state);
void BreakBlock(void);
void WideScroll(void);
void InitScroll(void);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
EFFECT *GetEffect(void);

//*****************************************************************************
// プロトタイプ宣言　爆発 てかAnimation全部
//*****************************************************************************
void InitAnimation(void);
void UninitAnimation(void);
void UpdateAnimation(void);
void DrawAnimation(ANIMTYPE type);
void SetAnimation(D3DXVECTOR3 pos, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nCntState, ANIMATION anim, ANIMTYPE type);
void BreakAnimation(void);
void HitItem(int nCntItem);
void CollisionItem(void);
void AnimationScroll(D3DXVECTOR3 move);
Animation *GetAnimation(void);

//*****************************************************************************
// プロトタイプ宣言　Animation全部
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nAtk, ANIMATION anim, EXPLOSIONSTATE state, USETYPE type, int nCntEnemy, float steep);
void ExplosionScroll(D3DXVECTOR3 move);
void BreakExplosion(void);

//*****************************************************************************
// プロトタイプ宣言  window
//*****************************************************************************
void InitGameWindow(void);
void UninitGameWindow(void);
void UpdateGameWindow(void);
void DrawGameWindow(void);
void SetGameWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntState, WINDOWSTATE state, WINDOWUSE use);
void BreakGameWindow(void);
void BackGameWindow(int nNumber);
void ChangeGameWindow(int nNumber, WINDOWSTATE state);

//*****************************************************************************
// プロトタイプ宣言  digital
//*****************************************************************************
DIGITAL *GetDigital(void);
void BreakDigital(void);
void DigitalScroll(D3DXVECTOR3 move);
void SetDigital(D3DXVECTOR3 pos, D3DXCOLOR col, DIGITALSTATE state, int nLengthX, int nLengthY, int nDigital);
void DrawDigital(void);
void UpdateDigital(void);
void UninitDigital(void);
void InitDigital(void);

#endif