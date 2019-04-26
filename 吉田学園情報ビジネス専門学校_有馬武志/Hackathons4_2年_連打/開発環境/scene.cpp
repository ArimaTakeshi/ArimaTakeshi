//=============================================================================
//
// �����_�����O���� [renderer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "SceneModel.h"
#include "SceneBullet.h"
#include "Player.h"
#include "SceneEnemy.h"
#include "SceneBoss.h"
#include "dungeon.h"
#include "Font.h"

#include "2DPolygon.h"
#include "2DGage.h"
#include "3DPolygon.h"

#include "collision.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CScene	**CScene::m_PScene[MAX_SCENE] = {};			// ���I�m�ۗp
int		CScene::m_nNumAll[MAX_SCENE] = {0, 0, 0, 0, 0, 0, 0, 0};		// ���������̐�
int		CScene::m_nMemoryAll[MAX_SCENE] = { 0, 0, 0, 0, 0, 0, 0, 0 };	// ���������
int		CScene::m_nDraw = 0;					// ���݂̕`����
int		CScene::m_nCntStart = 0;				// ���݂̕`����
bool	CScene::m_bPause = false;				//�|�[�Y�̗L��
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPrioryity)
{
	for (int nCount = 0; nCount < m_nMemoryAll[nPrioryity]; nCount++)
	{
		if (m_PScene[nPrioryity][nCount] == NULL)
		{
			m_PScene[nPrioryity][nCount] = this;
			m_nID = nCount;
			m_nPriority = nPrioryity;
			m_nNumAll[nPrioryity]++;	//����++
			SetObjType(OBJTYPE_NONE);
			return;
		}
	}
	MessageBox(0, "�G���[", "Scene�̃R���X�g���N�^�R��Ă��", MB_OK);
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene(void) {}

//==================================================================================================//
//    * �S����֐� *
//==================================================================================================//
void CScene::ReleaseAll(void)
{
	CSceneBullet::UnLoad();
	CScene2D::UnLoad();
	CScene3D::UnLoad();
	CSceneAnim3D::UnLoad();
	CSceneModel::UnLoadModel();
	CDungeon::UnLoadModel();
	CDungeon::UnLoad();
	CSceneBoss::UnLoad();

	C2D::UnLoad();
	C2DGage::UnLoad();
	C3D::UnLoad();
	CFont::UnLoad();
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_PScene[nCntScene] != NULL)
		{//�{�̂ɉ��������Ă���Ȃ�
			for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
			{//���������S�ĉ�]
				if (m_PScene[nCntScene][nCount] != NULL)
				{//���������Ă���Ȃ�I���ƃ������폜
					m_PScene[nCntScene][nCount][0].Uninit();
				}
			}
			delete[] m_PScene[nCntScene]; m_PScene[nCntScene] = NULL;
			m_nMemoryAll[nCntScene] = 0;	//�󂫃��Z�b�g
			m_nNumAll[nCntScene] = 0;		//�������Z�b�g
		}
	}
}
//==================================================================================================//
//    * �{�̐����֐� *
//==================================================================================================//
void CScene::CreateAll(int nPrioryity, int nNumber)
{//�ő�g����
	CScene::m_PScene[nPrioryity] = new CScene*[nNumber]; CScene::m_nMemoryAll[nPrioryity] = nNumber;
	for (int nCount = 0; nCount < CScene::m_nMemoryAll[nPrioryity]; nCount++) { CScene::m_PScene[nPrioryity][nCount] = NULL; }
}

