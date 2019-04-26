//=============================================================================
//
// レンダリング処理 [DebugLog.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _DEBUGLOG_H_
#define _DEBUGLOG_H_

#include "main.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CDebugLog
{
public:
	typedef enum
	{
		MODE_NONE,		
		MODE_Change,
		MODE_INFO,
		MODE_LOG,
		MODE_MAX
	}MODE;
	CDebugLog() {};
	~CDebugLog() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Printf(MODE mode, const TCHAR* format, ...);
	int  &GetnFPS(void) { return m_nFps; }

private:
	//変数宣言//***********************************************************************
	void LogUpdate(void);

	MODE		m_Mode;			// 現在のモード
	LPD3DXFONT	m_pFont;		// フォントへのポインタ
	char		m_aFPS[16];		// FPSの文字数
	char		m_aMode[64];	// MODEの文字数
	char		m_aStr[1024];	// 文字数

	int			m_nFps;			//FPSカウント
	int			m_nSelect;		// 選択
	bool		m_bDraw;		// 表示状態
};

#endif
