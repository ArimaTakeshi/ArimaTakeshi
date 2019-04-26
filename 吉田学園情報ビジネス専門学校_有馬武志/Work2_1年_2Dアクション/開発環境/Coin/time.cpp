//=============================================================================
//
// �^�C������ [time.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "time.h"		//�^�C��
#include "game.h"		//�Q�[��
#include "fade.h"		//�t�F�[�h
#include "score.h"		//�X�R�A
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_TIME			(3)								//�^�C���̍ő包��
#define TIME_SIZE			(25)							//���Ԃ̕�
#define TIME				(6000)							//�ŏ��̎��� //�P�b�P�O�O

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_posTime;					//�^�C���̈ʒu
Time					g_nTime;					//�^�C���̏��

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�^�C���̏������W
	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, 40, 0.0f);

	//�^�C���̏�����
	g_nTime.nTime = TIME;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				//�f�o�C�X�ւ̃|�C���^
							TEXTURE_TIME,			//�t�@�C���̖��O
							&g_pTextureTime);		//�e�N�X�`���ւ̃|�C���^

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);
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
		//���̕�
		g_posTime.x += 50;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

	//AddTime(180);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	//�����ڂ̏��
	int aNumber[MAX_TIME];
	//�b���J�E���g
	int nCount = 0;

	//���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//�R���ڂ܂ł̌v�Z
	aNumber[0] = g_nTime.nTime % 100000 / 10000;
	aNumber[1] = g_nTime.nTime % 10000 / 1000;
	aNumber[2] = g_nTime.nTime % 1000 / 100;

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{//�S�^�C���̌������J�E���g
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntTime] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntTime] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntTime] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntTime] * 0.1f, 1.0f);

		if (g_nTime.nTime <= 600)
		{//����̕b����؂����ꍇ�A�Ԃ�����
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		}
		//���_�f�[�^�̃|�C���^��4�i�߂�
		pVtx += 4;	
	} 
	//���Ԃ��O�ɂȂ�����I���I
	if (g_nTime.nTime <= 0)
	{
		//���[�h�̃|�C���^
		MODE pMode;
		pMode = *GetMode();

		//�^�C�����O�ɂȂ����烊�U���g�ɍs��
		if ((nCount % 250) == 0)
		{
			SetGameState(GAMESTATE_OVER);
		}
	}
	//�^�C���������Ă����A++�ɂ���Əオ���Ă���
	if (g_nTime.nTime >= 0)
	{
		g_nTime.nTime--;
		g_nTime.nTime--;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{//�S�^�C���̌������J�E���g
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}
//=========================================================================================================================
// �^�C���̎擾����
//=========================================================================================================================
Time *GetTime(void)
{
	return &g_nTime;
}
//=========================================================================================================================
// �u���b�N�̎擾����
//=========================================================================================================================
void DeleteTime(void)
{
	//�^�C���̏������W
	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, 40, 0.0f);

	//���_����ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();

	//�^�C���̏�����
	g_nTime.nTime = TIME;
}
