//=========================================================================================================================
// 
// �G���� [enemy.cpp]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "enemy.h"			// �G
#include "sound.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_ENEMY_TEXTURE				(2)											// �G�̎��
#define ENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\Enemy_CharTex000.png"		// �ǂݍ��ރe�N�X�`���t�@�C��1
#define ENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\Needle000.png"		// �ǂݍ��ރe�N�X�`���t�@�C��1
#define ENEMY_TEXTURE_SPEED				(15)										// �e�N�X�`���A�j���[�V�����X�s�[�h
#define ENEMY_TEXTURE_PATTERN			(4)											// �e�N�X�`���A�j���[�V�����p�^�[����
#define ENEMY_TEXTURE_UV_U				(5)										// �e�N�X�`���A�j���[�V����U�͈�
#define ENEMY_TEXTURE_UV_V				(3)										// �e�N�X�`���A�j���[�V����V�͈�
#define ENEMY_SPEED						(10)										// �G�ړ����x
#define ENEMY_FOUND_0					(0.65f)										//�����͈́@��ʂ�6/10
#define ENEMY_FOUND_1					(0.7f)										//�����͈́@��ʂ�7/10
#define ENEMY_FOUND_2					(0.75f)										//�����͈́@��ʂ�8/10
#define ENEMY_FOUND_3					(0.8f)										//�����͈́@��ʂ�9/10
#define ENEMY_FOUND_4					(1.0f)										//�����͈́@��ʂ�9/10
#define ENEMY_GRAVITY					(0.8f)										//�G�̏d��
#define ENEMY_NBGRAVITY					(0.3f)										//�G�̃m�b�N�o�b�N���̏d��
#define ENEMY_RESTIME					(600)										//�G�̃��X�|�[������

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9			g_apTextureEnemy[MAX_ENEMY_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffEnemy = NULL;							// ���_�o�b�t�@�ւ̃|�C���^
Enemy						g_aEnemy[MAX_ENEMY];							// �G�̏��

//=========================================================================================================================
// �G����������
//=========================================================================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	int nCntEnemy;		// �G�J�E���g

	// �G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		//g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G���S�l
		//g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�ړ��l
		//g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �G�F
		//g_aEnemy[nCntEnemy].nTexNum = 0;									// �G���
		//g_aEnemy[nCntEnemy].nLife = 0;										// �G�̗�
		//g_aEnemy[nCntEnemy].type = ENEMYTYPE_NORMALENEMY;					// �G�N���X
		//g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;						// �G���
		//g_aEnemy[nCntEnemy].nCounterState = 0;								// �G��ԃJ�E���g
		//g_aEnemy[nCntEnemy].nCounterAnim = 0;								// �G�J�E���^�A�j���[�V����
		//g_aEnemy[nCntEnemy].nPatternAnim = 1;								// �G�p�^�[���A�j���[�V����
		//g_aEnemy[nCntEnemy].nCountAttack = 0;
		//g_aEnemy[nCntEnemy].fMove = 0.0f;									//�ړ��l�ۑ�
		//g_aEnemy[nCntEnemy].nAngle = 1;
		g_aEnemy[nCntEnemy].bUse = false;									// �G�g�p���Ă��邩
		g_aEnemy[nCntEnemy].bRespawn = false;
	}

	// �e�N�X�`���̓ǂݍ���(�T)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_1, &g_apTextureEnemy[0]);// �G1
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_2, &g_apTextureEnemy[1]);// ��1

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock
	(
		0, 
		0, 
		(void**)&pVtx, 
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		//// ���_�ݒ�
		//pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//// ���_�J���[�ݒ�
		//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//// �e�N�X�`���ݒ�
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		//pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// �G�I������
//=========================================================================================================================
void UninitEnemy(void)
{
	int nCntTex;		// �e�N�X�`���J�E���^
	for (nCntTex = 0; nCntTex < MAX_ENEMY; nCntTex++)
	{
		g_aEnemy[nCntTex].bUse = false;
	}
// �e�N�X�`���̔j��
for (nCntTex = 0; nCntTex < MAX_ENEMY_TEXTURE; nCntTex++)
{// �e�N�X�`���J�E���^
	if (g_apTextureEnemy[nCntTex] != NULL)
	{
		g_apTextureEnemy[nCntTex]->Release();
		g_apTextureEnemy[nCntTex] = NULL;
	}
}

// ���_�o�b�t�@�̔j��
if (g_pVtxBuffEnemy != NULL)
{
	g_pVtxBuffEnemy->Release();
	g_pVtxBuffEnemy = NULL;
}
}

//=========================================================================================================================
// �G�X�V����
//=========================================================================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;						// �G�J�E���g
	PLAYER *pPlayer = GetPlayer();
	PLAYERSTATE state = PLAYERSTATE_NORMAL;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == true)
		{// �G���g�p����Ă���ꍇ
			g_aEnemy[nCntEnemy].posold = g_aEnemy[nCntEnemy].pos;
			g_aEnemy[nCntEnemy].nCounterAnim++;		// �J�E���^�[���Z
			g_aEnemy[nCntEnemy].nCounterDamage--;//��_�����Ԃ�����߂�
			if (g_aEnemy[nCntEnemy].nCounterDamage == 0) { g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			PLAYER *pPlayer = GetPlayer();
			g_aEnemy[nCntEnemy].move.y += 0.8f;
			if (g_aEnemy[nCntEnemy].fSteep != D3DX_PI) { g_aEnemy[nCntEnemy].move = D3DXVECTOR3(20.0f, -16.0f, 0.0f); }
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;
			g_aEnemy[nCntEnemy].fSteep += g_aEnemy[nCntEnemy].fplusSteep;

			if ((g_aEnemy[nCntEnemy].nCounterAnim % ENEMY_TEXTURE_SPEED) == 0 && g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_KNOCKBACK)
			{// �A�j���[�V�������x �����Ă���
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % ENEMY_TEXTURE_PATTERN;		// �p�^�[��No.�X�V
				if (g_aEnemy[nCntEnemy].posold.x - g_aEnemy[nCntEnemy].pos.x > 1 && g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_NORMAL) { g_aEnemy[nCntEnemy].nAngle = 0; }
				else if (g_aEnemy[nCntEnemy].posold.x - g_aEnemy[nCntEnemy].pos.x < -1 && g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_NORMAL) { g_aEnemy[nCntEnemy].nAngle = 1; }
			}//�~�܂�����

			if (CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posold, &g_aEnemy[nCntEnemy].move, NULL, false, &state, g_aEnemy[nCntEnemy].nCollisionX, g_aEnemy[nCntEnemy].nCollisionY, nCntEnemy, USETYPE_ENEMY) == true)
			{
				if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_KNOCKBACK || g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_JUMP)
				{
					g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
					g_aEnemy[nCntEnemy].fMove = 0.0f;
				}
			}
		}//true�̎�
		//else if (g_aEnemy[nCntEnemy].bRespawn == true)
		//{//�����\�Ȃ�
		//	//g_aEnemy[nCntEnemy].nResCount++;
		//	//if (g_aEnemy[nCntEnemy].nResCount > ENEMY_RESTIME)
		//	//{//����
		//	//	g_aEnemy[nCntEnemy].bRespawn = false;
		//	//	g_aEnemy[nCntEnemy].pos = g_aEnemy[nCntEnemy].respawn;
		//	//	g_aEnemy[nCntEnemy].posold = g_aEnemy[nCntEnemy].respawn;
		//	//	g_aEnemy[nCntEnemy].nLife = g_aEnemy[nCntEnemy].nMaxLife;
		//	//	g_aEnemy[nCntEnemy].fMove = 0.0f;
		//	//	g_aEnemy[nCntEnemy].fSteep = D3DX_PI;
		//	//	g_aEnemy[nCntEnemy].nCountAttack = 0;
		//	//	//g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		//	//	g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_NORMAL;
		//	//	g_aEnemy[nCntEnemy].nCounterDamage = 0;
		//	//	g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//	//	g_aEnemy[nCntEnemy].bUse = true;
		//	//}
		//}
	}
}
//=========================================================================================================//
// * �X���C��
//=========================================================================================================//
void SlimeUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_1 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_1 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_1 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_1)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nSize * -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 40)
		{
			g_aEnemy[nCntEnemy].fMove = 0.3f;
			g_aEnemy[nCntEnemy].nAngle ^= 1;
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 160)
		{
			g_aEnemy[nCntEnemy].fMove = 0.0f;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		break;
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 100; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
			if(g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < -3 || g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3)
			{ g_aEnemy[nCntEnemy].fMove = 0.5f; }
		}
		if (g_aEnemy[nCntEnemy].pos.x + 200 > pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.x - 200 < pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize > pPlayer[0].pos.y && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize < pPlayer[0].pos.y)
		{
			if (g_aEnemy[nCntEnemy].nCountAttack == 0)
			{//�U������
				g_aEnemy[nCntEnemy].nCountAttack = 1;
				g_aEnemy[nCntEnemy].fMove = 0.0f;
			}
			else if (g_aEnemy[nCntEnemy].nCountAttack == 2)
			{ 
				PlaySound(SOUND_LABEL_ATTACK002);
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			}
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 30)
		{//�U��
			g_aEnemy[nCntEnemy].move.y = -15;
			g_aEnemy[nCntEnemy].fMove = (pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x) / (g_aEnemy[nCntEnemy].move.y / ENEMY_GRAVITY * 7.9f);
			if (pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x > 0) { g_aEnemy[nCntEnemy].fMove *= -1; }
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_JUMP;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack <= 60)
		{//�U����������U���܂�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
		}
		break;
	}
}
//=========================================================================================================//
// * �R�E����
//=========================================================================================================//
void BatUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	if (g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_FLY)
	{//�U�����ȊO
		g_aEnemy[nCntEnemy].move.y -= 0.7428f;
		if (g_aEnemy[nCntEnemy].nPatternAnim == 2) { g_aEnemy[nCntEnemy].move.y = -1.0f; }
	}
	else
	{
		g_aEnemy[nCntEnemy].move.y -= g_aEnemy[nCntEnemy].fGravity + 0.8f;
		if (g_aEnemy[nCntEnemy].nCountAttack == 119) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND; }
	}
	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_3)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nSize * -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 50)
		{
			g_aEnemy[nCntEnemy].fMove = 0.4f;
			g_aEnemy[nCntEnemy].nAngle ^= 1;
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 200)
		{
			g_aEnemy[nCntEnemy].fMove = 0.0f;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		break;
	case ENEMYEFFECT_FLY:
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 130; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < -3) { g_aEnemy[nCntEnemy].nAngle = 1; }
			g_aEnemy[nCntEnemy].fMove = 0.0f;
		}
		if (g_aEnemy[nCntEnemy].pos.x + 250 > pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.x - 250 < pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 100 < pPlayer[0].pos.y && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 150 > pPlayer[0].pos.y)
		{
			if (g_aEnemy[nCntEnemy].nCountAttack == 0)
			{//�U������
				g_aEnemy[nCntEnemy].nCountAttack = 1;
				g_aEnemy[nCntEnemy].fMove = 0.0f;
				g_aEnemy[nCntEnemy].move.y = 0.0f;
			}
			else if (g_aEnemy[nCntEnemy].nCountAttack == 2)
			{//�U�����}
				PlaySound(SOUND_LABEL_ATTACK002);
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			}
		}
		else if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 100 > pPlayer[0].pos.y)
		{//�c����
			if (g_aEnemy[nCntEnemy].nPatternAnim == 2 && g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_FLY) { g_aEnemy[nCntEnemy].move.y = -2.0f; }
		}//������
		if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 150 < pPlayer[0].pos.y) { g_aEnemy[nCntEnemy].pos.y += 0.5f; }
		
		if(g_aEnemy[nCntEnemy].pos.x + 250 < pPlayer[0].pos.x || g_aEnemy[nCntEnemy].pos.x - 250 > pPlayer[0].pos.x) { g_aEnemy[nCntEnemy].fMove = 0.6f; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 30)
		{//�U��
			g_aEnemy[nCntEnemy].move.y = (pPlayer[0].pos.y - g_aEnemy[nCntEnemy].pos.y) * 2 / 60 + (pPlayer[0].pos.y - g_aEnemy[nCntEnemy].pos.y) * 2 / 60 / 60;
			g_aEnemy[nCntEnemy].fGravity = g_aEnemy[nCntEnemy].move.y / 60;
			//MessageBox(0, "", "", MB_OK);
			g_aEnemy[nCntEnemy].fMove = (pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x) / 120;
			if (pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x < 0) { g_aEnemy[nCntEnemy].fMove *= -1; }
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FLY;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack <= 30)
		{//�U����������U���܂�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
		}
		break;
	}
}
//=========================================================================================================//
// * ���l
//=========================================================================================================//
void GiantUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_0 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_0 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_0 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_0)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nSize * -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 55)
		{
			g_aEnemy[nCntEnemy].fMove = 0.3f;
			g_aEnemy[nCntEnemy].nAngle ^= 1;
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 240)
		{
			g_aEnemy[nCntEnemy].fMove = 0.0f;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		break;
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 100; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
			if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nCollisionY >  pPlayer[0].pos.y && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nCollisionY <  pPlayer[0].pos.y) { g_aEnemy[nCntEnemy].fMove = 1.0f; }
			else { g_aEnemy[nCntEnemy].fMove = 0.3f; }
		}
		break;
	}
}

