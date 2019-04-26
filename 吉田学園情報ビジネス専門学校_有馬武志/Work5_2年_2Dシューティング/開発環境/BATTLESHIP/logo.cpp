//=============================================================================
//
// ���S�̏��� [logo.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "logo.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\B.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2		"data\\TEXTURE\\A.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3		"data\\TEXTURE\\T.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4		"data\\TEXTURE\\T.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_5		"data\\TEXTURE\\L.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_6		"data\\TEXTURE\\E.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_7		"data\\TEXTURE\\S.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_8		"data\\TEXTURE\\H.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_9		"data\\TEXTURE\\I.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_10		"data\\TEXTURE\\P.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_11		"data\\TEXTURE\\PressAny.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_12		"data\\TEXTURE\\TitleButtleship.png"//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_13		"data\\TEXTURE\\TitleSentouki.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_23		"data\\TEXTURE\\EnemySentouki.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_14		"data\\TEXTURE\\tutorial003.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_15		"data\\TEXTURE\\tutorial001.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_16		"data\\TEXTURE\\tutorial002.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_21		"data\\TEXTURE\\tutorial003.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_29		"data\\TEXTURE\\tutorial004.jpg"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_17		"data\\TEXTURE\\instruction000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_18		"data\\TEXTURE\\instruction001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_19		"data\\TEXTURE\\instruction002.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_20		"data\\TEXTURE\\instruction003.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_22		"data\\TEXTURE\\instruction004.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_27		"data\\TEXTURE\\instruction005.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_28		"data\\TEXTURE\\instruction006.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_24		"data\\TEXTURE\\Bullet0003.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_26		"data\\TEXTURE\\Bullet0004.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_25		"data\\TEXTURE\\kuubo.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_30		"data\\TEXTURE\\hea.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MIN_POS				(230.0f)							//�Œ�ʒu
#define DOWNSPD				(5.0f)								//�����X�s�[�h
#define SKYSPD				(4.0f)								//��s�@�̔�s�X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CLogo::CLogo() : CScene2D(4)//�D��D�ʃC�j�V�����C�Y
{
	m_nCnt = 15;
	m_nCntTutorial = 0;
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntShip = 0;
	m_nExplosionCnt = 0;
	m_nCntShipDown = 0;
	m_bOneCnt = false;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CLogo::~CLogo()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLogo::Init(void)
{
	CScene2D::Init();

	D3DXCOLOR Color[4];

	for (int nCount = 0; nCount < 4; nCount++)
	{//����ȊO�̏ꍇ���ׂĂ̏�����
		Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogo::Update(void)
{
	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	D3DXCOLOR Color[4];

	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();

	//�Q�[���̏�Ԃ̊m�F
	CGame::GAMESTATE GameState = CGame::GetGameState();

	//�}�E�X��pos�����锠
	D3DXVECTOR3 mousepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�}�E�X�̍��W���擾
	mousepos = *CInputMouse::GetMousePos();

	//�f�o�b�N�p�@�I������炱�̕����������ƁI�@Manager�̎n�܂��TITLE�ɖ߂����ƁI
	//GameState = CGame::GAMESTATE_CLEAR;

	//�ړ��ʂ̊��蓖��
	D3DXVECTOR3 move;
	move = GetMove();

	//�ʒu�̊��蓖��
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//�ϐ��錾
	int nFrame = 15; //�Ԋu
	m_nCnt++;

	//�^�C�g�����S�𗎂Ƃ�
	for (int nCount = 0; nCount < 10; nCount++)
	{
		if (m_nType == nCount)
		{
			if (pos.y < MIN_POS && m_nCnt >= (nFrame * nCount + 1))
			{
				move = D3DXVECTOR3(0.0f, DOWNSPD, 0.0f);
			}
			else
			{//���̈ʒu�𒴂�����~�܂�
				move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	if (m_nType == 11 || m_nType == 25)
	{//��͂Ƌ��̂ݎg�p

		// �������o��
		m_fLength = sqrtf((m_size.x / 2 + m_size.x / 2) * (m_size.y / 2 + m_size.y / 2));
		// �p�x���o��
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

		if (m_nCntShip == 120)
		{
			//�J�E���^�[��0�ɖ߂�
			m_nCntShip = 0;
		}
		else if (m_nCntShip >= 60)
		{
			//�E��]
			m_rot.x -= 0.0003f;
			m_rot.y -= 0.0003f;
		}
		else if (m_nCntShip >= 0)
		{
			//����]
			m_rot.x += 0.0003f;
			m_rot.y += 0.0003f;
		}

		//�J�E���^�[�̑���
		m_nCntShip++;
	}

	//������s�@
	if (m_nType == 12)
	{
		move = D3DXVECTOR3(-SKYSPD, 0.0f, 0.0f);
	}
	//�G��s�@
	if (m_nType == 22)
	{
		move = D3DXVECTOR3(SKYSPD, 0.0f, 0.0f);
	}
	//�I�[�o�[���̔��e�̓���
	if (m_nType == 23 || m_nType == 24 && GameState == CGame::GAMESTATE_OVER)
	{
		move = D3DXVECTOR3(0.0f, SKYSPD, 0.0f);
	}
	//�N���A���̔��e�̓���
	if (m_nType == 26 || m_nType == 27 && GameState == CGame::GAMESTATE_CLEAR)
	{
		move = D3DXVECTOR3(-SKYSPD, 0.2f, 0.0f);

		// �������o��
		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// �p�x���o��
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

		//����]
		m_rot.x += 0.001f;
		m_rot.y += 0.001f;
	}

	if (m_nType == 28 || m_nType == 29)
	{//�񍐕�
	 //��x�̂ݓ���
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1135.0f)
			{//�E�ɓ�����
				move.x = -5;
			}
			else if (pos.x <= 1135.0f)
			{//��x�~�߂�
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
	}

	//�ʒu���X�V(�ړ�)
	pos.x += move.x;
	pos.y += move.y;


	//�N���X�w�A
	if (m_nType == 31)
	{
		//���g��POS�Ƀ}�E�X��POS������
		pos = mousepos;
	}

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	if (pCInputKeyBoard->GetKeyboardAny(1) == true || pCInputMouse->GetMouseTrigger(0) == true)
	{//�^�C�g�����S�𗎂Ƃ�
		for (int nCount = 0; nCount < 10; nCount++)
		{
			if (m_nType == nCount)
			{
				pos.y = MIN_POS;
			}
		}
	}

	//���������`���[�g���A����������
	if (m_nType == 16 && GameMode == CManager::MODE_TUTORIAL)
	{//�`���[�g���A���w���\��

		//��x�̂ݓ���
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1135.0f)
			{//�E�ɓ�����
				move.x = -5;
			}
			else if (pos.x <= 1135.0f)
			{//��x�~�߂�
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
		//�W�b���ʊO�ɖ߂�
		if (m_nCntTutorial == 500)
		{//���ɓ�����
			move.x = 5;
		}
		else if (m_nCntTutorial == 600)
		{
			//�e�N�X�`���̕ύX
			BindTexture(m_pTexture[17]);

			//������x��L�̓��������邪�AnCnt�͐i�񂾂܂܂Ȃ̂�2��ڂ͂��̂܂܎~�܂�
			m_bOneCnt = false;
		}
	}

	//���������Q�[����������
	if (m_nType == 18 && GameMode == CManager::MODE_GAME)
	{//�Q�[���w���\��
		//��x�̂ݓ���
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1135.0f)
			{//�E�ɓ�����
				move.x = -5;
			}
			else if (pos.x <= 1135.0f)
			{//��x�~�߂�
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
		//4�b���ʊO�ɖ߂�
		if (m_nCntTutorial == 240)
		{//���ɓ�����
			move.x = 5;
		}
		else if (m_nCntTutorial == 340)
		{
			//�e�N�X�`���̕ύX
			BindTexture(m_pTexture[19]);

			m_bOneCnt = false;
		}
		else if (m_nCntTutorial == 640)
		{//���ɓ�����
			move.x = 5;
		}
		else if (m_nCntTutorial == 740)
		{
			//�e�N�X�`���̕ύX
			BindTexture(m_pTexture[21]);

			//������x��L�̓��������邪�AnCnt�͐i�񂾂܂܂Ȃ̂�3��ڂ͂��̂܂܎~�܂�
			m_bOneCnt = false;
		}
		else if (m_nCntTutorial == 830)
		{
			//�����I�������I
			pSound->PlaySound(CSound::SOUND_LABEL_GO);
		}
	}

	if (m_nType == 20)
	{//�`���[�g���A���w���\��
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1130.0f && m_nCntTutorial == 460)
			{//�E�ɓ�����
				move.x = -5;
			}
			else if (pos.x <= 1130.0f)
			{//��x�~�߂�
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
	}

	//�J�E���g�̑���
	m_nCntTutorial++;
	
	if (m_nType == 10 || m_nType == 13)
	{//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		m_col.a -= 0.015f;

		if (m_col.a < 0.1f)
		{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			m_col.a = 1.0f;
		}

		// ���_�J���[�ݒ�
		for(int nCount = 0;nCount < 4;nCount++)
		{
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a);
		}
	}
	else if (m_nType == 22 || m_nType == 25)
	{//�G�̔�s�@�̐F
		// ���_�J���[�ݒ�
		for (int nCount = 0; nCount < 4; nCount++)
		{
			// ���_�J���[�ݒ�
			Color[nCount] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
		}
	}
	else
	{
		// ���_�J���[�ݒ�
		for (int nCount = 0; nCount < 4; nCount++)
		{
			// ���_�J���[�ݒ�
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//�����������U���g��������
	if (GameMode == CManager::MODE_RESULT)
	{//�Q�[���w���\��
		if (m_nType == 11 && GameState == CGame::GAMESTATE_OVER)
		{//�Q�[���I�[�o�[

			if (m_nCntShipDown >= 551)
			{
				//����]
				m_rot.x -= 0.001f;
				m_rot.y -= 0.001f;

				//�D�𒾂߂�
				pos.y += 0.05f;

				if (m_nType == 11)
				{
					//�I�����Ă���J���[�̒l�����炵�Ă���
					m_col.a -= 0.005f;

					// ���_�J���[�ݒ�
					for (int nCount = 0; nCount < 4; nCount++)
					{
						Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a);
					}
				}
			}
		}
		else if (m_nType == 25 && GameState == CGame::GAMESTATE_CLEAR)
		{//�Q�[���N���A
			if (m_nCntShipDown >= 551)
			{
				//����]
				m_rot.x += 0.001f;
				m_rot.y += 0.001f;

				//�D�𒾂߂�
				pos.y += 0.05f;

				if (m_nType == 25)
				{
					//�I�����Ă���J���[�̒l�����炵�Ă���
					m_col.a -= 0.005f;

					// ���_�J���[�ݒ�
					for (int nCount = 0; nCount < 4; nCount++)
					{
						Color[nCount] = D3DXCOLOR(1.0f, 0.6f, 0.6f, m_col.a);
					}
				}
			}
		}
		//�J�E���^�[�̑���
		m_nCntShipDown++;
	}

	//�F
	CScene2D::SetColor(&Color[0]);
	//���S�̈ʒu�ƃT�C�Y
	CScene2D::Set(pos,m_size);
	//���S�̈ʒu�ƃT�C�Y
	CScene2D::SetMove(move);

	if (m_nType == 11 || m_nType == 25 || m_nType == 26 || m_nType == 27)
	{//��]���������Ă����ނ̂�
		CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}

	if (m_nType == 23 || m_nType == 24 && GameState == CGame::GAMESTATE_OVER)
	{//�G�퓬�@�����Ƃ����e�̏I������
		if (pos.y > 550.0f && m_nType == 23)
		{
			//500�������甚��
			CLogo::Uninit();

			//�����鏈��
			CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - rand()% 50, 0.0f), D3DXVECTOR2(50.0f, 100.0f), 6);

			//������
			pSound->PlaySound(CSound::SOUND_LABEL_MIZUBASIRA);
		}
		if (pos.y > 550.0f && m_nType == 24)
		{
			//550�������甚��
			CLogo::Uninit();

			//�����̏���
			CExplosion::Create(D3DXVECTOR3(pos.x + 40.0f, pos.y + 10.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 40.0f, pos.y + 15.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(pos, D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x + 60.0f, pos.y - 25.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 60.0f, pos.y + 20.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);

			//������
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION000);
		}
	}
	if (m_nType == 26 || m_nType == 27 || m_nType == 28 && GameState == CGame::GAMESTATE_CLEAR)
	{//��͂��ł��e�̏I������
		if (pos.x < 370.0f && m_nType == 26)
		{
			//500�������甚��
			CLogo::Uninit();

			//�����鏈��
			CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - rand() % 50, 0.0f), D3DXVECTOR2(50.0f, 100.0f), 6);

			//������
			pSound->PlaySound(CSound::SOUND_LABEL_MIZUBASIRA);
		}
		if (pos.x < 370.0f && m_nType == 27)
		{
			//550�������甚��
			CLogo::Uninit();

			//�����̏���
			CExplosion::Create(D3DXVECTOR3(pos.x + 40.0f, pos.y + 10.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 40.0f, pos.y + 15.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(pos, D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x + 60.0f, pos.y - 25.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 60.0f, pos.y + 20.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);

			//������
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION000);
		}
	}

	if (m_nType == 11 || m_nType == 25)
	{//���ސ��
		if (m_col.a < 0.001f)
		{//�J���[�������ɂȂ�����
			CLogo::Uninit();
		}
	}
	if (pos.x - m_size.x < -500)
	{//����ʂ�-500�ɂ����������
		CLogo::Uninit();
	}
	if (pos.x - m_size.x > 1600)
	{//�E��ʂ�1600�ɂ����������
		CLogo::Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CLogo *pLogo = NULL;

	//NULL�`�F�b�N
	if (pLogo == NULL)
	{//�������̓��I�m��

		pLogo = new CLogo;

		if (pLogo != NULL)
		{
			//��ނ����蓖�Ă�
			pLogo->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pLogo->Init();
			//�e�N�X�`�������蓖�Ă�
			pLogo->BindTexture(m_pTexture[nType]);
			//�ʒu�����蓖�Ă�
			pLogo->SetPosition(pos);
			//�T�C�Y�̊��蓖��
			pLogo->m_size = size;
		}
	}

	return pLogo;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CLogo::Load(void)
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
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_7,
		&m_pTexture[6]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_8,
		&m_pTexture[7]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_9,
		&m_pTexture[8]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_10,
		&m_pTexture[9]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_11,
		&m_pTexture[10]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_12,
		&m_pTexture[11]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_13,
		&m_pTexture[12]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_14,
		&m_pTexture[13]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_15,
		&m_pTexture[14]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_16,
		&m_pTexture[15]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_17,
		&m_pTexture[16]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_18,
		&m_pTexture[17]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_19,
		&m_pTexture[18]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_20,
		&m_pTexture[19]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_21,
		&m_pTexture[20]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_22,
		&m_pTexture[21]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_23,
		&m_pTexture[22]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_24,
		&m_pTexture[23]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_24,
		&m_pTexture[24]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_25,
		&m_pTexture[25]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_26,
		&m_pTexture[26]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_26,
		&m_pTexture[27]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_27,
		&m_pTexture[28]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_28,
		&m_pTexture[29]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_29,
		&m_pTexture[30]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_30,
		&m_pTexture[31]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CLogo::UnLoad(void)
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