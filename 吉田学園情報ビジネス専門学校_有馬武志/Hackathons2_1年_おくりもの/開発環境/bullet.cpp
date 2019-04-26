//=========================================================================================================//
//
// [�e����]->�e�ړ����� [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"				//�������ĂԂ���
#include "enemy.h"				//�G�̏ꏊ�m�F�̂���
#include "sound.h"

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define BULLET_VERTEX_NUM			(4)					// ���_�̐�
#define BULLET_PRIMITIVE_NUM		(2)					// �v���~�e�B�u�̐�
#define BULLET_TextureName		"data/TEXTURE/AllPresent.png"
#define BULLET_MAX_Texture			(1)					//�摜�̎��
#define	MAX_BULLET			(128)				// �e�̍ő吔
#define HIT_PLUS			(3.0f)				//�GHit����̒e�̑傫���̔{��
#define HIT_SAFE			(0.55f)				//���@Hit����̒e�̑傫���̔{��
#define KNIFE_STEEP			(D3DX_PI * -0.55f)	//�i�C�t�̏����p�x
#define KNIFE_STEEPENEMY	(D3DX_PI * -0.45f)	//�i�C�t�̏����p�x
#define BULLET_SLIP			(0.15f)				//�e�̊���
#define BULLET_DELETE		(0)
#define BULLET_DELETE1		(1)

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^		

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBullet;

	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	// �e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//g_aBullet[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aBullet[nCntBullet].steep = 0.0f;
		//g_aBullet[nCntBullet].nType = 0;
		//g_aBullet[nCntBullet].nAtkType = 0;
		//g_aBullet[nCntBullet].nShot = 0;
		//g_aBullet[nCntBullet].nLengthX = 0;
		//g_aBullet[nCntBullet].nLengthY = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TextureName, &g_pTextureBullet[0]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * BULLET_VERTEX_NUM * MAX_BULLET,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		/*pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);*/

		pVtx[nCntBullet * 4].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 1].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 2].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 3].rhw = 1.0f;

		//�J���[�ݒ�
		pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = �����x
		pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�ݒ�
		pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitBullet(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < BULLET_MAX_Texture; nCntTexture++)
	{
		if (g_pTextureBullet[nCntTexture] != NULL)
		{
			g_pTextureBullet[nCntTexture]->Release();
			g_pTextureBullet[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateBullet(void)
{
	static int nCntTime = 100;
	static int nCntGuard = 100;
	int nCntBullet;			//�e������`
	int nCntEnemy;
	bool bHit;
	Enemy *pEnemy = GetEnemy();

	Bullet *g_aBullet;
	PLAYER *pPlayer;
	g_aBullet = GetBullet();
	pPlayer = GetPlayer();
	nCntTime++;
	nCntGuard++;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		if (g_aBullet[nCntBullet].bUse == true)
		{//�e��O�ɔ�΂�
		 //MessageBox(0, "�{�������H", "�I��", MB_YESNO);
			g_aBullet[nCntBullet].posold = g_aBullet[nCntBullet].pos;
			g_aBullet[nCntBullet].nCntState++;
			switch (g_aBullet[nCntBullet].state)
			{
			case BULLETSTATE_NONE:			//���ʂɔ��
				g_aBullet[nCntBullet].nCntState++;
				g_aBullet[nCntBullet].move.x += g_aBullet[nCntBullet].fSpeed;
				SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 50, 5, 2, 2, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
				if (g_aBullet[nCntBullet].nCntState > 60)
				{ 
					g_aBullet[nCntBullet].state = BULLETSTATE_DELETE;
					SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 2, 2, 0, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
				}
				g_aBullet[nCntBullet].steep += D3DX_PI * 0.2f;
				break;
			case BULLETSTATE_GRAVITY:
				SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30, 30, 5, 1, 2, 2, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);

				g_aBullet[nCntBullet].nCntState++;
				g_aBullet[nCntBullet].move.y += 1.0f;
				g_aBullet[nCntBullet].move.x += g_aBullet[nCntBullet].fSpeed;
				g_aBullet[nCntBullet].fSpeed -= g_aBullet[nCntBullet].fSpeed * 0.05f;
				g_aBullet[nCntBullet].steep += D3DX_PI * 0.2f;
				if (g_aBullet[nCntBullet].fSpeed < 0.0f) { g_aBullet[nCntBullet].fSpeed = 0.1f; }
				if (g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT) { g_aBullet[nCntBullet].state = BULLETSTATE_DELETE; }
				break;
			case BULLETSTATE_NORMAL:
				g_aBullet[nCntBullet].nCntState++;
				g_aBullet[nCntBullet].move += D3DXVECTOR3(sinf(g_aBullet[nCntBullet].steep), cosf(g_aBullet[nCntBullet].steep), 0.0f) * g_aBullet[nCntBullet].fSpeed;
				if (g_aBullet[nCntBullet].nCntState > 60) { g_aBullet[nCntBullet].state = BULLETSTATE_DELETE; }
				break;
			case BULLETSTATE_DELETE:		//�����Ă���

				g_aBullet[nCntBullet].move += D3DXVECTOR3(sinf(g_aBullet[nCntBullet].steep), cosf(g_aBullet[nCntBullet].steep), 0.0f) * g_aBullet[nCntBullet].fSpeed * g_aBullet[nCntBullet].col.a * 0.5f;
				g_aBullet[nCntBullet].col.a -= 1.0f;
				//pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);	// A = �����x
				//pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);
				//pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);
				//pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);
				if (g_aBullet[nCntBullet].col.a <= 0.0f) { g_aBullet[nCntBullet].bUse = false; }
				break;
			case BULLETSTATE_SINGLE:	//1F�ŏ�����@�摜�̂�
				g_aBullet[nCntBullet].bUse = false;
				break;
			case BULLETSTATE_THIRD:		//3F�ŏ�����
				if(g_aBullet[nCntBullet].nCntState > 2){ g_aBullet[nCntBullet].bUse = false; }
				break;
			case BULLETSTATE_FIFTH:		//5F�ŏ�����
				if (g_aBullet[nCntBullet].nCntState > 4) { g_aBullet[nCntBullet].bUse = false; }
				break;
			}
			g_aBullet[nCntBullet].steep += g_aBullet[nCntBullet].fCurve;
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			//�ړ��ʒቺ(��C��R���̂���)
			g_aBullet[nCntBullet].move.x += (0.0f - g_aBullet[nCntBullet].move.x) * BULLET_SLIP;
			g_aBullet[nCntBullet].move.y += (0.0f - g_aBullet[nCntBullet].move.y) * BULLET_SLIP;

			//if (g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].nLengthY <= -BULLET_DELETE || g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].nLengthY >= SCREEN_HEIGHT + BULLET_DELETE || g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].nLengthX <= -BULLET_DELETE || g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].nLengthX >= SCREEN_WIDTH + BULLET_DELETE)
			//{//��ʊO+200�̒e������
			//	g_aBullet[nCntBullet].bUse = false;
			//}

			if (g_aBullet[nCntBullet].nShot == BULLETTYPE_PLAYER && g_aBullet[nCntBullet].state != BULLETSTATE_DELETE && g_aBullet[nCntBullet].state != BULLETSTATE_GRAVITY&& g_aBullet[nCntBullet].state != BULLETSTATE_SINGLE)
			{//���@���������e�Ȃ�
				pEnemy = GetEnemy();
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{//�G�̐��������
					if (pEnemy[nCntEnemy].bUse == true && pEnemy[nCntEnemy].nCounterDamage < 0)
					{//�G������I
						bHit = HitAim(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].nLengthX, g_aBullet[nCntBullet].nLengthY, g_aBullet[nCntBullet].steep, pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].nSize);
						if (bHit == true)
						{//�e���������Ă�
							HitEnemy(nCntEnemy, g_aBullet[nCntBullet].nAtk, pPlayer[0].pos.x - pEnemy[nCntEnemy].pos.x, USETYPE_PLAYER);
							g_aBullet[nCntBullet].bUse = false;
							if (g_aBullet[nCntBullet].nType == 9)
							{//����
								PlaySound(SOUND_LABEL_ATTACK004);
								SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y - 110, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), 30, 150, 10, 1, 2, 0, g_aBullet[nCntBullet].nAtk, ANIMATION_NORMAL, EXPLOSIONSTATE_EHIT, USETYPE_IGNORE, 0, D3DX_PI); }
						}//�q�b�g����
					}//�G���ݔ���
				}//for����
			}
			else if(g_aBullet[nCntBullet].nShot == BULLETTYPE_ENEMY && g_aBullet[nCntBullet].state != BULLETSTATE_DELETE)
			{//�G�����������Ȃ�
				if (pPlayer[0].bUse == true && g_aBullet[nCntBullet].col.a == 1.0f)
				{//���@������I
					bHit = HitAim(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].nLengthX, g_aBullet[nCntBullet].nLengthY, g_aBullet[nCntBullet].steep, pPlayer[0].pos, pPlayer[0].nCollisionX);
					if (bHit == true)
					{//�e���������Ă�
						//g_aBullet[nCntBullet].bUse = false;
						HitPlayer(g_aBullet[nCntBullet].nAtk, g_aBullet[nCntBullet].pos.x - pPlayer[0].pos.x, g_aBullet[nCntBullet].nCntEnemy);
					}//�q�b�g����
				}
			}//���@���ݔ���
			if (g_aBullet[nCntBullet].bUse == true && HitBullet(g_aBullet[nCntBullet]) == true && g_aBullet[nCntBullet].nShot != BULLETTYPE_EFFECT)
			{//�u���b�N�ɓ�������
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
}
//=========================================================================================================//
// * �e�̓����蔻��
//=========================================================================================================//
bool HitAim(D3DXVECTOR3 MyPos, int nMyLengthX, int nMyLengthY, float fMyAngle, D3DXVECTOR3 aim, int nLength)
{
	//HitAim(Bullet pBullet, D3DXVECTOR3 aim, int nLength)

		float fLengthX;			//�e�̒��S����ڕW�̒��S�܂ł̋���X
		float fLengthY;			//�e�̒��S����ڕW�̒��S�܂ł̋���Y
		float fLengthAim;		//�ڕW�܂ł̋���(��)
		float fAimSteep = 1.0;	//�ڕW�܂ł̊p�x -> ������
		float fBullSteep;		//�e�̊p�x
		float fLengthBX;		//�e�̗L���̕�X
		float fLengthBY;		//�e�̗L���̕�Y
		float fLengthB;			//�e�̗L���̕�(���v)
		float fSteep[2] = { 1.0f, 1.0f };	//X���̃}�C�i�X�̕ۑ��p -> ������

		float fPercentY = 1.0f;		//�ȉ~����Y�̔{��
		float fPercentX = 1.0f;		//�ȉ~����X�̔{��

		fLengthX = aim.x - MyPos.x;	//��X����
		fLengthY = aim.y - MyPos.y;	//��Y����
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

		//���ŖڕW�ւ̊p�x->sin, cos�ɕϊ� 100����1.57�Ƃ���
		fAimSteep = fLengthY / (fLengthX + fLengthY) * (D3DX_PI / 2) * fSteep[1];
		fAimSteep = (D3DX_PI / 2 + fAimSteep) * fSteep[0];
		//fAimSteep = atan2f(fLengthX * fSteep[0], fLengthY * fSteep[1]);

		//�e�̊p�x�ƖڕW�̊p�x�̍���
		fBullSteep = fMyAngle;
		if (fBullSteep < 0)
		{//�␳�̕K�v���Ȃ��ꍇ
			fBullSteep = D3DX_PI + fBullSteep;
			fAimSteep -= fBullSteep;
		}
		else
		{//�e�̊p�x���ŏ��l�ɖ߂�
			fBullSteep = D3DX_PI - fBullSteep;
			fAimSteep += fBullSteep;
		}

		if (nMyLengthY > nMyLengthX || nMyLengthY < nMyLengthX)
		{//�|���S����XY�̔䗦�ɉ����Ċp�x��蒼��
			if (nMyLengthY > nMyLengthX)
			{//Y���������ꍇ�@Y�̔䗦�ۑ�
				fPercentX = sinf(fAimSteep) * nMyLengthY / nMyLengthX;
				fPercentY = cosf(fAimSteep) * 1.0f;
			}
			if (nMyLengthY < nMyLengthX)
			{//X���������ꍇ�@X�̔䗦�ۑ�
				fPercentX = sinf(fAimSteep) * 1.0f;
				fPercentY = cosf(fAimSteep) * nMyLengthX / nMyLengthY;
			}

			fAimSteep = 1;	//�p�x������
			fSteep[0] = 1;	//�}�C�i�X�ۑ��p��������
			if (fPercentX < 0.0f)
			{//X���̃}�C�i�X�ۑ�
				fPercentX *= -1;
				fSteep[0] = -1;
			}
			if (fPercentY < 0.0f)
			{//Y���̃}�C�i�X�ۑ�
				fPercentY *= -1;
				fAimSteep = -1;
			}
			//���ŖڕW�ւ̊p�x->sin, cos�ɕϊ� 100����1.57�Ƃ��� �ȉ~����
			fAimSteep = fPercentY / (fPercentX + fPercentY) * (D3DX_PI / 2) * fAimSteep;
			fAimSteep = (D3DX_PI / 2 + fAimSteep) * fSteep[0];
		}

		fLengthBY = cosf(fAimSteep) * nMyLengthY;
		fLengthBX = sinf(fAimSteep) * nMyLengthX;

		fLengthB = (fLengthBX + fLengthBY) * (fLengthBX + fLengthBY);	//�e�̗L���ȕ�(���v)����

		if (fLengthAim < fLengthB)
		{//����@2�悳�ꂽ��ԂȂ̂�
			return true;
		}
		else
		{
			return false;
		}
	}

