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
#define TEXTURE_MESHFIELD_0		"data\\TEXTURE\\sky.jpg"				// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_1		"data\\TEXTURE\\green2.jpg"				// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_2		"data\\TEXTURE\\field03.jpg"			// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_3		"data\\TEXTURE\\rock_002.jpg"			// 読み込むテクスチャファイル名
#define TEXTURE_MESHFIELD_4		"data\\TEXTURE\\soil.jpg"				// 読み込むテクスチャファイル名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture[MAX_MESH_TEXTURE] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 CMeshField::m_pVtxBuff = NULL;					// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 CMeshField::m_pIdxBuff = NULL;					// インデックスへのポインタ
//CMeshField::MeshField CMeshField::m_MeshField[MESH_DATA] = {};
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
	for (int nCntTex = 0; nCntTex < MAX_MESH_TEXTURE; nCntTex++)
	{
		//テクスチャの破棄
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}

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

	//近くのモデル以外を消す
	if (m_pos.x + 3000.0f >= PlayerPos.x && m_pos.x - 3000.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		CMesh::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		CMesh::Draw();
	}
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
		}
	}

	return pMeshField;
}
#if 0
//===============================================================================
//　クリエイト
//===============================================================================
void CMeshField::CreateMesh(void)
{
	//使う数を入れる箱
	int nNumMaxMesh = 0;
	char read[200];

	//ファイルのポインタ
	FILE *pFile;

	//ファイル設定
	pFile = fopen(MESHFILE_NAME, "r");

	//敵のテキストデータの読み込み
	if (pFile != NULL)
	{
		//総数のtexコメント
		fscanf(pFile, "%s", &read[0]);

		//コメント付け
		if (strcmp(&read[0], "#") == 0)
		{
			do
			{
				fscanf(pFile, "%c", &read[0]);
			}
			while (strcmp(&read[0], "\n") != 0);
		}

		//使う敵の数
		fscanf(pFile, "%d", &nNumMaxMesh);	//読み込み

		for (int nCntMesh = 0; nCntMesh < nNumMaxMesh; nCntMesh++)
		{
			//敵の種類のコメント
			for (int nCount = 0; nCount < 3; nCount++)
			{
				fscanf(pFile, "%s", &read[0]);

				if (strcmp(&read[0], "#") == 0)
				{
					do
					{
						fscanf(pFile, "%c", &read[0]);
					} while (strcmp(&read[0], "\n") != 0);
				}
			}

			//初期位置の設定
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].InitPos.x);		//位置X
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].InitPos.y);		//位置Y
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].InitPos.z);		//位置Z

			//分割数の設定
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nDivision_X);	//分割数X
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nDivision_Z);	//分割数Z

			//メッシュの横幅と奥行の設定
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].fWidth);			//横幅
			fscanf(pFile, "%f", &m_MeshField[nCntMesh].fDepth);			//奥行

			//テクスチャの設定
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nTexType);		//テクスチャ種類[0:空][1:草の地面][2:川]

			//メッシュシリンダーかフィールドか
			fscanf(pFile, "%d", &m_MeshField[nCntMesh].nMeshType);		//メッシュの種類[0:シリンダー][1:フィールド]

			//フィールドの生成
			CMeshField::Create
			(
				m_MeshField[nCntMesh].InitPos,		//初期位置D3DXVECTOR3型
				m_MeshField[nCntMesh].nDivision_X,	//int型の分割数X方向
				m_MeshField[nCntMesh].nDivision_Z,	//int型の分割数Z方向　シリンダーはYとして使う：フィールドはZとして使う
				m_MeshField[nCntMesh].fWidth,		//横幅のサイズ float型
				m_MeshField[nCntMesh].fDepth,		//奥行のサイズ float型
				m_MeshField[nCntMesh].nTexType,		//テクスチャの種類 int型 [0:空][1:草の地面][2:川]
				m_MeshField[nCntMesh].nMeshType		//メッシュフィールドの種類 [0:シリンダー][1:フィールド]
			);
		}

		fclose(pFile);	//ファイルを閉じる
	}
	else
	{//警告文
		MessageBox(0, "セーブファイルのチェックに失敗!", "警告", MB_ICONWARNING);
	}
}
#endif
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
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MESHFIELD_4, &m_pTexture[4]);

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

