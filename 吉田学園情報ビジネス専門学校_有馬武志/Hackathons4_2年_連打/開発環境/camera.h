//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCamera
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
	}Info;
	CCamera();
	~CCamera();

	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Reset(void);
	static void SetCamera(void);
	static void SetScene(SCENE_TYPE type);
	static void UpdateScene(void);
	static Info *GetCamera(void);
	void Collision(D3DXVECTOR3 *pos, float fLengthX, float fLengthZ);

	static CCamera camera;
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点

private://*****************************************************************************
		//変数宣言//***********************************************************************
	static Info m_info;			//カメラ情報

	D3DXVECTOR3 m_posC;			//当たり判定用
	D3DXVECTOR3 m_vecU;			//上方向のベクトル

	D3DXVECTOR3 m_goal;			//向かう位置
	D3DXVECTOR3 m_targetpos;	//追従する場所
	D3DXVECTOR3 m_rot;			//角度
	D3DXVECTOR3 m_addpos;			//カメラの水平移動分
	float		m_fDistance;		//カメラと注視点の距離
	float		m_fGMagnification;	//目的にいくまでの倍率

	int			m_nCntState;		//ムービーの進行度
	int			m_nCntModel;		//何のキャラを追従するか
	int			m_nCntTime;			//シーンのフレーム数記録
	bool		m_bCollision;		//プレイヤーがカメラ壁に当たっているかどうか

	D3DXMATRIX m_mtxProjection;		//プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			//ビューマトリックス
};

#endif
