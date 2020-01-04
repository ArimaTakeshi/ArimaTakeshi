//=============================================================================
//
// �K�C�h�̏��� [guide.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "guide.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "billboord.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GUIDE_TEXTURE_NAME_1		"data\\TEXTURE\\�ē�\\�|�[�Y.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_2		"data\\TEXTURE\\�ē�\\B3��2���e��.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_3		"data\\TEXTURE\\�ē�\\B2�S�W�K�w�H��.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_4		"data\\TEXTURE\\�ē�\\B1���l�p�L��.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_5		"data\\TEXTURE\\�ē�\\B1���l�R���H.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_6		"data\\TEXTURE\\�ē�\\F1���l�p����.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_7		"data\\TEXTURE\\�ē�\\�n��^����.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_8		"data\\TEXTURE\\�ē�\\�}�b�v.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_9		"data\\TEXTURE\\�ē�\\���݂̈ʒu.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_10		"data\\TEXTURE\\�ē�\\��.png"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_11		"data\\TEXTURE\\�ē�\\��.png"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_12		"data\\TEXTURE\\�ē�\\Rewind time.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_13		"data\\TEXTURE\\title.png"						//�ǂݍ��ރe�N�X�`���t�@�C��
#define GUIDE_TEXTURE_NAME_14		"data\\TEXTURE\\PressAButton.png"				//�ǂݍ��ރe�N�X�`���t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGuide::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CGuide::CGuide() : CScene2D(5, CScene::OBJTYPE_GUIDE)//�D��D�ʃC�j�V�����C�Y
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntBandTimer = 0;
	m_nCntStar = 0;
	m_fColorCount = 0.0f;
	m_bOneCnt = false;
	m_bPressA = false;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CGuide::~CGuide()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGuide::Init(void)
{
	m_fColorCount = 0;

	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGuide::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGuide::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	CSound *pSound = CManager::GetSound();

	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//�ʒu�̊��蓖��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ړ��ʂ̊��蓖��
	D3DXVECTOR3 move;
	move = GetMove();

	//�F�̊��蓖��
	D3DXCOLOR col[4];

	//���[�h
	CManager::MODE pMode = CManager::GetMode();
	
	//�}�b�v��̐��̈ʒu
	if (m_nType == 9)
	{
		// �������o��
		m_fLength = sqrtf((m_size.x / 2 + m_size.x / 2) * (m_size.y / 2 + m_size.y / 2));
		// �p�x���o��
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

		if (m_nCntStar == 60)
		{
			//�J�E���^�[��0�ɖ߂�
			m_nCntStar = 0;
		}
		else if (m_nCntStar >= 30)
		{
			//�E��]
			m_rot.x -= 0.01f;
			m_rot.y -= 0.01f;
		}
		else if (m_nCntStar >= 0)
		{
			//����]
			m_rot.x += 0.01f;
			m_rot.y += 0.01f;
		}

		//�J�E���^�[�̑���
		m_nCntStar++;

		switch (pStageNum)
		{
		case CGame::STAGENUM_1:
			pos = D3DXVECTOR3(1130.0f, 665.0f, 0.0f);
			break;
		case CGame::STAGENUM_2:
			pos = D3DXVECTOR3(1225.0f, 595.0f, 0.0f);
			break;
		case CGame::STAGENUM_3:
			pos = D3DXVECTOR3(1140.0f, 535.0f, 0.0f);
			break;
		case CGame::STAGENUM_4:
			pos = D3DXVECTOR3(1225.0f, 480.0f, 0.0f);
			break;
		case CGame::STAGENUM_5:
			pos = D3DXVECTOR3(1150.0f, 415.0f, 0.0f);
			break;
		case CGame::STAGENUM_6:
			pos = D3DXVECTOR3(1165.0f, 330.0f, 0.0f);
			break;
		}
	}

	if (pMode == CManager::MODE_TITLE)
	{
		if (m_nType == 13)
		{
			if (pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_B) == true || pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true)
			{
				//A�{�^���������ꂽ
				m_bPressA = true;
			}
			
			if (m_bPressA == true)
			{
				//�_�ŏ���
				//�I�����Ă���J���[�̒l�����炵�Ă���
				m_fColorCount -= 0.09f;

				if (m_fColorCount < 0.5f)
				{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
					m_fColorCount = 1.0f;
				}

				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			}
			else if (m_bPressA == false)
			{
				//�_�ŏ���
				//�I�����Ă���J���[�̒l�����炵�Ă���
				m_fColorCount -= 0.009f;

				if (m_fColorCount < 0.5f)
				{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
					m_fColorCount = 1.0f;
				}

				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			}

			CScene2D::SetColor(&col[0]);
		}

		if (m_nType == 12)
		{
			//�_�ŏ���
			//�I�����Ă���J���[�̒l�����炵�Ă���
			m_fColorCount += 0.009f;

			if (m_fColorCount > 1.0f)
			{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
				m_fColorCount = 1.0f;
			}

			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
		}
	}
	else
	{
		//�_�ŏ�Ԃ�������
		m_bPressA = false;
	}

	//�ē��\�L
	if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2 || pStageNum == CGame::STAGENUM_3 || pStageNum == CGame::STAGENUM_4 || pStageNum == CGame::STAGENUM_5 || pStageNum == CGame::STAGENUM_6)
	{
		//�ē��\�L�̕\��
		if (m_nType != 0 && m_nType != 7 && m_nType != 8 && m_nType != 9 && m_nType != 10 && m_nType != 11 && m_nType != 12 && m_nType != 13)
		{
			if (m_nCntMapGuideTimer >= 200)
			{//���ɓ�����
				move.x = -40;
			}
			else if (m_nCntMapGuideTimer >= 80)
			{//���ɓ�����
				if (pos.x >= SCREEN_WIDTH / 2)
				{//�E�ɓ�����
					move.x = -40;
				}
				else if (pos.x <= SCREEN_WIDTH / 2)
				{//��x�~�߂�
					move.x = 0.0f;
				}
			}

			m_nCntMapGuideTimer++;
		}
	}

	//�ʒu���X�V(�ړ�)
	pos.x += move.x;
	pos.y += move.y;

	if (m_nType != 9)
	{
		//���S�̈ʒu�ƃT�C�Y
		CScene2D::SetPosSize(pos, m_size);
		//���S�̈ʒu�ƃT�C�Y
		CScene2D::SetMove(move);
	}
	else if (m_nType == 9)
	{//��]���������Ă����ނ̂�
		CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}

	if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2 || pStageNum == CGame::STAGENUM_3 || pStageNum == CGame::STAGENUM_4 || pStageNum == CGame::STAGENUM_5 || pStageNum == CGame::STAGENUM_6)
	{
		//�ē��т̏o��
		if (m_nType == 0)
		{
			if (m_nCntBandTimer >= 240)
			{//�т̏k��
				m_size.y -= 5.0f;

				if (m_size.x == 0.0f || m_size.y == 0.0f)
				{
					//�T�C�Y�������Ȃ��Ȃ������ɍ폜����
					CGuide::Uninit();

					m_nCntBandTimer = 0;
				}
			}
			else if (m_nCntBandTimer >= 60)
			{//�т̏o��
				if (m_size.y < 100.0f / 2)
				{// �w��̍����܂ő�������
					m_size.y += 5.0f;
					// ������ʕ���
					m_size.x = SCREEN_WIDTH;
				}
			}
			//�J�E���g�𑝉�
			m_nCntBandTimer++;
		}
	}

	//��ʍ��ɐi�ݑ������ꍇ
	if (pos.x <= -1280.0f)
	{
		//�폜
		CGuide::Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGuide::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CGuide * CGuide::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CGuide *pGuide = NULL;

	//NULL�`�F�b�N
	if (pGuide == NULL)
	{//�������̓��I�m��

		pGuide = new CGuide;

		if (pGuide != NULL)
		{
			//��ނ����蓖�Ă�
			pGuide->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pGuide->Init();
			//�e�N�X�`�������蓖�Ă�
			pGuide->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pGuide->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pGuide->m_size = size;
		}
	}

	return pGuide;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CGuide::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_9, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_10, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_11, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_12, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_13, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_14, &m_pTexture[13]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CGuide::UnLoad(void)
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