//=========================================================================================================//
// * ��̐����@MYSTERY
//=========================================================================================================//
void MysteryUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_0 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_0)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nSize * -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		else
		{
			g_aEnemy[nCntEnemy].fMove = 0.0f;
		}
		break;
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 100; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			g_aEnemy[nCntEnemy].fMove = 0.0f;
		}
		if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize > pPlayer[0].pos.y && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize < pPlayer[0].pos.y)
		{//������ʒu�ɂ����
			if (g_aEnemy[nCntEnemy].nCountAttack == 0)
			{//�U������
				g_aEnemy[nCntEnemy].nCountAttack = 1;
			}
			else if (g_aEnemy[nCntEnemy].nCountAttack == 2)
			{//�U�����}
				PlaySound(SOUND_LABEL_ATTACK002);
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			}
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 30)
		{//�U��
			SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nCollisionX + (g_aEnemy[nCntEnemy].nCollisionX * 2) * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_NONE, D3DX_PI * -0.5f + D3DX_PI * g_aEnemy[nCntEnemy].nAngle, 0.0f, g_aEnemy[nCntEnemy].nSize / 2, g_aEnemy[nCntEnemy].nSize * 3, 2, g_aEnemy[nCntEnemy].nAtk, 3.0f, BULLETTYPE_ENEMY, nCntEnemy);
		}
		if (g_aEnemy[nCntEnemy].nCountAttack <= 30)
		{//�U����������U���܂�
			g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % ENEMY_TEXTURE_PATTERN;
			if ((g_aEnemy[nCntEnemy].nCounterAnim % ENEMY_TEXTURE_SPEED) == 0){}
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
		}
		break;
	}
}

 //=========================================================================================================//
 // * �r�[�X�g�@ENEMYTEX_BEAST
 //=========================================================================================================//
void WolfUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_2 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_2 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_1 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_1)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nSize * -1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 30)
		{
			g_aEnemy[nCntEnemy].fMove = 0.35f;
			g_aEnemy[nCntEnemy].nAngle ^= 1;
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 160)
		{
			g_aEnemy[nCntEnemy].fMove = 0.0f;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		break;
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 80; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < -3 || g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3)
			{
				g_aEnemy[nCntEnemy].fMove = 0.5f;
			}
		}
		if (g_aEnemy[nCntEnemy].pos.x + 300 > pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.x - 300 < pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize > pPlayer[0].pos.y && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize < pPlayer[0].pos.y)
		{
			if (g_aEnemy[nCntEnemy].nCountAttack == 0)
			{//�U������
				g_aEnemy[nCntEnemy].nCountAttack = 1;
				g_aEnemy[nCntEnemy].fMove = 0.0f;
			}
			else if (g_aEnemy[nCntEnemy].nCountAttack == 2)
			{//�U�����}
				PlaySound(SOUND_LABEL_ATTACK002);
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			}
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 30)
		{//�U��
			g_aEnemy[nCntEnemy].fMove = 10.0f;
			//if (pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x > 0) { g_aEnemy[nCntEnemy].fMove *= -1; }
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOTBACK;
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_ATTACK;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack <= 30)
		{//�U����������U���܂�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
		}
		break;
	case ENEMYEFFECT_ATTACK:
		g_aEnemy[nCntEnemy].fMove -= 0.28f;
		if (g_aEnemy[nCntEnemy].fMove < 1.0f) { g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL; }
		if (g_aEnemy[nCntEnemy].fMove < 0.0f)
		{ g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND; }
		break;
	}
}

