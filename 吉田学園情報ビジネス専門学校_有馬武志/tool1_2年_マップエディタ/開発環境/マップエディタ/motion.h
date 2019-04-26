//=============================================================================
//
// モーションの処理 [motion.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  CMotion 単独クラス
//=====================
class CMotion
{
public://誰でも扱える
	CMotion();
	~CMotion();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private://個人でのみ使う
	
};
#endif