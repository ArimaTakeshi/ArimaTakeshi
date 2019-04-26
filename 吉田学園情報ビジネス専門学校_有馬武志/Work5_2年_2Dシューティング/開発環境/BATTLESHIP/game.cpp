//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "game.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "gan.h"
#include "number.h"
#include "score.h"
#include "effect.h"
#include "time.h"
#include "polygon.h"
#include "fade.h"
#include "life.h"
#include "fram.h"
#include "2Dobject.h"
#include "pause.h"
#include "string.h"
#include "pause.h"
#include "logo.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_HP		(200)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBullet *CGame::m_pBullet = NULL;
CExplosion *CGame::m_pExplosion = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CGan *CGame::m_pGan = NULL;
CBg *CGame::m_pBg = NULL;
CFram *CGame::m_pFram = NULL;
CNumber *CGame::m_pNumber = NULL;
C2DObject *CGame::m_p2DObject = NULL;
//CString *CGame::m_pString = NULL;
CGame::GAMESTATE CGame::m_gameState = GAMESTATE_NONE;
CPause *CGame::m_pPause = NULL;
bool CGame::m_bPause = false;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_gameState = GAMESTATE_NONE;
	m_nCounterGameState = 0;
	m_NowGameState = GAMESTATE_NONE;
	CGame::GetPlayer() = NULL;
	m_bPause = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGame::Init()
{
	////NULL�`�F�b�N
	//if (m_pString == NULL)
	//{
	//	//Stiring�̓��I�m��
	//	m_pString = new CString;

	//	if (m_pString != NULL)
	//	{
	//		m_pString->Init();
	//	}
	//}

	//�v���C���[�̃e�N�X�`���̓ǂݍ���
	m_pPlayer->Load();

	m_pEnemy->Load();

	//�e�̃e�N�X�`���̓ǂݍ���
	m_pBullet->Load();

	//�����̃e�N�X�`���̓ǂݍ���
	m_pExplosion->Load();

	//�w�i�̃e�N�X�`���̓ǂݍ���
	m_pBg->Load();

	//�e�̃e�N�X�`���̓ǂݍ���
	m_pGan->Load();

	//�g�̃e�N�X�`���̓ǂݍ���
	m_pFram->Load();

	//�����̃e�N�X�`���̓ǂݍ���
	m_pNumber->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_p2DObject->Load();

	//�|�[�Y�̃e�N�X�`���̓ǂݍ���
	m_pPause->Load();

	//�G�t�F�N�g�̃e�N�X�`���ǂݍ���
	CEffect::Load();

	//�|���S���̃e�N�X�`���ǂݍ���
	CPolygon::Load();

	//�t�F�[�h�̃e�N�X�`���̓ǂݍ���
	CFade::Load();

	//�̗͂̃e�N�X�`���̓ǂݍ���
	CLife::Load();

	//���S�̃e�N�X�`���̓ǂݍ���
	CLogo::Load();

	//�I�u�W�F�N�g�̐���
	//C2DObject::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 0, 20);

	//�g����
	CFram::Create(4);
	CFram::Create(3);
	CFram::Create(2);
	CFram::Create(1);
	CFram::Create(0);

	//�w�i����
	CBg::Create(0);
	CBg::Create(1);
	CBg::Create(2);

	//�̗͂̐���
	CLife::Create();

	//�X�R�A�̐���
	CScore::Create();

	//�^�C���̐���
	CTime::Create();

	//���݂̏e�̕\��
	CGan::Create(D3DXVECTOR2(100.0f, 120.0f), CGan::GANTYPE_PLAYER, CGan::GAN_CANNON, 1);

	//�D���̉摜
	CLogo::Create(D3DXVECTOR3(1400.0f, 130.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 18);
	CLogo::Create(D3DXVECTOR3(1450.0f, 295.0f, 0.0f), D3DXVECTOR2(140.0f, 100.0f), 20);

	//�N���X�w�A
	CLogo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 31);

	//�v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR2(25, 85), PLAYER_HP);
	//CDamage::Create();

	//�G�̐���
	CEnemy::CreateEnemy();

	////SetString("���͂��镶��",rect { X, Y ,��, ����},0,�J���[);
	//m_pString->SetString("�v���C���[�O�ړ�", { 10,10,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("�v���C���[��ړ�", { 10,30,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("�v���C���[���ړ�", { 10,50,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("�v���C���[�E�ړ�", { 10,70,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("��C", { 10,90,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("�΋�C", { 10,110,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString("����", { 10,130,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	////SetString("���͂��镶��",rect { X, Y ,��, ����},0,�J���[);
	//m_pString->SetString(":  [ W ]", { 110,10,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ S ]", { 110,30,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ A ]", { 110,50,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ D ]", { 110,70,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ 1 ]", { 110,90,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ 2 ]", { 110,110,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//m_pString->SetString(":  [ 3 ]", { 110,130,0,0 }, 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_gameState = GAMESTATE_NORMAL;	//�ʏ��Ԃ�

	//�|�[�Y��������
	m_bPause = false;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	//�|�[�Y�폜
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	//�v���C���[�e�N�X�`���̔j��
	m_pPlayer->UnLoad();

	//�G�̃e�N�X�`���̔j��
	m_pEnemy->UnLoad();

	//�e�̃e�N�X�`���̔j��
	m_pBullet->UnLoad();

	//�����̃e�N�X�`���̔j��
	m_pExplosion->UnLoad();

	//�w�i�̃e�N�X�`���̔j��
	m_pBg->UnLoad();

	//�g�̃e�N�X�`���̔j��
	m_pFram->UnLoad();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_p2DObject->UnLoad();

	//�e�̃e�N�X�`���̔j��
	m_pGan->UnLoad();

	//�����̃e�N�X�`���̔j��
	m_pNumber->UnLoad();

	//�|�[�Y�̃e�N�X�`���̔j��
	m_pPause->UnLoad();

	//�̗͂̃e�N�X�`���̔j��
	CLife::UnLoad();

	//�|���S���̃e�N�X�`���̔j��
	CPolygon::UnLoad();

	//�t�F�[�h�̃e�N�X�`���̔j��
	CFade::UnLoad();

	//�G�t�F�N�g�̃e�N�X�`���̔j��
	CEffect::UnLoad();

	//���S�̃e�N�X�`���̔j��
	CLogo::UnLoad();

	//�`��D���1�ԍŏ��ȊO�̂��ׂĂ��폜
	for (int nCnPri = 0; nCnPri < NUM_PRIORITY - 1; nCnPri++)
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

	////�����̏I������
	//if (m_pString != NULL)
	//{
	//	m_pString->Uninit();
	//	delete m_pString;
	//	m_pString = NULL;
	//}
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//m_pString->Update();

	//�|�[�Y�̏���
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_P) == true)
	{//P�L�[�������ꂽ��

		m_bPause = m_bPause ? false : true;

		switch (m_bPause)
		{
		case true:
			if (m_pPause == NULL)
			{
				//�|�[�Y���J����
				pSound->PlaySound(CSound::SOUND_LABEL_PAUSE000);

				//�|�[�Y�̐���
				m_pPause = CPause::Create();

				//�|�[�Y�ƃt�F�[�h������
				CScene::SetUpdatePri(7);
			}
			break;
		case false:
			if (m_pPause != NULL)
			{
				//�|�[�Y����鉹
				pSound->PlaySound(CSound::SOUND_LABEL_PAUSE001);

				//�|�[�Y���폜
				m_pPause->Uninit();
				m_pPause = NULL;

				//�A�b�v�f�[�g���Ԃ����ׂĉ�
				CScene::SetUpdatePri(0);
			}
		}
	}
	if (m_pPause == false)
	{//�J����
	 //���݂̏�Ԃ�ۑ�
		m_NowGameState = GetGameState();

		switch (m_NowGameState)
		{
		case GAMESTATE_NORMAL:	//�ʏ�̏��
			break;
		case GAMESTATE_CLEAR:	//�Q�[�����N���A�������
			m_nCounterGameState++;

			if (m_nCounterGameState >= 60)
			{//��ʁi���[�h�j�̐ݒ�
				CFade::Create(CManager::MODE_RESULT);
			}
			break;
		case GAMESTATE_OVER:	//�Q�[���ŕ������Ƃ��̏��
			m_nCounterGameState++;

			if (m_nCounterGameState >= 60)
			{//��ʁi���[�h�j�̐ݒ�
				CFade::Create(CManager::MODE_RESULT);
			}
			break;
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	//m_pString->Draw();
}
//=============================================================================
//
//=============================================================================
void CGame::SetPause(bool bPause)
{
	m_bPause = bPause;

	switch (m_bPause)
	{
	case true:
		if (m_pPause == NULL)
		{
			//�|�[�Y�̐���
			m_pPause = CPause::Create();

			CScene::SetUpdatePri(7);
		}
		break;
	case false:
		if (m_pPause != NULL)
		{
			m_pPause->Uninit();
			m_pPause = NULL;

			CScene::SetUpdatePri(0);
		}
	}
}
