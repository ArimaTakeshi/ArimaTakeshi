//=============================================================================
//
// �I�u�W�F�N�g���� [2Dobject.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _2DOBJECT_H_
#define _2DOBJECT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`�@�Ƌ���
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2D�̔h���N���X
//=====================
class C2DObject : public CScene2D
{
public://�N�ł�������
	C2DObject();
	~C2DObject();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR2 *GetSize(void) { return &m_Size; }
	void HitObject(int nDamage);
	static C2DObject *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType,int nLife);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR2	m_Size;									//�T�C�Y
	D3DXVECTOR3 m_posold;								//�ߋ��̈ʒu
	float m_fPlayerLife;								//�v���C���[�̗̑͂����锠
	int m_nLife;
	int	m_nType;										//���
};
#endif