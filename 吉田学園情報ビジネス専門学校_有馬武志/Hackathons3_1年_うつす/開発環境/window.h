#pragma once
//=========================================================================================================================
//
// ゲームの処理 [game.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
//*************************************************************************************************************************
// 構造体
//*************************************************************************************************************************
typedef enum
{//windowの表示状態
	WINDOWSTATE_NORMAL = 0,			//何も更新しない
	WINDOWSTATE_Delete0,			//すぐ消す
	WINDOWSTATE_VIBRATION,			//振動
	WINDOWSTATE_LEVELUP,			//レベルアップ
	WINDOWSTATE_STEALTH,			//だんだん不透明に->通常になる
	WINDOWSTATE_FADEIN,				//
	WINDOWSTATE_FADEOUT,			//
	WINDOWSTATE_FADEOUT_B,			//
	WINDOWSTATE_FADE_Z,				//ズームしながら消える
	WINDOWSTATE_FADE_ALL,			//出てきて勝手に消える
	WINDOWSTATE_FLASH,				//点滅
	WINDOWSTATE_FLASH2,				//超点滅
	WINDOWSTATE_SCROLL0,			//縦スクロール
	WINDOWSTATE_SCROLL1,			//斜スクロール 左下へ
	WINDOWSTATE_SCROLL2,			//左SCROLL
	WINDOWSTATE_SELECTON,			//選択されている状態
	WINDOWSTATE_SELECTOFF,			//選択されていない状態
	WINDOWSTATE_WALL,				//壁
	WINDOWSTATE_BG,					//スクロールによる座標変更
	WINDOWSTATE_FIELD,				//地面
	WINDOWSTATE_STAMINAGAGE,			//右から左へ減るゲージ
	WINDOWSTATE_MAXSTAMINAGAGE,			//右から左へ減るゲージ
	WINDOWSTATE_LIFEGAGE,			//右から左へ減るゲージ
	WINDOWSTATE_AUTOLIFEGAGE,			//右から左へ減るゲージ
	WINDOWSTATE_MAXLIFEGAGE,		//ゲージ枠
	WINDOWSTATE_MPGAGE,			//右から左へ減るゲージ
	WINDOWSTATE_AUTOMPGAGE,		//自動で増減するゲージ
	WINDOWSTATE_MAXMPGAGE,		//ゲージ枠
	WINDOWSTATE_EXPGAGE,			//GAGE
	WINDOWSTATE_MAXEXPGAGE,			//後から増減していくGAGE
	WINDOWSTATE_PLAYER,				//自機のパターンにより変更
	WINDOWSTATE_FLOW,				//流れる
	WINDOWSTATE_FLOW0,				//斜め右下から流れる
	WINDOWSTATE_FLOW1,				//斜め左下から流れる
	WINDOWSTATE_SHOT,				//10倍a0.0fから1倍a1.0fまで
	WINDOWSTATE_MAX,

}WINDOWSTATE;
typedef enum
{//windowの表示状態
	WINDOWTYPE_CENTER = 0,			//中心
	WINDOWTYPE_LEFT_DOWN,			//左下
	WINDOWTYPE_MAX,

}WINDOWTYPE;
typedef enum
{//windowの表示状態
	WINDOW_UPDATE_GAME = 0,			//ゲーム内のみ更新
	WINDOW_UPDATE_SELECT,			//いつでも更新
	WINDOW_UPDATE_MAX,

}WINDOW_UPDATE;
typedef enum
{//windowの表示状態
	WINDOW_DRAW_0 = 0,		//表示順番
	WINDOW_DRAW_1,
	WINDOW_DRAW_2,
	WINDOW_DRAW_3,
	WINDOW_DRAW_PAUSE,
	WINDOW_DRAW_MAP,
	WINDOW_DRAW_MINIMAP,
	WINDOW_DRAW_MINIMAP0,
	WINDOW_DRAW_FRONT,
	WINDOW_DRAW_TIME,
	WINDOW_DRAW_BACK,
	WINDOW_DRAW_MAX,

}WINDOW_DRAW;

typedef enum
{//windowの使用状態
	WINDOWUSE_NORMAL = 0,
	WINDOWUSE_GAME,	//
	WINDOWUSE_SELECT,			//選択
	WINDOWUSE_GUARD,			//GUARD
	WINDOWUSE_LOAD,				//読み込み画面で
	WINDOWUSE_FONT,				//文字入力時 判定
	WINDOWUSE_RANKING,			//RANKINGの時に使用　難易度のロゴ
	WINDOWUSE_RANKNUMBER,		//RANKINGの時に使用　王冠
	WINDOWUSE_PLAYER,			//プレイヤーの場合
	WINDOWUSE_ENEMY,			//BOSSエネミーの場合
	WINDOWUSE_MAX,

}WINDOWUSE;


//*********************************************************************************************************//
// プロトタイプ宣言　背景
//*********************************************************************************************************//
void InitWindow(void);
void UninitWindow(void);
void UpdateWindow(void);
void DrawWindow(void);
int SetWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nPtnUV, int nPtnWide, int nPtnHeight
	, int nCntUse, WINDOW_UPDATE nUpdateType, WINDOWSTATE state, WINDOWUSE use, WINDOWTYPE type, WINDOW_DRAW draw);
void BreakWindow(void);
void ChangeWindow(int nCntWindow, D3DXCOLOR col, WINDOWSTATE state);
void CheckGage(float fGage, float fMaxGage, int nCntWindow);
void SelectWindow(int nNumber);
void BackWindow(int nNumber);
void FontWindowMove(int nWide, int nHeight);
#endif