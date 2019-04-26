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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\player.txt"	//読み込むtxtファイルの名前
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
		ENEMYANIM_MOVE,				//移動
		ENEMYANIM_JUMP,				//ジャンプ
		ENEMYANIM_ATTACK,			//近距離攻撃
		ENEMYANIM_HOLDAGAN,			//銃を構える
		ENEMYANIM_SHOT,				//銃を撃つ
		ENEMYANIM_BANZAI,			//バンザイ
		ENEMYANIM_BAKUTEN,			//バクテン
		ENEMY_MAX					//モーションの最大数
	}PlayerAnim;

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
	static CEnemy *Create(D3DXVECTOR3 pos);
	void CollisitionItem(void);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

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
	static D3DXVECTOR3	m_pos;						//位置
	static D3DXVECTOR3	m_rot;						//向き
	D3DXVECTOR3			m_posOld;					//過去の位置
	D3DXVECTOR3			m_move;						//動き
	D3DXMATRIX			m_mtxWorld;					//ワールドマトリックス
	CModel				*m_apModel[MAX_PARTS];		//モデルへのポインタ
	PlayerAnim			m_nAnimnow;					//現在のアニメーション
	D3DXVECTOR3			m_vtxMin;					//モデルの最小値
	D3DXVECTOR3			m_vtxMax;					//モデルの最大値
	bool				m_bJump;					//ジャンプ状態
	bool				m_bLand;					//着地状態
	bool				m_bInvincible;				//デバッグ用
	bool				m_bAttack;					//攻撃状態
	int					m_nAttackDelay;				//攻撃の硬直時間
	int					m_nAttackCount;				//攻撃までの時間
	bool				m_bResult;
													//モーション関数
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];	//キー情報へのポインタ
	int					m_nKey;						//現在のキーナンバー
	int					m_nCountFlame;				//フレーム数
	int					m_nNumParts;				//パーツ数
	int					m_aIndexParent[MAX_PARTS];	//親のインデックス
	KEY					m_aKayOffset[MAX_PARTS];	//オフセット情報
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];	//モーション情報
	int					m_nMotionType;				//モーションのタイプ(int型)
	bool				m_bMotionEnd;
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];

	static CMeshOrbit   *m_MeshOrbit;
};
#endif