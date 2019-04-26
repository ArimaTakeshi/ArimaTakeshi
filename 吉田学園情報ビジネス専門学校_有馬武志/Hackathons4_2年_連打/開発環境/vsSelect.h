//=============================================================================
//
// �ΐ폈�� [Versus.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _VS_SELECT_H_
#define _VS_SELECT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "Versus.h"
#include "manager.h"
#include"ScenePlayer.h"
class CFont;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_VS_GAGE		(3)
#define MAX_VS_WEAPON	(2)
#define MAX_VS_READY	(2)
#define MAX_VS_STAGE	(3)

#define MAX_VS_COST		(100)
#define MAX_VS_CFont	(6)
//*****************************************************************************
// �N���X�̒�` VS�Z���N�g�pUI
//*****************************************************************************
class CvsSelectUI : public CScene
{
public:
	typedef enum
	{
		SELECT_TANK0,
		SELECT_TANK1,
		SELECT_ITEM,
		SELECT_BULLET,
		SELECT_LIFE,
		SELECT_DEF,
		SELECT_ATK,
		SELECT_READY,
		SELECT_MAX
	}SELECT;
	CvsSelectUI(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity) 
	{ 
		m_p2DComLevel = NULL;
		m_pTank = NULL;
		for (int nCount = 0; nCount < MAX_VS_WEAPON; nCount++) { m_p2DTank[nCount] = NULL; }
		m_pItem = NULL;
		m_p2DColBullet = NULL;
		for (int nCount = 0; nCount < MAX_VS_GAGE; nCount++) { m_pGage[nCount] = NULL; m_p2DGage[nCount] = NULL; }
		m_p2DReady = NULL;
		m_p2DReadyLogo = NULL;
	};
	~CvsSelectUI() {};

	void Set(int &nID, CvsSelect *pvsSelect);	//�Z�b�g����
	void SetSelect(CvsSelect *pvsSelect, int &nID);
	void Select(SELECT &select, bool bChange, CvsSelect *pvsSelect, int &nID);
	void Cursor(SELECT &select);
	bool OverCost(CvsSelect *pvsSelect, int &nID);				//�R�X�g���I�[�o�[���Ă��邩����
	void FontOver(D3DXCOLOR col);								//�R�X�g���I�[�o�[���Ă���Ε����Ԃ�
	int SumCost(CvsSelect *pvsSelect, int &nID);				//�R�X�g�̍��v�l��Ԃ�
	int GetCost(SELECT select, CvsSelect *pvsSelect, int &nID);	//�w�肳�ꂽ�R�X�g��Ԃ��@�����ɕ\�L�̍X�V
	void Ready(bool bReady);
	void SpinTank(bool bSpin);
	void Uninit(void);	//�폜
	void Update(void);	//�X�V
	void Draw(void);	//�`��

private:
	C2D				*m_p2DSelect;				//�I��
	
	int				m_nCost;					//�R�X�g�̐��l
	CFont			*m_pCost;					//�R�X�g�̕\�L
	CFont			*m_pCostS[MAX_VS_CFont];	//STATUS���Ƃ̃R�X�g�̕\�L
	C2D				*m_p2DComLevel;				//COMLevel
	CSceneTank		*m_pTank;					//���
	C2D				*m_p2DTank[MAX_VS_WEAPON];	//��ԑ���
	C2D				*m_pItem;					//�A�C�e��
	C2D				*m_p2DColBullet;			//�e�̐F
	C2DGage			*m_pGage[MAX_VS_GAGE];		//�Q�[�W
	C2D				*m_p2DGage[MAX_VS_GAGE];	//�A�C�R��
	C2D				*m_p2DReady;				//����
	C2D				*m_p2DReadyLogo;			//�������S
};
//*****************************************************************************
// �N���X�̒�` �{�X�pUI
//*****************************************************************************
class CvsSelectStage : public CScene
{
public:
	CvsSelectStage(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_nSelect = 0;
		for (int nCount = 0; nCount < MAX_VS_READY; nCount++) { m_pReady[nCount] = NULL; }
		for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++) { m_pStage[nCount] = NULL; }
	};
	~CvsSelectStage() {};

	void Uninit(void);	//�폜
	void Update(void);	//�X�V
	void Draw(void);	//�`��

	void Set(void);	//�Z�b�g����
	void ChangeReady(bool bDraw);
	void ChangeStage(bool bDraw);
	void UpdateStage(void);

	C2DPolygon	*&GetpStage(int nID) { return m_pStage[nID]; }
	int  &GetnSelect(void) { return m_nSelect; };
	
private:
	int			m_nSelect;
	C2D			*m_pStageLogo;
	C2DPolygon	*m_pReady[MAX_VS_READY];
	C2DPolygon	*m_pStage[MAX_VS_STAGE];
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CvsSelect
{
public:
	CvsSelect() { for (int nCount = 0; nCount < MAX_PLAYER; nCount++) { m_pUI[nCount] = NULL; } };
	~CvsSelect() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	WeaponSelect(int &nCount);
	bool	StageSelect(int &nCount);
	void	Save(void);
	void	Load(void);
	static void LoadVS(int &nStage);

	CSceneModel::TEXTURE	&GetTex(int nID, int nCount) { return m_tex[nID][nCount]; }
	ITEM::TYPE	&GetItem(int nID)	{ return m_item[nID]; }
	float		&GetfLife(int nID)	{ return m_fLife[nID]; }
	float		&GetfAtk(int nID)	{ return m_fAtk[nID]; }
	float		&GetfDef(int nID)	{ return m_fDef[nID]; }
	int			&GetnUV(int nID)	{ return m_nUV[nID]; }
	int			&GetnComLevel(int nID) { return m_nComLevel[nID]; }

	float		&GetfMaxGage(void) { return m_fMaxGage; }

private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	CvsSelectStage	*m_pStage;
	CvsSelectUI		*m_pUI[MAX_PLAYER];
	float			m_fMaxGage;

	//�I���n//***********************************************************************
	CvsSelectUI::SELECT	m_Select[MAX_PLAYER];	//�v���C���[���Ƃ̑I��p
	bool m_bReady[MAX_PLAYER];	//��������
	bool m_bStage;				//�X�e�[�W�I�����
	bool m_bGo;					//�I�����I���������ǂ���

	CSceneModel::TEXTURE m_tex[MAX_PLAYER][2];	//�e�N�X�`���@�ԑ́@�C��
	ITEM::TYPE	m_item[MAX_PLAYER];						//�A�C�e��
	float		m_fLife[MAX_PLAYER];					//�̗�
	float		m_fAtk[MAX_PLAYER];						//�U����
	float		m_fDef[MAX_PLAYER];						//�h���
	int			m_nUV[MAX_PLAYER];						//�e�̐F
	int			m_nComLevel[MAX_PLAYER];						//COU�̏ꍇ�̋���
};

#endif
