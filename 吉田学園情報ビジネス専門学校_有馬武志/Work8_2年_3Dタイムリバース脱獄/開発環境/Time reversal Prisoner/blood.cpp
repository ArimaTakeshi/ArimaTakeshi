//=============================================================================
//
// ���̏��� [blood.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "blood.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "mesh.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BLOOD_TEXTURE_NAME_1	"data\\TEXTURE\\blood.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define BLOOD_MAX_SIZE_X		(50)								//���̍L����ő�͈̔�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3DTEXTURE9	CBlood::m_pTexture[MAX_BILLBOORD_TEX] = {};
float CBlood::m_fMeshHeight = 0.0f;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CBlood::CBlood() : CScene3D(SHADOW_PRIOTITY, CScene::OBJTYPE_BLOOD)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CBlood::~CBlood()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBlood::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::Init();

	//����̓r���{�[�h���G�t�F�N�g���̔���
	CScene3D::SetTypeNumber(CScene3D::TYPE_BLOOD);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBlood::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CBlood::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	D3DXVECTOR3 pos;

	pos = m_pos;

	if (m_fDepth < BLOOD_MAX_SIZE_X)
	{// �ړI�̑傫�����傫�����
	 // �k��������
		m_fDepth += 0.05f;
	}
	if (m_fWidth < BLOOD_MAX_SIZE_X)
	{// �ړI�̑傫�����傫�����
	 // �k��������
		m_fWidth += 0.05f;
	}

	//�e�ƃ��b�V���̔���
	CBlood::CollisitionMesh();

	CScene3D::SetGroundPosSize(pos,D3DXVECTOR2(m_fWidth, m_fDepth));
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBlood::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCOLOR col[4];

	col[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	col[1] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	col[2] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	col[3] = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	CScene3D::Draw();

	CScene3D::SetColor(&col[0]);

}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CBlood * CBlood::Create(D3DXVECTOR3 pos, float fWidth, float fDepth,int nTexType)
{
	CBlood *pBlood = NULL;

	//NULL�`�F�b�N
	if (pBlood == NULL)
	{//�������̓��I�m��

		pBlood = new CBlood;

		if (pBlood != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pBlood->Init();
			//�e�N�X�`���̊��蓖��
			pBlood->BindTexture(m_pTexture[nTexType]);
			//�ʒu����T�C�Y���o��
			pBlood->SetGroundPosSize(pos, D3DXVECTOR2(fWidth, fDepth));
			//�����̐ݒ�
			pBlood->m_fWidth = fWidth;
			//���s�̐ݒ�
			pBlood->m_fDepth = fDepth;
			//�ʒu�̊��蓖��
			pBlood->SetPosition(pos);
			//�ʒu�̐ݒ�
			pBlood->m_pos = pos;
		}
	}

	return pBlood;
}
//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void CBlood::CollisitionMesh(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(MESH_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_MESH)
			{
				//�������擾
				m_fMeshHeight = m_pos.y;
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void CBlood::SetPositionShadow(D3DXVECTOR3 pos)
{
	//�ʒu�𓮂���
	m_pos = pos;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CBlood::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BLOOD_TEXTURE_NAME_1, &m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CBlood::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD_TEX; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
