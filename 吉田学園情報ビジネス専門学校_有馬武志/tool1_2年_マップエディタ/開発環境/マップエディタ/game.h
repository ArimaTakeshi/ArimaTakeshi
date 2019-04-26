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
class CMarkObject;
class CMarkMeshField;
class CMarkWall;

//=====================
// ��{�N���X
//=====================
class CGame
{
public:
	typedef enum
	{
		GAMESTATE_NONE = 0,			//�������Ă��Ȃ����
		GAMESTATE_NORMAL,			//�ʏ���
		GAMESTATE_CLEAR,			//�Q�[���N���A
		GAMESTATE_OVER,				//�Q�[���I�[�o�[
		GAMESTATE_END,				//�Q�[���I��
		GAMESTATE_MAX				//�ő吔
	}GAMESTATE;

	CGame();						//�R���X�g���N�^
	~CGame();						//�f�X�g���N�^
	HRESULT Init();					//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��
	void CreateStage(void);			//�X�e�[�W�̐������ꊇ�Ǘ�
	void CreateObject(void);		//�X�e�[�W��̃I�u�W�F�N�g�������ꊇ�Ǘ�
	static void SetGameState(GAMESTATE state) { m_gameState = state; }
	static void SetPause(bool bPause);
	static bool GetPause(void) { return m_bPause; }
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
	static bool GetFieldObject(void){ return m_bFieldObject; }
	static bool GetWallMode(void) { return m_bWallMode; }

	//�t�@�C����ǂݍ���
	void TextLoad(void);
	void MeshTextLoad(void);
	void WallTextLoad(void);
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
		int								m_nTexType;				// �e�N�X�`���̎��
		int								m_nWidthDivide;			// ���̕�����������
		int								m_nDepthDivide;			// ���̕�����������
		float							m_fWidthLength;			// ���̒���
		float							m_fDepthLength;			// ���̒���
		float							m_fVtxHeight_No0;		// ���_�ԍ�0�𑀍�
		float							m_fVtxHeight_No1;		// ���_�ԍ�1�𑀍�
		float							m_fVtxHeight_No2;		// ���_�ԍ�2�𑀍�
		float							m_fVtxHeight_No3;		// ���_�ԍ�3�𑀍�
		D3DXVECTOR3						m_pos;					// �ʒu
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
	static CEnemy *m_pEnemy;				//�G�̃|�C���^
	static CMarkObject *m_pMarkObject;		//��̃I�u�W�F�N�g�̃|�C���^
	static CMarkMeshField *m_pMarkMeshField;//��̃��b�V���t�B�[���h�̃|�C���^
	static CMarkWall *m_pMarkWall;			//��̕�
	static bool m_bPause;					//���݃|�[�Y���|�[�Y����Ȃ���
	int m_nSetObjectNum;					//�I�u�W�F�N�g��u������
	int m_nWallNumber;						//�ǔԍ�
	int m_nNumber;							//�ԍ�
	int m_nSetMeshFieldNum;					//���b�V���t�B�[���h��u������
	int	m_nSetWallNum;						//�ǂ̒u������
	Map m_aMap[MAX_MAP_NUM];				//�ݒu����I�u�W�F�N�g�̍\����
	Mesh m_aMesh[MAX_MAP_NUM];				//�ݒu���郁�b�V���t�B�[���h�̍\����
	Wall m_aWall[MAX_MAP_NUM];				//�ݒu���郁�b�V���t�B�[���h�̍\����
	static bool m_bFieldObject;
	static bool m_bWallMode;
};
#endif