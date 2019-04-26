//=============================================================================
//
// 風処理 [wind.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _WIND_H_
#define _WIND_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_WIND	(3)
#define WIND_POW	(2.9f)
#define WIND_PLUS	(1.0f)
#define WIND_RANGE	(0.5f)
#define WIND_GOAL	(0.05f)
#define WIND_BACK	(0.05f)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CWind
{
public:
	CWind() {};
	~CWind() {};

	void	Init(void);
	void	Update(void);
	void	Uninit(void);
	float	&GetfPower(void) { return m_fPower; }
	float	&GetfRot(void)	 { return m_fRot; }
	float	&GetfRange(void) { return m_fRange; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	float m_fPower;		//風の威力
	float m_fMaxPower;	//風の最大威力
	float m_fRot;		//影響角度
	float m_fRange;		//影響範囲
	float m_fGoal;		//風の即効性
	float m_fBack;		//風のゆるみ具合
	bool  m_bState;		//影響状態
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CWind_Manager
{
public:
	CWind_Manager() {};
	~CWind_Manager() {};

	void	Init(void);
	void	Update(void);
	void	Uninit(void);
	int		&GetnMaxWind(void) { return m_nMaxWind; }
	CWind	*&GetpWind(void) { return m_pWind; }
	float	&GetfRot(void) { return m_fRot; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	int		m_nMaxWind;		//風の数
	float	m_fRot;			//角度
	float	m_fRotPlus;		//角度へのプラス値
	float	m_fCntState;	//Fカウント用
	CWind	*m_pWind;		//風
};

#endif