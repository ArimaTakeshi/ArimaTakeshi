//=============================================================================
//
// オブジェクトの処理 [model3D.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include <math.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//===============================================================================
//　オーバーロードコンストラクタ
//===============================================================================
CModel3D::CModel3D(int nPriority,CScene::OBJTYPE objType) : CScene(nPriority,objType)
{
	m_pMeshObject = NULL;					//メッシュ情報へのポインタ
	m_pBuffMatObject = NULL;				//マテリアルの情報へのポインタ
	m_nNumMatObject = 0;					//マテリアルの情報数
	m_mtxWorldObject;						//ワールドマトリックス
	m_VtxMinModel, m_VtxMaxModel;			//モデルの最小値・最大値
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//動き
	m_fRot = 0.0f;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CModel3D::~CModel3D()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CModel3D::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//位置
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向き達する
	m_VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);	//最大値
	m_VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);		//最小値

	//頂点数を取得
	nNumVtx = m_pMeshObject->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMeshObject->GetFVF());

	//頂点バッファのロック
	m_pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

		//最大値
		if (vtx.x > m_VtxMaxModel.x)
		{
			m_VtxMaxModel.x = vtx.x;
		}
		if (vtx.y > m_VtxMaxModel.y)
		{
			m_VtxMaxModel.y = vtx.y;
		}
		if (vtx.z > m_VtxMaxModel.z)
		{
			m_VtxMaxModel.z = vtx.z;
		}
		//最小値
		if (vtx.x < m_VtxMinModel.x)
		{
			m_VtxMinModel.x = vtx.x;
		}
		if (vtx.y < m_VtxMinModel.y)
		{
			m_VtxMinModel.y = vtx.y;
		}
		if (vtx.z < m_VtxMinModel.z)
		{
			m_VtxMinModel.z = vtx.z;
		}

		//サイズ文のポインタを進める
		pVtxBuff += sizeFVF;
	}

	//頂点バッファのアンロック
	m_pMeshObject->UnlockVertexBuffer();

	m_Rot.y = 0.0f;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CModel3D::Uninit(void)
{
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CModel3D::Update(void)
{
	//m_fRot += 0.01f;

	//クォータニオン
	CModel3D::Quaternion(m_fRot);
}
//=============================================================================
// 描画処理
//=============================================================================
void CModel3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				//計算洋間鳥kk数
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldObject);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorldObject, &m_mtxWorldObject, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorldObject, &m_mtxWorldObject, &mtxTrans);

	// ワールドマトリックスの設3定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldObject);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatObject; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャがある場合
			pDevice->SetTexture(0, m_pMeshTextures);
		}
		else
		{	// テクスチャを使っていない
			pDevice->SetTexture(0, NULL);
		}
		//オブジェクト(パーツ)の描画
		m_pMeshObject->DrawSubset(nCntMat);
	}


	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
//===============================================================================
//　値を渡す
//===============================================================================
void CModel3D::BindModel(LPD3DXMESH pMeshObject, LPD3DXBUFFER pBuffMatObject, DWORD nNumMatObject, LPDIRECT3DTEXTURE9 pMeshTextures)
{
	m_pMeshObject = pMeshObject;
	m_pBuffMatObject = pBuffMatObject;
	m_nNumMatObject = nNumMatObject;
	m_pMeshTextures = pMeshTextures;
}
//===============================================================================
//　クリエイト
//===============================================================================
CModel3D * CModel3D::Create(void)
{
	CModel3D *pModel3D = NULL;

	//NULLチェック
	if (pModel3D == NULL)
	{//メモリの動的確保

		pModel3D = new CModel3D;

		if (pModel3D != NULL)
		{
			//オブジェクトクラスの生成
			pModel3D->Init();
		}
	}
	
	return pModel3D;
}
//===============================================================================
// 
//===============================================================================
void CModel3D::Quaternion(float fRot)
{
	//クォータニオン宣言
	D3DXQUATERNION qouternion, pQou1, pQou2;

	//マトリックス宣言
	D3DXMATRIX mtx;

	//回転マトリックスを生成
	D3DXMatrixRotationYawPitchRoll(&mtx, qouternion.x, qouternion.y, qouternion.z);

	//回転マトリクスをクォータニオンに変換
	D3DXQuaternionRotationMatrix(&qouternion, &mtx);

	//中間姿勢のクォータニオンを取得
	D3DXQuaternionSlerp(&qouternion, &pQou1, &pQou2, 0.5f);

	//クォータニオンから回転行列
	D3DXMatrixRotationQuaternion(&mtx, &qouternion);
}