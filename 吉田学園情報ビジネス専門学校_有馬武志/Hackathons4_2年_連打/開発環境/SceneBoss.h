#pragma once
//=============================================================================
//
// シーン3D処理 [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEBOSS_H_
#define _SCENEBOSS_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"
#include "2DGage.h"
#include "sound.h"
#include "manager.h"

class C3D;
class CFont;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SBOSS_PRIORITY		(1)
#define MAX_BEfeect			(2)
#define UI_PRIORITY			(6)
#define SBOSS_LENGTH		(10.0f)

//*****************************************************************************
// クラスの定義 ボス用UI
//*****************************************************************************
class CSceneBossUI : public CScene
{
public:
	CSceneBossUI(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity) { m_pLifeGage = NULL; m_p2D = NULL; };
	~CSceneBossUI() {};

	C2DGage *&GetGage(void)			{ return m_pLifeGage; };
	C2D *&Getp2D(void)	{ return m_p2D; };
	void Uninit(void);	//削除
	void Update(void);	//更新
	void Draw(void);	//描画

private:
	C2DGage			*m_pLifeGage;	//HPゲージ
	C2D				*m_p2D;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneBoss : public CScene3D
{
public:
	typedef enum
	{
		/*店長*/	TEX_MANAGER,
		/*初期ボス*/	TEX_BOSS01,
		TEXTURE_MAX
	}TEXTURE;

	CSceneBoss(int nPrioryity = SBOSS_PRIORITY) : CScene3D::CScene3D(nPrioryity) { SetObjType(CScene::OBJTYPE_BOSS); m_p3DShadow = NULL; m_pUI = NULL; };
	~CSceneBoss() {};

	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);		//テクスチャの生成
	static void					UnLoad(TEXTURE tex);	//テクスチャの指定破棄
	static void					UnLoad(void);			//テクスチャの破棄
	void Update(void);
	void Draw(void);
	void Uninit(void) { if (m_pUI != NULL) { m_pUI->Uninit(); m_pUI = NULL; } CScene3D::Uninit(); };
	void DropUninit(void);
	void SetStatus(TEXTURE tex);
	void InitShadow(void);
	bool Damage(float fAtk);
	void SetJump(float fJump) { m_move.y = fJump; m_bJump = true; };
	void CreateUI(TEXTURE tex);
	static void Appear(TEXTURE tex);

	TEXTURE &GetTexture(void)		{ return m_TexType; };
	D3DXVECTOR3 &GetPosOld(void)	{ return m_posold; };
	D3DXVECTOR3 &GetMove(void)		{ return m_move; };
	float &GetfLife(void)			{ return m_fLife; };
	float &GetfMaxLife(void)		{ return m_fMaxLife; };
	float &GetfAtk(void)			{ return m_fAttack; };
	float &GetfDef(void)			{ return m_fDefense; };
	float &GetfPlusY(void)			{ return m_fPlusY; };
	float &GetfModeChange(void)		{ return m_fModeChange; };
	float &GetfAngle(void)			{ return m_fAngle; };
	bool  &GetbJump(void)			{ return m_bJump; }
	bool  &GetbShotDelete(void)		{ return m_bShotDelete; }
	bool  &GetbCollision(void)		{ return m_bCollision; }
protected://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

private://*****************************************************************************
	static C2DGage			*m_pLifeGage;	//HPゲージ

	D3DXVECTOR3 m_posold;		//前の場所
	D3DXVECTOR3 m_move;		//移動量
	int		m_nLevel;		//レベル
	float	m_fMaxLife;		//Maxヒットポイント
	float	m_fLife;		//ヒットポイント
	float	m_fAttack;		//攻撃力
	float	m_fDefense;		//防御力
	float	m_fPlusY;		//ジャンプ表現等に使用 実際に加算するのはZ軸
	float	m_fModeChange;	//次の行動までのF数
	float	m_fAngle;		//発射方向
	bool	m_bShotDelete;	//自機の弾の削除判断用
	bool	m_bJump;		//ジャンプ判断用
	bool	m_bCollision;	//当たり判定の有無
	TEXTURE	m_TexType;		//画像　判別用
	C3D		*m_p3DShadow;	//影
	CSceneBossUI	*m_pUI;	//UI
};
//*****************************************************************************
// クラスの定義 ボス出現演出用
//*****************************************************************************
class CSceneBossEffect : public CScene
{
public:
	CSceneBossEffect(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_nCntState = 0;
		for (int nCount = 0; nCount < MAX_BEfeect; nCount++)
		{
			m_p2D[nCount] = NULL;
		}
	};
	~CSceneBossEffect() {};

