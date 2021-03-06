//=========================================================================================================================
//
// 敵処理 [enemy.h]
// Author : 有馬　武志
//
//=========================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_ENEMY	(256)	//敵の最大数

//*************************************************************************************************************************
// 構造体定義
//*************************************************************************************************************************
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動
	int nType;				//種類
	bool bUse;				//使用しているかどうか
	ENEMYSTATE state;		//敵の状態
	int nLife;				//体力
	int nCounterState;		//状態管理のカウンター
}Enemy;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitEnemy(void);										//敵初期化処理
void UninitEnemy(void);										//敵終了処理
void UpdateEnemy(void);										//敵更新処理
void DrawEnemy(void);										//敵描画処理
void SetEnemy(D3DXVECTOR3 pos, int nType);					//敵の設定処理
Enemy *GetEnemy(void);										//敵の取得
void DeleteEnemy(void);										//
#endif
