//=========================================================================================================//
//
// window���� [window.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "enemy.h"
#include "fade.h"
#include "sound.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define BLOCK_VERTEX_NUM			(4)								// ���_�̐�
#define BLOCK_PRIMITIVE_NUM			(2)								// �v���~�e�B�u�̐�
#define BLOCK_MAX_TEXTURE			(8)
#define BLOCK_TextureName0		"data/TEXTURE/BlueRoof.jpg"			//�����K
#define BLOCK_TextureName1		"data/TEXTURE/YellowRoof.jpg"		//���蔲����
#define BLOCK_TextureName2		"data/TEXTURE/RedRoof.jpg"		//�����K �w�i
#define BLOCK_TextureName3		"data/TEXTURE/Chimney.jpg"		//��
#define BLOCK_TextureName4		"data/TEXTURE/GreenRoof.jpg"		//��
#define BLOCK_TextureName5		"data/TEXTURE/cloud.png"		//��
#define BLOCK_TextureName6		"data/TEXTURE/Stone.png"		//��
#define BLOCK_TextureName7		"data/TEXTURE/Ruins-2.png"		//��
#define	MAX_BLOCK			(1024)		// window�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posold;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR col;			//�F
	int nLengthX;			//����
	int nLengthY;			//����
	int nType;				//�摜
	float fSpeed;			//SPEED
	float fmoveSteep;		//�ړ������̊p�x
	float fCurve;			//������Z����J�[�u�l
	BLOCKSTATE state;		//
	int nCounterState[2];	//�G�l�~�[�̏�ԊǗ��p
	float fSteep;
	bool bUse;
}BLOCK;

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureBlock[BLOCK_MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
BLOCK					g_aBlock[MAX_BLOCK];
float					g_ScrollWide;
float					g_ScrollHeight;

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntWindow;

	// �e�̏��̏�����
	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		//g_aWindow[nCntWindow].pos = { 0.0f, 0.0f, 0.0f };
		//g_aWindow[nCntWindow].nLengthX = 0;
		//g_aWindow[nCntWindow].nLengthY = 0;
		//g_aWindow[nCntWindow].nType = 0;
		//g_aWindow[nCntWindow].col = { 1.0f, 1.0f, 1.0f, };
		g_aBlock[nCntWindow].bUse = false;
	}
	g_ScrollWide = 0.0f;
	g_ScrollHeight = 0.0f;

	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName0, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName4, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName5, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName6, &g_pTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName7, &g_pTextureBlock[7]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * BLOCK_VERTEX_NUM * MAX_BLOCK,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		//���_���W�̐ݒ�
		//pVtx[nCntWindow * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

		pVtx[nCntWindow * 4].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 1].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 2].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 3].rhw = 1.0f;

		//�J���[�ݒ�
		//pVtx[nCntWindow * 4].col = D3DCOLOR_RGBA(0, 0, 0, 255);	// A = �����x
		//pVtx[nCntWindow * 4 + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		//pVtx[nCntWindow * 4 + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		//pVtx[nCntWindow * 4 + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

		////�e�N�X�`�����W�ݒ�
		//pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 20.0f) * 1.0f, 0.0f);
		//pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, (g_aBlock[nCntWindow].nLengthY / 20.0f) * 1.0f);
		//pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 20.0f) * 1.0f, (g_aBlock[nCntWindow].nLengthY / 20.0f) * 1.0f);
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitBlock(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < BLOCK_MAX_TEXTURE; nCntTexture++)
	{
		if (g_pTextureBlock[nCntTexture] != NULL)
		{
			g_pTextureBlock[nCntTexture]->Release();
			g_pTextureBlock[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateBlock(void)
{
	int nCntBlock;
	PLAYER *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�S�E�B���h�E�����
		if (g_aBlock[nCntBlock].bUse == true)
		{//�g���Ă�����
			g_aBlock[nCntBlock].posold = g_aBlock[nCntBlock].pos;
			g_aBlock[nCntBlock].fmoveSteep += g_aBlock[nCntBlock].fCurve;
			g_aBlock[nCntBlock].move += D3DXVECTOR3(sinf(g_aBlock[nCntBlock].fmoveSteep), cosf(g_aBlock[nCntBlock].fmoveSteep), 0.0f) * g_aBlock[nCntBlock].fSpeed;
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;
			g_aBlock[nCntBlock].move.x += (0.0f - g_aBlock[nCntBlock].move.x) * 0.12f;
			g_aBlock[nCntBlock].move.y += (0.0f - g_aBlock[nCntBlock].move.y) * 0.12f;
			switch (g_aBlock[nCntBlock].state)
			{
			case BLOCKSTATE_FADE:
				if (pPlayer[0].pos.x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - PLAYER_CollisionX && pPlayer[0].pos.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + PLAYER_CollisionX &&
					pPlayer[0].pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - PLAYER_CollisionY + 1 && pPlayer[0].pos.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + PLAYER_CollisionY - 1)
				{//�͈͓��Ȃ�
					g_aBlock[nCntBlock].col.a -= 0.1f;
					if (g_aBlock[nCntBlock].col.a < 0.0f) { g_aBlock[nCntBlock].col.a = 0.0f; }
				}
				else
				{//�͈͊O�Ȃ�
					g_aBlock[nCntBlock].col.a += 0.002f;
					if (g_aBlock[nCntBlock].col.a >= 1.0f) { g_aBlock[nCntBlock].col.a = 1.0f; }
				}
				break;
			}
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	SettingPlayer();
}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawBlock(bool bBG)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntWindow;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	// �|���S���̕`��
	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		if (bBG == false && g_aBlock[nCntWindow].state != BLOCKSTATE_FADE)
		{
			if (g_aBlock[nCntWindow].bUse == true && g_aBlock[nCntWindow].pos.x - g_aBlock[nCntWindow].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntWindow].pos.x + g_aBlock[nCntWindow].nLengthX >= 0 && g_aBlock[nCntWindow].pos.y - g_aBlock[nCntWindow].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntWindow].pos.y + g_aBlock[nCntWindow].nLengthY >= 0)
			{// �e�N�X�`���̐ݒ�
				SettingBlock();
				pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntWindow].nType]);
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWindow * 4, BLOCK_PRIMITIVE_NUM);
			}
		}
		else if(bBG == true && g_aBlock[nCntWindow].state == BLOCKSTATE_FADE)
		{
			if (g_aBlock[nCntWindow].bUse == true && g_aBlock[nCntWindow].pos.x - g_aBlock[nCntWindow].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntWindow].pos.x + g_aBlock[nCntWindow].nLengthX >= 0 && g_aBlock[nCntWindow].pos.y - g_aBlock[nCntWindow].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntWindow].pos.y + g_aBlock[nCntWindow].nLengthY >= 0)
			{// �e�N�X�`���̐ݒ�
				SettingBlock();
				pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntWindow].nType]);
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWindow * 4, BLOCK_PRIMITIVE_NUM);
			}
		}
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SettingBlock(void)
{
	int nCntWindow;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		if (g_aBlock[nCntWindow].nType == 5) { g_aBlock[nCntWindow].nLengthY += 50; }
		else { g_aBlock[nCntWindow].nLengthY += 30; }
		//���_���W�̐ݒ�
		pVtx[nCntWindow * 4].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		if (g_aBlock[nCntWindow].nType == 5) { g_aBlock[nCntWindow].nLengthY -= 50; }
		else { g_aBlock[nCntWindow].nLengthY -= 30; }


		//�e�N�X�`�����W�ݒ�
		if (g_aBlock[nCntWindow].state == BLOCKSTATE_THIN0 || g_aBlock[nCntWindow].state == BLOCKSTATE_THIN1 || g_aBlock[nCntWindow].state == BLOCKSTATE_THIN2)
		{
			pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else
		{
			pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 100.0f) * 1.0f, 0.0f);
			pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 100.0f) * 1.0f,1.0f);
		}
		//�J���[�ݒ�
		pVtx[nCntWindow * 4].col = g_aBlock[nCntWindow].col;// A = �����x
		pVtx[nCntWindow * 4 + 1].col = g_aBlock[nCntWindow].col;
		pVtx[nCntWindow * 4 + 2].col = g_aBlock[nCntWindow].col;
		pVtx[nCntWindow * 4 + 3].col = g_aBlock[nCntWindow].col;
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, float fSteep, float fCurve, float fmoveSteep, float fSpeed, BLOCKSTATE state)
{
	int nCntWindow;

	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		if (g_aBlock[nCntWindow].bUse == false)
		{
			g_aBlock[nCntWindow] = { pos, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), col, nLengthX, nLengthY, nType, fSpeed, fmoveSteep, fCurve, state, {0,0},fSteep, true };
			break;
		}
	}
}
//=============================================================================
// �u���b�N�Ƃ̏Փ˔���
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float *fRide, bool bRide, PLAYERSTATE *state, int nLengthX, int nLengthY, int nCntEnemy, USETYPE type)
{
	int nCntBlock;
	int nLength;

	bool bJump = false;
	bool bWall = false;
	PLAYER *pPlayer = GetPlayer();

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�㉺�̔���
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN0&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN1&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN2)
		{//�g���Ă���u���b�N && ����t���̃u���b�N�Ȃ�
				if (g_aBlock[nCntBlock].posold.y - g_aBlock[nCntBlock].nLengthY >= pPosold[0].y + nLengthY && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= pPos[0].y + nLengthY)
				{//�O�񂪏�&&�����
					if (state[0] != PLAYERSTATE_FALL || g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
					{
						nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
						if (nLength < 0) { nLength *= -1; }
						nLength -= nLengthX;
						if (nLength <= g_aBlock[nCntBlock].nLengthX)
						{
							if (g_aBlock[nCntBlock].state == BLOCKSTATE_OUT && type == USETYPE_PLAYER) { SetFade(MODE_RESULT, 0); }	//���@���E��
							else if (g_aBlock[nCntBlock].state == BLOCKSTATE_OUT && type == USETYPE_ENEMY) {  }//�G���E��
							else
							{
								pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY;
								pMove[0].y = 0.0f;
								bJump = true;
								if (bRide == true) { *fRide += g_aBlock[nCntBlock].move.x; }
								if (g_aBlock[nCntBlock].state == BLOCKSTATE_CLEAR && pPlayer[0].nClear == 0) { pPlayer[0].nClear = 1; }
							}
						}
					}
				}
				//else if (g_aBlock[nCntBlock].posold.y + g_aBlock[nCntBlock].nLengthY <= pPosold[0].y - nLengthY && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= pPos[0].y - nLengthY && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
				//{//�O�񂪉�&&���艺 
				//	nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
				//	if (nLength < 0) { nLength *= -1; }
				//	nLength -= nLengthX;
				//	if (nLength <= g_aBlock[nCntBlock].nLengthX)
				//	{
				//		pPos[0].y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + nLengthY;
 			//			pMove[0].y = 0.0f;
				//	}
				//}
		}
	}

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�E���̔���
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_BOARD && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN0&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN1&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN2)
		{//�g���Ă���u���b�N && ����t���̃u���b�N�Ȃ�
				if (g_aBlock[nCntBlock].posold.x + g_aBlock[nCntBlock].nLengthX <= pPosold[0].x - nLengthX && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= pPos[0].x - nLengthX)
				{//�O�񂪉E&&����E
					nLength = (int)pPos[0].y - (int)g_aBlock[nCntBlock].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= nLengthY;
					if (nLength < g_aBlock[nCntBlock].nLengthY)
					{
						pPos[0].x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + nLengthX + 1.0f;
						pMove[0].x = 0.0f;
						bWall = true;
					}
				}
				if (g_aBlock[nCntBlock].posold.x - g_aBlock[nCntBlock].nLengthX >= pPosold[0].x + nLengthX && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= pPos[0].x + nLengthX)
				{//�O�񂪍�&&���荶
					nLength = (int)pPos[0].y - (int)g_aBlock[nCntBlock].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= nLengthY;
					if (nLength < g_aBlock[nCntBlock].nLengthY)
					{
						pPos[0].x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - nLengthX - 1.0f;
						pMove[0].x = 0.0f;
						bWall = true;
					}
				}
		}
	}

	if (bWall == true && bJump == false && type == USETYPE_PLAYER)
	{//�㉺���ʂ炸���̂ݒʂ����ꍇ�̊ђʖh�~�Ƃ���
		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{//�㉺�̔���
			if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= 0 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= 0 && 
				g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_BOARD)
			{//�g���Ă���u���b�N && ����t���̃u���b�N�Ȃ�
					if (g_aBlock[nCntBlock].posold.y - g_aBlock[nCntBlock].nLengthY >= pPosold[0].y + nLengthY && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= pPos[0].y + nLengthY)
					{//�O�񂪏�&&�����
						if (state[0] != PLAYERSTATE_FALL || g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
						{
							nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
							if (nLength < 0) { nLength *= -1; }
							nLength -= nLengthX;
							if (nLength <= g_aBlock[nCntBlock].nLengthX)
							{
								pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY;
								pMove[0].y = 0.0f;
								bJump = true;
							}
						}
					}
					else if (g_aBlock[nCntBlock].posold.y + g_aBlock[nCntBlock].nLengthY <= pPosold[0].y - nLengthY && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= pPos[0].y - nLengthY && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
					{//�O�񂪉�&&���艺
						nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
						if (nLength < 0) { nLength *= -1; }
						nLength -= nLengthX;
						if (nLength <= g_aBlock[nCntBlock].nLengthX)
						{
							pPos[0].y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + nLengthY;
							pMove[0].y = 0.0f;
						}
					}
			}
		}
	}

	//if (bJump == false && type == USETYPE_PLAYER)
	//{//���n�ł��Ă��Ȃ��ꍇ�@�R���܂�m�F
	//	PLAYER *pPlayer = GetPlayer();
	//	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//	{//�㉺�̔���
	//		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= 0 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= 0 &&
	//			g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BREAK && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN && g_aBlock[nCntBlock].state != BLOCKSTATE_BOARD)
	//		{//�g���Ă���u���b�N && ����t���̃u���b�N�Ȃ�
	//			if (g_aBlock[nCntBlock].posold.y - g_aBlock[nCntBlock].nLengthY >= pPosold[0].y - 15 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= pPos[0].y - 15)
	//			{//�O�񂪏�&&�����
	//				nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
	//				if (pPlayer[0].nAngle == PLAYERANGLE_LEFT)
	//				{//�������Ȃ�
	//					nLength -= nLengthX + 1;
	//					if (nLength == g_aBlock[nCntBlock].nLengthX)
	//					{//�����������Ȃ�
	//						pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY + 15;
	//						pMove[0].y = 0.0f;
	//						state[0] = PLAYERSTATE_CATCH;
	//					}
	//				}
	//				else
	//				{//�E�����Ȃ�
	//					nLength += nLengthX + 1;
	//					if (nLength == -g_aBlock[nCntBlock].nLengthX)
	//					{//�����������Ȃ�
	//						pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY + 15;
	//						pMove[0].y = 0.0f;
	//						state[0] = PLAYERSTATE_CATCH;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	return bJump;
}
//=========================================================================================================//
// * �e�̓����蔻��
//=========================================================================================================//
bool HitBullet(Bullet pBullet)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntBlock;
	int nScore = 0;
	float fLength[2];
	float fPercent = 1.0f;		//�e�̒����̔{��
	bool bHit = false;
	if (pBullet.nShot != BULLETTYPE_EFFECT)
	{
		if (pBullet.state == BULLETSTATE_NONE) { fPercent = 0.5f; }
		fLength[0] = (sinf(pBullet.steep) * pBullet.nLengthX + sinf(pBullet.steep) * pBullet.nLengthY) * fPercent;	//�e�̉��̒���
		fLength[1] = (cosf(pBullet.steep) * pBullet.nLengthX + cosf(pBullet.steep) * pBullet.nLengthY) * fPercent;	//�e�̏c�̒���
		if (fLength[0] < 0) { fLength[0] *= -1; }
		if (fLength[1] < 0) { fLength[1] *= -1; }

		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG)
			{
				if (pBullet.pos.x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - fLength[0] && pBullet.pos.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + fLength[0] &&
					pBullet.pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - fLength[1] && pBullet.pos.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + fLength[1])
				{
					if (g_aBlock[nCntBlock].state == BLOCKSTATE_BREAK)
					{//����
						bHit = true;
						g_aBlock[nCntBlock].bUse = false;
						SetExplosion(g_aBlock[nCntBlock].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aBlock[nCntBlock].nLengthX * 2, g_aBlock[nCntBlock].nLengthY * 2, 5, 1, 2, 2, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
					}
					else if (pBullet.state == BULLETSTATE_GRAVITY)
					{//���˂̏ꍇ && �d�͕t���v���[���g�̏ꍇ
						if (g_aBlock[nCntBlock].state == BLOCKSTATE_THIN0 && pBullet.posold.y < g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - fLength[1] && pBullet.pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - fLength[1])
						{//�X�R�A+
							PlaySound(SOUND_LABEL_ATTACK002);
							g_aBlock[nCntBlock].state = BLOCKSTATE_THIN2;
							if (pBullet.nType == 0) { nScore = 3000; }
							if (pBullet.nType == 1) { nScore = 8000; }
							if (pBullet.nType == 2) { nScore = 500; }
							if (pBullet.nType == 3) { nScore = 1200; }
							pPlayer[0].nScore += nScore;
							SetDigital(g_aBlock[nCntBlock].pos - D3DXVECTOR3(0.0f, g_aBlock[nCntBlock].nLengthY * 1.0f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_WAVE, 30, 45, nScore);
							SetExplosion(g_aBlock[nCntBlock].pos - D3DXVECTOR3(0.0f, g_aBlock[nCntBlock].nLengthY * 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
							bHit = true;
						}
					}
					else if(g_aBlock[nCntBlock].state == BLOCKSTATE_THIN0 &&g_aBlock[nCntBlock].state == BLOCKSTATE_THIN1 && g_aBlock[nCntBlock].state == BLOCKSTATE_THIN2){ bHit = true; }
					
				}
			}
		}
	}
	return bHit;
}
//=============================================================================
// �u���b�N�Ƃ̏Փ˔��� �o�O���(�떂����)�p
//=============================================================================
bool SafetynBlock(D3DXVECTOR3 *pPos, int nLengthX, int nLengthY)
{
	int nCntBlock;
	bool bJump;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�S�u���b�N�����
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= 0 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= 0 &&
			g_aBlock[nCntBlock].state != BLOCKSTATE_THIN && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG)
		{//����̂���u���b�N�̂�
			if (pPos[0].x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + nLengthX && pPos[0].x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - nLengthX&&
				pPos[0].y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + nLengthY && pPos[0].y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY)
			{//�|���S���̒��ɓ��荞��ł��܂����ꍇ
				pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY;
				MessageBox(0, "", "", MB_OK);
				bJump = true;
			}
		}

	}

	return bJump;
}
//=============================================================================
// window�j�󏈗�
//=============================================================================
void BreakBlock(void)
{//�S�E�B���h�E�j��
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			g_aBlock[nCntBlock].bUse = false;
		}
	}
}
//=========================================================================================================//
// * ���X�N���[��
//=========================================================================================================//
void WideScroll(void)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntBlock;
	float fPlayerPosx = 1.0f;
	float fPlayerPosy = 0.0f;
	D3DXVECTOR3 move;
	D3DXVECTOR3 data;
	bool PlayerMove = false;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���X�N���[��
	//if (SCREEN_WIDTH * 0.4f > pPlayer[0].pos.x || SCREEN_WIDTH * 0.6f < pPlayer[0].pos.x) { fPlayerPosx = 1.0f; }
	//else if (SCREEN_WIDTH * 0.5f > pPlayer[0].pos.x || SCREEN_WIDTH * 0.5f < pPlayer[0].pos.x) { fPlayerPosx = 0.8f; }
	//else if (SCREEN_WIDTH * 0.6f > pPlayer[0].pos.x || SCREEN_WIDTH * 0.4f < pPlayer[0].pos.x) { fPlayerPosx = 0.5f; }
	//if (SCREEN_WIDTH * 0.4f < pPlayer[0].pos.x && pPlayer[0].nAngle == PLAYERANGLE_RIGHT) { g_ScrollWide -= 0.2f; }
	//if (SCREEN_WIDTH * 0.6f > pPlayer[0].pos.x && pPlayer[0].nAngle == PLAYERANGLE_LEFT) { g_ScrollWide += 0.2f; }

	////�c�X�N���[��
	//	if (SCREEN_HEIGHT * 0.35f < pPlayer[0].pos.y && pPlayer[0].state == PLAYERSTATE_DOWN && pPlayer[0].nCntState[1] > 30) { g_ScrollHeight -= 0.6f; }
	//	else if (SCREEN_HEIGHT * 0.8f < pPlayer[0].pos.y && pPlayer[0].move.y > 0) { fPlayerPosy = 1.0f; }
	//	else if (SCREEN_HEIGHT * 0.7f < pPlayer[0].pos.y && pPlayer[0].move.y > 0) { fPlayerPosy = 0.8f; }
	//	else if (SCREEN_HEIGHT * 0.65f < pPlayer[0].pos.y) { g_ScrollHeight -= 0.5f; }
	//	if (SCREEN_HEIGHT * 0.1f > pPlayer[0].pos.y && pPlayer[0].move.y < 0) { fPlayerPosy = 1.0f; }
	//	else if (SCREEN_HEIGHT * 0.3f > pPlayer[0].pos.y && pPlayer[0].move.y < 0) { fPlayerPosy = 0.8f; }
	//	else if (SCREEN_HEIGHT * 0.45f > pPlayer[0].pos.y && pPlayer[0].state != PLAYERSTATE_DOWN) { g_ScrollHeight += 0.5f; }

	move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�X�N���[��
			g_aBlock[nCntBlock].pos += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f);
			g_aBlock[nCntBlock].posold += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f);

		}
	} 
	BulletScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	ExplosionScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	FontScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	BGScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	AnimationScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	EnemyScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	DigitalScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));

	pPlayer[0].pos += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f);
	pPlayer[0].posold += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight - 1.0f, 0.0f);

	SettingPlayer();
	//pPlayer[0].posold = pPlayer[0].pos;

	g_ScrollWide += (0.0f - g_ScrollWide) * 0.07f;
	g_ScrollHeight += (0.0f - g_ScrollHeight) * 0.2f;

	//���_BUFFER���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	//SettingPlayer();
}
//=========================================================================================================//
// * ���X�N���[��
//=========================================================================================================//
void InitScroll(void)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�X�N���[��
			g_aBlock[nCntBlock].pos -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
			g_aBlock[nCntBlock].posold -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
		}
	}
	pPlayer[0].pos -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
	pPlayer[0].posold -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
	AnimationScroll(pPlayer[0].respawn * -1 + D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f));
	EnemyScroll(pPlayer[0].respawn * -1 + D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f));
	ExplosionScroll(pPlayer[0].respawn * -1 + D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f));
	//fHeight = pPlayer[0].pos.y;
	//if (fHeight > SCREEN_HEIGHT * 0.5f) { fHeight -= SCREEN_HEIGHT * 0.5f; }
	//else if(fHeight < SCREEN_HEIGHT * 0.5f) { fHeight += SCREEN_HEIGHT * 0.5f; }

	//for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
	//	if (g_aBlock[nCntBlock].bUse == true)
	//	{//�X�N���[��
	//		g_aBlock[nCntBlock].pos += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//		g_aBlock[nCntBlock].posold += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//	}
	//}
	//pPlayer[0].pos += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//pPlayer[0].posold += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//AnimationScroll(D3DXVECTOR3(0.0f, fHeight, 0.0f));
	//EnemyScroll(D3DXVECTOR3(0.0f, fHeight, 0.0f));

}
