//=============================================================================
//
// �������� [distance.h]
// Author : �L�n�@���u
//
//=============================================================================
#ifndef _DISTANCE_H_
#define _DISTANCE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CBillNumber;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DISTANCE_MAX	(3)		// �^�C�}�[�̌���

//*****************************************************************************
// �N���X��`
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
	CBillNumber		*m_apBillNumber[DISTANCE_MAX];	// �i���o�[�ւ̃|�C���^
	static int		m_nDistance;					// ����
	int				m_nDistanceCount;				// ���Ԃ̃J�E���^
	D3DXVECTOR3		m_pos;							// �ʒu	
	int				m_nBoxNumber;					//���������邽�߂̔�
};

#endif