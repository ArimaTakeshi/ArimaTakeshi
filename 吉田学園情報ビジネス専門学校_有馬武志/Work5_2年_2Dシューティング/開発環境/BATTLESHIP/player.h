//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2D�̔h���N���X
//=====================
class CPlayer : public CScene2D
{
public://�N�ł�������
	typedef enum
	{
		PLAYERSTATE_NORMAL = 0,		//�ʏ���
		PLAYERSTATE_DAMAGE,			//�_���[�W���
		PLAYERSTATE_DEAHT,			//���S���	
		PLAYERSTATE_MAX				//��Ԃ̍ő吔
	}PLAYERSTATE;

	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float fLife);
	D3DXVECTOR2 *GetSize(void) { return &m_Size; }
	void SetLife(float life) { m_fLife = life; }
	void HitPlayer(float fDamage);
	static float GetLife(void) { return m_fLife; }
	static float GetMaxLife(void) { return m_fMaxLife; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	static float			  m_fLife;					//�̗�
	int						  m_nCounterState;			//��ԊǗ��̃J�E���^�[
	PLAYERSTATE				  m_state;					//�v���C���[�̏��
	int						  m_nCount;					//�J�E���^�[
	D3DXVECTOR2				  m_Size;					//�T�C�Y
	static float			  m_fMaxLife;				//�ő�̗̑�
	float					  m_fLength;				//����
	float					  m_fAngle;					//�p�x
	D3DXVECTOR3			      m_rot;					//����

};
#endif