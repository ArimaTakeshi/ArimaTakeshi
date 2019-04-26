//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author :　有馬　武志
//
//=============================================================================
#include "camera.h"		//カメラ
#include "input.h"		//キーボード
#include "player.h"		//プレイヤー
#include "bullet.h"		//弾
#include "object.h"		//オブジェクト
#include "herimodel.h"	//ヘリモデル
#include "sound.h"		//サウンド
#include "effect.h"		//エフェクト

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_ANGLE			(0.01f)				//カメラ角度の移動量
#define MOVE_ANGLE1			(0.001f)			//カメラ角度の移動量
#define MOVE_CAMERA			(1200.0f)			//カメラの距離
#define MOVE_OBJECT			(1000.0f)			//
//#define MOVE_CAMERA			(30.0f)			//カメラの距離
#define CAMERA_KM			(1200.0f)			//カメラの描画距離
#define MOVE_SPEED			(0.001f)			//カメラのスピード
#define MOVE_ANGLE2			(15.0f)				//角度
#define MOVE_ANGLE3			(0.03f)				//微調整用角度

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_Camera;							//カメラの情報
int g_nCount;								//秒数カウント
int g_CameraCount;							//カメラの移動時間
float g_fCameraAngle = 45.0f;				//角度
float g_fRot;								//回転
float g_BulletMouserotf;					//マウスの位置に弾を飛ばす

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	//プレイヤーの情報
	Object pObject = *GetObject();

	g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f, -400.0f);			//視点の初期値
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	g_Camera.vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);				//法線の向き
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	//g_Camera.rot.y = 0.0f;									//角度
	g_Camera.fLength = g_Camera.posV.z - g_Camera.posR.z;		//長さの計算　（VのｚからRのｚをひく）
	g_Camera.nType = CAMERA_TYPE_NONE;							//種類
	g_fCameraAngle = 45.0f;										//角度
	g_CameraCount = 0;											//カメラの数初期化
	g_fRot = 0;													//カメラの向き初期化
	g_BulletMouserotf = 0.0f;									//マウスの位置に弾を飛ばす初期化
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
	//マウスの情報
	DIMOUSESTATE2 pMouse = GetMousePointer();

	//プレイヤーの情報
	Object *pObject = GetObject();

	Player *pPlayer = GetPlayer();

	Player2 *pPlayer2 = GetPlayer2();

	Bullet *pBullet = GetBullet();

	static int nCount = 0;
	float fRot;

	//g_Camera.posV = pObject->pos;
	////g_Camera.posRに代入　　　　　　　　　　　　　	↓角度　　　　　↓Rとの距離
	//g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
	//g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fLength;

	////============================
	////飛行機の後ろにカメラが行くようにする処理
	////============================
	if (g_Camera.nType == CAMERA_TYPE_GAME)
	{//ゲーム内カメラ
		//=============================
		//　 　マウスでカメラ操作
		//=============================
		//注視点位置変更
		if (pMouse.lY < 0)
		{//Y座標
			g_Camera.posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
		}
		if (pMouse.lY > 0)
		{//Y座標
			g_Camera.posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
		}
		if (pMouse.lX < 0)
		{//X座標
			g_Camera.rot.y += (pMouse.lX / 600.0f);
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		}
		if (pMouse.lX > 0)
		{//X座標
			g_Camera.rot.y += (pMouse.lX / 600.0f);
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		}

		g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
		g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		{
			//============================
			//      弾を出す処理
			//============================

			//秒数カウント
			nCount++;

			g_BulletMouserotf += -pMouse.lY / 30.0f;

			//弾の出るスピード
			if (nCount % 8 == 0)
			{
				if (GetMousePress(0) == true)
				{//弾を出す
					fRot = atan2f(powf(g_Camera.posR.y - g_Camera.posV.y, 2), powf(g_Camera.posR.x - g_Camera.posV.x, 2) + powf(g_Camera.posR.z - g_Camera.posV.z, 2));
					SetBullet(D3DXVECTOR3(g_Camera.posV.x + sinf(g_Camera.rot.y) * 0.0f, g_Camera.posV.y - sinf(fRot) * 0.0f - 0.0f, g_Camera.posV.z + cosf(g_Camera.rot.y) * 0.0f), g_Camera.rot
						,D3DXVECTOR3((sinf(g_Camera.rot.y - D3DX_PI) * -20.0f) * cosf(fRot), sinf(fRot) * -20.0f, (cosf(g_Camera.rot.y - D3DX_PI) * -20.0f) * cosf(fRot)));
					PlaySound(SOUND_LABEL_SE_SHOOT);
				}
			}
		}
		{
			//============================
			//    モデルの位置の代入
			//============================

			//カメラに飛行機をくっつける
			pObject[1].pos = g_Camera.posV;

			//カメラに銃をくっつける
			//pObject[2].pos = g_Camera.posV;

			//カメラの回転と飛行機の回転が同じ値でなければならない
			pObject[1].rot.y += MOVE_SPEED;
		}
		{
			//=============================
			//          飛行機
			//=============================

			//回転させる
			g_fRot += MOVE_ANGLE1;

			if (g_fRot > D3DX_PI)
			{//左周り
				g_fRot = -D3DX_PI;
			}
			//============================
			//注視点をプレイヤーに追従ようにする
			//============================
			//g_Camera.posR.x = pPlayer->pos.x;
			//g_Camera.posR.z = pPlayer->pos.z;
			//視点をプレイヤーに追従ようにする
			g_Camera.posV.x = pPlayer->pos.x - sinf(g_fRot)* MOVE_CAMERA;
			g_Camera.posV.z = pPlayer->pos.z - cosf(g_fRot)* MOVE_CAMERA;
		}
	}
	if (g_Camera.nType == CAMERA_TYPE_DEMO)
	{//タイトルのカメラ
		if (g_CameraCount >= 0 && g_CameraCount <= 399)
		{//注視点を原点に左回り
			g_Camera.rot.y += MOVE_ANGLE1;
			if (g_Camera.rot.y > D3DX_PI)
			{//左周り
				g_Camera.rot.y = -D3DX_PI;
			}
			//g_Camera.posVにD3DXVECTOR3のsinとcosを代入
			g_Camera.posV = D3DXVECTOR3(g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fLength, g_Camera.posV.y, g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fLength);
		}
		if (g_CameraCount == 400)
		{//カメラの位置を初期値に戻し、角度も戻す
			g_Camera.rot.y = 0;
			g_Camera.posV = D3DXVECTOR3(-100.0f, 50.0f, -180.0f);			//視点の初期値
			g_Camera.posR = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);				//注視点の初期値
		}
		if (g_CameraCount >= 401 && g_CameraCount <= 799)
		{//カメラを自動タテ移動させる
			g_Camera.rot.y = 0;
			g_Camera.posV.z += 0.5f;
			g_Camera.posR.z += 0.5f;
		}
		if (g_CameraCount == 800)
		{//カメラの位置を初期化する
			g_Camera.rot.y = 0;
			g_Camera.posV = D3DXVECTOR3(0.0f, 300.0f, 0.0f);			//視点の初期値
			g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
		}
		if (g_CameraCount >= 801 && g_CameraCount <= 1199)
		{//視点を原点に右回り
			g_Camera.rot.y += MOVE_ANGLE1;
			if (g_Camera.rot.y > D3DX_PI)
			{//右周りの3.14を超えたら
				g_Camera.rot.y = -D3DX_PI;
			}
			//g_Camera.posRにD3DXVECTOR3のsinとcosを代
			g_Camera.posR = D3DXVECTOR3(g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength, g_Camera.posR.y, g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength);
		}
		if (g_CameraCount == 1200)
		{//最初のループに戻す
			g_Camera.rot.y = 0.0f;
			g_Camera.posV = D3DXVECTOR3(0.0f, 50.0f, -150.0f);			//視点の初期値
			g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
			g_CameraCount = 0;
		}
		//フレームカウント
		g_CameraCount++;
	}
	if (g_Camera.nType == CAMERA_TYPE_RANKING_DEMO)
	{//ランキングでのカメラ
		//Rは注視点
		//Vは視点
		if (g_CameraCount >= 0 && g_CameraCount <= 1)
		{//ヘリコプターの初期値
			g_Camera.rot.y = 0;
			g_Camera.posV = D3DXVECTOR3(-50.0f, 50.0f, -180.0f);	//視点の初期値
			g_Camera.posR = D3DXVECTOR3(-500.0f, 1000.0f, 0.0f);	//注視点の初期値
			pPlayer2->pos = D3DXVECTOR3(-150.0f, 300.0f, -300.0f);	//ヘリの初期化位置
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//ヘリのプロペラを回転
		}
		if (g_CameraCount >= 2 && g_CameraCount <= 79)
		{//前に移動（Z方向
			pPlayer2->pos.z += 3.8f;								//ヘリを前進させる
			g_Camera.posR.x += 5;									//カメラの横を移動
			g_Camera.posR.y -= 10;									//カメラの縦を移動
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//ヘリのプロペラを回転
		}
		if (g_CameraCount >= 80 && g_CameraCount <= 179)
		{//停止（ヘリから人が下りる
			g_Camera.posR = D3DXVECTOR3(-110.0f, 220.0f, 0.0f);		//カメラの位置を止める
			//pPlayer2->pos = D3DXVECTOR3(-150.0f, 300.0f, -3.5f);	//ヘリの止まる位置
			pPlayer2->pos.z += 0.1f;								//ヘリの慣性
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE3;		//ヘリのプロペラを回転
		}
		if (g_CameraCount >= 180 && g_CameraCount <= 219)
		{//プレイヤーが落ちてきたらそのプレイヤーに視点をやる
			pPlayer2->pos.z += 3.8f;								//また進行させる
			g_Camera.posR.y -= 5;									//カメラを下に下げる
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//ヘリのプロペラを回転
		}
		if (g_CameraCount >= 220 && g_CameraCount <= 800)
		{//ヘリを前進させておく
			pPlayer2->pos.z += 3.8f;								//ヘリを進行させる
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//ヘリのプロペラを回転
		}
		//フレームカウント
		g_CameraCount++;
	}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(CAMERATYPE CameraType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	g_Camera.nType = CameraType;

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH
	(
		&g_Camera.mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		7500
	);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,&g_Camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
					   &g_Camera.posV,
					   &g_Camera.posR,
		               &g_Camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}
//=============================================================================
//	カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera;
}