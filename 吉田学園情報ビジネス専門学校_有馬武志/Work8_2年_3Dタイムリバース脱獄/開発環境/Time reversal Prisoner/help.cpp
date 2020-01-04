//=============================================================================
//
// �w���v�̏��� [help.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "help.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_0			"data\\TEXTURE\\�ē�\\�ē�1.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_1			"data\\TEXTURE\\�ē�\\�ē�2.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2			"data\\TEXTURE\\�ē�\\�ē�3.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3			"data\\TEXTURE\\�ē�\\�ē�4.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4			"data\\TEXTURE\\�ē�\\�ē�6.png"		//�ǂݍ��ރe�N�X�`���t�@�C��

#define MAX_HELP				(128)							//�w���v�̍ő吔
#define HELP_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define HELP_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define HELP_SPEED				(0.003f)						//�w���v�X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHelp::m_pTexture[MAX_HELP_TEXTURE] = {};
bool			   CHelp::m_bPause = false;
bool			   CHelp::m_bSerectEnd = false;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CHelp::CHelp(int nPriority,CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_SelectColor = 0.0f;
	m_nCntState = 0;
	m_SelectNum = 0;
	m_nTxtureNumber = 0;
	m_nSize = D3DXVECTOR2(0.0f,0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CHelp::~CHelp()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CHelp::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_SelectNum = 0;
	m_SelectColor = 1.0f;

	// ���_����ݒ�
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(40.0f, 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1240.0f , 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(40.0f, 680.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1240.0f, 680.0f, 0.0f);
	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(HELP_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, HELP_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(HELP_TEXTURE_UV_U, HELP_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CHelp::Uninit(void)
{
	//�I��ł��Ԃ�߂�
	m_bSerectEnd = false;

	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//���g�̍폜
	CScene::Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CHelp::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�t�F�[�h�̃|�C���g
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true || pCInputMouse->GetMouseTrigger(0) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && m_bSerectEnd == false)
	{
		m_bSerectEnd = true;

		//�w���v�����
		CGame::SetHelp(false);

		if (pFade == CFade::FADE_NONE)
		{
			//�w���v�̑I���̌��艹
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CHelp::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//�X�e�[�W�ړ��̍ۂɃe�N�X�`���ύX
	if (pStageNum == CGame::STAGENUM_1)
	{
		m_nTxtureNumber = 0;
	}
	else if (pStageNum == CGame::STAGENUM_2)
	{
		m_nTxtureNumber = 1;
	}
	else if (pStageNum == CGame::STAGENUM_3)
	{
		m_nTxtureNumber = 2;
	}
	else if (pStageNum == CGame::STAGENUM_4)
	{
		m_nTxtureNumber = 3;
	}
	else if (pStageNum == CGame::STAGENUM_5)
	{
		m_nTxtureNumber = 3;
	}
	else if (pStageNum == CGame::STAGENUM_6)
	{
		m_nTxtureNumber = 4;
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexture[m_nTxtureNumber]);
	//pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CHelp * CHelp::Create()
{
	CHelp *pPause = NULL;

	//NULL�`�F�b�N
	if (pPause == NULL)
	{//�������̓��I�m��

		pPause = new CHelp;

		if (pPause != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pPause->Init();
		}
	}

	return pPause;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CHelp::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_3, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_4, &m_pTexture[4]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CHelp::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_HELP_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}