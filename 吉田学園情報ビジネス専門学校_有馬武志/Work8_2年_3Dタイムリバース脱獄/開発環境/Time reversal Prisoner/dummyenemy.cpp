//=============================================================================
//
// �G�l�~�[�̏��� [dummyenemy.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "dummyenemy.h"
#include "manager.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "object.h"
#include "game.h"
#include "wall.h"
#include "ground.h"
#include "item.h"
#include "shadow.h"
#include "input.h"
#include "serect.h"
#include "meshorbit.h"
#include "player.h"
#include "effect.h"
#include "billboord.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH	CDummyEnemy::m_pMesh[MAX_PARTS] = {};		//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CDummyEnemy::m_pBuffMat[MAX_PARTS] = {};	//�}�e���A���̏��ւ̃|�C���^
DWORD CDummyEnemy::m_nNumMat[MAX_PARTS] = {};			//�}�e���A���̏��
CMeshOrbit *CDummyEnemy::m_MeshOrbit = NULL;

//--------------------------------------------
//�O���[�o���ϐ�
//--------------------------------------------
int g_nNumDummyEnemyModel;
char g_aFileNameDummyEnemyModel[MAX_PARTS][256];

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CDummyEnemy::CDummyEnemy(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	//�l�̏�����
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		m_apModel[nCount] = NULL;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ߋ��̈ʒu
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CDummyEnemy::~CDummyEnemy()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CDummyEnemy::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ߋ��̈ʒu
	m_bJump = true;								//�W�����v�̏��
	m_bLand = true;								//���n�̏��
	m_bMotionEnd = true;						//���[�V�����̏I���
	m_nAnimnow = DUMMYENEMYANIM_NEUTRAL;		//���[�V�����̏�����

	//�v���C���[���̓ǂݍ���
	FileLoad();

	//�e�̕`��
	m_pShadow = CShadow::Create(m_pos, 25.0f, 25.0f, 0);

	//�r���{�[�h����
	m_pBillboord = CBillBoord::Create(m_pos, D3DXVECTOR2(30, 30),0);

	//�e�N�X�`���̓ǂݍ���
	//CMeshOrbit::Load();

	//�O�Ղ̐���
	//m_MeshOrbit = CMeshOrbit::Create();

	//�v���C���[�̃��[���h�}�g���b�N�X�̔��f
	//m_MeshOrbit->SetMatRarent(&m_apModel[15]->GetMtxWorld());

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CDummyEnemy::Uninit(void)
{
	//�e�N�X�`���̔j��
	CMeshOrbit::UnLoad();

	m_pShadow->Uninit();

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//3D���f����Uninit
			m_apModel[nCount]->Uninit();
			delete m_apModel[nCount];
			m_apModel[nCount] = NULL;
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CDummyEnemy::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	CSound *pSound = CManager::GetSound();
	CManager::MODE pMode = CManager::GetMode();
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

	//��]�̒l��ۑ�
	m_rotDest = m_rot;

	if (pMode == CManager::MODE_GAME)
	{
		// �d��
		m_move.y -= cosf(0) * 2.0f;

		//�ʒu���ړ��ɑ��
		//m_pos += m_move;

		//����������
		m_move.x += (0.0f - m_move.x) * 0.2f;
		m_move.z += (0.0f - m_move.z) * 0.2f;

		//�ڕW���`�F�b�N
		if (m_rotDest.y > D3DX_PI)
		{
			m_rotDest.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rotDest.y < -D3DX_PI)
		{
			m_rotDest.y += (D3DX_PI * 2.0f);
		}

		float fRotDest = (m_rotDest.y - m_rot.y);

		//�������`�F�b�N
		if (fRotDest > D3DX_PI)
		{
			fRotDest -= (D3DX_PI * 2.0f);
		}
		else if (fRotDest < -D3DX_PI)
		{
			fRotDest += (D3DX_PI * 2.0f);
		}

		m_rot.y += (fRotDest) * 0.2f;

		//�������`�F�b�N
		if (m_rot.y > D3DX_PI)
		{
			m_rot.y -= (D3DX_PI * 2.0f);
		}
		else if (m_rot.y < -D3DX_PI)
		{
			m_rot.y += (D3DX_PI * 2.0f);
		}

		//�e�̍�����ێ����Ă���
		float fMeshHeight = m_pShadow->GetShadowHeight();

		if (m_bJump == false)
		{
			m_pShadow->SetPositionShadow(D3DXVECTOR3(m_pos.x, fMeshHeight, m_pos.z));
		}
		if (m_bLand == true)
		{
			m_pShadow->SetPositionShadow(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z));
		}

		//// �n�ʂ̍������擾
		//CollisitionMesh();
		//// �ǂ̓����蔻��
		//CollisitionWall();
		//// �I�u�W�F�N�g�̓����蔻��
		//CollisitionObject3D(&m_pos, &m_posOld, &m_move);
		//// �A�C�e���̓����蔻��
		//CollisitionItem();
	}

	m_nMotionType = m_nAnimnow;

	//���[�V�����X�V
	UpdateMotion();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CDummyEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		if (m_apModel[nCount] != NULL)
		{
			//���f���̕`��
			m_apModel[nCount]->Draw(0.4f);
		}
	}
}
//=============================================================================
//	���b�V���̓����蔻��
//=============================================================================
void CDummyEnemy::CollisitionMesh(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(MESH_PRIOTITY);

	//�W�����v��false��
	m_bJump = false;

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_MESH)
			{
				//�v���C���[��Hight������
				if (((CMesh*)pScene)->GetHeight(m_pos))
				{
					//�W�����v���Ă����Ԃɂ���
					m_bJump = true;
					//�������Ƃ���move������������
					m_move.y = 0.0f;

					if (m_bJump == true)
					{
						m_pShadow->SetPositionShadow(m_pos);
					}
				}
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�ǂ̓����蔻��
//=============================================================================
void CDummyEnemy::CollisitionWall(void)
{
	CScene *pScene;
	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_WALL)
			{
				((CWall*)pScene)->CollisionWall(&m_pos, &m_posOld, &m_move, 20.0f);
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�I�u�W�F�N�g�̓����蔻��
//=============================================================================
void CDummyEnemy::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//�ϐ��錾
	bool bLand = false;

	//bLand�̏���������
	m_bLand = false;

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				//�I�u�W�F�N�g�̂����锻��
				bLand = ((CObject*)pScene)->CollisionObject(pPos, pPosOld, pMove);

				//���n�����L����
				if (bLand)
				{
					m_bLand = bLand;
				}
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�A�C�e���̓����蔻��
//=============================================================================
void CDummyEnemy::CollisitionItem(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(4);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v���A�C�e����������
			if (pScene->GetObjType() == OBJTYPE_ITEM)
			{
				//�����蔻��
				if (((CItem*)pScene)->CollisionItem(&m_pos, &m_posOld, &m_move))
				{
					pScene->Uninit();
				}
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
//	�ʒu��������
//=============================================================================
void CDummyEnemy::DeleteEnemy(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(2);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_ENEMY)
			{
				pScene->Uninit();
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CDummyEnemy * CDummyEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nAnimnow)
{
	CDummyEnemy *pDummyEnemy = NULL;

	//NULL�`�F�b�N
	if (pDummyEnemy == NULL)
	{//�������̓��I�m��

		pDummyEnemy = new CDummyEnemy;

		if (pDummyEnemy != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pDummyEnemy->Init();
			//�ʒu�̔��f
			pDummyEnemy->m_pos = pos;
			pDummyEnemy->m_rot = rot;
			pDummyEnemy->m_nAnimnow = (DummyEnemyAnim)nAnimnow;
		}
	}

	return pDummyEnemy;
}
//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CDummyEnemy::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CDummyEnemy::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}
//=============================================================================
// �v���C���[�̃��[�V����
//=============================================================================
void CDummyEnemy::UpdateMotion(void)
{
	//���[�V����
	KEY *pKey, *pNextKey;
	float fRateMotion;
	float fDiffMotion;
	D3DXVECTOR3 rotmotion;
	D3DXVECTOR3 posmotion;
	//D3DXVECTOR3 posParent;


	//�L�[���ő吔������Ȃ��悤��
	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	//���[�V�����X�V
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apModel[nCntParts] != NULL)
		{
			//���݂̃L�[���擾
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
			//���̃L�[���擾
			pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

			//���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
			fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

			//ROT
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->frotX - pKey->frotX;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

			//POS
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->fposX - pKey->fposX;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);


			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->frotY - pKey->frotY;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);
			//POS
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->fposY - pKey->fposY;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);


			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->frotZ - pKey->frotZ;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
			//POS
			//���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pNextKey->fposZ - pKey->fposZ;
			//���Βl���������g���Ċe�v�f�̒l���Z�o
			posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);


			//�p�[�c�𓮂���
			m_apModel[nCntParts]->Setrot(rotmotion);

			//POS
			m_apModel[nCntParts]->SetPos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x,
				m_OffSetPos[nCntParts].y + posmotion.y,
				m_OffSetPos[nCntParts].z + posmotion.z));

		}
	}

