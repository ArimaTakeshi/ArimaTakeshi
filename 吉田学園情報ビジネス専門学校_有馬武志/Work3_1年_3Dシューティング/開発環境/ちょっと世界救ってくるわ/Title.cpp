//=========================================================================================================================
//
// �^�C�g���̏��� [TITLE.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "Title.h"		//�^�C�g��
#include "input.h"		//����
#include "fade.h"		//�t�F�[�h
#include "camera.h"		//�J����
#include "light.h"		//���C�g
#include "meshbg.h"		//���b�V���V�����_�[
#include "meshfield.h"	//���b�V���t�B�[���h
#include "sound.h"		//�T�E���h
#include "billboord.h"	//�r���{�[�h
#include "wall.h"		//�E�H�[��
#include "effect.h"		//�G�t�F�N�g
#include "object.h"		//�I�u�W�F�N�g
#include "enter.h"		//�G���^�[
#include "frame.h"		//�e�N�X�`��

//*************************************************************************************************************************
// �}�N����`
//**************************************************************************************************************************
#define TITLE_TEXTURE_NAME		"data\\TEXTURE\\�^�C�g�����S02.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_TEX					(1)									//�e�N�X�`���̍ő吔
#define	TITLE_SIZE_X			(500)
#define	TITLE_SIZE_Y			(400)

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Title g_Title;										//�^�C�g���̏��
int g_nCounterGameState1;
int g_nCountTimer;
int g_nCntFadeTimer;

//=========================================================================================================================
// �^�C�g������������
//=========================================================================================================================
void InitTitle(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�|���S���̒��S�l
	g_Title.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 20, 430, 0.0f);
	//�|���S���ړ��l
	g_Title.move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
	g_Title.nCounterAnim = 0;
	g_Title.nPatteunAnim = 0;
	g_nCounterGameState1 = 0;
	g_nCountTimer = 0;
	g_nCntFadeTimer = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//1���ڂ̉摜
		pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTitle[0]
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
			pVtx[0].pos = D3DXVECTOR3(g_Title.pos.x - TITLE_SIZE_X, g_Title.pos.y - TITLE_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Title.pos.x + TITLE_SIZE_X, g_Title.pos.y - TITLE_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Title.pos.x - TITLE_SIZE_X, g_Title.pos.y + TITLE_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Title.pos.x + TITLE_SIZE_X, g_Title.pos.y + TITLE_SIZE_Y, 0.0f);

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

		//���_���炵
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�J�����̏���������
	InitCamera();

	//�J�����̏���������
	InitLight();

	//�̏���������
	InitMeshBg();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//�r���{�[�h�̏���������
	InitBillBoord();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�I�u�W�F�N�g�̏���������
	InitObject();

	//�G���^�[�̏���������
	InitEnter();

	//�t���[���̏���������
	InitFrame();

	SetObject(D3DXVECTOR3(40, 0, -95), D3DXVECTOR3(0, 0, 0));

	if (g_nCountTimer >= 0 && g_nCountTimer <= 299)
	{
		//��̃G�t�F�N�g
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_SNOW, 2.0f, 20, 0);
	}
	if (g_nCountTimer >= 300 && g_nCountTimer <= 599)
	{
		//�J�̃G�t�F�N�g
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-250.0f + rand() % (2 * 250), 50.0f, -250.0f + rand() % (2 * 250)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
	}
	if (g_nCountTimer == 600)
	{
		g_nCountTimer = 0;
	}
	g_nCountTimer++;

	//�r���{�[�h�I�u�W�F�N�g
	//SetBillBoord(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), 0);//���S
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

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�V�����_�[�̏I������
	UninitMeshBg();

	//�t�B�[���h�̏I������
	UninitMeshField();

	//�r���{�[�h�̏I������
	UninitBillBoord();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�t���[���̏I������
	UninitFrame();

	//�I�u�W�F�N�g�̏���������
	//UninitObject();

	//�G���^�[�̏���������
	UninitEnter();
}

//=========================================================================================================================
// �^�C�g���X�V����
//=========================================================================================================================
void UpdateTitle(void)
{
	//�t�F�[�h�̃|�C���^
	FADE pFade = *GetFade();

	g_nCntFadeTimer++;

	//�^�C�g���̓�����ǉ�
	g_Title.pos.y += g_Title.move.y;

	//�^�C�g�������Ȃ��I
	if (g_Title.pos.y >= 200)
	{
		g_Title.move.y = 0;
	}

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetMouseTrigger(0) == true)
		{//�G���^�[�L�[�������ꂽ��
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_TUTORIAL);
		}
		else if ((g_nCntFadeTimer % 1000) == 0)
		{//�P�O�b��Ƀ����L���O�֍s��
			SetFade(MODE_RANKING);
		}
	}

	//���C�g�̍X�V����
	UpdateLight();

	//�J�����̍X�V����
	UpdateCamera();

	//�V�����_�[�̍X�V����
	UpdateMeshBg();

	//�t�B�[���h�̍X�V����
	UpdateMeshField();

	//�r���{�[�h�̍X�V����
	UpdateBillBoord();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�t���[���̍X�V����
	UpdateFrame();

	//�I�u�W�F�N�g�̏���������
	UpdateObject();

	//�G���^�[�̏���������
	UpdateEnter();

}

//=========================================================================================================================
// �^�C�g���`�揈��
//=========================================================================================================================
void DrawTitle(void)
{
	//�J�����̕`�揈��
	SetCamera(CAMERA_TYPE_DEMO);

	//�t�B�[���h�̕`�揈��
	DrawMeshField();

	//�I�u�W�F�N�g�̏���������
	DrawObject();

	//�r���{�[�h�̕`�揈��
	DrawBillBoord();

	//�V�����_�[�̕`�揈��
	DrawMeshBg();

	//�G�t�F�N�g�̂̕`�揈��
	DrawEffect();

	//�G���^�[�̏���������
	DrawEnter();

	//�t���[���̕`�揈��
	DrawFrame();

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

}