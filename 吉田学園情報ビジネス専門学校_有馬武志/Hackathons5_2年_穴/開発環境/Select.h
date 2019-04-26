//=============================================================================
//
// Select���� [Select.h]
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
// �N���X�̒�`
//*****************************************************************************
#define MAX_SELECT	(4)
#define MAX_LOGO_UV	(6)

//*****************************************************************************
// �N���X�̒�`
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
	//�ϐ��錾//***********************************************************************
	SELECT	m_Select;		//���݂̑I�����
	float	m_fCntState;	//���ԃJ�E���g
	float	m_fAngle;		//�p�x
	float	m_fGAngle;		//�ڕW�̊p�x(�I�����Ă��鍀��)
	int		m_nMax3D;		//3D�|���S���̍ő�l
	C3D		**m_p3D;			//3D�|���S���̃|�C���^
	CSceneAnim2D *m_p2D[2];
	CScene2D *m_pScene2D;
};
//*****************************************************************************
// �N���X�̒�`
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
		//�ϐ��錾//***********************************************************************
	float	m_fCntState;	//���ԃJ�E���g
	CSelect_UI *m_pUI;
};

#endif
