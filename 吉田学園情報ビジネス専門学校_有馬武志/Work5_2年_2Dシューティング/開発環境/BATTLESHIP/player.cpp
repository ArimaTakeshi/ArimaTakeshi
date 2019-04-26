//=============================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "gan.h"
#include "effect.h"
#include "time.h"
#include "fade.h"
#include "game.h"
#include "explosion.h"
#include "damage.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1			"data\\TEXTURE\\PlayerButtleShip.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define	TEXTURE_WIDTH			(25)										//�摜�̉��T�C�Y
#define TEXTURE_HEIGHT			(85)										//�摜�̏c�T�C�Y
#define SINCOS_ANGLE_135		(0.75f)										//sin,cos�p�x�i0.75�j				
#define SINCOS_ANGLE_90			(0.5f)										//sin,cos�p�x�i0.5�j
#define SINCOS_ANGLE_45			(0.25f)										//sin,cos�p�x�i0.25�j
#define SINCOS_ANGLE_0			(0.0f)										//sin,cos�p�x�i0.0�j
#define SHIP_ROT				(0.45f)										//�p�x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_TEXTURE] = {};
float CPlayer::m_fLife = 0.0f;
float CPlayer::m_fMaxLife = 0.0f;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CPlayer::CPlayer() : CScene2D(3)//�D��D�ʃC�j�V�����C�Y
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterState = 0;
	m_state = PLAYERSTATE_NORMAL;
	CGame::GetPlayer() = this;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�e��ݒu����
	CGan::Create(D3DXVECTOR2(12.0f, 30.0f), CGan::GANTYPE_PLAYER, CGan::GAN_CANNON, 0);

	CScene2D::Init();

	//��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	CGame::GetPlayer() = NULL;
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	CScene2D::Update();

	float nPlayerSpeed = 0.5f;

	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	
	//�ʒu�̑��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ړ��ʂ̑��
	D3DXVECTOR3 move;
	move = GetMove();

	//�G�t�F�N�g�̐���
	//CEffect::Create(pos, D3DXVECTOR2(30, 30), -25.0f, 20, CEffect::EFFECTTYPE_RIPPLE, 0);
	
	//�v���C���[���G���A�O�ɂłȂ�����
	if (pos.x - m_Size.x < 320)
	{//��ʔ��Α��Ɉړ��i���j
		pos.x = 320 + m_Size.x;
	}
	if (pos.x + m_Size.x > SCREEN_WIDTH - 320)
	{//��ʔ��Α��Ɉړ��i�E�j
		pos.x = SCREEN_WIDTH - 320 - m_Size.x;
	}
	if (pos.y - m_Size.y < 0)
	{//��ʔ��Α��Ɉړ��i��j
		pos.y = m_Size.y;
	}
	if (pos.y + m_Size.y > SCREEN_HEIGHT)
	{//��ʔ��Α��Ɉړ��i���j 
		pos.y = SCREEN_HEIGHT - m_Size.y;
	}

	// �������o��
	m_fLength = sqrtf((m_Size.x + m_Size.x) * (m_Size.y + m_Size.y));
	// �p�x���o��
	m_fAngle = atan2f(m_Size.x / 2, m_Size.y / 2);

	//�ړ���������
	if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
	{//�C�ӂ̃L�[�iA�L�[�A���L�[�j���������ꍇ

		if (m_rot.x < SHIP_ROT && m_rot.y < SHIP_ROT)
		{
			//����]
			m_rot.x += 0.009f;
			m_rot.y += 0.009f;
		}
		else
		{
			//����]
			m_rot.x = SHIP_ROT;
			m_rot.y = SHIP_ROT;
		}

		move.x += sinf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
		move.y += cosf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
	}
	else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
	{//�C�ӂ̃L�[�iD�L�[�A�E�L�[�j���������ꍇ

		if (m_rot.x > -SHIP_ROT && m_rot.y > -SHIP_ROT)
		{
			//����]
			m_rot.x -= 0.009f;
			m_rot.y -= 0.009f;
		}
		else
		{
			//����]
			m_rot.x = -SHIP_ROT;
			m_rot.y = -SHIP_ROT;
		}
		
		move.x += sinf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
		move.y += cosf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
	}
	//�L�[�𗣂�����
	else if (m_rot.x <= SHIP_ROT && m_rot.y <= SHIP_ROT || m_rot.x >= -SHIP_ROT && m_rot.y >= -SHIP_ROT)
	{//���݂̊p�x��0.45�ȉ��܂��͈ȏ�̏ꍇ�@�����l�ł���0.0f�Ɋp�x��߂�
		if (m_rot.x <= SHIP_ROT && m_rot.y <= SHIP_ROT)
		{//���ɌX���Ă�����
			if (m_rot.x > 0.0f && m_rot.y > 0.0f)
			{
				m_rot.x -= 0.018f;
				m_rot.y -= 0.018f;
			}
		}
		if (m_rot.x >= -SHIP_ROT && m_rot.y >= -SHIP_ROT)
		{//�E�ɌX���Ă�����
			if (m_rot.x < 0.0f && m_rot.y < 0.0f)
			{
				m_rot.x += 0.018f;
				m_rot.y += 0.018f;
			}
		}	
	}

	//��Ԋm�F
	switch (m_state)
	{
	case PLAYERSTATE_NORMAL:	//�ʏ���
		break;
	case PLAYERSTATE_DAMAGE:	//�_���[�W���
		//��Ԃ��J�E���g
		m_nCounterState--;

		if (m_nCounterState <= 0)
		{//��ԃJ�E���g�I��
			//�F�����Ƃɖ߂�
			Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//��ԕω�
			m_state = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_DEAHT:		//���S���
		//��Ԃ��J�E���g
		m_nCounterState--;
		break;
	}

	//�ʒu���ړ��ɑ��
	pos.x += move.x;
	pos.y += move.y;

	//��������
	move.x += (0.0f - move.x) * 0.125f;
	move.y += (0.0f - move.y) * 0.125f;

	//�J���[�̊��蓖��
	CScene2D::SetColor(&Color[0]);

	//�v���C���[�̈ʒu�ƃT�C�Y
	CScene2D::Set(pos,D3DXVECTOR2(m_Size.x, m_Size.y));

	//�摜�̉�]
	CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);

	//�ړ��ʂ����蓖�Ă�
	CScene2D::SetMove(move);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,float fLife)
{
	CPlayer *pPlayer = NULL;

	//NULL�`�F�b�N
	if (pPlayer == NULL)
	{//�������̓��I�m��

		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pPlayer->Init();
			//�e�N�X�`�������蓖�Ă�
			pPlayer->BindTexture(m_pTexture[0]);
			//HP�����蓖�Ă�
			pPlayer->m_fLife = fLife;
			//�ő�HP�̊��蓖��
			pPlayer->m_fMaxLife = fLife;
			//�傫���ƈʒu
			pPlayer->SetPosition(pos);
			//�T�C�Y
			pPlayer->m_Size = size;
		}
	}
	return pPlayer;
}
//===============================================================================
// �v���C���[�̃_���[�W����
//===============================================================================
void CPlayer::HitPlayer(float fDamage)
{
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	if (m_fLife >= 1)
	{//���C�t���P�ȏ�̎��Ƀ_���[�W�̏�����ʂ�

		//HP����_���[�W��������
		m_fLife -= fDamage;

		//���C�t�Q�[�W���猸�炷
		CLife::AddLife(-(int)fDamage);

		//�_���[�W�̐��l��\��
		CDamage::Create();
		CDamage::AddDamage((int)fDamage);

		//HP���O�ȉ��̎��̕ی�
		if (m_fLife <= 0)
		{
			m_fLife = 0;
		}
	}

	if (m_fLife <= 0)
	{//���C�t���O�ȉ��̎�
		//������
		pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION000);
		//��Ԃ̑��
		m_state = PLAYERSTATE_DEAHT;	//���S
		//�v���C���[�̈ʒu�ƃT�C�Y
		CScene2D::SetPosition(pos);
		//�_���[�W����
		m_nCounterState = 30;
		//�����鏈��
		CExplosion::Create(pos, m_Size, 1);
		//�G�t�F�N�g�̐���
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 21, CEffect::EFFECTTYPE_RIPPLE, 0);
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 24, CEffect::EFFECTTYPE_RIPPLE, 0);
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 27, CEffect::EFFECTTYPE_RIPPLE, 0);
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 30, CEffect::EFFECTTYPE_RIPPLE, 0);
		m_fLife = 0;
		//�Q�[�����烊�U���g��
		CGame::SetGameState(CGame::GAMESTATE_OVER);

		//�v���C���[�̔j��
		CPlayer::Uninit();
	}
	else
	{//���C�t���O�ȏ�̎�
		//��Ԃ̑��
		m_state = PLAYERSTATE_DAMAGE;	//�_���[�W
		//�_���[�W����
		m_nCounterState = 30;

		//�e�N�X�`���ݒ�
		Color[0] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		Color[1] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		Color[2] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		Color[3] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);

		//�J���[�̊��蓖��
		CScene2D::SetColor(&Color[0]);
	}
}

//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CPlayer::Load(void)
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
void CPlayer::UnLoad(void)
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
