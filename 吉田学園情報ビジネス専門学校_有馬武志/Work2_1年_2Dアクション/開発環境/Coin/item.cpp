//=========================================================================================================================
//
// �A�C�e������ [items.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "item.h"		//�A�C�e��
#include "score.h"		//�X�R�A
#include "player.h"		//�v���C���[
#include "fade.h"		//�t�F�[�h
#include "itemcount.h"	//�A�C�e���J�E���g
#include "time.h"		//�^�C��
#include "sound.h"		//�T�E���h
#include "Game.h"		//�Q�[��
#include "player.h"		//�v���C���[
#include "life.h"		//���C�t
#include "explosion.h"	//����
#include "input.h"		//�L�[�{�[�h
#include "Game.h"		//�Q�[��

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_ITEM					(256)								//�A�C�e���̍ő吔
#define MAX_ITEM_TYPE				(10)								//�^�C�v�̎��
#define ITEM_TEXTURE_NAME			"data\\TEXTURE\\coin001.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME1			"data\\TEXTURE\\����.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME2			"data\\TEXTURE\\���v1.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME3			"data\\TEXTURE\\�󂢂���.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME4			"data\\TEXTURE\\�����̑�.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME5			"data\\TEXTURE\\�g�t���R�C��.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME6			"data\\TEXTURE\\���t����.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME7			"data\\TEXTURE\\�Q�[�g2.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_TEXTURE_NAME8			"data\\TEXTURE\\SHOP.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define ITEM_COIN_WID				(20)								//�R�C���̕�
#define ITEM_COIN_HEI				(35)								//�R�C���̍���
#define ITEM_MAGNET_WID				(25)								//���΂̕�
#define ITEM_MAGNET_HEI				(25)								//���΂̕�
#define ITEM_GATE_WID				(30)								//�Q�[�g�̕�
#define ITEM_GATE_HEI				(50)								//�Q�[�g�̍���
#define ITEM_SHOP_WID				(100)								//�V���b�v�̕�
#define ITEM_SHOP_HEI				(100)								//�V���b�v�̍���
#define ITEM_TIME_WID				(30)								//�^�C���̕�
#define ITEM_TIME_HEI				(30)								//�^�C���̕�
#define ITEM_TEXTURE_SPEED			(10)								//�e�N�X�`���A�j���[�V�����X�s�[�h
#define ITEM_TEXTURE_SPEED1			(20)								//�e�N�X�`���A�j���[�V�����X�s�[�h
#define ITEM_TEXTURE_SPEED2			(40)								//�e�N�X�`���A�j���[�V�����X�s�[�h
#define ITEM_TEXTURE_PATTERN		(4)									//�e�N�X�`���A�j���[�V�����p�^�[����
#define ITEM_TEXTURE_UV_U			(0.25f)								//�e�N�X�`���A�j���[�V����U�͈�
#define ITEM_TEXTURE_UV_V			(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�
#define ITEM_TEXTURE_UV_U1			(1.0f)								//�e�N�X�`���A�j���[�V����U�͈�
#define ITEM_TEXTURE_UV_V1			(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_ITEM_TYPE] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;				//���_�o�b�t�@�ւ̃|�C���^
Item					g_aItem[MAX_ITEM];					//�A�C�e���̏��
int						g_NumItem;							//�i���J�E���g�p

