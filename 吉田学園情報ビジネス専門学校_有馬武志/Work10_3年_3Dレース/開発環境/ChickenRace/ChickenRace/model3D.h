//=============================================================================
//
// モデルの処理 [model3D.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _MODEL3D_H_
#define _MODEL3D_H_

#include "main.h"
#include "scene.h"
#include "toonshader.h"
#include "camerabace.h"
#include "model3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYCOL	(4)

//=====================
//  CSceneの派生クラス
//=====================
class CModel3D : public CScene
{
public:
	typedef enum
	{// オブジェクトの種類
		MODEL_TYPE_TREE = 0,		//木
		MODEL_TYPE_SAKU,			//柵
		MODEL_TYPE_BOX,				//箱
		MODEL_TYPE_MAP_FIRST,		//1番目
		MODEL_TYPE_MAP_SECOND,		//2番目
		MODEL_TYPE_MAP_MOUNTAIN,	//山
		MODEL_TYPE_MAP_SKY,			//空
		MODEL_TYPE_CHICKEN_HOUSE,	//鶏の家
		MODEL_TYPE_L_SIGN,			//左の看板
		MODEL_TYPE_R_SIGN,			//右の看板
		MODEL_TYPE_LR_SIGN,			//両方の看板
		MODEL_TYPE_BRIDGE,			//橋
		MODEL_TYPE_STATUE,			//銅像
		MODEL_TYPE_PODIUM,			//表彰台
		MODEL_TYPE_BIGSIGN,			//大きな看板
		MODEL_TYPE_STONE,			//大きな岩
		MODEL_TYPE_GOAL,			//ゴール
		MODEL_TYPE_CLIFF_SIGN,		//崖看板
		MODEL_TYPE_FEED_SIGN,		//餌看板
		MODEL_TYPE_WATER_SIGN,		//水看板
		MODEL_TYPE_FEED_K,			//攻撃餌
		MODEL_TYPE_FEED_B,			//妨害餌
		MODEL_TYPE_FEED_S,			//速度餌
		MODEL_TYPE_EGG,				//卵
		MODEL_TYPE_CHICK,			//ヒヨコ
		MODEL_TYPE_DRIT,			//土煙エフェクト
		MODEL_TYPE_GRASS,			//草エフェクト
		MODEL_TYPE_MAX,				//最大数
	}MODEL_TYPE;

	typedef enum
	{// テクスチャの種類
		TEXTURE_TYPE_TREE = 0,		//木
		TEXTURE_TYPE_SAKU,			//柵
		TEXTURE_TYPE_BOX,			//箱
		TEXTURE_TYPE_MAP_FIRST,		//1番目
		TEXTURE_TYPE_MAP_SECOND,	//2番目
		TEXTURE_TYPE_MAP_MOUNTAIN,	//山
		TEXTURE_TYPE_MAP_SKY,		//空
		TEXTURE_TYPE_CHICKEN_HOUSE,	//鶏の家
		TEXTURE_TYPE_L_SIGN,		//左の看板
		TEXTURE_TYPE_R_SIGN,		//右の看板
		TEXTURE_TYPE_LR_SIGN,		//両方の看板
		TEXTURE_TYPE_BRIDGE,		//橋
		TEXTURE_TYPE_STATUE,		//銅像
		TEXTURE_TYPE_PODIUM,		//表彰台
		TEXTURE_TYPE_BIGSIGN,		//大きな看板
		TEXTURE_TYPE_STONE,			//大きな岩
		TEXTURE_TYPE_GOAL,			//ゴール
		TEXTURE_TYPE_CLIFF_SIGN,	//崖看板
		TEXTURE_TYPE_FEED_SIGN,		//餌看板
		TEXTURE_TYPE_WATER_SIGN,	//水看板
		TEXTURE_TYPE_FEED_K,		//攻撃餌
		TEXTURE_TYPE_FEED_B,		//妨害餌
		TEXTURE_TYPE_FEED_S,		//速度餌
		TEXTURE_TYPE_EGG_K,			//攻撃卵
		TEXTURE_TYPE_EGG_B,			//妨害卵
		TEXTURE_TYPE_EGG_S,			//速度卵
		TEXTURE_TYPE_CHICK_K,		//攻撃ヒヨコ
		TEXTURE_TYPE_CHICK_B,		//妨害ヒヨコ
		TEXTURE_TYPE_CHICK_S,		//速度ヒヨコ
		TEXTURE_TYPE_CHICK_K_S,		//強い攻撃ヒヨコ
		TEXTURE_TYPE_CHICK_B_S,		//強い妨害ヒヨコ
		TEXTURE_TYPE_CHICK_S_S,		//強い速度ヒヨコ
		TEXTURE_TYPE_DRIT,			//土煙エフェクト
		TEXTURE_TYPE_WATER,			//水エフェクト
		TEXTURE_TYPE_GRASS,			//草エフェクト
		TEXTURE_TYPE_MAX,			//最大数
	}TEXTURE_TYPE;

