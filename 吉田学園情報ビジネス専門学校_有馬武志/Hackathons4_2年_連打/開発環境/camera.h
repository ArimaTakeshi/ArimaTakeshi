//=============================================================================
//
// �J�������� [camera.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCamera
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
	}Info;
	CCamera();
	~CCamera();

	static void Init(void);
	static void Uninit(void);
	static void Update(void);
	static void Reset(void);
	static void SetCamera(void);
	static void SetScene(SCENE_TYPE type);
	static void UpdateScene(void);
	static Info *GetCamera(void);
	void Collision(D3DXVECTOR3 *pos, float fLengthX, float fLengthZ);

	static CCamera camera;
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static Info m_info;			//�J�������

	D3DXVECTOR3 m_posC;			//�����蔻��p
	D3DXVECTOR3 m_vecU;			//������̃x�N�g��

	D3DXVECTOR3 m_goal;			//�������ʒu
	D3DXVECTOR3 m_targetpos;	//�Ǐ]����ꏊ
	D3DXVECTOR3 m_rot;			//�p�x
	D3DXVECTOR3 m_addpos;			//�J�����̐����ړ���
	float		m_fDistance;		//�J�����ƒ����_�̋���
	float		m_fGMagnification;	//�ړI�ɂ����܂ł̔{��

	int			m_nCntState;		//���[�r�[�̐i�s�x
	int			m_nCntModel;		//���̃L������Ǐ]���邩
	int			m_nCntTime;			//�V�[���̃t���[�����L�^
	bool		m_bCollision;		//�v���C���[���J�����ǂɓ������Ă��邩�ǂ���

	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
};

#endif
