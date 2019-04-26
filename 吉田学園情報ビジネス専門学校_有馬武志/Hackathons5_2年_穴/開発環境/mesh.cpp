//=============================================================================
//
// mesh処理 [mesh.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "camera.h"
#include "mesh.h"
#include "dungeon.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME		"data\\TEXTURE\\市街地02.jpg"						//読み込むテクスチャファイル
#define BULOCK_X					(20.0f)											//ブロックの奥行
#define BULOCK_Y					(400.0f)											//ブロックの横行
#define BULOCK_Z					(20.0f)											//ブロックの横行
#define VERTEX						((VERTICAL + 1) * (CORSS + 1))						//指定した縦と横+１の値
#define IDX							((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4 + 2)	//インデックスの式
#define POLYGON						((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4)		//ポリゴン数の式
#define WALL_CURVE					(3.0f)		//壁の曲がり具合

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//==================================================================================================//
//    * メッシュのセット関数 *
//==================================================================================================//
void CMesh::Set(TYPE type, D3DXVECTOR3 pos, int nVertical, int nCorss, bool bMesh)	//ゲージセット処理
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	m_Type = type;
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nVertical = nVertical;
	m_nCross = nCorss;
	m_bMesh = bMesh;
	m_nNumVertex = (nVertical + 1) * (nCorss + 1);		//頂点数
	m_nNumIdx = (nVertical * nCorss) * 2 + (nVertical - 1) * 4 + 2;				//インデックス数
	m_nNumPolygon = (nVertical * nCorss) * 2 + (nVertical - 1) * 4;		//ポリゴン数

	//頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL );

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer ( sizeof(WORD) * m_nNumIdx, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL );
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	WORD * pIdx;		//インデックスデータへのポインタ
	float fUV_X = 0.25f, fUV_Y = 0.2f;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得
	//頂点、法線、カラー、テクスチャの頂点設定
	for (int nCntVertical = 0; nCntVertical < nVertical + 1; nCntVertical++)
	{//縦軸
		for (int nCntCorss = 0; nCntCorss < nCorss + 1; nCntCorss++)
		{//横軸
		 //頂点座標
			switch (type)
			{
			case TYPE_FIELD: 
				pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * nCntCorss, 0.0f, FIELD_SIZE * 2 - FIELD_SIZE * nCntVertical);
				break;
			case TYPE_WALL:		
				pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE * nCntCorss, FIELD_SIZE * nCntVertical, FIELD_SIZE * nCntCorss);
				break;
			case TYPE_CEILING:
				pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * nCntCorss, 100.0f - rand() % 10 * 10.0f, FIELD_SIZE * 2 + FIELD_SIZE * nCntVertical);
				if (nCntCorss == 0 || nCntCorss == nCorss || nCntVertical == 0 || nCntVertical == nVertical) 
				{
					pVtx[0].pos.y = 0.0f;
				}
				break;
			}
			

			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCntCorss * fUV_X, nCntVertical * fUV_Y);
			pVtx += 1;
		}
	}

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする

	//インデックスバッファのロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// インデックスの設定
	for (int nCount_yz = 0; nCount_yz < nVertical; nCount_yz++)
	{// yzをカウント
		for (int nCount_x = 0; nCount_x < nCorss + 1; nCount_x++)
		{// xをカウント
		 // インデックス情報の設定
			pIdx[0] = (WORD)(((nCount_yz + 1) * (nCorss + 1)) + nCount_x);
			pIdx[1] = (WORD)(((nCount_yz) * (nCorss + 1)) + nCount_x);

			pIdx += 2;			// インデックスバッファを進める

			if (nVertical > 1 && nCount_yz != nVertical - 1 && nCount_x == nCorss)
			{// 末端に到達したら
			 // インデックス情報の設定（縮退ポリゴン）
				pIdx[0] = (WORD)(((nCount_yz) * (nCorss + 1)) + nCount_x);
				pIdx[1] = (WORD)(((nCount_yz + 2) * (nCorss + 1)));

				pIdx += 2;		// インデックスバッファを進める
			}
		}
	}
	//インデックスのバッファのアンロック
	m_pIdxBuff->Unlock();
}
//==================================================================================================//
//    * 法線のセット処理 *
//==================================================================================================//
void	CMesh::SetNor(void)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 nor[2];
	int		nCntHit = 0;
	int nCntVertical, nCntCorss;
	VERTEX_3D *pVtxLU, *pVtxLD, *pVtxRU, *pVtxRD;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得
	for (nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
	{//縦軸
		for (nCntCorss = 0; nCntCorss < m_nCross + 1; nCntCorss++)
		{//横軸
			pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	for (int nCntVertical = 0; nCntVertical < m_nVertical; nCntVertical++)
	{//縦軸
		for (int nCntCorss = 0; nCntCorss < m_nCross; nCntCorss++)
		{//横軸
			//頂点取得
			pVtxLU = &pVtx[(nCntVertical) * (m_nCross + 1) + nCntCorss];
			pVtxLD = &pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCorss];
			pVtxRU = &pVtx[(nCntVertical) * (m_nCross + 1) + nCntCorss + 1];
			pVtxRD = &pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCorss + 1];
			//法線加算
			PlusNor(pVtxLD, pVtxLU, pVtxRD);
			PlusNor(pVtxRD, pVtxRD, pVtxLU);
		}
	}

	for (nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
	{//縦軸
		for (nCntCorss = 0; nCntCorss < m_nCross + 1; nCntCorss++)
		{//横軸
			if (nCntVertical == 0)
			{//上端
				if (nCntCorss == 0 || nCntCorss == m_nCross) { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 2.0f - (nCntCorss / m_nCross); }
				else { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 3.0f; }
			}
			else if (nCntVertical == m_nVertical)
			{//下端
				if (nCntCorss == 0 || nCntCorss == m_nCross) { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 1.0f + (nCntCorss / m_nCross); }
				else { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 3.0f; }
			}
			else
			{//中間
				if (nCntCorss == 0 || nCntCorss == m_nCross) { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 3.0f; }
				else { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 6.0f; }
			}
		}
	}
	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//==================================================================================================//
//    * 法線の加算処理 *
//==================================================================================================//
void CMesh::PlusNor(VERTEX_3D *pVtx, VERTEX_3D *pVtxL, VERTEX_3D *pVtxR)	//法線のセット処理
{
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 nor;

	//法線計算
	vec0 = pVtxL->pos - pVtx->pos;
	vec1 = pVtxR->pos - pVtx->pos;
	D3DXVec3Cross(&nor, (m_bMesh ? &vec0 : &vec1), (m_bMesh ? &vec1 : &vec0));	//外積計算
	D3DXVec3Normalize(&nor, &nor);												//正規化にする

	//加算
	pVtx->nor += nor;
	pVtxL->nor += nor;
	pVtxR->nor += nor;
}
//==================================================================================================//
//    * 頂点のセット関数 *
//==================================================================================================//
void CMesh::SetWall(D3DXVECTOR3 *vtx)	//ゲージセット処理
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	float *fCurve;

	fCurve = new float[m_nCross];

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得
	for (int nCountX = 0; nCountX < m_nVertical + 1; nCountX++)
	{
		for (int nCountY = 0; nCountY < m_nCross + 1; nCountY++)
		{
			if (nCountX == 0)
			{
				if (nCountY == m_nCross)
				{//始めの頂点につなげる
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos = pVtx[nCountX * (m_nCross + 1)].pos;
				}
				else
				{//引数の頂点を代入
					fCurve[nCountY] = (rand() % 628) * 0.01f;
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos
						= vtx[nCountY] + D3DXVECTOR3(sinf(fCurve[nCountY]) * WALL_CURVE, BULOCK_Y * nCountX, cosf(fCurve[nCountY]) * WALL_CURVE);
				}
			}
			else
			{
				if (nCountY == m_nCross)
				{//一つ下の始めの頂点を代入 + Y
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos = pVtx[nCountX * (m_nCross + 1)].pos;
				}
				else
				{//一つ下の頂点を代入 + Y
					fCurve[nCountY] += (rand() % 10) * 0.05f;
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos
						= vtx[nCountY]
						+ D3DXVECTOR3(sinf(fCurve[nCountY]) * WALL_CURVE, BULOCK_Y * nCountX, cosf(fCurve[nCountY]) * WALL_CURVE);
				}
			}
			pVtx[nCountX * (m_nCross + 1) + nCountY].tex = D3DXVECTOR2(nCountY*0.3f, nCountX* 0.5f);

			if(nCountX == 0)
			{
				//CScene3D *p3D;
				//if (SceneCreate(p3D, 0))
				//{
				//	p3D->Set(vtx[nCountY], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),
				//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
				//}
			}
		}
	}

	delete[] fCurve;

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//==================================================================================================//
//床セット処理
//==================================================================================================//
bool CMesh::SetField(int *nDig, int nMaxDig, float *fHeight, bool bRoom)
{
	int nPosX, nPosZ, nType;
	float fPHeight;
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得

	nType = 1;
	if (bRoom) { fPHeight = 500.0f; }
	else { fPHeight = 350.0f; }
	for (int nCount = 0; nCount < nMaxDig; nCount++)
	{//掘った分回転
		nPosX = nDig[nCount] % MAP_SIZE;
		nPosZ = (nDig[nCount] / MAP_SIZE);
		if (nPosX == 0 || nPosX == MAP_SIZE - 1 || nPosZ == 0 || nPosZ == MAP_SIZE - 1) { return false; }
		nPosX = nPosX * FIELD_SPLIT;
		nPosX = m_nCross - nPosX + 2 - FIELD_SPLIT;
		nPosZ = nPosZ* FIELD_SPLIT;
		if (nPosZ > 1) { nPosZ--; }
		if (m_Type == TYPE_CEILING)
		{
			nPosZ = m_nVertical - nPosZ; 
			nType = -1;
		}
		nPosZ = (nPosZ) * (m_nCross + 1);
		for (int nCntZ = 0; nCntZ < FIELD_SPLIT + 1; nCntZ++)
		{//分割量X
			for (int nCntX = 0; nCntX < FIELD_SPLIT + 1; nCntX++)
			{//分割量Z 十字にフィールドセット
				pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX + 1].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX - 1].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + (nCntZ + 1) * (m_nCross + 1) * nType + nCntX].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + (nCntZ - 1) * (m_nCross + 1) * nType + nCntX].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				//CScene3D *p3D;
				//if (SceneCreate(p3D, 4))
				//{
				//	p3D->Set(pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX].pos + m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
				//}
			}//分割量Z
		}//分割量X
	}//掘った分回転

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする

	return true;
}
//==================================================================================================//
//床プラス処理
//==================================================================================================//
void CMesh::UpField(int *nMap, float fHeight)	//床プラス処理
{
	bool bDown = false;
	int nWKZ, nWKX;
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得
	for (int nCntDown = FIELD_STRDOWN; nCntDown < FIELD_NUMDOWN; nCntDown++)
	{
		for (int nCntZ = nCntDown; nCntZ < m_nVertical - nCntDown; nCntZ++)
		{//分割量X
			for (int nCntX = nCntDown; nCntX < m_nCross - nCntDown; nCntX++)
			{//分割量Z
				if (nMap[(nCntZ / FIELD_SPLIT) * MAP_SIZE + (nCntX / FIELD_SPLIT)] == 1)
				{//床なら
					bDown = true;
					for (int nCntZ2 = -nCntDown - 1; nCntZ2 < nCntDown; nCntZ2++)
					{//	Z確認分回転
						for (int nCntX2 = -nCntDown + 1; nCntX2 < nCntDown - 1; nCntX2++)
						{//X確認分回転
							if (nMap[((nCntZ + nCntZ2) / FIELD_SPLIT) * MAP_SIZE + ((nCntX + nCntX2) / FIELD_SPLIT)] == 0) 
							{ bDown = false; nCntZ2 = nCntDown; break; }
						}
					}
					if (bDown)
					{//一マスごとにダウン
						nWKZ = (m_bMesh ? nCntZ + (3 - FIELD_SPLIT) : m_nVertical - nCntZ - (3 - FIELD_SPLIT));
						nWKX = (m_nCross + 1) - nCntX;
						//if (nCntX == nCntDown && nCntZ == nCntDown) { pVtx[nWKZ * (m_nCross + 1) + nWKX].pos.y += fHeight; }
						//if (nCntZ == nCntDown) { pVtx[nWKZ * (m_nCross + 1) + nWKX + 1].pos.y += fHeight; }
						//if (nCntX == nCntDown) { pVtx[(nWKZ + (m_bMesh ? 1 : -1)) * (m_nCross + 1) + nWKX].pos.y += fHeight; }
						pVtx[(nWKZ) * (m_nCross + 1) + nWKX + 1].pos.y += fHeight / (((nCntDown - FIELD_STRDOWN) * 2 + 1));
						//CScene3D *p3D;
						//if (SceneCreate(p3D, 4))
						//{
						//	p3D->Set(pVtx[(nWKZ) * (m_nCross + 1) + nWKX + 1].pos + m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
						//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
						//}
					}
				}
			}//分割量Z
		}//分割量X
	}//ダウン数
	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//=============================================================================
// メッシュの初期化処理
//=============================================================================
HRESULT  CMesh::Init(void)
{
	SetObjType(OBJTYPE_MESH);
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_pTex = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_bMesh = true;
	return S_OK;
}
//=============================================================================
// メッシュの終了処理
//=============================================================================
void  CMesh::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//インデックスバッファの解放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	CScene::Uninit();
}
//=============================================================================
// メッシュの描画処理
//=============================================================================
void  CMesh ::Draw (void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DXMATRIX			mtxWorld;		//ワールドマトリックス
	if (CScene::DrawPrepare(m_DrawType, pDevice)) { return; }

												// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	if (m_pTex != NULL) { pDevice->SetTexture(0, m_pTex); }

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	pDevice->SetTexture(0, NULL);
}
//=============================================================================
//メッシュ全屋根のあたり判定
//=============================================================================
void CMesh::MeshCollisionCeiling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &length)
{
	CScene *pScene;

	pScene = CScene::GetTop(MESH_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_MESH)
		{//メッシュ発見
			if (((CMesh*)pScene)->m_Type == TYPE_CEILING) { ((CMesh*)pScene)->MeshCeling(pos, posold, length.y); }
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//メッシュ全床のあたり判定
//=============================================================================
bool CMesh::MeshCollisionField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, bool &bJump)
{
	CScene *pScene;
	bool bLand = false;

	pScene = CScene::GetTop(MESH_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_MESH)
		{//メッシュ発見
			if (((CMesh*)pScene)->m_Type == TYPE_FIELD) { bLand = ((CMesh*)pScene)->MeshField(pos, posold, move, FNor, length.x, bJump); }
		}
		pScene = pScene->GetpNext();
	}

	return bLand;
}
//=============================================================================
//メッシュ全壁のあたり判定
//=============================================================================
void CMesh::MeshCollisionWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	CScene *pScene;

	pScene = CScene::GetTop(MESH_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_MESH)
		{//メッシュ発見
			if (((CMesh*)pScene)->m_Type == TYPE_WALL) { ((CMesh*)pScene)->MeshWall(pos, posold, move, length.x, nCntHit, bReflection); }
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//メッシュ天井のあたり判定
//=============================================================================
void CMesh::MeshCeling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLength)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	bool		bHit = true;
	D3DXVECTOR3 WKpos = pos - m_pos;
	D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vec[8];

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得

	if (FieldCheck(pVtx[m_nCross].pos, pVtx[0].pos, pVtx[m_nVertical * (m_nCross + 1) + m_nCross].pos, pVtx[m_nVertical * (m_nCross + 1)].pos, WKpos))
	{//四角範囲内なら
		WKpos = pos - m_pos;
		int	nField = 0;
		//float	fRotCross;										//面の角度X
		//float	fRotVertical;									//面の角度Z
		int		nCntCross;
		int		nCntVertical;

		nCntCross = (int)((WKpos.x - pVtx[0].pos.x) / FIELD_SIZE);		//横の頂点の列を算出
		nCntVertical = (int)((pVtx[0].pos.z - WKpos.z) / FIELD_SIZE);	//縦の頂点の列を算出
		if (nCntCross < 0) { nCntCross *= -1; }
		if (nCntVertical < 0) { nCntVertical *= -1; }
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "天井 %d　%d\n", nCntCross, nCntVertical);
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, " 判定　%d→%d", nCntVertical * (m_nCross + 1) + nCntCross, (nCntVertical + 1) * (m_nCross + 1) + nCntCross + 1);

		WKpos.y = FieldCollision(
			pVtx[nCntVertical * (m_nCross + 1) + nCntCross + 1].pos, pVtx[nCntVertical * (m_nCross + 1) + nCntCross].pos, 
			pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross].pos, pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross].pos,
			pos - m_pos, pos, WKnor);

		if (WKpos.y < pos.y + fLength)
		{//貫通していたら
			pos.y = WKpos.y - fLength;
		}
	}

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//=============================================================================
//メッシュ床のあたり判定
//=============================================================================
bool CMesh::MeshField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &FNor, float& fLength, bool &bJump)
{
	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	bool		bLand = false;
	D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 WKpos = pos - m_pos;
	D3DXVECTOR3 Vec[8];

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得

	if(FieldCheck(pVtx[0].pos, pVtx[m_nCross].pos, pVtx[m_nVertical * (m_nCross + 1)].pos, pVtx[m_nVertical * (m_nCross + 1) + m_nCross].pos, WKpos))
	{//四角範囲内なら
		WKpos = pos - m_pos;
		int		nCntCross;
		int		nCntVertical;

		nCntCross = (int)((WKpos.x - pVtx[0].pos.x) / FIELD_SIZE);		//横の頂点の列を算出
		nCntVertical = (int)((pVtx[0].pos.z - WKpos.z) / FIELD_SIZE);	//縦の頂点の列を算出
		if (nCntCross < 0) { nCntCross *= -1; }
		if (nCntVertical < 0) { nCntVertical *= -1; }
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "フィールド %d　%d\n", nCntCross, nCntVertical);
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, " 判定　%d→%d", nCntVertical * (m_nCross + 1) + nCntCross, (nCntVertical + 1) * (m_nCross + 1) + nCntCross + 1);
		
		WKpos.y = FieldCollision(
			pVtx[nCntVertical * (m_nCross + 1) + nCntCross].pos, pVtx[nCntVertical * (m_nCross + 1) + nCntCross + 1].pos,
			pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross].pos, pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross + 1].pos,
			pos - m_pos, pos, WKnor);

		if (WKpos.y >= pos.y - (bJump ?  10.0f : 0.0f))
		{//貫通していたら
			pos.y = WKpos.y;
			move.y = 0.0f;
			FNor = WKnor;
			if (!bJump) { bLand = true; }//前Fが空中なら
			bJump = true;
		}
	}

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
	return bLand;
}
//=============================================================================
//メッシュ壁のあたり判定
//=============================================================================
void CMesh::MeshWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection)
{
	//上のみ見る(2頂点のうち)
	int nVtxY = 0;	//比較する頂点を取得

	bool		bEnd = true;	//終了判定

	VERTEX_3D *pVtx;	//頂点情報へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得

	do
	{
		for (int nCount = 0; nCount < m_nCross; nCount++)
		{//メッシュWallのXZのみを見る
			
			if (WallCollision(pVtx[nVtxY * (m_nCross + 1) + nCount].pos, pVtx[nVtxY * (m_nCross + 1) + nCount + 1].pos, pos, posold, move, fLength, nCntHit, bReflection) == 2)
			{bEnd = true; break; }
		}
	} while (!bEnd);
	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//=============================================================================
// 外積壁のあたり判定をキャラ分大きく処理
//=============================================================================
void CMesh::WallPlus(D3DXVECTOR3& pos0, D3DXVECTOR3 &pos1, float& fLengthX, float& fLengthZ)
{
	if (pos0.x - pos1.x < 0)
	{//キャラが壁の右側
		if (pos0.x - pos1.x < fLengthX) { pos0.x += pos0.x - pos1.x; }
		else { pos0.x += fLengthX; }
	}
	else
	{//キャラが壁の左側
		if (pos0.x - pos1.x < -fLengthX) { pos0.x -= pos0.x - pos1.x; }
		else { pos0.x -= fLengthX; }
	}

	if (pos0.z - pos1.z < 0)
	{//キャラが壁の右側
		if (pos0.z - pos1.z < fLengthZ) { pos0.z += pos0.z - pos1.z; }
		else { pos0.z += fLengthZ; }
	}
	else
	{//キャラが壁の左側
		if (pos0.z - pos1.z < -fLengthZ) { pos0.z -= pos0.z - pos1.z; }
		else { pos0.z -= fLengthZ; }
	}
}
//=============================================================================
//角度と角度のチェック判定
//=============================================================================
int CMesh::AngleCheck(float fAngle0, float fAngle1)
{
	float fWKRot = fAngle0;
	fAngle0 = 0.0f;
	fAngle1 -= fWKRot;

	if (fAngle1 > D3DX_PI) { fAngle1 -= D3DX_PI * 2.0f; }
	if (fAngle1 < -D3DX_PI) { fAngle1 += D3DX_PI * 2.0f; }

	if (fAngle0 > fAngle1) { return 1; }
	else if (fAngle0 < fAngle1) { return -1; }
	return 0;
}
//=============================================================================
//内側外側のチェック判定
//=============================================================================
bool CMesh::FieldCheck(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3& pos)
{
	D3DXVECTOR3 Vec[8];

	Vec[0] = FposUL - FposUR;
	Vec[1] = pos - FposUR;
	Vec[2] = FposUR - FposDR;
	Vec[3] = pos - FposDR;
	Vec[4] = FposDR - FposDL;
	Vec[5] = pos - FposDL;
	Vec[6] = FposDL - FposUL;
	Vec[7] = pos - FposUL;

	if ((Vec[0].z * Vec[1].x) - (Vec[0].x * Vec[1].z) <= 0 &&
		(Vec[2].z * Vec[3].x) - (Vec[2].x * Vec[3].z) <= 0 &&
		(Vec[4].z * Vec[5].x) - (Vec[4].x * Vec[5].z) <= 0 &&
		(Vec[6].z * Vec[7].x) - (Vec[6].x * Vec[7].z) <= 0
		)
	{//四角範囲内なら
		return true;
	}
	return false;
}
//=============================================================================
//起伏判定
//=============================================================================
float CMesh::FieldCollision(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3 WKpos, D3DXVECTOR3& pos, D3DXVECTOR3 &FNor)
{
	bool bLand = false;
	D3DXVECTOR3 Vtx[4];
	D3DXVECTOR3 vec0, vec1;
	float		fData;
	D3DXVECTOR3 nor;
	vec0 = FposDR - FposUL;
	vec1 = WKpos - FposUL;

	if ((vec0.z * vec1.x) - (vec0.x * vec1.z) <= 0)
	{//三角形区分で右上側
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "右上\n");
		Vtx[0] = FposUR;
		Vtx[1] = FposUL;
		Vtx[2] = FposDR;
	}
	else
	{//三角形区分で左下側
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "左下\n");
		Vtx[0] = FposDL;
		Vtx[1] = FposDR;
		Vtx[2] = FposUL;
	}
	fData = Vtx[0].y; Vtx[0].y -= fData; Vtx[1].y -= fData; Vtx[2].y -= fData;

	vec0 = Vtx[2] - Vtx[0];
	vec1 = Vtx[1] - Vtx[0];
	D3DXVec3Cross(&nor, &vec0, &vec1);	//外積計算
	D3DXVec3Normalize(&nor, &nor);		//正規化にする
	D3DXVECTOR3 vec;
	vec = WKpos - Vtx[0];

	if (nor.y != 0)
	{
		//WKpos.y = ((nor.x * vec.x) + (nor.z * vec.z)) / -nor.y;
		WKpos.y = ((nor.x * vec.x) + (nor.z * vec.z)) / -nor.y;
	}
	else
	{
		//WKpos.y = 0.0f;
		WKpos.y = 0.0f;
	}
	FNor = nor;
	WKpos.y += fData;

	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "頂点0　%.1f　%.1f　%.1f\n", Vtx[0].x, Vtx[0].y, Vtx[0].z);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "頂点1　%.1f　%.1f　%.1f\n", Vtx[1].x, Vtx[1].y, Vtx[1].z);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "頂点2　%.1f　%.1f　%.1f\n", Vtx[2].x, Vtx[2].y, Vtx[2].z);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "補正値　%.1f\n", fData);
	//if (SceneCreate(p3D, 5))
	//{
	//	p3D->Set(Vtx[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
	//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	//	p3D->GetState() = CScene3D::STATE_FADEOUT;
	//	p3D->GetfCntState() = 0.3f;
	//}
	//if (SceneCreate(p3D, 5))
	//{
	//	p3D->Set(Vtx[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),
	//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	//	p3D->GetState() = CScene3D::STATE_FADEOUT;
	//	p3D->GetfCntState() = 0.3f;
	//}
	//if (SceneCreate(p3D, 5))
	//{
	//	p3D->Set(Vtx[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
	//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	//	p3D->GetState() = CScene3D::STATE_FADEOUT;
	//	p3D->GetfCntState() = 0.3f;
	//}
	return WKpos.y;
}
//=============================================================================
//線と線のあたり判定(壁)判定
//=============================================================================
int CMesh::WallCollision(D3DXVECTOR3 Wpos0, D3DXVECTOR3 Wpos1, D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection)
{
	D3DXVECTOR3 Wpos2;			//差分縮める用
	D3DXVECTOR3 Wpos3;			//差分縮める用
	float		fDistance;		//めり込んだ距離
	float		fCntZ;
	float		fWKrot = 0.0f;
	float		fAngle[5];
	float		fSave = pos.y;
	D3DXVECTOR3 Vec;
	int		nEnd = 0;	//終了判定

	//角度計算
	fAngle[0] = atan2f(Wpos1.x - Wpos0.x, Wpos1.z - Wpos0.z);
	Wpos2 = pos;
	Wpos0 += D3DXVECTOR3(sinf(fAngle[0] - D3DX_PI * 0.75f), 0.0f, cosf(fAngle[0] - D3DX_PI * 0.75f)) * fLength;
	Wpos1 += D3DXVECTOR3(sinf(fAngle[0] - D3DX_PI * 0.25f), 0.0f, cosf(fAngle[0] - D3DX_PI * 0.25f)) * fLength;

	fAngle[1] = atan2f(Wpos2.x - Wpos0.x, Wpos2.z - Wpos0.z);
	fAngle[2] = atan2f(Wpos0.x - posold.x, Wpos0.z - posold.z);
	fAngle[3] = atan2f(Wpos2.x - posold.x, Wpos2.z - posold.z);
	fAngle[4] = atan2f(Wpos1.x - posold.x, Wpos1.z - posold.z);

	if (AngleCheck(fAngle[0], fAngle[1]) <= 0 &&	//現在の位置が壁の向こうか
		AngleCheck(fAngle[0], fAngle[2]) <= 0 &&	//前の位置が壁の手前側
		AngleCheck(fAngle[3], fAngle[2]) <= 0 &&	//移動方向が壁時計回り手前頂点の内側
		AngleCheck(fAngle[3], fAngle[4]) >= 0		//移動方向が壁時計回り置く頂点の内側
		)
	{//交差チェック
		nCntHit++;
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "ヒット！ %d\n", nCntHit);
		if (nCntHit < 2 || bReflection)
		{//2回以上ヒット
		 //交点を求める
			fDistance = sqrtf(powf((Wpos2.x - Wpos0.x), 2) + powf((Wpos2.z - Wpos0.z), 2));
			nEnd = 1;

			if (fLength > 5.0f)
			{
				//反射計算
				fWKrot = fAngle[0] - fAngle[3]; //壁角度からプレイヤーの移動方向を引いて反転
				if (fWKrot > D3DX_PI) { fWKrot -= D3DX_PI * 2.0f; }
				if (fWKrot < -D3DX_PI) { fWKrot += D3DX_PI * 2.0f; }
				fAngle[3] += fWKrot * 2.0f;	//行きたい角度
				if (fAngle[3] > D3DX_PI) { fAngle[3] -= D3DX_PI * 2.0f; }
				if (fAngle[3] < -D3DX_PI) { fAngle[3] += D3DX_PI * 2.0f; }
			}
			else
			{
				nEnd = 2;
				//交点をずらさない
				fAngle[3] = atan2f(posold.x - Wpos2.x, posold.z - Wpos2.z);

				fAngle[1] = atan2f(pos.x - Wpos0.x, pos.z - Wpos0.z);	//posoldと壁原点の角度を取る
				fWKrot = D3DX_PI * -0.5f - fAngle[1];					//それと-1.57の差分を求める
				if (fWKrot > D3DX_PI) { fWKrot -= D3DX_PI * 2.0f; }
				if (fWKrot < -D3DX_PI) { fWKrot += D3DX_PI * 2.0f; }
				//元角度計算は行きたい角度と壁角度
				//それらを差分後角度で伸ばし1.0Ｙ分を取得
				Wpos1 = D3DXVECTOR3(sinf(fWKrot + fAngle[0]), 0.0f, cosf(fWKrot + fAngle[0])) * 1.0f;
				Wpos2 = D3DXVECTOR3(sinf(fWKrot + fAngle[3]), 0.0f, cosf(fWKrot + fAngle[3])) * 1.0f;
				Wpos1.x = Wpos1.x / Wpos1.z;
				Wpos2.x = Wpos2.x / Wpos2.z;
				fCntZ = fDistance / (-Wpos1.x + Wpos2.x);
				//(距離 / Ｘの和) = 回数 = 求めたい距離
				Wpos3 = D3DXVECTOR3(fCntZ * Wpos1.x, 0.0f, fCntZ);
				fDistance = sqrtf(powf((Wpos3.x), 2) + powf((Wpos3.z), 2));
			}
			//値代入
			Wpos0 = D3DXVECTOR3(Wpos0.x, pos.y, Wpos0.z) + D3DXVECTOR3(sinf(fAngle[0]), 0.0f, cosf(fAngle[0])) * fDistance;
			if (bReflection) { pos = Wpos0 + D3DXVECTOR3(sinf(fAngle[3]), 0.0f, cosf(fAngle[3])) * (WALL_PLUS); }
			else { pos = Wpos0 + D3DXVECTOR3(sinf(fAngle[0] - D3DX_PI * 0.5f), 0.0f, cosf(fAngle[0] - D3DX_PI * 0.5f)) * (0.1f); }

			CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "壁の角度 : %f\n", fAngle[0]);

		}
		else
		{
			nEnd = 2;
			//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "戻った！\n");
			pos.x = posold.x;
			pos.z = posold.z;
		}
		pos.y = fSave;
	}

	return nEnd;
}

