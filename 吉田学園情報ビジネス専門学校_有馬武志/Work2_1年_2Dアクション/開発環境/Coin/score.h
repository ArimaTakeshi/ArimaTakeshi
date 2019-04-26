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
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�J���[
	int nNumScore;			//��
	float ScoreWidth;		//��
	float ScoreHeight;		//����
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Score;

typedef enum
{
	SCORE_NONE = 0,
	SCORE_MENIYBOX,
	SCORE_RAKING,
	SCORE_COIN,
	SCORE_SHOP,
	SCORE_TIMER,
	SCORE_MAX				//�ő吔
}SCORESTATE;

typedef enum
{
	GETCOIN_NORMAL = 0,
	GETCOIN_X2
}GETCOINSTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue, SCORESTATE state);
void SetCoinState(GETCOINSTATE state);
void SetScore(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
Score *GetScore(void);

#endif
