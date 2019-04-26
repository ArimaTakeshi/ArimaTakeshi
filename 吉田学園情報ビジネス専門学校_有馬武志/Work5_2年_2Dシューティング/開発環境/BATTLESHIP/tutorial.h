//=============================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CBullet;
class CExplosion;
class CBg;
class CEnemy;
class CGan;
class CNumber;
class C2DObject;
class CFram;
class CString;
class CLife;

//=====================
// 基本クラス
//=====================
class CTutorial
{
public:
	CTutorial();							//コンストラクタ
	~CTutorial();							//デストラクタ
	HRESULT Init();							//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理
	static CPlayer *&GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CGan *GetGan(void) { return m_pGan; }

private:
	static CBullet		*m_pBullet;
	static CPlayer		*m_pPlayer;
	static CFram		*m_pFram;
	static CBg			*m_pBg;
	static CExplosion	*m_pExplosion;
	static C2DObject	*m_p2DObject;
	static CEnemy		*m_pEnemy;
	static CGan			*m_pGan;
	static CNumber		*m_pNumber;
	int					m_EnemyCnt;
	//static CString *m_pString;
};
#endif

