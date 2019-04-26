//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 有馬　武志
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanfエラー解除
#include <stdio.h>					//stdio
#include "player.h"					//プレイヤー
#include "input.h"					//キーボード
#include "camera.h"					//カメラ
#include "shadow.h"					//影
#include "bullet.h"					//弾
#include "effect.h"					//エフェクト
#include "object.h"					//オブジェクト
#include "score.h"					//スコア
#include "sound.h"					//サウンド

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

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player		g_Player;							//プレイヤー
int			g_nIdxShadow;						//どの影を使っているか
int			g_nCntTimePlayer;					//プレイヤーカウンター

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルのポインタ
	FILE *pFile;
	//プレイヤーカウンター
	int nCntPlayer;

	// 位置・向きの初期設定
	g_Player.pos = D3DXVECTOR3(0, 20, 0);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0);

	//ファイル設定
	pFile = fopen(FILE_NAME, "r");

	//プレイヤーの￥テキストデータの読み込み
	if (pFile != NULL)
	{
		//使うパーツ数
		fscanf(pFile, "%d", &g_Player.nMaxPartsNum);	//読み込み
		//ファイル名
		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{
			fscanf(pFile, "%s", &g_Player.aModel[nCntPlayer].FileName[0]); //読み込み
		}

		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{//初期値と向き
			fscanf(pFile, "%d", &g_Player.aModel[nCntPlayer].nIdxModelParent);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.x);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.y);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.z);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.x);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.y);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.z);//読み込み
		}

		//ファイル読み込み
		fscanf(pFile, "%d", &g_Player.nMaxAnimNum);

		for (int nCntPlayerAnim = 0; nCntPlayerAnim < g_Player.nMaxPartsNum; nCntPlayerAnim++)
		{
			//フレーム数
			fscanf(pFile, "%d", &g_Player.nAnimloop[nCntPlayerAnim]);
			//キー数
			fscanf(pFile, "%d", &g_Player.nAnimKey[nCntPlayerAnim]);

			for (int nCntPlayerAnimKey = 0; nCntPlayerAnimKey < g_Player.nAnimKey[nCntPlayerAnim]; nCntPlayerAnimKey++)
			{
				fscanf(pFile, "%d", &g_Player.nAnimfram[nCntPlayerAnim][nCntPlayerAnimKey]);//読み込み

				for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
				{
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//読み込み
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
	for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX
		(
			&g_Player.aModel[nCntPlayer].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntPlayer].pBuffMatModel,
			NULL,
			&g_Player.aModel[nCntPlayer].nNumMatModel,
			&g_Player.aModel[nCntPlayer].pMeshModel
		);
	}

	////モデル親とコモドのposの位置
	//g_Player.aModel[0].posModel = D3DXVECTOR3(0, 0, 0);			//体
	//g_Player.aModel[1].posModel = D3DXVECTOR3(0, 15, 0);			//頭
	//g_Player.aModel[2].posModel = D3DXVECTOR3(-6, 12, 0.0);		//右腕
	//g_Player.aModel[3].posModel = D3DXVECTOR3(-10, 0, 0);			//右手
	//g_Player.aModel[4].posModel = D3DXVECTOR3(6, 12, 0.0); 		//左腕
	//g_Player.aModel[5].posModel = D3DXVECTOR3(10, 0, 0.0);		//左手
	//g_Player.aModel[6].posModel = D3DXVECTOR3(-4, 0, 0);			//右もも
	//g_Player.aModel[7].posModel = D3DXVECTOR3(0, -10, 0);			//右足
	//g_Player.aModel[8].posModel = D3DXVECTOR3(4, 0, 0);			//左もも
	//g_Player.aModel[9].posModel = D3DXVECTOR3(0, -10, 0);			//左足

	//影の初期化設定
	g_nIdxShadow = SetShadow(g_Player.pos,g_Player.rot,15,15);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// メッシュの開放
		if (g_Player.aModel[nCount].pMeshModel != NULL)
		{
			g_Player.aModel[nCount].pMeshModel->Release();
			g_Player.aModel[nCount].pMeshModel = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// マテリアルの開放
		if (g_Player.aModel[nCount].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCount].pBuffMatModel->Release();
			g_Player.aModel[nCount].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//カメラの情報
	Camera *pCamera = GetCamera();
	
	//エフェクト
	SetBulletEffect(g_Player.pos + D3DXVECTOR3(sinf(g_Player.rot.y + D3DX_PI * 0.5f) * 9.0f,0.0f, cosf(g_Player.rot.y + D3DX_PI * 0.5f) * 9.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_BULLET, 2.0f, 10,0);
	SetBulletEffect(g_Player.pos + D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI * 0.5f) * 9.0f, 0.0f, cosf(g_Player.rot.y - D3DX_PI * 0.5f) * 9.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_BULLET, 2.0f, 10,0);

	//前回の位置を保存
	g_Player.posOld = g_Player.pos;

	float nSpeed = 5.0f;	//速度
	//float fDiffAngle;

	//壁のあたり判定
	if (g_Player.pos.z >= 390)
	{
		g_Player.pos.z = 390;
	}
	if (g_Player.pos.z <= -390)
	{
		g_Player.pos.z = -390;
	}
	if (g_Player.pos.x >= 390)
	{
		g_Player.pos.x = 390;
	}
	if (g_Player.pos.x <= -390)
	{
		g_Player.pos.x = -390;
	}

	//
	//
	//
	//fDiffAngle = (pCamera->fAngle + D3DX_PI) - g_Player.rot.y;
	//if (fDiffAngle > D3DX_PI)
	//{
	//	fDiffAngle -= D3DX_PI * 2.0;
	//}
	//else if (fDiffAngle < -D3DX_PI)
	//{
	//	fDiffAngle += D3DX_PI * 2.0;
	//}

	//g_Player.rot.y += fDiffAngle * 0.4f;

	//if (g_Player.rot.y > D3DX_PI)
	//{
	//	fDiffAngle -= D3DX_PI * 2.0;
	//}
	//else if (g_Player.rot.y < -D3DX_PI)
	//{
	//	fDiffAngle += D3DX_PI * 2.0;
	//}

	//移動処理
	if (GetKeyboardPress(DIK_UP) == true)
	{//矢印の上							↓上移動
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//矢印の下							 ↓上移動
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//その方向に向く
			g_Player.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//矢印の右							↓ 右移動
		g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//その方向に向く
		g_Player.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);
	}
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{//矢印の左							 ↓ 左移動
		g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//その方向に向く
		g_Player.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);
	}
	if (GetKeyboardPress(DIK_T) == true)
	{//上移動			
		g_Player.pos.y += 0.3f;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//下移動						
		g_Player.pos.y -= 0.3f;
	}

	//弾の発射
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//任意のキー（SPACEキー）を押した場合
		SetBullet(g_Player.pos, g_Player.rot,D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI) * 3.0f, 0.0f, cosf(g_Player.rot.y - D3DX_PI) * 3.0f));
		PlaySound(SOUND_LABEL_SE_SHOOT);
	}

	//位置を移動に代入
	g_Player.pos += g_Player.move;

	//慣性をつける
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

	//影がついてくる
	SetPositionShadow(g_nIdxShadow, g_Player.pos,g_Player.rot);

	//あたり判定
	CollisionObject(&g_Player.pos, &g_Player.posOld, &g_Player.move);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;						//

	{//プレイヤー
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);
		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);
		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);
		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);
	}
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].nIdxModelParent < 0)
		{//親モデル
			mtxParent = g_Player.mtxWorldPlayer;
		}
		else
		{//子モデル
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorldModel;
		}
		{//親モデル
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorldModel);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player.aModel[nCntParts].InitRot.y,
				g_Player.aModel[nCntParts].InitRot.x,
				g_Player.aModel[nCntParts].InitRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxRot
			);
			// 位置を反映
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player.aModel[nCntParts].InitPos.x,
				g_Player.aModel[nCntParts].InitPos.y,
				g_Player.aModel[nCntParts].InitPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxParent
			);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorldModel);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMatModel; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャをNULLにする
				pDevice->SetTexture(0, NULL);

				//pDevice->SetTexture(0, g_Player.nNumMatPlayer);

				// プレイヤー(パーツ)の描画
				g_Player.aModel[nCntParts].pMeshModel->DrawSubset(nCntMat);
			}
			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================================================================================================
// プレイヤーの取得処理
//=========================================================================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}
