//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"
#include "billboord.h"
#include "shadow.h"
#include "dummyenemy.h"
#include "blood.h"
#include "spotlight.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\stok2.txt"	//読み込むtxtファイルの名前
#define MAX_ENEMYANIM			(8)						//アニメーション数
#define MAX_ENEMYKEY			(8)						//キーフレーム数
#define MAX_PARTS				(30)					//パーツの最大数
#define MAX_MOTION				(10)					//モーションの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//=====================
//  CSceneの派生クラス
//=====================
class CEnemy : public CScene
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
		ENEMYANIM_NEUTRAL = 0,		//ニュートラルモーション
		ENEMYANIM_MOVE,				//移動モーション
		ENEMYANIM_JUMP,				//ジャンプモーション
		ENEMYANIM_ATTACK,			//近距離攻撃モーション
		ENEMYANIM_HOLDAGAN,			//銃を構えるモーション
		ENEMYANIM_SHOT,				//銃を撃つモーション
		ENEMYANIM_HOLDAGANWALK,		//構えて歩くモーション
		ENEMYANIM_TAKEGAN,			//銃をしまうモーション
		ENEMYANIM_LOOKAROUND,		//周りを見渡すモーション
		ENEMY_MAX					//モーションの最大数
	}PlayerAnim;

	typedef enum
	{
		MOVE_NONE = 0,				//何もない状態
		MOVE_STOP,					//止まっている状態
		MOVE_X_R,					//横に動いている状態(最初に→)
		MOVE_Z_G,					//縦に動いている状態(最初に↑)
		MOVE_X_L,					//縦に動いている状態(最初に←)
		MOVE_Z_B,					//縦に動いている状態(最初に↓)
		MOVE_RAND,					//ランダムに動いている状態
		MOVE_MAX,					//動きの最大
	}MoveList;

	CEnemy(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void CollisitionMesh(void);
	void CollisitionWall(void);
	void CollisitionGround(void);
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CEnemy *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nPattern, MoveList movelist);
	void CollisitionItem(void);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }
	void DeleteEnemy(void);
	void SetPattern(int nPattern) { m_nPattern = nPattern; }
	void SetLightIn(bool bLightIn) { m_bLightIn = bLightIn; }

	//モーションの更新関数
	void UpdateMotion(void);

	//ファイル読み込み関数
	void FileLoad(void);							//ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);		//1行読み込み
	char *GetLineTop(char *pStr);					//行の先頭を取得
	int  PopString(char *pStr, char *pDest);		//行の最後を切り捨て

private://個人でのみ使う
	static LPD3DXMESH	m_pMesh[MAX_PARTS];			//メッシュ情報へのポインタ
	static LPD3DXBUFFER	m_pBuffMat[MAX_PARTS];		//マテリアルの情報へのポインタ
	static DWORD		m_nNumMat[MAX_PARTS];		//マテリアルの情報数
	D3DXVECTOR3			m_pos;						//位置
	D3DXVECTOR3			m_rot;						//向き
	D3DXVECTOR3			m_posPast;					//過去の位置
	D3DXVECTOR3			m_rotPast;					//過去の向き
	D3DXVECTOR3			m_rotDest;					//向き
	D3DXVECTOR3			m_posOld;					//過去の位置
	D3DXVECTOR3			m_move;						//動き
	D3DXMATRIX			m_mtxWorld;					//ワールドマトリックス
	CModel				*m_apModel[MAX_PARTS];		//モデルへのポインタ
	PlayerAnim			m_nAnimnow;					//現在のアニメーション
	MoveList			m_MoveList;					//移動方法
	D3DXVECTOR3			m_vtxMin;					//モデルの最小値
	D3DXVECTOR3			m_vtxMax;					//モデルの最大値
	bool				m_bJump;					//ジャンプ状態
	bool				m_bLand;					//着地状態
	bool				m_bInvincible;				//デバッグ用
	bool				m_bAttack;					//攻撃状態
	int					m_nAttackDelay;				//攻撃の硬直時間
	int					m_nAttackCount;				//攻撃までの時間
	bool				m_bResult;
	bool				m_bInLength;				//発見した後の距離
	bool				m_bDiscovery;				//発見した状態
	int					m_nCntLook;					//見渡す時間
	int					m_nCntTime;					//見つけた後の状態を出す時間
	bool				m_bReturn;					//戻すときに1回だけはいるための
	bool				m_bTarget;					//追いかけた後にニュートラルにならないように
	int					m_nWaitTime;				//追いかけるまでの待機時間
	PlayerAnim			m_nAnimnowPast;				//過去のアニメーション
	MoveList			m_MoveListPast;				//過去の移動方法
	bool				m_bInLengthPast;			//過去の索敵
	bool				m_bTitle;					//タイトルでの制御
	int					m_nCntLookPast;				//過去に見た状態
	bool				m_bAttackPast;				//過去の攻撃状態
	int					m_nCntTimePast;				//未来の状態時間の表示
	bool				m_bReturnPast;				//過去に戻る
	int					m_nPatternPast;				//過去の行動パターン
	int					m_nPattern;					//行動パターン
	bool				m_bLightIn;					//ライトに入った判定
	bool				m_bLightInPast;				//過去にライトに入った判定
	int					m_nCountMoveXPast;			//過去のX方向に移動中
	int					m_nCountMoveZPast;			//過去のZ方向に移動中
	bool				m_bMoveTypePast;			//過去の移動の方法
	int					m_nCountMoveX;				//X方向に移動中
	int					m_nCountMoveZ;				//Z方向に移動中
	bool				m_bMoveType;				//移動の方法
	bool				m_bStartMotion;				//最初のモーション

	//モーション関数
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];	//キー情報へのポインタ
	int					m_nKey;						//現在のキーナンバー
	int					m_nCountFlame;				//フレーム数
	int					m_nNumParts;				//パーツ数
	int					m_aIndexParent[MAX_PARTS];	//親のインデックス
	KEY					m_aKayOffset[MAX_PARTS];	//オフセット情報
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];	//モーション情報
	int					m_nMotionType;				//モーションのタイプ(int型)
	bool				m_bMotionEnd;				//モーション終了
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];		//パーツごとの初期位置
	static CMeshOrbit   *m_MeshOrbit;				//軌跡のポインタ
	CBillBoord			*m_pBillboord;				//ビルボードのポインタ
	CShadow				*m_pShadow;					//影のポインタ
	CSpotLight			*m_pSpotLight;				//スポットライトのポインタ
	CDummyEnemy			*m_pDummyEnemy;				//目印の敵ポインタ
};
#endif