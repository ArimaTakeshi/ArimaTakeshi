//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "Effect.h"
#include "Scene3D.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �ݒ菈��
//=============================================================================
void	CLineEffect::Set(D3DXMATRIX &mtxWorld, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fInterval, bool &bDelete, TYPE type)
{
	m_pmtxWorld = &mtxWorld;
	m_pos = pos;
	m_rot = rot;
	m_fInterval = fInterval;
	m_bDelete = &bDelete;
	m_Type = type;
	SetEffect();
	m_posold = SetMtxWorld();
	SetObjType(CScene::OBJTYPE_LINE);
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLineEffect::Init(void)
{
	m_fInterval = 1.0f;
	m_fLength = 0.0f;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CLineEffect::Update(void)
{
	MoveSet(SetMtxWorld());
}
//=============================================================================
// �ړ��ʂɂ���ăZ�b�g����
//=============================================================================
void CLineEffect::MoveSet(D3DXVECTOR3 &pos)
{
	D3DXVECTOR3 posold = m_posold;
	float fLengthX, fLengthZ, fLengthY;
	int	  nCount;

	fLengthX = pos.x - m_posold.x; fLengthX *= fLengthX;
	fLengthY = pos.y - m_posold.y; fLengthY *= fLengthY;
	fLengthZ = pos.z - m_posold.z; fLengthZ *= fLengthZ;

	m_fLength += sqrtf(fLengthX + fLengthY + fLengthZ);	//Move�ʌv�Z
	nCount = (int)(m_fLength / m_fInterval);
	m_fLength = (float)((int)(m_fLength * 100.0f) % (int)(m_fInterval * 100.0f)) * 0.01f;
	for (int nCnt = 0; nCnt < nCount; nCnt++)
	{//��������������葱����
		m_posold += D3DXVECTOR3(pos.x - posold.x, pos.y - posold.y, pos.z - posold.z) / (float)nCount;
		SetEffect();
	}
}
//=============================================================================
// �^�C�v���Ƃ̃G�t�F�N�g�Z�b�g����
//=============================================================================
void CLineEffect::SetEffect()
{
	CSceneAnim3D *p3D;
	D3DXVECTOR3 fWKangle;
	D3DXVECTOR3 WKpos = m_posold - D3DXVECTOR3(m_pmtxWorld->_41, m_pmtxWorld->_42, m_pmtxWorld->_43);
	fWKangle.y = atan2f(WKpos.x, WKpos.z);
	fWKangle.x = atan2f(powf(WKpos.y, 2), powf(WKpos.x, 2) + powf(WKpos.z, 2)) * 0.85f;
	fWKangle.z = 0.0f;
	if (SceneCreate(p3D, S3D_PRIORITY))
	{
		p3D->Set(m_posold, fWKangle, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f),
			D3DXVECTOR3(75.0f, 75.0f, 0.0f), CScene::TEX_Fire, false, CScene::DRAW_TYPE_NORMAL, 0, 10, 1, 4, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
		p3D->BindDrawType(CScene::DRAW_TYPE_MULTIPLY);
	}
}
//=============================================================================
// �J�n���^�C�v���Ƃ̃G�t�F�N�g�Z�b�g����
//=============================================================================
void CLineEffect::StartEffect(void)
{

}
//=============================================================================
// �I�����^�C�v���Ƃ̃G�t�F�N�g�Z�b�g����
//=============================================================================
void CLineEffect::EndEffect(void)
{

}
//=============================================================================
// �ʒu�v�Z����
//=============================================================================
D3DXVECTOR3 CLineEffect::SetMtxWorld(void)
{
	D3DXMATRIX			mtxRot, mtxTrans, mtxWK;		//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWK);
	mtxWK = m_pmtxWorld[0];

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxRot, &mtxRot, &mtxWK);
	mtxWK = mtxRot;

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxTrans, &mtxTrans, &mtxWK);
	mtxWK = mtxTrans;

	return D3DXVECTOR3(mtxWK._41, mtxWK._42, mtxWK._43);
}
//=============================================================================
//�폜�m�F�Ɣj��
//=============================================================================
void	CLineEffect::Delete(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(SLEffect_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_LINE)
		{//���b�V������
			if (((CLineEffect*)pScene)->m_bDelete[0])
			{//�I���Ȃ�j��
				((CLineEffect*)pScene)->Uninit();
			}
		}
		pScene = pScene->GetpNext();
	}
}