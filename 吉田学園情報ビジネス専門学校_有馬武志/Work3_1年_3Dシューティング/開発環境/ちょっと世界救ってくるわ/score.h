//=============================================================================
//
// �X�R�A���� [score.h]
// Author :  �L�n�@���u
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*************************************************************************************************************************
// �u���b�N�̍\����
//*************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			//�ʒu
	D3DXCOLOR		col;			//�J���[
	int				nNumScore;		//��
	float			ScoreWidth;		//��
	float			ScoreHeight;	//����
	bool			bUse;			//�g�p���Ă��邩�ǂ���
}Score;

typedef enum
{
	SCORE_NONE = 0,			//�����Ȃ����
	SCORE_RAKING,			//�����L���O�ŏo���X�R�A
	SCORE_KILL,				//�Q�[������KILL�J�E���g�X�R�A
	SCORE_MAX				//�ő吔
}SCORESTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue, SCORESTATE state);
void SetScore(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
Score *GetScore(void);

#endif
