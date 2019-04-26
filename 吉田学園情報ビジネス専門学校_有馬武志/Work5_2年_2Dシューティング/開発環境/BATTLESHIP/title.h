//=============================================================================
//
// メイン処理 [title.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "sound.h"

//=====================
// 基本クラス
//=====================
class CTitle
{
public:
	CTitle();										//コンストラクタ
	~CTitle();										//デストラクタ
	HRESULT Init();									//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	static HRESULT Load(void);						//テクスチャ読み込み
	static void UnLoad(void);						//テクスチャの破棄

private:
	static LPDIRECT3DTEXTURE9     m_pTexture;
	int							  m_nCount;			
	int							  m_nCnt;
};
#endif

