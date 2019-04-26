//=============================================================================
//
// Select処理 [Select.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "3DPolygon.h"
//*****************************************************************************
// クラスの定義
//*****************************************************************************
#define MAX_SELECT	(4)
#define MAX_LOGO_UV	(6)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSelect_UI : public CScene
{
public:
	typedef enum
	{
		SELECT_FIRST,
		SELECT_MAX
	}SELECT;
	typedef enum
	{
		BRANCH_LABYRINTH,
		BRANCH_VERSUS,
		BRANCH_SURVIVAL,
		BRANCH_PRACTICE,
		BRANCH_TITLE,
		BRANCH_MAX
	}BRANCH;
	CSelect_UI(int nPrioryity = 0) : CScene::CScene(nPrioryity) {};
	~CSelect_UI() {};

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
private://*****************************************************************************
	void	SetSelect(SELECT select);
	//変数宣言//***********************************************************************
	SELECT	m_Select;		//現在の選択状態
	float	m_fCntState;	//時間カウント
	float	m_fAngle;		//角度
	float	m_fGAngle;		//目標の角度(選択している項目)
	int		m_nMax3D;		//3Dポリゴンの最大値
	C3D		**m_p3D;			//3Dポリゴンのポインタ
	CSceneAnim2D *m_p2D[2];
	CScene2D *m_pScene2D;
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSelect
{
public:
	typedef enum
	{
		SELECT_FIRST,
		SELECT_MAX
	}SELECT;
	CSelect() { m_pUI = NULL; }; ~CSelect() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
private://*****************************************************************************
		//変数宣言//***********************************************************************
	float	m_fCntState;	//時間カウント
	CSelect_UI *m_pUI;
};

#endif
