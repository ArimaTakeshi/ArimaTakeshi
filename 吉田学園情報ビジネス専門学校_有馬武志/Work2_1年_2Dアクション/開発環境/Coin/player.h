//=============================================================================
//
// プレイヤーの処理 [player.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//****************************************************************************
// 構造体
//****************************************************************************
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		//通常状態
	PLAYERSTATE_DAMAGE,			//ダメージ状態
	PLAYERSTATE_DEAHT,			//死亡状態	
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;			//位置		
	D3DXVECTOR3 posOld;			//前回の位置
	D3DXVECTOR3 move;			//移動値
	D3DXCOLOR	col;			//色
	PLAYERSTATE state;			//プレイヤーの状態
	float PlayerHeight;			//プレイヤーの身長
	float PlayerWidth;			//プレイヤーの横幅
	bool		bJump;			//ジャンプ
	int			nLife;			//体力
	int			TexT;			//テクスチャのタテ移動
	int nCounterAnim;			//アニメーションカウンター
	int nPatternAnim;			//アニメーションパターンNo.
	int nCounterState;			//状態管理のカウンター
	bool bUse;					//使用しているかどうか
	bool bDisp;					//表示するかしないか
	//Block *pBlock;			//対象のブロックへのポインタ
}Player;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer(void);			//プレイヤーの初期化処理	
void UninitPlayer(void);		//プレイヤーの終了処理
void UpdatePlayer(void);		//プレイヤーの更新処理
void DrawPlayer(void);			//プレイヤーの描画処理
void HitPlayer(int nDamage);
Player *GetPlayer(void);
void DeletePlayer(void);																	//
#endif