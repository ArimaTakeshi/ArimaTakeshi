//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// カメラの構造体
//*****************************************************************************
typedef enum
{
	CAMERA_TYPE_NONE = 0,
	CAMERA_TYPE_DEMO,
	CAMERA_TYPE_RANKING_DEMO,
	CAMERA_TYPE_GAME,
	CAMERA_TYPE_MAX
}CAMERATYPE;

typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 rot;			//カメラの向きを入れる
	float		fDistance;		//距離
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXMATRIX	mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX	mtxView;		//ビューマトリックス
	float		fAngle;			//角度
	float		fLength;		//距離
	int			nType;			//種類
	int			nCntTimer;
	D3DVIEWPORT9 ViewPort;
}Camera;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(CAMERATYPE CameraType, int nIndxCamera);
Camera *GetCamera(void);

#endif
