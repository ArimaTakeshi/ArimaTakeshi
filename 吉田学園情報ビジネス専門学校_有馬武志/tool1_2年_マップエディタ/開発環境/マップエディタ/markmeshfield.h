//=============================================================================
//
// 印のメッシュ処理 [markmeshfield.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _MARKMESHFIELD_H_
#define _MARKMESHFIELD_H_

#include "mesh.h"
#include "meshfield.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CMeshの派生クラス
//=====================
class CMarkMeshField : public CMesh
{
public://誰でも扱える
	CMarkMeshField();
	~CMarkMeshField();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UninitCreate(D3DXVECTOR3 pos);
	static CMarkMeshField *Create(D3DXVECTOR3 pos, int nMeshX, int nMeshZ, float fMeshWidth, float fMeshDepth,float fVtx0, float fVtxMeshX, float fVtxMeshZ, float fVtxMeshXMeshZ, int nTexTypeint,int nVtxNumber,int nMeshType);
	static int GetMeshFieldNum(void) { return m_nMarkFieldNum; }
	static void SetMeshFieldNum(int nNum) { m_nMarkFieldNum = nNum; }

private://個人でのみ使う
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_MESH_TEXTURE];	// テクスチャへのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						// 頂点バッファへのポインタ
	static LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;						// インデックスへのポインタ
	int								m_nCnt;
	int								m_nType;
	float							m_fVtx0;						// pVtx[0]番目の高さを変える
	float							m_fVtxMeshX;					// pVtx[MeshX + 1]番目の高さを変える
	static int						m_nMarkFieldNum;				// 生成したフィールドの数
	int								m_nWidthDivide;					// 横の分割数を入れる
	int								m_nDepthDivide;					// 奥の分割数を入れる
	float							m_fWidthLength;					// 横の長さ
	float							m_fDepthLength;					// 奥の長さ
	int								m_nSelectNum;					// 選んでいるもの
	int								m_nTexType;						// テクスチャの種類
	int								m_nVtxNumber;					// 選択している頂点の番号
	float							m_fVtxHeight_No0;				// 頂点番号0を操作
	float							m_fVtxHeight_No1;				// 頂点番号1を操作
	float							m_fVtxHeight_No2;				// 頂点番号2を操作
	float							m_fVtxHeight_No3;				// 頂点番号3を操作
	float							m_fMove;						// 変更するための移動量			
	D3DXVECTOR3						m_move;							// 型を入れる移動量
	D3DXVECTOR4						m_Vtx;							// 各頂点の高さ用
	int								m_nClidked;						// 保存用
	bool							m_bSetFeild;					// 設置用
	static CMeshField				*m_pMeshField;					// メッシュフィールドのポインタ

};
#endif