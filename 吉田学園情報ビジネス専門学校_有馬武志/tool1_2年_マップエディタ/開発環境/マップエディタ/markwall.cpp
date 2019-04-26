//=============================================================================
//
// ��̕Ǐ��� [markwall.cpp]
// Author : �L�n ���u
//
//=============================================================================
#include "markwall.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "imgui_arima.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MARKWALL_TEX_1	"data\\TEXTURE\\wall\\wall000.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_2	"data\\TEXTURE\\wall\\wall001.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_3	"data\\TEXTURE\\wall\\field03.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_4	"data\\TEXTURE\\wall\\rock_003.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_5	"data\\TEXTURE\\wall\\soil.jpg"				// �e�N�X�`���̖��O
#define MARKWALL_TEX_6	"data\\TEXTURE\\wall\\scarp02.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_7	"data\\TEXTURE\\wall\\wallRock.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_8	"data\\TEXTURE\\wall\\Black.jpg"			// �e�N�X�`���̖��O
#define MARKWALL_TEX_9	"data\\TEXTURE\\wall\\wall000.png"			// �e�N�X�`���̖��O
#define MAX_SPEED		(3.0f)										// �ǂ̈ړ����x
#define MAX_LSHIFTSPEED	(0.5f)										// �ǂ̈ړ����x

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CMarkWall::m_pTexture[MAX_MARKWALL_TEX] = {};
int CMarkWall::m_nWallNum = 0;
CWall *CMarkWall::m_pWall = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMarkWall::CMarkWall() : CScene3D(MARKWALL_PRIOTITY, CScene::OBJTYPE_MARKWALL)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_fWidthLength = 100.0f;
	m_fHightLength = 200.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMarkWall::~CMarkWall()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMarkWall::Init()
{
	//����������
	CScene3D::Init();

	//��ނ̐ݒ�
	SetTypeNumber(TYPE_WALL);

	if (m_nType == 9)
	{
		//CScene3D::SetNor(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMarkWall::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CMarkWall::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	//�ݒu���[�h
	int nSetMode = CImgui_Arima::GetSetMode();

	//�ǂ̌�����������
	m_rot = CScene3D::GetRotation();

	//�ҏW���[�h���J�n
	if (nSetMode == 2)
	{
		//�ۑ��p�f�[�^
		float fWallWL = m_fWidthLength;
		float fWallHL = m_fHightLength;

		//-------------------------------------
		//        Imgui����l��Ⴄ
		//-------------------------------------
		m_pos = CImgui_Arima::GetWallPos();
		m_rot = CImgui_Arima::GetWallRot();
		m_nWallTextureNumber = CImgui_Arima::GetWallType();
		m_fWidthLength = (float)CImgui_Arima::GetWallWL();
		m_fHightLength = (float)CImgui_Arima::GetWallHL();
		m_bSetWall = CImgui_Arima::GetWallSet();

		switch (m_nWallTextureNumber)
		{
		case 0:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �u���b�N�R���N���[�g
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 1:
			//�e�N�X�`���̎��
			m_nTexType = 1;
			// ������
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 2:
			//�e�N�X�`���̎��
			m_nTexType = 2;
			// �y��
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 3:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// ��̂ق�������
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 4:
			//�e�N�X�`���̎��
			m_nTexType = 4;
			// ��̂ق�����
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 5:
			//�e�N�X�`���̎��
			m_nTexType = 5;
			// ��
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 6:
			//�e�N�X�`���̎��
			m_nTexType = 6;
			// ���ɑ��������Ă����
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 7:
			//�e�N�X�`���̎��
			m_nTexType = 7;
			// �F��
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 8:
			//�e�N�X�`���̎��
			m_nTexType = 8;
			// ���������ȕ�
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		}

		//-------------------------------------
		//         �I�u�W�F�N�g����
		//-------------------------------------
		if (m_bSetWall == true)
		{
			//�I�u�W�F�N�g�̐���
			m_pWall = CWall::Create(m_pos, m_size, m_rot, m_nTexType);
			//�u�������̌v�Z
			m_nWallNum += 1;
		}

		//����n��
		CScene3D::SetWall(m_pos, m_rot, m_size);

		//-------------------------------------
		//         �c�̒����ύX��ύX
		//-------------------------------------
		if (fWallHL > m_fHightLength)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fHightLength > fWallHL)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         ���̒����ύX��ύX
		//-------------------------------------
		if (fWallWL > m_fWidthLength)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fWidthLength > fWallWL)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//�ʒu��ۑ�
		if (CImgui_Arima::GetWallClicked() % 2 == 1)
		{
			CDebugProc::Print("�ۑ��I");
			m_pWall->TextSave();
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMarkWall::Draw(void)
{
	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�ݒu���[�h
	int nSetMode = CImgui_Arima::GetSetMode();

	//�ҏW���[�h���J�n
	if (nSetMode == 2)
	{
		CScene3D::Draw();
	}
}
//=============================================================================
// ��������
//=============================================================================
CMarkWall * CMarkWall::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nTexType)
{
	CMarkWall *pWall = NULL;

	//NULL�`�F�b�N
	if (pWall == NULL)
	{//�������̓��I�m��

		pWall = new CMarkWall;

		if (pWall != NULL)
		{
			//��ނ̐ݒ�
			pWall->m_nType = nTexType;
			//����������
			pWall->Init();
			//�ʒu�̐ݒ�
			pWall->m_pos = pos;
			//�����蔻��p
			pWall->m_size = size;
			//�����̐ݒ�
			pWall->m_rot = rot;
			//�e�N�X�`���̐ݒ�
			pWall->BindTexture(m_pTexture[nTexType]);
			//�����̑��
			pWall->m_fWidthLength = size.x;
			//�c���̑��
			pWall->m_fHightLength = size.y;
			//�ʒu�Ɖ�]�ƃT�C�Y
			pWall->SetWall(pos, rot, size);
		}
	}

	return pWall;
}
//===============================================================================
//�@�폜�Ɛ���
//===============================================================================
void CMarkWall::UninitCreate(D3DXVECTOR3 pos)
{
	//�폜
	CMarkWall::Uninit();

	//����
	CMarkWall::Create(pos,D3DXVECTOR2(m_fWidthLength, m_fHightLength),m_rot, m_nTexType);
}
//=============================================================================
// �ǂݍ��ݏ���
//=============================================================================
HRESULT CMarkWall::Load(void)
{
	// �f�o�C�X�擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`������
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_9, &m_pTexture[8]);

	return S_OK;
}

//=============================================================================
// �J������
//=============================================================================
void CMarkWall::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MARKWALL_TEX; nCount++)
	{
		// �e�N�X�`���j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}