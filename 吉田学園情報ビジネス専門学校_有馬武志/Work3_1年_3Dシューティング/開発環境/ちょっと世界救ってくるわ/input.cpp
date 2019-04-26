//=========================================================================================================================
//
// ���͏��� [input.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "dinput.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// �L�[�̍ő吔
#define	NUM_MOUSE_MAX		(8)					// �}�E�X�̍ő吔

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECTINPUT8 g_pInput = NULL;					//DirerctInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h�̓��͏��i�v���X���j
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏�� (�g���K�[���)

//============
//  �}�E�X
//============
LPDIRECTINPUTDEVICE8		g_pDevMouse = NULL;						// ���̓f�o�C�X�i�}�E�X�j�ւ̃|�C���^
POINT					    Pos, WPos;
DIMOUSESTATE2				g_MouseState;
DIMOUSESTATE2				g_aMouseStatePress;						// �}�E�X�̓��͏��i�v���X���j
DIMOUSESTATE2				g_aMouseStateTrigger;					// �}�E�X�̓��͏��i�g���K�[���j
DIMOUSESTATE2				g_aMouseStateRelease;					// �}�E�X�̓��͏��i�����[�X���

//=========================================================================================================================
// �L�[�{�[�h�̏�����
//=========================================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat (&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel (hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return S_OK;
}


//=========================================================================================================================
// �L�[�{�[�h�̍X�V����
//=========================================================================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//���g���K�[�̂Ƃ��͈�ԏ�
			g_aKeyState[nCntKey] = aKeyState[nCntKey];																//�L�[�{�[�h�̓��͏��ۑ�
		}  
	}
	else
	{
		g_pDevKeyboard->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=========================================================================================================================
// �L�[�{�[�h�̓�+�͏��(�v���X���)���擾
//=========================================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
//bool GetKeyboardTrigger(int nKey)
//{
//	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
//}
//=========================================================================================================================
// �}�E�X�̏�����
//=========================================================================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
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
	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevMouse->Acquire();

	return S_OK;
}

//=========================================================================================================================
// �}�E�X�̍X�V����
//=========================================================================================================================
void UpdateMouse(void)
{
	int nCntMouse;

	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(g_MouseState), &g_MouseState)))
	{
		for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			g_aMouseStateRelease.rgbButtons[nCntMouse] = (g_aMouseStatePress.rgbButtons[nCntMouse] ^ g_MouseState.rgbButtons[nCntMouse]) & g_aMouseStatePress.rgbButtons[nCntMouse];
			g_aMouseStateTrigger.rgbButtons[nCntMouse] = (g_aMouseStatePress.rgbButtons[nCntMouse] ^ g_MouseState.rgbButtons[nCntMouse]) & g_MouseState.rgbButtons[nCntMouse];
			g_aMouseStatePress.rgbButtons[nCntMouse] = g_MouseState.rgbButtons[nCntMouse];
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool GetMousePress(int nKey)
{
	return (g_aMouseStatePress.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetMouseTrigger(int nKey)
{
	return (g_aMouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool GetMouseRelease(int nKey)
{
	return (g_aMouseStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�|�C���^�[)���擾
//=========================================================================================================================
DIMOUSESTATE2 GetMousePointer(void)
{
	return g_MouseState;
}
//=========================================================================================================================
// �L�[�{�[�h�̏I������
//=========================================================================================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���̓f�o�C�X(�}�E�X)�̊J��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();		// �}�E�X�ւ̃A�N�Z�X�������
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}




