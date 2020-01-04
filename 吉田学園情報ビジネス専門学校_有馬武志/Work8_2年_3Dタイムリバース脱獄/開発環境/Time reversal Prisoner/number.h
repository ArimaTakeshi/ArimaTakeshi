//=============================================================================
//
// 数字処理 [number.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "scene2D.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	static HRESULT Load(void);	//	読み込み
	static void Unload(void);	//	開放

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファへのポインタ
};

#endif