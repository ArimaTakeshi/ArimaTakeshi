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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\player.txt"	//�ǂݍ���txt�t�@�C���̖��O
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
		ENEMYANIM_MOVE,				//�ړ�
		ENEMYANIM_JUMP,				//�W�����v
		ENEMYANIM_ATTACK,			//�ߋ����U��
		ENEMYANIM_HOLDAGAN,			//�e���\����
		ENEMYANIM_SHOT,				//�e������
		ENEMYANIM_BANZAI,			//�o���U�C
		ENEMYANIM_BAKUTEN,			//�o�N�e��
		ENEMY_MAX					//���[�V�����̍ő吔
	}PlayerAnim;

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
	static CEnemy *Create(D3DXVECTOR3 pos);
	void CollisitionItem(void);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

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
	static D3DXVECTOR3	m_pos;						//�ʒu
	static D3DXVECTOR3	m_rot;						//����
	D3DXVECTOR3			m_posOld;					//�ߋ��̈ʒu
	D3DXVECTOR3			m_move;						//����
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	CModel				*m_apModel[MAX_PARTS];		//���f���ւ̃|�C���^
	PlayerAnim			m_nAnimnow;					//���݂̃A�j���[�V����
	D3DXVECTOR3			m_vtxMin;					//���f���̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���f���̍ő�l
	bool				m_bJump;					//�W�����v���
	bool				m_bLand;					//���n���
	bool				m_bInvincible;				//�f�o�b�O�p
	bool				m_bAttack;					//�U�����
	int					m_nAttackDelay;				//�U���̍d������
	int					m_nAttackCount;				//�U���܂ł̎���
	bool				m_bResult;
													//���[�V�����֐�
	KEY_INFO			*m_pKeyInfo[MAX_MOTION];	//�L�[���ւ̃|�C���^
	int					m_nKey;						//���݂̃L�[�i���o�[
	int					m_nCountFlame;				//�t���[����
	int					m_nNumParts;				//�p�[�c��
	int					m_aIndexParent[MAX_PARTS];	//�e�̃C���f�b�N�X
	KEY					m_aKayOffset[MAX_PARTS];	//�I�t�Z�b�g���
	MOTION_INFO			m_aMotionInfo[MAX_MOTION];	//���[�V�������
	int					m_nMotionType;				//���[�V�����̃^�C�v(int�^)
	bool				m_bMotionEnd;
	D3DXVECTOR3			m_OffSetPos[MAX_PARTS];

	static CMeshOrbit   *m_MeshOrbit;
};
#endif