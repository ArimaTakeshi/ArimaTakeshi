//=============================================================================
//
// �g�̏��� [fram.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "fram.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\fram000.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2		"data\\TEXTURE\\fram001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3		"data\\TEXTURE\\fram002.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4		"data\\TEXTURE\\BbFram.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BG_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CFram::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CFram::CFram() : CScene2D(4)//�D��D�ʃC�j�V�����C�Y
{
	m_nCnt = 0;
	m_nType = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CFram::~CFram()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CFram::Init(void)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_FRAM);

	D3DXVECTOR3 VtxPos[4];
	D3DXCOLOR Color[4];

	if (m_nType == 0)
	{//�\������̈͂�
		VtxPos[0] = D3DXVECTOR3(990.0f, 400.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH - 10.0f, 400.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(990.0f, SCREEN_HEIGHT - 10.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH - 10.0f, SCREEN_HEIGHT - 10.0f, 0.0f);
	}
	else if (m_nType == 1)
	{//�L���A�C�R��
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	}
	else if (m_nType == 2)
	{//HP�̃o�[�̃t���[��
		VtxPos[0] = D3DXVECTOR3(10.0f, 640.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(280.0f, 640.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(10.0f, 700.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(280.0f, 700.0f, 0.0f);
	}
	//���T�C�h�̃t���[��
	else if (m_nType == 3)
	{//�E�̃t���[��
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(300.0f, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 4)
	{//���̃t���[��
		VtxPos[0] = D3DXVECTOR3(980.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(980.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}

	{//����ȊO�̏ꍇ���ׂĂ̏�����
		for (int nCount = 0; nCount < 4; nCount++)
		{
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	CScene2D::SetVtxPos(&VtxPos[0]);

	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFram::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CFram::Update(void)
{
	D3DXVECTOR2 UV[4];

	UV[0] = D3DXVECTOR2(0.0f, 0.0f);
	UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f);
	UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V);
	UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V);

	//�w�i��UV
	CScene2D::SetBg(&UV[0]);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CFram::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CFram * CFram::Create(int nType)
{
	CFram *pFram = NULL;

	//NULL�`�F�b�N
	if (pFram == NULL)
	{//�������̓��I�m��

		pFram = new CFram;

		if (pFram != NULL)
		{
			//��ނ����蓖�Ă�
			pFram->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pFram->Init();
			//�e�N�X�`�������蓖�Ă�
			pFram->BindTexture(m_pTexture[nType]);
		}
	}

	return pFram;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CFram::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[1]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_3,
		&m_pTexture[2]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_4,
		&m_pTexture[3]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_4,
		&m_pTexture[4]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CFram::UnLoad(void)
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