#pragma once
//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _3DPOLYGON_H_
#define _3DPOLYGON_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define S3D_PRIORITY		(3)
#define S3DF_PRIORITY		(4)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C3D
{
public:
	typedef enum
	{
		/*影*/	TEX_SHADOW,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_GOAL, STATE_SHOP,
		STATE_GOAL2, STATE_SHOP2,
		/*フェード*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN, STATE_FADEOUT, STATE_FADEOUT2,
		/*UVフロー*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		STATE_MAX
	}STATE;
	C3D() { m_pTex = NULL; };
	~C3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE Tex, int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄

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
	void		PlusUV(D3DXVECTOR2 uv);

	void		BindTexture(LPDIRECT3DTEXTURE9 *pTex) { m_pTex = pTex; }

protected://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

	//変数用//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	LPDIRECT3DTEXTURE9		*GetTexture(void) { return m_pTex; }
	CScene::DRAW_TYPE		GetDrawType(void) { return m_DrawType; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
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
class C3DEffect : public C3D
{
public:

	C3DEffect() { m_pPos = NULL; m_pScene = NULL; };
	~C3DEffect() {};

	void C3DEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene);
	void Draw(void);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CAnim3D : public C3D
{
public:
	typedef enum
	{
		/*エフェクト*/	TEX_BARRIER,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		ANIMATION_NORMAL = 0,
		ANIMATION_LOOP,
		ANIMATION_MAX
	}ANIMATION;
	CAnim3D() {};
	~CAnim3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state);
	HRESULT Init(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄

private://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

	//変数宣言//***********************************************************************
	int			m_nCntAnim;			//Animationのカウント
	int			m_nPtnAnim;			//指定された座標で表示
	int			m_nPtnHeight;		//画像の縦の分割数
	int			m_nPtnWide;			//画像の横の分割数
	int			m_nPtnSpeed;		//Animation速度
	ANIMATION	m_animation;		//使用方法
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CAnim3DEffect : public CAnim3D
{
public:

	CAnim3DEffect() { m_pPos = NULL; m_pScene = NULL; };
	~CAnim3DEffect() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
#endif
