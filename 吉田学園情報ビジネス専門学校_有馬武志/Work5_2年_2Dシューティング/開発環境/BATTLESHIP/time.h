//=============================================================================
//
// タイム処理 [time.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_NUMBER (3)			//桁数

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//=====================
//  CSceneの派生クラス
//=====================
class CTime : CScene
{
public:
	CTime();						
	~CTime();								
	HRESULT Init(void);							
	void Uninit(void);							
	void Update(void);						
	void Draw(void);					
	int GetTime(void);
	static CTime *Create(void);
	static void AddTime(int nValue);

private:
	static CNumber *m_apNumber[MAX_NUMBER];  //スコアの桁数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	static int m_nTime;

};
#endif





