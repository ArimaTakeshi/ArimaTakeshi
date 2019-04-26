//=============================================================================
//
// ���b�V������ [mesh.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene.h"
#include "Scene3D.h"
class	CCharacter;
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define BULLET_PRIORYITY (1)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CBullet : public CScene
{
public:
	CBullet(int nPrioryity = BULLET_PRIORYITY) : CScene::CScene(nPrioryity) {};
	~CBullet() {};

	static  void AtkCheck(void);
	void	Set(CCharacter *pChar, CScene *pScene, D3DXMATRIX *pMtx, int nLife, float fAtkplus, float fRange);
	HRESULT	Init(void);
	void	Update(void);

private://*****************************************************************************
	//�ϐ��錾//***********************************************************************
	CCharacter	*m_pChar;		//�������L����
	CScene		*m_pScene;		//�����ڂ̖{��
	D3DXMATRIX	*m_pMtx;	//���[���h�}�g���b�N�X
	int			m_nLife;		//�����l
	float		m_fAtkplus;		//�{��
	float		m_fRange;		//�͈�
};

#endif