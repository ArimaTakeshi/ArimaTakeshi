//=============================================================================
//
// ���C�g���� [light.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define MAX_LIGHT (3)
#define MAX_TYPE  (3)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CLight
{
public:
	CLight();
	~CLight();

	void Init(void);
	void Uninit(void);
	void Update(void); 
	void Set(int nNumber);
	void SetStrength(float fGoal, float fFrame, int nNumber);
	D3DLIGHT9 &Getlight(int nID)	{ return m_light[nID]; }
	D3DXCOLOR &GetCol(int nID)		{ return m_col[nID]; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	D3DLIGHT9	m_light[MAX_LIGHT];		//���C�g�̏��
	D3DXCOLOR	m_col[MAX_TYPE];					//���C�g�̐F
	float		m_fStrength[MAX_TYPE];			//���C�g�̋���
	float		m_fGoal[MAX_TYPE];				//�����̖ڕW
	float		m_fFrame[MAX_TYPE];				//�ڕW�������������܂ł̃t���[����
};

#endif
