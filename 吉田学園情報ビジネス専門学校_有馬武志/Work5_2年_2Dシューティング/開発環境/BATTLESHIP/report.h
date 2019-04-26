//=============================================================================
//
// 報告の処理 [report.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _REPORT_H_
#define _REPORT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CReport : public CScene2D
{
public://誰でも扱える
	CReport();
	~CReport();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CReport *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int m_nCnt;											//フレームカウンタ
	int m_nType;										//種類
	D3DXVECTOR2 m_size;									//サイズ
	D3DXCOLOR m_col;									//カラー
	float m_fLength;									//距離
	float m_fAngle;										//角度
	D3DXVECTOR3 m_rot;									//向き

};
#endif