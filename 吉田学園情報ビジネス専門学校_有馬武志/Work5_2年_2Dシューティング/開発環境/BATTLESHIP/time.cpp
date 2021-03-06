//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "time.h"
#include "number.h"
#include <string>
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_X		(SCREEN_WIDTH)
#define SIZE_Y		(SCREEN_HEIGHT)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CNumber *CTime::m_apNumber[MAX_NUMBER] = {};
int CTime::m_nTime = 0;

//=============================================================================
//デフォルトコンストラクタ
//=============================================================================
CTime::CTime() : CScene(4)//優先優位イニシャライズ
{
	m_nTime = 0;
}
//=============================================================================
//デストラクタ
//=============================================================================
CTime::~CTime()
{

}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	//文字のタイプを入れる
	CNumber::SetType(CNumber::TYPE_KILL);

	for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = new CNumber;

			if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Init(D3DXVECTOR3(150.0f - (nCnt * 35.0f), 30.0f, 0));
			}
		}
	}

	return S_OK;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = {};
		}
	}

	//自分自身の破棄
	Release();
}
//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTime::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
//ポリゴンの生成処理
//=============================================================================
CTime *CTime::Create(void)
{
	CTime *pScore = {};

	if (pScore == NULL)
	{//NULLだったら

	 //メモリの動的確保
		pScore = new CTime;

		if (pScore != NULL)
		{//NULLじゃなかったら

		 //ポリゴンの初期化処理
			pScore->Init();
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULLじゃないです", "警告", MB_OK);
	}

	return pScore;
}
//==============================================================================
// スコアの加算
//==============================================================================
void CTime::AddTime(int nValue)
{
	m_nTime += nValue;		//スコアを代入

	int nTime = m_nTime;

	for (int nCnt = 0; nCnt < MAX_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->SetNumber(nTime);
		nTime /= 10;
	}
}
//==============================================================================
// スコアの情報
//==============================================================================
int CTime::GetTime(void)
{
	return m_nTime;
}



