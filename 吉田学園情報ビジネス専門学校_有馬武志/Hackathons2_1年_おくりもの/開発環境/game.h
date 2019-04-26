#pragma once
//=========================================================================================================//
//
// �|���S���F�v���g�^�C�v�錾 [Scan.h]
// Author : Ryo Sugimoto
//
//=========================================================================================================//
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include"main.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define PLAYER_POSX3			(60)	//�摜��X�̕� / 2
#define PLAYER_POSY3			(45)	//�摜��Y�̕� / 2
#define PLAYER_CollisionX		(18)	//�摜��X�̂����蔻��
#define PLAYER_CollisionY		(28)	//�摜��Y�̂����蔻��
#define FIELD					(60)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_END,
	GAMESTATE_PAUSE

}GAMESTATE;

typedef struct
{
	GAMESTATE now;		//���݂̏��
	MODE CHANGE;		//�ς��郂�[�h
	int nCntGameState;	//�J�E���g�p

}GAME;

typedef enum
{//�A�j���[�V�����̎g�p���
	EXPLOSIONSTATE_PHIT,		//�v���C���[�ɂ����蔻��̂��锚��
	EXPLOSIONSTATE_PHITMINUS,	//�v���C���[�ɂ����蔻��̂��锚�� ����̏�����
	EXPLOSIONSTATE_EHIT,		//�G�ɂ����蔻��̂��锚��
	EXPLOSIONSTATE_EFFECT,		//�����蔻�薳��
	EXPLOSIONSTATE_DELETE,		//�����Ă���
}EXPLOSIONSTATE;
typedef enum
{//�v���C���[���G��
	USETYPE_PLAYER = 0,		//���@
	USETYPE_PLAYERANIM,		//���@��Animation
	USETYPE_ENEMY,			//�G
	USETYPE_IGNORE,			//����
	USETYPE_MAX,

}USETYPE;
typedef enum
{
	PLAYERANGLE_RIGHT = 0,
	PLAYERANGLE_LEFT,

}PLAYERANGLE;
typedef enum
{
	PLAYERSTATE_NORMAL = 0,
	PLAYERSTATE_INVINCBLE,		//���G���
	PLAYERSTATE_DNORMAL,		//���Ⴊ�݌�W�����v����񂵂��ł��Ȃ��̂�h��
	PLAYERSTATE_FALL,			//���蔲�����
	PLAYERSTATE_ATTACK,			//�U����ԁ@�A�Œ�
	PLAYERSTATE_SATTACK,		//�󒆍U����ԁ@�A�Œ�
	PLAYERSTATE_SKYATTACK,		//�U����Ԃւ̈ڍs�@��]��
	PLAYERSTATE_WAIT,			//�U����Ԃւ̑ҋ@�@��]��
	PLAYERSTATE_CATCH,			//�R���܂���
	PLAYERSTATE_CLIMBR,			//�R������Ă�����
	PLAYERSTATE_CLIMBL,			//�R������Ă�����
	PLAYERSTATE_BACK,			//�m�b�N�o�b�N���
	PLAYERSTATE_DOWN,			//���Ⴊ�ݏ��
	PLAYERSTATE_KNOCKBACK,		//�m�b�N�o�b�N���
	PLAYERSTATE_DAMAGE,			//�_���[�W���

}PLAYERSTATE;
typedef struct
{
	D3DXVECTOR3 respawn;	//�|���S���̈ʒu
	D3DXVECTOR3 pos;	//�|���S���̈ʒu
	D3DXVECTOR3 posold;	//�|���S���̈ʒu
	D3DXVECTOR3 move;	//�|���S���̈ړ���
	D3DXCOLOR col;
	PLAYERSTATE state;	//���
	int nCntState[2];	//��Ԃ̊Ǘ��p
	int nVibration;		//�Q�[�W���U�����鎞��
	int nScore;			//�X�R�A
	int nTime[2];		//���ԃJ�E���g
	int nJump;			//�W�����v��
	int nPtnAnim;		//�摜�̃p�^�[��
	int nCntAnim;		//�摜�̃J�E���^�[
	int nAnimSpeed;		//�A�j���[�V����SPEED
	int nAngle;			//����
	int nLengthX;
	int nLengthY;
	int nCollisionX;
	int nCollisionY;
	int nLevel;
	int nLevelold;
	int nEXP;
	int nMAXEXP;
	int nEXPold;
	int nMAXEXPold;
	int nLife;
	int nLifeold;
	int nMaxLife;
	int nAttack;
	int nDefense;
	int nPresent[3];
	int nClear;
	float fSkyWait;
	float fSteep;		//�|���S���̊p�x
	float fRide;		//����Ă�����̂���̈ړ��l
	float fMove;		//�󒆂̎��̈ړ��l
	bool bPowerUP[10];	//�p���[�A�b�v�f�ގ擾���
	bool bClock[10];	//���v�擾���
	bool bPowerUPold[10];	//�p���[�A�b�v�f�ގ擾���
	bool bClockold[10];		//���v�擾���
	bool bRun;			//�����Ă��邩�ǂ���
	bool bFall;			//����������񂾂�
	bool bUse;			//���� or ���S

}PLAYER;

