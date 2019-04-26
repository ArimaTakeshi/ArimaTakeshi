//=============================================================================
//
// 2DPolygon処理 [2DPolygon.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "2DPolygon.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CFade
{
public:
	typedef enum
	{
		TEX_GAGE,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_OUT,		//exe始まりのフェード
		STATE_NOR_FADE,	//通常フェード
		STATE_FADE_NONE,
		STATE_FADE_NOW,
		STATE_MAX
	}STATE;


	CFade() { m_p2DFade = NULL; };
	~CFade() {};

	void	Set(void);

	HRESULT Init(STATE state);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄

	STATE &GetState(void) { return m_state; }
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
private://*****************************************************************************
		//変数宣言//***********************************************************************
	STATE		m_state;
	C2DPolygon	*m_p2DFade;
};

#endif