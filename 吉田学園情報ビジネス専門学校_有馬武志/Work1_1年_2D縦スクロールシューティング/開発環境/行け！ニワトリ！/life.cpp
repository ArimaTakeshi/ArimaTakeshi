//=============================================================================
//
// ���C�t���� [life.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "life.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_LIFE1		"data/TEXTURE/Life.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_POLYGON			(22)							//�X�R�A�̍ő包��
#define MAX_TEXTURE			(2)								//�X�R�A�̍ő包��
#define MAX_LIFE_TEX		(20)							//�X�R�A�̍ő包��
#define MAX_LIFE_NUM		(2)								//�X�R�A�̍ő包��

#define LIFE_SIZE			(25)
#define TEXLIFE_SIZE_X		(12)
#define TEXLIFE_SIZE_Y		(24)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife[MAX_TEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
int						g_nLife;								// �X�R�A
D3DXVECTOR3				g_posLife;
D3DXVECTOR3				g_posTexLife;
bool					g_bLifeTex[MAX_LIFE_TEX];

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posLife = D3DXVECTOR3(50, 630, 0.0f);

	g_posTexLife = D3DXVECTOR3(30, 680, 0.0f);

	for (int nCount = 0; nCount < MAX_LIFE_TEX; nCount++)
	{
		g_bLifeTex[nCount] = true;
	}

	// �X�R�A�̏�����
	g_nLife = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							TEXTURE_LIFE,			// �t�@�C���̖��O
							&g_pTextureLife[0]);		// �e�N�X�`���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							TEXTURE_LIFE1,			// �t�@�C���̖��O
							&g_pTextureLife[1]);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexLife(pDevice);

	AddLife(20, LifeTex_Init);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	int nCountTex;
	// �e�N�X�`���̊J��
	for (nCountTex = 0; nCountTex < MAX_TEXTURE; nCountTex++)
	{
		if (g_pTextureLife[nCountTex] != NULL)
		{
			g_pTextureLife[nCountTex] -> Release();
			g_pTextureLife[nCountTex] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCountTex;
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	for (nCountTex = 0; nCountTex < MAX_POLYGON; nCountTex++)
	{
		if (nCountTex < MAX_LIFE_NUM)
		{
			pDevice->SetTexture(0, g_pTextureLife[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex, 2);
		}
		else if (g_bLifeTex[nCountTex - MAX_LIFE_NUM] == true)
		{
			pDevice->SetTexture(0, g_pTextureLife[1]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex , 2);
		}
	}
		// �|���S���̕`��
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLife;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_POLYGON; nCntLife++)
	{
		if (nCntLife < MAX_LIFE_NUM)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posLife.x - LIFE_SIZE, g_posLife.y - LIFE_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posLife.x + LIFE_SIZE, g_posLife.y - LIFE_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posLife.x - LIFE_SIZE, g_posLife.y + LIFE_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posLife.x + LIFE_SIZE, g_posLife.y + LIFE_SIZE, 0.0f);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			g_posLife.x += 50;
		}
		else
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posTexLife.x - TEXLIFE_SIZE_X, g_posTexLife.y - TEXLIFE_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTexLife.x + TEXLIFE_SIZE_X, g_posTexLife.y - TEXLIFE_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTexLife.x - TEXLIFE_SIZE_X, g_posTexLife.y + TEXLIFE_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTexLife.x + TEXLIFE_SIZE_X, g_posTexLife.y + TEXLIFE_SIZE_Y, 0.0f);
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_posTexLife.x += 18;
		}
		
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nCntLife < MAX_POLYGON - 5)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddLife(int nLife, LIFETEX Life)
{
	int nCntLife;
	int aNumber[MAX_LIFE_NUM];

	g_nLife += nLife;

	if (Life == LifeTex_DAMAGE)
	{
		Player *pPlayer = GetPlayer();
		g_bLifeTex[pPlayer->nLife] = false;
	}

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	aNumber[0] = g_nLife % 100 / 10;
	aNumber[1] = g_nLife % 10;

	for (nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntLife] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntLife] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntLife] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntLife] * 0.1f, 1.0f);

		if (g_nLife <= 5)
		{
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		}

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}