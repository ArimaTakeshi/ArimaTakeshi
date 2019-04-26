//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanf�G���[����
#include <stdio.h>					//stdio
#include "herimodel.h"				//�v���C���[
#include "input.h"					//�L�[�{�[�h
#include "camera.h"					//�J����
#include "shadow.h"					//�e
#include "bullet.h"					//�e
#include "effect.h"					//�G�t�F�N�g
#include "object.h"					//�I�u�W�F�N�g
#include "score.h"					//�X�R�A
#include "game.h"					//�Q�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_ANGLE1	(0.0001f);		//�v���y���̓���
#define MOVE_OBJECT (1000.0f);		//�z�u�ʒu
#define MOVE_ANGLE2	(15.0f);		//�p�x
#define MOVE_SPEED	(2.5f);			//�v���y���̉�]�X�s�[�h

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player2		g_Player2;				//�v���C���[
int			g_nCntTimePlayer2;		//�v���C���[�J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�v���C���[�J�E���^�[
	int nCntPlayer2;

	// �ʒu�E�����̏����ݒ�
	g_Player2.pos = D3DXVECTOR3(0, 600, -1500);
	g_Player2.rot = D3DXVECTOR3(0, 0, 0);
	g_Player2.move = D3DXVECTOR3(0, 0, 0);

	//�t�@�C���ݒ�
	pFile = fopen(HERIFILE_NAME, "r");

	//�v���C���[�́��e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//�g���p�[�c��
		fscanf(pFile, "%d", &g_Player2.nMaxPartsNum);	//�ǂݍ���
		//�t�@�C����
		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{
			fscanf(pFile, "%s", &g_Player2.aModel[nCntPlayer2].FileName[0]); //�ǂݍ���
		}

		for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
		{//�����l�ƌ���
			fscanf(pFile, "%d", &g_Player2.aModel[nCntPlayer2].nIdxHeriParent);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriPos.x);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriPos.y);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriPos.z);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriRot.x);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriRot.y);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player2.aModel[nCntPlayer2].InitHeriRot.z);//�ǂݍ���
		}

		fclose(pFile);	//�t�@�C�������
	}
	else
	{
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s!", "�x��", MB_ICONWARNING);
	}

	//x�t�@�C���̓ǂݍ���
	for (nCntPlayer2 = 0; nCntPlayer2 < g_Player2.nMaxPartsNum; nCntPlayer2++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX
		(
			&g_Player2.aModel[nCntPlayer2].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player2.aModel[nCntPlayer2].pBuffMatHeri,
			NULL,
			&g_Player2.aModel[nCntPlayer2].nNumMatHeri,
			&g_Player2.aModel[nCntPlayer2].pMeshHeri
		);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer2(void)
{
	for (int nCount = 0; nCount < MAX_HERIPARTS; nCount++)
	{
		// ���b�V���̊J��
		if (g_Player2.aModel[nCount].pMeshHeri != NULL)
		{
			g_Player2.aModel[nCount].pMeshHeri->Release();
			g_Player2.aModel[nCount].pMeshHeri = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_HERIPARTS; nCount++)
	{
		// �}�e���A���̊J��
		if (g_Player2.aModel[nCount].pBuffMatHeri != NULL)
		{
			g_Player2.aModel[nCount].pBuffMatHeri->Release();
			g_Player2.aModel[nCount].pBuffMatHeri = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer2(void)
{
	//���[�h�̃|�C���^
	MODE pMode = *GetMode();

	if (pMode == MODE_GAME)
	{
		//�ړ�
		g_Player2.pos.z += MOVE_SPEED;

		if (g_Player2.pos.z == 1500)
		{
			g_Player2.pos = D3DXVECTOR3(0, 600, -1500);
		}

		//�v���y���̉�]
		g_Player2.aModel[1].InitHeriRot.y += MOVE_ANGLE2;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						//

	{//�v���C���[
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player2.mtxWorldPlayer2);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player2.rot.y, g_Player2.rot.x, g_Player2.rot.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorldPlayer2, &g_Player2.mtxWorldPlayer2, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player2.pos.x, g_Player2.pos.y, g_Player2.pos.z);
		D3DXMatrixMultiply(&g_Player2.mtxWorldPlayer2, &g_Player2.mtxWorldPlayer2, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player2.mtxWorldPlayer2);
	}
	for (int nCntParts = 0; nCntParts < MAX_HERIPARTS; nCntParts++)
	{
		if (g_Player2.aModel[nCntParts].nIdxHeriParent < 0)
		{//�e���f��
			mtxParent = g_Player2.mtxWorldPlayer2;
		}
		else
		{//�q���f��
			mtxParent = g_Player2.aModel[g_Player2.aModel[nCntParts].nIdxHeriParent].mtxWorldHeri;
		}
		{//�e���f��
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player2.aModel[nCntParts].mtxWorldHeri);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player2.aModel[nCntParts].InitHeriRot.y,
				g_Player2.aModel[nCntParts].InitHeriRot.x,
				g_Player2.aModel[nCntParts].InitHeriRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&mtxRot
			);
			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player2.aModel[nCntParts].InitHeriPos.x,
				g_Player2.aModel[nCntParts].InitHeriPos.y,
				g_Player2.aModel[nCntParts].InitHeriPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&g_Player2.aModel[nCntParts].mtxWorldHeri,
				&mtxParent
			);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player2.aModel[nCntParts].mtxWorldHeri);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player2.aModel[nCntParts].pBuffMatHeri->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player2.aModel[nCntParts].nNumMatHeri; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`����NULL�ɂ���
				pDevice->SetTexture(0, NULL);

				//pDevice->SetTexture(0, g_Player22.nNumMatPlayer2);

				// �v���C���[(�p�[�c)�̕`��
				g_Player2.aModel[nCntParts].pMeshHeri->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================================================================================================
// �v���C���[�̎擾����
//=========================================================================================================================
Player2 *GetPlayer2(void)
{
	return &g_Player2;
}
