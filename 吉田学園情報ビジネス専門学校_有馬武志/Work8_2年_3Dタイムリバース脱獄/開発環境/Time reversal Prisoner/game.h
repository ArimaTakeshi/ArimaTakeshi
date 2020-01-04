//=============================================================================
//
// ゲームの処理 [game.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MAP_NUM		(1000)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CBullet;
class CNumber;
class CPause;
class CHelp;
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;
class CItem;
class CShadow;
class CEnemy;
class CLogo;
class CDummyEnemy;
class CDummyPlayer;
class CBlood;
class CSpotLight;
class CObjectShadow;

//=====================
// 基本クラス
//=====================
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,					//何もしていない状態
		GAMESTATE_NORMAL,					//通常状態
		GAMESTATE_CLEAR,					//ゲームクリア
		GAMESTATE_OVER,						//ゲームオーバー
		GAMESTATE_END,						//ゲーム終了
		GAMESTATE_MAX						//最大数
	}GAMESTATE;

	typedef enum
	{//各ステージ
		STAGE_NONE = 0,						//何もしてない状態
		STAGENUM_1,							//ステージ1
		STAGENUM_2,							//ステージ2
		STAGENUM_3,							//ステージ3
		STAGENUM_4,							//ステージ4
		STAGENUM_5,							//ステージ5
		STAGENUM_6,							//ステージ6
		STAGENUM_7,							//ステージ7
	}STAGENUM;

	CGame();								//コンストラクタ
	~CGame();								//デストラクタ
	HRESULT Init();							//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理
	static void SetGameState(GAMESTATE state) { m_gameState = state; }
	static void SetPause(bool bPause);
	static void SetHelp(bool bHelp);
	static bool GetPause(void) { return m_bPause; }
	static bool GetHelp(void) { return m_bHelp; }
	static GAMESTATE GetGameState(void) { return m_gameState; }
	static CPlayer *&GetPlayer(void) { return m_pPlayer; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CModel *GetModel(void) { return m_pModel; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CObject *Get3DObject(void) { return m_pObject; }
	static CBillBoord *GetBillboord(void) { return m_pBillBoord; }
	static CEffect *GetEffect(void) { return m_pEffect; }
	static CGround *GetGround(void) { return m_pGround; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CDummyPlayer *&GetDummyPlayer(void) { return m_pDummyPlayer; }
	static CDummyEnemy *GetDummyEnemy(void) { return m_pDummyEnemy; }

	//ステージ
	static STAGENUM GetNumState(void) { return m_StageState; }
	void SetNumState(STAGENUM stagenum);
	void SetStageState(STAGENUM stage);
	void SetStage(void);

	//ファイルを読み込む
	void TextLoad(int nLoadNumber);
	void MeshTextLoad(int nLoadNumber);
	void WallTextLoad(int nLoadNumber);
	char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	char *GetLineTop(char *pStr);				//行の先頭を取得
	int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

private:
	//テキストの値を管理する場所
	typedef struct
	{
		int					m_nType;			// 種類
		int					m_nTexType;			// テクスチャの種類
		int					m_nCollision;		// 当たり判定のONOFF
		D3DXVECTOR3			m_pos;				// 位置
		D3DXVECTOR3			m_rot;				// 回転
	}Map;

	//テキストの値を管理する場所
	typedef struct
	{
		int					m_nTexType;						// テクスチャの種類
		int					m_nWidthDivide;					// 横の分割数を入れる
		int					m_nDepthDivide;					// 奥の分割数を入れる
		float				m_fWidthLength;					// 横の長さ
		float				m_fDepthLength;					// 奥の長さ
		float				m_fVtxHeight_No0;				// 頂点番号0を操作
		float				m_fVtxHeight_No1;				// 頂点番号1を操作
		float				m_fVtxHeight_No2;				// 頂点番号2を操作
		float				m_fVtxHeight_No3;				// 頂点番号3を操作
		D3DXVECTOR3			m_pos;							// 位置
	}Mesh;

	//テキストの値を管理する場所
	typedef struct
	{
		D3DXVECTOR3			m_pos;				// 位置
		D3DXVECTOR3			m_rot;				// 回転
		float				m_fWidthDivide;		// 横幅
		float				m_fHightDivide;		// 縦幅
		int					m_nTexType;			// テクスチャの種類
	}Wall;

	static GAMESTATE m_gameState;			//ゲーム状態
	GAMESTATE m_NowGameState;				//現在のゲーム状況
	int m_nCounterGameState;				//状態カウンタ
	static CBullet *m_pBullet;				//弾のポインタ
	static CPlayer *m_pPlayer;				//プレイヤーのポインタ
	static CNumber *m_pNumber;				//数字のポインタ
	static CPause *m_pPause;				//ポーズのポインタ
	static CHelp *m_pHelp;					//ヘルプのポインタ
	static CPolygon3D *m_pPolygon3D;		//３Dポリゴンのポインタ
	static CModel *m_pModel;				//モデルのポインタ
	static CMeshField *m_pMeshField;		//メッシュフィールドのポインタ
	static CObject *m_pObject;				//オブジェクトのポインタ
	static CBillBoord *m_pBillBoord;		//ビルボードのポインタ
	static CEffect *m_pEffect;				//エフェクトのポインタ
	static CWall *m_pWall;					//壁のポインタ
	static CGround *m_pGround;				//地面のポインタ
	static CItem *m_pItem;					//アイテムのポインタ
	static CShadow *m_pShadow;				//影のポインタ
	static CSpotLight *m_pSpotLight;		//スポットライトのポインタ
	static CEnemy *m_pEnemy;				//敵のポインタ
	static CDummyEnemy *m_pDummyEnemy;		//敵のポインタ
	static CDummyPlayer *m_pDummyPlayer;	//プレイヤーのポインタ
	static bool m_bPause;					//現在ポーズかポーズじゃないか
	static bool m_bHelp;					//現在ヘルプかヘルプじゃないか
	static int	m_nCntSetStage;				// ステージセットカウンタ
	static STAGENUM m_StageState;			// ステージ状態
	static STAGENUM m_ConteniueStage;		//コンテニュー時そこのエリアからスタート
	static CObjectShadow *m_pObjectShadow;	//ステンシルシャドウのポインタ
	int m_nSetObjectNum;					//オブジェクトを置いた数
	int m_nSetMeshFieldNum;					//メッシュフィールドを置いた数
	int	m_nSetWallNum;						//壁の置いた数
	int	m_nEnemyCount;						//敵の数
	Map m_Map[MAX_MAP_NUM];					//設置するオブジェクトの構造体
	Mesh m_Mesh[MAX_MAP_NUM];				//設置するメッシュフィールドの構造体
	Wall m_aWall[MAX_MAP_NUM];				//設置する壁の構造体
};
#endif