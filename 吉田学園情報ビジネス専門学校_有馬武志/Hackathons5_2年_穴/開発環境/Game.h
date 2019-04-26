//=============================================================================
//
// ゲーム処理 [Game.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
#define MAX_GAME_PAUSE		(6)
#define GAME_PAUSE_INTERVAL	(50.0f)
#define GAME_PAUSE_LOGOX	(150.0f)
#define GAME_PAUSE_LOGOY	(50.0f)


//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CGame
{
public:
	typedef enum
	{
		STATE_NONE,		//通常
		STATE_CLEAR,	//クリア
		STATE_OVER,		//ゲームオーバー
		STATE_MAX
	}STATE;
	CGame()		{ for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++) { m_pScene2D[nCount] = NULL; } };
	~CGame()	{};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	SetState(STATE state);
	void	Pause(void);
	STATE	&GetState(void) { return m_state; }
	CScene3D *&Get3D(int nID) { return m_p3D[nID]; }
	int		&GetnQuiz(void) { return m_nQuiz; }
	int		&GetnAnswer(void) { return m_nAnswer; }

	static bool &GetbDuo(void) { return m_bDuo; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static	bool	m_bDuo;	//2人プレイかどうか
	STATE	m_state;
	int		m_nScore;
	float	m_fCntState;
	int		m_nSelect;
	CScene2D *m_pScene2D[MAX_GAME_PAUSE];
	char	m_char[128];

	CScene3D    *m_p3D[16];
	int			m_nQuiz;
	int			m_nAnswer;
};

#endif
