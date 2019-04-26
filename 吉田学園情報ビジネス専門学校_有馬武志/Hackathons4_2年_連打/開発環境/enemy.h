#pragma once
//=============================================================================
//
// �G�l�~�[���� [Enemy.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CENEMY_H_
#define _CENEMY_H_

#include "Scene2D.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CEnemy : public CScene2D
{
public:
	typedef enum
	{// ���
		ENEMYSTATE_NORMAL = 0,
		ENEMYSTATE_DAMAGE,
		ENEMYSTATE_ICE,
		ENEMYSTATE_FIRE,
		ENEMYSTATE_STAN,
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	typedef enum
	{// �G�^�C�v
		ENEMYTYPE_NORMAL = 0,
		ENEMYTYPE_NORMAL2,
		ENEMYTYPE_SPEED,
		ENEMYTYPE_HP,
		ENEMYTYPE_MAX
	}ENEMYTYPE;

	CEnemy(int nPrioryity = 1) : CScene2D::CScene2D(nPrioryity) { SetObjType(CScene::OBJTYPE_ENEMY); };
	~CEnemy() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture, ENEMYTYPE enemyType);
	HRESULT	Init(void) { CScene2D::Init(); CScene::SetObjType(OBJTYPE_ENEMY); return S_OK; };
	void	Update(void);
	void	Draw(void);

	bool SetDamage(int nDamage, int nBulletType)
	{// �_���[�W����
		CSound *pSound = CManager::GetSound();
		m_nLife -= nDamage;		// �_���[�W�󂯂�

		switch (nBulletType)
		{
		case 4:		// �ʏ�
			break;
		case 3:		// �X
			if (rand() % 1 == 0)
			{// �m��
				m_state = ENEMYSTATE_ICE;	// ���������
				m_nCntState = 0;				// ��ԃJ�E���^
				CScene2D::SetColor(D3DXCOLOR(0.6f, 0.85f, 0.9f, 1.0f));
				pSound->Play(CSound::LABEL_ICE);
			}

			break;
		case 0:		// ��
			if (m_state != ENEMYSTATE_ICE)
			{
				if (rand() % 3 == 0)
				{// �m��
					m_state = ENEMYSTATE_FIRE;		// �R�������
					m_nCntState = 0;				// ��ԃJ�E���^
					CScene2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					pSound->Play(CSound::LABEL_FLAME);
				}
			}

			break;
		case 2:		// ��
			if (m_state != ENEMYSTATE_ICE)
			{
				if (rand() % 30 == 0)
				{// �m��
					m_state = ENEMYSTATE_STAN;		// Ⴢꂽ���
					m_nCntState = 0;				// ��ԃJ�E���^
					CScene2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
					pSound->Play(CSound::LABEL_STAN);
				}
			}

			break;
		}

		if (m_state == ENEMYSTATE_NORMAL)
		{// �R���ĂȂ�������
			m_state = ENEMYSTATE_DAMAGE;	// �_���[�W���
			m_nCntState = 0;				// ��ԃJ�E���^
			CScene2D::SetColor(D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f));
		}

		if (m_nLife < 1)
		{// �̗͂��O�ȉ��ɂȂ�����
			pSound->Play(CSound::LABEL_EXPLOSION001);
			if(rand() % 3 == 0){pSound->Play(CSound::LABEL_HIT999);}

			CSceneAnim2D *p2DAnim;
			if (SceneCreate(p2DAnim, 6))
			{//�����ł����Ȃ�@//�Ή�
				p2DAnim->Set(GetPosition()[0], 80.0f, 80.0f, D3DX_PI, 0, 10, 1, 4, 100.0f, CScene2D::STATE_BIG, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Explosion999);
				p2DAnim->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
			}
			if (SceneCreate(p2DAnim, 6))
			{//�����ł����Ȃ�@//�Ή�
				p2DAnim->Set(GetPosition()[0], 50.0f, 50.0f, D3DX_PI, 0, 10, 1, 4, 100.0f, CScene2D::STATE_BIG, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Explosion999);
				p2DAnim->BindDrawType(CScene::DRAW_TYPE_ADD);
			}
			Uninit();			// �I������

			return true;
		}
		return false;
	}

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	ENEMYTYPE	m_enemyType;			// �G�^�C�v
	ENEMYSTATE	m_state;				// ���
	int			m_nCntState;			// ��ԃJ�E���g
	int			m_nLife;				// �̗�
	float		m_nSpeed;				// ���x
	float		m_fRot;

};

#endif
