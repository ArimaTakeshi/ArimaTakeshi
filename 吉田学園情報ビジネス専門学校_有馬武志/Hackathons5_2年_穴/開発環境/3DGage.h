//=============================================================================
//
// 3D�Q�[�W���� [2DGage.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _3DGAGE_H_
#define _3DGAGE_H_

#include "main.h"
#include "scene.h"
#include "3DPolygon.h"
#include "2DPolygon.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C3DGage
{
public:
	typedef enum
	{
		TEX_GAGE,
		TEXTURE_MAX
	}TEXTURE;
	typedef enum
	{
		STATE_LIFE,
		STATE_MAX
	}STATE;

	C3DGage() { m_p3D = NULL; };
	~C3DGage() {};

	void	Set(D3DXVECTOR3 &pos, float fLengthMaxX, float flengthMaxY, float &pGage, float &pMaxGage, STATE state);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
private://*****************************************************************************
	D3DXCOLOR	GetGageColor(int nCntGage, bool bChange);
	bool		GetStartLength(void);
	//�ϐ��錾//***********************************************************************
	STATE	m_state;			//���
	float	*m_pGage;			//Gage�̃A�h���X
	float	*m_pMaxGage;		//Gage�̍ő�l�A�h���X
	C3D		**m_p3D;			//�����̃|�C���^
	D3DXVECTOR3 *m_pPos;			//�ǔ�����ʒu
};

#endif
