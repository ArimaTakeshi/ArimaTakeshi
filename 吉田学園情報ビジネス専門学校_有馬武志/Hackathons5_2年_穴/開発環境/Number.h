//=============================================================================
//
// 数字関係処理 [Number.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _2DNUMBER_H_
#define _2DNUMBER_H_

#include "main.h"
#include "2DPolygon.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_UV_X		(10)
#define NUMBER_UV_Y		(1)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CNumber
{
public:
	typedef enum
	{
		STATE_SCORE = 0,	//全てそのまま表示
		STATE_CHARGE,		//+なら出現、-になると消える
		STATE_STATUS,		//最大数より上の桁は透明に
		STATE_TIMER,
		STATE_MAX
	}STATE;

	CNumber() {};
	~CNumber() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state);	//スコア(数字)のTEXTURE
	void	SetNumber(int nScore);
	void	AddNumber(int nValue);
	void	SetColor(D3DXCOLOR col);
	int		&GetnNumber(void) { return m_nNumber; }
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
private://*****************************************************************************
		//変数宣言//***********************************************************************
	STATE	m_state;		//表示形式
	int		m_nNumber;		//数値
	int		m_nNum2D;		//最大桁数
	D3DXCOLOR m_col;		//カラー
	C2D		**m_p2D;		//桁事のポインタ
};

#endif
