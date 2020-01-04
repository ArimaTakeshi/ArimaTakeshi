//=============================================================================
//
// メイン処理 [camera.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=====================
//　   前方宣言
//=====================
class CPlayer;

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)				// キーの最大数
#define	NUM_MOUSE_MAX		(8)					// マウスの最大数

//=====================
//	   基本クラス
//=====================
class CCamera
{
public://誰でも扱える
	typedef enum
	{
		CAMERA_TYPE_NONE = 0,		//何もない状態
		CAMERA_TYPE_DEMO,			//タイトルカメラ
		CAMERA_TYPE_RANKING_DEMO,	//ランキングカメラ
		CAMERA_TYPE_GAME,			//ゲームカメラ
		CAMERA_TYPE_MAX				//カメラの最大数
	}CAMERATYPE;

	CCamera();
	~CCamera();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void SetCamera();
	float GetRot(void) { return m_fAngle; }
	static void Delete(void);
	static CCamera *Create(CAMERATYPE CameraType);

protected://個人でのみ使う
	D3DXVECTOR3 m_posV;				//視点
	D3DXVECTOR3 m_posR;				//注視点
	D3DXVECTOR3 m_posVDest;			//目的の視点
	D3DXVECTOR3 m_posRDest;			//目的の注視点
	D3DXVECTOR3 m_rot;				//カメラの向きを入れる
	float		m_fDistance;		//距離
	D3DXVECTOR3 m_vecU;				//上方向ベクトル
	D3DXMATRIX	m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX	m_mtxView;			//ビューマトリックス
	float		m_fAngle;			//角度
	float		m_fLength;			//距離
	int			m_nType;			//種類
	int			m_nCount;			//秒数カウント
	int			m_CameraCount;		//カメラの移動時間
	float		m_fCameraAngle;		//角度
	float		m_fRot;				//回転
	bool		m_bOnOff;
	float		m_fRange;			// Y軸の距離
	int			m_nCntTitle;		// タイトル時のカウンター
	bool		m_bReset;			// タイトルカメラのリセット
	static CPlayer *m_pPlayer;		// プレイヤーのポインタ
};

#endif