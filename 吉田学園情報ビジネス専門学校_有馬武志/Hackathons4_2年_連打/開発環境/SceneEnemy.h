#pragma once
//=============================================================================
//
// �G�l�~�[���� [SceneEnemy.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEENEMY_H_
#define _SCENEENEMY_H_

#include "SceneModel.h"
#include "ScenePlayer.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneEnemy : public CSceneTank
{
public:
	CSceneEnemy(int nPrioryity = MODEL_PRIORITY) : CSceneTank::CSceneTank(nPrioryity) {};
	~CSceneEnemy() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType);
	HRESULT	Init(void) { CSceneTank::Init(); CScene::SetObjType(OBJTYPE_ENEMY); m_nRank = 0;  return S_OK; };
	void	Update(void);
	void	SetDanger(float &fDistance, float fBulletRot, float fRotY, int &nID);
	float	&GetfDistance(void) { return m_fDistance; };
	int		GetExp(void) { return 100 + (CScenePlayer::GetnStage() - 1) * 50 + m_nRank * 50; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float	m_fDistance;	//�e�Ƃ̋���
	float	m_fRot;			//�e���痣������
	float	m_fBack;		//�e�̊p�x
	float	m_fShotWait;	//���ˌ�҂�����
	int		m_nRank;		//�G�̃����N
	int		m_nCntFrame;	//�e���痣���F��
	int		m_nNearBullet;	//�߂��̒e��
	int		m_nBulletID;	//�e��ID
	bool	m_bFound;		//�v���C���[�𔭌��ς݂�
};

#endif
