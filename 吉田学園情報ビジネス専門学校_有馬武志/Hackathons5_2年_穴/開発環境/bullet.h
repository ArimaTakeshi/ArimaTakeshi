//=============================================================================
//
// メッシュ処理 [mesh.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene.h"
#include "Scene3D.h"
class	CCharacter;
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define BULLET_PRIORYITY (1)
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CBullet : public CScene
{
public:
	CBullet(int nPrioryity = BULLET_PRIORYITY) : CScene::CScene(nPrioryity) {};
	~CBullet() {};

	static  void AtkCheck(void);
	void	Set(CCharacter *pChar, CScene *pScene, D3DXMATRIX *pMtx, int nLife, float fAtkplus, float fRange);
	HRESULT	Init(void);
	void	Update(void);

private://*****************************************************************************
	//変数宣言//***********************************************************************
	CCharacter	*m_pChar;		//撃ったキャラ
	CScene		*m_pScene;		//見た目の本体
	D3DXMATRIX	*m_pMtx;	//ワールドマトリックス
	int			m_nLife;		//生命値
	float		m_fAtkplus;		//倍率
	float		m_fRange;		//範囲
};

#endif