	C2DPolygon *&Getp2D(void) { return m_p2D[0]; };
	void Uninit(void);	//削除
	void Update(void);	//更新
	void Draw(void);	//描画
	void Set(CSceneBoss::TEXTURE tex);	//設定

private:
	int		m_nCntState;
	C2DPolygon		*m_p2D[MAX_BEfeect];
};

//*****************************************************************************
// クラスの定義 店長
//*****************************************************************************
class CSceneManager : public CSceneBoss
{
public:
	typedef enum
	{
		/*入店*/	MANAGER_START,
		/*購入*/	MANAGER_BUY,
		/*店長*/	MANAGER_WAIT,
		/*被弾*/	MANAGER_DAMAGE,
		/*回復*/	MANAGER_HEEL,
		/*攻撃*/	MANAGER_ATK,
		MANAGER_MAX
	}MANAGER;
	typedef enum
	{
		ATTACK_START,	//初期攻撃
		ATTACK_HALF,	//HPが半分削られた
		ATTACK_0,		//ばら撒き
		ATTACK_1,		//ターゲット方向レーザー
		ATTACK_2,		//ターゲット地点爆発
		ATTACK_3,		//円形ばら撒き
		ATTACK_MAX
	}ATTACK;
	CSceneManager(int nPrioryity = SBOSS_PRIORITY) : CSceneBoss::CSceneBoss(nPrioryity) { m_pFont = NULL; m_p2D = NULL; };
	~CSceneManager() {};

	void Set(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	MANAGER &GetManager(void) { return m_Manager; };

private:
	// 関数宣言 //***********************************************************************
	void Attack_Start(void);
	void Attack_Half(void);
	void Attack_0(void);
	void Attack_1(void);
	void Attack_2(void);
	void Attack_3(void);
	// 変数宣言 //***********************************************************************

	ATTACK  m_Attack;		//現在の攻撃パターン
	MANAGER m_Manager;		//店長の状態
	bool	m_bFly;			//下降か上昇か
	bool	m_bHalf;		//半分切ったかどうか
	D3DXVECTOR3 m_Target;	//発動までの保存用
	CFont	*m_pFont;		//文字のポインタ
	CScene2D	*m_p2D;			//文字のウィンドウ
};
//*****************************************************************************
// クラスの定義 初期ボス
//*****************************************************************************
class CSceneBoss01 : public CSceneBoss
{
public:
	typedef enum
	{
		ATTACK_START,	//初期攻撃
		ATTACK_HALF,	//HPが半分削られた
		ATTACK_0,		//ばら撒き
		ATTACK_1,		//ターゲット方向レーザー
		ATTACK_2,		//ターゲット地点爆発
		ATTACK_3,		//円形ばら撒き
		ATTACK_MAX
	}ATTACK;
	CSceneBoss01(int nPrioryity = SBOSS_PRIORITY) : CSceneBoss::CSceneBoss(nPrioryity) {  };
	~CSceneBoss01() {};

	void Set(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);

private:
	// 関数宣言 //***********************************************************************
	void Attack_Start(void);
	void Attack_Half(void);
	void Attack_0(void);
	void Attack_1(void);
	void Attack_2(void);
	void Attack_3(void);
	// 変数宣言 //***********************************************************************

	ATTACK  m_Attack;		//現在の攻撃パターン
	D3DXVECTOR3	m_JumpMove;		//距離保存
	int		m_nReplay;		//回数保存
	int		m_nStart;		//登場済みかどうか
	bool	m_bHalf;		//半分切ったかどうか
	D3DXVECTOR3 m_Target;	//発動までの保存用
};
#endif
