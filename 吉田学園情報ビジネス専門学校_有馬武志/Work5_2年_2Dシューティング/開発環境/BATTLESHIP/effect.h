//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2D�̔h���N���X
//=====================
class CEffect : public CScene2D
{
public://�N�ł�������
	typedef enum
	{
		EFFECTTYPE_NOLMAL = 0,
		EFFECTTYPE_RIPPLE,
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect();
	~CEffect();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect *Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,float fRadiusint,int nLife, EFFECTTYPE nType, int nTexType);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_DATA];	//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				  m_move;					//�ړ���
	int						  m_nLife;					//����
	D3DXVECTOR2				  m_Size;					//�T�C�Y
	float					  m_fRadius;				//���a
	EFFECTTYPE				  m_Type;					//���
};
#endif