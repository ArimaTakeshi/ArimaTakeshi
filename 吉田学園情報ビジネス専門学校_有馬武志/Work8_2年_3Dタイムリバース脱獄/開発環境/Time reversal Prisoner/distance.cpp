//=============================================================================
//
// 距離処理 [distance.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "distance.h"
#include "billnumber.h"
#include "player.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DISTANCE_CENTER_WIDTH	(SCREEN_WIDTH / 2)		// Xの中心座標
#define DISTANCE_SPACE			(5.0f)					// 数字と数字の間のサイズ
#define DISTANCE_POSITION_Y		(70.0f)					// タイマーのY座標

//=============================================================================
//	静的メンバ変数
//=============================================================================
int CDistance::m_nDistance = 0;

//=============================================================================
// 生成処理
//=============================================================================
CDistance *CDistance::Create(D3DXVECTOR3 pos)
{
	CDistance *pDistance = NULL;

	//NULLチェック
	if (pDistance == NULL)
	{//動的確保
		pDistance = new CDistance;

		//NULLチェック
		if (pDistance != NULL)
		{
			//位置の設定
			pDistance->m_pos = pos;
			//初期化処理
			pDistance->Init();
		}
	}

	return pDistance;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CDistance::CDistance(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nDistanceCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CDistance::~CDistance()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CDistance::Init(void)
{
	//ビルボード数字のテクスチャの読み込み
	CBillNumber::Load();

	m_nDistance = 0;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apBillNumber[nCntTime] = new CBillNumber;
		m_apBillNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - DISTANCE_SPACE * nCntTime), m_pos.y, m_pos.z));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CDistance::Uninit(void)
{
	//ビルボード数字のテクスチャの破棄
	CBillNumber::Unload();

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apBillNumber[nCntTime]->Uninit();
		delete m_apBillNumber[nCntTime];
		m_apBillNumber[nCntTime] = NULL;
	}

	//削除
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CDistance::Update(void)
{
	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();
	//D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

	if (GameMode == CManager::MODE_GAME)
	{//チュートリアル指示表示
		m_nDistanceCount++;

		//if (m_nDistanceCount % 60 == 0)
		{// 1秒ごとに加算
			//m_nDistance++;
		}

		//距離を測るための三角形の式
		//atan2f(-m_pos.x - -PlayerPos.x, -m_pos.z - -PlayerPos.z) + D3DX_PI;

		if (m_nDistance >= 0)
		{
			//m_nDistance = (m_pos.x - PlayerPos.x) + (m_pos.z - PlayerPos.z);
		}
		else if (m_nDistance <= -1)
		{
			//m_nDistance = (m_pos.x - PlayerPos.x) + (m_pos.z - PlayerPos.z)* -1;
		}

		int nTexData = m_nDistance;
		for (int nCntDistance = 0; nCntDistance < DISTANCE_MAX; nCntDistance++)
		{// テクスチャに反映
			m_apBillNumber[nCntDistance]->SetBillNumber(nTexData);
			nTexData /= 10;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CDistance::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apBillNumber[nCntTime]->Draw();
	}
}