//=============================================================================
//
// �����̏��� [explosion.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "explosion.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1					"data\\TEXTURE\\explosion000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2					"data\\TEXTURE\\explosion001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3					"data\\TEXTURE\\explosion002.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4					"data\\TEXTURE\\explosion004.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_5					"data\\TEXTURE\\explosion005.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_6					"data\\TEXTURE\\explosion006.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_7					"data\\TEXTURE\\explosion007.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_8					"data\\TEXTURE\\explosion008.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define EXPLOSION_TEXTURE_SPEED			(6)									//�e�N�X�`���A�j���[�V�����X�s�[�h
#define EXPLOSION_TEXTURE_PATTERN		(8)									//�e�N�X�`���A�j���[�V�����p�^�[����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CExplosion::CExplosion() : CScene2D(4)//�D��D�ʃC�j�V�����C�Y
{
	m_nCounterAnim = 0;
	m_nPatteunAnim = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CExplosion::~CExplosion()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(void)
{	
	CScene2D::Init();

	D3DXVECTOR2 uv[4];

	uv[0] = D3DXVECTOR2(0.0f,0.0f);
	uv[1] = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_PATTERN, 0.0f);
	uv[2] = D3DXVECTOR2(0.0f, 1.0f);
	uv[3] = D3DXVECTOR2(1.0f / EXPLOSION_TEXTURE_PATTERN, 1.0f);

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_EXPLOSION);

	CScene2D::SetBg(&uv[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	//�����l�ݒ�
	D3DXVECTOR3 pos;
	pos = CExplosion::GetPosition();

	CScene2D::Set(pos, m_Size);

	m_nCounterAnim++;		//�J�E���^�[���Z

	if ((m_nCounterAnim % EXPLOSION_TEXTURE_SPEED) == 0)
	{//�A�j���[�V�������x

		m_nPatteunAnim = (m_nPatteunAnim + 1) % EXPLOSION_TEXTURE_PATTERN;		//�p�^�[��No.�X�V

		CScene2D::SetAnim(D3DXVECTOR2(0.125f, 1.0f), m_nPatteunAnim);

		if (m_nPatteunAnim == EXPLOSION_TEXTURE_PATTERN - 1)
		{//�A�j���[�V�������Ō�܂ł������ꍇ
			CExplosion::Uninit();
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size, int nType)
{
	CExplosion *pExplosion = NULL;

	//NULL�`�F�b�N
	if (pExplosion == NULL)
	{//�������̓��I�m��

		pExplosion = new CExplosion;

		if (pExplosion != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pExplosion->Init();
			//��ނ̊��蓖��
			pExplosion->m_nType = nType;
			//�e�N�X�`�������蓖�Ă�
			pExplosion->BindTexture(m_pTexture[nType]);
			//�e��ݒu
			pExplosion->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pExplosion->m_Size = size;

		}
	}
	return pExplosion;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CExplosion::Load(void)
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
		TEXTURE_NAME_5,
		&m_pTexture[4]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_6,
		&m_pTexture[5]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_7,
		&m_pTexture[6]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_8,
		&m_pTexture[7]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CExplosion::UnLoad(void)
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