#pragma once
//=============================================================================
//
// 3D数字関係処理 [3DNumber.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _3DNUMBER_H_
#define _3DNUMBER_H_

#include "main.h"
#include "3DPolygon.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class C3DNumber : public CScene
{
public:
	typedef enum
	{
		TEXTURE_SCORE,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_SCORE = 0,	//全てそのまま表示
		STATE_STATUS,		//最大数より上の桁は透明に
		STATE_TIMER,
		STATE_MAX
	}STATE;

	C3DNumber(int nPrioryity = S3D_PRIORITY) : CScene::CScene(nPrioryity) { SetObjType(CScene::OBJTYPE_NUMBER); };
	~C3DNumber() {};

	void	Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, int nScore, int nDigits, D3DXCOLOR col, STATE state);	//スコア(数字)のTEXTURE
	void	SetNumber(int nScore);
	void	AddNumber(int nValue);
	int		&GetnNumber(void) { return m_nNumber; }
	D3DXVECTOR3 &GetPosition(void) { return m_pos; }
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
protected://*****************************************************************************
		  //変数宣言//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// テクスチャへのポインタ
private://*****************************************************************************
		//変数宣言//***********************************************************************
	STATE	m_state;		//表示形式 
	D3DXVECTOR3 m_pos;
	int		m_nNumber;		//数値
	int		m_nNum3D;		//最大桁数
	C3D		**m_p3D;		//桁事のポインタ
};

#endif
