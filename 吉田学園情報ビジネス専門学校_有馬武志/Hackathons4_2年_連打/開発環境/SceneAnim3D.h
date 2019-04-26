#pragma once
//=============================================================================
//
// シーン3D処理 [SceneAnim3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEANIM3D_H_
#define _SCENEANIM3D_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SAnim3D_PRIORITY		(3)
#define SAnim3DF_PRIORITY		(4)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneAnim3D : public CScene3D
{
public:
	typedef enum
	{
		/*爆発*/		TEX_EXPLOSION, TEX_FIRE_EXPLOSION,
		/*異常状態*/	TEX_FIRE,	TEX_ICE,	TEX_LIGHTNING,
		/*エフェクト*/	TEX_BARRIER, TEX_BEFFECT, TEX_MAGIC,
		/*ヒット*/		TEX_HIT,
		/*その他*/	TEX_GOAL, TEX_BREAK,
		/*チャージ*/TEX_CHARGE, TEX_CHARGE2, TEX_CHARGE3,
		/*ブースト*/TEX_BOOST,
		/*ドリフト*/TEX_DRIFT,
		/*ステUP*/	TEX_STATUS_UP,
		/*出現*/	TEX_APPEAR,
		/*回復*/	TEX_HEEL, TEX_SHIELD,
		/*装備切り替え*/TEX_WEAPON,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		ANIMATION_NORMAL = 0,
		ANIMATION_LOOP,
		ANIMATION_MAX
	}ANIMATION;
	CSceneAnim3D(int nPrioryity = SAnim3D_PRIORITY) : CScene3D::CScene3D(nPrioryity) { };
	~CSceneAnim3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state);
	HRESULT Init(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄
	static void					BreakPolygon(STATE state);

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
class CSceneAnimEffect : public CSceneAnim3D
{
public:

	CSceneAnimEffect(int nPrioryity = SAnim3D_PRIORITY) : CSceneAnim3D::CSceneAnim3D(nPrioryity) { m_pPos = NULL; m_pScene = NULL; };
	~CSceneAnimEffect() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneFrontAnim : public CSceneAnim3D
{
public:

	CSceneFrontAnim(int nPrioryity = SAnim3DF_PRIORITY) : CSceneAnim3D::CSceneAnim3D(nPrioryity) { SetObjType(OBJTYPE_EFFECT); };
	~CSceneFrontAnim() {};
};
#endif
