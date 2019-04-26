//=========================================================================================================================
//
// �G���� [enemy.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "enemy.h"				//�G
#include "explosion.h"			//����
#include "Game.h"				//�Q�[��
#include "score.h"				//�X�R�A
#include "sound.h"				//�T�E���h
#include "player.h"				//�v���C���[

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_TYPE_ENEMY					(4)									// �G�̎��
#define ENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\�G�r�t���C.png"		//�ǂݍ��ރe�N�X�`���t�@�C��1
#define ENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\.png"				//�ǂݍ��ރe�N�X�`���t�@�C��2
#define ENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\.png"				//�ǂݍ��ރe�N�X�`���t�@�C��3
#define ENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\.png"				//�ǂݍ��ރe�N�X�`���t�@�C��4
#define ENEMY_HEIGHT					(40)
#define ENEMY_WIDTH						(30)
#define ENEMY_TEXTURE_UV_U				(1.0f)								//�e�N�X�`���A�j���[�V����U�͈�
#define ENEMY_TEXTURE_UV_V				(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy;												//�G�̑���

//=========================================================================================================================
// ����������
//=========================================================================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�G���J�E���g
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(3, 3, 3);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 5;			//�G�̗̑�
		g_nNumEnemy = 0;						//�G�̑����N���A
	}

	//�e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile
	(//�P���ڂ̉摜
		pDevice,
		ENEMY_TEXTURE_NAME_1,
		&g_apTextureEnemy[0]
	);
	D3DXCreateTextureFromFile
	(//�Q���ڂ̉摜
		pDevice,
		ENEMY_TEXTURE_NAME_2,
		&g_apTextureEnemy[1]
	);
	D3DXCreateTextureFromFile
	(//�R���ڂ̉摜
		pDevice,
		ENEMY_TEXTURE_NAME_3,
		&g_apTextureEnemy[2]
	);
	D3DXCreateTextureFromFile
	(//�S���ڂ̉摜
		pDevice,
		ENEMY_TEXTURE_NAME_4,
		&g_apTextureEnemy[3]
	);

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock
	(
		0, 
		0, 
		(void**)&pVtx, 
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�G���J�E���g
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
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitEnemy(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���[�h�̎擾
	MODE pMode;
	pMode = *GetMode();
	//�v���C���[�̎擾
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)	//�G���g�p����Ă���
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
			//	g_aEnemy[nCntEnemy].move.x = (sinf(atan2(-pPlayer->pos.x - -pPlayer->pos.x, -pPlayer->pos.y - -pPlayer->pos.y))* 0.1f);
			//	g_aEnemy[nCntEnemy].move.x = (cosf(atan2(-pPlayer->pos.x - -pPlayer->pos.x, -pPlayer->pos.y - -pPlayer->pos.y))* 0.1f);

				break;
			case ENEMYSTATE_DAMAGE:
				break;
			}	
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G������ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// �G�̐ݒ�
//=========================================================================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;		//�G�J�E���g

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aEnemy[nCntEnemy].pos = pos;			//pos�l���
			g_aEnemy[nCntEnemy].nType = nType;		//nType�l���
			g_aEnemy[nCntEnemy].bUse = true;		//�g�p���Ă����Ԃɂ���
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;	
			g_aEnemy[nCntEnemy].nCounterState = 0;

			//���_�ݒ�
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);

			//�G�̑��������Z����
			g_nNumEnemy++;							
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}
//=========================================================================================================================
// �G�̎擾
//=========================================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
//============================================
//
//============================================
void DeleteEnemy(void)
{
	//�G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//�G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].nType = 0;
			g_aEnemy[nCntEnemy].bUse = false;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 5;			//�G�̗̑�
			g_nNumEnemy = 0;						//�G�̑����N���A
		}
	}
}
