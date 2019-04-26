//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{//���g�N���A
	CManager::GetLight() = this;
}
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::~CLight()
{//���g�N���A

}
//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::Init(void)
{
	for (int nCount = 0; nCount < MAX_TYPE; nCount++)
	{
		m_col[nCount] = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
		m_fStrength[nCount] = 0.0f;
		m_fGoal[nCount] = 0.0f;
	}
	//Set();
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::Uninit(void)
{
	delete this;
	CManager::GetLight() = NULL;
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::Update(void)
{
	for (int nCount = 0; nCount < MAX_TYPE; nCount++)
	{
		if (m_fFrame[nCount] > 0.0f)
		{//���C�g�̏��������K�v
			m_fFrame[nCount] -= 1.0f;
			if (m_fFrame[nCount] <= 0.0f)
			{
				m_fFrame[nCount] = 0.0f;
				m_fGoal[nCount] = 0.0f;
			}
		}
		m_col[nCount].r += (0.8f - m_col[nCount].r) * 0.1f / FRAME_SPEED;
		m_col[nCount].g += (0.8f - m_col[nCount].g) * 0.1f / FRAME_SPEED;
		m_col[nCount].b += (0.8f - m_col[nCount].b) * 0.1f / FRAME_SPEED;
		m_fStrength[nCount] += (m_fGoal[nCount] - m_fStrength[nCount]) * 0.1f / FRAME_SPEED;
	}
	//if (CManager::GetInputKey()->GetTrigger(DIK_L)) { SetStrength(0.5f, 30); }
	//if (CManager::GetInputKey()->GetTrigger(DIK_K)) { m_col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CLight::Set(int nNumber)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXVECTOR3			vecDir;
	int					nCntLight;
	D3DXCOLOR			WKcol;

	for (nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		WKcol = D3DXCOLOR(m_col[nNumber].r + m_fStrength[nNumber], 
			m_col[nNumber].g + m_fStrength[nNumber], 
			m_col[nNumber].b + m_fStrength[nNumber], 1.0f);
		if (WKcol.r > 1.0f) { WKcol.r = 1.0f; }
		if (WKcol.g > 1.0f) { WKcol.g = 1.0f; }
		if (WKcol.b > 1.0f) { WKcol.b = 1.0f; }
		//WKcol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		m_light[nCntLight].Diffuse = WKcol;

		// ���C�g�̕����̐ݒ�
		if (nCntLight == 0) { vecDir = D3DXVECTOR3(0.3f, 0.65f, -0.4f); }
		if (nCntLight == 1) { vecDir = D3DXVECTOR3(-0.5f, -0.2f, 0.4f); }
		if (nCntLight == 2) { vecDir = D3DXVECTOR3(0.4f, -0.8f, 1.0f); }

		D3DXVec3Normalize(&vecDir, &vecDir);				//���K���ɂ���
		m_light[nCntLight].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}
//=============================================================================
// ���̋����ݒ菈��
//=============================================================================
void CLight::SetStrength(float fGoal, float fFrame, int nNumber)
{
	m_fGoal[nNumber] = fGoal;
	m_fFrame[nNumber] = fFrame * FRAME_SPEED;
}

