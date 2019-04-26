//=============================================================================
//
// 2D�Q�[�W���� [2DGage.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "3DPolygon.h"
#include "2DGage.h"
#include "3DGage.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	C3DGage::m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^

//==================================================================================================//
//    * �Q�[�W�̃Z�b�g�֐� *
//==================================================================================================//
void C3DGage::Set(D3DXVECTOR3 &pos, float fLengthMaxX, float flengthMaxY, float &pGage, float &pMaxGage, STATE state)	//�Q�[�W�Z�b�g����
{
	m_pPos = &pos;
	m_pGage = &pGage;			//�Q�[�W�̌��݂̒l�̃A�h���X
	m_pMaxGage = &pMaxGage;		//�Q�[�W�̍ő�l�̃A�h���X
	m_state = state;

	if (m_p3D != NULL)
	{//���Ƀ��������g���Ă���Ȃ�
		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//����int���폜
			delete m_p3D[nCount];
		}//�{�̍폜
		delete[] m_p3D;
		m_p3D = NULL;
	}
	m_p3D = new C3D*[MAX_GAGE];
	if (m_p3D != NULL)
	{//�����ł����I
		D3DXCOLOR	col;
		float		fLengthX;

		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{//��������]
			col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			m_p3D[nCount] = new C3D;
			m_p3D[nCount]->Init();
			col = GetGageColor(nCount, true);

			//�Z�b�g����
			if (m_p3D != NULL)
			{//�����ł����I
				if (GetStartLength() || nCount == 0)	{ fLengthX = fLengthMaxX; }
				else					{ fLengthX = 0.0f; }
				m_p3D[nCount]->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), col, D3DXVECTOR3(fLengthX, flengthMaxY, 0.0f),
					0, 1, 1, CScene::DRAW_TYPE_NORMAL, CScene::TEX_Gage, true);
				m_p3D[nCount]->SetGage(fLengthX, fLengthMaxX);		//�Q�[�W�^�ɕϊ�
				//m_p3D[nCount]->BindTexture(Load(TEX_GAGE));	//�摜�\��t��
			}
		}
	}
}
//=============================================================================
// �Q�[�W�̏���������
//=============================================================================
HRESULT  C3DGage::Init(void)
{
	return S_OK;
}
//=============================================================================
// �Q�[�W�̏I������
//=============================================================================
void C3DGage::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p3D[nCount]->Uninit();
	}
	delete this;
}

//=============================================================================
// �Q�[�W�̍X�V����
//=============================================================================
void C3DGage::Update(void)
{
	//Life�Q�[�W�̐ݒ�
	if (m_p3D[2] != NULL && m_p3D[1] != NULL)
	{
		float fLengthX_2 = m_p3D[2]->GetLength().x;
		float fLengthX_1 = m_p3D[1]->GetLength().x;
		float fLengthX_0 = m_p3D[0]->GetLength().x;
		float WKfLength;

		float fGage = m_p3D[0]->GetLength().x * ((float)m_pGage[0] / (float)m_pMaxGage[0]);

		//2�̍X�V
		if (fGage < fLengthX_2)
		{ //��_���@��C��
			m_p3D[2]->SetGage(fGage, fLengthX_0);
		}
		else if (fGage > fLengthX_2)
		{ //�񕜁@�������
			WKfLength = (fGage - fLengthX_2) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_2 += WKfLength;
			if (fLengthX_2 > fGage) { fLengthX_2 = fGage; }
			m_p3D[2]->SetGage(fLengthX_2, fLengthX_0);
		}

		//1�̍X�V
		if (fGage > fLengthX_1)
		{//�񕜁@��C��
			m_p3D[1]->SetColor(GetGageColor(1, false));
			m_p3D[1]->SetGage(fGage, fLengthX_0);
		}
		else if (fGage < fLengthX_1)
		{//��_���@�������
			m_p3D[1]->SetColor(GetGageColor(1, true));
			WKfLength = (fLengthX_1 - fGage) * 0.05f;
			if (WKfLength < 0.05f) { WKfLength = 0.05f; }
			fLengthX_1 -= WKfLength;
			if (fLengthX_1 < fGage) { fLengthX_1 = fGage; }
			m_p3D[1]->SetGage(fLengthX_1, fLengthX_0);
		}

		for (int nCount = 0; nCount < MAX_GAGE; nCount++)
		{
			m_p3D[nCount]->GetPosition() = m_pPos[0] + D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		}
	}
}

//=============================================================================
// �Q�[�W�̕`�揈��
//=============================================================================
void C3DGage::Draw(void)
{
	for (int nCount = 0; nCount < MAX_GAGE; nCount++)
	{
		m_p3D[nCount]->Draw();
	}
}
//=============================================================================
// ��Ԃɂ��Q�[�W���̃J���[�Ԃ�����
//=============================================================================
D3DXCOLOR	C3DGage::GetGageColor(int nCntGage, bool bChange)
{
	switch (m_state)
	{
	case STATE_LIFE:
		switch (nCntGage)
		{
		case 0: return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		case 1: 
			if (bChange) { return D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f); }
			else		 { return D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
		case 2: return D3DXCOLOR(0.32f, 1.0f, 0.19f, 1.0f);
		}
			break;
	}

	return D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
}
//=============================================================================
// ��Ԃɂ��Q�[�W�̏����l����
//=============================================================================
bool	C3DGage::GetStartLength(void)
{
	switch (m_state)
	{
	case STATE_LIFE:	return true;
	}
	return true;
}
