//=============================================================================
//
// 銃の処理 [gan.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _GAN_H_
#define _GAN_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CScene2Dの派生クラス
//=====================
class CGan : public CScene2D
{
public://誰でも扱える
	typedef enum
	{
		GANTYPE_PLAYER = 0,		//プレイヤー
		GANTYPE_ENEMY,			//敵
		GANTYPE_MAX				//最大数
	}TYPE;

	typedef enum
	{
		GAN_CANNON = 0,			//大砲
		GAN_SKYCANNON,			//対空砲
		GAN_TORPEDO,			//魚雷
		GAN_MAX					//最大数
	}GAN;

	CGan();
	~CGan();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	GAN *GetGanType(void) { return &m_gantype; }
	static CGan *Create(D3DXVECTOR2 size,TYPE type, GAN gantype,int nfram);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	D3DXVECTOR3				  m_move;					//移動量
	int						  m_nType;					//種類
	int						  m_nCount;					//カウンター
	int						  m_nCannonCount;			//大砲カウンター
	GAN						  m_gantype;				//銃の種類
	D3DXVECTOR2				  m_Size;					//サイズ
	int						  m_nFram;					//枠か枠じゃないか
	float					  m_fLife;					//プレイヤーのHPを入れておく箱
	bool					  m_bInitTex;				//初期テクスチャ
	float					  m_fRot;					//回転
	float					  m_fLength;				//長さ
	D3DXVECTOR3				  m_rot;					
};

#endif