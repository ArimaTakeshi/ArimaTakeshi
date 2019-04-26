//=============================================================================
//
// ライフ処理 [length.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _LENGTH_H_
#define _LENGTH_H_

#include "main.h"

typedef enum
{
	LengthTex_Init = 0,
	LengthTex_DAMAGE,
	LengthTex_HIL,
	LengthTex_MAX,
}LENGTHTEX;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitLength(void);
void UninitLength(void);
void UpdateLength(void);
void DrawLength(void);

void AddLength(int nLength, LENGTHTEX Length);
#endif