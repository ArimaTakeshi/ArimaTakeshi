#pragma once
//=============================================================================
//
// �V�[��3D���� [scene3D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SCENEMODEL_H_
#define _SCENEMODEL_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_PRIORITY		(0)
#define SATELLITE_PRIORITY			(2)			//���b�V���̗D�揇��

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneModel : public CScene
{
public:
	typedef enum
	{
		//���[���@����
		MODEL_FENCE,	//��
		MODEL_STEEL,	//�S��
		//���[���@���S
		MODEL_STONE,	//��
		MODEL_STEEL_B,	//�S����
		//���[�h
		MODEL_BOX,		//�ؔ�
		MODEL_STONE_S,	//����
		//�G���g�����X

		MODEL_Gate,	//�Q�[�g
		MODEL_ICE,	//�X
		MODEL_SATELLITE,	//�q��
		MODEL_POS_MAG,	//���ʎ��j(�{��)
		MODEL_POS_NEE,	//���ʎ��j(�j)
		MODEL_Earth,	//�n��

		MODEL_Room,	//
		MODEL_Frame,	//
		MODEL_FrameV,	//
		MODEL_FrameC,	//

		MODEL_MAX
	}MODEL;
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_FADE,
		STATE_FADEIN,
		STATE_FADEOUT,
		STATE_MAX
	}STATE;
	CSceneModel(int nPrioryity = MODEL_PRIORITY) : CScene::CScene(nPrioryity) {};
	~CSceneModel() {};

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit);
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static void	LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex);			//���f���̐���
	static void UnLoadModel(void);											//Model���
	static void GetLength(MODEL model, D3DXVECTOR3 &length);				//���f���̒����擾
	static float GetHeight(MODEL model);									//���f���̒n�ʂ���̍����擾
	static void SetShadow(void);

	void	SetMtx(void);									//�}�g���b�N�X�̐ݒ�
	void	PlusMtx(D3DXVECTOR3 &move);						//�}�g���b�N�X�̐ݒ�

	D3DXVECTOR3			&GetPosition(void)				{ return m_pos; }
	D3DXVECTOR3			&GetRotation(void)				{ return m_rot; }
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex)	{ m_pTex = pTex; }
	CScene::DRAW_TYPE	&GetDrawType(void)				{ return m_DrawType; }
	MODEL				&GetModel(void)					{ return m_Model; }
	D3DXMATRIX			&GetmtxWorld(void)				{ return m_mtxWorld; }

protected://*****************************************************************************
	//���f��//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//���f���ւ̃|�C���^


	//�ϐ��錾//***********************************************************************
	D3DXCOLOR			&GetColor(void)		{ return m_col; }
	LPDIRECT3DTEXTURE9	&GetTexture(void)	{ return m_pTex; }
	STATE				&GetState(void)		{ return m_state; }
	float				&GetfCntState(void) { return m_fCntState; }

private://*****************************************************************************
	void	DrawModel(void);
	//�ϐ��錾//***********************************************************************
	D3DXMATRIX			m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_rot;				//����
	D3DXCOLOR			m_col;				//�F
	LPDIRECT3DTEXTURE9	m_pTex;				//�摜
	MODEL				m_Model;			//���f��
	CScene::DRAW_TYPE	m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	STATE				m_state;			//�g�p���@
	float				m_fCntState;		//STATE�Ǘ��p
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneObjct : public CSceneModel
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		USE_MAX
	}USE;
	CSceneObjct(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CSceneObjct() {};

	void	Update(void);
	void	DropUninit(void);
	USE		*GetUse(void) { return &m_use; }
	void	DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky);		//�A�C�e���h���b�v�֐�
	bool	DropExplosion(void);										//�����h���b�v
	void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use);
	static bool CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	bool Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static void SetObjField(void);
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	USE m_use;
	float fLife;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSatellite : public CSceneModel
{
public:
	CSatellite(int nPrioryity = SATELLITE_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CSatellite() {};
	void	Set(D3DXMATRIX &pMtx, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, D3DXVECTOR3 &move, float &fFrame, float fRot, float fDistance, bool &bDelete);
	void	Update(void);
	void	Draw(void);

	static void Delete(void);
	static void ReSet(void);
	float &GetfRot(void) { return m_fRot; }
	D3DXMATRIX *&GetpMtx(void) { return m_pMtx; }
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	D3DXMATRIX	*m_pMtx;		//�ǔ�����ʒu
	D3DXVECTOR3 *m_pmove;		//�ړ���
	float		*m_pfFrame;		//�t���[����
	bool		*m_bDelete;		//�����锻��

	float		m_fRot;			//���g�̊p�x
	float		m_fMoveRot;		//�h���p�̊p�x
	float		m_fDistance;	//����鋗��
};
#endif
