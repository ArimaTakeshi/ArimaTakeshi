//=============================================================================
//
// �I�u�W�F�N�g���� [model.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "object.h"		//�I�u�W�F�N�g
#include "input.h"		//�L�[�{�[�h
#include "camera.h"		//�J����
#include "bullet.h"		//�e
#include "player.h"		//�v���C���[
#include "main.h"		//�Q�[��

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define OBJECT_NAME			"data\\MODEL\\matimati.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME1		"data\\MODEL\\hikouki4.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_NAME2		"data\\MODEL\\�e.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define OBJECT_SPEED		(1.0f)							//�I�u�W�F�N�g�X�s�[�h
#define MAX_OBJECT			(3)								//�I�u�W�F�N�g�̍ő吔
#define MOVE_ANGLE1			(0.001f)
#define MOVE_LEG			(1200.0f)
#define MOVE_SPEED			(0.0009f)
#define MAX_TEX				(40)

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Object g_Object[MAX_OBJECT];											//�I�u�W�F�N�g
LPDIRECT3DTEXTURE9				g_pTextureObject[MAX_TEX] = {};			//�e�N�X�`���ւ̃|�C���^
float g_Objectf;

//=============================================================================
// ����������
//=============================================================================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[0].pBuffMatObject,
		NULL,
		&g_Object[0].nNumMatObject,
		&g_Object[0].pMeshObject
	);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[1].pBuffMatObject,
		NULL,
		&g_Object[1].nNumMatObject,
		&g_Object[1].pMeshObject
	);

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX
	(
		OBJECT_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Object[2].pBuffMatObject,
		NULL,
		&g_Object[2].nNumMatObject,
		&g_Object[2].pMeshObject
	);

	//D3DXMATERIAL *pMat;
	//pMat = (D3DXMATERIAL*)g_Object[1].pBuffMatObject->GetBufferPointer();

	//D3DXCreateTextureFromFile
	//(//1���ڂ̉摜
	//	pDevice,
	//	pMat[0].pTextureFilename,
	//	&g_pTextureObject[0]
	//);
	//D3DXCreateTextureFromFile
	//(//1���ڂ̉摜
	//	pDevice,
	//	pMat[0].pTextureFilename,
	//	&g_pTextureObject[1]
	//);

	D3DXMATERIAL *pMat;
	D3DMATERIAL9 *pMatDef;

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		pMat = (D3DXMATERIAL*)g_Object[nCount].pBuffMatObject->GetBufferPointer();
		pMatDef = new D3DMATERIAL9[g_Object[nCount].nNumMatObject];
		g_Object[nCount].pMeshTextures = new LPDIRECT3DTEXTURE9[g_Object[nCount].nNumMatObject];

		for (DWORD tex = 0; tex < g_Object[nCount].nNumMatObject; tex++)
		{
			pMatDef[tex] = pMat[tex].MatD3D;
			pMatDef[tex].Ambient = pMatDef[tex].Diffuse;
			g_Object[nCount].pMeshTextures[tex] = NULL;
			if (pMat[tex].pTextureFilename != NULL &&
				lstrlen(pMat[tex].pTextureFilename) > 0)
			{
				if (FAILED(D3DXCreateTextureFromFile(pDevice,
					pMat[tex].pTextureFilename,
					&g_Object[nCount].pMeshTextures[tex])))
				{
					MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", NULL, MB_OK);
				}
			}
		}
	}

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		int nNumVtx;		//���_��
		DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

		// �ʒu�E�����̏����ݒ�
		g_Object[nCount].pos = D3DXVECTOR3(0, 0, 0);
		g_Object[nCount].rot = D3DXVECTOR3(0, 0, 0);
		g_Object[nCount].VtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);
		g_Object[nCount].VtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
		g_Object[nCount].bUse = false;
		g_Objectf = 0.0f;

		//���_�����擾
		nNumVtx = g_Object[nCount].pMeshObject->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Object[nCount].pMeshObject->GetFVF());

		//���_�o�b�t�@�̃��b�N
		g_Object[nCount].pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//���_���W�̑��

			//�͈͎w��
			//�ő�l
			if (vtx.x > g_Object[nCount].VtxMaxModel.x)
			{
				g_Object[nCount].VtxMaxModel.x = vtx.x;
			}
			if (vtx.y > g_Object[nCount].VtxMaxModel.y)
			{
				g_Object[nCount].VtxMaxModel.y = vtx.y;
			}
			if (vtx.z > g_Object[nCount].VtxMaxModel.z)
			{
				g_Object[nCount].VtxMaxModel.z = vtx.z;
			}
			//�ŏ��l
			if (vtx.x < g_Object[nCount].VtxMinModel.x)
			{
				g_Object[nCount].VtxMinModel.x = vtx.x;
			}
			if (vtx.y < g_Object[nCount].VtxMinModel.y)
			{
				g_Object[nCount].VtxMinModel.y = vtx.y;
			}
			if (vtx.z < g_Object[nCount].VtxMinModel.z)
			{
				g_Object[nCount].VtxMinModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//�T�C�Y���̃|�C���^��i�߂�
		}
		//���_�o�b�t�@�̃A�����b�N
		g_Object[nCount].pMeshObject->UnlockVertexBuffer();
	}
	g_Object[1].rot.y = 0.0f;
}

