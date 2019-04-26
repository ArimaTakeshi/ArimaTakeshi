//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"SceneModel.h"
#include"ScenePlayer.h"
#include"SceneEnemy.h"
#include "SceneBullet.h"
#include "dungeon.h"

#include "manager.h"
#include"Renderer.h"

//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneEnemy::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType)
{//�����o�ϐ��ɑ��
	GetnLevel() = CManager::GetPlayer(0)->GetnStage();
	CSceneTank::Set(pos, rot, col, modelD, modelU, TypeD, TypeU, DrawType);

	//HP�_�E��
	GetfMaxLife() *= 0.25f;
	GetfLife()[0] = GetfMaxLife();
	m_fDistance = 20.0f * 20.0f;
	m_fRot = 0.0f;
	m_fBack = 0.0f;
	m_nBulletID = 0;
	m_nCntFrame = 0;
	m_nCntStart = 0;
	m_nRank = rand() % (1 + CScenePlayer::GetnStage());
	m_fShotWait = 90 - m_nRank * 30.0f;
	if (m_fShotWait < 0.0f) { m_fShotWait = 0.0f; }

	GetShot()[0] = CSceneBullet::SHOT_ENEMY;
}
//=============================================================================
// �X�V����
//=============================================================================
void	CSceneEnemy::Update(void)
{
	if (CScenePlayer::GetbCamera())
	{//�����Ă���
		CScenePlayer *pPlayer = CManager::GetNearPlayer(GetPosition()[0]);
		D3DXVECTOR3 *pPlayerpos = pPlayer->GetPosition();
		D3DXVECTOR3 *pPos = GetPosition();
		bool bMove = false;
		bool bBoost = false;
		bool bBrake = false;
		bool bCharge = false;
		bool bShot = false;

		//�펞�u���[�L��Y
		if (m_nRank <= 1) { bBrake = true; }

		if (m_nCntFrame > 0)
		{//����s��
			m_nCntFrame--;
			GetfMoveAngle()[0] = m_fRot;
			bMove = true;
			if (m_fDistance < 20 * 20 && m_nRank > 1) { bBoost = true; }
			if (rand() % 4 == 0)
			{
				if (m_fDistance < 10 * 10) { GetfMoveAngle()[0] = m_fBack; }
			}
			m_fDistance = 9999.9f;
		}
		else
		{//���R�s��
			if (m_bFound)
			{//�v���C���[�ɋC�t���Ă���Ȃ� �߂Â�
				GetfMoveAngle()[0] = atan2f(pPlayerpos[0].x - pPos[0].x, pPlayerpos[0].z - pPos[0].z);
				if (m_nRank > 2) { bBrake = true; }
				if (m_nRank > 0) { bMove = true; }
			}
		}

		if (m_bFound)
		{//�v���C���[�ɋC�t���Ă���Ȃ�
			//�C������
			GetRotationU()[0].y += (atan2f(pPlayerpos[0].x - pPos[0].x + pPlayer->GetMove()[0].x * 3.0f, pPlayerpos[0].z - pPos[0].z + pPlayer->GetMove()[0].z * 3.0f)
				- GetRotationU()[0].y) * 0.8f;

			if (m_fShotWait > 0) { m_fShotWait--; }
			else if(pPlayer->GetfLife()[0] > 0.0f)
			{
				if (rand() % 3 < 2)
				{
					switch ((int)GetfCharge())
					{
					case 31:	bShot = true; m_fShotWait = 200.0f - m_nRank * 30.0f;	break;
					case 91:	bShot = true; m_fShotWait = 230.0f - m_nRank * 30.0f;	break;
					case 181:	bShot = true; m_fShotWait = 260.0f - m_nRank * 30.0f;	break;
					case 301:	bShot = true; m_fShotWait = 290.0f - m_nRank * 30.0f;	break;
					}
				}
				else if (!bShot && GetfCharge() > 90) { bShot = true; m_fShotWait = 300.0f - m_nRank * 30.0f; }
				if (!bShot) { bCharge = true; }
			}

			if (powf(pPlayerpos[0].x - pPos[0].x, 2) + powf(pPlayerpos[0].z - pPos[0].z, 2) > 80.0f * 80.0f)
			{
				m_bFound = false;
				m_fDistance = 9999.9f;
			}
		}
		else
		{//�T��
			if (powf(pPlayerpos[0].x - pPos[0].x, 2) + powf(pPlayerpos[0].z - pPos[0].z, 2) < 50.0f * 50.0f)
			{
				m_bFound = true;
				m_fDistance = 9999.9f;
			}
		}
		if (m_nRank == 0) { bMove = false; }
		CSceneTank::Update(bMove, bCharge, bShot, false, bBoost, bBrake, NULL);
	}//�t�F�[�h��
	else { CSceneTank::Update(false, false, false, false, false, false, NULL); }
	m_nNearBullet = 0;
}
//=============================================================================
// �X�V����
//=============================================================================
void	CSceneEnemy::SetDanger(float &fDistance, float fBulletRot, float fRotY, int &nID)
{
	if (m_fDistance > fDistance)
	{//������
		float fPlus = 0.0;
		float fWKRot;
		m_fDistance = fDistance;

		//�e�ƃv���C���[�܂ł̊p�x�𐮂���
		if (fRotY < 0.0f) 
		{ fRotY += D3DX_PI * 2; }
		if (fBulletRot < 0.0f) 
		{ fBulletRot += D3DX_PI * 2; }

		fRotY = ((int)(fRotY * 100.0f) % 628) * 0.01f;
		fBulletRot = ((int)(fBulletRot * 100.0f) % 628) * 0.01f;

		fPlus		= fBulletRot - D3DX_PI;
		fWKRot = fBulletRot - fPlus;
		fRotY		-= fPlus;
		if (fRotY > D3DX_PI * 2.0f) { fRotY -= D3DX_PI * 2; }
		if (fRotY < 0.0f) { fRotY += D3DX_PI * 2; }

		if (fWKRot < fRotY)
		{//�^�Ȃ�e���猩�č���
			m_fRot = fBulletRot + D3DX_PI * 0.5f;
		}
		else
		{//�U�Ȃ�e���猩�ĉE��
			m_fRot = fBulletRot - D3DX_PI * 0.5f;
		}

		if (m_nBulletID != nID) { m_nCntFrame = 5; }
		else { m_nCntFrame = 30; }
		m_fBack = fBulletRot;
		m_bFound = true;
	}
}