	CModel3D(int nPriority = 3, CScene::OBJTYPE objType = CScene::OBJTYPE_3DMODEL);
	~CModel3D();
	HRESULT				Init(void);
	void				Uninit(void);
	void				Update(void);
	void				Draw(void);
	static void			ModelShaderDeleter(void);
	static LPD3DXMESH	&MeshLoad(MODEL_TYPE modeltype);
	static void			UnLoad(void);
	D3DXVECTOR3			GetPosition(void) { return m_Pos; }
	D3DXVECTOR3			&GetRot(void) { return m_Rot; }
	D3DXVECTOR3			GetMove(void) { return m_Move; }
	D3DXVECTOR3			GetScale(void) { return m_Scale; }
	D3DXMATRIX			GetMtx(void) { return m_mtxWorldObject; }
	static D3DXVECTOR3	&GetVtxMin(int nNumber) { return m_VtxMinModel[nNumber]; }
	static D3DXVECTOR3	&GetVtxMax(int nNumber) { return m_VtxMaxModel[nNumber]; }
	D3DXVECTOR3			&GetposR(void) { return m_Pos; }
	D3DXVECTOR3			&GetrotR(void) { return m_Rot; }

	static CModel3D		*Create(void);
	void				SetMove(D3DXVECTOR3 m_move) { m_Move = m_move; }
	void				SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void				SetPosition(D3DXVECTOR3 pos) { m_Pos = pos; }
	void				SetRot(D3DXVECTOR3 rot) { m_Rot = rot; };
	bool				Collision(D3DXVECTOR3 pos, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin, D3DXVECTOR3 move);
	void				Setcol(D3DXCOLOR col) { m_col = col; m_bcolChange = true; }

	D3DXCOLOR			&GetCol(void) { return m_col; }
	MODEL_TYPE			&GetModelType(void) { return m_modeltype; }
	bool				&GetbColR(void) { return m_bcolChange; }
	D3DXVECTOR3			&GetScaleR(void) { return m_Scale; }
	float				*GetfCola(void) { return &m_fCola[0]; }
	static CToonShader	*&GetToonShader(void) { return m_pToonShader; }

protected:
	void				SetModelType(int nModelType) { m_nModelType = nModelType; }
	void				SetTextureType(int nTextureType) { m_nTextureType = nTextureType; }

private:
	static const char			*m_apModelFile[];								// モデルの文字を格納する
	static const char			*m_apTextureFile[];								// テクスチャの文字を格納する
	static LPD3DXMESH			m_pMeshModel[MODEL_TYPE_MAX];					// メッシュ情報へのポインタ
	static LPD3DXBUFFER			m_pBuffMatModel[MODEL_TYPE_MAX];				// マテリアルの情報へのポインタ
	static DWORD				m_nNumMatModel[MODEL_TYPE_MAX];					// マテリアルの情報数
	static CToonShader			*m_pToonShader;									// シェーダーのポインタ
	static LPDIRECT3DTEXTURE9	m_pMeshTextures[TEXTURE_TYPE_MAX];				// テクスチャの情報
	static D3DMATERIAL9			*m_pMeshMaterials[MODEL_TYPE_MAX];				// メッシュマテリアルの情報
	static LPDIRECT3DTEXTURE9	*m_pShaderMeshTextures[MODEL_TYPE_MAX];			// シェーダー用
	static D3DXVECTOR3			m_VtxMinModel[MODEL_TYPE_MAX];
	static D3DXVECTOR3			m_VtxMaxModel[MODEL_TYPE_MAX];					// モデルの最小値・最大値
	D3DXMATRIX					m_mtxWorldObject;								// ワールドマトリックス
	D3DXMATRIX					m_mtxRot;										// 回転マトリックス(保存用)
	D3DXQUATERNION				m_quat;											// クォータニオン
	D3DXVECTOR3					m_VecAxis;										// 回転軸
	float						m_fValueRot;									// 回転角(回転量)
	D3DXVECTOR3					m_Pos;											// 位置
	D3DXVECTOR3					m_Rot;											// 向き
	D3DXVECTOR3					m_Scale;										// サイズ
	D3DXVECTOR3					m_Move;											// 動き
	bool						m_bcolChange;									// カラー変更
	D3DXCOLOR					m_col;											// カラー
	float						m_fLength;										// 距離
	bool						m_bTexMat;										// シェーダーに使うテクスチャとマテリアル
	int							m_nModelType;									// モデルの種類
	int							m_nTextureType;									// テクスチャの種類
	D3DXVECTOR3					m_MapView;										// マップに反映させるカメラ
	MODEL_TYPE					m_modeltype;									// モデル種類
	float						m_fCola[MAX_PLAYCOL];							//キャラ分α値保存
};
#endif