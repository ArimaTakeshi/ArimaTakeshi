//=========================================================================================================//
//
// [�e����]->�e�ړ�:�������� [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "sound.h"
#include <stdlib.h>				//�����h�p
#include <time.h>				//�����������h�p

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define EXPLOSION_VERTEX_NUM		(4)					// ���_�̐�
#define EXPLOSION_PRIMITIVE_NUM		(2)					// �v���~�e�B�u�̐�
#define EXPLOSION_MAX_TEX			(10)
#define EXPLOSION_TextureName		"data/TEXTURE/coin000.png"
#define EXPLOSION_TextureName1		"data/TEXTURE/icon000.png"
#define EXPLOSION_TextureName2		"data/TEXTURE/checkpoint000.png"
#define EXPLOSION_TextureName3		"data/TEXTURE/checkpoint001.png"
#define EXPLOSION_TextureName4		"data/TEXTURE/heart000.png"
#define EXPLOSION_TextureName5		"data/TEXTURE/food000.png"
#define EXPLOSION_TextureName6		"data/TEXTURE/food001.png"
#define EXPLOSION_TextureName7		"data/TEXTURE/food002.png"
#define EXPLOSION_TextureName8		"data/TEXTURE/food003.png"
#define EXPLOSION_TextureName9		"data/TEXTURE/Clock000.png"
#define	MAX_EXPLOSION				(64)		// �e�̍ő吔
#define HALFEXPLOSION				(30)

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9			g_pTextureAnimation[EXPLOSION_MAX_TEX] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffAnimation = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
Animation					g_aAnimation[MAX_EXPLOSION];					//�ő��Animation��

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitAnimation(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBullet;

	// �e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//g_aExplosion[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aExplosion[nCntBullet].col = { 1.0f, 1.0f, 1.0f, };
		//g_aExplosion[nCntBullet].nCntAnim = -1;
		//g_aExplosion[nCntBullet].nPtnAnim = -1;
		//g_aExplosion[nCntBullet].nType = 0;
		g_aAnimation[nCntBullet].bUse = false;
	}

	//TEXTURE�ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName, &g_pTextureAnimation[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName1, &g_pTextureAnimation[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName2, &g_pTextureAnimation[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName3, &g_pTextureAnimation[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName4, &g_pTextureAnimation[4]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName5, &g_pTextureAnimation[5]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName6, &g_pTextureAnimation[6]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName7, &g_pTextureAnimation[7]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName8, &g_pTextureAnimation[8]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName9, &g_pTextureAnimation[9]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * EXPLOSION_VERTEX_NUM * MAX_EXPLOSION,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffAnimation,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//���_���W�̐ݒ�
		//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

		pVtx[nCntBullet * 4].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 1].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 2].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 3].rhw = 1.0f;

		////�J���[�ݒ�
		//pVtx[nCntBullet * 4].col = D3DCOLOR_RGBA(0,0,0, 255);	// A = �����x
		//pVtx[nCntBullet * 4 + 1].col = D3DCOLOR_RGBA(0,0,0, 255);
		//pVtx[nCntBullet * 4 + 2].col = D3DCOLOR_RGBA(0,0,0, 255);
		//pVtx[nCntBullet * 4 + 3].col = D3DCOLOR_RGBA(0,0,0, 255);

		//�e�N�X�`�����W�ݒ�
		//pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffAnimation->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitAnimation(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	BreakAnimation();
	for (nCntTexture = 0; nCntTexture < EXPLOSION_MAX_TEX; nCntTexture++)
	{
		if (g_pTextureAnimation[nCntTexture] != NULL)
		{
			g_pTextureAnimation[nCntTexture]->Release();
			g_pTextureAnimation[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffAnimation != NULL)
	{
		g_pVtxBuffAnimation->Release();
		g_pVtxBuffAnimation = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateAnimation(void)
{
	int nCntBullet;
	float fRand = (rand() % 628) * 0.01f;
	int nRand = rand() % 10 + 55;
	static int nVibration = 0;
	PLAYER *pPlayer = GetPlayer();
	nVibration++;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{

		if (g_aAnimation[nCntBullet].bUse == true)
		{//�e��O�ɔ�΂�
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_CHECK0 && g_aAnimation[nCntBullet].pos.x + g_aAnimation[nCntBullet].nLengthX > pPlayer[0].pos.x && g_aAnimation[nCntBullet].pos.x - g_aAnimation[nCntBullet].nLengthX < pPlayer[0].pos.x &&
				g_aAnimation[nCntBullet].pos.y + g_aAnimation[nCntBullet].nLengthY > pPlayer[0].pos.y && g_aAnimation[nCntBullet].pos.y - g_aAnimation[nCntBullet].nLengthY < pPlayer[0].pos.y)
			{
				pPlayer[0].respawn = g_aAnimation[nCntBullet].initpos;
				g_aAnimation[nCntBullet].nType = 3;
				g_aAnimation[nCntBullet].type = ANIMTYPE_CHECK1;
				for (int nCntChack = 0; nCntChack < MAX_EXPLOSION; nCntChack++)
				{
					if (g_aAnimation[nCntChack].bUse == true && g_aAnimation[nCntChack].type == ANIMTYPE_CHECK0 && g_aAnimation[nCntChack].nCntState < g_aAnimation[nCntBullet].nCntState)
					{//�O�̃`�F�b�N�|�C���g���g�p�ς݂�
						g_aAnimation[nCntChack].type = ANIMTYPE_CHECK1;
						g_aAnimation[nCntChack].nType = 3;
					}
				}
			}
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_CLOCK && pPlayer[0].bClock[g_aAnimation[nCntBullet].nCntState] == true) { g_aAnimation[nCntBullet].bUse = false; }
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_POWERUP && pPlayer[0].bPowerUP[g_aAnimation[nCntBullet].nCntState] == true) { g_aAnimation[nCntBullet].bUse = false; }
		 //MessageBox(0, "�{�������H", "�I��", MB_YESNO);
			g_aAnimation[nCntBullet].posold = g_aAnimation[nCntBullet].pos;
			g_aAnimation[nCntBullet].nCntAnim++;

			if(g_aAnimation[nCntBullet].type == ANIMTYPE_NONE)
			{ 
				g_aAnimation[nCntBullet].nPtnAnim = pPlayer[0].nPtnAnim;
				g_aAnimation[nCntBullet].nCntState = pPlayer[0].nVibration;

				if (pPlayer[0].nVibration > 0)
				{//�w�肳�ꂽ���ԓ��葱����
					if (nVibration % 2 == 0) { g_aAnimation[nCntBullet].pos += D3DXVECTOR3(sinf(fRand) * 10, cosf(fRand) * 10, 0.0f); }
					else if (nVibration % 2 == 1) { g_aAnimation[nCntBullet].pos = g_aAnimation[nCntBullet].initpos; }
				}//�����ʒu�ɖ߂�
				else if (pPlayer[0].nVibration == 0) { g_aAnimation[nCntBullet].pos = g_aAnimation[nCntBullet].initpos; }
			}
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_NONE &&g_aAnimation[nCntBullet].nPtnAnim > 3) { g_aAnimation[nCntBullet].nPtnAnim -= 2; }

			if (g_aAnimation[nCntBullet].nCntAnim % g_aAnimation[nCntBullet].nPtnSpeed == 0 && g_aAnimation[nCntBullet].type != ANIMTYPE_NONE)
			{
				g_aAnimation[nCntBullet].nPtnAnim++;
				if (g_aAnimation[nCntBullet].nPtnAnim > g_aAnimation[nCntBullet].nPtnHeight * g_aAnimation[nCntBullet].nPtnWide && g_aAnimation[nCntBullet].anim != ANIMATION_LOOP)
				{//�S��1��\�������������
					g_aAnimation[nCntBullet].bUse = false;
				}
			}
		}
	}

}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawAnimation(ANIMTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffAnimation, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0 && g_aAnimation[nCntItem].type != ANIMTYPE_NONE && type != ANIMTYPE_NONE)
		{// �e�N�X�`���̐ݒ� �|���S���̕`�� �u���ȊO
			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);

			pVtx[nCntItem * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = �����x
			pVtx[nCntItem * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[nCntItem * 4].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));

			pDevice->SetTexture(0, g_pTextureAnimation[g_aAnimation[nCntItem].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, EXPLOSION_PRIMITIVE_NUM);
		}
		else if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0 && g_aAnimation[nCntItem].type == ANIMTYPE_NONE && type == ANIMTYPE_NONE)
		{//�u�������\�����Ȃ�
			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);

			pVtx[nCntItem * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = �����x
			pVtx[nCntItem * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[nCntItem * 4].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));

			pDevice->SetTexture(0, g_pTextureAnimation[g_aAnimation[nCntItem].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, EXPLOSION_PRIMITIVE_NUM);

		}
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffAnimation->Unlock();
}
//============================================================================= 
// �e�̐ݒ菈��
//=============================================================================
void SetAnimation(D3DXVECTOR3 pos, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nCntState, ANIMATION anim, ANIMTYPE type)
{
	int nCntBullet;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aAnimation[nCntBullet].bUse == false)
		{
			g_aAnimation[nCntBullet].pos = pos;
			g_aAnimation[nCntBullet].initpos = pos;
			g_aAnimation[nCntBullet].nCntAnim = -1;
			g_aAnimation[nCntBullet].nPtnAnim = -1;
			g_aAnimation[nCntBullet].nPtnHeight = nPtnHeight;
			g_aAnimation[nCntBullet].nPtnWide = nPtnWide;
			g_aAnimation[nCntBullet].nPtnSpeed = nPtnSpeed;
			g_aAnimation[nCntBullet].nLengthX = nLengthX;
			g_aAnimation[nCntBullet].nLengthY = nLengthY;
			g_aAnimation[nCntBullet].nType = nType;
			g_aAnimation[nCntBullet].anim = anim;
			g_aAnimation[nCntBullet].type = type;
			g_aAnimation[nCntBullet].nCntState = nCntState;
			g_aAnimation[nCntBullet].bUse = true;

			if (g_aAnimation[nCntBullet].type == ANIMTYPE_COIN)
			{
				g_aAnimation[nCntBullet].nLengthX = nLengthX;
				g_aAnimation[nCntBullet].nLengthY = nLengthY;
				g_aAnimation[nCntBullet].nPtnSpeed = 20;
			}

			break;
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffAnimation->Unlock();
}
//=========================================================================================================//
// * �SAnimation�j������
//=========================================================================================================//
void BreakAnimation(void)
{
	int nCntAnim;

	for (nCntAnim = 0; nCntAnim < MAX_EXPLOSION; nCntAnim++)
	{
		g_aAnimation[nCntAnim].bUse = false;
	}
}
//=============================================================================
// �u���b�N�Ƃ̏Փ˔���
//=============================================================================
void HitItem(int nCntItem)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntChack;

	switch (g_aAnimation[nCntItem].type)
	{
	case ANIMTYPE_COIN:
		g_aAnimation[nCntItem].bUse = false;
		PlaySound(SOUND_LABEL_COIN);
		pPlayer[0].nScore += 100;
		SetDigital(g_aAnimation[nCntItem].pos, D3DXCOLOR(0.4f, 0.98f, 1.0f, 0.0f), DIGITALSTATE_WAVE, 9, 15, 100);
		break;
	case ANIMTYPE_CHECK0:
		pPlayer[0].respawn = g_aAnimation[nCntItem].initpos;
		g_aAnimation[nCntItem].nType = 3;
		g_aAnimation[nCntItem].type = ANIMTYPE_CHECK1;
		for (nCntChack = 0; nCntChack < MAX_EXPLOSION; nCntChack++)
		{
			if (g_aAnimation[nCntChack].bUse == true && g_aAnimation[nCntChack].type == ANIMTYPE_CHECK0 && g_aAnimation[nCntChack].nCntState < g_aAnimation[nCntItem].nCntState)
			{//�O�̃`�F�b�N�|�C���g���g�p�ς݂�
				g_aAnimation[nCntChack].type = ANIMTYPE_CHECK1;
				g_aAnimation[nCntChack].nType = 3;
			}
		}
	case ANIMTYPE_CHECK1:
		if (pPlayer[0].nLife > 0)
		{
			SetExplosion(g_aAnimation[nCntItem].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			PlaySound(SOUND_LABEL_CHECKPOINT);
			pPlayer[0].nEXPold = pPlayer[0].nEXP;
			pPlayer[0].nMAXEXPold = pPlayer[0].nMAXEXP;
			pPlayer[0].nLevelold = pPlayer[0].nLevel;
			pPlayer[0].nLifeold = pPlayer[0].nLife;
			for (int nCount = 0; nCount < 10; nCount++) { pPlayer[0].bPowerUPold[nCount] = pPlayer[0].bPowerUP[nCount]; }
			for (int nCount = 0; nCount < 10; nCount++) { pPlayer[0].bClockold[nCount] = pPlayer[0].bClock[nCount]; }
		}
		break;
	case ANIMTYPE_POWERUP:
		PlaySound(SOUND_LABEL_HEEL);
		SetExplosion(g_aAnimation[nCntItem].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100,100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		SetDigital(D3DXVECTOR3(600, SCREEN_HEIGHT * 1.1f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_HEEL, 30, 45, 1000);
		pPlayer[0].nLife += 1000;
		pPlayer[0].nMaxLife += 1000;
		pPlayer[0].bPowerUP[g_aAnimation[nCntItem].nCntState] = true;
		g_aAnimation[nCntItem].bUse = false;
		break;
	case ANIMTYPE_ALLHEEL:
		PlaySound(SOUND_LABEL_HEEL);
		SetDigital(D3DXVECTOR3(600, SCREEN_HEIGHT * 1.1f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_HEEL, 30, 45, pPlayer[0].nMaxLife);
		g_aAnimation[nCntItem].bUse = false;
		pPlayer[0].nLife = pPlayer[0].nMaxLife;
		break;
	case ANIMTYPE_HEEL:
		PlaySound(SOUND_LABEL_HEEL);
		SetDigital(D3DXVECTOR3(600, SCREEN_HEIGHT * 1.1f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_HEEL, 30, 45, g_aAnimation[nCntItem].nCntState);
		pPlayer[0].nLife += g_aAnimation[nCntItem].nCntState;
		if (pPlayer[0].nLife > pPlayer[0].nMaxLife) { pPlayer[0].nLife = pPlayer[0].nMaxLife; }
		g_aAnimation[nCntItem].bUse = false;
		break;
	case ANIMTYPE_CLOCK:
		PlaySound(SOUND_LABEL_HEEL);
		pPlayer[0].nTime[0] += 1200;
		SetExplosion(g_aAnimation[nCntItem].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		pPlayer[0].bClock[g_aAnimation[nCntItem].nCntState] = true;
		g_aAnimation[nCntItem].bUse = false;
		break;
	}
}
//=============================================================================
// �u���b�N�Ƃ̏Փ˔���
//=============================================================================
void CollisionItem(void)
{
	int nCntItem;
	int nLength;
	PLAYER *pPlayer = GetPlayer();

	if (g_aAnimation[0].nCntAnim > 30)
	{
		for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
		{//�㉺�̔���
			if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0)
			{//�g���Ă���u���b�N && ����t���̃u���b�N�Ȃ�
				if (g_aAnimation[nCntItem].posold.y - g_aAnimation[nCntItem].nLengthY >= pPlayer[0].posold.y + PLAYER_CollisionY && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= pPlayer[0].pos.y + PLAYER_CollisionY)
				{//�O�񂪏�&&�����
					nLength = (int)pPlayer[0].pos.x - (int)g_aAnimation[nCntItem].pos.x;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionX;
					if (nLength <= g_aAnimation[nCntItem].nLengthX)
					{
						HitItem(nCntItem);
					}
				}
				else if (g_aAnimation[nCntItem].posold.y + g_aAnimation[nCntItem].nLengthY <= pPlayer[0].posold.y - PLAYER_CollisionY && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= pPlayer[0].pos.y - PLAYER_CollisionY)
				{//�O�񂪉�&&���艺 
					nLength = (int)pPlayer[0].pos.x - (int)g_aAnimation[nCntItem].pos.x;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionX;
					if (nLength <= g_aAnimation[nCntItem].nLengthX)
					{
						HitItem(nCntItem);
					}
				}
			}
		}

		for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
		{//�E���̔���
			if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0)
			{//�g���Ă���u���b�N && ����t���̃u���b�N�Ȃ�
				if (g_aAnimation[nCntItem].posold.x + g_aAnimation[nCntItem].nLengthX <= pPlayer[0].posold.x - PLAYER_CollisionX && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= pPlayer[0].pos.x - PLAYER_CollisionX)
				{//�O�񂪉E&&����E
					nLength = (int)pPlayer[0].pos.y - (int)g_aAnimation[nCntItem].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionY;
					if (nLength < g_aAnimation[nCntItem].nLengthY)
					{//���������I
						HitItem(nCntItem);
					}
				}
				if (g_aAnimation[nCntItem].posold.x - g_aAnimation[nCntItem].nLengthX >= pPlayer[0].posold.x + PLAYER_CollisionX && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= pPlayer[0].pos.x + PLAYER_CollisionX)
				{//�O�񂪍�&&���荶
					nLength = (int)pPlayer[0].pos.y - (int)g_aAnimation[nCntItem].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionY;
					if (nLength < g_aAnimation[nCntItem].nLengthY)
					{//���������I
						HitItem(nCntItem);
					}
				}
			}
		}
	}
}
//=========================================================================================================//
// * �SAnimation�X�N���[������
//=========================================================================================================//
void AnimationScroll(D3DXVECTOR3 move)
{
	int nCntItem;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].type != ANIMTYPE_NONE)
		{//�X�N���[��
			g_aAnimation[nCntItem].pos += move;
			g_aAnimation[nCntItem].posold += move;

			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);

		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffAnimation->Unlock();
}

//=========================================================================================================//
// * �SAnimation�j������
//=========================================================================================================//
Animation *GetAnimation(void)
{
	return &g_aAnimation[0];
}

