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
#include "input.h"		//����
#include "fade.h"		//�t�F�[�h
#include "sound.h"		//�T�E���h
#include "menu.h"		//���j���[
#include "enter.h"		//�G���^�[

//*************************************************************************************************************************
// �}�N����`
//*******************************************************w******************************************************************
#define TITLE_TEXTURE_NAME		"data\\TEXTURE\\�Ő�.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME1		"data\\TEXTURE\\�_1.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLE_TEXTURE_NAME2		"data\\TEXTURE\\�^�C�g�����S.png"//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_TEX					(3)								//�e�N�X�`���̍ő吔
#define TITLE_POS_X				(0)								//�^�C�g���̍���X���W
#define TITLE_POS_Y				(0)								//�^�C�g���̍���Y���W
#define TITLE_WIDTH				(SCREEN_WIDTH)					//�^�C�g���̕�
#define TITLE_HEIGHT			(SCREEN_HEIGHT)					//�^�C�g���̍���
#define TITLE_SPEED0			(0.0003f)						//�w�i�X�s�[�h
#define TITLE_SPEED01			(0.0005f)						//�w�i�X�s�[�h
#define TITLE_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define TITLE_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^

Title g_Title;										//�^�C�g���̏��
int g_nCounterGameState1;
//=========================================================================================================================
// �^�C�g������������
//=========================================================================================================================
void InitTitle(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�|���S���̒��S�l
	g_Title.pos = D3DXVECTOR3((TITLE_POS_X + TITLE_WIDTH) / 2, (TITLE_POS_Y + TITLE_HEIGHT) / 2, 0.0f);
	//�|���S���ړ��l
	g_Title.move = D3DXVECTOR3(0.0f, TITLE_SPEED0, 0.0f);
	g_Title.nCounterAnim = 0;
	g_Title.nPatteunAnim = 0;
	g_nCounterGameState1 = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�P���ڂ̉摜
		pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTitle[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		TITLE_TEXTURE_NAME1,
		&g_pTextureTitle[1]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�R���ڂ̉摜
		pDevice,
		TITLE_TEXTURE_NAME2,
		&g_pTextureTitle[2]
	);


	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEX ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;	

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{//�S�e�N�X�`���̃J�E���g
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

		//���_���炵
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	InitEnter();
}

//=========================================================================================================================
// �^�C�g���I������
//=========================================================================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount] ->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	UninitEnter();
}

//=========================================================================================================================
// �^�C�g���X�V����
//=========================================================================================================================
void UpdateTitle(void)
{
	//�ʒu�̍X�V
	g_Title.pos.y += g_Title.move.y;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	FADE pFade = *GetFade();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffTitle->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�Q���ڂ̉摜�����X�N���[��
	pVtx += 4;

	//�e�N�X�`���ݒ� �c�X�N���[���p
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_Title.pos.y - 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_Title.pos.y - 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_Title.pos.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_Title.pos.y);

	////�e�N�X�`���ݒ� ���X�N���[���p
	//pVtx[0].tex = D3DXVECTOR2(g_Title.pos.x + 0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(g_Title.pos.x + 0.25f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(g_Title.pos.x + 0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(g_Title.pos.x + 0.25f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//�G���^�[�L�[�������ꂽ��
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFadeMode(MODE_SERECT);
		}
		else
		{
			g_nCounterGameState1++;

			if (g_nCounterGameState1 >= 1200)
			{
				// = GAMESTATE_NONE;
				//��ʁi���[�h�j�̐ݒ�
				SetFadeMode(MODE_RANKING);
				//�^�C�g���̋Ȃ��~�߂�
				StopSound(SOUND_LABEL_BGM005);
			}
		}
	}
	UpdateEnter();
}

//=========================================================================================================================
// �^�C�g���`�揈��
//=========================================================================================================================
void DrawTitle(void)
{

	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice= GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//�^�C�g���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	DrawEnter();
}