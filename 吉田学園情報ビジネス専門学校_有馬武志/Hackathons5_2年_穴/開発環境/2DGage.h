//=============================================================================
//
// 2D�Q�[�W���� [2DGage.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _2DGAGE_H_
#define _2DGAGE_H_

#include "main.h"
#include "scene.h"
#include "2DPolygon.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define MAX_GAGE		(3)	//�Q�[�W�̍ő吔

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class C2DGage
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
		STATE_SP,
		STATE_STAMINA,
		STATE_EXP,
		STATE_STATUS,
		STATE_CHARGE,
		STATE_MAX
	}STATE;

	C2DGage() { m_p2D = NULL; };
	~C2DGage() {};

	void	Set(D3DXVECTOR3 pos, float fLengthMaxX, float flengthMaxY, float *pGage, float *pMaxGage, int nDirection, STATE state);	//�Q�[�W�Z�b�g����
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);
	void	Update(void);
protected://*****************************************************************************
		  //�ϐ��錾//***********************************************************************
private://*****************************************************************************
	D3DXCOLOR	GetGageColor(int nCntGage, bool bChange);
	bool		GetStartLength(void);
		//�ϐ��錾//***********************************************************************
	STATE	m_state;				//���
	int		m_nDirection;		//�Q�[�W�̌���
	float	*m_pGage;			//Gage�̃A�h���X
	float	*m_pMaxGage;		//Gage�̍ő�l�A�h���X
	C2D		**m_p2D;			//�����̃|�C���^
};

#endif
