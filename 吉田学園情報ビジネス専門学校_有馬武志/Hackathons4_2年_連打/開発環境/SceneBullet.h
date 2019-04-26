#pragma once
//=============================================================================
//
// 弾全般処理 [SceneBullet.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEBULLET_H_
#define _SCENEBULLET_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHOT_UV_X		(16)
#define SHOT_UV_Y		(10)
#define SHOT_UV_SMALL	(0.003f)
#define SHOT_DROW_X		(105.0f)
#define SHOT_DROW_Z		(59.0f)

#define SHOT_MAX_SPD	(0.05f)
#define SHOT_LIFE		(720.0f)

#define BULLET_PRIORITY		(5)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneBullet : public CScene3D
{
public:
	typedef enum
	{//発砲者
		SHOT_PLAYER1,
		SHOT_PLAYER2,
		SHOT_ENEMY,
		SHOT_IGNORED,
		SHOT_TROP,
		SHOT_MAX
	}SHOT;
	typedef enum
	{//変化
		CHANGE_NONE = 0,	//変化なし
		CHANGE_SPDUP,		//加速値
		CHANGE_SPDDOWN,		//減速
		CHANGE_BACK,		//Spd少しずつ反転
		CHANGE_BACK2,		//途中でSpd急に反転
		CHANGE_STRAIGHT,	//回転値 (*)
		CHANGE_SPINUP,		//回転値 (+)
		CHANGE_SLOW,		//遅く
		CHANGE_HOMING,		//途中でいきなり敵方向を向く
		CHANGE_HOMINGS,		//途中でいきなり敵方向を向き数F止まる
	//発射時//***********************************************************************
		CHANGE_NO = -1,	//変化なし
		CHANGE_FAST,		//初期加速
		CHANGE_FAST2,		//超初期加速
		CHANGE_GRAVITY,		//逆方向(ブレアリ)でジャンプ
		CHANGE_GRAVITY2,	//逆方向(超ブレ)でジャンプ
		CHANGE_MAX,
	}CHANGE;
	typedef enum
	{
		//一定間隔で起動
		SET_NONE,			//置くだけ
		SET_TURN,			//回転込置くだけ
		SET_EFFECT,	SET_EFFECT0,			//エフェクト感覚
		SET_SHOT,			//発射
		SET_SHOT2,			//発射
		SET_BEAM,			//BEAM
		SET_NEEDLE,			//棘のような球
		SET_PDIFFUSION00, SET_PDIFFUSION01,			//拡散 ばら撒く子機
		SET_RELEASE,			//順番開放
		SET_RANDSHOT,		//適当に発射
		SET_BACK_G,			//真後ろ重力付き
		SET_BACK_G2,		//真後ろ重力付き幅まし
		SET_FIRE0,			//後ろばらまき
		SET_FIRE,			//後ろばらまき
		SET_CROSS,			//十字発射
		SET_AROUND,			//左右分裂
		//起動時消滅//
		SET_PDIFFUSION,		//ばら撒く子機
		SET_PDIFFUSION2,	//生存時間が長い
		SET_DIFFUSION,		//ばら撒いて散る
		SET_DIFFUSION2,		//ばら撒いて散る
		SET_BRANCH,	//十字分裂発射　回転値無し
		SET_BRANCHES,		//枝分かれ
		//攻撃方法//
		SET_BATK_BRANCH,
		SET_BATK_CROSS,

		SET_MAX
	}SET;
	typedef enum
	{//攻撃方法//
		ATK_PTN00		, ATK_PTN01		, ATK_PTN02	, ATK_PTN03,	//基本パターン
		ATK_BEAM00		, ATK_BEAM01	, ATK_BEAM02, ATK_BEAM10,
		ATK_SETTING0	, ATK_SETTING1	,
		ATK_DIFFUSION	,ATK_PDIFFUSION	, ATK_PDIFFUSION2,				//拡散 ばら撒く子機
		ATK_PTN_FIRE	, ATK_PTN_FIRE2	, ATK_PTN_FIRE3,
		//ボス攻撃法//***********************************************************************
		BATK_BRANCH,
		BATK_CROSS,
		BATK_SPIN_0,
		BATK_SPIN_1,
		MAX
	}ATTACK;
	typedef enum
	{//画像//***********************************************************************
		/*弾*/		TEX_BULLET, TEX_BULLET2, TEX_BULLET_S,
		TEXTURE_MAX
	}TEXTURE;

	CSceneBullet(int nPriority = BULLET_PRIORITY) : CScene3D::CScene3D(nPriority) {};
	~CSceneBullet() {};
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//テクスチャの生成
	static void					UnLoad(void);	//テクスチャの破棄
	static void					ShotAttack(SHOT Shot, ATTACK Set, D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRotU, bool bFirst,
											float fSpd, float fSlip, float fLife, float fTurning, float fAccelerator, float fLengthX, float fLengthZ,
											float fRange, float fDistance, int nNumBullet, int nChange, CHANGE Change, float fAtk, bool bDestroy, bool *bShotDelete, int nUV);
	static void					BreakBullet(bool bAll);
	static void					CircleBreak(D3DXVECTOR3 pos, float fLength, SHOT shot1, SHOT shot2);
	bool CSceneBullet::SetAttack(SET SetType, float fMaxLife, float fAngleSet, int nNumSet, D3DXVECTOR3 move, int nUV, int& nInterval);
	bool LifeUpdate(void);

	HRESULT	Init(void) { CScene3D::Init(); CScene::SetObjType(OBJTYPE_BULLET);  return S_OK; };
	void	Draw(void);
	SHOT	*GetShot(void) { return &m_shot; }
	float	*GetfAtk(void) { return &m_fAtk; }
	bool	&GetbDestroy(void) { return m_bDestroy; }
	bool	*&GetbShotDelete(void) { return m_bShotDelete; }

	//void						SetPosition(D3DXVECTOR3 pos) { GetPosition()[0] += pos; };
	//void						SetRotation(float fRotY) { GetRotation()[0].y = fRotY; };
protected://*****************************************************************************
	void SetVtx(int nUV);

	//変数宣言//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
	SHOT	m_shot;		//発砲者のタグ	チーム分けタグのようなもの
	int		m_nChange;	//弾の変化タイプ
	float	m_fSpeed;		//スピード
	float	m_fAccelerator;	//加速値
	float	m_fTurning;		//旋回スピード
	float	m_fSlip;		//慣性
	float	m_fAtk;			//弾の攻撃力
	bool	m_bDestroy;		//破壊の有無
	bool	*m_bShotDelete;	//弾の破棄の有無
private://*****************************************************************************
	void DrawParts(float fPosY, LPDIRECT3DDEVICE9& pD3DDevice);
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneNorBullet : public CSceneBullet
{
public:

	CSceneNorBullet(int nPriority = BULLET_PRIORITY) : CSceneBullet::CSceneBullet(nPriority) {};
	~CSceneNorBullet() {};

	void Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete);
	void	Update(void);

protected://*****************************************************************************
	void SetMove(CHANGE& change);
		  //変数宣言//***********************************************************************
	D3DXVECTOR3 m_move;	//移動量
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneSetBullet : public CSceneNorBullet
{
public:
	CSceneSetBullet(int nPriority = BULLET_PRIORITY) : CSceneNorBullet::CSceneNorBullet(nPriority) {};
	~CSceneSetBullet() {};

	void CSceneSetBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete,
		SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval);
	void	Update(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	SET 	m_SetType;		//弾をセットするID
	float	m_fAngleSet;	//セット角度
	float	m_fAnglePlus;	//セット角度に+
	int 	m_nNumSet;		//弾をセットする数
	int		m_nInterval;	//セット起動間隔
	int		m_nUV;			//色選択権
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScenePairBullet : public CSceneNorBullet
{
public:
	CScenePairBullet(int nPriority = BULLET_PRIORITY) : CSceneNorBullet::CSceneNorBullet(nPriority) {};
	~CScenePairBullet() {};

	void CScenePairBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fXWall, float fZWall, float fRangeX, float fRangeZ,
		SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete);
	HRESULT	Init(void) { CSceneNorBullet::Init(); CScene::SetObjType(OBJTYPE_EFFECT);  return S_OK; };
	void Update(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	D3DXVECTOR3		*m_pPos;	//親の場所
	float			*m_pRot;	//親の角度
	D3DXVECTOR3		m_pos2;		//自分の位置
	D3DXVECTOR3		m_pos3;		//追尾する親の位置
	float	m_fRangeX;			//壁衝突時角度変更範囲
	float	m_fRangeZ;			//壁衝突時角度変更範囲
	float	m_fXWall;			//縦の壁
	float	m_fZWall;			//横の壁

	int		m_nNumCount;	//発射間隔のカウント
	float	m_fLife;		//生命値　-ならずっと

	SET 	m_SetType;		//弾をセットするID
	float	m_fAngleSet;	//セット角度
	float	m_fAnglePlus;	//セット角度に+
	int 	m_nNumSet;		//弾をセットする数
	int		m_nInterval;	//セット起動間隔
	float	m_fMaxLife;			//最初の生命値
	int		m_nUV;			//色選択権
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScenePairBullet2 : public CSceneBullet
{
public:
	CScenePairBullet2(int nPriority = BULLET_PRIORITY) : CSceneBullet::CSceneBullet(nPriority) {};
	~CScenePairBullet2() {};

	void CScenePairBullet2::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
		D3DXVECTOR3 *pPos, float *pRot, bool bDestroy, bool *bShotDelete);
	void Update(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	D3DXVECTOR3		*m_pPos;	//親の場所
	float			*m_pRot;	//親の角度
	D3DXVECTOR3		m_pos3;		//追尾する親の位置
	float			m_fAngle;		//親から見た角度
	float			m_fDistance;	//親までの距離
	float			m_fGMagnification;	//目的にいくまでの倍率
	float			m_fLife;		//生命値　-ならずっと
	float			m_fMaxLife;			//最初の生命値
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScenePairBulletSet : public CScenePairBullet2
{
public:
	CScenePairBulletSet(int nPriority = BULLET_PRIORITY) : CScenePairBullet2::CScenePairBullet2(nPriority) {};
	~CScenePairBulletSet() {};

	void CScenePairBulletSet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
		SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete);
	void Update(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	int		m_nNumCount;	//発射間隔のカウント
	SET 	m_SetType;		//弾をセットするID
	float	m_fAngleSet;	//セット角度
	float	m_fAnglePlus;	//セット角度に+
	int 	m_nNumSet;		//弾をセットする数
	int		m_nInterval;	//セット起動間隔
	int		m_nUV;			//色選択権
};
#endif
