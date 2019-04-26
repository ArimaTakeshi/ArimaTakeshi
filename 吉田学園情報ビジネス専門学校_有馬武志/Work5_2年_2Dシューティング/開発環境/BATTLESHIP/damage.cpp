//=============================================================================
//
// �_���[�W���� [damage.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "damage.h"
#include "number.h"
#include "player.h"
#include <string>
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SIZE_X		(SCREEN_WIDTH)
#define SIZE_Y		(SCREEN_HEIGHT)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CNumber *CDamage::m_apNumber[MAX_DAMAGE_NUMBER] = {};
int CDamage::m_nDamage = 0;

//=============================================================================
//�f�t�H���g�R���X�g���N�^
//=============================================================================
CDamage::CDamage() : CScene(5)//�D��D�ʃC�j�V�����C�Y
{
	m_nDamage = 0;
	m_nCount = 0;
	m_fLife = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
//�f�X�g���N�^
//=============================================================================
CDamage::~CDamage()
{

}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CDamage::Init(void)
{
	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		m_pos = pPlayer->GetPosition();
	}

	//�����̃^�C�v������
	CNumber::SetType(CNumber::TYPE_DAMAGE);

	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		//if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = new CNumber;

			//if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (nCnt * 20.0f), m_pos.y + 10.0f, 0));
			}
		}
	}

	return S_OK;
}
//=============================================================================
// �|���S���̏I������
//=============================================================================
void CDamage::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = {};
		}
	}

	//�������g�̔j��
	Release();
}
//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CDamage::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
	if (m_nCount >= 15)
	{
		//�������g�̔j��
		Release();
	}
	else if (m_nCount == 16)
	{
		m_nCount = 0;
	}

	m_nCount++;
}
//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CDamage::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
//�|���S���̐�������
//=============================================================================
CDamage *CDamage::Create(void)
{
	CDamage *pDamage = {};

	if (pDamage == NULL)
	{//NULL��������

	 //�������̓��I�m��
		pDamage = new CDamage;

		if (pDamage != NULL)
		{//NULL����Ȃ�������
			//�|���S���̏���������
			pDamage->Init();
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
	}

	return pDamage;
}
//==============================================================================
// �X�R�A�̉��Z
//==============================================================================
void CDamage::AddDamage(int nValue)
{
	m_nDamage = nValue;		//�X�R�A����

	int nDamage = m_nDamage;

	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->SetNumber(nDamage);
		nDamage /= 10;
	}
}
//==============================================================================
// �X�R�A�̏��
//==============================================================================
int CDamage::GetDamage(void)
{
	return m_nDamage;
}