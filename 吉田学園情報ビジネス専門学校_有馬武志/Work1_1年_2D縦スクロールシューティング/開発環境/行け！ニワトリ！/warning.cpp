	//=========================================================================================================================
//
// ���[�j���O�̏��� [warning.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "warning.h"		//���[�j���O
#include "sound.h"			//�T�E���h

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define WARNING_TEXTURE_NAME	 "data\\TEXTURE\\�{�X�O.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define WARNING_POS_X			 (0)							//���[�j���O�̍���X���W
#define WARNING_POS_Y			 (0)							//���[�j���O�̍���Y���W
#define WARNING_WIDTH			 (SCREEN_WIDTH)					//���[�j���O�̕�
#define WARNING_HEIGHT			 (SCREEN_HEIGHT)				//���[�j���O�̍���
#define WARNING_MAX				 (2)							//���[�j���O�̍���
#define WARNING_TEXTURE_SPEED	 (5)							//�e�N�X�`���A�j���[�V�����X�s�[�h
#define WARNING_TEXTURE_PATTERN	 (10)							//�e�N�X�`���A�j���[�V�����p�^�[����
#define WARNING_TEXTURE_UV_U	 (1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define WARNING_TEXTURE_UV_V	 (1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define WARNING_BACKTEXTURE_UV_U (1.0f)							//�O�e�N�X�`���A�j���[�V����U�͈�
#define WARNING_BACKTEXTURE_UV_V (1.0f)							//�O�e�N�X�`���A�j���[�V����V�͈�
#define WARNING_SPEED			 (0.003f)						//���[�j���O�X�s�[�h

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureWARNING = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWARNING = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posWARNING;								//���[�j���O�̈ʒu
D3DXVECTOR3 g_moveWARNING;								//���[�j���O�̈ړ�
bool g_bUse;											//���[�j���O���g�p���Ă邩�g�p���ĂȂ���
int g_nCount;											//

//=========================================================================================================================
// ���[�j���O����������
//=========================================================================================================================
void InitWarning(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nCount = 0;
	g_bUse = false;

	g_posWARNING = D3DXVECTOR3((WARNING_POS_X +WARNING_WIDTH) / 2, (WARNING_POS_Y +WARNING_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l
	g_moveWARNING = D3DXVECTOR3(WARNING_SPEED, 0.0f, 0.0f);		//�|���S���ړ��l

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		WARNING_TEXTURE_NAME,
		&g_pTextureWARNING
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWARNING,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffWARNING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(WARNING_POS_X,WARNING_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(WARNING_WIDTH,WARNING_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(WARNING_POS_X,WARNING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(WARNING_WIDTH,WARNING_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(WARNING_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,WARNING_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(WARNING_TEXTURE_UV_U,WARNING_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWARNING->Unlock();
}

//=========================================================================================================================
// ���[�j���O�I������
//=========================================================================================================================
void UninitWarning(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureWARNING != NULL)
	{
		g_pTextureWARNING->Release();
		g_pTextureWARNING = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWARNING != NULL)
	{
		g_pVtxBuffWARNING->Release();
		g_pVtxBuffWARNING = NULL;
	}
}

//=========================================================================================================================
// ���[�j���O�X�V����
//=========================================================================================================================
void UpdateWarning(void)
{
	g_posWARNING += g_moveWARNING;	//�ʒu�̍X�V

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWARNING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	g_nCount++;

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_posWARNING.x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_posWARNING.x + WARNING_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_posWARNING.x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_posWARNING.x + WARNING_TEXTURE_UV_U, 1.0f);

	if (g_posWARNING.x + (SCREEN_WIDTH / 2) <= 0)
	{//��ʊO�̃e�N�X�`������ɍX�V
		g_posWARNING.x = SCREEN_WIDTH;
	}

	if (g_nCount % 350 == 0)
	{
		g_bUse = false;

		StopSound(SOUND_LABEL_SE_SHOT);
	}


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWARNING->Unlock();
}

//=========================================================================================================================
// ���[�j���O�`�揈��
//=========================================================================================================================
void DrawWarning(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffWARNING,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureWARNING);

	if (g_bUse == true)
	{
		//���[�j���O�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}
//=========================================================================================================================
// ���[�j���O
//=========================================================================================================================
void SetWarning(void)
{
	g_bUse = true;

	PlaySound(SOUND_LABEL_SE_SHOT);
}