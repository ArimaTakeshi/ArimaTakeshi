//=============================================================================
//
// メイン処理 [number.h]
// Author : 
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMBER_TEXTURE		(2)						//テクスチャの最大枚数

//=====================
// 基本クラス
//=====================
class CNumber
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_KILL,
		TYPE_SCORE,
		TYPE_DAMAGE,
		TYPE_MAX
	}TYPE;

	CNumber();										//コンストラクタ
	~CNumber();										//デストラクタ
	HRESULT Init(D3DXVECTOR3 pos);					//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	static CNumber *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);						//テクスチャ読み込み
	static void UnLoad(void);
	static void SetType(TYPE Type) { m_nType = Type; }
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9     m_pTexture[MAX_NUMBER_TEXTURE];
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3					  m_pos;			//ポリゴンの位置
	D3DXCOLOR					  m_col;			//ポリゴンの位置
	static int				      m_nType;			//タイプを入れる箱
};
#endif

