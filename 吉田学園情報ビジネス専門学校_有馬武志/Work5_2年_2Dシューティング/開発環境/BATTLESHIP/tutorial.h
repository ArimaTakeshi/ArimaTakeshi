//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
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
// ��{�N���X
//=====================
class CTutorial
{
public:
	CTutorial();							//�R���X�g���N�^
	~CTutorial();							//�f�X�g���N�^
	HRESULT Init();							//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
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

