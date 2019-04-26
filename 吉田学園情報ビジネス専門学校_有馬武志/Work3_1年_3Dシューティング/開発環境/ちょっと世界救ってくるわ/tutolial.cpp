//=========================================================================================================================
//
// �^�C�g���̏��� [tutolial.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "tutolial.h"		//�`���[�g���A��
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "enter.h"

//*************************************************************************************************************************
// �}�N����`
//*******************************************************w******************************************************************
#define TUTOLIAL_TEXTURE_NAME		"data\\TEXTURE\\Tutorial2.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TUTOLIAL_TEXTURE_NAME1		"data\\TEXTURE\\Tutorial2.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TUTOLIAL_POS_X				(0)								//�^�C�g���̍���X���W
#define TUTOLIAL_POS_Y				(0)								//�^�C�g���̍���Y���W
#define TUTOLIAL_WIDTH				(SCREEN_WIDTH)					//�^�C�g���̕�
#define TUTOLIAL_HEIGHT				(SCREEN_HEIGHT)					//�^�C�g���̍���
#define TUTOLIAL_SPEED				(0.003f)						//�^�C�g���X�s�[�h
#define MAX_TEXTURE					(1)

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTUTOLIAL[MAX_TEXTURE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTUTOLIAL = NULL;					//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTUTOLIAL;											//�^�C�g���̈ʒu
D3DXVECTOR3 g_moveTUTOLIAL;											//�^�C�g���̈ړ�
int g_nCntTutorial = 0;

//=========================================================================================================================
// �^�C�g������������
//=========================================================================================================================
void InitTutolial(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posTUTOLIAL = D3DXVECTOR3((TUTOLIAL_POS_X + TUTOLIAL_WIDTH) / 2, (TUTOLIAL_POS_Y + TUTOLIAL_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TUTOLIAL_TEXTURE_NAME,
		&g_pTextureTUTOLIAL[0]
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTUTOLIAL,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTUTOLIAL->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
			//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(TUTOLIAL_POS_X, TUTOLIAL_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TUTOLIAL_WIDTH, TUTOLIAL_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TUTOLIAL_POS_X, TUTOLIAL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TUTOLIAL_WIDTH, TUTOLIAL_HEIGHT, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTUTOLIAL->Unlock();

	//�G���^�[
	InitEnter();
}

//=========================================================================================================================
// �^�C�g���I������
//=========================================================================================================================
void UninitTutolial(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (g_pTextureTUTOLIAL[nCount] != NULL)
		{
			g_pTextureTUTOLIAL[nCount] -> Release();
			g_pTextureTUTOLIAL[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTUTOLIAL != NULL)
	{
		g_pVtxBuffTUTOLIAL->Release();
		g_pVtxBuffTUTOLIAL = NULL;
	}
	//�G���^�[
	UninitEnter();
}

//=========================================================================================================================
// �^�C�g���X�V����
//=========================================================================================================================
void UpdateTutolial(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetMouseTrigger(0) == true)
	{
		//���艹
		PlaySound(SOUND_LABEL_SE_DECIDE);
		//���[�h�ݒ�
		SetFade(MODE_GAME);
	}

	//�G���^�[
	UpdateEnter();
}

//=========================================================================================================================
// �^�C�g���`�揈��
//=========================================================================================================================
void DrawTutolial(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTUTOLIAL,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureTUTOLIAL[nCount]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	//�G���^�[
	DrawEnter();
}