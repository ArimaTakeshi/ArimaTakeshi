//=============================================================================
//
// �e�̏��� [gan.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _GAN_H_
#define _GAN_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CGan : public CScene2D
{
public://�N�ł�������
	typedef enum
	{
		GANTYPE_PLAYER = 0,		//�v���C���[
		GANTYPE_ENEMY,			//�G
		GANTYPE_MAX				//�ő吔
	}TYPE;

	typedef enum
	{
		GAN_CANNON = 0,			//��C
		GAN_SKYCANNON,			//�΋�C
		GAN_TORPEDO,			//����
		GAN_MAX					//�ő吔
	}GAN;

	CGan();
	~CGan();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	GAN *GetGanType(void) { return &m_gantype; }
	static CGan *Create(D3DXVECTOR2 size,TYPE type, GAN gantype,int nfram);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				  m_move;					//�ړ���
	int						  m_nType;					//���
	int						  m_nCount;					//�J�E���^�[
	int						  m_nCannonCount;			//��C�J�E���^�[
	GAN						  m_gantype;				//�e�̎��
	D3DXVECTOR2				  m_Size;					//�T�C�Y
	int						  m_nFram;					//�g���g����Ȃ���
	float					  m_fLife;					//�v���C���[��HP�����Ă�����
	bool					  m_bInitTex;				//�����e�N�X�`��
	float					  m_fRot;					//��]
	float					  m_fLength;				//����
	D3DXVECTOR3				  m_rot;					
};

#endif