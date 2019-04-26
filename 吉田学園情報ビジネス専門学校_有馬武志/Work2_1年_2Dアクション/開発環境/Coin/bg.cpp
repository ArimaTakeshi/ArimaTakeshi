//=========================================================================================================================
//
// �w�i�̏��� [bg.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"	
#include "bg.h"		//�w�i
#include "player.h"	//�v���C���[

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define BG_TEXTURE_NAME		"data\\TEXTURE\\sky000.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BG_TEXTURE_NAME1	"data\\TEXTURE\\mountain000.png"//�ǂݍ��ރe�N�X�`���t�@�C��
#define BG_POS_X			(0)								//�w�i�̍���X���W
#define BG_POS_Y			(0)								//�w�i�̍���Y���W
#define BG_WIDTH			(SCREEN_WIDTH)					//�w�i�̕�
#define BG_HEIGHT			(SCREEN_HEIGHT)					//�w�i�̍���
#define BG_TEXTURE_UV_U		(0.3f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define BG_BACKTEXTURE_UV_U	(1.0f)							//�O�e�N�X�`���A�j���[�V����U�͈�
#define BG_BACKTEXTURE_UV_V	(1.0f)							//�O�e�N�X�`���A�j���[�V����V�͈�
#define BG_SPEED0			(0.00005f)						//�w�i�X�s�[�h
#define BG_SPEED1			(0.00003f)						//�w�i�X�s�[�h
#define MAX_TEXTURE			(2)								//�e�N�X�`������

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG[MAX_TEXTURE] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Bg g_Bg;													//�w�i�̏��

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitBG(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S���̒��S�l
	g_Bg.pos = D3DXVECTOR3((BG_POS_X + BG_WIDTH) / 2, (BG_POS_Y + BG_HEIGHT) / 2, 0.0f);

	//�|���S���ړ��l
	g_Bg.move = D3DXVECTOR3(BG_SPEED0, BG_SPEED0, 0.0f);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//1���ڂ̉摜
		pDevice,
		BG_TEXTURE_NAME,
		&g_pTextureBG[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//2���ڂ̉摜
		pDevice,
		BG_TEXTURE_NAME1,
		&g_pTextureBG[1]
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBG->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

	//���_���炵
	pVtx += 4;
	
	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 550, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280, 550, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280, 720, 0.0f);
	//1.0�ŌŒ�
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
	pVtx[1].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitBG(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureBG[nCount] != NULL)
		{
			g_pTextureBG[nCount] -> Release();
			g_pTextureBG[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdateBG(void)
{
	//�ʒu�̍X�V
	g_Bg.pos += g_Bg.move;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;		

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBG->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	////�e�N�X�`���ݒ� �c�X�N���[���p
	//pVtx[0].tex = D3DXVECTOR2(0.0f, g_posBG.y - BG_BACKTEXTURE_UV_V);
	//pVtx[1].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, g_posBG.y - BG_BACKTEXTURE_UV_V);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, g_posBG.y);
	//pVtx[3].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, g_posBG.y);

	//�e�N�X�`���ݒ� ���X�N���[���p
	pVtx[0].tex = D3DXVECTOR2(g_Bg.pos.x + 0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_Bg.pos.x + 0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_Bg.pos.x + 0.0f , 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_Bg.pos.x + 0.25f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBG->Unlock();
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffBG,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTextureBG[nCount]);

		//�w�i�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}