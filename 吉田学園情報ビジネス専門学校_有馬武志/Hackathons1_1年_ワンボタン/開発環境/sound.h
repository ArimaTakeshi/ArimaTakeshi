//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_RANKING000,		// RANKING
	SOUND_LABEL_FBGM000,		// FIELDBGM0

	SOUND_LABEL_BOTTON000,		//���艹 && �`���[�W��
	SOUND_LABEL_BOTTON001,		//�U��
	SOUND_LABEL_BOTTON002,		//�W�����v
	SOUND_LABEL_BOTTON003,		//�W�����v

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
