//=============================================================================
//
// ������ [wind.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _WIND_H_
#define _WIND_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define MAX_WIND	(3)
#define WIND_POW	(2.9f)
#define WIND_PLUS	(1.0f)
#define WIND_RANGE	(0.5f)
#define WIND_GOAL	(0.05f)
#define WIND_BACK	(0.05f)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CWind
{
public:
	CWind() {};
	~CWind() {};

	void	Init(void);
	void	Update(void);
	void	Uninit(void);
	float	&GetfPower(void) { return m_fPower; }
	float	&GetfRot(void)	 { return m_fRot; }
	float	&GetfRange(void) { return m_fRange; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float m_fPower;		//���̈З�
	float m_fMaxPower;	//���̍ő�З�
	float m_fRot;		//�e���p�x
	float m_fRange;		//�e���͈�
	float m_fGoal;		//���̑�����
	float m_fBack;		//���̂��݋
	bool  m_bState;		//�e�����
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CWind_Manager
{
public:
	CWind_Manager() {};
	~CWind_Manager() {};

	void	Init(void);
	void	Update(void);
	void	Uninit(void);
	int		&GetnMaxWind(void) { return m_nMaxWind; }
	CWind	*&GetpWind(void) { return m_pWind; }
	float	&GetfRot(void) { return m_fRot; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	int		m_nMaxWind;		//���̐�
	float	m_fRot;			//�p�x
	float	m_fRotPlus;		//�p�x�ւ̃v���X�l
	float	m_fCntState;	//F�J�E���g�p
	CWind	*m_pWind;		//��
};

#endif