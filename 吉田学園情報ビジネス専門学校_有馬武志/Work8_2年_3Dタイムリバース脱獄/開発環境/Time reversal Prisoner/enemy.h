//=============================================================================
//
// �G�l�~�[���� [enemy.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"
#include "billboord.h"
#include "shadow.h"
#include "dummyenemy.h"
#include "blood.h"
#include "spotlight.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\stok2.txt"	//�ǂݍ���txt�t�@�C���̖��O
#define MAX_ENEMYANIM			(8)						//�A�j���[�V������
#define MAX_ENEMYKEY			(8)						//�L�[�t���[����
#define MAX_PARTS				(30)					//�p�[�c�̍ő吔
#define MAX_MOTION				(10)					//���[�V�����̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  CScene�̔h���N���X
//=====================
class CEnemy : public CScene
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
		ENEMYANIM_NEUTRAL = 0,		//�j���[�g�������[�V����
		ENEMYANIM_MOVE,				//�ړ����[�V����
		ENEMYANIM_JUMP,				//�W�����v���[�V����
		ENEMYANIM_ATTACK,			//�ߋ����U�����[�V����
		ENEMYANIM_HOLDAGAN,			//�e���\���郂�[�V����
		ENEMYANIM_SHOT,				//�e�������[�V����
		ENEMYANIM_HOLDAGANWALK,		//�\���ĕ������[�V����
		ENEMYANIM_TAKEGAN,			//�e�����܂����[�V����
		ENEMYANIM_LOOKAROUND,		//��������n�����[�V����
		ENEMY_MAX					//���[�V�����̍ő吔
	}PlayerAnim;

	typedef enum
	{
		MOVE_NONE = 0,				//�����Ȃ����
		MOVE_STOP,					//�~�܂��Ă�����
		MOVE_X_R,					//���ɓ����Ă�����(�ŏ��Ɂ�)
		MOVE_Z_G,					//�c�ɓ����Ă�����(�ŏ��Ɂ�)
		MOVE_X_L,					//�c�ɓ����Ă�����(�ŏ��Ɂ�)
		MOVE_Z_B,					//�c�ɓ����Ă�����(�ŏ��Ɂ�)
		MOVE_RAND,					//�����_���ɓ����Ă�����
		MOVE_MAX,					//�����̍ő�
	}MoveList;

	CEnemy(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_ENEMY);
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void CollisitionMesh(void);
	void CollisitionWall(void);
	void CollisitionGround(void);
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CEnemy *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nPattern, MoveList movelist);
	void CollisitionItem(void);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }
	void DeleteEnemy(void);
	void SetPattern(int nPattern) { m_nPattern = nPattern; }
	void SetLightIn(bool bLightIn) { m_bLightIn = bLightIn; }

	//���[�V�����̍X�V�֐�
	void UpdateMotion(void);

	//�t�@�C���ǂݍ��݊֐�
	void FileLoad(void);							//�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);		//1�s�ǂݍ���
	char *GetLineTop(char *pStr);					//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);		//�s�̍Ō��؂�̂�

private://�l�ł̂ݎg��
	static LPD3DXMESH	m_pMesh[MAX_PARTS];			//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER	m_pBuffMat[MAX_PARTS];		//�}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMat[MAX_PARTS];		//�}�e���A���̏��
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	D3DXVECTOR3			m_posPast;					//�ߋ��̈ʒu
	D3DXVECTOR3			m_rotPast;					//�ߋ��̌���
	D3DXVECTOR3			m_rotDest;					//����
	D3DXVECTOR3			m_posOld;					//�ߋ��̈ʒu
	D3DXVECTOR3			m_move;						//����
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	CModel				*m_apModel[MAX_PARTS];		//���f���ւ̃|�C���^
	PlayerAnim			m_nAnimnow;					//���݂̃A�j���[�V����
	MoveList			m_MoveList;					//�ړ����@
	D3DXVECTOR3			m_vtxMin;					//���f���̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���f���̍ő�l
	bool				m_bJump;					//�W�����v���
	bool				m_bLand;					//���n���
	bool				m_bInvincible;				//�f�o�b�O�p
	bool				m_bAttack;					//�U�����
	int					m_nAttackDelay;				//�U���̍d������
	int					m_nAttackCount;				//�U���܂ł̎���
	bool				m_bResult;
	bool				m_bInLength;				//����������̋���
	bool				m_bDiscovery;				//�����������
	int					m_nCntLook;					//���n������
	int					m_nCntTime;					//��������̏�Ԃ��o������
	bool				m_bReturn;					//�߂��Ƃ���1�񂾂��͂��邽�߂�
	bool				m_bTarget;					//�ǂ���������Ƀj���[�g�����ɂȂ�Ȃ��悤��
	int					m_nWaitTime;				//�ǂ�������܂ł̑ҋ@����
	PlayerAnim			m_nAnimnowPast;				//�ߋ��̃A�j���[�V����
	MoveList			m_MoveListPast;				//�ߋ��̈ړ����@
	bool				m_bInLengthPast;			//�ߋ��̍��G
	bool				m_bTitle;					//�^�C�g���ł̐���
	int					m_nCntLookPast;				//�ߋ��Ɍ������
	bool				m_bAttackPast;				//�ߋ��̍U�����
	int					m_nCntTimePast;				//�����̏�Ԏ��Ԃ̕\��
	bool				m_bReturnPast;				//�ߋ��ɖ߂�
	int					m_nPatternPast;				//�ߋ��̍s���p�^�[��
	int					m_nPattern;					//�s���p�^�[��
	bool				m_bLightIn;					//���C�g�ɓ���������
	bool				m_bLightInPast;				//�ߋ��Ƀ��C�g�ɓ���������
	int					m_nCountMoveXPast;			//�ߋ���X�����Ɉړ���
	int					m_nCountMoveZPast;			//�ߋ���Z�����Ɉړ���
	bool				m_bMoveTypePast;			//�ߋ��̈ړ��̕��@
	int					m_nCountMoveX;				//X�����Ɉړ���
	int					m_nCountMoveZ;				//Z�����Ɉړ���
	bool				m_bMoveType;				//�ړ��̕��@
	bool				m_bStartMotion;				//�ŏ��̃��[�V����

	//���[�V�����֐�
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];	//�L�[���ւ̃|�C���^
	int					m_nKey;						//���݂̃L�[�i���o�[
	int					m_nCountFlame;				//�t���[����
	int					m_nNumParts;				//�p�[�c��
	int					m_aIndexParent[MAX_PARTS];	//�e�̃C���f�b�N�X
	KEY					m_aKayOffset[MAX_PARTS];	//�I�t�Z�b�g���
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];	//���[�V�������
	int					m_nMotionType;				//���[�V�����̃^�C�v(int�^)
	bool				m_bMotionEnd;				//���[�V�����I��
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];		//�p�[�c���Ƃ̏����ʒu
	static CMeshOrbit   *m_MeshOrbit;				//�O�Ղ̃|�C���^
	CBillBoord			*m_pBillboord;				//�r���{�[�h�̃|�C���^
	CShadow				*m_pShadow;					//�e�̃|�C���^
	CSpotLight			*m_pSpotLight;				//�X�|�b�g���C�g�̃|�C���^
	CDummyEnemy			*m_pDummyEnemy;				//�ڈ�̓G�|�C���^
};
#endif