//=========================================================================================================================
//
// �A�C�e������ [item.h]
// Author :  �L�n�@���u
//
//=========================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{//�A�C�e��
	ITEM_COIN = 0,			//�R�C��
	ITEM_MAGNET,			//����
	ITEM_MAX				//�ő吔
} ITEMTYPE;

typedef enum
{//�A�C�e��
	ITEM_STATE_APPER = 0,
	ITEM_STATE_NORMAL,
	ITEM_STATE_DELETE,
	ITEM_STATE_MAX
}ITEMSTATE;

typedef struct
{//�A�C�e��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	float fHeight;			//����
	float fWidth;			//��
	float fAngle;			//�p�x
	float fLength;			//����
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatteunAnim;		//�A�j���[�V�����p�^�[��No.
	ITEMTYPE ItemType;		//�A�C�e���̎��
	ITEMSTATE ItemState;	//�A�C�e��
	int	nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Item;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitItem(void);									//�A�C�e������������
void UninitItem(void);									//�A�C�e���I������
void UpdateItem(void);									//�A�C�e���X�V����
void DrawItem(void);									//�A�C�e���`�揈��
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col ,int nType);//�A�C�e���̐ݒ菈��
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWidth, float *fHeight);
void DeleteItem(int nCntItem);							//�A�C�e��������
void DeleteItem(void);
#endif
