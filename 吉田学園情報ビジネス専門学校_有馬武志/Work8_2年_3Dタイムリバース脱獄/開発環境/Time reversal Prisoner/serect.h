//=============================================================================
//
// 選択処理 [serect.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _SERECT_H_
#define _SERECT_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_SERECT_TEXTURE	(3)

//=====================
//  CSceneの派生クラス
//=====================
class CSerect : public CScene
{
public://誰でも扱える
	typedef enum
	{
		SERECT_NORMAL = 0,		//選択していない状態
		SERECT_SELECT,			//選択した状態
		SERECT_MAX				//選択時の最大数
	}PAUSESTATE;

	typedef enum
	{
		SERECT_START = 0,		//【ゲームをやりなおす】
		SERECT_TITLE,			//【タイトルに戻る】
		MAX_MEMU				//選択肢の最大数
	}SERECT;

	static HRESULT Load(void);
	static void UnLoad(void);
	CSerect(int nPriority = 7, CScene::OBJTYPE objType = CScene::OBJTYPE_SERECT);
	~CSerect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSerect *Create(int nCreaorOver);
	static int Get(void) { return m_SelectNum; };
	static bool GetSelectEnd() { return m_bSerectEnd; }

	//コンテニュー
	static bool GetContinue(void) { return m_bSerectContinue; }
	static void SetContinue(bool bContinue) { m_bSerectContinue = bContinue; }

private://個人でのみ使う
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_SERECT_TEXTURE];	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							//頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;								//位置
	D3DXCOLOR				m_col;								//色
	float					m_SelectColor;						//選択しているときの色
	int						m_nCntState;						//カウントしている状態
	static int				m_SelectNum;						//セレクトの数
	bool					m_bUse;								//使用しているかどうか
	SERECT					m_Serect;							//メニューの構造体
	PAUSESTATE				m_state;							//ポーズの状態
	D3DXVECTOR2				m_nSize;							//サイズ
	int						m_nCreaorOver;						//ゲームクリアかゲームオーバーの時
	int						m_nSerectCounter;					//ボタンを押したときのカウンター
	bool					m_bSerectOver;						//ゲームオーバーの時にカウントを増やすため
	static bool				m_bSerectContinue;					//セレクト画面でコンテニューの状態
	static bool				m_bSerectEnd;						//選び終わった状態
	int						m_nSetCnt;							//脱獄失敗をだすカウンター
	int						m_nCnt;								//
};
#endif