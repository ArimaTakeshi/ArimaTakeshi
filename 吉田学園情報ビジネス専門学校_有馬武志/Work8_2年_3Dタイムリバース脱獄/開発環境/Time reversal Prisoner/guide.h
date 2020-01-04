//=============================================================================
//
// �K�C�h�̏��� [guide.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _GUIDE_H_
#define _GUIDE_H_

#include "main.h"
#include "billboord.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  CScene2D�̔h���N���X
//=====================
class CGuide : public CScene2D
{
public://�N�ł�������
	CGuide();
	~CGuide();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGuide *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int							m_nType;					//���
	D3DXVECTOR2					m_size;						//�T�C�Y
	float						m_fLength;					//����
	float						m_fAngle;					//�p�x
	D3DXVECTOR3					m_rot;						//����
	int							m_nCntBandTimer;			//�т̏o�鎞��
	int							m_nCntMapGuideTimer;		//���݂̏ꏊ�̈ē�
	bool						m_bOneCnt;
	int							m_nCntStar;					//���̓����̃J�E���^�[
	float						m_fColorCount;				//�J���[�̃J�E���^�[
	bool						m_bPressA;					//�{�^���������ꂽ���
};
#endif