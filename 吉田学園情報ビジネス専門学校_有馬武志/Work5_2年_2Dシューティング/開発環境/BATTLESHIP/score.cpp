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
#include "score.h"
#include "number.h"
#include <string>
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_X (SCREEN_WIDTH)
#define SIZE_Y (SCREEN_HEIGHT)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CNumber *CScore::m_apNumber[MAX_TEXNUMBER] = {};
int CScore::m_nScore = 0;

//=============================================================================
//デフォルトコンストラクタ
//=============================================================================
CScore::CScore() : CScene(4)//優先優位イニシャライズ
{
	m_nScore = 0;
}
//=============================================================================
//デストラクタ
//=============================================================================
CScore::~CScore()
{

}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	//文字のタイプを入れる
	CNumber::SetType(CNumber::TYPE_SCORE);

	for (int nCnt = 0; nCnt < MAX_TEXNUMBER; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = new CNumber;

			if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Init(D3DXVECTOR3(1255.0f - (nCnt * 35.0f), 30.0f, 0));
			}
		}
	}

	return S_OK;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXNUMBER; nCnt++)
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
void CScore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXNUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TEXNUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
//ポリゴンの生成処理
//=============================================================================
CScore *CScore::Create(void)
{
	CScore *pScore = {};

	if (pScore == NULL)
	{//NULLだったら

	 //メモリの動的確保
		pScore = new CScore;

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
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;		//スコアを代入

	int nScore = m_nScore;

	for (int nCnt = 0; nCnt < MAX_TEXNUMBER; nCnt++)
	{
		m_apNumber[nCnt]->SetNumber(nScore);
		nScore /= 10;
	}
}
//==============================================================================
// スコアの情報
//==============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}



