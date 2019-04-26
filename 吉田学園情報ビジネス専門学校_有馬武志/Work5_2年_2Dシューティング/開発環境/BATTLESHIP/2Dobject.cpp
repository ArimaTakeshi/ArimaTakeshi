//=============================================================================
//
// �I�u�W�F�N�g�̏��� [2Dobject.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "2Dobject.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "bullet.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1					"data\\TEXTURE\\iwa.png"	//�ǂݍ��ރe�N�X�`���t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 C2DObject::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
C2DObject::C2DObject()
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPlayerLife = 0;
	m_nLife = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
C2DObject::~C2DObject()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT C2DObject::Init(void)
{
	CScene2D::Init();

	//��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_2DOBJECT);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void C2DObject::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void C2DObject::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�I���I�t�̐؂�ւ�
	bool bOnOff = false;

	//�ʒu����
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();

	//NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		//�v���C���[�̗̑͂������Ă���
		m_fPlayerLife = pPlayer->GetLife();
	}

	//�ړ�����
	if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
	{//���ɍs��
		pos.x += 0.8f;
	}
	else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
	{//�E�ɍs��
		pos.x -= 0.8f;
	}

	//�I�u�W�F�N�g�̈ʒu
	CScene2D::Set(pos, m_Size);

	//���ʂ��m�F
	for (int nCnPri = 0; nCnPri < NUM_PRIORITY; nCnPri++)
	{
		//�I�u�W�F�N�g�̑������m�F
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene2D *pScene;

			pScene = (CScene2D*)CScene::GetScene(nCnPri, nCntScene);

			if (pScene != NULL)
			{//NULL�`�F�b�N
			 //���[�J���ō��
				CScene::OBJTYPE ObjType;

				//�I�u�W�F�N�g�̃V�[�����擾
				ObjType = pScene->GetObjType();

				//�����蔻��
				if (ObjType == CScene::OBJTYPE_PLAYER)
				{//���������v���C���[�̏�����������

					//�^���G�l�~�[�ɓ����
					CPlayer *pPlayer = (CPlayer*)pScene;

					if (pScene->GetPosition().x - pPlayer->GetSize()->x < pos.x && pScene->GetPosition().x + pPlayer->GetSize()->x > pos.x &&
						pScene->GetPosition().y - pPlayer->GetSize()->y < pos.y && pScene->GetPosition().y + pPlayer->GetSize()->y > pos.y)
					{//�����蔻��
						//1��̂ݓ���
						if (bOnOff == false)
						{
							//�̗͂̍ő啪���Ȃ���
							pPlayer->HitPlayer(m_fPlayerLife);
							//0�ȉ��̏ꍇ0�������Ă���ȉ������Ȃ�
							m_fPlayerLife = 0;
							//�����̐���
							CExplosion::Create(pos, D3DXVECTOR2(20.0f, 20.0f), 0);

							bOnOff = true;
						}
					}
				}
				else if (ObjType == CScene::OBJTYPE_ENEMY)
				{//���������G�̏�����������

					//�^���G�l�~�[�ɓ����
					CEnemy *pEnemy = (CEnemy*)pScene;

					if (pScene->GetPosition().x - pEnemy->GetSize()->x < pos.x && pScene->GetPosition().x + pEnemy->GetSize()->x > pos.x &&
						pScene->GetPosition().y - pEnemy->GetSize()->y < pos.y && pScene->GetPosition().y + pEnemy->GetSize()->y > pos.y)
					{//�����蔻��
						//�G�̏I������
						pEnemy->Uninit();
						//�����̐���
						CExplosion::Create(pos, D3DXVECTOR2(30.0f, 30.0f), 0);
					}
				}
			}
		}
	}

	//�₩��̃_���[�W���v���C���[�ɓ����
	pPlayer->SetLife(m_fPlayerLife);
}
//=============================================================================
// �`�揈��
//=============================================================================
void C2DObject::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
C2DObject * C2DObject::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType,int nLife)
{
	C2DObject *p2DObject = NULL;

	//NULL�`�F�b�N
	if (p2DObject == NULL)
	{//�������̓��I�m��

		p2DObject = new C2DObject;

		if (p2DObject != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			p2DObject->Init();
			//��ނ̊��蓖��
			p2DObject->m_nType = nType;
			//�̗͂̊��蓖��
			p2DObject->m_nLife = nLife;
			//�e�N�X�`�������蓖�Ă�
			p2DObject->BindTexture(m_pTexture[nType]);
			//�e��ݒu
			p2DObject->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			p2DObject->m_Size = size;
		}
	}
	return p2DObject;
}
//===============================================================================
// �I�u�W�F�N�g�̃_���[�W����
//===============================================================================
void C2DObject::HitObject(int nDamage)
{
	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];

	//m_pos����
	D3DXVECTOR3 Objectpos = CScene2D::GetPosition();

	//�e�̈ʒu�ƃT�C�Y
	CScene2D::SetPosition(Objectpos);

	if (m_nLife >= 1)
	{//���C�t���P�ȏ�̎��Ƀ_���[�W�̏�����ʂ�
		//HP����_���[�W��������
		m_nLife -= nDamage;
	}

	if (m_nLife <= 0)
	{//���C�t���O�ȉ��̎�
		//�I�u�W�F�N�g�̔j��
		C2DObject::Uninit();
		//�₪����
		CExplosion::Create(Objectpos, D3DXVECTOR2(30.0f, 30.0f), 4);
		//�g��
		CEffect::Create(Objectpos, D3DXVECTOR2(100.0f, 100.0f), -25.0f, 40, CEffect::EFFECTTYPE_RIPPLE, 0);
	}
}

//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT C2DObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}

//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void C2DObject::UnLoad(void)
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