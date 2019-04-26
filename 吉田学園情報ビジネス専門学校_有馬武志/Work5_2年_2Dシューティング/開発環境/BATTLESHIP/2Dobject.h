//=============================================================================
//
// オブジェクト処理 [2Dobject.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _2DOBJECT_H_
#define _2DOBJECT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義　免許書
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2Dの派生クラス
//=====================
class C2DObject : public CScene2D
{
public://誰でも扱える
	C2DObject();
	~C2DObject();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 *GetSize(void) { return &m_Size; }
	void HitObject(int nDamage);
	static C2DObject *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType,int nLife);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	D3DXVECTOR2	m_Size;									//サイズ
	D3DXVECTOR3 m_posold;								//過去の位置
	float m_fPlayerLife;								//プレイヤーの体力を入れる箱
	int m_nLife;
	int	m_nType;										//種類
};
#endif