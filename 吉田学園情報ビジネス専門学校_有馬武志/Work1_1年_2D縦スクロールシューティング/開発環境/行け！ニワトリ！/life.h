//=============================================================================
//
// ���C�t���� [lefe.h]
// Author :  �L�n�@���u
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
// �v���g�^�C�v�錾
//*****************************************************************************
void InitLife(void);
void UninitLife(void);
void UpdateLife(void);
void DrawLife(void);

void AddLife(int nLife, LIFETEX Life);
#endif