typedef enum
{
	BLOCKSTATE_NONE = 0,	//�����Ȃ��u���b�N
	BLOCKSTATE_THIN,		//�㔻�肵���Ȃ��u���b�N
	BLOCKSTATE_THIN0,		//����
	BLOCKSTATE_THIN1,		//��������
	BLOCKSTATE_THIN2,		//�g�p�ς݉���
	BLOCKSTATE_MOVE,		//�����u���b�N
	BLOCKSTATE_BREAK,		//����u���b�N
	BLOCKSTATE_DAMAGE,		//�_���[�W��^����u���b�N
	BLOCKSTATE_DESS,		//������Ǝ��S
	BLOCKSTATE_OUT,			//��O����@������Ǝ��S
	BLOCKSTATE_FADE,		//���@�ɓ�����Ə����A�������Ă��Ȃ��ƍ����Ȃ�
	BLOCKSTATE_BG,			//�����蔻��̂Ȃ��u���b�N
	BLOCKSTATE_BOARD,		//�����蔻��̂Ȃ��u���b�N
	BLOCKSTATE_CLEAR,		//�N���A�u���b�N

}BLOCKSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ��l�̎c���
	D3DXCOLOR col;			// �F
	float fSteep;			//�p�x
	float fSpeed;
	float fRadius;			// ���a(�傫��)
	bool bUse;				// �g�p���Ă��邩�ǂ���

} EFFECT;

typedef enum
{
	ANIMTYPE_COIN = 0,	//�R�C��
	ANIMTYPE_CHECK0,		//�����n�_�X�V
	ANIMTYPE_CHECK1,		//�g�p�ςݕ����n�_
	ANIMTYPE_POWERUP,		//�p���[�A�b�vItem
	ANIMTYPE_HEEL,			//��
	ANIMTYPE_ALLHEEL,		//�S��
	ANIMTYPE_CLOCK,			//���v
	ANIMTYPE_BOARD,		//�Ŕ�
	ANIMTYPE_MESSAGE,	//�Ŕ���o�郁�b�Z�[�W
	ANIMTYPE_NONE,		//�X�N���[�����Ȃ�����

}ANIMTYPE;
typedef enum
{//�A�j���[�V�����̎g�p���
	ANIMATION_NORMAL = 0,
	ANIMATION_LOOP,
	ANIMATION_PLAYER,			//�v���C���[�̃p�^�[���ɉ����ĕύX
	ANIMATION_MAX,

}ANIMATION;

typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_EFFECT,

}BULLETTYPE;
typedef enum
{
	BULLETSTATE_NONE = 0,		//�����Ȃ�
	BULLETSTATE_NORMAL,			//�����Ȃ�
	BULLETSTATE_NOT,			//�g�p���Ă��Ȃ�
	BULLETSTATE_START,			//�J�n�̂݉���
	BULLETSTATE_ACCELERATOR,	//������������
	BULLETSTATE_DELETE,			//�����Ă���
	BULLETSTATE_SINGLE,			//1F�����̖�
	BULLETSTATE_THIRD,			//3F�����̖�
	BULLETSTATE_FIFTH,			//5F�����̖�
	BULLETSTATE_GRAVITY,		//�d��

}BULLETSTATE;
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	D3DXCOLOR col;
	BULLETSTATE state;	//�e�̏��
	int nCntState;	//�e�̏�ԗp STOP���̎��Ԃ��ۑ�
	int nLengthX;		//��X
	int nLengthY;		//��Y
	int nType;			//�摜�̎��
	BULLETTYPE nShot;			//�N����������
	int nAtk;			//�U����
	int nCntEnemy;		//�G�����ăi�C�t�U�肽����ł��I
	float steep;		//�X��
	float fCurve;		//�p�x�ω��p
	float fSpeed;		//�e�̃X�s�[�h
	bool bUse;			//�g�por�s�g�p
}Bullet;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 initpos;//�����ʒu
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posold;	//�ʒu
	D3DXVECTOR3 col;	//�F
	int nLengthX;		//X�̒���
	int nLengthY;		//Y�̒���
	int nCntAnim;		//Animation�̃J�E���g
	int nPtnAnim;		//�w�肳�ꂽ���W�ŕ\��
	int nPtnHeight;		//�摜�̏c�̕�����
	int nPtnWide;		//�摜�̉��̕�����
	int nPtnSpeed;		//Animation���x
	int nType;			//�摜�̎w��
	int nCntState;
	ANIMATION anim;		//�A�j���[�V�����̎g����
	ANIMTYPE type;	//���
	bool bUse;
}Animation;

