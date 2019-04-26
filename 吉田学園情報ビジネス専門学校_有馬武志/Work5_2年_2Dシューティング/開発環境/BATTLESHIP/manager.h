//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "result.h"
#include "title.h"
#include "game.h"
#include "sound.h"
#include "pause.h"
#include "tutorial.h"

//=====================
//  ��{�N���X
//=====================
class CManager
{
public://�N�ł�������
	typedef enum
	{
		MODE_TITLE = 0,		//�^�C�g��
		MODE_TUTORIAL,		//�`���[�g���A��
		MODE_GAME,			//�Q�[��
		MODE_RESULT,		//���U���g
		MODE_MAX			//�ő吔
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindows);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CInputKeyBoard *GetInput(void) { return m_pInputKeyBoard; }
	static CInputMouse *GetInputMouse(void) { return m_pInputMouse; }
	static CSound *GetSound(void) { return m_pSound; }

private://�l�ł̂ݎg��
	static CRenderer *m_pRenderer;
	static CSound *m_pSound;
	static CInputKeyBoard *m_pInputKeyBoard;
	static CInputMouse *m_pInputMouse;
	static CTitle *m_pTitle;
	static CTutorial *m_pTutorial;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static MODE m_mode;
};
#endif