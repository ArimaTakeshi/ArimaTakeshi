//=============================================================================
//
// �v���C���[���� [ScenePlayer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"SceneModel.h"
#include"ScenePlayer.h"
#include "SceneBullet.h"
#include "dungeon.h"
#include "collision.h"
#include "sound.h"

#include "manager.h"
#include"Renderer.h"
#include "Versus.h"
#include "camera.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
int		CScenePlayer::m_nNumPlayer = 0;	//���v�v���C���[��
//int		CScenePlayer::m_nStage = BOSS_STAGE;
int		CScenePlayer::m_nStage = 0;
bool	CScenePlayer::m_bCamera = true;		//�J�����𓮂�������
bool	CScenePlayer::m_bShop;				//���݂��V���b�v���ǂ���

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneTank::Init(void)
{
	CSceneModel::Init();
	m_nLevel = 1;
	m_fLife = 10.0f;
	m_fAttack = 1.0f;
	m_fCharge = 0.0f;
	m_fSpeed = 0.2f * 1.5f;
	m_fBoost = 0.25f * 1.5f;
	m_fSlip = 0.03f;
	m_nBoostTime = 0;
	m_posold = GetPosition()[0];
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bShotDelete = true;
	//bBarrier = true;
	if (m_pEffect == NULL)
	{//�G�t�F�N�g���Z�b�g
		if (SceneCreate(m_pEffect, S3D_PRIORITY))
		{
			m_pEffect->Set(GetPosition()[0], GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 5.0f, CSceneAnim3D::TEX_BARRIER, CScene::DRAW_TYPE_ADD, 0, 5, 1, 4, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_MAX);
		}
	}
	m_shot = CSceneBullet::SHOT_ENEMY;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CSceneTank::Uninit(void)
{
	if (m_pEffect != NULL)
	{//��ԃG�t�F�N�g�̏I��
		m_pEffect->Uninit();
	}
	if (m_pEffectU != NULL)
	{//�C���G�t�F�N�g�̏I��
		m_pEffectU->Uninit();
	}

	CSceneModel::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneTank::Update(bool bMove, bool bCharge, bool bShot, bool bShelling, bool bBoost, bool bBrake, ITEM *pItem)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�̃|�C���^���擾
	CSceneAnimEffect	*pSceneAnim3D;			//�G�t�F�N�g�p
	CSceneAnim3D		*pSAnim3D;				//�G�t�F�N�g�p	���@�ǔ�����

	D3DXVECTOR3 *pos = GetPosition();
	D3DXVECTOR3 *rot = GetRotation();
	bool		bRiver = true, bCStop = true;
	float fSpeed = m_fSpeed, fBoost = m_fBoost;
	float fChargeP = 1.0f;

	if (pItem != NULL)
	{//�A�C�e��������Ȃ�
		switch (pItem->GetType())
		{//���ʔ���
		case ITEM::TYPE_SPDUP:		fSpeed *= 1.1f, fBoost *= 1.1f;		break;
		case ITEM::TYPE_NORIVER:	bRiver = false;		break;
		case ITEM::TYPE_NOSTOP:		bCStop = false;		break;
		case ITEM::TYPE_CHARGEUP:	fChargeP *= 1.5f;	break;
		}
	}
	//�҂����ԃJ�E���g
	if (m_fWaitTime > 0.0f) { m_fWaitTime -= 1.0f; }

	if (bMove && m_fWaitTime <= 0.0f)
	{//�����Ă���Ȃ� && �������ԂȂ�

		//���f���̐���
		float fRotPoor = m_fMoveAngle - rot[0].y;
		if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
		else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
		rot[0].y += fRotPoor * 0.15f;
		if (rot[0].y > D3DX_PI) { rot[0].y -= D3DX_PI * 2; }
		if (rot[0].y < -D3DX_PI) { rot[0].y += D3DX_PI * 2; }

		if (bBrake)
		{//�u���[�L��
			if (!bBoost)
			{//�u�[�X�g���Ȃ�G�t�F�N�g
				if (m_nBoostTime > 3)
				{//�h���t�g
					m_nBoostTime = 5;
					m_move *= 1.35f;
					m_fSlip = 0.8f;
					if (SceneCreate(pSAnim3D, S3D_PRIORITY))
					{//�����ł����Ȃ�@//�h���t�g�G�t�F�N�g
						pSAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, rot[0].y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_DRIFT, CScene::DRAW_TYPE_ADD,
							0, 3, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
					}
				}
			}
			if (m_nBoostTime > 1) { m_move *= 0.85f; }
			else { m_move *= 0.0f; fSpeed *= 0.8f; }
		}//�u���[�Lif

		if (m_nBoostTime <= 0)
		{//�u�[�X�g���g�p���Ă��Ȃ�
		}
		if(m_nBoostTime > 0)
		{//�u�[�X�g�g�p�� ����s��
			if (m_nBoostTime > 5)
			{//�u�[�X�g��
				m_fSlip = 0.8f;
				//m_move = D3DXVECTOR3(sinf(fMoveAngle), 0.0f, cosf(fMoveAngle)) * (m_fBoost * ((25 - m_nBoostTime) * 0.01f + 1.f));
				m_move += D3DXVECTOR3(sinf(m_fMoveAngle), 0.0f, cosf(m_fMoveAngle)) * (fBoost * (m_nBoostTime * 0.01f + 1.0f));
				if (m_nBoostTime > 7)
				{//�u�[�X�g�G�t�F�N�g
					if (SceneCreate(pSAnim3D, S3D_PRIORITY))
					{//�����ł����Ȃ� �G�t�F�N�g
						pSAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.97f, 0.02f, (m_nBoostTime - 7) * 0.1f + 0.1f), 10.0f, 10.0f, CSceneAnim3D::TEX_BOOST, CScene::DRAW_TYPE_ADD,
							0, 5, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADEOUT);
					}
				}
			}//�ҋ@����
			else { m_move += D3DXVECTOR3(sinf(m_fMoveAngle), 0.0f, cosf(m_fMoveAngle)) * (fSpeed * 0.35f); }
		}
	}
	else if(m_fWaitTime <= 0.0f)
	{//�~�܂��Ă���
		if (m_nBoostTime > 0)
		{
			if (bBoost)
			{//�u�[�X�g�L�[�������ꂽ�܂�
				m_fSlip = 0.8f;//�����␳
			}
			else
			{//�u�[�X�g�L�[��������Ă���
				m_nBoostTime = 0;
				m_move *= 0.0f;	//�}�u���[�L
			}
		}
		else
		{//�~�܂��
			m_nBoostTime = 0;
			m_move *= 0.0f;	//�}�u���[�L
		}
	}
	//�C���̌����ύX
	if (m_rotU.y > D3DX_PI) { m_rotU.y -= D3DX_PI * 2; }
	if (m_rotU.y < -D3DX_PI) { m_rotU.y += D3DX_PI * 2; }
	//��Ԉُ�X�V
	if (m_nFire > 0)
	{//�₯�Ǐ��
		m_nFire--;
		if (m_nFire % 60 == 0) 
		{//�G�t�F�N�g
			if (m_fLife > 1.0f) { m_fLife -= m_fMaxLife * 0.03f; if (m_fLife < 1.0f) { m_fLife = 1.0f; } }
			//pSound->Play(CSound::LABEL_FIRE);
			if (SceneCreate(pSceneAnim3D, DUNGEON_PRIORYITY))
			{//�����ł����Ȃ�@//�Ή�
				pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_FIRE, CScene::DRAW_TYPE_ADD,
					0, 10, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
			}
		}
	}
	if (m_nLightning > 0)
	{//���d���
		m_nLightning--;
		fChargeP *= 0.5f;
		if (m_nLightning % 60 == 0)
		{//�G�t�F�N�g
			//pSound->Play(CSound::LABEL_SPARK);
			if (SceneCreate(pSceneAnim3D, DUNGEON_PRIORYITY))
			{//�����ł����Ȃ�@//�d�C
				pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_LIGHTNING, CScene::DRAW_TYPE_ADD,
					0, 5, 2, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
			}
		}
	}
	if (m_nIce > 0)
	{//�������
		m_nIce--;
		m_move *= 0.8f;
		if (m_nIce % 60 == 0)
		{//�G�t�F�N�g
			//pSound->Play(CSound::LABEL_FIRE);
			if (SceneCreate(pSceneAnim3D, DUNGEON_PRIORYITY))
			{//�����ł����Ȃ�@//�Ή�
				pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_ICE, CScene::DRAW_TYPE_ADD,
					0, 5, 2, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
			}
		}
	}

	//�X�e�[�^�X�̍X�V
	m_posold = pos[0];	//1F�O�̏ꏊ�̕ۑ�
	pos[0] += m_move;	//move���ړ�
	m_move *= m_fSlip;	//�����ɉ����Č���
	m_fSlip += (0.3f - m_fSlip) * 0.1f;	//��Ԃɉ����������̕ω�
	m_nBoostTime--;		//�u�[�X�g�^�C������

	if (m_fWaitTime <= 0.0f)
	{//�U�������@�҂����ԂȂ��Ȃ�
		//�e�̃`���[�W
		if (bCharge) { m_fCharge += fChargeP; ChargeNews(pos); }
		else
		{//�e�̔���
			if (bShot) { Shot(pos, fChargeP); }
			m_fCharge = 0.0f;
		}

		if (bShelling)
		{//�ߋ����U��
			ShortAtk(pos);
			if (bCStop) { m_fCharge = 0.0f; }
		}
	}

	//�e�V�[���̍X�V
	CSceneModel::Update();

	//�_���W��������
	float fLengthX, fLengthZ;
	CSceneModel::GetLength(GetModel()[0], fLengthX, fLengthZ);

	//�_���W�����̂����蔻��
	CDungeon *pDungeon = CManager::GetDungeon();
	if (pDungeon != NULL) 
	{ 
		if (m_ObjType == CScene::OBJTYPE_PLAYER)
		{//�v���C���[�Ȃ� 
			if (CScenePlayer::GetnStage() != BOSS_STAGE && CManager::GetDungeon()->GetShop() != 1 && CScenePlayer::GetbCamera())
			{//�J�������ǔ����Ă���Ȃ�
				CCamera::camera.Collision(pos, fLengthX, fLengthZ);
			}
		}
		pDungeon->Collision(pos[0], m_posold, m_move, fLengthX, fLengthZ, bRiver); 
	}

	//�I�u�W�F�N�g�̂����蔻��
	CCollision::ObjectCollisionAll(pos[0], m_posold, fLengthX, fLengthZ, m_nID);

	//�G�t�F�N�g�̍X�V
	EffectUpdate();
}
//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CSceneTank::EffectUpdate(void)
{
	if (m_pEffect != NULL)
	{
		m_pEffect->GetPosition()[0] = GetPosition()[0];
		m_pEffect->GetRotation()[0] = GetRotation()[0];
	}
	if (m_pEffectU != NULL)
	{
		m_pEffectU->GetPosition()[0] = GetPosition()[0] + D3DXVECTOR3(sinf(m_rotU.y), 0.0f, cosf(m_rotU.y)) * 5.0f;
		m_pEffectU->GetRotation()[0].y = m_rotU.y;
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSceneTank::Draw(void)
{
	DrawModel(MODEL_D);
	DrawModel(MODEL_U);
}
//=============================================================================
// ���f���`��
//=============================================================================
void CSceneTank::DrawModel(int nModelID)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR3 pos = GetPosition()[0];	//�`��ꏊ
	D3DXVECTOR3 rot;			//�`��p�x
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���b�N�X
	MODEL model;
	LPDIRECT3DTEXTURE9 *tex = NULL;

	switch (nModelID)
	{
	case MODEL_D://�ԑ̂̐ݒ�
		model = GetModel()[0];
		tex = GetTexture();
		rot = GetRotation()[0];;
		break;
	case MODEL_U://�C���̐ݒ�
		model = m_ModelU;
		tex = m_pTexU;
		pos.y -= 0.5f;
		rot = m_rotU;
		break;
	}
	if (CScene::DrawPrepare(GetDrawType()[0], pD3DDevice)) 
	{ return; }

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���݂̃}�e���A�����擾
	pD3DDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_Model_Draw[model]->pBuffMatModel->GetBufferPointer();
	
	if (tex != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, tex[0]);
	}

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	for (int nCountData = 0; nCountData < (int)m_Model_Draw[model]->nNumMatModel; nCountData++)
	{
		// �}�e���A���̐ݒ�
		pMat = (D3DXMATERIAL*)m_Model_Draw[model]->pBuffMatModel->GetBufferPointer();
		pD3DDevice->SetMaterial(&pMat[nCountData].MatD3D);
		pMat->MatD3D.Diffuse = GetColor()[0];
		// ���f��(�p�[�c)�̕`��
		m_Model_Draw[model]->MeshModel->DrawSubset(nCountData);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pD3DDevice->SetMaterial(&matDef);
	pD3DDevice->SetTexture(0, NULL);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneTank::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType)
{//�����o�ϐ��ɑ��
	GetPosition()[0] = pos;		GetRotation()[0] = rot;		GetColor()[0] = col;
	m_rotU = rot; GetPositionOld()[0] = pos;
	GetModel()[0] = modelD;	m_ModelU = modelU;	//���f���ԍ�
	GetDrawType()[0] = DrawType;					//�`����@

	//���f���Ɖ摜�̐���
	m_Type[0] = TypeD;
	m_Type[1] = TypeU;

	BindTexture(CSceneModel::Load(TypeD));
	m_pTexU = CSceneModel::Load(TypeU);
	CSceneModel::LoadModel(modelD);
	CSceneModel::LoadModel(m_ModelU);
	GetStatus();

	m_nUV = m_Type[1] - TEX_PTN_01;

	if (m_pEffectU == NULL)
	{//�G�t�F�N�g���Z�b�g
		if (SceneCreate(m_pEffectU, SAnim3DF_PRIORITY))
		{
			m_pEffectU->Set(GetPosition()[0], GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CScene3D::TEX_MARKER, m_nUV, 8, 1, CScene::DRAW_TYPE_ADD);
		}
	}

	//�̗͂̏�����
	m_fLife = m_fMaxLife;
}
//=============================================================================
// �X�e�[�^�X�ݒ菈��
//=============================================================================
void CSceneTank::GetStatus(void)
{
	float fLife, fLifeU;

	float fAtk, fDef;
	float fSpd, fBoost, fSpdU, fBoostU;

	switch (m_Type[0])
	{//�ԑ�
	case TEX_PTN_01: fLife = 2550; fDef = 85; fSpd = 0.11f * 0.8f;	fBoost = 0.11f * 0.8f;	break;
	case TEX_PTN_02: fLife = 2550; fDef = 65; fSpd = 0.1f * 0.8f;	fBoost = 0.09f * 0.8f;	break;
	case TEX_PTN_03: fLife = 2550; fDef = 90; fSpd = 0.11f * 0.8f; fBoost = 0.15f * 0.8f; break;
	case TEX_PTN_04: fLife = 2550; fDef = 95; fSpd = 0.115f * 0.8f; fBoost = 0.105f * 0.8f; break;
	case TEX_PTN_05: fLife = 2550; fDef = 95; fSpd = 0.11f * 0.8f;	fBoost = 0.115f * 0.8f;	break;
	case TEX_PTN_06: fLife = 2550; fDef = 60; fSpd = 0.095f * 0.8f; fBoost = 0.085f * 0.8f; break;
	case TEX_PTN_07: fLife = 2550; fDef = 90; fSpd = 0.105f * 0.8f;	fBoost = 0.125f * 0.8f;	break;
	case TEX_PTN_08: fLife = 2550; fDef = 95; fSpd = 0.115f * 0.8f;	fBoost = 0.135f * 0.8f;	break;
	}
	switch (m_Type[1])
	{//�C��
	case TEX_PTN_01: fLifeU = 350; fAtk = 85; fSpdU = 0.11f * 0.2f;  fBoostU = 0.11f * 0.2f;  break;
	case TEX_PTN_02: fLifeU = 350; fAtk = 100; fSpdU = 0.1f * 0.2f;	 fBoostU = 0.09f * 0.2f;   break;
	case TEX_PTN_03: fLifeU = 350; fAtk = 75; fSpdU = 0.11f * 0.2f; fBoostU = 0.15f * 0.2f; break;
	case TEX_PTN_04: fLifeU = 350; fAtk = 90; fSpdU = 0.115f * 0.2f; fBoostU = 0.105f * 0.2f; break;
	case TEX_PTN_05: fLifeU = 350; fAtk = 85; fSpdU = 0.11f * 0.2f;  fBoostU = 0.115f * 0.2f;  break;
	case TEX_PTN_06: fLifeU = 350; fAtk = 115; fSpdU = 0.095f * 0.2f; fBoostU = 0.085f * 0.2f; break;
	case TEX_PTN_07: fLifeU = 350; fAtk = 90; fSpdU = 0.105f * 0.2f;  fBoostU = 0.125f * 0.2f;  break;
	case TEX_PTN_08: fLifeU = 350; fAtk = 95; fSpdU = 0.115f * 0.2f;  fBoostU = 0.135f * 0.2f;  break;
	}
	m_fMaxLife = (((fLife * 0.02f) * m_nLevel) + fLife) + (((fLifeU * 0.02f) * m_nLevel) + fLifeU);
	m_fAttack = fAtk + ((fAtk * 0.02f) * m_nLevel);
	m_fDefense = fDef + ((fDef * 0.02f) * m_nLevel);

	m_fSpeed = 0.5f - fSpd - fSpdU;
	m_fBoost = 0.5f - fBoost - fBoostU;
	if (m_fMaxLife < m_fLife) { m_fLife = m_fMaxLife; }
}
//=============================================================================
// �`���[�W���Ƃ̂��m�点����
//=============================================================================
void	CSceneTank::ChargeNews(D3DXVECTOR3 *&pos)
{
	CSound *pSound = CManager::GetSound();

	//�`���[�W�ϊ�
	bool bCharge = false;
	bool bNews = false;
	int nUV = 0;
	int nChargeEffect = 0;

	if (m_fCharge == 30 - 18) { bNews = true; }

	if (m_fCharge >= 30)
	{
		nChargeEffect = 1;
		if (m_fCharge == 30) { nUV = 2; bCharge = true; }
		else if (m_fCharge == 90 - 18) { bNews = true; }

		if (m_fCharge >= 90)
		{
			nChargeEffect = 2;
			if (m_fCharge == 90) { nUV = 0; bCharge = true; }
			else if (m_fCharge == 180 - 18) { bNews = true; }

			if (m_fCharge >= 180)
			{
				nChargeEffect = 3;
				if (m_fCharge == 180) { nUV = 8; bCharge = true; }
				else if (m_fCharge == 300 - 18) { bNews = true; }

				if (m_fCharge >= 300)
				{
					nChargeEffect = 4;
					if (m_fCharge == 300) { nUV = 10; bCharge = true; }
					if (m_fLife > 1.0f) { m_fLife -= 2.0f; }
				}
			}
		}
	}

	if (bNews)
	{//�m�点�̃G�t�F�N�g
		CSceneAnimEffect *pSceneAnim3D;
		if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
		{//�`���[�W�^�߂̒m�点
			pSceneAnim3D->Set(D3DXVECTOR3(pos[0].x, 0.5f, pos[0].z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30.0f, 30.0f, CSceneAnim3D::TEX_CHARGE, CScene::DRAW_TYPE_ZADD, 0, 10, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CSceneAnim3D::STATE_NORMAL, pos, GetThisScene());
		}
	}
	if (bCharge)
	{//�`���[�W�����G�t�F�N�g
		CSceneEffect *pScene3D = NULL;
		if (SceneCreate(pScene3D, SAnim3D_PRIORITY))
		{ //�`���[�W�g
			pScene3D->Set(D3DXVECTOR3(pos[0].x, 0.0f, pos[0].z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3.0f, 3.0f, CScene3D::TEX_CHARGE, nUV, 6, 2, CScene::DRAW_TYPE_ZOVERLAY, pos, GetThisScene());
			pScene3D->GetState()[0] = CScene3D::STATE_FADESPIN;
		}
	}

	if ((int)m_fCharge % (9 - nChargeEffect * 2) == 0)
	{
		CSceneAnim3D *pScene3D = NULL;
		if (SceneCreate(pScene3D, SAnim3D_PRIORITY))
		{//�т�т�
			pScene3D->Set(D3DXVECTOR3(pos[0].x, 3.0f, pos[0].z),
				D3DXVECTOR3(0.0f, (float)(rand() % (int)(D3DX_PI * 2000)) / 1000, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 20.0f, CSceneAnim3D::TEX_CHARGE2, CScene::DRAW_TYPE_ZADD, 0, 8, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CSceneAnim3D::STATE_NORMAL);
			pScene3D->GetState()[0] = CScene3D::STATE_FADEOUT2;
		}
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot(D3DXVECTOR3 *&pos, float fChargeP)
{
	int nCharge;	//�`���[�W��
	int nUV = -1;

	//�`���[�W�ϊ�
	if		(m_fCharge > 300)	{ nCharge = CHARGE_300;		if (m_fCharge < 300 + SHOT_JUST * fChargeP) { nUV = 6; } }
	else if (m_fCharge > 180)	{ nCharge = CHARGE_180;		if (m_fCharge < 180 + SHOT_JUST * fChargeP) { nUV = 4; } }
	else if (m_fCharge > 90)	{ nCharge = CHARGE_90;		if (m_fCharge < 90.0f + SHOT_JUST * fChargeP) { nUV = 3; } }
	else if (m_fCharge > 30)	{ nCharge = CHARGE_30;		if (m_fCharge < 30.0f + SHOT_JUST * fChargeP) { nUV = 1; } }
	else						{ nCharge = CHARGE_NO; }

	switch (m_Type[1])
	{
	case CSceneTank::TEX_PTN_01:	Shot_Ptn01(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_02:	Shot_Ptn02(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_03:	Shot_Ptn03(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_04:	Shot_Ptn04(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_05:	Shot_Ptn05(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_06:	Shot_Ptn06(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_07:	Shot_Ptn07(nCharge, pos);	break;
	case CSceneTank::TEX_PTN_08:	Shot_Ptn08(nCharge, pos);	break;
	}

	if (nUV != -1)
	{//�W���X�g�{�[�i�X
		CSound *pSound = CManager::GetSound();

		CSceneEffect *pScene3D;
		CScenePairBulletSet *pPairBulletSet;
		CScenePairBullet	*pPairBullet;

		if (SceneCreate(pScene3D, SAnim3D_PRIORITY))
		{//�����ł����Ȃ�@//�`���[�W�g
			pScene3D->Set(D3DXVECTOR3(pos[0].x, 0.0f, pos[0].z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 5.0f, CScene3D::TEX_CHARGE, nUV, 6, 2, CScene::DRAW_TYPE_ZADD, NULL, NULL);
			pScene3D->GetState()[0] = CScene3D::STATE_FADESPIN;
		}

		switch (nUV)
		{//�W���X�g�{�[�i�X�@�W���X�g�`���[�W���ɂ���Ēǉ��e��
		case 1:
			CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN00, pos[0], m_move, GetRotationU()[0].y, true, 0.012f, 0.985f, SHOT_LIFE * 0.0f, 0.0f, 0.0f,
				3.0f, 3.0f, D3DX_PI, 0.0f, 8, 0, CSceneBullet::CHANGE_GRAVITY, m_fAttack + 200, false, &m_bShotDelete, 48 + m_nUV * 2);
			break;
		case 3:
			if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
					SHOT_LIFE - 100.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, m_fAttack, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.02f, 1, 6,
					pos, NULL, &m_bShotDelete);
				pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
					SHOT_LIFE - 100.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, m_fAttack, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.02f, 1, 6,
					pos, NULL, &m_bShotDelete);
				pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			break;
		case 4:
			if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, m_fAttack, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.02f, 1, 20,
					pos, &m_rotU.y, &m_bShotDelete);
				pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, m_fAttack, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.02f, 1, 20,
					pos, &m_rotU.y, &m_bShotDelete);
				pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			break;
		case 6:
			if (SceneCreate(pPairBullet, BULLET_PRIORITY))
			{//�����ł����Ȃ�//�q�@
				pPairBullet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.3f, 0, 0.1f, 0.0f, D3DX_PI * 0.0f, 0.99f, m_fAttack + 100, 1.5f, 1.0f, 0.5f, 0.5f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.05f, 1, 10,
					pos, &m_rotU.y, &m_bShotDelete);
				pPairBullet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			if (SceneCreate(pPairBullet, BULLET_PRIORITY))
			{//�����ł����Ȃ�//�q�@
				pPairBullet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * -0.25f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.3f, 0, 0.1f, 0.0f, D3DX_PI * 0.0f, 0.99f, m_fAttack + 100, 1.5f, 1.0f, 0.5f, 0.5f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.05f, 1, 10,
					pos, &m_rotU.y, &m_bShotDelete);
				pPairBullet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			if (SceneCreate(pPairBullet, BULLET_PRIORITY))
			{//�����ł����Ȃ�//�q�@
				pPairBullet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.3f, 0, 0.1f, 0.0f, D3DX_PI * 0.0f, 0.99f, m_fAttack + 100, 1.5f, 1.0f, 0.5f, 0.5f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.05f, 1, 10,
					pos, &m_rotU.y, &m_bShotDelete);
				pPairBullet->SetObjType(CScene::OBJTYPE_BULLET2);
			}
			break;
		}
	}
}
//=============================================================================
// �ߐڍU��, �C���ɂ���ĕς��
//=============================================================================
void CSceneTank::ShortAtk(D3DXVECTOR3 *&pos)
{
	CSound *pSound = CManager::GetSound();

	switch (m_Type[1])
	{
	case CSceneTank::TEX_PTN_01:	Short_Ptn01(pos);	break;
	case CSceneTank::TEX_PTN_02:	Short_Ptn02(pos);	break;
	case CSceneTank::TEX_PTN_03:	Short_Ptn03(pos);	break;
	case CSceneTank::TEX_PTN_04:	Short_Ptn04(pos);	break;
	case CSceneTank::TEX_PTN_05:	Short_Ptn05(pos);	break;
	case CSceneTank::TEX_PTN_06:	Short_Ptn06(pos);	break;
	case CSceneTank::TEX_PTN_07:	Short_Ptn07(pos);	break;
	case CSceneTank::TEX_PTN_08:	Short_Ptn08(pos);	break;
	}
}
//=============================================================================
//�C��PTN01 �C��
//=============================================================================
void CSceneTank::Short_Ptn01(D3DXVECTOR3 *&pos)
{
	CScenePairBullet2 *pPairBullet2;

	m_fWaitTime = 25;
	
	if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
	{//�����ł����Ȃ�
		pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.55f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 12.0f, 48 + m_nUV * 2,
			SHOT_LIFE - 9.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.1f, 0.97f, (m_fAttack + 500.0f) * 2.0f, m_rotU.y, 13.0f, 0.1f,
			pos, &m_rotU.y, true, &m_bShotDelete);
		//pPairBulletSet->SetObjType(CScene::OBJTYPE_NONE);
	}
}
//=============================================================================
//�C��PTN02 �C��
//=============================================================================
void CSceneTank::Short_Ptn02(D3DXVECTOR3 *&pos)
{
	m_fWaitTime = 15;

	CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN_FIRE2, pos[0], m_move, m_rotU.y, true, 0.025f, 0.97f, SHOT_LIFE * 0.99f, 0.0f, 0.0f,
		2.5f, 5.0f, D3DX_PI * 0.26f, -0.5f, 8, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 200) * 1.5f, true, &m_bShotDelete, 16 + m_nUV * 2);
}
//=============================================================================
//�C��PTN03 �C��
//=============================================================================
void CSceneTank::Short_Ptn03(D3DXVECTOR3 *&pos)
{
	m_fWaitTime = 20;

	CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM01, pos[0], m_move, m_rotU.y, true, 0.035f, 0.97f, SHOT_LIFE * 0.9f, 0.0f, 0.0f,
		1.5f, 3.0f, D3DX_PI * 0.1f, 3.0, 32, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 250, true, &m_bShotDelete, 16 + m_nUV * 2);
}
//=============================================================================
//�C��PTN04 �C��
//=============================================================================
void CSceneTank::Short_Ptn04(D3DXVECTOR3 *&pos)
{
	m_fWaitTime = 15;

	CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_DIFFUSION, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE - 6.0f, 0.0f, 0.0f,
		6.0f, 6.0f, D3DX_PI * 0.26f, 5.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 400, true, &m_bShotDelete, 16 * 1 + m_nUV * 2);
}
//=============================================================================
//�C��PTN05 �C��
//=============================================================================
void CSceneTank::Short_Ptn05(D3DXVECTOR3 *&pos)
{
	CScenePairBullet2 *pPairBullet2;

	m_fWaitTime = 25;

	if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
	{//�����ł����Ȃ�
		pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.55f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 48 + m_nUV * 2,
			SHOT_LIFE - 9.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 350.0f) * 2, m_rotU.y, 8.0f, 0.1f,
			pos, &m_rotU.y, true, &m_bShotDelete);
	}
	if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
	{//�����ł����Ȃ�
		pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 1.1f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 48 + m_nUV * 2,
			SHOT_LIFE - 18.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 350.0f) * 2, m_rotU.y, 18.0f, 0.1f,
			pos, &m_rotU.y, true, &m_bShotDelete);
	}
}
//=============================================================================
//�C��PTN06 �C��
//=============================================================================
void CSceneTank::Short_Ptn06(D3DXVECTOR3 *&pos)
{
	CScenePairBullet2 *pPairBullet2;

	m_fWaitTime = 30;

	m_fSlip = 1.65f;

	if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
	{//�����ł����Ȃ�
		pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 10.0f, 16 + m_nUV * 2,
			SHOT_LIFE - 20.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 300.0f) * 1.5f, m_rotU.y, 13.0f, 1.0f,
			pos, &m_rotU.y, true, &m_bShotDelete);
	}
	if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
	{//�����ł����Ȃ�
		pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 10.0f, 16 + m_nUV * 2,
			SHOT_LIFE - 20.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 300.0f) * 1.5f, m_rotU.y, 13.0f, 1.0f,
			pos, &m_rotU.y, true, &m_bShotDelete);
	}
}
//=============================================================================
//�C��PTN07 �C��
//=============================================================================
void CSceneTank::Short_Ptn07(D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet;

	m_fWaitTime = 30;

	CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE - 10.0f, 0.0f, 0.0f,
		5.0f, 10.0f, D3DX_PI * 0.51f, 10.0f, 4, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 300) * 2, true, &m_bShotDelete, 16 * 1 + m_nUV * 2);

	if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
	{//�����ł����Ȃ�
		pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 16 + m_nUV * 2,
			SHOT_LIFE - 20, 0, 0.02f, 0.0f, D3DX_PI / 20, 0.97f, m_fAttack + 150, m_rotU.y, 5.0f, 0.1f, CSceneBullet::SET_NEEDLE, m_rotU.y - D3DX_PI * 0.5f, D3DX_PI / 20, 1, 2,
			pos, NULL, &m_bShotDelete);
		pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
	}
}
//=============================================================================
//�C��PTN08 �C��
//=============================================================================
void CSceneTank::Short_Ptn08(D3DXVECTOR3 *&pos)
{
	m_fWaitTime = 30;

	CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM00, pos[0], m_move, m_rotU.y, true, 0.03f, 0.95f, SHOT_LIFE * 0.9f, 0.0f, 0.0f,
		5.0f, 10.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 450) * 2, true, &m_bShotDelete, 16 * 6 + m_nUV * 2);
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn01(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet = NULL;
	CScenePairBullet2	*pPairBullet2 = NULL;
	CScenePairBullet	*pPairBullet = NULL;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			5.0f, 5.0f, D3DX_PI * 0.128f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 350, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_90:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 100.0f, 0, 0.1f, 0.0f, D3DX_PI * 0.0f, 0.97f, m_fAttack + 200, m_rotU.y, 0.0f, 1.0f, CSceneBullet::SET_RANDSHOT, m_rotU.y, D3DX_PI * 0.3f, 1, 6,
				pos, &m_rotU.y, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);

		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 4.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 450, false, &m_bShotDelete, 16 + m_nUV * 2);

		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.025f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 0.26f, -10.0f, 8, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 300, false, &m_bShotDelete, 16 + m_nUV * 2);
		break;
	case CHARGE_180:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 0.51f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 400, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN00, pos[0], m_move, m_rotU.y + D3DX_PI * 0.25f, true, -2.0f, 0.2f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 4.0f, D3DX_PI * 0.51f, 0.0f, 8, 1, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 48 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN00, pos[0], m_move, m_rotU.y - D3DX_PI * 0.25f, true, -2.0f, 0.2f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 4.0f, D3DX_PI * 0.51f, 0.0f, 8, 1, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 48 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 3.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.015f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 3.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.015f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}

		break;
	case CHARGE_300:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * (1.0f / 8.0f), true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 0.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 650, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, -5.0f, 8, 0, CSceneBullet::CHANGE_NO, m_fAttack + 650, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 5.0f, 8, 0, CSceneBullet::CHANGE_NO, m_fAttack + 650, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * (1.0f / 8.0f), true, -2.0f, 0.2f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 0.0f, 8, 1, CSceneBullet::CHANGE_NO, m_fAttack + 650, false, &m_bShotDelete, 16 + m_nUV * 2);

		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 100.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.04f, 0.97f, m_fAttack + 150, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_RELEASE, m_rotU.y, D3DX_PI * -0.04f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 100.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.04f, 0.97f, m_fAttack + 150, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_RELEASE, m_rotU.y, D3DX_PI * 0.04f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
	//CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN_FIRE2, pos[0], m_move, rot[0].y, m_nID, D3DX_PI * 0.5f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST2, 50);


	//CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, rot[0].y, m_nID, D3DX_PI * 1.5f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST2, 16);

	//CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN02, pos[0], m_move, rot[0].y, m_nID, D3DX_PI * 0.5f, 0.0f, 8, 0, CSceneBullet::CHANGE_GRAVITY, 50);
	//CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN02, pos[0], m_move, rot[0].y, m_nID, D3DX_PI, -10.0f, 16, 0, CSceneBullet::CHANGE_GRAVITY2, 50);





			//Create(bulletNor); if (bulletNor != NULL)
			//{//�����ł����Ȃ�
			//	bulletNor->Set(CSceneBullet::SHOT_IGNORED, pos[0] + D3DXVECTOR3(sinf(fAngle) * -5.0f, 2.0f, cosf(fAngle) * -5.0f), m_move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
			//		0.0f, 25, 0.1f, 0.0f, 0.3f, 0.99f, CSceneBullet::CHANGE_FAST);
			//}

			//float	fRange = D3DX_PI;int		nNumBullet = 8;
			//BOSS�p�@****************************************************************


			//�e�X�g�p ��납��d�͕t��
			//float	fRange = D3DX_PI; int		nNumBullet = 1;
			//Create(bulletSet); if (bulletSet != NULL)
			//{//�����ł����Ȃ�
			//	bulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(sinf(fAngle), 2.0f, cosf(fAngle)) * 1.0f, m_move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3.0f, 5.0f, 50,
			//			0.0f, 0, 0.015f, 0.001f, 0.0f, 0.98f, CSceneBullet::CHANGE_FAST2, CSceneBullet::SET_BACK_G, fAngle, 0.0f, 1, 5, m_nID);
			//}


}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn02(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet = NULL;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM00, pos[0], m_move, m_rotU.y, true, 0.03f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			5.0f, 10.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 30.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.06f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.03f, 1, 5,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 30.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.06f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.03f, 1, 5,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case CHARGE_90:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM02, pos[0], m_move, m_rotU.y, false, 0.03f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			5.0f, 10.0f, D3DX_PI * 0.51f, 8.0f, 4, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.03f, 1, 5,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.03f, 1, 5,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case CHARGE_180:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM01, pos[0], m_move, m_rotU.y, false, 0.03f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			5.0f, 10.0f, D3DX_PI * 0.125f, 8.0f, 33, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 90.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.03f, 1, 5,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 90.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.03f, 1, 5,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case CHARGE_300:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM01, pos[0], m_move, m_rotU.y, true, 0.03f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			12.0f, 24.0f, D3DX_PI * 0.5f, 8.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 1000, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM02, pos[0] + D3DXVECTOR3(sinf(m_rotU.y), 0.0f, cosf(m_rotU.y)) * -10.0f, m_move, m_rotU.y, false, 0.03f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 5.0f, D3DX_PI * 0.51f, 18.0f, 4, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 400, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.03f, 1, 4,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 8.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.03f, 1, 4,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn03(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 35, 0, 0.02f, 0.0f, D3DX_PI / 35, 0.97f, m_fAttack + 250, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_BEAM, m_rotU.y - D3DX_PI * 0.5f, D3DX_PI / 35, 1, 6,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_90:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 70, 0, 0.03f, 0.0f, D3DX_PI * 0.06f, 0.97f, m_fAttack + 200, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.12f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM02, pos[0], m_move, m_rotU.y, true, 0.035f, 0.97f, SHOT_LIFE * 0.9f, 0.0f, 0.0f,
			1.5f, 2.5f, D3DX_PI * 0.6f, 10.0, 4, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 275, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 5.0f, 16, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_180:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 70, 0, 0.03f, 0.0f, D3DX_PI * 0.06f, 0.97f, m_fAttack + 150, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.12f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 70, 0, 0.03f, 0.0f, D3DX_PI * -0.06f, 0.97f, m_fAttack + 150, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.12f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM01, pos[0], m_move, m_rotU.y, true, 0.035f, 0.97f, SHOT_LIFE * 0.9f, 0.0f, 0.0f,
			1.5f, 2.5f, D3DX_PI * 0.2f, 5.0, 32, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 300, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 12, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * 0.125f, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 8.0f, 12, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);

		break;
	case CHARGE_300:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 70, 0, 0.03f, 0.0f, D3DX_PI * 0.06f, 0.97f, m_fAttack + 250, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.12f, 1, 1,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 140, 0, 0.02f, 0.0f, D3DX_PI / 20, 0.97f, m_fAttack + 250, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_BEAM, m_rotU.y - D3DX_PI * 0.5f, D3DX_PI / 20, 1, 6,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.035f, 0.97f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, -10.0, 8, 0, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 16 + m_nUV * 2);
		break;
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn04(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet;
	CScenePairBullet	*pPairBullet;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_DIFFUSION, pos[0], m_move, m_rotU.y, true, 0.012f, 0.97f, SHOT_LIFE - 30.0f, 0.0f, 0.0f,
			3.0f, 3.0f, D3DX_PI * 0.26f, 5.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 300, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_DIFFUSION, pos[0], m_move, m_rotU.y, false, 0.012f, 0.97f, SHOT_LIFE - 15.0f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 0.26f, 5.0f, 8, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 300, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_90:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_SETTING0, pos[0], m_move, m_rotU.y, true, 0.03f, 0.97f, SHOT_LIFE - 30.0f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 0.26f, 5.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 200, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 35, 0, 0.01f, 0.0f, D3DX_PI * 0.06f, 0.97f, m_fAttack + 250, m_rotU.y, 15.0f, 0.1f, CSceneBullet::SET_TURN, m_rotU.y, D3DX_PI * 0.6f, 1, 1,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * 0.125f, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 12, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_180:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PDIFFUSION, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE - 10.0f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 0.26f, 5.0f, 3, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 700) / 2, true, &m_bShotDelete, 16 * 1 + m_nUV * 2);

		if (SceneCreate(pPairBullet, BULLET_PRIORITY))
		{//�����ł����Ȃ�//�q�@
			pPairBullet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE * 0.85f, 0, 0.1f, 0.0f, D3DX_PI * 0.0f, 0.97f, m_fAttack + 200, 4.0f, 2.0f, 0.5f, 0.5f, CSceneBullet::SET_BACK_G2, m_rotU.y, D3DX_PI * 0.05f, 1, 3,
				pos, &m_rotU.y, &m_bShotDelete);
			pPairBullet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * 0.125f, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_300:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PDIFFUSION, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE - 10.0f, 0.0f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, -10.0f, 3, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 700) / 2, true, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * 0.125f, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI * 0.125f, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn05(int nCharge, D3DXVECTOR3 *&pos)
{
	CSceneNorBullet		*bulletNor;
	CScenePairBullet2	*pPairBullet2;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		if (SceneCreate(bulletNor, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			bulletNor->Set(m_shot, pos[0] + D3DXVECTOR3(sinf(m_rotU.y) * 3.0f, 0.0f, cosf(m_rotU.y) * 3.0f), m_move * 0.1f, D3DXVECTOR3(0.0f, m_rotU.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 16 * 3 + m_nUV * 2,
				SHOT_LIFE * 0.3f, 0, 0.01f, 0.0f, 0.0f, 0.97f, CSceneBullet::CHANGE_FAST2, m_fAttack + 250, false, &m_bShotDelete);
			if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.3f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 10.0f, 1.0f,
					bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
			}
			if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 48 + m_nUV * 2,
					SHOT_LIFE * 0.3f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 10.0f, 1.0f,
					bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
			}
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.0f, 0.2f, SHOT_LIFE * 0.0f, -0.1f, 0.015f,
			3.0f, 3.0f, D3DX_PI * 1.1f, 0.0f, 6, 2, CSceneBullet::CHANGE_NO, m_fAttack + 300, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		break;
	case CHARGE_90:
		if (SceneCreate(bulletNor, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			bulletNor->Set(m_shot, pos[0] + D3DXVECTOR3(sinf(m_rotU.y) * 3.0f, 0.0f, cosf(m_rotU.y) * 3.0f), m_move * 0.1f, D3DXVECTOR3(0.0f, m_rotU.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 16 * 3 + m_nUV * 2,
				SHOT_LIFE * 0.3f, 0, 0.01f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_FAST2, m_fAttack + 250, false, &m_bShotDelete);
			for (int nCount = 0; nCount < 4; nCount++)
			{
				if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * (0.5f * nCount), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 48 + m_nUV * 2,
						SHOT_LIFE * 0.3f, 0, 0.0f, 0.0f, D3DX_PI * -0.01f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 15.0f, 1.0f,
						bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
				}
			}
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 12, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);

		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, -1.0f, 0.2f, SHOT_LIFE * 0.5f, 0.1f, 0.015f,
			4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, 8, 2, CSceneBullet::CHANGE_NO, m_fAttack + 300, false, &m_bShotDelete, 48 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.0f, 0.2f, SHOT_LIFE * 0.0f, 0.1f, 0.015f,
			8.0f, 8.0f, D3DX_PI * 1.1f, 0.0f, 6, 2, CSceneBullet::CHANGE_NO, m_fAttack + 300, false, &m_bShotDelete, 16 * 4 + m_nUV * 2);
		break;
	case CHARGE_180:
		if (SceneCreate(bulletNor, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			bulletNor->Set(m_shot, pos[0] + D3DXVECTOR3(sinf(m_rotU.y) * 3.0f, 0.0f, cosf(m_rotU.y) * 3.0f), m_move * 0.1f, D3DXVECTOR3(0.0f, m_rotU.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 16 * 3 + m_nUV * 2,
				SHOT_LIFE * 0.3f, 0, 0.01f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_FAST2, m_fAttack + 150, false, &m_bShotDelete);
			for (int nCount = 0; nCount < 4; nCount++)
			{
				if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * (0.5f * nCount), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 16 * 6 + m_nUV * 2,
						SHOT_LIFE * 0.3f, 0, 0.0f, 0.0f, D3DX_PI * -0.01f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 10.0f, 1.0f,
						bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
				}
				if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * (0.5f * nCount) + D3DX_PI * 0.25f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 16 * 6 + m_nUV * 2,
						SHOT_LIFE * 0.3f, 0, 0.0f, 0.0f, D3DX_PI * -0.01f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 10.0f, 1.0f,
						bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
				}
			}
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);

		//�Z�n��
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.0f, 0.2f, 6.0f, 0.1f, 0.015f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 5.0f, 8, 2, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 16 * 4 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.0f, 0.2f, 6.0f, -0.1f, 0.015f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 5.0f, 8, 2, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 16 * 4 + m_nUV * 2);
		//���n��
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.0f, 0.2f, SHOT_LIFE * 0.0f, 0.1f, 0.015f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 0.0f, 8, 2, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.0f, 0.2f, SHOT_LIFE * 0.0f, -0.1f, 0.015f,
			6.0f, 6.0f, D3DX_PI * 1.1f, 0.0f, 8, 2, CSceneBullet::CHANGE_NO, m_fAttack + 350, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		break;
	case CHARGE_300:
		if (SceneCreate(bulletNor, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			bulletNor->Set(m_shot, pos[0] + D3DXVECTOR3(sinf(m_rotU.y) * 3.0f, 0.0f, cosf(m_rotU.y) * 3.0f), m_move * 0.1f, D3DXVECTOR3(0.0f, m_rotU.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 16 * 3 + m_nUV * 2,
				SHOT_LIFE * 0.3f, 0, 0.01f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_FAST2, m_fAttack + 150, false, &m_bShotDelete);
			for (int nCount = 0; nCount < 8; nCount++)
			{
				if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * (0.25f * nCount), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 16 * 6 + m_nUV * 2,
						SHOT_LIFE * 0.3f, 0, 0.0f, 0.0f, D3DX_PI * -0.01f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 10.0f, 1.0f,
						bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
				}
				if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					pPairBullet2->Set(m_shot, bulletNor->GetPosition()[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * (0.25f * nCount) + D3DX_PI * 0.125f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6.0f, 6.0f, 16 * 6 + m_nUV * 2,
						SHOT_LIFE * 0.3f, 0, 0.0f, 0.0f, D3DX_PI * -0.01f, 0.97f, m_fAttack + 300.0f, m_rotU.y, 13.0f, 1.0f,
						bulletNor->GetPosition(), NULL, false, &m_bShotDelete);
				}
			}
		}
		for (int nCount = 0;nCount < 3;nCount++)
		{
			CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + nCount * (D3DX_PI * 0.1f), true, 0.0f, 0.2f, (float)nCount * 30.0f + 30.0f * 3, 0.1f, 0.015f,
				3.0f, 3.0f, D3DX_PI * 1.1f, 12.0f - (float)nCount * 2.0f, 16, 2, CSceneBullet::CHANGE_NO, m_fAttack + 450, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
			CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y - nCount * (D3DX_PI * 0.1f), true, 0.0f, 0.2f, (float)nCount * 30.0f, -0.1f, 0.015f,
				3.0f, 3.0f, D3DX_PI * 1.1f, 12.0f - (float)nCount * 2.0f, 16, 2, CSceneBullet::CHANGE_NO, m_fAttack + 450, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 36, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn06(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet = NULL;
	CScenePairBullet2	*pPairBullet2 = NULL;
	CScenePairBullet	*pPairBullet = NULL;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM10, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 8.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 400) * 2, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_DIFFUSION, pos[0], m_move, m_rotU.y, false, 0.012f, 0.97f, SHOT_LIFE - 15.0f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.51f, 5.0f, 4, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 150, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		break;
	case CHARGE_90:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM10, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 8.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 400) * 2, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, -1.0f, 0.2f, SHOT_LIFE * 0.0f, 0.0f, 0.015f,
			4.0f, 4.0f, D3DX_PI * 0.51f, 0.0f, 16, 2, CSceneBullet::CHANGE_NO, m_fAttack + 200, false, &m_bShotDelete, 48 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 8.0f, D3DX_PI * 0.45f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 200, false, &m_bShotDelete, 16 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y + D3DX_PI, false, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 8.0f, D3DX_PI * 0.45f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 200, false, &m_bShotDelete, 16 + m_nUV * 2);
		break;
	case CHARGE_180:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM10, pos[0], m_move, m_rotU.y, true, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			4.0f, 8.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 400) * 2, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_SETTING0, pos[0], m_move, m_rotU.y + D3DX_PI * 0.25f, true, 0.03f, 0.97f, SHOT_LIFE - 10.0f, 0.0f, 0.0f,
			3.5f, 3.5f, D3DX_PI * 1.1f, 5.0f, 4, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 200, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 6.0f, 16 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 600) / 2, m_rotU.y, 18.0f, 1.0f,
				pos, &m_rotU.y, true, &m_bShotDelete);
		}
		if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 6.0f, 16 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 600) / 2, m_rotU.y, 18.0f, 1.0f,
				pos, &m_rotU.y, true, &m_bShotDelete);
		}

		break;
	case CHARGE_300:
		for (int nCount = 0; nCount < 4; nCount++)
		{
			if (SceneCreate(pPairBullet2, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				pPairBullet2->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -(0.5f * nCount), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5.0f, 10.0f, 16 + m_nUV * 2,
					SHOT_LIFE * 0.75f, 0, 0.01f, 0.0f, D3DX_PI * -0.115f, 0.97f, (m_fAttack + 600) / 2, m_rotU.y, 18.0f, 1.0f,
					pos, &m_rotU.y, true, &m_bShotDelete);
			}
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 16 + m_nUV * 2,
				SHOT_LIFE - 180.0f, 0, 0.02f, 0.0f, D3DX_PI / 30, 0.97f, m_fAttack + 300, m_rotU.y, 0.0f, 0.1f, CSceneBullet::SET_NEEDLE, m_rotU.y - D3DX_PI * 0.5f, D3DX_PI / 30, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU - D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 16 + m_nUV * 2,
				SHOT_LIFE - 180.0f, 0, 0.02f, 0.0f, -D3DX_PI / 30, 0.97f, m_fAttack + 300, m_rotU.y, 0.0f, 0.1f, CSceneBullet::SET_NEEDLE, m_rotU.y + D3DX_PI * 0.5f, -D3DX_PI / 30, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn07(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet = NULL;
	CScenePairBullet2	*pPairBullet2 = NULL;
	CScenePairBullet	*pPairBullet = NULL;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.015f, 0.98f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			3.0f, 3.0f, D3DX_PI * 0.26f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 0.45f, 3.0f, 24, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 3 + m_nUV * 2);
		break;
	case CHARGE_90:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.45f, 3.0f, 24, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 3 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.98f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.45f, -10.0f, 24, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 500, false, &m_bShotDelete, 16 * 3 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.03f, 0.95f, SHOT_LIFE * 0.0f, 0.02f, 0.0f,
			5.0f, 5.0f, D3DX_PI * 1.1f, -10.0f, 4, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 500, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);

		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 3.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.03f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 3.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.03f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case CHARGE_180:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 200.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.02f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), m_move, m_rotU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.02f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.03f, 0.95f, SHOT_LIFE * 0.0f, 0.02f, 0.0f,
			6.0f, 6.0f, D3DX_PI * 1.1f, -10.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 400, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);

		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, (m_fAttack + 200) / 3, m_rotU.y + D3DX_PI, 3.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.03f, 1, 4,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 60.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, (m_fAttack + 200) / 3, m_rotU.y + D3DX_PI, 3.0f, 0.1f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * -0.03f, 1, 4,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case CHARGE_300:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 150.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.08f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 150.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.08f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 150.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, m_fAttack + 150, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * 0.08f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 150.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, (m_fAttack + 200) / 2, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.08f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}

		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 1.5f, 1.5f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.02f, 0.0f, D3DX_PI * 0.01f, 0.97f, (m_fAttack + 200) / 3, m_rotU.y, 3.0f, 1.0f, CSceneBullet::SET_SHOT2, m_rotU.y, D3DX_PI * 0.01f, 3, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
}
//=============================================================================
// �e���ˏ���
//=============================================================================
void CSceneTank::Shot_Ptn08(int nCharge, D3DXVECTOR3 *&pos)
{
	CScenePairBulletSet *pPairBulletSet = NULL;
	CScenePairBullet2	*pPairBullet2 = NULL;
	CScenePairBullet	*pPairBullet = NULL;

	switch (nCharge)
	{//�`���[�W�ʂɉ����Ēe���ω�
	case CHARGE_NO:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack * 0.1f, false, &m_bShotDelete, 16 * 8 + m_nUV * 2);
		break;
	case CHARGE_30:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 1.1f, 0.0f, 8, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 300, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);

		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 30.0f, 0, 0.03f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack / 4, m_rotU.y, 15.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.03f, 1, 2,
				pos, &m_rotU.y, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}	

		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 8, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_90:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.0f, 0.01f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 1.1f, 0.0f, 8, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 250, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.0f, -0.01f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 1.1f, 0.0f, 8, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 250, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);

		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 0.26f, 5.0f, 32, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 300) / 2, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 0.26f, -5.0f, 32, 0, CSceneBullet::CHANGE_FAST2, (m_fAttack + 300) / 2, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 12, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_180:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 0.5f, 5.0f, 64, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 150, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 0.5f, -5.0f, 64, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 150, false, &m_bShotDelete, 16 * 1 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.03f, 0.97f, m_fAttack + 200, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_RELEASE, m_rotU.y, D3DX_PI * 0.015f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack + 200, m_rotU.y, 10.0f, 0.1f, CSceneBullet::SET_RELEASE, m_rotU.y, D3DX_PI * -0.03f, 1, 3,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, -0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 16, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	case CHARGE_300:
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_BEAM00, pos[0], m_move, m_rotU.y, true, 0.03f, 0.95f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			5.0f, 10.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, m_fAttack + 800, false, &m_bShotDelete, 16 * 6 + m_nUV * 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * -0.66f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack + 250, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.03f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.66f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack + 150, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.03f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			pPairBulletSet->Set(m_shot, pos[0], m_move, m_rotU + D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 48 + m_nUV * 2,
				SHOT_LIFE - 120.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, m_fAttack + 150, m_rotU.y, 20.0f, 0.1f, CSceneBullet::SET_SHOT, m_rotU.y, D3DX_PI * -0.03f, 1, 2,
				pos, NULL, &m_bShotDelete);
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		CSceneBullet::ShotAttack(m_shot, CSceneBullet::ATK_PTN03, pos[0], m_move, m_rotU.y, false, 0.02f, 0.95f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			1.5f, 1.5f, D3DX_PI * 1.1f, 3.0f, 32, 0, CSceneBullet::CHANGE_FAST, m_fAttack + 150, false, &m_bShotDelete, 48 + m_nUV * 2);
		break;
	}
}

