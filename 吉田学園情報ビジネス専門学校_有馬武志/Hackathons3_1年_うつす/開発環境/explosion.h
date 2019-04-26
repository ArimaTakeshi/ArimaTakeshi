//=============================================================================
//
// ポリゴン処理 [explosion.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// 壁の構造体
//*****************************************************************************
typedef enum
{//アニメーションの使用状態
	EXPLOSIONSTATE_PHIT,		//プレイヤーにあたり判定のある爆発
	EXPLOSIONSTATE_PHITMINUS,	//プレイヤーにあたり判定のある爆発 判定の小さい
	EXPLOSIONSTATE_EHIT,		//敵にあたり判定のある爆発
	EXPLOSIONSTATE_EFFECT,		//あたり判定無し
	EXPLOSIONSTATE_DELETE,		//消えていく
	EXPLOSIONSTATE_FADE,
	EXPLOSIONSTATE_GAGE,		//EXPゲージ
	EXPLOSIONSTATE_LOAD,		//LOAD専用
	EXPLOSIONSTATE_DFADE,		//出てきて消える

}EXPLOSIONSTATE;
typedef enum
{//アニメーションの使用状態
	ANIMATION_NORMAL = 0,
	ANIMATION_FADE,
	ANIMATION_LOOP,
	ANIMATION_UP,
	ANIMATION_MAX,

}ANIMATION;

//*****************************************************************************
// プロトタイプ宣言　Animation全部
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
int SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, ANIMATION anim, EXPLOSIONSTATE state, float steep, int nView);
void ExplosionScroll(D3DXVECTOR3 move);
void BreakExplosion(void);
void CheckEXP(float fEXP, float fMaxEXP, int nCntExplosion);
void ChangeExplosion(int nCntExplosion, EXPLOSIONSTATE state);

#endif
