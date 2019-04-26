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
{
	ENEMYTEXTYPE_ENEMY = 0,		//敵
	ENEMYTEXTYPE_TRAP,			//TRAP
	ENEMYTEXTYPE_MAX

}ENEMYTEXTYPE;
typedef enum
{
	ENEMYTEX_SLIME = 0,		//スライム
	ENEMYTEX_BAT,			//コウモリ
	ENEMYTEX_INSECT,		//虫
	ENEMYTEX_WOLF,			//狼
	ENEMYTEX_GIANT,			//巨人
	ENEMYTEX_MYSTERY,		//謎の生物
	ENEMYTEX_W_UNICORN,		//白いユニコーン
	ENEMYTEX_B_UNICORN,		//黒いユニコーン
	ENEMYTEX_R_DRAGON,		//赤いドラゴン
	ENEMYTEX_B_DRAGON,		//青いドラゴン
	ENEMYTEX_WK_DRAGON,		//白いドラゴン
	ENEMYTEX_BK_DRAGON,		//黒いドラゴン
	ENEMYTEX_BEAST,			//マンティコア
	ENEMYTEX_DEATH,			//死神
	ENEMYTEX_LAST_DRAGON,	//ラストドラゴン
	ENEMYTEX_BICSLIME,		//ビックスライム
	ENEMYTEX_MAX

}ENEMYTEX;

typedef enum
{// 敵種類
	ENEMYTYPE_NORMALENEMY = 0,	// ノーマル
	ENEMYTYPE_BOSSENEMY,		// 大ボス
	ENEMYTYPE_TITLE,			//TITLEに戻る
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef enum
{// 敵状態
	ENEMYSTATE_APPEAR = 0,		// 出現
	ENEMYSTATE_NORMAL,			// 見つかっていない状態
	ENEMYSTATE_DEATH,			// デス
	ENEMYSTATE_ATTACK,			//攻撃状態
	ENEMYSTATE_BOSS,			//見逃さない状態
	ENEMYSTATE_HALFBACK,		// Lifeが半分削られると一度だけノックバック
	ENEMYSTATE_NOTBACK,			// KNOCKBACKしない 一時的に
	ENEMYSTATE_NOTBACK0,		// KNOCKBACKしない
	ENEMYSTATE_NOTBACK_S,		// KNOCKBACKしない　スライム出現
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{// 敵状態
	ENEMYEFFECT_NORMAL = 0,		// 見つかっていない状態
	ENEMYEFFECT_FIND,			//発見状態
	ENEMYEFFECT_JUMP,			//発見状態　着地でfMove = 0;
	ENEMYEFFECT_FLY,			//飛んでいる状態
	ENEMYEFFECT_ATTACK,			//攻撃状態
	ENEMYEFFECT_MAGIC,			//攻撃状態
	ENEMYEFFECT_KNOCKBACK,		// ノックバック状態
	ENEMYEFFECT_MAX
}ENEMYEFFECT;

typedef struct
{// 敵
	D3DXVECTOR3 respawn;		// 初期位置
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 posold;			// 前の位置
	D3DXVECTOR3 move;			// 移動置
	D3DXCOLOR col;				// 色
	ENEMYTEX nTexNum;				// 種類
	ENEMYTEXTYPE nTexType;				//トラップか敵か
	int nAngle;					// 向き
	int nSize;					// 大きさ
	int nLife;					// 寿命
	int nMaxLife;				//最大HP
	int nAtk;					// 攻撃力
	int nDff;					// 防御力
	int nEXP;					// スキルのレベル上げのため
	int nGold;					// 体力回復やスキル等の購入
	int nScore;					// ゲームのScore
	int nCollisionX;			//あたり判定X
	int nCollisionY;			//あたり判定Y
	int nHit;					//攻撃によるあたり判定(丸)
	float fSteep;				// ポリゴンの角度	
	float fplusSteep;
	float fGravity;				//重力　飛行ユニット用
	float fMove;
	ENEMYTYPE type;				// 敵の種類
	ENEMYSTATE state;			// 敵の情報
	ENEMYEFFECT effect;			// 効果
	int nCounterState;			// 状態管理カウンター
	int nCountereffect;			// 効果管理用
	int nCountAttack;			// 攻撃用のCounter
	int nCounterDamage;			//Damage後のカウント
	int nCounterAnim;			// アニメーションカウンター
	int nPatternAnim;			// アニメーションパターンNo.
	bool bUse;					// 使用しているかどうか
	int nResCount;				//リスポーンまでのカウント
	bool bRespawn;				//復活できるかどうか
}Enemy;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitEnemy(void);			// 敵初期化処理
void UninitEnemy(void);			// 敵終了処理
void UpdateEnemy(void);			// 敵更新処理
void DrawEnemy(void);			// 敵描画処理
void EnemyScroll(D3DXVECTOR3 move);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTEXTYPE nTexType, ENEMYTEX nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, float steep, ENEMYTYPE Type);
void SlimeUpdate(int nCntEnemy);
void BatUpdate(int nCntEnemy);
void GiantUpdate(int nCntEnemy);
void MysteryUpdate(int nCntEnemy);
void WolfUpdate(int nCntEnemy);
void DragonUpdate(int nCntEnemy);
void DeathUpdate(int nCntEnemy);
Enemy *GetEnemy(void);						// 敵の取得
void CleanEnemy(void);
void HitEnemy(int nCntEnemy, int nAtk, float fAngle, USETYPE type);// 敵へのダメージ判定

#endif
