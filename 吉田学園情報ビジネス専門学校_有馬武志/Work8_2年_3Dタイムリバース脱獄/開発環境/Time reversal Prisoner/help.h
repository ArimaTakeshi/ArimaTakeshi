//=============================================================================
//
// ヘルプ処理 [help.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _HELP_H_
#define _HELP_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_HELP_TEXTURE	(5)

//=====================
//  CSceneの派生クラス
//=====================
class CHelp : public CScene
{
public://誰でも扱える
	static HRESULT Load(void);
	static void UnLoad(void);
	CHelp(int nPriority = 7, CScene::OBJTYPE objType = CScene::OBJTYPE_HELP);
	~CHelp();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CHelp *Create();
	static bool &GetbPause() { return m_bPause; }
	static bool GetPauseEnd() { return m_bSerectEnd; }

private://個人でのみ使う
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_HELP_TEXTURE];//テクスチャへのポインタ
	LPDIRECT3DTEXTURE9 m_pKeepTexture[MAX_HELP_TEXTURE];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						//頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;							//位置
	D3DXCOLOR				m_col;							//色
	float					m_SelectColor;					//選択しているときの色
	int						m_nCntState;					//カウントしている状態
	int						m_SelectNum;					//ヘルプの数
	static bool				m_bSerectEnd;					//選び終わった状態
	D3DXVECTOR2				m_nSize;						//サイズ
	static bool				m_bPause;
	int						m_nTxtureNumber;
};
#endif