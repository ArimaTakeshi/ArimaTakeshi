//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "player.h"
#include "manager.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "object.h"
#include "game.h"
#include "wall.h"
#include "ground.h"
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "serect.h"
#include "meshorbit.h"
#include "life.h"
#include "gauge.h"
#include "action2D.h"
#include "fade.h"
#include "blood.h"
#include "serect.h"
#include "guide.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_WALK			(0.2f)
#define MODEL_RAN			(1.0f)
#define MODEL_SQUAT			(0.1f)
#define MODEL_SNEAK			(0.1f)
#define JUMP_POWER			(26.0f)
#define TIRED_TIME_START	(120)
#define TIRED_TIME_END		(121)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH	CPlayer::m_pMesh[MAX_PARTS] = {};					//���b�V�����̏�����
LPD3DXBUFFER CPlayer::m_pBuffMat[MAX_PARTS] = {};				//�}�e���A���̏��̏�����
DWORD CPlayer::m_nNumMat[MAX_PARTS] = {};						//�}�e���A���̏�񐔂̏�����
D3DXVECTOR3 CPlayer::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
D3DXVECTOR3 CPlayer::m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����̏�����
D3DXVECTOR3 CPlayer::m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��̏�����
CMeshOrbit *CPlayer::m_MeshOrbit = NULL;						//�O�Ղ̏�����
CSerect *CPlayer::m_pSerect = NULL;								//�Z���N�g�̃|�C���^
bool CPlayer::m_bFuture = false;								//�����̏�Ԃ̏�����
bool CPlayer::m_bFutureCancel = false;							//�����̏�Ԃ̃L�����Z���̏�����
bool CPlayer::m_bCancelHeal = false;							//�L�����Z�����̉񕜂̏�����
bool CPlayer::m_bActionFade = false;							//�A�N�V�����t�F�[�h�̋N���̏�����
bool CPlayer::m_bEnemyFuture = false;							//�G�̖����̏�����
bool CPlayer::m_bEnemyFutureSukill = false;						//�G�̖������ɃX�L���L�����Z���̏�����
bool CPlayer::m_bLifeFuture = false;							//�����̗̑͂̏�����
bool CPlayer::m_bLifeFutureSukill = false;						//�̗̖͂������ɃX�L���L�����Z���̏�����
bool CPlayer::m_bDie = false;									//���񂾏��
bool CPlayer::m_bDieSukill = false;								//���񂾏��
bool CPlayer::m_bStageNext = false;								//�X�e�[�W���ς�����ۂ̏�����
bool CPlayer::m_bOverResult = false;							//���񂾌�̃��U���g

