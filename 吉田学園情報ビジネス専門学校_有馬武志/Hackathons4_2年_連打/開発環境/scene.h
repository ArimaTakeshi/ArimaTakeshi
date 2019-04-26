//=============================================================================
//
// シーン処理 [scene.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define MAX_SCENE		(8)
#define PAUSE_PRIORITY	(MAX_SCENE - 1)				//ポーズの優先順位
#define PAUSE_LENGTH	(75.0f)				//ポーズ上下枠の長さ

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CScene
{
public://*****************************************************************************
	typedef enum
	{
		DRAW_TYPE_NORMAL = 0,		//通常描画
		DRAW_TYPE_ADD,				//加算合成
		DRAW_TYPE_SUBTRACT,			//減算合成
		DRAW_TYPE_MULTIPLY,			//乗算合成
		DRAW_TYPE_OVERLAY,			//黒無視加算無し
		DRAW_TYPE_ZNORMAL = 10,		//Z無視通常
		DRAW_TYPE_ZADD,				//Z無視加算
		DRAW_TYPE_ZSUBTRACT,		//Z無視減算
		DRAW_TYPE_ZMULTIPLY,		//乗算合成
		DRAW_TYPE_ZOVERLAY,			//黒無視加算無し
		DRAW_TYPE_NO,				//描画しない
		DRAW_TYPE_MAX
	}DRAW_TYPE;
	typedef enum
	{//判定したい全クラス お前誰よ？->俺だよ俺ってやつ
		OBJTYPE_NONE,
		OBJTYPE_DUNGEON,
		OBJTYPE_BULLET, OBJTYPE_BULLET2, OBJTYPE_BULLET3,
		OBJTYPE_EFFECT, OBJTYPE_ANIM3D, OBJTYPE_SALE,
		OBJTYPE_BOSS, 
		//モデル//**********************************************
		OBJTYPE_PLAYER, OBJTYPE_ENEMY, OBJTYPE_OBJ,
		//画像//**********************************************
		OBJTYPE_OBJ_NO,	//モデル　判定：(有/無し)
		OBJTYPE_NUMBER,
		OBJTYPE_GOAL, OBJTYPE_SHOP,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef struct
	{//種類ごとのモデル情報保存
		LPD3DXMESH		MeshModel = NULL;		//メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffMatModel = NULL;	//マテリアル情報へのポインタ
		DWORD			nNumMatModel = NULL;	//マテリアルの情報数
												//LPDIRECT3DTEXTURE9	pTexture = NULL;	//テクスチャ
	}MODEL_DRAW;

	CScene::CScene(int nPrioryity = 3);
	~CScene();

	static void CScene::CreateAll(int nPrioryity, int nNumber);
	static void		ReleaseAll(void);
	static void		UpdateAll(void);
	static void		DrawAll(LPDIRECT3DDEVICE9 &pDevice);

	static CScene **GetScene(int nPrioryity);
	static CScene *GetScene(int nPriority, int nID) { return m_PScene[nPriority][nID]; };
	CScene *GetThisScene(void) {return m_PScene[m_nPriority][m_nID]; };
	//*****************************************************************************
	virtual HRESULT Init(void)					 { return S_OK; };
	virtual void	Uninit(void)				 { Release(); };
	virtual void	Draw(void)					 {};
	virtual void	Update(void)				 {};
	static int		GetnNumAll(int nPriority)	 { return m_nNumAll[nPriority]; }
	static int		GetnMemoryAll(int nPriority) { return m_nMemoryAll[nPriority]; }
	static int		&GetnCntStart(void)			 { return m_nCntStart; }
	static bool		&GetbPause(void)			 { return m_bPause; }
	static bool		DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//描画準備処理

	void	SetObjType(OBJTYPE ObjType)			 { m_ObjType = ObjType; }
	OBJTYPE GetObjType(void)					 { return m_ObjType; }
	int		&GetID(void)						 { return m_nID; }
	void	BreakObject(void);			//オブジェクトの全破壊
	void	BreakObject(OBJTYPE obj);	//指定したオブジェクトを破壊
protected://*****************************************************************************
	void			Release(void);											//解放処理			

	//その他//***********************************************************************
	static int		m_nDraw;			//現在の描画方法

	//変数宣言//***********************************************************************
	static CScene	**m_PScene[MAX_SCENE];		//レンダリングのポインタのポインタ
	static int		m_nNumAll[MAX_SCENE];		// 生成したの数
	static int		m_nMemoryAll[MAX_SCENE];	// 生成できる合計数
	static int		m_nCntStart;				//Updateのスタート位置
	static bool		m_bPause;					//ポーズの有無
	int				m_nID;			//自分の番号
	int				m_nPriority;	//自分の優先順位
	OBJTYPE			m_ObjType;		//オブジェクトタイプ
};

//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool SceneCreate(T *&pScene, int nPriority)
{
	pScene = NULL;
	if (CScene::GetnNumAll(nPriority) < CScene::GetnMemoryAll(nPriority))
	{//生成できる最大値出ないなら
	 pScene = new T(nPriority);
	 if (pScene != NULL) { pScene->Init(); return true; }
	}

	//MessageBox(0, "生成できない！", "", MB_OK);
	return false;
}
//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool Create(T *&pScene)
{
	pScene = NULL;
	pScene = new T;
	if (pScene != NULL) { pScene->Init(); return true; }
	//MessageBox(0, "生成できない！", "", MB_OK);

	return false;
}

#endif
