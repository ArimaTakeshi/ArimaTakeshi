#pragma once
//=============================================================================
//
// 当たり判定処理 [collision.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

class CMesh;
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CCollision
{
public:
	CCollision() {};
	~CCollision() {};

	static void	CollisionAll(void);		//全てのあたり判定
	static void ObjectCollisionAll(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float fLengthX, float fLengthZ, int nID);

	//範囲内のモデル破壊
	static void DestroyRange(D3DXVECTOR3 pos, float fLengthX, float fLengthZ, CScene::OBJTYPE ObjType);

private://*****************************************************************************
	static void ObjectCollision(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLengthX, float& fLengthZ, CScene *&pScene1);
	//static bool BulletCollision(CScene *&pTarget, CScene::OBJTYPE& obj, CSceneBullet *&pBullet);					//弾のあたり判定
	static bool CCollision::GetInfo(CScene *&pScene, CScene::OBJTYPE& obj, D3DXVECTOR3 *&pos, D3DXVECTOR3 *&posold, D3DXVECTOR3 &length, bool bHit); //あたり判定に必要な要素を獲得

//変数宣言//***********************************************************************
};

#endif
