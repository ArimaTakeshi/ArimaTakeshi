//=============================================================================
//
// マネージャー処理 [Manager.h]
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
#include "DebugLog.h"
class CCamera_Manager;
class CSound;
class CTitle;
class CGame;
class CSelect;
class CPractice;
class CCamera;
class CPlayer;
class CLight;
class CWind_Manager;
class CDungeon;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER	(2)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE,
		MODE_SELECT,
		MODE_PRACTICE,
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
	//static CScenePlayer *&GetPlayer(int nID)	{ return m_pPlayer[nID]; }
	//static CScenePlayer *&GetRandPlayer(void);
	//static CScenePlayer *&GetNearPlayer(D3DXVECTOR3 pos);
	//static CScenePlayer *&GetNearPlayer(D3DXVECTOR3 pos, float &fDistance);

	static void				SetFade(MODE mode, int nEndCount);
	static void				SetMode(void);
	static CDebugLog		*&GetDLog(void)			{ return m_pDebugLog; }
	static MODE				&GetMode(void)			{ return m_mode; }
	static CFade			&GetFade(void)			{ return m_Fade; }
	static int				&GetEndCount(void)		{ return m_nEndCount; }
	static CSound			*&GetSound(void)		{ return m_pSound; }
	static CDungeon			*&GetpDungeon(void)		{ return m_pDungeon; }
	static CGame			*&GetGame(void)			{ return m_pGame; }

	static CWind_Manager	*&GetWind(void)			{ return m_pWind; }
	static CCamera_Manager  *&GetCamera(void)		{ return m_pCamera; }
	static CLight			*&GetLight(void)		{ return m_pLight; }


	static CPlayer			*&GetPlayer(int nID)	{ return m_pPlayer[nID]; }
	static bool				&GetbDuo(void)			{ return m_bDuo; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static CRenderer		*m_pRenderer;
	static CInputKeyboard	*m_pInputKey;
	static CInputJoyPad		*m_pJoyPad[JOYPAD_MAX];
	//static CScenePlayer		*m_pPlayer[MAX_PLAYER];
	static CCamera_Manager	*m_pCamera;		//カメラ
	static CLight			*m_pLight;		//カメラ
	
	static CDebugLog		*m_pDebugLog;	//デバックログ
	static MODE				m_mode;			//モード
	static MODE				m_NextMode;		//次のモード
	static CFade			m_Fade;			//フェード本体
	static CSound			*m_pSound;		// サウンドクラスのポインタ
	static int				m_nEndCount;	//フェードまでのカウント

	static CDungeon			*m_pDungeon;	//ダンジョンのポインタ
	static CTitle			*m_pTitle;		//タイトルのポインタ
	static CSelect			*m_pSelect;		//セレクトのポインタ
	static CGame			*m_pGame;		//ゲームのポインタ
	static CPractice		*m_pPractice;	//練習のポインタ
	static int				nCntTime;		//時間カウント

	static CWind_Manager	*m_pWind;		//風のポインタ
	static CPlayer			*m_pPlayer[MAX_PLAYER];		//プレイヤーのポインタ
	static bool				m_bDuo;						//2人プレイかどうか
};

#endif
