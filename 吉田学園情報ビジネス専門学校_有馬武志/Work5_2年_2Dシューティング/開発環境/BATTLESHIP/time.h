//=============================================================================
//
// �^�C������ [time.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMBER (3)			//����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//=====================
//  CScene�̔h���N���X
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
	static CNumber *m_apNumber[MAX_NUMBER];  //�X�R�A�̌���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	static int m_nTime;

};
#endif





