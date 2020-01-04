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

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CBullet;
class CNumber;
class CPause;
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

	CGame();								//コンストラクタ
	~CGame();								//デストラクタ
	HRESULT Init();							//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理
	void CreateStage(void);					//ステージの生成を一括管理
	void CreateObject(void);				//ステージ上のオブジェクト生成を一括管理
	static void SetGameState(GAMESTATE state) { m_gameState = state; }
	static void SetPause(bool bPause);
	static bool GetPause(void) { return m_bPause; }
	static GAMESTATE GetGameState(void) { return m_gameState; }
	static CPlayer *&GetPlayer(void) { return m_pPlayer; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CModel *GetModel(void) { return m_pModel; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CObject *Get3DObject(void) { return m_pObject; }
	static CBillBoord *GetBillboord(void) { return m_pBillBoord; }
	static CEffect *GetEffect(void) { return m_pEffect; }
	static CGround *GetGround(void) { return m_pGround; }

private:
	static GAMESTATE m_gameState;			//ゲーム状態
	GAMESTATE m_NowGameState;				//現在のゲーム状況
	int m_nCounterGameState;				//状態カウンタ
	static CBullet *m_pBullet;				//弾のポインタ
	static CPlayer *m_pPlayer;				//プレイヤーのポインタ
	static CNumber *m_pNumber;				//数字のポインタ
	static CPause *m_pPause;				//ポーズのポインタ
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
	static bool m_bPause;					//現在ポーズかポーズじゃないか
};
#endif