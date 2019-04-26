//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2D�̔h���N���X
//=====================
class CBullet : public CScene2D
{
public://�N�ł�������
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,		//�v���C���[
		BULLETTYPE_ENEMY,			//�G
		BULLETTYPE_MAX				//�ő吔
	}BULLETTYPE;

	typedef enum
	{
		GAN_CANNON = 0,				//��C�e
		GAN_SKYCANNON,				//�΋�C�e
		GAN_TORPEDO,				//�����e
		GAN_MAX						//�ő吔
	}GANTYPE_BULLET;

	typedef enum
	{
		PLAYER_SHIP = 0,			//�v���C���[���
		ENEMY_SHIP,					//�G���
		ENEMY_DIGHTER,				//�G�퓬�@
		ENEMY_SUBMARINE,			//�G������
		ENEMT_CARRIER,				//�G���
	}PETYPE;

	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size, BULLETTYPE type, GANTYPE_BULLET bullettype, PETYPE petype,int nBulletType);
	GANTYPE_BULLET GetBulletType(void) { return m_gantype; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				  m_move;					//�ړ���
	int						  m_nType;					//���
	int						  m_nDamage;				//�_���[�W
	int						  m_nBulletType;			//�e�̒e�̎��
	D3DXVECTOR2				  m_Size;					//�T�C�Y
	PETYPE					  m_Petype;					//�G��������
	GANTYPE_BULLET            m_gantype;				//�e�̎��
};

#endif