//=============================================================================
//
// タイム処理 [damage.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _DAMAGE_H_
#define _DAMAGE_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_DAMAGE_NUMBER (2)			//桁数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//=====================
//  CSceneの派生クラス
//=====================
class CDamage : CScene
{
public:
	CDamage();
	~CDamage();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetDamage(void);
	static CDamage *Create(void);
	static void AddDamage(int nValue);

private:
	static CNumber *m_apNumber[MAX_DAMAGE_NUMBER];  //スコアの桁数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	static int m_nDamage;
	int m_nCount;
	float m_fLife;
};
#endif