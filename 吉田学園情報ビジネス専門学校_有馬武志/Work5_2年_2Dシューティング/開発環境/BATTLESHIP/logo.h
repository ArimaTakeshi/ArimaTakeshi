//=============================================================================
//
// ロゴの処理 [logo.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CLogo : public CScene2D
{
public://誰でも扱える
	CLogo();
	~CLogo();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int m_nCnt;											//フレームカウンタ
	bool m_bOneCnt;										//一回だけ入る
	int m_nCntTutorial;									//チュートリアル指示表示
	int m_nCntShip;										//戦艦のフレームカウンター
	int	m_nExplosionCnt;								//爆弾の時間
	int	m_nCntShipDown;									//船が沈むまでの時間
	int m_nType;										//種類
	D3DXVECTOR2 m_size;									//サイズ
	D3DXCOLOR m_col;									//カラー
	float m_fLength;									//距離
	float m_fAngle;										//角度
	D3DXVECTOR3 m_rot;									//向き

};
#endif