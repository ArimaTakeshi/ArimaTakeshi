//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"
#include "dummyplayer.h"
#include "blood.h"
#include "serect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME_PRISONER		"data\\TEXT\\Prisoner1.txt"	//�ǂݍ���txt�t�@�C���̖��O
#define MAX_PLAYERANIM			(8)							//�A�j���[�V������
#define MAX_PLAYERKEY			(8)							//�L�[�t���[����
#define MAX_PARTS				(30)						//�p�[�c�̍ő吔
#define MAX_MOTION				(10)						//���[�V�����̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  CScene�̔h���N���X
//=====================
class CPlayer : public CScene
{
public://�N�ł�������

	//�L�[�v�f
	typedef struct
	{
		float fposX;
		float fposY;
		float fposZ;
		float frotX;
		float frotY;
		float frotZ;
	}KEY;

	//�L�[���
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//���[�V�������
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKayInfo[MAX_MOTION];
	}MOTION_INFO;

	//���[�V�������
	typedef enum
	{
		PLAYERANIM_NEUTRAL = 0,		//�j���[�g�������[�V����
		PLAYERANIM_WALK,			//����
		PLAYERANIM_RUN,				//����
		PLAYERANIM_SIT,				//����
		PLAYERANIM_TIRED,			//����
		PLAYERANIM_SQUAT,			//���Ⴊ��
		PLAYERANIM_SNEAK,			//���Ⴊ�ݕ���
		PLAYERANIM_DIE,				//�|���
		PLALYER_MAX					//���[�V�����̍ő吔
	}PlayerAnim;

	CPlayer(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_PLAYER);
	~CPlayer();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	static void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void CollisitionMesh(void);
	void CollisitionWall(void);
	void CollisitionGround(void);
	void CollisitionSpotLight(void);
	void CollisitionBullet(void);
	void CollisitionItem(void);
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CPlayer *Create(D3DXVECTOR3 pos);
	PlayerAnim GetAnim(void) { return m_nAnimnow; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

	//�����p�̊֐�
	static bool GetFuture(void) { return m_bFuture; }
	static void SetFuture(bool bFuture) { m_bFuture = bFuture; }
	static bool GetFutureCancel(void) { return m_bFutureCancel; }
	static void SetFutureCancel(bool bFutureCancel) { m_bFutureCancel = bFutureCancel; }
	static bool GetCancelHeal(void) { return m_bCancelHeal; }
	static void SetCancelHeal(bool bCancelHeal) { m_bCancelHeal = bCancelHeal; }
	static bool GetActionFade(void) { return m_bActionFade; }
	static void SetActionFade(bool bActionFade) { m_bActionFade = bActionFade; }
	static bool GetCancelStageNext(void) { return m_bStageNext; }
	static void SetCancelStageNext(bool bCancelStageNext) { m_bStageNext = bCancelStageNext; }

	//�����̓G�p�֐�
	static bool GetEnemyFuture(void) { return m_bEnemyFuture; }
	static void SetEnemyFuture(bool bEnemyFuture) { m_bEnemyFuture = bEnemyFuture; }
	static bool GetEnemyFutureSukill(void) { return m_bEnemyFutureSukill; }
	static void SetEnemyFutureSukill(bool bEnemyFutureSukill) { m_bEnemyFutureSukill = bEnemyFutureSukill; }

	//�����̗̑͗p�֐�
	static bool GetLifeFuture(void) { return m_bLifeFuture; }
	static void SetLifeFuture(bool bLifeFture) { m_bLifeFuture = bLifeFture; }
	static bool GetLifeFutureSukill(void) { return m_bLifeFutureSukill; }
	static void SetLifeFutureSukill(bool bLifeFtureSukill) { m_bLifeFutureSukill = bLifeFtureSukill; }

	//���񂾂Ƃ�
	static bool GetDie(void) { return m_bDie; }
	static void SetDie(bool bDie) { m_bDie = bDie; }
	static bool GetOverResult(void) { return m_bOverResult; }
	static void SetOverResult(bool bOverResult) { m_bOverResult = bOverResult; }

	//�v���C���[�̍폜
	void ResetPlayer(void);

	//���[�V�����̍X�V�֐�
	void UpdateMotion(void);

	//�t�@�C���ǂݍ��݊֐�
	void FileLoad(void);								//�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);			//1�s�ǂݍ���
	char *GetLineTop(char *pStr);						//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);			//�s�̍Ō��؂�̂�

private://�l�ł̂ݎg��
	static LPD3DXMESH	m_pMesh[MAX_PARTS];				//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER	m_pBuffMat[MAX_PARTS];			//�}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMat[MAX_PARTS];			//�}�e���A���̏��
	static D3DXVECTOR3	m_pos;							//�ʒu
	static D3DXVECTOR3	m_move;							//����
	static D3DXVECTOR3	m_rot;							//����
	D3DXVECTOR3			m_rotDest;						//�ߋ��̌���
	D3DXVECTOR3			m_posOld;						//�ߋ��̈ʒu
	D3DXVECTOR3			m_posFuture;					//�����̈ʒu
	D3DXVECTOR3			m_rotFuture;					//�����̌���
	D3DXMATRIX			m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel				*m_apModel[MAX_PARTS];			//���f���ւ̃|�C���^
	PlayerAnim			m_nAnimnow;						//���݂̃A�j���[�V����
	D3DXVECTOR3			m_vtxMin;						//���f���̍ŏ��l
	D3DXVECTOR3			m_vtxMax;						//���f���̍ő�l
	bool				m_bJump;						//�W�����v���
	bool				m_bLand;						//���n���
	bool				m_bInvincible;					//�f�o�b�O�p
	bool				m_bAttack;						//�U�����
	int					m_nAttackDelay;					//�U���̍d������
	bool				m_bResult;						//���U���g��ʂ̏��
	float				m_fSpeedMove;					//�����܂��͑��鑬�x
	bool				m_fStageNext;					//�}�b�v�ړ�
	static bool			m_bFuture;						//�����ɍs���Ă���
	int					m_nFutureStandTime;				//��������߂������̓����Ȃ�����
	static bool			m_bFutureCancel;				//�����̃L�����Z��
	static bool			m_bCancelHeal;					//�L�����Z����̉�
	int					m_nStandTime;					//�������L�����Z�������ۂ̓����Ȃ�����
	static bool			m_bActionFade;					//�A�N�V�����t�F�[�h���N��
	static bool			m_bEnemyFuture;					//�G�̖����̊J�n
	static bool			m_bEnemyFutureSukill;			//�G�̖������ɃX�L���L�����Z��
	static bool			m_bLifeFuture;					//������HP
	static bool			m_bLifeFutureSukill;			//HP�̖������ɃX�L���L�����Z��
	bool				m_bTrapSukill;					//�X�L���g�p���̃g���b�v�̏��
	static bool			m_bDie;							//���S
	static bool			m_bDieSukill;					//���S�X�L���ɂ�镜��
	static bool			m_bStageNext;					//�X�e�[�W������ւ���
	bool				m_bSukillActivate;				//�X�L������
	int					m_nDieTimer;					//���񂾌�̎���
	int					m_nDieSukillTimer;				//�X�L�����Ɏ��񂾌�̎���
	bool				m_bSukillDie;					//�X�L�����Ɏ��񂾌�̎����I
	static bool			m_bOverResult;					//���񂾌�ɏo�����U���g
	bool				m_bStageReset;					//�X�e�[�W�����Z�b�g�����Ƃ�

	// ���[�V�����֐�	�V�K
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];		//�L�[���ւ̃|�C���^
	int					m_nKey;							//���݂̃L�[�i���o�[
	int					m_nCountFlame;					//�t���[����
	int					m_nNumParts;					//�p�[�c��
	int					m_aIndexParent[MAX_PARTS];		//�e�̃C���f�b�N�X
	KEY					m_aKayOffset[MAX_PARTS];		//�I�t�Z�b�g���
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];		//���[�V�������
	int					m_nMotionType;					//���[�V�����̃^�C�v(int�^)
	bool				m_bMotionEnd;					//���[�V�����I��
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];			//�p�[�c���Ƃ̍ŏ��̈ʒu

	static CMeshOrbit   *m_MeshOrbit;					//�O�Ղ̃|�C���^
	static CSerect		*m_pSerect;						// �Z���N�g�̃|�C���^
	CDummyPlayer		*m_pDummyPlayer;				//�ڈ�̃v���C���[
	CBlood				*m_pBlood;						//���̃|�C���^
	bool				m_bGaugeOnOff;					//�Q�[�W�̃I���I�t�̏��
};
#endif