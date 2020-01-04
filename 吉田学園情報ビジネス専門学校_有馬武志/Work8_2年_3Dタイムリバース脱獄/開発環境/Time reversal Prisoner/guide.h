//=============================================================================
//
// ガイドの処理 [guide.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _GUIDE_H_
#define _GUIDE_H_

#include "main.h"
#include "billboord.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CGuide : public CScene2D
{
public://誰でも扱える
	CGuide();
	~CGuide();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGuide *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int							m_nType;					//種類
	D3DXVECTOR2					m_size;						//サイズ
	float						m_fLength;					//距離
	float						m_fAngle;					//角度
	D3DXVECTOR3					m_rot;						//向き
	int							m_nCntBandTimer;			//帯の出る時間
	int							m_nCntMapGuideTimer;		//現在の場所の案内
	bool						m_bOneCnt;
	int							m_nCntStar;					//星の動きのカウンター
	float						m_fColorCount;				//カラーのカウンター
	bool						m_bPressA;					//ボタンが押された状態
};
#endif