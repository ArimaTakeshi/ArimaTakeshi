//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CBullet;
class CExplosion;
class CBg;
class CEnemy;
class CGan;
class CNumber;
class C2DObject;
class CFram;
class CPause;
class CString;
class CLife;

//=====================
// 基本クラス
//=====================
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,					//何もしていない状態
		GAMESTATE_NORMAL,					//通常状態
		GAMESTATE_CLEAR,					//クリア
		GAMESTATE_OVER,						//ゲームオーバー
		GAMESTATE_END,						//ゲーム終了
		GAMESTATE_MAX						//最大数
	}GAMESTATE;

	CGame();								//コンストラクタ
	~CGame();								//デストラクタ
	HRESULT Init();							//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理
	static void SetGameState(GAMESTATE state) { m_gameState = state; }
	static GAMESTATE GetGameState(void) { return m_gameState; }
	static CPlayer *&GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CGan *GetGan(void) { return m_pGan; }
	static void SetPause(bool bPause);
	static bool GetPause(void) { return m_bPause; }

private:
	static GAMESTATE m_gameState;					//ゲーム状態
	GAMESTATE m_NowGameState;
	int m_nCounterGameState;						//状態カウンタ
	static CBullet *m_pBullet;
	static CPlayer *m_pPlayer;
	static CFram *m_pFram;
	static CBg *m_pBg;
	static CExplosion *m_pExplosion;
	static C2DObject *m_p2DObject;
	static CEnemy *m_pEnemy;
	static CGan *m_pGan;
	static CNumber *m_pNumber;
	static CPause *m_pPause;
	static bool m_bPause;
	//static CString *m_pString;
};
#endif

