//=============================================================================
//
// タイトルテキストの処理 [titletex.h]
// Author : 荒谷由朗
//
//=============================================================================
#ifndef _TITLETEX_H_
#define _TITLETEX_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CTitletex : public CScene2D
{
public://誰でも扱える
	CTitletex();
	~CTitletex();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitletex *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int m_nType;										//種類
	D3DXVECTOR2 m_size;									//サイズ(現在)
	D3DXVECTOR2 m_sizeDest;								//サイズ(目的)
	float m_fLength;									//距離
	float m_fAngle;										//角度
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR3 m_posDest;								//座標(目的)
	int m_nCounterAnim;									//アニメーションのカウンター
	int m_nPatternAnim;									//アニメーションパターンのカウンター
	int m_nCntflame;									//カウンター
	int m_nCntDelete;									//カウンター
	bool m_nBlink;										//点滅
};
#endif