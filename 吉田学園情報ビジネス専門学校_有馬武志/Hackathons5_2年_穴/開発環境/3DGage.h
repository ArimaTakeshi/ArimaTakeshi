//=============================================================================
//
// 3Dゲージ処理 [2DGage.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _3DGAGE_H_
#define _3DGAGE_H_

#include "main.h"
#include "scene.h"
#include "3DPolygon.h"
#include "2DPolygon.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C3DGage
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
		STATE_MAX
	}STATE;

	C3DGage() { m_p3D = NULL; };
	~C3DGage() {};

	void	Set(D3DXVECTOR3 &pos, float fLengthMaxX, float flengthMaxY, float &pGage, float &pMaxGage, STATE state);	//ゲージセット処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
private://*****************************************************************************
	D3DXCOLOR	GetGageColor(int nCntGage, bool bChange);
	bool		GetStartLength(void);
	//変数宣言//***********************************************************************
	STATE	m_state;			//状態
	float	*m_pGage;			//Gageのアドレス
	float	*m_pMaxGage;		//Gageの最大値アドレス
	C3D		**m_p3D;			//桁事のポインタ
	D3DXVECTOR3 *m_pPos;			//追尾する位置
};

#endif