//=========================================================================================================//
// * �h���S��
//=========================================================================================================//
void DragonUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	float fSteep;

	g_aEnemy[nCntEnemy].move.y -= 0.7428f;
	if (g_aEnemy[nCntEnemy].nPatternAnim == 2) { g_aEnemy[nCntEnemy].move.y = -1.0f; }
	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_3)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nCollisionY - 30 * 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 50)
		{
			g_aEnemy[nCntEnemy].fMove = 0.4f;
			g_aEnemy[nCntEnemy].nAngle ^= 1;
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 200)
		{
			g_aEnemy[nCntEnemy].fMove = 0.0f;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
		}
		break;
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 150; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < -3) { g_aEnemy[nCntEnemy].nAngle = 1; }
			g_aEnemy[nCntEnemy].fMove = 0.0f;
		}
		if (g_aEnemy[nCntEnemy].pos.x + 250 > pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.x - 250 < pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 50 < pPlayer[0].pos.y)
		{
			if (g_aEnemy[nCntEnemy].nCountAttack == 0)
			{//�U������
				g_aEnemy[nCntEnemy].nCountAttack = 1;
				g_aEnemy[nCntEnemy].fMove = 0.0f;
				g_aEnemy[nCntEnemy].move.y = 0.0f;
			}
		}
		else if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 50 > pPlayer[0].pos.y)
		{//�c����
			if (g_aEnemy[nCntEnemy].nPatternAnim == 2 && g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_FLY) { g_aEnemy[nCntEnemy].move.y = -2.0f; }
		}//������
		if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize + 100 < pPlayer[0].pos.y) { g_aEnemy[nCntEnemy].pos.y += 0.5f; }

		if (g_aEnemy[nCntEnemy].pos.x + 250 < pPlayer[0].pos.x || g_aEnemy[nCntEnemy].pos.x - 250 > pPlayer[0].pos.x) { g_aEnemy[nCntEnemy].fMove = 0.6f; }
		if (g_aEnemy[nCntEnemy].nCountAttack % 10 == 2 && g_aEnemy[nCntEnemy].nCountAttack < 30)
		{//�U�����}
			PlaySound(SOUND_LABEL_ATTACK002);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack % 10 == 0 && g_aEnemy[nCntEnemy].nCountAttack > 20 && g_aEnemy[nCntEnemy].nCountAttack < 60)
		{//�U��
			fSteep = atan2f(pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer[0].pos.y - g_aEnemy[nCntEnemy].pos.y);
			SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nCollisionX + (g_aEnemy[nCntEnemy].nCollisionX * 2) * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_NONE, fSteep, 0.0f, g_aEnemy[nCntEnemy].nSize * 2 / 3, g_aEnemy[nCntEnemy].nSize * 4 / 3, 0, g_aEnemy[nCntEnemy].nAtk / 2, 3.0f, BULLETTYPE_ENEMY, nCntEnemy);
		}
		if (g_aEnemy[nCntEnemy].nCountAttack <= 90)
		{//�U����������U���܂�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
		}
		break;
	}
}

