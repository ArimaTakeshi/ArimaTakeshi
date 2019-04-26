//=========================================================================================================================
//
// �v���C���[�̏��� [playe.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "player.h"		//�v���C���[
#include "bullet.h"		//�e
#include "input.h"		//���͏���
#include <stdlib.h>		//lib
#include <time.h>		//time
#include "explosion.h"	//��������
#include "fade.h"		//�t�F�[�h
#include "life.h"		//���C�t
#include "minibossenemy.h"
#include "bossenemy.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define PLAYER_TEXTURE_NAME		"data\\TEXTURE\\�j���g��.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define PLAYER_POS_X			(SCREEN_WIDTH / 2 - 25)					//�v���C���[�̍���X���W
#define PLAYER_POS_Y			(SCREEN_HEIGHT - 100)					//�v���C���[�̍���Y���W
#define PLAYER_WIDTH			(SCREEN_WIDTH / 2 + 25)					//�v���C���[�̕�
#define PLAYER_HEIGHT			(SCREEN_HEIGHT - 50)					//�v���C���[�̍���
#define PLAYER_G_POS_X			(25)									//g_pos�����X����
#define PLAYER_G_POS_Y			(35)									//g_pos�����Y����
#define PLAYER_TEXTURE_SPEED	(10)									//�e�N�X�`���A�j���[�V�����X�s�[�h
#define PLAYER_TEXTURE_PATTERN	(10)									//�e�N�X�`���A�j���[�V�����p�^�[����
#define PLAYER_TEXTURE_UV_U		(1.0f)									//�e�N�X�`���A�j���[�V����U�͈�
#define PLAYER_TEXTURE_UV_V		(1.0f)									//�e�N�X�`���A�j���[�V����V�͈�
#define PLAYER_UPSPEED			(1.0f)									//�v���C���[�����X�s�[�h
#define PLAYER_DOWNSPEED		(0.125f)								//�v���C���[�����X�s�[�h
#define SINCOS_ANGLE_135		(0.75f)									//sin,cos�p�x�i0.75�j				
#define SINCOS_ANGLE_90			(0.5f)									//sin,cos�p�x�i0.5�j
#define SINCOS_ANGLE_45			(0.25f)									//sin,cos�p�x�i0.25�j
#define SINCOS_ANGLE_0			(0.0f)									//sin,cos�p�x�i0.0�j

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureplayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffplayer = NULL;			//���_�o�b�t�@�ւ̃|�C���^
int g_nCounterAnim;										//�A�j���[�V�����J�E���^�[
int g_nPatternAnim;										//�A�j���[�V�����p�^�[��No.
Player g_player;

//=========================================================================================================================
// �v���C���[����������
//=========================================================================================================================
void InitPlayer(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_nCounterAnim = 0;		//�J�E���^�[��������
	g_nPatternAnim = 0;		//�p�^�[����������

	g_player.pos = D3DXVECTOR3((PLAYER_POS_X + PLAYER_WIDTH) / 2, (PLAYER_POS_Y + PLAYER_HEIGHT) / 2, 0.0f);	//�v���C���[���S�l
	g_player.move = D3DXVECTOR3(0, 0, 0.0f);																	//�v���C���[�ړ��l
	g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);															//�v���C���[�̐F
	MODE *pMode;
	pMode = GetMode();

	if (*pMode == MODE_PLAYTUTORIAL)
	{//�`���[�g���A�����̃v���C���[�̗�
		g_player.nLife = 100000;
	}
	else if(*pMode == MODE_GAME)
	{//�Q�[�����[�h���̃v���C���[�̗�
		g_player.nLife = 20;
	}
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;
	g_player.bUse = true;


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		PLAYER_TEXTURE_NAME,
		&g_pTextureplayer
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffplayer,
		NULL
	);
	
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffplayer->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH, PLAYER_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYER_POS_X, PLAYER_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, PLAYER_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, PLAYER_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffplayer->Unlock();
}

//=========================================================================================================================
// �v���C���[�I������
//=========================================================================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureplayer != NULL)
	{
		g_pTextureplayer->Release();
		g_pTextureplayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffplayer != NULL)
	{
		g_pVtxBuffplayer->Release();
		g_pVtxBuffplayer = NULL;
	}
}

