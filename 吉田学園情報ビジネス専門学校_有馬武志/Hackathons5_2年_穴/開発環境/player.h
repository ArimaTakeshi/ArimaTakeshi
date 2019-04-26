//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "Scene2D.h"
#include "motion.h"
class C2DGage;
class C2D;
class C2DPolygon;
class CNumber;
class CPlayer_UI;
class CSceneModel;
class CFont;
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define MAX_UIDeco		(2)
#define MAX_MotionUI	(15)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer : public CCharacter
{
public:
	typedef enum
	{
		MODE_START,
		MODE_HIDE,
		MODE_BREAK,
		MODE_FIGHT,
	}MODE;
	CPlayer(int nPrioryity = CHAR_PRIORITY) : CCharacter::CCharacter(nPrioryity) {};
	~CPlayer() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	Break(void);
	void	Answer(void);
	void	Dead(void);
	void	Over(void);
	void SetLightCol(D3DXCOLOR col);
	void SetLightStr(float fGoal, float fFrame);

	MODE    &GetMode(void) { return m_Mode; }
	int		&GetnID(void) { return m_nID; }
	int		&GetnBreak(void) { return m_nBreak; }
	bool	&GetbReset(void) { return m_bReset; }
	CPlayer_UI	*&GetpUI(void) { return m_pUI; }

private://*****************************************************************************
	void	LockUpdate(void);
	void	ChangeMotion(void);
	//�ϐ��錾//***********************************************************************
	static	int	m_nNumPlayer;	//�v���C���[�̑����J�E���g

	CPlayer_UI *m_pUI;
	int			m_nID;			//�v���C���[��ID
	CScene2D	*m_pLockOn;		//���b�N����UI
	float		m_fDistance;	//�J�����Ƃ̋���
	float		m_fBase;		//�����̊�b�l
	float		m_fRatio;		//�����̔{��
	bool		m_bReset;

	int		m_nCntState;
	int		m_nCntBreak;
	int		m_nBreak;
	int		m_nBreak2;
	D3DXVECTOR3 m_Finger;
	CSceneModel *m_pModel;
	MODE		m_Mode;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class Motion_UI
{
public:
	typedef enum
	{
		TYPE_GROUND,	//�n��
		TYPE_SKY,		//��
		TYPE_NO,		//����
		TYPE_MAX,
	}TYPE;
	Motion_UI() {};
	~Motion_UI() {};

	void	Set(CPlayer *pPlayer, D3DXVECTOR3 pos, int nID, int nUV, TYPE type);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	TYPE		m_Type;			//�Q�Ƃ̎��
	D3DXVECTOR3	m_pos;			//���g�̏ꏊ
	int			m_nID;			//�Q�Ƃ��郂�[�V�����ԍ�
	CPlayer		*m_pPlayer;		//�v���C���[�̃|�C���^
	C2DPolygon	*m_p2D;			//2D�|���S��
	C2DGage		*m_pGage;		//�Q�[�W	�c�Q�[�W
	CNumber		*m_pNumber;		//����		�b��


};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CPlayer_UI : public CScene
{
public:
	typedef enum
	{
		LOCK_CANCEL,
		LOCK_NO,
		LOCK_START,
		LOCK_ON,
		LOCK_MAX,
	}LOCK;
	CPlayer_UI(int nPrioryity = S2D_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CPlayer_UI() {};

	void	Set(CPlayer *pPlayer);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void	SetLockOn(LOCK lock, D3DXVECTOR3 *pos);

	CSceneEffect *&GetpLockOn(void) { return m_pLockOn; }
private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	CPlayer			*m_pPlayer;					//�v���C���[�̃|�C���^
	C2D				*m_p2DHelp;					//�w���v
	C2D				*m_p2DDeco[MAX_UIDeco];		//�Q�[�W�̑���
	C2DGage			*m_pLife;					//HP
	C2DGage			*m_pSP;						//MP
	C2DGage			*m_pStamina;				//�X�^�~�i
	CSceneModel		*m_pModel;					//���ʎ��j���f��(�{��)
	CSceneModel		*m_pNeedle;					//���ʎ��j���f��(�j)
	CSceneEffect	*m_pLockOn;					//���b�N�I��UI
	Motion_UI		*m_pMotion_UI;				//���[�V����UI
	CFont			*m_pFont;					//�w���v�p�̕���
	bool			m_bHelp;

	CFont		*m_pSelect[4];
	C2D			*m_p2DSelect;					//�w���v

	CNumber		*m_pTime;						//����
};
#endif
