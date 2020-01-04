//=============================================================================
//
// �X�|�b�g���C�g�̏��� [spotlight.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "spotlight.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "mesh.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	SPOTLIGHT_TEXTURE_NAME_1	"data\\TEXTURE\\Bullet000.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define SPOTLIGHT_MAX_SIZE_X		(50)								//�X�|�b�g���C�g�̍L����ő�͈̔�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3DTEXTURE9	CSpotLight::m_pTexture[MAX_BILLBOORD_TEX] = {};
float CSpotLight::m_fMeshHeight = 0.0f;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CSpotLight::CSpotLight() : CScene3D(SPOTLIGHT_PRIOTITY, CScene::OBJTYPE_SPOTLIGHT)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bSpotLightIn = false;
	m_nSwingTime = 0;
	m_fSwing = 0.0f;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CSpotLight::~CSpotLight()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSpotLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::Init();

	//����̓r���{�[�h���G�t�F�N�g���̔���
	CScene3D::SetTypeNumber(CScene3D::TYPE_SPOTLIGHT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSpotLight::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CSpotLight::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	//���C�g��U�铮��
	if (m_nSwingTime < 120)
	{
		m_fSwing -= 0.09f;
	}
	else if (m_nSwingTime < 240)
	{
		m_fSwing += 0.09f;
	}
	else if (m_nSwingTime >= 240)
	{
		m_nSwingTime = 0;
	}
	
	//�����𓮂���
	m_pos.x += m_fSwing;

	//�J�E���g����
	m_nSwingTime++;

	//�e�ƃ��b�V���̔���
	CSpotLight::CollisitionMesh();

	CScene3D::SetPosition(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));

	CDebugProc::Print("m_bSpotLightIn = %s\n", m_bSpotLightIn ? "true" : "false");

}
//=============================================================================
// �`�揈��
//=============================================================================
void CSpotLight::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�t�H�O���g�p���Ȃ�
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	CScene3D::Draw();

	//�t�H�O���g�p����
	pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CSpotLight * CSpotLight::Create(D3DXVECTOR3 pos, float fWidth, float fDepth,int nTexType, CEnemy *pEnemy)
{
	CSpotLight *pBlood = NULL;

	//NULL�`�F�b�N
	if (pBlood == NULL)
	{//�������̓��I�m��

		pBlood = new CSpotLight;

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

			pBlood->m_pEnemy = pEnemy;
		}
	}

	return pBlood;
}
//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void CSpotLight::CollisitionMesh(void)
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
void CSpotLight::SetPositionSpotLight(D3DXVECTOR3 pos)
{
	//�ʒu�𓮂���
	m_pos = pos;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CSpotLight::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, SPOTLIGHT_TEXTURE_NAME_1, &m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CSpotLight::UnLoad(void)
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
//=============================================================================
// ���̓����蔻��
//=============================================================================
void CSpotLight::CollisionSpotLight(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	// pos���擾
	D3DXVECTOR3 SpotLightPos = CScene3D::GetPosition();
	D3DXVECTOR3 SpotLightRot = CScene3D::GetRotation();
	D3DXVECTOR3 SpotLightMove = CScene3D::GetMove();
	D3DXVECTOR2 SpotLightSize = CScene3D::GetSize();
	bool		bCheck = false;

	CSound *pSound = CManager::GetSound();

	if (pPos->x <= SpotLightPos.x + SpotLightSize.x
		&& pPos->x >= SpotLightPos.x - SpotLightSize.x)
	{// ���Ɠ���z���ɑ��݂��Ă���
		if (pPos->z <= SpotLightPos.z + SpotLightSize.y
			&& pPos->z >= SpotLightPos.z - SpotLightSize.y)
		{// ���Ɠ���x���ɑ��݂��Ă���
			if (pPos->y <= SpotLightPos.y)
			{// ���ɐG��Ă���
				pMove->x += SpotLightMove.x;
				pMove->y += SpotLightMove.y;
				pMove->z += SpotLightMove.z;
				bCheck = true;

				m_pEnemy->SetLightIn(true);
				m_bSpotLightIn = true;
			}
		}
	}

	if (!bCheck)
	{
		m_pEnemy->SetLightIn(false);
		m_bSpotLightIn = false;
	}
}
