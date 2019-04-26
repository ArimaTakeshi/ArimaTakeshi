//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanf�G���[����
#include <stdio.h>					//stdio
#include "player.h"					//�v���C���[
#include "input.h"					//�L�[�{�[�h
#include "camera.h"					//�J����
#include "shadow.h"					//�e
#include "bullet.h"					//�e
#include "effect.h"					//�G�t�F�N�g
#include "object.h"					//�I�u�W�F�N�g
#include "score.h"					//�X�R�A
#include "sound.h"					//�T�E���h

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//#define MODEL_NAME			"data\\MODEL\\airplane000.x"	//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME			"data\\MODEL\\00_body.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME2			"data\\MODEL\\01_head.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME3			"data\\MODEL\\02_armR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME4			"data\\MODEL\\03_handR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME5			"data\\MODEL\\04_armL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME6			"data\\MODEL\\05_handL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME7			"data\\MODEL\\06_legR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME8			"data\\MODEL\\07_footR.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME9			"data\\MODEL\\08_legL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
//#define MODEL_NAME10			"data\\MODEL\\09_footL.x"		//�ǂݍ��ރe�N�X�`���t�@�C��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player		g_Player;							//�v���C���[
int			g_nIdxShadow;						//�ǂ̉e���g���Ă��邩
int			g_nCntTimePlayer;					//�v���C���[�J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���̃|�C���^
	FILE *pFile;
	//�v���C���[�J�E���^�[
	int nCntPlayer;

	// �ʒu�E�����̏����ݒ�
	g_Player.pos = D3DXVECTOR3(0, 20, 0);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0);

	//�t�@�C���ݒ�
	pFile = fopen(FILE_NAME, "r");

	//�v���C���[�́��e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//�g���p�[�c��
		fscanf(pFile, "%d", &g_Player.nMaxPartsNum);	//�ǂݍ���
		//�t�@�C����
		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{
			fscanf(pFile, "%s", &g_Player.aModel[nCntPlayer].FileName[0]); //�ǂݍ���
		}

		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{//�����l�ƌ���
			fscanf(pFile, "%d", &g_Player.aModel[nCntPlayer].nIdxModelParent);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.x);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.y);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.z);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.x);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.y);//�ǂݍ���
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.z);//�ǂݍ���
		}

		//�t�@�C���ǂݍ���
		fscanf(pFile, "%d", &g_Player.nMaxAnimNum);

		for (int nCntPlayerAnim = 0; nCntPlayerAnim < g_Player.nMaxPartsNum; nCntPlayerAnim++)
		{
			//�t���[����
			fscanf(pFile, "%d", &g_Player.nAnimloop[nCntPlayerAnim]);
			//�L�[��
			fscanf(pFile, "%d", &g_Player.nAnimKey[nCntPlayerAnim]);

			for (int nCntPlayerAnimKey = 0; nCntPlayerAnimKey < g_Player.nAnimKey[nCntPlayerAnim]; nCntPlayerAnimKey++)
			{
				fscanf(pFile, "%d", &g_Player.nAnimfram[nCntPlayerAnim][nCntPlayerAnimKey]);//�ǂݍ���

				for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
				{
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//�ǂݍ���
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//�ǂݍ���
				}
			}
		}

		fclose(pFile);	//�t�@�C�������
	}
	else
	{
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s!", "�x��", MB_ICONWARNING);
	}

	//x�t�@�C���̓ǂݍ���
	for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX
		(
			&g_Player.aModel[nCntPlayer].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntPlayer].pBuffMatModel,
			NULL,
			&g_Player.aModel[nCntPlayer].nNumMatModel,
			&g_Player.aModel[nCntPlayer].pMeshModel
		);
	}

	////���f���e�ƃR���h��pos�̈ʒu
	//g_Player.aModel[0].posModel = D3DXVECTOR3(0, 0, 0);			//��
	//g_Player.aModel[1].posModel = D3DXVECTOR3(0, 15, 0);			//��
	//g_Player.aModel[2].posModel = D3DXVECTOR3(-6, 12, 0.0);		//�E�r
	//g_Player.aModel[3].posModel = D3DXVECTOR3(-10, 0, 0);			//�E��
	//g_Player.aModel[4].posModel = D3DXVECTOR3(6, 12, 0.0); 		//���r
	//g_Player.aModel[5].posModel = D3DXVECTOR3(10, 0, 0.0);		//����
	//g_Player.aModel[6].posModel = D3DXVECTOR3(-4, 0, 0);			//�E����
	//g_Player.aModel[7].posModel = D3DXVECTOR3(0, -10, 0);			//�E��
	//g_Player.aModel[8].posModel = D3DXVECTOR3(4, 0, 0);			//������
	//g_Player.aModel[9].posModel = D3DXVECTOR3(0, -10, 0);			//����

	//�e�̏������ݒ�
	g_nIdxShadow = SetShadow(g_Player.pos,g_Player.rot,15,15);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// ���b�V���̊J��
		if (g_Player.aModel[nCount].pMeshModel != NULL)
		{
			g_Player.aModel[nCount].pMeshModel->Release();
			g_Player.aModel[nCount].pMeshModel = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// �}�e���A���̊J��
		if (g_Player.aModel[nCount].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCount].pBuffMatModel->Release();
			g_Player.aModel[nCount].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	//�J�����̏��
	Camera *pCamera = GetCamera();
	
	//�G�t�F�N�g
	SetBulletEffect(g_Player.pos + D3DXVECTOR3(sinf(g_Player.rot.y + D3DX_PI * 0.5f) * 9.0f,0.0f, cosf(g_Player.rot.y + D3DX_PI * 0.5f) * 9.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_BULLET, 2.0f, 10,0);
	SetBulletEffect(g_Player.pos + D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI * 0.5f) * 9.0f, 0.0f, cosf(g_Player.rot.y - D3DX_PI * 0.5f) * 9.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_BULLET, 2.0f, 10,0);

	//�O��̈ʒu��ۑ�
	g_Player.posOld = g_Player.pos;

	float nSpeed = 5.0f;	//���x
	//float fDiffAngle;

	//�ǂ̂����蔻��
	if (g_Player.pos.z >= 390)
	{
		g_Player.pos.z = 390;
	}
	if (g_Player.pos.z <= -390)
	{
		g_Player.pos.z = -390;
	}
	if (g_Player.pos.x >= 390)
	{
		g_Player.pos.x = 390;
	}
	if (g_Player.pos.x <= -390)
	{
		g_Player.pos.x = -390;
	}

	//
	//
	//
	//fDiffAngle = (pCamera->fAngle + D3DX_PI) - g_Player.rot.y;
	//if (fDiffAngle > D3DX_PI)
	//{
	//	fDiffAngle -= D3DX_PI * 2.0;
	//}
	//else if (fDiffAngle < -D3DX_PI)
	//{
	//	fDiffAngle += D3DX_PI * 2.0;
	//}

	//g_Player.rot.y += fDiffAngle * 0.4f;

	//if (g_Player.rot.y > D3DX_PI)
	//{
	//	fDiffAngle -= D3DX_PI * 2.0;
	//}
	//else if (g_Player.rot.y < -D3DX_PI)
	//{
	//	fDiffAngle += D3DX_PI * 2.0;
	//}

	//�ړ�����
	if (GetKeyboardPress(DIK_UP) == true)
	{//���̏�							����ړ�
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//���̉�							 ����ړ�
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);
		}
		else
		{
			g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * MODEL_SPEED;
			//���̕����Ɍ���
			g_Player.rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);
		}
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//���̉E							�� �E�ړ�
		g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* MODEL_SPEED;
		//���̕����Ɍ���
		g_Player.rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);
	}
	else if (GetKeyboardPress(DIK_LEFT) == true)
	{//���̍�							 �� ���ړ�
		g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * MODEL_SPEED;
		//���̕����Ɍ���
		g_Player.rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);
	}
	if (GetKeyboardPress(DIK_T) == true)
	{//��ړ�			
		g_Player.pos.y += 0.3f;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//���ړ�						
		g_Player.pos.y -= 0.3f;
	}

	//�e�̔���
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//�C�ӂ̃L�[�iSPACE�L�[�j���������ꍇ
		SetBullet(g_Player.pos, g_Player.rot,D3DXVECTOR3(sinf(g_Player.rot.y - D3DX_PI) * 3.0f, 0.0f, cosf(g_Player.rot.y - D3DX_PI) * 3.0f));
		PlaySound(SOUND_LABEL_SE_SHOOT);
	}

	//�ʒu���ړ��ɑ��
	g_Player.pos += g_Player.move;

	//����������
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

	//�e�����Ă���
	SetPositionShadow(g_nIdxShadow, g_Player.pos,g_Player.rot);

	//�����蔻��
	CollisionObject(&g_Player.pos, &g_Player.posOld, &g_Player.move);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxParent;						//

	{//�v���C���[
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);
		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
		D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);
		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);
	}
	for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
	{
		if (g_Player.aModel[nCntParts].nIdxModelParent < 0)
		{//�e���f��
			mtxParent = g_Player.mtxWorldPlayer;
		}
		else
		{//�q���f��
			mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorldModel;
		}
		{//�e���f��
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorldModel);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll
			(
				&mtxRot,
				g_Player.aModel[nCntParts].InitRot.y,
				g_Player.aModel[nCntParts].InitRot.x,
				g_Player.aModel[nCntParts].InitRot.z
			);
			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxRot
			);
			// �ʒu�𔽉f
			D3DXMatrixTranslation
			(
				&mtxTrans,
				g_Player.aModel[nCntParts].InitPos.x,
				g_Player.aModel[nCntParts].InitPos.y,
				g_Player.aModel[nCntParts].InitPos.z
			);
			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxTrans
			);

			D3DXMatrixMultiply
			(
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&g_Player.aModel[nCntParts].mtxWorldModel,
				&mtxParent
			);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorldModel);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMatModel; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`����NULL�ɂ���
				pDevice->SetTexture(0, NULL);

				//pDevice->SetTexture(0, g_Player.nNumMatPlayer);

				// �v���C���[(�p�[�c)�̕`��
				g_Player.aModel[nCntParts].pMeshModel->DrawSubset(nCntMat);
			}
			// �}�e���A�����f�t�H���g�ɖ߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}
//=========================================================================================================================
// �v���C���[�̎擾����
//=========================================================================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}
