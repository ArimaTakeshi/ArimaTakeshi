//=========================================================================================================================
//
// �|���S���̏��� [polygon.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "player.h"		//�|���S��
#include "input.h"		//����
#include <stdlib.h>		//lib
#include <time.h>		//time
#include "fade.h"		//�t�F�[�h
#include "block.h"		//�u���b�N
#include "life.h"		//���C�t
#include "item.h"		//�A�C�e��
#include "sound.h"		//�T�E���h

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define PLAYER_TEXTURE_NAME		"data\\TEXTURE\\player000.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define PLAYER_TEXTURE_UV_U		(0.25f)									//�e�N�X�`���A�j���[�V����U�͈�
#define PLAYER_TEXTURE_UV_V		(0.5f)									//�e�N�X�`���A�j���[�V����V�͈�
#define PLAYER_HEIGHT			(60)									//�v���C���[�̐g��
#define PLAYER_WIDTH			(30)									//�v���C���[�̉���
#define PLAYER_LIFE				(3)										//�v���C���[��HP
//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePlayer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Player g_player;
//�J�E���g�ϐ�������
int g_nCount;
//=========================================================================================================================
	// �|���S������������
//=========================================================================================================================
void InitPlayer(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//������
	g_player.nCounterAnim = 0;		//�J�E���^�[��������
	g_player.nPatternAnim = 0;		//�p�^�[����������
	g_player.TexT  = 0;				//�e�N�X�`���̃^�e�ړ�		
	//�J�n�ʒu
	g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 600/*+ 300*/, 0.0f);
	g_player.move = D3DXVECTOR3(0, 0, 0.0f);
	g_player.bJump = true;
	g_player.PlayerHeight = PLAYER_HEIGHT;
	g_player.PlayerWidth = PLAYER_WIDTH;
	g_player.nLife = PLAYER_LIFE;
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nCounterState = 0;
	g_player.bUse = true;
	g_nCount = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		PLAYER_TEXTURE_NAME,
		&g_pTexturePlayer
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffPlayer->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, PLAYER_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U, PLAYER_TEXTURE_UV_V);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=========================================================================================================================
// �|���S���I������
//=========================================================================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=========================================================================================================================
// �|���S���X�V����
//=========================================================================================================================
void UpdatePlayer(void)
{		
		//���_���ւ̃|�C���^
		VERTEX_2D *pVtx;	

		//�p�^�[�����̍X�V
		g_player.nCounterAnim++;	

		//�O��̈ʒu��ۑ�
		g_player.posOld = g_player.pos;


		//���_�o�b�t�@�����b�N
		g_pVtxBuffPlayer->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		switch (g_player.state)
		{//�v���C���[�̏��
		//�ʏ���
		case PLAYERSTATE_NORMAL:		
			break;
		//�_���[�W���
		case PLAYERSTATE_DAMAGE:		
			g_player.nCounterState--;	//��Ԃ��J�E���g

			if (g_player.nCounterState <= 0)
			{//��ԃJ�E���g�I��
				//�F�ύX
				g_player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				//��ԕω�
				g_player.state = PLAYERSTATE_NORMAL;
			}

			break;
		//�v���C���[�����ʂƂ�
		case PLAYERSTATE_DEAHT:
			//�J�E���g��--���O�ȉ��ɂ���
			g_player.nCounterState--;
			if (g_player.nCounterState <= 0)
			{
				SetFadeMode(MODE_RESULT);
			}
			return;
			break;
		}

		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{//���ɍs��
			//g_player.move.x -= 3.0f;
				g_player.pos.x += sinf(-D3DX_PI * 0.5f) * 5.0f;
				g_player.pos.y += cosf(-D3DX_PI * 0.5f) * 5.0f;

				//�t���[���p�^�[��
				if ((g_player.nCounterAnim % 5) == 0 && g_player.bJump == false)
				{
					//�A�j���[�V�����̃p�^�[��No.�������l�ɖ߂�
					g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
				}
				//������
				g_player.TexT = 1;
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{//�E�ɍs��
			//g_player.move.x += 3.0f;

				g_player.pos.x += sinf(D3DX_PI * 0.5f) * 5.0f;
				g_player.pos.y += cosf(D3DX_PI * 0.5f) * 5.0f;

				//�t���[���p�^�[��
				if ((g_player.nCounterAnim % 5) == 0 && g_player.bJump == false)
				{
					//�A�j���[�V�����̃p�^�[��No.�������l�ɖ߂�
					g_player.nPatternAnim = (g_player.nPatternAnim + 1) % 4;
				}
				//�E����
				g_player.TexT = 0;
		}
		else
		{//�L�[�{�[�h�������ĂȂ��Ƃ�
			if ((g_player.nCounterAnim % 5) == 0 && g_player.bJump == false)
			{
				//�p�^�[����������
				g_player.nPatternAnim = 0;
				g_player.nCounterAnim = 0;
			}
		}
		

		//�|���S�����G���A�O�̏ꍇ
		if (g_player.pos.x - PLAYER_WIDTH < PLAYER_WIDTH * -1)
		{//��ʔ��Α��Ɉړ��i���j
			g_player.pos.x = SCREEN_WIDTH;
		}
		else if (g_player.pos.x + PLAYER_WIDTH > SCREEN_WIDTH + PLAYER_WIDTH)
		{//��ʔ��Α��Ɉړ��i�E�j
			g_player.pos.x = 0;
		}
		if (g_player.pos.y - PLAYER_HEIGHT < 0)
		{//��ʂ̏�ɏo���Ȃ�
			g_player.pos.y = PLAYER_HEIGHT;
			//�V��ɓ��������ꍇmove��0�ɂ���
			g_player.move.y = 0.0f;
		}
		if (g_player.pos.y  > SCREEN_HEIGHT)
		{//���ɗ������珉���l�ɂ��ǂ�
			g_nCount++;
			//�P�b��������
			if ((g_nCount % 60) == 0)
			{
				//�����l�ɖ߂�
				g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 630/*+ 300*/, 0.0f);
				g_player.posOld = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 630/*+ 300*/, 0.0f);
				//�G�⌊�ɗ�������HP�����炵�Ă���
				HitPlayer(1);

				g_nCount = 0;
			}
		}
		
		//�W�����v	
		if (GetKeyboardTrigger(DIK_SPACE) == true && g_player.bJump == false)
		{
			//�W�����v��
			PlaySound(SOUND_LABEL_SE_JAMP);
			//�W�����v�̍���
			g_player.move.y = -15.0f;

			//�W�����v�������J��
			g_player.nPatternAnim = 1;

			g_player.bJump = true;
		}
		else if (GetKeyboardTrigger(DIK_W) == true && g_player.bJump == false)
		{
			//�W�����v��
			PlaySound(SOUND_LABEL_SE_JAMP);
			//�W�����v�̍���
			g_player.move.y = -15.0f;

			//�W�����v�������J��
			g_player.nPatternAnim = 1;

			g_player.bJump = true;
		}
		//�d�͂̒l�@�⑫:���̒l���A�P�ɋ߂Â����Ƃɏd�͂��Ȃ��Ȃ�
		g_player.move.y += 0.5f;

		g_player.pos.y += g_player.move.y;

		//�A�C�e���̂����蔻��
		CollisionItem(&g_player.pos,&g_player.posOld,&g_player.move,&g_player.PlayerWidth,&g_player.PlayerHeight);

		//���n������
		if (CollisionBlock(&g_player.pos, &g_player.posOld, &g_player.move, &g_player.PlayerWidth, &g_player.PlayerHeight) == true)
		{
			g_player.bJump = false;
		}
		else
		{//�����ŁAtrue�ɂ��Ȃ��ƁA�������󒆃W�����v���ł���悤�ɂȂ�
			g_player.bJump = true;	
		}

		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V);
		pVtx[1].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V);
		pVtx[2].tex = D3DXVECTOR2(0.0f + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V + PLAYER_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PLAYER_TEXTURE_UV_U + float(0.25 * g_player.nPatternAnim), g_player.TexT  * PLAYER_TEXTURE_UV_V + PLAYER_TEXTURE_UV_V);

		//���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y, 0.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffPlayer->Unlock();	
}

