//=============================================================================
//
// �Q�[������ [Game.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
#define MAX_GAME_PAUSE		(6)
#define GAME_PAUSE_INTERVAL	(100.0f)
#define GAME_PAUSE_LOGOX	(300.0f)
#define GAME_PAUSE_LOGOY	(100.0f)


//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CGame
{
public:
	typedef enum
	{
		STATE_NONE,		//�ʏ�
		STATE_CLEAR,	//�N���A
		STATE_OVER,		//�Q�[���I�[�o�[
		STATE_MAX
	}STATE;
	CGame()		{ for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++) { m_pScene2D[nCount] = NULL; } };
	~CGame()	{};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	SetState(STATE state);
	void	Pause(void);
	STATE	&GetState(void) { return m_state; }

	static bool &GetbDuo(void) { return m_bDuo; }
	int &GetnWave(void) { return m_nWave; }


private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static	bool	m_bDuo;	//2�l�v���C���ǂ���
	STATE	m_state;
	float	m_fCntState;
	int		m_nSelect;

	int		m_nCntTime;
	float	m_fInterval;
	int		m_nWave;
	int		m_nCntType;

	CScene2D *m_pScene2D[MAX_GAME_PAUSE];
};

#endif
