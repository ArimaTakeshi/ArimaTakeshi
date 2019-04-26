//=========================================================================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �L�n�@���u
//
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"
#include "game.h"			//�w�i
#include "player.h"			//�v���C���[
#include "bullet.h"			//�e
#include "explosion.h"		//����
#include "enemy.h"			//�G
#include "bg.h"				//�w�i
#include "score.h"			//�X�R�A
#include "effect.h"			//�G�t�F�N�g
#include "minibossenemy.h"	//���{�X
#include "ranking.h"		//�����L���O
#include "fade.h"			//�t�F�[�h	
#include "bossenemy.h"		//�{�X
#include "sound.h"			//�T�E���h
#include "warning.h"		//���[�j���O
#include "input.h"			//�L�[�{�[�h����
#include "pause.h"			//�|�[�Y
#include "life.h"			//���C�t
#include "time.h"			//����

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
GAMESTATE g_gameState = GAMESTATE_NORMAL;	//�Q�[�����
int g_nCounterGameState;					//��ԃJ�E���^�[
bool g_bPause;								//�|�[�Y

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitGame(void)
{
	//�w�i����������
	InitBG();

	//�{�X�̏���������
	InitBossEnemy();

	//���{�X�̏���������
	InitMiniBossEnemy();

	//�G�̏���������
	InitEnemy();
	
	SetEnemy(D3DXVECTOR3(200, 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(300, 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(400, 100, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(500, 100, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(600, 100, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(700, 100, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(800, 100, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(900, 100, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(1000, 100, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(1100, 100, 0.0f), 3);
	//�Q���
	SetEnemy(D3DXVECTOR3(200, 200, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(300, 200, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(400, 200, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(500, 200, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(600, 200, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(700, 200, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(800, 200, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(900, 200, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(1000, 200, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(1100, 200, 0.0f), 0);
	//�R���
	SetEnemy(D3DXVECTOR3(200, 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(300, 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(400, 300, 0.0f), 2);
	SetEnemy(D3DXVECTOR3(500, 300, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(600, 300, 0.0f), 3);
	SetEnemy(D3DXVECTOR3(700, 300, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(800, 300, 0.0f), 0);
	SetEnemy(D3DXVECTOR3(900, 300, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(1000, 300, 0.0f), 1);
	SetEnemy(D3DXVECTOR3(1100, 300, 0.0f), 1);

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�v���C���[����������
	InitPlayer();

	//�����̏���������
	InitExplosion();

	//�e�̏���������
	InitBullet();

	//���[�j���O�̏���������
	InitWarning();

	//�X�R�A�̏���������
	InitScore();
	
	//���C�t�̏���������
	InitLife();

	//���Ԃ̏���������
	InitTime();

	//�|�[�Y�̏���������
	InitPause();

	
	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	g_nCounterGameState = 0;

	g_bPause = false;
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBG();
	
	//�G�̏I������
	UninitEnemy();

	//�{�X�̏I������
	UninitBossEnemy();

	//���{�X�̏I������
	UninitMiniBossEnemy();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�v���C���[�̏I������
	UninitPlayer();

	//�����̏I������
	UninitExplosion();

	//�e�̏I������
	UninitBullet();

	//���[�j���O�̏I������
	UninitWarning();

	//�X�R�A�̏I������
	UninitScore();

	//���C�t�̏I������
	UninitLife();

	//���Ԃ̏I������
	UninitTime();

	//�|�[�Y�̏I������
	UninitPause();

}
//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdateGame(void)
{
	//�|�[�Y�̏���
	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;

		if (g_bPause == false)
		{
			//�J����
			PlaySound(SOUND_LABEL_SE_OPEN000);
		}
		else
		{
			//���艹
			PlaySound(SOUND_LABEL_SE_DOWN000);
		}
	}
	if (g_bPause == false)
	{

		//�w�i�̍X�V����
		UpdateBG();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�G�̍X�V����
		UpdateEnemy();

		//�{�X�̍X�V����
		UpdateBossEnemy();

		//���{�X�̍X�V����
		UpdateMiniBossEnemy();

		//�����̍X�V����
		UpdateExplosion();

		//�e�̍X�V����
		UpdateBullet();

		//���[�j���O�̍X�V����
		UpdateWarning();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�X�R�A�̍X�V����
		UpdateScore();

		//���C�t�̍X�V����
		UpdateLife();

		//���Ԃ̍X�V����
		UpdateTime();
	}
	else
	{
		//�|�[�Y
		UpdatePause();
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 60)
		{
			// = GAMESTATE_NONE;

			//��ʁi���[�h�j�̐ݒ�
			SetFade(MODE_RESULT);
		}
	}
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�{�X�̕`�揈��
	DrawBossEnemy();

	//�G�̕`�揈��
	DrawEnemy();
	
	//BOSS�G�̕`�揈��
	DrawMiniBossEnemy();

	//�v���C���[�̕`��
	DrawPlayer();

	//�����̕`�揈��
	DrawExplosion();

	//�e�̕`�揈��
	DrawBullet();

	//���[�j���O�̕`�揈��
	DrawWarning();
	
	//�X�R�A�̕`�揈��
	DrawScore();

	//���C�t�̕`�揈��
	DrawLife();

	//���Ԃ̕`�揈��
	DrawTime();

	if (g_bPause == true)
	{
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;
	g_nCounterGameState = 0;
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=========================================================================================================================
// �Q�[����Ԃ̎擾
//=========================================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}

