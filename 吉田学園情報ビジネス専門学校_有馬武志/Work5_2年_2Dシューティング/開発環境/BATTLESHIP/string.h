//=============================================================================
//
// メイン処理 [string.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _STRING_H_
#define _STRING_H_

#include "main.h"
#include <string.h>		// 文字列をコピーするのに必要

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_FONT	(1)						// フォントの設定
#define MAX_STRING	(32)					// 文字列の最大数

//=====================
// 基本クラス
//=====================
class CString
{
public:
	typedef enum
	{
		TYPE_MODE = 0,
		TYPE_SAVE_FILE,
		TYPE_NUM,
		TYPE_SELECT,
		TYPE_MAX
	}STRIG_TYPE;

	CString();										//コンストラクタ
	~CString();										//デストラクタ
	HRESULT Init();									//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
	void SetString(char *str, RECT rect, int nFont, D3DXCOLOR col);		// 描画処理で呼ぶ

private:
	typedef struct
	{
		char			m_cString[64];				//表示する文字列
		D3DXCOLOR		m_col;						//色
		RECT			m_rect;						//文字の表示範囲
		int				m_nFont;					//使うフォント
		bool			m_bUse;						//使っているかいないか
		bool			m_bDisplay;					//表示か非表示
	}String;

	String			m_aString[MAX_STRING];			//文字列の情報
	String			m_cSymbol;						//記号「:」用
	String			m_aButton[TYPE_MAX];			//対応キーを表示
	LPD3DXFONT		m_pFont[MAX_FONT];			//フォントへのポインタ

};
#endif