//=============================================================================
// �I������
//=============================================================================
void UninitObject(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// ���b�V���̊J��
		if (g_Object[nCount].pMeshObject != NULL)
		{
			g_Object[nCount].pMeshObject->Release();
			g_Object[nCount].pMeshObject = NULL;
		}
		// �}�e���A���̊J��
		if (g_Object[nCount].pBuffMatObject != NULL)
		{
			g_Object[nCount].pBuffMatObject->Release();
			g_Object[nCount].pBuffMatObject = NULL;
		}

		//�e�N�X�`��
		for (DWORD nTex = 0; nTex < g_Object[nCount].nNumMatObject; nTex++)
		{
			if (g_Object[nCount].pMeshTextures[nTex] != NULL)
			{
				g_Object[nCount].pMeshTextures[nTex]->Release();
				g_Object[nCount].pMeshTextures[nTex] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateObject(void)
{
	//���[�h�̃|�C���^
	MODE pMode = *GetMode();
	DIMOUSESTATE2 pMouse = GetMousePointer();
	float fRot;
	if (pMode == MODE_GAME)
	{//�Q�[���̏ꍇ

		//�J�����̃|�C���^
		Camera *pCamera = GetCamera();

		//���f�����J�����ɑ��
		g_Object[2].pos = pCamera[0].posV;

		//�J�����̌������I�u�W�F�N�g�ɑ��
	/*	g_Object[2].rot = pCamera.rot;
		g_Objectf += (pMouse.lY / 500.0f);*/

		fRot = atan2f(powf(pCamera[0].posR.y - pCamera[0].posV.y, 2), powf(pCamera[0].posR.x - pCamera[0].posV.x, 2) + powf(pCamera[0].posR.z - pCamera[0].posV.z, 2));
		g_Object[2].rot.x = fRot;

		//�e�̃Z�b�g
		//SetObject(pCamera[0].posV, pCamera[0].rot);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�m�Ԓ�kk��
	D3DMATERIAL9 matDef;						//���݂̃}�e���A����ۑ�
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Object[nCount].mtxWorldObject);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object[nCount].rot.y, g_Object[nCount].rot.x, g_Object[nCount].rot.z);

		D3DXMatrixMultiply(&g_Object[nCount].mtxWorldObject, &g_Object[nCount].mtxWorldObject, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Object[nCount].pos.x, g_Object[nCount].pos.y, g_Object[nCount].pos.z);

		D3DXMatrixMultiply(&g_Object[nCount].mtxWorldObject, &g_Object[nCount].mtxWorldObject, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐�3��
		pDevice->SetTransform(D3DTS_WORLD, &g_Object[nCount].mtxWorldObject);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Object[nCount].pBuffMatObject->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Object[nCount].nNumMatObject; nCntMat++)
		{
			if (g_Object[nCount].bUse == true)
			{//�r���{�[�h������ꍇ
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`����NULL�ɂ���
				pDevice->SetTexture(0, g_Object[nCount].pMeshTextures[nCntMat]);

				// �I�u�W�F�N�g(�p�[�c)�̕`��
				g_Object[nCount].pMeshObject->DrawSubset(nCntMat);
			}
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=========================================================================================================================
// �I�u�W�F�N�g�̎擾����
//=========================================================================================================================
Object *GetObject(void)
{
	return &g_Object[0];
}
//=========================================================================================================================
// �I�u�W�F�N�g�̂����蔻��
//=========================================================================================================================
void CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	for (int nCntBlock = 0; nCntBlock < MAX_OBJECT; nCntBlock++)
	{//
		if (pPos->x > g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x && pPos->x < g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x)
		{//���͈͊m�F
			if (pPosOld->z >= g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z && g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z > pPos->z)
			{//�ő�̂����蔻��
				pPos->z = g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z;
				pMove->z = 0;
				pMove->x = 0;
			}
			else if (pPosOld->z <= g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z && g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z < pPos->z)
			{//�ŏ��̂����锻��
				pPos->z = g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z;
				pMove->z = 0;
				pMove->x = 0;
			}
		}
		if (pPos->z > g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMinModel.z && pPos->z < g_Object[nCntBlock].pos.z + g_Object[nCntBlock].VtxMaxModel.z)
		{//z�͈͊m�F
			if (pPosOld->x >= g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x && g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x > pPos->x)
			{//�ő�̂����蔻��
				pPos->x = g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMaxModel.x;
				pMove->z = 0;
				pMove->x = 0;
			}
			else if (pPosOld->x <= g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x && g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x < pPos->x)
			{//�ŏ��̂����锻��
				pPos->x = g_Object[nCntBlock].pos.x + g_Object[nCntBlock].VtxMinModel.x;
				pMove->z = 0;
				pMove->x = 0;
			}
		}
	}
}
//=========================================================================================================================
// �A�C�e���̂����蔻��
//=========================================================================================================================
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Camera *pCamera = GetCamera();

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{//�S�e�N�X�`���̃J�E���g
		if (g_Object[nCount].bUse == false)
		{
			g_Object[nCount].pos = pos;
			g_Object[nCount].rot = rot;
			g_Object[nCount].bUse = true;
		break;
		}
	}
}
