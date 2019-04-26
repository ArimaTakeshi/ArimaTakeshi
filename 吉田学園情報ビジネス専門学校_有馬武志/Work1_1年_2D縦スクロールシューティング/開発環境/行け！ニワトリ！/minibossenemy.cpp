//=========================================================================================================================
//
// �G���� [minibossenemy.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "minibossenemy.h"		//���{�X
#include "bossenemy.h"			//�{�X
#include "explosion.h"			//����
#include "bullet.h"				//�e
#include "Game.h"				//�Q�[��
#include "score.h"				//�X�R�A
#include "sound.h"				//�T�E���h
#include "warning.h"			//���[�j���O
#include "enemy.h"				//�G���G	

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_TYPE_MINIBOSSENEMY					(4)									// �G�̎��
#define MINIBOSSENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\enemy002.png"		//�ǂݍ��ރe�N�X�`���t�@�C��1
#define MINIBOSSENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\enemy002.png"	//�ǂݍ��ރe�N�X�`���t�@�C��2
#define MINIBOSSENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\enemy002.png"		//�ǂݍ��ރe�N�X�`���t�@�C��3
#define MINIBOSSENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\enemy002.png"		//�ǂݍ��ރe�N�X�`���t�@�C��4
#define WARNING_TEXTURE_NAME					"data\\TEXTURE\\�{�X�O.png"			//�ǂݍ��ރe�N�X�`���t�@�C��5
#define MINIBOSSENEMY_TEXTURE_UV_U				(1.0f)								//�e�N�X�`���A�j���[�V����U�͈�
#define MINIBOSSENEMY_TEXTURE_UV_V				(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureMiniBossEnemy[MAX_TYPE_MINIBOSSENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMiniBossEnemy = NULL;							//���_�o�b�t�@�ւ̃|�C���^
MiniBossEnemy g_aMiniBossEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumMiniBossEnemy;														//�G�̑���

