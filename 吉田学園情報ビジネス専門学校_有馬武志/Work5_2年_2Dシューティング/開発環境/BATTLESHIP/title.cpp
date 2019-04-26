//=============================================================================
//
// �����̏��� [title.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "title.h"
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
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = {};

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	m_nCnt = 0;
	m_nCount = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{

}
//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CTitle::Load(void)
{
	return S_OK;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTitle::Init()
{
	//�w�i�e�N�X�`���̐���
	CBg::Load();

	//���S�e�N�X�`���̐���
	CLogo::Load();

	////�w�i�̐���
	CBg::Create(3);
	CBg::Create(7);
	CBg::Create(6);
	CBg::Create(9);
	CBg::Create(8);

	//���S�̐���
	for (int nCount = 0; nCount < 10; nCount++)
	{
		CLogo::Create(D3DXVECTOR3(140.0f + nCount * 110.0f, -150.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), nCount);
	}

	//���
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH - 170.0f, 550.0f, 0.0f), D3DXVECTOR2(200.0f, 110.0f), 11);

	//�G���^�[�w��
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR2(300.0f, 70.0f), 10);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	//�w�i�e�N�X�`���̔j��
	CBg::UnLoad();

	//���S�e�N�X�`���̔j��
	CLogo::UnLoad();

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
void CTitle::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�t�F�[�h�̃|�C���g
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardAny(1) == true || pCInputMouse->GetMouseTrigger(0) == true)
	{//�^�C�g������Q�[����
		if (m_nCount >= 1)
		{
			//�t�F�[�h���n�܂�����
			if (pFade == CFade::FADE_NONE)
			{
				//�^�C�g���ȗ���
				pSound->PlaySound(CSound::SOUND_LABEL_ENTERSE);
			}
			CFade::Create(CManager::MODE_TUTORIAL);
		}
		m_nCount++;
	}

	//�퓬�@
	if (m_nCnt == 260)
	{
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH + 50.0f, 100.0f + rand()%200 * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 12);

		if (rand() % 2 == 0)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH + rand()%300 * 1.0f, 100.0f + rand() % 200 * 1.0f, 0.0f), D3DXVECTOR2(13.0f, 5.0f), 12);
		}
	}
	else if(m_nCnt >= 261)
	{
		m_nCnt = 0;
	}

	m_nCnt++;
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	
}
//=============================================================================
// �e�N�X�`���̊J������
//=============================================================================
void CTitle::UnLoad(void)
{

}
