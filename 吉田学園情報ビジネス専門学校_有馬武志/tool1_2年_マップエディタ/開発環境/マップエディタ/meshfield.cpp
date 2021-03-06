//=============================================================================
//
// メッシュの処理 [mesh.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "meshfield.h"
#include "markmeshfield.h"
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
#define TEXTURE_MESHFIELD_0		"data\\TEXTURE\\mesh\\stairs.png"		// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_1		"data\\TEXTURE\\mesh\\flooa000.jpg"	// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_2		"data\\TEXTURE\\mesh\\field03.jpg"	// 読み込むテクスチャファイル名
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

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CMeshField::CMeshField() : CMesh(MESHFIELD_PRIOTITY, CScene::OBJTYPE_MESHFILED)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nWidthDivide = 5;
	m_nDepthDivide = 5;
	m_fWidthLength = 500.0f;
	m_fDepthLength = 500.0f;
	m_fVtxHeight_No0 = 0.0f;
	m_fVtxHeight_No1 = 0.0f;
	m_fVtxHeight_No2 = 0.0f;
	m_fVtxHeight_No3 = 0.0f;
	m_nTexType = 0;
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

	//CDebugProc::Print("メッシュフィールドの座標[X : %.1f][Y : %.1f][Z : %.1f]\n", m_pos.x, m_pos.y, m_pos.z);
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

			//ファイル書き込み用変数
			pMeshField->m_nWidthDivide = nMeshX;
			pMeshField->m_nDepthDivide = nMeshZ;
			pMeshField->m_fWidthLength = fMeshWidth;
			pMeshField->m_fDepthLength = fMeshDepth;
			pMeshField->m_fVtxHeight_No0 = fVtx0;
			pMeshField->m_fVtxHeight_No1 = fVtxMeshX;
			pMeshField->m_fVtxHeight_No2 = fVtxMeshZ;
			pMeshField->m_fVtxHeight_No3 = fVtxMeshXMeshZ;
			pMeshField->m_nTexType = nTexType;
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
//===============================================================================
// ファイルにセーブ
//===============================================================================
void CMeshField::TextSave(void)
{
	int nMarkMeshField = CMarkMeshField::GetMeshFieldNum();

	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(MESHFIELD_PRIOTITY);

	//ファイルのポインタ
	FILE *pFile;

	//ファイル読み取り設定
	pFile = fopen(MESHFILE_NAME, "wb");

	//プレイヤーのテキストデータの読み込み
	if (pFile != NULL)
	{
		//説明文
		fprintf(pFile, "#====================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#　マップのメッシュフィールド配置のエディタ [meshfield.txt]\n");
		fprintf(pFile, "#　制作者 : 有馬　武志\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================\n\n");
		//置いたオブジェクトの数
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#　メッシュフィールドの設置数\n");
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "MESHFIELD_SETNUM = ");
		fprintf(pFile, "%d\n\n", nMarkMeshField);
		//説明文
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#　メッシュフィールドの設置情報\n");
		fprintf(pFile, "#----------------------------------------------------\n");

		//NULLチェック
		while (pScene != NULL)
		{
			//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
			CScene *pSceneNext = pScene->GetNext();

			if (pScene->GetDeath() == false)
			{
				//タイプがオブジェクトだったら
				if (pScene->GetObjType() == OBJTYPE_MESHFILED)
				{
					//開始のための宣言
					fprintf(pFile, "MESHFIELD_START\n");
					//テクスチャの種類を入れる
					fprintf(pFile, "	TEXTURETYPE = ");
					fprintf(pFile, "%d\n", ((CMeshField*)pScene)->m_nTexType); 
					//横の分割数を入れる
					fprintf(pFile, "	X_DIVIDE = ");
					fprintf(pFile, "%d\n", ((CMeshField*)pScene)->m_nWidthDivide);
					//縦の分割数を入れる
					fprintf(pFile, "	Z_DIVIDE = ");
					fprintf(pFile, "%d\n", ((CMeshField*)pScene)->m_nDepthDivide);
					//横の分割数を入れる
					fprintf(pFile, "	X_LENGTH = ");
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_fWidthLength);
					//縦の分割数を入れる
					fprintf(pFile, "	Z_LENGTH = ");
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_fDepthLength);
					//0番の頂点の高さを入れる
					fprintf(pFile, "	VTX0_HEIGHT = ");
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_fVtxHeight_No0);
					//1番の頂点の高さを入れる
					fprintf(pFile, "	VTX1_HEIGHT = ");
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_fVtxHeight_No1);
					//2番の頂点の高さを入れる
					fprintf(pFile, "	VTX2_HEIGHT = ");
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_fVtxHeight_No2);
					//3番の頂点の高さを入れる
					fprintf(pFile, "	VTX3_HEIGHT = ");
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_fVtxHeight_No3);
					//位置を入れる
					fprintf(pFile, "	POS = ");
					fprintf(pFile, "%.2f ", ((CMeshField*)pScene)->m_pos.x);
					fprintf(pFile, "%.2f ", ((CMeshField*)pScene)->m_pos.y);
					fprintf(pFile, "%.2f\n", ((CMeshField*)pScene)->m_pos.z);
					//開始のための宣言
					fprintf(pFile, "MESHFIELD_END\n\n");
				}
			}

			//Nextに次のSceneを入れる
			pScene = pSceneNext;
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

