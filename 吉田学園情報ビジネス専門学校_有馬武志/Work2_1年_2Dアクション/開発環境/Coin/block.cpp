//=========================================================================================================================
//
// �u���b�N���� [block.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "block.h"		//�u���b�N
#include "item.h"		//�A�C�e��
#include "player.h"		//�v���C���[
#include "score.h"		//�X�R�A
#include "sound.h"		//�T�E���h
#include "life.h"		//���C�t

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define BLOCK_TEXTURE_NAME			"data\\TEXTURE\\block000.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME1			"data\\TEXTURE\\block001.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME2			"data\\TEXTURE\\block002.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME3			"data\\TEXTURE\\�x���g�R���x�A�[.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME4			"data\\TEXTURE\\�x���g�R���x�A�[2.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME5			"data\\TEXTURE\\block005.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME6			"data\\TEXTURE\\block004.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME7			"data\\TEXTURE\\block003.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME8			"data\\TEXTURE\\���y����.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME9			"data\\TEXTURE\\����������̃u���b�N.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME10		"data\\TEXTURE\\������.jpg"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME11		"data\\TEXTURE\\����.jpg"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME12		"data\\TEXTURE\\��.jpg"						//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME13		"data\\TEXTURE\\��������.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME14		"data\\TEXTURE\\���������U.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME15		"data\\TEXTURE\\block0031.jpg"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME16		"data\\TEXTURE\\�S�[���h�u���b�N.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME17		"data\\TEXTURE\\����.png"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME18		"data\\TEXTURE\\�A�C�e������.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME19		"data\\TEXTURE\\�������.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME20		"data\\TEXTURE\\�Ƃ�.png"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME21		"data\\TEXTURE\\�Ƃ�����.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME22		"data\\TEXTURE\\�Ƃ�����.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_NAME23		"data\\TEXTURE\\���[������.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define BLOCK_TEXTURE_UV_U			(1.0f)										//�u���b�N�A�j���[�V����U�͈�
#define BLOCK_TEXTURE_UV_V			(1.0f)										//�u���b�N�A�j���[�V����V�͈�
#define MAX_TYPE_BLOCK				(24)										//�u���b�N�̎��
#define MAX_BLOCK_TEX				(24)										//�摜�̖���

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TYPE_BLOCK] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];										//�u���b�N�̏��
int g_nCntBlock = 0;                                            //�u���b�N�J�E���g
int g_nCntBlockt = 0;                                            //�u���b�N�J�E���g
int g_nCount1;
int g_nCount2;

