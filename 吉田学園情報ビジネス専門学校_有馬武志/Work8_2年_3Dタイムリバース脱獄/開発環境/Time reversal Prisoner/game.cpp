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
#include "fade.h"
#include "pause.h"
#include "logo.h"
#include "sound.h"
#include "billboord.h"
#include "meshfield.h"
#include "object.h"
#include "fade.h"
#include "effect.h"
#include "time.h"
#include "wall.h"
#include "ground.h"
#include "item.h"
#include "shadow.h"
#include "enemy.h"
#include "life.h"
#include "gauge.h"
#include "distance.h"
#include "guide.h"
#include "action2D.h"
#include "blood.h"
#include "serect.h"
#include "spotlight.h"
#include "objectshadow.h"
#include "help.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�X�e�[�W�P
#define TEXT_OBJECTNAME1		"data\\TEXT\\�X�e�[�W1\\objecy.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_MESHFIELDNAME1		"data\\TEXT\\�X�e�[�W1\\meshfield.txt"		// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_WALLNAME1			"data\\TEXT\\�X�e�[�W1\\wall.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��

//�X�e�[�W�Q
#define TEXT_OBJECTNAME2		"data\\TEXT\\�X�e�[�W2\\objecy.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_MESHFIELDNAME2		"data\\TEXT\\�X�e�[�W2\\meshfield.txt"		// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_WALLNAME2			"data\\TEXT\\�X�e�[�W2\\wall.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��

//�X�e�[�W�R
#define TEXT_OBJECTNAME3		"data\\TEXT\\�X�e�[�W3\\objecy.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_MESHFIELDNAME3		"data\\TEXT\\�X�e�[�W3\\meshfield.txt"		// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_WALLNAME3			"data\\TEXT\\�X�e�[�W3\\wall.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��

//�X�e�[�W�S
#define TEXT_OBJECTNAME4		"data\\TEXT\\�X�e�[�W4\\objecy.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_MESHFIELDNAME4		"data\\TEXT\\�X�e�[�W4\\meshfield.txt"		// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_WALLNAME4			"data\\TEXT\\�X�e�[�W4\\wall.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��

//�X�e�[�W�T
#define TEXT_OBJECTNAME5		"data\\TEXT\\�X�e�[�W5\\objecy.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_MESHFIELDNAME5		"data\\TEXT\\�X�e�[�W5\\meshfield.txt"		// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_WALLNAME5			"data\\TEXT\\�X�e�[�W5\\wall.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��

//�X�e�[�W�U
#define TEXT_OBJECTNAME6		"data\\TEXT\\�X�e�[�W6\\objecy.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_MESHFIELDNAME6		"data\\TEXT\\�X�e�[�W6\\meshfield.txt"		// �ǂݍ��ރe�L�X�g�t�@�C��
#define TEXT_WALLNAME6			"data\\TEXT\\�X�e�[�W6\\wall.txt"			// �ǂݍ��ރe�L�X�g�t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CGame::m_pPlayer = NULL;
CBullet *CGame::m_pBullet = NULL;
CNumber *CGame::m_pNumber = NULL;
CBillBoord *CGame::m_pBillBoord = NULL;
CPolygon3D *CGame::m_pPolygon3D = NULL;
CMeshField *CGame::m_pMeshField = NULL;
CObject *CGame::m_pObject = NULL;
CPause *CGame::m_pPause = NULL;
CHelp *CGame::m_pHelp = NULL;
CModel *CGame::m_pModel = NULL;
CEffect *CGame::m_pEffect = NULL;
CWall *CGame::m_pWall = NULL;
CGround *CGame::m_pGround = NULL; 
CShadow *CGame::m_pShadow = NULL;
CSpotLight *CGame::m_pSpotLight = NULL;
CItem *CGame::m_pItem = NULL;
CEnemy *CGame::m_pEnemy = NULL;
CDummyEnemy *CGame::m_pDummyEnemy = NULL;
CDummyPlayer *CGame::m_pDummyPlayer = NULL;
CObjectShadow *CGame::m_pObjectShadow = NULL;

