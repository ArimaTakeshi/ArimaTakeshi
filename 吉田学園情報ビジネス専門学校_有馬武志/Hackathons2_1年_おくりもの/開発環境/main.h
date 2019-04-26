#pragma once
//=========================================================================================================//
//
// DirectX雛型処理 [main.h]
// Author : Ryo Sugimoto
//
//=========================================================================================================//
#ifndef _MAIN_H_
#define _MAIN_H_

//*********************************************************************************************************//
// インクルードファイル
//*********************************************************************************************************//
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//ビルド時の警告対処用マクロ
#include "dinput.h"					//入力処理に必要
#include "xaudio2.h"				//サウンド処理で必要

//*********************************************************************************************************//
// ライブラリのリンク
//*********************************************************************************************************//
#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント(部品)
#pragma comment(lib,"winmm.lib")	//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define SCREEN_WIDTH	(1280)		// ウインドウの幅
#define SCREEN_HEIGHT	(720)		// ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_GAMEX			(800)

//*********************************************************************************************************//
// 構造体定義
//*********************************************************************************************************//
typedef enum
{//モードの状態
	MODE_TITLE = 0,	//タイトル
	MODE_RANKING,	//ランキング
	MODE_WATCH,		//ゲーム観戦状態
	MODE_TUTORIAL,	//チュートリアル
	MODE_GAME,		//ゲームメイン
	MODE_RESULT,	//リザルト
	MODE_MAX

}MODE;

typedef enum
{//windowの表示状態
	WINDOWSTATE_NORMAL = 0,			//何も更新しない
	WINDOWSTATE_VIBRATION,			//振動
	WINDOWSTATE_LEVELUP,			//レベルアップ
	WINDOWSTATE_STEALTH,			//だんだん不透明に->通常になる
	WINDOWSTATE_FADEIN,				//
	WINDOWSTATE_FADEOUT,			//
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
	WINDOWSTATE_LIFEGAGE,				//右から左へ減るゲージ
	WINDOWSTATE_MAXLIFEGAGE,			//ゲージ枠
	WINDOWSTATE_AUTOLIFEGAGE,			//後から増減していくGAGE
	WINDOWSTATE_MAXEXPGAGE,			//後から増減していくGAGE
	WINDOWSTATE_AUTOEXPGAGE,			//後から増減していくGAGE
	WINDOWSTATE_EXPGAGE,			//GAGE
	WINDOWSTATE_PLAYER,				//自機のパターンにより変更
	WINDOWSTATE_MAX,

}WINDOWSTATE;

typedef enum
{//windowの使用状態
	WINDOWUSE_NORMAL = 0,
	WINDOWUSE_RESIDUALAIRPORT,	//残機
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

typedef enum
{//スコアの状態
	SCORESTATE_NONE = 0,
	SCORESTATE_FADE,
	SCORESTATE_DELETE,
	SCORESTATE_RANKDOWN,
	SCORESTATE_SET,
	SCORESTATE_RANKSET,			//ランキング時右から左へ流れてセット
	SCORESTATE_Damage,

}SCORESTATE;
typedef struct
{//スコアの構造体
	D3DXVECTOR3 pos;			//場所
	D3DXCOLOR	col;			//カラー
	int			g_nScore;		// スコア
	SCORESTATE	state;			//状態
	float		fCntstate;		//状態管理用
	bool		bUse;			//使ってるか使ってないか

}SCORE;

typedef struct
{
	D3DXVECTOR3 pos;			//頂点座標
	float		rhw;			//1.0fで固定
	D3DCOLOR	col;			//頂点カラー
	D3DXVECTOR2 tex;			//テクスチャ座標

}VERTEX_2D;

typedef enum
{//文字の状態
	FONTSTATE_NONE = 0,
	FONTSTATE_DELETE,
	FONTSTATE_RANKDOWN,
	FONTSTATE_RANKSET,		//ランキング時のセット
	FONTSTATE_RANKDELETE,	//ランキング時のデリート

}FONTSTATE;
typedef struct
{
	FONTSTATE	state;		//文字の状態
	D3DCOLOR	col;		//カラー
	RECT		rect;		//文字の表示範囲
	int			nWide;
	int			nHeight;
	int		fCntState;	//状態管理用
	char		aStr[256];	//文字の量
	bool		bUse;		//使用or未使用

}Font;

typedef struct
{//リザルトで使う
	int nCntScore;		//forで回さないためローカルだと初期化に困る
	int nCntResult;		//時間カウント
	int nRankin;		//ハイスコア時の順位保存 名前入力時使用
	int nWideFont;		//50音表の横選択部分
	int nHightFont;		//50音表の縦選択部分
	char aStr[25];		//名前入力のため

}Result;

typedef struct
{
	int colR;
	int colG;
	int colB;
	int colA;
}COLLAR;

//*********************************************************************************************************//
// プロトタイプ宣言
//*********************************************************************************************************//
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE *GetMode(void);
HWND *GethWnd(void);

//*********************************************************************************************************//
// プロトタイプ宣言
//*********************************************************************************************************//
void InitFont(void);
void UninitFont(void);
void UpdateFont(void);
void DrawFont(void);
void SetFont(RECT rect, D3DCOLOR col, char *aStr, int nNumber, int nWide, int nHeight, FONTSTATE state);
void ChangeFont(bool bUse, char *aStr, int nNumber, FONTSTATE state, D3DCOLOR col);
void BreakFont(void);
int *GetSetFont(void);
void SetFontDamage(RECT rect, D3DCOLOR col, char *aStr, int nWide, int nHeight, FONTSTATE state);
void FontScroll(D3DXVECTOR3 move);

//*********************************************************************************************************//
// プロトタイプ宣言 チュートリアル
//*********************************************************************************************************//
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

//*********************************************************************************************************//
// プロトタイプ宣言 リザルト
//*********************************************************************************************************//
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

//*********************************************************************************************************//
// プロトタイプ宣言　背景
//*********************************************************************************************************//
void InitWindow(void);
void UninitWindow(void);
void UpdateWindow(void);
void DrawWindow(void);
void SetWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntUse, int nEnemy, WINDOWSTATE state, WINDOWUSE use);
void BreakWindow(void);
bool BreakAirport(void);
void SelectWindow(int nNumber);
void BackWindow(int nNumber);
void FontWindowMove(int nWide, int nHeight);

//*********************************************************************************************************//
// プロトタイプ宣言　背景
//*********************************************************************************************************//
void InitBGWindow(void);
void UninitBGWindow(void);
void UpdateBGWindow(void);
void DrawBGWindow(void);
void SetBGWindow(D3DXVECTOR3 pos, COLLAR col, float fSpeed, float fPos, int nLengthX, int nLengthY, int nType, WINDOWSTATE state);
void BreakBGWindow(void);
void BGScroll(D3DXVECTOR3 move);

//*********************************************************************************************************//
// プロトタイプ宣言　フェードのポリゴン表示処理
//*********************************************************************************************************//
void InitFadeWindow(void);
void UninitFadeWindow(void);
void UpdateFadeWindow(void);
void DrawFadeWindow(void);
void SetFadeWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntUse, WINDOWSTATE state, WINDOWUSE use);
void LoadBreakWindow(void);

#endif