//=============================================================================
//
// タイマー処理 [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "number.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)	// Xの中心座標
#define TIMER_SPACE			(70.0f)				// 数字と数字の間のサイズ
#define TIMER_POSITION_Y	(70.0f)				// タイマーのY座標

//=============================================================================
//	静的メンバ変数
//=============================================================================
int CTime::m_nTime = 0;

//=============================================================================
// 生成処理
//=============================================================================
CTime *CTime::Create(D3DXVECTOR3 pos)
{
	CTime *pTime = NULL;

	//NULLチェック
	if (pTime == NULL)
	{//動的確保
		pTime = new CTime;

		//NULLチェック
		if (pTime != NULL)
		{
			//位置の設定
			pTime->m_pos = pos;
			//初期化処理
			pTime->Init();
		}
	}

	return pTime;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	CNumber::Load();

	m_nTime = 0;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apNumber[nCntTime] = new CNumber;
		m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntTime), m_pos.y, m_pos.z));
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apNumber[nCntTime]->Uninit();
	}

	CNumber::Unload();

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTime::Update(void)
{
	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();

	if (GameMode == CManager::MODE_GAME)
	{//チュートリアル指示表示
		m_nTimeCount++;

		if (m_nTimeCount % 60 == 0)
		{// 1秒ごとに加算
			m_nTime++;
		}

		int nTexData = m_nTime;
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{// テクスチャに反映
			m_apNumber[nCntTime]->SetNumber(nTexData);
			nTexData /= 10;
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apNumber[nCntTime]->Draw();
	}
}

//=============================================================================
// タイム減算処理
//=============================================================================
void CTime::MinusTime(int nTime)
{
	m_nTime -= nTime;
	if (m_nTime < 0)
	{
		m_nTime = 0;
	}
}