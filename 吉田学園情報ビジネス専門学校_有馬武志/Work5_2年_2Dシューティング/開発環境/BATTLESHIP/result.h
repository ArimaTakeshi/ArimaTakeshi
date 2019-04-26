//=============================================================================
//
// リザルト処理 [result.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CSerect;

//=====================
// 基本クラス
//=====================
class CResult
{
public:
	CResult();										//コンストラクタ
	~CResult();										//デストラクタ
	HRESULT Init();									//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	static HRESULT Load(void);						//テクスチャ読み込み
	static void UnLoad(void);

private:
	static CSerect				  *m_pSerect;
	static LPDIRECT3DTEXTURE9     m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3					  m_pos;			//ポリゴンの位置
	D3DXCOLOR					  m_col;			//ポリゴンの位置
	float						  m_fSize;			//サイズ
	int							  m_nCnt;			//タイトルに行く時間
	int							  m_nSetCnt;		//報告の時間
};
#endif

