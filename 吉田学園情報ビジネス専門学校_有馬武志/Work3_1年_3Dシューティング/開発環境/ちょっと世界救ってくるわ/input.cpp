//=========================================================================================================================
//
// 入力処理 [input.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "dinput.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// キーの最大数
#define	NUM_MOUSE_MAX		(8)					// マウスの最大数

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECTINPUT8 g_pInput = NULL;					//DirerctInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		//入力デバイス（キーボード）へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];					//キーボードの入力情報（プレス情報）
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];			//キーボードの入力情報 (トリガー情報)

//============
//  マウス
//============
LPDIRECTINPUTDEVICE8		g_pDevMouse = NULL;						// 入力デバイス（マウス）へのポインタ
POINT					    Pos, WPos;
DIMOUSESTATE2				g_MouseState;
DIMOUSESTATE2				g_aMouseStatePress;						// マウスの入力情報（プレス情報）
DIMOUSESTATE2				g_aMouseStateTrigger;					// マウスの入力情報（トリガー情報）
DIMOUSESTATE2				g_aMouseStateRelease;					// マウスの入力情報（リリース情報

//=========================================================================================================================
// キーボードの初期化
//=========================================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat (&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel (hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	return S_OK;
}


//=========================================================================================================================
// キーボードの更新処理
//=========================================================================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];			//※トリガーのときは一番上
			g_aKeyState[nCntKey] = aKeyState[nCntKey];																//キーボードの入力情報保存
		}  
	}
	else
	{
		g_pDevKeyboard->Acquire();		//キーボードへのアクセス権を獲得
	}
}

//=========================================================================================================================
// キーボードの入+力情報(プレス情報)を取得
//=========================================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=========================================================================================================================
// キーボードの入力情報(トリガー情報)を取得
//=========================================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=========================================================================================================================
// キーボードの入力情報(リリース情報)を取得
//=========================================================================================================================
//bool GetKeyboardTrigger(int nKey)
//{
//	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
//}
//=========================================================================================================================
// マウスの初期化
//=========================================================================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// 入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	// 軸モードを設定（相対値モードに設定）
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData = DIPROPAXISMODE_ABS; // 絶対値モードの場合
	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// マウスへのアクセス権を獲得(入力制御開始)
	g_pDevMouse->Acquire();

	return S_OK;
}

//=========================================================================================================================
// マウスの更新処理
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
// マウスの入力情報(プレス情報)を取得
//=========================================================================================================================
bool GetMousePress(int nKey)
{
	return (g_aMouseStatePress.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// マウスの入力情報(トリガー情報)を取得
//=========================================================================================================================
bool GetMouseTrigger(int nKey)
{
	return (g_aMouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// マウスの入力情報(リリース情報)を取得
//=========================================================================================================================
bool GetMouseRelease(int nKey)
{
	return (g_aMouseStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// マウスの入力情報(ポインター)を取得
//=========================================================================================================================
DIMOUSESTATE2 GetMousePointer(void)
{
	return g_MouseState;
}
//=========================================================================================================================
// キーボードの終了処理
//=========================================================================================================================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の開放
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// 入力デバイス(マウス)の開放
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();		// マウスへのアクセス権を放棄
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//DirectInputオブジェクトの開放
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}