//--------------------------------------------
//�O���[�o���ϐ�
//--------------------------------------------
int g_nNumModel;
char g_aFileNameModel[MAX_PARTS][256];

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CPlayer::CPlayer(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	//�l�̏�����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_apModel[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ߋ��̈ʒu
	m_fSpeedMove = 0.0f;
	m_fStageNext = false;
	m_bStageReset = false;
	CGame::GetPlayer() = this;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ߋ��̈ʒu
	m_bJump = true;										//�W�����v�̏��
	m_bLand = true;										//���n�̏��
	m_bInvincible = false;								//�`�[�g�̏��
	m_fStageNext = false;								//���̃X�e�[�W
	m_bMotionEnd = true;								//���[�V�����I��
	m_nAnimnow = PLAYERANIM_NEUTRAL;					//�j���[�g�������
	m_nAttackDelay = 0;									//�U��
	m_bSukillActivate = false;							//�X�L�����g�p�������ǂ���
	m_bGaugeOnOff = false;								//�Q�[�W���g�p���������Ă��Ȃ����̏��
	m_nDieTimer = 0;									//���񂾌�̑ҋ@����
	m_nDieSukillTimer = 0;								//�X�L�����Ɏ��񂾌�̌o�ߎ���
	m_bSukillDie = false;

	//�v���C���[���̓ǂݍ���
	FileLoad();

	CManager::MODE pMode = CManager::GetMode();

	//�e�N�X�`���̓ǂݍ���
	CMeshOrbit::Load();

	//���̃e�N�X�`���̓ǂݍ���
	m_pBlood->Load();

	//�Z���N�g�̃e�N�X�`���̓ǂݍ���
	m_pSerect->Load();

	//�ڈ�v���C���[�̓ǂݍ���
	m_pDummyPlayer->Load();

	//�O�Ղ̐���
	//m_MeshOrbit = CMeshOrbit::Create();

	//�v���C���[�̃��[���h�}�g���b�N�X�̔��f
	//m_MeshOrbit->SetMatRarent(&m_apModel[0]->GetMtxWorld());

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//�e�N�X�`���̔j��
	CMeshOrbit::UnLoad();

	//�Z���N�g�̃e�N�X�`���̔j��
	m_pSerect->UnLoad();

	//�ڈ�v���C���[�̔j��
	m_pDummyPlayer->UnLoad();

	//���̃e�N�X�`���̔j��
	m_pBlood->UnLoad();

	m_bFuture = false;			//�����̏�Ԃ�������
	m_bFutureCancel = false;	//�����̏�Ԃ̃L�����Z��
	m_bCancelHeal = false;		//�L�����Z�����̉�
	m_bActionFade = false;		//�t�F�[�h���폜
	m_bDie = false;				//�����̏�Ԃ�������
	m_bOverResult = false;		//���񂾌�̃��U���g���

	//�Z���N�g�̍폜
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//3D���f����Uninit
			m_apModel[nCount]->Uninit();
			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	CSound *pSound = CManager::GetSound();
	CManager::MODE pMode = CManager::GetMode();
	CObject *pObject = CGame::Get3DObject();
	CCamera *pCamera = CManager::GetCamera();
	CEnemy *pEnemy = CGame::GetEnemy();
	m_bEnemyFuture = false;
	m_bEnemyFutureSukill = false;

	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//��]�̒l��ۑ�
	m_rotDest = m_rot;

	if (pMode == CManager::MODE_TITLE)
	{
		//�ړ����[�V����
		m_nAnimnow = PLAYERANIM_SIT;

		m_rot.y = ((D3DX_PI * -0.5f));
	}
	//�Q�[����������
	else if (pMode == CManager::MODE_GAME)
	{
		//�O��̈ʒu��ۑ�
		m_posOld = m_pos;

		//============================
		//    �����\�m�X�L���g�p
		//============================
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_G) == true && CGauge::GetGaugeDownOn() == false && m_bDie == false && m_bStageNext == false || 
			pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_X) == true && CGauge::GetGaugeDownOn() == false && m_bDie == false && m_bStageNext == false)
		{
			//�X�L����
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILL);

			//�X�L���𔭓�
			m_bSukillActivate = true;

			//�Q�[�W�����炷���[�h�ɓ���
			m_bGaugeOnOff = true;

			//�Q�[���̏�Ԃ�n��
			CGauge::SetGaugeOnOff(m_bGaugeOnOff);

			//���݂̈ʒu�𖢗��ɓ����
			m_posFuture = m_pos;
			//���݂̌����𖢗��ɓ����
			m_rotFuture = m_rot;

			//�����̏�Ԃ�����
			m_bDieSukill = m_bDie;

			//�G�̖��������s
			m_bEnemyFuture = true;

			//������HP
			m_bLifeFuture = true;

			//�g���b�v�̏�Ԃ�ۑ�
			m_bTrapSukill = CGround::GetTrap();

			//�����̃t�F�[�h
			CAction2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(0.0f, 0.0f), 0);

			//�ڈ�𐶐�
			m_pDummyPlayer = CDummyPlayer::Create(m_pos,m_rot,m_nAnimnow);
		}

		CDebugProc::Print("m_bFutureCancel = %s\n", m_bFutureCancel ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bCancelHeal = %s\n", m_bCancelHeal ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bActionFade = %s\n", m_bActionFade ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bStageNext = %s\n", m_bStageNext ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bStageNext = %s\n", m_bStageNext ? "TRUE" : "FALSE"); 
		CDebugProc::Print("m_bEnemyFuture = %s\n", m_bEnemyFuture ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bEnemyFutureSukill = %s\n", m_bEnemyFutureSukill ? "TRUE" : "FALSE");
		CDebugProc::Print("m_bSukillActivate = %s\n", m_bSukillActivate ? "TRUE" : "FALSE");

		//============================
		// �����\�m�X�L���̃L�����Z��
		//============================
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_G) == true && CGauge::GetGaugeDownOn() == true && m_bFutureCancel == false && m_bCancelHeal == false && m_bStageNext == false ||
			pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_X) == true && CGauge::GetGaugeDownOn() == true && m_bFutureCancel == false && m_bCancelHeal == false && m_bStageNext == false || m_bSukillDie == true)
		{
			//�X�L���L�����Z����
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILLCANCEL);

			m_bSukillDie = false;

			//�����폜
			if (m_pBlood != NULL)
			{
				m_nDieSukillTimer = 0;
				m_pBlood->Uninit();
				m_pBlood = NULL;
			}

			//�X�L���𖳌���
			m_bSukillActivate = false;

			//�����̃L�����Z��
			m_bFutureCancel = true;

			//�����̎��ԉ񕜂����s
			m_bCancelHeal = true;

			//�A�N�V�����t�F�[�h�����s
			m_bActionFade = true;

			//�G�̖��������s
			m_bEnemyFuture = false;

			//�G�̖������ɃL�����Z�����s
			m_bEnemyFutureSukill = true;

			//�̗̖͂������ɃL�����Z�����s
			m_bLifeFutureSukill = true;

			//�����̏�Ԃ�����
			m_bDie = m_bDieSukill;

			//�ߋ��̃g���b�v�̏�Ԃ�����
			CGround::SetTrap(m_bTrapSukill);

			//NULL�`�F�b�N
			if (m_pDummyPlayer != NULL)
			{
				//�ڈ�̍폜
				m_pDummyPlayer->Uninit();
				m_pDummyPlayer = NULL;
			}

			//�����\�m�̃��L���X�g�^�C��
			CGauge::SetRecastTime(0);
		}

		//�L�����Z�����������ꍇ
		if (m_bFutureCancel == true && m_bStageNext == false)
		{
			//�ߋ��̈ʒu�ɖ߂�
			m_pos = m_posFuture;

			//�ߋ��̌����ɖ߂�
			m_rot = m_rotFuture;

			if (m_bDie == true)
			{
				//�j���[�g�������[�V�����ɖ߂�
				m_nAnimnow = PLAYERANIM_DIE;
			}
			else if (m_bDie == false)
			{
				//�A�j���[�V���������Ԃɂ���
				m_nAnimnow = PLAYERANIM_TIRED;
			}

			//3�b�̑ҋ@���Ԃ�݂���
			if (m_nFutureStandTime <= TIRED_TIME_END&& m_nFutureStandTime >= TIRED_TIME_START)
			{
				//�����Ȃ�����
				m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				//�ҋ@���Ԃ̏���������
				m_nFutureStandTime = 0;

				//�����̃L�����Z����߂�
				m_bFutureCancel = false;

				//�����̎��ԉ񕜂����s
				m_bCancelHeal = true;

				//�j���[�g�������[�V�����ɖ߂�
				m_nAnimnow = PLAYERANIM_NEUTRAL;
			}

			//�J�E���g�̑���
			m_nFutureStandTime++;
		}

		//============================
		// �X�e�[�W���؂�ւ�������̂�
		//============================
		if (m_bStageNext == true)
		{
			//�X�L���̔����𖳌���
			m_bSukillActivate = false;

			//�����̃L�����Z����߂�
			m_bFutureCancel = false;

			//�����̎��ԉ񕜂����s
			m_bCancelHeal = true;

			//�A�N�V�����t�F�[�h�����s
			m_bActionFade = true;

			//NULL�`�F�b�N
			if (m_pDummyPlayer != NULL)
			{
				//�ڈ�̍폜
				m_pDummyPlayer->Uninit();
				m_pDummyPlayer = NULL;
			}
		}

		//============================
		// �@�Q�[�W���Ȃ��Ȃ�����
		//============================
		if (CGauge::GetTired() == true && m_bStageNext == false)
		{
			//�X�L���L�����Z����
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SKILLCANCEL);

			//�X�L���̔����𖳌���
			m_bSukillActivate = false; 

			if (m_bDie == true)
			{
				//�j���[�g�������[�V�����ɖ߂�
				m_nAnimnow = PLAYERANIM_DIE;
			}
			else if (m_bDie == false)
			{
				//�A�j���[�V���������Ԃɂ���
				m_nAnimnow = PLAYERANIM_TIRED;
			}

			//NULL�`�F�b�N
			if (m_pDummyPlayer != NULL)
			{
				//�ڈ�̍폜
				m_pDummyPlayer->Uninit();
				m_pDummyPlayer = NULL;
			}

			//3�b�̑ҋ@���Ԃ�݂���
			if (m_nFutureStandTime <= TIRED_TIME_END && m_nFutureStandTime >= TIRED_TIME_START)
			{
				//�j���[�g�������[�V�����ɖ߂�
				m_nAnimnow = PLAYERANIM_NEUTRAL;

				m_nFutureStandTime = 0;

				CGauge::SetTired(false);
			}
			//�J�E���g�̑���
			m_nFutureStandTime++;
		}

		//============================
		//     �v���C���[�̈ړ�
		//============================
		if (m_bAttack == false && m_nAnimnow != PLAYERANIM_TIRED)
		{
			//�O�Ղ̕`�悷�邩�ǂ���
			//m_MeshOrbit->SetOrbitOn(true);

			//�f�o�b�N�p
			if (pCInputKeyBoard->GetKeyboardPress(DIK_K) == true)
			{
				CGauge::AddGauge(150);
			}

			//���[�V�������̃X�s�[�h
			if (m_nAnimnow == PLAYERANIM_WALK)
			{
				m_fSpeedMove = MODEL_WALK;
			}
			else if (m_nAnimnow == PLAYERANIM_RUN)
			{
				m_fSpeedMove = MODEL_RAN;
			}
			else if (m_nAnimnow == PLAYERANIM_SNEAK)
			{
				m_fSpeedMove = MODEL_SNEAK;
			}
			else if (m_nAnimnow == PLAYERANIM_SQUAT)
			{
				m_fSpeedMove = MODEL_SQUAT;
			}

			if (pCamera->GetCameraPosV() != D3DXVECTOR3(59.0f, 146.0f, 568.0f) && pCamera->GetCameraPosV() != D3DXVECTOR3(905.0f, 190.0f, 540.0f)
				&& pCamera->GetCameraPosV() != D3DXVECTOR3(470.0f, 240.0f, 660.0f) && pCamera->GetCameraPosV() != D3DXVECTOR3(-1040.0f, 170.0f, 400.0f) && m_bDie == false)
			{
				//�ړ�����
				if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
				{//���̏�							����ړ�
					if ((m_bJump || m_bLand))
					{
						//�ړ����[�V����
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//���郂�[�V����
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//���Ⴊ�ރ��[�V����
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}

					if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
					{
						m_move.x += sinf(D3DX_PI * 0.25f) * m_fSpeedMove;
						m_move.z += cosf(D3DX_PI * 0.25f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * -0.75f));
					}
					else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
					{
						m_move.x += sinf(-D3DX_PI * 0.25f) * m_fSpeedMove;
						m_move.z += cosf(-D3DX_PI * 0.25f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * 0.75f));
					}
					else
					{
						m_move.x += sinf(D3DX_PI * 0.0f) * m_fSpeedMove;
						m_move.z += cosf(D3DX_PI * 0.0f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * -1.0f));
					}
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
				{//���̉�							 ����ړ�
					if ((m_bJump || m_bLand))
					{
						//�ړ����[�V����
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//���郂�[�V����
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//���Ⴊ�ރ��[�V����
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
					if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
					{
						m_move.x += sinf(D3DX_PI * 0.75f) * m_fSpeedMove;
						m_move.z += cosf(D3DX_PI * 0.75f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * -0.25f));
					}
					else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
					{
						m_move.x += sinf(-D3DX_PI * 0.75f) * m_fSpeedMove;
						m_move.z += cosf(-D3DX_PI * 0.75f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * 0.25f));
					}
					else
					{
						m_move.x += sinf(-D3DX_PI * 1.0f) * m_fSpeedMove;
						m_move.z += cosf(-D3DX_PI * 1.0f) * m_fSpeedMove;
						m_rotDest.y = ((D3DX_PI * 0.0f));
					}
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{//���̉E							�� �E�ړ�
					m_move.x += sinf(D3DX_PI * 0.5f) * m_fSpeedMove;
					m_move.z += cosf(D3DX_PI * 0.5f) * m_fSpeedMove;
					m_rotDest.y = ((D3DX_PI * -0.5f));
					if ((m_bJump || m_bLand))
					{
						//�ړ����[�V����
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//���郂�[�V����
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//���Ⴊ�ރ��[�V����
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{//���̍�							 �� ���ړ�
					m_move.x += sinf(-D3DX_PI * 0.5f) * m_fSpeedMove;
					m_move.z += cosf(-D3DX_PI * 0.5f) * m_fSpeedMove;
					m_rotDest.y = ((D3DX_PI * 0.5f));

					if ((m_bJump || m_bLand))
					{
						//�ړ����[�V����
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputKeyBoard->GetKeyboardPress(DIK_LSHIFT) == true)
						{
							//���郂�[�V����
							m_nAnimnow = PLAYERANIM_RUN;
						}
						if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
						{
							//���Ⴊ�ރ��[�V����
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
				}
				else if (pCInputJoyPad->GetPress(CInputJoypad::STICK_L_UP) == true || pCInputJoyPad->GetPress(CInputJoypad::STICK_L_DOWN) == true
					|| pCInputJoyPad->GetPress(CInputJoypad::STICK_L_RIGHT) == true || pCInputJoyPad->GetPress(CInputJoypad::STICK_L_LEFT) == true)
				{//�W���C�R��
					CDebugProc::Print("�������Ă���\n");

					m_move.x -= sinf(pCamera->GetRot() - pCInputJoyPad->GetLeftAxiz()) * m_fSpeedMove;
					m_move.z -= cosf(pCamera->GetRot() - pCInputJoyPad->GetLeftAxiz()) * m_fSpeedMove;

					//����
					m_rotDest.y = (pCamera->GetRot() - pCInputJoyPad->GetLeftAxiz());

					if ((m_bJump || m_bLand))
					{
						m_nAnimnow = PLAYERANIM_WALK;

						if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_RB) == true)
						{
							//���郂�[�V����
							m_nAnimnow = PLAYERANIM_RUN;
						}

						if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_A) == true)
						{
							//���Ⴊ�ރ��[�V����
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
						else if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_LB) == true)
						{
							//���Ⴊ�ރ��[�V����
							m_nAnimnow = PLAYERANIM_SNEAK;
						}
					}
				}
				else if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_LB) == true)
				{
					//���郂�[�V����
					m_nAnimnow = PLAYERANIM_SQUAT;
				}
				else if (pCInputJoyPad->GetPress(CInputJoypad::BUTTON_A) == true)
				{
					//���Ⴊ�ރ��[�V����
					m_nAnimnow = PLAYERANIM_SQUAT;
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_LCONTROL) == true)
				{
					//���Ⴊ�ރ��[�V����
					m_nAnimnow = PLAYERANIM_SQUAT;
				}
				else
				{
					if ((m_bJump || m_bLand) && m_bAttack == false && m_bResult == false)
					{
						//�ҋ@���[�V����
						m_nAnimnow = PLAYERANIM_NEUTRAL;
					}
				}
			}
			else if(m_bDie == true)
			{
				m_nAnimnow = PLAYERANIM_DIE;
			}
			//============================
			//     �X�e�[�W�̑J��
			//============================
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(59.0f, 146.0f, 568.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//�ړ����[�V����
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * -1.0f));
			}
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(905.0f, 190.0f, 540.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//�ړ����[�V����
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * 0.5f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * 0.5f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * -0.5f));
			}
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(470.0f, 240.0f, 660.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//�ړ����[�V����
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * 0.0f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * -1.0f));
			}
			else if (pCamera->GetCameraPosV() == D3DXVECTOR3(-1040.0f, 170.0f, 400.0f))
			{
				if ((m_bJump || m_bLand))
				{
					//�ړ����[�V����
					m_nAnimnow = PLAYERANIM_WALK;
				}

				m_move.x += sinf(D3DX_PI * -0.5f) * m_fSpeedMove;
				m_move.z += cosf(D3DX_PI * -0.5f) * m_fSpeedMove;
				m_rotDest.y = ((D3DX_PI * 0.5f));
			}
		}

		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_V) == true && (m_bJump || m_bLand) && m_bAttack == false
			|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_B) == true && (m_bJump || m_bLand) && m_bAttack == false)
		{
			//�U�����[�V����
			//m_nKey = 0;
			//m_nAnimnow = PLAYERANIM_ATTACK;
			//m_bAttack = true;

			//�O�Ղ̕`����J�n����
			//m_MeshOrbit->SetOrbitOn(true);
		}

		if (m_bDie == true && m_bSukillActivate == false)
		{
			if (m_nDieTimer >= 22 && m_nDieTimer <= 22)
			{
				//NULL�`�F�b�N
				if (m_pBlood == NULL)
				{
					//�_���[�W���̐�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

					//���̐���
					m_pBlood = CBlood::Create(m_pos, 30.0f, 30.0f, 0);
				}
			}
			if (m_nDieTimer == 180)
			{
				//�Q�[���I�[�o�[
				//CGame::SetGameState(CGame::GAMESTATE_OVER);

				//���񂾎��̃��U���g
				m_bOverResult = true;

				//Rewind time ���o��
				CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 110.0f, 0.0f), D3DXVECTOR2(250.0f, 50.0f), 11);

				//�Z���N�g���o��
				m_pSerect = CSerect::Create(1);


				//m_nDieTimer = 0;
			}
			
			m_nDieTimer++;
		}
		else if (m_bDie == true && m_bSukillActivate == true)
		{
			if (m_nDieSukillTimer == 22)
			{
				//NULL�`�F�b�N
				if (m_pBlood == NULL)
				{
					//�_���[�W���̐�
					pSound->PlaySound(CSound::SOUND_LABEL_SE_DAMAGE);

					//���̐���
					m_pBlood = CBlood::Create(m_pos, 30.0f, 30.0f, 0);
				}
			}
			else if (m_nDieSukillTimer >= 60)
			{
				m_bSukillDie = true;
			}

			m_nDieSukillTimer++;
		}

