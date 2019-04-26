//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"SceneModel.h"
#include"ScenePlayer.h"
#include"Enemy.h"
#include"SceneBoss.h"
#include "Bullet.h"
#include "SceneAnim3D.h"
#include "3DNumber.h"
#include "dungeon.h"
#include "collision.h"
#include "camera.h"
#include "Game.h"
#include "manager.h"
#include"Renderer.h"

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CCollision::CollisionAll(void)
{
	CScene **PScene;
	CScene::OBJTYPE obj = CScene::OBJTYPE_NONE;
	D3DXVECTOR3 *Targetpos = NULL;
	float		*fTargetX = NULL;
	float		*fTargetZ = NULL;
	D3DXVECTOR3 *pos;

	//�V�[���h�̔���
	//for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	//{
	//	pPlayer = CManager::GetPlayer(nCount);
	//	if (pPlayer != NULL) { pPlayer->Shield(); }
	//}

	//for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		int nCount = 1;
		PScene = CScene::GetScene(nCount);
		for (int nCntScene = 0; nCntScene < CScene::GetnMemoryAll(nCount); nCntScene++)
		{//�S�V�[�������
			if (PScene[nCntScene] != NULL)
			{//���g��NULL�łȂ�
				switch (PScene[nCntScene]->GetObjType())
				{//����̂���I�u�W�F�N�g�Ȃ�
				case CScene::OBJTYPE_ENEMY:
					obj = CScene::OBJTYPE_ENEMY;
					break;
				case CScene::OBJTYPE_BOSS:
					if (((CSceneBoss*)PScene[nCntScene])->GetfPlusY() <= 2.0f)
					{
						obj = CScene::OBJTYPE_BOSS;
					}
					break;
				case CScene::OBJTYPE_PLAYER:
					if (((CScenePlayer*)PScene[nCntScene])->GetfLife()[0] > 0.0f)
					{
						obj = CScene::OBJTYPE_PLAYER;
					}
					break;

				case CScene::OBJTYPE_OBJ:
					pos = ((CSceneObjct*)PScene[nCntScene])->GetPosition();
					if (pos[0].x > CCamera::camera.m_posV.x + 120 || pos[0].x < CCamera::camera.m_posV.x - 120 ||
						pos[0].z > CCamera::camera.m_posV.z + 80 || pos[0].z > CCamera::camera.m_posV.z + 80)
					{
						break;
					}
					else
					{
						obj = CScene::OBJTYPE_OBJ;
					}
					break;
				}

				if (obj == CScene::OBJTYPE_ENEMY)
				{//�����ɓ������Ȃ�
					CScene **PSceneTarget = NULL;
					int nTarget = BULLET_PRIORITY;
					//for (int nCnt = 0; nCnt < 1; nCnt++)
					{
						//switch (nCnt)
						//{
						//case 0: nTarget = BULLET_PRIORITY; break;
						//}
						PSceneTarget = CScene::GetScene(nTarget);
						for (int nCntTarget = 0; nCntTarget < CScene::GetnMemoryAll(nTarget); nCntTarget++)
						{
							if (PSceneTarget[nCntTarget] != NULL && (nCntScene != nCntTarget || nTarget != 1))
							{
								if (CScene::OBJTYPE_BULLET == PSceneTarget[nCntTarget]->GetObjType())
								{//�e�I
									CBullet *pBullet = (CBullet*)PSceneTarget[nCntTarget];
									if (BulletCollision(PScene[nCntScene], obj, pBullet)) { break; }//nCnt = 3;
								}//if(BULLET)
							}//if(NULL)
						}//for()
					}
					obj = CScene::OBJTYPE_NONE;
				}//���肠����̂Ȃ�
			}//NULL�`�F�b�N
		}//for()
	}
}
//=============================================================================
//�I�u�W�F�N�g�̂����蔻��	�S����]
//=============================================================================
void CCollision::ObjectCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float fLengthX, float fLengthZ, int nID)
{
	CScene **PSceneTarget = NULL;

	PSceneTarget = CScene::GetScene(1);
	for (int nCntTarget = 0; nCntTarget < CScene::GetnMemoryAll(1); nCntTarget++)
	{
		if (PSceneTarget[nCntTarget] != NULL && nID != nCntTarget)
		{
			if (PSceneTarget[nCntTarget]->GetObjType() >= CScene::OBJTYPE_PLAYER && PSceneTarget[nCntTarget]->GetObjType() <= CScene::OBJTYPE_OBJ)
			{//���f���Ȃ�
				ObjectCollision(pos, posold, fLengthX, fLengthZ, PSceneTarget[nCntTarget]);
			}
		}//if(NULL)
	}//for()

}
//=============================================================================
//�I�u�W�F�N�g�̂����蔻��	�e�������A�v���C���[����߂�
//=============================================================================
void CCollision::ObjectCollision(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLengthX, float& fLengthZ, CScene *&pScene1)
{
	//�I�u�W�F�^�C�v�l��
	CScene::OBJTYPE obj1 = pScene1->GetObjType();

	//���̊l��
	D3DXVECTOR3 *pos1 ;
	D3DXVECTOR3 *posold1;
	float		fSizeX1;
	float		fSizeZ1;
	if (GetInfo(pScene1, obj1, pos1, posold1, fSizeX1, fSizeZ1, false)) { return; }

	if (pos1[0].x + fSizeX1 > pos.x - fLengthX && pos1[0].x - fSizeX1 < pos.x + fLengthX)
	{//�������͈͓� //�㉺Hit
		if (pos1[0].z + fSizeZ1 > pos.z - fLengthZ && pos1[0].z + fSizeZ1 <= posold.z - fLengthZ)
		{//��
			pos.z = pos1[0].z + fSizeZ1 + fLengthZ;
		}
		else if (pos1[0].z - fSizeZ1 < pos.z + fLengthZ && pos1[0].z - fSizeZ1 >= posold.z + fLengthZ)
		{//��
			pos.z = pos1[0].z - fSizeZ1 - fLengthZ;
		}
	}
	if (pos1[0].z + fSizeZ1 > pos.z - fLengthZ && pos1[0].z - fSizeZ1 < pos.z + fLengthZ)
	{//�c�����͈͓� //��Hit
		if (pos1[0].x + fSizeX1 > pos.x - fLengthX && pos1[0].x + fSizeX1 <= posold.x - fLengthX)
		{//�E
			pos.x = pos1[0].x + fSizeX1 + fLengthX;
		}
		else if (pos1[0].x - fSizeX1 < pos.x + fLengthX && pos1[0].x - fSizeX1 >= posold.x + fLengthX)
		{//��
			pos.x = pos1[0].x - fSizeX1 - fLengthX;
		}
	}


}
//=============================================================================
// �e�̓����蔻�菈��
//============================================================================
bool CCollision::BulletCollision(CScene *&pTarget, CScene::OBJTYPE& obj, CBullet *&pBullet)
{
	D3DXVECTOR3 *Targetpos;
	float		fSizeX = 0.0f;
	float		fSizeZ = 0.0f;
	D3DXVECTOR3 Bulletpos = pBullet->GetPosition()[0];
	int			nType = pBullet->GetType();
	int			nAtk = 1;

	switch (nType)
	{
	case 0: nAtk = 15; break;
	case 1: nAtk = (int)(500.0f * pBullet->GetfLife()); break;
	case 2: nAtk = 5; break;
	case 3: nAtk = 200; break;
	}

	float		fBulletX = 10.0f;
	float		fBulletZ = 10.0f;

	GetInfo(pTarget, obj, Targetpos, Targetpos, fSizeX, fSizeZ, true);

	if (Bulletpos.x + 80.0f > Targetpos[0].x && Bulletpos.x - 150.0f < Targetpos[0].x &&
		Bulletpos.y + 30.0f > Targetpos[0].y && Bulletpos.y - 30.0f < Targetpos[0].y)
	{//��������
		if (((CEnemy*)pTarget)->SetDamage(nAtk, nType)) { return true; }
		if (nType != 2 && nType != 0) { pBullet->Uninit(); }
	}

	return false;
}
//=============================================================================
//�����蔻��ɕK�v�ȗv�f���l��
//=============================================================================
bool CCollision::GetInfo(CScene *&pScene, CScene::OBJTYPE& obj, D3DXVECTOR3 *&pos, D3DXVECTOR3 *&posold, float& fLengthX, float& fLengthZ, bool bHit)
{
	CEnemy *pEnemy;
	CSceneBoss  *pBoss;
	CScenePlayer *pPlayer;
	CSceneModel *pModel;

	switch (obj)
	{
	case CScene::OBJTYPE_ENEMY:
		pEnemy = (CEnemy*)pScene;
		posold = pEnemy->GetPosition();
		pos = pEnemy->GetPosition();
		break;
	case CScene::OBJTYPE_BOSS:
		pBoss = (CSceneBoss*)pScene;
		posold = &pBoss->GetPosOld();
		pos = pBoss->GetPosition();
		fLengthX = pBoss->GetfLengthX()[0];
		fLengthZ = pBoss->GetfLengthZ()[0];
		break;
	case CScene::OBJTYPE_PLAYER:
		pPlayer = (CScenePlayer*)pScene;
		if (pPlayer->GetDrawType()[0] == CScene::DRAW_TYPE_NO) { return true; }
		posold = pPlayer->GetPositionOld();
		pos = pPlayer->GetPosition();
		if (bHit)
		{
			fLengthX = -0.2f;
			fLengthZ = -0.2f;
		}
		else
		{
			CSceneModel::GetLength(pPlayer->GetModel()[0], fLengthX, fLengthZ);
		}
		break;
	case CScene::OBJTYPE_OBJ:
		pModel = (CSceneModel*)pScene;
		pos = pModel->GetPosition();
		posold = pos;
		CSceneModel::GetLength(pModel->GetModel()[0], fLengthX, fLengthZ);
		break;
	}
	return false;
}
//=============================================================================
// �e�̓����蔻�菈��
//=============================================================================
void CCollision::DestroyRange(D3DXVECTOR3 pos, float fLengthX, float fLengthZ, CScene::OBJTYPE ObjType)
{
	CScene **PScene;;

	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		PScene = CScene::GetScene(nCount);
		if (PScene != NULL)
		{
			for (int nCntScene = 0; nCntScene < CScene::GetnMemoryAll(nCount); nCntScene++)
			{
				if (PScene[nCntScene] != NULL)
				{
					if (ObjType == PScene[nCntScene]->GetObjType())
					{
						D3DXVECTOR3 *Targetpos = NULL;
						switch (ObjType)
						{
							case CScene::OBJTYPE_ENEMY:
							case CScene::OBJTYPE_OBJ:
							case CScene::OBJTYPE_OBJ_NO:
								Targetpos = ((CSceneModel*)PScene[nCntScene])->GetPosition();
							break;
							case CScene::OBJTYPE_NUMBER:
								Targetpos = &((C3DNumber*)PScene[nCntScene])->GetPosition();
								break;
						}
						if (Targetpos != NULL)
						{
							if (Targetpos[0].x + fLengthX > pos.x && Targetpos[0].x - fLengthX < pos.x &&
								Targetpos[0].z + fLengthZ > pos.z && Targetpos[0].z - fLengthZ < pos.z)
							{//�͈͓��Ȃ�
								PScene[nCntScene]->Uninit();
							}
						}
						else
						{
							MessageBox(0, "�j���ݒ肳��ĂȂ���I", "", MB_OK);
						}
					}
				}
			}
		}
	}
}
