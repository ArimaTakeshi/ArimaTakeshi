//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CEnemy : public CCharacter
{
public:
	typedef enum
	{
		TYPE_NONE,
		TYPE_TITLE,
		TYPE_MAX
	}TYPE;
	CEnemy(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CEnemy() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, TYPE Etype, int nLevel);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	void	Dead(void);
	void	Over(void);
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	TYPE m_Type;
	bool bFight;
	bool bAlarm;
};

#endif
