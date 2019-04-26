//=============================================================================
//
// フェード処理 [Fade.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "2DPolygon.h"
#include "Fade.h"
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
LPDIRECT3DTEXTURE9	CFade::m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CFade::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		//if (m_pTexture[tex] == NULL)
		//{//読み込んでないなら
		//	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
		//	switch (tex)
		//	{//読み込み
		//	//case TEX_GAGE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/GAGE000.jpg", &m_pTexture[tex]);		break;

		//	}
		//}
		//return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CFade::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void CFade::Set(void)
{

}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT  CFade::Init(STATE state)
{
	switch (state)
	{
	case STATE_OUT:
		if (m_p2DFade == NULL)
		{
			Create(m_p2DFade);
			if (m_p2DFade != NULL)
			{//フェード生成処理
				m_p2DFade->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.05f, C2DPolygon::STATE_FADEOUT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		break;
	case STATE_NOR_FADE:
		if (m_p2DFade == NULL)
		{
			Create(m_p2DFade);
			if (m_p2DFade != NULL)
			{//フェード生成処理
				m_p2DFade->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.05f, C2DPolygon::STATE_FADEIN, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f));
			}
		}
		break;
	}
	m_state = STATE_FADE_NOW;
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CFade::Uninit(void)
{
	if (m_p2DFade != NULL) { m_p2DFade->Uninit(); m_p2DFade = NULL; }
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CFade::Update(void)
{
	if (m_p2DFade != NULL)
	{
		if (m_p2DFade->GetColor().a == 0.0f)
		{
			m_p2DFade->Uninit();
			m_p2DFade = NULL;
			m_state = STATE_FADE_NONE;
		}
		else if (m_p2DFade->GetState() == CScene2D::STATE_NORMAL)
		{//セットモード　フェードアウト
			CManager::SetMode();
			m_p2DFade->GetState() = C2DPolygon::STATE_FADEOUT;
			//MessageBox(0, "", "", MB_OK);
		}
		else { m_p2DFade->Update(); }
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CFade::Draw(void)
{
	if (m_p2DFade != NULL) { m_p2DFade->Draw(); }
}
