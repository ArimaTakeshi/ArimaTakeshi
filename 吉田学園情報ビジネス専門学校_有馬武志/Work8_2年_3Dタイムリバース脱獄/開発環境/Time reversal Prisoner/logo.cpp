//=============================================================================
//
// ���S�̏��� [logo.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "logo.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "billboord.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LOGO_TEXTURE_NAME_1		"data\\TEXTURE\\State\\none.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_2		"data\\TEXTURE\\State\\qusetion000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_3		"data\\TEXTURE\\State\\exclamation000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_4		"data\\TEXTURE\\State\\attack000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_5		"data\\TEXTURE\\fram.png"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_6		"data\\TEXTURE\\State\\Stealth.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_7		"data\\TEXTURE\\State\\Hidden.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_8		"data\\TEXTURE\\State\\Caution.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_9		"data\\TEXTURE\\State\\Danger.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_10	"data\\TEXTURE\\�ē�\\�R���g���[���[.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_11	"data\\TEXTURE\\�ē�\\�ē�1.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_12	"data\\TEXTURE\\�ē�\\�ē�2.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_13	"data\\TEXTURE\\�ē�\\�ē�3.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_14	"data\\TEXTURE\\�ē�\\�ē�4.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_15	"data\\TEXTURE\\�ē�\\�ē�6.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define LOGO_TEXTURE_NAME_16	"data\\TEXTURE\\Tutorial.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_TEXTURE] = {};
int CLogo::m_nNextType = 0;
int CLogo::m_nNextFont = 0;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CLogo::CLogo() : CScene2D(5, CScene::OBJTYPE_LOGO)//�D��D�ʃC�j�V�����C�Y
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTutorial = 0;
	m_bOneCnt = false;
	m_nStateFont = 0;
	m_nStateType = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CLogo::~CLogo()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLogo::Init(void)
{
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogo::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�ʒu�̊��蓖��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ړ��ʂ̊��蓖��
	D3DXVECTOR3 move;
	move = GetMove();

	//�\����Ԃ̃X�e�[�^�X�݂̂ɔ��f
	if (m_nType >= 0 && m_nType <= 3)
	{
		if (m_nStateType != m_nNextType)
		{
			m_nStateType = m_nNextType;
			//��Ԃ̒l������
			m_nType = m_nStateType;
		}
		//�l�̏�����
		m_nNextType = 0;
	}
	//�\����Ԃ̃t�H���g�݂̂ɔ��f
	if (m_nType >= 5 && m_nType <= 8)
	{
		if (m_nStateFont != m_nNextFont)
		{
			m_nStateFont = m_nNextFont;
			//��Ԃ̒l������
			m_nType = m_nStateFont;
		}
		//�l�̏�����
		m_nNextFont = 5;
	}

	switch (m_nType)
	{
	case 0:
		//�����Ȃ���Ԃ̕\��
		BindTexture(m_pTexture[0]);
		break;
	case 1:
		//�r�b�N���}�[�N�̕\��
		BindTexture(m_pTexture[1]);
		break;
	case 2:
		//�����̕\��
		BindTexture(m_pTexture[2]);
		break;
	case 3:
		//�������\��
		BindTexture(m_pTexture[3]);
		break;
	case 5:
		//Caution�\��
		BindTexture(m_pTexture[5]);
		break;
	case 6:
		//Danger�\��
		BindTexture(m_pTexture[6]);
		break;
	case 7:
		//hidden�\��
		BindTexture(m_pTexture[7]);
		break;
	case 8:
		//Stealth�\��
		BindTexture(m_pTexture[8]);
		break;
	}
	
	//�ό`�ł���
	if (m_nTransformType == 1)
	{
		if (m_nType == 4)
		{//�t���[��
			CScene2D::SetPosDiamond(pos, m_size, D3DXVECTOR4(25.0f, 25.0f, 3.0f, 3.0f));
		}
	}


	//�ʒu���X�V(�ړ�)
	pos.x += move.x;
	pos.y += move.y;

	if (m_nTransformType == 0)
	{
		//���S�̈ʒu�ƃT�C�Y
		CScene2D::SetPosSize(pos, m_size);
		//���S�̈ʒu�ƃT�C�Y
		CScene2D::SetMove(move);
		//��]����
		//CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CLogo::Draw(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();

	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType,int nTransformType)
{
	CLogo *pLogo = NULL;

	//NULL�`�F�b�N
	if (pLogo == NULL)
	{//�������̓��I�m��

		pLogo = new CLogo;

		if (pLogo != NULL)
		{
			//��ނ����蓖�Ă�
			pLogo->m_nType = nType;
			//�ό`�ł�����
			pLogo->m_nTransformType = nTransformType;
			//�I�u�W�F�N�g�N���X�̐���
			pLogo->Init();
			//�e�N�X�`�������蓖�Ă�
			pLogo->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pLogo->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pLogo->m_size = size;
		}
	}

	return pLogo;
}
//===============================================================================
//�@��Ԃ̗D�揇��
//===============================================================================
void CLogo::SetLogoState(int nStateType, int nStateFont)
{
	//�A�C�R���̗D�揇��
	if (m_nNextType <= nStateType)
	{
		m_nNextType = nStateType;
	}
	//�t�H���g�̗D�揇��
	if (m_nNextFont <= nStateFont)
	{
		m_nNextFont = nStateFont;
	}
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CLogo::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_9, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_10, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_11, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_12, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_13, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_14, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_15, &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_16, &m_pTexture[15]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CLogo::UnLoad(void)
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