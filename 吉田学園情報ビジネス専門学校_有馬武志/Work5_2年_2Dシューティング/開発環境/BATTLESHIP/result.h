//=============================================================================
//
// ���U���g���� [result.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CSerect;

//=====================
// ��{�N���X
//=====================
class CResult
{
public:
	CResult();										//�R���X�g���N�^
	~CResult();										//�f�X�g���N�^
	HRESULT Init();									//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	static HRESULT Load(void);						//�e�N�X�`���ǂݍ���
	static void UnLoad(void);

private:
	static CSerect				  *m_pSerect;
	static LPDIRECT3DTEXTURE9     m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3					  m_pos;			//�|���S���̈ʒu
	D3DXCOLOR					  m_col;			//�|���S���̈ʒu
	float						  m_fSize;			//�T�C�Y
	int							  m_nCnt;			//�^�C�g���ɍs������
	int							  m_nSetCnt;		//�񍐂̎���
};
#endif

