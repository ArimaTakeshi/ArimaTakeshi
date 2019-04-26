//=============================================================================
//
// �A�C�e���̃J�E���g�̕\������ [ItemCount.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "itemcount.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_ITEMCOUNT	"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_ITEMCOUNT		(3)								//�X�R�A�̍ő包��
#define ITEMCOUNT_SIZE		(25)							//���̕�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexItemCount(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItemCount = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemCount = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nItemCount;					// �X�R�A
D3DXVECTOR3				g_posItemCount;

//=============================================================================
// ����������
//=============================================================================
void InitItemCount(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�����l
	g_posItemCount = D3DXVECTOR3(80, 32, 0.0f);

	// �X�R�A�̏�����
	g_nItemCount = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�摜�P����
		pDevice,
		TEXTURE_ITEMCOUNT,
		&g_pTextureItemCount
	);

	// ���_���̍쐬
	MakeVertexItemCount(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitItemCount(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureItemCount != NULL)
	{
		g_pTextureItemCount->Release();
		g_pTextureItemCount = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffItemCount != NULL)
	{
		g_pVtxBuffItemCount->Release();
		g_pVtxBuffItemCount = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItemCount(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItemCount(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItemCount, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItemCount);

	for (int nCntItemCount = 0; nCntItemCount < MAX_ITEMCOUNT; nCntItemCount++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemCount, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexItemCount(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntItemCount;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemCount,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemCount->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItemCount = 0; nCntItemCount < MAX_ITEMCOUNT; nCntItemCount++)
	{//�S�e�N�X�`���̃J�E���g
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posItemCount.x - ITEMCOUNT_SIZE, g_posItemCount.y - ITEMCOUNT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posItemCount.x + ITEMCOUNT_SIZE, g_posItemCount.y - ITEMCOUNT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posItemCount.x - ITEMCOUNT_SIZE, g_posItemCount.y + ITEMCOUNT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posItemCount.x + ITEMCOUNT_SIZE, g_posItemCount.y + ITEMCOUNT_SIZE, 0.0f);

		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
		g_posItemCount.x += 43;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemCount->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddItemCount(int nValue)
{
	int nCntItemCount;
	int aNumber[MAX_ITEMCOUNT];

	g_nItemCount += nValue;

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItemCount->Lock(0, 0, (void**)&pVtx, 0);

	//�������i�R���j
	aNumber[0] = g_nItemCount % 1000 / 100;
	aNumber[1] = g_nItemCount % 100 / 10;
	aNumber[2] = g_nItemCount % 10;

	for (nCntItemCount = 0; nCntItemCount < MAX_ITEMCOUNT; nCntItemCount++)
	{//�S�e�N�X�`���̃J�E���g
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntItemCount] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntItemCount] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntItemCount] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntItemCount] * 0.1f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4�i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemCount->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
int GetItemCount(void)
{
	return g_nItemCount;
}