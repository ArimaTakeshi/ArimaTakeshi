#pragma once
//=============================================================================
//
// �v���C���[����(��ԏ������܂�) [ScenePlayer.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _Player_H_
#define _Player_H_

#include "main.h"
#include "scene.h"
#include "Scene2D.h"

class C2D;
class C2DGage;
class CNumber;
class CFont;

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer : public CScene2D
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_Damage,		//���̃}�b�v�֐i��
		STATE_MAX
	}STATE;
	CPlayer(int nPrioryity = 1) : CScene2D::CScene2D(nPrioryity)
	{
		m_pIcon = NULL;
		m_pLifeGage = NULL;
		m_pBomb[0] = NULL;
		m_pBomb[1] = NULL;
		m_pBomb[2] = NULL;
	};
	~CPlayer() {};

	void	Set(int nLane);
	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	DrawUI(void);
	int 	&GetnInvincible(void) { return m_nInvincible; };
	int 	&GetnBomb(void) { return m_nBomb; };
	float	&GetfLife(void) { return m_fLife; };
	C2D		*&GetpBomb(int nCount) { return m_pBomb[nCount]; };
	CFont	*&GetpFont(void) { return m_pFont; };

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static	int		m_nStage;		//�X�e�[�W�ԍ�
	static	CFont	*m_pFont2;		//�X�e�[�W�ԍ�
	static	int		m_nTime;		//�X�e�[�W�ԍ�

	int			m_nWait;
	float		m_fLane;
	float		m_fLPlus;
	int			m_nInvincible;		//���G����
	int			m_nBomb;
	float		m_fLife;
	float		m_fMaxLife;
	CFont		*m_pFont;		//
	C2D			*m_pBomb[3];		//�A�C�R��
	C2D			*m_pIcon;		//�A�C�R��
	C2DGage		*m_pLifeGage;	//HP�Q�[�W
};

#endif
