//=============================================================================
//
// ���͏��� [input.cpp]
// Author :Ryo Sugimoto
//
//=============================================================================
#include "input.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECTINPUT8	CInput::m_pInput = NULL;		//DIRECTINPUT�I�u�W�F�N�g�ւ̃|�C���^
int CInputJoyPad::m_nNumPad = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}
//=============================================================================
// �f�X�X�g���N�^
//=============================================================================
CInput::~CInput() {}
//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput, NULL)))
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
	if (m_pInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if(FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	int *nQuick = GetTrigger();
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		nQuick[nCntKey] = 0;
	}
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	if (m_pDevice != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h���͏��ۑ�
			//g_aKeyStateTrigger[nCntKey] = ((g_aKeyState[nCntKey] + 1) * aKeyState[nCntKey]) % 2;
		}
	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X���l��
	}
}
//=============================================================================
// �L�[�{�[�h�̓��͏������ɂ��炷
//=============================================================================
void CInputKeyboard::Skip(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
		m_aKeyState[nCntKey] = false;	//�L�[�{�[�h���͏��ۑ�
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{	//�L�[�{�[�h�̓��͏��(�v���X���)���l��
		return(m_aKeyState[nKey] & 0x080) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(1F�O�̃v���X���)���擾
//=============================================================================
bool  CInputKeyboard::GetPressOld(int nKey)
{//�L�[�{�[�h�̓��͏��(1F�O�̃v���X���)���l��
	return(m_aKeyStateOld[nKey] & 0x080) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�S�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetAllTrigger(void)
{
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		if (GetTrigger(nCount)) { return true; }
	}
	return false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{	//�L�[�{�[�h�̓��͏��(�v���X���)���l��
	if (GetPress(nKey) && !GetPressOld(nKey)) { return true; }
	return false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{	//�L�[�{�[�h�̓��͏��(�v���X���)���l��
	if (!GetPress(nKey) && GetPressOld(nKey)) { return true; }
	return false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(Quick���)���擾
//=============================================================================
bool CInputKeyboard::GetQuick(int nKey, bool bUse)
{
	static int nTime = 0;				//�A�����͐����p
	int nCntKeyboard;
	bool bQuick = false;

	int *nQuick = GetTrigger();
	if (!bUse)
	{//�J�E���g�����͊m�F
		nTime--;
		for (nCntKeyboard = 0; nCntKeyboard < NUM_KEY_MAX; nCntKeyboard++)
		{//���Ԍo�ߗp
			nQuick[nCntKeyboard]--;
		}
	}
	else
	{
		if (GetTrigger(nKey))
		{//Trigger���͊m�F
			if (nQuick[nKey] > 0 && nTime < 0)
			{//2�����
				nQuick[nKey] = 0;
				bQuick = true;
				nTime = 35;	//�A�����͐��� 35F
			}
			else
			{//1�x��
				nQuick[nKey] = 20;
				bQuick = false;
			}
		}
	}

	return bQuick;
}
//=============================================================================
// �_�b�V������
//=============================================================================
bool CInputKeyboard::GetRun(int nKey, bool bRun)
{//�L�[�{�[�h�̓��͏��(�v���X���)���l��
	int *nQuick = GetTrigger();

	if (GetTrigger(nKey) || bRun)
	{//Trigger���͊m�F
		if (bRun == true)
		{
			nQuick[nKey] = 0;
			if (GetPress(nKey) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (nQuick[nKey] > 0) { return true; }
			nQuick[nKey] = 15;
		}
	}
	return false;
}
//=========================================================================================================//
// * �v���C���[�̏��������
//=========================================================================================================//
int *CInputKeyboard::GetTrigger(void)
{
	static int nQuick[NUM_KEY_MAX];		//�S�ẴL�[���擾�̂���

	return &nQuick[0];
}
//=============================================================================
// �_�b�V������
//=============================================================================
bool CInputKeyboard::GetTPress(int nKey)
{
	int *nQuick = GetTrigger();

	if (nQuick[nKey] > 30 && nQuick[nKey] % 3 == 0)
	{//30F�ȏ㉟���Ă���
		return GetPress(nKey);
	}
	else if(nQuick[nKey] <= 30)
	{
		return GetTrigger(nKey);
	}

	return false;
}
//=============================================================================
// �J�E���g
//=============================================================================
void CInputKeyboard::GetCount(void)
{
	int *nQuick = GetTrigger();
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		if(GetPress(nCount)){ nQuick[nCount]++; }
		else { nQuick[nCount] = 0; }
	}
}

//=============================================================================
// �W���C�p�b�h�N���X�̃R���X�g���N�^
//=============================================================================
CInputJoyPad::CInputJoyPad()
{
	m_abConnection = false;
	m_nID = m_nNumPad;
	m_nNumPad++;
}

//=============================================================================
// �W���C�p�b�h�N���X�̃f�X�g���N�^
//=============================================================================
CInputJoyPad::~CInputJoyPad()
{

}
//=============================================================================
// �W���C�p�b�h�N���X�̐ڑ����菈��
//=============================================================================
bool CInputJoyPad::Connect(void)
{
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂�", "", MB_OK );
		// �f�b�h�]�[���̐ݒ�
		if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}

		if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}

		m_abConnection = true;
	}
	else
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂���", "", MB_OK);
		m_abConnection = false;
	}

	return m_abConnection;
}
//=============================================================================
// �W���C�p�b�h�N���X�̏���������
//=============================================================================
void CInputJoyPad::Init(void)
{
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂�", "", MB_OK );
		// �f�b�h�]�[���̐ݒ�
		if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}

		if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}

		m_abConnection = true;
	}
	else
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂���", "", MB_OK);
		m_abConnection = false;
	}

	//���͏��̏�����
	for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
	{//�{�^���̏�����
		m_bInput[nCntButton] = true;
		m_bButtonOld[nCntButton] = false;
		m_bButton[nCntButton] = false;
		m_nPress[nCntButton] = 0;
		m_nRelease[nCntButton] = 0;
	}
	m_nPress[LEFT_STICK] = 0; m_nPress[RIGHT_STICK] = 0;
	m_fStickAngle[LEFT_STICK] = 99.9f; m_fStickAngle[RIGHT_STICK] = 99.9f;
}

