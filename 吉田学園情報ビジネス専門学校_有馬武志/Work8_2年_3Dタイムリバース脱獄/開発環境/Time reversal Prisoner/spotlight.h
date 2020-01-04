//=============================================================================
//
// スポットライトの処理 [spotlight.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"
class CEnemy;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SPOTLIGHT_PRIOTITY		(3)

//=====================
//  CScene3Dの派生クラス
//=====================
class CSpotLight : public CScene3D
{
public://誰でも扱える
	CSpotLight();
	~CSpotLight();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSpotLight *Create(D3DXVECTOR3 pos, float fWidth, float fDepth,int nTexType,CEnemy *pEnemy);
	void SetPositionSpotLight(D3DXVECTOR3 pos);
	void CollisitionMesh(void);
	void CollisionSpotLight(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	float GetSpotLightHeight(void) { return m_fMeshHeight; }

private://個人でのみ使う
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_BILLBOORD_TEX];	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						// 頂点バッファへのポインタ
	D3DXVECTOR3					m_pos;							// 位置
	float						m_fWidth;						// 横幅
	float						m_fDepth;						// 奥行	
	static float				m_fMeshHeight;					// 影からみたメッシュの高さ
	bool						m_bSpotLightIn;					// ライトに入った状態
	float						m_fSwing;						//ライトを振る
	int							m_nSwingTime;					//ライトを振るタイミング
	CEnemy						*m_pEnemy;

};
#endif