//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author :　有馬　武志　＆　加藤
//
//=============================================================================
#include "camera.h"		//カメラ
#include "input.h"		//キーボード
#include "player.h"		//プレイヤー
#include "player2.h"	//プレイヤー
#include "bullet.h"		//弾
#include "object.h"		//オブジェクト
#include "sound.h"		//サウンド
#include "effect.h"		//エフェクト
#include "enemy.h"		//鬼

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_ANGLE			(0.01f)				//カメラ角度の移動量
#define MOVE_ANGLE1			(0.001f)			//カメラ角度の移動量
//#define MOVE_CAMERA			(1200.0f)			//カメラの距離
#define MOVE_OBJECT			(1000.0f)
#define MOVE_CAMERA			(160.0f)			//カメラの距離
#define CAMERA_KM			(1200.0f)			//カメラの描画距離
#define MOVE_SPEED			(0.001f)
#define MOVE_ANGLE2			(15.0f)
#define MOVE_ANGLE3			(0.03f)
#define MAX_CAMERA			(5)					//カメラの最大数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_Camera[MAX_CAMERA];					//カメラの情報
int g_nCount;									//秒数カウント
float g_fCameraAngle = 45.0f;					//角度
float g_fRot;

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	//プレイヤーの情報
	Object pObject = *GetObject();

	//================
	//1プレイヤー目のカメラの位置
	//================
	g_Camera[0].posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);			//視点の初期値
	g_Camera[0].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//法線の向き
	g_Camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[0].fLength = g_Camera[0].posV.z - g_Camera[0].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[0].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[0].ViewPort.X = 0;
	g_Camera[0].ViewPort.Y = 0;
	g_Camera[0].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[0].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[0].ViewPort.MinZ = 0.0f;
	g_Camera[0].ViewPort.MaxZ = 1.0f;

	//================
	// 2プレイヤー目のカメラの位置
	//================
	g_Camera[1].posV = D3DXVECTOR3(0.0f, 300.0f, -300.0f);			//視点の初期値
	g_Camera[1].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[1].fLength = g_Camera[1].posV.z - g_Camera[1].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[1].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[1].ViewPort.X = 0;
	g_Camera[1].ViewPort.Y = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[1].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.MinZ = 0.0f;
	g_Camera[1].ViewPort.MaxZ = 1.0f;

	//================
	// 鬼カメラの位置
	//================
	g_Camera[2].posV = D3DXVECTOR3(0.0f, 400.0f, -400.0f);			//視点の初期値
	g_Camera[2].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera[2].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[2].fLength = g_Camera[2].posV.z - g_Camera[2].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[2].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[2].ViewPort.X = SCREEN_WIDTH / 2;
	g_Camera[2].ViewPort.Y = 0;
	g_Camera[2].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[2].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[2].ViewPort.MinZ = 0.0f;
	g_Camera[2].ViewPort.MaxZ = 1.0f;

	//================
	// 固定カメラの位置
	//================
	g_Camera[3].posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//視点の初期値
	g_Camera[3].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera[3].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[3].fLength = g_Camera[3].posV.z - g_Camera[3].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[3].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[3].ViewPort.X = SCREEN_WIDTH / 2;
	g_Camera[3].ViewPort.Y = SCREEN_HEIGHT / 2;
	g_Camera[3].ViewPort.Width = SCREEN_WIDTH / 2;
	g_Camera[3].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[3].ViewPort.MinZ = 0.0f;
	g_Camera[3].ViewPort.MaxZ = 1.0f;

	//================
	// タイトルのカメラの位置
	//================
	g_Camera[4].posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);			//視点の初期値
	g_Camera[4].posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);				//注視点の初期値
	g_Camera[4].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[4].fLength = g_Camera[4].posV.z - g_Camera[4].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[4].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[4].ViewPort.X = 0;
	g_Camera[4].ViewPort.Y = 0;
	g_Camera[4].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[4].ViewPort.Height = SCREEN_HEIGHT;
	g_Camera[4].ViewPort.MinZ = 0.0f;
	g_Camera[4].ViewPort.MaxZ = 1.0f;

	//================
	// タイトルのカメラの位置
	//================
	g_Camera[5].posV = D3DXVECTOR3(1500.0f, 60.0f, -3600.0f);			//視点の初期値
	g_Camera[5].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera[5].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[5].fLength = g_Camera[5].posV.z - g_Camera[5].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[5].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[5].ViewPort.X = 0;
	g_Camera[5].ViewPort.Y = 0;
	g_Camera[5].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[5].ViewPort.Height = SCREEN_HEIGHT;
	g_Camera[5].ViewPort.MinZ = 0.0f;
	g_Camera[5].ViewPort.MaxZ = 1.0f;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera()
{
	//プレイヤーの情報
	Object *pObject = GetObject();
	Player *pPlayer = GetPlayer();
	Player2 *pPlayer2 = GetPlayer2();
	Enemy *pEnemy = GetEnemy();
	Bullet *pBullet = GetBullet();

	static int nCount = 0;

	////============================
	////飛行機の後ろにカメラが行くようにする処理
	////============================
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (g_Camera[nCount].nType == CAMERA_TYPE_GAME)
		{//ゲーム内カメラ
			if (nCount != 4 && nCount != 3)
			{
				if (nCount == 0)
				{
					///*if (pPlayer->move.x < 0.01f || pPlayer->move.x > -0.01f || pPlayer->move.z < 0.01f || pPlayer->move.z > -0.01f)
					//{*/
					//	//回数を足す
					//	g_nCount++;
					//	//3秒後に後ろに回りこむ
					//	//if (g_nCount >= 180)
					//	//{//止まってから１秒後に
					//		fDiAngle = (pPlayer->rot.y + D3DX_PI) - g_Camera[nCount].fAngle;
					//		if (fDiAngle > D3DX_PI)
					//		{
					//			fDiAngle -= D3DX_PI * 2.0f;
					//		}
					//		if (fDiAngle < -D3DX_PI)
					//		{
					//			fDiAngle += D3DX_PI * 2.0f;
					//		}
					//		//	カメラのアングルに目的のアングルを足し、速度をかける
					//		g_Camera[nCount].fAngle += fDiAngle * 0.05f;

					//		if (g_Camera[nCount].fAngle > D3DX_PI)
					//		{
					//			fDiAngle -= D3DX_PI * 2.0f;
					//		}
					//		if (g_Camera[nCount].fAngle > D3DX_PI)
					//		{
					//			fDiAngle += D3DX_PI * 2.0f;
					//		}
					////	}
					////}
					////else
					////{//動いているときは、０を代入
					////	g_nCount = 0;
					////}

					////=============================
					////　 　マウスでカメラ操作
					////=============================
					////注視点位置変更
					//if (pMouse.lY < 0)
					//{//Y座標
					//	g_Camera[nCount].posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
					//}
					//if (pMouse.lY > 0)
					//{//Y座標
					//	g_Camera[nCount].posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
					//}
					//if (pMouse.lX < 0)
					//{//X座標
					//	g_Camera[nCount].rot.y += (pMouse.lX / 600.0f);
					//	g_Camera[nCount].posR.x = g_Camera[nCount].posV.x - sinf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//	g_Camera[nCount].posR.z = g_Camera[nCount].posV.z - cosf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//}
					//if (pMouse.lX > 0)
					//{//X座標
					//	g_Camera[nCount].rot.y += (pMouse.lX / 600.0f);
					//	g_Camera[nCount].posR.x = g_Camera[nCount].posV.x - sinf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//	g_Camera[nCount].posR.z = g_Camera[nCount].posV.z - cosf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//}

					////画面がガクガクしないようにする。
					//g_Camera[nCount].posR.x = g_Camera[nCount].posV.x - sinf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;
					//g_Camera[nCount].posR.z = g_Camera[nCount].posV.z - cosf(g_Camera[nCount].rot.y) * g_Camera[nCount].fLength;

					//===================================
					//注視点をプレイヤーに追従ようにする
					//===================================
					g_Camera[nCount].posR.x = pPlayer->pos.x;
					g_Camera[nCount].posR.z = pPlayer->pos.z;
					//視点をプレイヤーに追従ようにする
					g_Camera[nCount].posV.x = pPlayer->pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
					g_Camera[nCount].posV.z = pPlayer->pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				}
				if (nCount == 1)
				{
				

					//===================================
					//注視点をプレイヤーに追従ようにする
					//===================================
					g_Camera[nCount].posR.x = pPlayer2->pos.x;
					g_Camera[nCount].posR.z = pPlayer2->pos.z;
					//視点をプレイヤーに追従ようにする
					g_Camera[nCount].posV.x = pPlayer2->pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
					g_Camera[nCount].posV.z = pPlayer2->pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				}
				if (nCount == 2)
				{
					//===================================
					//注視点をプレイヤーに追従ようにする
					//===================================
					for (int nCount1 = 0; nCount1 < 2; nCount1++)
					{
						g_Camera[nCount].posR.x = pEnemy[nCount1].pos.x;
						g_Camera[nCount].posR.z = pEnemy[nCount1].pos.z;
						//視点をプレイヤーに追従ようにする
						g_Camera[nCount].posV.x = pEnemy[nCount1].pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
						g_Camera[nCount].posV.z = pEnemy[nCount1].pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
					}
				}
			}
			else if (nCount == 3)
			{//固定カメラ
				g_Camera[nCount].posV = D3DXVECTOR3(2000.0f, 5600.0f, -2051.0f);	//視点の初期値
				g_Camera[nCount].posR = D3DXVECTOR3(2000.0f, 0.0f, -2001.0f);		//注視点の初期値
			}
		}
		else if (g_Camera[nCount].nType == CAMERA_TYPE_DEMO)
		{//タイトルのカメラ
			if (nCount == 4)
			{
				g_Camera[nCount].posV = D3DXVECTOR3(0.0f, 50.0f, 0.0f);	//視点の初期値
				g_Camera[nCount].posR = D3DXVECTOR3(0.0f,0.0f, 0.0f);	//注視点の初期値
			}
		}
	}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(CAMERATYPE CameraType, int nIndxCamera)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	g_Camera[nIndxCamera].nType = CameraType;

	//ビューポートの設定
	pDevice->SetViewport(&g_Camera[nIndxCamera].ViewPort);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera[nIndxCamera].mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH
	(
		&g_Camera[nIndxCamera].mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)g_Camera[nIndxCamera].ViewPort.Width / (float)g_Camera[nIndxCamera].ViewPort.Height,
		10.0f,
		10000
	);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera[nIndxCamera].mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera[nIndxCamera].mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_Camera[nIndxCamera].mtxView,
		&g_Camera[nIndxCamera].posV,
		&g_Camera[nIndxCamera].posR,
		&g_Camera[nIndxCamera].vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera[nIndxCamera].mtxView);

}
//=============================================================================
//	カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera[0];
}