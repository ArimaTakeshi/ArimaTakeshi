//=========================================================================================================================
//
// 爆発処理 [explosion.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitExplosion(void);									//爆発初期化処理
void UninitExplosion(void);									//爆発終了処理
void UpdateExplosion(void);									//爆発更新処理
void DrawExplosion(void);									//爆発描画処理
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col);			//爆発の設定処理

#endif
