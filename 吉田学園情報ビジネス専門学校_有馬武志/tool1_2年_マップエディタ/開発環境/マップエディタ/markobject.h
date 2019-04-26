//=============================================================================
//
// �I�u�W�F�N�g���� [markobject.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _MARKOBJECT_H_
#define _MARKOBJECT_H_

#include "model3D.h"
#include "camera.h"
#include "object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MARKOBJECT_TEXTURE			(11)			// �I�u�W�F�N�g�̃e�N�X�`����
#define MAX_MARKOBJECT					(32)			// �I�u�W�F�N�g�̃��f����
#define MARKOBJECT_PRIOTITY				(2)				// �I�u�W�F�N�g�̗D�揇��

//=====================
//  CModel3D�̔h���N���X
//=====================
class CMarkObject : public CModel3D
{
public://�N�ł�������
	CMarkObject();
	~CMarkObject();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMarkObject *Create(D3DXVECTOR3 pos,int nTexTypeint,int nObjectType);
	static int GetObjectNum(void) { return m_nMarkObjNum; }
	static void SetObjectNum(int nNum) { m_nMarkObjNum = nNum; }
	void CollisitionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	static bool GetCraftDelete(void) { return m_bCraftDelete; }

private://�l�ł̂ݎg��
	static CObject		*m_pObject;											// �I�u�W�F�N�g�̃|�C���^
	static LPD3DXMESH	m_pMeshMarkModel[MAX_MARKOBJECT];					// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatMarkModel[MAX_MARKOBJECT];				// �}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMatMarkModel[MAX_MARKOBJECT];					// �}�e���A���̏��
	static LPDIRECT3DTEXTURE9 m_pMeshMarkTextures[MAX_MARKOBJECT_TEXTURE];	// �e�N�X�`���̏��
	D3DXVECTOR3			m_move;												// �ړ���
	D3DXVECTOR3			m_Spin;												// ��]
	int					m_nCount;											// �J�E���^�[
	int					m_nCollision;										// �����蔻���ONOFF
	int					m_nType;											// ���
	D3DXVECTOR3			m_ModelMove;										// �ړ��̎d��
	float				m_fMove;											// �ړ��̑���
	int					m_nSelectNum;										// �I�u�W�F�N�g�̑I��
	int					m_nSelectCollision;									// �����蔻��̑I��
	static int			m_nMarkObjNum;										// ������I�u�W�F�N�g�̐�
	int					m_nTexType;											// �e�N�X�`���̎��
	int					m_nCraftDeleteNumber;
	bool				m_bSetObject;										// �I�u�W�F�N�g�̐ݒu
	static bool			m_bCraftDelete;										// �폜���[�h���������[�h�̏��
};
#endif