//=========================================================================================================================
// �A�C�e������������
//=========================================================================================================================
void InitItem(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;	

	//�A�C�e���J�E���g
	int nCntItem;					
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�A�C�e���̏��̏�����
	for(nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].fHeight = 0;
		g_aItem[nCntItem].fWidth = 0;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatteunAnim = 0;
		g_aItem[nCntItem].ItemState = ITEM_STATE_APPER;
		g_aItem[nCntItem].bUse = false;
		g_NumItem = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//1���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME,
		&g_pTextureItem[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//2���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME1,
		&g_pTextureItem[1]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//3���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME,
		&g_pTextureItem[2]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//4���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME2,
		&g_pTextureItem[3]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//5���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME3,
		&g_pTextureItem[4]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//6���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME4,
		&g_pTextureItem[5]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//7���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME5,
		&g_pTextureItem[6]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//8���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME6,
		&g_pTextureItem[7]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//9���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME7,
		&g_pTextureItem[8]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//10���ڂ̉摜
		pDevice,
		ITEM_TEXTURE_NAME8,
		&g_pTextureItem[9]
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL
	);

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;	

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�A�C�e���̏��̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g

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
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 0.0f);
		

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================================
// �A�C�e���I������
//=========================================================================================================================
void UninitItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM_TYPE; nCntItem++)
	{//�A�C�e�����J�E���g
		//�e�N�X�`���[�̔j��
		if (g_pTextureItem[nCntItem] != NULL)
		{
			g_pTextureItem[nCntItem] ->Release();
			g_pTextureItem[nCntItem] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem ->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=========================================================================================================================
// �A�C�e���X�V����
//=========================================================================================================================
void UpdateItem(void)
{
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;	

	//�A�C�e���J�E���g
	int nCntItem;
	//�J�E���g�Ə�����
	int nCount = 0;

	//�v���C���[�̃|�C���^
	Player *pPlayer;
	pPlayer = GetPlayer();//�|�C���^�[�̎g�������Ԉ���Ă����̂ŁA�C���B�@pPlayer�̂܂��Ɂ�������

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g
		if (g_aItem[nCntItem].bUse == true)
		{//�A�C�e�����g�p����Ă���ꍇ

			switch (g_aItem[nCntItem].ItemState)
			{
			case ITEM_STATE_APPER:
				break;
			case ITEM_STATE_NORMAL:
				//�^�C�v�O====================================================================================
				if (g_aItem[nCntItem].nType == 0)
				{//�^�C�v�O�@���ʂ̃R�C��
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0 && g_aItem[nCntItem].nType == 0)
					{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//�p�^�[��No.�X�V
						//���_�ݒ�
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						//���_�J���[�ݒ�
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//�e�N�X�`���ݒ�
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				/*	case ITEM_MAGNET:*/
				//�^�C�v�P====================================================================================
				if (g_aItem[nCntItem].nType == 1)
				{//�^�C�v�P�@����
				 //���_�ݒ�
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					//���_�J���[�ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//�e�N�X�`���ݒ�
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);

				}
				//�^�C�v�Q====================================================================================
				if (g_aItem[nCntItem].nType == 2)
				{//�^�C�v�Q�@�ԃR�C��
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0 && g_aItem[nCntItem].nType == 2)
					{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//�p�^�[��No.�X�V

																															//���_�ݒ�
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						//���_�J���[�ݒ�
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//�e�N�X�`���ݒ�
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);

					}
				}
				//�^�C�v�R====================================================================================
				if (g_aItem[nCntItem].nType == 3)
				{//�^�C�v�R�@���v
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED1) == 0 && g_aItem[nCntItem].nType == 3)
					{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//�p�^�[��No.�X�V
																															//���_�ݒ�
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						//���_�J���[�ݒ�
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//�e�N�X�`���ݒ�
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				//�^�C�v�S====================================================================================
				if (g_aItem[nCntItem].nType == 4)
				{//�^�C�v4   ��
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED2) == 0 && g_aItem[nCntItem].nType == 4)
					{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % 2;		//�p�^�[��No.�X�V
																										//���_�ݒ�
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
						//���_�J���[�ݒ�
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//�e�N�X�`���ݒ�
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim + 0.5f, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(0.5f * g_aItem[nCntItem].nPatteunAnim + 0.5f, ITEM_TEXTURE_UV_V);
					}
					if (pPlayer->pos.y - pPlayer->PlayerHeight < g_aItem[nCntItem].pos.y && pPlayer->pos.y + pPlayer->PlayerHeight > g_aItem[nCntItem].pos.y && pPlayer->pos.x + pPlayer->PlayerWidth > g_aItem[nCntItem].pos.x && pPlayer->pos.x - pPlayer->PlayerWidth < g_aItem[nCntItem].pos.x)
					{//�󔠂��Ƃ�����̂����蔻��
					 //�󔠂��Ƃ�����false�ɂ���
						g_aItem[nCntItem].bUse = false;		//�g�p���Ă��Ȃ����
					}
				}
				//�^�C�v�T====================================================================================
				if (g_aItem[nCntItem].nType == 5)
				{//�^�C�v5�@�����̑�
				 //���_�ݒ�
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					//���_�J���[�ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//�e�N�X�`���ݒ�
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);
				}
				//�^�C�v�U====================================================================================
				if (g_aItem[nCntItem].nType == 6)
				{//�^�C�v�V�@�͌^�̃R�C��
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED1) == 0 && g_aItem[nCntItem].nType == 6)
					{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//�p�^�[��No.�X�V
																															//���_�ݒ�
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y - ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_COIN_WID, g_aItem[nCntItem].pos.y + ITEM_COIN_HEI, 0.0f);
						//���_�J���[�ݒ�
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//�e�N�X�`���ݒ�
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				//�^�C�v�V====================================================================================
				if (g_aItem[nCntItem].nType == 7)
				{//�^�C�v�V�@���t����
				 //���_�ݒ�
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y - ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_MAGNET_WID, g_aItem[nCntItem].pos.y + ITEM_MAGNET_HEI, 0.0f);
					//���_�J���[�ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//�e�N�X�`���ݒ�
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);
				}
				//�^�C�v�W====================================================================================
				if (g_aItem[nCntItem].nType == 8)
				{//�^�C�v�W�@
				 //���_�ݒ�
					if ((g_aItem[nCntItem].nCounterAnim % ITEM_TEXTURE_SPEED) == 0 && g_aItem[nCntItem].nType == 8)
					{//�A�j���[�V�������x                                                  ���p�^�[�����P�Âi��ł�����(�Q�ɂ���ƂQ���i��)
						g_aItem[nCntItem].nPatteunAnim = (g_aItem[nCntItem].nPatteunAnim + 1) % ITEM_TEXTURE_PATTERN;		//�p�^�[��No.�X�V
																															//���_�ݒ�
						pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_GATE_WID, g_aItem[nCntItem].pos.y - ITEM_GATE_HEI, 0.0f);
						pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_GATE_WID, g_aItem[nCntItem].pos.y - ITEM_GATE_HEI, 0.0f);
						pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_GATE_WID, g_aItem[nCntItem].pos.y + ITEM_GATE_HEI, 0.0f);
						pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_GATE_WID, g_aItem[nCntItem].pos.y + ITEM_GATE_HEI, 0.0f);
						//���_�J���[�ݒ�
						pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						//�e�N�X�`���ݒ�
						pVtx[nCntItem * 4].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, 0.0f);
						pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, 0.0f);
						pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim, ITEM_TEXTURE_UV_V);
						pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U * g_aItem[nCntItem].nPatteunAnim + ITEM_TEXTURE_UV_U, ITEM_TEXTURE_UV_V);
					}
				}
				//�^�C�v�X====================================================================================
				if (g_aItem[nCntItem].nType == 9)
				{//�^�C�v9�@SHOP
					//���_�ݒ�
					pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_SHOP_WID, g_aItem[nCntItem].pos.y - ITEM_SHOP_HEI, 0.0f);
					pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_SHOP_WID, g_aItem[nCntItem].pos.y - ITEM_SHOP_HEI, 0.0f);
					pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_SHOP_WID, g_aItem[nCntItem].pos.y + ITEM_SHOP_HEI, 0.0f);
					pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_SHOP_WID, g_aItem[nCntItem].pos.y + ITEM_SHOP_HEI, 0.0f);
					//���_�J���[�ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					//�e�N�X�`���ݒ�
					pVtx[nCntItem * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, 0.0f);
					pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2(0.0f, ITEM_TEXTURE_UV_V1);
					pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2(ITEM_TEXTURE_UV_U1, ITEM_TEXTURE_UV_V1);
				}
				break;
			case ITEM_STATE_DELETE:			
				break;
			}
			//�J�E���^�[���Z
			g_aItem[nCntItem].nCounterAnim++;
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}