#if 0
		//���U���g�̓����m�F�p
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_R) == true)
		{
			//���[�h���U���g
			m_bResult = true;
		}
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_G) == true)
		{
			//���U���g���[�V����
			m_nAnimnow = PLAYERANIM_RESULTUP;
		}
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_B) == true)
		{
			//���U���g���[�V����
			m_nAnimnow = PLAYERANIM_RESULTDOWN;
		}
#endif

		if (m_bInvincible == true)
		{
			if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
			{//���̏�							����ړ�
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.25f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.25f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * -0.75f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.25f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 0.25f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * 0.75f));
				}
				else
				{
					m_move.x += sinf(D3DX_PI * 0.0f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.0f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * -1.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
			{//���̉�							 ����ړ�
				if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
				{
					m_move.x += sinf(D3DX_PI * 0.75f) * 3.0f;
					m_move.z += cosf(D3DX_PI * 0.75f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * -0.25f));
				}
				else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
				{
					m_move.x += sinf(-D3DX_PI * 0.75f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 0.75f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * 0.25f));
				}
				else
				{
					m_move.x += sinf(-D3DX_PI * 1.0f) * 3.0f;
					m_move.z += cosf(-D3DX_PI * 1.0f) * 3.0f;
					m_rotDest.y = ((D3DX_PI * 0.0f));
				}
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
			{//���̉E							�� �E�ړ�
				m_move.x += sinf(D3DX_PI * 0.5f) * 3.0f;
				m_move.z += cosf(D3DX_PI * 0.5f) * 3.0f;
				m_rotDest.y = ((D3DX_PI * -0.5f));
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
			{//���̍�							 �� ���ړ�
				m_move.x += sinf(-D3DX_PI * 0.5f) * 3.0f;
				m_move.z += cosf(-D3DX_PI * 0.5f) * 3.0f;
				m_rotDest.y = ((D3DX_PI * 0.5f));
			}

			if (pCInputKeyBoard->GetKeyboardPress(DIK_Q) == true)
			{// �v���C���[�̏㏸
				m_pos.y += 5.0f;
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_E) == true)
			{// �v���C���[�̉��~
				m_pos.y -= 5.0f;
			}
		}
