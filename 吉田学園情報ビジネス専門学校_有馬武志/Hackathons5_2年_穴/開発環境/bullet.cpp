//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "motion.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//==================================================================================================//
//    * �e�̍U������ �m�F�֐� *
//==================================================================================================//
void CBullet::AtkCheck(void)
{
	CScene *pSceneAtk;
	CScene *pSceneDef;

	pSceneAtk = CScene::GetTop(BULLET_PRIORYITY);
	while (pSceneAtk != NULL)
	{//�I���܂�
		if (pSceneAtk->GetObjType() == OBJTYPE_BULLET)
		{//�L��������
			CCharacter *pAtk = ((CBullet*)pSceneAtk)->m_pChar;
			pSceneDef = CScene::GetTop(CHAR_PRIORITY);
			while (pSceneDef != NULL)
			{//�I���܂�
				if (pSceneAtk != pSceneDef)
				{//�����L�����o�Ȃ�
					if (pSceneDef->GetObjType() == OBJTYPE_PLAYER || pSceneDef->GetObjType() == OBJTYPE_ENEMY)
					{//�L��������
						//HitCheck(pSceneAtk, pSceneDef);	//���݂��Ƀq�b�g�`�F�b�N
					}
				}
				pSceneDef = pSceneDef->GetpNext();
			}//����
		}//if(�L����)
		pSceneAtk = pSceneAtk->GetpNext();
	}//while(NULL)
}
//==================================================================================================//
//    * �e�̃Z�b�g�֐� *
//==================================================================================================//
void CBullet::Set(CCharacter *pChar, CScene *pScene, D3DXMATRIX *pMtx, int nLife, float fAtkplus, float fRange)
{
	m_pChar = pChar;
	m_pScene = pScene;
	m_pMtx = pMtx;
	m_nLife = nLife;
	m_fRange = fRange;
	m_fAtkplus = fAtkplus;
}
//=============================================================================
// �e�̏���������
//=============================================================================
HRESULT	CBullet::Init(void)
{
	m_pChar = NULL;
	m_pScene = NULL;
	m_pMtx = NULL;
	m_nLife = 0;
	m_fRange = 0.0f;
	m_fAtkplus = 0.0f;

	return S_OK;
}
//=============================================================================
// �e�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	m_nLife--;
	if (m_nLife < 0) 
	{ 
		m_pScene->Uninit();
		Uninit();
	}
}

