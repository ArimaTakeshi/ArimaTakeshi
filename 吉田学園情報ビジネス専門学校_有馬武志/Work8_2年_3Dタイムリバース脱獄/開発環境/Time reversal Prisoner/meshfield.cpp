//=============================================================================
//
// メッシュの処理 [mesh.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "meshfield.h"
#include "mesh.h"
#include "manager.h"
#include "scene.h"
#include "model.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MESHFIELD_0		"data\\TEXTURE\\mesh\\stairs.png"	// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_1		"data\\TEXTURE\\mesh\\flooa000.jpg"	// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_2		"data\\TEXTURE\\mesh\\sky001.jpg"	// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_3		"data\\TEXTURE\\mesh\\green2.jpg"	// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture[MAX_MESH_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 CMeshField::m_pVtxBuff = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 CMeshField::m_pIdxBuff = NULL;				// インデックスへのポインタ
int CMeshField::m_nMeshType = 0;
//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CMeshField::CMeshField()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//　デストラクタ
//===============================================================================
CMeshField::~CMeshField()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CMesh::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	CMesh::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshField::Update(void)
{
	CMesh::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	CMesh::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CMeshField * CMeshField::Create(D3DXVECTOR3 pos,int nMeshX, int nMeshZ,float fMeshWidth, float fMeshDepth, float fVtx0, float fVtxMeshX, float fVtxMeshZ, float fVtxMeshXMeshZ, int nTexType,int nMeshType)
{
	CMeshField *pMeshField = NULL;

	//NULLチェック
	if (pMeshField == NULL)
	{//メモリの動的確保

		pMeshField = new CMeshField;

		if (pMeshField != NULL)
		{
			//位置を変数に代入
			pMeshField->m_pos = pos;
			//位置の代入
			pMeshField->SetPosition(pos);
			//メッシュの種類
			pMeshField->SetMeshType(nMeshType);
			//メッシュの情報を親クラスに渡す
			pMeshField->SetMeshInfo(nMeshX, nMeshZ, fMeshDepth, fMeshWidth);
			//メッシュの頂点の高さ
			pMeshField->SetVtx(fVtx0, fVtxMeshX, fVtxMeshZ, fVtxMeshXMeshZ);
			//オブジェクトクラスの生成
			pMeshField->Init();
			//テクスチャの設定
			pMeshField->BindTexture(m_pTexture[nTexType]);

			pMeshField->m_nMeshType = nTexType;
		}
	}

	return pMeshField;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CMeshField::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_3, &m_pTexture[3]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CMeshField::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MESH_TEXTURE; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
//	ステージ移動時に初期化するため
//=============================================================================
void CMeshField::DeleteMeshField(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(MESH_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_MESH)
			{
				pScene->Uninit();
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

