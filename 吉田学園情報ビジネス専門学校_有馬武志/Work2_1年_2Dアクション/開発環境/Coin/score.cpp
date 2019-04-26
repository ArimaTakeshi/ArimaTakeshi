//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "score.h"		//�X�R�A
#include "Game.h"		//�Q�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE	"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_SCORE	(8)									//�X�R�A�̍ő包��
#define SCORE_SIZE	(25)								//�X�R�A�̏c�̕��A���̕�
#define MAX_SET		(6)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
Score g_nScore[MAX_SET];
SCORESTATE g_ScoreState;
GETCOINSTATE g_GetCoinState;
//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	for (int nCntScore = 0; nCntScore < MAX_SET; nCntScore++)
	{//�X�R�A�̌������J�E���g
		g_nScore[nCntScore].pos = D3DXVECTOR3(0, 0, 0);
		g_nScore[nCntScore].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_nScore[nCntScore].ScoreHeight = 0;
		g_nScore[nCntScore].ScoreWidth = 0;
		g_nScore[nCntScore].bUse = false;
	//	g_nScore[nCntScore].nNumScore = 0;
	}
	g_GetCoinState = GETCOIN_NORMAL;
	g_ScoreState = SCORE_NONE;
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^
	// ���_���̍쐬
	MakeVertexScore(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (int nCntScore = 0; nCntScore < MAX_SET; nCntScore++)
	{//�X�R�A�\����
		if (g_nScore[nCntScore].bUse == true)
		{//�X�R�A��true�Ȃ�
			for (int nCntScore2 = 0; nCntScore2 < MAX_SCORE; nCntScore2++)
			{//�X�R�A�̌������J�E���g
			 // �|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntScore2 + MAX_SCORE * 4 * nCntScore, 2);
			}
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	//�J�E���g�X�R�A
	int nCntScore;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (MAX_SCORE * MAX_SET),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < (MAX_SCORE * MAX_SET); nCntScore++)
	{//�X�R�A�\�������X�R�A������
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//1.0f�ŌŒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//���_�f�[�^�̃|�C���^��4�i�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue ,SCORESTATE state)
{
	//�J�E���g�X�R�A
	int nCntScore;

	//�����̓��ꕨ
	int aNumber[MAX_SCORE];

	int nScoreDate;

	g_ScoreState = state;

	MODE pMode = *GetMode();
	GAMESTATE pGame = GetGameState();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	if (pGame == GAMESTATE_CLEAR || pGame == GAMESTATE_OVER)
	{//�N���A���I�[�o�[��������
		for (int nCount = 0; nCount < MAX_SET - 1; nCount++)
		{//�\������
			for (int nCount2 = nCount + 1; nCount2 < MAX_SET; nCount2++)
			{//�X�R�A�̌�����
				if (g_nScore[nCount].nNumScore < g_nScore[nCount2].nNumScore)
				{//�~���ɓ���ւ�
					nScoreDate = g_nScore[nCount2].nNumScore;
					g_nScore[nCount2].nNumScore = g_nScore[nCount].nNumScore;
					g_nScore[nCount].nNumScore = nScoreDate;
				}
			}
		}
	}
	//for (nCntData = 0; nCntData < MAX_DATA - 1; nCntData++)
	//{	//��r�̌J��Ԃ�
	//	for (nCntData2 = nCntData + 1; nCntData2 < MAX_DATA; nCntData2++)
	//	{	//��r�Ώۂ̌J��Ԃ�
	//		if (pData[nCntData] < pData[nCntData2])
	//		{	//�l�̔�r	�i�~�����ёւ� < �j(�������ёւ� > )
	//			//�l�̊i�[
	//			nData = pData[nCntData2];

	//			//�l�̓���ւ�
	//			pData[nCntData2] = pData[nCntData];
	//			pData[nCntData] = nData;
	//		}
	//	}
	//}

	for (int nCount = 0; nCount < MAX_SET; nCount++)
	{
		if (g_nScore[nCount].bUse == true)
		{
			if (pGame == GAMESTATE_NORMAL)
			{
				//�X�R�A�ɉ��Z
				if (g_ScoreState == SCORE_COIN && g_GetCoinState == GETCOIN_X2)
				{
					nValue *= 2;
				}
				g_nScore[nCount].nNumScore += nValue;
			}

			if (pGame == GAMESTATE_NORMAL ||
				((pGame == GAMESTATE_CLEAR || pGame == GAMESTATE_OVER) && pMode == MODE_RANKING))
			{
				//�v�Z��
				aNumber[7] = g_nScore[nCount].nNumScore / 10000000;
				aNumber[6] = g_nScore[nCount].nNumScore % 10000000 / 1000000;
				aNumber[5] = g_nScore[nCount].nNumScore % 1000000 / 100000;
				aNumber[4] = g_nScore[nCount].nNumScore % 100000 / 10000;
				aNumber[3] = g_nScore[nCount].nNumScore % 10000 / 1000;
				aNumber[2] = g_nScore[nCount].nNumScore % 1000 / 100;
				aNumber[1] = g_nScore[nCount].nNumScore % 100 / 10;
				aNumber[0] = g_nScore[nCount].nNumScore % 10;

				for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
				{//�X�R�A�̌������J�E���g
				 //�e�N�X�`�����W
					pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntScore] * 0.1f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntScore] * 0.1f, 1.0f);

					//���_�f�[�^�̃|�C���^��4�i�߂�
					pVtx += 4;
				}
			}
		}
		else
		{
			//���_�f�[�^�̃|�C���^��4�i�߂�
			pVtx += (4 * MAX_SCORE);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// �Z�b�g�X�R�A
//=============================================================================
void SetScore(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	//�X�R�A�̃J�E���g
	int nCntScore;

	GAMESTATE pGame = GetGameState();

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffScore->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntScore = 0; nCntScore < MAX_SET; nCntScore++)
	{//�X�R�A�̕\����
		if (g_nScore[nCntScore].bUse == false)
		{//�u���b�N���g�p����Ă��Ȃ��ꍇ
			g_nScore[nCntScore].pos = pos;				//pos�l���
			g_nScore[nCntScore].col = col;				//�J���[
			g_nScore[nCntScore].bUse = true;			//�g�p���Ă����Ԃɂ���
			g_nScore[nCntScore].ScoreHeight = fHeight;	//�u���b�N�̍���
			g_nScore[nCntScore].ScoreWidth = fWidth;	//�u���b�N�̕�

			if (pGame == GAMESTATE_NONE)
			{//�Q�[����Ԃ�none��������
				g_nScore[MAX_SET - 1].nNumScore = g_nScore[nCntScore].nNumScore;
				//������
				g_nScore[nCntScore].nNumScore = 0;
			}
			for (int nCntScore2 = 0; nCntScore2 < MAX_SCORE; nCntScore2++)
			{//�X�R�A�̌������J�E���g
				//���_�ݒ�
				pVtx[nCntScore2 * 4].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y, 0.0f);
				pVtx[nCntScore2 * 4 + 1].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x + g_nScore[nCntScore].ScoreWidth - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y, 0.0f);
				pVtx[nCntScore2 * 4 + 2].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y + g_nScore[nCntScore].ScoreHeight, 0.0f);
				pVtx[nCntScore2 * 4 + 3].pos = D3DXVECTOR3(g_nScore[nCntScore].pos.x + g_nScore[nCntScore].ScoreWidth - (nCntScore2 * (g_nScore[nCntScore].ScoreWidth)), g_nScore[nCntScore].pos.y + g_nScore[nCntScore].ScoreHeight, 0.0f);
				//���_�J���[�ݒ�
				pVtx[nCntScore2 * 4].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
				pVtx[nCntScore2 * 4 + 1].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
				pVtx[nCntScore2 * 4 + 2].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
				pVtx[nCntScore2 * 4 + 3].col = D3DXCOLOR(g_nScore[nCntScore].col.r, g_nScore[nCntScore].col.g, g_nScore[nCntScore].col.b, g_nScore[nCntScore].col.a);
			}
			break;
		}
		pVtx += (4 * MAX_SCORE);
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
//
//=============================================================================
void SetCoinState(GETCOINSTATE state)
{
	g_GetCoinState = state;
}
//=============================================================================
// �X�R�A�̃Q�b�g
//=============================================================================
Score *GetScore(void)
{
	return &g_nScore[0];
}