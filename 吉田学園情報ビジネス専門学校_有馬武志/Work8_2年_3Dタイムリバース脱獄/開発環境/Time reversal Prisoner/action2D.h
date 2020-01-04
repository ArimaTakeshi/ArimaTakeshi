//=============================================================================
//
// アクションポリゴンの処理 [action2D.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _ACTION2D_H_
#define _ACTION2D_H_

#include "main.h"
#include "billboord.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CAction2D : public CScene2D
{
public://誰でも扱える
	CAction2D();
	~CAction2D();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAction2D *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int							m_nType;					//種類
	D3DXVECTOR2					m_size;						//サイズ
};
#endif