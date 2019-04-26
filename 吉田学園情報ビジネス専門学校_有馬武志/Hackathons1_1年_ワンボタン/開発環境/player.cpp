//=========================================================================================================//
//
// ���@ ���� [player.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "input.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "enemy.h"
#include <stdlib.h>				//�����h�p
#include <time.h>				//�����������h�p

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_BUFFER�ւ̃|�C���^
PLAYER g_Player;
int g_nAppears;

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define PLAYER_TextureName		"data/TEXTURE/player000.png"	//TEXTURE�̖��O
#define VERTEX_NUM				(4)				// ���_�̐�
#define PRIMITIVE_NUM			(2)				// �v���~�e�B�u�̐�
#define RECAST_TIME				(4)				//�e�̔��ˑ��x

#define MOVEPOLYGON				(1.0f)			//�|���S���̐i�ޑ���
#define SLIPPLAYER				(0.12f)
#define WIDETEXTURE				(0.5f)			//TEXTURE�̕�
#define HEIGHTTEXTURE			(1.0f)			//TEXTURE�̍���
#define FIELD					(SCREEN_HEIGHT / 10 * 8)


//=========================================================================================================//
// * �v���C���[�̕`�揈��1	����������
//=========================================================================================================//
void InitPlayer(void)
{
	srand((unsigned int)time(0));
	LPDIRECT3DDEVICE9 pDevice;	
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3{ 0.0f, FIELD, 0.0f };		//�|���S���̒��S
	g_Player.move = D3DXVECTOR3{ 0,0,0.0f };	//�|���S���̈ړ�
	g_Player.nHP = 100;
	g_Player.nLevel = 1;
	g_Player.nMAX_HP = 100;
	g_Player.nAttack = 10;
	g_Player.nDefense = 5;
	g_Player.nJump = 0;
	g_Player.nCntAnim = 0;
	g_Player.nPtnAnim = 0;
	g_Player.nMeter = 0;
	g_Player.nEXP = 0;
	g_Player.nGold = 0;
	g_Player.nScore = 0;
	g_Player.nMAX_EXP = 50;
	g_Player.fAngle = D3DX_PI;
	g_Player.bMove = false;
	g_Player.bUse = true;

	g_nAppears = 0;

	D3DXCreateTextureFromFile(pDevice, PLAYER_TextureName, &g_pTexturePlayer);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// A = �����x
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(WIDETEXTURE, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, HEIGHTTEXTURE);
	pVtx[3].tex = D3DXVECTOR2(WIDETEXTURE, HEIGHTTEXTURE);

	//���_BUFFER���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}
//=========================================================================================================//
// * �v���C���[�̕`�揈��2	�I������
//=========================================================================================================//
void UninitPlayer(void)
{//�e�N�X�`���̔j��
	g_Player.bUse = false;
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//=========================================================================================================//
// * �v���C���[�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdatePlayer(void)
{
	int nCntEnemy;
	static int nCntTime;
	char aStr[256];

	if (g_Player.bUse == true)
	{
		nCntTime++;
		if (nCntTime % 30 == 0 && g_Player.nHP < g_Player.nMAX_HP) { g_Player.nHP++; }
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
		//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_Player.nCntAnim++;
		if (GetKeyboardTrigger(DIK_RETURN) == true && g_Player.nJump < 2)
		{//�W�����v��2��܂�
			g_Player.move.y = -20.0f;
			g_Player.nJump++;
			PlaySound(SOUND_LABEL_BOTTON001);
		}
		if (g_Player.nJump == 2) { g_Player.fAngle -= 0.13f; }
		if (g_Player.pos.y < FIELD) { g_Player.move.y += 1.0f; }

		if (g_Player.pos.x > SCREEN_WIDTH / 3)
		{
			g_Player.bMove = true;
			g_Player.move.x = 0.0f;
			g_Player.nMeter++;
			EnemyAppears();
		}
		else
		{
			g_Player.bMove = false;
			g_Player.move.x += 1.5f;
		}

		g_Player.pos += g_Player.move;//x�ړ��̂�
		//�ړ��ʒቺ(��C��R���̂���)
		g_Player.move.x += (0.0f - g_Player.move.x) * BULLET_SLIP;
		if (g_Player.pos.y > FIELD)
		{
			g_Player.pos.y = FIELD;
			g_Player.nJump = 0;
			g_Player.fAngle = D3DX_PI;
		}

		//���_���W�̐ݒ�
		//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);

		Enemy *pEnemy = GetEnemy();
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{
			if (pEnemy[nCntEnemy].bUse == true)
			{
				if (HitAim(pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].nSize) == true && pEnemy[nCntEnemy].State != ENEMYSTATE_DAMAGE)
				{//�������Ă���Ȃ�
					g_Player.pos.y = FIELD;
					g_Player.nJump = 0;
					g_Player.fAngle = D3DX_PI;
					g_Player.move.x = 0.0f;
					g_Player.move.x -= 20.0f;
					g_Player.pos.x -= 50;
					HitEnemy(nCntEnemy, g_Player.nAttack);
					HitPlayer(pEnemy[nCntEnemy].nAtk);
					PlaySound(SOUND_LABEL_BOTTON000);
				}
			}
		}

		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fAngle) * PLAYER_POSY3) + (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y - (sinf(g_Player.fAngle) * PLAYER_POSX3) + (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fAngle) * PLAYER_POSY3) - (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y + (sinf(g_Player.fAngle) * PLAYER_POSX3) + (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fAngle) * PLAYER_POSY3) + (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y - (sinf(g_Player.fAngle) * PLAYER_POSX3) - (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fAngle)* PLAYER_POSY3) - (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y + (sinf(g_Player.fAngle) * PLAYER_POSX3) - (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);

		if ((g_Player.nCntAnim % 10) == 0)
		{// �A�j���[�V�������x
			g_Player.nPtnAnim = (g_Player.nPtnAnim + 1) % 2;		// �p�^�[��No.�X�V
																													// �e�N�X�`���ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim + 0.5f, 1.0f);
		}

		//���_BUFFER���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
	wsprintf(&aStr[0], "%d / %d", g_Player.nHP, g_Player.nMAX_HP);
	ChangeFont(true, &aStr[0], 4, FONTSTATE_NONE);
	wsprintf(&aStr[0], "%d", g_Player.nGold);
	ChangeFont(true, &aStr[0], 7, FONTSTATE_NONE);
	wsprintf(&aStr[0], "SCORE�F%d", g_Player.nScore);
	ChangeFont(true, &aStr[0], 6, FONTSTATE_NONE);
	wsprintf(&aStr[0], "���̃��x���܂� %d", g_Player.nMAX_EXP - g_Player.nEXP);
	ChangeFont(true, &aStr[0], 5, FONTSTATE_NONE);
	wsprintf(&aStr[0], "Lv %d", g_Player.nLevel);
	ChangeFont(true, &aStr[0], 8, FONTSTATE_NONE);
}
//=========================================================================================================//
// * �e�̓����蔻��
//=========================================================================================================//
bool HitAim(D3DXVECTOR3 aim, int nLength)
{
	float fLengthX;			//�e�̒��S����ڕW�̒��S�܂ł̋���X
	float fLengthY;			//�e�̒��S����ڕW�̒��S�܂ł̋���Y
	float fLengthAim;		//�ڕW�܂ł̋���(��)
	float fAimSteep = 1.0;	//�ڕW�܂ł̊p�x -> ������
	float fSteep[2] = { 1.0f, 1.0f };	//X���̃}�C�i�X�̕ۑ��p -> ������

	float fPercentY = 1.0f;		//�ȉ~����Y�̔{��
	float fPercentX = 1.0f;		//�ȉ~����X�̔{��

	fLengthX = aim.x - g_Player.pos.x;	//��X����
	fLengthY = aim.y - g_Player.pos.y;	//��Y����
	if (fLengthX < 0.0f)
	{//X�̒l���}�C�i�X�Ȃ�v���X��
		fLengthX *= -1;	//X���]
		fSteep[0] *= -1;	//X�����}�C�i�X��ۑ�
	}
	if (fLengthY < 0.0f)
	{//Y�̒l���}�C�i�X�Ȃ�v���X��
		fLengthY *= -1;		//Y���]
		fSteep[1] *= -1;	//Y�����}�C�i�X��ۑ�
	}


	//����(��)��2��̏�Ԃő��
	fLengthAim = (fLengthX * fLengthX) + (fLengthY * fLengthY);
	fLengthAim -= nLength * nLength;

	
	if (fLengthAim < 60 * 60)
	{//����@2�悳�ꂽ��ԂȂ̂�
		return true;
	}
	else
	{
		return false;
	}
}
//=========================================================================================================//
// * �v���C���[�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X���擾����
	pDevice = GetDevice();

	//���_BUFFER���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

									//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���̕`��
	if (g_Player.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	}

}
//=========================================================================================================//
// * �v���C���[�̏��������
//=========================================================================================================//
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
//=========================================================================================================//
// * �v���C���[�̕`�揈��4	�`�揈��
//=========================================================================================================//
void EnemyAppears(void)
{
	if (g_Player.nMeter == 1 && g_nAppears == 0)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 50 && g_nAppears == 1)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 150 && g_nAppears == 2)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 300 && g_nAppears == 3)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 330 && g_nAppears == 4)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 430 && g_nAppears == 5)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 530 && g_nAppears == 6)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 600 && g_nAppears == 7)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 610 && g_nAppears == 8)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 20, 20, 20, 40, 200, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 620 && g_nAppears == 9)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 680 && g_nAppears == 10)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 750 && g_nAppears == 11)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 800 && g_nAppears == 12)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 900 && g_nAppears == 13)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 910 && g_nAppears == 14)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 920 && g_nAppears == 15)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 930 && g_nAppears == 16)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1100 && g_nAppears == 17)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1150 && g_nAppears == 18)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1180 && g_nAppears == 19)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1200 && g_nAppears == 20)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD - 100, 0.0f), 3, 200, 90, 40, 20, 500, 300, 3000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1220 && g_nAppears == 21)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1225 && g_nAppears == 22)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1230 && g_nAppears == 23)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1270 && g_nAppears == 24)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1370 && g_nAppears == 25)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1375 && g_nAppears == 26)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1380 && g_nAppears == 27)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1385 && g_nAppears == 28)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1390 && g_nAppears == 29)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1450 && g_nAppears == 30)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1480 && g_nAppears == 31)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1510 && g_nAppears == 32)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1515 && g_nAppears == 33)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1520 && g_nAppears == 34)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1525 && g_nAppears == 35)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD - 100, 0.0f), 4, 250, 130, 70, 40, 700, 500, 5000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1600 && g_nAppears == 36)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1605 && g_nAppears == 37)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1610 && g_nAppears == 38)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1615 && g_nAppears == 39)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1620 && g_nAppears == 40)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1625 && g_nAppears == 41)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1630 && g_nAppears == 42)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1730 && g_nAppears == 43)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 80, 40, 40, 100, 500, 30000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1770 && g_nAppears == 44)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 1, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1950 && g_nAppears == 45)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1955 && g_nAppears == 46)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1955 && g_nAppears == 47)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 1, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1960 && g_nAppears == 48)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 1, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1965 && g_nAppears == 49)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 80, 40, 40, 100, 500, 30000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1990 && g_nAppears == 50)
	{//�G�̏o��
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD - 120, 0.0f), 5, 300, 100, 50, 30, 1000, 5000, 100000, ENEMYTYPE_BOSSENEMY);
	}
}
//=========================================================================================================================
// �G�̒e�����菈��
//=========================================================================================================================
void HitPlayer(int nAtk)
{
	int nDamage;
	int nRand;
	char aStr[256];

	nRand = rand() % 15 + 45;
	PLAYER *pPlayer = GetPlayer();

	// ���C�t������
	nDamage = nAtk - (g_Player.nDefense * nRand / 100);
	if (nDamage < 0) { nDamage = 0; }
	g_Player.nHP -= nDamage;
	wsprintf(&aStr[0], "%d", nDamage);
	SetFont(RECT{ (int)g_Player.pos.x - 50 , (int)g_Player.pos.y - 50, (int)g_Player.pos.x + 50, (int)g_Player.pos.y }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 2, FONTSTATE_RANKDELETE);

	g_Player.nScore += nDamage;
	g_Player.nGold += nDamage;

	AddScore(SCORETYPE_RNKING_NO1, g_Player.nScore);

	if (g_Player.nHP < 1)
	{// ���C�t��0�ȉ��ɂȂ����ꍇ
		g_Player.bUse = false;				// �g�p���ĂȂ����
		g_Player.nHP = 0;
		g_Player.bMove = false;
		g_Player.nScore += g_Player.nMeter;
		SetGameState(GAMESTATE_END, MODE_RESULT, 150);
	}
}