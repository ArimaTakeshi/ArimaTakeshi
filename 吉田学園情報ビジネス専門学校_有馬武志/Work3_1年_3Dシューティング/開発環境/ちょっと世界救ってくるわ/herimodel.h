//=============================================================================
//
// ���f������ [herimodel.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _HERIMODEL_H_
#define _HERIMODEL_H_

#include "main.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
#define MAX_HERITEXT_NAME			(255)							//�t�@�C�����̖��O�̍ő吔
#define HERIFILE_NAME				"data\\TEXT\\herimodel.txt"		//�ǂݍ���txt�t�@�C���̖��O
#define MAX_HERIPARTS				(2)								//�p�[�c��
#define HERIMODEL_SPEED				(1.0f)							//�v���C���[�X�s�[�h
#define MAX_HERIANIM				(12)							//�A�j���[�V������
#define MAX_HERIKEY					(10)							//�L�[�t���[����

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	HERIANIM_NEUTRAL = 0,
	HERIANIM_WALK,
	HERIANIM_ATTACK
}Player2Anim;

typedef struct
{
	char			FileName[MAX_HERITEXT_NAME];						//X�t�@�C����
	LPD3DXMESH		pMeshHeri = NULL;								//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatHeri = NULL;							//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatHeri = 0;								//�}�e���A���̏��
	D3DXMATRIX		mtxWorldHeri;									//���[���h�}�g���b�N�X
	D3DXVECTOR3		posHeri;										//�ʒu
	D3DXVECTOR3		InitHeriPos;										//�����ʒu
	D3DXVECTOR3		posHeriAnim[MAX_HERIANIM][MAX_HERIKEY];			//�A�j���[�V����pos
	D3DXVECTOR3		rotHeri;										//����
	D3DXVECTOR3		InitHeriRot;										//��������
	D3DXVECTOR3		rotAnim[MAX_HERIANIM][MAX_HERIKEY];			//�A�j���[�V����rot
	int				nIdxHeriParent = 0;							//�e���f���̃C���f�b�N�X�@-1���e
}Heri;

typedef struct
{
		
	D3DXMATRIX		mtxWorldPlayer2;								//���[���h�}�g���b�N�X
	LPD3DXMESH		pMeshPlayer2 = NULL;							//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	pBuffMatPlayer2 = NULL;							//�}�e���A���̏��ւ̃|�C���^
	DWORD			nNumMatPlayer2 = 0;								//�}�e���A���̏��
	D3DXVECTOR3		posOld;											//�ߋ��̈ʒu
	D3DXVECTOR3		pos;											//�ʒu
	D3DXVECTOR3		move;											//�ړ�
	D3DXVECTOR3		rot;											//����
	int				nMaxPartsNum;									//�p�[�c�̍ő吔
	Heri			aModel[MAX_HERIPARTS];							//[�Z]�����ɂ̓p�[�c��������
	int				nMaxAnimNum;									//�A�j���[�V�����̍ő吔
	int				nAnimloop[MAX_HERIANIM];						//���[�v
	int				nAnimKey[MAX_HERIANIM];							//�L�[��
	int				nAnimfram[MAX_HERIANIM][MAX_HERIKEY];			//�t���[����
	Player2Anim		nAnimnuw;										//���݂̃A�j���[�V����
	int				nAnimKeynuw;									//���݂̃L�[
	bool			bAttack;										//�g�p���Ă��邩�ǂ���
	bool			bUse;											//�g�p���Ă��邩�ǂ���
}Player2;
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer2(void);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
Player2 *GetPlayer2(void);

#endif
