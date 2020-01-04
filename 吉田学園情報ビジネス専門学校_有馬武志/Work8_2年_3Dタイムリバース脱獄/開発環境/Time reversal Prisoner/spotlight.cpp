//=============================================================================
//
// スポットライトの処理 [spotlight.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "spotlight.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "mesh.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SPOTLIGHT_TEXTURE_NAME_1	"data\\TEXTURE\\Bullet000.png"		//読み込むテクスチャファイル名
#define SPOTLIGHT_MAX_SIZE_X		(50)								//スポットライトの広がる最大の範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3DTEXTURE9	CSpotLight::m_pTexture[MAX_BILLBOORD_TEX] = {};
float CSpotLight::m_fMeshHeight = 0.0f;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CSpotLight::CSpotLight() : CScene3D(SPOTLIGHT_PRIOTITY, CScene::OBJTYPE_SPOTLIGHT)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bSpotLightIn = false;
	m_nSwingTime = 0;
	m_fSwing = 0.0f;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CSpotLight::~CSpotLight()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSpotLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::Init();

	//これはビルボードかエフェクトかの判別
	CScene3D::SetTypeNumber(CScene3D::TYPE_SPOTLIGHT);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSpotLight::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CSpotLight::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	//ライトを振る動作
	if (m_nSwingTime < 120)
	{
		m_fSwing -= 0.09f;
	}
	else if (m_nSwingTime < 240)
	{
		m_fSwing += 0.09f;
	}
	else if (m_nSwingTime >= 240)
	{
		m_nSwingTime = 0;
	}
	
	//横軸を動かす
	m_pos.x += m_fSwing;

	//カウント増加
	m_nSwingTime++;

	//影とメッシュの判定
	CSpotLight::CollisitionMesh();

	CScene3D::SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));

	CDebugProc::Print("m_bSpotLightIn = %s\n", m_bSpotLightIn ? "true" : "false");

}
//=============================================================================
// 描画処理
//=============================================================================
void CSpotLight::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//フォグを使用しない
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CScene3D::Draw();

	//フォグを使用する
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}
//===============================================================================
//　クリエイト
//===============================================================================
CSpotLight * CSpotLight::Create(D3DXVECTOR3 pos, float fWidth, float fDepth,int nTexType, CEnemy *pEnemy)
{
	CSpotLight *pBlood = NULL;

	//NULLチェック
	if (pBlood == NULL)
	{//メモリの動的確保

		pBlood = new CSpotLight;

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

			pBlood->m_pEnemy = pEnemy;
		}
	}

	return pBlood;
}
//=============================================================================
// 影の位置を設定
//=============================================================================
void CSpotLight::CollisitionMesh(void)
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
void CSpotLight::SetPositionSpotLight(D3DXVECTOR3 pos)
{
	//位置を動かす
	m_pos = pos;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CSpotLight::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, SPOTLIGHT_TEXTURE_NAME_1, &m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CSpotLight::UnLoad(void)
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
//=============================================================================
// 床の当たり判定
//=============================================================================
void CSpotLight::CollisionSpotLight(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	// posを取得
	D3DXVECTOR3 SpotLightPos = CScene3D::GetPosition();
	D3DXVECTOR3 SpotLightRot = CScene3D::GetRotation();
	D3DXVECTOR3 SpotLightMove = CScene3D::GetMove();
	D3DXVECTOR2 SpotLightSize = CScene3D::GetSize();
	bool		bCheck = false;

	CSound *pSound = CManager::GetSound();

	if (pPos->x <= SpotLightPos.x + SpotLightSize.x
		&& pPos->x >= SpotLightPos.x - SpotLightSize.x)
	{// 床と同じz軸に存在している
		if (pPos->z <= SpotLightPos.z + SpotLightSize.y
			&& pPos->z >= SpotLightPos.z - SpotLightSize.y)
		{// 床と同じx軸に存在している
			if (pPos->y <= SpotLightPos.y)
			{// 床に触れている
				pMove->x += SpotLightMove.x;
				pMove->y += SpotLightMove.y;
				pMove->z += SpotLightMove.z;
				bCheck = true;

				m_pEnemy->SetLightIn(true);
				m_bSpotLightIn = true;
			}
		}
	}

	if (!bCheck)
	{
		m_pEnemy->SetLightIn(false);
		m_bSpotLightIn = false;
	}
}