//=============================================================================
//	�_���[�W
//=============================================================================
bool CSceneTank::Damage(float fAtk)
{
	if (m_ObjType == OBJTYPE_PLAYER)
	{//���������̂��v���C���[
		if (((CScenePlayer*)this)->GetnInvincible() > 0)
		{//���G���ԂȂ�
			return false;
		}
	}

	CSound *pSound = CManager::GetSound();

	float fDef = m_fDefense * 0.65f;
	if (m_ObjType == CScene::OBJTYPE_PLAYER)
	{
		fDef *= ((CScenePlayer*)this)->GetDefUP() * PLUS_DEF + 1.0f;
		fDef += fAtk * ((CScenePlayer*)this)->GetDefUP() * (PLUS_DEF * 0.5f);
	}
	fAtk *= 1.5f;
	int nDamage = (int)((fAtk / (fAtk + fDef)) * fAtk);
	if (CManager::GetMode()[0] == CManager::MODE_VERSUS) { nDamage = (int)(nDamage * 1.5f); }

	if (nDamage < (int)(fAtk * 0.1f)) { nDamage = (int)(fAtk * 0.1f); }
	m_fLife -= (float)nDamage;

	if (m_ObjType == OBJTYPE_PLAYER)
	{
		if (m_fLife <= 1 && m_pEffect->GetDrawType() != CScene::DRAW_TYPE_NO)
		{//�v���C���[�Ńo���A��������
			m_pEffect->BindDrawType(CScene::DRAW_TYPE_NO);
			m_fLife = 1;
			((CScenePlayer*)this)->GetnInvincible() = 30;
			CSceneBullet::BreakBullet(true);
			CSceneAnimEffect	*pSceneE3D;

			if (SceneCreate(pSceneE3D, SAnim3D_PRIORITY))
			{//�����ł����Ȃ�@//�`���[�W�g
				pSceneE3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 25.0f, 25.0f, CSceneAnim3D::TEX_BREAK, CScene::DRAW_TYPE_SUBTRACT,
					0, 14, 1, 5, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
			}
		}

		CDungeon *pDungeon = CManager::GetDungeon();
		if (pDungeon != NULL)
		{
			pDungeon->SetDamageBG(GetpEfect()->GetDrawType(), GetfLife()[0] / GetfMaxLife(), true, ((CScenePlayer*)this)->GetPlayerID());
		}
	}

	if (m_fLife <= 0) 
	{
		m_fLife = 0.0f;
		m_bShotDelete = false;
		CSceneBullet::BreakBullet(false);
		m_bShotDelete = true;
		if (m_ObjType == OBJTYPE_PLAYER) 
		{ 
			CScenePlayer *pPlayer = (CScenePlayer*)this;
			pPlayer->GetnDeadCount() = 2;
			CDungeon *pDungeon = CManager::GetDungeon();
			if (pDungeon != NULL)
			{
				pDungeon->SetDamageBG(CScene::DRAW_TYPE_MAX, 1.0f, true, ((CScenePlayer*)this)->GetPlayerID());
			}
		}
		return true;
	}
	else 
	{ 
		CSceneAnim3D	*pScene3D;
		if (SceneCreate(pScene3D, SAnim3D_PRIORITY))
		{//�����ł����Ȃ�@//�Ή�
			pScene3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_HIT, CScene::DRAW_TYPE_OVERLAY,
				0, 5, 2, 8, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
		}
	}

	return false;
}
//=============================================================================
//	��
//=============================================================================
void CSceneTank::Heel(float fHeel, bool bEffect)
{
	CSceneAnimEffect *pSceneAnim3DE;
	//GetColor()[0].a = 1.0f;
	if (m_ObjType == OBJTYPE_PLAYER)
	{//�v���C���[�Ȃ琶���Ԃ蔻��
		CScenePlayer *pPlayer = (CScenePlayer*)this;
		if (pPlayer->GetDrawType()[0] == CScene::DRAW_TYPE_NO)
		{//����ł���Ȃ�
			m_fLife = m_fMaxLife * 0.5f;
			pPlayer->DeadPlayer(false);
			return;
		}
	}

	if (m_pEffect->GetDrawType() != CScene::DRAW_TYPE_NO)
	{//�񕜉\
		m_fLife += m_fMaxLife * fHeel;
		if (m_fLife > m_fMaxLife) { m_fLife = m_fMaxLife; }
		if (bEffect)
		{//�G�t�F�N�g������Ȃ�
			if (SceneCreate(pSceneAnim3DE, S3DF_PRIORITY))
			{//�����ł����Ȃ�@//��
				pSceneAnim3DE->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_HEEL, CScene::DRAW_TYPE_ADD,
					0, 10, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
			}
		}
	}
	else
	{//�o���A����
		m_pEffect->BindDrawType(CScene::DRAW_TYPE_ADD);
		m_fLife = 2;
		m_fLife += (m_fMaxLife * fHeel) / 4;
		if (m_fLife > m_fMaxLife) { m_fLife = m_fMaxLife; }
		if (bEffect)
		{//�G�t�F�N�g������Ȃ�
			if (SceneCreate(pSceneAnim3DE, S3DF_PRIORITY))
			{//�����ł����Ȃ�@//�o���A����
				pSceneAnim3DE->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_SHIELD, CScene::DRAW_TYPE_ADD,
					0, 4, 4, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
			}
		}
	}
}
//=============================================================================
// �ُ��ԉ�
//=============================================================================
void	CSceneTank::Heal(void)
{
	m_nFire = 0;
	m_nLightning = 0;
	m_nIce = 0;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CScenePlayer::Init(void)
{
	CSceneAnim3D::Load(CSceneAnim3D::TEX_CHARGE);
	CSceneAnim3D::Load(CSceneAnim3D::TEX_CHARGE2);
	CSceneAnim3D::Load(CSceneAnim3D::TEX_CHARGE3);
	CScene3D::Load(CScene3D::TEX_CHARGE);

	CSceneTank::Init();

	CManager::GetPlayer(m_nPlayerID) = this;
	CScene::SetObjType(OBJTYPE_PLAYER);
	m_fExp = 0;
	m_fMaxExp = powf(powf(GetnLevel() - 1.0f, 2) + 10, 2);
	m_nBombTime = BOMB_WAIT_TIME;
	m_nDeadCount = 0;
	m_nInvincible = 0;

	bool	bDirection = true;
	switch (m_nPlayerID)
	{
	case 0: bDirection = true; 
		GetShot()[0] = CSceneBullet::SHOT_PLAYER1;
		break;
	case 1: bDirection = false;
		GetShot()[0] = CSceneBullet::SHOT_PLAYER2;
		break;

	}
	if (m_pIcon == NULL)
	{//�A�C�R���̐���
		Create(m_pIcon); if (m_pIcon != NULL)
		{
			m_pIcon->Set(D3DXVECTOR3((bDirection ? 35.0f : SCREEN_WIDTH - 35.0f), 35.0f, 0.0f), 30.0f, 30.0f, D3DX_PI, (bDirection ? 0 : 1), 2, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_PIcon);
		}
	}
	if (m_pItem == NULL)
	{//�A�C�e���g�̐���
		Create(m_pItem); if (m_pItem != NULL)
		{
			m_pItem->Set(D3DXVECTOR3((bDirection ? 350.0f : SCREEN_WIDTH - 350.0f), 35, 0.0f), 30.0f, 30.0f, D3DX_PI, (bDirection ? 0 : 1), 2, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), C2D::TEXTURE_MAX);
			m_pItem->BindTexture(CScene3D::Load(CScene3D::TEX_ITEM));
		}
	}
	int nData = 1, nUVX = 1, nUVY = 1;	//�ꎞ�I�ȕۑ��̂���
	C2D::TEXTURE tex = C2D::TEXTURE_MAX;
	D3DXVECTOR3	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fLengthX = 0.0f, fLengthY = 0.0f;
	for (int nCount = 0; nCount < MAX_UI; nCount++)
	{
		if (m_pUI[nCount] == NULL)
		{ //UI�̃Z�b�g
			Create(m_pUI[nCount]); if (m_pUI[nCount] != NULL)
			{
				switch (nCount)
				{
				case 0: fLengthX = 45.0f; fLengthY = 20.0f; nData = 0; nUVX = 1; nUVY = 2; tex = C2D::TEX_UI000; pos = D3DXVECTOR3((bDirection ? 350.0f - 270.5f : SCREEN_WIDTH - 245.0f + 165.5f), 50.0f, 0.0f); break;
				case 1: fLengthX = 30.0f; fLengthY = 20.0f; nData = 1; nUVX = 1; nUVY = 2; tex = C2D::TEX_UI000; pos = D3DXVECTOR3((bDirection ? 350.0f - 180.5f : SCREEN_WIDTH - 245.0f + 75.0f), 50.0f, 0.0f); break;
				case 2: fLengthX = 20.0f; fLengthY = 20.0f; nData = 0; nUVX = 3; nUVY = 1; tex = C2D::TEX_UI001; pos = D3DXVECTOR3((bDirection ? 350.0f + 60.5f : SCREEN_WIDTH - 245.0f - 165.5f), 25.0f, 0.0f); break;
				case 3: fLengthX = 20.0f; fLengthY = 20.0f; nData = 1; nUVX = 3; nUVY = 1; tex = C2D::TEX_UI001; pos = D3DXVECTOR3((bDirection ? 350.0f + 110.5f : SCREEN_WIDTH - 245.0f - 215.5f), 25.0f, 0.0f); break;
				case 4: fLengthX = 20.0f; fLengthY = 20.0f; nData = 2; nUVX = 3; nUVY = 1; tex = C2D::TEX_UI001; pos = D3DXVECTOR3((bDirection ? 350.0f + 160.5f : SCREEN_WIDTH - 245.0f - 265.5f), 25.0f, 0.0f); break;
				}
				m_pUI[nCount]->Set(pos, fLengthX, fLengthY, D3DX_PI, nData, nUVX, nUVY, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), tex);
			}
		}
		if (m_pNumber[nCount] == NULL)
		{ //�����̃Z�b�g
			Create(m_pNumber[nCount]); if (m_pNumber[nCount] != NULL)
			{
				switch (nCount)
				{
				case 0: nData = 3; pos = D3DXVECTOR3((bDirection ? 350.0f - 215.5f : SCREEN_WIDTH - 245.0f + 140.5f), 50.0f, 0.0f); break;
				case 1: nData = 8; pos = D3DXVECTOR3((bDirection ? 350.0f - 42.5f : SCREEN_WIDTH - 245.0f + 42.5f), 50.0f, 0.0f); break;
				case 2: nData = 3; pos = D3DXVECTOR3((bDirection ? 350.0f + 75.5f : SCREEN_WIDTH - 245.0f - 150.5f), 50.0f, 0.0f); break;
				case 3: nData = 3; pos = D3DXVECTOR3((bDirection ? 350.0f + 125.5f : SCREEN_WIDTH - 245.0f - 200.5f), 50.0f, 0.0f); break;
				case 4: nData = 3; pos = D3DXVECTOR3((bDirection ? 350.0f + 175.5f : SCREEN_WIDTH - 245.0f - 250.5f), 50.0f, 0.0f); break;
				}
				m_pNumber[nCount]->Set(pos, 7.5f, 15.0f, 0, nData, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_SCORE);
			}
		}
	}
	m_pNumber[0]->SetNumber(1);
	
	if (m_pLifeGage == NULL)
	{//HP�Q�[�W�̏�����
		Create(m_pLifeGage); if (m_pLifeGage != NULL)
		{
			m_pLifeGage->Set(D3DXVECTOR3((bDirection ? 70.0f : SCREEN_WIDTH - 70.0f), 17.5f, 0.0f), 240.0f, 12.5f, GetfLife(), &GetfMaxLife(), bDirection, C2DGage::STATE_LIFE);
		}
	}
	if (m_pExpGage == NULL)
	{//EXP�Q�[�W�̏�����
		Create(m_pExpGage); if (m_pExpGage != NULL)
		{
			m_pExpGage->Set(D3DXVECTOR3((bDirection ? 70.0f : SCREEN_WIDTH - 70.0f), 32.5f, 0.0f), 240.0f, 2.5f, &m_fExp, &m_fMaxExp, bDirection, C2DGage::STATE_EXP);
		}
	}

	if (m_pHeart == NULL)
	{//�j�̐���
		if (SceneCreate(m_pHeart, S3D_PRIORITY + 3))
		{
			m_pHeart->Set(GetPosition()[0], GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.25f, 1.25f, CScene3D::TEX_HEART, m_nPlayerID, 2, 1, CScene::DRAW_TYPE_ZNORMAL);
		}
	}
	if (m_pBomb == NULL)
	{//���@�w�̐���
		if (SceneCreate(m_pBomb, MODEL_PRIORITY + 1))
		{
			m_pBomb->Set(GetPosition()[0], GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8.0f, 8.0f, CScene3D::TEX_BOMB000 , m_nPlayerID * 2, 2, 2, CScene::DRAW_TYPE_ADD);
		}
	}
	m_pItemType = NULL;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CScenePlayer::Uninit(void)
{
	m_nNumPlayer--;
	CManager::GetPlayer(m_nPlayerID) = NULL;

	for (int nCount = 0; nCount < MAX_UI; nCount++)
	{//UI�̔j��
		if (m_pUI[nCount] != NULL) { m_pUI[nCount]->Uninit(); }
		if (m_pNumber[nCount] != NULL) { m_pNumber[nCount]->Uninit(); }
	}
	if (m_pIcon != NULL) { m_pIcon->Uninit(); }
	if (m_pItem != NULL) { m_pItem->Uninit(); }
	if (m_pLifeGage != NULL) { m_pLifeGage->Uninit(); }
	if (m_pExpGage != NULL) { m_pExpGage->Uninit(); }

	if (m_pHeart != NULL)
	{//�j�̏I��
		m_pHeart->Uninit();
	}
	if (m_pBomb != NULL)
	{//���@�w�̏I��
		m_pBomb->Uninit();
	}
	//�{�̂̔j��
	CSceneTank::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CScenePlayer::Update(void)
{
	if (PlayPlayer())
	{//�����Ă������ǂ���
		if (GetfLife()[0] > 0.0f)
		{//�������Ă���
			if (m_bCamera)
			{//�J�����̌���������Ȃ�
				CInputKeyboard	*pInputKey = CManager::GetInputKey();			//�L�[�{�[�h���l��
				CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(m_nID);	//�W���C�p�b�h���l��
				CSceneAnimEffect	*pSceneAnim3D;			//�G�t�F�N�g�p
				CSound *pSound = CManager::GetSound();		//�T�E���h�̃|�C���^���擾

				float	fMoveX = 0.0f, fMoveZ = 0.0f;	//�ړ������v�Z�p
				bool	bMove = false;
				bool	bRiver = true;

				//�ړ�����
				if (pInputKey->GetPress(DIK_UP)) { fMoveZ = 1.0f; }
				if (pInputKey->GetPress(DIK_DOWN)) { fMoveZ = -1.0f; }
				if (pInputKey->GetPress(DIK_LEFT)) { fMoveX = -1.0f; }
				if (pInputKey->GetPress(DIK_RIGHT)) { fMoveX = 1.0f; }
				//if (pInputKey->GetPress(DIK_V)) { CSceneBullet::BreakBullet(false); }

				if (fMoveX != 0.0f || fMoveZ != 0.0f)
				{//�����Ă���Ȃ�
					bMove = true;
					GetfMoveAngle()[0] = atan2f(fMoveX, fMoveZ);	//�ړ������v�Z
					GetRotationU()[0].y = GetRotation()[0].y;
				}

				if (pInputPad->GetStickDefeat(LEFT_STICK))
				{//�W���C�R����L�X�e�B�b�N���|����Ă���Ȃ�
					bMove = true;
					GetfMoveAngle()[0] = pInputPad->GetfStickAngle(LEFT_STICK);	//�ړ������v�Z
																				//�C���̍X�V
					if (pInputPad->GetStickDefeat(RIGHT_STICK))
					{//�W���C�R����R�X�e�B�b�N���|����Ă���Ȃ�
						GetRotationU()[0].y = pInputPad->GetfStickAngle(RIGHT_STICK);	//�C���̕������
					}//�ړ������ɑ��
					else { GetRotationU()[0].y = pInputPad->GetfStickAngle(LEFT_STICK); }
				}
				else if (pInputPad->GetPress(INPUT_UP) || pInputPad->GetPress(INPUT_DOWN) || pInputPad->GetPress(INPUT_LEFT) || pInputPad->GetPress(INPUT_RIGHT))
				{
					bMove = true;
					if (pInputPad->GetPress(INPUT_UP)) { fMoveZ = 1.0f; }
					if (pInputPad->GetPress(INPUT_DOWN)) { fMoveZ = -1.0f; }
					if (pInputPad->GetPress(INPUT_LEFT)) { fMoveX = -1.0f; }
					if (pInputPad->GetPress(INPUT_RIGHT)) { fMoveX = 1.0f; }
					GetfMoveAngle()[0] = atan2f(fMoveX, fMoveZ);	//�ړ������v�Z
					if (pInputPad->GetStickDefeat(RIGHT_STICK))
					{//�W���C�R����R�X�e�B�b�N���|����Ă���Ȃ�
						GetRotationU()[0].y = pInputPad->GetfStickAngle(RIGHT_STICK);	//�C���̕������
					}//�ړ������ɑ��
					else { GetRotationU()[0].y = GetfMoveAngle()[0]; }

				}
				else
				{//�ړ�����
					if (pInputPad->GetStickDefeat(RIGHT_STICK))
					{//�W���C�R����R�X�e�B�b�N���|����Ă���Ȃ�
						GetRotationU()[0].y = pInputPad->GetfStickAngle(RIGHT_STICK);	//�C���̕������
					}
				}
				//�J������Y���␳
				CCamera::camera.m_posV.y += (CAMERA_Y - CCamera::camera.m_posV.y) * 0.1f;

				//��Ԗ{�̂̍X�V
				CSceneTank::Update(bMove,
					(pInputPad->GetPress(INPUT_R1) ? true : pInputKey->GetPress(DIK_Z)),
					(pInputPad->GetRelease(INPUT_R1) ? true : pInputKey->GetRelease(DIK_Z)),
					(pInputPad->GetTrigger(INPUT_R2) ? true : pInputKey->GetTrigger(DIK_X)),
					(pInputPad->GetPress(INPUT_L1) ? true : pInputKey->GetPress(DIK_LSHIFT)),
					(pInputPad->GetPress(INPUT_L2) ? true : (pInputPad->GetPress(INPUT_X) ? true : pInputKey->GetPress(DIK_LCONTROL))),
					m_pItemType);

				if (m_pBomb != NULL)
				{//�{��(���@�w)�̍X�V
					if (m_nBombTime <= BOMB_WAIT_TIME)
					{//�{���N���O
						if (m_nBombTime < BOMB_WAIT_TIME - 1)
						{//������
							if (m_pBomb->GetColor()[0].a == 0.0f)
							{
								m_pBomb->SetUV(m_nPlayerID * 2, 2, 2);
								m_pBomb->SetSize(8.0f, 8.0f);
								m_nBombTime = 1;
							}
							if (m_nBombTime > 0)
							{
								m_nBombTime++;
								m_pBomb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, (1.0f - (BOMB_WAIT_TIME - m_nBombTime) / BOMB_WAIT_TIME) * 0.3f));
							}
						}
						else if (m_nBombTime == BOMB_WAIT_TIME - 1)
						{//�N���������ł���
							//m_pBomb->GetState()[0] = CScene3D::STATE_FADEIN;
							m_pBomb->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
							m_nBombTime = BOMB_WAIT_TIME;
							if (SceneCreate(pSceneAnim3D, S3DF_PRIORITY))
							{//�����ł����Ȃ�@//�`���[�W��
								pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20.0f, 20.0f, CSceneAnim3D::TEX_CHARGE3, CScene::DRAW_TYPE_ADD,
									0, 10, 1, 2, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, GetPosition(), GetThisScene());
							}
						}
						else
						{//�N���҂�
							if (pInputKey->GetPress(DIK_C) || pInputPad->GetTrigger(INPUT_A))
							{//�N��
								m_pBomb->SetUV(m_nPlayerID * 2 + 1, 2, 2);
								m_nBombTime = BOMB_WAIT_TIME + 1;
							}
						}//else(�N���҂�)
					}//if(�N���O)
					if (m_nBombTime > BOMB_WAIT_TIME)
					{//�{���N����
						m_nBombTime++;
						if (m_nBombTime < BOMB_TIME)
						{//���ԓ��e�폜�@�\
							m_pBomb->SetSize(m_pBomb->GetfLengthX()[0] * (((BOMB_TIME - m_nBombTime) * 0.001f) + 1), m_pBomb->GetfLengthZ()[0] * (((BOMB_TIME - m_nBombTime) * 0.001f) + 1));
						}
						else
						{//���Ԑ؂�@������
							m_nBombTime = 0;
							m_pBomb->GetState()[0] = CScene3D::STATE_FADEOUT2;
						}
					}
				}//if(�{��!=NULL)
			}//if(�J�����ǔ�)
			else
			{ //�t�F�[�h�ڍs��
				CSceneBullet::BreakBullet(true);
				GetMove()[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				GetRotation()[0].y += D3DX_PI * 0.2f;
			}
			CDungeon *pDungeon = CManager::GetDungeon();
			if (pDungeon != NULL)
			{//�����̍X�V
				pDungeon->SetDamageBG(GetpEfect()->GetDrawType(), GetfLife()[0] / GetfMaxLife(), false, m_nPlayerID);
			}
		}//if(����)
		else
		{
			if (m_nDeadCount > 0)
			{
				m_nDeadCount--;
				if (m_nDeadCount == 0)
				{
					DeadPlayer(true);
				}
			}
		}
	}//if(�����Ă������ǂ���)

	//���̑��̍X�V
	PEffectUpdate();
}
//=============================================================================
// �v���C���[�������Ă������ǂ�����Ԃ�����
//=============================================================================
bool	CScenePlayer::PlayPlayer(void)
{
	CManager::MODE mode = CManager::GetMode()[0];

	if (mode == CManager::MODE_VERSUS && CManager::GetVersus() != NULL)
	{//�o�[�T�X���[�h
		if (CManager::GetVersus()->GetState() == CVersus::STATE_START) { return false; }
	}

	return true;
}
//=============================================================================
// �V�[���h�̍X�V����
//=============================================================================
void	CScenePlayer::Shield(void)
{
	if (m_nBombTime > BOMB_WAIT_TIME)
	{//�{���N����
		if (m_nBombTime < BOMB_TIME)
		{//���ԓ��e�폜�@�\
			if (CManager::GetMode()[0] == CManager::MODE_GAME) { CSceneBullet::CircleBreak(m_pBomb->GetPosition()[0], m_pBomb->GetfLengthX()[0], CSceneBullet::SHOT_PLAYER1, CSceneBullet::SHOT_PLAYER2); }
			else { CSceneBullet::CircleBreak(m_pBomb->GetPosition()[0], m_pBomb->GetfLengthX()[0], GetShot()[0], GetShot()[0]); }
		}
	}
}
//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void	CScenePlayer::PEffectUpdate(void)
{
	if (m_nInvincible > 0) { m_nInvincible--; }		//���G���ԍX�V
	if (m_pLifeGage != NULL) { m_pLifeGage->Update(); }	//���C�t�Q�[�W�̍X�V
	if (m_pExpGage != NULL) { m_pExpGage->Update(); }	//EXP�Q�[�W�̍X�V

	if (m_pHeart != NULL)
	{//�j�̍X�V
		m_pHeart->GetPosition()[0] = GetPosition()[0];
		m_pHeart->GetRotation()[0].y += D3DX_PI * 0.01f;
	}
	if (m_pBomb != NULL)
	{//���@�w�̍X�V
		if (m_nBombTime <= BOMB_WAIT_TIME && m_nBombTime > 0) { m_pBomb->GetPosition()[0] = GetPosition()[0] + D3DXVECTOR3(0.0f, -0.0f, 0.0f); }
		m_pBomb->GetRotation()[0].y += D3DX_PI * 0.02f;
	}
}
//=============================================================================
// ���Sor�s�������菈��
//=============================================================================
void	CScenePlayer::DeadPlayer(bool bDead)
{
	if (bDead)
	{//����
		GetDrawType()[0] = CScene::DRAW_TYPE_NO;
		m_pBomb->GetDrawType() = CScene::DRAW_TYPE_NO;
		m_pHeart->GetDrawType() = CScene::DRAW_TYPE_NO;
		GetpEfect()->GetDrawType() = CScene::DRAW_TYPE_NO;
		GetpEffectU()->GetDrawType() = CScene::DRAW_TYPE_NO;
	}
	else
	{//�����Ԃ���
		GetDrawType()[0] = CScene::DRAW_TYPE_NORMAL;
		m_pBomb->GetDrawType() = CScene::DRAW_TYPE_ADD;
		m_pHeart->GetDrawType() = CScene::DRAW_TYPE_ZNORMAL;
		GetpEfect()->GetDrawType() = CScene::DRAW_TYPE_ADD;
		GetpEffectU()->GetDrawType() = CScene::DRAW_TYPE_ADD;
	}
}
//=============================================================================
// �`�揈�� UI��
//=============================================================================
void CScenePlayer::DrawUI(void)
{
	for (int nCount = 0; nCount < MAX_UI; nCount++)
	{//UI�̕\��
		m_pUI[nCount]->Draw();
		m_pNumber[nCount]->Draw();
	}
	m_pItem->Draw();
	m_pIcon->Draw();
	m_pLifeGage->Draw(); 
	m_pExpGage->Draw();
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CScenePlayer::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType)
{//�����o�ϐ��ɑ��
	CSceneTank::Set(pos, rot, col, modelD, modelU, TypeD, TypeU, DrawType);
}
//=============================================================================
// �X�e�[�^�X���Z����
//=============================================================================
void	CScenePlayer::PlusLevel(int nLevel)
{
	float fLife = GetfLife()[0];
	float fMaxLife = GetfMaxLife();

	GetnLevel() += nLevel;	//���x���㏸
	GetStatus();		//���̃��x���ŃX�e�[�^�X�v�Z
	GetfMaxLife()	+= m_pNumber[2]->GetnNumber() * PLUS_LIFE;
	GetfLife()[0] = fLife;

	if (nLevel > 0)
	{//���x�����オ����
		GetfLife()[0] += GetfMaxLife() - fMaxLife;
		for (int nCount = 0; nCount < nLevel; nCount++) { Heel(0.5f, false); }

		m_fMaxExp = powf(powf(GetnLevel() - 1.0f, 2) + 10, 2);
		m_pNumber[0]->AddNumber(nLevel);
	}
}
//=============================================================================
// �A�C�e���Z�b�g����
//=============================================================================
void	CScenePlayer::SetItem(ITEM::TYPE Item)
{
	CScenePairBulletSet *pPairBulletSet;
	CScenePairBullet	*pPairBullet;

	if (m_pItemType != NULL)
	{//�A�C�e���̍폜
		if (m_pItemType->GetType() == ITEM::TYPE_PAIR0 || m_pItemType->GetType() == ITEM::TYPE_PAIR1)
		{//�e�ǉ��A�C�e���Ȃ�e�̍폜
			((ITEM_PAIR*)m_pItemType)->GetShotDelete() = false;
			CSceneBullet::BreakBullet(false);
		}
		delete m_pItemType;
		m_pItemType = NULL;
	}

	if (m_pItemType == NULL)
	{//�A�C�e���̐���
		switch (Item)
		{
		case ITEM::TYPE_SPDUP: 
		case ITEM::TYPE_NORIVER:
		case ITEM::TYPE_NOSTOP:
		case ITEM::TYPE_CHARGEUP:
		case ITEM::TYPE_SCOREUP:
			m_pItemType = new ITEM;
			break;
		case ITEM::TYPE_PAIR0:
		case ITEM::TYPE_PAIR1:
			m_pItemType = new ITEM_PAIR;
			break;
		}
	}

	if (m_pItemType != NULL)
	{//���������ʓK�p
		m_pItemType->GetType() = Item;

		switch (Item)
		{
		case ITEM::TYPE_PAIR0:
			for (int nCount = 0; nCount < 2; nCount++)
			{
				if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�0
					pPairBulletSet->Set(GetShot()[0], GetPosition()[0], GetMove()[0], GetRotationU()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + GetnUV() * 2,
						-99.9f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f + (D3DX_PI * 0.04f) * nCount, 0.97f, GetfAtk() + 100, GetRotationU()[0].y, 12.0f, 1.0f, CSceneBullet::SET_SHOT, GetRotationU()[0].y, D3DX_PI * -0.02f + (D3DX_PI * 0.04f) * nCount, 1, 25,
						GetPosition(), &GetRotationU()[0].y, &((ITEM_PAIR*)m_pItemType)->GetShotDelete());
					pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET3);
				}
			}
			break;
		case ITEM::TYPE_PAIR1:
			for (int nCount = 0; nCount < 3; nCount++)
			{
				if (SceneCreate(pPairBullet, BULLET_PRIORITY))
				{//�����ł����Ȃ�//�q�@
					pPairBullet->Set(GetShot()[0], GetPosition()[0], GetMove()[0], GetRotationU()[0] - D3DXVECTOR3(0.0f, D3DX_PI * 0.333f * nCount, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 48 + +GetnUV() * 2,
						-99.9f, 0, 0.1f, 0.0f, D3DX_PI * 0.0f, 0.99f, GetfAtk() + 100, 2.0f, 1.0f, 0.25f, 0.25f, CSceneBullet::SET_SHOT, GetRotationU()[0].y, D3DX_PI * 0.05f, 1, 20,
						GetPosition(), &GetRotationU()[0].y, &((ITEM_PAIR*)m_pItemType)->GetShotDelete());
					pPairBullet->SetObjType(CScene::OBJTYPE_BULLET3);
				}
			}
			break;
		}
	}

	if (m_pIcon != NULL)
	{
		m_pItem->SetUV((int)m_pItemType->GetType() + 13, 5, 4);
		m_pItem->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
//=============================================================================
// �o���l�l������
//=============================================================================
void	CScenePlayer::AddExp(int nExp)
{
	int nLevelUp;
	int nPlusLevel = 0;
	m_fExp += nExp;

	while (1)
	{//���x���A�b�v���I������܂�
		nLevelUp = (int)powf(powf(GetnLevel() + nPlusLevel - 1.0f, 2) + 10, 2);
		if ((int)m_fExp >= nLevelUp)
		{//�o���l������Ă���Ȃ�
			m_fExp -= (float)nLevelUp;
			nPlusLevel++;
		}
		else { break; }
	}

	if (nPlusLevel > 0) 
	{//���x���A�b�v�����Ȃ�
		PlusLevel(nPlusLevel);
		//�G�t�F�N�g�Ɖ�
		CSceneAnim3D *pSceneAnim3D;
		if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
		{
			pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 25.0f, 25.0f, CSceneAnim3D::TEX_WEAPON, CScene::DRAW_TYPE_SUBTRACT, 0, 5, 2, 6, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_FADE);
		}
	}
}
