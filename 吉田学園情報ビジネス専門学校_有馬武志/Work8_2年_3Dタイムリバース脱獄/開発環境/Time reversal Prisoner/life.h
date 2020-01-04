//=============================================================================
//
// 体力の処理 [life.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIFE			(200)		//ライフの上限
#define BAR_WIDTH_LIFE		(350)		//横幅
#define BAR_HEIGHT_LIFE		(30)		//縦幅
#define NUM_TEXTURE_LIFE	(1)			//使用テクスチャ枚数
#define NUM_POLYGON_LIFE	(4)			//頂点数
#define SUBTRACT_TIME		(25)		//減らすカウント時間
#define HP_DIAMOND			(20)		//HPゲージの角度

//=====================
//  CSceneの派生クラス
//=====================
class CLife : CScene
{
public://誰でも扱える
	CLife();
	~CLife();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLife *Create(D3DXVECTOR3 pos);
	void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
	static void AddLife(int nValue);
	int GetLife(void) { return m_Life[3].nLife; }

private:
	typedef struct 
	{
		D3DXVECTOR3 pos;		// 左上の位置
		D3DXCOLOR col;			// 色
		int nLife;				// 現在のライフ
		float fLength;			// バーの長さ	[0:現在のライフ　1:ダメージで減った分]
		int nType;				// テクスチャの種類（-1でなし）
	}Life;

	typedef struct
	{
		D3DXVECTOR3 pos;		// 左上の位置
		D3DXCOLOR col;			// 色
		int nLife;				// 現在のライフ
		float fLength;			// バーの長さ	[0:現在のライフ　1:ダメージで減った分]
		int nType;				// テクスチャの種類（-1でなし）
	}LifeFuture;

	static LPDIRECT3DTEXTURE9		m_pTexture[NUM_TEXTURE_LIFE];	//共有テクスチャのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						//頂点バッファのポインタ
	static int						m_nCntSubtraction;				//バーを減らし始めるカウンタ
	static Life						m_Life[NUM_POLYGON_LIFE];		//体力
	static int						m_nMaxLife;						//最大の体力
	D3DXVECTOR3						m_pos;							//位置
	LifeFuture						m_LifeFuture[NUM_POLYGON_LIFE];	//未来の体力
};
#endif