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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\stok2.txt"			//読み込むtxtファイルの名前
#define MAX_PLAYERANIM			(8)								//アニメーション数
#define MAX_PLAYERKEY			(8)								//キーフレーム数

//新規
#define MAX_PARTS		(30)
#define MAX_MOTION		(10)

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

	typedef enum
	{
		PLAYERANIM_NEUTRAL = 0,		//ニュートラルモーション
		PLAYERANIM_MOVE,			//移動
		PLAYERANIM_JUMP,			//ジャンプ
		PLAYERANIM_ATTACK,			//攻撃
		PLAYERANIM_RESULTUP,		//リザルト上
		PLAYERANIM_RESULTDOWN,		//リザルト下
		PLAYERANIM_BANZAI,			//バンザイ
		PLAYERANIM_BAKUTEN,			//バクテン
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
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void CollisitionMesh(void);
	void CollisitionWall(void);
	void CollisitionGround(void);
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CPlayer *Create(D3DXVECTOR3 pos);
	void CollisitionItem(void);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

	//モーションの更新関数
	void UpdateMotion(void);

	//ファイル読み込み関数
	void FileLoad(void);						//ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	char *GetLineTop(char *pStr);				//行の先頭を取得
	int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て


private://個人でのみ使う
	static LPD3DXMESH	m_pMesh[MAX_PARTS];			//メッシュ情報へのポインタ
	static LPD3DXBUFFER	m_pBuffMat[MAX_PARTS];		//マテリアルの情報へのポインタ
	static DWORD		m_nNumMat[MAX_PARTS];		//マテリアルの情報数
	int					m_nMaxAnimNum;									//アニメーションの最大数
	int					m_nAnimloop[MAX_PLAYERANIM];					//ループ
	int					m_nAnimKey[MAX_PLAYERANIM];						//キー数
	int					m_nAnimfram[MAX_PLAYERANIM][MAX_PLAYERKEY];		//フレーム数
	D3DXVECTOR3			m_posAnim[MAX_PLAYERANIM][MAX_PLAYERKEY];		//アニメーションpos
	D3DXVECTOR3			m_InitPos;										//初期位置
	D3DXVECTOR3			m_InitRot;										//初期向き
	D3DXVECTOR3			m_rotAnim[MAX_PLAYERANIM][MAX_PLAYERKEY];		//アニメーションrot
	D3DXVECTOR3			m_rotModel;										//向き
	D3DXVECTOR3			m_rotDest;										//目的の位置
	int					m_nCntTimePlayer;								//カウンター
	int					m_nCntPlayer;									//プレイヤーのどこか
	int					m_nAnimKeynow;									//現在のキー
	static D3DXVECTOR3	m_pos;								//位置
	static D3DXVECTOR3	m_rot;								//向き
	D3DXVECTOR3			m_posOld;							//過去の位置
	D3DXVECTOR3			m_move;								//動き
	D3DXMATRIX			m_mtxWorld;							//ワールドマトリックス
	CModel				*m_apModel[MAX_PARTS];		//モデルへのポインタ
	PlayerAnim			m_nAnimnow;							//現在のアニメーション
	D3DXVECTOR3			m_vtxMin;							// モデルの最小値
	D3DXVECTOR3			m_vtxMax;							// モデルの最大値
	bool				m_bJump;							// ジャンプ状態
	bool				m_bLand;							// 着地状態
	bool				m_bInvincible;						// デバッグ用
	bool				m_bAttack;							// 攻撃状態
	int					m_nAttackDelay;						// 攻撃の硬直時間
	bool				m_bResult;
															// モーション関数	新規
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];		//キー情報へのポインタ
	int					m_nKey;							//現在のキーナンバー
	int					m_nCountFlame;					//フレーム数
	int					m_nNumParts;					//パーツ数
	int					m_aIndexParent[MAX_PARTS];		//親のインデックス
	KEY					m_aKayOffset[MAX_PARTS];		//オフセット情報
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];		//モーション情報
	int					m_nMotionType;					//モーションのタイプ(int型)
	bool				m_bMotionEnd;
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];

};
#endif