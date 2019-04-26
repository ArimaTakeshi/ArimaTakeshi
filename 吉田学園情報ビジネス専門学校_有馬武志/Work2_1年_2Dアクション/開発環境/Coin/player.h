//=============================================================================
//
// �v���C���[�̏��� [player.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//****************************************************************************
// �\����
//****************************************************************************
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		//�ʏ���
	PLAYERSTATE_DAMAGE,			//�_���[�W���
	PLAYERSTATE_DEAHT,			//���S���	
	PLAYERSTATE_MAX
}PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;			//�ʒu		
	D3DXVECTOR3 posOld;			//�O��̈ʒu
	D3DXVECTOR3 move;			//�ړ��l
	D3DXCOLOR	col;			//�F
	PLAYERSTATE state;			//�v���C���[�̏��
	float PlayerHeight;			//�v���C���[�̐g��
	float PlayerWidth;			//�v���C���[�̉���
	bool		bJump;			//�W�����v
	int			nLife;			//�̗�
	int			TexT;			//�e�N�X�`���̃^�e�ړ�
	int nCounterAnim;			//�A�j���[�V�����J�E���^�[
	int nPatternAnim;			//�A�j���[�V�����p�^�[��No.
	int nCounterState;			//��ԊǗ��̃J�E���^�[
	bool bUse;					//�g�p���Ă��邩�ǂ���
	bool bDisp;					//�\�����邩���Ȃ���
	//Block *pBlock;			//�Ώۂ̃u���b�N�ւ̃|�C���^
}Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);			//�v���C���[�̏���������	
void UninitPlayer(void);		//�v���C���[�̏I������
void UpdatePlayer(void);		//�v���C���[�̍X�V����
void DrawPlayer(void);			//�v���C���[�̕`�揈��
void HitPlayer(int nDamage);
Player *GetPlayer(void);
void DeletePlayer(void);																	//
#endif