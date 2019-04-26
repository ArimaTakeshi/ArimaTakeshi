//=========================================================================================================================
//
// �G���� [bossenemy.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "bossenemy.h"		//�G
#include "explosion.h"		//����
#include "bullet.h"			//�e
#include "Game.h"			//�Q�[��
#include "score.h"			//�X�R�A
#include "sound.h"			//�T�E���h
#include "bossenemy.h"		//�{�X
#include "player.h"			//�v���C���[
//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_TYPE_BOSSENEMY					(1)									// �G�̎��
#define BOSSENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\enemy000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��1
#define BOSSENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\enemy000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��2
#define BOSSENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\enemy000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��3
#define BOSSENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\enemy000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��4
#define BOSSENEMY_TEXTURE_UV_U				(1.0f)								//�e�N�X�`���A�j���[�V����U�͈�
#define BOSSENEMY_TEXTURE_UV_V				(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBossEnemy[MAX_TYPE_BOSSENEMY] = {};			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossEnemy = NULL;								//���_�o�b�t�@�ւ̃|�C���^
BossEnemy g_aBossEnemy[MAX_ENEMY];												//�G�̏��

//=========================================================================================================================
// ����������
//=========================================================================================================================
void InitBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBossEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�̏��̏�����
	for (int nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{//�G���J�E���g
		g_aBossEnemy[nCntBossEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBossEnemy[nCntBossEnemy].move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		g_aBossEnemy[nCntBossEnemy].nType = 0;
		g_aBossEnemy[nCntBossEnemy].bUse = false;
		g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_NORMAL;
		g_aBossEnemy[nCntBossEnemy].nCounterState = 0;
		g_aBossEnemy[nCntBossEnemy].nLife = 0;			//�G�̗̑�
	}

	//�e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_1,
		&g_apTextureBossEnemy[0]
	);
	/*D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_2,
		&g_apTextureBossEnemy[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_3,
		&g_apTextureBossEnemy[2]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_4,
		&g_apTextureBossEnemy[3]
	);*/

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBossEnemy,
		NULL
	);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(BOSSENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,BOSSENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BOSSENEMY_TEXTURE_UV_U,BOSSENEMY_TEXTURE_UV_V);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBossEnemy->Unlock();
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitBossEnemy(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_BOSSENEMY; nCntTex++)
	{
		if (g_apTextureBossEnemy[nCntTex] != NULL)
		{
			g_apTextureBossEnemy[nCntTex]->Release();
			g_apTextureBossEnemy[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBossEnemy != NULL)
	{
		g_pVtxBuffBossEnemy->Release();
		g_pVtxBuffBossEnemy = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateBossEnemy(void)
{
	int nCntBossEnemy;

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	Player *pPlayer;

	pPlayer = GetPlayer();

	for (nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{
		if (g_aBossEnemy[nCntBossEnemy].bUse == true)	//�G���g�p����Ă���
		{
			//�{�X�̃X�s�[�h
			g_aBossEnemy[nCntBossEnemy].pos.y += g_aBossEnemy[nCntBossEnemy].move.y;

			//���_�ݒ�
			pVtx[nCntBossEnemy * 4].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 90, g_aBossEnemy[nCntBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 90, g_aBossEnemy[nCntBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 90, g_aBossEnemy[nCntBossEnemy].pos.y + 90, 0.0f);
			pVtx[nCntBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 90, g_aBossEnemy[nCntBossEnemy].pos.y + 90, 0.0f);

			//�~�܂鏈��
			if (g_aBossEnemy[nCntBossEnemy].pos.y >= 200)
			{
				g_aBossEnemy[nCntBossEnemy].move.y = 0;

				//�U���X�s�[�h
				static int nCount = 0;

				switch (g_aBossEnemy[nCntBossEnemy].state)
				{
				case BOSSENEMYSTATE_NORMAL:
					g_aBossEnemy[nCntBossEnemy].nCounterState++;

					nCount++;
					//�G�̒e�̃����_��
					if (rand() % 10 == 0)
					if(nCount % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;
						

						
						//�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.0f, cosf(D3DX_PI + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.0f, cosf(D3DX_PI * 0 + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//�ǔ�
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, cosf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						/*SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  2.0f, cosf(D3DX_PI - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  2.0f, cosf(D3DX_PI * 0 - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  2.0f, cosf(D3DX_PI * 0.5f - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  2.0f, cosf(D3DX_PI * -0.5f - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);*/
					}
					break;

				case BOSSENEMYSTATE_DAMAGE:
					g_aBossEnemy[nCntBossEnemy].nCounterState--;
					if (g_aBossEnemy[nCntBossEnemy].nCounterState <= 0)
					{
						g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_NORMAL;

						//���_�J���[�ݒ�
						pVtx[nCntBossEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}

					//�G�̒e�̃����_��
					if (rand() % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;

						//�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						

						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.5f, cosf(D3DX_PI + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.5f, cosf(D3DX_PI * 0 + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//���G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  4.5f, cosf(D3DX_PI + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) *  4.5f, cosf(D3DX_PI * 0 + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

						//�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) * 1.5f, cosf(D3DX_PI - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 1.5f, cosf(D3DX_PI * 0 - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  2.5f, cosf(D3DX_PI - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  2.5f, cosf(D3DX_PI * 0 - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//���G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  4.5f, cosf(D3DX_PI - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  4.5f, cosf(D3DX_PI * 0 - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);



						//���@��]�@�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  3.0f, cosf(D3DX_PI - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 3.0f, cosf(D3DX_PI * 0 - nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);



						//���@��]�@�G�̒e
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  3.0f, cosf(D3DX_PI + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 3.0f, cosf(D3DX_PI * 0 + nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

						//�ǔ�
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, cosf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
					}
					break;
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBossEnemy->Unlock();
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�|�C���^

								//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBossEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{//�G���J�E���g
		if (g_aBossEnemy[nCntBossEnemy].bUse == true)
		{//�G������ꍇ
		 // �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBossEnemy[g_aBossEnemy[nCntBossEnemy].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBossEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// �G�̐ݒ�
//=========================================================================================================================
void SetBossEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntBossEnemy;		//�G�J�E���g

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

								//���_�o�b�t�@�����b�N
	g_pVtxBuffBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{//�G���J�E���g
		if (g_aBossEnemy[nCntBossEnemy].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aBossEnemy[nCntBossEnemy].pos = pos;			//pos�l���
			g_aBossEnemy[nCntBossEnemy].nType = nType;		//nType�l���
			g_aBossEnemy[nCntBossEnemy].bUse = true;		//�g�p���Ă����Ԃɂ���
			g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_NORMAL;
			g_aBossEnemy[nCntBossEnemy].nCounterState = 0;
			g_aBossEnemy[nCntBossEnemy].nLife = 250;			//�G�̗̑�

																		//���_�ݒ�
			pVtx[nCntBossEnemy * 4].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 150, g_aBossEnemy[nCntBossEnemy].pos.y - 150, 0.0f);
			pVtx[nCntBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 150, g_aBossEnemy[nCntBossEnemy].pos.y - 150, 0.0f);
			pVtx[nCntBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 150, g_aBossEnemy[nCntBossEnemy].pos.y + 150, 0.0f);
			pVtx[nCntBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 150, g_aBossEnemy[nCntBossEnemy].pos.y + 150, 0.0f);

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBossEnemy->Unlock();
}

//=========================================================================================================================
// �G�̎擾
//=========================================================================================================================
BossEnemy *GetBossEnemy(void)
{
	return &g_aBossEnemy[0];
}
//=========================================================================================================================
// �G�̃_���[�W����
//=========================================================================================================================
void HitBossEnemy(int nCntBossEnemy, int nDamage)
{

	g_aBossEnemy[nCntBossEnemy].nLife -= nDamage;
	if (g_aBossEnemy[nCntBossEnemy].nLife <= 0)
	{
		//������
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		//����
		SetExplosion(g_aBossEnemy[nCntBossEnemy].pos, D3DXCOLOR(255, 255, 255, 255));
		g_aBossEnemy[nCntBossEnemy].bUse = false;

		MODE pMode;
		pMode = *GetMode();

		if (pMode == MODE_GAME)
		{
			//�G�̓��_
			AddScore(1234567);

			//�b���J�E���^�[
			int nCount = 0;

			if ((nCount % 250) == 0)
			{//�G���S�ł�����
				SetGameState(GAMESTATE_CLEAR);
			}
		}
	}
	else
	{
		VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBossEnemy->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_DAMAGE;
		g_aBossEnemy[nCntBossEnemy].nCounterState = 5;		//�_���[�W�̎��ԁ@���l���傫���قǒx���Ȃ�

		//���_�J���[�ݒ�
		pVtx[nCntBossEnemy * 4].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffBossEnemy->Unlock();
	}
}
