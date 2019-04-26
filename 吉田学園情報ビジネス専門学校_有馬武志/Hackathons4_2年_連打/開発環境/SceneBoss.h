#pragma once
//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEBOSS_H_
#define _SCENEBOSS_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"
#include "2DGage.h"
#include "sound.h"
#include "manager.h"

class C3D;
class CFont;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SBOSS_PRIORITY		(1)
#define MAX_BEfeect			(2)
#define UI_PRIORITY			(6)
#define SBOSS_LENGTH		(10.0f)

//*****************************************************************************
// �N���X�̒�` �{�X�pUI
//*****************************************************************************
class CSceneBossUI : public CScene
{
public:
	CSceneBossUI(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity) { m_pLifeGage = NULL; m_p2D = NULL; };
	~CSceneBossUI() {};

	C2DGage *&GetGage(void)			{ return m_pLifeGage; };
	C2D *&Getp2D(void)	{ return m_p2D; };
	void Uninit(void);	//�폜
	void Update(void);	//�X�V
	void Draw(void);	//�`��

private:
	C2DGage			*m_pLifeGage;	//HP�Q�[�W
	C2D				*m_p2D;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneBoss : public CScene3D
{
public:
	typedef enum
	{
		/*�X��*/	TEX_MANAGER,
		/*�����{�X*/	TEX_BOSS01,
		TEXTURE_MAX
	}TEXTURE;

	CSceneBoss(int nPrioryity = SBOSS_PRIORITY) : CScene3D::CScene3D(nPrioryity) { SetObjType(CScene::OBJTYPE_BOSS); m_p3DShadow = NULL; m_pUI = NULL; };
	~CSceneBoss() {};

	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);		//�e�N�X�`���̐���
	static void					UnLoad(TEXTURE tex);	//�e�N�X�`���̎w��j��
	static void					UnLoad(void);			//�e�N�X�`���̔j��
	void Update(void);
	void Draw(void);
	void Uninit(void) { if (m_pUI != NULL) { m_pUI->Uninit(); m_pUI = NULL; } CScene3D::Uninit(); };
	void DropUninit(void);
	void SetStatus(TEXTURE tex);
	void InitShadow(void);
	bool Damage(float fAtk);
	void SetJump(float fJump) { m_move.y = fJump; m_bJump = true; };
	void CreateUI(TEXTURE tex);
	static void Appear(TEXTURE tex);

	TEXTURE &GetTexture(void)		{ return m_TexType; };
	D3DXVECTOR3 &GetPosOld(void)	{ return m_posold; };
	D3DXVECTOR3 &GetMove(void)		{ return m_move; };
	float &GetfLife(void)			{ return m_fLife; };
	float &GetfMaxLife(void)		{ return m_fMaxLife; };
	float &GetfAtk(void)			{ return m_fAttack; };
	float &GetfDef(void)			{ return m_fDefense; };
	float &GetfPlusY(void)			{ return m_fPlusY; };
	float &GetfModeChange(void)		{ return m_fModeChange; };
	float &GetfAngle(void)			{ return m_fAngle; };
	bool  &GetbJump(void)			{ return m_bJump; }
	bool  &GetbShotDelete(void)		{ return m_bShotDelete; }
	bool  &GetbCollision(void)		{ return m_bCollision; }
protected://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^

private://*****************************************************************************
	static C2DGage			*m_pLifeGage;	//HP�Q�[�W

	D3DXVECTOR3 m_posold;		//�O�̏ꏊ
	D3DXVECTOR3 m_move;		//�ړ���
	int		m_nLevel;		//���x��
	float	m_fMaxLife;		//Max�q�b�g�|�C���g
	float	m_fLife;		//�q�b�g�|�C���g
	float	m_fAttack;		//�U����
	float	m_fDefense;		//�h���
	float	m_fPlusY;		//�W�����v�\�����Ɏg�p ���ۂɉ��Z����̂�Z��
	float	m_fModeChange;	//���̍s���܂ł�F��
	float	m_fAngle;		//���˕���
	bool	m_bShotDelete;	//���@�̒e�̍폜���f�p
	bool	m_bJump;		//�W�����v���f�p
	bool	m_bCollision;	//�����蔻��̗L��
	TEXTURE	m_TexType;		//�摜�@���ʗp
	C3D		*m_p3DShadow;	//�e
	CSceneBossUI	*m_pUI;	//UI
};
//*****************************************************************************
// �N���X�̒�` �{�X�o�����o�p
//*****************************************************************************
class CSceneBossEffect : public CScene
{
public:
	CSceneBossEffect(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_nCntState = 0;
		for (int nCount = 0; nCount < MAX_BEfeect; nCount++)
		{
			m_p2D[nCount] = NULL;
		}
	};
	~CSceneBossEffect() {};

