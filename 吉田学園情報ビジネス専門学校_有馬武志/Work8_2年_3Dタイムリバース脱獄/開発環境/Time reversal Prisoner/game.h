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
#define MAX_MAP_NUM		(1000)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CBullet;
class CNumber;
class CPause;
class CHelp;
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;
class CItem;
class CShadow;
class CEnemy;
class CLogo;
class CDummyEnemy;
class CDummyPlayer;
class CBlood;
class CSpotLight;
class CObjectShadow;

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
		GAMESTATE_CLEAR,					//�Q�[���N���A
		GAMESTATE_OVER,						//�Q�[���I�[�o�[
		GAMESTATE_END,						//�Q�[���I��
		GAMESTATE_MAX						//�ő吔
	}GAMESTATE;

	typedef enum
	{//�e�X�e�[�W
		STAGE_NONE = 0,						//�������ĂȂ����
		STAGENUM_1,							//�X�e�[�W1
		STAGENUM_2,							//�X�e�[�W2
		STAGENUM_3,							//�X�e�[�W3
		STAGENUM_4,							//�X�e�[�W4
		STAGENUM_5,							//�X�e�[�W5
		STAGENUM_6,							//�X�e�[�W6
		STAGENUM_7,							//�X�e�[�W7
	}STAGENUM;

	CGame();								//�R���X�g���N�^
	~CGame();								//�f�X�g���N�^
	HRESULT Init();							//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	static void SetGameState(GAMESTATE state) { m_gameState = state; }
	static void SetPause(bool bPause);
	static void SetHelp(bool bHelp);
	static bool GetPause(void) { return m_bPause; }
	static bool GetHelp(void) { return m_bHelp; }
	static GAMESTATE GetGameState(void) { return m_gameState; }
	static CPlayer *&GetPlayer(void) { return m_pPlayer; }
	static CPolygon3D *GetPolygon3D(void) { return m_pPolygon3D; }
	static CModel *GetModel(void) { return m_pModel; }
	static CMeshField *GetMeshField(void) { return m_pMeshField; }
	static CObject *Get3DObject(void) { return m_pObject; }
	static CBillBoord *GetBillboord(void) { return m_pBillBoord; }
	static CEffect *GetEffect(void) { return m_pEffect; }
	static CGround *GetGround(void) { return m_pGround; }
	static CEnemy *GetEnemy(void) { return m_pEnemy; }
	static CDummyPlayer *&GetDummyPlayer(void) { return m_pDummyPlayer; }
	static CDummyEnemy *GetDummyEnemy(void) { return m_pDummyEnemy; }

	//�X�e�[�W
	static STAGENUM GetNumState(void) { return m_StageState; }
	void SetNumState(STAGENUM stagenum);
	void SetStageState(STAGENUM stage);
	void SetStage(void);

	//�t�@�C����ǂݍ���
	void TextLoad(int nLoadNumber);
	void MeshTextLoad(int nLoadNumber);
	void WallTextLoad(int nLoadNumber);
	char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	char *GetLineTop(char *pStr);				//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

private:
	//�e�L�X�g�̒l���Ǘ�����ꏊ
	typedef struct
	{
		int					m_nType;			// ���
		int					m_nTexType;			// �e�N�X�`���̎��
		int					m_nCollision;		// �����蔻���ONOFF
		D3DXVECTOR3			m_pos;				// �ʒu
		D3DXVECTOR3			m_rot;				// ��]
	}Map;

	//�e�L�X�g�̒l���Ǘ�����ꏊ
	typedef struct
	{
		int					m_nTexType;						// �e�N�X�`���̎��
		int					m_nWidthDivide;					// ���̕�����������
		int					m_nDepthDivide;					// ���̕�����������
		float				m_fWidthLength;					// ���̒���
		float				m_fDepthLength;					// ���̒���
		float				m_fVtxHeight_No0;				// ���_�ԍ�0�𑀍�
		float				m_fVtxHeight_No1;				// ���_�ԍ�1�𑀍�
		float				m_fVtxHeight_No2;				// ���_�ԍ�2�𑀍�
		float				m_fVtxHeight_No3;				// ���_�ԍ�3�𑀍�
		D3DXVECTOR3			m_pos;							// �ʒu
	}Mesh;

	//�e�L�X�g�̒l���Ǘ�����ꏊ
	typedef struct
	{
		D3DXVECTOR3			m_pos;				// �ʒu
		D3DXVECTOR3			m_rot;				// ��]
		float				m_fWidthDivide;		// ����
		float				m_fHightDivide;		// �c��
		int					m_nTexType;			// �e�N�X�`���̎��
	}Wall;

	static GAMESTATE m_gameState;			//�Q�[�����
	GAMESTATE m_NowGameState;				//���݂̃Q�[����
	int m_nCounterGameState;				//��ԃJ�E���^
	static CBullet *m_pBullet;				//�e�̃|�C���^
	static CPlayer *m_pPlayer;				//�v���C���[�̃|�C���^
	static CNumber *m_pNumber;				//�����̃|�C���^
	static CPause *m_pPause;				//�|�[�Y�̃|�C���^
	static CHelp *m_pHelp;					//�w���v�̃|�C���^
	static CPolygon3D *m_pPolygon3D;		//�RD�|���S���̃|�C���^
	static CModel *m_pModel;				//���f���̃|�C���^
	static CMeshField *m_pMeshField;		//���b�V���t�B�[���h�̃|�C���^
	static CObject *m_pObject;				//�I�u�W�F�N�g�̃|�C���^
	static CBillBoord *m_pBillBoord;		//�r���{�[�h�̃|�C���^
	static CEffect *m_pEffect;				//�G�t�F�N�g�̃|�C���^
	static CWall *m_pWall;					//�ǂ̃|�C���^
	static CGround *m_pGround;				//�n�ʂ̃|�C���^
	static CItem *m_pItem;					//�A�C�e���̃|�C���^
	static CShadow *m_pShadow;				//�e�̃|�C���^
	static CSpotLight *m_pSpotLight;		//�X�|�b�g���C�g�̃|�C���^
	static CEnemy *m_pEnemy;				//�G�̃|�C���^
	static CDummyEnemy *m_pDummyEnemy;		//�G�̃|�C���^
	static CDummyPlayer *m_pDummyPlayer;	//�v���C���[�̃|�C���^
	static bool m_bPause;					//���݃|�[�Y���|�[�Y����Ȃ���
	static bool m_bHelp;					//���݃w���v���w���v����Ȃ���
	static int	m_nCntSetStage;				// �X�e�[�W�Z�b�g�J�E���^
	static STAGENUM m_StageState;			// �X�e�[�W���
	static STAGENUM m_ConteniueStage;		//�R���e�j���[�������̃G���A����X�^�[�g
	static CObjectShadow *m_pObjectShadow;	//�X�e���V���V���h�E�̃|�C���^
	int m_nSetObjectNum;					//�I�u�W�F�N�g��u������
	int m_nSetMeshFieldNum;					//���b�V���t�B�[���h��u������
	int	m_nSetWallNum;						//�ǂ̒u������
	int	m_nEnemyCount;						//�G�̐�
	Map m_Map[MAX_MAP_NUM];					//�ݒu����I�u�W�F�N�g�̍\����
	Mesh m_Mesh[MAX_MAP_NUM];				//�ݒu���郁�b�V���t�B�[���h�̍\����
	Wall m_aWall[MAX_MAP_NUM];				//�ݒu����ǂ̍\����
};
#endif