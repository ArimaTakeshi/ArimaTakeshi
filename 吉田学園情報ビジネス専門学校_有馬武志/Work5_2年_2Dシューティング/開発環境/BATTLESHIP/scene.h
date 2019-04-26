//=============================================================================
//
// ���C������ [scene.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_DATA		(500)		//�o�����̂̍ő吔
#define NUM_PRIORITY	(8)			//�D�揇�ʂ̍ő吔

//=====================
//	   ��{�N���X
//=====================
class CScene
{
public://�N�ł�������
	typedef enum
	{
		OBJTYPE_NONE = 0,		//�g���Ă��Ȃ����
		OBJTYPE_PLAYER,			//�v���C���[
		OBJTYPE_ENEMY,			//�G
		OBJTYPE_BULLET,			//�e
		OBJTYPE_EXPLOSION,		//����
		OBJTYPE_BG,				//�w�i
		OBJTYPE_FRAM,			//�g
		OBJTYPE_GAN,			//����
		OBJTYPE_DAMAGE,			//�_���[�W
		OBJTYPE_SCORE,			//�X�R�A
		OBJTYPE_2DOBJECT,		//�I�u�W�F�N�g
		OBJTYPR_LIFE,			//�̗�
		OBJTYPE_FADE,			//�t�F�[�h
		OBJTYPE_MAX,			//�ő吔
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void SetObjType(OBJTYPE ObjType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriNumber, int nIdx);
	static void SetUpdatePri(int nUpdatePri);

private://�l�ł̂ݎg��
	static CScene *	m_apScene[NUM_PRIORITY][MAX_DATA];
	static int		m_nNumAll;				//�G�̑���
	int				m_nID;					//�ԍ�
	OBJTYPE			m_ObjType;				//�I�u�W�F�N�g�̎��
	int				m_nPriority;			//�D�揇�ʂ̔ԍ�
	static int      m_nUpdatePri;

protected:
	void Release(void);
};
#endif