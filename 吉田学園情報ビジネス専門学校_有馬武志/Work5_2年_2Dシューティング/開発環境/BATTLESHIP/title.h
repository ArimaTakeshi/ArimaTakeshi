//=============================================================================
//
// ���C������ [title.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "sound.h"

//=====================
// ��{�N���X
//=====================
class CTitle
{
public:
	CTitle();										//�R���X�g���N�^
	~CTitle();										//�f�X�g���N�^
	HRESULT Init();									//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	static HRESULT Load(void);						//�e�N�X�`���ǂݍ���
	static void UnLoad(void);						//�e�N�X�`���̔j��

private:
	static LPDIRECT3DTEXTURE9     m_pTexture;
	int							  m_nCount;			
	int							  m_nCnt;
};
#endif

