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
#define GAME_PAUSE_INTERVAL	(100.0f)
#define GAME_PAUSE_LOGOX	(300.0f)
#define GAME_PAUSE_LOGOY	(100.0f)


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

	static bool &GetbDuo(void) { return m_bDuo; }
	int &GetnWave(void) { return m_nWave; }


private://*****************************************************************************
		//変数宣言//***********************************************************************
	static	bool	m_bDuo;	//2人プレイかどうか
	STATE	m_state;
	float	m_fCntState;
	int		m_nSelect;

	int		m_nCntTime;
	float	m_fInterval;
	int		m_nWave;
	int		m_nCntType;

	CScene2D *m_pScene2D[MAX_GAME_PAUSE];
};

#endif
