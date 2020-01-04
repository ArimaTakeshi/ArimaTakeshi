//=============================================================================
//
// プレイヤー処理 [dummyplayer.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _DUMMYPLAYER_H_
#define _DUMMYPLAYER_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME_DUMMYPRISONER		"data\\TEXT\\Prisoner1.txt"	//読み込むtxtファイルの名前
#define MAX_DUMMYPLAYERANIM			(8)							//アニメーション数
#define MAX_DUMMYPLAYERKEY			(8)							//キーフレーム数
#define MAX_DUMMYPARTS				(30)						//パーツの最大数
#define MAX_DUMMYMOTION				(10)						//モーションの最大数

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//=====================
//  CSceneの派生クラス
//=====================
class CDummyPlayer : public CScene
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
		KEY aKey[MAX_DUMMYPARTS];
	}KEY_INFO;

	//モーション情報
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKayInfo[MAX_DUMMYMOTION];
	}MOTION_INFO;

	//モーション種類
	typedef enum
	{
		DUMMYPLAYERANIM_NEUTRAL = 0,	//ニュートラルモーション
		DUMMYPLAYERANIM_WALK,			//歩く
		DUMMYPLAYERANIM_RUN,			//走る
		DUMMYPLAYERANIM_SIT,			//座る
		DUMMYPLAYERANIM_TIRED,			//疲れる
		DUMMYPLAYERANIM_SQUAT,			//しゃがむ
		DUMMYPLAYERANIM_SNEAK,			//しゃがみ歩き
		DUMMYPLAYERANIM_DIE,			//倒れる
		DUMMYPLALYER_MAX				//モーションの最大数
	}DummyPlayerAnim;

	CDummyPlayer(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_PLAYER);
	~CDummyPlayer();
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
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CDummyPlayer *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nAnimnow);
	DummyPlayerAnim GetAnim(void) { return m_nAnimnow; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

	//モーションの更新関数
	void UpdateMotion(void);

	//ファイル読み込み関数
	void FileLoad(void);								//ファイル読み込み
	char *ReadLine(FILE *pFile, char *pDst);			//1行読み込み
	char *GetLineTop(char *pStr);						//行の先頭を取得
	int  PopString(char *pStr, char *pDest);			//行の最後を切り捨て

private://個人でのみ使う
	static LPD3DXMESH	m_pMesh[MAX_DUMMYPARTS];		//メッシュ情報へのポインタ
	static LPD3DXBUFFER	m_pBuffMat[MAX_DUMMYPARTS];		//マテリアルの情報へのポインタ
	static DWORD		m_nNumMat[MAX_DUMMYPARTS];		//マテリアルの情報数
	static D3DXVECTOR3	m_pos;							//位置
	static D3DXVECTOR3	m_move;							//動き
	static D3DXVECTOR3	m_rot;							//向き
	D3DXVECTOR3			m_rotDest;						//過去の向き
	D3DXVECTOR3			m_posOld;						//過去の位置
	D3DXVECTOR3			m_posFuture;					//未来の位置
	D3DXVECTOR3			m_rotFuture;					//未来の向き
	D3DXMATRIX			m_mtxWorld;						//ワールドマトリックス
	CModel				*m_apModel[MAX_DUMMYPARTS];		//モデルへのポインタ
	DummyPlayerAnim		m_nAnimnow;						//現在のアニメーション
	D3DXVECTOR3			m_vtxMin;						//モデルの最小値
	D3DXVECTOR3			m_vtxMax;						//モデルの最大値
	bool				m_bJump;						//ジャンプ状態
	bool				m_bLand;						//着地状態

	// モーション関数	新規
	KEY_INFO			*m_pKeyInfo[MAX_DUMMYMOTION];	//キー情報へのポインタ
	int					m_nKey;							//現在のキーナンバー
	int					m_nCountFlame;					//フレーム数
	int					m_nNumParts;					//パーツ数
	int					m_aIndexParent[MAX_DUMMYPARTS];	//親のインデックス
	KEY					m_aKayOffset[MAX_DUMMYPARTS];	//オフセット情報
	MOTION_INFO			m_aMotionInfo[MAX_DUMMYMOTION];	//モーション情報
	int					m_nMotionType;					//モーションのタイプ(int型)
	bool				m_bMotionEnd;					//モーション終了
	D3DXVECTOR3			m_OffSetPos[MAX_DUMMYPARTS];	//パーツごとの最初の位置

	static CMeshOrbit   *m_MeshOrbit;					//軌跡のポインタ
	bool				m_bGaugeOnOff;					//ゲージのオンオフの状態
};
#endif