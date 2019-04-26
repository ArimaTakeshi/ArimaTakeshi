//=============================================================================
//
// 印のメッシュの処理 [markmesh.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "markmeshfield.h"
#include "meshfield.h"
#include "mesh.h"
#include "manager.h"
#include "scene.h"
#include "model.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"
#include "imgui_arima.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MARKMESHFIELD_0		"data\\TEXTURE\\mesh\\stairs.png"	// 読み込むテクスチャファイル名
#define TEXTURE_MARKMESHFIELD_1		"data\\TEXTURE\\mesh\\flooa000.jpg"	// 読み込むテクスチャファイル名
#define TEXTURE_MARKMESHFIELD_2		"data\\TEXTURE\\mesh\\field03.jpg"	// 読み込むテクスチャファイル名
#define TEXTURE_MARKMESHFIELD_3		"data\\TEXTURE\\mesh\\green2.jpg"	// 読み込むテクスチャファイル名

#define MAX_VTX_NUMBER				(4)									// 選択できる頂点のかず
#define MAX_LSHIFTSPEED				(0.5f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMarkMeshField::m_pTexture[MAX_MESH_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 CMarkMeshField::m_pVtxBuff = NULL;				// 頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 CMarkMeshField::m_pIdxBuff = NULL;				// インデックスへのポインタ
CMeshField *CMarkMeshField::m_pMeshField = NULL;						// メッシュフィールドのポインタ
int CMarkMeshField::m_nMarkFieldNum = 0;								// メッシュフィールドの個数

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CMarkMeshField::CMarkMeshField() : CMesh(MESHFIELD_PRIOTITY, CScene::OBJTYPE_MARKMESHFILED)
{
	m_fMove = 3.0f;
	m_nWidthDivide = 5;
	m_nDepthDivide = 5;
	m_fDepthLength = 500.0f;
	m_fWidthLength = 500.0f;
	m_nVtxNumber = 0;
	m_fVtxHeight_No0 = 0;
	m_fVtxHeight_No1 = 0;
	m_fVtxHeight_No2 = 0;
	m_fVtxHeight_No3 = 0;
	m_nClidked = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CMarkMeshField::~CMarkMeshField()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMarkMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CMesh::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMarkMeshField::Uninit(void)
{
	CMesh::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CMarkMeshField::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();

	//設置モード
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 1)
	{
		//位置の反映
		D3DXVECTOR3 &m_pos = CMesh::GetPosition();

		CMesh::Update();

		//設置したかしていないか
		bool bOnOff = false;

		//保存用データ
		int nFieldWD = m_nWidthDivide;
		int nFieldHD = m_nDepthDivide;
		float fFieldWL = m_fWidthLength;
		float fFieldHL = m_fDepthLength;
		float fVtxHeight_No0 = m_fVtxHeight_No0;
		float fVtxHeight_No1 = m_fVtxHeight_No1;
		float fVtxHeight_No2 = m_fVtxHeight_No2;
		float fVtxHeight_No3 = m_fVtxHeight_No3;

		//-------------------------------------
		//        Imguiから値を貰う
		//-------------------------------------
		m_pos = CImgui_Arima::GetFieldPos();
		m_nWidthDivide = CImgui_Arima::GetFieldWD();
		m_nDepthDivide = CImgui_Arima::GetFieldHD();
		m_fWidthLength = (float)CImgui_Arima::GetFieldWL();
		m_fDepthLength = (float)CImgui_Arima::GetFieldHL();
		m_Vtx = CImgui_Arima::GetFieldVtx();
		m_nSelectNum = CImgui_Arima::GetFieldType();
		m_bSetFeild = CImgui_Arima::GetFeildSet();

		m_nClidked = CImgui_Arima::GetFieldClidked();
	
		m_fVtxHeight_No0 = m_Vtx.x;
		m_fVtxHeight_No1 = m_Vtx.y;
		m_fVtxHeight_No2 = m_Vtx.z;
		m_fVtxHeight_No3 = m_Vtx.w;

		//-------------------------------------
		//         縦の分割数を変更
		//-------------------------------------
		if (nFieldWD > m_nWidthDivide)
		{//分割数減少
			//削除と生成
			UninitCreate(m_pos);
		}
		if (m_nWidthDivide > nFieldWD)
		{//分割数増加
			//削除と生成
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         横の分割数を変更
		//-------------------------------------
		if (nFieldHD > m_nDepthDivide)
		{//分割数減少
			//削除と生成
			UninitCreate(m_pos);
		}
		if (m_nDepthDivide > nFieldHD)
		{//分割数増加
			//削除と生成
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         縦の長さ変更を変更
		//-------------------------------------
		if (fFieldHL > m_fDepthLength)
		{//分割数減少
			//削除と生成
			UninitCreate(m_pos);
		}
		if (m_fDepthLength > fFieldHL)
		{//分割数増加
			//削除と生成
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         横の長さ変更を変更
		//-------------------------------------
		if (fFieldWL > m_fWidthLength)
		{//分割数減少
			//削除と生成
			UninitCreate(m_pos);
		}
		if (m_fWidthLength > fFieldWL)
		{//分割数増加
			//削除と生成
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         頂点の高さの変更
		//-------------------------------------
		if (fVtxHeight_No0 > m_fVtxHeight_No0)
		{//分割数減少
			//削除と生成
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No0 > fVtxHeight_No0)
		{//分割数増加
			//削除と生成
			UninitCreate(m_pos);
		}

		if (fVtxHeight_No1 > m_fVtxHeight_No1)
		{//分割数減少
		 //削除と生成
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No1 > fVtxHeight_No1)
		{//分割数増加
		 //削除と生成
			UninitCreate(m_pos);
		}

		if (fVtxHeight_No2 > m_fVtxHeight_No2)
		{//分割数減少
		 //削除と生成
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No2 > fVtxHeight_No2)
		{//分割数増加
		 //削除と生成
			UninitCreate(m_pos);
		}

		if (fVtxHeight_No3 > m_fVtxHeight_No3)
		{//分割数減少
		 //削除と生成
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No3 > fVtxHeight_No3)
		{//分割数増加
		 //削除と生成
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         テクスチャの変更
		//-------------------------------------
		switch (m_nSelectNum)
		{
		case 0:
			//テクスチャの種類
			m_nTexType = 0;
			//テクスチャの設定
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 1:
			//テクスチャの種類
			m_nTexType = 1;
			//テクスチャの設定
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 2:
			//テクスチャの種類
			m_nTexType = 2;
			//テクスチャの設定
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 3:
			//テクスチャの種類
			m_nTexType = 3;
			//テクスチャの設定
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		}

		//-------------------------------------
		//         オブジェクト生成
		//-------------------------------------
		if (m_bSetFeild == true)
		{
			//オブジェクトの生成
			m_pMeshField = CMeshField::Create(m_pos, m_nWidthDivide, m_nDepthDivide, m_fWidthLength, m_fDepthLength, m_fVtxHeight_No0, m_fVtxHeight_No1, m_fVtxHeight_No2, m_fVtxHeight_No3, m_nSelectNum, 0);
			//置いた状態
			bOnOff = true;
			//置いた数の計算
			m_nMarkFieldNum += 1;
		}

		//位置を保存
		if (CImgui_Arima::GetFieldClidked() % 2 == 1)
		{
			m_pMeshField->TextSave();
		}

		m_pos += m_move;

		//慣性
		m_move.x += (0.0f - m_move.x) * 0.8f;
		m_move.y += (0.0f - m_move.y) * 0.8f;
		m_move.z += (0.0f - m_move.z) * 0.8f;

	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CMarkMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//設置モード
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 1)
	{
		CMesh::Draw();
	}
}
//===============================================================================
//　削除と生成
//===============================================================================
void CMarkMeshField::UninitCreate(D3DXVECTOR3 pos)
{
	//削除
	CMarkMeshField::Uninit();

	//生成
	CMarkMeshField::Create(pos, m_nWidthDivide, m_nDepthDivide, m_fWidthLength, m_fDepthLength,
		m_fVtxHeight_No0, m_fVtxHeight_No1, m_fVtxHeight_No2, m_fVtxHeight_No3, m_nSelectNum, m_nVtxNumber, 0);
}
//===============================================================================
//　クリエイト
//===============================================================================
CMarkMeshField * CMarkMeshField::Create(D3DXVECTOR3 pos,int nMeshX, int nMeshZ,float fMeshWidth, float fMeshDepth, float fVtx0, float fVtxMeshX, float fVtxMeshZ, float fVtxMeshXMeshZ, int nTexType, int nVtxNumber,int nMeshType)
{
	CMarkMeshField *pMeshField = NULL;

	//NULLチェック
	if (pMeshField == NULL)
	{//メモリの動的確保

		pMeshField = new CMarkMeshField;

		if (pMeshField != NULL)
		{
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
			//横の分割数を代入
			pMeshField->m_nWidthDivide = nMeshX;
			//縦の分割数を代入
			pMeshField->m_nDepthDivide = nMeshZ;
			//横幅の代入
			pMeshField->m_fWidthLength = fMeshWidth;
			//奥行の代入
			pMeshField->m_fDepthLength = fMeshDepth;
			//現在の選択しているテクスチャ
			pMeshField->m_nSelectNum = nTexType;
			//頂点の番号を代入
			pMeshField->m_nVtxNumber = nVtxNumber;
			//各頂点の高さの代入
			pMeshField->m_fVtxHeight_No0 = fVtx0;
			pMeshField->m_fVtxHeight_No1 = fVtxMeshX;
			pMeshField->m_fVtxHeight_No2 = fVtxMeshZ;
			pMeshField->m_fVtxHeight_No3 = fVtxMeshXMeshZ;
		}
	}

	return pMeshField;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CMarkMeshField::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_3, &m_pTexture[3]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CMarkMeshField::UnLoad(void)
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

