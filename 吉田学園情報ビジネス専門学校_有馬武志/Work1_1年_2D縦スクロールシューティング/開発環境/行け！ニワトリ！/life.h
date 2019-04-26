//=============================================================================
//
// ライフ処理 [lefe.h]
// Author :  有馬　武志
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"

typedef enum
{
	LifeTex_Init = 0,
	LifeTex_DAMAGE,
	LifeTex_MAX,
}LIFETEX;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

void AddLife(int nLife, LIFETEX Life);
#endif