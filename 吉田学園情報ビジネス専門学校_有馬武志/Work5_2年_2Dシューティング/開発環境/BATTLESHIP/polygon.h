//=============================================================================
//
// メイン処理 [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"
#include "scene2D.h"

//=====================
// 基本クラス
//=====================
class CPolygon
{
public:
	CPolygon();										//コンストラクタ
	~CPolygon();									//デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);					//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	static CPolygon *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);						//テクスチャ読み込み
	static void UnLoad(void);
	float GetSize(void) { return m_fSize; }
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9     m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3					  m_pos;			//ポリゴンの位置
	D3DXCOLOR					  m_col;			//ポリゴンの位置
	float						  m_fSize;			//サイズ
};
#endif

