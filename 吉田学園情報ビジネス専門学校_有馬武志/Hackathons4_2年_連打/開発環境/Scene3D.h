#pragma once
//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

class CScenePlayer;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define S3D_PRIORITY		(3)
#define S3DF_PRIORITY		(4)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene3D : public CScene
{
public:
	typedef enum
	{
		/*その他*/	TEX_ITEM, TEX_TRAP,
		/*核*/		TEX_HEART,
		/*魔法陣*/	TEX_BOMB000,
		/*マーカー*/TEX_MARKER,
		/*チャージ*/TEX_CHARGE,
		/*マット*/	TEX_MATTE,
		/*ボスBG*/	TEX_BG000,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_GOAL,STATE_SHOP,
		STATE_GOAL2, STATE_SHOP2,
		/*フェード*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN, STATE_FADEOUT, STATE_FADEOUT2, STATE_FADEOUTN,
		/*UVフロー*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		/*ボスBG*/	STATE_BFLOW_IN, STATE_BFLOW_OUT,

		/*トラップ効果*/
		STATE_EXPLOSION0, STATE_EXPLOSION1	,STATE_BLACK0,
		STATE_ICE		, STATE_LIGHTNING	,STATE_FIRE	,
		STATE_WIND		, STATE_MONSTER		,

		/*アイテム効果*/
		STATE_HEEL0		, STATE_HEEL1	, STATE_HEEL2	, STATE_HEEL3	, STATE_HEEL4,
		STATE_SCORE0	, STATE_SCORE1	,
		STATE_LIFE		, STATE_DEFENSE	, STATE_ATTACK	,
		STATE_LIFEUP	, STATE_DEFUP	, STATE_ATKUP, STATE_SPDUP, STATE_PAIR0,
		STATE_NORIVER	, STATE_NOSTOP, STATE_CHARGEUP	, STATE_SCOREUP	, STATE_PAIR1,

		/*ショップ*/
		STATE_S_HEEL0, STATE_S_HEEL1, STATE_S_HEEL2, STATE_S_HEEL3, STATE_S_HEEL4,
		STATE_S_SCORE0, STATE_S_SCORE1,
		STATE_S_LIFE, STATE_S_DEFENSE, STATE_S_ATTACK,
		STATE_S_LIFEUP, STATE_S_DEFUP, STATE_S_ATKUP, STATE_S_SPDUP, STATE_S_PAIR0,
		STATE_S_NORIVER, STATE_S_NOSTOP, STATE_S_CHARGEUP, STATE_S_SCOREUP, STATE_S_PAIR1,

		/*ボスの状態*/
		STATE_WAIT, STATE_ATK, STATE_JUMP, STATE_CHANGE,

		STATE_MAX
	}STATE;
	CScene3D(int nPrioryity = 3) : CScene::CScene(nPrioryity) { m_pTex = NULL; };
	~CScene3D() {};

	void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, 
		TEXTURE nType, int nUV, int nUV_X, int nUV_Y, DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);		//テクスチャの生成
	static void					UnLoad(void);			//テクスチャの破棄

	D3DXVECTOR3 *GetPosition(void) { return &m_pos; }
	D3DXVECTOR3 *GetRotation(void) { return &m_rot; }
	D3DXCOLOR	*GetColor(void) { return &m_col; }
	float		*GetfLengthX(void) { return &m_fLengthX; }
	float		*GetfLengthZ(void) { return &m_fLengthZ; }
	float		*GetfCntState(void) { return &m_fCntState; }
	STATE		*GetState(void) { return &m_state; }
	void		SetColor(D3DXCOLOR col);
	void		SetSize(float fLengthX, float fLengthZ);
	void		SetUV(int nUV, int nUV_X, int nUV_Y);
	void		SetUVPattern(float fUV_X, float fUV_Y);
	void		PlusUV(D3DXVECTOR2 uv);
	void		ItemEffect(CScenePlayer *&pPlayer);
	void		BreakSale(void);
	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	CScene::DRAW_TYPE		&GetDrawType(void) { return m_DrawType; }
	static void		ItemBuy(void);
	void		BindTexture(LPDIRECT3DTEXTURE9 *pTex) { m_pTex = pTex; }

protected://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

	//変数用//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

	LPDIRECT3DTEXTURE9		*GetTexture(void) { return m_pTex; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	void Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLengthX, float &fLengthZ);
	//変数宣言//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_rot;				//向き
	D3DXCOLOR			m_col;				//色
	LPDIRECT3DTEXTURE9	*m_pTex;			//画像
	CScene::DRAW_TYPE	m_DrawType;			// 描画する方法(加算合成など)
	float				m_fLengthX;			//長さX	弾でもあたり判定に使うから結局消せない
	float				m_fLengthZ;			//長さZ 弾でないなら変更価値あるし...
	float				m_fCntState;		//STATE管理用
	STATE				m_state;			//使用方法

};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneEffect : public CScene3D
{
public:

	CSceneEffect(int nPrioryity = 3) : CScene3D::CScene3D(nPrioryity) { m_pPos = NULL; m_pScene = NULL; };
	~CSceneEffect() {};

	void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, int nUV, int nUV_X, int nUV_Y, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene);
	void Draw(void);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneFrontEffect : public CScene3D
{
public:

	CSceneFrontEffect(int nPrioryity = 4) : CScene3D::CScene3D(nPrioryity) { SetObjType(OBJTYPE_EFFECT); };
	~CSceneFrontEffect() {};
};
#endif