//=============================================================================
// メッシュオービット設定処理
//=============================================================================
void	CMeshOrbit::Set(D3DXMATRIX &mtxWorld, D3DXVECTOR3 length0, D3DXVECTOR3 length1, bool &bDelete, D3DXCOLOR col, CScene::TEXTURE tex)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	//代入
	m_pmtxWorld = &mtxWorld;	m_bDelete = &bDelete;
	m_col = col;				m_pTex = Load(tex);

	m_nCross = 100;										//横の長さ
	m_nNumPolygon = (1 * m_nCross) * 2 + (1 - 1) * 4;	//面の数
	m_fPlusCol = 1.0f / m_nCross;
	m_fUV = 0.0f;
	m_DrawType = CScene::DRAW_TYPE_ADD;

	for (int nCount = 0; nCount < 2; nCount++)
	{//マトリックス計算
		if (nCount == 1) { length0 = length1; }
		// 自身の位置を計算
		D3DXMatrixTranslation(&m_mtxWorld[nCount], length0.x, length0.y, length0.z);
	}

	//頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((1 + 1) * (m_nCross + 1)), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//メッシュ設定
	//CMesh::Set(CMesh::TYPE_ORBIT, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1, 100, true);
	SetObjType(OBJTYPE_ORBIT);

	SetVtx(true);
}
//=============================================================================
//更新処理
//=============================================================================
void	CMeshOrbit::Update(void)
{
	SwapVtx();		//頂点の入れ替え

	//最新の頂点を代入
	if (m_pmtxWorld != NULL) { SetVtx(false); }
	else
	{
		m_fEnd += m_fPlusCol;
		if (m_fEnd >= 1.0f) { Uninit(); }
	}
}
//=============================================================================
//描画処理
//=============================================================================
void	CMeshOrbit::Draw(void)
{
	//デバイスを取得
	LPDIRECT3DDEVICE9 &pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;	//計算用マトリックス
	D3DXMATRIX	mtxWorld;					//ワールドマトリックス

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // 裏面をカリング

	if (CScene::DrawPrepare(GetDrawType(), pDevice)) { return; }

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	if (m_pTex != NULL)
	{//テクスチャの設定
		pDevice->SetTexture(0, m_pTex);
	}//テクスチャ削除

	 // ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, m_nNumPolygon);
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);    // 裏面をカリング
}
//=============================================================================
//最新の頂点を計算して代入
//=============================================================================
void	CMeshOrbit::SetVtx(bool bAll)
{
	if (m_nReset == 1) { m_nReset--; SetVtx(true); }
	else if (m_nReset > 0) { m_nReset--; return; }
	D3DXMATRIX mtxWK;

	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得

	for (int nCount = 0; nCount < 2; nCount++)
	{
		// 計算用マトリックスに代入
		mtxWK = m_mtxWorld[nCount];

		// 親の角度を用いて移動を反映
		D3DXMatrixMultiply(&mtxWK, &mtxWK, m_pmtxWorld);

		pVtx[nCount].pos = D3DXVECTOR3(mtxWK._41, mtxWK._42, mtxWK._43);
		pVtx[nCount].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, (bAll ? 0.0f : 1.0f));
		pVtx[nCount].tex = D3DXVECTOR2(m_fUV * 0.1f, (nCount == 0 ? 0.0f : 1.0f));
		pVtx[nCount].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_fUV += 0.1f;
	}

	if (bAll)
	{//全ての頂点に代入
		for (int nCount = 1; nCount < m_nCross + 1; nCount++)
		{//横の分割数分回転
			pVtx[(nCount) * 2]		= pVtx[0];
			pVtx[(nCount) * 2 + 1]	= pVtx[1];
		}
	}

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//=============================================================================
//頂点の入れ替え
//=============================================================================
void	CMeshOrbit::SwapVtx(void)
{
	D3DXCOLOR				col;

	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//頂点バッファをロックし頂点データへのポインタを取得

	for (int nCount = m_nCross - 1; nCount >= 0; nCount--)
	{//横の分割数分回転

		//透明度薄く
		col = pVtx[(nCount * 2)].col;		pVtx[(nCount * 2)].col	   = D3DXCOLOR(col.r, col.g, col.b, col.a - m_fPlusCol);
		col = pVtx[(nCount * 2) + 1].col;	pVtx[(nCount * 2) + 1].col = D3DXCOLOR(col.r, col.g, col.b, col.a - m_fPlusCol);

		//入れ替え
		pVtx[(nCount * 2) + 2] = pVtx[(nCount * 2)];
		pVtx[(nCount * 2) + 3] = pVtx[(nCount * 2) + 1];
	}

	m_pVtxBuff->Unlock();	//頂点バッファのアンロックする
}
//=============================================================================
//頂点のリセット
//=============================================================================
void	CMeshOrbit::ReSetAll(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(ORBIT_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_ORBIT)
		{//メッシュ発見
			((CMeshOrbit*)pScene)->ReSet();
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//削除確認と破棄
//=============================================================================
void	CMeshOrbit::Delete(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(ORBIT_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_ORBIT)
		{//メッシュ発見
			if (((CMeshOrbit*)pScene)->m_bDelete[0])
			{//終了なら破棄
				((CMeshOrbit*)pScene)->m_pmtxWorld = NULL;
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//頂点のリセット
//=============================================================================
void	CMeshOrbit::ReSet(void)
{
	m_fUV = 0.0f;
	m_nReset = 3;
	SetVtx(true);
}
