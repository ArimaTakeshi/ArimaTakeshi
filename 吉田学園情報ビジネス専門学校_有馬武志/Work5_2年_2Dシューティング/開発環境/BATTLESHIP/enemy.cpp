//=============================================================================
//
// �G�̏��� [enemy.cpp]
// Author : �L�n���u
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanf�G���[����
#include <stdio.h>					//stdio
#include "scene.h"
#include "scene2D.h"
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "score.h"
#include "player.h"
#include "effect.h"
#include "time.h"
#include "game.h"
#include "sound.h"
#include "explosion.h"
#include "damage.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1			"data\\TEXTURE\\EnemyButtleShip.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2			"data\\TEXTURE\\�퓬�@.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3			"data\\TEXTURE\\EnemySubmarine.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4			"data\\TEXTURE\\���.png"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define	TEXTURE_SHIP_WIDTH		(25)									//��͂̉��T�C�Y
#define TEXTURE_SHIP_HEIGHT		(85)									//��͂̏c�T�C�Y
#define	TEXTURE_DIGHTER_WIDTH	(20)									//�퓬�@�̉��T�C�Y
#define TEXTURE_DIGHTER_HEIGHT	(20)									//�퓬�@�̏c�T�C�Y
#define RANGE_SIZE_X			(300)									//�G�̍��G�͈�X
#define RANGE_SIZE_Y			(300)									//�G�̍��G�͈�Y
#define CHASE_RANGE_SIZE_X		(600)									//�G�̍��G�͈�X
#define CHASE_RANGE_SIZE_Y		(600)									//�G�̍��G�͈�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_TEXTURE] = {};
int CEnemy::m_nNumEnemy = 0;
int CEnemy::m_nNumMaxEnemy = 0;
CEnemy::Enemy CEnemy::m_Enemy[MAX_DATA] = {};
int	CEnemy::m_nCntEnemy = 0;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CEnemy::CEnemy() : CScene2D(3)//�D��D�ʃC�j�V�����C�Y
{
	m_nLife = 0;
	m_nCounterState = 0;
	m_nCount = 0;
	m_type = ENEMYTYPE_SHIP;
	m_state = ENEMYSTATE_NORMAL;
	m_fAngle = 0.0f;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumMaxEnemy = 0;
	m_nOnOffAttack = 0;
	m_nChase = 0;
	//m_nNumEnemy = 0;

	//m_nNumEnemy++;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CEnemy::~CEnemy()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();

	//��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_ENEMY);

	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//�J���[�̐ݒ�
	Color[0] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	Color[1] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	Color[2] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	Color[3] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);

	//�J���[�̊��蓖��
	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	CScene2D::Update();

	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();

	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	//NULL�`�F�b�N
	if (pPlayer != NULL)
	{
		PlayerPos = pPlayer->GetPosition();
	}

	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	}

	//��ނ̑��
	static CBullet::BULLETTYPE type = CBullet::BULLETTYPE_ENEMY;

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�����l�ݒ�
	D3DXVECTOR3 pos;
	pos = CEnemy::GetPosition();

	//�ǔ����邩���Ȃ��� 1�͂���@0�͂��Ȃ�
	if (m_nChase == 1)
	{
		//NULL�`�F�b�N
		if (pPlayer != NULL)
		{
			//���G�͈�
			if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
				pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
			{
				//�}�E�X�̕��p������
				m_fRot = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);

				//��]
				CScene2D::SetRot(m_fRot, m_Size);

				//�G���ǔ����Ă���
				m_move = D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 1.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 1.0f, 0.0f);
			}
		}
	}
	
	//�ړ��ʂ�ǉ�
	pos += m_move;
	
	//��Ԋm�F
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:	//�ʏ���
		break;
	case ENEMYSTATE_DAMAGE:	//�_���[�W���

		//��Ԃ��J�E���g
		m_nCounterState--;

		if (m_nCounterState <= 0)
		{//��ԃJ�E���g�I��
			//�F�����Ƃɖ߂�
			Color[0] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
			Color[1] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
			Color[2] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
			Color[3] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);

			//��ԕω�
			m_state = ENEMYSTATE_NORMAL;
		}

		break;
	case ENEMYSTATE_DEAHT:		//���S���
		//��Ԃ��J�E���g
		m_nCounterState--;
		break;
	}

	//�J���[�̊��蓖��
	CScene2D::SetColor(&Color[0]);

	//��Ԋm�F
	switch (m_type)
	{
	case ENEMYTYPE_SHIP:	//���

		//�傫���ƈʒu
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));

		//�g��G�t�F�N�g�̐���
		CEffect::Create(pos, D3DXVECTOR2(30,30),-25.0f, 20,CEffect::EFFECTTYPE_RIPPLE,0);

		//�����V���b�g
		if (m_nCount == 120 && m_nOnOffAttack == 0)
		{//�e�̐���
				//NULL�`�F�b�N
			if (pPlayer != NULL)
			{
				//���G�͈�
				if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
					pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
				{
					//��C�e�̉�
					pSound->PlaySound(CSound::SOUND_LABEL_ENEMYCANNON);

					//�ǔ�
					CBullet::Create(pos, D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::ENEMY_SHIP, 2);
				}
			}
		}
		else if (m_nCount >= 121)
		{//���ɖ߂�
			m_nCount = 0;
		}
		//�U���J�E���^�[�𑝂₷
		m_nCount++;

		break;
	case ENEMYTYPE_DIGHTER:	//�퓬�@

		//�傫���ƈʒu
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));

		//���G�t�F�N�g�̐���
		CEffect::Create(D3DXVECTOR3(pos.x - 15,pos.y,pos.z),D3DXVECTOR2(3,3),2.0f, 8, CEffect::EFFECTTYPE_NOLMAL,1);
		CEffect::Create(D3DXVECTOR3(pos.x + 15, pos.y, pos.z), D3DXVECTOR2(3, 3),2.0f, 8, CEffect::EFFECTTYPE_NOLMAL,1);

		if (pos.y == 200.0f)
		{//�G�����̈ʒu�Ŏ~�߂�
			m_move.y = 0;
		}
		
		if (pPlayer != NULL)
		{
			//���G�͈�
			if (pos.x <= PlayerPos.x + RANGE_SIZE_X && pos.x >= PlayerPos.x - RANGE_SIZE_X &&
				pos.y <= PlayerPos.y + RANGE_SIZE_Y && pos.y >= PlayerPos.y - RANGE_SIZE_Y)
			{
				if (rand() % 20 == 0 && m_nOnOffAttack == 0)
				{//�e�̐���
					//�΋�C�̉�
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CBullet::Create(D3DXVECTOR3(pos.x + 15, pos.y, pos.z), D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::ENEMY_DIGHTER, 2);
				}
				if (rand() % 20 == 0 && m_nOnOffAttack == 0)
				{//�e�̐���
					//�΋�C�̉�
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CBullet::Create(D3DXVECTOR3(pos.x - 15, pos.y, pos.z), D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::ENEMY_DIGHTER, 2);
				}
			}
		}

		break;
	case ENEMYTYPE_SUBMARINE:	//������

		//�傫���ƈʒu
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));
		//�g��G�t�F�N�g�̐���
		CEffect::Create(pos, D3DXVECTOR2(20, 20),-15.0f, 15, CEffect::EFFECTTYPE_RIPPLE,0);

		//�����V���b�g
		if (m_nCount == 120 && m_nOnOffAttack == 0)
		{//�e�̐���
			if (pPlayer != NULL)
			{
				//���G�͈�
				if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
					pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
				{
					//�����C�̉�
					pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);

					//�ʏ�
					CBullet::Create(pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::ENEMY_SUBMARINE, 3);
				}
			}
		}
		else if (m_nCount >= 121)
		{//���ɖ߂�
			m_nCount = 0;
		}
		//�U���J�E���^�[�𑝂₷
		m_nCount++;

		break;
	case ENEMTTYPE_CARRIER:		//���

		//�傫���ƈʒu
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));
		//�g��G�t�F�N�g�̐���
		CEffect::Create(pos, D3DXVECTOR2(30.0f, 30.0f), -15.0f, 15, CEffect::EFFECTTYPE_RIPPLE, 0);

		if (pos.y == 200.0f)
		{//�G�����̈ʒu�Ŏ~�߂�
			m_move.y = 0;
		}

		if (m_nCount == 300)
		{//�G�̐���
			//���G�͈�
			if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
				pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
			{
				if (GameMode == CManager::MODE_TUTORIAL)
				{//�`���[�g���A���̏ꍇ �U�����Ȃ��G�̐���
					CEnemy::Create(pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1, 0);
				}
				else if (GameMode == CManager::MODE_GAME)
				{//�Q�[���̏ꍇ �U������G�̐���
					CEnemy::Create(D3DXVECTOR3(pos.x - 10, pos.y - 30.0f,pos.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 0, 1);
					CEnemy::Create(pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 10, 0, 1);
					CEnemy::Create(D3DXVECTOR3(pos.x + 10, pos.y + 30.0f, pos.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 20, 0, 1);
				}
			}
		}
		else if (m_nCount >= 301)
		{//���ɖ߂�
			m_nCount = 0;
		}

		//�U���J�E���^�[�𑝂₷
		m_nCount++;

		break;
	}

	if (GameMode == CManager::MODE_TUTORIAL)
	{//�`���[�g���A���̏ꍇ
		if (pos.y == 200.0f)
		{//�G�����̈ʒu�Ŏ~�߂�
			m_move.y = 0;
		}
	}

	//m_nCntEnemy++;

	//�G���G���A�O�̏ꍇ
	if (pos.x - m_Size.x < 0)
	{//��ʔ��Α��Ɉړ��i���j
		pos.x = m_Size.x;
	}
	if (pos.x + m_Size.x > SCREEN_WIDTH)
	{//��ʔ��Α��Ɉړ��i�E�j
		pos.x = SCREEN_WIDTH - m_Size.x;
	}
	if (pos.y - m_Size.y < 0)
	{//��ʔ��Α��Ɉړ��i��j
		pos.y = m_Size.y;
	}
	if (pos.y + m_Size.y > SCREEN_HEIGHT + 30)
	{//��ʔ��Α��Ɉړ��i���j 
		CEnemy::Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	//��]
	CScene2D::SetRot(m_fRot, m_Size);

	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size,ENEMYTYPE type,int nLife,int nOnOffAttak,int nChase)
{
	CEnemy *pEnemy = NULL;

	//NULL�`�F�b�N
	if (pEnemy == NULL)
	{//�������̓��I�m��

		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pEnemy->Init();
			//�e�N�X�`�������蓖�Ă�
			pEnemy->BindTexture(m_pTexture[type]);
			//HP�����蓖�Ă�
			pEnemy->m_nLife = nLife;
			//�傫���ƈʒu
			pEnemy->SetPosition(pos);
			//�ړ�
			pEnemy->m_move = move;
			//�T�C�Y
			pEnemy->m_Size = size;
			//�^�C�v�̊��蓖��
			pEnemy->m_type = type;
			//�U�������邩���Ȃ����̊��蓖��
			pEnemy->m_nOnOffAttack = nOnOffAttak;
			//�ǔ����邩���Ȃ���
			pEnemy->m_nChase = nChase;
			//�G�̑����J�E���^�[
			//pEnemy->m_nNumEnemy++;
		}
	}

	return pEnemy;
}
//===============================================================================
//  �t�@�C�����o�͂ɂ��G�̈ʒu��ݒu
//===============================================================================
void CEnemy::CreateEnemy(void)
{
	int nNumMaxEnemy = 0;
	char read[256];
	//int nCntFream = 0;

	//�t�@�C���̃|�C���^
	FILE *pFile;

	//�t�@�C���ݒ�
	pFile = fopen(FILE_NAME, "r");

	//�G�̃e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//������tex�R�����g
		fscanf(pFile, "%s", &read[0]);

		if (strcmp(&read[0], "#") == 0)
		{
			do
			{
				fscanf(pFile, "%c", &read[0]);
			} while (strcmp(&read[0], "\n") != 0);
		}

		//�g���G�̐�
		fscanf(pFile, "%d", &nNumMaxEnemy);	//�ǂݍ���

		for (int nCntEnemy = 0; nCntEnemy < nNumMaxEnemy; nCntEnemy++)
		{
			//�G�̎�ނ̃R�����g
			for (int nCount = 0; nCount < 3; nCount++) 
			{ 
				fscanf(pFile, "%s", &read[0]);

				if (strcmp(&read[0], "#") == 0) 
				{ 
					do 
					{ 
						fscanf(pFile, "%c", &read[0]); 
					}
				while (strcmp(&read[0], "\n") != 0); 
				}
			}

			//�����ʒu�̐ݒ�
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitPos.x);		//�ʒuX
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitPos.y);		//�ʒuY
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitPos.z);		//�ʒuZ

			//�����l�̓����̐ݒ�
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitMove.x);	//�ړ�����X
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitMove.y);	//�ړ�����Y
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitMove.z);	//�ړ�����Z

			//�����l�̃T�C�Y�̐ݒ�
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitSize.x);	//����X
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitSize.y);	//�c��Y

			//�G�̃^�C�v�̐ݒ�
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].EnemyType);		//�^�C�v�̑��

			//�G��HP�̐ݒ�
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].nLife);			//���C�t�̑��

			//�G�̍U�������邩���Ȃ����̐ݒ�
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].nAttack);		//Attack���邩���Ȃ��� 0�U���J�n�@1�U�����Ȃ�

			//�ǔ����邩���Ȃ���
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].nChase);		//1�ǔ�����ꍇ   0���Ȃ��ꍇ

			//�G�̐���
			//CEnemy::Create(�ʒu�E�����E�T�C�Y�E�G�̎�ށE�̗́E�U������1 �U�����Ȃ�0�ȊO�E�ǔ�����1 �ǔ����Ȃ�0);
			//�G�̐���  ENEMYTYPE_SHIP ���0  : ENEMYTYPE_DIGHTER �퓬�@1  : ENEMYTYPE_SUBMARINE ������2  : ENEMTTYPE_CARRIER  ���3
			CEnemy::Create(m_Enemy[nCntEnemy].InitPos, m_Enemy[nCntEnemy].InitMove, m_Enemy[nCntEnemy].InitSize, m_Enemy[nCntEnemy].EnemyType, m_Enemy[nCntEnemy].nLife, m_Enemy[nCntEnemy].nAttack, m_Enemy[nCntEnemy].nChase);
		}

		fclose(pFile);	//�t�@�C�������
	}
	else
	{//�x����
		MessageBox(0, "�Z�[�u�t�@�C���̃`�F�b�N�Ɏ��s!", "�x��", MB_ICONWARNING);
	}

	//�G�̐�������
	m_nNumMaxEnemy = nNumMaxEnemy;
}
//===============================================================================
// �G�̃_���[�W����
//===============================================================================
void CEnemy::HitEnemy(int nDamage)
{
	//�ʒu�̏��
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//�J���[�̐錾�Ə�����
	D3DXCOLOR Color[4];

	if (m_nLife >= 1)
	{//���C�t���P�ȏ�̎��Ƀ_���[�W�̏�����ʂ�
		//HP����_���[�W��������
		m_nLife -= nDamage;
	}

	if (m_nLife <= 0)
	{//���C�t���O�ȉ��̎�
		//��Ԃ̑��
		m_state = ENEMYSTATE_DEAHT;		//���S
		//�X�R�A���Z
		CScore::AddScore(1000);
		//���j�������Z
		CTime::AddTime(1);
		//�_���[�W����
		m_nCounterState = 30;

		//�G�̎��ʉ��o
		switch (m_type)
		{
		case ENEMYTYPE_SHIP://���
			//�G�t�F�N�g�̐���
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 30, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 27, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 24, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 21, CEffect::EFFECTTYPE_RIPPLE, 0);
			break;
		case ENEMYTYPE_DIGHTER://�퓬�@
			//�����鏈��
			CExplosion::Create(pos, m_Size, 3);
			break;
		case ENEMYTYPE_SUBMARINE://������
			break;
		case ENEMTTYPE_CARRIER://���
			//�G�t�F�N�g�̐���
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 30, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 27, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 24, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 21, CEffect::EFFECTTYPE_RIPPLE, 0);

			if (m_type == ENEMTTYPE_CARRIER)
			{//�G���S�ł�����
				CGame::SetGameState(CGame::GAMESTATE_CLEAR);
			}
			break;
		}

		//�v���C���[�̔j��
		CEnemy::Uninit();
	}
	else
	{//���C�t���O�ȏ�̎�
		//��Ԃ̑��
		m_state = ENEMYSTATE_DAMAGE;	//�_���[�W
		//�X�R�A���Z
		CScore::AddScore(1);
		//�_���[�W����
		m_nCounterState = 30;

		//�J���[�̐ݒ�
		Color[0] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Color[1] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Color[2] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Color[3] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		//�J���[�̊��蓖��
		CScene2D::SetColor(&Color[0]);
	}
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CEnemy::Load(void)
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

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CEnemy::UnLoad(void)
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