#ifdef _DEBUG
		//�`�[�g�̃I���I�t
		if (pCInputKeyBoard->GetKeyboardPress(DIK_Z) == true && pCInputKeyBoard->GetKeyboardTrigger(DIK_X) == true)
		{
			m_bInvincible = m_bInvincible ? false : true;
		}
#endif
		if (m_bInvincible == false)
		{
			// �d��
			m_move.y -= cosf(0) * 2.0f;
		}

		//�ʒu���ړ��ɑ��
		m_pos += m_move;

		//����������
		m_move.x += (0.0f - m_move.x) * 0.2f;
		m_move.z += (0.0f - m_move.z) * 0.2f;

		//�ڕW���`�F�b�N
		if (m_rotDest.y > D3DX_PI)
		{
			m_rotDest.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rotDest.y < -D3DX_PI)
		{
			m_rotDest.y += (D3DX_PI * 2.0f);
		}

		float fRotDest = (m_rotDest.y - m_rot.y);

		//�������`�F�b�N
		if (fRotDest > D3DX_PI)
		{
			fRotDest -= (D3DX_PI * 2.0f);
		}
		else if (fRotDest < -D3DX_PI)
		{
			fRotDest += (D3DX_PI * 2.0f);
		}

		m_rot.y += (fRotDest) * 0.2f;

		//�������`�F�b�N
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += (D3DX_PI * 2.0f);
		}

		//�`�[�g��OFF�̏�ԁ@���@��������A��ۓ����蔻��ɓ������Ă��܂����߁AFururesukill��false�ɂ���K�v������
		if (m_bInvincible == false && m_bEnemyFutureSukill == false)
		{
			// �n�ʂ̍������擾
			CollisitionMesh();
			//���̓����蔻��
			CollisitionGround();
			//���C�g�̓����蔻��
			CollisitionSpotLight();
			// �ǂ̓����蔻��
			CollisitionWall();
			// �I�u�W�F�N�g�̓����蔻��
			CollisitionObject3D(&m_pos, &m_posOld, &m_move);
			//�e�̓����蔻��
			CollisitionBullet();
			// �A�C�e���̓����蔻��
			CollisitionItem();
		}

		//���f���̃f�o�b�N�ʒu
		CDebugProc::Print("�v���C���[pos�̈ʒu :�y%.1f�z�y%.1f�z�y%.1f�z\n", m_pos.x, m_pos.y, m_pos.z);
		CDebugProc::Print("%s\n", m_bInvincible ? "true" : "false");
	}
	else if (pMode == CManager::MODE_RESULT)
	{//���U���g��������
		//�I�����Ă���ԍ����擾
		int SelectNum = CSerect::Get();
		
		m_nAnimnow = PLAYERANIM_RUN;

		m_pos.z -= 4.0f;
	}
	else if (pMode == CManager::MODE_RANKING)
	{//�����L���O��������
		if (m_bInvincible == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_SPACE) == true
			|| pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_A) == true)
		{// �W�����v
			//if (m_nAnimnow != PLAYERANIM_BAKUTEN)
			{	//�o���U�C

				//m_nAnimnow = PLAYERANIM_BAKUTEN;
				//m_bMotionEnd = false;
			}
		}
		//else if (m_nAnimnow != PLAYERANIM_BANZAI && m_bMotionEnd == true)
		{	//�o���U�C
			//m_nAnimnow = PLAYERANIM_BANZAI;
		}
	}
	m_nMotionType = m_nAnimnow;

	//���[�V�����X�V
	UpdateMotion();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�m�Ԓ�kk��

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//// ���C�g�𖳌��ɂ���
	//pDevice->LightEnable(0, FALSE);
	//pDevice->LightEnable(1, FALSE);
	//pDevice->LightEnable(2, FALSE);

	////�e
	//D3DXMATRIX	mtxShadow;		//�V���h�E�}�g���b�N�X
	//D3DXPLANE	planeFielld;
	//D3DXVECTOR4 vecLight;
	//D3DXVECTOR3 pos, normal;

	//// �V���h�E�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&mtxShadow);

	//// ��ԋ������C�g�̈ʒu
	//vecLight = D3DXVECTOR4(-0.22f, 0.87f, -0.44f, 0.0f);

	//// �e�̈ʒu
	//pos = D3DXVECTOR3(0.0f, m_pos.y + 1.0f, 0.0f);

	//// �@���̌���
	//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//// ���ʂ����
	//D3DXPlaneFromPointNormal(&planeFielld, &pos, &normal);

	//D3DXMatrixShadow(&mtxShadow, &vecLight, &planeFielld);

	////�}�g���b�N�X���|�����킹��       �����΂ɂ���Ɖe�������܂ł��Ă���
	//D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	//{
	//	if (m_apModel[nCount] != NULL)
	//	{
	//		//���f���̕`��
	//		m_apModel[nCount]->Draw(1.0f);
	//	}
	//}

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(0, TRUE);
	//pDevice->LightEnable(1, TRUE);
	//pDevice->LightEnable(2, TRUE);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//���f���̕`��
			m_apModel[nCount]->Draw(1.0f);
		}
	}
}
//=============================================================================
//	���b�V���̓����蔻��
//=============================================================================
void CPlayer::CollisitionMesh(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(MESH_PRIOTITY);

	//�W�����v��false��
	m_bJump = false;

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_MESH)
			{
				//�v���C���[��Hight������
				if (((CMesh*)pScene)->GetHeight(m_pos))
				{
					//�W�����v���Ă����Ԃɂ���
					m_bJump = true;
					//�������Ƃ���move������������
					m_move.y = 0.0f;
				}
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�ǂ̓����蔻��
//=============================================================================
void CPlayer::CollisitionWall(void)
{
	CScene *pScene;
	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_WALL)
			{
				((CWall*)pScene)->CollisionWall(&m_pos, &m_posOld, &m_move, 20.0f);
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�I�u�W�F�N�g�̓����蔻��
//=============================================================================
void CPlayer::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//�ϐ��錾
	bool bLand = false;

	//bLand�̏���������
	m_bLand = false;

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				//�I�u�W�F�N�g�̂����锻��
				bLand = ((CObject*)pScene)->CollisionObject(pPos, pPosOld, pMove);

				//���n�����L����
				if (bLand)
				{
					m_bLand = bLand;
				}
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�e�̓����蔻��
//=============================================================================
void CPlayer::CollisitionBullet(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(BULLET_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v���e�e��������
			if (pScene->GetObjType() == OBJTYPE_BULLET)
			{
				//�����蔻��
				if (((CBullet*)pScene)->CollisitionBullet(&m_pos,20.0f))
				{
					if (m_bStageNext == false)
					{
						//���C�t�Q�[�W���猸�炷
						CLife::AddLife(-200);
					}
					pScene->Uninit();
				}
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�A�C�e���̓����蔻��
//=============================================================================
void CPlayer::CollisitionItem(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(4);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v���A�C�e����������
			if (pScene->GetObjType() == OBJTYPE_ITEM)
			{
				//�����蔻��
				if (((CItem*)pScene)->CollisionItem(&m_pos, &m_posOld, &m_move))
				{
					pScene->Uninit();
				}
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	���̓����蔻��
//=============================================================================
void CPlayer::CollisitionGround(void)
{
	CScene *pScene;
	bool bWater = false;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(GROUND_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v������������
			if (pScene->GetObjType() == OBJTYPE_GROUND)
			{
				((CGround*)pScene)->CollisionGround(&m_pos, &m_posOld, &m_move);
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	���C�g�̓����蔻��
//=============================================================================
void CPlayer::CollisitionSpotLight(void)
{
	CScene *pScene;
	bool bWater = false;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(SPOTLIGHT_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v������������
			if (pScene->GetObjType() == OBJTYPE_SPOTLIGHT)
			{
				((CSpotLight*)pScene)->CollisionSpotLight(&m_pos, &m_posOld, &m_move);
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;

	//NULL�`�F�b�N
	if (pPlayer == NULL)
	{//�������̓��I�m��

		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pPlayer->Init();
			//�ʒu����
			pPlayer->SetPos(pos);
		}
	}

	return pPlayer;
}
//=========================================================================================================================
// �}�b�v�ړ��̍ۂ̃v���C���[�̏�����
//=========================================================================================================================
void CPlayer::ResetPlayer(void)
{
	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2 || pStageNum == CGame::STAGENUM_3 || pStageNum == CGame::STAGENUM_5)
	{
		m_pos = D3DXVECTOR3(0.0f, 0.0f, -350.0f);		//�ʒu
		m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);			//����

		m_bStageReset = true;							//�X�e�[�W���ς������
	}
	if (pStageNum == CGame::STAGENUM_4)
	{
		m_pos = D3DXVECTOR3(-60.0f, 0.0f, -200.0f);		//�ʒu
		m_rot = D3DXVECTOR3(0.0f, -1.57f, 0.0f);		//����

		m_bStageReset = true;							//�X�e�[�W���ς������
	}
	if (pStageNum == CGame::STAGENUM_6)
	{
		m_pos = D3DXVECTOR3(-40.0f, 0.0f, 1280.0f);		//�ʒu
		m_rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);			//����

		m_bStageReset = true;							//�X�e�[�W���ς������
	}

	if (m_bStageReset == true)
	{
		m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ߋ��̈ʒu
		m_bJump = true;									//�W�����v�̏��
		m_bLand = true;									//���n�̏��
		m_bInvincible = false;							//�`�[�g���[�h
		m_fStageNext = false;							//�X�e�[�W�؂�ւ�
		m_bMotionEnd = true;							//���[�V�����I��
		m_nAnimnow = PLAYERANIM_NEUTRAL;				//���[�V����������
		m_nAttackDelay = 0;								//�U��

		m_bStageReset = false;							//�X�e�[�W���ς������
	}
}
//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CPlayer::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}
//=============================================================================
// �v���C���[�̃��[�V����
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	//���[�V����
	KEY *pKey, *pNextKey;
	float fRateMotion;
	float fDiffMotion;
	D3DXVECTOR3 rotmotion;
	D3DXVECTOR3 posmotion;
	//D3DXVECTOR3 posParent;


	//�L�[���ő吔������Ȃ��悤��
	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	//���[�V�����X�V
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apModel[nCntParts] != NULL)
		{
			//���݂̃L�[���擾
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
			//���̃L�[���擾
			pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

			//���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
			fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

			//ROT
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->frotX - pKey->frotX;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

			//POS
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->fposX - pKey->fposX;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);


			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->frotY - pKey->frotY;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
			//POS
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->fposY - pKey->fposY;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);


			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->frotZ - pKey->frotZ;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
			//POS
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->fposZ - pKey->fposZ;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);


			//�p�[�c�𓮂���
			m_apModel[nCntParts]->Setrot(rotmotion);

			//POS
			m_apModel[nCntParts]->SetPos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x,
				m_OffSetPos[nCntParts].y + posmotion.y,
				m_OffSetPos[nCntParts].z + posmotion.z));

		}
	}

	//���[�v�̔���
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{
	case true:
		//���[�v����
		//�t���[����i�߂�
		m_nCountFlame++;
		//�L�[�̍X�V
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
			{
				m_nKey = 0;
			}
			else
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}

		break;
	case false:
		//���[�v���Ȃ�
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//�t���[����i�߂�
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{
			//if (m_nAnimnow == PLAYERANIM_ATTACK)
			//{//�U�����[�V����
			//	m_nAttackDelay++;
			//	if (m_nAttackDelay > 20)
			//	{
			//		m_bAttack = false;
			//		m_nAttackDelay = 0;
			//	}
			//}
			m_bMotionEnd = true;
		}
		//�L�[�̍X�V
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}
		break;
	}

