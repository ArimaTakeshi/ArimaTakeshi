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

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C3D
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_GOAL, STATE_SHOP,
		STATE_GOAL2, STATE_SHOP2,
		/*フェード*/STATE_FADESPIN, STATE_FADE, STATE_FADEIN, STATE_FADEOUT, STATE_FADEOUT2,
		/*UVフロー*/STATE_UVFLOW_0, STATE_UVFLOW_1,
		STATE_MAX
	}STATE;
	C3D() { m_Tex = NULL; };
	~C3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
			 int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType, CScene::TEXTURE tex, bool bBillboard);
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);

	D3DXVECTOR3 &GetPosition(void)	{ return m_pos; }
	D3DXVECTOR3 &GetRotation(void)	{ return m_rot; }
	D3DXCOLOR	&GetColor(void)		{ return m_col; }
	D3DXVECTOR3	&GetLength(void)	{ return m_length; }
	float		&GetfCntState(void) { return m_fCntState; }
	STATE		&GetState(void)		{ return m_state; }
	void		SetColor(D3DXCOLOR col);
	void		SetSize(D3DXVECTOR3 length);
	void		SetUV(int nUV, int nUV_X, int nUV_Y);
	void		SetGage(float fLengthX, float &fSlide);
	void		PlusUV(D3DXVECTOR2 uv);

	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_Tex = pTex; }

protected://*****************************************************************************
	void SetMtx(void);
	//変数用//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	LPDIRECT3DTEXTURE9		&GetTexture(void) { return m_Tex; }
	CScene::DRAW_TYPE		GetDrawType(void) { return m_DrawType; }
private://*****************************************************************************
	void MakeVertex(LPDIRECT3DDEVICE9 pDevice);
	//変数宣言//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXMATRIX			m_mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3			m_pos;				//位置
	D3DXVECTOR3			m_rot;				//向き
	D3DXCOLOR			m_col;				//色
	LPDIRECT3DTEXTURE9	m_Tex;			//画像
	CScene::DRAW_TYPE	m_DrawType;			// 描画する方法(加算合成など)
	D3DXVECTOR3			m_length;			//長さ
	float				m_fCntState;		//STATE管理用
	STATE				m_state;			//使用方法
	bool				m_bBillboard;		//ビルボードかどうか
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C3DEffect : public C3D
{
public:

	C3DEffect() { m_pPos = NULL; m_pScene = NULL; };
	~C3DEffect() {};

	void C3DEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
		int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene, bool bBillboard);
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
		ANIMATION_NORMAL = 0,
		ANIMATION_LOOP,
		ANIMATION_MAX
	}ANIMATION;
	CAnim3D() {};
	~CAnim3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
			CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, bool bBillboard);
	HRESULT Init(void);
	void	Update(void);

private://*****************************************************************************

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

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,
			CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, 
		int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene, bool bBillboard);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
#endif
