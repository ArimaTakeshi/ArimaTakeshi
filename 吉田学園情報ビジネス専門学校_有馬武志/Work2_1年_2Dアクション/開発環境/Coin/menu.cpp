//=========================================================================================================================
//
// ���j���[�̏��� [manu.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "menu.h"		//���j���[
#include "input.h"		//�L�[�{�[�h
#include "fade.h"		//�t�F�[�h
#include "game.h"		//���j���[
#include "sound.h"		//�T�E���h
#include "score.h"		//�X�R�A
#include "itemcount.h"	//�A�C�e���J�E���g
#include "player.h"		//�v���C���[
#include "life.h"		//���C�t

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MENU_TEXTURE_MENU		"data\\TEXTURE\\�V���b�v.jpg"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MENU_TEXTURE_MENU0		"data\\TEXTURE\\�A�C�e���Q�{.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MENU_TEXTURE_MENU1		"data\\TEXTURE\\�̗�+1.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MENU_TEXTURE_MENU2		"data\\TEXTURE\\�X�R�A���Z.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MENU_TEXTURE_MENU3		"data\\TEXTURE\\1��50�R�C��.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MENU_TEXTURE_MENU4		"data\\TEXTURE\\�O�ɏo��.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_TEXTURE				(6)										//�e�N�X�`���̍ő吔
#define MENU_POS_X				(0)										//���j���[�̍���X���W
#define MENU_POS_Y				(0)										//���j���[�̍���Y���W
#define MENU_WIDTH				(SCREEN_WIDTH)							//���j���[�̕�
#define MENU_HEIGHT				(SCREEN_HEIGHT)							//���j���[�̍���
#define MENU_TEXTURE_UV_U		(1.0f)									//�e�N�X�`���A�j���[�V����U�͈�
#define MENU_TEXTURE_UV_V		(1.0f)									//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMenu[MAX_TEXTURE] = {};//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenu = NULL;		 //���_�o�b�t�@�ւ̃|�C���^
MENUIN g_Menu[MAX_TEXTURE];										 //�|�[�X�̏��
int g_nSelectNum;

