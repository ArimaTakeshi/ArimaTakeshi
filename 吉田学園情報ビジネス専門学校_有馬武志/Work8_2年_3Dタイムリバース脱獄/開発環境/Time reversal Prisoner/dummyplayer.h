//=============================================================================
//
// �v���C���[���� [dummyplayer.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _DUMMYPLAYER_H_
#define _DUMMYPLAYER_H_

#include "scene.h"
#include "model.h"
#include "meshorbit.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME_DUMMYPRISONER		"data\\TEXT\\Prisoner1.txt"	//�ǂݍ���txt�t�@�C���̖��O
#define MAX_DUMMYPLAYERANIM			(8)							//�A�j���[�V������
#define MAX_DUMMYPLAYERKEY			(8)							//�L�[�t���[����
#define MAX_DUMMYPARTS				(30)						//�p�[�c�̍ő吔
#define MAX_DUMMYMOTION				(10)						//���[�V�����̍ő吔

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  CScene�̔h���N���X
//=====================
class CDummyPlayer : public CScene
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
		DUMMYPLAYERANIM_NEUTRAL = 0,	//�j���[�g�������[�V����
		DUMMYPLAYERANIM_WALK,			//����
		DUMMYPLAYERANIM_RUN,			//����
		DUMMYPLAYERANIM_SIT,			//����
		DUMMYPLAYERANIM_TIRED,			//����
		DUMMYPLAYERANIM_SQUAT,			//���Ⴊ��
		DUMMYPLAYERANIM_SNEAK,			//���Ⴊ�ݕ���
		DUMMYPLAYERANIM_DIE,			//�|���
		DUMMYPLALYER_MAX				//���[�V�����̍ő吔
	}DummyPlayerAnim;

	CDummyPlayer(int nPriority = 2, CScene::OBJTYPE objType = CScene::OBJTYPE_PLAYER);
	~CDummyPlayer();
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
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static CDummyPlayer *Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nAnimnow);
	DummyPlayerAnim GetAnim(void) { return m_nAnimnow; }
	D3DXVECTOR3 GetVtxMax(void) { return m_vtxMax; }
	D3DXVECTOR3 GetVtxMin(void) { return m_vtxMin; }

	//���[�V�����̍X�V�֐�
	void UpdateMotion(void);

	//�t�@�C���ǂݍ��݊֐�
	void FileLoad(void);								//�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);			//1�s�ǂݍ���
	char *GetLineTop(char *pStr);						//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);			//�s�̍Ō��؂�̂�

private://�l�ł̂ݎg��
	static LPD3DXMESH	m_pMesh[MAX_DUMMYPARTS];		//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER	m_pBuffMat[MAX_DUMMYPARTS];		//�}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMat[MAX_DUMMYPARTS];		//�}�e���A���̏��
	static D3DXVECTOR3	m_pos;							//�ʒu
	static D3DXVECTOR3	m_move;							//����
	static D3DXVECTOR3	m_rot;							//����
	D3DXVECTOR3			m_rotDest;						//�ߋ��̌���
	D3DXVECTOR3			m_posOld;						//�ߋ��̈ʒu
	D3DXVECTOR3			m_posFuture;					//�����̈ʒu
	D3DXVECTOR3			m_rotFuture;					//�����̌���
	D3DXMATRIX			m_mtxWorld;						//���[���h�}�g���b�N�X
	CModel				*m_apModel[MAX_DUMMYPARTS];		//���f���ւ̃|�C���^
	DummyPlayerAnim		m_nAnimnow;						//���݂̃A�j���[�V����
	D3DXVECTOR3			m_vtxMin;						//���f���̍ŏ��l
	D3DXVECTOR3			m_vtxMax;						//���f���̍ő�l
	bool				m_bJump;						//�W�����v���
	bool				m_bLand;						//���n���

	// ���[�V�����֐�	�V�K
	KEY_INFO			*m_pKeyInfo[MAX_DUMMYMOTION];	//�L�[���ւ̃|�C���^
	int					m_nKey;							//���݂̃L�[�i���o�[
	int					m_nCountFlame;					//�t���[����
	int					m_nNumParts;					//�p�[�c��
	int					m_aIndexParent[MAX_DUMMYPARTS];	//�e�̃C���f�b�N�X
	KEY					m_aKayOffset[MAX_DUMMYPARTS];	//�I�t�Z�b�g���
	MOTION_INFO			m_aMotionInfo[MAX_DUMMYMOTION];	//���[�V�������
	int					m_nMotionType;					//���[�V�����̃^�C�v(int�^)
	bool				m_bMotionEnd;					//���[�V�����I��
	D3DXVECTOR3			m_OffSetPos[MAX_DUMMYPARTS];	//�p�[�c���Ƃ̍ŏ��̈ʒu

	static CMeshOrbit   *m_MeshOrbit;					//�O�Ղ̃|�C���^
	bool				m_bGaugeOnOff;					//�Q�[�W�̃I���I�t�̏��
};
#endif