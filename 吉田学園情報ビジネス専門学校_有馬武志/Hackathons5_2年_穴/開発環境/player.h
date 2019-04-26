//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "Scene2D.h"
#include "motion.h"
class C2DGage;
class C2D;
class C2DPolygon;
class CNumber;
class CPlayer_UI;
class CSceneModel;
class CFont;
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_UIDeco		(2)
#define MAX_MotionUI	(15)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		MODE_START,
		MODE_HIDE,
		MODE_BREAK,
		MODE_FIGHT,
	}MODE;
	CPlayer(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CPlayer() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);	//ゲージセット処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	Break(void);
	void	Answer(void);
	void	Dead(void);
	void	Over(void);
	void SetLightCol(D3DXCOLOR col);
	void SetLightStr(float fGoal, float fFrame);

	MODE    &GetMode(void) { return m_Mode; }
	int		&GetnID(void) { return m_nID; }
	int		&GetnBreak(void) { return m_nBreak; }
	bool	&GetbReset(void) { return m_bReset; }
	CPlayer_UI	*&GetpUI(void) { return m_pUI; }

private://*****************************************************************************
	void	LockUpdate(void);
	void	ChangeMotion(void);
	//変数宣言//***********************************************************************
	static	int	m_nNumPlayer;	//プレイヤーの総数カウント

	CPlayer_UI *m_pUI;
	int			m_nID;			//プレイヤーのID
	CScene2D	*m_pLockOn;		//ロック時のUI
	float		m_fDistance;	//カメラとの距離
	float		m_fBase;		//距離の基礎値
	float		m_fRatio;		//距離の倍率
	bool		m_bReset;

	int		m_nCntState;
	int		m_nCntBreak;
	int		m_nBreak;
	int		m_nBreak2;
	D3DXVECTOR3 m_Finger;
	CSceneModel *m_pModel;
	MODE		m_Mode;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class Motion_UI
{
public:
	typedef enum
	{
		TYPE_GROUND,	//地上
		TYPE_SKY,		//空中
		TYPE_NO,		//無視
		TYPE_MAX,
	}TYPE;
	Motion_UI() {};
	~Motion_UI() {};

	void	Set(CPlayer *pPlayer, D3DXVECTOR3 pos, int nID, int nUV, TYPE type);	//ゲージセット処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private://*****************************************************************************
		//変数宣言//***********************************************************************
	TYPE		m_Type;			//参照の種類
	D3DXVECTOR3	m_pos;			//自身の場所
	int			m_nID;			//参照するモーション番号
	CPlayer		*m_pPlayer;		//プレイヤーのポインタ
	C2DPolygon	*m_p2D;			//2Dポリゴン
	C2DGage		*m_pGage;		//ゲージ	縦ゲージ
	CNumber		*m_pNumber;		//文字		秒数


};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CPlayer_UI : public CScene
{
public:
	typedef enum
	{
		LOCK_CANCEL,
		LOCK_NO,
		LOCK_START,
		LOCK_ON,
		LOCK_MAX,
	}LOCK;
	CPlayer_UI(int nPrioryity = S2D_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CPlayer_UI() {};

	void	Set(CPlayer *pPlayer);	//ゲージセット処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	SetLockOn(LOCK lock, D3DXVECTOR3 *pos);

	CSceneEffect *&GetpLockOn(void) { return m_pLockOn; }
private://*****************************************************************************
	//変数宣言//***********************************************************************
	CPlayer			*m_pPlayer;					//プレイヤーのポインタ
	C2D				*m_p2DHelp;					//ヘルプ
	C2D				*m_p2DDeco[MAX_UIDeco];		//ゲージの装飾
	C2DGage			*m_pLife;					//HP
	C2DGage			*m_pSP;						//MP
	C2DGage			*m_pStamina;				//スタミナ
	CSceneModel		*m_pModel;					//方位磁針モデル(本体)
	CSceneModel		*m_pNeedle;					//方位磁針モデル(針)
	CSceneEffect	*m_pLockOn;					//ロックオンUI
	Motion_UI		*m_pMotion_UI;				//モーションUI
	CFont			*m_pFont;					//ヘルプ用の文字
	bool			m_bHelp;

	CFont		*m_pSelect[4];
	C2D			*m_p2DSelect;					//ヘルプ

	CNumber		*m_pTime;						//時間
};
#endif
