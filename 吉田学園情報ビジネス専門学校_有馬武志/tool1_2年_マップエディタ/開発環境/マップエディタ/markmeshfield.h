//=============================================================================
//
// ��̃��b�V������ [markmeshfield.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _MARKMESHFIELD_H_
#define _MARKMESHFIELD_H_

#include "mesh.h"
#include "meshfield.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CMesh�̔h���N���X
//=====================
class CMarkMeshField : public CMesh
{
public://�N�ł�������
	CMarkMeshField();
	~CMarkMeshField();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UninitCreate(D3DXVECTOR3 pos);
	static CMarkMeshField *Create(D3DXVECTOR3 pos, int nMeshX, int nMeshZ, float fMeshWidth, float fMeshDepth,float fVtx0, float fVtxMeshX, float fVtxMeshZ, float fVtxMeshXMeshZ, int nTexTypeint,int nVtxNumber,int nMeshType);
	static int GetMeshFieldNum(void) { return m_nMarkFieldNum; }
	static void SetMeshFieldNum(int nNum) { m_nMarkFieldNum = nNum; }

private://�l�ł̂ݎg��
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_MESH_TEXTURE];	// �e�N�X�`���ւ̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;						// �C���f�b�N�X�ւ̃|�C���^
	int								m_nCnt;
	int								m_nType;
	float							m_fVtx0;						// pVtx[0]�Ԗڂ̍�����ς���
	float							m_fVtxMeshX;					// pVtx[MeshX + 1]�Ԗڂ̍�����ς���
	static int						m_nMarkFieldNum;				// ���������t�B�[���h�̐�
	int								m_nWidthDivide;					// ���̕�����������
	int								m_nDepthDivide;					// ���̕�����������
	float							m_fWidthLength;					// ���̒���
	float							m_fDepthLength;					// ���̒���
	int								m_nSelectNum;					// �I��ł������
	int								m_nTexType;						// �e�N�X�`���̎��
	int								m_nVtxNumber;					// �I�����Ă��钸�_�̔ԍ�
	float							m_fVtxHeight_No0;				// ���_�ԍ�0�𑀍�
	float							m_fVtxHeight_No1;				// ���_�ԍ�1�𑀍�
	float							m_fVtxHeight_No2;				// ���_�ԍ�2�𑀍�
	float							m_fVtxHeight_No3;				// ���_�ԍ�3�𑀍�
	float							m_fMove;						// �ύX���邽�߂̈ړ���			
	D3DXVECTOR3						m_move;							// �^������ړ���
	D3DXVECTOR4						m_Vtx;							// �e���_�̍����p
	int								m_nClidked;						// �ۑ��p
	bool							m_bSetFeild;					// �ݒu�p
	static CMeshField				*m_pMeshField;					// ���b�V���t�B�[���h�̃|�C���^

};
#endif