//=========================================================================================================================
// �A�C�e���`�揈��
//=========================================================================================================================
void DrawItem(void)
{	
	//�f�o�C�X�|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�A�C�e���J�E���g
	int nCntItem;				

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffItem,
		0, 
		sizeof(VERTEX_2D)
	);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(nCntItem = 0; nCntItem< MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g

		if (g_aItem[nCntItem].bUse == true)
		{//�A�C�e��������ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);
		
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}

//=========================================================================================================================
// �A�C�e���̐ݒ菈��
//=========================================================================================================================
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col, int nType)
{
	//�A�C�e���J�E���g
	int nCntItem;			

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;			

	//���_�o�b�t�@�����b�N
	g_pVtxBuffItem->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntItem = 0; nCntItem< MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g
		if (g_aItem[nCntItem].bUse == false)
		{//�A�C�e�����g�p����Ă��Ȃ�
			g_aItem[nCntItem].pos = pos;		//pos�l���
			g_aItem[nCntItem].col = col;		//move�l���
			g_aItem[nCntItem].nCounterAnim = 0;	//�J�E���^�[�����l�ݒ�
			g_aItem[nCntItem].nPatteunAnim = 0;	//�p�^�[��No.�����l�ݒ�
			g_aItem[nCntItem].ItemState = ITEM_STATE_NORMAL;
			g_aItem[nCntItem].nType = nType;	//�^�C�v
			g_aItem[nCntItem].bUse = true;		//�g�p���Ă����Ԃɂ���

			//���_�J���[�ݒ�
			pVtx[nCntItem * 4].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);
			pVtx[nCntItem * 4 + 1].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);
			pVtx[nCntItem * 4 + 2].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);
			pVtx[nCntItem * 4 + 3].col = D3DXCOLOR(g_aItem[nCntItem].col.r, g_aItem[nCntItem].col.g, g_aItem[nCntItem].col.b, g_aItem[nCntItem].col.a);

			if (g_aItem[nCntItem].nType != 8 && g_aItem[nCntItem].nType != 9)
			{
				g_aItem[nCntItem].fHeight = ITEM_COIN_HEI;
				g_aItem[nCntItem].fWidth = ITEM_COIN_WID;
				if (g_aItem[nCntItem].nType == 0)
				{//���ʂ̃R�C��
					//����
					//SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					g_NumItem++;
				}
				if (g_aItem[nCntItem].nType == 2)
				{//�Ԃ��R�C��
					
					g_NumItem++;
				}
			}
			if (g_aItem[nCntItem].nType == 8)
			{
				g_aItem[nCntItem].fHeight = ITEM_GATE_HEI;
				g_aItem[nCntItem].fWidth = ITEM_GATE_WID;
			}
			else if (g_aItem[nCntItem].nType == 9)
			{
				g_aItem[nCntItem].fHeight = ITEM_SHOP_HEI;
				g_aItem[nCntItem].fWidth = ITEM_SHOP_WID;
			}
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffItem->Unlock();
}
//=========================================================================================================================
// �����A�C�e��
//=========================================================================================================================
void DeleteItem(int nCntItem)
{
	//�ϐ��錾
	int nCount = 0;

	//�v���C���[�̃|�C���^
	Player *pPlayer = GetPlayer();

	//�^�C�}�[�̃|�C���^
	Time *pTime= GetTime();

	STAGENUM pStageNum = GetNumState();

	if (g_aItem[nCntItem].nType != 8 && g_aItem[nCntItem].nType != 6 && g_aItem[nCntItem].nType != 9)
	{	
		//�g�p���Ă��Ȃ����
		g_aItem[nCntItem].bUse = false;		

		if (g_aItem[nCntItem].nType == 0)
		{//�^�C�v�O�@�R�C��
			//�R�C�����Ƃ鉹
			PlaySound(SOUND_LABEL_SE_GETCOIN);
			//�R�C���̃X�R�A
			AddScore(1000, SCORE_COIN);
			//�R�C���̖���
			AddItemCount(1);
			//�Ƃ����疇�������炵�Ă���
			g_NumItem--;

			SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//g_aItem[g_aItem[nCount].nType == 2].bUse = false;

			//�R�C����S���������
			if (g_NumItem <= 0)
			{
				if ((nCount % 180) == 0)
				{//�N���A��ʂɍs�����ԁ@��R�b
					if (pStageNum == STAGENUM_1)
					{
						SetNumGame(STAGENUM_2);
					}
					else if (pStageNum == STAGENUM_2)
					{
						SetNumGame(STAGENUM_3);
					}
					else if (pStageNum == STAGENUM_3)
					{
						SetNumGame(STAGENUM_4);
					}
					else if (pStageNum == STAGENUM_4)
					{
						SetNumGame(STAGENUM_5);
					}
					else if (pStageNum == STAGENUM_5)
					{
						SetNumGame(STAGENUM_6);
						//SetGameState(GAMESTATE_CLEAR);
					}
					else if (pStageNum == STAGENUM_6)
					{
						SetGameState(GAMESTATE_CLEAR);
					}
				}
			}
		}
		else if (g_aItem[nCntItem].nType == 1)
		{//�^�C�v�P�@����
			//���΂��Ƃ�����false�ɂ���
			g_aItem[nCntItem].bUse = false;		//�g�p���Ă��Ȃ����
		}
		else if (g_aItem[nCntItem].nType == 2)
		{//�^�C�v�Q�@�ԃR�C��
			//�ԃR�C�����Ƃ������̉�
			PlaySound(SOUND_LABEL_SE_GETMONEY);
			//�R�C���̃X�R�A
			AddScore(3000,SCORE_COIN);
			//�R�C���̖���
			AddItemCount(3);
			//�Ƃ����疇�������炵�Ă���
			g_NumItem--;
			//����
			SetExplosion(g_aItem[nCntItem].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//�R�C����S���������
			if (g_NumItem <= 0)
			{
				if ((nCount % 180) == 0)
				{//�N���A��ʂɍs�����ԁ@��R�b
					if (pStageNum == STAGENUM_1)
					{
						SetNumGame(STAGENUM_2);
					}
					else if (pStageNum == STAGENUM_2)
					{
						SetNumGame(STAGENUM_3);
					}
					else if (pStageNum == STAGENUM_3)
					{
						SetNumGame(STAGENUM_4);
					}
					else if (pStageNum == STAGENUM_4)
					{
						SetNumGame(STAGENUM_5);
					}
					else if (pStageNum == STAGENUM_5)
					{
						SetNumGame(STAGENUM_6);
						//SetGameState(GAMESTATE_CLEAR);
					}
					else if (pStageNum == STAGENUM_6)
					{
						SetGameState(GAMESTATE_CLEAR);
					}
				}
			}
		}
		else if (g_aItem[nCntItem].nType == 3)
		{//�^�C�v�R�@���v
			//���v���Ƃ鉹
			PlaySound(SOUND_LABEL_SE_TIME);
			//���_�̌��_
			AddScore(-5000,SCORE_TIMER);
			//�R�C���̖����𓾓_������
			AddItemCount(-5);
			//�^�C���𑝉�
			pTime->nTime += 1000;
		}
		else if (g_aItem[nCntItem].nType == 4)
		{//�^�C�v�S�@��
		}
		else if (g_aItem[nCntItem].nType == 5)
		{//�^�C�v�T�@�����̑�
			//�����̑܂��Ƃ������̉�
			PlaySound(SOUND_LABEL_SE_GETMONEY);
			//�����̑܂̃X�R�A
			AddScore(10000,SCORE_MENIYBOX);
		}
		else if (g_aItem[nCntItem].nType == 7)
		{//�^�C�v�V�@���t����
			//���t�������Ƃ�����̂����蔻��
			if (pPlayer->nLife < 3)
			{
				pPlayer->nLife += 1;
				AddLife(1, LifeTex_HIL);
			}
		}
	}
	else if (g_aItem[nCntItem].nType == 6)
	{//���{
	}
	else if (g_aItem[nCntItem].nType == 8)
	{//�Q�[�g
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			//�^�C�g���ɖ߂�
			SetFadeMode(MODE_TITLE);
		}
	}
	else if (g_aItem[nCntItem].nType == 9)
	{//�V���b�v
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			SetMenuState(true);
			//�V���b�v�̋�
			PlaySound(SOUND_LABEL_BGM004);
		}
	
	}
}
//=========================================================================================================================
// �A�C�e���̂����蔻��
//=========================================================================================================================
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWidth, float *fHeight)
{
	//�J�E���g
	int nCount = 0;
	//�J�E���g
	int nCntItem;

	//�v���C���[�̃|�C���^
	Player *pPlayer = GetPlayer();

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g
		if (g_aItem[nCntItem].bUse == true)
		{
			if (pPlayer->pos.y - pPlayer->PlayerHeight < g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight && pPlayer->pos.y > g_aItem[nCntItem].pos.y - g_aItem[nCntItem].fHeight  && pPlayer->pos.x + pPlayer->PlayerWidth  > g_aItem[nCntItem].pos.x /*- g_aItem[nCntItem].fWidth*/ && pPlayer->pos.x - pPlayer->PlayerWidth < g_aItem[nCntItem].pos.x /*+ g_aItem[nCntItem].fWidth*/)
			{//�����蔻��
				DeleteItem(nCntItem);
			}
		}
	}
}
//=========================================================================================================================
// �A�C�e���̂����蔻��
//=========================================================================================================================
void DeleteItem(void)
{
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{//�A�C�e�����J�E���g
		if (g_aItem[nCntItem].bUse == true)
		{
			g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aItem[nCntItem].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			g_aItem[nCntItem].fHeight = 0;
			g_aItem[nCntItem].fWidth = 0;
			g_aItem[nCntItem].nType = 0;
			g_aItem[nCntItem].nCounterAnim = 0;
			g_aItem[nCntItem].nPatteunAnim = 0;
			g_aItem[nCntItem].ItemState = ITEM_STATE_APPER;
			g_aItem[nCntItem].bUse = false;
		}
	}
	g_NumItem = 0;
}
