//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "game.h"
#include "tutorial.h"
#include "title.h"
#include "result.h"
#include "sound.h"
#include "main.h"
#include "pause.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyBoard *CManager::m_pInputKeyBoard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CSound *CManager::m_pSound = NULL;

//�Q�[���̈�ԍŏ�
CManager::MODE CManager::m_mode = MODE_TITLE;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CManager::CManager()
{

}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CManager::~CManager()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindows)
{
	//NULL�`�F�b�N
	if (m_pRenderer == NULL)
	{
		//���I�m��
		m_pRenderer = new CRenderer;

		//NULL�`�F�b�N
		if (m_pRenderer != NULL)
		{
			// ����������
			if (FAILED(m_pRenderer->Init(hWnd, bWindows)))		//FALSE.TRUE
			{
				return -1;
			}
		}
		else
		{//�x����
			MessageBox(0, "�x���F���������Ȃ��ł�", "�x��", MB_OK);
		}
	}
	else
	{//�x����
		MessageBox(0, "�x���F�����������Ă܂�", "�x��", MB_OK);
	}
	//�L�[�{�[�h����
	m_pInputKeyBoard = CInputKeyBoard::Create(hInstance,hWnd);

	//�}�E�X����
	m_pInputMouse = CInputMouse::Create(hInstance, hWnd);

	//NULL�`�F�b�N
	if (m_pSound == NULL)
	{
		//�T�E���h�̓��I�m��
		m_pSound = new CSound;

		//NULL�`�F�b�N
		if (m_pSound != NULL)
		{
			//�T�E���h�̏���������
			m_pSound->InitSound(hWnd);
		}
	}

	//���[�h�̐ݒ�
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�S�Ă̍폜
	CScene::ReleseAll();

	//Sound�@NULL�`�F�b�N
	if (m_pSound != NULL)
	{
		//�T�E���h�̏I������
		m_pSound->UninitSound();
		//�������̉��
		delete m_pSound;
		m_pSound = NULL;
	}

	//Renderer NULL�`�F�b�N
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		//�������̉��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//pCInput NULL�`�F�b�N
	if (m_pInputKeyBoard != NULL)
	{
		// �I������
		m_pInputKeyBoard->Uninit();
		//�������̉��
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//�}�E�XInput�� NULL�`�F�b�N
	if (m_pInputMouse != NULL)
	{
		// �I������
		m_pInputMouse->Uninit();
		//�������̉��
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�X�V����
	m_pInputKeyBoard->Update();

	//�}�E�X�X�V����
	m_pInputMouse->Update();

	// �X�V����
	m_pRenderer->Update();

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	{//���i��false�ɂ��Ă���
		switch (m_mode)
		{
		case MODE_TITLE:	//�^�C�g��
			if (m_pTitle != NULL)
			{
				m_pTitle->Update();
			}
			break;
		case MODE_TUTORIAL:	//�`���[�g���A��
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Update();
			}
			break;
		case MODE_GAME:		//�Q�[��
			if (m_pGame != NULL)
			{
				m_pGame->Update();
			}
			break;
		case MODE_RESULT:	//���U���g
			if (m_pResult != NULL)
			{
				m_pResult->Update();
			}
			break;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �`�揈��
	m_pRenderer->Draw();

	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	//�`��̊J�n
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		switch (m_mode)
		{
		case MODE_TITLE:	//�^�C�g��
			if (m_pTitle != NULL)
			{
				m_pTitle->Draw();
			}
			break;
		case MODE_TUTORIAL:	//�`���[�g���A��
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Draw();
			}
			break;
		case MODE_GAME:		//�Q�[��
			if(m_pGame != NULL)
			{
				m_pGame->Draw();
			}
			break;
		case MODE_RESULT:	//���U���g
			if (m_pResult != NULL)
			{
				m_pResult->Draw();
			}
			break;
		}
		// �`��̏I��
		pDevice->EndScene();
	}
}
//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;

			//�^�C�g���Ȃ��Ƃ߂�
			m_pSound->StopSound(CSound::SOUND_LABEL_TITLEBGM000);
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);

		}
		break;
	case MODE_TUTORIAL:	//�`���[�g���A��
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;

			//�`���[�g���A���̋Ȃ��Ƃ߂�
			m_pSound->StopSound(CSound::SOUND_LABEL_TUTORIALBGM000);
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);
		}
		break;
	case MODE_GAME:		//�Q�[��
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

			//�Q�[���̋Ȃ��Ƃ߂�
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM000);
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;

			//�Q�[���̋Ȃ��Ƃ߂�
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);
		}
		break;
	}
	
	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:	//�^�C�g��
		if (m_pTitle == NULL)
		{//�������𓮓I�m��
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
				//�^�C�g���̋ȗ���
				m_pSound->PlaySound(CSound::SOUND_LABEL_TITLEBGM000);
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	case MODE_TUTORIAL:	//�`���[�g���A��
		if (m_pTutorial == NULL)
		{//�������𓮓I�m��
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init();

				//�`���[�g���A���̋ȗ���
				m_pSound->PlaySound(CSound::SOUND_LABEL_TUTORIALBGM000);
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	case MODE_GAME:		//�Q�[��
		if (m_pGame == NULL)
		{//�������𓮓I�m��
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				m_pGame->Init();
				//�Q�[���̋ȗ���
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM000);
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	case MODE_RESULT:	//���U���g
		if (m_pResult == NULL)
		{//�������𓮓I�m��
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				m_pResult->Init();

				//�Q�[���̋ȗ���
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	}
}