//=============================================================================
//
// ���C������ [title.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "sound.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MAP_NUM		(1000)
#define TITLEWORD_INITPOS_Y (350.0f)		// �^�C�g�������̏�������
#define SUBTITLE_INITSIZE (1000.0f)			// �T�u�^�C�g���̏����T�C�Y
#define ISLAND_STERT (600)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;
class CShadow;
class CSpotLight;
//=====================
// ��{�N���X
//=====================
class CTitle
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SKIP,
		TYPE_MAX
	}TYPE;

	CTitle();								// �R���X�g���N�^
	~CTitle();								// �f�X�g���N�^
	HRESULT Init();							// ����������
	void	Uninit(void);					// �I������
	void	Update(void);					// �X�V����
	void	Draw(void);						// �`�揈��
	void	Set(void);						// �ŏ���Create

	void	CreateStage(void);				// �X�e�[�W�̐������ꊇ�Ǘ�
	void	CreateObject(void);				// �X�e�[�W��̃I�u�W�F�N�g�������ꊇ�Ǘ�
	static TYPE GetType(void);				// �^�C�v�̎擾

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
		int								m_nTexType;						// �e�N�X�`���̎��
		int								m_nWidthDivide;					// ���̕�����������
		int								m_nDepthDivide;					// ���̕�����������
		float							m_fWidthLength;					// ���̒���
		float							m_fDepthLength;					// ���̒���
		float							m_fVtxHeight_No0;				// ���_�ԍ�0�𑀍�
		float							m_fVtxHeight_No1;				// ���_�ԍ�1�𑀍�
		float							m_fVtxHeight_No2;				// ���_�ԍ�2�𑀍�
		float							m_fVtxHeight_No3;				// ���_�ԍ�3�𑀍�
		D3DXVECTOR3						m_pos;							// �ʒu
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

	static TYPE			m_pType;			// �^�C�g����ʂ� �^�C�v

	static CPolygon3D	*m_pPolygon3D;		// �RD�|���S���� �|�C���^
	static CModel		*m_pModel;			// ���f���� �|�C���^
	static CMeshField	*m_pMeshField;		// ���b�V���t�B�[���h�� �|�C���^
	static CObject		*m_pObject;			// �I�u�W�F�N�g�� �|�C���^
	static CBillBoord	*m_pBillBoord;		// �r���{�[�h�� �|�C���^
	static CEffect		*m_pEffect;			// �G�t�F�N�g�� �|�C���^
	static CWall		*m_pWall;			// �ǂ� �|�C���^
	static CGround		*m_pGround;			// �n�ʂ� �|�C���^
	static CPlayer		*m_pPlayer;			//�v���C���[�̃|�C���^
	static CEnemy		*m_pEnemy;			//�G�̃|�C���^
	static CShadow		*m_pShadow;			//�e�̃|�C���^
	static CSpotLight	*m_pSpotLight;		//�X�|�b�g���C�g�̃|�C���^

	int					m_nCount;			// �����t�� �J�E���^�[
	int					m_nCnt;				// �e�N�X�`���� �J�E���^�[
	int					m_nLagCnt;
	int					m_nLeafposY;		// �����t�� �������W
	int					m_nLeafsize;		// �����t�� �T�C�Y
	bool				m_bOnOff;

	int m_nSetObjectNum;					//�I�u�W�F�N�g��u������
	int m_nSetMeshFieldNum;					//���b�V���t�B�[���h��u������
	int	m_nSetWallNum;						//�ǂ̒u������
	Map m_Map[MAX_MAP_NUM];					//�ݒu����I�u�W�F�N�g�̍\����
	Mesh m_Mesh[MAX_MAP_NUM];				//�ݒu���郁�b�V���t�B�[���h�̍\����
	Wall m_aWall[MAX_MAP_NUM];				//�ݒu����ǂ̍\����
};
#endif