//=========================================================================================================================
// �v���C���[�X�V����
//=========================================================================================================================
void UpdatePlayer(void)
{
	//�ϐ��錾
	float nPlayerSpeed = PLAYER_UPSPEED;	//�v���C���[���x
	static int nSelectSpeed = 1;			//�e���ύX 
	static int nSelectAngle = 2;			//�e���ύX
	static int nSelectColNum = 0;			//�e�H�ύX
	static BULLETTYPE Type = BULLETTYPE_PLAYER;
	static D3DXVECTOR3 nSelectMove(0.0f, 0.0f, 0.0f);		//�e�ړ��l
	static D3DXCOLOR nSelectColor(1.0f, 1.0f, 1.0f, 1.0f);	//�e�F�ύX
	static float nAngleSpeed = 0.05f;		//�p�x
	static float nAngle = nAngleSpeed;		//�p�x2
	float nSpeed = 5.0f;					//���x

	nAngle += nAngleSpeed;

	g_nCounterAnim++;	//�J�E���^�[���Z

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffplayer->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
		switch (g_player.state)
		{//�G���
		case PLAYERSTATE_NORMAL:			//�ʏ���
			break;
		case PLAYERSTATE_DAMAGE:		//�_���[�W���
			g_player.nCounterState--;	//��Ԃ��J�E���g

			if (g_player.nCounterState <= 0)
			{//��ԃJ�E���g�I��
				 //�F�ύX
				g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//��ԕω�
				g_player.state = PLAYERSTATE_NORMAL;
			}

			break;
		case PLAYERSTATE_DEAHT:
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				SetFade(MODE_RESULT);
			}
			return;
			break;
		}


		//�ړ����x�ύX



		if (GetKeyboardPress(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true)
		{//�C�ӂ̃L�[�iSHIFT�L�[�j���������ꍇ
			nPlayerSpeed = PLAYER_UPSPEED - 0.7f;
			nPlayerSpeed = PLAYER_UPSPEED - 0.7f;
		}
		else if (GetKeyboardRelease(DIK_LSHIFT) == true || GetKeyboardPress(DIK_RSHIFT) == true)
		{//�C�ӂ̃L�[�iSHIFT�L�[�j�𗣂����ꍇ
			nPlayerSpeed = PLAYER_UPSPEED;
			nPlayerSpeed = PLAYER_UPSPEED;
		}


		//�ړ���������
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{//�C�ӂ̃L�[�iA�L�[�A���L�[�j���������ꍇ
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{//�㓯������
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{//����������
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;

				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//���̂�
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{//�C�ӂ̃L�[�iD�L�[�A�E�L�[�j���������ꍇ
			if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
			{//�㓯������
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_135) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
			{//����������
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//�E�̂�
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_UP) == true)
		{//�C�ӂ̃L�[�iW�L�[�A��L�[�j���������ꍇ
			if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
			{//����������
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
			{//�E��������
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//��̂�
				g_player.move.x += sinf(D3DX_PI) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI) * nPlayerSpeed;
			}
		}
		else if (GetKeyboardPress(DIK_S) == true || GetKeyboardPress(DIK_DOWN) == true)
		{//�C�ӂ̃L�[�iD�L�[�A���L�[�j���������ꍇ
			if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
			{//����������
				g_player.move.x += sinf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(-D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
			{//�E��������
				g_player.move.x += sinf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
				g_player.move.y += cosf(D3DX_PI * SINCOS_ANGLE_45) * nPlayerSpeed;
			}
			else
			{//���̂�
				g_player.move.x += sinf(SINCOS_ANGLE_0) * nPlayerSpeed;
				g_player.move.y += cosf(SINCOS_ANGLE_0) * nPlayerSpeed;
			}
		}

		//�ړ�����
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		//��������
		g_player.move.x += (0.0f - g_player.move.x) * PLAYER_DOWNSPEED;
		g_player.move.y += (0.0f - g_player.move.y) * PLAYER_DOWNSPEED;

		//�v���C���[���G���A�O�̏ꍇ
		if (g_player.pos.x - 20 < 0)
		{//��ʔ��Α��Ɉړ��i���j
			g_player.pos.x = 20;
		}
		if (g_player.pos.x + 20 > SCREEN_WIDTH)
		{//��ʔ��Α��Ɉړ��i�E�j
			g_player.pos.x = SCREEN_WIDTH - 20;
		}
		if (g_player.pos.y - 20 < 0)
		{//��ʔ��Α��Ɉړ��i��j
			g_player.pos.y = 20;
		}
		if (g_player.pos.y + 20 > SCREEN_HEIGHT)
		{//��ʔ��Α��Ɉړ��i���j 
			g_player.pos.y = SCREEN_HEIGHT - 20;
		}

		//�����ʒu�ɖ߂�
		if (GetKeyboardPress(DIK_NUMPAD0) == true)
		{//�C�ӂ̃L�[�i0�L�[�j���������ꍇ
			g_player.pos = D3DXVECTOR3((PLAYER_POS_X + PLAYER_WIDTH) / 2, (PLAYER_POS_Y + PLAYER_HEIGHT) / 2, 0.0f);
		}

		//�e���ύX
		if (GetKeyboardPress(DIK_NUMPAD1) == true)
		{//�C�ӂ̃L�[�i1�L�[�j���������ꍇ
			nSelectSpeed = 1;
		}
		//else if (GetKeyboardPress(DIK_NUMPAD2) == true)
		//{//�C�ӂ̃L�[�i2�L�[�j���������ꍇ
		//	nSelectSpeed = 3;
		//}
		//else if (GetKeyboardPress(DIK_NUMPAD3) == true)
		//{//�C�ӂ̃L�[�i3�L�[�j���������ꍇ
		//	nSelectSpeed = 1;
		//}

		////�e���ύX
		//if (GetKeyboardPress(DIK_Z) == true || GetKeyboardPress(DIK_NUMPAD4) == true)
		//{//�C�ӂ̃L�[�iZ�L�[�A4�L�[�j���������ꍇ
		//	nSelectAngle = 1;
		//}
		//else if (GetKeyboardPress(DIK_X) == true || GetKeyboardPress(DIK_NUMPAD5) == true)
		//{//�C�ӂ̃L�[�iX�L�[�A5�L�[�j���������ꍇ
		//	nSelectAngle = 2;
		//}
		//else if (GetKeyboardPress(DIK_C) == true || GetKeyboardPress(DIK_NUMPAD6) == true)
		//{//�C�ӂ̃L�[�iC�L�[�A6�L�[�j���������ꍇ
		//	nSelectAngle = 3;
		//}
		else if (GetKeyboardPress(DIK_V) == true || GetKeyboardPress(DIK_NUMPAD8) == true)
		{//�C�ӂ̃L�[�iV�L�[�A8�L�[�j���������ꍇ
			nSelectAngle = 4;
		}

		//�C�ӂ̃L�[�iENTER�L�[�j���������ꍇ
		if (GetKeyboardTrigger(DIK_C) == true)
		{//�e�F�ύX
			nSelectColNum = (nSelectColNum + 1) % 2;
			//nDistance = nSelectColNum;	//����F�̋����ω�

			if (nSelectColNum == 0)
			{//�F�ύX�i���j
				nSelectColor.r = 1.0f;
				nSelectColor.g = 1.0f;
				nSelectColor.b = 1.0f;
				nSelectColor.a = 1.0f;
			}
			else if (nSelectColNum == 1)
			{//�F�ύX�i�΁j
				nSelectColor.r = 0.0f;
				nSelectColor.g = 0.0f;
				nSelectColor.b = 1.0f;
				nSelectColor.a = 1.0f;
			}
		}

		//�e���ˏ���
		if (GetKeyboardPress(DIK_SPACE) == true)
		{//�C�ӂ̃L�[�iSPACE�L�[�j���������ꍇ
			if (nSelectSpeed == 1)
			{//���x�����i�P�j
				if ((g_nCounterAnim % PLAYER_TEXTURE_SPEED) == 0)
				{//�l�i�T�j
					if (nSelectAngle == 1)
					{//���E�e��
						//���O
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E�O
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//����
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 2)
					{//�����e��
						//�O
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//�O
						nSelectMove.x = sinf(D3DX_PI * 0.9f) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * 0.9f) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//�O
						nSelectMove.x = sinf(D3DX_PI * -0.9f) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * -0.9f) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 3)
					{//�\���e��
						//�O
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 4)
					{//��]�e��
						//�O
						nSelectMove.x = sinf(D3DX_PI + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//���������������������������������������� �E�@���@�O�@��@��������������������������������������
											//�O
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
				}
			}
			else if (nSelectSpeed == 2)
			{//���x�����i�Q�j
				if ((g_nCounterAnim % (PLAYER_TEXTURE_SPEED - 2)) == 0)
				{//�l�i�R�j
					if (nSelectAngle == 1)
					{//���E�e��
					 //���O
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E�O
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//����
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 2)
					{//�����e��
						//�O
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 3)
					{//�E�O�e��
						//�O
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 4)
					{//��]�e��
					 //�O
						nSelectMove.x = sinf(D3DX_PI + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
				}
			}
			else if (nSelectSpeed == 3)
			{//���x�����i�R�j
				if ((g_nCounterAnim % (PLAYER_TEXTURE_SPEED - 5)) == 0)
				{//�l�i�P�j
					if (nSelectAngle == 1)
					{//���E�e��
					 //���O
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E�O
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//����
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 2)
					{//�����e��
						//�O
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 3)
					{//�E�O�e��
						//�O
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;//�O
						nSelectMove.x = sinf(D3DX_PI) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
					}
					else if (nSelectAngle == 4)
					{//��]�e��
					 //�O
						nSelectMove.x = sinf(D3DX_PI + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//���������������������������������������� �E�@���@�O�@��@��������������������������������������

											//�O
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_135 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_45 + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//���������������������������������������� �E��@����@�O���@�㉺�@��������������������������������������

											//�O
						nSelectMove.x = sinf(D3DX_PI * 0.375f + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * 0.375f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * 0.125f + nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * 0.125f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * 0.375f + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * 0.375f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(-D3DX_PI * 0.125f + nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * 0.125f + nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//���������������������������������������� �E��/2�@����/2�@�O��/2�@�㉺/2�@��������������������������������������

											//���Ύ���=====================================================
											//�O
						nSelectMove.x = sinf(D3DX_PI - nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_0 - nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_0 - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//��
						nSelectMove.x = sinf(-D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						nSelectMove.y = cosf(-D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);
						//�E
						nSelectMove.x = sinf(D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						nSelectMove.y = cosf(D3DX_PI * SINCOS_ANGLE_90 - nAngle) * nSpeed;
						SetBullet(g_player.pos, nSelectMove, nSelectColor, Type);

						//���������������������������������������� �E���΁@�����΁@�O���΁@�㔽�΁@��������������������������������������
					}
				}
			}
		}
//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y - 20, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y - 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - 20, g_player.pos.y + 20, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + 20, g_player.pos.y + 20, 0.0f);
	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	pVtx[1].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	pVtx[2].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	pVtx[3].col = D3DXCOLOR(g_player.col.r, g_player.col.g, g_player.col.b, g_player.col.a);
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffplayer->Unlock();
}

//=========================================================================================================================
// �v���C���[�`�揈��
//=========================================================================================================================
void DrawPlayer(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffplayer,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureplayer);

	// �|���S���̕`��
	if (g_player.bUse == true)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureplayer);
		//�v���C���[�̕`�� 
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//=========================================================================================================================
// �v���C���[�̃_���[�W����
//=========================================================================================================================
void HitPlayer(int nDamage)
{
	//�ϐ��錾
	/*int nCount = 0;*/

	MODE *pMode;
	pMode = GetMode();

	MiniBossEnemy *pMiniBossEnemy;
	pMiniBossEnemy = GetMiniBossEnemy();

	BossEnemy *pBossEnemy;
	pBossEnemy = GetBossEnemy();

	//���C�t������
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{//���C�t��0�ȉ��ɂȂ����ꍇ
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEAHT;
		g_player.nCounterState = 60;

		SetExplosion(g_player.pos, D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f));
		g_player.bUse = false;
		
		pMiniBossEnemy->bUse = false;

		pBossEnemy->bUse = false;

		if (*pMode == MODE_GAME)
		{
			//�e������������HP�����炵�Ă���
			AddLife(-1, LifeTex_DAMAGE);
		}

	}
	else
	{//���C�t��1�ȏ�̏ꍇ
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;

		if (*pMode == MODE_GAME)
		{
			//�e������������HP�����炵�Ă���
			AddLife(-1, LifeTex_DAMAGE);
		}
		//�F�ύX
		g_player.col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	}
}
//=========================================================================================================================
// �v���C���[�̎擾����
//=========================================================================================================================
Player *GetPlayer(void)
{
	return &g_player;
}