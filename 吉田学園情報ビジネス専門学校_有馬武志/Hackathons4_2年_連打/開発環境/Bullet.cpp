//=============================================================================
//
// 2D�Q�[�W���� [2DGage.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "2DGage.h"
#include "Bullet.h"
#include "enemy.h"
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
//    * �Q�[�W�̃Z�b�g�֐� *
//==================================================================================================//
void	CBullet::Set(float fLane, int nType, int nState)
{
	float fLengthX;
	float fLengthY;
	D3DXCOLOR col;

	m_nType = nType;
	m_nState = nState;
	m_fMoveY = -10.0f;
	switch (nType)
	{
	case 0: fLengthX = 25.0f; fLengthY = 5.0f; m_fMove = 20.0f; col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); break;
	case 1: fLengthX = 25.0f; fLengthY = 5.0f; m_fMove = 25.0f; col = D3DXCOLOR(0.55f, 1.0f, 0.0f, 1.0f); break;
	case 2: fLengthX = 25.0f; fLengthY = 5.0f; m_fMove = 30.0f; col = D3DXCOLOR(0.98f, 1.0f, 0.0f, 1.0f); break;
	case 3: fLengthX = 25.0f; fLengthY = 5.0f; m_fMove = 15.0f; col = D3DXCOLOR(0.0f, 0.55f, 1.0f, 1.0f); break;
	case 4: fLengthX = 25.0f; fLengthY = 25.0f; m_fMove = 13.5f; col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); break;

	}
	CScene2D::Set(D3DXVECTOR3(100.0f, SCREEN_HEIGHT / 6 * fLane, 0.0f), fLengthX, fLengthY, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, col, CScene2D::TEX_Bullet999);

	if (nState != 0) 
	{ 
		SetObjType(CScene::OBJTYPE_NONE);
		BindTexture(CScene2D::Load(CScene2D::TEX_Bomb999));
	}

}
//=============================================================================
// �Q�[�W�̏���������
//=============================================================================
HRESULT  CBullet::Init(void)
{
	m_nType = 0;
	m_fLife = 1.0f;
	CScene2D::Init();
	return S_OK;
}

//=============================================================================
// �Q�[�W�̍X�V����
//=============================================================================
void CBullet::Update(void)
{
	float fPosX = GetPosition()[0].x;
	m_fLife -= 0.025f;
	if (m_nState != 0) 
	{//��֒e�Ȃ�
		GetPosition()[0].y += m_fMoveY;
		m_fMoveY += 0.5f;
		if (fPosX > SCREEN_WIDTH / 2)
		{//����
			Bomb();
			Uninit(); return;
		}
	}

	if (m_nType == 1 && m_fLife <= 0.3f) { Uninit(); return; }
	if (fPosX > SCREEN_WIDTH) { Uninit(); return; }
	SetPosition(GetPosition()[0] + D3DXVECTOR3(m_fMove, 0.0f, 0.0f));
}
//=============================================================================
// �Q�[�W�̍X�V����
//=============================================================================
void CBullet::Bomb(void)
{
	CScene **PScene;
	D3DXVECTOR3 pos = GetPosition()[0];
	D3DXVECTOR3 EnemyPos;

	PScene = CScene::GetScene(1);
	for (int nCntScene = 0; nCntScene < CScene::GetnMemoryAll(1); nCntScene++)
	{//�S�V�[�������
		if (PScene[nCntScene] != NULL)
		{//���g��NULL�łȂ�
			if (PScene[nCntScene]->GetObjType() == CScene::OBJTYPE_ENEMY)
			{//�G����
				EnemyPos = ((CEnemy*)PScene[nCntScene])->GetPosition()[0];
				if (pos.x + 150.0f > EnemyPos.x && pos.x - 150.0f < EnemyPos.x &&
					pos.y + 150.0f > EnemyPos.y && pos.y - 150.0f < EnemyPos.y)
				{
					((CEnemy*)PScene[nCntScene])->SetDamage(99999, 0);
				}

			}
		}
	}

	CSceneAnim2D *p2DAnim;
	if (SceneCreate(p2DAnim, 6))
	{//�����ł����Ȃ�@//�Ή�
		p2DAnim->Set(GetPosition()[0], 180.0f, 180.0f, D3DX_PI, 0, 10, 1, 4, 100.0f, CScene2D::STATE_BIG, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Explosion999);
		p2DAnim->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
	}
	if (SceneCreate(p2DAnim, 6))
	{//�����ł����Ȃ�@//�Ή�
		p2DAnim->Set(GetPosition()[0], 150.0f, 150.0f, D3DX_PI, 0, 10, 1, 4, 100.0f, CScene2D::STATE_BIG, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Explosion999);
		p2DAnim->BindDrawType(CScene::DRAW_TYPE_ADD);
	}
}