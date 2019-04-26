//=============================================================================
//
// 2Dゲージ処理 [2DGage.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "3DPolygon.h"
#include "2DGage.h"
#include "3DGage.h"
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
LPDIRECT3DTEXTURE9	C3DGage::m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

//==================================================================================================//
//    * ゲージのセット関数 *
//==================================================================================================//
void C3DGage::Set(D3DXVECTOR3 &pos, float fLengthMaxX, float flengthMaxY, float &pGage, float &pMaxGage, STATE state)	//ゲージセット処理
{
	m_pPos = &pos;
	m_pGage = &pGage;			//ゲージの現在の値のアドレス
	m_pMaxGage = &pMaxGage;		//ゲージの最大値のアドレス
	m_state = state;

	if (m_p3D != NULL)
	{//既にメモリが使われているなら
		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//一つ一つのintを削除
			delete m_p3D[nCount];
		}//本体削除
		delete[] m_p3D;
		m_p3D = NULL;
	}
	m_p3D = new C3D*[MAX_GAGE];
	if (m_p3D != NULL)
	{//生成できた！
		D3DXCOLOR	col;
		float		fLengthX;

		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//桁数分回転
			col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			m_p3D[nCount] = new C3D;
			m_p3D[nCount]->Init();
			col = GetGageColor(nCount, true);

			//セット処理
			if (m_p3D != NULL)
			{//生成できた！
				if (GetStartLength() || nCount == 0)	{ fLengthX = fLengthMaxX; }
				else					{ fLengthX = 0.0f; }
				m_p3D[nCount]->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), col, D3DXVECTOR3(fLengthX, flengthMaxY, 0.0f),
					0, 1, 1, CScene::DRAW_TYPE_NORMAL, CScene::TEX_Gage, true);
				m_p3D[nCount]->SetGage(fLengthX, fLengthMaxX);		//ゲージ型に変換
				//m_p3D[nCount]->BindTexture(Load(TEX_GAGE));	//画像貼り付け
			}
		}
	}
}
//=============================================================================
// ゲージの初期化処理
//=============================================================================
HRESULT  C3DGage::Init(void)
{
	return S_OK;
}
//=============================================================================
// ゲージの終了処理
//=============================================================================
void C3DGage::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p3D[nCount]->Uninit();
	}
	delete this;
}

//=============================================================================
// ゲージの更新処理
//=============================================================================
void C3DGage::Update(void)
{
	//Lifeゲージの設定
	if (m_p3D[2] != NULL && m_p3D[1] != NULL)
	{
		float fLengthX_2 = m_p3D[2]->GetLength().x;
		float fLengthX_1 = m_p3D[1]->GetLength().x;
		float fLengthX_0 = m_p3D[0]->GetLength().x;
		float WKfLength;

		float fGage = m_p3D[0]->GetLength().x * ((float)m_pGage[0] / (float)m_pMaxGage[0]);

		//2の更新
		if (fGage < fLengthX_2)
		{ //被ダメ　一気に
			m_p3D[2]->SetGage(fGage, fLengthX_0);
		}
		else if (fGage > fLengthX_2)
		{ //回復　ゆっくり
			WKfLength = (fGage - fLengthX_2) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_2 += WKfLength;
			if (fLengthX_2 > fGage) { fLengthX_2 = fGage; }
			m_p3D[2]->SetGage(fLengthX_2, fLengthX_0);
		}

		//1の更新
		if (fGage > fLengthX_1)
		{//回復　一気に
			m_p3D[1]->SetColor(GetGageColor(1, false));
			m_p3D[1]->SetGage(fGage, fLengthX_0);
		}
		else if (fGage < fLengthX_1)
		{//被ダメ　ゆっくり
			m_p3D[1]->SetColor(GetGageColor(1, true));
			WKfLength = (fLengthX_1 - fGage) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_1 -= WKfLength;
			if (fLengthX_1 < fGage) { fLengthX_1 = fGage; }
			m_p3D[1]->SetGage(fLengthX_1, fLengthX_0);
		}

		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{
			m_p3D[nCount]->GetPosition() = m_pPos[0] + D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		}
	}
}

//=============================================================================
// ゲージの描画処理
//=============================================================================
void C3DGage::Draw(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p3D[nCount]->Draw();
	}
}
//=============================================================================
// 状態によるゲージ事のカラー返し処理
//=============================================================================
D3DXCOLOR	C3DGage::GetGageColor(int nCntGage, bool bChange)
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
	}

	return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//=============================================================================
// 状態によるゲージの初期値処理
//=============================================================================
bool	C3DGage::GetStartLength(void)
{
	switch (m_state)
	{
	case STATE_LIFE:	return true;
	}
	return true;
}
