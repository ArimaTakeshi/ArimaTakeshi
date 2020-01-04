//=============================================================================
//
// �X�|�b�g���C�g�̏��� [spotlight.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"
class CEnemy;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SPOTLIGHT_PRIOTITY		(3)

//=====================
//  CScene3D�̔h���N���X
//=====================
class CSpotLight : public CScene3D
{
public://�N�ł�������
	CSpotLight();
	~CSpotLight();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSpotLight *Create(D3DXVECTOR3 pos, float fWidth, float fDepth,int nTexType,CEnemy *pEnemy);
	void SetPositionSpotLight(D3DXVECTOR3 pos);
	void CollisitionMesh(void);
	void CollisionSpotLight(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	float GetSpotLightHeight(void) { return m_fMeshHeight; }

private://�l�ł̂ݎg��
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_BILLBOORD_TEX];	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3					m_pos;							// �ʒu
	float						m_fWidth;						// ����
	float						m_fDepth;						// ���s	
	static float				m_fMeshHeight;					// �e����݂����b�V���̍���
	bool						m_bSpotLightIn;					// ���C�g�ɓ��������
	float						m_fSwing;						//���C�g��U��
	int							m_nSwingTime;					//���C�g��U��^�C�~���O
	CEnemy						*m_pEnemy;

};
#endif