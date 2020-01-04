//=============================================================================
//
// �I�u�W�F�N�g���� [objectshadow.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _OBJECTSHADOW_H_
#define _OBJECTSHADOW_H_

#include "model3D.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_OBJECTSHADOW_TEXTURE			(1)			// �I�u�W�F�N�g�̃e�N�X�`����
#define MAX_OBJECTSHADOW					(1)			// �I�u�W�F�N�g�̃��f����
#define OBJECTSHADOW_PRIOTITY				(4)

//=====================
//  CModel3D�̔h���N���X
//=====================
class CObjectShadow : public CModel3D
{
public://�N�ł�������
	CObjectShadow();
	~CObjectShadow();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CObjectShadow *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float move, int nTexTypeint,int nObjectType, MOVETYPE nMovetype, int nCollision);
	bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	void DeleteObject(void);

private://�l�ł̂ݎg��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	static LPD3DXMESH	m_pMeshModel[MAX_OBJECTSHADOW];					//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMatModel[MAX_OBJECTSHADOW];				//�}�e���A���̏��ւ̃|�C���^
	static DWORD		m_nNumMatModel[MAX_OBJECTSHADOW];					//�}�e���A���̏��
	static LPDIRECT3DTEXTURE9 m_pMeshTextures[MAX_OBJECTSHADOW_TEXTURE];
	D3DXVECTOR3			m_move;										// �ړ���
	D3DXVECTOR3			m_Spin;										// ��]
	int					m_nCount;									// �J�E���^�[
	int					m_nCollision;								// �����蔻���ONOFF
	int					m_nType;									// ���
	D3DXVECTOR3			m_ModelMove;								// �ړ��̎d��
	int					m_nStageCount;								// �X�e�[�W�̈ړ����ɏ������Ԃ�������
	bool				m_bStageNext;								// �X�e�[�W�J�ڒ�

	CShadow				*m_pShadow;									//�e�̃|�C���^
	CLogo				*m_pLogo;
};
#endif