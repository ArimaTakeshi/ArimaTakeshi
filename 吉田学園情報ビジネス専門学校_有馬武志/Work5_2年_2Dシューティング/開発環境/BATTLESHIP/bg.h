//=============================================================================
//
// �w�i�̏��� [bg.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CBg : public CScene2D
{
public://�N�ł�������
	CBg();
	~CBg();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBg *Create(int nType);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int m_nCnt;											//�t���[���J�E���^
	int m_nType;										//���
};
#endif