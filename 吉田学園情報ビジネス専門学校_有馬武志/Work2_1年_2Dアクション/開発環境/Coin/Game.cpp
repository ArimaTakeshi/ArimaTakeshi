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
#include "game.h"			//�Q�[��
#include "player.h"			//�v���C���[
#include "fade.h"			//�t�F�[�h
#include "input.h"			//�L�[�{�[�h����
#include "time.h"			//����
#include "bg.h"				//�w�i
#include "block.h"			//�u���b�N
#include "score.h"			//�X�R�A
#include "item.h"			//�A�C�e��
#include "time.h"			//�^�C�}�[
#include "pause.h"			//�|�[�Y
#include "itemcount.h"		//�A�C�e���J�E���g
#include "sound.h"			//�T�E���h
#include "life.h"			//���C�t
#include "explosion.h"		//����
#include "enemy.h"			//�G
#include "ranking.h"		//�����L���O
#include "menu.h"			//���j���[
#include "effect.h"			//���ӂ���tp
//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void SetStage(void);

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
GAMESTATE g_gameState;	//�Q�[�����
STAGENUM g_StageState;						// �X�e�[�W���
int g_nCounterGameState;					//��ԃJ�E���^�[
bool g_bPause;								//�|�[�Y
bool g_bMenu;								//���j���[
int	g_nCntSetStage;							// �X�e�[�W�Z�b�g�J�E���^

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitGame(void)
{
	g_gameState = GAMESTATE_NONE;	//�Q�[�����
	g_nCounterGameState = 0;

	//�w�i�̏���������
	InitBG();

	//�����̏���������
	InitExplosion();

	//�v���C���[����������
	InitPlayer();

	//�u���b�N�̏���������
	InitBlock();

	//�G�̏���������
	InitEnemy();

	//�X�R�A�̏���������
	InitScore();

	//�A�C�e���J�E���g�̏���������
	InitItemCount();

	//�A�C�e���̏���������
	InitItem();

	//���C�t�̏���������
	InitLife();

	//�^�C���̏���������
	InitTime();

	//�|�[�Y�̏���������
	InitPause();

	//���j���[�̏���������
	InitMenu();

	InitEffect();

	//�X�R�A�̕\��
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 530,SCREEN_HEIGHT / 2 - 350,0.0f),D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),50,50);

	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�
	//g_nCounterGameState = 0;
	g_nCntSetStage = 0;					// �J�E���^������
	//�J�n�X�e�[�W
	g_StageState = STAGENUM_1;			// �X�e�[�W���

	//�|�[�Y���g�p���ĂȂ���Ԃɂ���
	g_bPause = false;

	g_bMenu = false;
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBG();

	//�����̏I������
	UninitExplosion();

	//�v���C���[�̏I������
	UninitPlayer();

	//�u���b�N�̏I������
	UninitBlock();

	//�G�̏I������
	UninitEnemy();

	//�X�R�A�̏I������
	UninitScore();

	//���j���[�̏I������
	UninitMenu();

	//�A�C�e���J�E���g�̏I������
	UninitItemCount();

	//�A�C�e���̏I������
	UninitItem();

	//���C�t�̏I������
	UninitLife();

	//�^�C���̏I������
	UninitTime();

	//�|�[�Y�̏I������
	UninitPause();

	UninitEffect();
}
//=========================================================================================================================
// �w�i�X�V����
//=========================================================================================================================
void UpdateGame(void)
{
	//�|�[�Y�̏���
	if (GetKeyboardTrigger(DIK_P) == true)
	{//P�L�[�������ꂽ��
		g_bPause = g_bPause ? false : true;

		if (g_bPause == false)
		{//�J����
			PlaySound(SOUND_LABEL_SE_OPEN000);
		}
		else
		{//���艹
			PlaySound(SOUND_LABEL_SE_DOWN000);
		}
	}
	if (g_bPause == false && g_bMenu == false)
	{//���i��false�ɂ��Ă���
		//�w�i�̍X�V����
		UpdateBG();

		//�����̍X�V����
		UpdateExplosion();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�u���b�N�̍X�V����
		UpdateBlock();

		//�G�̍X�V����
		UpdateEnemy();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�A�C�e���J�E���g�̍X�V����
		UpdateItemCount();

		//���C�t�̍X�V����
		UpdateLife();

		//�A�C�e���̍X�V����
		UpdateItem();

		//�^�C���̍X�V����
		UpdateTime();

		UpdateEffect();

		//�X�e�[�W�ݒ�
		SetStage();
	}
	else if (g_bPause == true)
	{//true�ɂȂ�����|�[�Y���X�V����
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	else if(g_bMenu == true)
	{
		//���j���[�̍X�V����
		UpdateMenu();
	}

	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 120)
		{
			// = GAMESTATE_NONE;
			//��ʁi���[�h�j�̐ݒ�
			SetFadeMode(MODE_RESULT);
		}
		break;
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 120)
		{
			// = GAMESTATE_NONE;
			//��ʁi���[�h�j�̐ݒ�
			SetFadeMode(MODE_RESULT);
		}
		break;
	}
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBG();

	//�����̕`�揈��
	DrawExplosion();

	//�u���b�N�̕`�揈��
	DrawBlock();

	//�G�̕`�揈��
	DrawEnemy();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�A�C�e���J�E���g�̕`�揈��
	DrawItemCount();

	//�A�C�e���̕`�揈��
	DrawItem();

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//���C�t�̕`�揈��
	DrawLife();

	//�^�C���̕`�揈��
	DrawTime();

	DrawEffect();

	if (g_bPause == true)
	{//�|�[�Y��true��������
		//�|�[�Y�̕`�揈��
		DrawPause();
	}
	if(g_bMenu == true)
	{//�|�[�Y��true��������

		//���j���[�̕`�揈��
		DrawMenu();

		//�A�C�e���J�E���g�̕`�揈��
		DrawItemCount();

		//�X�R�A�̕`�揈��
		DrawScore();

		//���C�t�̕`�揈��
		DrawLife();

		//************************************
		// �A�C�e���u���{�R�C���v�̔z�u
		//************************************

		////���ؗp���{�R�C��
		SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

	}
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetPauseState(bool bPause)
{
	g_bPause = bPause;
}
//=========================================================================================================================
// �Q�[����Ԃ̐ݒ�
//=========================================================================================================================
void SetMenuState(bool bMenu)
{
	g_bMenu = bMenu;
}
//=========================================================================================================================
// �Q�[����Ԃ̎擾
//=========================================================================================================================
GAMESTATE GetGameState(void)
{
	return g_gameState;
}
//=========================================================================================================================
// �Q�[����Ԃ̎擾
//=========================================================================================================================
STAGENUM GetNumState(void)
{
	return  g_StageState;
}
//=========================================================================================================================
// �Q�[���ݒ菈��
//=========================================================================================================================
void SetStageState(STAGENUM stage)
{
	if (g_StageState != stage)
	{
		DeleteItem();
		DeleteBlock();
		DeleteEnemy();
		DeletePlayer();
		DeleteTime();
	}

		if (g_StageState == STAGENUM_1)
		{

		}
		else if (g_StageState == STAGENUM_2)
		{

		}
		else if (g_StageState == STAGENUM_3)
		{

		}
		else if (g_StageState == STAGENUM_4)
		{

		}
		else if (g_StageState == STAGENUM_5)
		{

		}
		else if (g_StageState == STAGENUM_6)
		{

		}
		/*else if (g_StageState == STAGENUM_7)
		{

		}*/

	g_StageState = stage;			// ��Ԃ��L��
	g_nCntSetStage = 0;
}

