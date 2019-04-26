#pragma once
//=============================================================================
//
// エネミー処理 [SceneEnemy.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEENEMY_H_
#define _SCENEENEMY_H_

#include "SceneModel.h"
#include "ScenePlayer.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSceneEnemy : public CSceneTank
{
public:
	CSceneEnemy(int nPrioryity = MODEL_PRIORITY) : CSceneTank::CSceneTank(nPrioryity) {};
	~CSceneEnemy() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL modelD, MODEL modelU, CSceneModel::TEXTURE TypeD, CSceneModel::TEXTURE TypeU, CScene::DRAW_TYPE DrawType);
	HRESULT	Init(void) { CSceneTank::Init(); CScene::SetObjType(OBJTYPE_ENEMY); m_nRank = 0;  return S_OK; };
	void	Update(void);
	void	SetDanger(float &fDistance, float fBulletRot, float fRotY, int &nID);
	float	&GetfDistance(void) { return m_fDistance; };
	int		GetExp(void) { return 100 + (CScenePlayer::GetnStage() - 1) * 50 + m_nRank * 50; }
private://*****************************************************************************
		//変数宣言//***********************************************************************
	float	m_fDistance;	//弾との距離
	float	m_fRot;			//弾から離れる向き
	float	m_fBack;		//弾の角度
	float	m_fShotWait;	//発射後待ち時間
	int		m_nRank;		//敵のランク
	int		m_nCntFrame;	//弾から離れるF数
	int		m_nNearBullet;	//近くの弾数
	int		m_nBulletID;	//弾のID
	bool	m_bFound;		//プレイヤーを発見済みか
};

#endif
