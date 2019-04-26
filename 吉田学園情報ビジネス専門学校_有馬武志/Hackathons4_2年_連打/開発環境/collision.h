#pragma once
//=============================================================================
//
// �����蔻�菈�� [collision.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

class CBullet;
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCollision
{
public:
	CCollision() {};
	~CCollision() {};

	static void	CollisionAll(void);		//�S�Ă̂����蔻��
	static void ObjectCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float fLengthX, float fLengthZ, int nID);

	//�͈͓��̃��f���j��
	static void DestroyRange(D3DXVECTOR3 pos, float fLengthX, float fLengthZ, CScene::OBJTYPE ObjType);

private://*****************************************************************************
	static void ObjectCollision(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLengthX, float& fLengthZ, CScene *&pScene1);
	static bool BulletCollision(CScene *&pTarget, CScene::OBJTYPE& obj, CBullet *&pBullet);					//�e�̂����蔻��
	static bool CCollision::GetInfo(CScene *&pScene, CScene::OBJTYPE& obj, D3DXVECTOR3 *&pos, D3DXVECTOR3 *&posold, float& fLengthX, float& fLengthZ, bool bHit); //�����蔻��ɕK�v�ȗv�f���l��
		//�ϐ��錾//***********************************************************************
};
////==================================================================================================//
////    * �e���v���[�g��` *
////==================================================================================================//
//template<class T> bool Search(CScene **&PScene,int& nCntScene,T *&pScene, CScene::OBJTYPE obj)
//{
//	for (nCntScene = nNumber; nCntScene < CScene::GetnMemoryAll(); nCntScene++)
//	{
//		if (PScene[nCntScene] != NULL)
//		{
//			if (obj == PScene[nCntScene]->GetObjType())
//			{
//				T *pScene = (T*)PScene[nCntScene];
//				return false;
//			}//if(ENEMY)
//		}//if(!=NULL)
//	}//for()
//
//	return true;
//}
#endif
