#pragma once
//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_PRIORITY		(0)
#define SATELLITE_PRIORITY			(2)			//メッシュの優先順位

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneModel : public CScene
{
public:
	typedef enum
	{
		//ルーム　周囲
		MODEL_FENCE,	//柵
		MODEL_STEEL,	//鉄骨
		//ルーム　中心
		MODEL_STONE,	//岩
		MODEL_STEEL_B,	//鉄骨塊
		//ロード
		MODEL_BOX,		//木箱
		MODEL_STONE_S,	//小岩
		//エントランス

		MODEL_Gate,	//ゲート
		MODEL_ICE,	//氷
		MODEL_SATELLITE,	//衛星
		MODEL_POS_MAG,	//方位磁針(本体)
		MODEL_POS_NEE,	//方位磁針(針)
		MODEL_Earth,	//地球

		MODEL_Room,	//
		MODEL_Frame,	//
		MODEL_FrameV,	//
		MODEL_FrameC,	//

		MODEL_MAX
	}MODEL;
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_FADE,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_MAX
	}STATE;
	CSceneModel(int nPrioryity = MODEL_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CSceneModel() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit);
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static void	LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex);			//モデルの生成
	static void UnLoadModel(void);											//Model解放
	static void GetLength(MODEL model, D3DXVECTOR3 &length);				//モデルの長さ取得
	static float GetHeight(MODEL model);									//モデルの地面からの高さ取得
	static void SetShadow(void);

	void	SetMtx(void);									//マトリックスの設定
	void	PlusMtx(D3DXVECTOR3 &move);						//マトリックスの設定

	D3DXVECTOR3			&GetPosition(void)				{ return m_pos; }
	D3DXVECTOR3			&GetRotation(void)				{ return m_rot; }
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex)	{ m_pTex = pTex; }
	CScene::DRAW_TYPE	&GetDrawType(void)				{ return m_DrawType; }
	MODEL				&GetModel(void)					{ return m_Model; }
	D3DXMATRIX			&GetmtxWorld(void)				{ return m_mtxWorld; }

protected://*****************************************************************************
	//モデル//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//モデルへのポインタ


	//変数宣言//***********************************************************************
	D3DXCOLOR			&GetColor(void)		{ return m_col; }
	LPDIRECT3DTEXTURE9	&GetTexture(void)	{ return m_pTex; }
	STATE				&GetState(void)		{ return m_state; }
	float				&GetfCntState(void) { return m_fCntState; }

private://*****************************************************************************
	void	DrawModel(void);
	//変数宣言//***********************************************************************
	D3DXMATRIX			m_mtxWorld;			//ワールドマトリックス
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_rot;				//向き
	D3DXCOLOR			m_col;				//色
	LPDIRECT3DTEXTURE9	m_pTex;				//画像
	MODEL				m_Model;			//モデル
	CScene::DRAW_TYPE	m_DrawType;			// 描画する方法(加算合成など)
	STATE				m_state;			//使用方法
	float				m_fCntState;		//STATE管理用
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneObjct : public CSceneModel
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		USE_MAX
	}USE;
	CSceneObjct(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CSceneObjct() {};

	void	Update(void);
	void	DropUninit(void);
	USE		*GetUse(void) { return &m_use; }
	void	DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky);		//アイテムドロップ関数
	bool	DropExplosion(void);										//爆発ドロップ
	void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use);
	static bool CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static void SetObjField(void);
private://*****************************************************************************
		//変数宣言//***********************************************************************
	USE m_use;
	float fLife;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSatellite : public CSceneModel
{
public:
	CSatellite(int nPrioryity = SATELLITE_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CSatellite() {};
	void	Set(D3DXMATRIX &pMtx, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, D3DXVECTOR3 &move, float &fFrame, float fRot, float fDistance, bool &bDelete);
	void	Update(void);
	void	Draw(void);

	static void Delete(void);
	static void ReSet(void);
	float &GetfRot(void) { return m_fRot; }
	D3DXMATRIX *&GetpMtx(void) { return m_pMtx; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	D3DXMATRIX	*m_pMtx;		//追尾する位置
	D3DXVECTOR3 *m_pmove;		//移動量
	float		*m_pfFrame;		//フレーム数
	bool		*m_bDelete;		//消える判定

	float		m_fRot;			//自身の角度
	float		m_fMoveRot;		//揺れる用の角度
	float		m_fDistance;	//離れる距離
};
#endif
