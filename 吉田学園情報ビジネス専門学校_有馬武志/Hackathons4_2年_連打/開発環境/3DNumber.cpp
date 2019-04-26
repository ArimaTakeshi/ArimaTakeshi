//=============================================================================
//
// 数字関係処理 [Number.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "3DPolygon.h"
#include "3DNumber.h"
#include "Number.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	C3DNumber::m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void C3DNumber::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state)	//スコア(数字)のTEXTURE
{
	m_state = state;
	m_nNumber = nScore;
	m_pos = pos;

	if (m_p3D != NULL)
	{//既にメモリが使われているなら
		for (int nCount = 0; nCount < m_nNum3D; nCount++)
		{//一つ一つのintを削除
			delete m_p3D[nCount];
		}//本体削除
		delete[] m_p3D;
		m_p3D = NULL;
	}
	m_nNum3D = nDigits;
	m_p3D = new C3D*[m_nNum3D];
	if (m_p3D != NULL)
	{//生成できた！
		int nNumber = m_nNumber;
		for (int nCount = 0; nCount < m_nNum3D; nCount++)
		{//桁数分回転
			m_p3D[nCount] = new C3D;
			m_p3D[nCount]->Init();

			//セット処理
			if (m_p3D != NULL)
			{//生成できた！
				m_p3D[nCount]->Set(pos + D3DXVECTOR3(nCount * (fLengthX * -2.0f), 0.0f, 0.0f),D3DXVECTOR3(0.0f, 0.0f, 0.0f),col, fLengthX, flengthY,C3D::TEXTURE_MAX, nNumber % 10, NUMBER_UV_X, NUMBER_UV_Y, CScene::DRAW_TYPE_NORMAL);
				m_p3D[nCount]->BindTexture(C2D::Load(C2D::TEX_SCORE));	//画像貼り付け
			}

			nNumber /= 10;
		}
	}
}
//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void C3DNumber::SetNumber(int nScore)
{
	m_nNumber = nScore;
	if (m_p3D != NULL)
	{
		int nNumber = m_nNumber;
		for (int nCount = 0; nCount < m_nNum3D; nCount++)
		{
			m_p3D[nCount]->SetUV(nNumber % 10, NUMBER_UV_X, NUMBER_UV_Y);
			nNumber /= 10;
		}
	}
}
//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void C3DNumber::AddNumber(int nValue)
{
	m_nNumber += nValue;
	SetNumber(m_nNumber);
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT  C3DNumber::Init(void)
{
	m_nNumber = 0;
	m_nNum3D = 0;
	m_p3D = NULL;
	m_state = STATE_MAX;
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void C3DNumber::Uninit(void)
{
	for (int nCount = 0; nCount < m_nNum3D; nCount++)
	{
		m_p3D[nCount]->Uninit();
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void C3DNumber::Update(void)
{
	if (m_state != STATE_MAX)
	{
		int nNumber;

		switch (m_state)
		{
		case STATE_TIMER:
			if (m_nNumber > 0) { m_nNumber--; }
			nNumber = m_nNumber;
			SetNumber(((nNumber / 60)));
			m_nNumber = nNumber;
			break;
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void C3DNumber::Draw(void)
{
	for (int nCount = 0; nCount < m_nNum3D; nCount++)
	{
		m_p3D[nCount]->Draw();
	}
}
