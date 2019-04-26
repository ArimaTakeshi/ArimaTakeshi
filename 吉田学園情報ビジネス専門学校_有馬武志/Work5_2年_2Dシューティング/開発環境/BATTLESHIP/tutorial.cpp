//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "tutorial.h"
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
#include "logo.h"
#include "2Dobject.h"
#include "pause.h"
#include "string.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_HP		(100)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CTutorial::m_pPlayer = NULL;
CBullet *CTutorial::m_pBullet = NULL;
CExplosion *CTutorial::m_pExplosion = NULL;
CEnemy *CTutorial::m_pEnemy = NULL;
CGan *CTutorial::m_pGan = NULL;
CBg *CTutorial::m_pBg = NULL;
CFram *CTutorial::m_pFram = NULL;
CNumber *CTutorial::m_pNumber = NULL;
C2DObject *CTutorial::m_p2DObject = NULL;
//CString *CTutorial::m_pString = NULL;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
	CTutorial::GetPlayer() = NULL;
	m_EnemyCnt = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CTutorial::Init()
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

	//�`���[�g���A���̉摜
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 40.0f, 0.0f), D3DXVECTOR2(170.0f, 35.0f), 13);
	CLogo::Create(D3DXVECTOR3(150.0f, 200.0f, 0.0f), D3DXVECTOR2(140.0f, 140.0f), 14);
	CLogo::Create(D3DXVECTOR3(150.0f, 490.0f, 0.0f), D3DXVECTOR2(140.0f, 140.0f), 15);
	CLogo::Create(D3DXVECTOR3(1400.0f, 130.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 16);
	CLogo::Create(D3DXVECTOR3(1130.0f, 295.0f, 0.0f), D3DXVECTOR2(140.0f, 100.0f), 30);

	//�v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), D3DXVECTOR2(25, 85), PLAYER_HP);

	//�N���X�w�A
	CLogo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 31);

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

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CTutorial::Uninit(void)
{
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

	//���S�̃e�N�X�`���̔j��
	CLogo::UnLoad();

	//�̗͂̃e�N�X�`���̔j��
	CLife::UnLoad();

	//�|���S���̃e�N�X�`���̔j��
	CPolygon::UnLoad();

	//�t�F�[�h�̃e�N�X�`���̔j��
	CFade::UnLoad();

	//�G�t�F�N�g�̃e�N�X�`���̔j��
	CEffect::UnLoad();

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
void CTutorial::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//m_pString->Update();

	//CEnemy::Create(�ʒu�E�����E�T�C�Y�E�G�̎�ށE�̗́E�U������1 �U�����Ȃ�0�ȊO�E�ǔ�����1 �ǔ����Ȃ�0);
	//�G�̐���  ENEMYTYPE_SHIP ���0  : ENEMYTYPE_DIGHTER �퓬�@1  : ENEMYTYPE_SUBMARINE ������2  : ENEMTTYPE_CARRIER  ���3
	if (m_EnemyCnt == 0)
	{
		CEnemy::Create(D3DXVECTOR3(380.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1,0);
		CEnemy::Create(D3DXVECTOR3(440.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1, 0);
		CEnemy::Create(D3DXVECTOR3(500.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1, 0);
	}
	else if (m_EnemyCnt == 60)
	{
		CEnemy::Create(D3DXVECTOR3(620.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(10, 35), CEnemy::ENEMYTYPE_SUBMARINE, 50, 1, 0);
	}
	else if (m_EnemyCnt == 120)
	{
		CEnemy::Create(D3DXVECTOR3(750.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(25, 85), CEnemy::ENEMYTYPE_SHIP, 30, 1, 0);
	}
	else if (m_EnemyCnt == 180)
	{
		CEnemy::Create(D3DXVECTOR3(860.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(25, 85), CEnemy::ENEMYTYPE_SHIP, 30, 1, 0);
	}
	m_EnemyCnt++;

	//�`���[�g���A���X�L�b�v�̏���
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_N) == true)
	{//H�L�[�������ꂽ��
		CFade::Create(CManager::MODE_GAME);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
	//m_pString->Draw();
}