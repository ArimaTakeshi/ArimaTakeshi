//=============================================================================
//
// ���[�V�������� [motion.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "scene.h"
#include "3DGage.h"
#include "SceneAnim3D.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHAR_PRIORITY	(0)
#define MAX_HITCHAR		(16)
#define MAX_WAIT_MOTION	(15)

class CCharacter;
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CKey
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,	//�ʏ�L�[
		TYPE_ATTACK,		//�U���L�[
		TYPE_MAX
	}TYPE;
	CKey() { m_pRot = NULL; m_pEffect = NULL; };
	~CKey() {};
	void Uninit(void);

	float		&GetfSlip(void)		{ return m_fSlip; }
	float		&GetfMove(void)		{ return m_fMove; }
	int			&GetnMoveType(void) { return m_nMoveType; }
	D3DXVECTOR3 &GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 *&GetpRot(void)		{ return m_pRot; }
	D3DXVECTOR3 &GetMove(void)		{ return m_move; }
	int			&GetnFrame(void)	{ return m_nFrame; }
	int			&GetnMaxEffect(void){ return m_nMaxEffect; }
	int			*&GetpEffect(void)	{ return m_pEffect; }
	int			&GetnFloating(void) { return m_nFloating; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float		m_fSlip;		//����
	float		m_fMove;		//�ړ��\���ǂ���
	int			m_nMoveType;	//�ړ����@	0:�i�� 1:�P��
	D3DXVECTOR3 m_pos;			//���_�ړ��l
	D3DXVECTOR3 *m_pRot;		//��]�l
	D3DXVECTOR3	m_move;			//�ړ���
	int			m_nFrame;		//�t���[����
	int			m_nMaxEffect;	//����
	int			*m_pEffect;		//SA�△�G���A����
	int			m_nFloating;	//�ړ����@	0:�ʏ� 1:���V 2:�n�ʕt���Ȃ�
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CAtkKey : public CKey
{
public:

	CAtkKey() {};
	~CAtkKey() {};

	typedef enum
	{
		ATK_TYPE_NO = 0,	//���݂̂�
		ATK_TYPE_NORMAL,	//���q�b�g�Ő������
		ATK_TYPE_SMASH,		//�q�b�g�Ő������
		ATK_TYPE_MAX
	}ATK_TYPE;

	int			&GetnAtkType(void)			{ return m_nAtkType; }
	int			&GetnAtkParts(void)			{ return m_nAtkParts; }
	int			&GetnCntAtk(void)			{ return m_nCntAtk; }
	int			&GetnHitFrame(int nCount)	{ return m_nHitFrame[nCount]; }
	float		&GetfRange(void)			{ return m_fRange; }
	float		&GetfAtkplus(void)			{ return m_fAtkplus; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	int			m_nAtkType;		//�U���^�C�v
	int			m_nAtkParts;	//�U������
	int			m_nCntAtk;		//�U����
	int			m_nHitFrame[2];	//�U���L��F
	float		m_fRange;		//�U���͈�
	float		m_fAtkplus;		//�_���[�W�{��
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class COneMotion
{
public:

	COneMotion() { m_type = NULL; m_Key = NULL; };
	~COneMotion() {};
	void Uninit(void);

	int			&GetnNorBranch(void)			{ return m_nNorBranch; }
	int			&GetnLandBranch(void)			{ return m_nLandBranch; }
	int			&GetnStartCancel(int nNumber)	{ return m_nStartCancel[nNumber]; }
	int			&GetnEndCancel(int nNumber)		{ return m_nEndCancel[nNumber]; }
	int			&GetnOtherCancel(int nNumber)	{ return m_nOtherCancel[nNumber]; }
	int			&GetnMaxKey(void)				{ return m_nMaxKey; }
	float		&GetfWaitTime(void)				{ return m_fWaitTime; }
	CKey::TYPE	*&GetType(void)					{ return m_type; }
	CKey		**&GetKey(void)					{ return m_Key; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float	m_fWaitTime;		//�g�p���҂�����
	int		m_nNorBranch;		//�ʏ핪��
	int		m_nLandBranch;		//���n����
	int		m_nStartCancel[2];	//�����L�����Z��	 �J�n, �I��
	int		m_nEndCancel[2];	//�U��؂�L�����Z�� �J�n, �I��
	int		m_nOtherCancel[2];	//���̑��L�����Z��	 �J�n, �I��

	int			m_nMaxKey;		//�L�[�̍ő吔
	CKey::TYPE	*m_type;		//�L�[�̃^�C�v
	CKey		**m_Key;		//�L�[�{��
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMotion
{
public:
	typedef enum
	{
		TYPE_BOX_Sword,	//��
		TYPE_BOX_Stick,	//���_
		TYPE_MAX
	}TYPE;
	CMotion()	{ m_OneMotion = NULL; };
	~CMotion()	{};

	static void Load(void);
	static void UnLoad(void);
	void Uninit(void);

	static CMotion *GetMotion(int nType)	 { return m_pMotion[nType]; };
	COneMotion *&GetOneMotion(void) { return m_OneMotion; };
	int &GetnMaxParts(void)			 { return m_nMaxParts; };
	int &GetnMaxMotion(void)		 { return m_nMaxMotion; };

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static int			m_nNumMotion;			//�ő�L������
	static CMotion		**m_pMotion;				//���[�V�����{��

	int m_nMaxParts;	//�\�����Ă���p�[�c��
	int m_nMaxMotion;	//�\�����Ă��郂�[�V������
	COneMotion *m_OneMotion;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CVtxInfo
{
public:
	CVtxInfo() { m_nBone = NULL; m_fWeight = NULL; m_pos = NULL; };
	~CVtxInfo() {};
	int			&GetnMaxBone(void) { return m_nMaxBone; };
	int			*&GetnBone(void) { return m_nBone; };
	float		*&GetfWeight(void) { return m_fWeight; };
	D3DXVECTOR3 *&Getpos(void) { return m_pos; };

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	int			m_nMaxBone;		//�{�[���̐�
	int			*m_nBone;		//�{�[��
	float		*m_fWeight;		//�E�G�C�g
	D3DXVECTOR3 *m_pos;			//�ʒu
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBone
{
public:
	CBone() { m_pMtx = NULL; };
	~CBone() {};

	D3DXMATRIX	*&GetPairMtx(void) { return m_pMtx; }
	D3DXMATRIX	&GetMtx(void) { return m_Mtx; }
	D3DXVECTOR3 &GetaddRot(void) { return m_addRot; }
	D3DXVECTOR3 &GetaddRotMove(void) { return m_addRotMove; }
	D3DXVECTOR3 &GetaddPos(void) { return m_addPos; }
	D3DXVECTOR3 &GetaddPosMove(void) { return m_addPosMove; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	D3DXMATRIX		*m_pMtx;		//�e�̃��[���h�}�g���b�N�X
	D3DXMATRIX		m_Mtx;			//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_addRot;					//���Z�̌��� ���[�V����
	D3DXVECTOR3		m_addRotMove;				//���[�V�����̈ړ�
	D3DXVECTOR3		m_addPos;					//���Z�̌��� ���[�V����
	D3DXVECTOR3		m_addPosMove;				//���[�V�����̈ړ�
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCharParts
{
public:
	typedef enum
	{
		BRIG_hip,		//�{�b�N�X���O	�K
		BRIG_hara,		//�{�b�N�X���O	��
		BRIG_mune,		//�{�b�N�X���O	��
		BRIG_head,		//�{�b�N�X���O	��
		BRIG_armUR,		//�{�b�N�X���O	�E��r
		BRIG_armUL,		//�{�b�N�X���O	����r
		BRIG_armD,		//�{�b�N�X���O	���r
		BRIG_hand,		//�{�b�N�X���O	��
		BRIG_handR2,	//�{�b�N�X���O	�E�b
		BRIG_handR3,	//�{�b�N�X���O	�E�w
		BRIG_handL2,	//�{�b�N�X���O	���b
		BRIG_handL3,	//�{�b�N�X���O	���w
		BRIG_legUR,		//�{�b�N�X���O	�E��
		BRIG_legUL,		//�{�b�N�X���O	����
		BRIG_legD,		//�{�b�N�X���O	��
		BRIG_foot,		//�{�b�N�X���O	��
		TEST_000,		//TEST
		BOX_100,		//���^�X�L�����b�V���p���f��
		Face_000,		//���^�X�L�����b�V���p���f��
		Cloak_000,		//�}���g
		BRIG_Sword0,	//��
		BRIG_Stick,		//��
		PARTS_MAX
	}PARTS;
	CCharParts(void) { m_pBone = NULL; m_pChar = NULL; m_pDrawMtx = NULL; m_pMeshModel = NULL; m_pModel = NULL; };
	~CCharParts() {};

	static CVtxInfo *&GetVtxInfo(int nID) {return m_pVtxInfo[nID]; }
	static void SetTEST_000(CCharacter *pChar);
	static void SetBox_100(CCharacter *pChar);
	static void SetBox_Sword(CCharacter *pChar);
	static void SetBox_Stick(CCharacter *pChar);

	void LoadChar(int nNumber, char *aStr);
	static void LoadVtx(int nNumber, char *aStr);

	void Draw(CCharacter *pChar);
	void DrawModel(CCharacter *pChar, int &nCount, bool bTex);
	void Uninit(void);

	virtual void SetVtx(int &nCount);	//��X�o�b�t�@�̂��������
	void Set(int nNumber, D3DXMATRIX *pDraw, PARTS model);
	void SetBone(int nNumber, D3DXMATRIX *pPair, D3DXVECTOR3 pos);

	CCharacter		*&GetpChar(void) { return m_pChar; }
	D3DXMATRIX		&GetmtxWorld(int nNumber)	{ return m_pBone[nNumber].GetMtx(); }
	CMotion::TYPE	&GetMotion(void)			{ return m_Motion; };
	CBone			*&GetBone(void)				{ return m_pBone; };
	PARTS			*&GetModel(void)			{ return m_pModel; };
	LPD3DXMESH		*&GetpMeshModel(void) { return m_pMeshModel; };
	D3DXMATRIX		**&GetDrawMtx(void)			{ return m_pDrawMtx; };
	int				&GetnMaxBone(void) { return m_nMaxBone; };
	int				&GetnMaxModel(void) { return m_nMaxModel; };
	void			NewBone(int nMax);
	void			NewModel(int nMax);

private://*****************************************************************************
	static CVtxInfo *m_pVtxInfo[PARTS_MAX];
		//�ϐ��錾//***********************************************************************
	CCharacter		*m_pChar;		//�L�����̃|�C���^
	CMotion::TYPE	m_Motion;		//���[�V�����̎��
	CBone			*m_pBone;		//�{�[��
	PARTS			*m_pModel;		//���f��
	LPD3DXMESH		*m_pMeshModel;	//���b�V�����ւ̃|�C���^
	D3DXMATRIX		**m_pDrawMtx;	//�`�掞�Ɏg���{�[��
	int				m_nMaxBone;		//�{�[���̍ő吔
	int				m_nMaxModel;	//���f���̍ő�
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCharacter	:	public CScene
{
public:
	typedef struct
	{//��ނ��Ƃ̃��f�����ۑ�
		LPD3DXMESH		MeshModel = NULL;		//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
		DWORD			nNumMatModel = NULL;	//�}�e���A���̏��
		D3DXVECTOR3		*pPos;					//�ʒu�̒��_���
		CScene::TEXTURE	tex;					//�摜
		char			aText[32];				//���f���ǂݍ��݂��x�����ߕK�v�ɂȂ�܂Ńe�L�X�g�ŊǗ�
	}MODEL_PARTS;
	//*****************************************************************************
	typedef enum
	{
		MOTION_NEUTRAL,		//�j���[�g����
		MOTION_WALK,		//����
		MOTION_JUMP,		//�W�����v
		MOTION_LAND,		//���n
		MOTION_S_NEUTRAL,	//�󒆃j���[�g����
		MOTION_BOOST,		//�n��u�[�X�g
		MOTION_BOOST_END,		//�u�[�X�g�I��
		MOTION_STEP,		//�X�e�b�v
		MOTION_GUARD,		//�K�[�h
		MOTION_PARIS,		//�p���B
		MOTION_GUARD2,		//�K�[�h������
		MOTION_PARIS2,		//�p���B��e��
		MOTION_DESPONDENCY,	//����
		MOTION_BLOW,		//�������
		MOTION_DOWN,		//�_�E��
		MOTION_RETURN,		//���A
		MOTION_APPEAL,		//�A�s�[��
		MOTION_ATTACK,		//�U�����[�V����
	}MOTION;
	typedef enum
	{
		DIRECT_NO,		//�w���Ȃ�
		DIRECT_ATTACK,		//��U��
		DIRECT_ATTACK2,		//���U��
		DIRECT_SKILL1,		//�X�L���U��
		DIRECT_SKILL2,		//�X�L���U��
		DIRECT_JUMP,		//�W�����v
		DIRECT_BOOST,		//�u�[�X�g
		DIRECT_GUARD,		//�K�[�h
		DIRECT_PARIS,		//�p���B
	}DIRECT;
	typedef enum
	{
		LOCK_AIR,	//���������b�N
		LOCK_NO,	//���������b�N
		LOCK_FIRST,	//���������b�N
		LOCK_RIGHT,	//�E�������b�N
		LOCK_LEFT,	//���������b�N
		LOCK_NEAR,	//�߂����̂����b�N
		LOCK_MAX,
	}LOCK;
	typedef enum
	{
		STATE_NONE,		//�ʏ�
		STATE_AVOID,	//���
		STATE_PARIS,	//�󂯗���
		STATE_GUARD,	//�h��
		STATE_ARMOR,	//�X�[�p�[�A�[�}�[
		STATE_CANCEL,	//�����̃L�����Z���w��
		STATE_MAX,
	}STATE;
	typedef enum
	{
		TEAM_PLAYER,	//�v���C���[
		TEAM_ENEMY,		//�G�l�~�[
		TEAM_IGNORED,	//����
		TEAM_MAX,
	}TEAM;

	CCharacter(int nPrioryity = CHAR_PRIORITY) : CScene::CScene(nPrioryity) { m_pTex = NULL; m_pParts = NULL; m_pGage = NULL; };
	~CCharacter() {};
	//*****************************************************************************
	static LPD3DXMESH Load(CCharParts::PARTS parts);
	static void Load(void);
	static void UnLoad(void);
	static void AtkCollision(void);								//�U���`�F�b�N �S�̂���
	static void HitCheck(CScene *&pAtkChar, CScene *&pDefChar);	//�U���`�F�b�N �P�̂���
	static void HitMotionAll(void);								//�q�b�g�ヂ�[�V�����X�V
	//*****************************************************************************
	HRESULT Init(void);
	void Uninit(void);
	void Update(bool bMove);						//���[�V�����̍X�V
	void DirectMotion(DIRECT Direct);				//���[�V�����ւ̎w��
	void AtkRot(float &fRot, int &nID);						//�U�����̊p�x�␳
	void Draw(void);
	virtual void Dead(void);
	virtual void Over(void);
	virtual void SetLightCol(D3DXCOLOR col) {};
	virtual void SetLightStr(float fGoal, float fFrame) {};

	//*****************************************************************************
	void AtkVoice(void);
	void DefVoice(void);
	void DeadVoice(void);
	void SetNextMotion(int nNumber);				//���̃��[�V�����ւ̗\��
	void ResetMotion(void);							//���[�V�������j���[�g�����Ƀ��Z�b�g
	void SetRotMotion(void);						//���݂̃L�[�Ɋp�x�����S�ɍ��킹��
	void SetPlusFrame(float fPFrame, float fCount);	//�t���[���̐i�s���x�ݒ�
	void CollisionAll(CScene *pChar);	//�L�������m�̂����蔻��
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);			//�ݒ菈��
	CScene *LockChar(LOCK lock);			//�L���������b�N
	void LockCancel(void);					//�L�������b�N������
	void SetStatus(void);					//���݂̃��x���ŃX�e�[�^�X�v�Z
	//*****************************************************************************
	TEAM		&GetTeam(void)				{ return m_Team; }
	int			&GetnMaxParts(void)			{ return m_nMaxParts; }

	CScene::DRAW_TYPE  &GetDrawType(void) { return m_DrawType; }
	D3DXMATRIX  &GetMtx(void)				{ return m_Mtx; }
	D3DXVECTOR3 &Getpos(void)				{ return m_pos; }
	D3DXVECTOR3 &Getposold(void)			{ return m_posold; }
	D3DXVECTOR3 &Getrot(void)				{ return m_rot; }
	D3DXVECTOR3 &Getaddpos(void)			{ return m_addpos; }
	D3DXVECTOR3 &GetaddPosmove(void)		{ return m_addPosmove; }
	D3DXVECTOR3 &Getmove(void)				{ return m_move; }
	D3DXVECTOR3 &Getlength(void)			{ return m_length; }
	D3DXCOLOR	&GetCollar(void)			{ return m_col; }
	float		&GetfRot(void)				{ return m_fRot; }
	float		&GetfSumFrame(void)			{ return m_fSumFrame; }
	int			&GetnNumMotion(int nNumber) { return m_nNumMotion[nNumber]; }
	bool		&GetbJump(void)				{ return m_bJump; }
	bool		&GetbOrbit(void)			{ return m_bOrbit; }
	CCharParts	**&GetpParts(void)			{ return m_pParts; }
	CMotion::TYPE	&GetType(void)			{ return m_pParts[0]->GetMotion(); }
	CScene		*&GetpLockChar(void)		{ return m_pLockChar; }

	int			&GetnLevel(void)			{ return m_nLevel; }
	float		&GetfMaxLife(void)			{ return m_fMaxLife; }
	float		&GetfLife(void)				{ return m_fLife; }
	float		&GetfMaxSP(void)			{ return m_fMaxSP; }
	float		&GetfSP(void)				{ return m_fSP; }
	float		&GetfAtk(void)				{ return m_fAtk; }
	float		&GetfMaxStamina(void)		{ return m_fMaxStamina; }
	float		&GetfStamina(void)			{ return m_fStamina; }
	bool		&GetbVtx(void) {			return m_bVtx; }
	bool		&GetbBoost(void)			{ return m_bBoost; }
	bool		*&GetpUseMotion(void)		{ return m_pUseMotion; }
	float		*&GetpWaitMotion(void)		{ return m_pWaitMotion; }
	int			&GetnInvincible(void)		{ return m_nInvincible; }

	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }
	void		DrawGage(void) { if (m_pGage != NULL) { m_pGage->Draw(); } };

	virtual void CancelLock(void);													//���S���A���g�ւ̃��b�N���O��
	static MODEL_PARTS *&GetpartsAll(int nNumber) { return m_partsAll[nNumber]; }	//�S�p�[�c�̃|�C���^��Ԃ�
	static bool CheckSP(CMotion::TYPE type, int nNumber, float &fValue);			//�X�^�~�i�̎g�p
	static float GetEffect_SP(int nNumber);											//�L�[���ɌĂԌ���
private://*****************************************************************************
	void HitMotion(void);				//�q�b�g�ヂ�[�V�����X�V �P�̂���
	void CancelUpdate(void);			//���[�V�����̃L�����Z���X�V
	void SetCancelMotion(int nNumber);	//���[�V�����̃L�����Z���ݒ�
	void SetAtkNumber(int nNumber);		//���[�V�����̔ԍ��̕ۑ�
	void ResetUpdate(void);				//���[�V�����̔ԍ��̃��Z�b�g�X�V
	void ResetAtkNumber(void);			//���[�V�����̔ԍ��̃��Z�b�g
	bool CheckAtkNumber(int nNumber);	//���[�V�����̔ԍ��̊m�F
	void Collision(CScene *pChar);		//�L�������m�̂����蔻��
	void SetEffect(CKey *&pKey);		//�L�[���ɌĂԌ���
	float AngleCheck(float fAngle0, float fAngle1);	//2�̊p�x�̍���Ԃ�
	void UseStamina(float fValue);		//�X�^�~�i�̎g�p
	bool UseSP(int nNumber);			//�X�^�~�i�̎g�p

	void ReSetHitChar(void);			//�L�����q�b�g�������Z�b�g
	bool CheckHitChar(CScene *&pChar);	//�L�����q�b�g����ۑ�
		//�ϐ��錾//***********************************************************************
	static MODEL_PARTS	*m_partsAll[CCharParts::PARTS_MAX];	//�S�p�[�c���

	TEAM			m_Team;				//��������`�[��(�U������p)
	STATE			m_state;			//���
	LPDIRECT3DTEXTURE9	m_pTex;			//�摜
	CScene::DRAW_TYPE	m_DrawType;		// �`�悷����@(���Z�����Ȃ�)

	int				m_nMaxParts;		//�p�[�c��
	CCharParts		**m_pParts;			//�����̃p�[�c���
	D3DXMATRIX		m_Mtx;			//���[���h�}�g���b�N�X

	D3DXCOLOR		m_col;				//���g�̐F
	D3DXVECTOR3		m_pos;				//�v���C���[�̌��_
	D3DXVECTOR3		m_posold;			//�O��̃��f���̈ʒu
	D3DXVECTOR3		m_rot;				//�v���C���[�̌���
	D3DXVECTOR3		m_move;				//���f���̈ʒu
	D3DXVECTOR3		m_addpos;			//���Z�̈ʒu ���[�V����
	D3DXVECTOR3		m_addPosmove;		//���[�V�����̈ړ�
	D3DXVECTOR3		m_length;			//�|���S���̒���
	D3DXVECTOR3		m_FNor;				//�n�ʂ̖@��
	float			m_fRot;				//�ړ�����
	float			m_fARot;			//���[�V�����o�^���̓��͌���
	int				m_nInvincible;		//���G����
	int				m_nCntReUse;		//���g�p�̎g�p���[�V�����̃��Z�b�g�܂ł�F
	float			*m_pWaitMotion;		//�҂����Ԃ̂��郂�[�V�������Ǘ�
	bool			*m_pUseMotion;		//�g�p�����U�����[�V�����L�^

	int				m_nNumMotion[4];	//0:���݂̃��[�V���� 1:���̃��[�V���� 2:�L�[�ԍ� 3:�O�̃��[�V����
	float			m_fFrame;			//���݂̃t���[����
	float			m_fFramePlus;		//�t���[���ւ̃v���X�l
	float			m_fFramePlus2;		//�t���[���ւ̎��R�l
	float			m_fInitFrame;		//�t���[���̑��x�������������܂ł̒l
	float			m_fSumFrame;		//�i�s���鍇�v�t���[����
	float			m_fMotionFrame;		//MOTION�S�̂̃t���[�������J�E���g
	float			m_fKeepFrame;		//MOTION���p������F��
	int				m_nCancelFrame;		//�L�����Z���҂��̕ێ��t���[����
	int				m_nLeg;				//�E�����o���Ă��邩�������o���Ă��邩
	int				m_nCntDamage;		//�_���[�W�ォ��̎��ԃJ�E���g
	int				m_nCntHit;			//�q�b�g��
	CScene			*m_pHit[MAX_HITCHAR];//�������G
	bool			m_bJump;			//�W�����v�̗L��

	bool			m_bVtx;				//���_���ݒ�̗L��
	bool			m_bBoost;			//�u�[�X�g�̗L��
	bool			m_bOrbit;			//�I�[�r�b�g�̔j���p
	CScene			*m_pLockChar;		//lock���Ă���L����
	CSound::LABEL	m_Voice;		//�{�C�X���

	int				m_nLevel;			//���x��
	float			m_fMaxLife;			//�q�b�g�|�C���g�̍ő�l
	float			m_fLife;			//�q�b�g�|�C���g
	float			m_fMaxSP;			//�X�y�V�����|�C���^�̍ő�l
	float			m_fSP;				//�X�y�V�����|�C���g
	float			m_fAtk;				//�U����
	float			m_fCntStamina;		//�X�^�~�i�񕜂܂ł��J�E���g
	float			m_fMaxStamina;		//�X�^�~�i�̍ő�l
	float			m_fStamina;			//�X�^�~�i

	C3DGage			*m_pGage;			//����HP�̕\��
};
#endif
