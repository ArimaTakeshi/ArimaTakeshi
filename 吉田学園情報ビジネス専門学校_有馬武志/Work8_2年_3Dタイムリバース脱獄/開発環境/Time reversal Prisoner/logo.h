//=============================================================================
//
// ���S�̏��� [logo.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "billboord.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CLogo : public CScene2D
{
public://�N�ł�������
	CLogo();
	~CLogo();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLogo *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType, int nTransformType);
	static void SetLogoState(int nStateType, int nStateFont);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	static int					m_nNextType;				//��Ԃ�Ⴄ�Ƃ��̃^�C�v
	static int					m_nNextFont;				//��Ԃ̕���
	int							m_nStateType;				//��Ԃ�Ⴄ�Ƃ��̃^�C�v
	int							m_nStateFont;				//��Ԃ̕���
	int							m_nType;					//���
	int							m_nTransformType;			//�摜�̌`��ς����^�C�v
	D3DXVECTOR2					m_size;						//�T�C�Y
	float						m_fLength;					//����
	float						m_fAngle;					//�p�x
	D3DXVECTOR3					m_rot;						//����
	int							m_nCntTutorial;
	bool						m_bOneCnt;
};
#endif