//=========================================================================================================//
//
// window���� [window.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "window.h"

#include <stdlib.h>				//�����h�p
#include <time.h>				//�����������h�p

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define WINDOW_VERTEX_NUM			(4)					// ���_�̐�
#define WINDOW_PRIMITIVE_NUM		(2)					// �v���~�e�B�u�̐�
#define WINDOW_MAX_TEXTURE			(3)
#define WINDOW_TextureName0		""		//�^�C�g�� �G���^�[�L�[
#define WINDOW_TextureName1		"data/TEXTURE/effect001.jpg"				//�v���C���[�̃Q�[�W
#define WINDOW_TextureName2		"data/TEXTURE/texture.png"				//�v���C���[�̃Q�[�W
#define	MAX_WINDOW			(48)		// window�̍ő吔
#define HALFEXPLOSION		(30)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 initpos;	//�����ʒu
	D3DXCOLOR col;
	float fLengthX;
	float fLengthY;
	int nPtnUV;			//�w�肳�ꂽ���W�ŕ\��
	int nPtnHeight;		//�摜�̏c�̕�����
	int nPtnWide;		//�摜�̉��̕�����
	int nType;
	float fSteep;			//�p�x
	WINDOWSTATE state;
	WINDOWUSE use;
	WINDOWTYPE PosType;	//�\������Ƃ��̎��̐ݒ�
	WINDOW_DRAW	draw;
	int nCounterState[2];	//�G�l�~�[�̏�ԊǗ��p
	WINDOW_UPDATE nUpdateType;		//�X�V�𕪂��邽��
	bool bUse;
}Window;

