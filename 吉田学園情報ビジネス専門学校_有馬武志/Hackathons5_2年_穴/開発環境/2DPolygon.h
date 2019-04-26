//=============================================================================
//
// 2DPolygon処理 [2DPolygon.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _2DPOLYGON_H_
#define _2DPOLYGON_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C2D
{
public:
	C2D() {};
	~C2D() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, D3DXCOLOR col);
	void	SetPosition(float fRot);
	void	SetPosition2(float fSize);
	void	SetUV(int nUV, int nUV_X, int nUV_Y);
	void	SetUV_Camera(float fUV_X, float fUV_Y, float m_fDiameter);
	void	SetGageUV(float fMaxLengthX);
	void	SetGage(float fLengthX, int nDirection);
	void	SetColor(D3DXCOLOR col);
	void	PlusColor(D3DXCOLOR col);
	void	SetSideAlpha(float fCol, float fMinCol, int nID);
	void	PlusUV(D3DXVECTOR2 uv);

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 pTex)	 { m_pTex = pTex; }
	void	BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }

	float		*GetfLengthX(void) { return &m_fLengthX; }
	D3DXVECTOR3 &GetPosition(void) { return m_pos; }
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
private://*****************************************************************************
		//変数宣言//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;				// ポリゴンの位置
	LPDIRECT3DTEXTURE9		m_pTex;			// テクスチャ番号
	CScene::DRAW_TYPE		m_DrawType;		// 描画する方法(加算合成など)
	float					m_fLengthX;			// ポリゴンの長さX
	float					m_fLengthY;			// ポリゴンの長さY
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C2DAnim : public C2D
{
public:
	C2DAnim() {};
	~C2DAnim() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, 
		CSceneAnim3D::ANIMATION animation, D3DXCOLOR col);
	void	Update(void);
private://*****************************************************************************
		//変数宣言//***********************************************************************
	int			m_nCntAnim;			//Animationのカウント
	int			m_nPtnAnim;			//指定された座標で表示
	int			m_nPtnHeight;		//画像の縦の分割数
	int			m_nPtnWide;			//画像の横の分割数
	int			m_nPtnSpeed;		//Animation速度
	CSceneAnim3D::ANIMATION		m_animation;		//使用方法
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C2DCameraBG : public C2D
{
public:
	C2DCameraBG() {};
	~C2DCameraBG() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, float fUV_X, float fUV_Y, float fDiameter, D3DXCOLOR col);
	void	Update(void);
private://*****************************************************************************
		//変数宣言//***********************************************************************
	float	m_fUV_X;		//UV_X
	float	m_fUV_Y;		//UV_Y
	float	m_fUV_XPlus;	//Xのプラス値
	float	m_fUV_YPlus;	//Yのプラス値
	float	m_fDiameter;	//カメラ距離の倍率
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C2DPolygon : public C2D
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_FADE,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_SLIDEIN, STATE_SLIDEOUT,
		STATE_SLIDEIN2, STATE_SLIDEOUT2,
		STATE_BIG, STATE_MEDIUM, STATE_SMALL,
		STATE_MAX
	}STATE;
	C2DPolygon() {};
	~C2DPolygon() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col);
	void	Update(void);

	D3DXCOLOR	&GetColor(void) { return m_col; }
	STATE		&GetState(void) { return m_state; }
	float		&GetfCntState(void) { return m_fCntState; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	float				m_fCntState;		//STATE管理用
	STATE				m_state;			//使用方法
	D3DXCOLOR m_col;
};
#endif
