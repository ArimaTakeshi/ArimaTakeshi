//=============================================================================
//
// オブジェクト処理 [markobject.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _MARKOBJECT_H_
#define _MARKOBJECT_H_

#include "model3D.h"
#include "camera.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MARKOBJECT_TEXTURE			(11)			// オブジェクトのテクスチャ数
#define MAX_MARKOBJECT					(32)			// オブジェクトのモデル数
#define MARKOBJECT_PRIOTITY				(2)				// オブジェクトの優先順位

//=====================
//  CModel3Dの派生クラス
//=====================
class CMarkObject : public CModel3D
{
public://誰でも扱える
	CMarkObject();
	~CMarkObject();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMarkObject *Create(D3DXVECTOR3 pos,int nTexTypeint,int nObjectType);
	static int GetObjectNum(void) { return m_nMarkObjNum; }
	static void SetObjectNum(int nNum) { m_nMarkObjNum = nNum; }
	void CollisitionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static bool GetCraftDelete(void) { return m_bCraftDelete; }

private://個人でのみ使う
	static CObject		*m_pObject;											// オブジェクトのポインタ
	static LPD3DXMESH	m_pMeshMarkModel[MAX_MARKOBJECT];					// メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatMarkModel[MAX_MARKOBJECT];				// マテリアルの情報へのポインタ
	static DWORD		m_nNumMatMarkModel[MAX_MARKOBJECT];					// マテリアルの情報数
	static LPDIRECT3DTEXTURE9 m_pMeshMarkTextures[MAX_MARKOBJECT_TEXTURE];	// テクスチャの情報
	D3DXVECTOR3			m_move;												// 移動量
	D3DXVECTOR3			m_Spin;												// 回転
	int					m_nCount;											// カウンター
	int					m_nCollision;										// 当たり判定のONOFF
	int					m_nType;											// 種類
	D3DXVECTOR3			m_ModelMove;										// 移動の仕方
	float				m_fMove;											// 移動の速さ
	int					m_nSelectNum;										// オブジェクトの選択
	int					m_nSelectCollision;									// 当たり判定の選択
	static int			m_nMarkObjNum;										// 作ったオブジェクトの数
	int					m_nTexType;											// テクスチャの種類
	int					m_nCraftDeleteNumber;
	bool				m_bSetObject;										// オブジェクトの設置
	static bool			m_bCraftDelete;										// 削除モードか生成モードの状態
};
#endif