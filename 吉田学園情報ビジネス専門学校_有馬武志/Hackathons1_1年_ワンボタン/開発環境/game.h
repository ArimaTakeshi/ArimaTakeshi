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
#define PLAYER_POSX			(SCREEN_GAMEX / 2 - 22)					//�摜��X
#define PLAYER_POSY			(SCREEN_HEIGHT / 4 * 3)					//�摜��Y
#define PLAYER_POSX2			(SCREEN_GAMEX / 2 + 22)					//�摜��X2
#define PLAYER_POSY2			(SCREEN_HEIGHT / 4 * 3 + 44)			//�摜��Y2
#define PLAYER_POSX3			(80)	//�摜��X�̕� / 2
#define PLAYER_POSY3			(80)	//�摜��Y�̕� / 2
#define POSPLAYERX				((PLAYER_POSX + PLAYER_POSX2) / 2)	//X�̒��S
#define POSPLAYERY				((PLAYER_POSY + PLAYER_POSY2) / 2)	//Y�̒��S

#define BULLET_ATKTYPE0			(0)										//�ʏ�e
#define BULLET_ATKTYPE1			(1)										//����
#define BULLET_ATKTYPE50		(50)									//����
#define BULLET_ATKTYPE99		(99)									//�i�C�t�I
#define KNIFE_TIME				(BULLET_ATKTYPE99 + 6)					//�i�C�t�̗L������

#define HALF_EXPLOSION			(30)									//�����̕�����
#define GUARD_BREAK				(481)			//GUARD�����܂ł̎���

#define MAX_SCORE		(5 * 4)		//5��*��Փx��
#define RANK_SCORE		(5)			//�����L���O�Ɏg���Ă���X�R�A

#define	MAX_BULLET			(3840)				// �e�̍ő吔
#define BULLET_SLIP			(0.15f)				//�e�̊���
#define BULLET_DELETE		(200)

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

typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

typedef struct
{
	GAMESTATE now;		//���݂̏��
	MODE CHANGE;		//�ς��郂�[�h
	int nCntGameState;	//�J�E���g�p

}GAME;

typedef struct
{
	D3DXVECTOR3 pos;	//�|���S���̈ʒu
	D3DXVECTOR3 move;	//�|���S���̈ړ���
	int nCntAnim;		//�J�E���g�p
	int nPtnAnim;		//�p�^�[����
	int nLevel;			//Level
	int nHP;			//HP
	int nMAX_HP;
	int nAttack;		//�U��
	int nDefense;		//�h��
	int nJump;			//Jump
	int nMeter;			//�i�񂾋���
	int nMAX_EXP;		//���̃��x���܂ł̌o���l
	int nEXP;			//�擾�����o���l
	int nGold;			//����
	int nScore;
	float fAngle;		//�p�x
	bool bMove;			//�w�i�𓮂������ǂ���
	bool bUse;			//���� or ���S

}PLAYER;

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

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@Game
//*********************************************************************************************************//
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
GAME *GetGameState(void);
void SetGameState(GAMESTATE game, MODE mode, int nCntGameState);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�|���S��
//*********************************************************************************************************//
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
bool HitAim(D3DXVECTOR3 aim, int nLength);
void EnemyAppears(void);
void HitPlayer(int nAtk);

//*****************************************************************************
// �v���g�^�C�v�錾  window
//*****************************************************************************
void InitGameWindow(void);
void UninitGameWindow(void);
void UpdateGameWindow(void);
void DrawGameWindow(void);
void SetGameWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, WINDOWSTATE state, WINDOWUSE use);
void BreakGameWindow(void);
void BackGameWindow(int nNumber);
void ChangeGameWindow(int nNumber, WINDOWSTATE state);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
EFFECT *GetEffect(void);

#endif