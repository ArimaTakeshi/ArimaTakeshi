//=============================================================================
//
// �Ǐ��� [wall.cpp]
// Author : �L�n ���u
//
//=============================================================================
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "markwall.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define WALL_TEX_1	"data\\TEXTURE\\wall\\wall000.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_2	"data\\TEXTURE\\wall\\wall001.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_3	"data\\TEXTURE\\wall\\field03.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_4	"data\\TEXTURE\\wall\\rock_003.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_5	"data\\TEXTURE\\wall\\soil.jpg"				// �e�N�X�`���̖��O
#define WALL_TEX_6	"data\\TEXTURE\\wall\\scarp02.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_7	"data\\TEXTURE\\wall\\wallRock.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_8	"data\\TEXTURE\\wall\\Black.jpg"			// �e�N�X�`���̖��O
#define WALL_TEX_9	"data\\TEXTURE\\wall\\wall000.png"			// �e�N�X�`���̖��O

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CWall::m_pTexture[MAX_WALL_TEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWall::CWall() : CScene3D(WALL_PRIOTITY, CScene::OBJTYPE_WALL)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWall::~CWall()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWall::Init()
{
	//����������
	CScene3D::Init();

	//��ނ̐ݒ�
	SetTypeNumber(TYPE_WALL);

	if (m_nType == 9)
	{
		CScene3D::SetNor(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWall::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CWall::Update(void)
{
	CScene3D::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CWall::Draw(void)
{
	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�߂��̕ǈȊO������
	if (m_pos.x + 2000.0f >= PlayerPos.x && m_pos.x - 2000.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		//3D���f����Draw
		CScene3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		CScene3D::Draw();
	}
}
//=============================================================================
// ��������
//=============================================================================
CWall * CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nTexType)
{
	CWall *pWall = NULL;

	//NULL�`�F�b�N
	if (pWall == NULL)
	{//�������̓��I�m��

		pWall = new CWall;

		if (pWall != NULL)
		{
			//��ނ̐ݒ�
			pWall->m_nType = nTexType;
			//����������
			pWall->Init();
			//�ʒu�̐ݒ�
			pWall->m_pos = pos;
			//�����蔻��p
			pWall->m_size = size;
			//�e�N�X�`���̐ݒ�
			pWall->BindTexture(m_pTexture[nTexType]);
			//�ʒu�Ɖ�]�ƃT�C�Y
			pWall->SetWall(pos, rot, size);

			//�t�@�C���p
			pWall->m_fWidthDivide = size.x;
			pWall->m_fHightDivide = size.y;
			pWall->m_rot = rot;
			pWall->m_nTexType = nTexType;
		}
	}

	return pWall;
}
//=============================================================================
// �ǂ̓����蔻��
//=============================================================================
void CWall::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fDepth)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene *pScene;
	
	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_WALL)
			{// pos��rot���擾
				D3DXVECTOR3 WallPos = ((CScene3D*)pScene)->GetPosition();
				D3DXVECTOR3 WallRot = ((CScene3D*)pScene)->GetRotation();
				D3DXVECTOR2 WallSize = ((CScene3D*)pScene)->GetSize();

				if (WallRot.y == (0.0f * D3DX_PI))
				{// Z�����̕�
					if (pPos->x <= WallPos.x + WallSize.x + 18.5f
						&& pPos->x >= WallPos.x - WallSize.x - 18.5f)
					{// �ǂƓ���z���ɑ��݂��Ă���
						if (pPos->z <= WallPos.z + WallSize.x + 18.5f
							&& pPos->z >= WallPos.z - WallSize.x - 18.5f)
						{// �ǂƓ���x���ɑ��݂��Ă���
							if (pPos->y < WallPos.y + WallSize.y && pPos->y + 100.0f >= WallPos.y)
							{// �ǂ����Ⴂ
								if (pPos->z >= WallPos.z - fDepth
									&& pPosOld->z <= WallPos.z - fDepth)
								{// ��O����ǂ��ђʂ���
									pPos->z = WallPos.z - fDepth;
								}
								else if (pPos->z <= WallPos.z + fDepth
									&& pPosOld->z >= WallPos.z + fDepth)
								{// ������ǂ��ђʂ���
									pPos->z = WallPos.z + fDepth;
								}
							}
						}
					}
				}			
				else if (WallRot.y == (0.5f * D3DX_PI))
				{// X�����̕�
					if (pPos->x <= WallPos.x + WallSize.x + 18.5f
						&& pPos->x >= WallPos.x - WallSize.x - 18.5f)
					{// �ǂƓ���z���ɑ��݂��Ă���
						if (pPos->z <= WallPos.z + WallSize.x + 18.5f
							&& pPos->z >= WallPos.z - WallSize.x - 18.5f)
						{// �ǂƓ���x���ɑ��݂��Ă���
							if (pPos->y < WallPos.y + WallSize.y && pPos->y + 100.0f >= WallPos.y)
							{// �ǂ����Ⴂ
								if (pPos->x >= WallPos.x - fDepth
									&& pPosOld->x <= WallPos.x - fDepth)
								{// ��O����ǂ��ђʂ���
									pPos->x = WallPos.x - fDepth;
								}
								else if (pPos->x <= WallPos.x + fDepth
									&& pPosOld->x >= WallPos.x + fDepth)
								{// ������ǂ��ђʂ���
									pPos->x = WallPos.x + fDepth;
								}
							}
						}
					}
				}
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}

//=============================================================================
// �ǂݍ��ݏ���
//=============================================================================
HRESULT CWall::Load(void)
{
	// �f�o�C�X�擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`������
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_9, &m_pTexture[8]);

	return S_OK;
}

//=============================================================================
// �J������
//=============================================================================
void CWall::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_WALL_TEX; nCount++)
	{
		// �e�N�X�`���j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//===============================================================================
// �t�@�C���ɃZ�[�u
//===============================================================================
void CWall::TextSave(void)
{
	int nMarkWall = CMarkWall::GetWallNum();

	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//�t�@�C���̃|�C���^
	FILE *pFile;

	//�t�@�C���ǂݎ��ݒ�
	pFile = fopen(WALL_NAME, "wb");

	//�v���C���[�̃e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//������
		fprintf(pFile, "#====================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#�@�}�b�v�̕ǔz�u�̃G�f�B�^ [wall.txt]\n");
		fprintf(pFile, "#�@����� : �L�n�@���u\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================\n\n");
		//�u�����I�u�W�F�N�g�̐�
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#�@�ǂ̐ݒu��\n");
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "WALL_SETNUM = ");
		fprintf(pFile, "%d\n\n", nMarkWall);
		//������
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#�@�ǂ̐ݒu���\n");
		fprintf(pFile, "#----------------------------------------------------\n");

		//NULL�`�F�b�N
		while (pScene != NULL)
		{
			//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
			CScene *pSceneNext = pScene->GetNext();

			if (pScene->GetDeath() == false)
			{
				//�^�C�v���I�u�W�F�N�g��������
				if (pScene->GetObjType() == OBJTYPE_WALL)
				{
					//�J�n�̂��߂̐錾
					fprintf(pFile, "WALL_START\n");
					//�ʒu������
					fprintf(pFile, "	POS = ");
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_pos.x);
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_pos.y);
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_pos.z);
					//��]������
					fprintf(pFile, "	ROT = ");
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_rot.x);
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_rot.y);
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_rot.z);
					//X�T�C�Y������
					fprintf(pFile, "	WIDTH = ");
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_fWidthDivide);
					//Y�T�C�Y������
					fprintf(pFile, "	HIGHT = ");
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_fHightDivide);
					//�e�N�X�`���̎�ނ�����
					fprintf(pFile, "	TEXTURE = ");
					fprintf(pFile, "%d\n", ((CWall*)pScene)->m_nTexType);
					//�J�n�̂��߂̐錾
					fprintf(pFile, "WALL_END\n\n");
				}
			}

			//Next�Ɏ���Scene������
			pScene = pSceneNext;
		}

		//�t�@�C�������
		fclose(pFile);
	}
}

