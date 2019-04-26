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
#define MAX_SCENE		(8)					//シーンの最大優先順位
#define OBJ_PRIORITY	(5)					//3Dオブジェの優先順位
#define MAX_3DSCENE		(OBJ_PRIORITY + 1)					//3D最大の優先順位
#define START_2DSCENE	(MAX_3DSCENE)	//2D開始の優先順位
#define PAUSE_PRIORITY	(MAX_SCENE - 1)		//ポーズの優先順位

#define PAUSE_PRIORITY	(MAX_SCENE - 1)		//ポーズの優先順位
#define PAUSE_LENGTH	(25.0f)				//ポーズ上下枠の長さ

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
		DRAW_TYPE_AER,			//黒無視加算無し
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
		OBJTYPE_NONE2,
		OBJTYPE_DUNGEON, OBJTYPE_MESH,
		OBJTYPE_EFFECT, OBJTYPE_ANIM3D, OBJTYPE_SALE,
		OBJTYPE_Satellite, OBJTYPE_ORBIT, OBJTYPE_LINE, OBJTYPE_BULLET, 
		OBJTYPE_BOSS, 
		//モデル//**********************************************
		OBJTYPE_PLAYER, OBJTYPE_ENEMY, OBJTYPE_OBJ,
		//画像//**********************************************
		OBJTYPE_OBJ_NO,	//モデル　判定：(有/無し)
		OBJTYPE_OTHER,	//ゲーム外カメラ用(UI用)
		OBJTYPE_UI,		//ユーザーインターフェイス
		OBJTYPE_NUMBER,
		OBJTYPE_GOAL, OBJTYPE_SHOP,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef struct
	{//種類ごとのモデル情報保存
		LPD3DXMESH		MeshModel = NULL;		//メッシュ情報へのポインタ
		LPD3DXBUFFER	pBuffMatModel = NULL;	//マテリアル情報へのポインタ
		DWORD			nNumMatModel = NULL;	//マテリアルの情報数
	}MODEL_DRAW;
	typedef enum
	{
		/* BG */			TEX_Title, TEX_Select, TEX_Select0, TEX_G_EXPLOSION,
		/* 雲 */			TEX_Fog000, TEX_Fog001,
		/* ロゴ */			TEX_TitleLogo, TEX_Press, TEX_HitLogo,
		/* UI */			TEX_Arrow, TEX_S_Move,TEX_Help,
		/*ロックオン*/		TEX_Lock_On,	/*ボタンUI*/		TEX_Button_UI,
		/*ゲージ*/			TEX_Gage, TEX_GageDeco,
		/*数字*/			TEX_Number,
		/*ヒット*/			TEX_HIT0, TEX_HIT1,
		/*死亡*/			TEX_Dead,		/*消失前兆*/		TEX_Omen,		/*消失*/			TEX_Over,
		/*エフェクト*/		TEX_Fire,		/*軌跡*/			TEX_Orbit,		/*ゲート*/			TEX_GateE,
		/*キャラ*/			TEX_BSword,
		TEX_TAKASHI,
		TEX_Icon_TKS,
		TEX_Hole,
		TEX_Room,
		TEX_CLEAR,
		TEX_OVER,
		TEX_Alarm,
		TEX_PressA,
		TEX_Quiz,
		TEX_Pause,
		TEX_PHand,
		TEX_HIT99,
		/*洞窟*/			TEX_Dungeon,	/*ゲート*/			TEX_Gate,
		/* ドア */			TEX_Door,		/* 紙 */			TEX_Paper,
		/* 柵 */			TEX_Fence,		/* 岩 */			TEX_Stone,		/*鉄骨*/			TEX_Steel,
		/*方位磁針(本体)*/	TEX_Pos_Mag,	/*方位磁針(針)*/	TEX_Pos_Nee,	/*衛星*/			TEX_Satellite,
		/*ここからモデル用*/TEX_CHAR,
		/*マント*/			TEX_Cloak = TEX_CHAR,
		/*剣*/				TEX_Sword,
		/*棍*/				TEX_Stick,
		TEX_MAX
	}TEXTURE;
	CScene::CScene(int nPrioryity = 3);
	~CScene();

	static LPDIRECT3DTEXTURE9	&Load(TEXTURE tex);
	static void	UnLoad(void);
	static void	ReleaseAll(void);
	static void	UpdateAll(void);
	static void	DrawAll(LPDIRECT3DDEVICE9 &pDevice);
	static void	Draw3D(LPDIRECT3DDEVICE9 &pDevice);
	static void	DrawObj(LPDIRECT3DDEVICE9 &pDevice);
	static void	Draw2D(LPDIRECT3DDEVICE9 &pDevice);

	static void	UninitAll(void);
	static void	BreakObject(void);			//オブジェクトの全破壊
	static void	BreakObject(OBJTYPE obj);	//指定したオブジェクトを破壊

	static CScene *&GetTop(int nPrioryity) { return m_pTop[nPrioryity]; };
	static CScene *&GetCur(int nPrioryity) { return m_pCur[nPrioryity]; };
	static int &GetnNumAll(int nPrioryity) { return m_nNumAll[nPrioryity]; };
	//*****************************************************************************
	virtual HRESULT Init(void)					 { return S_OK; };
	virtual void	Uninit(void) { m_bDeath = true; SetObjType(OBJTYPE_NONE); };
	virtual void	Draw(void)					 {};
	virtual void	Update(void)				 {};
	static int		&GetnCntStart(void)			 { return m_nCntStart; }
	static bool		&GetbPause(void)			 { return m_bPause; }
	static bool		DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//描画準備処理

	D3DXVECTOR3	*Getpos(void);
	CScene	*&GetpNext(void) { return m_pNext; }
	CScene	*&GetpPrev(void) { return m_pPrev; }
	bool	&GetbDeath(void) { return m_bDeath; }
	void	SetObjType(OBJTYPE ObjType)			 { m_ObjType = ObjType; }
	OBJTYPE GetObjType(void)					 { return m_ObjType; }
	static LPDIRECT3DTEXTURE9	&GetTexture(int nNumber) { return m_pTexture[nNumber]; }

protected://*****************************************************************************
	void			Release(void);											//解放処理			
private://*****************************************************************************
	//変数宣言//***********************************************************************
	static int		m_nDraw;			//現在の描画方法
	static LPDIRECT3DTEXTURE9	m_pTexture[TEX_MAX];		// テクスチャへのポインタ
	static CScene	*m_pTop[MAX_SCENE];		// 開始位置
	static CScene	*m_pCur[MAX_SCENE];		// 最後尾(カレントの略->現在)
	static int		m_nNumAll[MAX_SCENE];				//Updateのスタート位置
	static int		m_nCntStart;				//Updateのスタート位置
	static bool		m_bPause;					//ポーズの有無

	CScene *m_pNext;				//次
	CScene *m_pPrev;				//前
	int				m_nPriority;	//自分の優先順位
	OBJTYPE			m_ObjType;		//オブジェクトタイプ
	bool			m_bDeath;		//死亡フラグ
};

//==================================================================================================//
//    * テンプレート定義 *
//==================================================================================================//
template<class T> bool SceneCreate(T *&pScene, int nPriority)
{
	pScene = NULL;
	pScene = new T(nPriority);
	if (pScene != NULL) { pScene->Init(); return true; }

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
