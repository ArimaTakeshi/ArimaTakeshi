#pragma once
//=========================================================================================================================
//
// �Q�[���̏��� [game.h]
// Author :  �L�n�@���u
//
//=========================================================================================================================
#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
//*************************************************************************************************************************
// �\����
//*************************************************************************************************************************
typedef enum
{//window�̕\�����
	WINDOWSTATE_NORMAL = 0,			//�����X�V���Ȃ�
	WINDOWSTATE_Delete0,			//��������
	WINDOWSTATE_VIBRATION,			//�U��
	WINDOWSTATE_LEVELUP,			//���x���A�b�v
	WINDOWSTATE_STEALTH,			//���񂾂�s������->�ʏ�ɂȂ�
	WINDOWSTATE_FADEIN,				//
	WINDOWSTATE_FADEOUT,			//
	WINDOWSTATE_FADEOUT_B,			//
	WINDOWSTATE_FADE_Z,				//�Y�[�����Ȃ��������
	WINDOWSTATE_FADE_ALL,			//�o�Ă��ď���ɏ�����
	WINDOWSTATE_FLASH,				//�_��
	WINDOWSTATE_FLASH2,				//���_��
	WINDOWSTATE_SCROLL0,			//�c�X�N���[��
	WINDOWSTATE_SCROLL1,			//�΃X�N���[�� ������
	WINDOWSTATE_SCROLL2,			//��SCROLL
	WINDOWSTATE_SELECTON,			//�I������Ă�����
	WINDOWSTATE_SELECTOFF,			//�I������Ă��Ȃ����
	WINDOWSTATE_WALL,				//��
	WINDOWSTATE_BG,					//�X�N���[���ɂ����W�ύX
	WINDOWSTATE_FIELD,				//�n��
	WINDOWSTATE_STAMINAGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_MAXSTAMINAGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_LIFEGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_AUTOLIFEGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_MAXLIFEGAGE,		//�Q�[�W�g
	WINDOWSTATE_MPGAGE,			//�E���獶�֌���Q�[�W
	WINDOWSTATE_AUTOMPGAGE,		//�����ő�������Q�[�W
	WINDOWSTATE_MAXMPGAGE,		//�Q�[�W�g
	WINDOWSTATE_EXPGAGE,			//GAGE
	WINDOWSTATE_MAXEXPGAGE,			//�ォ�瑝�����Ă���GAGE
	WINDOWSTATE_PLAYER,				//���@�̃p�^�[���ɂ��ύX
	WINDOWSTATE_FLOW,				//�����
	WINDOWSTATE_FLOW0,				//�΂߉E�����痬���
	WINDOWSTATE_FLOW1,				//�΂ߍ������痬���
	WINDOWSTATE_SHOT,				//10�{a0.0f����1�{a1.0f�܂�
	WINDOWSTATE_MAX,

}WINDOWSTATE;
typedef enum
{//window�̕\�����
	WINDOWTYPE_CENTER = 0,			//���S
	WINDOWTYPE_LEFT_DOWN,			//����
	WINDOWTYPE_MAX,

}WINDOWTYPE;
typedef enum
{//window�̕\�����
	WINDOW_UPDATE_GAME = 0,			//�Q�[�����̂ݍX�V
	WINDOW_UPDATE_SELECT,			//���ł��X�V
	WINDOW_UPDATE_MAX,

}WINDOW_UPDATE;
typedef enum
{//window�̕\�����
	WINDOW_DRAW_0 = 0,		//�\������
	WINDOW_DRAW_1,
	WINDOW_DRAW_2,
	WINDOW_DRAW_3,
	WINDOW_DRAW_PAUSE,
	WINDOW_DRAW_MAP,
	WINDOW_DRAW_MINIMAP,
	WINDOW_DRAW_MINIMAP0,
	WINDOW_DRAW_FRONT,
	WINDOW_DRAW_TIME,
	WINDOW_DRAW_BACK,
	WINDOW_DRAW_MAX,

}WINDOW_DRAW;

typedef enum
{//window�̎g�p���
	WINDOWUSE_NORMAL = 0,
	WINDOWUSE_GAME,	//
	WINDOWUSE_SELECT,			//�I��
	WINDOWUSE_GUARD,			//GUARD
	WINDOWUSE_LOAD,				//�ǂݍ��݉�ʂ�
	WINDOWUSE_FONT,				//�������͎� ����
	WINDOWUSE_RANKING,			//RANKING�̎��Ɏg�p�@��Փx�̃��S
	WINDOWUSE_RANKNUMBER,		//RANKING�̎��Ɏg�p�@����
	WINDOWUSE_PLAYER,			//�v���C���[�̏ꍇ
	WINDOWUSE_ENEMY,			//BOSS�G�l�~�[�̏ꍇ
	WINDOWUSE_MAX,

}WINDOWUSE;


//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�w�i
//*********************************************************************************************************//
void InitWindow(void);
void UninitWindow(void);
void UpdateWindow(void);
void DrawWindow(void);
int SetWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nPtnUV, int nPtnWide, int nPtnHeight
	, int nCntUse, WINDOW_UPDATE nUpdateType, WINDOWSTATE state, WINDOWUSE use, WINDOWTYPE type, WINDOW_DRAW draw);
void BreakWindow(void);
void ChangeWindow(int nCntWindow, D3DXCOLOR col, WINDOWSTATE state);
void CheckGage(float fGage, float fMaxGage, int nCntWindow);
void SelectWindow(int nNumber);
void BackWindow(int nNumber);
void FontWindowMove(int nWide, int nHeight);
#endif