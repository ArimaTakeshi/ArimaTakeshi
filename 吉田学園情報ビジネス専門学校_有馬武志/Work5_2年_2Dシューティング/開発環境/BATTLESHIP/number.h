//=============================================================================
//
// ���C������ [number.h]
// Author : 
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_NUMBER_TEXTURE		(2)						//�e�N�X�`���̍ő喇��

//=====================
// ��{�N���X
//=====================
class CNumber
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_KILL,
		TYPE_SCORE,
		TYPE_DAMAGE,
		TYPE_MAX
	}TYPE;

	CNumber();										//�R���X�g���N�^
	~CNumber();										//�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);					//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	static CNumber *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);						//�e�N�X�`���ǂݍ���
	static void UnLoad(void);
	static void SetType(TYPE Type) { m_nType = Type; }
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9     m_pTexture[MAX_NUMBER_TEXTURE];
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3					  m_pos;			//�|���S���̈ʒu
	D3DXCOLOR					  m_col;			//�|���S���̈ʒu
	static int				      m_nType;			//�^�C�v�����锠
};
#endif