//=========================================================================================================================
// �u���b�N����������
//=========================================================================================================================
void InitBlock(void)
{	
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;	

	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�u���b�N�̏��̏�����
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�����l
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	
		g_aBlock[nCntBlock].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f,0.0f);
		g_aBlock[nCntBlock].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
		g_aBlock[nCntBlock].BlockWidth = 0;
		g_aBlock[nCntBlock].BlockHeight = 0;
	}
	g_nCount1 = 0;
	g_nCount2 = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P����
		pDevice,
		BLOCK_TEXTURE_NAME,
		&g_pTextureBlock[0]		
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q����
		pDevice,
		BLOCK_TEXTURE_NAME1,
		&g_pTextureBlock[1]		
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�R����
		pDevice,
		BLOCK_TEXTURE_NAME2,
		&g_pTextureBlock[2]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�S����
		pDevice,
		BLOCK_TEXTURE_NAME3,
		&g_pTextureBlock[3]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�T����
		pDevice,
		BLOCK_TEXTURE_NAME4,
		&g_pTextureBlock[4]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�U����
		pDevice,
		BLOCK_TEXTURE_NAME5,
		&g_pTextureBlock[5]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�V����
		pDevice,
		BLOCK_TEXTURE_NAME6,
		&g_pTextureBlock[6]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�W����
		pDevice,
		BLOCK_TEXTURE_NAME7,
		&g_pTextureBlock[7]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�X����
		pDevice,
		BLOCK_TEXTURE_NAME8,
		&g_pTextureBlock[8]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�O����
		pDevice,
		BLOCK_TEXTURE_NAME9,
		&g_pTextureBlock[9]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�P����
		pDevice,
		BLOCK_TEXTURE_NAME10,
		&g_pTextureBlock[10]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�Q����
		pDevice,
		BLOCK_TEXTURE_NAME11,
		&g_pTextureBlock[11]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�R����
		pDevice,
		BLOCK_TEXTURE_NAME12,
		&g_pTextureBlock[12]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�S����
		pDevice,
		BLOCK_TEXTURE_NAME13,
		&g_pTextureBlock[13]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�T����
		pDevice,
		BLOCK_TEXTURE_NAME14,
		&g_pTextureBlock[14]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�U����
		pDevice,
		BLOCK_TEXTURE_NAME15,
		&g_pTextureBlock[15]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�V����
		pDevice,
		BLOCK_TEXTURE_NAME16,
		&g_pTextureBlock[16]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�W����
		pDevice,
		BLOCK_TEXTURE_NAME17,
		&g_pTextureBlock[17]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P�X����
		pDevice,
		BLOCK_TEXTURE_NAME18,
		&g_pTextureBlock[18]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q�O����
		pDevice,
		BLOCK_TEXTURE_NAME19,
		&g_pTextureBlock[19]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q�P����
		pDevice,
		BLOCK_TEXTURE_NAME20,
		&g_pTextureBlock[20]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q�Q����
		pDevice,
		BLOCK_TEXTURE_NAME21,
		&g_pTextureBlock[21]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q�R����
		pDevice,
		BLOCK_TEXTURE_NAME22,
		&g_pTextureBlock[22]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�Q�S����
		pDevice,
		BLOCK_TEXTURE_NAME23,
		&g_pTextureBlock[23]
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_BLOCK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;	

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�u���b�N�̏��̏�����
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N���J�E���g
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BLOCK_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BLOCK_TEXTURE_UV_U, BLOCK_TEXTURE_UV_V);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================================
// �u���b�N�I������
//=========================================================================================================================
void UninitBlock(void)
{
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK_TEX; nCntBlock++)
	{//�S�u���b�N�̃J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureBlock[nCntBlock] != NULL)
		{
			g_pTextureBlock[nCntBlock]->Release();
			g_pTextureBlock[nCntBlock] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBlock!= NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock= NULL;
	}
}