//=========================================================================================================//
// * ���_
//=========================================================================================================//
void DeathUpdate(int nCntEnemy)
{
	PLAYER *pPlayer = GetPlayer();
	float fSteep;
	int nRand;

	if (g_aEnemy[nCntEnemy].pos.y - 50 > g_aEnemy[nCntEnemy].respawn.y) { g_aEnemy[nCntEnemy].move.y = -5.0f; }
	if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_FLY) { g_aEnemy[nCntEnemy].move.y -= 0.2f; }
	if (g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_FLY && g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_ATTACK)
	{//�n��U���ȊO�̎�
		g_aEnemy[nCntEnemy].move.y -= 0.7428f;
		if (g_aEnemy[nCntEnemy].nPatternAnim == 2) { g_aEnemy[nCntEnemy].move.y = -1.0f; }
	}

	switch (g_aEnemy[nCntEnemy].effect)
	{
	case ENEMYEFFECT_NORMAL://�������Ă��Ȃ�
		g_aEnemy[nCntEnemy].nCountAttack++;
		if (g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH * ENEMY_FOUND_4 && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= -SCREEN_WIDTH * ENEMY_FOUND_4 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT * ENEMY_FOUND_3 && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= -SCREEN_HEIGHT * ENEMY_FOUND_3)
		{
			SetExplosion(D3DXVECTOR3(10000.0f, 10000.0f, 0.0f), D3DXVECTOR3(0.0f, g_aEnemy[nCntEnemy].nCollisionY - 30 * 1.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 20, 3, 1, 10, 3, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_ENEMY, nCntEnemy, D3DX_PI);
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].nCountAttack = 0;
			if (g_aEnemy[nCntEnemy].type == ENEMYTYPE_BOSSENEMY)
			{
				CleanEnemy();
				SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.67f - 65.0f, SCREEN_HEIGHT * 0.17f - 5.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 60, 60, 2, nCntEnemy, WINDOWSTATE_NORMAL, WINDOWUSE_ENEMY);
				SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.67f - 5.0f, SCREEN_HEIGHT * 0.17f - 5.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 400, 60, 0, nCntEnemy, WINDOWSTATE_MAXLIFEGAGE, WINDOWUSE_ENEMY);
				SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.67f, SCREEN_HEIGHT * 0.17f, 0.0f), D3DXCOLOR(0.8f, 0.1f, 0.02f, 1.0f), 300, 50, 0, nCntEnemy, WINDOWSTATE_AUTOLIFEGAGE, WINDOWUSE_ENEMY);
				SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.67f, SCREEN_HEIGHT * 0.17f, 0.0f), D3DXCOLOR(0.25f, 1.0f, 0.1f, 1.0f), 300, 50, 0, nCntEnemy, WINDOWSTATE_LIFEGAGE, WINDOWUSE_ENEMY);
			}
		}
		break;
	case ENEMYEFFECT_FLY:
	case ENEMYEFFECT_MAGIC:
	case ENEMYEFFECT_ATTACK:
	case ENEMYEFFECT_FIND:
		if (g_aEnemy[nCntEnemy].nCountAttack != 0 && g_aEnemy[nCntEnemy].nLife > g_aEnemy[nCntEnemy].nMaxLife / 2) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 350; }
		else if (g_aEnemy[nCntEnemy].nCountAttack != 0) { g_aEnemy[nCntEnemy].nCountAttack = (g_aEnemy[nCntEnemy].nCountAttack + 1) % 250; }
		if (g_aEnemy[nCntEnemy].nCountAttack == 0)
		{//�U�����Ă��Ȃ���ԂȂ�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < -3) { g_aEnemy[nCntEnemy].nAngle = 1; }
			if (g_aEnemy[nCntEnemy].nLife > g_aEnemy[nCntEnemy].nMaxLife / 2) { if (g_aEnemy[nCntEnemy].pos.x + 300 < pPlayer[0].pos.x || g_aEnemy[nCntEnemy].pos.x - 300 > pPlayer[0].pos.x) { g_aEnemy[nCntEnemy].fMove = 1.0f; } }
			else { if (g_aEnemy[nCntEnemy].pos.x + 300 < pPlayer[0].pos.x || g_aEnemy[nCntEnemy].pos.x - 300 > pPlayer[0].pos.x) { g_aEnemy[nCntEnemy].fMove = 2.0f; } }
			g_aEnemy[nCntEnemy].fMove = 0.3f;
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
		}
		if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize - 30 > pPlayer[0].pos.y) { g_aEnemy[nCntEnemy].pos.y -= 0.2f; }
		if (g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize - 30 < pPlayer[0].pos.y && g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_FLY) { g_aEnemy[nCntEnemy].pos.y += 0.5f; }
		//if (g_aEnemy[nCntEnemy].state != ENEMYSTATE_ATTACK)
		//{//�c������

		//}
		if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_FIND)
		{
			if (g_aEnemy[nCntEnemy].pos.x + 300 >= pPlayer[0].pos.x && g_aEnemy[nCntEnemy].pos.x - 300 <= pPlayer[0].pos.x)
			{//X���U���͈͓�
				g_aEnemy[nCntEnemy].fMove = 0.0f;
				nRand = rand() % 3;
					if (nRand == 0) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_ATTACK; }
					if (nRand == 1) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FLY; }
					if (nRand == 2) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_MAGIC; }

				//if (g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize > pPlayer[0].pos.y)
				//{//��ɂ���ꍇ
				//	nRand = rand() % 2;
				//	if (nRand == 0) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FLY; }
				//	if (nRand == 1) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_MAGIC; }
				//}
				//else
				//{//���ɂ���ꍇ
				//	nRand = rand() % 2;
				//	if (nRand == 0) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_ATTACK; }
				//	if (nRand == 1) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_MAGIC; }
				//}
				g_aEnemy[nCntEnemy].nCountAttack = 1;
			}
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 2 && g_aEnemy[nCntEnemy].effect != ENEMYEFFECT_MAGIC)
		{//�U�����}
			PlaySound(SOUND_LABEL_ATTACK002);
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 2 && g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_MAGIC)
		{//���̏ꍇ
			SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 100 + 200 * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 3, 3, 3, 6, g_aEnemy[nCntEnemy].nAtk, ANIMATION_LOOP, EXPLOSIONSTATE_DELETE, USETYPE_IGNORE, 0, D3DX_PI);
			SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 200 + 400 * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 3, 3, 3, 6, g_aEnemy[nCntEnemy].nAtk, ANIMATION_LOOP, EXPLOSIONSTATE_DELETE, USETYPE_IGNORE, 0, D3DX_PI);
			SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 300 + 600 * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 3, 3, 3, 6, g_aEnemy[nCntEnemy].nAtk, ANIMATION_LOOP, EXPLOSIONSTATE_DELETE, USETYPE_IGNORE, 0, D3DX_PI);
		}
		if (g_aEnemy[nCntEnemy].nCountAttack == 30)
		{//���ꂼ��̏����s��
			if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_ATTACK) { g_aEnemy[nCntEnemy].fMove = 10.0f; }
			if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_FLY)
			{
				g_aEnemy[nCntEnemy].move.y = -17.0f;
				g_aEnemy[nCntEnemy].fMove = 1.0f;
			}
			if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_MAGIC)
			{
				PlaySound(SOUND_LABEL_ATTACK002);
				SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aEnemy[nCntEnemy].nSize * 3, g_aEnemy[nCntEnemy].nSize * 3, 10, 1, 3, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			}
		}

		if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_ATTACK && g_aEnemy[nCntEnemy].nCountAttack > 30)
		{//�ːi�U��
			g_aEnemy[nCntEnemy].fMove -= 0.28f;
			if (g_aEnemy[nCntEnemy].fMove < 0.0f) { g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND; }
		}
		else if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_FLY && g_aEnemy[nCntEnemy].nCountAttack % 10 == 0 && g_aEnemy[nCntEnemy].nCountAttack > 49 && g_aEnemy[nCntEnemy].nCountAttack < 71)
		{//JUMP
			fSteep = atan2f(pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer[0].pos.y - g_aEnemy[nCntEnemy].pos.y);
			SetBullet(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nCollisionX + (g_aEnemy[nCntEnemy].nCollisionX * 2) * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_NONE, fSteep, 0.0f, 30, 60, 0, g_aEnemy[nCntEnemy].nAtk / 2, 3.0f, BULLETTYPE_ENEMY, nCntEnemy);
		}
		else if (g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_FLY && g_aEnemy[nCntEnemy].nCountAttack == 90)
		{ 
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_FIND;
			g_aEnemy[nCntEnemy].fMove = 0.0f;
		}
		else if (g_aEnemy[nCntEnemy].nCountAttack == 60 && g_aEnemy[nCntEnemy].effect == ENEMYEFFECT_MAGIC)
		{
			SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 100 + 200 * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 3, 3, 3, 7, g_aEnemy[nCntEnemy].nAtk, ANIMATION_LOOP, EXPLOSIONSTATE_PHITMINUS, USETYPE_IGNORE, 0, D3DX_PI);
			SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 200 + 400 * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 3, 3, 3, 7, g_aEnemy[nCntEnemy].nAtk, ANIMATION_LOOP, EXPLOSIONSTATE_PHITMINUS, USETYPE_IGNORE, 0, D3DX_PI);
			SetExplosion(D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 300 + 600 * g_aEnemy[nCntEnemy].nAngle, g_aEnemy[nCntEnemy].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 200, 3, 3, 3, 7, g_aEnemy[nCntEnemy].nAtk, ANIMATION_LOOP, EXPLOSIONSTATE_PHITMINUS, USETYPE_IGNORE, 0, D3DX_PI);
			g_aEnemy[nCntEnemy].nCountAttack += 160;
		}
		if (g_aEnemy[nCntEnemy].nCountAttack < 3)
		{//�U����������U���܂�
			if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x > 3) { g_aEnemy[nCntEnemy].nAngle = 0; }
			else if (g_aEnemy[nCntEnemy].pos.x - pPlayer[0].pos.x < 3) { g_aEnemy[nCntEnemy].nAngle = 1; }
		}
		break;
	}
}

