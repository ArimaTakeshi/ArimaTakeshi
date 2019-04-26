//=============================================================================
//
// �e�̏��� [gan.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "gan.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "game.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\PlayerGun.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2	"data\\TEXTURE\\PlayerGunSky.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3	"data\\TEXTURE\\PlayerGunDown.png"		//�ǂݍ��ރe�N�X�`���t�@�C��	
#define TEXTURE_NAME_4	"data\\TEXTURE\\FramPlayerGun.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_5	"data\\TEXTURE\\FramPlayerGunSky.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_6	"data\\TEXTURE\\FramPlayerGunDown.png"	//�ǂݍ��ރe�N�X�`���t�@�C��	
#define TORPEDO_COUNT	(80)									//������ł܂ł̎���
#define CANNON_COUNT	(80)									//��C��ł܂ł̎���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGan::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CGan::CGan() : CScene2D(4)//�D��D�ʃC�j�V�����C�Y
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_fLife = 0;
	m_nCount = 0;
	m_nCannonCount = 0;
	m_gantype = GAN_CANNON;
	m_nFram = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_bInitTex = false;
	m_fRot = 0.0f;
	m_fLength = 0.0f;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CGan::~CGan()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGan::Init(void)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_GAN);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGan::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGan::Update(void)
{
	CScene2D::Update();

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (pPlayer != NULL)
	{
		pos = pPlayer->GetPosition();

		//�}�E�X��pos�����锠
		D3DXVECTOR3 mousepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�}�E�X�̍��W���擾
		mousepos = *CInputMouse::GetMousePos();

		//�}�E�X�̕��p������
		m_fRot = atan2f(mousepos.x - pos.x, mousepos.y - pos.y);
		
		if (m_nFram != 1)
		{//�t���[������Ȃ��ꍇ�̂�
			//��]
			CScene2D::SetRot(m_fRot, m_Size);
		}
	}

	////�}�E�X�̍��W���擾
	/*POINT pt;
	GetCursorPos(&pt);*/

	//D3DXVECTOR3 pos = 

	//��ނ̑��
	static CBullet::BULLETTYPE type = CBullet::BULLETTYPE_PLAYER;

	if (m_nFram == 0)
	{
		//��͂ɏe��t����
		Set(D3DXVECTOR3(pos.x, pos.y - 10, pos.z), D3DXVECTOR2(m_Size.x, m_Size.y));
	}
	else if (m_nFram == 1)
	{
		//�\������̈ʒu
		Set(D3DXVECTOR3(1120.0f, 570.0f, 0.0f), D3DXVECTOR2(m_Size.x, m_Size.y));
	}

	if (m_nFram == 1 && m_bInitTex == false)
	{//�t���[������Ȃ��ꍇ�̂�
		BindTexture(m_pTexture[3]);

		m_bInitTex = true;
	}

	//����̃`�F���W
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_1) == true)
	{//��C
		//����؂�ւ��̉�
		pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEAPON);

		m_gantype = GAN_CANNON;

		if (m_nFram == 0)
		{//����̃e�N�X�`�����ւ�
			BindTexture(m_pTexture[0]);
		}
		else
		{//�t���[���̃e�N�X�`���̒��ւ�
			BindTexture(m_pTexture[3]);
		}
	}
	else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_2) == true)
	{//�΋�C
		//����؂�ւ��̉�
		pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEAPON);

		m_gantype = GAN_SKYCANNON;

		if (m_nFram == 0)
		{//����̃e�N�X�`�����ւ�
			BindTexture(m_pTexture[1]);
		}
		else
		{//�t���[���̃e�N�X�`���̒��ւ�
			BindTexture(m_pTexture[4]);
		}
	}
	else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_3) == true)
	{//����
		//����؂�ւ��̉�
		pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEAPON);

		m_gantype = GAN_TORPEDO;
		if (m_nFram == 0)
		{//����̃e�N�X�`�����ւ�
			BindTexture(m_pTexture[2]);
		}
		else
		{//�t���[���̃e�N�X�`���̒��ւ�
			BindTexture(m_pTexture[5]);
		}
	}

	//�e�̐؂�ւ�
	switch (m_gantype)
	{
	case GAN_CANNON:		//��C
		//�J�E���g��ł��ĂȂ��Ƃ��ɂ�++����@����nCount�܂ł����甭�˂ł���
		if (m_nCannonCount < CANNON_COUNT)
		{//�l��菬�����ꍇ�@�����Ă���
			m_nCannonCount++;
		}
		if (m_nFram != 1)
		{//�t���[������Ȃ��ꍇ�̂�
			if (m_nCannonCount == CANNON_COUNT && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//��C���ˉ�
				pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);

				//�J�E���g�𑫂�
				m_nCannonCount++;

				//���C�̔���
				CExplosion::Create(D3DXVECTOR3(pos.x + 5, pos.y - 25, pos.z), D3DXVECTOR2(17, 17), 0);
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - 25, pos.z), D3DXVECTOR2(17, 17), 0);
				CExplosion::Create(D3DXVECTOR3(pos.x - 5, pos.y - 25, pos.z), D3DXVECTOR2(17, 17), 0);

				//�e�̐���
				CBullet::Create(D3DXVECTOR3(pos.x + 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 30.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::PLAYER_SHIP, 0);
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 30.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::PLAYER_SHIP, 0);
				CBullet::Create(D3DXVECTOR3(pos.x - 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 30.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::PLAYER_SHIP, 0);
			}
			if (m_nCannonCount >= CANNON_COUNT + 1)
			{
  				m_nCannonCount = 0;
			}
		}
		break;
	case GAN_SKYCANNON:		//�΋�C
		if (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true)
		{//�e�̐���
			if (m_nFram != 1)
			{//�t���[������Ȃ��ꍇ�̂�
				if (rand() % 15 == 0)
				{
					//�΋�C���ˉ�
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x + 10, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x + 10, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::PLAYER_SHIP, 0);
				}
				if (rand() % 20 == 0)
				{
					//�΋�C���ˉ�
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x + 5, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x + 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::PLAYER_SHIP, 0);
				}
				if (rand() % 15 == 0)
				{
					//�΋�C���ˉ�
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x - 5, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x - 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::PLAYER_SHIP, 0);
				}
				if (rand() % 20 == 0)
				{
					//�΋�C���ˉ�
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x - 10, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x - 10, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::ENEMY_DIGHTER, 0);
				}
			}
		}
		break;
	case GAN_TORPEDO:		//����
		//�J�E���g��ł��ĂȂ��Ƃ��ɂ�++����@����nCount�܂ł����甭�˂ł���
		if (m_nCount < TORPEDO_COUNT)
		{//�l��菬�����ꍇ�@�����Ă���
			m_nCount++;
		}
		else if (m_nCount < TORPEDO_COUNT * 2 && m_nCount > TORPEDO_COUNT)
		{//�l��菬�����ꍇ�@�����Ă���
			m_nCount++;
		}
		else if (m_nCount < TORPEDO_COUNT * 3 && m_nCount > TORPEDO_COUNT * 2)
		{//�l��菬�����ꍇ�@�����Ă���
			m_nCount++;
		}

		if (m_nFram != 1)
		{//�t���[������Ȃ��ꍇ�̂�
			if (m_nCount == TORPEDO_COUNT && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//�����C���ˉ�
				pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
				//�J�E���g�𑫂�
				m_nCount++;
				CExplosion::Create(D3DXVECTOR3(pos.x + 5, pos.y - 25, pos.z), D3DXVECTOR2(13, 13), 0);
				CBullet::Create(D3DXVECTOR3(pos.x + 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 5.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::PLAYER_SHIP, 1);
			}
			else if (m_nCount == TORPEDO_COUNT * 2 && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//�����C���ˉ�
				pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
				//�J�E���g�𑫂�
				m_nCount++;
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - 25, pos.z), D3DXVECTOR2(13, 13), 0);
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 5.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::PLAYER_SHIP, 1);
			}
			else if (m_nCount == TORPEDO_COUNT * 3 && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//�����C���ˉ�
				pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
				//�J�E���g�𑫂�
				m_nCount++;
				CExplosion::Create(D3DXVECTOR3(pos.x - 5, pos.y - 25, pos.z), D3DXVECTOR2(13, 13), 0);
				CBullet::Create(D3DXVECTOR3(pos.x - 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 5.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::PLAYER_SHIP, 1);
			}
			else if (m_nCount >= (TORPEDO_COUNT * 3) + 1)
			{//nCnt�̏�����
				m_nCount = 0;
			}
		}
		break;
	}

	//�v���C���[�̗̑͂������Ă���
	m_fLife = pPlayer->GetLife();

	if (m_fLife <= 0)
	{//�v���C���[��HP��0�ɂȂ����ꍇ���������(�\�������������(�d�l�ɂ��悤���ȁH)
		CGan::Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGan::Draw(void)
{
	if (m_nFram != 1)
	{//�t���[������Ȃ��ꍇ�̂�
		CScene2D::SetRot(m_fRot, m_Size);
	}

	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CGan * CGan::Create(D3DXVECTOR2 size,TYPE type,GAN gantype,int nfram)
{
	CGan *pGan = NULL;

	//NULL�`�F�b�N
	if (pGan == NULL)
	{//�������̓��I�m��

		pGan = new CGan;

		if (pGan != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pGan->Init();
			//�e�N�X�`�������蓖�Ă�
			pGan->BindTexture(m_pTexture[gantype]);
			//��ނ����蓖�Ă�
			pGan->m_nType = type;
			//�T�C�Y�̊��蓖��
			pGan->m_Size = size;
			//�t���[�����t���[������Ȃ���
			pGan->m_nFram = nfram;
		}
	}
	return pGan;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CGan::Load(void)
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
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_3,
		&m_pTexture[2]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_4,
		&m_pTexture[3]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_5,
		&m_pTexture[4]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_6,
		&m_pTexture[5]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CGan::UnLoad(void)
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