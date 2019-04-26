////=========================================================================================================================
////
//// �`���[�g���A���̏��� [tutorial.cpp]
//// Author :  �L�n�@���u
////
////=========================================================================================================================
//
////*************************************************************************************************************************
//// �C���N���[�h�t�@�C��
////*************************************************************************************************************************
//#include "main.h"
//#include "tutorial.h"
//#include "input.h"
//#include "fade.h"
//#include "sound.h"
//
////*************************************************************************************************************************
//// �}�N����`
////*************************************************************************************************************************
//#define TUTORIAL_TEXTURE_NAME		"data\\TEXTURE\\�`���[�g���A��.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
//#define TUTORIAL_POS_X				(0)								//�w�i�̍���X���W
//#define TUTORIAL_POS_Y				(0)								//�w�i�̍���Y���W
//#define TUTORIAL_WIDTH				(SCREEN_WIDTH)					//�w�i�̕�
//#define TUTORIAL_HEIGHT				(SCREEN_HEIGHT)					//�w�i�̍���
//#define TUTORIAL_MAX				(2)								//�w�i�̍���
//#define TUTORIAL_TEXTURE_SPEED		(5)								//�e�N�X�`���A�j���[�V�����X�s�[�h
//#define TUTORIAL_TEXTURE_PATTERN	(10)							//�e�N�X�`���A�j���[�V�����p�^�[����
//#define TUTORIAL_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
//#define TUTORIAL_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
//#define TUTORIAL_BACKTEXTURE_UV_U	(1.0f)							//�O�e�N�X�`���A�j���[�V����U�͈�
//#define TUTORIAL_BACKTEXTURE_UV_V	(1.0f)							//�O�e�N�X�`���A�j���[�V����V�͈�
//#define TUTORIAL_SPEED				(0.003f)						//�w�i�X�s�[�h
//
////*************************************************************************************************************************
//// �O���[�o���ϐ�
////*************************************************************************************************************************
//LPDIRECT3DTEXTURE9 g_pTextureTUTORIAL = NULL;			//�e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTUTORIAL = NULL;		//���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_posTUTORIAL;								//�w�i�̈ʒu
//D3DXVECTOR3 g_moveTUTORIAL;								//�w�i�̈ړ�
//
////=========================================================================================================================
//// �w�i����������
////=========================================================================================================================
//void InitTutorial(void)
//{
//	//�f�o�C�X�|�C���^
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	g_posTUTORIAL = D3DXVECTOR3((TUTORIAL_POS_X + TUTORIAL_WIDTH) / 2, (TUTORIAL_POS_Y + TUTORIAL_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l
//	g_moveTUTORIAL = D3DXVECTOR3(0.0f, TUTORIAL_SPEED, 0.0f);		//�|���S���ړ��l
//
//														//�e�N�X�`���̓ǂݍ���
//	D3DXCreateTextureFromFile
//	(
//		pDevice,
//		TUTORIAL_TEXTURE_NAME,
//		&g_pTextureTUTORIAL
//	);
//
//	//���_�o�b�t�@����
//	pDevice->CreateVertexBuffer
//	(
//		sizeof(VERTEX_2D) * 4,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffTUTORIAL,
//		NULL
//	);
//
//	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
//
//						//���_�o�b�t�@�����b�N
//	g_pVtxBuffTUTORIAL->Lock
//	(
//		0,
//		0,
//		(void**)&pVtx,
//		0
//	);
//
//	//���_�ݒ�
//	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);
//	//1.0f�ŌŒ�
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//	//���_�J���[�ݒ�
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	//�e�N�X�`���ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(TUTORIAL_TEXTURE_UV_U, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, TUTORIAL_TEXTURE_UV_V);
//	pVtx[3].tex = D3DXVECTOR2(TUTORIAL_TEXTURE_UV_U, TUTORIAL_TEXTURE_UV_V);
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffTUTORIAL->Unlock();
//}
//
////=========================================================================================================================
//// �w�i�I������
////=========================================================================================================================
//void UninitTutorial(void)
//{
//	//�e�N�X�`���[�̔j��
//	if (g_pTextureTUTORIAL != NULL)
//	{
//		g_pTextureTUTORIAL->Release();
//		g_pTextureTUTORIAL = NULL;
//	}
//	//���_�o�b�t�@�̔j��
//	if (g_pVtxBuffTUTORIAL != NULL)
//	{
//		g_pVtxBuffTUTORIAL->Release();
//		g_pVtxBuffTUTORIAL = NULL;
//	}
//}
//
////=========================================================================================================================
//// �w�i�X�V����
////=========================================================================================================================
//void UpdateTutorial(void)
//{
//	//�ݒ�L�[�iENTER�L�[�j�������ꂽ���ǂ���
//	if (GetKeyboardTrigger(DIK_RETURN) == true)
//	{
//		//���艹
//		PlaySound(SOUND_LABEL_SE_DECIDE);
//		//���[�h�ݒ�
//		SetFade(MODE_GAME);
//	}
//}
//
////=========================================================================================================================
//// �w�i�`�揈��
////=========================================================================================================================
//void DrawTutorial(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
//
//									//�f�o�C�X�̎擾
//	pDevice = GetDevice();
//
//	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
//	pDevice->SetStreamSource
//	(
//		0,
//		g_pVtxBuffTUTORIAL,
//		0,
//		sizeof(VERTEX_2D)
//	);
//
//	//���_�t�H�[�}�b�g
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//�e�N�X�`���ݒ�
//	pDevice->SetTexture(0, g_pTextureTUTORIAL);
//
//	//�w�i�̕`��
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//}
