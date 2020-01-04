//=============================================================================
//
// �������� [distance.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "distance.h"
#include "billnumber.h"
#include "player.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DISTANCE_CENTER_WIDTH	(SCREEN_WIDTH / 2)		// X�̒��S���W
#define DISTANCE_SPACE			(5.0f)					// �����Ɛ����̊Ԃ̃T�C�Y
#define DISTANCE_POSITION_Y		(70.0f)					// �^�C�}�[��Y���W

//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
int CDistance::m_nDistance = 0;

//=============================================================================
// ��������
//=============================================================================
CDistance *CDistance::Create(D3DXVECTOR3 pos)
{
	CDistance *pDistance = NULL;

	//NULL�`�F�b�N
	if (pDistance == NULL)
	{//���I�m��
		pDistance = new CDistance;

		//NULL�`�F�b�N
		if (pDistance != NULL)
		{
			//�ʒu�̐ݒ�
			pDistance->m_pos = pos;
			//����������
			pDistance->Init();
		}
	}

	return pDistance;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDistance::CDistance(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nDistanceCount = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDistance::~CDistance()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CDistance::Init(void)
{
	//�r���{�[�h�����̃e�N�X�`���̓ǂݍ���
	CBillNumber::Load();

	m_nDistance = 0;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apBillNumber[nCntTime] = new CBillNumber;
		m_apBillNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - DISTANCE_SPACE * nCntTime), m_pos.y, m_pos.z));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CDistance::Uninit(void)
{
	//�r���{�[�h�����̃e�N�X�`���̔j��
	CBillNumber::Unload();

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apBillNumber[nCntTime]->Uninit();
		delete m_apBillNumber[nCntTime];
		m_apBillNumber[nCntTime] = NULL;
	}

	//�폜
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CDistance::Update(void)
{
	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();
	//D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

	if (GameMode == CManager::MODE_GAME)
	{//�`���[�g���A���w���\��
		m_nDistanceCount++;

		//if (m_nDistanceCount % 60 == 0)
		{// 1�b���Ƃɉ��Z
			//m_nDistance++;
		}

		//�����𑪂邽�߂̎O�p�`�̎�
		//atan2f(-m_pos.x - -PlayerPos.x, -m_pos.z - -PlayerPos.z) + D3DX_PI;

		if (m_nDistance >= 0)
		{
			//m_nDistance = (m_pos.x - PlayerPos.x) + (m_pos.z - PlayerPos.z);
		}
		else if (m_nDistance <= -1)
		{
			//m_nDistance = (m_pos.x - PlayerPos.x) + (m_pos.z - PlayerPos.z)* -1;
		}

		int nTexData = m_nDistance;
		for (int nCntDistance = 0; nCntDistance < DISTANCE_MAX; nCntDistance++)
		{// �e�N�X�`���ɔ��f
			m_apBillNumber[nCntDistance]->SetBillNumber(nTexData);
			nTexData /= 10;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CDistance::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		m_apBillNumber[nCntTime]->Draw();
	}
}