//=============================================================================
// �X�V����
//=============================================================================
void  CScene::UpdateAll(void)
{
	for (int nCntScene = (m_bPause ? MAX_SCENE - 1 : m_nCntStart); nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_PScene[nCntScene] != NULL)
		{// �|���S���̍X�V����
			for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
			{//�������ꂽ�����Đ�
			 //if ((*(PScene + nCount)) != NULL)
				if (m_PScene[nCntScene][nCount] != NULL)
				{//�A�h���X�����݂���Ȃ�	//	(*PScene)->Update;
				 //(*(PScene + nCount))->Update();
				 //(*PScene)->Update;PScene++;
					m_PScene[nCntScene][nCount]->Update();
				}
			}
		}
	}
	CCollision::CollisionAll();
}
//=============================================================================
// �`�揈��
//=============================================================================
void  CScene::DrawAll(LPDIRECT3DDEVICE9 &pDevice)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE - 1; nCntScene++)
	{
		if (m_PScene[nCntScene] != NULL)
		{// �|���S���̕`�揈��
			if (nCntScene == BULLET_PRIORITY)
			{
				// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
				pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
			}
			for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
			{//�������ꂽ�����Đ�
				if (m_PScene[nCntScene][nCount] != NULL)
				{//�A�h���X�����݂���Ȃ�
					m_PScene[nCntScene][nCount]->Draw();
				}
			}
		}
	}
	CPlayer *pPlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		pPlayer = CManager::GetPlayer0();
		if (pPlayer != NULL) { pPlayer->DrawUI(); }
	}

	if (m_PScene[PAUSE_PRIORITY] != NULL)
	{// �|���S���̕`�揈��
		for (int nCount = 0; nCount < m_nMemoryAll[PAUSE_PRIORITY]; nCount++)
		{//�������ꂽ�����Đ�
			if (m_PScene[PAUSE_PRIORITY][nCount] != NULL)
			{//�A�h���X�����݂���Ȃ�
				m_PScene[PAUSE_PRIORITY][nCount]->Draw();
			}
		}
	}
}
//==================================================================================================//
//    * �`�揀���֐� *
//==================================================================================================//
bool CScene::DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	if (DrawType == DRAW_TYPE_NO) { return true; }

	if (m_nDraw / 10 != DrawType / 10)
	{//���݂�Z�e�X�g�ƕ`����@���Ⴄ�Ȃ�
		if (DrawType >= CScene::DRAW_TYPE_ZNORMAL)
		{// Z�e�X�g����
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		}
		else
		{// Z�e�X�g�n��
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		}
	}
	if (m_nDraw % 10 != DrawType % 10)
	{//���݂̍������@���Ⴄ�Ȃ�
		switch (DrawType % 10)
		{//�ق�Ƃ�3�s���邱�Ƃ�Y��Ă͂����Ȃ�...
		case CScene::DRAW_TYPE_NORMAL:// �ʏ�
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case CScene::DRAW_TYPE_ADD:// ���u�����f�B���O�����Z�����ɐݒ�
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_SUBTRACT:// ���Z
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_MULTIPLY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			break;
		case CScene::DRAW_TYPE_OVERLAY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		}
	}
	m_nDraw = DrawType;	//�`����@�̑��

	return false;
}
//==================================================================================================//
//    * �����폜�֐� *
//==================================================================================================//
void CScene::Release()
{
	if (m_PScene[m_nPriority][m_nID] != NULL)
	{ 
		int nID = m_nID;
		int nPriority = m_nPriority;
		m_nNumAll[nPriority]--;
		delete this;
		m_PScene[nPriority][nID] = NULL;
	}
}
//=============================================================================
//	�S�I�u�W�F�N�g��j��
//=============================================================================
void CScene::BreakObject(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
		{//�S�V�[�������
			if (m_PScene[nCntScene][nCount] != NULL)
			{
				m_PScene[nCntScene][nCount]->Uninit();
			}
		}
	}
}
//=============================================================================
//	�w�肵���I�u�W�F�N�g��j��
//=============================================================================
void CScene::BreakObject(OBJTYPE obj)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
		{//�S�V�[�������
			if (m_PScene[nCntScene][nCount] != NULL)
			{
				if (obj == m_PScene[nCntScene][nCount]->GetObjType())
				{//�w��̃I�u�W�F�Ȃ�j��
					m_PScene[nCntScene][nCount]->Uninit();
				}
			}
		}
	}
}
//=============================================================================
// �V�[����Ԃ�
//=============================================================================
CScene **CScene::GetScene(int nPrioryity)
{
	return m_PScene[nPrioryity];
}
#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
//void CScene::DrawFPS(void)
//{
//	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	char str[256];
//
//	wsprintf(str, "FPS:%d\n", GetFPS());
//
//	// �e�L�X�g�`��
//	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//}
#endif
