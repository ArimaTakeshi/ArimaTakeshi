//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "game.h"
#include "title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_CAMERA			(320.0f)		//�J�����̈ړ���
#define MOVE_ANGLE			(0.01f)			//�J�����p�x�̈ړ���
#define MOVE_ANGLE1			(0.01f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CPlayer *CCamera::m_pPlayer = NULL;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_�̏����l
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_fAngle = 0.0f;
	m_fCameraAngle = 45.0f;								//�p�x
	m_CameraCount = 0;									//�J�����̐�������
	m_fRot = 0;											//�J�����̌���������
	m_fLength = m_posV.z - m_posR.z;					//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	m_nType = CAMERA_TYPE_NONE;							//���
	m_nCntTitle = 0;
	m_bReset = false;
	m_bResultCamera = false;
	m_nCountTimer = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CCamera::~CCamera()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_posV = D3DXVECTOR3(0.0f, 200.0f, 0.0f);			//���_�̏����l
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	m_fAngle = 0.0f;									//�J�����̊p�x�̏�����
	m_fLength = m_posV.z - m_posR.z;					//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	m_fRange = m_posV.y - m_posR.y;						//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	m_nCntTitle = 0;
	m_bResultCamera = false;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();

	CManager::MODE pMode = CManager::GetMode();

	if (pMode == CManager::MODE_TITLE)
	{
		m_posV = D3DXVECTOR3(-365.0f, 80.0f, -140.0f);		//���_�̏����l
		m_posR = D3DXVECTOR3(-80.0f, 0.0f, 270.0f);			//�����_�̏����l
		m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	}
	else if (pMode == CManager::MODE_GAME)
	{
		float fcof = 0;
		bool bOnTPS = false;
		bool bOnFPS = false;

		//�v���C���[��pos����
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
		D3DXVECTOR3 PlayerRot = m_pPlayer->GetRot();
		D3DXVECTOR3 PlayerMove = m_pPlayer->GetMove();

		//�X�e�[�W�J�ڒ��ł͂Ȃ�
		if (CPlayer::GetCancelStageNext() == false && CPlayer::GetDie() == false && CGame::GetPause() == false)
		{
			//============================
			//     ���_�̍��E�O��ړ�
			//============================
			if (pCInputKeyBoard->GetKeyboardPress(DIK_RIGHT) == true)//�E���L�[���������Ƃ�
			{//�E�ړ�							�@�@�@���p�x�@�@�@�@���ړ���
				m_posV.x += sinf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
				m_posV.z += cosf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
				//m_posR�ɑ��
				m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
				m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
			}
			if (pCInputKeyBoard->GetKeyboardPress(DIK_LEFT) == true)//�����L�[���������Ƃ�
			{//���ړ�									���p�x�@�@�@���ړ���
				m_posV.x += sinf((D3DX_PI * -0.5f) + m_fAngle) * MOVE_CAMERA;
				m_posV.z += cosf((D3DX_PI * -0.5f) + m_fAngle) * MOVE_CAMERA;
				//m_posR�ɑ��
				m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
				m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
			}
			if (pCInputKeyBoard->GetKeyboardPress(DIK_UP) == true)//����L�[���������Ƃ�
			{//�O�ړ�								  ���p�x�@�@�@�@���ړ���
				m_posV.x += sinf((D3DX_PI * 0.0f) + m_fAngle) * MOVE_CAMERA;
				m_posV.z += cosf((D3DX_PI * 0.0f) + m_fAngle) * MOVE_CAMERA;
				//m_posR�ɑ��
				m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
				m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;

			}
			if (pCInputKeyBoard->GetKeyboardPress(DIK_DOWN) == true)//�����L�[���������Ƃ�
			{//��ړ�						  ���p�x�@�@�@�@���ړ���
				m_posV.x += sinf((D3DX_PI)+m_fAngle) * MOVE_CAMERA;
				m_posV.z += cosf((D3DX_PI)+m_fAngle) * MOVE_CAMERA;
				//m_posR�ɑ��
				m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
				m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
			}
			//============================
			//        ���_�ړ�
			//============================
			if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD1) == true)
			{//C�L�[���������Ƃ��@�@�@���p�x�̈ړ���
				m_fAngle += MOVE_ANGLE;
				if (m_fAngle > D3DX_PI)
				{//������
					m_fAngle = -D3DX_PI;
				}
				//g_Camera.posV��D3DXVECTOR3��sin��cos����
				m_posV = D3DXVECTOR3(m_posR.x + sinf(m_fAngle) * m_fLength, m_posV.y, m_posR.z + cosf(m_fAngle) * m_fLength);
			}
			if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD3) == true)
			{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
				m_fAngle -= MOVE_ANGLE;
				if (m_fAngle < -D3DX_PI)
				{//�E����
					m_fAngle = D3DX_PI;
				}
				//g_Camera.posV��D3DXVECTOR3��sin��cos����
				m_posV = D3DXVECTOR3(m_posR.x + sinf(m_fAngle) * m_fLength, m_posV.y, m_posR.z + cosf(m_fAngle) * m_fLength);
			}

			if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD2) == true)
			{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
				m_posV.y += 2.0f;
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD0) == true)
			{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
				m_posV.y -= 2.0f;
			}

			if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD8) == true)
			{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
				m_posR.y += 2.0f;
			}
			else if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD5) == true)
			{//V�L�[���������Ƃ��@�@�@���p�x�̈ړ���
				m_posR.y -= 2.0f;
			}

			if (pCInputJoyPad->GetPress(CInputJoypad::STICK_R_LEFT) == true)
			{// �J�����̈ړ�
				m_fAngle -= 0.02f;

				if (m_fAngle < -D3DX_PI)
				{//������
					m_fAngle += D3DX_PI * 2.0f;
				}
				//m_posV.y -= 2.0f;
			}
			else if (pCInputJoyPad->GetPress(CInputJoypad::STICK_R_RIGHT) == true)
			{
				m_fAngle += 0.02f;

				if (m_fAngle > D3DX_PI)
				{//������
					m_fAngle -= D3DX_PI * 2.0f;
				}
				//m_posV.y += 2.0f;
			}

			//===================================
			//�����_���v���C���[�ɒǏ]�悤�ɂ���
			//===================================
			m_posR.x = PlayerPos.x;
			m_posR.z = PlayerPos.z;
			m_posR.y = PlayerPos.y;

			m_posV.x = PlayerPos.x - sinf(m_fAngle)* MOVE_CAMERA;
			m_posV.z = PlayerPos.z - cosf(m_fAngle)* MOVE_CAMERA;	
		}
	
		////���_�E�����_�̍X�V
		//m_posVDest.x = PlayerPos.x + sinf(PlayerRot.y) * m_fLength;
		//m_posVDest.y = PlayerPos.y + m_fRange;
		//m_posVDest.z = PlayerPos.z + cosf(PlayerRot.y) * m_fLength;

		//m_posRDest.x = PlayerPos.x - sinf(m_fAngle) * 1.0f;
		//m_posRDest.y = PlayerPos.y;
		//m_posRDest.z = PlayerPos.z - cosf(m_fAngle) * 1.0f;

		//m_posV.x += (m_posVDest.x - m_posV.x) * 1.0f;
		//m_posV.z += (m_posVDest.z - m_posV.z) * 1.0f;
		//m_posR += (m_posRDest - m_posR) * 1.0f;

		/*m_posVDest.x = PlayerPos.x - sinf(PlayerRot.y);
		m_posVDest.z = PlayerPos.z - cosf(PlayerRot.y);
		m_posRDest.x = PlayerPos.x + sinf(m_fAngle) * MOVE_CAMERA;
		m_posRDest.z = PlayerPos.z + cosf(m_fAngle) * MOVE_CAMERA;*/

		//�ړ��̃f�o�b�N�p
		//CDebugProc::Print("�J����������@ �y���@�O�ړ��z�y���@���ړ��z�y���@��ړ��z�y���@�E�ړ��z�yNUM 1 ����]�z�yNUM 2�@�E��]�z\n");
		//�J�����̃f�o�b�N�ʒu
		CDebugProc::Print("�J����posV�̈ʒu :�y%.1f�z�y%.1f�z�y%.1f�z\n", m_posV.x, m_posV.y, m_posV.z);
		CDebugProc::Print("�J����posR�̈ʒu :�y%.1f�z�y%.1f�z�y%.1f�z\n", m_posR.x, m_posR.y, m_posR.z);
	}
	else if (pMode == CManager::MODE_RESULT)
	{
#if 1
		if (m_bResultCamera == false)
		{
			m_posV = D3DXVECTOR3(0.0f, 50.0f, -3550.0f);		//���_
			m_posR = D3DXVECTOR3(-150.0f, 50.0f, -3150.0f);		//�����_

			m_bResultCamera = true;
		}

		m_posV.z -= 4.0f;
		m_posR.z -= 4.0f;
#endif
	}
}
//=============================================================================
//�@�J�����̐���
//=============================================================================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		30000
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
//=============================================================================
//�@�Q�[���J�ڂ̎��ɏ����J����
//=============================================================================
void CCamera::Delete(void)
{
	CCamera *pCamere = CManager::GetCamera();
	pCamere->m_posV = D3DXVECTOR3(0.0f, 200.0f, 0.0f);				//���_�̏����l
	pCamere->m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	pCamere->m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	pCamere->m_fAngle = 0.0f;										//�J�����̊p�x
	pCamere->m_fLength = pCamere->m_posV.z - pCamere->m_posR.z;		//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	pCamere->m_fRange = pCamere->m_posV.y - pCamere->m_posR.y;		//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	pCamere->m_nCntTitle = 0;
	pCamere->m_bResultCamera = false;
}
//=============================================================================
//�@�}�b�v�ړ��̍ۏ���������J����
//=============================================================================
void CCamera::DeleteCamera(void)
{
	CCamera *pCamere = CManager::GetCamera();
	pCamere->m_posV = D3DXVECTOR3(0.0f, 200.0f, 0.0f);				//���_�̏����l
	pCamere->m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	pCamere->m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�@���̌���
	pCamere->m_fAngle = 0.0f;										//�J�����̊p�x
	pCamere->m_fLength = pCamere->m_posV.z - pCamere->m_posR.z;		//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	pCamere->m_fRange = pCamere->m_posV.y - pCamere->m_posR.y;		//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	pCamere->m_nCntTitle = 0;
	pCamere->m_bResultCamera = false;
}