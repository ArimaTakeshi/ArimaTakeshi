#pragma once
//=============================================================================
//
// �v���C���[����(��ԏ������܂�) [ScenePlayer.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEPlayer_H_
#define _SCENEPlayer_H_

#include "main.h"
#include "scene.h"
#include "sceneModel.h"
#include "SceneAnim3D.h"
#include "SceneBullet.h"
#include "Number.h"
#include "2DGage.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_D		(0)
#define MODEL_U		(1)
#define CAMERA_Y	(475.0f)
#define SHOT_JUST	(6)
#define PLUS_LIFE	(50.0f)
#define PLUS_ATK	(0.01f)
#define PLUS_DEF	(0.01f)
#define PLAYER_Y	(20.5f)
#define BOMB_WAIT_TIME		(600)
#define BOMB_TIME			(BOMB_WAIT_TIME + 60)
#define MAX_UI			(5)
#define UI_PRIORITY		(6)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class ITEM
{
public:
	typedef enum
	{//�A�C�e���̎��
		TYPE_SPDUP = 0,
		TYPE_PAIR0, TYPE_NORIVER, TYPE_NOSTOP,
		TYPE_CHARGEUP, TYPE_SCOREUP, TYPE_PAIR1,
		TYPE_MAX
	}TYPE;
	ITEM() {};
	~ITEM() {};
	TYPE			&GetType(void) { return m_type; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	TYPE	m_type;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class ITEM_PAIR : public ITEM
{
public:
	typedef enum
	{//�A�C�e���̎��
		ITEM_SPDUP = 0,
		ITEM_PAIR0, ITEM_NORIVER, ITEM_NOSTOP,
		ITEM_CHARGEUP, ITEM_SCOREUP, ITEM_PAIR1,
		ITEM_MAX
	}TYPE;
	ITEM_PAIR() { m_bShotDelete = true; };
	~ITEM_PAIR() {};
	bool	&GetShotDelete(void) { return m_bShotDelete; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	bool	m_bShotDelete;
};

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneTank : public CSceneModel
{
public:
	CSceneTank(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity)
	{
		m_pEffect = NULL; m_pEffectU = NULL;
	};
	~CSceneTank() {};

	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);

	bool Damage(float fAtk);
	void Heel(float fHeel, bool bEffect);
	void Heal(void);
	void EffectUpdate(void);
	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType);
	CSceneBullet::SHOT *GetShot(void)	{ return &m_shot; }
	D3DXVECTOR3 *GetPositionOld(void)	{ return &m_posold; }
	D3DXVECTOR3 *GetMove(void)			{ return &m_move; }
	float		&GetfSlip(void)			{ return m_fSlip; }

	float		*GetfMoveAngle(void)	{ return &m_fMoveAngle; }
	float		&GetfCharge(void)		{ return m_fCharge; }
	float		*GetfLife(void)			{ return &m_fLife; }
	float		&GetfMaxLife(void)		{ return m_fMaxLife; }
	float		&GetfAtk(void)			{ return m_fAttack; }
	float		&GetfDef(void)			{ return m_fDefense; }
	int			&GetnLevel(void)		{ return m_nLevel; }
	int			&GetnFire(void)			{ return m_nFire; }
	int			&GetnIce(void)			{ return m_nIce; }
	int			&GetnLightning(void)	{ return m_nLightning; }
	int			&GetnUV(void)			{ return m_nUV; }
	void		GetStatus(void);	//�X�e�[�^�X�v�Z

	CSceneFrontAnim		*GetpEfect(void)		{ return m_pEffect; }
	LPDIRECT3DTEXTURE9	*&GetTextureU(void)		{ return m_pTexU; }
	TEXTURE				&GetTEX_TYPE(int nType)	{ return m_Type[nType]; }
	MODEL				&GetModelU(void)		{ return m_ModelU; }
	CSceneFrontEffect	*&GetpEffectU(void)		{ return m_pEffectU; }
	D3DXVECTOR3			*GetRotationU(void)		{ return &m_rotU; }

protected://*****************************************************************************
	typedef enum
	{
		CHARGE_NO = 0,
		CHARGE_30,
		CHARGE_90,
		CHARGE_180,
		CHARGE_300,
		CHARGE_MAX
	}CHARGE;
	void	Update(bool bMove, bool bCharge, bool bShot, bool bShelling, bool bBoost, bool bBrake, ITEM *pItem);
	void	DrawModel(int nModelID);
	void	ChargeNews(D3DXVECTOR3 *&pos);

	void	Shot(D3DXVECTOR3 *&pos, float fChargeP);	//�`���[�W�ɉ������e�𔭎� �C���ɂ���ĕς��
	void	Shot_Ptn01(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN01 �e��
	void	Shot_Ptn02(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN02 �e��
	void	Shot_Ptn03(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN03 �e��
	void	Shot_Ptn04(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN04 �e��
	void	Shot_Ptn05(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN05 �e��
	void	Shot_Ptn06(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN05 �e��
	void	Shot_Ptn07(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN05 �e��
	void	Shot_Ptn08(int nCharge, D3DXVECTOR3 *&pos);	//�C��PTN05 �e��

	void	ShortAtk(D3DXVECTOR3 *&pos);				//�ߐڍU��, �C���ɂ���ĕς��
	void	Short_Ptn01(D3DXVECTOR3 *&pos);			//�C��PTN01 �C��
	void	Short_Ptn02(D3DXVECTOR3 *&pos);			//�C��PTN02 �C��
	void	Short_Ptn03(D3DXVECTOR3 *&pos);			//�C��PTN03 �C��
	void	Short_Ptn04(D3DXVECTOR3 *&pos);			//�C��PTN04 �C��
	void	Short_Ptn05(D3DXVECTOR3 *&pos);			//�C��PTN05 �C��
	void	Short_Ptn06(D3DXVECTOR3 *&pos);			//�C��PTN05 �C��
	void	Short_Ptn07(D3DXVECTOR3 *&pos);			//�C��PTN05 �C��
	void	Short_Ptn08(D3DXVECTOR3 *&pos);			//�C��PTN05 �C��


	//�ϐ��p//***********************************************************************
	//bool		*GetbBarrier(void) { return &bBarrier; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	CSceneFrontAnim		*m_pEffect;		//��Ԃ̃G�t�F�N�g
	CSceneFrontEffect	*m_pEffectU;	//�C���̃G�t�F�N�g
	//bool				m_bBarrier;

	CSceneBullet::SHOT	m_shot;			//����������
	MODEL				m_ModelU;		//�C�����f��
	LPDIRECT3DTEXTURE9	*m_pTexU;		//�摜

	D3DXVECTOR3			m_rotU;			//�C���̊p�x
	D3DXVECTOR3			m_posold;		//�ړ���
	D3DXVECTOR3			m_move;			//�ړ���
	float				m_fMoveAngle;	//�ړ�����
	float				m_fSlip;		//����
	float				m_fCharge;		//Charge��
	int					m_nBoostTime;	//�u�[�X�g�ւ̑҂�����
	float				m_fWaitTime;	//�ړ��s�̑҂�����

	float				m_fLife;		//�q�b�g�|�C���g
	TEXTURE				m_Type[2];		//�C���Ǝԑ̂̉摜�@����ɕK�v
	int					m_nLevel;		//���x��
	bool				m_bShotDelete;	//�e���������f

	int					m_nFire;		//�₯��	��F�_���[�W
	int					m_nIce;			//����		�ړ����xDOWN
	int					m_nLightning;	//���d		�`���[�W���x����
	int					m_nUV;			//�e�̐F
		//�v�Z��X�e�[�^�X//***********************************************************************
	float				m_fMaxLife;		//Max�q�b�g�|�C���g
	float				m_fAttack;		//�U����
	float				m_fDefense;		//�h���
	float				m_fSpeed;		//���x
	float				m_fWeight;		//�d��
	float				m_fBoost;		//������+���x
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CScenePlayer : public CSceneTank
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_ADVANCE,		//���̃}�b�v�֐i��
		STATE_MAX
	}STATE;

	CScenePlayer(int nPrioryity = MODEL_PRIORITY) : CSceneTank::CSceneTank(nPrioryity)
	{ 
		m_nPlayerID = m_nNumPlayer; m_nNumPlayer++; m_pHeart = NULL; m_pLifeGage = NULL; m_pExpGage = NULL;
		for (int nCount = 0; nCount < MAX_UI; nCount++) { m_pUI[nCount] = NULL; m_pNumber[nCount] = NULL; }
	};
	~CScenePlayer() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType);
	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);

	bool	PlayPlayer(void);
	void	Shield(void);
	void	PEffectUpdate(void);
	void	DeadPlayer(bool bDead);
	void	DrawUI(void);
	void	PlusLevel(int nLevel);
	void	SetItem(ITEM::TYPE Item);
	void	AddExp(int nExp);

	static	int		&GetnNumPlayer(void) { return m_nNumPlayer; }
	static	int		&GetnStage(void)	{ return m_nStage; }
	static	bool	&GetbCamera(void)	{ return m_bCamera; }
	static	bool	&GetbShop(void)		{ return m_bShop; }
	CNumber			*&GetScore(void)	{ return m_pNumber[1]; }

	int				&GetLifeUP(void)	{ return m_pNumber[2]->GetnNumber(); }
	int				&GetAtkUP(void)		{ return m_pNumber[4]->GetnNumber(); }
	int				&GetDefUP(void)		{ return m_pNumber[3]->GetnNumber(); }
	ITEM			*&GetItem(void)		{ return m_pItemType; }
	int				&GetnDeadCount(void) { return m_nDeadCount; }

	void			PlusLifeUP(int nPlus) { m_pNumber[2]->AddNumber(nPlus); }
	void			PlusDefUP(int nPlus)  { m_pNumber[3]->AddNumber(nPlus); }
	void			PlusAtkUP(int nPlus)  { m_pNumber[4]->AddNumber(nPlus); }
	int				&GetPlayerID(void)	{ return m_nPlayerID; }
	int				&GetnInvincible(void) { return m_nInvincible; }

	CSceneFrontEffect *&GetpHeart(void) { return m_pHeart; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static	int		m_nNumPlayer;	//���v�v���C���[��
	static	int		m_nStage;		//�X�e�[�W�ԍ�
	static	bool	m_bCamera;		//�J�����𓮂�������
	static	bool	m_bShop;		//���݂��V���b�v���ǂ���

	//�A�C�e��
	float	m_fExp;			//�o���l
	float	m_fMaxExp;			//�o���l
	ITEM	*m_pItemType;			//�A�C�e���̎��

	CSceneFrontEffect	*m_pHeart;		//��ԐS���̃G�t�F�N�g
	CSceneFrontEffect	*m_pBomb;		//�{���̃G�t�F�N�g(���@�w)
	int		m_nBombTime;		//�{���g�p�܂ł̎��ԃJ�E���g
	int		m_nDeadCount;		//���S���ď�����܂ł̎���
	int		m_nInvincible;		//���G����

	int				m_nPlayerID;	//�v���C���[ID
	C2D				*m_pIcon;		//�A�C�R��
	C2D				*m_pItem;		//�A�C�e��
	C2DGage			*m_pLifeGage;	//HP�Q�[�W
	C2DGage			*m_pExpGage;	//EXP�Q�[�W

	C2D				*m_pUI[MAX_UI];		//���x���A�X�R�A�A�����l3��
	CNumber			*m_pNumber[MAX_UI];	//���x���A�X�R�A�A�����l3��
};

#endif
