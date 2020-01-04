//=============================================================================
//
// �A�N�V�����|���S���̏��� [action2D.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "action2D.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "gauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ACTION2D_TEXTURE_NAME_1		"data\\TEXTURE\\sukill.png"			//�ǂݍ��ރe�N�X�`���t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CAction2D::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CAction2D::CAction2D() : CScene2D(4, CScene::OBJTYPE_LOGO)//�D��D�ʃC�j�V�����C�Y
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CAction2D::~CAction2D()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CAction2D::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CAction2D::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CAction2D::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�ʒu�̊��蓖��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ړ��ʂ̊��蓖��
	D3DXVECTOR3 move;
	move = GetMove();

	//�ʒu���X�V(�ړ�)
	pos.x += move.x;
	pos.y += move.y;

	//���S�̈ʒu�ƃT�C�Y
	CScene2D::SetPosSize(pos, m_size);
	//���S�̈ʒu�ƃT�C�Y
	CScene2D::SetMove(move);

	//�A�N�V�����t�F�[�h���N�����ĂȂ��ꍇ
	if (CPlayer::GetActionFade() == false && CGauge::GetGaugeActionFade() == false)
	{
		if (m_size.x < 2500.0f / 2)
		{
			// �w��̍����܂ő�������
			m_size.y += 90.0f;
			// ������ʕ���
			m_size.x += 100.0f;
		}
		else if (m_size.x <= 2500.0f / 2)
		{
			//2500�𒴂�����2500��������
			m_size.y = 2500.0f;
			m_size.x = 2500.0f;
		}
	}
	//�A�N�V�����t�F�[�h���N�����Ă�ꍇ
	else if (CPlayer::GetActionFade() == true || CGauge::GetGaugeActionFade() == true)
	{
		if (m_size.x > 0)
		{	
			// �w��̍����܂ŏ���������
			m_size.y -= 90.0f;
			// ������ʕ���
			m_size.x -= 100.0f;
		}
		else if (m_size.x >= 0)
		{
			//0�𒴂�����0��������
			m_size.y = 0.0f;
			m_size.x = 0.0f;

			//�t�F�[�h������
			CAction2D::Uninit();

			//�A�N�V�����t�F�[�h��false��Ԃ�
			CPlayer::SetActionFade(false);

			//�Q�[�W�����A�N�V�����t�F�[�h��false��Ԃ�
			CGauge::SetGaugeActionFade(false);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CAction2D::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CAction2D * CAction2D::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CAction2D *pAction2D = NULL;

	//NULL�`�F�b�N
	if (pAction2D == NULL)
	{//�������̓��I�m��

		pAction2D = new CAction2D;

		if (pAction2D != NULL)
		{
			//��ނ����蓖�Ă�
			pAction2D->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pAction2D->Init();
			//�e�N�X�`�������蓖�Ă�
			pAction2D->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pAction2D->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pAction2D->m_size = size;
		}
	}

	return pAction2D;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CAction2D::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, ACTION2D_TEXTURE_NAME_1,&m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CAction2D::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}