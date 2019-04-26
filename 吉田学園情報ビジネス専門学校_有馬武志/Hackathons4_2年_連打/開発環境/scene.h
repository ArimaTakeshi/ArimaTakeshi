//=============================================================================
//
// �V�[������ [scene.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define MAX_SCENE		(8)
#define PAUSE_PRIORITY	(MAX_SCENE - 1)				//�|�[�Y�̗D�揇��
#define PAUSE_LENGTH	(75.0f)				//�|�[�Y�㉺�g�̒���

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScene
{
public://*****************************************************************************
	typedef enum
	{
		DRAW_TYPE_NORMAL = 0,		//�ʏ�`��
		DRAW_TYPE_ADD,				//���Z����
		DRAW_TYPE_SUBTRACT,			//���Z����
		DRAW_TYPE_MULTIPLY,			//��Z����
		DRAW_TYPE_OVERLAY,			//���������Z����
		DRAW_TYPE_ZNORMAL = 10,		//Z�����ʏ�
		DRAW_TYPE_ZADD,				//Z�������Z
		DRAW_TYPE_ZSUBTRACT,		//Z�������Z
		DRAW_TYPE_ZMULTIPLY,		//��Z����
		DRAW_TYPE_ZOVERLAY,			//���������Z����
		DRAW_TYPE_NO,				//�`�悵�Ȃ�
		DRAW_TYPE_MAX
	}DRAW_TYPE;
	typedef enum
	{//���肵�����S�N���X ���O�N��H->�����扴���Ă��
		OBJTYPE_NONE,
		OBJTYPE_DUNGEON,
		OBJTYPE_BULLET, OBJTYPE_BULLET2, OBJTYPE_BULLET3,
		OBJTYPE_EFFECT, OBJTYPE_ANIM3D, OBJTYPE_SALE,
		OBJTYPE_BOSS, 
		//���f��//**********************************************
		OBJTYPE_PLAYER, OBJTYPE_ENEMY, OBJTYPE_OBJ,
		//�摜//**********************************************
		OBJTYPE_OBJ_NO,	//���f���@����F(�L/����)
		OBJTYPE_NUMBER,
		OBJTYPE_GOAL, OBJTYPE_SHOP,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef struct
	{//��ނ��Ƃ̃��f�����ۑ�
		LPD3DXMESH		MeshModel = NULL;		//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
		DWORD			nNumMatModel = NULL;	//�}�e���A���̏��
												//LPDIRECT3DTEXTURE9	pTexture = NULL;	//�e�N�X�`��
	}MODEL_DRAW;

	CScene::CScene(int nPrioryity = 3);
	~CScene();

	static void CScene::CreateAll(int nPrioryity, int nNumber);
	static void		ReleaseAll(void);
	static void		UpdateAll(void);
	static void		DrawAll(LPDIRECT3DDEVICE9 &pDevice);

	static CScene **GetScene(int nPrioryity);
	static CScene *GetScene(int nPriority, int nID) { return m_PScene[nPriority][nID]; };
	CScene *GetThisScene(void) {return m_PScene[m_nPriority][m_nID]; };
	//*****************************************************************************
	virtual HRESULT Init(void)					 { return S_OK; };
	virtual void	Uninit(void)				 { Release(); };
	virtual void	Draw(void)					 {};
	virtual void	Update(void)				 {};
	static int		GetnNumAll(int nPriority)	 { return m_nNumAll[nPriority]; }
	static int		GetnMemoryAll(int nPriority) { return m_nMemoryAll[nPriority]; }
	static int		&GetnCntStart(void)			 { return m_nCntStart; }
	static bool		&GetbPause(void)			 { return m_bPause; }
	static bool		DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//�`�揀������

	void	SetObjType(OBJTYPE ObjType)			 { m_ObjType = ObjType; }
	OBJTYPE GetObjType(void)					 { return m_ObjType; }
	int		&GetID(void)						 { return m_nID; }
	void	BreakObject(void);			//�I�u�W�F�N�g�̑S�j��
	void	BreakObject(OBJTYPE obj);	//�w�肵���I�u�W�F�N�g��j��
protected://*****************************************************************************
	void			Release(void);											//�������			

	//���̑�//***********************************************************************
	static int		m_nDraw;			//���݂̕`����@

	//�ϐ��錾//***********************************************************************
	static CScene	**m_PScene[MAX_SCENE];		//�����_�����O�̃|�C���^�̃|�C���^
	static int		m_nNumAll[MAX_SCENE];		// ���������̐�
	static int		m_nMemoryAll[MAX_SCENE];	// �����ł��鍇�v��
	static int		m_nCntStart;				//Update�̃X�^�[�g�ʒu
	static bool		m_bPause;					//�|�[�Y�̗L��
	int				m_nID;			//�����̔ԍ�
	int				m_nPriority;	//�����̗D�揇��
	OBJTYPE			m_ObjType;		//�I�u�W�F�N�g�^�C�v
};

//==================================================================================================//
//    * �e���v���[�g��` *
//==================================================================================================//
template<class T> bool SceneCreate(T *&pScene, int nPriority)
{
	pScene = NULL;
	if (CScene::GetnNumAll(nPriority) < CScene::GetnMemoryAll(nPriority))
	{//�����ł���ő�l�o�Ȃ��Ȃ�
	 pScene = new T(nPriority);
	 if (pScene != NULL) { pScene->Init(); return true; }
	}

	//MessageBox(0, "�����ł��Ȃ��I", "", MB_OK);
	return false;
}
//==================================================================================================//
//    * �e���v���[�g��` *
//==================================================================================================//
template<class T> bool Create(T *&pScene)
{
	pScene = NULL;
	pScene = new T;
	if (pScene != NULL) { pScene->Init(); return true; }
	//MessageBox(0, "�����ł��Ȃ��I", "", MB_OK);

	return false;
}

#endif