//==================================================================================================
// �X�e�[�W�ݒ�
//==================================================================================================
void SetStage(void)
{
	if (g_nCntSetStage == 0)
	{
//=================================================================================
//	�X�e�[�W1
//=================================================================================
		if (g_StageState == STAGENUM_1)
		{
			//���΃G�t�F�N�g
			//SetParticleEffect(D3DXVECTOR3(50, 0, 0), EFFECTTYPE_ERUPTION, 10, 3, 500, 0);

			//���G�t�F�N�g
			SetParticleEffect(D3DXVECTOR3(100.0f, -50.0f, 0.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
			//SetParticleEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);

			//���G�t�F�N�g
			//SetParticleEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);

			//�΂̕��G�t�F�N�g
			//SetParticleEffect(D3DXVECTOR3(0.0f, 0.0f, 0.0f), EFFECTTYPE_POWDER, 3, 1, 50, 0);


			//************************************
			// �u���b�N�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
			}
			*/
			for (int nCount = 0; nCount < 32; nCount++)
			{//  �P�i�ڏ�
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ���
				SetBlock(D3DXVECTOR3(40 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ���
				SetBlock(D3DXVECTOR3(320 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ��E
				SetBlock(D3DXVECTOR3(760 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ��E
				SetBlock(D3DXVECTOR3(1040 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 320, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 320, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  �S�i�ڏ�����
				SetBlock(D3DXVECTOR3(320 + nCount * 40.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  �S�i�ڏ�����
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			//************************************
			// �u���b�N�̔z�u�u�y�����̏��v
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//���̕Ǒւ��
				SetBlock(D3DXVECTOR3(0, 480 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�E�̕Ǒւ��
				SetBlock(D3DXVECTOR3(1240, 480 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//���ړ�����
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//���ړ�����
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�����鏰�v
			//************************************

			////���ؗp�����鏰�i��ɏ�����������j
			SetBlock(D3DXVECTOR3(520, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(560, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(680, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(720, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�󂹂�u���b�N�v
			//************************************

			////���ؗp�󂹂鏰�i������̓��˂��j
			SetBlock(D3DXVECTOR3(600, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);
			SetBlock(D3DXVECTOR3(640, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�������鏰�v
			//************************************

			////���ؗp�������鏰���ɉ���
			SetBlock(D3DXVECTOR3(1080, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 120, 40);

			//************************************
			// �u���b�N�̔z�u�u�������鏰�v
			//************************************
			////���ؗp�������鏰�E�ɉ���
			SetBlock(D3DXVECTOR3(160, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 15, 120, 40);

			//************************************
			// �u���b�N�̔z�u�u�ړ����v
			//************************************

			//���ؗp�c�ړ�����
			SetBlock(D3DXVECTOR3(240, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
			SetBlock(D3DXVECTOR3(280, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

			////���ؗp�c�ړ����E
			SetBlock(D3DXVECTOR3(960, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
			SetBlock(D3DXVECTOR3(1000, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�x���g�R���x�A�[�v
			//************************************

			//�E�ɉ������
			SetBlock(D3DXVECTOR3(440, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 50, 160);
			//���ɉ������
			SetBlock(D3DXVECTOR3(680, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 50, 160);

			//************************************
			// �u���b�N�̔z�u�u�����ȃu���b�N�v
			//************************************
			////���ؗp�����u���b�N
			SetBlock(D3DXVECTOR3(1240, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);

			//************************************
			// �A�C�e���u�R�C���v�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�n�܂�ʒu + �J�E���g * �R�C���Ƃ̉��� , �ݒu�̍��� , 0.0f ),D3DXCOLOR(RGB�J���[),�^�C�v);
			}
			*/
			for (int nCount = 0; nCount < 8; nCount++)
			{//�P�i�ڃR�C��
				SetItem(D3DXVECTOR3(220.0f + nCount * 120, 630, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڔj��u���b�N�̉�
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 560.0f + nCount * 70.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�Q�i�ډ����鏰�̍�
				SetItem(D3DXVECTOR3(60 + nCount * 40.0f, 450, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�Q�i�ډ����鏰�̍�
				SetItem(D3DXVECTOR3(60 + nCount * 40.0f, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�R�i�ډ����鏰�̍�
				SetItem(D3DXVECTOR3(60 + nCount * 40.0f, 280, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�Q�i�ډ����鏰�̉E
				SetItem(D3DXVECTOR3(1140 + nCount * 40.0f, 450, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�Q�i�ډ����鏰�̉E
				SetItem(D3DXVECTOR3(1140 + nCount * 40.0f, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�R�i�ډ����鏰�̉E
				SetItem(D3DXVECTOR3(1140 + nCount * 40.0f, 280, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 7; nCount++)
			{//�S�i�ڃR�C��
				SetItem(D3DXVECTOR3(340.0f + nCount * 100, 160, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}

			//************************************
			// �A�C�e���u�ԃR�C���v�̔z�u
			//************************************

			////���ؗp�ԃR�C��
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 220, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// �A�C�e���u���v�v�̔z�u
			//************************************

			////���ؗp���v
			SetItem(D3DXVECTOR3(40, 140, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

			//************************************
			// �A�C�e���u���{�R�C���v�̔z�u
			//************************************

			////���ؗp���{�R�C��
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//g_StageState = STAGENUM_2;		// �X�e�[�W2�Ɉڍs
			////SetNumStage(g_StageState);	// �X�e�[�W�ԍ��\��

		}
//=================================================================================
//	�X�e�[�W�Q
//=================================================================================
		else if (g_StageState == STAGENUM_2)
		{
			//************************************
			// �u���b�N�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
			}
			*/
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �P�i�ڏ��E
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//  �P�i�ڏ���
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �P�i�ڏ���
				SetBlock(D3DXVECTOR3(680 + nCount * 560.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�@�������R�P�i�ڍ�
				SetBlock(D3DXVECTOR3(200 + nCount * 120.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�@�������R�Q�i�ڍ�
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 600, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�@�������R�P�i�ډE
				SetBlock(D3DXVECTOR3(920 + nCount * 120.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�@�������R�Q�i�ډE
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 600, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  �Q�i�ڏ��E
				SetBlock(D3DXVECTOR3(40 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڒ�����
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ���
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 11; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 1; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(520 + nCount * 40.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ�K�i
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 220 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u���ǁv
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ����
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 680, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ����
				SetBlock(D3DXVECTOR3(560 + nCount * 120.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 460, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�y�����̏��v
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//  �P�i��
				SetBlock(D3DXVECTOR3(200 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  �P�i��
				SetBlock(D3DXVECTOR3(920 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �������R�̒�
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �������R�̒�
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ�K�i�@���̉�
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 260 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  �Q�i�ڏ�K�i�@�y�̉�
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 300 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  �Q�i�ڏ�K�i�@�y�̉�
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 340 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �Q�i�ڏ�K�i�@�y�̉�
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 380 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 1; nCount++)
			{//  �Q�i�ڏ�K�i�@�y�̉�
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 420 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�󂹂�u���b�N�v
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//  �Q�i�ڂ̉󂹂鏰
				SetBlock(D3DXVECTOR3(200 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�����鏰�v
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//	�Q�i�ڂ̗����鏰
				SetBlock(D3DXVECTOR3(920 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�������鏰�v
			//************************************
			//�@�Q�i�ڏ�̓������鏰
			SetBlock(D3DXVECTOR3(400, 260, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 160, 40);

			//************************************
			// �u���b�N�̔z�u�u�x���g�R���x�A�[�v
			//************************************

			//�E�ɉ������
			SetBlock(D3DXVECTOR3(1080, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 50, 120);
			//���ɉ������
			SetBlock(D3DXVECTOR3(760, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 50, 160);

			//************************************
			// �A�C�e���u�R�C���v�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�n�܂�ʒu + �J�E���g * �R�C���Ƃ̉��� , �ݒu�̍��� , 0.0f ),D3DXCOLOR(RGB�J���[),�^�C�v);
			}
			*/
			for (int nCount = 0; nCount < 4; nCount++)
			{//�P�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(220.0f + nCount * 40, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڏ�R��̃R�C��
				SetItem(D3DXVECTOR3(220.0f + nCount * 120, 610, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڏ�R��̃R�C��
				SetItem(D3DXVECTOR3(180.0f + nCount * 200, 610, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڏ�R��̃R�C��
				SetItem(D3DXVECTOR3(180.0f + nCount * 200, 655, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�Q�i�ڍ���̃R�C��
				SetItem(D3DXVECTOR3(80.0f + nCount * 40, 370, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�Q�i�ڍ���̃R�C��
				SetItem(D3DXVECTOR3(80.0f + nCount * 40, 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�R�i�ڂɏオ��Ƃ��̃R�C��
				SetItem(D3DXVECTOR3(480.0f, 270.0f + nCount * 60, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�R�i�ڏ�̃R�C��
				SetItem(D3DXVECTOR3(70.0f + nCount * 100, 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�R�i�ڏ�̃R�C��
				SetItem(D3DXVECTOR3(120.0f + nCount * 100, 140, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//  �Q�i�ڏ�K�i
				SetItem(D3DXVECTOR3(740.0f + nCount * 40.0f, 190 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//	�Q�i�ڗ����鏰�̉�
				SetItem(D3DXVECTOR3(940.0f + nCount * 40.0f, 500, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڂ̃x���g�R���x���[�̍���
				SetItem(D3DXVECTOR3(800 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڂ̃x���g�R���x���[�̉E��
				SetItem(D3DXVECTOR3(1120 + nCount * 40.0f, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//�P�i�ڌ��ɗ����鎞�ɂƂ��R�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 300.0f + nCount * 90.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//************************************
			// �A�C�e���u�ԃR�C���v�̔z�u
			//************************************

			//������щz���̂Ƃ���̃R�C��
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// �u���b�N�̔z�u�u�����ȃu���b�N�v
			//************************************

			//�P�i�ڂ̏�
			SetBlock(D3DXVECTOR3(520, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);

			//************************************
			// �A�C�e���u���v�v�̔z�u
			//************************************

			//�Q�i�ډE�[
			SetItem(D3DXVECTOR3(1190, 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);


			//************************************
			// �A�C�e���u���t�����v�̔z�u
			//************************************

			//SetItem(D3DXVECTOR3(1190, 250, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7);

			//************************************
			// �A�C�e���u���{�R�C���v�̔z�u
			//************************************

			////���ؗp���{�R�C��
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);



			////���ؗp�G
			//SetEnemy(D3DXVECTOR3(200, 100, 0.0f), 0);

			//g_StageState = STAGENUM_3;		// �X�e�[�W3�Ɉڍs
			//SetNumStage(g_StageState);		// �X�e�[�W�ԍ��\��
		}
//=================================================================================
//	�X�e�[�W�R
//=================================================================================
		else if (g_StageState == STAGENUM_3)
		{
			//************************************
			// �u���b�N�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
			}
			*/
			for (int nCount = 0; nCount < 10; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 10; nCount++)
			{//�P�i�ډE�ꏰ
				SetBlock(D3DXVECTOR3(880 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 11; nCount++)
			{//�Q�i�ډE��
				SetBlock(D3DXVECTOR3(850 + nCount * 40.0f, 520, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 11; nCount++)
			{//�Q�i�ڍ���
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 520, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 16; nCount++)
			{//�R�i�ڒ�����
				SetBlock(D3DXVECTOR3(320 + nCount * 40.0f, 310, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�R�i�ڒ�����
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�R�i�ڒ��E��
				SetBlock(D3DXVECTOR3(1120 + nCount * 40.0f, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 13; nCount++)
			{//�S�i�ډE��
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 140, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 13; nCount++)
			{//�S�i�ڍ���
				SetBlock(D3DXVECTOR3(770 + nCount * 40.0f, 140, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40); /*(13 * 40 = 520) 520 + 520 = 1040 - 1280 = 140 + 520 = 660 + 110 = 770*/
			}
			//************************************
			// �u���b�N�̔z�u�u�y�����̏��v
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(0, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(1240, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�����鏰�v
			//************************************

			////���ؗp�����鏰�i��ɏ�����������j
			SetBlock(D3DXVECTOR3(1040, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			SetBlock(D3DXVECTOR3(1080, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�󂹂�u���b�N�v
			//************************************

			////���ؗp�󂹂鏰�i������̓��˂��j
			SetBlock(D3DXVECTOR3(160, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);
			SetBlock(D3DXVECTOR3(200, 370, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 5, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�������鏰�v
			//************************************

			////���ؗp�������鏰
			SetBlock(D3DXVECTOR3(950, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 120, 50);

			//************************************
			// �u���b�N�̔z�u�u�ړ����v
			//************************************

			////���ؗp���ړ���
			//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2, 520, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 40, 40);
			//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2, 640, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1, 40, 40);

			////���ؗp�c�ړ�����
//			SetBlock(D3DXVECTOR3(240, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
	//		SetBlock(D3DXVECTOR3(280, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

		//	////���ؗp�c�ړ����E
			//SetBlock(D3DXVECTOR3(960, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);
			//SetBlock(D3DXVECTOR3(1000, 310, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�x���g�R���x�A�[�v
			//************************************

			//�E�ɉ������
			SetBlock(D3DXVECTOR3(400, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3, 50, 200);
			//���ɉ������
			SetBlock(D3DXVECTOR3(680, 680, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4, 50, 200);

			//************************************
			// �u���b�N�̔z�u�u�����ȃu���b�N�v
			//************************************

			////���ؗp�����u���b�N
			SetBlock(D3DXVECTOR3(40, 560, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 9, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�������v
			//************************************

			////���ؗp������
			//SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 10, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 40, 40);
			//SetBlock(D3DXVECTOR3(60,540, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 40, 40);

			//************************************
			// �A�C�e���u�R�C���v�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�n�܂�ʒu + �J�E���g * �R�C���Ƃ̉��� , �ݒu�̍��� , 0.0f ),D3DXCOLOR(RGB�J���[),�^�C�v);
			}
			*/
			for (int nCount = 0; nCount < 7; nCount++)
			{//�P�i�ڒ�������R�C��
				SetItem(D3DXVECTOR3(460.0f + nCount * 60, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�P�i�ډE�[�R�C��
				SetItem(D3DXVECTOR3(1090.0f + nCount * 40, 650, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
				SetItem(D3DXVECTOR3(1090.0f + nCount * 40, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//2�i�ڍ�����R�C��
				SetItem(D3DXVECTOR3(30.0f + nCount * 60, 480, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//2�i�ڒ����R�C��
				SetItem(D3DXVECTOR3(490.0f + nCount * 100, 400, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//2�i�ډE����R�C��
				SetItem(D3DXVECTOR3(1070.0f + nCount * 60, 480, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�㉺�ړ����̏㏰��R�C��
				SetItem(D3DXVECTOR3(280, 270.0f + nCount * 60, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�㉺�ړ����̏㏰��R�C��
				SetItem(D3DXVECTOR3(1000, 270.0f + nCount * 60, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 7; nCount++)
			{//3�i�ڒ�������R�C��
				SetItem(D3DXVECTOR3(430.0f + nCount * 70, 270, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//4�i�ډE���R�C��
				SetItem(D3DXVECTOR3(50.0f + nCount * 100, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//4�i�ڍ����R�C��
				SetItem(D3DXVECTOR3(840.0f + nCount * 100, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//************************************
			// �A�C�e���u���΁v�̔z�u
			//************************************

			////���ؗp����
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1);

			//************************************
			// �A�C�e���u�ԃR�C���v�̔z�u
			//************************************

			////���ؗp�ԃR�C��
			SetItem(D3DXVECTOR3(30, 220, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// �A�C�e���u���v�v�̔z�u
			//************************************

			////���ؗp���v
			SetItem(D3DXVECTOR3(1230, 220, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

			//************************************
			// �A�C�e���u�󔠁v�̔z�u
			//************************************

			////���ؗp��
			//SetItem(D3DXVECTOR3(150, 600, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 4);

			//************************************
			// �A�C�e���u���{�R�C���v�̔z�u
			//************************************

			////���ؗp���{�R�C��
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//g_StageState = STAGENUM_4;		// �X�e�[�W4�Ɉڍs
			//SetNumStage(g_StageState);		// �X�e�[�W�ԍ��\��
		}
		else if (g_StageState == STAGENUM_4)
		{// �X�e�[�W�S
			//************************************
			// �u���b�N�̔z�u
			//************************************
			/*
			 for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
				SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
			}
			*/
			for (int nCount = 0; nCount < 32; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�S�[���h�u���b�N�v
			//************************************
			for (int nCount = 0; nCount < 4; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 80 + nCount * 40.0f , 120, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 120 + nCount * 200.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 160 + nCount * 280.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 160 + nCount * 280.0f, 240, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 160, 280 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 120 + nCount * 200.0f, 480, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 40 + nCount * 40.0f, 520, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 120, 400 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�{�[�i�X�u���b�N�I
				SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40 + nCount * 40.0f,360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 40, 40);
			}

			// �u���b�N�̔z�u�u���ǁv
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ����
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 680, 40);
			}

			//************************************
			// �A�C�e���u�R�C���v�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�n�܂�ʒu + �J�E���g * �R�C���Ƃ̉��� , �ݒu�̍��� , 0.0f ),D3DXCOLOR(RGB�J���[),�^�C�v);
			}
			*/
			for (int nCount = 0; nCount < 4; nCount++)
			{//�P�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 60 + nCount * 40.0f, 180, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�Q�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 220, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�R�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 260, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�S�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 300, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�T�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 340, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�U�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 380, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�V�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�W�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100 + nCount * 40.0f, 460, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�X�i�ڃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2 - 60 + nCount * 40.0f, 500, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//************************************
			// �A�C�e���u�ԃR�C���v�̔z�u
			//************************************
			////���ؗp�ԃR�C��
			SetItem(D3DXVECTOR3(SCREEN_WIDTH / 2, 100, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// �A�C�e���u���{�R�C���v�̔z�u
			//************************************

			////���ؗp���{�R�C��
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//************************************
			// �A�C�e���u�V���b�v�v�̔z�u
			//************************************

			////���ؗp���v
			SetItem(D3DXVECTOR3(250, 580, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 9);

			//g_StageState = STAGENUM_5;		// �X�e�[�W5�Ɉڍs
			//SetNumStage(g_StageState);		// �X�e�[�W�ԍ��\��
		}
		else if (g_StageState == STAGENUM_5)
		{// �X�e�[�W�T
		 //************************************
		 // �u���b�N�̔z�u
		 //************************************
		 /*
		 for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
		 {
		 SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
		 }
		 */
		 //�������X�|�[�������Ȃ��悤��
			SetBlock(D3DXVECTOR3(160, 640, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			for (int nCount = 0; nCount < 7; nCount++)
			{//  �P�i�ڏ���
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//  �P�i�ڏ�����
				SetBlock(D3DXVECTOR3(360 + nCount * 120.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 7; nCount++)
			{//  �P�i�ڏ��E
				SetBlock(D3DXVECTOR3(1000 + nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 14; nCount++)
			{//  �Q�i�ڏ��E
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(560, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			for (int nCount = 0; nCount < 2; nCount++)
			{//  �Q�i�ڏ��łƂ̊�
				SetBlock(D3DXVECTOR3(760 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  �Q�i�ڏ��łƂ̊�
				SetBlock(D3DXVECTOR3(880 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �Q�i�ڏ��łƂ̊�
				SetBlock(D3DXVECTOR3(1000 + nCount * 80.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �Q�i�ڏ��E
				SetBlock(D3DXVECTOR3(1200 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �R�i�ڏ��E���@�����鏰�Ƃ̊ԁ@
				SetBlock(D3DXVECTOR3(760 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//  �R�i�ڏ��E���@�����鏰�Ƃ̊�
				SetBlock(D3DXVECTOR3(880 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 1; nCount++)
			{//  �R�i�ڏ��E�E�@�����鏰�Ƃ̊�
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//  �R�i�ڏ��E�E�@�����鏰�Ƃ̊�
				SetBlock(D3DXVECTOR3(1200 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 13; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 9; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(120 + nCount * 40.0f, 280, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(640, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			SetBlock(D3DXVECTOR3(680, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u���ǁv
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ����
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 440, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 240, 40);
			}
			//�^�񒆂̎d�؂�
			SetBlock(D3DXVECTOR3(SCREEN_WIDTH / 2 - 40, 0, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 400, 40);
			for (int nCount = 0; nCount < 2; nCount++)
			{//  ����
				SetBlock(D3DXVECTOR3(nCount * 1240.0f, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 200, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u�y�����̏��v
			//************************************
			//���u���b�N�̂���
			for (int nCount = 0; nCount < 3; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(560 + nCount * 40.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//  �R�i�ڏ���
				SetBlock(D3DXVECTOR3(480, 200 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}

			//************************************
			// �u���b�N�̔z�u�u������ǁv
			//************************************
			//����������t�����U��
			SetBlock(D3DXVECTOR3(1000, 560, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 14, 120, 80);

			//************************************
			// �u���b�N�̔z�u�u�������鏰�v
			//************************************
			////���ؗp�������鏰�E
			SetBlock(D3DXVECTOR3(160, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7, 80, 40);

			//************************************
			// �u���b�N�̔z�u�u�������鏰�v
			//************************************
			////���ؗp�������鏰��
			SetBlock(D3DXVECTOR3(440, 320, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 15, 80, 40);

			//************************************
			// �u���b�N�̔z�u�u�Łv
			//************************************
			//for (int nCount = 0; nCount < 2; nCount++)
			//{//�ł̏�
			//	SetBlock(D3DXVECTOR3(720 + nCount * 120.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 40, 40);
			//}
			//�ł̏�
			//SetBlock(D3DXVECTOR3(1040, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 40, 40);

			//************************************
			// �u���b�N�̔z�u�u�����鏰�v
			//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//���ɗ����鏰�@���ɂ͓�
				SetBlock(D3DXVECTOR3(720 + nCount * 120.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//���ɗ����鏰�@���ɂ͓�
				SetBlock(D3DXVECTOR3(1120 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			//���ɗ����鏰�@���ɂ͓�
			SetBlock(D3DXVECTOR3(1040, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);

			//************************************
			// �A�C�e���u�R�C���v�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�n�܂�ʒu + �J�E���g * �R�C���Ƃ̉��� , �ݒu�̍��� , 0.0f ),D3DXCOLOR(RGB�J���[),�^�C�v);
			}
			*/
			for (int nCount = 0; nCount < 7; nCount++)
			{//�P�i�ڃW�����v�P�i�ڃR�C��
				SetItem(D3DXVECTOR3(260.0f + nCount * 120, 630, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 6; nCount++)
			{//�P�i�ڃW�����v�Q�i�ڃR�C��
				SetItem(D3DXVECTOR3(320.0f + nCount * 120, 470, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڃW�����v�Q�i�ڃR�C��
				SetItem(D3DXVECTOR3(1100.0f + nCount * 30, 630, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//�Q�i�ړŏ�P�i�ڃR�C��
				SetItem(D3DXVECTOR3(740.0f + nCount * 80, 360, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�Q�i�ڂ���R�i�ڂ̃W�����v�R�C��
				SetItem(D3DXVECTOR3(660, 220 + nCount * 100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//�������炵���R�C���@�W�����v�̋O��
			SetItem(D3DXVECTOR3(695, 175, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);

			for (int nCount = 0; nCount < 2; nCount++)
			{//�R�i�ڗ�����u���b�N�̏�
				SetItem(D3DXVECTOR3(740.0f + nCount * 120.0f, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�R�i�ڗ�����u���b�N�̏�
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40.0f, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			//�R�i�ڗ�����u���b�N�̏�
			SetItem(D3DXVECTOR3(1060, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);

			for (int nCount = 0; nCount < 6; nCount++)
			{//�R�i�ڍ���
				SetItem(D3DXVECTOR3(60.0f + nCount * 80.0f, 130, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//�R�i�ڍ���
				SetItem(D3DXVECTOR3(80.0f + nCount * 80.0f, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//�R�i�ڍ�����
				SetItem(D3DXVECTOR3(230.0f + nCount * 52.0f, 240, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}

			//************************************
			// �A�C�e���u���{�R�C���v�̔z�u
			//************************************

			////���ؗp���{�R�C��
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//************************************
			// �A�C�e���u�ԃR�C���v�̔z�u
			//************************************

			////���ؗp�ԃR�C��
			SetItem(D3DXVECTOR3(440, 240, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);

			//************************************
			// �A�C�e���u���v�v�̔z�u
			//************************************

			////���ؗp���v
			SetItem(D3DXVECTOR3(1210, 240, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

			//************************************
			// �A�C�e���u���t�����v�̔z�u
			//************************************

			////���ؗp���v
			SetItem(D3DXVECTOR3(1210, 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 7);

			//g_StageState = STAGENUM_6;		// �X�e�[�W6�Ɉڍs
			//SetNumStage(g_StageState);		// �X�e�[�W�ԍ��\��
		}
		else if (g_StageState == STAGENUM_6)
		{// �X�e�[�W�U
		 //************************************
		 // �u���b�N�̔z�u
		 //************************************
			 /*
			 for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			 {
				 SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
			 }
			 */
			for (int nCount = 0; nCount < 5; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//�P�i�ڒ����W�����v
				SetBlock(D3DXVECTOR3(320 + nCount * 160.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ډE��
				SetBlock(D3DXVECTOR3(1120 + nCount * 40.0f, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 8; nCount++)
			{//�Q�i�ڏ�
				SetBlock(D3DXVECTOR3(200 + nCount * 120.0f, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(1080, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

			for (int nCount = 0; nCount < 6; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(40 + nCount * 40.0f, nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 200 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 5; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(560 + nCount * 120.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(1080 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
			}
			SetBlock(D3DXVECTOR3(1240, 200, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);

		//************************************
		// �u���b�N�́u�Ƃ��v�z�u
		//************************************
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(200 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(520 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(680 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(1000 + nCount * 40.0f, 690, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 20, 40, 40);
			}

		//************************************
		// �u���b�N�̔z�u�u���ǁv
		//************************************
			SetBlock(D3DXVECTOR3(0, 440, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 240, 40);
			SetBlock(D3DXVECTOR3(1240, 240, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 11, 360, 40);


		//************************************
		// �u���b�N�̔z�u�u�����ǁv
		//************************************

			////���ؗp������
			SetBlock(D3DXVECTOR3(0, 440, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 21, 240, 40);

		//************************************
		// �u���b�N�̔z�u�u�����ǁv
		//************************************

			////���ؗp�����Ǒ������
			SetBlock(D3DXVECTOR3(0, 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 22, 200, 40);

		//************************************
		// �u���b�N�̔z�u�u�y�����̏��v
		//************************************
			//���u���b�N�̂���
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ډE��
				SetBlock(D3DXVECTOR3(1160 + nCount * 40.0f, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ډE��
				SetBlock(D3DXVECTOR3(1200 + nCount * 40.0f, 680 - nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			SetBlock(D3DXVECTOR3(1240, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);

			for (int nCount = 0; nCount < 5; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 240 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 4; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 280 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 320 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//3�i�ڏ�
				SetBlock(D3DXVECTOR3(nCount * 40.0f, 360 + nCount * 40.0f, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);
			}
			SetBlock(D3DXVECTOR3(0, 400, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 8, 40, 40);

		//************************************
		// �u���b�N�́u�Łv�z�u
		//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(240 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(360 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(480 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(600 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 420, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 12, 20, 40);
			}

		//************************************
		// �u���b�N�̔z�u�u�����鏰�v
		//************************************
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(480 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(600 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(720 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(840 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}
			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڍ��ꏰ
				SetBlock(D3DXVECTOR3(960 + nCount * 40.0f, 160, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6, 40, 40);
			}

			//************************************
			// �A�C�e���u���{�R�C���v�̔z�u
			//************************************

			////���ؗp���{�R�C��
			SetItem(D3DXVECTOR3(30, 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 6);

			//************************************
			// �A�C�e���u�R�C���v�̔z�u
			//************************************
			/*
			for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
			{
			SetBlock(D3DXVECTOR3(�n�܂�ʒu + �J�E���g * �R�C���Ƃ̉��� , �ݒu�̍��� , 0.0f ),D3DXCOLOR(RGB�J���[),�^�C�v);
			}
			*/
			SetItem(D3DXVECTOR3(1140.0f , 670, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);

			for (int nCount = 0; nCount < 2; nCount++)
			{//�P�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 620, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 570, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 520, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 470, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 3; nCount++)
			{//�P�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(1140.0f + nCount * 40, 420, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 8; nCount++)
			{//�Q�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(220 + nCount * 120.0f, 360, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}
			for (int nCount = 0; nCount < 9; nCount++)
			{//�Q�i�ڎR��̃R�C��
				SetItem(D3DXVECTOR3(230 + nCount * 120.0f, 110, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0);
			}


			////************************************
			//// �A�C�e���u�ԃR�C���v�̔z�u
			////************************************
			for (int nCount = 0; nCount < 7; nCount++)
			{
				////���ؗp�ԃR�C��
				SetItem(D3DXVECTOR3(SCREEN_WIDTH / 4  + nCount * 110.0f, 230, 0.0f), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 2);
			}

			//************************************
			// �A�C�e���u���v�v�̔z�u
			//************************************

			////���ؗp���v
			SetItem(D3DXVECTOR3(1210, 240, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3);

		}
		//else if (g_StageState == STAGENUM_7)
		//{// �X�e�[�W�V
		// //************************************
		// // �u���b�N�̔z�u
		// //************************************
		//	/*
		//	 for (�J�E���g������; �J�E���g�� < �u���b�N��; �J�E���g++)
		//	{
		//	 SetBlock(D3DXVECTOR3(�J�E���g * �u���b�N�̉��� , �ݒu�̍��� , 0) �^�C�v , ���� , ��);
		//	 }
		//	*/

		//	for (int nCount = 0; nCount < 32; nCount++)
		//	{//  �P�i�ڏ���
		//		SetBlock(D3DXVECTOR3(nCount * 40.0f, 680, 0), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0, 40, 40);
		//	}
		//}
		g_nCntSetStage = 1;
	}
}