//=========================================================================================================================
// ����������
//=========================================================================================================================
void InitMiniBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntMiniBossEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�̏��̏�����
	for(int nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//�G���J�E���g
		g_aMiniBossEnemy[nCntMiniBossEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMiniBossEnemy[nCntMiniBossEnemy].move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		g_aMiniBossEnemy[nCntMiniBossEnemy].nType = 0;
		g_aMiniBossEnemy[nCntMiniBossEnemy].bUse = false;
		g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_NORMAL;
		g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState = 0;
		g_aMiniBossEnemy[nCntMiniBossEnemy].nLife = 0;			//�G�̗̑�
		g_nNumMiniBossEnemy = 0;								//�G�̑����N���A
	}

	//�e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile
	(
		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_1,
		&g_apTextureMiniBossEnemy[0]
	);
	D3DXCreateTextureFromFile
	(

		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_2,
		&g_apTextureMiniBossEnemy[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_3,
		&g_apTextureMiniBossEnemy[2]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_4,
		&g_apTextureMiniBossEnemy[3]
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
		&g_pVtxBuffMiniBossEnemy,
		NULL
	);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMiniBossEnemy->Lock
	(
		0, 
		0, 
		(void**)&pVtx, 
		0
	);

	for(nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(MINIBOSSENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, MINIBOSSENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(MINIBOSSENEMY_TEXTURE_UV_U, MINIBOSSENEMY_TEXTURE_UV_V);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	/*SetEnemy(D3DXVECTOR3(200, 100, 0.0f), 0);*/

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMiniBossEnemy->Unlock();
}

//=========================================================================================================================
// �I������
//=========================================================================================================================
void UninitMiniBossEnemy(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_MINIBOSSENEMY; nCntTex++)
	{
		if (g_apTextureMiniBossEnemy[nCntTex] != NULL)
		{
			g_apTextureMiniBossEnemy[nCntTex]->Release();
			g_apTextureMiniBossEnemy[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffMiniBossEnemy != NULL)
	{
		g_pVtxBuffMiniBossEnemy->Release();
		g_pVtxBuffMiniBossEnemy = NULL;
	}
}

//=========================================================================================================================
// �X�V����
//=========================================================================================================================
void UpdateMiniBossEnemy(void)
{
	int nCntMiniBossEnemy;

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMiniBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{
		if (g_aMiniBossEnemy[nCntMiniBossEnemy].bUse == true)	//�G���g�p����Ă���
		{	 
			//�~�j�{�X�̃X�s�[�h
			g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y += g_aMiniBossEnemy[nCntMiniBossEnemy].move.y;

			//���_�ݒ�
			pVtx[nCntMiniBossEnemy * 4].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);

			//�~�܂鏈��
			if (g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y >= 200)
			{
				g_aMiniBossEnemy[nCntMiniBossEnemy].move.y = 0;

				switch (g_aMiniBossEnemy[nCntMiniBossEnemy].state)
				{
				case MINIBOSSENEMYSTATE_NORMAL:
					g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState++;

					//�G�̒e�̃����_��
					//�ʏ펞
					if (rand() % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;

						//�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.0f, cosf(D3DX_PI + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.0f, cosf(D3DX_PI * 0 + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

					}
					break;

				case MINIBOSSENEMYSTATE_DAMAGE:
					g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState--;
					if (g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState <= 0)
					{
						g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_NORMAL;

						//���_�J���[�ݒ�
						pVtx[nCntMiniBossEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntMiniBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntMiniBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntMiniBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}

					//�_���[�W��^�����Ƃ��̊o����
					if (rand() % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;

						//�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.5f, cosf(D3DX_PI + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.5f, cosf(D3DX_PI * 0 + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//���G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  4.5f, cosf(D3DX_PI + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) *  4.5f, cosf(D3DX_PI * 0 + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

						//�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) * 1.5f, cosf(D3DX_PI - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 1.5f, cosf(D3DX_PI * 0 - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  2.5f, cosf(D3DX_PI - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  2.5f, cosf(D3DX_PI * 0 - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//���G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  4.5f, cosf(D3DX_PI - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  4.5f, cosf(D3DX_PI * 0 - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
				


						//���@��]�@�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  3.0f, cosf(D3DX_PI - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 3.0f, cosf(D3DX_PI * 0 - nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);



						//���@��]�@�G�̒e
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  3.0f, cosf(D3DX_PI + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 3.0f, cosf(D3DX_PI * 0 + nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

					
					}
					break;
				}
			}
		}
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMiniBossEnemy->Unlock();
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawMiniBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffMiniBossEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//�G���J�E���g
		if (g_aMiniBossEnemy[nCntMiniBossEnemy].bUse == true)
		{//�G������ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureMiniBossEnemy[g_aMiniBossEnemy[nCntMiniBossEnemy].nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMiniBossEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// �G�̐ݒ�
//=========================================================================================================================
void SetMiniBossEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntMiniBossEnemy;		//�G�J�E���g

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMiniBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//�G���J�E���g
		if (g_aMiniBossEnemy[nCntMiniBossEnemy].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aMiniBossEnemy[nCntMiniBossEnemy].pos = pos;			//pos�l���
			g_aMiniBossEnemy[nCntMiniBossEnemy].nType = nType;		//nType�l���
			g_aMiniBossEnemy[nCntMiniBossEnemy].bUse = true;		//�g�p���Ă����Ԃɂ���
			g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_NORMAL;
			g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState = 0;
			g_aMiniBossEnemy[nCntMiniBossEnemy].nLife = 180;			//�G�̗̑�

			//���_�ݒ�
			pVtx[nCntMiniBossEnemy * 4].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);

			g_nNumMiniBossEnemy++;							//�G�̑��������Z����
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffMiniBossEnemy->Unlock();
}

//=========================================================================================================================
// �G�̎擾
//=========================================================================================================================
MiniBossEnemy *GetMiniBossEnemy(void)
{
	return &g_aMiniBossEnemy[0];
}
//=========================================================================================================================
// �G�̃_���[�W����
//=========================================================================================================================
void HitMiniBossEnemy(int nCntMiniBossEnemy, int nDamage)
{

	g_aMiniBossEnemy[nCntMiniBossEnemy].nLife -= nDamage;

	Bullet *pBullet;
	pBullet = GetBullet();

	if (g_aMiniBossEnemy[nCntMiniBossEnemy].nLife <= 0)
	{
		//������
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		//����
		SetExplosion(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXCOLOR(255,255,255,255));
		g_aMiniBossEnemy[nCntMiniBossEnemy].bUse = false;

		//�G�̓��_
		AddScore(156000);

		g_nNumMiniBossEnemy--;						//�G�̑��������炷
		if (g_nNumMiniBossEnemy <= 0)
		{//�G���S�ł�����

			//���[�j���O�R�[��
			SetWarning();

			//���[�L���O���ɒe���Ȃ���
			for (int nCount = 0; nCount < MAX_BULLET; nCount++, pBullet++)
			{
				//�e������
				pBullet->bUse = false;
			}
			//�{�X�ݒu
			SetBossEnemy(D3DXVECTOR3(SCREEN_WIDTH / 2, -500.0f, 0.0f), 0);
		}
	}
	else
	{
		VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾

		//�o�O�����@�{�X�|�������ƃ��g���C�̃`���[�g���A���ŃG���[
		g_pVtxBuffMiniBossEnemy->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_DAMAGE;
		g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState = 5;		//�_���[�W�̎��ԁ@���l���傫���قǒx���Ȃ�

		//���_�J���[�ݒ�
		pVtx[nCntMiniBossEnemy * 4].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntMiniBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntMiniBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntMiniBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffMiniBossEnemy->Unlock();
	}
}
