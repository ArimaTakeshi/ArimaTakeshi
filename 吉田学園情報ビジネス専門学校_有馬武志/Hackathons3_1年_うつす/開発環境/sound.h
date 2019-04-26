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
	SOUND_LABEL_BGM000 = 0,		// �^�C�g��
	SOUND_LABEL_BGM001,			// �Q�[��
	SOUND_LABEL_BGM002,			// ���U���g
	SOUND_LABEL_BGM003,			// �Q�[���I�[�o�[
	SOUND_LABEL_SE_KARSOL,		// �J�[�\��
	SOUND_LABEL_SE_PBUTTUN,		// P�{�^��
	SOUND_LABEL_SE_ENTER,		// ���艹
	SOUND_LABEL_SE_START,		// �Q�[���J�n��
	SOUND_LABEL_SE_TAKESHOT,	// �V���b�^�[��
	SOUND_LABEL_SE_HART,		// �S����
	SOUND_LABEL_NEAR,			// �ڋߎ�
	SOUND_LABEL_DETH,			// �v���C���[�̎��S��
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
