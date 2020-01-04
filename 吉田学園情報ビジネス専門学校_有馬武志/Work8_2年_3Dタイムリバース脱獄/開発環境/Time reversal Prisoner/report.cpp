//=============================================================================
//
// �񍐂̏��� [report.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "report.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\�Q�[���N���A\\W�E.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2		"data\\TEXTURE\\�Q�[���N���A\\W��.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3		"data\\TEXTURE\\�Q�[���N���A\\W��.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4		"data\\TEXTURE\\�Q�[���N���A\\W��.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_5		"data\\TEXTURE\\�Q�[���I�[�o�[\\L�E.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_6		"data\\TEXTURE\\�Q�[���I�[�o�[\\L��.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_7		"data\\TEXTURE\\�Q�[���I�[�o�[\\L��.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_8		"data\\TEXTURE\\�Q�[���I�[�o�[\\L�s.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define REPORT_MIN_POS		(200.0f)									//�Œ�ʒu
#define REPORT_MAX_SIZE_X	(90.0f)										//X�ő�̃T�C�Y
#define REPORT_MAX_SIZE_Y	(120.0f)									//Y�ő�̃T�C�Y
#define REPORT_DOWNSPD		(5.0f)										//�����X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CReport::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CReport::CReport() : CScene2D(4)//�D��D�ʃC�j�V�����C�Y
{
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CReport::~CReport()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CReport::Init(void)
{
	CScene2D::Init();

	D3DXCOLOR Color[4];

	for (int nCount = 0; nCount < 4; nCount++)
	{//����ȊO�̏ꍇ���ׂĂ̏�����
		Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CReport::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CReport::Update(void)
{
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();

	//�Q�[���̏�Ԃ̊m�F
	CGame::GAMESTATE GameState = CGame::GetGameState();

	//�f�o�b�N�p�@�I������炱�̕����������ƁI�@Manager�̎n�܂��TITLE�ɖ߂����ƁI 
	//�N���A�@GAMESTATE_CLEAR�@�I�[�o�[  GAMESTATE_OVER
	//GameState = CGame::GAMESTATE_CLEAR;

	//�ړ��ʂ̊��蓖��
	D3DXVECTOR3 move;
	move = GetMove();

	//�ʒu�̊��蓖��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	if (m_size.x > REPORT_MAX_SIZE_X)
	{// �ړI�̑傫�����傫�����
		// �k��������
		m_size -= D3DXVECTOR2(5.0f, 5.0f);
	}

	//�ʒu���X�V(�ړ�)
	pos.x += move.x;
	pos.y += move.y;

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�񍐂̈ʒu�ƃT�C�Y
	CScene2D::SetPosSize(pos, m_size);
	//�񍐂̈ʒu�ƃT�C�Y
	CScene2D::SetMove(move);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CReport::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CReport * CReport::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CReport *pReport = NULL;

	//NULL�`�F�b�N
	if (pReport == NULL)
	{//�������̓��I�m��

		pReport = new CReport;

		if (pReport != NULL)
		{
			//��ނ����蓖�Ă�
			pReport->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pReport->Init();
			//�e�N�X�`�������蓖�Ă�
			pReport->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pReport->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pReport->m_size = size;
		}
	}

	return pReport;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CReport::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_2,&m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_3,&m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_4,&m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_8, &m_pTexture[7]);
	
	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CReport::UnLoad(void)
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