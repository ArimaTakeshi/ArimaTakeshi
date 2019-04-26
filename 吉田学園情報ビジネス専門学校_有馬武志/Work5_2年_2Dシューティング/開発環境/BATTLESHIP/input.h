//=============================================================================
//
// メイン処理 [input.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// キーの最大数
#define	NUM_MOUSE_MAX		(8)					// マウスの最大数

//=====================
//	   基本クラス
//=====================
class CInput
{
public://誰でも扱える
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected://個人でのみ使う
	static LPDIRECTINPUT8 m_pInput;			//DirerctInputオブジェクトへのポインタ //全員が一個だけもっていればいいからstatic
	LPDIRECTINPUTDEVICE8 m_pDevice;			//入力デバイス（キーボード）へのポインタ
};

//=====================
//	   派生クラス
//=====================
class CInputKeyBoard : public CInput 
{
public://誰でも扱える
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nKey);		//キーボードプレス
	bool GetKeyboardTrigger(int nKey);		//キーボードトリガー
	bool GetKeyboardAny(int nNumber);		//キーボードトリガー
	static CInputKeyBoard *Create(HINSTANCE hInstance, HWND hWnd);
private://個人でのみ使う
	BYTE m_aKeyState[NUM_KEY_MAX];			//キーボードの入力情報（プレス情報）
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//キーボードの入力情報 (トリガー情報)
};

//=====================
//	   派生クラス
//=====================
class CInputMouse : public CInput
{
public://誰でも扱える
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetMousePress(int Key);			// マウスプレス
	bool GetMouseTrigger(int Key);			// マウストリガー
	bool GetMouseRelease(int Key);			// マウスリリース
	//DIMOUSESTATE2 GetMousePointer(void);
	static CInputMouse *Create(HINSTANCE hInstance, HWND hWnd);
	static D3DXVECTOR3 *GetMousePos(void) { return &m_MousePos; }
	
private://個人でのみ使う
	RECT					m_moveRect;				// 画面上で動ける範囲
	int						m_x;					// X座標
	int						m_y;					// Y座標
	bool					m_lButton;				// 左ボタン
	bool					m_rButton;				// 右ボタン
	bool					m_cButton;				// 真ん中ボタン
	int						m_moveAdd;				// 移動量
	RECT					m_imgRect;				// マウス用画像矩形
	int						m_imgWidth;				// マウス画像幅
	int						m_imgHeight;			// マウス画像高さ
	POINT					m_Pos, m_WPos;
	static D3DXVECTOR3		m_MousePos;
	DIMOUSESTATE2			m_MouseState;
	DIMOUSESTATE2			m_MouseStatePress;		// マウスの入力情報（プレス情報）
	DIMOUSESTATE2			m_MouseStateTrigger;	// マウスの入力情報（トリガー情報）
	DIMOUSESTATE2			m_MouseStateRelease;	// マウスの入力情報（リリース情報
};

#endif