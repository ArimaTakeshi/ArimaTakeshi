//=========================================================================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "player.h"			//�v���C���[
#include "bullet.h"			//�e
#include "explosion.h"		//����
#include "enemy.h"			//�G
#include "effect.h"			//�G�t�F�N�g
#include "fade.h"			//�t�F�[�h	
#include "sound.h"			//�T�E���h
#include "input.h"			//�L�[�{�[�h����
#include "pause.h"			//�|�[�Y
#include "playtutorial.h"	//�`���[�g���A��

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define PLAYTUTORIAL_TEXTURE_NAME	"data\\TEXTURE\\�`���[�g���A��.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define PLAYTUTORIAL_POS_X			(0)								//�w�i�̍���X���W
#define PLAYTUTORIAL_POS_Y			(0)								//�w�i�̍���Y���W
#define PLAYTUTORIAL_WIDTH			(SCREEN_WIDTH)					//�w�i�̕�
#define PLAYTUTORIAL_HEIGHT			(SCREEN_HEIGHT)					//�w�i�̍���
#define PLAYTUTORIAL_TEXTURE_UV_U	(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define PLAYTUTORIAL_TEXTURE_UV_V	(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�
#define PLAYTUTORIAL_BACKTEXTURE_UV_V	(1.0f)							//�O�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
PLAYTUTORIALSTATE g_PlayTutorialState = PLAYTUTORIALSTATE_NORMAL;	//�Q�[�����
int g_nCounterPlayTutorialState;									//��ԃJ�E���^�[
LPDIRECT3DTEXTURE9 g_pTexturePLAYTUTORIAL = NULL;								//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPLAYTUTORIAL = NULL;						//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posPLAYTUTORIAL;												//�w�i�̈ʒu
D3DXVECTOR3 g_movePLAYTUTORIAL;												//�w�i�̈ړ�

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitPlayTutorial(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_posPLAYTUTORIAL = D3DXVECTOR3((PLAYTUTORIAL_POS_X + PLAYTUTORIAL_WIDTH) / 2, (PLAYTUTORIAL_POS_Y + PLAYTUTORIAL_HEIGHT) / 2, 0.0f);		//�|���S���̒��S�l

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		PLAYTUTORIAL_TEXTURE_NAME,
		&g_pTexturePLAYTUTORIAL
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPLAYTUTORIAL,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N
	g_pVtxBuffPLAYTUTORIAL->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PLAYTUTORIAL_POS_X, PLAYTUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYTUTORIAL_WIDTH, PLAYTUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYTUTORIAL_POS_X, PLAYTUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYTUTORIAL_WIDTH, PLAYTUTORIAL_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(PLAYTUTORIAL_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, PLAYTUTORIAL_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(PLAYTUTORIAL_TEXTURE_UV_U, PLAYTUTORIAL_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPLAYTUTORIAL->Unlock();


	//�G�̏���������
	InitEnemy();

	//�`���[�g���A���̓G
	SetEnemy(D3DXVECTOR3(SCREEN_WIDTH / 2, 150, 0.0f), 0);

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�v���C���[����������
	InitPlayer();

	//�����̏���������
	InitExplosion();

	//�e�̏���������
	InitBullet();

	//�|�[�Y�̏���������
	InitPause();

	g_PlayTutorialState = PLAYTUTORIALSTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCounterPlayTutorialState = 0;
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitPlayTutorial(void)
{

	//�G�̏I������
	UninitEnemy();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�v���C���[�̏I������
	UninitPlayer();

	//�����̏I������
	UninitExplosion();

	//�e�̏I������
	UninitBullet();

	//�|�[�Y�̏I������
	UninitPause();

	//�e�N�X�`���[�̔j��
	if (g_pTexturePLAYTUTORIAL != NULL)
	{
		g_pTexturePLAYTUTORIAL->Release();
		g_pTexturePLAYTUTORIAL = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPLAYTUTORIAL != NULL)
	{
		g_pVtxBuffPLAYTUTORIAL->Release();
		g_pVtxBuffPLAYTUTORIAL = NULL;
	}
}
//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdatePlayTutorial(void)
{
	//�t�F�[�h
	FADE pFade;
	pFade = *GetFade();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�G�̍X�V����
	UpdateEnemy();

	//�����̍X�V����
	UpdateExplosion();

	//�e�̍X�V����
	UpdateBullet();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	if (pFade == FADE_NONE)
	{
		//�ݒ�L�[�iENTER�L�[�j�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DECIDE);

			//���[�h�ݒ�
			SetFade(MODE_GAME);
		}
	}

}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawPlayTutorial(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffPLAYTUTORIAL,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTexturePLAYTUTORIAL);

	//�w�i�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�G�̕`�揈��
	DrawEnemy();

	//�v���C���[�̕`��
	DrawPlayer();

	//�����̕`�揈��
	DrawExplosion();

	//�e�̕`�揈��
	DrawBullet();
}
