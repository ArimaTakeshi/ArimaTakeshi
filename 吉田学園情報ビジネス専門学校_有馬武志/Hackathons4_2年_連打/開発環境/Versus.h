//=============================================================================
//
// �ΐ폈�� [Versus.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _VERSUS_H_
#define _VERSUS_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "Game.h"
#include "manager.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define MAX_VS_LOGO	(2)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CVersus
{
public:
	typedef enum
	{
		STATE_START,	//�J�n��
		STATE_NONE,		//�ʏ�
		STATE_P1_WIN,	//P1����
		STATE_P2_WIN,	//P2����
		STATE_DRAW,		//��������
		STATE_TIME_UP,	//�^�C���A�b�v
		STATE_MAX
	}STATE;
	CVersus() { for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++) { m_pScene2D[nCount] = NULL; } };
	~CVersus() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	SetState(STATE state);
	void	Pause(void);
	void	UpdateEnd();
	void	UpdateStart();

	STATE	&GetState(void) { return m_state; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	STATE	m_state;
	float	m_fCntState;
	int		m_nSelect;
	CScene2D *m_pScene2D[MAX_GAME_PAUSE];
	CScene2D *m_p2DStart[MAX_VS_LOGO];
};

#endif
