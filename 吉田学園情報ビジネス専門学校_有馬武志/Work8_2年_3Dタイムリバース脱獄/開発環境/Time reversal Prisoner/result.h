//=============================================================================
//
// ���U���g���� [result.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MAP_NUM		(1000)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CPlayer;
class CSerect;
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

//=====================
// ��{�N���X
//=====================
class CResult
{
public:
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
		int					m_nTexType;			// �e�N�X�`���̎��
		int					m_nWidthDivide;		// ���̕�����������
		int					m_nDepthDivide;		// ���̕�����������
		float				m_fWidthLength;		// ���̒���
		float				m_fDepthLength;		// ���̒���
		float				m_fVtxHeight_No0;	// ���_�ԍ�0�𑀍�
		float				m_fVtxHeight_No1;	// ���_�ԍ�1�𑀍�
		float				m_fVtxHeight_No2;	// ���_�ԍ�2�𑀍�
		float				m_fVtxHeight_No3;	// ���_�ԍ�3�𑀍�
		D3DXVECTOR3			m_pos;				// �ʒu
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

	CResult();								// �R���X�g���N�^
	~CResult();								// �f�X�g���N�^
	HRESULT Init();							// ����������
	void	Uninit(void);					// �I������
	void	Update(void);					// �X�V����
	void	Draw(void);						// �`�揈��

	//�t�@�C����ǂݍ���
	void TextLoad(int nLoadNumber);
	void MeshTextLoad(int nLoadNumber);
	void WallTextLoad(int nLoadNumber);
	char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	char *GetLineTop(char *pStr);				//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�
private:
	static CSerect		*m_pSerect;			// �Z���N�g�� �|�C���^
	static CPlayer		*m_pPlayer;			// �v���C���[�� �|�C���^
	static CPolygon3D	*m_pPolygon3D;		// �RD�|���S���� �|�C���^
	static CModel		*m_pModel;			// ���f���� �|�C���^
	static CMeshField	*m_pMeshField;		// ���b�V���t�B�[���h�� �|�C���^
	static CObject		*m_pObject;			// �I�u�W�F�N�g�� �|�C���^
	static CBillBoord	*m_pBillBoord;		// �r���{�[�h�� �|�C���^
	static CEffect		*m_pEffect;			// �G�t�F�N�g�� �|�C���^
	static CWall		*m_pWall;			// �ǂ� �|�C���^
	static CGround		*m_pGround;			// �n�ʂ� �|�C���^
	static CItem		*m_pItem;			// �A�C�e��	�� �|�C���^
	static CShadow		*m_pShadow;			// �e�̃|�C���^

	int					m_nCnt;				// �J�E���^�[
	int					m_nSetCnt;

	int m_nSetObjectNum;					//�I�u�W�F�N�g��u������
	int m_nSetMeshFieldNum;					//���b�V���t�B�[���h��u������
	int	m_nSetWallNum;						//�ǂ̒u������
	Map m_Map[MAX_MAP_NUM];					//�ݒu����I�u�W�F�N�g�̍\����
	Mesh m_Mesh[MAX_MAP_NUM];				//�ݒu���郁�b�V���t�B�[���h�̍\����
	Wall m_aWall[MAX_MAP_NUM];				//�ݒu����ǂ̍\����
};
#endif