//=========================================================================================================================
// ���j���[����������
//=========================================================================================================================
void InitMenu(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntMenu = 0; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{//�u���b�N���J�E���g
		g_Menu[nCntMenu].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_Menu[nCntMenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Menu[nCntMenu].MenuHeight = 0;
		g_Menu[nCntMenu].MenuWidtht = 0;
		g_Menu[nCntMenu].SelectColor = 1.0f;
		g_Menu[nCntMenu].bUse = false;
		g_Menu[nCntMenu].PosMenu = 0;
	}

	g_nSelectNum = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�P���ڂ̉摜
		pDevice,
		MENU_TEXTURE_MENU,
		&g_pTextureMenu[0]
	);
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		MENU_TEXTURE_MENU0,
		&g_pTextureMenu[1]
	);
	D3DXCreateTextureFromFile
	(//�R���ڂ̉摜
		pDevice,
		MENU_TEXTURE_MENU1,
		&g_pTextureMenu[2]
	);
	D3DXCreateTextureFromFile
	(//�S���ڂ̉摜
		pDevice,
		MENU_TEXTURE_MENU2,
		&g_pTextureMenu[3]
	);
	D3DXCreateTextureFromFile
	(//�T���ڂ̉摜
		pDevice,
		MENU_TEXTURE_MENU3,
		&g_pTextureMenu[4]
	);
	D3DXCreateTextureFromFile
	(//�U���ڂ̉摜
		pDevice,
		MENU_TEXTURE_MENU4,
		&g_pTextureMenu[5]
	);


	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMenu,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMenu->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (nCount == 0)
		{//�J�E���g�O�������ꍇ
			//���_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���_�J���[�ݒ�
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
		else
		{//����ȊO�̏ꍇ
			//1.0f�ŌŒ�
			if (nCount == 1)
			{
				//���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}

		}
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(MENU_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, MENU_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(MENU_TEXTURE_UV_U, MENU_TEXTURE_UV_V);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMenu->Unlock();

	SetMenu(D3DXVECTOR3(0, 0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 720, 1280, 0);
	SetMenu(D3DXVECTOR3(100, 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130,1);
	SetMenu(D3DXVECTOR3(340, 280, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130, 2);
	SetMenu(D3DXVECTOR3(540, 80, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 170, 170, 3);
	SetMenu(D3DXVECTOR3(960, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130, 4);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, 590, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 250, 5);
}

//=========================================================================================================================
// ���j���[�I������
//=========================================================================================================================
void UninitMenu(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureMenu[nCount] != NULL)
		{
			g_pTextureMenu[nCount] -> Release();
			g_pTextureMenu[nCount] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMenu != NULL)
	{
		g_pVtxBuffMenu->Release();
		g_pVtxBuffMenu = NULL;
	}
}

//=========================================================================================================================
// ���j���[�X�V����
//=========================================================================================================================
void UpdateMenu(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	Player *pPlayer = GetPlayer();
	int nGetMaxCoin = GetItemCount();

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffMenu->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_A) == true )
	{//���L�[�̏���������Ƃ�
		//���j���[�ړ���
		PlaySound(SOUND_LABEL_SE_MENUUPDOWN);
		// ���_�J���[�ݒ�
		g_Menu[g_nSelectNum + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_nSelectNum = (g_nSelectNum + 4) % 5;
		g_Menu[g_nSelectNum + 1].SelectColor = 1.0f;
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_D) == true)
	{//���L�[�̉����������Ƃ�
		//���j���[�ړ���
		PlaySound(SOUND_LABEL_SE_MENUUPDOWN);
		// ���_�J���[�ݒ�
		g_Menu[g_nSelectNum + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_nSelectNum = (g_nSelectNum + 1) % 5;
		g_Menu[g_nSelectNum + 1].SelectColor = 1.0f;
	}

	//�_�ŏ���
	//�I�����Ă���J���[�̒l�����炵�Ă���
	g_Menu[g_nSelectNum + 1].col.r -= 0.03f;
	g_Menu[g_nSelectNum + 1].col.g -= 0.03f;
	g_Menu[g_nSelectNum + 1].col.b -= 0.03f;

	if (g_Menu[g_nSelectNum + 1].col.r < 0.5f && g_Menu[g_nSelectNum + 1].col.g < 0.5f && g_Menu[g_nSelectNum + 1].col.b < 0.5f)
	{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
		g_Menu[g_nSelectNum + 1].col.r = 1.0f;
		g_Menu[g_nSelectNum + 1].col.g = 1.0f;
		g_Menu[g_nSelectNum + 1].col.b = 1.0f;
	}

	for (int nCntMenu = 1; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{
		// ���_�J���[�ݒ�
		pVtx[nCntMenu * 4].col = g_Menu[nCntMenu].col;
		pVtx[nCntMenu * 4 + 1].col = g_Menu[nCntMenu].col;
		pVtx[nCntMenu * 4 + 2].col = g_Menu[nCntMenu].col;
		pVtx[nCntMenu * 4 + 3].col = g_Menu[nCntMenu].col;

	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_nSelectNum == 0)
		{//���j���[�̂O�Ԗ�
			if (nGetMaxCoin - 150 > 0)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_ITEMBEY);

				//�R�C���̖������Ђ�
				AddItemCount(-150);

				//�R�C���Q�{
				SetCoinState(GETCOIN_X2);
			}
			else
			{
				//����������Ȃ��Ƃ�
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 1)
		{//���j���[�̂P�Ԗ�
			if (nGetMaxCoin - 60 > 0)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_ITEMBEY);

				//�R�C���̖������Ђ�
				AddItemCount(-60);

				if (pPlayer->nLife < 3)
				{
					pPlayer->nLife += 1;
					AddLife(1, LifeTex_HIL);
				}
			}
			else
			{
				//����������Ȃ��Ƃ�
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 2)
		{//���j���[�̂Q�Ԗ�
			if (nGetMaxCoin - 80 > 0)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_ITEMBEY);

				//�R�C���̖������Ђ�
				AddItemCount(-80);
				// �X�R�A�����Z
				AddScore(100000, SCORE_SHOP);
			}
			else
			{
				//����������Ȃ��Ƃ�
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 3)
		{//���j���[�̂R�Ԗ�
			if (nGetMaxCoin - 170 > 0)
			{
				//���艹
				PlaySound(SOUND_LABEL_SE_ITEMBEY);
				//�R�C���̖������Ђ�
				AddItemCount(-170);
				if (pPlayer->nLife < 3)
				{//HP3�ȏ�ɂȂ����ꍇ�����Ȃ��悤�ɂ���
					pPlayer->nLife += 3;
					AddLife(3, LifeTex_HIL);
				}
			}
			else
			{
				//����������Ȃ��Ƃ�
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 4)
		{//���j���[�̂S�Ԗ�
			//���艹
			PlaySound(SOUND_LABEL_SE_ITEMBEY);
			StopSound(SOUND_LABEL_BGM004);
			SetMenuState(false);
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffMenu->Unlock();
}

//=========================================================================================================================
// ���j���[�`�揈��
//=========================================================================================================================
void DrawMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffMenu,
		0,
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		if (g_Menu[nCount].bUse == true)
		{
			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_pTextureMenu[g_Menu[nCount].nType]);

			//���j���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}
//============================================
//�@���j���[�̃Z�b�g
//============================================
void SetMenu(D3DXVECTOR3 pos, D3DXCOLOR col, float fHeight, float fWidth , int nType)
{
	//�u���b�N�J�E���g
	int nCntMenu;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMenu->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntMenu = 0; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{//�u���b�N���J�E���g
		if (g_Menu[nCntMenu].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_Menu[nCntMenu].pos = pos;				//pos�l���
			g_Menu[nCntMenu].col = col;				//�J���[
			g_Menu[nCntMenu].nType = nType;			//���
			g_Menu[nCntMenu].bUse = true;			//�g�p���Ă����Ԃɂ���
			g_Menu[nCntMenu].MenuHeight = fHeight;	//�u���b�N�̍���
			g_Menu[nCntMenu].MenuWidtht = fWidth;	//�u���b�N�̕�

			//���_�ݒ�
			pVtx[nCntMenu * 4].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x, g_Menu[nCntMenu].pos.y, 0.0f);
			pVtx[nCntMenu * 4 + 1].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x + g_Menu[nCntMenu].MenuWidtht, g_Menu[nCntMenu].pos.y, 0.0f);
			pVtx[nCntMenu * 4 + 2].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x, g_Menu[nCntMenu].pos.y + g_Menu[nCntMenu].MenuHeight, 0.0f);
			pVtx[nCntMenu * 4 + 3].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x + g_Menu[nCntMenu].MenuWidtht, g_Menu[nCntMenu].pos.y + g_Menu[nCntMenu].MenuHeight, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntMenu * 4].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			pVtx[nCntMenu * 4 + 1].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			pVtx[nCntMenu * 4 + 2].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			pVtx[nCntMenu * 4 + 3].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMenu->Unlock();
}

//============================================
//
//============================================
void DeleteMenu(void)
{
	for (int nCntMenu = 0; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{//�u���b�N���J�E���g
		if (g_Menu[nCntMenu].bUse == true)
		{//true��������
			g_Menu[nCntMenu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Menu[nCntMenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Menu[nCntMenu].MenuHeight = 0;
			g_Menu[nCntMenu].MenuWidtht = 0;
			g_Menu[nCntMenu].SelectColor = 1.0f;
			g_Menu[nCntMenu].bUse = false;
			g_Menu[nCntMenu].PosMenu = 0;
		}
	}
}