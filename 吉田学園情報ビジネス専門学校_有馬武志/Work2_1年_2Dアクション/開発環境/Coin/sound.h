//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �L�n�@���u
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
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM7
	SOUND_LABEL_SE_GETCOIN,		// �R�C�����Ƃ鉹
	SOUND_LABEL_SE_DOWN000,		// ����
	SOUND_LABEL_SE_OPEN000,		// �J��
	SOUND_LABEL_SE_GETMONEY,	// �����n�̉�
	SOUND_LABEL_SE_PRESS,		// �����Ƃ��̉�
	SOUND_LABEL_SE_BREAK,		// �󂷂Ƃ��̉�
	SOUND_LABEL_SE_FALL,		// ������Ƃ�
	SOUND_LABEL_SE_TIME,		// ���v
	SOUND_LABEL_SE_FOUND,		// ����
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_JAMP,		// �W�����v��
	SOUND_LABEL_SE_RECOVERY,	// �񕜉�
	SOUND_LABEL_SE_RANKING,		//�����L���O
	SOUND_LABEL_SE_ITEMBEY,		//�A�C�e���w��
	SOUND_LABEL_SE_MENUUPDOWN,	//���j���[�ړ�
	SOUND_LABEL_SE_ITEMGET,		//�A�C�e���Ƃ�����
	SOUND_LABEL_SE_GAMEOVER,	//�Q�[���I�[�o�[
	SOUND_LABEL_SE_NOT,			//����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label); //�Q�[���̏������߂��@
void StopSound(SOUND_LABEL label);	  //�������O�������ăX�g�b�v��������
void StopSound(void);

#endif
