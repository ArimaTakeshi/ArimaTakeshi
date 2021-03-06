//=========================================================================================================================
//
// 入力処理 [input.h]
// Author : 有馬　武志
//
//=========================================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キーボード初期化処理
void UninitKeyboard(void);								//キーボード終了処理
void UpdateKeyboard(void);								//キーボード更新処理
bool GetKeyboardPress(int Key);							//キーボードプレス
bool GetKeyboardTrigger(int Key);						//キーボードトリガー

#endif