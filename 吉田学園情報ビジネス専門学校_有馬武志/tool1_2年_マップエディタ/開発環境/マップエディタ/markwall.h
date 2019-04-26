//=============================================================================
//
// 印の壁処理 [markwall.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _MARKWALL_H_
#define _MARKWALL_H_

#include "main.h"
#include "scene3D.h"
#include "wall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MARKWALL_PRIOTITY		(2)
#define	MAX_MARKWALL_TEX		(9)

//=============================================================================
// クラス定義
//=============================================================================
class CMarkWall : public CScene3D
{
public:
	CMarkWall();
	~CMarkWall();

	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMarkWall *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nType);
	void UninitCreate(D3DXVECTOR3 pos);
	static int GetWallNum(void) { return m_nWallNum; }
	static void SetWallNum(int nNum) { m_nWallNum = nNum; }

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_MARKWALL_TEX];	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						// 頂点バッファへのポインタ
	D3DXMATRIX					m_mtxWorld;						// ワールドマトリックス
	D3DXVECTOR3					m_pos;							// 位置
	D3DXVECTOR3					m_rot;							// 向き
	D3DXVECTOR2					m_size;							// 大きさ
	int							m_nType;						// 壁の方向
	int							m_nWallTextureNumber;			// テクスチャの種類変更
	int							m_nTexType;						// テクスチャ番号
	float						m_fHightLength;					// 縦のサイズの変更
	float						m_fWidthLength;					// 横のサイズの変更
	static int					m_nWallNum;						// 壁の数
	bool						m_bSetWall;						// 壁の設置
	static CWall				*m_pWall;						// 壁のポインタ
};
#endif
