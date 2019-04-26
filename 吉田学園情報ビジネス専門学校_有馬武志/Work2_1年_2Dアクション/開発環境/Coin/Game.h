//=========================================================================================================================
//
// �Q�[���̏��� [game.h]
// Author :  �L�n�@���u
//
//=========================================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
//*************************************************************************************************************************
// �\����
//*************************************************************************************************************************
typedef enum
{//�e�X�e�[�W
	STAGE_NONE = 0,			//�������ĂȂ����
	STAGENUM_1,				//�X�e�[�W1
	STAGENUM_2,				//�X�e�[�W2
	STAGENUM_3,				//�X�e�[�W3
	STAGENUM_4,				//�X�e�[�W4
	STAGENUM_5,				//�X�e�[�W5
	STAGENUM_6,				//�X�e�[�W6
	STAGENUM_7,				//�X�e�[�W7
}STAGENUM;

typedef enum
{
	GAMESTATE_NONE = 0,		//�������Ă��Ȃ����
	GAMESTATE_NORMAL,		//�ʏ���
	GAMESTATE_CLEAR,		//�N���A
	GAMESTATE_OVER,			//�Q�[���I�[�o�[
	GAMESTATE_END,
	GAMESTATE_MAX			//�ő吔
}GAMESTATE;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitGame(void);							//�^�C�g������������
void UninitGame(void);							//�^�C�g���I������
void UpdateGame(void);							//�^�C�g���X�V����
void DrawGame(void);							//�^�C�g���`�揈��
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
STAGENUM GetNumState(void);
void SetPauseState(bool bPause);
void SetMenuState(bool bMenu);
void SetStageState(STAGENUM stage);				// �X�e�[�W�ݒ菈��

#endif