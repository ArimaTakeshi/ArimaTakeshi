//=============================================================================
//
// 距離処理 [distance.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CBillNumber;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define DISTANCE_MAX	(3)		// タイマーの桁数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDistance : public CScene
{
public:
	CDistance(int nPriority = 6, OBJTYPE objType = OBJTYPE_DISTANCE);
	~CDistance();

	static CDistance *Create(D3DXVECTOR3 pos);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

private:
	CBillNumber		*m_apBillNumber[DISTANCE_MAX];	// ナンバーへのポインタ
	static int		m_nDistance;					// 時間
	int				m_nDistanceCount;				// 時間のカウンタ
	D3DXVECTOR3		m_pos;							// 位置	
	int				m_nBoxNumber;					//数字を入れるための箱
};

#endif