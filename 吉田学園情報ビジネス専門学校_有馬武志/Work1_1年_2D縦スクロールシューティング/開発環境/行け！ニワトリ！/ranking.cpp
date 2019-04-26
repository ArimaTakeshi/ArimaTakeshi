//=========================================================================================================================
//
// �����L���O�̏��� [ranking.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define RANKING_TEXTURE_NAME		"data\\TEXTURE\\�����L���O.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define RANKING_POS_X				(0)								//�w�i�̍���X���W
#define RANKING_POS_Y				(0)								//�w�i�̍���Y���W
#define RANKING_WIDTH				(SCREEN_WIDTH)					//�w�i�̕�
#define RANKING_HEIGHT				(SCREEN_HEIGHT)					//�w�i�̍���
#define RANKING_MAX					(2)								//�w�i�̍���
#define RANKING_TEXTURE_SPEED		(5)								//�e�N�X�`���A�j���[�V�����X�s�[�h
#define RANKING_TEXTURE_PATTERN	(10)							//�e�N�X�`���A�j���[�V�����p�^�[����
#define RANKING_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define RANKING_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define RANKING_BACKTEXTURE_UV_U	(1.0f)							//�O�e�N�X�`���A�j���[�V����U�͈�
#define RANKING_BACKTEXTURE_UV_V	(1.0f)							//�O�e�N�X�`���A�j���[�V����V�͈�
#define RANKING_SPEED				(0.003f)						//�w�i�X�s�[�h

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRANKING = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRANKING = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRANKING;								//�w�i�̈ʒu
D3DXVECTOR3 g_moveRANKING;								//�w�i�̈ړ�

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitRanking(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posRANKING = D3DXVECTOR3((RANKING_POS_X + RANKING_WIDTH) / 2, (RANKING_POS_Y + RANKING_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l
	g_moveRANKING = D3DXVECTOR3(0.0f, RANKING_SPEED, 0.0f);		//�|���S���ړ��l

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		RANKING_TEXTURE_NAME,
		&g_pTextureRANKING
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRANKING,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffRANKING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(RANKING_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RANKING_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(RANKING_TEXTURE_UV_U, RANKING_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRANKING->Unlock();
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitRanking(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureRANKING != NULL)
	{
		g_pTextureRANKING->Release();
		g_pTextureRANKING = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRANKING != NULL)
	{
		g_pVtxBuffRANKING->Release();
		g_pVtxBuffRANKING = NULL;
	}
}

//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdateRanking(void)
{
	static int nCount = 0;

	nCount++;
	//�ݒ�L�[�iENTER�L�[�j�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true || (nCount % 250) == 0)
	{
		//���艹
		PlaySound(SOUND_LABEL_SE_DECIDE);
		//���[�h�ݒ�
		SetFade(MODE_TITLE);
	}
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffRANKING,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureRANKING);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