//=========================================================================================================//
// * �SAnimation�X�N���[������
//=========================================================================================================//
void EnemyScroll(D3DXVECTOR3 move)
{
	int nCntEnemy;
	PLAYERSTATE state = PLAYERSTATE_NORMAL;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true || g_aEnemy[nCntEnemy].bRespawn == true)
		{//�X�N���[��
			g_aEnemy[nCntEnemy].posold += D3DXVECTOR3(move.x, move.y - 1.0f, 0.0f);
			g_aEnemy[nCntEnemy].pos += move;
			g_aEnemy[nCntEnemy].respawn += move;
			CollisionBlock(&g_aEnemy[nCntEnemy].pos, &g_aEnemy[nCntEnemy].posold, &g_aEnemy[nCntEnemy].move, NULL, false, &state, g_aEnemy[nCntEnemy].nCollisionX, g_aEnemy[nCntEnemy].nCollisionY, nCntEnemy, USETYPE_ENEMY);
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// �`�揈��
//=========================================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntEnemy;		// �G�J�E���g

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource
	(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D *pVtx;					// ���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= 0 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= 0)
		{// �G������ꍇ
			// ���_�J���[�ݒ�
			pVtx[nCntEnemy * 4].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 1].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 2].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 3].col = g_aEnemy[nCntEnemy].col;

			if (g_aEnemy[nCntEnemy].nTexType == ENEMYTEXTYPE_ENEMY)
			{
				//// ���_�ݒ�
				//pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
				//pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
				//pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
				//pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);

				pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);

				// �e�N�X�`���ݒ�
				pVtx[nCntEnemy * 4 + g_aEnemy[nCntEnemy].nAngle].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * (1.0f / ENEMY_TEXTURE_UV_U), 1.0f / ENEMY_TEXTURE_UV_V * g_aEnemy[nCntEnemy].nTexNum);
				pVtx[nCntEnemy * 4 + g_aEnemy[nCntEnemy].nAngle ^ 1].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * (1.0f / ENEMY_TEXTURE_UV_U) + (1.0f / ENEMY_TEXTURE_UV_U), 1.0f / ENEMY_TEXTURE_UV_V * g_aEnemy[nCntEnemy].nTexNum);
				pVtx[nCntEnemy * 4 + 2 + g_aEnemy[nCntEnemy].nAngle].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * (1.0f / ENEMY_TEXTURE_UV_U), 1.0f / ENEMY_TEXTURE_UV_V * g_aEnemy[nCntEnemy].nTexNum + 1.0f / ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 2 + g_aEnemy[nCntEnemy].nAngle ^ 1].tex = D3DXVECTOR2(g_aEnemy[nCntEnemy].nPatternAnim * (1.0f / ENEMY_TEXTURE_UV_U) + (1.0f / ENEMY_TEXTURE_UV_U), 1.0f / ENEMY_TEXTURE_UV_V * g_aEnemy[nCntEnemy].nTexNum + 1.0f / ENEMY_TEXTURE_UV_V);
			}
			else
			{
				pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) + (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), g_aEnemy[nCntEnemy].pos.y + (sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize) - (cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nSize), 0.0f);
				// �e�N�X�`���ݒ�
				pVtx[nCntEnemy * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nTexType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
		else if(g_aEnemy[nCntEnemy].fplusSteep != 0.0f)
		{ g_aEnemy[nCntEnemy].bUse = false; }
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// �G�̐ݒ菈��
//=========================================================================================================================
void SetEnemy(D3DXVECTOR3 pos, ENEMYTEXTYPE nTexType, ENEMYTEX nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, float steep , ENEMYTYPE Type)
{
	int nCntEnemy;				// �G�J�E���g

	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

								//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == false && g_aEnemy[nCntEnemy].bRespawn == false)
		{// �G���g�p����Ă��Ȃ�
			g_aEnemy[nCntEnemy].respawn = pos;								//�����ʒu
			g_aEnemy[nCntEnemy].pos = pos;									// �ʒu�ݒ�
			g_aEnemy[nCntEnemy].posold = pos;									// �ʒu�ݒ�
			g_aEnemy[nCntEnemy].effect = ENEMYEFFECT_NORMAL;				// ���ʏ�����
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �G�ړ��l
			g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
			g_aEnemy[nCntEnemy].nTexNum = nTexNum;							// �e�N�X�`���ԍ��ݒ�
			g_aEnemy[nCntEnemy].nTexType = nTexType;
			g_aEnemy[nCntEnemy].nSize = nSize;								// �傫���ݒ�
			g_aEnemy[nCntEnemy].nLife = nLife;								// �̗͐ݒ�
			g_aEnemy[nCntEnemy].nMaxLife = nLife;								// �̗͐ݒ�
			g_aEnemy[nCntEnemy].type = Type;								// �G��ނ�ݒ�
			g_aEnemy[nCntEnemy].nAtk = nAtk;
			g_aEnemy[nCntEnemy].nDff = nDff;
			g_aEnemy[nCntEnemy].nEXP = nEXP;
			g_aEnemy[nCntEnemy].nGold = nGold;
			g_aEnemy[nCntEnemy].nScore = nScore;
			g_aEnemy[nCntEnemy].fplusSteep = 0.0f;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					// ��Ԃ�ݒ�
			g_aEnemy[nCntEnemy].nCounterState = 0;							// ��ԃJ�E���^�����l�ݒ�
			g_aEnemy[nCntEnemy].nCountereffect = 0;
			g_aEnemy[nCntEnemy].nCounterAnim = 0;							// �J�E���^�[�����l�ݒ�
			g_aEnemy[nCntEnemy].nPatternAnim = 1;							// �p�^�[��No.�����l�ݒ�
			g_aEnemy[nCntEnemy].nCountAttack = 0;
			g_aEnemy[nCntEnemy].fMove = 0.0f;									//�ړ��l�ۑ�
			g_aEnemy[nCntEnemy].fSteep = D3DX_PI;
			g_aEnemy[nCntEnemy].nAngle = 1;
			g_aEnemy[nCntEnemy].nCounterDamage = -1;
			g_aEnemy[nCntEnemy].bUse = true;								// �g�p���Ă����Ԃɂ���
			g_aEnemy[nCntEnemy].nResCount = 0;

			if (g_aEnemy[nCntEnemy].nTexType == ENEMYTEXTYPE_ENEMY)
			{//TRAP�łȂ��Ȃ�
				if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_BICSLIME)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NOTBACK_S;
					g_aEnemy[nCntEnemy].nTexNum = ENEMYTEX_SLIME;
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 70 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 70 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_SLIME)
				{//�X���C���̂����蔻��
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 70 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 70 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_BAT)
				{//�R�E�����̂����蔻��
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 75 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 80 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_WOLF)
				{//�r�[�X�g�̂����蔻��
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 90 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 90 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_GIANT)
				{//���l�̂����蔻��
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_HALFBACK;					// ��Ԃ�ݒ�
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 80 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 100 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_MYSTERY)
				{//��̐����̂����蔻��
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_HALFBACK;					// ��Ԃ�ݒ�
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 90 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 100 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_R_DRAGON)
				{//�h���S���̂����蔻��
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 80 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 70 / 100;
				}
				else if (g_aEnemy[nCntEnemy].nTexNum == ENEMYTEX_DEATH)
				{//���_(�{�X)�̂����蔻��
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_HALFBACK;					// ��Ԃ�ݒ�
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 100 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 80 / 100;
				}
			}
			if (g_aEnemy[nCntEnemy].nTexType == ENEMYTEXTYPE_TRAP)
			{
					g_aEnemy[nCntEnemy].nCollisionX = nSize * 65 / 100;
					g_aEnemy[nCntEnemy].nCollisionY = nSize * 150 / 100;
			}
			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// �G�̎擾
//=========================================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];		// �l��Ԃ�
}

