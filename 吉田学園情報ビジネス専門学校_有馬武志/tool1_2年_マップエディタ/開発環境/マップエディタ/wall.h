//=============================================================================
//
// 壁処理 [wall.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "scene3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WALL_NAME			"data\\TEXT\\ステージフラット\\wall.txt"	//読み込むtxtファイルの名前
#define WALL_PRIOTITY		(3)
#define	MAX_WALL_TEX		(9)

//=============================================================================
// クラス定義
//=============================================================================
class CWall : public CScene3D
{
public:
	CWall();
	~CWall();

	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nType);
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fDepth);
	void TextSave(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_WALL_TEX];	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATRIX					m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3					m_pos;						// 位置
	D3DXVECTOR3					m_rot;						// 回転
	D3DXVECTOR2					m_size;						// 大きさ
	int							m_nType;					// 壁の方向
	float						m_fWidthDivide;				// 横幅
	float						m_fHightDivide;				// 縦幅
	int							m_nTexType;					// テクスチャの種類
};
#endif
