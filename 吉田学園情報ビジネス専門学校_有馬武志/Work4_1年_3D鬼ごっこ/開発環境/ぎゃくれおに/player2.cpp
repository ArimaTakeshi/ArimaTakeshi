//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 有馬　武志　＆　箱崎
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanfエラー解除
#include <stdio.h>					//stdio
#include "player2.h"				//プレイヤー
#include "input.h"					//キーボード
#include "camera.h"					//カメラ
#include "shadow.h"					//影
#include "bullet.h"					//弾
#include "effect.h"					//エフェクト
#include "object.h"					//オブジェクト
#include "sound.h"					//サウンド
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define MODEL_NAME			"data\\MODEL\\airplane000.x"	//読み込むテクスチャファイル
//#define MODEL_NAME			"data\\MODEL\\00_body.x"		//読み込むテクスチャファイル
//#define MODEL_NAME2			"data\\MODEL\\01_head.x"		//読み込むテクスチャファイル
//#define MODEL_NAME3			"data\\MODEL\\02_armR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME4			"data\\MODEL\\03_handR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME5			"data\\MODEL\\04_armL.x"		//読み込むテクスチャファイル
//#define MODEL_NAME6			"data\\MODEL\\05_handL.x"		//読み込むテクスチャファイル
//#define MODEL_NAME7			"data\\MODEL\\06_legR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME8			"data\\MODEL\\07_footR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME9			"data\\MODEL\\08_legL.x"		//読み込むテクスチャファイル
//#define MODEL_NAME10			"data\\MODEL\\09_footL.x"		//読み込むテクスチャファイル
#define PLAYER2_SPEED			(5.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player2		g_Player2;							//プレイヤー
int			g_nCntTimePlayer2;					//プレイヤーカウンター

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルのポインタ
	FILE *pFile;
	//プレイヤーカウンター
	int nCntPlayer2;

	// 位置・向きの初期設定
	g_Player2.pos = D3DXVECTOR3(200, 20, 40);
	g_Player2.rot = D3DXVECTOR3(0, 0, 0);
	g_Player2.move = D3DXVECTOR3(0, 0, 0);
	g_Player2.bUse = true;
	g_Player2.bLand = true;
	g_Player2.nCntPlayer2 = 1;

	//ファイル設定
	pFile = fopen(FILE_NAME_PLAYER2, "r");

	//プレイヤーの￥テキストデータの読み込み
	if (pFile != NULL)
	{
		//使うパーツ数
		fscanf(pFile, "%d", &g_Player2.nMaxPartsNum);	//読み込み
		//ファイル名
		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{
			fscanf(pFile, "%s", &g_Player2.aModelPlayer2[nCntPlayer2].FileName[0]); //読み込み
		}

		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{//初期値と向き
			fscanf(pFile, "%d", &g_Player2.aModelPlayer2[nCntPlayer2].nIdxModelPlayer2Parent);	//読み込み
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitPos.x);				//読み込み
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitPos.y);				//読み込み
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitPos.z);				//読み込み
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitRot.x);				//読み込み
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitRot.y);				//読み込み
			fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].InitRot.z);				//読み込み
		}

		//ファイル読み込み
		fscanf(pFile, "%d", &g_Player2.nMaxAnimNum);

		for (int nCntPlayer2Anim = 0; nCntPlayer2Anim < g_Player2.nMaxPartsNum; nCntPlayer2Anim++)
		{
			//フレーム数
			fscanf(pFile, "%d", &g_Player2.nAnimloop[nCntPlayer2Anim]);
			//キー数
			fscanf(pFile, "%d", &g_Player2.nAnimKey[nCntPlayer2Anim]);

			for (int nCntPlayer2AnimKey = 0; nCntPlayer2AnimKey < g_Player2.nAnimKey[nCntPlayer2Anim]; nCntPlayer2AnimKey++)
			{
				fscanf(pFile, "%d", &g_Player2.nAnimfram[nCntPlayer2Anim][nCntPlayer2AnimKey]);//読み込み

				for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
				{
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].posAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].x);		//読み込み
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].posAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].y);		//読み込み
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].posAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].z);		//読み込み
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].rotAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].x);		//読み込み
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].rotAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].y);		//読み込み
					fscanf(pFile, "%f", &g_Player2.aModelPlayer2[nCntPlayer2].rotAnim[nCntPlayer2Anim][nCntPlayer2AnimKey].z);		//読み込み
				}
			}
		}

		fclose(pFile);	//ファイルを閉じる
	}
	else
	{
		MessageBox(0, "セーブファイルのチェックに失敗!", "警告", MB_ICONWARNING);
	}

	//xファイルの読み込み
	for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX
		(
			&g_Player2.aModelPlayer2[nCntPlayer2].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player2.aModelPlayer2[nCntPlayer2].pBuffMatModelPlayer2,
			NULL,
			&g_Player2.aModelPlayer2[nCntPlayer2].nNumMatModelPlayer2,
			&g_Player2.aModelPlayer2[nCntPlayer2].pMeshModelPlayer2
		);
	}

	//影の初期化設定
	g_Player2.nIdxShadow2 = SetShadow(g_Player2.pos,g_Player2.rot,15,15);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer2(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// メッシュの開放
		if (g_Player2.aModelPlayer2[nCount].pMeshModelPlayer2 != NULL)
		{
			g_Player2.aModelPlayer2[nCount].pMeshModelPlayer2->Release();
			g_Player2.aModelPlayer2[nCount].pMeshModelPlayer2 = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// マテリアルの開放
		if (g_Player2.aModelPlayer2[nCount].pBuffMatModelPlayer2 != NULL)
		{
			g_Player2.aModelPlayer2[nCount].pBuffMatModelPlayer2->Release();
			g_Player2.aModelPlayer2[nCount].pBuffMatModelPlayer2 = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer2(void)
{
	//カメラの情報
	Camera *pCamera = GetCamera();

	//鬼の取得
	Enemy *pEnemy = GetEnemy();

	//フレームカウント
	g_nCntTimePlayer2++;

	//前回の位置を保存
	g_Player2.posOld = g_Player2.pos;

	float nSpeed = 5.0f;	//速度
	//float fDiffAngle;

	//壁のあたり判定
	if (g_Player2.pos.z >= 200)
	{//上
		g_Player2.pos.z = 200;
	}
	if (g_Player2.pos.z <= -4200)
	{//下
		g_Player2.pos.z = -4200;
	}
	if (g_Player2.pos.x >= 4200)
	{//右
		g_Player2.pos.x = 4200;
	}
	if (g_Player2.pos.x <= -200)
	{//左
		g_Player2.pos.x = -200;
	}

	//移動処理
	if (GetKeyboardPress(DIK_U) == true)
	{//矢印の上							↓上移動
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_Player2.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player2.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_H) == true)
		{
			g_Player2.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player2.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else
		{
			g_Player2.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player2.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
	}
	else if (GetKeyboardPress(DIK_J) == true)
	{//矢印の下							 ↓上移動
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_Player2.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player2.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_H) == true)
		{
			g_Player2.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player2.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
		else
		{
			g_Player2.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player2.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player2.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);

			if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
			{
				g_Player2.nAnimnow = PLAYER2ANIM_WALK;
				g_nCntTimePlayer2 = 0;
				g_Player2.nAnimKeynow = 0;
			}
		}
	}
	else if (GetKeyboardPress(DIK_K) == true)
	{//矢印の右							↓ 右移動
		g_Player2.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player2.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//その方向に向く
		g_Player2.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);

		if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_WALK;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}
	else if (GetKeyboardPress(DIK_H) == true)
	{//矢印の左							 ↓ 左移動
		g_Player2.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player2.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//その方向に向く
		g_Player2.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);

		if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_WALK;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}
	else if (GetJoyPadPress(DIJS_BUTTON_10, 1) == true || GetJoyPadPress(DIJS_BUTTON_11, 1) == true || GetJoyPadPress(DIJS_BUTTON_12, 1) == true || GetJoyPadPress(DIJS_BUTTON_13, 1) == true)
	{//ジョイコン
		g_Player2.pos.x -= sinf(pCamera->fAngle - GetJotPadRightStick(1)) * PLAYER2_SPEED;
		g_Player2.pos.z -= cosf(pCamera->fAngle - GetJotPadRightStick(1)) * PLAYER2_SPEED;

		g_Player2.rot.y = pCamera->fAngle - GetJotPadRightStick(1);

		if (g_Player2.nAnimnow != PLAYER2ANIM_WALK)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_WALK;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}
	else
	{
		if (g_Player2.nAnimnow != PLAYER2ANIM_NEUTRAL)
		{
			g_Player2.nAnimnow = PLAYER2ANIM_NEUTRAL;
			g_nCntTimePlayer2 = 0;
			g_Player2.nAnimKeynow = 0;
		}
	}

	//位置を移動に代入
	g_Player2.pos += g_Player2.move;

	//慣性をつける
	g_Player2.move.x += (0.0f - g_Player2.move.x) * 0.2f;
	g_Player2.move.z += (0.0f - g_Player2.move.z) * 0.2f;

	//影がついてくる
	SetPositionShadow(g_Player2.nIdxShadow2, g_Player2.pos,g_Player2.rot);

	//あたり判定
	CollisionObject(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move);
	CollisionEnemy2(&g_Player2.pos, &g_Player2.posOld, &g_Player2.move);

	//差分のローカル変数
	float fDes;
	float frac;


	//キーを進める！
	if (g_nCntTimePlayer2 % g_Player2.nAnimfram[g_Player2.nAnimnow][g_Player2.nAnimKeynow] == 0)
	{
		g_nCntTimePlayer2 = 0;
		g_Player2.nAnimKeynow = (g_Player2.nAnimKeynow + 1) % g_Player2.nAnimKey[g_Player2.nAnimnow];
	}

	//差分の計算
	frac = (g_Player2.nAnimfram[g_Player2.nAnimnow][g_Player2.nAnimKeynow] - g_nCntTimePlayer2) * 1.0f;

	//アニメーション
	for (int nCntPlayer2Anim = 0; nCntPlayer2Anim < g_Player2.nMaxPartsNum; nCntPlayer2Anim++)
	{
		//===================
		// Xの角度
		//===================

		//目的の角度をしらべる
		g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotAnim[g_Player2.nAnimnow][g_Player2.nAnimKeynow];

		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x -= D3DX_PI * 2.0f;
		}
		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.x - g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x;

		//差分の調節
		if (fDes > D3DX_PI)
		{
			fDes -= D3DX_PI * 2.0f;
		}
		if (fDes > D3DX_PI)
		{
			fDes += D3DX_PI * 2.0f;
		}

		//現在の向きの設定
		g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x += fDes / frac;

		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x -= D3DX_PI * 2.0f;
		}
		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.x += D3DX_PI * 2.0f;
		}


		//===================
		// Yの角度
		//===================

		//y目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y -= D3DX_PI * 2.0f;
		}
		//y目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.y - g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y;

		//差分の調節
		if (fDes > D3DX_PI)
		{
			fDes -= D3DX_PI * 2.0f;
		}
		if (fDes > D3DX_PI)
		{
			fDes += D3DX_PI * 2.0f;
		}

		//現在の向きの設定
		g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y += fDes / frac;

		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y -= D3DX_PI * 2.0f;
		}
		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.y += D3DX_PI * 2.0f;
		}

		//===================
		// Zの角度
		//===================

		//z目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z -= D3DX_PI * 2.0f;
		}
		//z目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z += D3DX_PI * 2.0f;
		}

		//
		fDes = g_Player2.aModelPlayer2[nCntPlayer2Anim].rotDest.z - g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z;

		//差分の調節
		if (fDes > D3DX_PI)
		{
			fDes -= D3DX_PI * 2.0f;
		}
		if (fDes > D3DX_PI)
		{
			fDes += D3DX_PI * 2.0f;
		}

		//現在の向きの設定
		g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z += fDes / frac;

		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z > D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z -= D3DX_PI * 2.0f;
		}
		//x目的の位置の調整
		if (g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z < -D3DX_PI)
		{
			g_Player2.aModelPlayer2[nCntPlayer2Anim].InitRot.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;						//

	{//プレイヤー
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player2.mtxWorldPlayer2);
		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.rot.y, g_Player2.rot.x, g_Player2.rot.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorldPlayer2, &g_Player2.mtxWorldPlayer2, &mtxRot);
		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player2.pos.x, g_Player2.pos.y, g_Player2.pos.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorldPlayer2, &g_Player2.mtxWorldPlayer2, &mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player2.mtxWorldPlayer2);
	}
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player2.aModelPlayer2[nCntParts].nIdxModelPlayer2Parent < 0)
		{//親モデル
			mtxParent = g_Player2.mtxWorldPlayer2;
		}
		else
		{//子モデル
			mtxParent = g_Player2.aModelPlayer2[g_Player2.aModelPlayer2[nCntParts].nIdxModelPlayer2Parent].mtxWorldModelPlayer2;
		}
		{//親モデル
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player2.aModelPlayer2[nCntParts].InitRot.y,
				g_Player2.aModelPlayer2[nCntParts].InitRot.x,
				g_Player2.aModelPlayer2[nCntParts].InitRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&mtxRot
			);
			// 位置を反映
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player2.aModelPlayer2[nCntParts].InitPos.x,
				g_Player2.aModelPlayer2[nCntParts].InitPos.y,
				g_Player2.aModelPlayer2[nCntParts].InitPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2,
				&mtxParent
			);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player2.aModelPlayer2[nCntParts].mtxWorldModelPlayer2);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player2.aModelPlayer2[nCntParts].pBuffMatModelPlayer2->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player2.aModelPlayer2[nCntParts].nNumMatModelPlayer2; nCntMat++)
			{
				if (g_Player2.bUse == true)
				{
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					// テクスチャをNULLにする
					pDevice->SetTexture(0, NULL);

					//pDevice->SetTexture(0, g_Player2.nNumMatPlayer2);

					// プレイヤー(パーツ)の描画
					g_Player2.aModelPlayer2[nCntParts].pMeshModelPlayer2->DrawSubset(nCntMat);
				}
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================================================================================================
// プレイヤーの取得処理
//=========================================================================================================================
Player2 *GetPlayer2(void)
{
	return &g_Player2;
}
