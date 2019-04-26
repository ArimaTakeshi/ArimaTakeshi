//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "effect.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\effect001.jpg"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2	"data\\TEXTURE\\effect002.jpg"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULLET_X		(30)									//���̑傫��
#define	BULLET_Y		(30)									//�c�̑傫��
#define DAMAGE			(1)										//�_���[�W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEffect::m_pTexture[MAX_DATA] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CEffect::CEffect() : CScene2D(2)//�D��D�ʃC�j�V�����C�Y
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_fRadius = 0.0f;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(void)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	//m_pos����
	D3DXVECTOR3 Effectpos = CScene2D::GetPosition();

	//�G�t�F�N�g�̈ʒu�ƃT�C�Y
	CScene2D::Set(Effectpos, D3DXVECTOR2(m_Size.x, m_Size.y));

	switch (m_Type)
	{
	case EFFECTTYPE_NOLMAL:
		//���a��傫�����Ă���
		m_fRadius--;

		//���a�̍X�V
		CScene2D::SetRadius(Effectpos, m_fRadius);
		break;
	case EFFECTTYPE_RIPPLE:
		//���a��傫�����Ă���
		m_fRadius--;

		//���a�̍X�V
		CScene2D::SetRadius(Effectpos, m_fRadius);
		break;
	}

	//���C�t�����炵�Ă���
	m_nLife--;

	if (m_nLife <= 0)
	{//���C�t��0�ȉ��̏ꍇ
		//�G�t�F�N�g�̏I������
		CEffect::Uninit(); return;
	}
	else if (Effectpos.y < m_Size.y || Effectpos.y > SCREEN_HEIGHT - m_Size.y || Effectpos.x < m_Size.x || Effectpos.x > SCREEN_WIDTH - m_Size.x)
	{//��ʊO�̏ꍇ
	 //�G�t�F�N�g�̏I������
		CEffect::Uninit(); return;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();
	
	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//===============================================================================
//�@�N���G�C�g
//===============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos,D3DXVECTOR2 size,float fRadiusint,int nLife,EFFECTTYPE nType,int nTexType)
{
	CEffect *pEffect = NULL;

	//NULL�`�F�b�N
	if (pEffect == NULL)
	{//�������̓��I�m��

		pEffect = new CEffect;

		if (pEffect != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pEffect->Init();
			//�e�N�X�`�������蓖�Ă�
			pEffect->BindTexture(m_pTexture[nTexType]);
			//���C�t����
			pEffect->m_nLife = nLife;
			//�T�C�Y�̕ێ�
			pEffect->m_Size = size;
			//���a�̊��蓖��
			pEffect->m_fRadius = fRadiusint;
			//��ނ̑��
			pEffect->m_Type = nType;
			//�G�t�F�N�g�̂�ݒu
			pEffect->SetPosition(pos);
		}
	}
	return pEffect;
}

//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CEffect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[1]
	);

	return S_OK;
}

//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CEffect::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}