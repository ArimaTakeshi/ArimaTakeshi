//=============================================================================
//
// ライト処理 [light.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_LIGHT (3)
#define MAX_TYPE  (3)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CLight
{
public:
	CLight();
	~CLight();

	void Init(void);
	void Uninit(void);
	void Update(void); 
	void Set(int nNumber);
	void SetStrength(float fGoal, float fFrame, int nNumber);
	D3DLIGHT9 &Getlight(int nID)	{ return m_light[nID]; }
	D3DXCOLOR &GetCol(int nID)		{ return m_col[nID]; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	D3DLIGHT9	m_light[MAX_LIGHT];		//ライトの情報
	D3DXCOLOR	m_col[MAX_TYPE];					//ライトの色
	float		m_fStrength[MAX_TYPE];			//ライトの強さ
	float		m_fGoal[MAX_TYPE];				//強さの目標
	float		m_fFrame[MAX_TYPE];				//目標が初期化されるまでのフレーム数
};

#endif
