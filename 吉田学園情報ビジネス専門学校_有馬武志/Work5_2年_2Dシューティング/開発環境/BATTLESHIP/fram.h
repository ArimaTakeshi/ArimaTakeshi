//=============================================================================
//
// �g�̏��� [fram.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _FRAM_H_
#define _FRAM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CFram : public CScene2D
{
public://�N�ł�������
	CFram();
	~CFram();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFram *Create(int nType);
	
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int m_nCnt;											//�t���[���J�E���^
	int m_nType;										//���
};
#endif