//=============================================================================
//
// 2Dゲージ処理 [2DGage.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "2DGage.h"
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

//==================================================================================================//
//    * ゲージのセット関数 *
//==================================================================================================//
void C2DGage::Set(D3DXVECTOR3 pos, float fLengthMaxX, float flengthMaxY, float *pGage, float *pMaxGage, int nDirection, STATE state)	//ゲージセット処理
{
	m_pGage = pGage;			//ゲージの現在の値のアドレス
	m_pMaxGage = pMaxGage;		//ゲージの最大値のアドレス
	m_nDirection = nDirection;	//ゲージの向き
	m_state = state;

	if (m_p2D != NULL)
	{//既にメモリが使われているなら
		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//一つ一つのintを削除
			delete m_p2D[nCount];
		}//本体削除
		delete[] m_p2D;
		m_p2D = NULL;
	}
	m_p2D = new C2D*[MAX_GAGE];
	if (m_p2D != NULL)
	{//生成できた！
		D3DXCOLOR	col;
		float		fLengthX;

		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//桁数分回転
			col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			m_p2D[nCount] = new C2D;
			m_p2D[nCount]->Init();
			col = GetGageColor(nCount, true);

			//セット処理
			if (m_p2D != NULL)
			{//生成できた！
				if (GetStartLength() || nCount == 0)	{ fLengthX = fLengthMaxX; }
				else					{ fLengthX = 0.0f; }
				m_p2D[nCount]->Set(pos, fLengthX, flengthMaxY, D3DX_PI, 0, 1, 1, col);
				m_p2D[nCount]->SetGage(fLengthX, m_nDirection);		//ゲージ型に変換
				//m_p2D[nCount]->BindTexture(Load(TEX_GAGE));	//画像貼り付け
			}
		}
	}
}
//=============================================================================
// ゲージの初期化処理
//=============================================================================
HRESULT  C2DGage::Init(void)
{
	return S_OK;
}
//=============================================================================
// ゲージの終了処理
//=============================================================================
void C2DGage::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p2D[nCount]->Uninit();
	}
	delete this;
}

//=============================================================================
// ゲージの更新処理
//=============================================================================
void C2DGage::Update(void)
{
	//Lifeゲージの設定
	if (m_p2D[2] != NULL && m_p2D[1] != NULL)
	{
		float fLengthX_2 = m_p2D[2]->GetfLengthX()[0];
		float fLengthX_1 = m_p2D[1]->GetfLengthX()[0];
		float WKfLength;

		float fGage = m_p2D[0]->GetfLengthX()[0] * ((float)m_pGage[0] / (float)m_pMaxGage[0]);

		//2の更新
		if (fGage < fLengthX_2)
		{ //被ダメ　一気に
			m_p2D[2]->SetGage(fGage, m_nDirection);
		}
		else if (fGage > fLengthX_2)
		{ //回復　ゆっくり
			WKfLength = (fGage - fLengthX_2) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_2 += WKfLength;
			if (fLengthX_2 > fGage) { fLengthX_2 = fGage; }
			m_p2D[2]->SetGage(fLengthX_2, m_nDirection);
		}

		//1の更新
		if (fGage > fLengthX_1)
		{//回復　一気に
			m_p2D[1]->SetColor(GetGageColor(1, false));
			m_p2D[1]->SetGage(fGage, m_nDirection);
		}
		else if (fGage < fLengthX_1)
		{//被ダメ　ゆっくり
			m_p2D[1]->SetColor(GetGageColor(1, true));
			WKfLength = (fLengthX_1 - fGage) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_1 -= WKfLength;
			if (fLengthX_1 < fGage) { fLengthX_1 = fGage; }
			m_p2D[1]->SetGage(fLengthX_1, m_nDirection);
		}

		if (m_state == STATE_STAMINA)
		{//スタミナなら
			if (fGage + 0.5f >= m_p2D[0]->GetfLengthX()[0])
			{//消える
				for (int nCount = 0; nCount < 3; nCount++)
				{
					m_p2D[nCount]->PlusColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.1f));
				}
			}
			else
			{//出る
				for (int nCount = 0; nCount < 3; nCount++)
				{
					m_p2D[nCount]->PlusColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.1f));
				}
			}
		}//スタミナなら
	}
}

//=============================================================================
// ゲージの描画処理
//=============================================================================
void C2DGage::Draw(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p2D[nCount]->Draw();
	}
}
//=============================================================================
// 状態によるゲージ事のカラー返し処理
//=============================================================================
D3DXCOLOR	C2DGage::GetGageColor(int nCntGage, bool bChange)
{
	switch (m_state)
	{
	case STATE_LIFE:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		case 1: 
			if (bChange) { return D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f); }
			else		 { return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		case 2: return D3DXCOLOR(0.32f, 1.0f, 0.19f, 1.0f);
		}
			break;
	case STATE_SP:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		case 1:
			if (bChange) { return D3DXCOLOR(0.9f, 0.0f, 1.0f, 1.0f); }
			else { return D3DXCOLOR(1.0f, 0.98f, 0.02f, 1.0f); }
		case 2: return D3DXCOLOR(0.15f, 0.3f, 1.0f, 1.0f);
		}
		break;
	case STATE_STAMINA:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		case 1:
			if (bChange) { return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f); }
			else { return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		case 2: return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;
	case STATE_EXP:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f);
		case 1:
			if (bChange) { return D3DXCOLOR(0.85f, 0.0f, 1.0f, 1.0f); }
			else { return D3DXCOLOR(1.0f, 0.98f, 0.02f, 1.0f); }
		case 2: return D3DXCOLOR(0.0f, 0.55f, 1.0f, 1.0f);
		}
		break;
	case STATE_STATUS:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		case 1:
			if (bChange) { return D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f); }
			else { return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		case 2: return D3DXCOLOR(0.0f, 0.55f, 1.0f, 1.0f);
		}
		break;
	case STATE_CHARGE:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		case 1:
			if (bChange) { return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.75f); }
			else { return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); }
		case 2: return D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
		break;
	}

	return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//=============================================================================
// 状態によるゲージの初期値処理
//=============================================================================
bool	C2DGage::GetStartLength(void)
{
	switch (m_state)
	{
	case STATE_LIFE:	return true;
	case STATE_EXP:		return false;
	case STATE_STATUS:	return false;
	}
	return true;
}
