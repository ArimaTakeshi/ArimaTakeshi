//=============================================================================
//
// オブジェクト処理 [model.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "object.h"		//オブジェクト
#include "input.h"		//キーボード
#include "camera.h"		//カメラ
#include "bullet.h"		//弾
#include "player.h"		//プレイヤー
#include "main.h"		//ゲーム

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBJECT_NAME			"data\\MODEL\\matimati.x"		//読み込むテクスチャファイル
#define OBJECT_NAME1		"data\\MODEL\\hikouki4.x"		//読み込むテクスチャファイル
#define OBJECT_NAME2		"data\\MODEL\\銃.x"				//読み込むテクスチャファイル
#define OBJECT_SPEED		(1.0f)							//オブジェクトスピード
#define MAX_OBJECT			(3)								//オブジェクトの最大数
#define MOVE_ANGLE1			(0.001f)
#define MOVE_LEG			(1200.0f)
#define MOVE_SPEED			(0.0009f)
#define MAX_TEX				(40)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object g_Object[MAX_OBJECT];											//オブジェクト
LPDIRECT3DTEXTURE9				g_pTextureObject[MAX_TEX] = {};			//テクスチャへのポインタ
float g_Objectf;

//=============================================================================
// 初期化処理
//=============================================================================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[0].pBuffMatObject,
		NULL,
		&g_Object[0].nNumMatObject,
		&g_Object[0].pMeshObject
	);

	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[1].pBuffMatObject,
		NULL,
		&g_Object[1].nNumMatObject,
		&g_Object[1].pMeshObject
	);

	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[2].pBuffMatObject,
		NULL,
		&g_Object[2].nNumMatObject,
		&g_Object[2].pMeshObject
	);

	//D3DXMATERIAL *pMat;
	//pMat = (D3DXMATERIAL*)g_Object[1].pBuffMatObject->GetBufferPointer();

	//D3DXCreateTextureFromFile
	//(//1枚目の画像
	//	pDevice,
	//	pMat[0].pTextureFilename,
	//	&g_pTextureObject[0]
	//);
	//D3DXCreateTextureFromFile
	//(//1枚目の画像
	//	pDevice,
	//	pMat[0].pTextureFilename,
	//	&g_pTextureObject[1]
	//);

	D3DXMATERIAL *pMat;
	D3DMATERIAL9 *pMatDef;

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		pMat = (D3DXMATERIAL*)g_Object[nCount].pBuffMatObject->GetBufferPointer();
		pMatDef = new D3DMATERIAL9[g_Object[nCount].nNumMatObject];
		g_Object[nCount].pMeshTextures = new LPDIRECT3DTEXTURE9[g_Object[nCount].nNumMatObject];

		for (DWORD tex = 0; tex < g_Object[nCount].nNumMatObject; tex++)
		{
			pMatDef[tex] = pMat[tex].MatD3D;
			pMatDef[tex].Ambient = pMatDef[tex].Diffuse;
			g_Object[nCount].pMeshTextures[tex] = NULL;
			if (pMat[tex].pTextureFilename != NULL &&
				lstrlen(pMat[tex].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pMat[tex].pTextureFilename,
					&g_Object[nCount].pMeshTextures[tex])))
				{
					MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
				}
			}
		}
	}

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		int nNumVtx;		//頂点数
		DWORD sizeFVF;		//頂点フォーマットのサイズ
		BYTE *pVtxBuff;		//頂点バッファへのポインタ

		// 位置・向きの初期設定
		g_Object[nCount].pos = D3DXVECTOR3(0, 0, 0);
		g_Object[nCount].rot = D3DXVECTOR3(0, 0, 0);
		g_Object[nCount].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
		g_Object[nCount].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
		g_Object[nCount].bUse = false;
		g_Objectf = 0.0f;

		//頂点数を取得
		nNumVtx = g_Object[nCount].pMeshObject->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Object[nCount].pMeshObject->GetFVF());

		//頂点バッファのロック
		g_Object[nCount].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			//範囲指定
			//最大値
			if (vtx.x > g_Object[nCount].VtxMaxModel.x)
			{
				g_Object[nCount].VtxMaxModel.x = vtx.x;
			}
			if (vtx.y > g_Object[nCount].VtxMaxModel.y)
			{
				g_Object[nCount].VtxMaxModel.y = vtx.y;
			}
			if (vtx.z > g_Object[nCount].VtxMaxModel.z)
			{
				g_Object[nCount].VtxMaxModel.z = vtx.z;
			}
			//最小値
			if (vtx.x < g_Object[nCount].VtxMinModel.x)
			{
				g_Object[nCount].VtxMinModel.x = vtx.x;
			}
			if (vtx.y < g_Object[nCount].VtxMinModel.y)
			{
				g_Object[nCount].VtxMinModel.y = vtx.y;
			}
			if (vtx.z < g_Object[nCount].VtxMinModel.z)
			{
				g_Object[nCount].VtxMinModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//サイズ文のポインタを進める
		}
		//頂点バッファのアンロック
		g_Object[nCount].pMeshObject->UnlockVertexBuffer();
	}
	g_Object[1].rot.y = 0.0f;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObject(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// メッシュの開放
		if (g_Object[nCount].pMeshObject != NULL)
		{
			g_Object[nCount].pMeshObject->Release();
			g_Object[nCount].pMeshObject = NULL;
		}
		// マテリアルの開放
		if (g_Object[nCount].pBuffMatObject != NULL)
		{
			g_Object[nCount].pBuffMatObject->Release();
			g_Object[nCount].pBuffMatObject = NULL;
		}

		//テクスチャ
		for (DWORD nTex = 0; nTex < g_Object[nCount].nNumMatObject; nTex++)
		{
			if (g_Object[nCount].pMeshTextures[nTex] != NULL)
			{
				g_Object[nCount].pMeshTextures[nTex]->Release();
				g_Object[nCount].pMeshTextures[nTex] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObject(void)
{
	//モードのポインタ
	MODE pMode = *GetMode();
	DIMOUSESTATE2 pMouse = GetMousePointer();
	float fRot;
	if (pMode == MODE_GAME)
	{//ゲームの場合

		//カメラのポインタ
		Camera *pCamera = GetCamera();

		//モデルをカメラに代入
		g_Object[2].pos = pCamera[0].posV;

		//カメラの向きをオブジェクトに代入
	/*	g_Object[2].rot = pCamera.rot;
		g_Objectf += (pMouse.lY / 500.0f);*/

		fRot = atan2f(powf(pCamera[0].posR.y - pCamera[0].posV.y, 2), powf(pCamera[0].posR.x - pCamera[0].posV.x, 2) + powf(pCamera[0].posR.z - pCamera[0].posV.z, 2));
		g_Object[2].rot.x = fRot;

		//銃のセット
		//SetObject(pCamera[0].posV, pCamera[0].rot);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算洋間鳥kk数
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object[nCount].mtxWorldObject);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCount].rot.y, g_Object[nCount].rot.x, g_Object[nCount].rot.z);

		D3DXMatrixMultiply(&g_Object[nCount].mtxWorldObject, &g_Object[nCount].mtxWorldObject, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Object[nCount].pos.x, g_Object[nCount].pos.y, g_Object[nCount].pos.z);

		D3DXMatrixMultiply(&g_Object[nCount].mtxWorldObject, &g_Object[nCount].mtxWorldObject, &mtxTrans);

		// ワールドマトリックスの設3定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCount].mtxWorldObject);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Object[nCount].pBuffMatObject->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Object[nCount].nNumMatObject; nCntMat++)
		{
			if (g_Object[nCount].bUse == true)
			{//ビルボードがある場合
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャをNULLにする
				pDevice->SetTexture(0, g_Object[nCount].pMeshTextures[nCntMat]);

				// オブジェクト(パーツ)の描画
				g_Object[nCount].pMeshObject->DrawSubset(nCntMat);
			}
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=========================================================================================================================
// オブジェクトの取得処理
//=========================================================================================================================
Object *GetObject(void)
{
	return &g_Object[0];
}
//=========================================================================================================================
// オブジェクトのあたり判定
//=========================================================================================================================
void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECT; nCntBlock++)
	{//
		if (pPos->x > g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x && pPos->x < g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x)
		{//ｘ範囲確認
			if (pPosOld->z >= g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z && g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z > pPos->z)
			{//最大のあたり判定
				pPos->z = g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z;
				pMove->z = 0;
				pMove->x = 0;
			}
			else if (pPosOld->z <= g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z && g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z < pPos->z)
			{//最小のあたる判定
				pPos->z = g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z;
				pMove->z = 0;
				pMove->x = 0;
			}
		}
		if (pPos->z > g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z && pPos->z < g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z)
		{//z範囲確認
			if (pPosOld->x >= g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x && g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x > pPos->x)
			{//最大のあたり判定
				pPos->x = g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x;
				pMove->z = 0;
				pMove->x = 0;
			}
			else if (pPosOld->x <= g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x && g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x < pPos->x)
			{//最小のあたる判定
				pPos->x = g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x;
				pMove->z = 0;
				pMove->x = 0;
			}
		}
	}
}
//=========================================================================================================================
// アイテムのあたり判定
//=========================================================================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Camera *pCamera = GetCamera();

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{//全テクスチャのカウント
		if (g_Object[nCount].bUse == false)
		{
			g_Object[nCount].pos = pos;
			g_Object[nCount].rot = rot;
			g_Object[nCount].bUse = true;
		break;
		}
	}
}
