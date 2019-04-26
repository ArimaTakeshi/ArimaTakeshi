#pragma once
//=============================================================================
//
// �e�S�ʏ��� [SceneBullet.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEBULLET_H_
#define _SCENEBULLET_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SHOT_UV_X		(16)
#define SHOT_UV_Y		(10)
#define SHOT_UV_SMALL	(0.003f)
#define SHOT_DROW_X		(105.0f)
#define SHOT_DROW_Z		(59.0f)

#define SHOT_MAX_SPD	(0.05f)
#define SHOT_LIFE		(720.0f)

#define BULLET_PRIORITY		(5)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneBullet : public CScene3D
{
public:
	typedef enum
	{//���C��
		SHOT_PLAYER1,
		SHOT_PLAYER2,
		SHOT_ENEMY,
		SHOT_IGNORED,
		SHOT_TROP,
		SHOT_MAX
	}SHOT;
	typedef enum
	{//�ω�
		CHANGE_NONE = 0,	//�ω��Ȃ�
		CHANGE_SPDUP,		//�����l
		CHANGE_SPDDOWN,		//����
		CHANGE_BACK,		//Spd���������]
		CHANGE_BACK2,		//�r����Spd�}�ɔ��]
		CHANGE_STRAIGHT,	//��]�l (*)
		CHANGE_SPINUP,		//��]�l (+)
		CHANGE_SLOW,		//�x��
		CHANGE_HOMING,		//�r���ł����Ȃ�G����������
		CHANGE_HOMINGS,		//�r���ł����Ȃ�G������������F�~�܂�
	//���ˎ�//***********************************************************************
		CHANGE_NO = -1,	//�ω��Ȃ�
		CHANGE_FAST,		//��������
		CHANGE_FAST2,		//����������
		CHANGE_GRAVITY,		//�t����(�u���A��)�ŃW�����v
		CHANGE_GRAVITY2,	//�t����(���u��)�ŃW�����v
		CHANGE_MAX,
	}CHANGE;
	typedef enum
	{
		//���Ԋu�ŋN��
		SET_NONE,			//�u������
		SET_TURN,			//��]���u������
		SET_EFFECT,	SET_EFFECT0,			//�G�t�F�N�g���o
		SET_SHOT,			//����
		SET_SHOT2,			//����
		SET_BEAM,			//BEAM
		SET_NEEDLE,			//���̂悤�ȋ�
		SET_PDIFFUSION00, SET_PDIFFUSION01,			//�g�U �΂�T���q�@
		SET_RELEASE,			//���ԊJ��
		SET_RANDSHOT,		//�K���ɔ���
		SET_BACK_G,			//�^���d�͕t��
		SET_BACK_G2,		//�^���d�͕t�����܂�
		SET_FIRE0,			//���΂�܂�
		SET_FIRE,			//���΂�܂�
		SET_CROSS,			//�\������
		SET_AROUND,			//���E����
		//�N��������//
		SET_PDIFFUSION,		//�΂�T���q�@
		SET_PDIFFUSION2,	//�������Ԃ�����
		SET_DIFFUSION,		//�΂�T���ĎU��
		SET_DIFFUSION2,		//�΂�T���ĎU��
		SET_BRANCH,	//�\���������ˁ@��]�l����
		SET_BRANCHES,		//�}������
		//�U�����@//
		SET_BATK_BRANCH,
		SET_BATK_CROSS,

		SET_MAX
	}SET;
	typedef enum
	{//�U�����@//
		ATK_PTN00		, ATK_PTN01		, ATK_PTN02	, ATK_PTN03,	//��{�p�^�[��
		ATK_BEAM00		, ATK_BEAM01	, ATK_BEAM02, ATK_BEAM10,
		ATK_SETTING0	, ATK_SETTING1	,
		ATK_DIFFUSION	,ATK_PDIFFUSION	, ATK_PDIFFUSION2,				//�g�U �΂�T���q�@
		ATK_PTN_FIRE	, ATK_PTN_FIRE2	, ATK_PTN_FIRE3,
		//�{�X�U���@//***********************************************************************
		BATK_BRANCH,
		BATK_CROSS,
		BATK_SPIN_0,
		BATK_SPIN_1,
		MAX
	}ATTACK;
	typedef enum
	{//�摜//***********************************************************************
		/*�e*/		TEX_BULLET, TEX_BULLET2, TEX_BULLET_S,
		TEXTURE_MAX
	}TEXTURE;

	CSceneBullet(int nPriority = BULLET_PRIORITY) : CScene3D::CScene3D(nPriority) {};
	~CSceneBullet() {};
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//�e�N�X�`���̐���
	static void					UnLoad(void);	//�e�N�X�`���̔j��
	static void					ShotAttack(SHOT Shot, ATTACK Set, D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRotU, bool bFirst,
											float fSpd, float fSlip, float fLife, float fTurning, float fAccelerator, float fLengthX, float fLengthZ,
											float fRange, float fDistance, int nNumBullet, int nChange, CHANGE Change, float fAtk, bool bDestroy, bool *bShotDelete, int nUV);
	static void					BreakBullet(bool bAll);
	static void					CircleBreak(D3DXVECTOR3 pos, float fLength, SHOT shot1, SHOT shot2);
	bool CSceneBullet::SetAttack(SET SetType, float fMaxLife, float fAngleSet, int nNumSet, D3DXVECTOR3 move, int nUV, int& nInterval);
	bool LifeUpdate(void);

	HRESULT	Init(void) { CScene3D::Init(); CScene::SetObjType(OBJTYPE_BULLET);  return S_OK; };
	void	Draw(void);
	SHOT	*GetShot(void) { return &m_shot; }
	float	*GetfAtk(void) { return &m_fAtk; }
	bool	&GetbDestroy(void) { return m_bDestroy; }
	bool	*&GetbShotDelete(void) { return m_bShotDelete; }

	//void						SetPosition(D3DXVECTOR3 pos) { GetPosition()[0] += pos; };
	//void						SetRotation(float fRotY) { GetRotation()[0].y = fRotY; };
protected://*****************************************************************************
	void SetVtx(int nUV);

	//�ϐ��錾//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
	SHOT	m_shot;		//���C�҂̃^�O	�`�[�������^�O�̂悤�Ȃ���
	int		m_nChange;	//�e�̕ω��^�C�v
	float	m_fSpeed;		//�X�s�[�h
	float	m_fAccelerator;	//�����l
	float	m_fTurning;		//����X�s�[�h
	float	m_fSlip;		//����
	float	m_fAtk;			//�e�̍U����
	bool	m_bDestroy;		//�j��̗L��
	bool	*m_bShotDelete;	//�e�̔j���̗L��
private://*****************************************************************************
	void DrawParts(float fPosY, LPDIRECT3DDEVICE9& pD3DDevice);
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneNorBullet : public CSceneBullet
{
public:

	CSceneNorBullet(int nPriority = BULLET_PRIORITY) : CSceneBullet::CSceneBullet(nPriority) {};
	~CSceneNorBullet() {};

	void Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete);
	void	Update(void);

protected://*****************************************************************************
	void SetMove(CHANGE& change);
		  //�ϐ��錾//***********************************************************************
	D3DXVECTOR3 m_move;	//�ړ���
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneSetBullet : public CSceneNorBullet
{
public:
	CSceneSetBullet(int nPriority = BULLET_PRIORITY) : CSceneNorBullet::CSceneNorBullet(nPriority) {};
	~CSceneSetBullet() {};

	void CSceneSetBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete,
		SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval);
	void	Update(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	SET 	m_SetType;		//�e���Z�b�g����ID
	float	m_fAngleSet;	//�Z�b�g�p�x
	float	m_fAnglePlus;	//�Z�b�g�p�x��+
	int 	m_nNumSet;		//�e���Z�b�g���鐔
	int		m_nInterval;	//�Z�b�g�N���Ԋu
	int		m_nUV;			//�F�I����
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScenePairBullet : public CSceneNorBullet
{
public:
	CScenePairBullet(int nPriority = BULLET_PRIORITY) : CSceneNorBullet::CSceneNorBullet(nPriority) {};
	~CScenePairBullet() {};

	void CScenePairBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fXWall, float fZWall, float fRangeX, float fRangeZ,
		SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete);
	HRESULT	Init(void) { CSceneNorBullet::Init(); CScene::SetObjType(OBJTYPE_EFFECT);  return S_OK; };
	void Update(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	D3DXVECTOR3		*m_pPos;	//�e�̏ꏊ
	float			*m_pRot;	//�e�̊p�x
	D3DXVECTOR3		m_pos2;		//�����̈ʒu
	D3DXVECTOR3		m_pos3;		//�ǔ�����e�̈ʒu
	float	m_fRangeX;			//�ǏՓˎ��p�x�ύX�͈�
	float	m_fRangeZ;			//�ǏՓˎ��p�x�ύX�͈�
	float	m_fXWall;			//�c�̕�
	float	m_fZWall;			//���̕�

	int		m_nNumCount;	//���ˊԊu�̃J�E���g
	float	m_fLife;		//�����l�@-�Ȃ炸����

	SET 	m_SetType;		//�e���Z�b�g����ID
	float	m_fAngleSet;	//�Z�b�g�p�x
	float	m_fAnglePlus;	//�Z�b�g�p�x��+
	int 	m_nNumSet;		//�e���Z�b�g���鐔
	int		m_nInterval;	//�Z�b�g�N���Ԋu
	float	m_fMaxLife;			//�ŏ��̐����l
	int		m_nUV;			//�F�I����
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScenePairBullet2 : public CSceneBullet
{
public:
	CScenePairBullet2(int nPriority = BULLET_PRIORITY) : CSceneBullet::CSceneBullet(nPriority) {};
	~CScenePairBullet2() {};

	void CScenePairBullet2::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
		D3DXVECTOR3 *pPos, float *pRot, bool bDestroy, bool *bShotDelete);
	void Update(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	D3DXVECTOR3		*m_pPos;	//�e�̏ꏊ
	float			*m_pRot;	//�e�̊p�x
	D3DXVECTOR3		m_pos3;		//�ǔ�����e�̈ʒu
	float			m_fAngle;		//�e���猩���p�x
	float			m_fDistance;	//�e�܂ł̋���
	float			m_fGMagnification;	//�ړI�ɂ����܂ł̔{��
	float			m_fLife;		//�����l�@-�Ȃ炸����
	float			m_fMaxLife;			//�ŏ��̐����l
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScenePairBulletSet : public CScenePairBullet2
{
public:
	CScenePairBulletSet(int nPriority = BULLET_PRIORITY) : CScenePairBullet2::CScenePairBullet2(nPriority) {};
	~CScenePairBulletSet() {};

	void CScenePairBulletSet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
		float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
		SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete);
	void Update(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	int		m_nNumCount;	//���ˊԊu�̃J�E���g
	SET 	m_SetType;		//�e���Z�b�g����ID
	float	m_fAngleSet;	//�Z�b�g�p�x
	float	m_fAnglePlus;	//�Z�b�g�p�x��+
	int 	m_nNumSet;		//�e���Z�b�g���鐔
	int		m_nInterval;	//�Z�b�g�N���Ԋu
	int		m_nUV;			//�F�I����
};
#endif
