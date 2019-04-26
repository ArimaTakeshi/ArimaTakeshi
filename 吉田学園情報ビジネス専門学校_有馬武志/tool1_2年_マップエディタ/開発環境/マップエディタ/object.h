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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT_TEXTURE			(11)				// オブジェクトのテクスチャ数
#define MAX_OBJECT					(32)				// オブジェクトのモデル数
#define OBJECT_PRIOTITY				(2)

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
	static CObject *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, float move, int nTexTypeint,int nObjectType, MOVETYPE nMovetype,int nCollision);
	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	
	//ファイル入出力
	void TextSave(void);
private://個人でのみ使う
	static LPD3DXMESH	m_pMeshModel[MAX_OBJECT];					//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel[MAX_OBJECT];				//マテリアルの情報へのポインタ
	static DWORD		m_nNumMatModel[MAX_OBJECT];					//マテリアルの情報数
	static LPDIRECT3DTEXTURE9 m_pMeshTextures[MAX_OBJECT_TEXTURE];
	D3DXVECTOR3			m_move;										// 移動量
	D3DXVECTOR3			m_Spin;										// 回転
	int					m_nCount;									// カウンター
	D3DXVECTOR3			m_ModelMove;								// 移動の仕方
	int					m_nSelectNum;								// オブジェクトの変更
	int					m_nSetObjectNum;							// オブジェクトの数
	//ファイル
	int					m_nType;									// 種類
	int					m_nTexType;									// テクスチャの種類
	int					m_nCollision;								// 当たり判定のONOFF
	D3DXVECTOR3			m_pos;										// 位置
	D3DXVECTOR3			m_rot;										// 回転
};
#endif