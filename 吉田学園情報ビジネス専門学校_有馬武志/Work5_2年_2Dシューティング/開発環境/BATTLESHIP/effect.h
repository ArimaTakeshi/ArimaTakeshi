//=============================================================================
//
// エフェクト処理 [effect.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2Dの派生クラス
//=====================
class CEffect : public CScene2D
{
public://誰でも扱える
	typedef enum
	{
		EFFECTTYPE_NOLMAL = 0,
		EFFECTTYPE_RIPPLE,
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect();
	~CEffect();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,float fRadiusint,int nLife, EFFECTTYPE nType, int nTexType);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_DATA];	//共有テクスチャのポインタ
	D3DXVECTOR3				  m_move;					//移動量
	int						  m_nLife;					//時間
	D3DXVECTOR2				  m_Size;					//サイズ
	float					  m_fRadius;				//半径
	EFFECTTYPE				  m_Type;					//種類
};
#endif