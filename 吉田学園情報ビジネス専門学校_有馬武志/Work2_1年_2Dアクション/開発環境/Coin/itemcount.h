//=============================================================================
//
// �A�C�e���J�E���g�̕\������ [itemcount.h]
// Author :  �L�n�@���u
//
//=============================================================================
#ifndef _ITEMCOUNT_H_
#define _ITEMCOUNT_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItemCount(void);
void UninitItemCount(void);
void UpdateItemCount(void);
void DrawItemCount(void);

void AddItemCount(int nValue);
int GetItemCount(void);
#endif