//=========================================================================================================================
// �|���S���`�揈��
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
		g_pVtxBuffPlayer,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	if (g_player.bUse == true)
	{
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		//�|���S���̕`��
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

	//���C�t������
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{//���C�t��0�ȉ��ɂȂ����ꍇ
		g_player.nLife = 0;
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEAHT;
		g_player.nCounterState = 60;
		g_player.bUse = false;
	
		//�G�ɓ���������HP�����炵�Ă���
		AddLife(-nDamage, LifeTex_DAMAGE);
	}
	else
	{//���C�t��1�ȏ�̏ꍇ
		g_player.state = PLAYERSTATE_DAMAGE;
		g_player.nCounterState = 5;

		//�G�⌊�ɗ�������HP�����炵�Ă���
		AddLife(-nDamage, LifeTex_DAMAGE);

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

//============================================
//
//============================================
void DeletePlayer(void)
{
	if (g_player.bUse == true)
	{
		//������
		g_player.nCounterAnim = 0;		//�J�E���^�[��������
		g_player.nPatternAnim = 0;		//�p�^�[����������
		g_player.TexT = 0;				//�e�N�X�`���̃^�e�ړ�		
		//�J�n�ʒu
		g_player.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 545, 600/*+ 300*/, 0.0f);
		g_player.move = D3DXVECTOR3(0, 0, 0.0f);
		g_player.bJump = true;
		g_player.state = PLAYERSTATE_NORMAL;
		g_player.nCounterState = 0;
	}
}