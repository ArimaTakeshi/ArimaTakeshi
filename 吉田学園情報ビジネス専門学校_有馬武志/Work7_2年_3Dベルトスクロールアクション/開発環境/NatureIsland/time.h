//=============================================================================
//
// タイマー処理 [time.h]
// Author : keisuke komatsu
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene.h"

class CNumber;
//=============================================================================
//	マクロ定義
//=============================================================================
#define TIME_MAX	(3)		// タイマーの桁数

//=============================================================================
// クラス定義
//=============================================================================
class CTime : public CScene
{
public:
	CTime(int nPriority = 6, OBJTYPE objType = OBJTYPE_TIME);
	~CTime();

	static CTime *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static int GetTime(void) { return m_nTime; };
	static void MinusTime(int nTime);

private:
	CNumber *m_apNumber[TIME_MAX];	// ナンバーへのポインタ
	static int m_nTime;				// 時間
	int m_nTimeCount;				// 時間のカウンタ
	D3DXVECTOR3 m_pos;				// 位置	
};

#endif