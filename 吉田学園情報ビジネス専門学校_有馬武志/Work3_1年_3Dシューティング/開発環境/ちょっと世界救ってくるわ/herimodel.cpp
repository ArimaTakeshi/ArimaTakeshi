//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 有馬　武志
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanfエラー解除
#include <stdio.h>					//stdio
#include "herimodel.h"				//プレイヤー
#include "input.h"					//キーボード
#include "camera.h"					//カメラ
#include "shadow.h"					//影
#include "bullet.h"					//弾
#include "effect.h"					//エフェクト
#include "object.h"					//オブジェクト
#include "score.h"					//スコア
#include "game.h"					//ゲーム

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_ANGLE1	(0.0001f);		//プロペラの動き
#define MOVE_OBJECT (1000.0f);		//配置位置
#define MOVE_ANGLE2	(15.0f);		//角度
#define MOVE_SPEED	(2.5f);			//プロペラの回転スピード

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player2		g_Player2;				//プレイヤー
int			g_nCntTimePlayer2;		//プレイヤーカウンター

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
	g_Player2.pos = D3DXVECTOR3(0, 600, -1500);
	g_Player2.rot = D3DXVECTOR3(0, 0, 0);
	g_Player2.move = D3DXVECTOR3(0, 0, 0);

	//ファイル設定
	pFile = fopen(HERIFILE_NAME, "r");

	//プレイヤーの￥テキストデータの読み込み
	if (pFile != NULL)
	{
		//使うパーツ数
		fscanf(pFile, "%d", &g_Player2.nMaxPartsNum);	//読み込み
		//ファイル名
		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{
			fscanf(pFile, "%s", &g_Player2.aModel[nCntPlayer2].FileName[0]); //読み込み
		}

		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{//初期値と向き
			fscanf(pFile, "%d", &g_Player2.aModel[nCntPlayer2].nIdxHeriParent);//読み込み
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriPos.x);//読み込み
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriPos.y);//読み込み
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriPos.z);//読み込み
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriRot.x);//読み込み
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriRot.y);//読み込み
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriRot.z);//読み込み
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
			&g_Player2.aModel[nCntPlayer2].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player2.aModel[nCntPlayer2].pBuffMatHeri,
			NULL,
			&g_Player2.aModel[nCntPlayer2].nNumMatHeri,
			&g_Player2.aModel[nCntPlayer2].pMeshHeri
		);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer2(void)
{
	for (int nCount = 0; nCount < MAX_HERIPARTS; nCount++)
	{
		// メッシュの開放
		if (g_Player2.aModel[nCount].pMeshHeri != NULL)
		{
			g_Player2.aModel[nCount].pMeshHeri->Release();
			g_Player2.aModel[nCount].pMeshHeri = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_HERIPARTS; nCount++)
	{
		// マテリアルの開放
		if (g_Player2.aModel[nCount].pBuffMatHeri != NULL)
		{
			g_Player2.aModel[nCount].pBuffMatHeri->Release();
			g_Player2.aModel[nCount].pBuffMatHeri = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer2(void)
{
	//モードのポインタ
	MODE pMode = *GetMode();

	if (pMode == MODE_GAME)
	{
		//移動
		g_Player2.pos.z += MOVE_SPEED;

		if (g_Player2.pos.z == 1500)
		{
			g_Player2.pos = D3DXVECTOR3(0, 600, -1500);
		}

		//プロペラの回転
		g_Player2.aModel[1].InitHeriRot.y += MOVE_ANGLE2;
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
	for (int nCntParts = 0; nCntParts < MAX_HERIPARTS; nCntParts++)
	{
		if (g_Player2.aModel[nCntParts].nIdxHeriParent < 0)
		{//親モデル
			mtxParent = g_Player2.mtxWorldPlayer2;
		}
		else
		{//子モデル
			mtxParent = g_Player2.aModel[g_Player2.aModel[nCntParts].nIdxHeriParent].mtxWorldHeri;
		}
		{//親モデル
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player2.aModel[nCntParts].mtxWorldHeri);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player2.aModel[nCntParts].InitHeriRot.y,
				g_Player2.aModel[nCntParts].InitHeriRot.x,
				g_Player2.aModel[nCntParts].InitHeriRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&mtxRot
			);
			// 位置を反映
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player2.aModel[nCntParts].InitHeriPos.x,
				g_Player2.aModel[nCntParts].InitHeriPos.y,
				g_Player2.aModel[nCntParts].InitHeriPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&mtxParent
			);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player2.aModel[nCntParts].mtxWorldHeri);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Player2.aModel[nCntParts].pBuffMatHeri->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player2.aModel[nCntParts].nNumMatHeri; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャをNULLにする
				pDevice->SetTexture(0, NULL);

				//pDevice->SetTexture(0, g_Player22.nNumMatPlayer2);

				// プレイヤー(パーツ)の描画
				g_Player2.aModel[nCntParts].pMeshHeri->DrawSubset(nCntMat);
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
