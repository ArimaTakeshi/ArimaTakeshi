//=========================================================================================================================
//
// �������� [explosion.cpp]
// Author :  �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "explosion.h"	//����

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_EXPLOSION					(256)								//�����̍ő吔
#define EXPLOSION_TEXTURE_NAME			"data\\TEXTURE\\explosion000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define EXPLOSION_G_POS_X				(30)								//g_pos�����X����
#define EXPLOSION_G_POS_Y				(30)								//g_pos�����Y����
#define EXPLOSION_TEXTURE_SPEED			(5)									//�e�N�X�`���A�j���[�V�����X�s�[�h
#define EXPLOSION_TEXTURE_PATTERN		(8)									//�e�N�X�`���A�j���[�V�����p�^�[����
#define EXPLOSION_TEXTURE_UV_U			(0.125f)							//�e�N�X�`���A�j���[�V����U�͈�
#define EXPLOSION_TEXTURE_UV_V			(1.0f)								//�e�N�X�`���A�j���[�V����V�͈�

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef struct
{//����
	D3DXVECTOR3 pos;		//�ʒu
	D3DXCOLOR col;			//�F
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatteunAnim;		//�A�j���[�V�����p�^�[��No.
	bool bUse;				//�g�p���Ă��邩�ǂ���
}Explosion;

//*************************************************************************************************************************
// �O���[�o���ϐ��錾
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//���_�o�b�t�@�ւ̃|�C���^
Explosion  g_aExplosion[MAX_EXPLOSION];					//�����̏��

//=========================================================================================================================
// ��������������
//=========================================================================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
	int nCntExplosion;				//�����J�E���g
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�����̏��̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{//�������J�E���g
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatteunAnim = 0;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(
		pDevice,
		EXPLOSION_TEXTURE_NAME,
		&g_pTextureExplosion
	);

	//���_�o�b�t�@����
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL
	);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//�����̏��̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{//�������J�E���g
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
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//�e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, EXPLOSION_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

		pVtx += 4;	//���_�f�[�^�̃|�C���^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=========================================================================================================================
// �����I������
//=========================================================================================================================
void UninitExplosion(void)
{
	//�e�N�X�`���[�̔j��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=========================================================================================================================
// �����X�V����
//=========================================================================================================================
void UpdateExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
	int nCntExplosion;				//�����J�E���g

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{//�������J�E���g
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�e���g�p����Ă���
			g_aExplosion[nCntExplosion].nCounterAnim++;		//�J�E���^�[���Z

			if ((g_aExplosion[nCntExplosion].nCounterAnim % EXPLOSION_TEXTURE_SPEED) == 0)
			{//�A�j���[�V�������x
				g_aExplosion[nCntExplosion].nPatteunAnim = (g_aExplosion[nCntExplosion].nPatteunAnim + 1) % EXPLOSION_TEXTURE_PATTERN;		//�p�^�[��No.�X�V

				//���_�ݒ�
				pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_G_POS_Y, 0.0f);
				pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_G_POS_Y, 0.0f);
				pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_G_POS_Y, 0.0f);
				pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_G_POS_Y, 0.0f);
				//���_�J���[�ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
				//�e�N�X�`���ݒ�
				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_aExplosion[nCntExplosion].nPatteunAnim, 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_aExplosion[nCntExplosion].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_aExplosion[nCntExplosion].nPatteunAnim, EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_aExplosion[nCntExplosion].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

				if (g_aExplosion[nCntExplosion].nPatteunAnim == EXPLOSION_TEXTURE_PATTERN - 1)
				{//�A�j���[�V�������Ō�܂ł������ꍇ
					g_aExplosion[nCntExplosion].bUse = false;		//�g�p���Ă��Ȃ����
				}
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=========================================================================================================================
// �����`�揈��
//=========================================================================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�|�C���^
	int nCntExplosion;				//�e�J�E���g

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffExplosion,
		0, 
		sizeof(VERTEX_2D)
	);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	// �|���S���̕`��
	for(nCntExplosion = 0; nCntExplosion< MAX_EXPLOSION; nCntExplosion++)
	{//�������J�E���g
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//����������ꍇ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//=========================================================================================================================
// �����̐ݒ菈��
//=========================================================================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;			//�����J�E���g

	VERTEX_2D *pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntExplosion = 0; nCntExplosion< MAX_EXPLOSION; nCntExplosion++)
	{//�������J�E���g
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�������g�p����Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;			//pos�l���
			g_aExplosion[nCntExplosion].col = col;			//move�l���
			g_aExplosion[nCntExplosion].nCounterAnim = 0;	//�J�E���^�[�����l�ݒ�
			g_aExplosion[nCntExplosion].nPatteunAnim = 0;	//�p�^�[��No.�����l�ݒ�
			g_aExplosion[nCntExplosion].bUse = true;		//�g�p���Ă����Ԃɂ���

			//���_�ݒ�
			pVtx[nCntExplosion * 4].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_G_POS_Y, 0.0f);
			pVtx[nCntExplosion * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_G_POS_Y, 0.0f);
			pVtx[nCntExplosion * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_G_POS_Y, 0.0f);
			pVtx[nCntExplosion * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_G_POS_X, g_aExplosion[nCntExplosion].pos.y + EXPLOSION_G_POS_Y, 0.0f);
			//���_�J���[�ݒ�
			pVtx[nCntExplosion * 4].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
			pVtx[nCntExplosion * 4 + 1].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
			pVtx[nCntExplosion * 4 + 2].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);
			pVtx[nCntExplosion * 4 + 3].col = D3DXCOLOR(g_aExplosion[nCntExplosion].col.r, g_aExplosion[nCntExplosion].col.g, g_aExplosion[nCntExplosion].col.b, g_aExplosion[nCntExplosion].col.a);

			break;
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}