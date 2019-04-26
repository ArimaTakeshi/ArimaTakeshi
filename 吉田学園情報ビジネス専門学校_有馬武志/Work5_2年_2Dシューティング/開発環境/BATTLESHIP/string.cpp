//=============================================================================
//
// フォントの処理 [string.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "string.h"
#include "main.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STRING_FILE	"data/string.txt"		// 文字列の情報を格納するファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CString::CString()
{
	m_aString[MAX_STRING];			// 文字列の情報
	m_cSymbol;						// 記号「:」用
	m_aButton[TYPE_MAX];			// 対応キーを表示

	// 文字列の情報の初期化
	for (int nCntString = 0; nCntString < MAX_STRING; nCntString++)
	{
		m_aString[nCntString].m_cString[0] = {};
		m_aString[nCntString].m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aString[nCntString].m_nFont = 0;
		m_aString[nCntString].m_rect = { 0,0,0,0 };	// { x, y, 高さ, 幅 }
		m_aString[nCntString].m_bUse = false;
		m_aString[nCntString].m_bDisplay = false;
		m_aButton[nCntString] = m_aString[nCntString];
		m_pFont[nCntString] = {};			// フォントへのポインタ
	}
}
//=============================================================================
// デストラクタ
//=============================================================================
CString::~CString()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CString::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 文字列の情報の初期化
	for (int nCntString = 0; nCntString < MAX_STRING; nCntString++)
	{
		m_aString[nCntString].m_cString[0] = '\0';
		m_aString[nCntString].m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aString[nCntString].m_nFont = 0;
		m_aString[nCntString].m_rect = { 0,0,0,0 };	// { x, y, 高さ, 幅 }
		m_aString[nCntString].m_bUse = false;
		m_aString[nCntString].m_bDisplay = false;
	}
	
	for (int nCntString = 0; nCntString < TYPE_MAX; nCntString++)
	{
		m_aButton[nCntString] = m_aString[0];
	}

	m_cSymbol = m_aString[0];
	m_cSymbol.m_cString[0] = ':';
	m_cSymbol.m_bUse = true;

	//文字列フォントの初期化
	for (int nCntString = 0; nCntString < MAX_FONT; nCntString++)
	{
		D3DXCreateFont(pDevice,
			18,                     // 文字高さ
			8,                      // 文字幅
			0,						// フォントスタイル(太さ)
			0,						// ミップマップモデルの数
			FALSE,                  // 斜体にするかどうか
			MONO_FONT,				// 文字セット(言語)
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			"Arial Black",          //フォントの種類
			&m_pFont[nCntString]);

	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CString::Uninit(void)
{
	for (int nCntString = 0; nCntString < MAX_FONT; nCntString++)
	{// 開放
		if (NULL != m_pFont[nCntString])
		{
			m_pFont[nCntString]->Release();
			m_pFont[nCntString] = NULL;
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CString::Update(void)
{
	
}
//=============================================================================
// 描画処理
//=============================================================================
void CString::Draw(void)
{
	for (int nCntString = 0; nCntString < MAX_STRING; nCntString++)
	{// 最大数回す
		if (true == m_aString[nCntString].m_bUse)
		{
			m_cSymbol.m_rect = { 140, 10 + (nCntString * 20), 0, 0 };

			//文字列サイズを計算
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aString[nCntString].m_cString[0],	// 表示する文字列
				-1,										// 表示サイズ(-1で全部)
				&m_aString[nCntString].m_rect,			// 表示範囲
				DT_CALCRECT,							// 表示範囲に調整
				NULL);									// 色

			//そのサイズでレンダリング
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aString[nCntString].m_cString[0],
				-1,										//表示サイズ(-1で全部)
				&m_aString[nCntString].m_rect,			//表示範囲
				DT_LEFT | DT_BOTTOM,					//左詰めで両端揃え
				m_aString[nCntString].m_col);			//色

//記号を入れる-----------------------------------------------------------------------------------
			//文字列サイズを計算
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_cSymbol.m_cString[0],				// 表示する文字列
				-1,										// 表示サイズ(-1で全部)
				&m_cSymbol.m_rect,						// 表示範囲
				DT_CALCRECT,							// 表示範囲に調整
				NULL);									// 色

			//そのサイズでレンダリング
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_cSymbol.m_cString[0],
				-1,										//表示サイズ(-1で全部)
				&m_cSymbol.m_rect,						//表示範囲
				DT_LEFT | DT_BOTTOM,					//左詰めで両端揃え
				m_cSymbol.m_col);						//色
		}
		if (true == m_aButton[nCntString].m_bUse)
		{
			//文字列サイズを計算
			m_pFont[m_aButton[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aButton[nCntString].m_cString[0],	// 表示する文字列
				-1,										// 表示サイズ(-1で全部)
				&m_aButton[nCntString].m_rect,			// 表示範囲
				DT_CALCRECT,							// 表示範囲に調整
				NULL);									// 色

			//そのサイズでレンダリング
			m_pFont[m_aButton[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aButton[nCntString].m_cString[0],
				-1,										//表示サイズ(-1で全部)
				&m_aButton[nCntString].m_rect,			//表示範囲
				DT_LEFT | DT_BOTTOM,					//左詰めで両端揃え
				m_aButton[nCntString].m_col);			//色
		}
	}
}
//=============================================================================
// 文字列の設定
//=============================================================================
void CString::SetString(char *str, RECT rect, int nFont, D3DXCOLOR col)
{
	/***********************************************************
	*
	*	必ず「描画処理」で呼んでください
	*
	************************************************************/

	//文字列サイズを計算
	m_pFont[nFont]->DrawText(
		NULL,
		&str[0],				//表示する文字列
		-1,						//表示サイズ(-1で全部)
		&rect,					//表示範囲
		DT_CALCRECT,			//表示範囲に調整
		NULL);					//色

								//そのサイズでレンダリング
	m_pFont[nFont]->DrawText(
		NULL,
		&str[0],				//表示する文字列
		-1,						//表示サイズ(-1で全部)
		&rect,					//表示範囲
		DT_LEFT | DT_BOTTOM,	//左詰めで両端揃え
		col);					//色
}