//=========================================================================================================//
// * �e�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//// ���u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, 2);
	
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	// �|���S���̕`��

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);

			pVtx[nCntBullet * 4].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2));
			pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2) + (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2));
			pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2) + (1.0f / 2));
			pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2) + (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2) + (1.0f / 2));

			//�J���[�ݒ�
			pVtx[nCntBullet * 4].col = g_aBullet[nCntBullet].col;	// A = �����x
			pVtx[nCntBullet * 4 + 1].col = g_aBullet[nCntBullet].col;
			pVtx[nCntBullet * 4 + 2].col = g_aBullet[nCntBullet].col;
			pVtx[nCntBullet * 4 + 3].col = g_aBullet[nCntBullet].col;

			pDevice->SetTexture(0, g_pTextureBullet[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, BULLET_PRIMITIVE_NUM);
		}
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffBullet->Unlock();
	//// ���u�����f�B���O�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXCOLOR col, BULLETSTATE state, float steep, float fCurve, int nLengthX, int nLengthY, int nType, int nAtk, float fSpeed, BULLETTYPE nShot, int nCntEnemy)
{
	int nCntBullet;			//�e������́`
	int nClear = 255;		//�����ݒ�̂���
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			//�܂Ƃ߂ď�����
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].state = state;
			g_aBullet[nCntBullet].nCntState = 0;
			g_aBullet[nCntBullet].nLengthX = nLengthX;
			g_aBullet[nCntBullet].nLengthY = nLengthY;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].nAtk = nAtk;
			g_aBullet[nCntBullet].nShot = nShot;
			g_aBullet[nCntBullet].nCntEnemy = nCntEnemy;
			g_aBullet[nCntBullet].steep = steep;
			g_aBullet[nCntBullet].fCurve = fCurve;
			g_aBullet[nCntBullet].fSpeed = fSpeed;
			g_aBullet[nCntBullet].bUse = true;
			if (g_aBullet[nCntBullet].state == BULLETSTATE_GRAVITY) { g_aBullet[nCntBullet].move.y = -25.0f; }
			break;
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void StartBullet(int nCntEnemy, int nCntAtk)
{
	int nCntBullet;
	Bullet *g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].nCntEnemy == nCntEnemy && g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].nCntState = 0;
		}
	}
}
//=========================================================================================================//
// * �SAnimation�X�N���[������
//=========================================================================================================//
void BulletScroll(D3DXVECTOR3 move)
{
	int nCntBullet;
	Bullet *g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�X�N���[��
			g_aBullet[nCntBullet].pos += move;
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void BreakBullet(void)
{
	int nCntBullet;
	Bullet *g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].bUse = false;
	}
}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void BreakBullet(int nCntEnemy)
{
	int nCntBullet;
	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//�w�肵���G�l�~�[�̒e��j��
		if(g_aBullet[nCntBullet].nCntEnemy == nCntEnemy)
		{ 
			g_aBullet[nCntBullet].state = BULLETSTATE_DELETE;
			//ExplosionEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR{ 1.0f, 0.05f, 0.05f, 0.75f }, 100, 100, 0.1f, g_aBullet[nCntBullet].nLengthX * 0.05f, 0.1f, 1.0f);
		}
		//�G�t�F�N�g�~������
	}
}
//=============================================================================
// �e�̎擾
//=============================================================================
Bullet *GetBullet(void)
{
	static Bullet bullet[MAX_BULLET];//�e�̍ő吔

	return &bullet[0];
}