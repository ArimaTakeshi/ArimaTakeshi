//=============================================================================
//
// ポリゴン処理 [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"SceneModel.h"
#include "SceneAnim3D.h"
#include "3DNumber.h"
#include "collision.h"
#include "mesh.h"

#include "camera.h"
#include "Game.h"
#include "manager.h"
#include"Renderer.h"

//=============================================================================
// 当たり判定処理
//=============================================================================
void CCollision::CollisionAll(void)
{
	CCharacter::AtkCollision();
}
//=============================================================================
//オブジェクトのあたり判定	全部回転
//=============================================================================
void CCollision::ObjectCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float fLengthX, float fLengthZ, int nID)
{
	//CScene **PSceneTarget = NULL;

	//PSceneTarget = CScene::GetScene(1);
	//for (int nCntTarget = 0; nCntTarget < CScene::GetnMemoryAll(1); nCntTarget++)
	//{
	//	if (PSceneTarget[nCntTarget] != NULL && nID != nCntTarget)
	//	{
	//		if (PSceneTarget[nCntTarget]->GetObjType() >= CScene::OBJTYPE_PLAYER && PSceneTarget[nCntTarget]->GetObjType() <= CScene::OBJTYPE_OBJ)
	//		{//モデルなら
	//			ObjectCollision(pos, posold, fLengthX, fLengthZ, PSceneTarget[nCntTarget]);
	//		}
	//	}//if(NULL)
	//}//for()

}

//=============================================================================
//あたり判定に必要な要素を獲得
//=============================================================================
bool CCollision::GetInfo(CScene *&pScene, CScene::OBJTYPE& obj, D3DXVECTOR3 *&pos, D3DXVECTOR3 *&posold, D3DXVECTOR3 &length, bool bHit)
{
	CSceneModel *pModel;

	switch (obj)
	{
	case CScene::OBJTYPE_ENEMY:
		//pEnemy = (CSceneEnemy*)pScene;
		//posold = pEnemy->GetPositionOld();
		//pos = pEnemy->GetPosition();
		//CSceneModel::GetLength(pEnemy->GetModel()[0], fLengthX, fLengthZ);
		break;
	case CScene::OBJTYPE_BOSS:
		//pBoss = (CSceneBoss*)pScene;
		//posold = &pBoss->GetPosOld();
		//pos = pBoss->GetPosition();
		//fLengthX = pBoss->GetfLengthX()[0];
		//fLengthZ = pBoss->GetfLengthZ()[0];
		break;
	case CScene::OBJTYPE_PLAYER:
		//pPlayer = (CScenePlayer*)pScene;
		//if (pPlayer->GetDrawType()[0] == CScene::DRAW_TYPE_NO) { return true; }
		//posold = pPlayer->GetPositionOld();
		//pos = pPlayer->GetPosition();
		//if (bHit)
		//{
		//	fLengthX = -0.2f;
		//	fLengthZ = -0.2f;
		//}
		//else
		//{
		//	CSceneModel::GetLength(pPlayer->GetModel()[0], fLengthX, fLengthZ);
		//}
		break;
	case CScene::OBJTYPE_OBJ:
		pModel = (CSceneModel*)pScene;
		pos = &pModel->GetPosition();
		posold = pos;
		CSceneModel::GetLength(pModel->GetModel(), length);
		break;
	}
	return false;
}
//=============================================================================
// 弾の当たり判定処理
//=============================================================================
void CCollision::DestroyRange(D3DXVECTOR3 pos, float fLengthX, float fLengthZ, CScene::OBJTYPE ObjType)
{
	CScene *pScene;
	CScene *pTarget;

	for (int nCount = 0; nCount < MAX_SCENE; nCount++)
	{
		pScene = CScene::GetTop(nCount);
		while (pScene != NULL)
		{
			pTarget = pScene;
			pScene = pScene->GetpNext();

			if (ObjType == pTarget->GetObjType())
			{
				D3DXVECTOR3 *Targetpos = NULL;
				switch (ObjType)
				{
				case CScene::OBJTYPE_ENEMY:
				case CScene::OBJTYPE_OBJ:
				case CScene::OBJTYPE_OBJ_NO:
					Targetpos = &((CSceneModel*)pTarget)->GetPosition();
					break;
				case CScene::OBJTYPE_NUMBER:
					Targetpos = &((C3DNumber*)pTarget)->GetPosition();
					break;
				}
				if (Targetpos != NULL)
				{
					if (Targetpos[0].x + fLengthX > pos.x && Targetpos[0].x - fLengthX < pos.x &&
						Targetpos[0].z + fLengthZ > pos.z && Targetpos[0].z - fLengthZ < pos.z)
					{//範囲内なら
						pTarget->Uninit();
					}
				}
				else
				{
					MessageBox(0, "破棄設定されてないよ！", "", MB_OK);
				}
			}
		}
	}
}
