//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"
#include "dummyplayer.h"
#include "blood.h"
#include "serect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME_PRISONER		"data\\TEXT\\Prisoner1.txt"	//読み込むtxtファイルの名前
#define MAX_PLAYERANIM			(8)							//アニメーション数
#define MAX_PLAYERKEY			(8)							//キーフレーム数
#define MAX_PARTS				(30)						//パーツの最大数
#define MAX_MOTION				(10)						//モーションの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//=====================
//  CSceneの派生クラス
//=====================
class CPlayer : public CScene
{
public://誰でも扱える

	//キー要素
	typedef struct
	{
		float fposX;
		float fposY;
		float fposZ;
		float frotX;
		float frotY;
		float frotZ;
	}KEY;

	//キー情報
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//モーション情報
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKayInfo[MAX_MOTION];
	}MOTION_INFO;

	//モーション種類
	typedef enum
	{
		PLAYERANIM_NEUTRAL = 0,		//ニュートラルモーション
		PLAYERANIM_WALK,			//歩く
		PLAYERANIM_RUN,				//走る
		PLAYERANIM_SIT,				//座る
		PLAYERANIM_TIRED,			//疲れる
		PLAYERANIM_SQUAT,			//しゃがむ
		PLAYERANIM_SNEAK,			//しゃがみ歩き
		PLAYERANIM_DIE,				//倒れる
		PLALYER_MAX					//モーションの最大数
	}PlayerAnim;

	CPlayer(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	static void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void CollisitionMesh(void);
	void CollisitionWall(void);
	void CollisitionGround(void);
	void CollisitionSpotLight(void);
	void CollisitionBullet(void);
	void CollisitionItem(void);
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CPlayer *Create(D3DXVECTOR3 pos);
	PlayerAnim GetAnim(void) { return m_nAnimnow; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

	//未来用の関数
	static bool GetFuture(void) { return m_bFuture; }
	static void SetFuture(bool bFuture) { m_bFuture = bFuture; }
	static bool GetFutureCancel(void) { return m_bFutureCancel; }
	static void SetFutureCancel(bool bFutureCancel) { m_bFutureCancel = bFutureCancel; }
	static bool GetCancelHeal(void) { return m_bCancelHeal; }
	static void SetCancelHeal(bool bCancelHeal) { m_bCancelHeal = bCancelHeal; }
	static bool GetActionFade(void) { return m_bActionFade; }
	static void SetActionFade(bool bActionFade) { m_bActionFade = bActionFade; }
	static bool GetCancelStageNext(void) { return m_bStageNext; }
	static void SetCancelStageNext(bool bCancelStageNext) { m_bStageNext = bCancelStageNext; }

	//未来の敵用関数
	static bool GetEnemyFuture(void) { return m_bEnemyFuture; }
	static void SetEnemyFuture(bool bEnemyFuture) { m_bEnemyFuture = bEnemyFuture; }
	static bool GetEnemyFutureSukill(void) { return m_bEnemyFutureSukill; }
	static void SetEnemyFutureSukill(bool bEnemyFutureSukill) { m_bEnemyFutureSukill = bEnemyFutureSukill; }

	//未来の体力用関数
	static bool GetLifeFuture(void) { return m_bLifeFuture; }
	static void SetLifeFuture(bool bLifeFture) { m_bLifeFuture = bLifeFture; }
	static bool GetLifeFutureSukill(void) { return m_bLifeFutureSukill; }
	static void SetLifeFutureSukill(bool bLifeFtureSukill) { m_bLifeFutureSukill = bLifeFtureSukill; }

	//死んだとき
	static bool GetDie(void) { return m_bDie; }
	static void SetDie(bool bDie) { m_bDie = bDie; }
	static bool GetOverResult(void) { return m_bOverResult; }
	static void SetOverResult(bool bOverResult) { m_bOverResult = bOverResult; }

	//プレイヤーの削除
	void ResetPlayer(void);

	//モーションの更新関数
	void UpdateMotion(void);

	//ファイル読み込み関数
	void FileLoad(void);								//ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);			//1行読み込み
	char *GetLineTop(char *pStr);						//行の先頭を取得
	int  PopString(char *pStr, char *pDest);			//行の最後を切り捨て

private://個人でのみ使う
	static LPD3DXMESH	m_pMesh[MAX_PARTS];				//メッシュ情報へのポインタ
	static LPD3DXBUFFER	m_pBuffMat[MAX_PARTS];			//マテリアルの情報へのポインタ
	static DWORD		m_nNumMat[MAX_PARTS];			//マテリアルの情報数
	static D3DXVECTOR3	m_pos;							//位置
	static D3DXVECTOR3	m_move;							//動き
	static D3DXVECTOR3	m_rot;							//向き
	D3DXVECTOR3			m_rotDest;						//過去の向き
	D3DXVECTOR3			m_posOld;						//過去の位置
	D3DXVECTOR3			m_posFuture;					//未来の位置
	D3DXVECTOR3			m_rotFuture;					//未来の向き
	D3DXMATRIX			m_mtxWorld;						//ワールドマトリックス
	CModel				*m_apModel[MAX_PARTS];			//モデルへのポインタ
	PlayerAnim			m_nAnimnow;						//現在のアニメーション
	D3DXVECTOR3			m_vtxMin;						//モデルの最小値
	D3DXVECTOR3			m_vtxMax;						//モデルの最大値
	bool				m_bJump;						//ジャンプ状態
	bool				m_bLand;						//着地状態
	bool				m_bInvincible;					//デバッグ用
	bool				m_bAttack;						//攻撃状態
	int					m_nAttackDelay;					//攻撃の硬直時間
	bool				m_bResult;						//リザルト画面の状態
	float				m_fSpeedMove;					//歩くまたは走る速度
	bool				m_fStageNext;					//マップ移動
	static bool			m_bFuture;						//未来に行ってる状態
	int					m_nFutureStandTime;				//未来から戻った時の動けない時間
	static bool			m_bFutureCancel;				//未来のキャンセル
	static bool			m_bCancelHeal;					//キャンセル後の回復
	int					m_nStandTime;					//未来をキャンセルした際の動けない時間
	static bool			m_bActionFade;					//アクションフェードを起動
	static bool			m_bEnemyFuture;					//敵の未来の開始
	static bool			m_bEnemyFutureSukill;			//敵の未来中にスキルキャンセル
	static bool			m_bLifeFuture;					//未来のHP
	static bool			m_bLifeFutureSukill;			//HPの未来中にスキルキャンセル
	bool				m_bTrapSukill;					//スキル使用時のトラップの状態
	static bool			m_bDie;							//死亡
	static bool			m_bDieSukill;					//死亡スキルによる復活
	static bool			m_bStageNext;					//ステージが入れ替わる際
	bool				m_bSukillActivate;				//スキル発動
	int					m_nDieTimer;					//死んだ後の時間
	int					m_nDieSukillTimer;				//スキル中に死んだ後の時間
	bool				m_bSukillDie;					//スキル中に死んだ後の自動的
	static bool			m_bOverResult;					//死んだ後に出すリザルト
	bool				m_bStageReset;					//ステージがリセットされるとき

	// モーション関数	新規
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];		//キー情報へのポインタ
	int					m_nKey;							//現在のキーナンバー
	int					m_nCountFlame;					//フレーム数
	int					m_nNumParts;					//パーツ数
	int					m_aIndexParent[MAX_PARTS];		//親のインデックス
	KEY					m_aKayOffset[MAX_PARTS];		//オフセット情報
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];		//モーション情報
	int					m_nMotionType;					//モーションのタイプ(int型)
	bool				m_bMotionEnd;					//モーション終了
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];			//パーツごとの最初の位置

	static CMeshOrbit   *m_MeshOrbit;					//軌跡のポインタ
	static CSerect		*m_pSerect;						// セレクトのポインタ
	CDummyPlayer		*m_pDummyPlayer;				//目印のプレイヤー
	CBlood				*m_pBlood;						//血のポインタ
	bool				m_bGaugeOnOff;					//ゲージのオンオフの状態
};
#endif