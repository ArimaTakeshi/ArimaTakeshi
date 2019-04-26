//=============================================================================
//
// バレット処理 [bullet.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "bullet.h"
#include "motion.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//==================================================================================================//
//    * 弾の攻撃判定 確認関数 *
//==================================================================================================//
void CBullet::AtkCheck(void)
{
	CScene *pSceneAtk;
	CScene *pSceneDef;

	pSceneAtk = CScene::GetTop(BULLET_PRIORYITY);
	while (pSceneAtk != NULL)
	{//終わるまで
		if (pSceneAtk->GetObjType() == OBJTYPE_BULLET)
		{//キャラ発見
			CCharacter *pAtk = ((CBullet*)pSceneAtk)->m_pChar;
			pSceneDef = CScene::GetTop(CHAR_PRIORITY);
			while (pSceneDef != NULL)
			{//終わるまで
				if (pSceneAtk != pSceneDef)
				{//同じキャラ出ない
					if (pSceneDef->GetObjType() == OBJTYPE_PLAYER || pSceneDef->GetObjType() == OBJTYPE_ENEMY)
					{//キャラ発見
						//HitCheck(pSceneAtk, pSceneDef);	//お互いにヒットチェック
					}
				}
				pSceneDef = pSceneDef->GetpNext();
			}//判定
		}//if(キャラ)
		pSceneAtk = pSceneAtk->GetpNext();
	}//while(NULL)
}
//==================================================================================================//
//    * 弾のセット関数 *
//==================================================================================================//
void CBullet::Set(CCharacter *pChar, CScene *pScene, D3DXMATRIX *pMtx, int nLife, float fAtkplus, float fRange)
{
	m_pChar = pChar;
	m_pScene = pScene;
	m_pMtx = pMtx;
	m_nLife = nLife;
	m_fRange = fRange;
	m_fAtkplus = fAtkplus;
}
//=============================================================================
// 弾の初期化処理
//=============================================================================
HRESULT	CBullet::Init(void)
{
	m_pChar = NULL;
	m_pScene = NULL;
	m_pMtx = NULL;
	m_nLife = 0;
	m_fRange = 0.0f;
	m_fAtkplus = 0.0f;

	return S_OK;
}
//=============================================================================
// 弾の更新処理
//=============================================================================
void CBullet::Update(void)
{
	m_nLife--;
	if (m_nLife < 0) 
	{ 
		m_pScene->Uninit();
		Uninit();
	}
}

