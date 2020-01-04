//=============================================================================
//
// ゲージの処理 [gauge.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_GAUGE			(200)		//ライフの上限
#define BAR_WIDTH_GAUGE		(300)		//横幅
#define BAR_HEIGHT_GAUGE	(20)		//縦幅
#define NUM_TEXTURE_GAUGE	(1)			//使用テクスチャ枚数
#define NUM_POLYGON_GAUGE	(4)			//頂点数
#define GAUGE_SUBTRACT_TIME	(10)		//減らすカウント時間
#define GAUGE_DIAMOND		(15)		//ゲージの角度

//=====================
//  CSceneの派生クラス
//=====================
class CGauge : CScene
{
public://誰でも扱える
	CGauge();
	~CGauge();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge *Create(D3DXVECTOR3 pos);
	void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice);
	static void AddGauge(float fValue);
	float GetGauge(void) { return m_aGauge[3].fGauge; }
	static void SetGaugeOnOff(bool bGaugeOnOff) { m_bGaugeOnOff = bGaugeOnOff; }
	static bool GetGaugeOnOff(void) { return m_bGaugeOnOff; }
	static bool GetGaugeDownOn(void) { return m_bGaugeDownOn; }
	static void SetGaugeDownOn(bool bGaugeDownOn) { m_bGaugeDownOn = bGaugeDownOn; }
	static void SetRecastTime(int nGageRecastTime) { m_nGaugeRecastTime = nGageRecastTime; }
	static bool GetGaugeActionFade(void) { return m_bGaugeActionFade; }
	static void SetGaugeActionFade(bool bGaugeActionFade) { m_bGaugeActionFade = bGaugeActionFade; }

	//疲れた状態を渡す関数
	static bool GetTired(void) { return m_bTired; }
	static void SetTired(bool bTired) { m_bTired = bTired; }

	//カラー変更用
	void ColorUpdate(float fCntColor);
	void ColorInit(void);

private:
	typedef struct 
	{
		D3DXVECTOR3 pos;		// 左上の位置
		D3DXCOLOR col;			// 色
		float fGauge;			// 現在のライフ
		float fLength;			// バーの長さ	[0:現在のライフ　1:ダメージで減った分]
		int nType;				// テクスチャの種類（-1でなし）
	}Gauge;

	static LPDIRECT3DTEXTURE9		m_pTexture[NUM_TEXTURE_GAUGE];		//共有テクスチャのポインタ
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;							//頂点バッファのポインタ
	static int						m_nCntSubtraction;					//バーを減らし始めるカウンタ
	static Gauge					m_aGauge[NUM_POLYGON_GAUGE];		//体力
	static int						m_nMaxGauge;						//ゲージの最大
	D3DXVECTOR3						m_pos;								//位置
	static bool						m_bGaugeOnOff;						//ゲージが減っている状態
	static bool						m_bGaugeDownOn;						//ゲージを減らすためのONoFF
	static int						m_nGaugeRecastTime;					//ゲージのリキャストタイム
	static bool						m_bGaugeActionFade;					//ゲージが持つアクションフェード
	float							m_fCntColor;						//カラーを点滅させるときのため
	static bool						m_bTired;							//疲れた状態

};
#endif