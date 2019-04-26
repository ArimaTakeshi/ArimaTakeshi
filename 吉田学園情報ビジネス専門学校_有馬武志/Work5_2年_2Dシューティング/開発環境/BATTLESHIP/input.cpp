//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECTINPUT8 CInput::m_pInput = NULL;
D3DXVECTOR3 CInputMouse::m_MousePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CInput::~CInput()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//NULL�`�F�b�N
	if (m_pInput == NULL)
	{//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CInput::Uninit(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�������
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CInput::Update(void)
{

}


//��������h���N���X�̃L�[�{�[�h


//===============================================================================
//�@�L�[�{�[�h�̃f�t�H���g�R���X�g���N�^
//===============================================================================
CInputKeyBoard::CInputKeyBoard()
{
	//�L�[���̃N���A
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;			//�L�[�{�[�h�̓��͏��i�v���X���j
		m_aKeyStateTrigger[nCnt] = 0;	//�L�[�{�[�h�̓��͏�� (�g���K�[���)
	}
}
//===============================================================================
//�@�L�[�{�[�h�̃f�X�g���N�^
//===============================================================================
CInputKeyBoard::~CInputKeyBoard()
{

}
//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance,hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}
//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//���g���K�[�̂Ƃ��͈�ԏ�
			m_aKeyState[nCntKey] = aKeyState[nCntKey];																//�L�[�{�[�h�̓��͏��ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}
//===============================================================================
// �L�[�{�[�h�̃N���G�C�g
//===============================================================================
CInputKeyBoard *CInputKeyBoard::Create(HINSTANCE hInstance,HWND hWnd)
{
	CInputKeyBoard *pCInputKeyBoard = NULL;

	//NULL�`�F�b�N
	if (pCInputKeyBoard == NULL)
	{
		//���I�m��
		pCInputKeyBoard = new CInputKeyBoard;

		//NULL�`�F�b�N
		if (pCInputKeyBoard != NULL)
		{
			//����������
			pCInputKeyBoard->Init(hInstance, hWnd);
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

	return pCInputKeyBoard;
}
//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool CInputKeyBoard::GetKeyboardPress(int nKey)
{
	return (m_aKeyState[nKey] & 0x80) ? true : false;
}
//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool CInputKeyBoard::GetKeyboardTrigger(int nKey)
{
	return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�S�{�^�����)���擾
//=========================================================================================================================
bool CInputKeyBoard::GetKeyboardAny(int nNumber)
{
	if (nNumber == 1)
	{
		for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
		{
			if (m_aKeyStateTrigger[nCount] == 0x80)
			{
				return true;
			}
		}
	}
	return false;
}

//��������h���N���X�̃}�E�X


//===============================================================================
//�@�}�E�X�̃f�t�H���g�R���X�g���N�^
//===============================================================================
CInputMouse::CInputMouse()
{
	//�L�[���̃N���A
	for (int nCnt = 0; nCnt < NUM_MOUSE_MAX; nCnt++)
	{
		m_moveRect;					// ��ʏ�œ�����͈�
		m_x = 0;					// X���W
		m_y = 0;					// Y���W
		m_lButton = 0;				// ���{�^��
		m_rButton = 0;				// �E�{�^��
		m_cButton = 0;				// �^�񒆃{�^��
		m_moveAdd = 0;				// �ړ���
		m_imgRect;					// �}�E�X�p�摜��`
		m_imgWidth = 0;				// �}�E�X�摜��
		m_imgHeight = 0;			// �}�E�X�摜����
		m_MousePos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		m_Pos, m_WPos;
		m_MouseState;
		m_MouseStatePress = {};		// �}�E�X�̓��͏��i�v���X���j
		m_MouseStateTrigger = {};	// �}�E�X�̓��͏��i�g���K�[���j
		m_MouseStateRelease = {};	// �}�E�X�̓��͏��i�����[�X���
	}
}
//===============================================================================
//�@�}�E�X�̃f�X�g���N�^
//===============================================================================
CInputMouse::~CInputMouse()
{

}
//=============================================================================
// �}�E�X�̏���������
//=============================================================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h�̏ꍇ
	if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}
//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void CInputMouse::Uninit(void)
{
	CInput::Uninit();
}
//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
void CInputMouse::Update(void)
{
	//�ϐ��錾
	int nCntMouse;

	POINT pt;
	GetCursorPos(&pt); 
	
	//POINT�^��D3DXVECTOR3�^�̕��ɑ������
	m_MousePos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(m_MouseState), &m_MouseState)))
	{
		for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			m_MouseStateRelease.rgbButtons[nCntMouse] = (m_MouseStatePress.rgbButtons[nCntMouse] ^ m_MouseState.rgbButtons[nCntMouse]) & m_MouseStatePress.rgbButtons[nCntMouse];
			m_MouseStateTrigger.rgbButtons[nCntMouse] = (m_MouseStatePress.rgbButtons[nCntMouse] ^ m_MouseState.rgbButtons[nCntMouse]) & m_MouseState.rgbButtons[nCntMouse];
			m_MouseStatePress.rgbButtons[nCntMouse] = m_MouseState.rgbButtons[nCntMouse];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}
//===============================================================================
// �}�E�X�̃N���G�C�g
//===============================================================================
CInputMouse *CInputMouse::Create(HINSTANCE hInstance, HWND hWnd)
{
	CInputMouse *pCInputMouse = NULL;

	//NULL�`�F�b�N
	if (pCInputMouse == NULL)
	{
		//���I�m��
		pCInputMouse = new CInputMouse;

		//NULL�`�F�b�N
		if (pCInputMouse != NULL)
		{
			//����������
			pCInputMouse->Init(hInstance, hWnd);
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

	return pCInputMouse;
}
//=========================================================================================================================
// �}�E�X�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool CInputMouse::GetMousePress(int nKey)
{
	return (m_MouseStatePress.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool CInputMouse::GetMouseTrigger(int nKey)
{
	return (m_MouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool CInputMouse::GetMouseRelease(int nKey)
{
	return (m_MouseStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}