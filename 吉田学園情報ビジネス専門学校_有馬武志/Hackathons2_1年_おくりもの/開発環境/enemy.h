//=========================================================================================================================
// 
// �G���� [enemy.h]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "game.h"	// �Q�[��

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_ENEMY				(128)	// �G�̍ő吔

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{
	ENEMYTEXTYPE_ENEMY = 0,		//�G
	ENEMYTEXTYPE_TRAP,			//TRAP
	ENEMYTEXTYPE_MAX

}ENEMYTEXTYPE;
typedef enum
{
	ENEMYTEX_SLIME = 0,		//�X���C��
	ENEMYTEX_BAT,			//�R�E����
	ENEMYTEX_INSECT,		//��
	ENEMYTEX_WOLF,			//�T
	ENEMYTEX_GIANT,			//���l
	ENEMYTEX_MYSTERY,		//��̐���
	ENEMYTEX_W_UNICORN,		//�������j�R�[��
	ENEMYTEX_B_UNICORN,		//�������j�R�[��
	ENEMYTEX_R_DRAGON,		//�Ԃ��h���S��
	ENEMYTEX_B_DRAGON,		//���h���S��
	ENEMYTEX_WK_DRAGON,		//�����h���S��
	ENEMYTEX_BK_DRAGON,		//�����h���S��
	ENEMYTEX_BEAST,			//�}���e�B�R�A
	ENEMYTEX_DEATH,			//���_
	ENEMYTEX_LAST_DRAGON,	//���X�g�h���S��
	ENEMYTEX_BICSLIME,		//�r�b�N�X���C��
	ENEMYTEX_MAX

}ENEMYTEX;

typedef enum
{// �G���
	ENEMYTYPE_NORMALENEMY = 0,	// �m�[�}��
	ENEMYTYPE_BOSSENEMY,		// ��{�X
	ENEMYTYPE_TITLE,			//TITLE�ɖ߂�
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef enum
{// �G���
	ENEMYSTATE_APPEAR = 0,		// �o��
	ENEMYSTATE_NORMAL,			// �������Ă��Ȃ����
	ENEMYSTATE_DEATH,			// �f�X
	ENEMYSTATE_ATTACK,			//�U�����
	ENEMYSTATE_BOSS,			//�������Ȃ����
	ENEMYSTATE_HALFBACK,		// Life�����������ƈ�x�����m�b�N�o�b�N
	ENEMYSTATE_NOTBACK,			// KNOCKBACK���Ȃ� �ꎞ�I��
	ENEMYSTATE_NOTBACK0,		// KNOCKBACK���Ȃ�
	ENEMYSTATE_NOTBACK_S,		// KNOCKBACK���Ȃ��@�X���C���o��
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef enum
{// �G���
	ENEMYEFFECT_NORMAL = 0,		// �������Ă��Ȃ����
	ENEMYEFFECT_FIND,			//�������
	ENEMYEFFECT_JUMP,			//������ԁ@���n��fMove = 0;
	ENEMYEFFECT_FLY,			//���ł�����
	ENEMYEFFECT_ATTACK,			//�U�����
	ENEMYEFFECT_MAGIC,			//�U�����
	ENEMYEFFECT_KNOCKBACK,		// �m�b�N�o�b�N���
	ENEMYEFFECT_MAX
}ENEMYEFFECT;

typedef struct
{// �G
	D3DXVECTOR3 respawn;		// �����ʒu
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 posold;			// �O�̈ʒu
	D3DXVECTOR3 move;			// �ړ��u
	D3DXCOLOR col;				// �F
	ENEMYTEX nTexNum;				// ���
	ENEMYTEXTYPE nTexType;				//�g���b�v���G��
	int nAngle;					// ����
	int nSize;					// �傫��
	int nLife;					// ����
	int nMaxLife;				//�ő�HP
	int nAtk;					// �U����
	int nDff;					// �h���
	int nEXP;					// �X�L���̃��x���グ�̂���
	int nGold;					// �̗͉񕜂�X�L�����̍w��
	int nScore;					// �Q�[����Score
	int nCollisionX;			//�����蔻��X
	int nCollisionY;			//�����蔻��Y
	int nHit;					//�U���ɂ�邠���蔻��(��)
	float fSteep;				// �|���S���̊p�x	
	float fplusSteep;
	float fGravity;				//�d�́@��s���j�b�g�p
	float fMove;
	ENEMYTYPE type;				// �G�̎��
	ENEMYSTATE state;			// �G�̏��
	ENEMYEFFECT effect;			// ����
	int nCounterState;			// ��ԊǗ��J�E���^�[
	int nCountereffect;			// ���ʊǗ��p
	int nCountAttack;			// �U���p��Counter
	int nCounterDamage;			//Damage��̃J�E���g
	int nCounterAnim;			// �A�j���[�V�����J�E���^�[
	int nPatternAnim;			// �A�j���[�V�����p�^�[��No.
	bool bUse;					// �g�p���Ă��邩�ǂ���
	int nResCount;				//���X�|�[���܂ł̃J�E���g
	bool bRespawn;				//�����ł��邩�ǂ���
}Enemy;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitEnemy(void);			// �G����������
void UninitEnemy(void);			// �G�I������
void UpdateEnemy(void);			// �G�X�V����
void DrawEnemy(void);			// �G�`�揈��
void EnemyScroll(D3DXVECTOR3 move);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTEXTYPE nTexType, ENEMYTEX nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, float steep, ENEMYTYPE Type);
void SlimeUpdate(int nCntEnemy);
void BatUpdate(int nCntEnemy);
void GiantUpdate(int nCntEnemy);
void MysteryUpdate(int nCntEnemy);
void WolfUpdate(int nCntEnemy);
void DragonUpdate(int nCntEnemy);
void DeathUpdate(int nCntEnemy);
Enemy *GetEnemy(void);						// �G�̎擾
void CleanEnemy(void);
void HitEnemy(int nCntEnemy, int nAtk, float fAngle, USETYPE type);// �G�ւ̃_���[�W����

#endif
