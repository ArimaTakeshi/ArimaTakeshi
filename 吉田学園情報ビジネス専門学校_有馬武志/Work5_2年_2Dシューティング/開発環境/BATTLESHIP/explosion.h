//=============================================================================
//
// �o���b�g���� [explosion.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`�@�Ƌ���
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2D�̔h���N���X
//=====================
class CExplosion : public CScene2D
{
public://�N�ł�������
	CExplosion();
	~CExplosion();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int m_nCounterAnim;									//�A�j���[�V�����J�E���^�[
	int m_nPatteunAnim;									//�A�j���[�V�����p�^�[��No.
	D3DXVECTOR2	m_Size;									//�T�C�Y
	int	m_nType;										//���
};
#endif