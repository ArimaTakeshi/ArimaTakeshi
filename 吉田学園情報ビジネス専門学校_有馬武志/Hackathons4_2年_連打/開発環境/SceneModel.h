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
#define MODEL_PRIORITY		(1)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneModel : public CScene
{
public:
	typedef enum
	{
		MODEL_TANKD = 0,
		MODEL_TANKU,
		//ダンジョン用object//
		MODEL_SHOP,			//破壊時ショップ出現
		//ダンジョンランダム生成//
		MODEL_BOX_2,
		MODEL_BOX_1,
		MODEL_STONE,
		MODEL_STEEL,
		MODEL_STEELBIOCK,
		MODEL_MAX
	}MODEL;
	typedef enum
	{
		/*宝箱*/	TEX_BOX_00, TEX_BOX_01, TEX_BOX_02,
		/*箱苔込*/	TEX_BOX_10, TEX_BOX_11, TEX_BOX_12,
		/*模様*/	TEX_PTN_01, TEX_PTN_02, TEX_PTN_03, TEX_PTN_04,
					TEX_PTN_05, TEX_PTN_06, TEX_PTN_07, TEX_PTN_08,
		/*オブジェ*/TEX_OBJ_00,
		TEXTURE_MAX
	}TEXTURE;
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

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, TEXTURE Type, DRAW_TYPE DrawType, bool bHit);
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄
	static void	LoadModel(MODEL model);					//モデルの生成
	static void UnLoadModel(void);				//Model解放
	static void GetLength(MODEL model, float& fLengthX, float& fLengthZ);

	D3DXVECTOR3			*GetPosition(void)				{ return &m_pos; }	//判定のためやむを得ない
	D3DXVECTOR3			*GetRotation(void)				{ return &m_rot; }
	void		BindTexture(LPDIRECT3DTEXTURE9 *pTex)	{ m_pTex = pTex; }
	MODEL				*GetModel(void)					{ return &m_Model; }
	CScene::DRAW_TYPE	*GetDrawType(void)				{ return &m_DrawType; }


protected://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
	//モデル//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//モデルへのポインタ


	//変数宣言//***********************************************************************
	//D3DXMATRIX			m_mtxWorld;			//ワールドマトリックス
	D3DXCOLOR			*GetColor(void)		{ return &m_col; }
	LPDIRECT3DTEXTURE9	*GetTexture(void)	{ return m_pTex; }
	STATE				*GetState(void)		{ return &m_state; }
	float				*GetfCntState(void) { return &m_fCntState; }

private://*****************************************************************************
	//変数宣言//***********************************************************************
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_rot;				//向き
	D3DXCOLOR			m_col;				//色
	LPDIRECT3DTEXTURE9	*m_pTex;			//画像
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
		USE_SHOP,	//ショップ出現
		USE_DROP,	//悲しみのドロップ量
		USE_DROP00, USE_DROP01, USE_DROP02,	//それぞれのドロップ
		USE_DROP10, USE_DROP11, USE_DROP12,	//爆発込み
		/*車体交換*/
		USE_PTN01, USE_PTN02, USE_PTN03, USE_PTN04,
		USE_PTN05, USE_PTN06, USE_PTN07, USE_PTN08,
		/*砲塔交換*/
		USE_PTN11, USE_PTN12, USE_PTN13, USE_PTN14,
		USE_PTN15, USE_PTN16, USE_PTN17, USE_PTN18,
		USE_MAX
	}USE;
	CSceneObjct(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CSceneObjct() {};

	void	Update(void);
	void	DropUninit(void);
	USE		*GetUse(void) { return &m_use; }
	CSceneModel::TEXTURE	GetTexType(USE use);
	void	DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky);		//アイテムドロップ関数
	bool	DropExplosion(void);										//爆発ドロップ
	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, TEXTURE Type, DRAW_TYPE DrawType, bool bHit, USE use)
	{
		CSceneModel::Set(pos, rot, col, model, Type, DrawType, bHit);
		m_use = use;
	}
private://*****************************************************************************
		//変数宣言//***********************************************************************
	USE m_use;
	int nLife;
};

#endif
