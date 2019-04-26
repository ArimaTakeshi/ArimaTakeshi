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
	typedef enum
	{
		TEX_SCORE,		//スコア
		TEX_TIMER,		//タイマー
		TEX_PIcon,		//プレイヤーアイコン
		TEX_Darkness,	//闇背景
		TEX_Cloud1,		//雲背景1
		TEX_Cloud2,		//雲背景2
		TEX_UI000,		//レベルとスコアロゴ
		TEX_UI001,		//強化値アイコン
		TEX_Blood000,	//血痕
		TEX_BossLabel,	//全ボスアイコン
		TEX_Versus,		//ボス演出用VS
		TEX_VsSelect,	//バーサスセレクト枠
		TEX_Type,		//戦車のタイプ
		TEX_Stage,		//ステージの種類
		TEX_Icon,		//ステージの種類

		TEXTURE_MAX
	}TEXTURE;
	C2D() {};
	~C2D() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, D3DXCOLOR col, TEXTURE Texture);
	void	SetPosition(float fRot);
	void	SetPosition2(float fSize);
	void	SetUV(int nUV, int nUV_X, int nUV_Y);
	void	SetUV_Camera(float fUV_X, float fUV_Y, float m_fDiameter);
	void	SetGageUV(float fMaxLengthX);
	void	SetGage(float fLengthX, bool bDirection);
	void	SetColor(D3DXCOLOR col);
	void	SetSideAlpha(float fCol, float fMinCol, int nID);
	void	PlusUV(D3DXVECTOR2 uv);

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
	void	BindTexture(LPDIRECT3DTEXTURE9 *pTex)	 { m_pTex = pTex; }
	void	BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);		//テクスチャの破棄

	float		*GetfLengthX(void) { return &m_fLengthX; }
	D3DXVECTOR3 &GetPosition(void) { return m_pos; }
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
private://*****************************************************************************
		//変数宣言//***********************************************************************
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	D3DXVECTOR3				m_pos;				// ポリゴンの位置
	LPDIRECT3DTEXTURE9		*m_pTex;			// テクスチャ番号
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
		CSceneAnim3D::ANIMATION animation, D3DXCOLOR col, C2D::TEXTURE Texture);
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

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, float fUV_X, float fUV_Y, float fDiameter, D3DXCOLOR col, C2D::TEXTURE Texture);
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
		STATE_BIG, STATE_SMALL,
		STATE_MAX
	}STATE;
	C2DPolygon() {};
	~C2DPolygon() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture);
	void	Update(void);

	D3DXCOLOR	*GetColor(void) { return &m_col; }
	STATE		*GetState(void) { return &m_state; }
	float		&GetfCntState(void) { return m_fCntState; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	float				m_fCntState;		//STATE管理用
	STATE				m_state;			//使用方法
	D3DXCOLOR m_col;
};
#endif
