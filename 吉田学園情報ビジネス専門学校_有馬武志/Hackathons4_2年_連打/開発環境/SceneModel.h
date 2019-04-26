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
#define MODEL_PRIORITY		(1)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneModel : public CScene
{
public:
	typedef enum
	{
		MODEL_TANKD = 0,
		MODEL_TANKU,
		//�_���W�����pobject//
		MODEL_SHOP,			//�j�󎞃V���b�v�o��
		//�_���W���������_������//
		MODEL_BOX_2,
		MODEL_BOX_1,
		MODEL_STONE,
		MODEL_STEEL,
		MODEL_STEELBIOCK,
		MODEL_MAX
	}MODEL;
	typedef enum
	{
		/*��*/	TEX_BOX_00, TEX_BOX_01, TEX_BOX_02,
		/*���ۍ�*/	TEX_BOX_10, TEX_BOX_11, TEX_BOX_12,
		/*�͗l*/	TEX_PTN_01, TEX_PTN_02, TEX_PTN_03, TEX_PTN_04,
					TEX_PTN_05, TEX_PTN_06, TEX_PTN_07, TEX_PTN_08,
		/*�I�u�W�F*/TEX_OBJ_00,
		TEXTURE_MAX
	}TEXTURE;
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

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, TEXTURE Type, DRAW_TYPE DrawType, bool bHit);
	HRESULT Init(void);
	void	Update(void);
	void	Draw(void);
	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);	//�e�N�X�`���̐���
	static void					UnLoad(void);	//�e�N�X�`���̔j��
	static void	LoadModel(MODEL model);					//���f���̐���
	static void UnLoadModel(void);				//Model���
	static void GetLength(MODEL model, float& fLengthX, float& fLengthZ);

	D3DXVECTOR3			*GetPosition(void)				{ return &m_pos; }	//����̂��߂�ނ𓾂Ȃ�
	D3DXVECTOR3			*GetRotation(void)				{ return &m_rot; }
	void		BindTexture(LPDIRECT3DTEXTURE9 *pTex)	{ m_pTex = pTex; }
	MODEL				*GetModel(void)					{ return &m_Model; }
	CScene::DRAW_TYPE	*GetDrawType(void)				{ return &m_DrawType; }


protected://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
	//���f��//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//���f���ւ̃|�C���^


	//�ϐ��錾//***********************************************************************
	//D3DXMATRIX			m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXCOLOR			*GetColor(void)		{ return &m_col; }
	LPDIRECT3DTEXTURE9	*GetTexture(void)	{ return m_pTex; }
	STATE				*GetState(void)		{ return &m_state; }
	float				*GetfCntState(void) { return &m_fCntState; }

private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	D3DXVECTOR3			m_pos;				//�ʒu
	D3DXVECTOR3			m_rot;				//����
	D3DXCOLOR			m_col;				//�F
	LPDIRECT3DTEXTURE9	*m_pTex;			//�摜
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
		USE_SHOP,	//�V���b�v�o��
		USE_DROP,	//�߂��݂̃h���b�v��
		USE_DROP00, USE_DROP01, USE_DROP02,	//���ꂼ��̃h���b�v
		USE_DROP10, USE_DROP11, USE_DROP12,	//��������
		/*�ԑ̌���*/
		USE_PTN01, USE_PTN02, USE_PTN03, USE_PTN04,
		USE_PTN05, USE_PTN06, USE_PTN07, USE_PTN08,
		/*�C������*/
		USE_PTN11, USE_PTN12, USE_PTN13, USE_PTN14,
		USE_PTN15, USE_PTN16, USE_PTN17, USE_PTN18,
		USE_MAX
	}USE;
	CSceneObjct(int nPrioryity = MODEL_PRIORITY) : CSceneModel::CSceneModel(nPrioryity) {};
	~CSceneObjct() {};

	void	Update(void);
	void	DropUninit(void);
	USE		*GetUse(void) { return &m_use; }
	CSceneModel::TEXTURE	GetTexType(USE use);
	void	DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky);		//�A�C�e���h���b�v�֐�
	bool	DropExplosion(void);										//�����h���b�v
	void	Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, TEXTURE Type, DRAW_TYPE DrawType, bool bHit, USE use)
	{
		CSceneModel::Set(pos, rot, col, model, Type, DrawType, bHit);
		m_use = use;
	}
private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	USE m_use;
	int nLife;
};

#endif
