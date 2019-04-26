//=============================================================================
//
// 2Dゲージ処理 [2DGage.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _2DGAGE_H_
#define _2DGAGE_H_

#include "main.h"
#include "scene.h"
#include "2DPolygon.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_GAGE		(3)	//ゲージの最大数

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C2DGage
{
public:
	typedef enum
	{
		TEX_GAGE,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_LIFE,
		STATE_EXP,
		STATE_STATUS,
		STATE_MAX
	}STATE;

	C2DGage() { m_p2D = NULL; };
	~C2DGage() {};

	void	Set(D3DXVECTOR3 pos, float fLengthMaxX, float flengthMaxY, float *pGage, float *pMaxGage, bool bDirection, STATE state);	//ゲージセット処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
private://*****************************************************************************
	D3DXCOLOR	GetGageColor(int nCntGage, bool bChange);
	bool		GetStartLength(void);
		//変数宣言//***********************************************************************
	STATE	m_state;				//状態
	bool	m_bDirection;		//ゲージの向き
	float	*m_pGage;			//Gageのアドレス
	float	*m_pMaxGage;		//Gageの最大値アドレス
	C2D		**m_p2D;			//桁事のポインタ
};

#endif
