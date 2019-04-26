//=============================================================================
//
// 入力処理 [input.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define JOYPAD_MAX			(2)		// ジョイパッドの接続数
#define JOYPAD_MAX_BUTTON	(14)	// ジョイパッドのボタン数
#define JOYPAD_MAX_STICK	(2)		// ジョイパッドの入力個数
#define LEFT_STICK			(0)		// ジョイパッドのLスティックの番号
#define RIGHT_STICK			(1)		// ジョイパッドのRスティックの番号
#define JOYPAD_MAX_KEY		(JOYPAD_MAX_BUTTON + JOYPAD_MAX_STICK * 4)	// ジョイパッドの入力個数
//*****************************************************************************
// 列挙の定義
//*****************************************************************************
typedef enum
{//入力情報
	INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT,
	INPUT_START, INPUT_BACK,
	INPUT_L2, INPUT_R2, INPUT_L1, INPUT_R1,
	INPUT_A, INPUT_B, INPUT_X, INPUT_Y,
	INPUT_LS_R, INPUT_LS_L, INPUT_LS_U, INPUT_LS_D,
	INPUT_RS_R, INPUT_RS_L, INPUT_RS_U, INPUT_RS_D,
	INPUT_MAX
}JOY_INPUT;
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CInput
{
public:
#define	NUM_KEY_MAX			(256)			// キーの最大数
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected://*****************************************************************************
		//変数宣言//***********************************************************************
	static LPDIRECTINPUT8	m_pInput;				//DIRECTINPUTオブジェクトへのポインタ
	LPDIRECTINPUTDEVICE8	m_pDevice;	//入力デバイスへのキーボードのポインタ
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard() {};
	~CInputKeyboard() {};

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Skip(void);
	bool GetPressOld(int nKey);
	bool GetPress(int nKey);

	bool GetAllTrigger(void);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetQuick(int nKey, bool bUse);
	bool GetRun(int nKey, bool bRun);
	int *GetTrigger(void);
	bool GetTPress(int nKey);
	void GetCount(void);

private://*****************************************************************************
		//変数宣言//***********************************************************************
	BYTE					m_aKeyState[NUM_KEY_MAX];				//キーボード入力情報(プレス情報)
	BYTE					m_aKeyStateOld[NUM_KEY_MAX];				//キーボード入力情報(プレス情報)
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CInputJoyPad : public CInput
{
public:
	CInputJoyPad();
	~CInputJoyPad();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void InputUpdate(bool bInput, int input);
	void Skip(void);

	bool GetConnect(void)	 { return m_abConnection; };

	bool GetAllTrigger(void);
	bool GetPress(int input)	 { return m_bButton[input]; };
	bool GetTrigger(int input) { return (m_bButtonOld[input] ? false : (m_bButton[input] ? true : false)); };
	bool GetTPress(int input) { if (m_nPress[input] < 30) { return GetTrigger(input); } else if (m_nPress[input] % 2 == 0) { return m_bButton[input]; } else { return false; } return false; };
	bool GetRelease(int input) { return (m_bButtonOld[input] ? (m_bButton[input] ? false : true) : false); };
	float GetfStickAngle(int nStick) { return m_fStickAngle[nStick]; };
	void ReSetPress(void);
	void NoInput(int input)		{ m_bInput[input] = false; m_nPress[input] = 0; }
	int &GetnPress(int input)	{ return m_nPress[input]; }
	int &GetnRelease(int input) { return m_nRelease[input]; }
	int &GetnStickX(int nStick) { return m_nStickX[nStick]; };
	int &GetnStickY(int nStick) { return m_nStickY[nStick]; };
	bool GetStickDefeat(int nStick) 
	{//スティックが倒れていればtrue
		int nPlus = nStick * 4; 
		if (m_bButton[INPUT_LS_R + nPlus] || m_bButton[INPUT_LS_L + nPlus] || m_bButton[INPUT_LS_U + nPlus] || m_bButton[INPUT_LS_D + nPlus]) { return true; }
		return false;
	};

private:
	bool Connect(void);

	static int m_nNumPad;					//ジョイパッドの総数
	int  m_nID;								//ジョイパッドの番号
	bool m_abConnection;					// ジョイパッドの接続状態
	int		m_nStickX[2];
	int		m_nStickY[2];
	bool	m_bInput[JOYPAD_MAX_KEY];		//入力制限の有無

	int	 m_nPress[JOYPAD_MAX_KEY];			//押し続けているF数
	int	 m_nRelease[JOYPAD_MAX_KEY];		//離したF数
	bool m_bButtonOld[JOYPAD_MAX_KEY];		//前回のボタン
	bool m_bButton[JOYPAD_MAX_KEY];			//今回のボタン
	float m_fStickAngle[JOYPAD_MAX_STICK];	//スティックの角度
};
#endif