#ifdef  _DEBUG
	CDebugProc::Print(" Num�L�[  : (%d)\n", m_nKey);
	CDebugProc::Print(" m_nCountFlame  : (%d)\n", m_nCountFlame);

#endif

}

//=============================================================================
// �t�@�C���ǂݍ���
//=============================================================================
void CPlayer::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�

	D3DXVECTOR3 ParentPos;	//�e�̈ʒu�����擾
#if 1
							//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME_PRISONER, "r");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; )
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				g_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������߂�
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//���o��
						pStrcur += strlen("MODEL_FILENAME = ");

						//�������ݒ�
						strcpy(aStr, pStrcur);

						//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//����������߂�
						strcpy(aStr, pStrcur);

						//�Ō�̕�����NULL����������
						aStr[nNullNum - 1] = '\0';

						//�Ώۂ̕����񂩂甲���o��
						strcpy(&g_aFileNameModel[nCntModel][0], aStr);

						// X�t�@�C���̓ǂݍ���
						D3DXLoadMeshFromX(&g_aFileNameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMat[nCntModel],
							NULL,
							&m_nNumMat[nCntModel],
							&m_pMesh[nCntModel]);
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}


			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_PARTS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEX��ǂݍ���
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								//���o��
								pStrcur += strlen("INDEX = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								nIndex = atoi(pStrcur);
							}
							//PARENT��ǂݍ���
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								//���o��
								pStrcur += strlen("PARENT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								m_aIndexParent[nIndex] = atoi(pStrcur);
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
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

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
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);
							}
							//�p�[�c�Z�b�g�I��
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{
								//NULL�`�F�b�N
								if (m_apModel[nIndex] == NULL)
								{//���I�m��
									m_apModel[nIndex] = new CModel;
									//NULL�`�F�b�N
									if (m_apModel[nIndex] != NULL)
									{
										//���f���̐���
										m_apModel[nIndex]->BindModel(m_pMesh[nIndex], m_pBuffMat[nIndex], m_nNumMat[nIndex]);
										m_apModel[nIndex]->Init();
									}
								}

								//���f���𐶐�	�I�t�Z�b�g�ݒ�
								/*m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
										m_pos.y + m_aKayOffset[nIndex].fposY,
										m_pos.z + m_aKayOffset[nIndex].fposZ), m_rot);*/

								m_apModel[nIndex]->SetPos(D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
									m_pos.y + m_aKayOffset[nIndex].fposY,
									m_pos.z + m_aKayOffset[nIndex].fposZ));

								//pos����
								ParentPos = m_apModel[nIndex]->GetPos();
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//���f�������蓖��
								m_apModel[nIndex]->BindModel(m_pMesh[nIndex], m_pBuffMat[nIndex], m_nNumMat[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{
									//���f���̐e���w��
									m_apModel[nIndex]->SetParent(NULL);
									ParentPos = m_apModel[nIndex]->GetPos();
								}
								else
								{
									//���f���̐e���w��
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}

								break;
							}
						}
					}
					//�L�����N�^�[�Z�b�g�I��
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}

			//���[�V�����ǂݍ���
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MOTIONSET");

				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//���o��
						pStrcur += strlen("LOOP = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
					}
					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_KEY = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
						//����������o��
						strcpy(aStr, pStrcur);
					}

					//�L�[�̐ݒ�
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{
							//���o��
							pStrcur += strlen("KEYSET");
							//������̐擪��ݒ�
							strcpy(aStr, pStrcur);
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{
								//���o��
								pStrcur += strlen("FRAME = ");

								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);

								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
							}

							//�p�[�c����
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);

									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{
										//���o��
										pStrcur += strlen("POS = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
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
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{
										//���o��
										pStrcur += strlen("END_KEY");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
										//�p�[�c�̃J�E���g��i�߂�
										nCntParts++;
									}
								}
								else
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
								//�J�E���g��i�߂�
								nCntKey++;
							}
						}
						else
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						//���[�V�����̏����Z�b�g
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						nCntMotion++;
						break;
					}
				}
			}
			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
#endif

}

//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CPlayer::ReadLine(FILE *pFile, char *pDst)
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
char * CPlayer::GetLineTop(char * pStr)
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
int CPlayer::PopString(char * pStr, char * pDest)
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
