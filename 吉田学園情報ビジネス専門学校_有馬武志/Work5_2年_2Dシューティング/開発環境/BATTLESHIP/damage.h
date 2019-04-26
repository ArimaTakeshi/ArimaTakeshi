//=============================================================================
//
// �^�C������ [damage.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _DAMAGE_H_
#define _DAMAGE_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_DAMAGE_NUMBER (2)			//����

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//=====================
//  CScene�̔h���N���X
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
	static CNumber *m_apNumber[MAX_DAMAGE_NUMBER];  //�X�R�A�̌���
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	static int m_nDamage;
	int m_nCount;
	float m_fLife;
};
#endif