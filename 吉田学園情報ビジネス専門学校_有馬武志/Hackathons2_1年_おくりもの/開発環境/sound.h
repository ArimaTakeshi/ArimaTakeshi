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
	SOUND_LABEL_TITLE000 = 0,	// taitol0
	SOUND_LABEL_TUTORIAL000,	// TUTORIAL
	SOUND_LABEL_RESULT000,	// TUTORIAL

	SOUND_LABEL_FBGM000,		// FIELDBGM0
	SOUND_LABEL_FBGM001,		// FIELDBGM0
	SOUND_LABEL_FBGM002,		// FIELDBGM0
	SOUND_LABEL_TIME000,		// 60�b��؂�

	SOUND_LABEL_BOTTON000,		//���艹
	SOUND_LABEL_BOTTON001,		//�J�[�\���ړ���
	SOUND_LABEL_ATTACK000,		//�󒆍U���J�n��
	SOUND_LABEL_ATTACK001,		//�U����
	SOUND_LABEL_ATTACK002,		//�U�����}
	SOUND_LABEL_ATTACK003,		//�U���q�b�g
	SOUND_LABEL_ATTACK004,		//�U������
	SOUND_LABEL_JUMP000,		//�W�����v
	SOUND_LABEL_DEATH,			//���S��
	SOUND_LABEL_Damage000,		//��_��
	SOUND_LABEL_Damage001,		//��_��
	SOUND_LABEL_Damage002,		//��_��
	SOUND_LABEL_LEVELUP,		//���x���A�b�v
	SOUND_LABEL_COIN,			//�R�C��
	SOUND_LABEL_CHECKPOINT,		//�`�F�b�N�|�C���g
	SOUND_LABEL_HEEL,			//��

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
