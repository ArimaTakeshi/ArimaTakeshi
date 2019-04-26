//=============================================================================
//
// 2DPolygon処理 [2DPolygon.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _FONT_H_
#define _FONT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define FONT_PRIORITY		(4)
#define MAX_FONT_TYPE		(8)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CFont : public CScene
{
public:
	typedef enum
	{//文字の状態
		STATE_NONE = 0,
		STATE_UP,		//上へ
		STATE_FADE,	//出現後消える
		STATE_FADEOUT,	//消える
		STATE_FADEOUT2,	//消えてNONEへ
		STATE_RANKIN,
		STATE_MAX,		//最大値

	}STATE;
	CFont(int nPrioryity = FONT_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CFont() {};

	static void	Load(int nID);
	static void	UnLoad(void);
	void	Set(RECT rect, D3DXCOLOR col, char *aStr, int nType, int nFormat, int nMaxFont, bool bShadow, STATE state);
	void	SetFont(char *aStr, int nMaxFont);	//文字部分のみ変更

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);

	RECT	&GetRect(void)		{ return m_rect; }
	STATE	&GetState(void)		{ return m_state; }
	float	&GetfCntState(void) { return m_fCntState; }
	bool	&GetbDisplay(void)	{ return m_bDisplay; }
	D3DXCOLOR &GetCollar(void)  { return m_col; }
protected://*****************************************************************************
		  //変数宣言//***********************************************************************

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static	LPD3DXFONT			m_pFont[MAX_FONT_TYPE];			// フォントへのポインタ
	STATE		m_state;		//文字の状態
	D3DXCOLOR	m_col;		//カラー
	RECT		m_rect;		//文字の表示範囲
	int			m_nType;		//フォントのタイプ
	int			m_nFormat;	//表示場所
	float		m_fCntState;	//状態管理用
	int			m_nMaxFont;	//表示する最大数
	int			m_nCntTime;	//表示のためのカウント
	char		m_aStr[84];	//文字の量
	bool		m_bDisplay;	//表示非表示
	bool		m_bshadow;	//影の有無

};
#endif