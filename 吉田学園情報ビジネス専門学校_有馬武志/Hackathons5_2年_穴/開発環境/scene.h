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
#define MAX_SCENE		(8)					//�V�[���̍ő�D�揇��
#define OBJ_PRIORITY	(5)					//3D�I�u�W�F�̗D�揇��
#define MAX_3DSCENE		(OBJ_PRIORITY + 1)					//3D�ő�̗D�揇��
#define START_2DSCENE	(MAX_3DSCENE)	//2D�J�n�̗D�揇��
#define PAUSE_PRIORITY	(MAX_SCENE - 1)		//�|�[�Y�̗D�揇��

#define PAUSE_PRIORITY	(MAX_SCENE - 1)		//�|�[�Y�̗D�揇��
#define PAUSE_LENGTH	(25.0f)				//�|�[�Y�㉺�g�̒���

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
		DRAW_TYPE_AER,			//���������Z����
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
		OBJTYPE_NONE2,
		OBJTYPE_DUNGEON, OBJTYPE_MESH,
		OBJTYPE_EFFECT, OBJTYPE_ANIM3D, OBJTYPE_SALE,
		OBJTYPE_Satellite, OBJTYPE_ORBIT, OBJTYPE_LINE, OBJTYPE_BULLET, 
		OBJTYPE_BOSS, 
		//���f��//**********************************************
		OBJTYPE_PLAYER, OBJTYPE_ENEMY, OBJTYPE_OBJ,
		//�摜//**********************************************
		OBJTYPE_OBJ_NO,	//���f���@����F(�L/����)
		OBJTYPE_OTHER,	//�Q�[���O�J�����p(UI�p)
		OBJTYPE_UI,		//���[�U�[�C���^�[�t�F�C�X
		OBJTYPE_NUMBER,
		OBJTYPE_GOAL, OBJTYPE_SHOP,
		OBJTYPE_MAX
	}OBJTYPE;
	typedef struct
	{//��ނ��Ƃ̃��f�����ۑ�
		LPD3DXMESH		MeshModel = NULL;		//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
		DWORD			nNumMatModel = NULL;	//�}�e���A���̏��
	}MODEL_DRAW;
	typedef enum
	{
		/* BG */			TEX_Title, TEX_Select, TEX_Select0, TEX_G_EXPLOSION,
		/* �_ */			TEX_Fog000, TEX_Fog001,
		/* ���S */			TEX_TitleLogo, TEX_Press, TEX_HitLogo,
		/* UI */			TEX_Arrow, TEX_S_Move,TEX_Help,
		/*���b�N�I��*/		TEX_Lock_On,	/*�{�^��UI*/		TEX_Button_UI,
		/*�Q�[�W*/			TEX_Gage, TEX_GageDeco,
		/*����*/			TEX_Number,
		/*�q�b�g*/			TEX_HIT0, TEX_HIT1,
		/*���S*/			TEX_Dead,		/*�����O��*/		TEX_Omen,		/*����*/			TEX_Over,
		/*�G�t�F�N�g*/		TEX_Fire,		/*�O��*/			TEX_Orbit,		/*�Q�[�g*/			TEX_GateE,
		/*�L����*/			TEX_BSword,
		TEX_TAKASHI,
		TEX_Icon_TKS,
		TEX_Hole,
		TEX_Room,
		TEX_CLEAR,
		TEX_OVER,
		TEX_Alarm,
		TEX_PressA,
		TEX_Quiz,
		TEX_Pause,
		TEX_PHand,
		TEX_HIT99,
		/*���A*/			TEX_Dungeon,	/*�Q�[�g*/			TEX_Gate,
		/* �h�A */			TEX_Door,		/* �� */			TEX_Paper,
		/* �� */			TEX_Fence,		/* �� */			TEX_Stone,		/*�S��*/			TEX_Steel,
		/*���ʎ��j(�{��)*/	TEX_Pos_Mag,	/*���ʎ��j(�j)*/	TEX_Pos_Nee,	/*�q��*/			TEX_Satellite,
		/*�������烂�f���p*/TEX_CHAR,
		/*�}���g*/			TEX_Cloak = TEX_CHAR,
		/*��*/				TEX_Sword,
		/*��*/				TEX_Stick,
		TEX_MAX
	}TEXTURE;
	CScene::CScene(int nPrioryity = 3);
	~CScene();

	static LPDIRECT3DTEXTURE9	&Load(TEXTURE tex);
	static void	UnLoad(void);
	static void	ReleaseAll(void);
	static void	UpdateAll(void);
	static void	DrawAll(LPDIRECT3DDEVICE9 &pDevice);
	static void	Draw3D(LPDIRECT3DDEVICE9 &pDevice);
	static void	DrawObj(LPDIRECT3DDEVICE9 &pDevice);
	static void	Draw2D(LPDIRECT3DDEVICE9 &pDevice);

	static void	UninitAll(void);
	static void	BreakObject(void);			//�I�u�W�F�N�g�̑S�j��
	static void	BreakObject(OBJTYPE obj);	//�w�肵���I�u�W�F�N�g��j��

	static CScene *&GetTop(int nPrioryity) { return m_pTop[nPrioryity]; };
	static CScene *&GetCur(int nPrioryity) { return m_pCur[nPrioryity]; };
	static int &GetnNumAll(int nPrioryity) { return m_nNumAll[nPrioryity]; };
	//*****************************************************************************
	virtual HRESULT Init(void)					 { return S_OK; };
	virtual void	Uninit(void) { m_bDeath = true; SetObjType(OBJTYPE_NONE); };
	virtual void	Draw(void)					 {};
	virtual void	Update(void)				 {};
	static int		&GetnCntStart(void)			 { return m_nCntStart; }
	static bool		&GetbPause(void)			 { return m_bPause; }
	static bool		DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice);	//�`�揀������

	D3DXVECTOR3	*Getpos(void);
	CScene	*&GetpNext(void) { return m_pNext; }
	CScene	*&GetpPrev(void) { return m_pPrev; }
	bool	&GetbDeath(void) { return m_bDeath; }
	void	SetObjType(OBJTYPE ObjType)			 { m_ObjType = ObjType; }
	OBJTYPE GetObjType(void)					 { return m_ObjType; }
	static LPDIRECT3DTEXTURE9	&GetTexture(int nNumber) { return m_pTexture[nNumber]; }

protected://*****************************************************************************
	void			Release(void);											//�������			
private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	static int		m_nDraw;			//���݂̕`����@
	static LPDIRECT3DTEXTURE9	m_pTexture[TEX_MAX];		// �e�N�X�`���ւ̃|�C���^
	static CScene	*m_pTop[MAX_SCENE];		// �J�n�ʒu
	static CScene	*m_pCur[MAX_SCENE];		// �Ō��(�J�����g�̗�->����)
	static int		m_nNumAll[MAX_SCENE];				//Update�̃X�^�[�g�ʒu
	static int		m_nCntStart;				//Update�̃X�^�[�g�ʒu
	static bool		m_bPause;					//�|�[�Y�̗L��

	CScene *m_pNext;				//��
	CScene *m_pPrev;				//�O
	int				m_nPriority;	//�����̗D�揇��
	OBJTYPE			m_ObjType;		//�I�u�W�F�N�g�^�C�v
	bool			m_bDeath;		//���S�t���O
};

//==================================================================================================//
//    * �e���v���[�g��` *
//==================================================================================================//
template<class T> bool SceneCreate(T *&pScene, int nPriority)
{
	pScene = NULL;
	pScene = new T(nPriority);
	if (pScene != NULL) { pScene->Init(); return true; }

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
