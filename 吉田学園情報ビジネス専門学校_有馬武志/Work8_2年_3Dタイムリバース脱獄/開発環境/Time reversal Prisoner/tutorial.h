//=============================================================================
//
// チュートリアル処理 [tutorial.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "sound.h"

#define TITLEWORD_INITPOS_Y (350.0f)		// タイトル文字の初期高さ
#define SUBTITLE_INITSIZE (1000.0f)			// サブタイトルの初期サイズ
#define ISLAND_STERT (600)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//=====================
// 基本クラス
//=====================
class CTutorial
{
public:
	CTutorial();								// コンストラクタ
	~CTutorial();								// デストラクタ
	HRESULT Init();							// 初期化処理
	void	Uninit(void);					// 終了処理
	void	Update(void);					// 更新処理
	void	Draw(void);						// 描画処理

private:
	int					m_nCount;			// 落ち葉				の カウンター
	int					m_nCnt;				// テクスチャ			の カウンター
	int				m_nLeafposY;			// 落ち葉				の 生成座標
	int				m_nLeafsize;			// 落ち葉				の サイズ
};
#endif