//=========================================================================================================================
// �G�̎擾
//=========================================================================================================================
void CleanEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//��ʊO&&�{�X�ȊO
		if (g_aEnemy[nCntEnemy].bUse == true && g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize <= SCREEN_WIDTH && g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize >= 0 && g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize <= SCREEN_HEIGHT && g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize >= 0){}
		else if(g_aEnemy[nCntEnemy].type != ENEMYTYPE_BOSSENEMY){ g_aEnemy[nCntEnemy].bUse = false; }
	}
}
//=========================================================================================================================
// �G�̒e�����菈��
//=========================================================================================================================
void HitEnemy(int nCntEnemy, int nAtk, float fAngle, USETYPE type)
{

		int nDamage;
		int nScore = 0;
		int nRand[2];
		int nLife = g_aEnemy[nCntEnemy].nLife;
		nRand[0] = rand() % 10 + 100;	//�f�B�t�F���X�����h
		nRand[1] = rand() % 5 + 55;	//�f�B�t�F���X�����h
		PLAYER *pPlayer = GetPlayer();
		if (g_aEnemy[nCntEnemy].nTexType != ENEMYTEXTYPE_TRAP)
		{
		//float fSteep = atan2f(pPlayer[0].pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer[0].pos.y - g_aEnemy[nCntEnemy].pos.y);
		//float nTargetLengthX = sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nCollisionX + sinf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nCollisionY;
		//float nTargetLengthY = cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nCollisionX + cosf(g_aEnemy[nCntEnemy].fSteep) * g_aEnemy[nCntEnemy].nCollisionY;
		//float fPercentX;
		//float fPercentY;

		//if (nTargetLengthY > nTargetLengthX || nTargetLengthY < nTargetLengthX)
		//{//�|���S����XY�̔䗦�ɉ����Ċp�x��蒼��
		//	if (nTargetLengthY > nTargetLengthX)
		//	{//Y���������ꍇ�@Y�̔䗦�ۑ�
		//		fPercentX = sinf(fSteep) * nTargetLengthY / nTargetLengthX;
		//		fPercentY = cosf(fSteep) * 1.0f;
		//	}
		//	if (nTargetLengthY < nTargetLengthX)
		//	{//X���������ꍇ�@X�̔䗦�ۑ�
		//		fPercentX = sinf(fSteep) * 1.0f;
		//		fPercentY = cosf(fSteep) * nTargetLengthX / nTargetLengthY;
		//	}
		//	fSteep = atan2f(fPercentX, fPercentY);//�p�x��蒼��
		//}

		// ���C�t������
		nDamage = (nAtk * nRand[0] / 100) - (g_aEnemy[nCntEnemy].nDff * nRand[1] / 100);
		if (nDamage < 0) { nDamage = 1; }
		//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30, 30, 5, 1, 2, 2, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		PlaySound(SOUND_LABEL_ATTACK003);
		g_aEnemy[nCntEnemy].nLife -= nDamage;
		//SetDigital(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.4f, 0.98f, 1.0f, 0.0f), DIGITALSTATE_WAVE, 9, 15, nDamage);

		if (g_aEnemy[nCntEnemy].nLife <= 0)
		{// ���C�t��0�ȉ��ɂȂ����ꍇ
			SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 2, 2, 0, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			g_aEnemy[nCntEnemy].fplusSteep = D3DX_PI * 0.2f;
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(8.0f, -50.0f, 0.0f);
			pPlayer[0].nScore += g_aEnemy[nCntEnemy].nScore;
			SetDigital(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_WAVE, 20, 30, g_aEnemy[nCntEnemy].nScore);
			//SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		}

	}
}