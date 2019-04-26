//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void UninitAll(void);
	void Update(void);
	void Draw(void);
	void ResetViewport(void);
	LPDIRECT3DDEVICE9 &GetDevice(void){ return m_pD3DDevice; }
private:
	//変数宣言//***********************************************************************
	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
};

#endif