//*********************************************************************************************************//
// �\���̒�`
//*********************************************************************************************************//
typedef enum
{//�X�R�A�̏��
	DIGITALSTATE_NONE = 0,
	DIGITALSTATE_WAVE,
	DIGITALSTATE_DAMAGE,		//�΂߉E���ɃX���C�h
	DIGITALSTATE_HEEL,			//�΂ߍ���ɃX���C�h
	DIGITALSTATE_WAVE0,

}DIGITALSTATE;
typedef struct
{//�X�R�A�̍\����
	D3DXVECTOR3 pos;			//�ꏊ
	D3DXVECTOR3 move;			//�����l
	D3DXCOLOR	col;			//�J���[
	int			nDigital;		// ����
	int			nLengthX;
	int			nLengthY;
	float		fHeight;
	DIGITALSTATE	state;		//���
	int		nCntstate;			//��ԊǗ��p
	bool		bUse;			//�g���Ă邩�g���ĂȂ���

}DIGITAL;

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@Game
//*********************************************************************************************************//
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void InitGame0(void);
GAME *GetGameState(void);
void SetGameState(GAMESTATE game, MODE mode, int nCntGameState);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�|���S��
//*********************************************************************************************************//
void InitPlayer(void);
void InitPlayer0(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SettingPlayer(void);
PLAYER *GetPlayer(void);
void HitPlayer(int nAtk, float fAngle, int nCntEnemy);
//bool HitAim(D3DXVECTOR3 aim, int nLength);

//*****************************************************************************
// �v���g�^�C�v�錾�@�e
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXCOLOR col, BULLETSTATE state, float steep, float fCurve, int nLengthX, int nLengthY, int nType, int nAtk, float fSpeed, BULLETTYPE nShot, int nCntEnemy);
void StartBullet(int nCntEnemy, int nCntAtk);
void BreakBullet(void);
void BreakBullet(int nCntEnemy);
bool HitAim(D3DXVECTOR3 MyPos, int nMyLengthX, int nMyLengthY, float fMyAngle, D3DXVECTOR3 aim, int nLength);
void BulletScroll(D3DXVECTOR3 move);
Bullet *GetBullet(void);

//*****************************************************************************
// �v���g�^�C�v�錾  window
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(bool bBG);
void SettingBlock(void);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float *fRide, bool bRide, PLAYERSTATE *state, int nLengthX, int nLengthY, int nCntEnemy, USETYPE type);
bool HitBullet(Bullet pBullet);
bool SafetynBlock(D3DXVECTOR3 *pPos, int nLengthX, int nLengthY);
void SetBlock(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, float fSteep, float fCurve, float fmoveSteep, float fSpeed, BLOCKSTATE state);
void BreakBlock(void);
void WideScroll(void);
void InitScroll(void);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
EFFECT *GetEffect(void);

//*****************************************************************************
// �v���g�^�C�v�錾�@���� �Ă�Animation�S��
//*****************************************************************************
void InitAnimation(void);
void UninitAnimation(void);
void UpdateAnimation(void);
void DrawAnimation(ANIMTYPE type);
void SetAnimation(D3DXVECTOR3 pos, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nCntState, ANIMATION anim, ANIMTYPE type);
void BreakAnimation(void);
void HitItem(int nCntItem);
void CollisionItem(void);
void AnimationScroll(D3DXVECTOR3 move);
Animation *GetAnimation(void);

//*****************************************************************************
// �v���g�^�C�v�錾�@Animation�S��
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nAtk, ANIMATION anim, EXPLOSIONSTATE state, USETYPE type, int nCntEnemy, float steep);
void ExplosionScroll(D3DXVECTOR3 move);
void BreakExplosion(void);

//*****************************************************************************
// �v���g�^�C�v�錾  window
//*****************************************************************************
void InitGameWindow(void);
void UninitGameWindow(void);
void UpdateGameWindow(void);
void DrawGameWindow(void);
void SetGameWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntState, WINDOWSTATE state, WINDOWUSE use);
void BreakGameWindow(void);
void BackGameWindow(int nNumber);
void ChangeGameWindow(int nNumber, WINDOWSTATE state);

//*****************************************************************************
// �v���g�^�C�v�錾  digital
//*****************************************************************************
DIGITAL *GetDigital(void);
void BreakDigital(void);
void DigitalScroll(D3DXVECTOR3 move);
void SetDigital(D3DXVECTOR3 pos, D3DXCOLOR col, DIGITALSTATE state, int nLengthX, int nLengthY, int nDigital);
void DrawDigital(void);
void UpdateDigital(void);
void UninitDigital(void);
void InitDigital(void);

#endif