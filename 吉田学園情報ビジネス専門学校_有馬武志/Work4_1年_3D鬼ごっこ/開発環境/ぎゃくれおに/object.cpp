//=============================================================================
//
// モデル処理 [Object.cpp]
// Author : 有馬 武志　＆　内山　＆　箱崎
//
//=============================================================================
#include "object.h"		//オブジェクト
#include "input.h"		//キーボード
#include "camera.h"		//カメラ
#include "shadow.h"		//影
#include "player.h"		//プレイヤー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define OBJECT_NAME			"data\\MODEL\\ビル200.x"		//読み込むテクスチャファイル
#define OBJECT_NAME1		"data\\MODEL\\ビル400.x"		//読み込むテクスチャファイル
#define OBJECT_NAME2		"data\\MODEL\\ビル600.x"		//読み込むテクスチャファイル
#define OBJECT_NAME3		"data\\MODEL\\信号(下).x"		//読み込むテクスチャファイル
#define OBJECT_NAME4		"data\\MODEL\\街灯(下).x"		//読み込むテクスチャファイル
#define OBJECT_NAME5		"data\\MODEL\\ダンボール.x"		//読み込むテクスチャファイル
#define OBJECT_NAME6		"data\\MODEL\\トラック.x"		//読み込むテクスチャファイル
#define OBJECT_NAME7		"data\\MODEL\\木(下).x"			//読み込むテクスチャファイル
#define OBJECT_NAME8		"data\\MODEL\\自販機.x"			//読み込むテクスチャファイル
#define OBJECT_NAME9		"data\\MODEL\\ゴミ箱.x"			//読み込むテクスチャファイル滑り台.x
#define OBJECT_NAME10		"data\\MODEL\\滑り台.x"			//読み込むテクスチャファイル滑り台.x
#define MAX_TEX				(40)							//オブジェクトのテクスチャ最大数
#define MAX_OBJECT			(427)							//オブジェクトの最大数
#define MAX_VARIATION		(11)							//オブジェクトの種類
#define PULS				(20)							//あたり反t寧		
//*****************************************************************************
// グローバル変数
//*****************************************************************************
Object g_Object[MAX_OBJECT];

