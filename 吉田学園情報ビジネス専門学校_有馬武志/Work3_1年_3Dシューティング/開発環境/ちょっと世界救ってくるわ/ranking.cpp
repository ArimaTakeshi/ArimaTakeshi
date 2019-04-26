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
#include "ranking.h"	//�����L���O
#include "input.h"		//�L�[�{�[�h
#include "fade.h"		//�t�B�[���h
#include "sound.h"		//�T�E���h
#include "score.h"		//�X�R�A
#include "meshbg.h"		//���b�V���V�����_�[
#include "meshfield.h"	//���b�V���t�B�[���h
#include "camera.h"		//�J����
#include "light.h"		//���C�g
#include "wall.h"		//��
#include "object.h"		//�I�u�W�F�N�g
#include "enter.h"		//�G���^�[
#include "herimodel.h"	//�w��

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define RANKING_TEXTURE_NAME		"data\\TEXTURE\\����.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define RANKING_SIZE_X				(60)							//�w�i�̍���X���W
#define RANKING_SIZE_Y				(305)							//�w�i�̍���Y���W
#define RANKING_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define RANKING_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRANKING = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRANKING = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRanking;								//�w�i�̈ʒu

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitRanking(void)
{
	//�w���R�v�^�[
	Player2 pPlayer2 = *GetPlayer2();

	PlaySound(SOUND_LABEL_SE_HERI);

	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//�����l
	g_posRanking = D3DXVECTOR3(SCREEN_WIDTH / 2 + 220,SCREEN_HEIGHT / 2,0.0f);		//�|���S���̒��S�l

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

	//���_�o�b�t�@�����b�N
	g_pVtxBuffRANKING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�e�̒��_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_posRanking.x - RANKING_SIZE_X, g_posRanking.y - RANKING_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posRanking.x + RANKING_SIZE_X, g_posRanking.y - RANKING_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posRanking.x - RANKING_SIZE_X, g_posRanking.y + RANKING_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posRanking.x + RANKING_SIZE_X, g_posRanking.y + RANKING_SIZE_Y, 0.0f);

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

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRANKING->Unlock();


	InitCamera();

	InitLight();

	InitMeshBg();

	InitMeshField();

	InitWall();

	InitObject();

	InitEnter();

	InitPlayer2();

	SetObject(D3DXVECTOR3(40, 0, -95), D3DXVECTOR3(0, 0, 0));

	//�X�R�A�̏�����
	InitScore();

	//************************************
	// �����L���O�\��
	//************************************
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 290, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 160, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 + 90, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 + 220, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);

	AddScore(0,SCORE_RAKING);
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

	//�X�R�A�̏I������
	UninitScore();

	UninitCamera();

	UninitLight();

	UninitMeshBg();

	UninitMeshField();

	UninitWall();

	UninitObject();

	UninitEnter();

	UninitPlayer2();
}

//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdateRanking(void)
{

	//�t�F�[�h�̃|�C���^
	FADE pFade = *GetFade();

	static int nCount = 0;

	nCount++;
	if (pFade == FADE_NONE)
	{
		//�ݒ�L�[�iENTER�L�[�j�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetMouseTrigger(0) == true || (nCount % 650) == 0)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}
	//�X�R�A�̍X�V����
	UpdateScore();

	UpdateLight();

	UpdateCamera();

	UpdateMeshBg();

	UpdateMeshField();

	UpdateObject();

	UpdateWall();

	UpdateEnter();

	UpdatePlayer2();
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawRanking(void)
{

	SetCamera(CAMERA_TYPE_RANKING_DEMO);

	DrawWall();

	DrawMeshBg();

	DrawMeshField();

	DrawObject();

	DrawScore();

	DrawEnter();

	DrawPlayer2();

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
