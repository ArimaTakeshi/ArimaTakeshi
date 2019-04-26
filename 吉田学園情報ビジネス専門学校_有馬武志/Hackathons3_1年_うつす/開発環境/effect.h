//=========================================================================================================================
//
// エフェクトの処理 [effect.h]
// Author : 有馬　武志
//
//=========================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// 構造体定義
//*************************************************************************************************************************
typedef enum
{
	EFFECTTYPE_NONE = 0,
	EFFECTTYPE_BULLET,
	EFFECTTYPE_EXPLOSION,
	EFFECTTYPE_EXPLOSION2,
	EFFECTTYPE_RESURRECTION, 
	EFFECTTYPE_ERUPTION,
	EFFECTTYPE_SMOKE,
	EFFECTTYPE_SNOW,
	EFFECTTYPE_RAIN,
	EFFECTTYPE_FIRE,
	EFFECTTYPE_POWDER,
	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			//位置
	D3DXVECTOR3 posOld;			//過去の位置
	D3DXVECTOR3 move;			//移動値
	D3DXCOLOR col;				//色
	EFFECTTYPE Type;			//種類
	D3DXVECTOR3 rot;			//法線ベクトル
	D3DXMATRIX mtxWorld;		//頂点カラー
	float fRadius;				//半径(大きさ)
	int nIdxShadow;				//影の番号
	int nLife;					//表示時間(寿命)
	int nType;					//種類
	bool bUse;					//使用しているかどうか
} EFFECT;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitEffect(void);			// エフェクト初期化処理
void UninitEffect(void);		// エフェクト終了処理
void UpdateEffect(void);		// エフェクト更新処理
void DrawEffect(void);			// エフェクト描画処理

void SetBulletEffect(D3DXVECTOR3 pos, D3DXCOLOR col, EFFECTTYPE Type, float fRadius, int nLife,int nType);	// 弾エフェクト設定処理
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife,int nType);	// 爆発エフェクト設定処理

#endif