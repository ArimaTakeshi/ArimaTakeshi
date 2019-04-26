//=============================================================================
//
// 数字関係処理 [Number.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "Number.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUMBER_UV_X		(10)
#define NUMBER_UV_Y		(1)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void CNumber::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state)	//スコア(数字)のTEXTURE
{
	m_state = state;
	m_nNumber = nScore;

	if (m_p2D != NULL)
	{//既にメモリが使われているなら
		for (int nCount = 0; nCount < m_nNum2D; nCount++)
		{//一つ一つのintを削除
			delete m_p2D[nCount];
		}//本体削除
		delete[] m_p2D;
		m_p2D = NULL;
	}
	m_nNum2D = nDigits;
	m_p2D = new C2D*[m_nNum2D];
	if (m_p2D != NULL)
	{//生成できた！
		int nNumber = m_nNumber;
		for (int nCount = 0; nCount < m_nNum2D; nCount++)
		{//桁数分回転
			m_p2D[nCount] = new C2D;
			m_p2D[nCount]->Init();

			//セット処理
			if (m_p2D != NULL)
			{//生成できた！
				m_p2D[nCount]->Set(pos + D3DXVECTOR3(nCount * (fLengthX * -2.0f), 0.0f, 0.0f), fLengthX, flengthY, D3DX_PI, nNumber % 10, NUMBER_UV_X, NUMBER_UV_Y, col);
				m_p2D[nCount]->BindTexture(CScene::Load(CScene::TEX_Number));
			}

			nNumber /= 10;
		}
	}
}
//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void CNumber::SetNumber(int nScore)
{
	m_nNumber = nScore;
	if (m_p2D != NULL)
	{
		int nNumber = m_nNumber;
		if (m_state == STATE_TIMER || m_state == STATE_CHARGE) { nNumber /= 60 * FRAME_SPEED; }
		for (int nCount = 0; nCount < m_nNum2D; nCount++)
		{
			m_p2D[nCount]->SetUV(nNumber % 10, NUMBER_UV_X, NUMBER_UV_Y);
			nNumber /= 10;
		}
	}
}
//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void CNumber::AddNumber(int nValue)
{
	m_nNumber += nValue;
	SetNumber(m_nNumber);
}
//=============================================================================
// 全数字の色変更処理
//=============================================================================
void	CNumber::SetColor(D3DXCOLOR col)
{
	for (int nCount = 0; nCount < m_nNum2D; nCount++)
	{//桁数分回転
		m_p2D[nCount]->SetColor(col);
	}
}
//=============================================================================
// 数字の初期化処理
//=============================================================================
HRESULT  CNumber::Init(void)
{
	m_nNumber = 0;
	m_nNum2D = 0;
	m_p2D = NULL;
	m_state = STATE_MAX;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	for (int nCount = 0; nCount < m_nNum2D; nCount++)
	{
		m_p2D[nCount]->Uninit();
	}
	delete this;
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CNumber::Update(void)
{
	if (m_state != STATE_MAX)
	{
		switch (m_state)
		{
		case STATE_TIMER:
			if (m_nNumber > 0) { m_nNumber--; }
			SetNumber(m_nNumber);
			break;
		case STATE_CHARGE:
			if (m_nNumber >= 0) { m_nNumber--; }
			SetNumber(m_nNumber);
			if (m_nNumber == -1)
			{//消えていく
				if (m_col.a > 0.0f)
				{
					m_col.a -= 0.05f;
					if (m_col.a < 0.0f) { m_col.a = 0.0f; }
					SetColor(m_col);
				}
			}
			else
			{//出現
				if (m_col.a < 1.0f)
				{
					m_col.a += 0.05f;
					if (m_col.a > 1.0f) { m_col.a = 1.0f; }
					SetColor(m_col);
				}
			}
			break;
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CNumber::Draw(void)
{
	for (int nCount = 0; nCount < m_nNum2D; nCount++)
	{
		m_p2D[nCount]->Draw();
	}
}
