#pragma once
//=============================================================================
//
// �V�[��3D���� [SceneAnim3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEANIM3D_H_
#define _SCENEANIM3D_H_

#include "main.h"
#include "scene.h"
#include "scene3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SAnim3D_PRIORITY		(3)
#define SAnim3DF_PRIORITY		(4)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneAnim3D : public CScene3D
{
public:
	typedef enum
	{
		/*����*/		TEX_EXPLOSION, TEX_FIRE_EXPLOSION,
		/*�ُ���*/	TEX_FIRE,	TEX_ICE,	TEX_LIGHTNING,
		/*�G�t�F�N�g*/	TEX_BARRIER, TEX_BEFFECT, TEX_MAGIC,
		/*�q�b�g*/		TEX_HIT,
		/*���̑�*/	TEX_GOAL, TEX_BREAK,
		/*�`���[�W*/TEX_CHARGE, TEX_CHARGE2, TEX_CHARGE3,
		/*�u�[�X�g*/TEX_BOOST,
		/*�h���t�g*/TEX_DRIFT,
		/*�X�eUP*/	TEX_STATUS_UP,
		/*�o��*/	TEX_APPEAR,
		/*��*/	TEX_HEEL, TEX_SHIELD,
		/*�����؂�ւ�*/TEX_WEAPON,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		ANIMATION_NORMAL = 0,
		ANIMATION_LOOP,
		ANIMATION_MAX
	}ANIMATION;
	CSceneAnim3D(int nPrioryity = SAnim3D_PRIORITY) : CScene3D::CScene3D(nPrioryity) { };
	~CSceneAnim3D() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state);
	HRESULT Init(void);
	void	Update(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//�e�N�X�`���̐���
	static void					UnLoad(void);	//�e�N�X�`���̔j��
	static void					BreakPolygon(STATE state);

private://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^

	//�ϐ��錾//***********************************************************************
	int			m_nCntAnim;			//Animation�̃J�E���g
	int			m_nPtnAnim;			//�w�肳�ꂽ���W�ŕ\��
	int			m_nPtnHeight;		//�摜�̏c�̕�����
	int			m_nPtnWide;			//�摜�̉��̕�����
	int			m_nPtnSpeed;		//Animation���x
	ANIMATION	m_animation;		//�g�p���@
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneAnimEffect : public CSceneAnim3D
{
public:

	CSceneAnimEffect(int nPrioryity = SAnim3D_PRIORITY) : CSceneAnim3D::CSceneAnim3D(nPrioryity) { m_pPos = NULL; m_pScene = NULL; };
	~CSceneAnimEffect() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
		TEXTURE nType, DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene);
	void Update(void);

	CScene		*m_pScene;
	D3DXVECTOR3 *m_pPos;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneFrontAnim : public CSceneAnim3D
{
public:

	CSceneFrontAnim(int nPrioryity = SAnim3DF_PRIORITY) : CSceneAnim3D::CSceneAnim3D(nPrioryity) { SetObjType(OBJTYPE_EFFECT); };
	~CSceneFrontAnim() {};
};
#endif
