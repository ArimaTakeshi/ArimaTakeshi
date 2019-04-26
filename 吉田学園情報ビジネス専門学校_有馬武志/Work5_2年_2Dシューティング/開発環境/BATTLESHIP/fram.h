//=============================================================================
//
// 枠の処理 [fram.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _FRAM_H_
#define _FRAM_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CFram : public CScene2D
{
public://誰でも扱える
	CFram();
	~CFram();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFram *Create(int nType);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int m_nCnt;											//フレームカウンタ
	int m_nType;										//種類
};
#endif