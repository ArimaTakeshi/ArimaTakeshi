//=============================================================================
//
// 血の処理 [blood.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "blood.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "mesh.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BLOOD_TEXTURE_NAME_1	"data\\TEXTURE\\blood.png"			//読み込むテクスチャファイル名
#define BLOOD_MAX_SIZE_X		(50)								//血の広がる最大の範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3DTEXTURE9	CBlood::m_pTexture[MAX_BILLBOORD_TEX] = {};
float CBlood::m_fMeshHeight = 0.0f;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CBlood::CBlood() : CScene3D(SHADOW_PRIOTITY, CScene::OBJTYPE_BLOOD)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//　デストラクタ
//===============================================================================
CBlood::~CBlood()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBlood::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::Init();

	//これはビルボードかエフェクトかの判別
	CScene3D::SetTypeNumber(CScene3D::TYPE_BLOOD);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBlood::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CBlood::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	D3DXVECTOR3 pos;

	pos = m_pos;

	if (m_fDepth < BLOOD_MAX_SIZE_X)
	{// 目的の大きさより大きければ
	 // 縮小させる
		m_fDepth += 0.05f;
	}
	if (m_fWidth < BLOOD_MAX_SIZE_X)
	{// 目的の大きさより大きければ
	 // 縮小させる
		m_fWidth += 0.05f;
	}

	//影とメッシュの判定
	CBlood::CollisitionMesh();

	CScene3D::SetGroundPosSize(pos,D3DXVECTOR2(m_fWidth, m_fDepth));
}
//=============================================================================
// 描画処理
//=============================================================================
void CBlood::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCOLOR col[4];

	col[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	col[1] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	col[2] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	col[3] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	CScene3D::Draw();

	CScene3D::SetColor(&col[0]);

}
//===============================================================================
//　クリエイト
//===============================================================================
CBlood * CBlood::Create(D3DXVECTOR3 pos, float fWidth, float fDepth,int nTexType)
{
	CBlood *pBlood = NULL;

	//NULLチェック
	if (pBlood == NULL)
	{//メモリの動的確保

		pBlood = new CBlood;

		if (pBlood != NULL)
		{
			//オブジェクトクラスの生成
			pBlood->Init();
			//テクスチャの割り当て
			pBlood->BindTexture(m_pTexture[nTexType]);
			//位置からサイズを出す
			pBlood->SetGroundPosSize(pos, D3DXVECTOR2(fWidth, fDepth));
			//横幅の設定
			pBlood->m_fWidth = fWidth;
			//奥行の設定
			pBlood->m_fDepth = fDepth;
			//位置の割り当て
			pBlood->SetPosition(pos);
			//位置の設定
			pBlood->m_pos = pos;
		}
	}

	return pBlood;
}
//=============================================================================
// 影の位置を設定
//=============================================================================
void CBlood::CollisitionMesh(void)
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
		{
			//タイプがメッシュだったら
			if (pScene->GetObjType() == OBJTYPE_MESH)
			{
				//高さを取得
				m_fMeshHeight = m_pos.y;
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
// 影の位置を設定
//=============================================================================
void CBlood::SetPositionShadow(D3DXVECTOR3 pos)
{
	//位置を動かす
	m_pos = pos;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CBlood::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BLOOD_TEXTURE_NAME_1, &m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CBlood::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD_TEX; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
