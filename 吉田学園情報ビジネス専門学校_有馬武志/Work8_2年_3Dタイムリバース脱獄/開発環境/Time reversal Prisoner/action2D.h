//=============================================================================
//
// �A�N�V�����|���S���̏��� [action2D.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _ACTION2D_H_
#define _ACTION2D_H_

#include "main.h"
#include "billboord.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CAction2D : public CScene2D
{
public://�N�ł�������
	CAction2D();
	~CAction2D();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CAction2D *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int							m_nType;					//���
	D3DXVECTOR2					m_size;						//�T�C�Y
};
#endif