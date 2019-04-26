//=============================================================================
//
// �}�l�[�W���[���� [Manager.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "renderer.h"
#include "input.h"
#include "Fade.h"
class CSound;
class CScenePlayer;
class CDungeon;
class CTitle;
class CGame;
class CSelect;
class CvsSelect;
class CVersus;
class CPractice;
class CPlayer;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER		(2)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE,
		MODE_SELECT,
		MODE_PRACTICE,
		MODE_VS_SELECT,
		MODE_VERSUS,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static CRenderer *GetRenderer(void)			{ return m_pRenderer; }
	static CInputKeyboard *GetInputKey(void)	{ return m_pInputKey; }
	static CInputJoyPad *&GetInputJoyPad(int nID) { return m_pJoyPad[nID]; }
	static CScenePlayer *&GetPlayer(int nID)	{ return m_pPlayer[nID]; }
	static CPlayer *&GetPlayer0(void) { return m_pPlayer0; }
	static CScenePlayer *&GetRandPlayer(void);
	static CScenePlayer *&GetNearPlayer(D3DXVECTOR3 pos);
	static CScenePlayer *&GetNearPlayer(D3DXVECTOR3 pos, float &fDistance);
	static CDungeon *&GetDungeon(void)			{ return m_pDungeon; }

	static void SetFade(MODE mode, int nEndCount);
	static void SetMode(void);
	static MODE *GetMode(void)		{ return &m_mode; }
	static CFade *GetFade(void)		{ return &m_Fade; }
	static int	&GetEndCount(void)	{ return m_nEndCount; }
	static CSound *&GetSound(void)	{ return m_pSound; }
	static CGame *&GetGame(void)	{ return m_pGame; }
	static CVersus *&GetVersus(void) { return m_pVersus; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static CRenderer		*m_pRenderer;
	static CInputKeyboard	*m_pInputKey;
	static CInputJoyPad		*m_pJoyPad[JOYPAD_MAX];
	static CPlayer			*m_pPlayer0;
	static CScenePlayer		*m_pPlayer[MAX_PLAYER];
	static CDungeon			*m_pDungeon;

	static MODE				m_mode;			//���[�h
	static MODE				m_NextMode;		//���̃��[�h
	static CFade			m_Fade;			//�t�F�[�h�{��
	static CSound			*m_pSound;		// �T�E���h�N���X�̃|�C���^
	static int				m_nEndCount;	//�t�F�[�h�܂ł̃J�E���g

	static CTitle			*m_pTitle;		//�^�C�g������
	static CSelect			*m_pSelect;		//�Z���N�g����
	static CvsSelect		*m_pvsSelect;	//�o�[�T�X�I������
	static CVersus			*m_pVersus;		//�o�[�T�X����

	static CGame			*m_pGame;		//�Q�[������
	static CPractice		*m_pPractice;		//�Q�[������
	static int				nCntTime;		//���ԃJ�E���g
};

#endif
