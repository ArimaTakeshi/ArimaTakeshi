//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "manager.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define		DRAW_ANGLE		(45.0f)				//カメラ本体 +上, -下
#define		DRAW_ANGLEP		(DRAW_ANGLE + 10.0f)				//カメラ本体 +上, -下
#define		DRAW_DISTANCE	(2000.0f * 2000.0f)				//カメラ本体 +上, -下
#define		DRAW_DISTANCE2	(100.0f * 100.0f)				//カメラ本体 +上, -下
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera
{
public:
	typedef enum
	{//モデルの種類
		CAMERA_TYPE_NORMAL,
		CAMERA_TYPE_CHAR,
		CAMERA_TYPE_OBJ,
		CAMERA_TYPE_EVENT,
		CAMERA_TYPE_MAX,
	}CAMERA_TYPE;
	CCamera() {};
	~CCamera() {};

	void Init(void);
	void Draw(void);
	void SetCamera(D3DXVECTOR3 WKposV);
	bool DrawCheck(D3DXVECTOR3 &pos, float fLength);
	void SetViewport(int left, int up, int right, int bottom);

	D3DXVECTOR3 &GetRot(void) { return m_rot; };
	D3DXVECTOR3 &GetposV(void) { return m_posV; };
	D3DXVECTOR3 &GetposR(void) { return m_posR; };
	D3DXVECTOR3 &GetvecU(void) { return m_vecU; };
	D3DXVECTOR3 &Gettargetpos(void) { return m_targetpos; };
	float		&GetfDistance(void) { return m_fDistance; };
	CAMERA_TYPE	&GetType(void) { return m_Type; };
	int	&GetnNumCamera(void) { return m_nNumCamera; };

private://*****************************************************************************

	//変数宣言//***********************************************************************
	int			m_nNumCamera;	//カメラ番号
	CAMERA_TYPE m_Type;			//カメラタイプ
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_targetpos;	//追従する場所
	D3DXVECTOR3 m_rot;			//角度
	float		m_fDistance;		//カメラと注視点の距離

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
	D3DVIEWPORT9 m_viewport;		//カメラ設定用
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera_Char : public CCamera
{
public:
	CCamera_Char()	{};
	~CCamera_Char() {};

	void Init(void);
	void Uninit(void) { delete this; };
	void Update(void);
	void Draw(void);
	void Reset(void);
	void SetCamera(void);

	float *&GetpDistance(void) { return m_pDistance; };
	D3DXVECTOR3 *&GetpChare(void) { return m_pChar; };
	D3DXVECTOR3 *&GetpMove(void) { return m_pMove; };
private://*****************************************************************************
		//変数宣言//***********************************************************************
	D3DXVECTOR3	*m_pChar;		//何のキャラを追従するか
	D3DXVECTOR3	*m_pMove;		//何のキャラを追従するか
	D3DXVECTOR3 m_goal;			//向かう位置
	float		*m_pDistance;		//カメラと注視点の距離の目的値
	float		m_fGMagnification;	//目的にいくまでの倍率

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera_Play
{
public:
	CCamera_Play() {};
	~CCamera_Play() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CCamera_Char *&GetChar(void) { return m_pCamera_Char; }
	CCamera		 *&GetObj(void)  { return m_pCamera_Obj; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	CCamera_Char *m_pCamera_Char;	//キャラクター追尾
	CCamera		 *m_pCamera_Obj;	//オブジェのみ
};

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera_Manager
{
public:
	typedef enum
	{//モデルの種類
		STATE_NONE = 0,	//動かせない
		STATE_GAME,		//ゲーム
		STATE_MOVIE,		//ムービー

	}CAMERA_STATE;
	typedef enum
	{//モデルの種類
		VIEW_IGNORE = 0,	//何にも関わらない
		VIEW_FOLLOW,		//追従
		VIEW_WATCH,			//追わずに見るだけ

	}CAMERA_VIEW;
	typedef enum
	{//モデルの種類
		SCENE_VIEW_NORMAL = 0,	//通常通り動く
		SCENE_VIEW_STOP,		//モデルのみ止まる

	}SCENE_VIEW;
	typedef enum
	{//モデルの種類
		SCENE_TYPE_NO = 0,	//戻る　間違えようの対処
		SCENE_TYPE_BOSS,	//ボス前のシーン

	}SCENE_TYPE;
	typedef struct
	{
		CAMERA_STATE	state;		//状態
		CAMERA_VIEW		ViewC;		//見る状態 カメラ
		SCENE_VIEW		ViewS;		//見る状態 カメラ以外(モデル等)
		SCENE_TYPE		scene;			//何のシーンか
		CCamera			*pCamera;		//現在描画中のカメラ
		int				nCntState;		//ムービーの進行度
		int				nCntTime;		//シーンのフレーム数記録

	}Info;
	CCamera_Manager() {};
	~CCamera_Manager() {};

	void Init(void);
	void Update(void);
	void Uninit(void);
	void Uninit_Event(void);
	void Draw(void);
	CCamera_Char *&GetEvent(void) { return m_pEvent; }
	CCamera_Play *&GetPlay(int nID) { return m_pPlay[nID]; }

	static bool DrawCheck(D3DXVECTOR3 &pos, float fLength);
	static CCamera_Char *&Create_Event(void);
	static CCamera_Play *&Create_Play(int nCount);
	static void SetScene(CCamera_Manager::SCENE_TYPE type);
	static void UpdateScene(void);
	static Info &GetInfo(void) { return m_info; };

private://*****************************************************************************
	static Info	m_info;

	//変数宣言//***********************************************************************
	CCamera_Char *m_pEvent;
	CCamera_Play *m_pPlay[MAX_PLAYER];
};
#endif
