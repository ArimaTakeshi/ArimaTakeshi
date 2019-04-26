//=============================================================================
//
// 背景の処理 [bg.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CBg : public CScene2D
{
public://誰でも扱える
	CBg();
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(int nType);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int m_nCnt;											//フレームカウンタ
	int m_nType;										//種類
};
#endif