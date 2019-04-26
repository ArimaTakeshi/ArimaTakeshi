//=============================================================================
//
// ���C������ [polygon.h]
// Author : 
//
//=============================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "main.h"
#include "scene2D.h"

//=====================
// ��{�N���X
//=====================
class CPolygon
{
public:
	CPolygon();										//�R���X�g���N�^
	~CPolygon();									//�f�X�g���N�^
	HRESULT Init(D3DXVECTOR3 pos);					//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	static CPolygon *Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);						//�e�N�X�`���ǂݍ���
	static void UnLoad(void);
	float GetSize(void) { return m_fSize; }
	void SetNumber(int nNumber);

private:
	static LPDIRECT3DTEXTURE9     m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3					  m_pos;			//�|���S���̈ʒu
	D3DXCOLOR					  m_col;			//�|���S���̈ʒu
	float						  m_fSize;			//�T�C�Y
};
#endif