//=============================================================================
// �W���C�p�b�h�N���X�̏I������
//=============================================================================
void CInputJoyPad::Uninit(void)
{
	m_nNumPad--;
	XInputEnable(false);
}

//=============================================================================
// �W���C�p�b�h�N���X�̍X�V����
//=============================================================================
void CInputJoyPad::Update(void)
{
	if(Connect())
	{//�q�����Ă����
		// �W���C�p�b�h���̎擾
		XINPUT_STATE state;

		XInputGetState(m_nID, &state);
		for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
		{//��F������
			m_bButtonOld[nCntButton] = m_bButton[nCntButton];
			m_bButton[nCntButton] = false;
			if (m_nPress[nCntButton] > 999999) { m_nPress[nCntButton] = 999; }
			if (m_nRelease[nCntButton] < -999999) { m_nRelease[nCntButton] = -999; }
		}
		//�{�^��
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ? true : false), 0);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ? true : false), 1);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ? true : false), 2);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ? true : false), 3);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_START ? true : false), 4);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK ? true : false), 5);
		InputUpdate(state.Gamepad.bLeftTrigger > 0, 6);
		InputUpdate(state.Gamepad.bRightTrigger > 0, 7);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ? true : false), 8);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ? true : false), 9);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_A ? true : false), 10);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_B ? true : false), 11);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_X ? true : false), 12);
		InputUpdate((state.Gamepad.wButtons & XINPUT_GAMEPAD_Y ? true : false), 13);
		//L�X�e�B�b�N
		InputUpdate(state.Gamepad.sThumbLX > 10000, 14);
		InputUpdate(state.Gamepad.sThumbLX < -10000, 15);
		InputUpdate(state.Gamepad.sThumbLY > 10000, 16);
		InputUpdate(state.Gamepad.sThumbLY < -10000, 17);
		//R�X�e�B�b�N
		InputUpdate(state.Gamepad.sThumbRX > 10, 18);
		InputUpdate(state.Gamepad.sThumbRX < -10, 19);
		InputUpdate(state.Gamepad.sThumbRY > 10, 20);
		InputUpdate(state.Gamepad.sThumbRY < -10, 21);

		m_fStickAngle[LEFT_STICK] = atan2f(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		m_fStickAngle[RIGHT_STICK] = atan2f(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);

		m_nStickX[0] = state.Gamepad.sThumbLX;
		m_nStickX[1] = state.Gamepad.sThumbRX;
		m_nStickY[0] = state.Gamepad.sThumbLY;
		m_nStickY[1] = state.Gamepad.sThumbRY;

		for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
		{//���͐�������
			if (GetTrigger(nCntButton)) { m_bInput[nCntButton] = true; }
		}
	}
}
//=============================================================================
// �W���C�p�b�h�@���͎��̍X�V����
//=============================================================================
void CInputJoyPad::InputUpdate(bool bInput, int input)
{
	if(bInput)
	{ 
		m_bButton[input] = true; 
		if (m_nPress[input] < 0) { m_nPress[input] = 0; }
		if (m_bInput[input]) { m_nPress[input]++; }
		m_nRelease[input] = 0;
	}
	else 
	{
		if (m_nPress[input] > 0) { m_nPress[input] *= -1; }
		m_nRelease[input]--;
	}
}
//=============================================================================
// �W���C�p�b�h�@�S�{�^���g���K�[����
//=============================================================================
bool CInputJoyPad::GetAllTrigger(void)
{
	for (int nCount = 0; nCount < INPUT_MAX; nCount++)
	{
		if ((m_bButtonOld[nCount] ? false : (m_bButton[nCount] ? true : false)))
		{
			return true;
		}
	}
	return false;
}
//=============================================================================
// �W���C�p�b�h�@������F�������Z�b�g
//=============================================================================
void CInputJoyPad::ReSetPress(void)
{
	for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
	{//�{�^���̏�����
		m_nPress[nCntButton] = 0;
	}
}