//=============================================================================
//
// 入力処理 [input.cpp]
// Author :Ryo Sugimoto
//
//=============================================================================
#include "input.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECTINPUT8	CInput::m_pInput = NULL;		//DIRECTINPUTオブジェクトへのポインタ
int CInputJoyPad::m_nNumPad = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}
//=============================================================================
// デスストラクタ
//=============================================================================
CInput::~CInput() {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// DirectInputオブジェクトの生成
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
// 終了処理
//=============================================================================
void CInput::Uninit(void)
{
	if (m_pInput != NULL)
	{// DirectInputオブジェクトの開放
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if(FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if(FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
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
// キーボードの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	if (m_pDevice != NULL)
	{// 入力デバイス(キーボード)の開放
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//キーボード入力情報保存
			//g_aKeyStateTrigger[nCntKey] = ((g_aKeyState[nCntKey] + 1) * aKeyState[nCntKey]) % 2;
		}
	}
	else
	{
		m_pDevice->Acquire();	//キーボードへのアクセス権獲得
	}
}
//=============================================================================
// キーボードの入力情報を次にずらす
//=============================================================================
void CInputKeyboard::Skip(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
		m_aKeyState[nCntKey] = false;	//キーボード入力情報保存
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{	//キーボードの入力情報(プレス情報)を獲得
		return(m_aKeyState[nKey] & 0x080) ? true : false;
}
//=============================================================================
// キーボードの入力情報(1F前のプレス情報)を取得
//=============================================================================
bool  CInputKeyboard::GetPressOld(int nKey)
{//キーボードの入力情報(1F前のプレス情報)を獲得
	return(m_aKeyStateOld[nKey] & 0x080) ? true : false;
}
//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{	//キーボードの入力情報(プレス情報)を獲得
	if (GetPress(nKey) && !GetPressOld(nKey)) { return true; }
	return false;
}
//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{	//キーボードの入力情報(プレス情報)を獲得
	if (!GetPress(nKey) && GetPressOld(nKey)) { return true; }
	return false;
}
//=============================================================================
// キーボードの入力情報(Quick情報)を取得
//=============================================================================
bool CInputKeyboard::GetQuick(int nKey, bool bUse)
{
	static int nTime = 0;				//連続入力制限用
	int nCntKeyboard;
	bool bQuick = false;

	int *nQuick = GetTrigger();
	if (!bUse)
	{//カウントか入力確認
		nTime--;
		for (nCntKeyboard = 0; nCntKeyboard < NUM_KEY_MAX; nCntKeyboard++)
		{//時間経過用
			nQuick[nCntKeyboard]--;
		}
	}
	else
	{
		if (GetTrigger(nKey))
		{//Trigger入力確認
			if (nQuick[nKey] > 0 && nTime < 0)
			{//2回入力
				nQuick[nKey] = 0;
				bQuick = true;
				nTime = 35;	//連続入力制限 35F
			}
			else
			{//1度目
				nQuick[nKey] = 20;
				bQuick = false;
			}
		}
	}

	return bQuick;
}
//=============================================================================
// ダッシュ判定
//=============================================================================
bool CInputKeyboard::GetRun(int nKey, bool bRun)
{//キーボードの入力情報(プレス情報)を獲得
	int *nQuick = GetTrigger();

	if (GetTrigger(nKey) || bRun)
	{//Trigger入力確認
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
// * プレイヤーの情報代入処理
//=========================================================================================================//
int *CInputKeyboard::GetTrigger(void)
{
	static int nQuick[NUM_KEY_MAX];		//全てのキー情報取得のため

	return &nQuick[0];
}
//=============================================================================
// ダッシュ判定
//=============================================================================
bool CInputKeyboard::GetTPress(int nKey)
{
	int *nQuick = GetTrigger();

	if (nQuick[nKey] > 30 && nQuick[nKey] % 3 == 0)
	{//30F以上押している
		return GetPress(nKey);
	}
	else if(nQuick[nKey] <= 30)
	{
		return GetTrigger(nKey);
	}

	return false;
}
//=============================================================================
// カウント
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
// ジョイパッドクラスのコンストラクタ
//=============================================================================
CInputJoyPad::CInputJoyPad()
{
	m_abConnection = false;
	m_nID = m_nNumPad;
	m_nNumPad++;
}

//=============================================================================
// ジョイパッドクラスのデストラクタ
//=============================================================================
CInputJoyPad::~CInputJoyPad()
{

}
//=============================================================================
// ジョイパッドクラスの接続判定処理
//=============================================================================
bool CInputJoyPad::Connect(void)
{
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		//MessageBox(0, "コントローラーが接続されています", "", MB_OK );
		// デッドゾーンの設定
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
		//MessageBox(0, "コントローラーが接続されていません", "", MB_OK);
		m_abConnection = false;
	}

	return m_abConnection;
}
//=============================================================================
// ジョイパッドクラスの初期化処理
//=============================================================================
void CInputJoyPad::Init(void)
{
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		//MessageBox(0, "コントローラーが接続されています", "", MB_OK );
		// デッドゾーンの設定
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
		//MessageBox(0, "コントローラーが接続されていません", "", MB_OK);
		m_abConnection = false;
	}

	//入力情報の初期化
	for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
	{//ボタンの初期化
		m_bButtonOld[nCntButton] = false;
		m_bButton[nCntButton] = false;
	}
	m_nPress[LEFT_STICK] = 0; m_nPress[RIGHT_STICK] = 0;
	m_fStickAngle[LEFT_STICK] = 99.9f; m_fStickAngle[RIGHT_STICK] = 99.9f;
}

//=============================================================================
// ジョイパッドクラスの終了処理
//=============================================================================
void CInputJoyPad::Uninit(void)
{
	m_nNumPad--;
	XInputEnable(false);
}

//=============================================================================
// ジョイパッドクラスの更新処理
//=============================================================================
void CInputJoyPad::Update(void)
{
	if(Connect())
	{//繋がっていれば
		// ジョイパッド情報の取得
		XINPUT_STATE state;

		XInputGetState(m_nID, &state);
		for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
		{
			m_bButtonOld[nCntButton] = m_bButton[nCntButton];
			m_bButton[nCntButton] = false;
		}
		//ボタン
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)		{ m_bButton[0] = true;   m_nPress[0]++; }  else { m_nPress[0] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)		{ m_bButton[1] = true;   m_nPress[1]++; }  else { m_nPress[1] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)		{ m_bButton[2] = true;   m_nPress[2]++; }  else { m_nPress[2] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)		{ m_bButton[3] = true;   m_nPress[3]++; }  else { m_nPress[3] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)			{ m_bButton[4] = true;   m_nPress[4]++; }  else { m_nPress[4] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)			{ m_bButton[5] = true;   m_nPress[5]++; }  else { m_nPress[5] = 0; }
		if (state.Gamepad.bLeftTrigger > 0)							{ m_bButton[6] = true;   m_nPress[6]++; }  else { m_nPress[6] = 0; }
		if (state.Gamepad.bRightTrigger > 0)						{ m_bButton[7] = true;   m_nPress[7]++; }  else { m_nPress[7] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)	{ m_bButton[8] = true;   m_nPress[8]++; }  else { m_nPress[8] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) { m_bButton[9] = true;   m_nPress[9]++; }  else { m_nPress[9] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)				{ m_bButton[10] = true;  m_nPress[10]++; } else { m_nPress[10] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)				{ m_bButton[11] = true;  m_nPress[11]++; } else { m_nPress[11] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)				{ m_bButton[12] = true;  m_nPress[12]++; } else { m_nPress[12] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)				{ m_bButton[13] = true;  m_nPress[13]++; } else { m_nPress[13] = 0; }
		//Lスティック
		if (state.Gamepad.sThumbLX > 10)							{ m_bButton[14] = true;  m_nPress[14]++; } else { m_nPress[14] = 0; }
		if (state.Gamepad.sThumbLX < -10)							{ m_bButton[15] = true;  m_nPress[15]++; } else { m_nPress[15] = 0; }
		if (state.Gamepad.sThumbLY > 10)							{ m_bButton[16] = true;  m_nPress[16]++; } else { m_nPress[16] = 0; }
		if (state.Gamepad.sThumbLY < -10)							{ m_bButton[17] = true;  m_nPress[17]++; } else { m_nPress[17] = 0; }
		//Rスティック
		if (state.Gamepad.sThumbRX > 10)							{ m_bButton[18] = true;  m_nPress[18]++; } else { m_nPress[18] = 0; }
		if (state.Gamepad.sThumbRX < -10)							{ m_bButton[19] = true;  m_nPress[19]++; } else { m_nPress[19] = 0; }
		if (state.Gamepad.sThumbRY > 10)							{ m_bButton[20] = true;  m_nPress[20]++; } else { m_nPress[20] = 0; }
		if (state.Gamepad.sThumbRY < -10)							{ m_bButton[21] = true;  m_nPress[21]++; } else { m_nPress[21] = 0; }

		m_fStickAngle[LEFT_STICK] = atan2f(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		m_fStickAngle[RIGHT_STICK] = atan2f(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
	}
}
//=============================================================================
// ジョイパッド　全ボタントリガー処理
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