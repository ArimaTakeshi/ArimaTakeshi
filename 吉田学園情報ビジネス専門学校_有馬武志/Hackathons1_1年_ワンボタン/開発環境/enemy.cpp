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
#include "sound.h"			// �T�E���h

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_ENEMY_TEXTURE				(6)									// �G�̎��
#define ENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\Zako01.png"		// �ǂݍ��ރe�N�X�`���t�@�C��1
#define ENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\Zako02.png"		// �ǂݍ��ރe�N�X�`���t�@�C��2
#define ENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\Zako03.png"		// �ǂݍ��ރe�N�X�`���t�@�C��3
#define ENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\Boss01.png"		// �ǂݍ��ރe�N�X�`���t�@�C��4
#define ENEMY_TEXTURE_NAME_5			"data\\TEXTURE\\Boss02.png"		// �ǂݍ��ރe�N�X�`���t�@�C��5
#define ENEMY_TEXTURE_NAME_6			"data\\TEXTURE\\Boss03.png"		// �ǂݍ��ރe�N�X�`���t�@�C��5

#define ENEMY_TEXTURE_SPEED				(15)								// �e�N�X�`���A�j���[�V�����X�s�[�h
#define ENEMY_TEXTURE_PATTERN			(1)									// �e�N�X�`���A�j���[�V�����p�^�[����
#define ENEMY_TEXTURE_UV_U				(1.0f)								// �e�N�X�`���A�j���[�V����U�͈�
#define ENEMY_TEXTURE_UV_V				(1.0f)								// �e�N�X�`���A�j���[�V����V�͈�
#define ENEMY_SPEED						(10)								// �G�ړ����x

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
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G���S�l
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�ړ��l
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �G�F
		g_aEnemy[nCntEnemy].nTexNum = 0;									// �G���
		g_aEnemy[nCntEnemy].nLife = 0;										// �G�̗�
		g_aEnemy[nCntEnemy].Type = ENEMYTYPE_NORMALENEMY;					// �G�N���X
		g_aEnemy[nCntEnemy].State = ENEMYSTATE_NOMAL;						// �G���
		g_aEnemy[nCntEnemy].nCounterState = 0;								// �G��ԃJ�E���g
		g_aEnemy[nCntEnemy].nCounterAnim = 0;								// �G�J�E���^�A�j���[�V����
		g_aEnemy[nCntEnemy].nPatternAnim = 0;								// �G�p�^�[���A�j���[�V����
		g_aEnemy[nCntEnemy].bUse = false;									// �G�g�p���Ă��邩
	}

	// �e�N�X�`���̓ǂݍ���(�T)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_1, &g_apTextureEnemy[0]);// �G1
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_2, &g_apTextureEnemy[1]);// �G2
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_3, &g_apTextureEnemy[2]);// �G3
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_4, &g_apTextureEnemy[3]);// �G4
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_5, &g_apTextureEnemy[4]);// �G5
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_6, &g_apTextureEnemy[5]);// �G5

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
		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		// 1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// ���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

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

	// �e�N�X�`���̔j��
	for(nCntTex = 0; nCntTex < MAX_ENEMY_TEXTURE; nCntTex++)
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

	VERTEX_2D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == true)
		{// �G���g�p����Ă���ꍇ
			switch (g_aEnemy[nCntEnemy].State)
			{// �G���
			case ENEMYSTATE_NOMAL:	// �ʏ���
				break;
			case ENEMYSTATE_DAMAGE:	// �_���[�W���
				g_aEnemy[nCntEnemy].nCounterState--;	// ��Ԃ��J�E���g

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{// ��ԃJ�E���g�I��
					// �F�ύX
					g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// ��ԕω�
					g_aEnemy[nCntEnemy].State = ENEMYSTATE_NOMAL;
				}
				break;
			}
			
			if (-100 > g_aEnemy[nCntEnemy].pos.x || SCREEN_WIDTH + 100 < g_aEnemy[nCntEnemy].pos.x || -100 > g_aEnemy[nCntEnemy].pos.y || SCREEN_HEIGHT + 100 < g_aEnemy[nCntEnemy].pos.y)
			{// ��ʊO�̏ꍇ
				g_aEnemy[nCntEnemy].bUse = false;
				if (g_aEnemy[nCntEnemy].Type == ENEMYTYPE_BOSSENEMY)
				{
					SetGameState(GAMESTATE_END, MODE_RESULT, 150);
				}
			}

			g_aEnemy[nCntEnemy].nCounterAnim++;		// �J�E���^�[���Z

			if ((g_aEnemy[nCntEnemy].nCounterAnim % ENEMY_TEXTURE_SPEED) == 0)
			{// �A�j���[�V�������x
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % ENEMY_TEXTURE_PATTERN;		// �p�^�[��No.�X�V

				// �e�N�X�`���ݒ�
				pVtx[nCntEnemy * 4].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim + ENEMY_TEXTURE_UV_U, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim, ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim + ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);
			}
			PLAYER *pPlayer = GetPlayer();
			if (pPlayer[0].bMove == true)
			{
				g_aEnemy[nCntEnemy].move.x -= 1.5f;
			}
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].move.x += (0.0f - g_aEnemy[nCntEnemy].move.x) * BULLET_SLIP;

			// ���_�ݒ�
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
			// ���_�J���[�ݒ�
			pVtx[nCntEnemy * 4].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 1].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 2].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 3].col = g_aEnemy[nCntEnemy].col;
		}
	}

	// ���_�o�b�t�@���A�����b�N
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
	(
		0,
		g_pVtxBuffEnemy,
		0,
		sizeof(VERTEX_2D)
	);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == true)
		{// �G������ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nTexNum]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// �G�̐ݒ菈��
//=========================================================================================================================
void SetEnemy(D3DXVECTOR3 pos, int nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, ENEMYTYPE Type)
{
	int nCntEnemy;				// �G�J�E���g

	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G���J�E���g
		if (g_aEnemy[nCntEnemy].bUse == false)
		{// �G���g�p����Ă��Ȃ�
			g_aEnemy[nCntEnemy].pos = pos;									// �ʒu�ݒ�
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�ړ��l
			g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
			g_aEnemy[nCntEnemy].nTexNum = nTexNum;							// �e�N�X�`���ԍ��ݒ�
			g_aEnemy[nCntEnemy].nSize = nSize;								// �傫���ݒ�
			g_aEnemy[nCntEnemy].nLife = nLife;								// �̗͐ݒ�
			g_aEnemy[nCntEnemy].Type = Type;								// �G��ނ�ݒ�
			g_aEnemy[nCntEnemy].nAtk = nAtk;
			g_aEnemy[nCntEnemy].nDff = nDff;
			g_aEnemy[nCntEnemy].nEXP = nEXP;
			g_aEnemy[nCntEnemy].nGold = nGold;
			g_aEnemy[nCntEnemy].nScore;
			g_aEnemy[nCntEnemy].State = ENEMYSTATE_NOMAL;					// ��Ԃ�ݒ�
			g_aEnemy[nCntEnemy].nCounterState = 0;							// ��ԃJ�E���^�����l�ݒ�
			g_aEnemy[nCntEnemy].nCounterAnim = 0;							// �J�E���^�[�����l�ݒ�
			g_aEnemy[nCntEnemy].nPatternAnim = 0;							// �p�^�[��No.�����l�ݒ�
			g_aEnemy[nCntEnemy].bUse = true;								// �g�p���Ă����Ԃɂ���

			// ���_�ݒ�
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);

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
// �G�̒e�����菈��
//=========================================================================================================================
void HitEnemy(int nCntEnemy, int nAtk)
{
	int nDamage;
	int nRand;
	char aStr[256];
	nRand = rand() % 40 + 20;
	PLAYER *pPlayer = GetPlayer();
	int nCount;
	for (nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		g_aEnemy[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	// ���C�t������
	nDamage = nAtk - (g_aEnemy[nCntEnemy].nDff * nRand / 100);
	if (nDamage < 0) { nDamage = 1; }
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	wsprintf(&aStr[0], "%d", nDamage);
	SetFont(RECT{ (int)g_aEnemy[nCntEnemy].pos.x - 50 , (int)g_aEnemy[nCntEnemy].pos.y - 50, (int)g_aEnemy[nCntEnemy].pos.x + 50, (int)g_aEnemy[nCntEnemy].pos.y }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 3, FONTSTATE_RANKDELETE);
	pPlayer[0].nScore += nDamage;
	pPlayer[0].nGold += nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{// ���C�t��0�ȉ��ɂȂ����ꍇ
		g_aEnemy[nCntEnemy].bUse = false;				// �g�p���ĂȂ����
		pPlayer[0].nScore += g_aEnemy[nCntEnemy].nScore;
		pPlayer[0].nEXP += g_aEnemy[nCntEnemy].nEXP;
		pPlayer[0].nGold += g_aEnemy[0].nGold;
		if (pPlayer[0].nEXP >= pPlayer[0].nMAX_EXP)
		{//���x���A�b�v�����ꍇ
			while (1)
			{
				pPlayer[0].nLevel++;
				pPlayer[0].nEXP -= pPlayer[0].nMAX_EXP;
				pPlayer[0].nMAX_EXP = pPlayer[0].nMAX_EXP * 130 / 100;
				pPlayer[0].nMAX_HP += 15;
				pPlayer[0].nAttack += 5;
				pPlayer[0].nDefense += 3;
				pPlayer[0].nHP = pPlayer[0].nMAX_HP;
				PlaySound(SOUND_LABEL_BOTTON003);//���x���A�b�v���S
				if (pPlayer[0].nEXP < pPlayer[0].nMAX_EXP) { break; }
			}
		}
		if (g_aEnemy[nCntEnemy].Type == ENEMYTYPE_BOSSENEMY)
		{
			pPlayer[0].nScore += pPlayer[0].nGold;
			pPlayer[0].nScore += pPlayer[0].nMeter;
			SetGameState(GAMESTATE_END, MODE_RESULT, 150);
		}
	}
	else
	{// ���C�t��1�ȏ�̏ꍇ
		g_aEnemy[nCntEnemy].State = ENEMYSTATE_DAMAGE;		// ��ԕω�
		g_aEnemy[nCntEnemy].nCounterState = 5;				// ��ԃJ�E���^

		// �F�ύX
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	}
}