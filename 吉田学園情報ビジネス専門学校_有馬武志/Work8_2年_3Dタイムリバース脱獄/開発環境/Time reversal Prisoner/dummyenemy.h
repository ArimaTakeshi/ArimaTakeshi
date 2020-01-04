//=============================================================================
//
// �G�l�~�[���� [dummyenemy.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _DUMMYENEMY_H_
#define _DUMMYENEMY_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"
#include "billboord.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_DUMMYNAME				"data\\TEXT\\stok2.txt"	//�ǂݍ���txt�t�@�C���̖��O
#define MAX_DUMMYENEMYANIM			(8)						//�A�j���[�V������
#define MAX_DUMMYENEMYKEY			(8)						//�L�[�t���[����
#define MAX_DUMMYPARTS				(30)					//�p�[�c�̍ő吔
#define MAX_DUMMYMOTION				(10)					//���[�V�����̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  CScene�̔h���N���X
//=====================
class CDummyEnemy : public CScene
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
		KEY aKey[MAX_DUMMYPARTS];
	}KEY_INFO;

	//���[�V�������
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKayInfo[MAX_DUMMYMOTION];
	}MOTION_INFO;

	//���[�V�������
	typedef enum
	{
		DUMMYENEMYANIM_NEUTRAL = 0,		//�j���[�g�������[�V����
		DUMMYENEMYANIM_MOVE,			//�ړ����[�V����
		DUMMYENEMYANIM_JUMP,			//�W�����v���[�V����
		DUMMYENEMYANIM_ATTACK,			//�ߋ����U�����[�V����
		DUMMYENEMYANIM_HOLDAGAN,		//�e���\���郂�[�V����
		DUMMYENEMYANIM_SHOT,			//�e�������[�V����
		DUMMYENEMYANIM_HOLDAGANWALK,	//�\���ĕ������[�V����
		DUMMYENEMYANIM_TAKEGAN,			//�e�����܂����[�V����
		DUMMYENEMYANIM_LOOKAROUND,		//��������n�����[�V����
		DUMMYENEMY_MAX					//���[�V�����̍ő吔
	}DummyEnemyAnim;

	CDummyEnemy(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_ENEMY);
	~CDummyEnemy();
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
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CDummyEnemy *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nAnimnow);
	void CollisitionItem(void);
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }
	void DeleteEnemy(void);

	//���[�V�����̍X�V�֐�
	void UpdateMotion(void);

	//�t�@�C���ǂݍ��݊֐�
	void FileLoad(void);							//�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);		//1�s�ǂݍ���
	char *GetLineTop(char *pStr);					//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);		//�s�̍Ō��؂�̂�

private://�l�ł̂ݎg��
	static LPD3DXMESH	m_pMesh[MAX_DUMMYPARTS];	//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER	m_pBuffMat[MAX_DUMMYPARTS];	//�}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMat[MAX_DUMMYPARTS];	//�}�e���A���̏��
	D3DXVECTOR3			m_pos;						//�ʒu
	D3DXVECTOR3			m_rot;						//����
	D3DXVECTOR3			m_posPast;					//�ߋ��̈ʒu
	D3DXVECTOR3			m_rotPast;					//�ߋ��̌���
	D3DXVECTOR3			m_rotDest;					//����
	D3DXVECTOR3			m_posOld;					//�ߋ��̈ʒu
	D3DXVECTOR3			m_move;						//����
	D3DXMATRIX			m_mtxWorld;					//���[���h�}�g���b�N�X
	CModel				*m_apModel[MAX_DUMMYPARTS];	//���f���ւ̃|�C���^
	DummyEnemyAnim		m_nAnimnow;					//���݂̃A�j���[�V����
	D3DXVECTOR3			m_vtxMin;					//���f���̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���f���̍ő�l
	bool				m_bJump;					//�W�����v���
	bool				m_bLand;					//���n���

	//���[�V�����֐�
	KEY_INFO			*m_pKeyInfo[MAX_DUMMYMOTION];	//�L�[���ւ̃|�C���^
	int					m_nKey;							//���݂̃L�[�i���o�[
	int					m_nCountFlame;					//�t���[����
	int					m_nNumParts;					//�p�[�c��
	int					m_aIndexParent[MAX_DUMMYPARTS];	//�e�̃C���f�b�N�X
	KEY					m_aKayOffset[MAX_DUMMYPARTS];	//�I�t�Z�b�g���
	MOTION_INFO			m_aMotionInfo[MAX_DUMMYMOTION];	//���[�V�������
	int					m_nMotionType;					//���[�V�����̃^�C�v(int�^)
	bool				m_bMotionEnd;					//���[�V�����I��
	D3DXVECTOR3			m_OffSetPos[MAX_DUMMYPARTS];	//�p�[�c���Ƃ̏����ʒu
		
	static CMeshOrbit   *m_MeshOrbit;				//�O�Ղ̃|�C���^
	CBillBoord			*m_pBillboord;				//�r���{�[�h�̃|�C���^
	CShadow				*m_pShadow;					//�e�̃|�C���^
};
#endif