//=========================================================================================================================
// �u���b�N�X�V����
//=========================================================================================================================
void UpdateBlock(void)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���[�h�̃|�C���^
	MODE pMode = *GetMode();

	//�v���C���[�̃|�C���^
	Player *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	//�㉺�́A�������ɂ�����Ƃ��ɗ����邩��A�u���b�N�̉ߋ��̈ʒu��pos�ɑ��
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�S�u���b�N�J�E���g
		//���
		g_aBlock[nCntBlock].posold = g_aBlock[nCntBlock].pos;
	}
	//�ړ��n�̏��̐ݒ�
	for(int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�S�u���b�N�̃J�E���g
		//�^�C�v�P
		if (g_aBlock[nCntBlock].nType == 1)
		{//���ɓ����ړ���
			if (g_aBlock[nCntBlock].pos.x >= 810)
			{//���E810�܂ōs������
				//�ړ�                                        ���p�x�@ ���X�s�[�h
				g_aBlock[nCntBlock].move.x += sinf(-D3DX_PI * 0.5f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].pos.x <= 440)
			{//����440�܂ōs������
				//�ړ�                                       ���p�x�@ ���X�s�[�h
				g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].move.x == 0)
			{//�ړ��̃X�^�[�g
				//�ړ�                                       ���p�x�@ ���X�s�[�h
				g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 1.0f;
			}
		}
		//�^�C�v�Q
		if (g_aBlock[nCntBlock].nType == 2)
		{//�c�ɓ����ړ���
			if (g_aBlock[nCntBlock].pos.y <= 200)
			{//��180�܂ōs������
				//�ړ�                                       ���p�x�@ ���X�s�[�h
				g_aBlock[nCntBlock].move.y += cosf(D3DX_PI * 0.0f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].pos.y >= 370)
			{//��480�܂ōs������
				//�ړ�                                       ���p�x�@ ���X�s�[�h
				g_aBlock[nCntBlock].move.y += cosf(D3DX_PI * 1.0f) * 1.0f;
			}
			else if (g_aBlock[nCntBlock].move.y == 0)
			{//�ړ��̃X�^�[�g
				//�ړ�                                       ���p�x�@ ���X�s�[�h
				g_aBlock[nCntBlock].move.y += cosf(D3DX_PI * 0.0f) * 1.0f;
			}
		}
		//�^�C�v�Q�P
		if (g_aBlock[nCntBlock].nType == 21)
		{//���ɓ����ړ���
			g_nCount2++;
			if ((g_nCount2 % 60) == 0)
			{
				if (g_aBlock[nCntBlock].pos.x >= 1040)
				{//���E810�܂ōs������
				 //�ړ�                                        ���p�x�@ ���X�s�[�h
					g_aBlock[nCntBlock].move.x += sinf(-D3DX_PI * 0.5f) * 2.0f;
					g_aBlock[nCntBlock].move.x = 0;
					g_nCount2 = 0;
				}
				else if (g_aBlock[nCntBlock].move.x == 0)
				{//�ړ��̃X�^�[�g
				 //�ړ�                                       ���p�x�@ ���X�s�[�h
					g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 2.0f;
				}
			}
		}
		//�^�C�v�Q�Q
		if (g_aBlock[nCntBlock].nType == 22)
		{//���ɓ����ړ���
			g_nCount1 ++;
			if ((g_nCount1 == 600))
			{
				if (g_aBlock[nCntBlock].pos.x >= 1320)
				{//����440�܂ōs������
				 //�ړ�                                       ���p�x�@ ���X�s�[�h
					g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 2.3f;
					g_aBlock[nCntBlock].move.x = 0;
					g_nCount1 = 0;
				}
				else if (g_aBlock[nCntBlock].move.x == 0)
				{//�ړ��̃X�^�[�g
				 //�ړ�                                       ���p�x�@ ���X�s�[�h
					g_aBlock[nCntBlock].move.x += sinf(D3DX_PI * 0.5f) * 2.0f;
				}
			}
		}
		
		//move��pos�ɑ����
		g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;
		//move��pos�ɑ��y
		g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;

		//���_�J���[�ݒ�
		pVtx[nCntBlock * 4].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		pVtx[nCntBlock * 4 + 1].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		pVtx[nCntBlock * 4 + 2].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		pVtx[nCntBlock * 4 + 3].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
		//���_�ݒ�
		pVtx[nCntBlock * 4].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[nCntBlock * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
		pVtx[nCntBlock * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);
		pVtx[nCntBlock * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);

	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=========================================================================================================================
// �u���b�N�`�揈��
//=========================================================================================================================
void DrawBlock(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;	

	//�u���b�N�J�E���g
	int nCntBlock;					

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffBlock, 
		0, 
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	//�|���S���̕`��
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N���J�E���g
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N������ꍇ
			 //�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}
//=========================================================================================================================
// �u���b�N�̐ݒ菈��
//=========================================================================================================================
void SetBlock(D3DXVECTOR3 pos,D3DXCOLOR col, int nType, float fHeight, float fWidth)
{	
	//�u���b�N�J�E���g
	int nCntBlock;		

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;		

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�u���b�N���J�E���g
		if (g_aBlock[nCntBlock].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_aBlock[nCntBlock].pos = pos;				//pos�l���
			g_aBlock[nCntBlock].col = col;				//�J���[
			g_aBlock[nCntBlock].bUse = true;			//�g�p���Ă����Ԃɂ���
			g_aBlock[nCntBlock].nType = nType;			//�u���b�N�^�Cpu
			g_aBlock[nCntBlock].BlockHeight = fHeight;	//�u���b�N�̍���
			g_aBlock[nCntBlock].BlockWidth = fWidth;	//�u���b�N�̕�
	
			//���_�ݒ�
			pVtx[nCntBlock * 4].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[nCntBlock * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);
			pVtx[nCntBlock * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntBlock * 4].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			pVtx[nCntBlock * 4 + 1].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			pVtx[nCntBlock * 4 + 2].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			pVtx[nCntBlock * 4 + 3].col = D3DXCOLOR(g_aBlock[nCntBlock].col.r, g_aBlock[nCntBlock].col.g, g_aBlock[nCntBlock].col.b, g_aBlock[nCntBlock].col.a);
			break;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
//=========================================================================================================================
// �u���b�N�̂����蔻��
//=========================================================================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove , float *fWidth, float *fHeight)
{	
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;		

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBlock->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	int nCount = 0;

	bool bLand = false;	//���n�������ǂ�

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�S�u���b�N�̃J�E���g                                         ��������/3�����Ȃ��Ƌ󒆕��V����                          ��������/3�����Ȃ��Ƌ󒆕��V����
		if (g_aBlock[nCntBlock].bUse == true && (pPos->x + *fWidth / 3) >= g_aBlock[nCntBlock].pos.x && (pPos->x - *fWidth / 3) <= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth)
		{	//�ォ��������@                      ���u���b�N�̌��݈ʒu
			if (pPosOld->y <= g_aBlock[nCntBlock].posold.y && pPos->y >= g_aBlock[nCntBlock].pos.y)
			{//��̂����蔻��
				bLand = true;
				pPos->y = g_aBlock[nCntBlock].pos.y; //�v���C���[�̈ʒu(����)���X�V

//***************************
//	���낢��v�f�����鏰
//***************************
				//�^�C�v�R�@�E�p�x���g�R���x�A�[
				if (g_aBlock[nCntBlock].nType == 3)
				{//�u���b�N�̏�ɍڂ��Ă���Ƃ�
					//�v���C���[��move�lx��1.5f�ɂ���(�E)
					pMove->x = 1.0f;
				}
				//�^�C�v�S�@���p�x���g�R���x�A�[
				else if (g_aBlock[nCntBlock].nType == 4)
				{//�u���b�N�̏�ɍڂ��Ă���Ƃ�
					//�v���C���[��move�lx��-1.5f�ɂ���(��)
					pMove->x = -1.0f;
				}
				//��������Ȃ������ꍇ
				else
				{//�u���b�N���痎���āA�n�ʂɂ����ꍇ
					 //�v���C���[��move�lx��0�ɂ���
					pMove->x = 0.0f;
				}

				//�^�C�v�U	�����鏰
				if (g_aBlock[nCntBlock].nType == 6)
				{//�u���b�N�̏�ɍڂ��Ă���Ƃ�
					//�����鉹
					PlaySound(SOUND_LABEL_SE_FALL);
					g_aBlock[nCntBlock].move.y = 6.0f;
				}
				if (g_aBlock[nCntBlock].nType == 12)
				{//�u���b�N�̏�ɍڂ��Ă���Ƃ�
					//�Ńu���b�N
						HitPlayer(3);
				}
				if (g_aBlock[nCntBlock].nType == 20)
				{//�u���b�N�̏�ɍڂ��Ă���Ƃ�
				 //�Ƃ�
				 //if (nCount % 240 == 0)
				 //{
						HitPlayer(3);
				 //}
				}
//***************************

				//�v���C���[��move�ly��0�ɂ���
				pMove->y = 0.0f;

				////�u���b�N��move�̒l���v���C���[�ɑ�����A�v���C���[�������Ȃ��悤�ɂ���
				pPos->x += g_aBlock[nCntBlock].move.x;
			}
			//������˂��グ��         �����_���W�𓪂̈ʒu�܂ŏグ��i�������v���C���[�̐g���������������j�@�@�@      �@�@�@�@�@�����������                                                 ���u���b�N�̍����������蔻��
			else if ((pPosOld->y - *fHeight) >= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight) && (pPos->y - *fHeight) <= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight))
			{//���̂����蔻��                                                              ���߂荞�݂������Ԃ�(�v���C���[�̐g����)
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight + *fHeight; //�v���C���[�̈ʒu(����)���X�V

//***************************
//�@���낢��v�f�����鏰
//***************************
				//�^�C�v�T�@�󂹂鏰
				if (g_aBlock[nCntBlock].nType == 5)
				{//�u���b�N�̉����炠�������ꍇ
					//�󂷂Ƃ��̉�
					PlaySound(SOUND_LABEL_SE_BREAK);
					//�u���b�N�̉��ɓ���������AbUse��false�ɂ���
					g_aBlock[nCntBlock].bUse = false;
				}
				//�^�C�v�X�@�����ȃu���b�N
 				if (g_aBlock[nCntBlock].nType == 9)
				{//�u���b�N�̉����炠�������ꍇ
					g_aBlock[nCntBlock].col.a = 1.0f;
					//������
					PlaySound(SOUND_LABEL_SE_FOUND);
					//�u���b�N������������+
					if (g_nCntBlockt == 0)
					{
						//���������P��݂̂ɂ���
						StopSound(SOUND_LABEL_SE_FOUND);

						//�A�C�e���u�����̑܁v
						SetItem(D3DXVECTOR3(60, 660, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5);
					}
					g_nCntBlockt = 1;
					
					//�����u���b�N
					//SetBlock(D3DXVECTOR3(40, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);
					
				}
				if (g_aBlock[nCntBlock].nType == 10)
				{//�u���b�N�̉����炠�������ꍇ
					
				}
//***************************
				//�v���C���[��move�l��0�ɂ���
				pMove->y = 0.0f;
			}
			//������Ԃ���
			else if (pPos->y >= g_aBlock[nCntBlock].pos.y && (pPos->y - *fHeight) <= (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].BlockHeight))
			{//���̓����蔻��
				if (pPosOld->x >= pPos->x)
				{//�E�ǂ̂����蔻��@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ ���߂荞�݂������Ԃ�(�v���C���[�̔����̉�����)
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].BlockWidth + *fWidth / 2; //�v���C���[�̈ʒu(����)���X�V

//****************************
//	���낢��v�f�����鏰
//****************************
					//�^�C�v�P�S�@�������Ƃ��ł��鏰
					if (g_aBlock[nCntBlock].nType == 14)
					{//�u���b�N���E���牟���Ă���Ƃ�
						//�����Ă鉹
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x += 2;
					}
					//�^�C�v�P�T�@�������Ƃ��ł��鏰
					if (g_aBlock[nCntBlock].nType == 15)
					{//�u���b�N���E���牟���Ă���Ƃ�
					 //�����Ă鉹
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x -= 2;
					}
					if (g_aBlock[nCntBlock].nType == 21)
					{
						HitPlayer(3);
					}
					if (g_aBlock[nCntBlock].nType == 22)
					{
						HitPlayer(3);
					}
//****************************
					//�v���C���[��move�l��0�ɂ���
					pMove->x = 0.0f;
				}
				else if (pPosOld->x < pPos->x)
				{//���ǂ̂����蔻��@�@�@�@�@�@�@�@�@�@�@�@�@�@�@  ���߂荞�݂������Ԃ�(�v���C���[�̔����̉�����)
					pPos->x = g_aBlock[nCntBlock].pos.x - *fWidth / 2;	//�v���C���[�̈ʒu(����)���X�V

//*****************************
// ���낢��v�f�����鏰
//*****************************
					//�^�C�v�V	�������Ƃ��ł��鏰
					if (g_aBlock[nCntBlock].nType == 7)
					{//�u���b�N�������牟���Ă���Ƃ�
						//�����Ă鎞�̉�
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x += 2;
					}
					//�^�C�v�P�S�@�������Ƃ��ł���U��
					if (g_aBlock[nCntBlock].nType == 14)
					{//�u���b�N���E���牟���Ă���Ƃ�
					 //�����Ă鉹
						PlaySound(SOUND_LABEL_SE_PRESS);
						g_aBlock[nCntBlock].pos.x -= 2;
					}
//******************************
					//�v���C���[��move�l��0�ɂ���
					pMove->x = 0.0f;
				}
			}
		}
	}
	return bLand;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
//=========================================================================================================================
// �u���b�N�̎擾����
//=========================================================================================================================
Block *GetBlock(void)
{
	return &g_aBlock[0];
}
//==========================================================================================================================
//�u���b�N�̏�����
//==========================================================================================================================
void DeleteBlock(void)
{
	//�u���b�N�̏��̏�����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//�����l
		if (g_aBlock[nCntBlock].bUse == true)
		{//true��������
			g_aBlock[nCntBlock].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
			g_aBlock[nCntBlock].posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aBlock[nCntBlock].bUse = false;
			g_aBlock[nCntBlock].nType = 0;
			g_aBlock[nCntBlock].BlockWidth = 0;
			g_aBlock[nCntBlock].BlockHeight = 0;
		}
	}
}