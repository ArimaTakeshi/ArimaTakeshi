//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"Scene2D.h"
#include"enemy.h"
#include"player.h"

#include "manager.h"
#include "Game.h"
#include"Renderer.h"

#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DAMAGE_CLEAR	(10)		// �_���[�W����

#define ICE_CLEAR		(150)		// ����������

#define FIRE_CLEAR		(60)		// �R��������
#define FIRE_INTERVAL	(20)		// �R����Ԋu

#define STAN_CLEAR		(60)		// Ⴢꂽ����
#define STAN_INTERVAL	(60)		// Ⴢ��Ԋu

#define ENEMY_END		(0.0f)		// �G�S�[���n�_

//=============================================================================
// �ݒ菈��
//=============================================================================
void CEnemy::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture, ENEMYTYPE enemyType)
{//�����o�ϐ��ɑ��
	CScene2D::Set(pos, 40.0f, flengthY, fRot, nUV, nUV_X, nUV_Y, fCntState, state, col, Texture);

	m_enemyType = enemyType;		// �G�^�C�v�ݒ�

	m_state = ENEMYSTATE_NORMAL;	// ���
	m_nCntState = 0;				// ��ԃJ�E���g

	switch (m_enemyType)
	{// �^�C�v�ɂ���đ̗́A���x�ݒ�
	case ENEMYTYPE_NORMAL:			// �ʏ�
		m_nLife = 1000;
		m_nSpeed = -1.25f;
		break;
	case ENEMYTYPE_NORMAL2:			// �ʏ�
		m_nLife = 1500;
		m_nSpeed = -2.0f;
		break;
	case ENEMYTYPE_HP:				// �̗�
		m_nLife = 3000;
		m_nSpeed = -0.75f;
		break;
	case ENEMYTYPE_SPEED:			// ���x
		m_nLife = 750;
		m_nSpeed = -4.0f;
		break;
	}
	SetUV(m_enemyType, ENEMYTYPE_MAX, 1);
	BindTexture(CScene2D::Load(CScene2D::TEX_Enemy999));
	m_fRot = (rand() % (int)(D3DX_PI * 200)) * 0.01f;
}
//=============================================================================
// �X�V����
//=============================================================================
void	CEnemy::Update(void)
{
	CSound *pSound = CManager::GetSound();			//BGM�̍Đ�
	CPlayer *pPlayer = CManager::GetPlayer0();
	D3DXVECTOR3 *pos = CScene2D::GetPosition();			// �ʒu�擾
	float		fLengthX = CScene2D::GetfLengthX();		// X�T�C�Y�擾
	float		fLengthY = CScene2D::GetfLengthY();		// Y�T�C�Y�擾
	bool		bDelete = false;						// �j������
	float		nSpeed = m_nSpeed;						// ���x
	D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// �F

	switch (m_state)
	{// ���
	case ENEMYSTATE_NORMAL:			// �ʏ�
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �f�t�H���g�J���[

		break;
	case ENEMYSTATE_DAMAGE:			// �_���[�W
		m_nCntState++;						// ��ԃJ�E���g

		col = D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f);		// �F�ύX

		if (DAMAGE_CLEAR < m_nCntState)
		{// ���J�E���g��
			m_state = ENEMYSTATE_NORMAL;	// ���
			m_nCntState = 0;				// ��ԃJ�E���g
			col = D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f);	// �_���[�W�J���[
		}

		break;
	case ENEMYSTATE_ICE:			// ������		
		m_nCntState++;						// ��ԃJ�E���g

		nSpeed = 0.0f;						// �~�߂�

		col = D3DXCOLOR(0.6f, 0.85f, 0.9f, 1.0f);	// �f�t�H���g�J���[

		if (ICE_CLEAR < m_nCntState)
		{// ���J�E���g��
			m_state = ENEMYSTATE_NORMAL;	// ���
			m_nCntState = 0;				// ��ԃJ�E���g
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �f�t�H���g�J���[
		}

		break;
	case ENEMYSTATE_FIRE:			// �R����
		m_nCntState++;						// ��ԃJ�E���g

		if (m_nCntState % FIRE_INTERVAL < (FIRE_INTERVAL * 0.5f))
		{// ���Ԋu��
			if (m_nCntState % (int)(FIRE_INTERVAL * 0.5f) == 1)
			{// ���Ԋu��
				bDelete = SetDamage(1, 0);	// �_���[�W����
			}

			col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	// �_���[�W�J���[
		}
		else
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �f�t�H���g�J���[
		}

		if (FIRE_CLEAR < m_nCntState)
		{// ���J�E���g��
			m_state = ENEMYSTATE_NORMAL;	// ���
			m_nCntState = 0;				// ��ԃJ�E���g
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �f�t�H���g�J���[
		}

		break;
	case ENEMYSTATE_STAN:			// Ⴢꂽ
		m_nCntState++;						// ��ԃJ�E���g

		if (m_nCntState % STAN_INTERVAL < (STAN_INTERVAL * 0.5f))
		{// ���Ԋu��
			nSpeed = 0.0f;					// �~�߂�
			col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);	// �X�^���J���[
		}
		else
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �f�t�H���g�J���[
		}

		if (STAN_CLEAR < m_nCntState)
		{// ���J�E���g��
			m_state = ENEMYSTATE_NORMAL;	// ���
			m_nCntState = 0;				// ��ԃJ�E���g
		}

		break;
	}

	if (m_state != ENEMYSTATE_ICE && CManager::GetGame()->GetState() != CGame::STATE_OVER)
	{// ��������ԈȊO
		if (pPlayer != NULL)
		{// �v���C���[������
			if (pos->y - fLengthY < pPlayer->GetPosition()->y && pPlayer->GetPosition()->y < pos->y + fLengthY)
			{// Y�͈�
				if (pos->x - fLengthX <= pPlayer->GetPosition()->x + pPlayer->GetfLengthX())
				{// �v���C���[���i�񂾂�
					nSpeed = 0.0f;			// �~�߂�
					if (pPlayer->GetnInvincible() <= 0)
					{//Damage
						pPlayer->GetfLife() -= 1.0f;
						pPlayer->GetnInvincible() = 60;
						pPlayer->SetColor(D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f));
						pSound->Play(CSound::LABEL_DAMAGE);
					}
				}
			}
		}
	}

	pos->x += nSpeed;					// �ړ�����
	m_fRot += D3DX_PI * 0.01f;
	if (bDelete == false)
	{
		CScene2D::SetPosition(*pos);	// �ʒu�ݒ�
		CScene2D::SetColor(col);		// �F�ύX

		if (pos->x - fLengthX < ENEMY_END)
		{// ���ʒu�܂ōs������
			CManager::GetGame()->SetState(CGame::STATE_OVER);
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void	CEnemy::Draw(void)
{
	D3DXVECTOR3 pos = GetPosition()[0];
	SetPosition(GetPosition()[0] + D3DXVECTOR3(0.0f, cosf(m_fRot), 0.0f) * 10.0f);
	CScene2D::Draw();
	SetPosition(pos);
}
