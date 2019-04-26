//=========================================================================================================================
//
// �^�C�g���̏��� [TITLE.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "Title.h"		//�^�C�g��
#include "input.h"
#include "fade.h"
#include "sound.h"
//*************************************************************************************************************************
// �}�N����`
//*******************************************************w******************************************************************
#define TITLE_TEXTURE_NAME		"data\\TEXTURE\\�͂Ȃނ�.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME1		"data\\TEXTURE\\������1.png"    //�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_POS_X				(0)								//�^�C�g���̍���X���W
#define TITLE_POS_Y				(0)								//�^�C�g���̍���Y���W
#define TITLE_WIDTH				(SCREEN_WIDTH)					//�^�C�g���̕�
#define TITLE_HEIGHT			(SCREEN_HEIGHT)					//�^�C�g���̍���
#define TITLE_MAX				(2)								//�^�C�g���̍���
#define TITLE_TEXTURE_SPEED		(5)								//�e�N�X�`���A�j���[�V�����X�s�[�h
#define TITLE_TEXTURE_PATTERN	(10)							//�e�N�X�`���A�j���[�V�����p�^�[����
#define TITLE_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define TITLE_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define TITLE_BACKTEXTURE_UV_U	(1.0f)							//�O�e�N�X�`���A�j���[�V����U�͈�
#define TITLE_BACKTEXTURE_UV_V	(1.0f)							//�O�e�N�X�`���A�j���[�V����V�͈�
#define TITLE_SPEED				(0.003f)						//�^�C�g���X�s�[�h
#define MAX_TEXTURE				(2)

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTITLE[MAX_TEXTURE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTITLE;								//�^�C�g���̈ʒu
D3DXVECTOR3 g_moveTITLE;							//�^�C�g���̈ړ�

//=========================================================================================================================
// �^�C�g������������
//=========================================================================================================================
void InitTitle(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posTITLE = D3DXVECTOR3((TITLE_POS_X + TITLE_WIDTH) / 2, (TITLE_POS_Y + TITLE_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l
	g_moveTITLE = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);		//�|���S���ړ��l

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTITLE[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TITLE_TEXTURE_NAME1,
		&g_pTextureTITLE[1]
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * TITLE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTITLE->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V);

	pVtx += 4;

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTITLE->Unlock();
}

//=========================================================================================================================
// �^�C�g���I������
//=========================================================================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (g_pTextureTITLE[nCount] != NULL)
		{
			g_pTextureTITLE[nCount] -> Release();
			g_pTextureTITLE[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTITLE != NULL)
	{
		g_pVtxBuffTITLE->Release();
		g_pVtxBuffTITLE = NULL;
	}
}

//=========================================================================================================================
// �^�C�g���X�V����
//=========================================================================================================================
void UpdateTitle(void)
{
	//�ݒ�L�[�iENTER�L�[�j�������ꂽ���ǂ���
	g_posTITLE -= g_moveTITLE;	//�ʒu�̍X�V

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N
	g_pVtxBuffTITLE->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	pVtx += 4;

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_posTITLE.y - TITLE_BACKTEXTURE_UV_V);
	pVtx[1].tex = D3DXVECTOR2(TITLE_BACKTEXTURE_UV_U, g_posTITLE.y - TITLE_BACKTEXTURE_UV_V);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_posTITLE.y);
	pVtx[3].tex = D3DXVECTOR2(TITLE_BACKTEXTURE_UV_U, g_posTITLE.y);

	////�e�N�X�`���ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - 0.5f);
	//pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f - 0.5f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V - 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V - 0.5f);

	if (g_posTITLE.y + (SCREEN_HEIGHT / 2) >= SCREEN_HEIGHT)
	{//��ʊO�̃e�N�X�`������ɍX�V
		g_posTITLE.y = 0;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//���艹
		PlaySound(SOUND_LABEL_SE_DECIDE);
		//���[�h�ݒ�
		SetFade(MODE_PLAYTUTORIAL);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTITLE->Unlock();
}

//=========================================================================================================================
// �^�C�g���`�揈��
//=========================================================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTITLE,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureTITLE[nCount]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}