//=============================================================================
//
// バレット処理 [explosion.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義　免許書
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2Dの派生クラス
//=====================
class CExplosion : public CScene2D
{
public://誰でも扱える
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int m_nCounterAnim;									//アニメーションカウンター
	int m_nPatteunAnim;									//アニメーションパターンNo.
	D3DXVECTOR2	m_Size;									//サイズ
	int	m_nType;										//種類
};
#endif