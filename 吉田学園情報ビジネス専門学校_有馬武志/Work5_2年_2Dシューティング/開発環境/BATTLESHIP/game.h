//=============================================================================
//
// �Q�[���̏��� [game.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

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
class CPause;
class CString;
class CLife;

//=====================
// ��{�N���X
//=====================
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,					//�������Ă��Ȃ����
		GAMESTATE_NORMAL,					//�ʏ���
		GAMESTATE_CLEAR,					//�N���A
		GAMESTATE_OVER,						//�Q�[���I�[�o�[
		GAMESTATE_END,						//�Q�[���I��
		GAMESTATE_MAX						//�ő吔
	}GAMESTATE;

	CGame();								//�R���X�g���N�^
	~CGame();								//�f�X�g���N�^
	HRESULT Init();							//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	static void SetGameState(GAMESTATE state) { m_gameState = state; }
	static GAMESTATE GetGameState(void) { return m_gameState; }
	static CPlayer *&GetPlayer(void) { return m_pPlayer; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CGan *GetGan(void) { return m_pGan; }
	static void SetPause(bool bPause);
	static bool GetPause(void) { return m_bPause; }

private:
	static GAMESTATE m_gameState;					//�Q�[�����
	GAMESTATE m_NowGameState;
	int m_nCounterGameState;						//��ԃJ�E���^
	static CBullet *m_pBullet;
	static CPlayer *m_pPlayer;
	static CFram *m_pFram;
	static CBg *m_pBg;
	static CExplosion *m_pExplosion;
	static C2DObject *m_p2DObject;
	static CEnemy *m_pEnemy;
	static CGan *m_pGan;
	static CNumber *m_pNumber;
	static CPause *m_pPause;
	static bool m_bPause;
	//static CString *m_pString;
};
#endif