#ifdef  _DEBUG
	CDebugProc::Print(" Num�L�[  : (%d)\n", m_nKey);
	CDebugProc::Print(" m_nCountFlame  : (%d)\n", m_nCountFlame);

#endif

}

//=============================================================================
// �t�@�C���ǂݍ���
//=============================================================================
void CDummyEnemy::FileLoad(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�t�@�C���ǂݍ��ݗp�ϐ�
	FILE *pFile;		//�t�@�C���|�C���^
	char *pStrcur;		//���݂̐擪�̕�����
	char aLine[256];	//������
	char aStr[256];		//�ꎞ�ۑ�������
	int nIndex = 0;		//���݂̃C���f�b�N�X
	int nWord = 0;		//�|�b�v�ŕԂ��ꂽ�l��ێ�

	D3DXVECTOR3 ParentPos;	//�e�̈ʒu�����擾
#if 1
	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME, "r");

	//NULL�`�F�b�N
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; )
		{
			//������̐擪��ݒ�
			pStrcur = ReadLine(pFile, &aLine[0]);
			//����������o��
			strcpy(aStr, pStrcur);

			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//���o��
				pStrcur += strlen("NUM_MODEL = ");
				//������̐擪��ݒ�
				strcpy(aStr, pStrcur);
				//�����񔲂��o��
				g_nNumDummyEnemyModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumDummyEnemyModel; nCntModel++)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������߂�
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//���o��
						pStrcur += strlen("MODEL_FILENAME = ");

						//�������ݒ�
						strcpy(aStr, pStrcur);

						//�K�v�ȕ�����̍Ō�̕����܂ł̕������𐔂���
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//����������߂�
						strcpy(aStr, pStrcur);

						//�Ō�̕�����NULL����������
						aStr[nNullNum - 1] = '\0';

						//�Ώۂ̕����񂩂甲���o��
						strcpy(&g_aFileNameDummyEnemyModel[nCntModel][0], aStr);

						// X�t�@�C���̓ǂݍ���
						D3DXLoadMeshFromX(&g_aFileNameDummyEnemyModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMat[nCntModel],
							NULL,
							&m_nNumMat[nCntModel],
							&m_pMesh[nCntModel]);
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}


			//������̃f�[�^ ��r���镶���� ��r���镶����
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_PARTS = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEX��ǂݍ���
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								//���o��
								pStrcur += strlen("INDEX = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								nIndex = atoi(pStrcur);
							}
							//PARENT��ǂݍ���
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								//���o��
								pStrcur += strlen("PARENT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//�����񔲂��o��
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							//POS��ǂݍ���
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{
								//���o��
								pStrcur += strlen("POS = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//���������i�߂�
								pStrcur += nWord;

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							//ROT��ǂݍ���
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{
								//���o��
								pStrcur += strlen("ROT = ");
								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);

								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//���������i�߂�
								pStrcur += nWord;
								//��������Ԃ��Ă��炤
								nWord = PopString(pStrcur, &aStr[0]);
								//������ϊ�
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);
							}
							//�p�[�c�Z�b�g�I��
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{
								//NULL�`�F�b�N
								if (m_apModel[nIndex] == NULL)
								{//���I�m��
									m_apModel[nIndex] = new CModel;
									//NULL�`�F�b�N
									if (m_apModel[nIndex] != NULL)
									{
										//���f���̐���
										m_apModel[nIndex]->BindModel(m_pMesh[nIndex], m_pBuffMat[nIndex], m_nNumMat[nIndex]);
										m_apModel[nIndex]->Init();
									}
								}

								//���f���𐶐�	�I�t�Z�b�g�ݒ�
								/*m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
										m_pos.y + m_aKayOffset[nIndex].fposY,
										m_pos.z + m_aKayOffset[nIndex].fposZ), m_rot);*/

								m_apModel[nIndex]->SetPos(D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
									m_pos.y + m_aKayOffset[nIndex].fposY,
									m_pos.z + m_aKayOffset[nIndex].fposZ));

								//pos����
								ParentPos = m_apModel[nIndex]->GetPos();
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//���f�������蓖��
								m_apModel[nIndex]->BindModel(m_pMesh[nIndex], m_pBuffMat[nIndex], m_nNumMat[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{
									//���f���̐e���w��
									m_apModel[nIndex]->SetParent(NULL);
									ParentPos = m_apModel[nIndex]->GetPos();
								}
								else
								{
									//���f���̐e���w��
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}

								break;
							}
						}
					}
					//�L�����N�^�[�Z�b�g�I��
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
				//������̐擪��ݒ�
				pStrcur = ReadLine(pFile, &aLine[0]);
				//����������o��
				strcpy(aStr, pStrcur);
			}

			//���[�V�����ǂݍ���
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{
				//���o��
				pStrcur += strlen("MOTIONSET");

				while (1)
				{
					//������̐擪��ݒ�
					pStrcur = ReadLine(pFile, &aLine[0]);
					//����������o��
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//���o��
						pStrcur += strlen("LOOP = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//�����񔲂��o��
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
					}
					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//���o��
						pStrcur += strlen("NUM_KEY = ");
						//������̐擪��ݒ�
						strcpy(aStr, pStrcur);
						//�����񔲂��o��
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//������̐擪��ݒ�
						pStrcur = ReadLine(pFile, &aLine[0]);
						//����������o��
						strcpy(aStr, pStrcur);
					}

					//�L�[�̐ݒ�
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{
							//���o��
							pStrcur += strlen("KEYSET");
							//������̐擪��ݒ�
							strcpy(aStr, pStrcur);
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{
								//���o��
								pStrcur += strlen("FRAME = ");

								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);

								//������̐擪��ݒ�
								strcpy(aStr, pStrcur);
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
							}

							//�p�[�c����
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);

									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{
										//���o��
										pStrcur += strlen("POS = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z���
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									//ROT��ǂݍ���
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{
										//���o��
										pStrcur += strlen("ROT = ");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//���������i�߂�
										pStrcur += nWord;

										//��������Ԃ��Ă��炤
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{
										//���o��
										pStrcur += strlen("END_KEY");
										//������̐擪��ݒ�
										strcpy(aStr, pStrcur);
										//������̐擪��ݒ�
										pStrcur = ReadLine(pFile, &aLine[0]);
										//�p�[�c�̃J�E���g��i�߂�
										nCntParts++;
									}
								}
								else
								{
									//������̐擪��ݒ�
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								//������̐擪��ݒ�
								pStrcur = ReadLine(pFile, &aLine[0]);
								//�J�E���g��i�߂�
								nCntKey++;
							}
						}
						else
						{
							//������̐擪��ݒ�
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						//���[�V�����̏����Z�b�g
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						nCntMotion++;
						break;
					}
				}
			}
			//�X�N���v�g�̏I���
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
#endif

}

//=============================================================================
//�@�t�@�C���ǂݍ��ݖ�������r��
//=============================================================================
char *CDummyEnemy::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//�P�s���ǂݍ���
		fgets(&pDst[0], 256, pFile);

		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//�@�t�@�C���ǂݍ��ݐ擪��r��
//=============================================================================
char * CDummyEnemy::GetLineTop(char * pStr)
{
	while (1)
	{
		//������̃f�[�^ ��r���镶���� ��r���镶����
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//�@��������Ԃ�
//=============================================================================
int CDummyEnemy::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//���o��
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//���o��
			pStr = "\0";
			nWord += (int)strlen("\t");
			break;
		}
		//������̃f�[�^ ��r���镶���� ��r���镶����
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//���o��
			nWord += (int)strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//������̐���Ԃ�
	return nWord;
}
