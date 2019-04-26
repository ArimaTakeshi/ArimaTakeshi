#pragma once
//=============================================================================
//
// プレイヤー処理(戦車処理を含む) [ScenePlayer.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEPlayer_H_
#define _SCENEPlayer_H_

#include "main.h"
#include "scene.h"
#include "sceneModel.h"
#include "SceneAnim3D.h"
#include "SceneBullet.h"
#include "Number.h"
#include "2DGage.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_D		(0)
#define MODEL_U		(1)
#define CAMERA_Y	(475.0f)
#define SHOT_JUST	(6)
#define PLUS_LIFE	(50.0f)
#define PLUS_ATK	(0.01f)
#define PLUS_DEF	(0.01f)
#define PLAYER_Y	(20.5f)
#define BOMB_WAIT_TIME		(600)
#define BOMB_TIME			(BOMB_WAIT_TIME + 60)
#define MAX_UI			(5)
#define UI_PRIORITY		(6)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class ITEM
{
public:
	typedef enum
	{//アイテムの種類
		TYPE_SPDUP = 0,
		TYPE_PAIR0, TYPE_NORIVER, TYPE_NOSTOP,
		TYPE_CHARGEUP, TYPE_SCOREUP, TYPE_PAIR1,
		TYPE_MAX
	}TYPE;
	ITEM() {};
	~ITEM() {};
	TYPE			&GetType(void) { return m_type; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	TYPE	m_type;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class ITEM_PAIR : public ITEM
{
public:
	typedef enum
	{//アイテムの種類
		ITEM_SPDUP = 0,
		ITEM_PAIR0, ITEM_NORIVER, ITEM_NOSTOP,
		ITEM_CHARGEUP, ITEM_SCOREUP, ITEM_PAIR1,
		ITEM_MAX
	}TYPE;
	ITEM_PAIR() { m_bShotDelete = true; };
	~ITEM_PAIR() {};
	bool	&GetShotDelete(void) { return m_bShotDelete; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	bool	m_bShotDelete;
};

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneTank : public CSceneModel
{
public:
	CSceneTank(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity)
	{
		m_pEffect = NULL; m_pEffectU = NULL;
	};
	~CSceneTank() {};

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);

	bool Damage(float fAtk);
	void Heel(float fHeel, bool bEffect);
	void Heal(void);
	void EffectUpdate(void);
	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType);
	CSceneBullet::SHOT *GetShot(void)	{ return &m_shot; }
	D3DXVECTOR3 *GetPositionOld(void)	{ return &m_posold; }
	D3DXVECTOR3 *GetMove(void)			{ return &m_move; }
	float		&GetfSlip(void)			{ return m_fSlip; }

	float		*GetfMoveAngle(void)	{ return &m_fMoveAngle; }
	float		&GetfCharge(void)		{ return m_fCharge; }
	float		*GetfLife(void)			{ return &m_fLife; }
	float		&GetfMaxLife(void)		{ return m_fMaxLife; }
	float		&GetfAtk(void)			{ return m_fAttack; }
	float		&GetfDef(void)			{ return m_fDefense; }
	int			&GetnLevel(void)		{ return m_nLevel; }
	int			&GetnFire(void)			{ return m_nFire; }
	int			&GetnIce(void)			{ return m_nIce; }
	int			&GetnLightning(void)	{ return m_nLightning; }
	int			&GetnUV(void)			{ return m_nUV; }
	void		GetStatus(void);	//ステータス計算

	CSceneFrontAnim		*GetpEfect(void)		{ return m_pEffect; }
	LPDIRECT3DTEXTURE9	*&GetTextureU(void)		{ return m_pTexU; }
	TEXTURE				&GetTEX_TYPE(int nType)	{ return m_Type[nType]; }
	MODEL				&GetModelU(void)		{ return m_ModelU; }
	CSceneFrontEffect	*&GetpEffectU(void)		{ return m_pEffectU; }
	D3DXVECTOR3			*GetRotationU(void)		{ return &m_rotU; }

protected://*****************************************************************************
	typedef enum
	{
		CHARGE_NO = 0,
		CHARGE_30,
		CHARGE_90,
		CHARGE_180,
		CHARGE_300,
		CHARGE_MAX
	}CHARGE;
	void	Update(bool bMove, bool bCharge, bool bShot, bool bShelling, bool bBoost, bool bBrake, ITEM *pItem);
	void	DrawModel(int nModelID);
	void	ChargeNews(D3DXVECTOR3 *&pos);

	void	Shot(D3DXVECTOR3 *&pos, float fChargeP);	//チャージに応じた弾を発射 砲塔によって変わる
	void	Shot_Ptn01(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN01 弾幕
	void	Shot_Ptn02(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN02 弾幕
	void	Shot_Ptn03(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN03 弾幕
	void	Shot_Ptn04(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN04 弾幕
	void	Shot_Ptn05(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN05 弾幕
	void	Shot_Ptn06(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN05 弾幕
	void	Shot_Ptn07(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN05 弾幕
	void	Shot_Ptn08(int nCharge, D3DXVECTOR3 *&pos);	//砲塔PTN05 弾幕

	void	ShortAtk(D3DXVECTOR3 *&pos);				//近接攻撃, 砲塔によって変わる
	void	Short_Ptn01(D3DXVECTOR3 *&pos);			//砲塔PTN01 砲撃
	void	Short_Ptn02(D3DXVECTOR3 *&pos);			//砲塔PTN02 砲撃
	void	Short_Ptn03(D3DXVECTOR3 *&pos);			//砲塔PTN03 砲撃
	void	Short_Ptn04(D3DXVECTOR3 *&pos);			//砲塔PTN04 砲撃
	void	Short_Ptn05(D3DXVECTOR3 *&pos);			//砲塔PTN05 砲撃
	void	Short_Ptn06(D3DXVECTOR3 *&pos);			//砲塔PTN05 砲撃
	void	Short_Ptn07(D3DXVECTOR3 *&pos);			//砲塔PTN05 砲撃
	void	Short_Ptn08(D3DXVECTOR3 *&pos);			//砲塔PTN05 砲撃


	//変数用//***********************************************************************
	//bool		*GetbBarrier(void) { return &bBarrier; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	CSceneFrontAnim		*m_pEffect;		//戦車のエフェクト
	CSceneFrontEffect	*m_pEffectU;	//砲塔のエフェクト
	//bool				m_bBarrier;

	CSceneBullet::SHOT	m_shot;			//撃ったもの
	MODEL				m_ModelU;		//砲塔モデル
	LPDIRECT3DTEXTURE9	*m_pTexU;		//画像

	D3DXVECTOR3			m_rotU;			//砲塔の角度
	D3DXVECTOR3			m_posold;		//移動量
	D3DXVECTOR3			m_move;			//移動量
	float				m_fMoveAngle;	//移動方向
	float				m_fSlip;		//慣性
	float				m_fCharge;		//Charge量
	int					m_nBoostTime;	//ブーストへの待ち時間
	float				m_fWaitTime;	//移動不可の待ち時間

	float				m_fLife;		//ヒットポイント
	TEXTURE				m_Type[2];		//砲塔と車体の画像　分岐に必要
	int					m_nLevel;		//レベル
	bool				m_bShotDelete;	//弾を消す判断

	int					m_nFire;		//やけど	毎Fダメージ
	int					m_nIce;			//凍結		移動速度DOWN
	int					m_nLightning;	//感電		チャージ速度半減
	int					m_nUV;			//弾の色
		//計算後ステータス//***********************************************************************
	float				m_fMaxLife;		//Maxヒットポイント
	float				m_fAttack;		//攻撃力
	float				m_fDefense;		//防御力
	float				m_fSpeed;		//速度
	float				m_fWeight;		//重さ
	float				m_fBoost;		//加速時+速度
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScenePlayer : public CSceneTank
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_ADVANCE,		//次のマップへ進む
		STATE_MAX
	}STATE;

	CScenePlayer(int nPrioryity = MODEL_PRIORITY) : CSceneTank::CSceneTank(nPrioryity)
	{ 
		m_nPlayerID = m_nNumPlayer; m_nNumPlayer++; m_pHeart = NULL; m_pLifeGage = NULL; m_pExpGage = NULL;
		for (int nCount = 0; nCount < MAX_UI; nCount++) { m_pUI[nCount] = NULL; m_pNumber[nCount] = NULL; }
	};
	~CScenePlayer() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);

	bool	PlayPlayer(void);
	void	Shield(void);
	void	PEffectUpdate(void);
	void	DeadPlayer(bool bDead);
	void	DrawUI(void);
	void	PlusLevel(int nLevel);
	void	SetItem(ITEM::TYPE Item);
	void	AddExp(int nExp);

	static	int		&GetnNumPlayer(void) { return m_nNumPlayer; }
	static	int		&GetnStage(void)	{ return m_nStage; }
	static	bool	&GetbCamera(void)	{ return m_bCamera; }
	static	bool	&GetbShop(void)		{ return m_bShop; }
	CNumber			*&GetScore(void)	{ return m_pNumber[1]; }

	int				&GetLifeUP(void)	{ return m_pNumber[2]->GetnNumber(); }
	int				&GetAtkUP(void)		{ return m_pNumber[4]->GetnNumber(); }
	int				&GetDefUP(void)		{ return m_pNumber[3]->GetnNumber(); }
	ITEM			*&GetItem(void)		{ return m_pItemType; }
	int				&GetnDeadCount(void) { return m_nDeadCount; }

	void			PlusLifeUP(int nPlus) { m_pNumber[2]->AddNumber(nPlus); }
	void			PlusDefUP(int nPlus)  { m_pNumber[3]->AddNumber(nPlus); }
	void			PlusAtkUP(int nPlus)  { m_pNumber[4]->AddNumber(nPlus); }
	int				&GetPlayerID(void)	{ return m_nPlayerID; }
	int				&GetnInvincible(void) { return m_nInvincible; }

	CSceneFrontEffect *&GetpHeart(void) { return m_pHeart; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static	int		m_nNumPlayer;	//合計プレイヤー数
	static	int		m_nStage;		//ステージ番号
	static	bool	m_bCamera;		//カメラを動かす権利
	static	bool	m_bShop;		//現在がショップかどうか

	//アイテム
	float	m_fExp;			//経験値
	float	m_fMaxExp;			//経験値
	ITEM	*m_pItemType;			//アイテムの種類

	CSceneFrontEffect	*m_pHeart;		//戦車心臓のエフェクト
	CSceneFrontEffect	*m_pBomb;		//ボムのエフェクト(魔法陣)
	int		m_nBombTime;		//ボム使用までの時間カウント
	int		m_nDeadCount;		//死亡して消えるまでの時間
	int		m_nInvincible;		//無敵時間

	int				m_nPlayerID;	//プレイヤーID
	C2D				*m_pIcon;		//アイコン
	C2D				*m_pItem;		//アイテム
	C2DGage			*m_pLifeGage;	//HPゲージ
	C2DGage			*m_pExpGage;	//EXPゲージ

	C2D				*m_pUI[MAX_UI];		//レベル、スコア、強化値3つ
	CNumber			*m_pNumber[MAX_UI];	//レベル、スコア、強化値3つ
};

#endif