bool CGame::m_bHelp = false;
bool CGame::m_bPause = false;
CGame::GAMESTATE CGame::m_gameState = GAMESTATE_NONE;
int	CGame::m_nCntSetStage = 0;								// �X�e�[�W�Z�b�g�J�E���^
CGame::STAGENUM CGame::m_StageState = STAGENUM_1;			// �X�e�[�W���

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
	m_gameState = GAMESTATE_NONE;
	m_nCounterGameState = 0;
	m_NowGameState = GAMESTATE_NONE;
	CGame::GetPlayer() = NULL;
	m_StageState = STAGENUM_1;			// �X�e�[�W���
	m_nCntSetStage = 0;
	m_bPause = false;
	m_nEnemyCount = 0;
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
	//===================================
	//		 Load�̓ǂݍ��ݏꏊ
	//===================================
	//2D�摜�e�N�X�`���̓ǂݍ���
	CLogo::Load();

	//�t�F�[�h�̃e�N�X�`���̓ǂݍ���
	CFade::Load();

	//���C�t�̃e�N�X�`���̓ǂݍ���
	CLife::Load();

	//�Q�[�W�̃e�N�X�`���̓ǂݍ���
	CGauge::Load();

	//�ē��̃e�N�X�`���̓ǂݍ���
	CGuide::Load();

	//�A�N�V�����X�L���g�p���̃e�N�X�`���̓ǂݍ���
	CAction2D::Load();

	//�Z���N�g�̃e�N�X�`���̓ǂݍ���
	m_pPause->Load();

	//�w���v�̃e�N�X�`���̓ǂݍ���
	m_pHelp->Load();

	//���b�V���t�B�[���h�̃e�N�X�`���̓ǂݍ���
	m_pMeshField->Load();

	//�r���{�[�h�e�N�X�`���̓ǂݍ���
	m_pBillBoord->Load();

	//�e�̃e�N�X�`���̓ǂݍ���
	m_pBullet->Load();

	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	//�v���C���[�̃e�N�X�`���̓ǂݍ���
	//m_pPlayer->Load();

	//�G�t�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pEffect->Load();

	//�n�ʂ̃e�N�X�`���̓ǂݍ���
	m_pGround->Load();

	//�ǂ̃e�N�X�`���̓ǂݍ���
	m_pWall->Load();

	//�A�C�e���̃e�N�X�`���ǂݍ���
	m_pItem->Load();

	//�e�̃e�N�X�`���ǂݍ���
	m_pShadow->Load();

	//�X�|�b�g���C�g���̓ǂݍ���
	m_pSpotLight->Load();

	//�X�e���V���V���h�E�̓ǂݍ���
	m_pObjectShadow->Load();

	//�����̐����@�q�[�v���Ă�
	//CDistance::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f));

	//�Q�[�W�p�g
	CLogo::Create(D3DXVECTOR3(310.0f, 30.0f, 0.0f), D3DXVECTOR2(183.0f, 17.0f), 4, 1);
	CLogo::Create(D3DXVECTOR3(265.0f, 60.0f, 0.0f), D3DXVECTOR2(197.0f * 0.8f, 17.0f* 0.8f), 4, 1);

	//�Q�[�W�̐���
	CGauge::Create(D3DXVECTOR3(122.0f, 50.0f, 0.0f));

	//���C�t�̐���
	CLife::Create(D3DXVECTOR3(140.0f, 15.0f, 0.0f));

	//���S��\��
	CLogo::Create(D3DXVECTOR3(1180.0f, 100.0f, 0.0f), D3DXVECTOR2(90.0f, 90.0f), 4, 0);
	CLogo::Create(D3DXVECTOR3(1180.0f, 100.0f, 0.0f), D3DXVECTOR2(80.0f, 80.0f), 0, 0);
	CLogo::Create(D3DXVECTOR3(1180.0f, 163.0f, 0.0f), D3DXVECTOR2(80.0f, 20.0f), 5, 0);
	CLogo::Create(D3DXVECTOR3(160.0f, 620.0f, 0.0f), D3DXVECTOR2(160.0f, 90.0f), 9, 0);

	//�}�b�v
	CGuide::Create(D3DXVECTOR3(1180.0f, 500.0f, 0.0f), D3DXVECTOR2(90.0f, 200.0f), 7);
	CGuide::Create(D3DXVECTOR3(1180.0f, 270.0f, 0.0f), D3DXVECTOR2(80.0f, 30.0f), 8);
	CGuide::Create(D3DXVECTOR3(1130.0f, 665.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 9);
	CGuide::Create(D3DXVECTOR3(77.0f, 68.0f, 0.0f), D3DXVECTOR2(80.0f, 68.0f), 10);

	//�v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f));

	//�I�u�W�F�N�g�e�̐���		
	m_pObjectShadow = CObjectShadow::Create(D3DXVECTOR3(0.0f, 0.0f, -300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, CModel3D::MOVETYPE_NOT, 0);

	//�r���{�[�h����
	//m_pBillBoord = CBillBoord::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30,30),0);

	//�A�C�e���̐���
	//m_pItem = CItem::Create(D3DXVECTOR3(0, 50.0f, 600.0f), 0);

	//�ʏ��Ԃ�
	m_gameState = GAMESTATE_NORMAL;	

	//�ǂ��̃X�e�[�W����J�n���邩
	m_nCntSetStage = 0;			

	//�G�̐�������
	m_nEnemyCount = 0;

	//�J�n�X�e�[�W
	m_StageState = STAGENUM_1;			// �X�e�[�W���

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

	if (m_pHelp != NULL)
	{
		m_pHelp->Uninit();
		m_pHelp = NULL;
	}

	//===================================
	//	�@�@UnLoad�̔j������ꏊ
	//===================================
	//�Z���N�g�̃e�N�X�`���̔j��
	m_pPause->UnLoad();

	m_pHelp->UnLoad();

	//���b�V���t�B�[���h�e�N�X�`���̔j��
	m_pMeshField->UnLoad();

	//2D�摜�e�N�X�`���̔j��
	CLogo::UnLoad();

	//�t�F�[�h�̃e�N�X�`���̔j��
	CFade::UnLoad();

	//���C�t�̃e�N�X�`���̔j��
	CLife::UnLoad();

	//�Q�[�W�̃e�N�X�`���̔j��
	CGauge::UnLoad();

	//�ē��̃e�N�X�`���̔j��
	CGuide::UnLoad();

	//�A�N�V�����X�L���g�p���̃e�N�X�`���̔j��
	CAction2D::UnLoad();

	//�r���{�[�h�e�N�X�`���̔j��
	m_pBillBoord->UnLoad();

	//�e�̃e�N�X�`���̔j��
	m_pBullet->UnLoad();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->UnLoad();

	//�v���C���[�̃e�N�X�`���̔j��
	//m_pPlayer->UnLoad();

	//�G�t�F�N�g�̃e�N�X�`���̔j��
	m_pEffect->UnLoad();

	//�n�ʂ̃e�N�X�`���̔j��
	m_pGround->UnLoad();

	//�ǂ̃e�N�X�`���̔j��
	m_pWall->UnLoad();

	//�A�C�e���̃e�N�X�`���j��
	m_pItem->UnLoad();

	//�e�̃e�N�X�`���̔j��
	m_pShadow->UnLoad();

	//�X�|�b�g���C�g���̔j��
	m_pSpotLight->UnLoad();

	//�X�e���V���V���h�E�̔j��
	m_pObjectShadow->UnLoad();

	//���b�V���t�B�[���h�̔j��
	m_pMeshField->Uninit();
	m_pMeshField = NULL;

	//�t�F�[�h�ȊO�̔j��
	CScene::NotFadeReleseAll();
}
//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	if (m_StageState == 1)
	{
		CDebugProc::Print("���݂̃X�e�[�W = 1\n");
	}
	else if (m_StageState == 2)
	{
		CDebugProc::Print("���݂̃X�e�[�W = 2\n");
	}
	else if (m_StageState == 3)
	{
		CDebugProc::Print("���݂̃X�e�[�W = 3\n");
	}
	else if (m_StageState == 4)
	{
		CDebugProc::Print("���݂̃X�e�[�W = 4\n");
	}
	else if (m_StageState == 5)
	{
		CDebugProc::Print("���݂̃X�e�[�W = 5\n");
	}
	else if (m_StageState == 6)
	{
		CDebugProc::Print("���݂̃X�e�[�W = 6\n");
	}


	if (m_pPause == false || m_pPause == false)
	{//�J����
		//���݂̏�Ԃ�ۑ�
		m_NowGameState = GetGameState();

		switch (m_NowGameState)
		{
		case GAMESTATE_NORMAL:	//�ʏ�̏��
			
			//�X�e�[�W�ݒ�
			SetStage();

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

	//�|�[�Y�̏���
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_P) == true && m_pPlayer->GetDie() == false || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_START) == true && m_pPlayer->GetDie() == false && CPause::GetPauseEnd() == false && CSerect::GetSelectEnd() == false)
	{//P�L�[�������ꂽ��

		m_bPause = m_bPause ? false : true;

		switch (m_bPause)
		{
		case true:
			if (m_pPause == NULL)
			{
				if (CPlayer::GetCancelStageNext() == false)
				{
					//�|�[�Y���J����
					pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_OPEN);

					//�|�[�Y�̐���
					m_pPause = CPause::Create();

					//�|�[�Y�ƃt�F�[�h������
					CScene::SetUpdatePri(7);
				}
			}
			break;
		case false:
			if (m_pPause != NULL)
			{
				//�|�[�Y����鉹
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_CLOSE);

				//�|�[�Y���폜
				m_pPause->Uninit();
				m_pPause = NULL;

				//�A�b�v�f�[�g���Ԃ����ׂĉ�
				CScene::SetUpdatePri(0);
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{
	
}
//=============================================================================
// �|�[�Y�����������ǂ���
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
//=============================================================================
// �w���v�̕\��
//=============================================================================
void CGame::SetHelp(bool bHelp)
{
	m_bHelp = bHelp;

	switch (m_bHelp)
	{
	case true:
		if (m_pHelp == NULL)
		{
			//�|�[�Y�̐���
			m_pHelp = CHelp::Create();

			CScene::SetUpdatePri(7);
		}
		break;
	case false:
		if (m_pHelp != NULL)
		{
			m_pHelp->Uninit();
			m_pHelp = NULL;

			CScene::SetUpdatePri(0);
		}
	}
}
//=============================================================================
// �X�e�[�W���
//=============================================================================
void CGame::SetNumState(STAGENUM stagenum)
{
	m_StageState = stagenum;
}
//=============================================================================
// �Q�[���ݒ菈��
//=============================================================================
void CGame::SetStageState(STAGENUM stage)
{
	CCamera *pCamera = CManager::GetCamera();

	//�폜���鏈��
	if (m_StageState != stage)
	{
		//m_pPlayer->ResetPlayer();
		pCamera->DeleteCamera();
		m_pWall->DeleteWall();
		m_pObject->DeleteObject();
		m_pEnemy->DeleteEnemy();
		m_pBillBoord->ResetBillboord();
		m_pMeshField->DeleteMeshField();
		m_pGround->DeleteGround();
	}

	//��Ԃ��L��
	m_StageState = stage;

	//�폜���鏈��
	if (m_StageState == stage)
	{
		m_pPlayer->ResetPlayer();
	}
	m_nCntSetStage = 0;
}
//=============================================================================
// �X�e�[�W�ݒ�
//=============================================================================
void CGame::SetStage(void)
{
	//�T�E���h�̃|�C���^
	CSound *pSound = CManager::GetSound();

	if (m_nCntSetStage == 0)
	{
		//=====================================================================
		//	�X�e�[�W1 ��3���e��
		//=====================================================================
		if (m_StageState == STAGENUM_1)
		{
			//�w���v�̕\��
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//�ē��̕\��
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 1);

			//���ē�
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3,1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//�ē��p
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//�`���[�g���A��
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 10, 0);

			//�}�b�v��ǂݍ���
			TextLoad(1);
			WallTextLoad(1);
			MeshTextLoad(1);

			//�G�̐���
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-125.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f,0.0f,0.0f), 0);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(120.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_G);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-120.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_B);
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(125.0f, 0.0f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-150.0f, 0.0f, 300.0f));

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//�ǂ̐���		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//�t�B�[���h�̐���		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//====================================================================
		//	�X�e�[�W2 �S�K�w�H��
		//====================================================================
		else if (m_StageState == STAGENUM_2)
		{
			//�w���v�̕\��
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//�ē��̕\��
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 2);

			//���ē�
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//�ē��p
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//�`���[�g���A��
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 11, 0);

			//�}�b�v��ǂݍ���
			TextLoad(2);
			MeshTextLoad(2);
			WallTextLoad(2);

			//�G�̐���
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-100.0f, 0.0f, 300.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_X_R);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(370.0f, 0.0f, 100.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_Z_B);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-370.0f, 0.0f, -100.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_Z_G);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//�ǂ̐���		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
		}
		//=======================================================================
		//	�X�e�[�W3�@���l�p�L��
		//=======================================================================
		else if (m_StageState == STAGENUM_3)
		{
			//�w���v�̕\��
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//�ē��̕\��
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 3);

			//�ē��p
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//�`���[�g���A��
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 12, 0);

			//���ē�
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, -130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(400.0f, 5.0f, 70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(400.0f, 5.0f, 610.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(750.0f, 65.0f, 590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//�}�b�v��ǂݍ���
			TextLoad(3);
			WallTextLoad(3);
			MeshTextLoad(3);

			//�G�̐���
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 600.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 0, CEnemy::MOVE_Z_B);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(400.0f, 0.0f, 730.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(300.0f, 0.0f, -110.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_X_L);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//�ǂ̐���		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//�t�B�[���h�̐���		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//=======================================================================
		//	�X�e�[�W4�@���l�R���H
		//=======================================================================
		else if (m_StageState == STAGENUM_4)
		{
			//�w���v�̕\��
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//�ē��̕\��
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 4);

			//���ē�
			m_pGround = CGround::Create(D3DXVECTOR3(100.0f, 5.0f, -200.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(400.0f, 5.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(900.0f, 5.0f, -170.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(880.0f, 5.0f, 420.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(506.0f, 112.0f, 455.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//�ē��p
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//�`���[�g���A��
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 13, 0);

			//�}�b�v��ǂݍ���
			TextLoad(4);
			WallTextLoad(4);
			MeshTextLoad(4);

			//�G�̐���
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(320.0f, 0.0f, 5.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(657.0f, 0.0f, -42.0f),  D3DXVECTOR3(0.0f,0.0f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(1040.0f, 0.0f, 17.0f),  D3DXVECTOR3(0.0f,-1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(936.0f, 0.0f, 510.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);

			//�댯�ꏊ
			m_pGround = CGround::Create(D3DXVECTOR3(350.0f, 2.0f, 40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(145.0f, 50.0f), 0, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(640.0f, 2.0f, -165.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(145.0f, 50.0f), 0, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(645.0f, 2.0f, -330.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(140.0f, 65.0f), 0, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(925.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(165.0f, 70.0f), 0, 0);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//�ǂ̐���		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//�t�B�[���h�̐���		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//=======================================================================
		//	�X�e�[�W5�@����
		//=======================================================================
		else if (m_StageState == STAGENUM_5)
		{
			//�w���v�̕\��
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//�ē��̕\��
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 5);

			//���ē�
			m_pGround = CGround::Create(D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-160.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-160.0f, 5.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-760.0f, 5.0f, 290.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);
		
			//�ē��p
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//�}�b�v��ǂݍ���
			TextLoad(5);
			WallTextLoad(5);
			MeshTextLoad(5);

			//�G�̐���
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-730.0f, 0.0f, 110.0f), D3DXVECTOR3(0.0f,1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-760.0f, 0.0f, 520.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(240.0f, 0.0f, 400.0f),  D3DXVECTOR3(0.0f,3.14f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-340.0f, 0.0f, 200.0f),  D3DXVECTOR3(0.0f,-1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-400.0f, 0.0f, -100.0f),  D3DXVECTOR3(0.0f,1.57f,0.0f), 1, CEnemy::MOVE_STOP);

			//�댯�ꏊ
			m_pGround = CGround::Create(D3DXVECTOR3(-350.0f, 2.0f, 90.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 380.0f), 0, 0);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//�ǂ̐���		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//�t�B�[���h�̐���		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}
		//=======================================================================
		//	�X�e�[�W6�@�^����
		//=======================================================================
		else if (m_StageState == STAGENUM_6)
		{
			//�w���v�̕\��
			SetHelp(true);

			m_pPlayer->SetCancelStageNext(false);
			m_pPlayer->SetActionFade(false);

			//�ē��̕\��
			CGuide::Create(D3DXVECTOR3(0.0f, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);
			CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH + (SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 + 200.0f, 0.0f), D3DXVECTOR2(400.0f, 45.0f), 6);

			//���ē�
			m_pGround = CGround::Create(D3DXVECTOR3(-265.0f, 5.0f, 1240.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-340.0f, 5.0f, 950.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR2(50.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-470.0f, 5.0f, 950.0f), D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 1);
			m_pGround = CGround::Create(D3DXVECTOR3(-480.0f, 5.0f, -1170.0f), D3DXVECTOR3(0.0f, 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0, 0.0f), D3DXVECTOR2(45.0f, 20.0f), 3, 2);

			//�ē��p
			pSound->PlaySound(CSound::SOUND_LABEL_SE_INTRODUCTION);

			//�`���[�g���A��
			CLogo::Create(D3DXVECTOR3(160.0f, 410.0f, 0.0f), D3DXVECTOR2(160.0f, 110.0f), 14, 0);

			//�}�b�v��ǂݍ���
			TextLoad(6);
			WallTextLoad(6);
			MeshTextLoad(6);

			//�B���]�[��
			m_pGround = CGround::Create(D3DXVECTOR3(-550.0f, 2.0f, 75.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-454.0f, 2.0f, 385.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(60.0f, 50.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-454.0f, 2.0f, 670.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(60.0f, 50.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-477.5f, 2.0f, -275.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(85.0f, 20.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-527.5f, 2.0f, -585.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(135.0f, 20.0f), 1, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-507.5f, 2.0f, -1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(135.0f, 20.0f), 1, 0);

			//���C�g�]�[��
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, -1150.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, -650.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, 300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);
			m_pGround = CGround::Create(D3DXVECTOR3(-670.0f, 0.8f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(280.0f, 80.0f), 2, 0);

			//�G�̐���
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-900.0f, 0.0f, 1250.0f),  D3DXVECTOR3(0.0f,-1.57f,0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-895.0f, 0.0f, 1080.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-680.0f, 0.0f, 530.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_G);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-800.0f, 0.0f, 190.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_B);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-700.0f, 0.0f, -440.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-630.0f, 0.0f, -1190.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), 1, CEnemy::MOVE_STOP);
			m_pEnemy = CEnemy::Create(D3DXVECTOR3(-645.0f, 0.0f, 1080.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_X_R);
			
			//�ނ������邽�߃R�����g�A�E�g
			//m_pEnemy = CEnemy::Create(D3DXVECTOR3(-410.0f, 0.0f, -590.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0, CEnemy::MOVE_Z_G);

			for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
			{
				//�I�u�W�F�N�g�̐���		
				m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
			}
			for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
			{
				//�ǂ̐���		
				m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
			}
			for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
			{
				//�t�B�[���h�̐���		
				m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
			}
		}

		m_nCntSetStage = 1;
	}
}
//===============================================================================
// �t�@�C�����烍�[�h
//===============================================================================
void CGame::TextLoad(int nLoadNumber)
{
	//�t�@�C���p�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�

	//�t�@�C���|�C���^�̏���������
	pFile = NULL;

	//�ǂ̃X�e�[�W��ǂݍ��ނ�
	int nStageLoadNumber = nLoadNumber;

	//�t�@�C���̓ǂݍ��ݐ��ύX
	switch (nStageLoadNumber)
	{
	case 1:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_OBJECTNAME1, "r");
		break;
	case 2:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_OBJECTNAME2, "r");
		break;
	case 3:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_OBJECTNAME3, "r");
		break;
	case 4:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_OBJECTNAME4, "r");
		break;
	case 5:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_OBJECTNAME5, "r");
		break;
	case 6:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_OBJECTNAME6, "r");
		break;
	}

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//������̐擪��ݒ�
		pStrcur = ReadLine(pFile, &aLine[0]);
		//����������o��
		strcpy(aStr, pStrcur);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStrcur, "OBJECT_SETNUM = ", strlen("OBJECT_SETNUM = ")) == 0)
		{
			//���o��
			pStrcur += strlen("OBJECT_SETNUM = ");
			//������̐擪��ݒ�
			strcpy(aStr, pStrcur);
			//�����񔲂��o��
			m_nSetObjectNum = atoi(pStrcur);
		}

		//�I�u�W�F�N�g�̐�����
		for (int nCntObject = 0; nCntObject < m_nSetObjectNum; nCntObject++)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "OBJECT_START", strlen("OBJECT_START")) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);

					//��ނ̂�ǂݍ���
					if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
					{
						//���o��
						pStrcur += strlen("TYPE = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Map[nCntObject].m_nType = atoi(pStrcur);
					}
					//��ނ̂�ǂݍ���
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//���o��
						pStrcur += strlen("TEXTURETYPE = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Map[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//�����蔻���ǂݍ���
					if (memcmp(pStrcur, "COLLISION = ", strlen("COLLISION = ")) == 0)
					{
						//���o��
						pStrcur += strlen("COLLISION = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Map[nCntObject].m_nCollision = atoi(pStrcur);
					}
					//POS��ǂݍ���
					if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("POS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Map[nCntObject].m_pos.x = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Map[nCntObject].m_pos.y = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Map[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					//ROT��ǂݍ���
					if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("ROT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Map[nCntObject].m_rot.x = (float)atof(pStrcur);

						//���������i�߂�
						pStrcur += nWord;
						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Map[nCntObject].m_rot.y = (float)atof(pStrcur);

						//���������i�߂�
						pStrcur += nWord;
						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Map[nCntObject].m_rot.z = (float)atof(pStrcur);
					}
					else if (memcmp(pStrcur, "OBJECT_END", strlen("OBJECT_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}

	//m_pMarkObject->SetObjectNum(CMarkObject::GetObjectNum() + m_nSetObjectNum);
}
//===============================================================================
// ���b�V���t�B�[���h���t�@�C�����烍�[�h
//===============================================================================
void CGame::MeshTextLoad(int nLoadNumber)
{
	//�t�@�C���p�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�

	//�t�@�C���|�C���^�̏���������
	pFile = NULL;

	//�ǂ̃X�e�[�W��ǂݍ��ނ�
	int nStageLoadNumber = nLoadNumber;

	//�t�@�C���̓ǂݍ��ݐ��ύX
	switch (nStageLoadNumber)
	{
	case 1:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_MESHFIELDNAME1, "r");
		break;
	case 2:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_MESHFIELDNAME2, "r");
		break;
	case 3:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_MESHFIELDNAME3, "r");
		break;
	case 4:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_MESHFIELDNAME4, "r");
		break;
	case 5:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_MESHFIELDNAME5, "r");
		break;
	case 6:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_MESHFIELDNAME6, "r");
		break;
	}

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//������̐擪��ݒ�
		pStrcur = ReadLine(pFile, &aLine[0]);
		//����������o��
		strcpy(aStr, pStrcur);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStrcur, "MESHFIELD_SETNUM = ", strlen("MESHFIELD_SETNUM = ")) == 0)
		{
			//���o��
			pStrcur += strlen("MESHFIELD_SETNUM = ");
			//������̐擪��ݒ�
			strcpy(aStr, pStrcur);
			//�����񔲂��o��
			m_nSetMeshFieldNum = atoi(pStrcur);
		}

		//�I�u�W�F�N�g�̐�����
		for (int nCntObject = 0; nCntObject < m_nSetMeshFieldNum; nCntObject++)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "MESHFIELD_START", strlen("MESHFIELD_START")) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);

					//��ނ̂�ǂݍ���
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//���o��
						pStrcur += strlen("TEXTURETYPE = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//���̕�������ǂݍ���
					if (memcmp(pStrcur, "X_DIVIDE = ", strlen("X_DIVIDE = ")) == 0)
					{
						//���o��
						pStrcur += strlen("X_DIVIDE = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_nWidthDivide = atoi(pStrcur);
					}
					//�c�̕�������ǂݍ���
					if (memcmp(pStrcur, "Z_DIVIDE = ", strlen("Z_DIVIDE = ")) == 0)
					{
						//���o��
						pStrcur += strlen("Z_DIVIDE = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_nDepthDivide = atoi(pStrcur);
					}
					//���̒�����ǂݍ���
					if (memcmp(pStrcur, "X_LENGTH = ", strlen("X_LENGTH = ")) == 0)
					{
						//���o��
						pStrcur += strlen("X_LENGTH = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_fWidthLength = (float)atoi(pStrcur);
					}
					//�c�̒�����ǂݍ���
					if (memcmp(pStrcur, "Z_LENGTH = ", strlen("Z_LENGTH = ")) == 0)
					{
						//���o��
						pStrcur += strlen("Z_LENGTH = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_fDepthLength = (float)atoi(pStrcur);
					}
					//�P���_�̍���
					if (memcmp(pStrcur, "VTX0_HEIGHT = ", strlen("VTX0_HEIGHT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("VTX0_HEIGHT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_fVtxHeight_No0 = (float)atoi(pStrcur);
					}
					//�Q���_�̍���
					if (memcmp(pStrcur, "VTX1_HEIGHT = ", strlen("VTX1_HEIGHT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("VTX1_HEIGHT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_fVtxHeight_No1 = (float)atoi(pStrcur);
					}
					//�R���_�̍���
					if (memcmp(pStrcur, "VTX2_HEIGHT = ", strlen("VTX2_HEIGHT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("VTX2_HEIGHT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_fVtxHeight_No2 = (float)atoi(pStrcur);
					}
					//�S���_�̍���
					if (memcmp(pStrcur, "VTX3_HEIGHT = ", strlen("VTX3_HEIGHT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("VTX3_HEIGHT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_Mesh[nCntObject].m_fVtxHeight_No3 = (float)atoi(pStrcur);
					}
					//POS��ǂݍ���
					if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("POS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Mesh[nCntObject].m_pos.x = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Mesh[nCntObject].m_pos.y = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_Mesh[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					else if (memcmp(pStrcur, "MESHFIELD_END", strlen("MESHFIELD_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}

	//m_pMarkMeshField->SetMeshFieldNum(CMarkMeshField::GetMeshFieldNum() + m_nSetMeshFieldNum);
}
//===============================================================================
// �ǂ��t�@�C�����烍�[�h
//===============================================================================
void CGame::WallTextLoad(int nLoadNumber)
{
	//�t�@�C���p�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�

	//�t�@�C���|�C���^�̏���������
	pFile = NULL;

	//�ǂ̃X�e�[�W��ǂݍ��ނ�
	int nStageLoadNumber = nLoadNumber;

	//�t�@�C���̓ǂݍ��ݐ��ύX
	switch (nStageLoadNumber)
	{
	case 1:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_WALLNAME1, "r");
		break;
	case 2:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_WALLNAME2, "r");
		break;
	case 3:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_WALLNAME3, "r");
		break;
	case 4:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_WALLNAME4, "r");
		break;
	case 5:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_WALLNAME5, "r");
		break;
	case 6:
		//�t�@�C�����J�� �ǂݍ���
		pFile = fopen(TEXT_WALLNAME6, "r");
		break;
	}
	
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		//������̐擪��ݒ�
		pStrcur = ReadLine(pFile, &aLine[0]);
		//����������o��
		strcpy(aStr, pStrcur);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStrcur, "WALL_SETNUM = ", strlen("WALL_SETNUM = ")) == 0)
		{
			//���o��
			pStrcur += strlen("WALL_SETNUM = ");
			//������̐擪��ݒ�
			strcpy(aStr, pStrcur);
			//�����񔲂��o��
			m_nSetWallNum = atoi(pStrcur);
		}

		//�I�u�W�F�N�g�̐�����
		for (int nCntObject = 0; nCntObject < m_nSetWallNum; nCntObject++)
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "WALL_START", strlen("WALL_START")) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);

					//POS��ǂݍ���
					if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("POS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_pos.x = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_pos.y = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					//ROT��ǂݍ���
					if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("ROT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_rot.x = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_rot.y = (float)atof(pStrcur);
						//���������i�߂�
						pStrcur += nWord;

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_rot.z = (float)atof(pStrcur);

					}
					//WIDTH��ǂݍ���
					if (memcmp(pStrcur, "WIDTH = ", strlen("WIDTH = ")) == 0)
					{
						//���o��
						pStrcur += strlen("WIDTH = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_fWidthDivide = (float)atof(pStrcur);
					}
					//HIGHT��ǂݍ���
					if (memcmp(pStrcur, "HIGHT = ", strlen("HIGHT = ")) == 0)
					{
						//���o��
						pStrcur += strlen("HIGHT = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_fHightDivide = (float)atof(pStrcur);
					}
					//HIGHT��ǂݍ���
					if (memcmp(pStrcur, "TEXTURE = ", strlen("TEXTURE = ")) == 0)
					{
						//���o��
						pStrcur += strlen("TEXTURE = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						//��������Ԃ��Ă��炤
						nWord = PopString(pStrcur, &aStr[0]);
						//������ϊ�
						m_aWall[nCntObject].m_nTexType = (int)atof(pStrcur);
					}
					else if (memcmp(pStrcur, "WALL_END", strlen("WALL_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}

	//m_pMarkWall->SetWallNum(CMarkWall::GetWallNum() + m_nSetWallNum);
}
//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CGame::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//�@�t�@�C���ǂݍ��ݐ擪��r��
//=============================================================================
char *CGame::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//�@��������Ԃ�
//=============================================================================
int CGame::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += (int)strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//���o��
			nWord += (int)strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nWord;
}