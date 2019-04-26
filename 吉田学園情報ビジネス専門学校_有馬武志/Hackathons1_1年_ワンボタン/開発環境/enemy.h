//=========================================================================================================================
// 
// 敵処理 [enemy.h]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "game.h"	// ゲーム

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_ENEMY				(128)	// 敵の最大数

//*************************************************************************************************************************
// 構造体定義
//*************************************************************************************************************************
typedef enum
{// 敵種類
	ENEMYTYPE_NORMALENEMY = 0,	// ノーマル
	ENEMYTYPE_BOSSENEMY,		// 大ボス
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef enum
{// 敵状態
	ENEMYSTATE_APPEAR = 0,		// 出現
	ENEMYSTATE_NOMAL,			// ノーマル
	ENEMYSTATE_DAMAGE,			// ダメージ
	ENEMYSTATE_DEATH,			// デス
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef struct
{// 敵
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 move;			// 移動置
	D3DXCOLOR col;				// 色
	int nTexNum;				// 種類
	int nSize;					// 大きさ
	int nLife;					// 寿命
	int nAtk;
	int nDff;
	int nEXP;
	int nGold;
	int nScore;
	ENEMYTYPE Type;				// 敵の種類
	ENEMYSTATE State;			// 敵の情報
	int nCounterState;			// 状態管理カウンター
	int nCounterAnim;			// アニメーションカウンター
	int nPatternAnim;			// アニメーションパターンNo.
	bool bUse;					// 使用しているかどうか
}Enemy;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitEnemy(void);			// 敵初期化処理
void UninitEnemy(void);			// 敵終了処理
void UpdateEnemy(void);			// 敵更新処理
void DrawEnemy(void);			// 敵描画処理

void SetEnemy(D3DXVECTOR3 pos, int nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, ENEMYTYPE Type);
Enemy *GetEnemy(void);									// 敵の取得
void HitEnemy(int nCntEnemy, int nDamage);				// 敵の弾当たり処理

#endif
