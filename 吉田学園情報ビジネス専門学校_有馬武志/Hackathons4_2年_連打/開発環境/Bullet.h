#pragma once
//=============================================================================
//
// �v���C���[����(��ԏ������܂�) [ScenePlayer.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _Bullet_H_
#define _Bullet_H_

#include "main.h"
#include "scene.h"
#include "Scene2D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBullet : public CScene2D
{
public:
	CBullet(int nPrioryity = 1) : CScene2D::CScene2D(nPrioryity) { SetObjType(CScene::OBJTYPE_BULLET); };
	~CBullet() {};

	void	Set(float fLane, int nType, int nState);
	HRESULT Init(void);
	void	Update(void);
	void	Bomb(void);
	int &GetType(void) { return m_nType; };
	float &GetfLife(void) { return m_fLife; };

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float	m_fLife;
	int		m_nType;
	float	m_fMove;
	int		m_nState;
	float	m_fMoveY;
};

#endif
