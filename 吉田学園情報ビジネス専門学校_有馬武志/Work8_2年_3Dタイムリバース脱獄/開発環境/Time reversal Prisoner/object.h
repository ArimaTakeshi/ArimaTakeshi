//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "model3D.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT_TEXTURE			(11)			// オブジェクトのテクスチャ数
#define MAX_OBJECT					(32)			// オブジェクトのモデル数
#define OBJECT_PRIOTITY				(3)

//=====================
//  CModel3Dの派生クラス
//=====================
class CObject : public CModel3D
{
public://誰でも扱える
	CObject();
	~CObject();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float move, int nTexTypeint,int nObjectType, MOVETYPE nMovetype, int nCollision);
	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	void DeleteObject(void);

private://個人でのみ使う
	static LPD3DXMESH	m_pMeshModel[MAX_OBJECT];					//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel[MAX_OBJECT];				//マテリアルの情報へのポインタ
	static DWORD		m_nNumMatModel[MAX_OBJECT];					//マテリアルの情報数
	static LPDIRECT3DTEXTURE9 m_pMeshTextures[MAX_OBJECT_TEXTURE];
	D3DXVECTOR3			m_move;										// 移動量
	D3DXVECTOR3			m_Spin;										// 回転
	int					m_nCount;									// カウンター
	int					m_nCollision;								// 当たり判定のONOFF
	int					m_nType;									// 種類
	D3DXVECTOR3			m_ModelMove;								// 移動の仕方
	int					m_nStageCount;								// ステージの移動時に少し時間をかける
	bool				m_bStageNext;								// ステージ遷移中

	CShadow				*m_pShadow;									//影のポインタ
};
#endif