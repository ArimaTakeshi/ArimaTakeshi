//=============================================================================
//
// �J�������� [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#include "manager.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define		DRAW_ANGLE		(45.0f)				//�J�����{�� +��, -��
#define		DRAW_ANGLEP		(DRAW_ANGLE + 10.0f)				//�J�����{�� +��, -��
#define		DRAW_DISTANCE	(2000.0f * 2000.0f)				//�J�����{�� +��, -��
#define		DRAW_DISTANCE2	(100.0f * 100.0f)				//�J�����{�� +��, -��
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera
{
public:
	typedef enum
	{//���f���̎��
		CAMERA_TYPE_NORMAL,
		CAMERA_TYPE_CHAR,
		CAMERA_TYPE_OBJ,
		CAMERA_TYPE_EVENT,
		CAMERA_TYPE_MAX,
	}CAMERA_TYPE;
	CCamera() {};
	~CCamera() {};

	void Init(void);
	void Draw(void);
	void SetCamera(D3DXVECTOR3 WKposV);
	bool DrawCheck(D3DXVECTOR3 &pos, float fLength);
	void SetViewport(int left, int up, int right, int bottom);

	D3DXVECTOR3 &GetRot(void) { return m_rot; };
	D3DXVECTOR3 &GetposV(void) { return m_posV; };
	D3DXVECTOR3 &GetposR(void) { return m_posR; };
	D3DXVECTOR3 &GetvecU(void) { return m_vecU; };
	D3DXVECTOR3 &Gettargetpos(void) { return m_targetpos; };
	float		&GetfDistance(void) { return m_fDistance; };
	CAMERA_TYPE	&GetType(void) { return m_Type; };
	int	&GetnNumCamera(void) { return m_nNumCamera; };

private://*****************************************************************************

	//�ϐ��錾//***********************************************************************
	int			m_nNumCamera;	//�J�����ԍ�
	CAMERA_TYPE m_Type;			//�J�����^�C�v
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_vecU;
	D3DXVECTOR3 m_targetpos;	//�Ǐ]����ꏊ
	D3DXVECTOR3 m_rot;			//�p�x
	float		m_fDistance;		//�J�����ƒ����_�̋���

	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_viewport;		//�J�����ݒ�p
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera_Char : public CCamera
{
public:
	CCamera_Char()	{};
	~CCamera_Char() {};

	void Init(void);
	void Uninit(void) { delete this; };
	void Update(void);
	void Draw(void);
	void Reset(void);
	void SetCamera(void);

	float *&GetpDistance(void) { return m_pDistance; };
	D3DXVECTOR3 *&GetpChare(void) { return m_pChar; };
	D3DXVECTOR3 *&GetpMove(void) { return m_pMove; };
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	D3DXVECTOR3	*m_pChar;		//���̃L������Ǐ]���邩
	D3DXVECTOR3	*m_pMove;		//���̃L������Ǐ]���邩
	D3DXVECTOR3 m_goal;			//�������ʒu
	float		*m_pDistance;		//�J�����ƒ����_�̋����̖ړI�l
	float		m_fGMagnification;	//�ړI�ɂ����܂ł̔{��

	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera_Play
{
public:
	CCamera_Play() {};
	~CCamera_Play() {};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CCamera_Char *&GetChar(void) { return m_pCamera_Char; }
	CCamera		 *&GetObj(void)  { return m_pCamera_Obj; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	CCamera_Char *m_pCamera_Char;	//�L�����N�^�[�ǔ�
	CCamera		 *m_pCamera_Obj;	//�I�u�W�F�̂�
};

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera_Manager
{
public:
	typedef enum
	{//���f���̎��
		STATE_NONE = 0,	//�������Ȃ�
		STATE_GAME,		//�Q�[��
		STATE_MOVIE,		//���[�r�[

	}CAMERA_STATE;
	typedef enum
	{//���f���̎��
		VIEW_IGNORE = 0,	//���ɂ��ւ��Ȃ�
		VIEW_FOLLOW,		//�Ǐ]
		VIEW_WATCH,			//�ǂ킸�Ɍ��邾��

	}CAMERA_VIEW;
	typedef enum
	{//���f���̎��
		SCENE_VIEW_NORMAL = 0,	//�ʏ�ʂ蓮��
		SCENE_VIEW_STOP,		//���f���̂ݎ~�܂�

	}SCENE_VIEW;
	typedef enum
	{//���f���̎��
		SCENE_TYPE_NO = 0,	//�߂�@�ԈႦ�悤�̑Ώ�
		SCENE_TYPE_BOSS,	//�{�X�O�̃V�[��

	}SCENE_TYPE;
	typedef struct
	{
		CAMERA_STATE	state;		//���
		CAMERA_VIEW		ViewC;		//������ �J����
		SCENE_VIEW		ViewS;		//������ �J�����ȊO(���f����)
		SCENE_TYPE		scene;			//���̃V�[����
		CCamera			*pCamera;		//���ݕ`�撆�̃J����
		int				nCntState;		//���[�r�[�̐i�s�x
		int				nCntTime;		//�V�[���̃t���[�����L�^

	}Info;
	CCamera_Manager() {};
	~CCamera_Manager() {};

	void Init(void);
	void Update(void);
	void Uninit(void);
	void Uninit_Event(void);
	void Draw(void);
	CCamera_Char *&GetEvent(void) { return m_pEvent; }
	CCamera_Play *&GetPlay(int nID) { return m_pPlay[nID]; }

	static bool DrawCheck(D3DXVECTOR3 &pos, float fLength);
	static CCamera_Char *&Create_Event(void);
	static CCamera_Play *&Create_Play(int nCount);
	static void SetScene(CCamera_Manager::SCENE_TYPE type);
	static void UpdateScene(void);
	static Info &GetInfo(void) { return m_info; };

private://*****************************************************************************
	static Info	m_info;

	//�ϐ��錾//***********************************************************************
	CCamera_Char *m_pEvent;
	CCamera_Play *m_pPlay[MAX_PLAYER];
};
#endif
