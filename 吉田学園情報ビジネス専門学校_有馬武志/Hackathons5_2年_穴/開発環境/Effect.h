//=============================================================================
//
// �V�[������ [scene2D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SLEffect_PRIORITY		(2)

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CLineEffect : public CScene
{
public:
	typedef enum
	{
		TYPE_FIRE,
		TYPE_MAX
	}TYPE;
	CLineEffect(int nPrioryity = SLEffect_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_pmtxWorld = NULL;
		m_bDelete = NULL;
	};
	~CLineEffect() {};

	void	Set(D3DXMATRIX &mtxWorld, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fInterval, bool &bDelete, TYPE type);
	HRESULT Init(void);
	void	Update(void);
	D3DXVECTOR3	ChangePos(void);
	void MoveSet(D3DXVECTOR3 &pos);
	void SetEffect(void);
	void StartEffect(void);
	void EndEffect(void);
	static void Delete(void);

protected://*****************************************************************************
private://*****************************************************************************
	D3DXVECTOR3 SetMtxWorld(void);
		//�ϐ��錾//***********************************************************************
	TYPE			m_Type;			// �Z�b�g���
	D3DXMATRIX		*m_pmtxWorld;	//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_posold;		// ���g�O�̈ʒu
	D3DXVECTOR3		m_pos;			// ���_����̊p�x�v���X�l
	D3DXVECTOR3		m_rot;			// ���_����̊p�x�v���X�l
	float			m_fLength;		//�i�񂾋����ۑ�
	float			m_fInterval;	//�Z�b�g�܂ł̊Ԋu
	bool			*m_bDelete;		//�����锻��
};

#endif
