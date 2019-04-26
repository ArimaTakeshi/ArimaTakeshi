//=============================================================================
//
// ���C������ [input.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// �L�[�̍ő吔
#define	NUM_MOUSE_MAX		(8)					// �}�E�X�̍ő吔

//=====================
//	   ��{�N���X
//=====================
class CInput
{
public://�N�ł�������
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;
protected://�l�ł̂ݎg��
	static LPDIRECTINPUT8 m_pInput;			//DirerctInput�I�u�W�F�N�g�ւ̃|�C���^ //�S��������������Ă���΂�������static
	LPDIRECTINPUTDEVICE8 m_pDevice;			//���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
};

//=====================
//	   �h���N���X
//=====================
class CInputKeyBoard : public CInput 
{
public://�N�ł�������
	CInputKeyBoard();
	~CInputKeyBoard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nKey);		//�L�[�{�[�h�v���X
	bool GetKeyboardTrigger(int nKey);		//�L�[�{�[�h�g���K�[
	bool GetKeyboardAny(int nNumber);		//�L�[�{�[�h�g���K�[
	static CInputKeyBoard *Create(HINSTANCE hInstance, HWND hWnd);
private://�l�ł̂ݎg��
	BYTE m_aKeyState[NUM_KEY_MAX];			//�L�[�{�[�h�̓��͏��i�v���X���j
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];	//�L�[�{�[�h�̓��͏�� (�g���K�[���)
};

//=====================
//	   �h���N���X
//=====================
class CInputMouse : public CInput
{
public://�N�ł�������
	CInputMouse();
	~CInputMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetMousePress(int Key);			// �}�E�X�v���X
	bool GetMouseTrigger(int Key);			// �}�E�X�g���K�[
	bool GetMouseRelease(int Key);			// �}�E�X�����[�X
	//DIMOUSESTATE2 GetMousePointer(void);
	static CInputMouse *Create(HINSTANCE hInstance, HWND hWnd);
	static D3DXVECTOR3 *GetMousePos(void) { return &m_MousePos; }
	
private://�l�ł̂ݎg��
	RECT					m_moveRect;				// ��ʏ�œ�����͈�
	int						m_x;					// X���W
	int						m_y;					// Y���W
	bool					m_lButton;				// ���{�^��
	bool					m_rButton;				// �E�{�^��
	bool					m_cButton;				// �^�񒆃{�^��
	int						m_moveAdd;				// �ړ���
	RECT					m_imgRect;				// �}�E�X�p�摜��`
	int						m_imgWidth;				// �}�E�X�摜��
	int						m_imgHeight;			// �}�E�X�摜����
	POINT					m_Pos, m_WPos;
	static D3DXVECTOR3		m_MousePos;
	DIMOUSESTATE2			m_MouseState;
	DIMOUSESTATE2			m_MouseStatePress;		// �}�E�X�̓��͏��i�v���X���j
	DIMOUSESTATE2			m_MouseStateTrigger;	// �}�E�X�̓��͏��i�g���K�[���j
	DIMOUSESTATE2			m_MouseStateRelease;	// �}�E�X�̓��͏��i�����[�X���
};

#endif