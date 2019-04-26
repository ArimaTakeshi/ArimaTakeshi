//=============================================================================
//
// �|���S������ [explosion.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// �ǂ̍\����
//*****************************************************************************
typedef enum
{//�A�j���[�V�����̎g�p���
	EXPLOSIONSTATE_PHIT,		//�v���C���[�ɂ����蔻��̂��锚��
	EXPLOSIONSTATE_PHITMINUS,	//�v���C���[�ɂ����蔻��̂��锚�� ����̏�����
	EXPLOSIONSTATE_EHIT,		//�G�ɂ����蔻��̂��锚��
	EXPLOSIONSTATE_EFFECT,		//�����蔻�薳��
	EXPLOSIONSTATE_DELETE,		//�����Ă���
	EXPLOSIONSTATE_FADE,
	EXPLOSIONSTATE_GAGE,		//EXP�Q�[�W
	EXPLOSIONSTATE_LOAD,		//LOAD��p
	EXPLOSIONSTATE_DFADE,		//�o�Ă��ď�����

}EXPLOSIONSTATE;
typedef enum
{//�A�j���[�V�����̎g�p���
	ANIMATION_NORMAL = 0,
	ANIMATION_FADE,
	ANIMATION_LOOP,
	ANIMATION_UP,
	ANIMATION_MAX,

}ANIMATION;

//*****************************************************************************
// �v���g�^�C�v�錾�@Animation�S��
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
int SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, ANIMATION anim, EXPLOSIONSTATE state, float steep, int nView);
void ExplosionScroll(D3DXVECTOR3 move);
void BreakExplosion(void);
void CheckEXP(float fEXP, float fMaxEXP, int nCntExplosion);
void ChangeExplosion(int nCntExplosion, EXPLOSIONSTATE state);

#endif