//*********************************************************************************************************//
// �O���[�o���ϐ�
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureWindow[WINDOW_MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWindow = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Window g_aWindow[MAX_WINDOW];

//=========================================================================================================//
// * �w�i�̕`�揈��1	����������
//=========================================================================================================//
void InitWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntWindow;

	// �e�̏��̏�����
	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		//g_aWindow[nCntWindow].pos = { 0.0f, 0.0f, 0.0f };
		//g_aWindow[nCntWindow].nLengthX = 0;
		//g_aWindow[nCntWindow].nLengthY = 0;
		//g_aWindow[nCntWindow].nType = 0;
		//g_aWindow[nCntWindow].col = { 1.0f, 1.0f, 1.0f, };
		g_aWindow[nCntWindow].bUse = false;
		g_aWindow[nCntWindow].nUpdateType = WINDOW_UPDATE_SELECT;
	}

	D3DXCreateTextureFromFile(pDevice, WINDOW_TextureName0, &g_pTextureWindow[0]);
	D3DXCreateTextureFromFile(pDevice, WINDOW_TextureName1, &g_pTextureWindow[1]);
	D3DXCreateTextureFromFile(pDevice, WINDOW_TextureName2, &g_pTextureWindow[2]);

	//���_BUFFER�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * WINDOW_VERTEX_NUM * MAX_WINDOW,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffWindow,
		NULL);

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWindow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		//���_���W�̐ݒ�
		pVtx[nCntWindow * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

		pVtx[nCntWindow * 4].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 1].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 2].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 3].rhw = 1.0f;

		//�J���[�ݒ�
		pVtx[nCntWindow * 4].col = D3DCOLOR_RGBA(0, 0, 0, 255);	// A = �����x
		pVtx[nCntWindow * 4 + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[nCntWindow * 4 + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[nCntWindow * 4 + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

		//�e�N�X�`�����W�ݒ�
		pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//���_BUFFER���A�����b�N����
	g_pVtxBuffWindow->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��2	�I������
//=========================================================================================================//
void UninitWindow(void)
{//�e�N�X�`���̔j��
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < WINDOW_MAX_TEXTURE; nCntTexture++)
	{
		if (g_pTextureWindow[nCntTexture] != NULL)
		{
			g_pTextureWindow[nCntTexture]->Release();
			g_pTextureWindow[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffWindow != NULL)
	{
		g_pVtxBuffWindow->Release();
		g_pVtxBuffWindow = NULL;
	}
}
//=========================================================================================================//
// * �w�i�̕`�揈��3	�X�V����
//=========================================================================================================//
void UpdateWindow(void)
{
	int nCntWindow;
	int nRand;
	float fRand;	//0.01����6.28�܂�
	static float fStealth = 0.02f;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//pPlayer = GetPlayer();

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWindow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		if (g_aWindow[nCntWindow].bUse == true)
		{
			switch (g_aWindow[nCntWindow].state)
			{
				break;
			case WINDOWSTATE_FADEIN:	//Stealth�̑�����Ȃ�
				g_aWindow[nCntWindow].col.a += 0.012f;
				if (g_aWindow[nCntWindow].col.a >= 1.0f)
				{
					g_aWindow[nCntWindow].col.a = 1.0f;
					g_aWindow[nCntWindow].state = WINDOWSTATE_NORMAL;
				}
				break;
			case WINDOWSTATE_FADEOUT://�ݒ肳�ꂽ�����x����Â��Ȃ�0�ŏ�����
				g_aWindow[nCntWindow].col.a -= 0.012f;
				if (g_aWindow[nCntWindow].col.a <= 0.0f)
				{
					g_aWindow[nCntWindow].col.a = 0.0f;
					g_aWindow[nCntWindow].bUse = false;
				}
				break;

			case WINDOWSTATE_FADEOUT_B://�ݒ肳�ꂽ�����x����Â��Ȃ�0�ŏ�����
				g_aWindow[nCntWindow].col.a -= 0.012f;
				g_aWindow[nCntWindow].fLengthX *= 1.01f;
				g_aWindow[nCntWindow].fLengthY *= 1.01f;
				if (g_aWindow[nCntWindow].col.a <= 0.0f)
				{
					g_aWindow[nCntWindow].col.a = 0.0f;
					g_aWindow[nCntWindow].bUse = false;
				}
				break;

			case WINDOWSTATE_FADE_ALL://�ݒ肳�ꂽ�����x����Â��Ȃ�0�ŏ�����
				if (g_aWindow[nCntWindow].nCounterState[0] == 0)
				{
					g_aWindow[nCntWindow].col.a += 0.05f;
					if (g_aWindow[nCntWindow].col.a >= 1.0f)
					{
						g_aWindow[nCntWindow].col.a = 1.0f;
						g_aWindow[nCntWindow].nCounterState[0] = 1;
					}
				}
				else { g_aWindow[nCntWindow].nCounterState[0]++; }

				if (g_aWindow[nCntWindow].nCounterState[0] > 0)
				{
					g_aWindow[nCntWindow].col.a -= 0.05f;
					if (g_aWindow[nCntWindow].col.a <= 0.0f)
					{
						g_aWindow[nCntWindow].col.a = 0.0f;
						g_aWindow[nCntWindow].bUse = false;
					}
				}
				break;

			case WINDOWSTATE_FLASH://�_�łŕ\��
				g_aWindow[nCntWindow].nCounterState[0]++;
				if (g_aWindow[nCntWindow].nCounterState[1] % 2 == 0 && g_aWindow[nCntWindow].nCounterState[0] % 45 == 0)
				{
					g_aWindow[nCntWindow].col.a = 1.0f;
					g_aWindow[nCntWindow].nCounterState[1]++;
				}
				else if (g_aWindow[nCntWindow].nCounterState[0] % 45 == 0)
				{
					g_aWindow[nCntWindow].col.a = 0.0f;
					g_aWindow[nCntWindow].nCounterState[1]++;
				}
				break;

			case WINDOWSTATE_SELECTON://SELECT�����Ŏg�p����A�I������Ă���Ƃ�
				g_aWindow[nCntWindow].col.r += fStealth;
				g_aWindow[nCntWindow].col.g += fStealth;
				g_aWindow[nCntWindow].col.b += fStealth;
				g_aWindow[nCntWindow].col.a = 1.0f;
				if (g_aWindow[nCntWindow].col.r >= 1.0f || g_aWindow[nCntWindow].col.r <= 0.22f)
				{//���邳���ő�, �ŏ��ɂȂ����甽�]
					fStealth *= -1.0f;
				}
				break;

			case WINDOWSTATE_SELECTOFF://SELECT�����Ŏg�p����A�I������Ă��Ȃ��Ƃ�
				g_aWindow[nCntWindow].col.r = 0.23f;
				g_aWindow[nCntWindow].col.g = 0.23f;
				g_aWindow[nCntWindow].col.b = 0.23f;
				g_aWindow[nCntWindow].col.a = 1.0f;
				break;

			case WINDOWSTATE_LEVELUP:
				g_aWindow[nCntWindow].col.a -= 0.01f;
				g_aWindow[nCntWindow].pos.y -= 3;
				g_aWindow[nCntWindow].initpos.y -= 3;
				if (g_aWindow[nCntWindow].col.a <= 0.0f)
				{
					g_aWindow[nCntWindow].col.a = 0.0f;
					g_aWindow[nCntWindow].bUse = false;
				}
			case WINDOWSTATE_VIBRATION:	//�U��
				fRand = (rand() % 628) * 0.01f;
				nRand = rand() % 30 + 5;
				g_aWindow[nCntWindow].nCounterState[0] = (g_aWindow[nCntWindow].nCounterState[0] + 1) % 2;
				if (g_aWindow[nCntWindow].nCounterState[0] == 0) { g_aWindow[nCntWindow].pos += D3DXVECTOR3(sinf(fRand) * nRand, cosf(fRand) * nRand, 0.0f); }
				if (g_aWindow[nCntWindow].nCounterState[0] == 1) { g_aWindow[nCntWindow].pos = g_aWindow[nCntWindow].initpos; }
				break;

			case WINDOWSTATE_FLOW:
				if (g_aWindow[nCntWindow].nCounterState[0] == 0)
				{//������E�ɗ���Ȃ���\��
					g_aWindow[nCntWindow].col.a += 0.05f;
					g_aWindow[nCntWindow].pos.x += 20.0f;
					if (g_aWindow[nCntWindow].col.a >= 1.0f)
					{
						g_aWindow[nCntWindow].col.a = 1.0f;
						g_aWindow[nCntWindow].nCounterState[0] = 1;
					}
				}
				else
				{//���Ԍo�߂�
					g_aWindow[nCntWindow].nCounterState[0]++;
					if (g_aWindow[nCntWindow].nCounterState[0] > 60)
					{//����Ɏ��Ԍo�߂�
						g_aWindow[nCntWindow].col.a -= 0.029f;
						g_aWindow[nCntWindow].pos.x += 8.0f;
						if (g_aWindow[nCntWindow].col.a <= 0.0f)
						{//�E�ɗ���Ȃ��������
							g_aWindow[nCntWindow].col.a = 0.0f;
							g_aWindow[nCntWindow].bUse = false;
						}
					}
				}
				break;

			}

			switch (g_aWindow[nCntWindow].PosType)
			{

			case WINDOWTYPE_CENTER:
				pVtx[nCntWindow * 4].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
				pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
				pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
				pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
				break;
			case WINDOWTYPE_LEFT_DOWN:
				pVtx[nCntWindow * 4].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), g_aWindow[nCntWindow].pos.y + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
				pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
				pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x, g_aWindow[nCntWindow].pos.y, 0.0f);
				pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), 0.0f);
				break;

			}
			pVtx[nCntWindow * 4].col = g_aWindow[nCntWindow].col;	// A = �����x
			pVtx[nCntWindow * 4 + 1].col = g_aWindow[nCntWindow].col;
			pVtx[nCntWindow * 4 + 2].col = g_aWindow[nCntWindow].col;
			pVtx[nCntWindow * 4 + 3].col = g_aWindow[nCntWindow].col;
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffWindow->Unlock();
}
//=========================================================================================================//
// * �w�i�̕`�揈��4	�`�揈��
//=========================================================================================================//
void DrawWindow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntWindow;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffWindow, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	// �|���S���̕`��
	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		if (g_aWindow[nCntWindow].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWindow[g_aWindow[nCntWindow].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWindow * 4, WINDOW_PRIMITIVE_NUM);
		}
	}

}
//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
int SetWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nPtnUV, int nPtnWide, int nPtnHeight
	, int nCntUse, WINDOW_UPDATE nUpdateType, WINDOWSTATE state, WINDOWUSE use, WINDOWTYPE type, WINDOW_DRAW draw)
{
	int nCntWindow;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWindow->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWindow = 1; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		if (g_aWindow[nCntWindow].bUse == false)
		{
			g_aWindow[nCntWindow].pos = pos;
			g_aWindow[nCntWindow].initpos = pos;
			g_aWindow[nCntWindow].fLengthX = nLengthX * 1.0f;
			g_aWindow[nCntWindow].fLengthY = nLengthY * 1.0f;
			g_aWindow[nCntWindow].nType = nType;
			g_aWindow[nCntWindow].nUpdateType = nUpdateType;
			g_aWindow[nCntWindow].nPtnUV = nPtnUV;
			g_aWindow[nCntWindow].nPtnWide = nPtnWide;
			g_aWindow[nCntWindow].nPtnHeight = nPtnHeight;
			g_aWindow[nCntWindow].state = state;
			g_aWindow[nCntWindow].use = use;
			g_aWindow[nCntWindow].nCounterState[0] = nCntUse;
			g_aWindow[nCntWindow].nCounterState[1] = 1;
			g_aWindow[nCntWindow].PosType = type;
			g_aWindow[nCntWindow].draw = draw;
			g_aWindow[nCntWindow].bUse = true;

			g_aWindow[nCntWindow].fSteep = D3DX_PI;
			/*pVtx[nCntWindow * 4].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - g_aWindow[nCntWindow].nLengthX, g_aWindow[nCntWindow].pos.y - g_aWindow[nCntWindow].nLengthY, 0.0f);
			pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + g_aWindow[nCntWindow].nLengthX, g_aWindow[nCntWindow].pos.y - g_aWindow[nCntWindow].nLengthY, 0.0f);
			pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - g_aWindow[nCntWindow].nLengthX, g_aWindow[nCntWindow].pos.y + g_aWindow[nCntWindow].nLengthY, 0.0f);
			pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + g_aWindow[nCntWindow].nLengthX, g_aWindow[nCntWindow].pos.y + g_aWindow[nCntWindow].nLengthY, 0.0f);*/

			pVtx[nCntWindow * 4].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
			pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
			pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) + (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);
			pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(g_aWindow[nCntWindow].pos.x - (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX), g_aWindow[nCntWindow].pos.y + (sinf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthX) - (cosf(g_aWindow[nCntWindow].fSteep) * g_aWindow[nCntWindow].fLengthY), 0.0f);

			g_aWindow[nCntWindow].col = col;
			pVtx[nCntWindow * 4].col = col;	// A = �����x
			pVtx[nCntWindow * 4 + 1].col = col;
			pVtx[nCntWindow * 4 + 2].col = col;
			pVtx[nCntWindow * 4 + 3].col = col;

			pVtx[nCntWindow * 4].tex = D3DXVECTOR2((g_aWindow[nCntWindow].nPtnUV % g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnWide), (g_aWindow[nCntWindow].nPtnUV / g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnHeight));
			pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2((g_aWindow[nCntWindow].nPtnUV % g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnWide) + (1.0f / g_aWindow[nCntWindow].nPtnWide), (g_aWindow[nCntWindow].nPtnUV / g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnHeight));
			pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2((g_aWindow[nCntWindow].nPtnUV % g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnWide), (g_aWindow[nCntWindow].nPtnUV / g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnHeight) + (1.0f / g_aWindow[nCntWindow].nPtnHeight));
			pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2((g_aWindow[nCntWindow].nPtnUV % g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnWide) + (1.0f / g_aWindow[nCntWindow].nPtnWide), (g_aWindow[nCntWindow].nPtnUV / g_aWindow[nCntWindow].nPtnWide) * (1.0f / g_aWindow[nCntWindow].nPtnHeight) + (1.0f / g_aWindow[nCntWindow].nPtnHeight));

			break;
		}
	}
	//���_BUFFER���A�����b�N����
	g_pVtxBuffWindow->Unlock();

	return nCntWindow;
}
//=============================================================================
// window�̔j��
//=============================================================================
void BreakWindow(void)
{//�S�E�B���h�E�j��
	int nCntWindow;

	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		g_aWindow[nCntWindow].bUse = false;
	}
}
//=============================================================================
// window�̎w��ύX
//=============================================================================
void ChangeWindow(int nCntWindow, D3DXCOLOR col, WINDOWSTATE state)
{
	if (g_aWindow[nCntWindow].bUse == true)
	{
		g_aWindow[nCntWindow].col = col;
		if (state != WINDOWSTATE_MAX) { g_aWindow[nCntWindow].state = state; }
	}
}
//=============================================================================
// window�̔j��
//=============================================================================
void CheckGage(float fGage, float fMaxGage, int nCntWindow)
{
	float fPercent;
	float fPlus;
	float fLength = 0.0f;
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWindow->Lock(0, 0, (void**)&pVtx, 0);

	//�ő�l����%�����߂�
	fPercent = fGage / fMaxGage;
	if (fPercent > 1.0f) { fPercent = 1.0f; }

	//Window�̃^�C�v�ɂ���Ē�����ύX
	switch (g_aWindow[nCntWindow].state)
	{//�����̔{���ɂ�����
	case WINDOWSTATE_LIFEGAGE:
		fLength = 430.0f;
		if (g_aWindow[nCntWindow].fLengthX > fLength * fPercent) { g_aWindow[nCntWindow].fLengthX = fLength * fPercent; }
		else
		{//���񂾂񑝂���
			fPlus = (fLength * fPercent - g_aWindow[nCntWindow].fLengthX) * 0.03f;
			if (fPlus < fLength * 0.001f) { fPlus = fLength * 0.001f; }
			g_aWindow[nCntWindow].fLengthX += fPlus;
			if (g_aWindow[nCntWindow].fLengthX > fLength * fPercent) { g_aWindow[nCntWindow].fLengthX = fLength * fPercent; }
		}
		break;

	case WINDOWSTATE_MPGAGE:
		fLength = 400.0f;
		if (g_aWindow[nCntWindow].fLengthX > fLength * fPercent) { g_aWindow[nCntWindow].fLengthX = fLength * fPercent; }
		else
		{//���񂾂񑝂���
			fPlus = (fLength * fPercent - g_aWindow[nCntWindow].fLengthX) * 0.03f;
			if (fPlus < fLength * 0.001f) { fPlus = fLength * 0.001f; }
			g_aWindow[nCntWindow].fLengthX += fPlus;
			if (g_aWindow[nCntWindow].fLengthX > fLength * fPercent) { g_aWindow[nCntWindow].fLengthX = fLength * fPercent; }
		}
		break;

	case WINDOWSTATE_AUTOLIFEGAGE:
		fLength = 430.0f;

		if (g_aWindow[nCntWindow].fLengthX > fLength * fPercent)
		{//���񂾂񌸂�
			fPlus = (fLength * fPercent - g_aWindow[nCntWindow].fLengthX) * 0.03f;
			if (fPlus < fLength * 0.0015f) { fPlus = fLength * 0.0015f; }
			g_aWindow[nCntWindow].fLengthX -= fPlus;
			g_aWindow[nCntWindow].col = D3DXCOLOR(0.76f, 0.1f, 0.0f, 1.0f);
			if (g_aWindow[nCntWindow].fLengthX < fLength * fPercent) { g_aWindow[nCntWindow].fLengthX = fLength * fPercent; }
		}
		else if (g_aWindow[nCntWindow].fLengthX < fLength * fPercent)
		{//���̂܂ܑ��
			g_aWindow[nCntWindow].fLengthX = fLength * fPercent;
			g_aWindow[nCntWindow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else { g_aWindow[nCntWindow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		break;

	case WINDOWSTATE_AUTOMPGAGE:
		fLength = 400.0f;

		if (g_aWindow[nCntWindow].fLengthX > fLength * fPercent)
		{//���񂾂񌸂�
			fPlus = (fLength * fPercent - g_aWindow[nCntWindow].fLengthX) * 0.03f;
			if (fPlus < fLength * 0.0015f) { fPlus = fLength * 0.0015f; }
			g_aWindow[nCntWindow].fLengthX -= fPlus;
			g_aWindow[nCntWindow].col = D3DXCOLOR(0.45f, 0.0f, 3.0f, 1.0f);
			if (g_aWindow[nCntWindow].fLengthX < fLength * fPercent) { g_aWindow[nCntWindow].fLengthX = fLength * fPercent; }
		}
		else if (g_aWindow[nCntWindow].fLengthX < fLength * fPercent)
		{//���̂܂ܑ��
			g_aWindow[nCntWindow].fLengthX = fLength * fPercent;
			g_aWindow[nCntWindow].col = D3DXCOLOR(0.99f, 1.0f, 0.18f, 1.0f);
		}
		else { g_aWindow[nCntWindow].col = D3DXCOLOR(0.99f, 1.0f, 0.18f, 1.0f); }
		break;
	}

	pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2((g_aWindow[nCntWindow].fLengthX / fLength) * 1.0f, 0.0f);
	pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2((g_aWindow[nCntWindow].fLengthX / fLength) * 1.0f, 1.0f);


	//���_BUFFER���A�����b�N����
	g_pVtxBuffWindow->Unlock();
}
//=============================================================================
// �I������
//=============================================================================
void SelectWindow(int nNumber)
{
	int nCntWindow;

	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		if (g_aWindow[nCntWindow].use == WINDOWUSE_SELECT && g_aWindow[nCntWindow].bUse == true)
		{
			if (g_aWindow[nCntWindow].nCounterState[0] == nNumber)
			{
				g_aWindow[nCntWindow].state = WINDOWSTATE_SELECTON;
			}
			else
			{
				g_aWindow[nCntWindow].state = WINDOWSTATE_SELECTOFF;
			}
		}
	}
}
//=============================================================================
// �w�肵��window���j��
//=============================================================================
void BackWindow(int nNumber)
{
	int nCntWindow;			//window�𐔂���
	int nBreak = nNumber;	//nNumber����������ǂ��Ȃ邩�킩���...

	for (nCntWindow = MAX_WINDOW; nCntWindow > 0; nCntWindow--)
	{//�ő�ł��S���I�������I��
		if (g_aWindow[nCntWindow - 1].bUse == true)
		{//��납�猩��true�ɂȂ��Ƃ����E��
			g_aWindow[nCntWindow - 1].bUse = false;
			nBreak--;
			if (nBreak < 1)
			{//0�ȉ��ɂȂ�����I���
				break;
			}
		}
	}
}
//=============================================================================
// 50���\���̘g�ړ�����
//=============================================================================
void FontWindowMove(int nWide, int nHeight)
{
	int nCntWindow;

	for (nCntWindow = 0; nCntWindow < MAX_WINDOW; nCntWindow++)
	{
		if (g_aWindow[nCntWindow].use == WINDOWUSE_FONT)
		{
			if (nHeight == 5)
			{//�Ђ� �J�i �I���̏ꍇ
				g_aWindow[nCntWindow].fLengthY = SCREEN_HEIGHT / 30;
				g_aWindow[nCntWindow].pos.y = SCREEN_HEIGHT * 0.805f;
				if (nWide == 0)
				{
					g_aWindow[nCntWindow].fLengthX = SCREEN_WIDTH / 20;
					g_aWindow[nCntWindow].pos.x = SCREEN_WIDTH * 0.405f;
				}
				else if (nWide == 1)
				{
					g_aWindow[nCntWindow].fLengthX = SCREEN_WIDTH / 20;
					g_aWindow[nCntWindow].pos.x = SCREEN_WIDTH * 0.505f;
				}
				else if (nWide == 2)
				{
					g_aWindow[nCntWindow].fLengthX = SCREEN_WIDTH / 17;
					g_aWindow[nCntWindow].pos.x = SCREEN_WIDTH * 0.608f;
				}
				else if (nWide == 3)
				{
					g_aWindow[nCntWindow].fLengthX = SCREEN_WIDTH / 17;
					g_aWindow[nCntWindow].pos.x = SCREEN_WIDTH * 0.7305f;
				}
			}
			else
			{//�Ђ� �J�i �I��� �ȊO
				g_aWindow[nCntWindow].fLengthX = SCREEN_WIDTH / 38;
				g_aWindow[nCntWindow].fLengthY = SCREEN_HEIGHT / 19;
				g_aWindow[nCntWindow].pos.x = nWide * SCREEN_WIDTH * 0.0525f + SCREEN_WIDTH * 0.2365f;
				g_aWindow[nCntWindow].pos.y = nHeight * SCREEN_HEIGHT * 0.101f + SCREEN_HEIGHT * 0.31f;
			}
		}
	}
}
