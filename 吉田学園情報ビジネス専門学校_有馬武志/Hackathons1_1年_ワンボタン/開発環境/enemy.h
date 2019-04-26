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
{// �G���
	ENEMYTYPE_NORMALENEMY = 0,	// �m�[�}��
	ENEMYTYPE_BOSSENEMY,		// ��{�X
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef enum
{// �G���
	ENEMYSTATE_APPEAR = 0,		// �o��
	ENEMYSTATE_NOMAL,			// �m�[�}��
	ENEMYSTATE_DAMAGE,			// �_���[�W
	ENEMYSTATE_DEATH,			// �f�X
	ENEMYSTATE_MAX
}ENEMYSTATE;

typedef struct
{// �G
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ��u
	D3DXCOLOR col;				// �F
	int nTexNum;				// ���
	int nSize;					// �傫��
	int nLife;					// ����
	int nAtk;
	int nDff;
	int nEXP;
	int nGold;
	int nScore;
	ENEMYTYPE Type;				// �G�̎��
	ENEMYSTATE State;			// �G�̏��
	int nCounterState;			// ��ԊǗ��J�E���^�[
	int nCounterAnim;			// �A�j���[�V�����J�E���^�[
	int nPatternAnim;			// �A�j���[�V�����p�^�[��No.
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Enemy;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitEnemy(void);			// �G����������
void UninitEnemy(void);			// �G�I������
void UpdateEnemy(void);			// �G�X�V����
void DrawEnemy(void);			// �G�`�揈��

void SetEnemy(D3DXVECTOR3 pos, int nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, ENEMYTYPE Type);
Enemy *GetEnemy(void);									// �G�̎擾
void HitEnemy(int nCntEnemy, int nDamage);				// �G�̒e�����菈��

#endif
