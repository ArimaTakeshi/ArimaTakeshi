//=========================================================================================================================
//
// �e���� [bullet.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "bullet.h"		//�e
#include "explosion.h"	//����
#include "enemy.h"		//�G
#include "player.h"		//�v���C���[
#include "minibossenemy.h"//���{�X
#include "effect.h"		//�G�t�F�N�g
#include "bossenemy.h"	//�{�X
#include "sound.h"		//�T�E���h

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define BULLET_TEXTURE_NAME			"data\\TEXTURE\\���܂�.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULLET_LIFE					(150)								//�e�̎���
#define BULLET_TEXTURE_UV_U			(1.0f)								//�e�A�j���[�V����U�͈�
#define BULLET_TEXTURE_UV_V			(1.0f)								//�e�A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��

//=========================================================================================================================
// �e����������
//=========================================================================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
	int nCntBullet;					//�e�J�E���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].nLife = BULLET_LIFE;
		g_aBullet[nCntBullet].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		BULLET_TEXTURE_NAME,
		&g_pTextureBullet
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e���J�E���g
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
		pVtx[1].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BULLET_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, BULLET_TEXTURE_UV_V);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================================
// �e�I������
//=========================================================================================================================
void UninitBullet(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureBullet!= NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet= NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet!= NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet= NULL;
	}
}

//=========================================================================================================================
// �e�X�V����
//=========================================================================================================================
void UpdateBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
	int nCntBullet;					//�e�J�E���g
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e���J�E���g
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			int nCntEnemy;		//�G�J�E���g
			Enemy *pEnemy;		//�G�|�C���^
			MiniBossEnemy *pMiniBossEnemy;	//�~�j�{�X�̃|�C���^
			BossEnemy *pBossEnemy;
		
			//�G�̎擾
			pEnemy = GetEnemy();

			//�~�j�{�X�̎擾
			pMiniBossEnemy = GetMiniBossEnemy();

			//�{�X�̎擾
			pBossEnemy = GetBossEnemy();

			//��莞�ԂŌ���
			g_aBullet[nCntBullet].nLife--;

			//�ړ��l���
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;	

			//���_�ݒ�
			pVtx[nCntBullet * 4].pos	 = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 29, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 4, g_aBullet[nCntBullet].pos.y - 29, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 15, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 4, g_aBullet[nCntBullet].pos.y - 15, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntBullet * 4].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);

			//
			//
			//���
			//
			//
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)	//�v���C���[�̒e
			{
				/*//�ł������̉�
				PlaySound(SOUND_LABEL_SE_SHOT);*/
				/*�G�t�F�N�g
				SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 5.0f, 10);*/

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x - 25 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 25 > g_aBullet[nCntBullet].pos.x && pEnemy->pos.y - 25 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 25 > g_aBullet[nCntBullet].pos.y)
						{
							//�q�b�g��
							PlaySound(SOUND_LABEL_SE_HIT000);
							//�_���[�W

							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
						}
					}
				}
				if (pMiniBossEnemy->bUse == true)
				{
					if (pMiniBossEnemy->move.y == 0)
					{
						if (pMiniBossEnemy->pos.x - 70 < g_aBullet[nCntBullet].pos.x && pMiniBossEnemy->pos.x + 70 > g_aBullet[nCntBullet].pos.x && pMiniBossEnemy->pos.y - 70 < g_aBullet[nCntBullet].pos.y && pMiniBossEnemy->pos.y + 90 > g_aBullet[nCntBullet].pos.y)
						{
							//�q�b�g��
							PlaySound(SOUND_LABEL_SE_HIT000);
							//�_���[�W
							HitMiniBossEnemy(0, 1);
							g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
						}
					}
				}
				if (pBossEnemy->bUse == true)
				{
					if (pBossEnemy->move.y == 0)
					{
						if (pBossEnemy->pos.x - 90 < g_aBullet[nCntBullet].pos.x && pBossEnemy->pos.x + 90 > g_aBullet[nCntBullet].pos.x && pBossEnemy->pos.y - 90 < g_aBullet[nCntBullet].pos.y && pBossEnemy->pos.y + 90 > g_aBullet[nCntBullet].pos.y)
						{
							//�q�b�g��
							PlaySound(SOUND_LABEL_SE_HIT000);
							//�_���[�W
							HitBossEnemy(0, 1);
							g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
						}
					}
				}
				if (g_aBullet[nCntBullet].nLife <= 0)
				{//���C�t��0�ȉ��ɂȂ����ꍇ
					/*SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/
					g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
				}

				if (g_aBullet[nCntBullet].pos.y < -0.1 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT + 0.1 || g_aBullet[nCntBullet].pos.x < -0.1 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 0.1)
				{//��ʊO�̏ꍇ
					g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//int nCntPlayer;
				Player *pPlayer;

				//�v���C���[�̎擾
				pPlayer = GetPlayer();

				/*for (nCntPlayer = 0; nCntPlayer < MAX_ENEMY; nCntPlayer++, pPlayer++)
				{*/

					if (pPlayer->bUse == true)
					{
						if (pPlayer->pos.x - 5 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 5 > g_aBullet[nCntBullet].pos.x && pPlayer->pos.y - 5 < g_aBullet[nCntBullet].pos.y && pPlayer->pos.y + 5 > g_aBullet[nCntBullet].pos.y)
						{
							//�q�b�g��
							PlaySound(SOUND_LABEL_SE_HIT001);
							//�_���[�W
							HitPlayer(1);
							g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
						}
					}
				/*}*/

				
			}

			if (g_aBullet[nCntBullet].pos.y < -10 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT + 10 || g_aBullet[nCntBullet].pos.x < -10 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 10)
			{//��ʊO�̏ꍇ
				g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ����
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================================
// �e�`�揈��
//=========================================================================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
	int nCntBullet;					//�e�J�E���g

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffBullet, 
		0, 
		sizeof(VERTEX_2D)
	);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	//�|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e���J�E���g
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e������ꍇ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}
//=========================================================================================================================
// �e�̐ݒ菈��
//=========================================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, BULLETTYPE Type)
{
	int nCntBullet;			//�e�J�E���g

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�e���J�E���g
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ��ꍇ
			g_aBullet[nCntBullet].pos = pos;		//pos�l���
			g_aBullet[nCntBullet].move = move;		//move�l���
			g_aBullet[nCntBullet].col = col;		//color�l���
			g_aBullet[nCntBullet].type = Type;
			g_aBullet[nCntBullet].nLife = BULLET_LIFE;		//���C�t�ݒ�
			g_aBullet[nCntBullet].bUse = true;		//�g�p���Ă����Ԃɂ���

			//���_�ݒ�
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntBullet * 4].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}
//=========================================================================================================================
// �o���b�g�̎擾����
//=========================================================================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}