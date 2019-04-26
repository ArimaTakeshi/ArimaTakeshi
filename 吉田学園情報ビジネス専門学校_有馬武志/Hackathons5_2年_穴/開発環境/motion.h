//=============================================================================
//
// モーション処理 [motion.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "scene.h"
#include "3DGage.h"
#include "SceneAnim3D.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CHAR_PRIORITY	(0)
#define MAX_HITCHAR		(16)
#define MAX_WAIT_MOTION	(15)

class CCharacter;
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CKey
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,	//通常キー
		TYPE_ATTACK,		//攻撃キー
		TYPE_MAX
	}TYPE;
	CKey() { m_pRot = NULL; m_pEffect = NULL; };
	~CKey() {};
	void Uninit(void);

	float		&GetfSlip(void)		{ return m_fSlip; }
	float		&GetfMove(void)		{ return m_fMove; }
	int			&GetnMoveType(void) { return m_nMoveType; }
	D3DXVECTOR3 &GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 *&GetpRot(void)		{ return m_pRot; }
	D3DXVECTOR3 &GetMove(void)		{ return m_move; }
	int			&GetnFrame(void)	{ return m_nFrame; }
	int			&GetnMaxEffect(void){ return m_nMaxEffect; }
	int			*&GetpEffect(void)	{ return m_pEffect; }
	int			&GetnFloating(void) { return m_nFloating; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	float		m_fSlip;		//慣性
	float		m_fMove;		//移動可能かどうか
	int			m_nMoveType;	//移動方法	0:永続 1:単発
	D3DXVECTOR3 m_pos;			//原点移動値
	D3DXVECTOR3 *m_pRot;		//回転値
	D3DXVECTOR3	m_move;			//移動量
	int			m_nFrame;		//フレーム数
	int			m_nMaxEffect;	//下個数
	int			*m_pEffect;		//SAや無敵等、音も
	int			m_nFloating;	//移動方法	0:通常 1:浮遊 2:地面付かない
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CAtkKey : public CKey
{
public:

	CAtkKey() {};
	~CAtkKey() {};

	typedef enum
	{
		ATK_TYPE_NO = 0,	//怯みのみ
		ATK_TYPE_NORMAL,	//次ヒットで吹っ飛び
		ATK_TYPE_SMASH,		//ヒットで吹っ飛び
		ATK_TYPE_MAX
	}ATK_TYPE;

	int			&GetnAtkType(void)			{ return m_nAtkType; }
	int			&GetnAtkParts(void)			{ return m_nAtkParts; }
	int			&GetnCntAtk(void)			{ return m_nCntAtk; }
	int			&GetnHitFrame(int nCount)	{ return m_nHitFrame[nCount]; }
	float		&GetfRange(void)			{ return m_fRange; }
	float		&GetfAtkplus(void)			{ return m_fAtkplus; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	int			m_nAtkType;		//攻撃タイプ
	int			m_nAtkParts;	//攻撃部位
	int			m_nCntAtk;		//攻撃個数
	int			m_nHitFrame[2];	//攻撃有効F
	float		m_fRange;		//攻撃範囲
	float		m_fAtkplus;		//ダメージ倍率
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class COneMotion
{
public:

	COneMotion() { m_type = NULL; m_Key = NULL; };
	~COneMotion() {};
	void Uninit(void);

	int			&GetnNorBranch(void)			{ return m_nNorBranch; }
	int			&GetnLandBranch(void)			{ return m_nLandBranch; }
	int			&GetnStartCancel(int nNumber)	{ return m_nStartCancel[nNumber]; }
	int			&GetnEndCancel(int nNumber)		{ return m_nEndCancel[nNumber]; }
	int			&GetnOtherCancel(int nNumber)	{ return m_nOtherCancel[nNumber]; }
	int			&GetnMaxKey(void)				{ return m_nMaxKey; }
	float		&GetfWaitTime(void)				{ return m_fWaitTime; }
	CKey::TYPE	*&GetType(void)					{ return m_type; }
	CKey		**&GetKey(void)					{ return m_Key; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	float	m_fWaitTime;		//使用時待ち時間
	int		m_nNorBranch;		//通常分岐
	int		m_nLandBranch;		//着地分岐
	int		m_nStartCancel[2];	//初動キャンセル	 開始, 終了
	int		m_nEndCancel[2];	//振り切りキャンセル 開始, 終了
	int		m_nOtherCancel[2];	//その他キャンセル	 開始, 終了

	int			m_nMaxKey;		//キーの最大数
	CKey::TYPE	*m_type;		//キーのタイプ
	CKey		**m_Key;		//キー本体
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMotion
{
public:
	typedef enum
	{
		TYPE_BOX_Sword,	//剣
		TYPE_BOX_Stick,	//棍棒
		TYPE_MAX
	}TYPE;
	CMotion()	{ m_OneMotion = NULL; };
	~CMotion()	{};

	static void Load(void);
	static void UnLoad(void);
	void Uninit(void);

	static CMotion *GetMotion(int nType)	 { return m_pMotion[nType]; };
	COneMotion *&GetOneMotion(void) { return m_OneMotion; };
	int &GetnMaxParts(void)			 { return m_nMaxParts; };
	int &GetnMaxMotion(void)		 { return m_nMaxMotion; };

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static int			m_nNumMotion;			//最大キャラ数
	static CMotion		**m_pMotion;				//モーション本体

	int m_nMaxParts;	//構成しているパーツ数
	int m_nMaxMotion;	//構成しているモーション数
	COneMotion *m_OneMotion;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CVtxInfo
{
public:
	CVtxInfo() { m_nBone = NULL; m_fWeight = NULL; m_pos = NULL; };
	~CVtxInfo() {};
	int			&GetnMaxBone(void) { return m_nMaxBone; };
	int			*&GetnBone(void) { return m_nBone; };
	float		*&GetfWeight(void) { return m_fWeight; };
	D3DXVECTOR3 *&Getpos(void) { return m_pos; };

private://*****************************************************************************
		//変数宣言//***********************************************************************
	int			m_nMaxBone;		//ボーンの数
	int			*m_nBone;		//ボーン
	float		*m_fWeight;		//ウエイト
	D3DXVECTOR3 *m_pos;			//位置
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBone
{
public:
	CBone() { m_pMtx = NULL; };
	~CBone() {};

	D3DXMATRIX	*&GetPairMtx(void) { return m_pMtx; }
	D3DXMATRIX	&GetMtx(void) { return m_Mtx; }
	D3DXVECTOR3 &GetaddRot(void) { return m_addRot; }
	D3DXVECTOR3 &GetaddRotMove(void) { return m_addRotMove; }
	D3DXVECTOR3 &GetaddPos(void) { return m_addPos; }
	D3DXVECTOR3 &GetaddPosMove(void) { return m_addPosMove; }

private://*****************************************************************************
		//変数宣言//***********************************************************************
	D3DXMATRIX		*m_pMtx;		//親のワールドマトリックス
	D3DXMATRIX		m_Mtx;			//ワールドマトリックス
	D3DXVECTOR3		m_addRot;					//加算の向き モーション
	D3DXVECTOR3		m_addRotMove;				//モーションの移動
	D3DXVECTOR3		m_addPos;					//加算の向き モーション
	D3DXVECTOR3		m_addPosMove;				//モーションの移動
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCharParts
{
public:
	typedef enum
	{
		BRIG_hip,		//ボックスリグ	尻
		BRIG_hara,		//ボックスリグ	腹
		BRIG_mune,		//ボックスリグ	胸
		BRIG_head,		//ボックスリグ	頭
		BRIG_armUR,		//ボックスリグ	右上腕
		BRIG_armUL,		//ボックスリグ	左上腕
		BRIG_armD,		//ボックスリグ	下腕
		BRIG_hand,		//ボックスリグ	手
		BRIG_handR2,	//ボックスリグ	右甲
		BRIG_handR3,	//ボックスリグ	右指
		BRIG_handL2,	//ボックスリグ	左甲
		BRIG_handL3,	//ボックスリグ	左指
		BRIG_legUR,		//ボックスリグ	右腿
		BRIG_legUL,		//ボックスリグ	左腿
		BRIG_legD,		//ボックスリグ	脛
		BRIG_foot,		//ボックスリグ	足
		TEST_000,		//TEST
		BOX_100,		//箱型スキンメッシュ用モデル
		Face_000,		//箱型スキンメッシュ用モデル
		Cloak_000,		//マント
		BRIG_Sword0,	//剣
		BRIG_Stick,		//棍
		PARTS_MAX
	}PARTS;
	CCharParts(void) { m_pBone = NULL; m_pChar = NULL; m_pDrawMtx = NULL; m_pMeshModel = NULL; m_pModel = NULL; };
	~CCharParts() {};

	static CVtxInfo *&GetVtxInfo(int nID) {return m_pVtxInfo[nID]; }
	static void SetTEST_000(CCharacter *pChar);
	static void SetBox_100(CCharacter *pChar);
	static void SetBox_Sword(CCharacter *pChar);
	static void SetBox_Stick(CCharacter *pChar);

	void LoadChar(int nNumber, char *aStr);
	static void LoadVtx(int nNumber, char *aStr);

	void Draw(CCharacter *pChar);
	void DrawModel(CCharacter *pChar, int &nCount, bool bTex);
	void Uninit(void);

	virtual void SetVtx(int &nCount);	//後々バッファのやつも引数に
	void Set(int nNumber, D3DXMATRIX *pDraw, PARTS model);
	void SetBone(int nNumber, D3DXMATRIX *pPair, D3DXVECTOR3 pos);

	CCharacter		*&GetpChar(void) { return m_pChar; }
	D3DXMATRIX		&GetmtxWorld(int nNumber)	{ return m_pBone[nNumber].GetMtx(); }
	CMotion::TYPE	&GetMotion(void)			{ return m_Motion; };
	CBone			*&GetBone(void)				{ return m_pBone; };
	PARTS			*&GetModel(void)			{ return m_pModel; };
	LPD3DXMESH		*&GetpMeshModel(void) { return m_pMeshModel; };
	D3DXMATRIX		**&GetDrawMtx(void)			{ return m_pDrawMtx; };
	int				&GetnMaxBone(void) { return m_nMaxBone; };
	int				&GetnMaxModel(void) { return m_nMaxModel; };
	void			NewBone(int nMax);
	void			NewModel(int nMax);

private://*****************************************************************************
	static CVtxInfo *m_pVtxInfo[PARTS_MAX];
		//変数宣言//***********************************************************************
	CCharacter		*m_pChar;		//キャラのポインタ
	CMotion::TYPE	m_Motion;		//モーションの種類
	CBone			*m_pBone;		//ボーン
	PARTS			*m_pModel;		//モデル
	LPD3DXMESH		*m_pMeshModel;	//メッシュ情報へのポインタ
	D3DXMATRIX		**m_pDrawMtx;	//描画時に使うボーン
	int				m_nMaxBone;		//ボーンの最大数
	int				m_nMaxModel;	//モデルの最大
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCharacter	:	public CScene
{
public:
	typedef struct
	{//種類ごとのモデル情報保存
		LPD3DXMESH		MeshModel = NULL;		//メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffMatModel = NULL;	//マテリアル情報へのポインタ
		DWORD			nNumMatModel = NULL;	//マテリアルの情報数
		D3DXVECTOR3		*pPos;					//位置の頂点情報
		CScene::TEXTURE	tex;					//画像
		char			aText[32];				//モデル読み込みが遅いため必要になるまでテキストで管理
	}MODEL_PARTS;
	//*****************************************************************************
	typedef enum
	{
		MOTION_NEUTRAL,		//ニュートラル
		MOTION_WALK,		//歩き
		MOTION_JUMP,		//ジャンプ
		MOTION_LAND,		//着地
		MOTION_S_NEUTRAL,	//空中ニュートラル
		MOTION_BOOST,		//地上ブースト
		MOTION_BOOST_END,		//ブースト終了
		MOTION_STEP,		//ステップ
		MOTION_GUARD,		//ガード
		MOTION_PARIS,		//パリィ
		MOTION_GUARD2,		//ガード成功時
		MOTION_PARIS2,		//パリィ被弾時
		MOTION_DESPONDENCY,	//怯み
		MOTION_BLOW,		//吹っ飛び
		MOTION_DOWN,		//ダウン
		MOTION_RETURN,		//復帰
		MOTION_APPEAL,		//アピール
		MOTION_ATTACK,		//攻撃モーション
	}MOTION;
	typedef enum
	{
		DIRECT_NO,		//指示なし
		DIRECT_ATTACK,		//弱攻撃
		DIRECT_ATTACK2,		//強攻撃
		DIRECT_SKILL1,		//スキル攻撃
		DIRECT_SKILL2,		//スキル攻撃
		DIRECT_JUMP,		//ジャンプ
		DIRECT_BOOST,		//ブースト
		DIRECT_GUARD,		//ガード
		DIRECT_PARIS,		//パリィ
	}DIRECT;
	typedef enum
	{
		LOCK_AIR,	//初期をロック
		LOCK_NO,	//初期をロック
		LOCK_FIRST,	//初期をロック
		LOCK_RIGHT,	//右側をロック
		LOCK_LEFT,	//左側をロック
		LOCK_NEAR,	//近いものをロック
		LOCK_MAX,
	}LOCK;
	typedef enum
	{
		STATE_NONE,		//通常
		STATE_AVOID,	//回避
		STATE_PARIS,	//受け流し
		STATE_GUARD,	//防御
		STATE_ARMOR,	//スーパーアーマー
		STATE_CANCEL,	//判定後のキャンセル指定
		STATE_MAX,
	}STATE;
	typedef enum
	{
		TEAM_PLAYER,	//プレイヤー
		TEAM_ENEMY,		//エネミー
		TEAM_IGNORED,	//無視
		TEAM_MAX,
	}TEAM;

	CCharacter(int nPrioryity = CHAR_PRIORITY) : CScene::CScene(nPrioryity) { m_pTex = NULL; m_pParts = NULL; m_pGage = NULL; };
	~CCharacter() {};
	//*****************************************************************************
	static LPD3DXMESH Load(CCharParts::PARTS parts);
	static void Load(void);
	static void UnLoad(void);
	static void AtkCollision(void);								//攻撃チェック 全体から
	static void HitCheck(CScene *&pAtkChar, CScene *&pDefChar);	//攻撃チェック 単体から
	static void HitMotionAll(void);								//ヒット後モーション更新
	//*****************************************************************************
	HRESULT Init(void);
	void Uninit(void);
	void Update(bool bMove);						//モーションの更新
	void DirectMotion(DIRECT Direct);				//モーションへの指示
	void AtkRot(float &fRot, int &nID);						//攻撃時の角度補正
	void Draw(void);
	virtual void Dead(void);
	virtual void Over(void);
	virtual void SetLightCol(D3DXCOLOR col) {};
	virtual void SetLightStr(float fGoal, float fFrame) {};

	//*****************************************************************************
	void AtkVoice(void);
	void DefVoice(void);
	void DeadVoice(void);
	void SetNextMotion(int nNumber);				//次のモーションへの予約
	void ResetMotion(void);							//モーションをニュートラルにリセット
	void SetRotMotion(void);						//現在のキーに角度を完全に合わせる
	void SetPlusFrame(float fPFrame, float fCount);	//フレームの進行速度設定
	void CollisionAll(CScene *pChar);	//キャラ同士のあたり判定
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);			//設定処理
	CScene *LockChar(LOCK lock);			//キャラをロック
	void LockCancel(void);					//キャラロックを解除
	void SetStatus(void);					//現在のレベルでステータス計算
	//*****************************************************************************
	TEAM		&GetTeam(void)				{ return m_Team; }
	int			&GetnMaxParts(void)			{ return m_nMaxParts; }

	CScene::DRAW_TYPE  &GetDrawType(void) { return m_DrawType; }
	D3DXMATRIX  &GetMtx(void)				{ return m_Mtx; }
	D3DXVECTOR3 &Getpos(void)				{ return m_pos; }
	D3DXVECTOR3 &Getposold(void)			{ return m_posold; }
	D3DXVECTOR3 &Getrot(void)				{ return m_rot; }
	D3DXVECTOR3 &Getaddpos(void)			{ return m_addpos; }
	D3DXVECTOR3 &GetaddPosmove(void)		{ return m_addPosmove; }
	D3DXVECTOR3 &Getmove(void)				{ return m_move; }
	D3DXVECTOR3 &Getlength(void)			{ return m_length; }
	D3DXCOLOR	&GetCollar(void)			{ return m_col; }
	float		&GetfRot(void)				{ return m_fRot; }
	float		&GetfSumFrame(void)			{ return m_fSumFrame; }
	int			&GetnNumMotion(int nNumber) { return m_nNumMotion[nNumber]; }
	bool		&GetbJump(void)				{ return m_bJump; }
	bool		&GetbOrbit(void)			{ return m_bOrbit; }
	CCharParts	**&GetpParts(void)			{ return m_pParts; }
	CMotion::TYPE	&GetType(void)			{ return m_pParts[0]->GetMotion(); }
	CScene		*&GetpLockChar(void)		{ return m_pLockChar; }

	int			&GetnLevel(void)			{ return m_nLevel; }
	float		&GetfMaxLife(void)			{ return m_fMaxLife; }
	float		&GetfLife(void)				{ return m_fLife; }
	float		&GetfMaxSP(void)			{ return m_fMaxSP; }
	float		&GetfSP(void)				{ return m_fSP; }
	float		&GetfAtk(void)				{ return m_fAtk; }
	float		&GetfMaxStamina(void)		{ return m_fMaxStamina; }
	float		&GetfStamina(void)			{ return m_fStamina; }
	bool		&GetbVtx(void) {			return m_bVtx; }
	bool		&GetbBoost(void)			{ return m_bBoost; }
	bool		*&GetpUseMotion(void)		{ return m_pUseMotion; }
	float		*&GetpWaitMotion(void)		{ return m_pWaitMotion; }
	int			&GetnInvincible(void)		{ return m_nInvincible; }

	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	void		DrawGage(void) { if (m_pGage != NULL) { m_pGage->Draw(); } };

	virtual void CancelLock(void);													//死亡時、自身へのロックを外す
	static MODEL_PARTS *&GetpartsAll(int nNumber) { return m_partsAll[nNumber]; }	//全パーツのポインタを返す
	static bool CheckSP(CMotion::TYPE type, int nNumber, float &fValue);			//スタミナの使用
	static float GetEffect_SP(int nNumber);											//キー事に呼ぶ効果
private://*****************************************************************************
	void HitMotion(void);				//ヒット後モーション更新 単体ごと
	void CancelUpdate(void);			//モーションのキャンセル更新
	void SetCancelMotion(int nNumber);	//モーションのキャンセル設定
	void SetAtkNumber(int nNumber);		//モーションの番号の保存
	void ResetUpdate(void);				//モーションの番号のリセット更新
	void ResetAtkNumber(void);			//モーションの番号のリセット
	bool CheckAtkNumber(int nNumber);	//モーションの番号の確認
	void Collision(CScene *pChar);		//キャラ同士のあたり判定
	void SetEffect(CKey *&pKey);		//キー事に呼ぶ効果
	float AngleCheck(float fAngle0, float fAngle1);	//2つの角度の差を返す
	void UseStamina(float fValue);		//スタミナの使用
	bool UseSP(int nNumber);			//スタミナの使用

	void ReSetHitChar(void);			//キャラヒット情報をリセット
	bool CheckHitChar(CScene *&pChar);	//キャラヒット情報を保存
		//変数宣言//***********************************************************************
	static MODEL_PARTS	*m_partsAll[CCharParts::PARTS_MAX];	//全パーツ情報

	TEAM			m_Team;				//所属するチーム(攻撃判定用)
	STATE			m_state;			//状態
	LPDIRECT3DTEXTURE9	m_pTex;			//画像
	CScene::DRAW_TYPE	m_DrawType;		// 描画する方法(加算合成など)

	int				m_nMaxParts;		//パーツ数
	CCharParts		**m_pParts;			//自分のパーツ情報
	D3DXMATRIX		m_Mtx;			//ワールドマトリックス

	D3DXCOLOR		m_col;				//自身の色
	D3DXVECTOR3		m_pos;				//プレイヤーの原点
	D3DXVECTOR3		m_posold;			//前回のモデルの位置
	D3DXVECTOR3		m_rot;				//プレイヤーの向き
	D3DXVECTOR3		m_move;				//モデルの位置
	D3DXVECTOR3		m_addpos;			//加算の位置 モーション
	D3DXVECTOR3		m_addPosmove;		//モーションの移動
	D3DXVECTOR3		m_length;			//ポリゴンの長さ
	D3DXVECTOR3		m_FNor;				//地面の法線
	float			m_fRot;				//移動方向
	float			m_fARot;			//モーション登録時の入力向き
	int				m_nInvincible;		//無敵時間
	int				m_nCntReUse;		//次使用の使用モーションのリセットまでのF
	float			*m_pWaitMotion;		//待ち時間のあるモーションを管理
	bool			*m_pUseMotion;		//使用した攻撃モーション記録

	int				m_nNumMotion[4];	//0:現在のモーション 1:次のモーション 2:キー番号 3:前のモーション
	float			m_fFrame;			//現在のフレーム数
	float			m_fFramePlus;		//フレームへのプラス値
	float			m_fFramePlus2;		//フレームへの自由値
	float			m_fInitFrame;		//フレームの速度が初期化されるまでの値
	float			m_fSumFrame;		//進行する合計フレーム数
	float			m_fMotionFrame;		//MOTION全体のフレーム数をカウント
	float			m_fKeepFrame;		//MOTIONを継続するF数
	int				m_nCancelFrame;		//キャンセル待ちの保持フレーム数
	int				m_nLeg;				//右足を出しているか左足を出しているか
	int				m_nCntDamage;		//ダメージ後からの時間カウント
	int				m_nCntHit;			//ヒット数
	CScene			*m_pHit[MAX_HITCHAR];//殴った敵
	bool			m_bJump;			//ジャンプの有無

	bool			m_bVtx;				//頂点情報設定の有無
	bool			m_bBoost;			//ブーストの有無
	bool			m_bOrbit;			//オービットの破棄用
	CScene			*m_pLockChar;		//lockしているキャラ
	CSound::LABEL	m_Voice;		//ボイス情報

	int				m_nLevel;			//レベル
	float			m_fMaxLife;			//ヒットポイントの最大値
	float			m_fLife;			//ヒットポイント
	float			m_fMaxSP;			//スペシャルポインタの最大値
	float			m_fSP;				//スペシャルポイント
	float			m_fAtk;				//攻撃力
	float			m_fCntStamina;		//スタミナ回復までをカウント
	float			m_fMaxStamina;		//スタミナの最大値
	float			m_fStamina;			//スタミナ

	C3DGage			*m_pGage;			//頭上HPの表示
};
#endif