//=============================================================================
// 初期化処理
//=============================================================================
void InitObject(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[0].pBuffMatObject,
		NULL, &g_Object[0].nNumMatObject,
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
		NULL, &g_Object[2].nNumMatObject,
		&g_Object[2].pMeshObject
	);
	// Xファイルの読み込み	
	D3DXLoadMeshFromX
	(
		OBJECT_NAME3,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[3].pBuffMatObject,
		NULL, &g_Object[3].nNumMatObject,
		&g_Object[3].pMeshObject
	);
	// Xファイルの読み込み	OBJECT_NAME5
	D3DXLoadMeshFromX
	(
		OBJECT_NAME4,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[4].pBuffMatObject,
		NULL, &g_Object[4].nNumMatObject,
		&g_Object[4].pMeshObject
	);

	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME5,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[5].pBuffMatObject,
		NULL, &g_Object[5].nNumMatObject,
		&g_Object[5].pMeshObject
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME6,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[6].pBuffMatObject,
		NULL, &g_Object[6].nNumMatObject,
		&g_Object[6].pMeshObject
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME7,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[7].pBuffMatObject,
		NULL, &g_Object[7].nNumMatObject,
		&g_Object[7].pMeshObject
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME8,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[8].pBuffMatObject,
		NULL, &g_Object[8].nNumMatObject,
		&g_Object[8].pMeshObject
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME9,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[9].pBuffMatObject,
		NULL, &g_Object[9].nNumMatObject,
		&g_Object[9].pMeshObject
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(
		OBJECT_NAME10,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[10].pBuffMatObject,
		NULL, &g_Object[10].nNumMatObject,
		&g_Object[10].pMeshObject
	);
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 *pMatDef;

	//テクスチャをつける
	for (int nCount = 0; nCount < MAX_VARIATION; nCount++)
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
					//MessageBox(NULL, "テクスチャの読み込みに失敗しました", NULL, MB_OK);
				}
			}
		}
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		g_Object[nCntObject].VtxMinObject = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_Object[nCntObject].VtxMaxObject = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_Object[nCntObject].pos = D3DXVECTOR3(0, 0, 0);
		g_Object[nCntObject].rot = D3DXVECTOR3(0, 0, 0);
		g_Object[nCntObject].bUse = false;
	}

	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマット7のサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ

	for (int nCount = 0; nCount < MAX_VARIATION; nCount++)
	{
		//頂点数を取得
		nNumVtx = g_Object[nCount].pMeshObject->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Object[nCount].pMeshObject->GetFVF());

		//頂点バッファをロック
		g_Object[nCount].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff; //頂点座標の代入

													   //範囲指定
													   //最大値
			if (vtx.x < g_Object[nCount].VtxMinObject.x)
			{
				g_Object[nCount].VtxMinObject.x = vtx.x;
			}
			if (vtx.z < g_Object[nCount].VtxMinObject.z)
			{
				g_Object[nCount].VtxMinObject.z = vtx.z;
			}
			if (vtx.y < g_Object[nCount].VtxMinObject.y)
			{
				g_Object[nCount].VtxMinObject.y = vtx.y;
			}
			//最小値
			if (vtx.x > g_Object[nCount].VtxMaxObject.x)
			{
				g_Object[nCount].VtxMaxObject.x = vtx.x;
			}
			if (vtx.z > g_Object[nCount].VtxMaxObject.z)
			{
				g_Object[nCount].VtxMaxObject.z = vtx.z;
			}
			if (vtx.y > g_Object[nCount].VtxMaxObject.y)
			{
				g_Object[nCount].VtxMaxObject.y = vtx.y;
			}
			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
		}
		//頂点バッファをアンロック
		g_Object[nCount].pMeshObject->UnlockVertexBuffer();
	}

	//オブジェクトの代入
	for (int nPotaCountObject = 11; nPotaCountObject < MAX_OBJECT; nPotaCountObject++)
	{
		if (nPotaCountObject < 100)
		{//オブジェクトビル２００
			g_Object[nPotaCountObject] = g_Object[0];
		}
		else if (nPotaCountObject < 110)
		{//オブジェクトビル４００
			g_Object[nPotaCountObject] = g_Object[1];
		}
		else if (nPotaCountObject < 114)
		{//オブジェクトビル６００
			g_Object[nPotaCountObject] = g_Object[2];
		}
		else if (nPotaCountObject < 117)
		{//オブジェクト信号(下)
			g_Object[nPotaCountObject] = g_Object[3];
		}
		else if (nPotaCountObject < 163)
		{//オブジェクト信号(下)
			g_Object[nPotaCountObject] = g_Object[4];
		}
		else if (nPotaCountObject < 291)
		{//ダンボール
			g_Object[nPotaCountObject] = g_Object[5];
		}
		else if (nPotaCountObject < 293)
		{//オブジェクト信号(下)
			g_Object[nPotaCountObject] = g_Object[6];
		}
		else if (nPotaCountObject < 404)
		{//オブジェクト信号(下)
			g_Object[nPotaCountObject] = g_Object[7];
		}
		else if (nPotaCountObject < 415)
		{//自販機
			g_Object[nPotaCountObject] = g_Object[8];
		}
		else if (nPotaCountObject < 426)
		{//自販機
			g_Object[nPotaCountObject] = g_Object[9];
		}
		else if (nPotaCountObject < 427)
		{//自販機
			g_Object[nPotaCountObject] = g_Object[10];
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitObject(void)
{
	for (int nCntObject = 0; nCntObject < MAX_VARIATION; nCntObject++)
	{
		// メッシュの開放
		if (g_Object[nCntObject].pMeshObject != NULL)
		{
			g_Object[nCntObject].pMeshObject->Release();
			g_Object[nCntObject].pMeshObject = NULL;
		}
		// マテリアルの開放
		if (g_Object[nCntObject].pBuffMatObject != NULL)
		{
			g_Object[nCntObject].pBuffMatObject->Release();
			g_Object[nCntObject].pBuffMatObject = NULL;
		}

		//テクスチャ
		for (DWORD nTex = 0; nTex < g_Object[nCntObject].nNumMatObject; nTex++)
		{
			if (g_Object[nCntObject].pMeshTextures[nTex] != NULL)
			{
				g_Object[nCntObject].pMeshTextures[nTex]->Release();
				g_Object[nCntObject].pMeshTextures[nTex] = NULL;
			}
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateObject(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	for (int nCount2 = 0; nCount2 < MAX_OBJECT; nCount2++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Object[nCount2].mtxWorldObject);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCount2].rot.y, g_Object[nCount2].rot.x, g_Object[nCount2].rot.z);

		D3DXMatrixMultiply(&g_Object[nCount2].mtxWorldObject, &g_Object[nCount2].mtxWorldObject, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, g_Object[nCount2].pos.x, g_Object[nCount2].pos.y, g_Object[nCount2].pos.z);

		D3DXMatrixMultiply(&g_Object[nCount2].mtxWorldObject, &g_Object[nCount2].mtxWorldObject, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCount2].mtxWorldObject);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Object[nCount2].pBuffMatObject->GetBufferPointer();

		for (int nCntMat = 0; nCntMat<(int)g_Object[nCount2].nNumMatObject; nCntMat++)
		{
			if (g_Object[nCount2].bUse == true)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_Object[nCount2].pMeshTextures[nCntMat]);
				// モデル(パーツ)の描画
				g_Object[nCount2].pMeshObject->DrawSubset(nCntMat);
			}
		}
		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// セットモデル
//=============================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntObject;

	for (nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (g_Object[nCntObject].bUse == false)
		{
			g_Object[nCntObject].pos = pos;
			g_Object[nCntObject].rot = rot;
			g_Object[nCntObject].bUse = true;
			break;
		}
	}
}
//=============================================================================
// モデルの当たり判定
//=============================================================================
bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove)
{
	int nCount;
	bool bLand = false;
	Player * pPlayer = GetPlayer();

	for (nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (pPos->x > g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS && pPos->x < g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS)
		{	//Xの範囲
			if (pPosold->z >= g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS && pPos->z < g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS)
			{
				pPos->z = g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS;
				pPos->z = pPosold->z;
			}
			else if (pPosold->z <= g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS && pPos->z > g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS)
			{
				pPos->z = g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS;
				pPos->z = pPosold->z;
			}
		}
		if (pPos->z > g_Object[nCount].pos.z + g_Object[nCount].VtxMinObject.z - PULS && pPos->z < g_Object[nCount].pos.z + g_Object[nCount].VtxMaxObject.z + PULS)
		{	//Zの範囲
			if (pPosold->x >= g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS && pPos->x < g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS)
			{
				pPos->x = g_Object[nCount].pos.x + g_Object[nCount].VtxMaxObject.x + PULS;
				pPos->x = pPosold->x;
			}
			else if (pPosold->x <= g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS && pPos->x > g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS)
			{
				pPos->x = g_Object[nCount].pos.x + g_Object[nCount].VtxMinObject.x - PULS;
				pPos->x = pPosold->x;
			}
		}
	}
	return bLand;
}
//=========================================================================================================================
// オブジェクトの取得処理
//=========================================================================================================================
Object *GetObject(void)
{
	return &g_Object[0];
}