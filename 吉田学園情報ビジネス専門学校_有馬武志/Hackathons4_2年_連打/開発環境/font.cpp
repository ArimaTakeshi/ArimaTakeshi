//=========================================================================================================//
//
// 背景処理 [bg.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include "Font.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define SPEECH_FLOW		(3)
//*********************************************************************************************************//
// 静的メンバ変数
//*********************************************************************************************************//
LPD3DXFONT	CFont::m_pFont[MAX_FONT_TYPE] = {};			// フォントへのポインタ

//=========================================================================================================//
// 初期化処理
//=========================================================================================================//
void	CFont::Load(int nID)
{
	if (m_pFont[nID] == NULL)
	{
		switch (nID)
		{
		case 0:
			D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 34, 11, 0, 0, FALSE, MONO_FONT,
				OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont[nID]);
			break;
		case 1:
			D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 44, 16, 0, 0, FALSE, MONO_FONT,
				OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont[nID]);
			break;
		case 2:
			D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 144, 33, 0, 0, FALSE, MONO_FONT,
				OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont[nID]);
			break;
		case 3:
			D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 100, 22, 0, 0, FALSE, MONO_FONT,
				OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont[nID]);
			break;
		}
	}
}
//=========================================================================================================//
// 初期化処理
//=========================================================================================================//
void	CFont::UnLoad(void)
{
	for (int nCntFont = 0; nCntFont < MAX_FONT_TYPE; nCntFont++)
	{
		if (m_pFont[nCntFont] != NULL)
		{// デバッグ表示用フォントの開放
			m_pFont[nCntFont]->Release();
			m_pFont[nCntFont] = NULL;
		}
	}
}
//=========================================================================================================//
// 初期化処理
//=========================================================================================================//
HRESULT CFont::Init(void)
{
	m_bDisplay = false;
	m_state = STATE_NONE;
	return S_OK;
}
//=========================================================================================================//
// 終了処理
//=========================================================================================================//
void CFont::Uninit(void)
{
	Release();
}
//=========================================================================================================//
// 更新処理
//=========================================================================================================//
void CFont::Update(void)
{
	if (m_state != STATE_NONE)
	{//状態が通常ではない...!!
		switch (m_state)
		{
		case STATE_UP:
			break;
		case STATE_RANKIN:
			m_fCntState += 1.0f;
			if ((int)m_fCntState % 10 == 0) { m_col = D3DXCOLOR(0.98f, 1.0f, 0.02f, 1.0f); }
			else if ((int)m_fCntState % 5 == 0) { m_col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
			break;
		case STATE_FADE:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_state = STATE_FADEOUT;
			}
			break;
		case STATE_FADEOUT2:
			m_col.a -= 0.03f;
			if (m_col.a <= 0.0f) 
			{
				m_col.a = 0.0f;
				m_state = STATE_NONE;
			}
			break;
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f)
			{
				Uninit();
			}
			break;
		}
	}
}

//=========================================================================================================//
// 描画処理
//=========================================================================================================//
void CFont::Draw(void)
{
	D3DCOLOR col;
	RECT rect;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	char aStr[84];
	char aStr0[84];		//\n確認用
	int nLength;

	// テキスト描画
	// hDC      : デバイスコンテキストのハンドル
	// lpString : 描画する文字列へのポインタ
	// nCount   : 文字列の文字数
	// lpRect   : 長方形領域
	// uFormat  : テキストの整形方法を指定

	if (m_bDisplay == true)
	{// 文字列を代入 表示
		strcpy(&aStr[0], &m_aStr[0]);
		if (m_nMaxFont > -1)
		{//文字数が決められている
			nLength = (int)strlen(&aStr[0]);
			if (nLength > m_nMaxFont)
			{//文字列のほうが長い
				strcpy(&aStr[m_nMaxFont], "\0");
				m_nCntTime--;
				if (m_nCntTime <= 0)
				{//カウントが進んだ
					strcpy(&aStr0[0], &m_aStr[0]);
					strcpy(&aStr0[m_nMaxFont + 1], "\0");
					if (strcmp(&aStr0[m_nMaxFont], "\n") == 0) { m_nMaxFont++; }
					m_nCntTime = SPEECH_FLOW;
					m_nMaxFont += 2;
					if (nLength <= m_nMaxFont) {m_nMaxFont = -1; }
				}
			}
		}

		if (m_bshadow == true)
		{//影が要望なら
			col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			rect = m_rect;
			rect.left += 2; rect.top += 2; rect.right += 2; rect.bottom += 2;
			m_pFont[m_nType]->DrawText(NULL, &aStr[0], -1, &rect, m_nFormat, col);
		}
		col = m_col;	//色の型を変換
		m_pFont[m_nType]->DrawText(NULL, &aStr[0], -1, &m_rect, m_nFormat, col);
		//DT_LEFT;
	}
}
//=========================================================================================================//
// 文字代入処理  Set!!
//=========================================================================================================//
void CFont::Set(RECT rect, D3DXCOLOR col, char *aStr, int nType, int nFormat, int nMaxFont, bool bShadow, STATE state)
{//文字セット
	m_bDisplay = true;
	m_state = state;
	m_nType = nType;
	m_nFormat = nFormat;
	m_nMaxFont = nMaxFont;
	m_nCntTime = SPEECH_FLOW;
	m_rect = rect;
	strcpy(&m_aStr[0], &aStr[0]);
	m_col = col;
	m_fCntState = 0.0f;
	m_bshadow = bShadow;

	Load(nType);
}
//=========================================================================================================//
//	文字部分のみ変更
//=========================================================================================================//
void	CFont::SetFont(char *aStr, int nMaxFont)
{
	strcpy(&m_aStr[0], &aStr[0]);
	m_nMaxFont = nMaxFont;
}
