//=============================================================================
//
// オブジェクト処理 [objectshadow.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _OBJECTSHADOW_H_
#define _OBJECTSHADOW_H_

#include "model3D.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECTSHADOW_TEXTURE			(1)			// オブジェクトのテクスチャ数
#define MAX_OBJECTSHADOW					(1)			// オブジェクトのモデル数
#define OBJECTSHADOW_PRIOTITY				(4)

//=====================
//  CModel3Dの派生クラス
//=====================
class CObjectShadow : public CModel3D
{
public://誰でも扱える
	CObjectShadow();
	~CObjectShadow();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObjectShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float move, int nTexTypeint,int nObjectType, MOVETYPE nMovetype, int nCollision);
	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	void DeleteObject(void);

private://個人でのみ使う
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// 頂点バッファへのポインタ
	static LPD3DXMESH	m_pMeshModel[MAX_OBJECTSHADOW];					//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel[MAX_OBJECTSHADOW];				//マテリアルの情報へのポインタ
	static DWORD		m_nNumMatModel[MAX_OBJECTSHADOW];					//マテリアルの情報数
	static LPDIRECT3DTEXTURE9 m_pMeshTextures[MAX_OBJECTSHADOW_TEXTURE];
	D3DXVECTOR3			m_move;										// 移動量
	D3DXVECTOR3			m_Spin;										// 回転
	int					m_nCount;									// カウンター
	int					m_nCollision;								// 当たり判定のONOFF
	int					m_nType;									// 種類
	D3DXVECTOR3			m_ModelMove;								// 移動の仕方
	int					m_nStageCount;								// ステージの移動時に少し時間をかける
	bool				m_bStageNext;								// ステージ遷移中

	CShadow				*m_pShadow;									//影のポインタ
	CLogo				*m_pLogo;
};
#endif