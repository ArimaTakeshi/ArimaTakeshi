//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author :　有馬　武志　＆　加藤
//
//=============================================================================
#include "camera.h"		//カメラ
#include "input.h"		//キーボード
#include "player.h"		//プレイヤー
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
#define MAX_CAMERA			(3)					//カメラの最大数

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
	g_Camera[0].posV = D3DXVECTOR3(0.0f, 70.0f, 40.0f);			//視点の初期値
	g_Camera[0].posR = D3DXVECTOR3(0.0f, 70.0f, 340.0f);				//注視点の初期値
	g_Camera[0].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//法線の向き
	g_Camera[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[0].fLength = g_Camera[0].posV.z - g_Camera[0].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[0].nCntTimer = 0;										//時間
	g_Camera[0].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[0].ViewPort.X = 0;
	g_Camera[0].ViewPort.Y = 0;
	g_Camera[0].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[0].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[0].ViewPort.MinZ = 0.0f;
	g_Camera[0].ViewPort.MaxZ = 1.0f;

	//================
	// 2プレイヤー目のカメラの位置
	//================
	g_Camera[1].posV = D3DXVECTOR3(2000.0f, 70.0f, -4100.0f);			//視点の初期値
	g_Camera[1].posR = D3DXVECTOR3(2000.0f, 70.0f, -3800.0f);				//注視点の初期値
	g_Camera[1].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[1].fLength = g_Camera[1].posV.z - g_Camera[1].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[1].nCntTimer = 0;										//時間
	g_Camera[1].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[1].ViewPort.X = 0;
	g_Camera[1].ViewPort.Y = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[1].ViewPort.Height = SCREEN_HEIGHT / 2;
	g_Camera[1].ViewPort.MinZ = 0.0f;
	g_Camera[1].ViewPort.MaxZ = 1.0f;

	//================
	// タイトルのカメラの位置
	//================
	g_Camera[2].posV = D3DXVECTOR3(1500.0f, 60.0f, -3600.0f);			//視点の初期値
	g_Camera[2].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera[2].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	g_Camera[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	g_Camera[2].fLength = g_Camera[2].posV.z - g_Camera[2].posR.z;	//長さの計算　（VのｚからRのｚをひく）
	g_Camera[2].nCntTimer = 0;										//時間
	g_Camera[2].nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;											//角度
	g_fRot = 0;

	//ビューポートの初期化処理
	g_Camera[2].ViewPort.X = 0;
	g_Camera[2].ViewPort.Y = 0;
	g_Camera[2].ViewPort.Width = SCREEN_WIDTH;
	g_Camera[2].ViewPort.Height = SCREEN_HEIGHT;
	g_Camera[2].ViewPort.MinZ = 0.0f;
	g_Camera[2].ViewPort.MaxZ = 1.0f;
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
	Enemy *pEnemy = GetEnemy();

	int nCount = 0;
	float fcof = 0;

	////============================
	////飛行機の後ろにカメラが行くようにする処理
	////============================
	for (int nCount = 0; nCount < MAX_CAMERA; nCount++)
	{
		if (g_Camera[nCount].nType == CAMERA_TYPE_GAME)
		{//ゲーム内カメラ
			if (nCount == 0)
			{//プレイヤーのカメラ

				if (GetKeyboardPress(DIK_Q) == true)
				{
					g_Camera[nCount].fAngle -= 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				}
				if (GetKeyboardPress(DIK_E) == true)
				{
					g_Camera[nCount].fAngle += 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				}

				g_Camera[nCount].posVDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y);
				//g_Camera[nCount].posVDest.y = pPlayer->pos.y;
				g_Camera[nCount].posVDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y);
				g_Camera[nCount].posRDest.x = pPlayer->pos.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				//g_Camera[nCount].posRDest.y = pPlayer->pos.y;
				g_Camera[nCount].posRDest.z = pPlayer->pos.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				if (pPlayer->move.x > 0.7f || pPlayer->move.x < -0.7f || pPlayer->move.z > 0.7f || pPlayer->move.z < -0.7f)
				{// 移動時

					if (g_Camera[nCount].nCntTimer < 10)
					{
						if (g_Camera[nCount].posR.y < 52.0f || g_Camera[nCount].posV.y < 54.0f)
						{
							g_Camera[nCount].posR.y += 2.0f / 10.0f;
							g_Camera[nCount].posV.y += 4.0f / 10.0f;
						}
					}
					else
					{
						if (g_Camera[nCount].posR.y > 50.0f || g_Camera[nCount].posV.y > 50.0f)
						{
							g_Camera[nCount].posR.y -= 1.5f / 10.0f;
							g_Camera[nCount].posV.y -= 3.0f / 10.0f;
						}
					}

					if (g_Camera[nCount].nCntTimer < 20)
					{
						g_Camera[nCount].nCntTimer++;
					}
					else
					{
						g_Camera[nCount].nCntTimer = 0;
					}

					fcof = 0.1f + (float)(g_Camera[nCount].nCntTimer * 0.001f);
				}
				else
				{// 停止時
					g_Camera[nCount].nCntTimer = 0;

					fcof = 0.09f;

					if (g_Camera[nCount].posR.y != 50.0f || g_Camera[nCount].posV.y != 50.0f)
					{
						g_Camera[nCount].posR.y += (50.0f - g_Camera[nCount].posR.y) / 10.0f;
						g_Camera[nCount].posV.y += (50.0f - g_Camera[nCount].posV.y) / 10.0f;
					}
				}

				// 値代入
				g_Camera[nCount].posR.x += (g_Camera[nCount].posRDest.x - g_Camera[nCount].posR.x) * fcof;
				g_Camera[nCount].posR.z += (g_Camera[nCount].posRDest.z - g_Camera[nCount].posR.z) * fcof;
				g_Camera[nCount].posV.x += (g_Camera[nCount].posVDest.x - g_Camera[nCount].posV.x) * fcof;
				g_Camera[nCount].posV.z += (g_Camera[nCount].posVDest.z - g_Camera[nCount].posV.z) * fcof;

				/*//===================================
				//注視点をプレイヤーに追従ようにする
				//===================================
				g_Camera[nCount].posV.x = pPlayer->pos.x;
				g_Camera[nCount].posV.z = pPlayer->pos.z;
				//視点をプレイヤーに追従ようにする
				g_Camera[nCount].posR.x = pPlayer->pos.x - sinf(g_Camera[nCount].fAngle)* -MOVE_CAMERA;
				g_Camera[nCount].posR.z = pPlayer->pos.z - cosf(g_Camera[nCount].fAngle)* -MOVE_CAMERA;*/
			}
			if (nCount == 1)
			{//鬼のカメラ

				if (GetKeyboardPress(DIK_NUMPAD7) == true)
				{
					g_Camera[nCount].fAngle -= 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				}
				if (GetKeyboardPress(DIK_NUMPAD9) == true)
				{
					g_Camera[nCount].fAngle += 0.04f;
					g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
					g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				}

				g_Camera[nCount].posVDest.x = pEnemy[1].pos.x - sinf(pEnemy[1].rot.y);
				//g_Camera[nCount].posVDest.y = pEnemy[1].pos.y;
				g_Camera[nCount].posVDest.z = pEnemy[1].pos.z - cosf(pEnemy[1].rot.y);
				g_Camera[nCount].posRDest.x = pEnemy[1].pos.x + sinf(g_Camera[nCount].fAngle) * MOVE_CAMERA;
				//g_Camera[nCount].posRDest.y = pEnemy[1].pos.y;
				g_Camera[nCount].posRDest.z = pEnemy[1].pos.z + cosf(g_Camera[nCount].fAngle) * MOVE_CAMERA;

				if (pEnemy[1].move.x > 0.7f || pEnemy[1].move.x < -0.7f || pEnemy[1].move.z > 0.7f || pEnemy[1].move.z < -0.7f)
				{// 移動時
					if (g_Camera[nCount].nCntTimer < 30)
					{
						g_Camera[nCount].nCntTimer++;
					}

					fcof = 0.1f + (float)(g_Camera[nCount].nCntTimer * 0.001f);
				}
				else
				{// 停止時
					g_Camera[nCount].nCntTimer = 0;

					fcof = 0.09f;
				}

				// 値代入
				g_Camera[nCount].posR.x += (g_Camera[nCount].posRDest.x - g_Camera[nCount].posR.x) * fcof;
				g_Camera[nCount].posR.z += (g_Camera[nCount].posRDest.z - g_Camera[nCount].posR.z) * fcof;
				g_Camera[nCount].posV.x += (g_Camera[nCount].posVDest.x - g_Camera[nCount].posV.x) * fcof;
				g_Camera[nCount].posV.z += (g_Camera[nCount].posVDest.z - g_Camera[nCount].posV.z) * fcof;

				/*if (GetKeyboardPress(DIK_RSHIFT) == true)
				{
				g_Camera[nCount].fAngle -= 0.05f;
				g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;
				g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;

				}
				if (GetKeyboardPress(DIK_NUMPAD1) == true)
				{
				g_Camera[nCount].fAngle += 0.05f;
				g_Camera[nCount].posVDest.x = g_Camera[nCount].posR.x + sinf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;
				g_Camera[nCount].posVDest.z = g_Camera[nCount].posR.z + cosf(g_Camera[nCount].fAngle) * g_Camera[nCount].fDistance;
				}

				//===================================
				//注視点をプレイヤーに追従ようにする
				//===================================
				//for (int nCount1 = 0; nCount1 < 2; nCount1++)
				{
				g_Camera[nCount].posV.x = pEnemy[1].pos.x;
				g_Camera[nCount].posV.z = pEnemy[1].pos.z;
				//視点をプレイヤーに追従ようにする
				g_Camera[nCount].posR.x = pEnemy[1].pos.x - sinf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				g_Camera[nCount].posR.z = pEnemy[1].pos.z - cosf(g_Camera[nCount].fAngle)* MOVE_CAMERA;
				}*/
			}
			if (nCount == 2)
			{//タイトルのカメラ
				g_Camera[nCount].posV = D3DXVECTOR3(0.0f, 50.0f, 0.0f);	//視点の初期値
				g_Camera[nCount].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//注視点の初期値
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