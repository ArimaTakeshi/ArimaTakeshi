//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "bg.h"
#include "score.h"
#include "title.h"
#include "fade.h"
#include "logo.h"
#include "sound.h"
#include "serect.h"
#include "explosion.h"
#include "report.h"
#include <string>
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME			"data\\TEXTURE\\.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_SIZE_X				(500)							//�e�N�X�`���c�T�C�Y
#define MAX_SIZE_Y				(600)							//�e�N�X�`�����T�C�Y
#define BG_TEXTURE_UV_U			(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V			(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CResult::m_pTexture = {};
CSerect *CResult::m_pSerect = NULL;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	m_pVtxBuff = NULL;
	m_nSetCnt = 0;
	m_nCnt = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CResult::Load(void)
{
	return S_OK;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init()
{
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	//�f�o�b�N�p�@�I������炱�̕����������ƁI�@Manager�̎n�܂��TITLE�ɖ߂����ƁI
	//GameStateNow = CGame::GAMESTATE_CLEAR;

	//�w�i�̃e�N�X�`���̓ǂݍ���
	CBg::Load();

	//���S�̃e�N�X�`���̓ǂݍ���
	CLogo::Load();

	//�����̃e�N�X�`���̓ǂݍ���
	CExplosion::Load();

	//�񍐂̃e�N�X�`���̓ǂݍ���
	CReport::Load();

	//�Z���N�g�̃e�N�X�`���̓ǂݍ���
	m_pSerect->Load();

	//�G���^�[�w��
	//CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH - 350.0f, 650.0f, 0.0f), D3DXVECTOR2(300.0f, 70.0f), 10);

	//�Z���N�g�̐���
	m_pSerect = CSerect::Create();

	if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//�Q�[���N���A�����ꍇ

		//�Q�[���N���A��BGM
		pSound->PlaySound(CSound::SOUND_LABEL_WINERBGM);

		//�w�i�̐���
		CBg::Create(3);
		CBg::Create(7);
		CBg::Create(6);
		CBg::Create(9);
		CBg::Create(8);

		//���
		CLogo::Create(D3DXVECTOR3(340.0f, 550.0f, 0.0f), D3DXVECTOR2(240.0f, 110.0f), 25);
		CLogo::Create(D3DXVECTOR3(1050.0f, 550.0f, 0.0f), D3DXVECTOR2(200.0f, 110.0f), 11);

		//�D��
		CLogo::Create(D3DXVECTOR3(1400.0f, 650.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 28);
	}
	else if (GameStateNow == CGame::GAMESTATE_OVER)
	{//�Q�[���I�[�o�[�����ꍇ

		//�Q�[���I�[�o�[��BGM
		pSound->PlaySound(CSound::SOUND_LABEL_GAMEOVER);

		//�w�i�̐���
		CBg::Create(3);
		CBg::Create(7);
		CBg::Create(6);
		CBg::Create(9);
		CBg::Create(8);

		//���
		CLogo::Create(D3DXVECTOR3(370.0f, 550.0f, 0.0f), D3DXVECTOR2(200.0f, 110.0f), 11);

		//�D��
		CLogo::Create(D3DXVECTOR3(1400.0f, 650.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 29);

		//������
		pSound->PlaySound(CSound::SOUND_LABEL_LOSE);
	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	//�|�[�Y�폜
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�Q�[���I�[�o�[��BGM
	pSound->StopSound(CSound::SOUND_LABEL_GAMEOVER);
	pSound->StopSound(CSound::SOUND_LABEL_WINERBGM);

	//�w�i�̃e�N�X�`���̔j��
	CBg::UnLoad();

	//���S�̃e�N�X�`���̔j��
	CLogo::UnLoad();

	//�����̃e�N�X�`���̔j��
	CExplosion::UnLoad();

	//�񍐂̃e�N�X�`���̔j��
	CReport::UnLoad();

	//�Z���N�g�̃e�N�X�`���̔j��
	m_pSerect->UnLoad();

	//���ʂ��m�F
	for (int nCnPri = 0; nCnPri < 7; nCnPri++)
	{
		//�I�u�W�F�N�g�̑������m�F
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene *pScene = CScene::GetScene(nCnPri, nCntScene);

			if (pScene != NULL)
			{
				pScene->Uninit();
			}
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	//�f�o�b�N�p�@�I������炱�̕����������ƁI�@Manager�̎n�܂��TITLE�ɖ߂����ƁI
	//GameStateNow = CGame::GAMESTATE_CLEAR;

	//�������o��
	if (m_nSetCnt == 560)
	{
		CReport::Create(D3DXVECTOR3(140.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 0);

		//������
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}
	else if (m_nSetCnt == 610)
	{
		CReport::Create(D3DXVECTOR3(310.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 1);

		//������
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}
	else if (m_nSetCnt == 660)
	{
		CReport::Create(D3DXVECTOR3(480.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 2);

		//������
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}
	else if (m_nSetCnt == 710)
	{
		CReport::Create(D3DXVECTOR3(650.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 3);

		//������
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}

	m_nSetCnt++;

	if (GameStateNow == CGame::GAMESTATE_OVER)
	{//�Q�[���I�[�o�[�����ꍇ
		
		//�퓬�@
		if (m_nCnt == 130)
		{//1�@��
			CLogo::Create(D3DXVECTOR3(-50.0f, 100.0f * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 22);

			//�퓬�@�ʉ߉�
			pSound->PlaySound(CSound::SOUND_LABEL_HIKOUKI);
		}
		else if (m_nCnt == 250)
		{//2�@��
			CLogo::Create(D3DXVECTOR3(-50.0f, 150.0f * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 22);

			//�퓬�@�ʉ߉�
			pSound->PlaySound(CSound::SOUND_LABEL_HIKOUKI);
		}
		else if (m_nCnt == 350)
		{//3�@��
			CLogo::Create(D3DXVECTOR3(-50.0f, 200.0f * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 22);

			//�퓬�@�ʉ߉�
			pSound->PlaySound(CSound::SOUND_LABEL_HIKOUKI);
		}

		//���e
		if (m_nCnt == 270)
		{//1�ډE�ɊO�� y����+10.0f�͔�s�@�Ɣ��Ȃ��悤�ɔ�s�@�̑傫���𑫂������� ����3���ׂĂ���
			CLogo::Create(D3DXVECTOR3(520.0f, 100.0f + 10.0f, 0.0f), D3DXVECTOR2(3.0f, 15.0f), 23);

			//���e�𗎂Ƃ���
			pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
		}
		else if (m_nCnt == 310)
		{//2�ڍ��ɊO��
			CLogo::Create(D3DXVECTOR3(200.0f, 150.0f + 10.0f, 0.0f), D3DXVECTOR2(3.0f, 15.0f), 23);

			//���e�𗎂Ƃ�
			pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
		}
		else if (m_nCnt == 450)
		{//3�ڐ�͂ɂ��Ă�
			CLogo::Create(D3DXVECTOR3(370.0f, 200.0f + 10.0f, 0.0f), D3DXVECTOR2(3.0f, 15.0f), 24);

			//���e�𗎂Ƃ�
			pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
		}
	}
	else if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//�Q�[���N���A�����ꍇ
	 //���e
		if (m_nCnt == 200)
		{//1��
			CLogo::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(10.0f, 1.5f), 26);

			//�����̐���
			CExplosion::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(40, 40), 0);

			//��C���ˉ�
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);
		}
		else if (m_nCnt == 240)
		{//2��
			CLogo::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(10.0f, 1.5f), 26);

			//�����̐���
			CExplosion::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(40, 40), 0);

			//��C���ˉ�
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);
		}
		else if (m_nCnt == 380)
		{//3�ڐ�͂ɂ��Ă�
			CLogo::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(10.0f, 1.5f), 27);

			//�����̐���
			CExplosion::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(40, 40), 0);

			//��C���ˉ�
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);
		}
	}

	if (m_nCnt == 1040)
	{//17�b��ɉ������ĂȂ��ꍇ�߂�
		//�^�C�g���ȗ���
		pSound->PlaySound(CSound::SOUND_LABEL_ENTERSE);
		CFade::Create(CManager::MODE_TITLE);
	}

	m_nCnt++;
}
//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
	
}
//=============================================================================
// �e�N�X�`���̊J������
//=============================================================================
void CResult::UnLoad(void)
{

}