	C2DPolygon *&Getp2D(void) { return m_p2D[0]; };
	void Uninit(void);	//�폜
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	void Set(CSceneBoss::TEXTURE tex);	//�ݒ�

private:
	int		m_nCntState;
	C2DPolygon		*m_p2D[MAX_BEfeect];
};

//*****************************************************************************
// �N���X�̒�` �X��
//*****************************************************************************
class CSceneManager : public CSceneBoss
{
public:
	typedef enum
	{
		/*���X*/	MANAGER_START,
		/*�w��*/	MANAGER_BUY,
		/*�X��*/	MANAGER_WAIT,
		/*��e*/	MANAGER_DAMAGE,
		/*��*/	MANAGER_HEEL,
		/*�U��*/	MANAGER_ATK,
		MANAGER_MAX
	}MANAGER;
	typedef enum
	{
		ATTACK_START,	//�����U��
		ATTACK_HALF,	//HP���������ꂽ
		ATTACK_0,		//�΂�T��
		ATTACK_1,		//�^�[�Q�b�g�������[�U�[
		ATTACK_2,		//�^�[�Q�b�g�n�_����
		ATTACK_3,		//�~�`�΂�T��
		ATTACK_MAX
	}ATTACK;
	CSceneManager(int nPrioryity = SBOSS_PRIORITY) : CSceneBoss::CSceneBoss(nPrioryity) { m_pFont = NULL; m_p2D = NULL; };
	~CSceneManager() {};

	void Set(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	MANAGER &GetManager(void) { return m_Manager; };

private:
	// �֐��錾 //***********************************************************************
	void Attack_Start(void);
	void Attack_Half(void);
	void Attack_0(void);
	void Attack_1(void);
	void Attack_2(void);
	void Attack_3(void);
	// �ϐ��錾 //***********************************************************************

	ATTACK  m_Attack;		//���݂̍U���p�^�[��
	MANAGER m_Manager;		//�X���̏��
	bool	m_bFly;			//���~���㏸��
	bool	m_bHalf;		//�����؂������ǂ���
	D3DXVECTOR3 m_Target;	//�����܂ł̕ۑ��p
	CFont	*m_pFont;		//�����̃|�C���^
	CScene2D	*m_p2D;			//�����̃E�B���h�E
};
//*****************************************************************************
// �N���X�̒�` �����{�X
//*****************************************************************************
class CSceneBoss01 : public CSceneBoss
{
public:
	typedef enum
	{
		ATTACK_START,	//�����U��
		ATTACK_HALF,	//HP���������ꂽ
		ATTACK_0,		//�΂�T��
		ATTACK_1,		//�^�[�Q�b�g�������[�U�[
		ATTACK_2,		//�^�[�Q�b�g�n�_����
		ATTACK_3,		//�~�`�΂�T��
		ATTACK_MAX
	}ATTACK;
	CSceneBoss01(int nPrioryity = SBOSS_PRIORITY) : CSceneBoss::CSceneBoss(nPrioryity) {  };
	~CSceneBoss01() {};

	void Set(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);

private:
	// �֐��錾 //***********************************************************************
	void Attack_Start(void);
	void Attack_Half(void);
	void Attack_0(void);
	void Attack_1(void);
	void Attack_2(void);
	void Attack_3(void);
	// �ϐ��錾 //***********************************************************************

	ATTACK  m_Attack;		//���݂̍U���p�^�[��
	D3DXVECTOR3	m_JumpMove;		//�����ۑ�
	int		m_nReplay;		//�񐔕ۑ�
	int		m_nStart;		//�o��ς݂��ǂ���
	bool	m_bHalf;		//�����؂������ǂ���
	D3DXVECTOR3 m_Target;	//�����܂ł̕ۑ��p
};
#endif
