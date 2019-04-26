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
#include "pause.h"			//�|�[�Y
#include "explosion.h"		//����
#include "meshbg.h"			//���b�V���V�����_�[
#include "meshfield.h"		//���b�V���t�B�[���h
#include "wall.h"			//��
#include "shadow.h"			//�e
#include "object.h"			//�I�u�W�F�N�g
#include "billboord.h"		//�r���{�[�h
#include "bullet.h"			//�o���b�g
#include "effect.h"			//�G�t�F�N�g
#include "light.h"			//���C�g
#include "camera.h"			//�J����
#include "sound.h"			//�T�E���h
#include "score.h"			//�X�R�A
#include "time.h"			//�^�C��
#include "camera.h"			//�J����
#include "herimodel.h"		//�w�����f��
#include "frame.h"			//�g
#include "length.h"			//�G���W��
#include "item.h"			//�A�C�e��
#include "possession.h"		//������
#include "Blood.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
GAMESTATE g_gameState;						//�Q�[�����
int g_nCounterGameState;					//��ԃJ�E���^�[
bool g_bPause;								//�|�[�Y
bool g_bMenu;								//���j���[

//=========================================================================================================================
// �w�i����������
//=========================================================================================================================
void InitGame(void)
{
	//�J�����̂ۂ��񂽁@
	Camera *pCamera = GetCamera();
	g_gameState = GAMESTATE_NONE;	//�Q�[�����
	g_nCounterGameState = 0;

	// �|���S���̏���������
	//InitPolygon();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	//�w�i�̏���������
	InitMeshBg();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//�ǂ̏���������
	InitWall();

	//�e�̏���������
	InitShadow();

	//���f���̏���������
	//InitPlayer();

	//�w�����f���̏�����
	InitPlayer2();

	//�I�u�W�F�N�g�̏���������
	InitObject();

	//�r���{�[�h�̏���������
	InitBillBoord();

	//�e�̏���������
	InitBullet();

	// ���̏���������
	InitBlood();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�����̏���������
	InitExplosion();

	//�X�R�A�̏���������
	InitScore();

	//�^�C���̏���������
	InitTime();

	//�����̏���������
	InitLength();

	//�g�̏���������
	InitFrame();

	//�|�[�Y�̏���������
	InitPause();

	//�X�R�A�̕\��
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 580, SCREEN_HEIGHT / 2 - 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 50);

#if 1

	{//����3�ԖډE���̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(855, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(855, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(855, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(855, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(855, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(855, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(945, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//����2�ԖډE���̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(445, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(445, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(445, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(445, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(445, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(445, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(535, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//����1�ԖډE���̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(159, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(159, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(159, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(159, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(159, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(159, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(245, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//�^�񒆂̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-59, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-59, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-59, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-59, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-59, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-59, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-145, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//����3�n�ԍ����̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-1059, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-1059, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-1059, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-1059, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-1145, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//����2�Ԗڍ����̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-759, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-759, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-759, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-759, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-759, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-759, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-845, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	{//����1�Ԗڍ����̑�ʂ�
		for (int nCount = 0; nCount < 8; nCount++)
		{
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-465, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, 1110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-465, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, 610 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-465, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, 110 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-465, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, -390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-465, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, -890 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			//�r���{�[�h
			SetBillBoord(D3DXVECTOR3(-465, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
			SetBillBoord(D3DXVECTOR3(-555, 0, -1390 + nCount * 50.0f), D3DXVECTOR3(0, 0, 0), 0);
		}
	}
	//�]���r�c��
#if 1
	//
	//���Q
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, -985.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, -930.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, -950.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, -970.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//���P
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, -485.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, -430.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, -450.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, -470.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//���S
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, 20.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, 65.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, 40.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, 60.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//�E�P
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1380.0f + nCount * 90.0f + rand() % (2 * 5), 0, 520.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1300.0f + nCount * 70.0f + rand() % (2 * 5), 0, 565.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1350.0f + nCount * 80.0f + rand() % (2 * 5), 0, 540.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 40; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1400.0f + nCount * 70.0f + rand() % (2 * 5), 0, 560.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//�E�Q
	//
	//�]���r
	for (int nCount = 0; nCount < 20; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1080.0f + nCount * 90.0f + rand() % (2 * 5), 0, 1020.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1000.0f + nCount * 70.0f + rand() % (2 * 5), 0, 1065.0f + rand() % (2 * -10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 25; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1050.0f + nCount * 80.0f + rand() % (2 * 5), 0, 1040.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1100.0f + nCount * 70.0f + rand() % (2 * 5), 0, 1060.0f + rand() % (2 * 10)), D3DXVECTOR3(0, 0, 0), 4);
	}
#endif
	//�]���r����
#if 1
	//
	//���S
	//
	//�]���r
	for (int nCount = 0; nCount < 25; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(1170.0f + rand() % (2 * 5), 0, -900.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(1190.0f + rand() % (2 * 5), 0, -850.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(1210.0f + rand() % (2 * 5), 0, -890.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(1240.0f + rand() % (2 * 5), 0, -900.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//���R
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(870.0f + rand() % (2 * 5), 0, -1200.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(890.0f + rand() % (2 * 5), 0, -1150.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(910.0f + rand() % (2 * 5), 0, -1190.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(940.0f + rand() % (2 * 5), 0, -1200.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//���Q
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(470.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(490.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(510.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(540.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//���P
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(170.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(190.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(210.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(240.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//����
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-70.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-90.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-110.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-140.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//�E�P
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-470.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-490.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-510.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-540.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//�E�Q
	//
	//�]���r
	for (int nCount = 0; nCount < 30; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-770.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-790.0f + rand() % (2 * 5), 0, -1350.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-810.0f + rand() % (2 * 5), 0, -1390.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	for (int nCount = 0; nCount < 35; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-840.0f + rand() % (2 * 5), 0, -1400.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
	//
	//�E�R
	//
	//�]���r
	for (int nCount = 0; nCount < 25; nCount++)
	{
		SetBillBoord(D3DXVECTOR3(-1070.0f + rand() % (2 * 5), 0, -1000.0f + nCount * 70.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1140.0f + rand() % (2 * 5), 0, -1000.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1110.0f + rand() % (2 * 5), 0, -990.0f + nCount * 80.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
		SetBillBoord(D3DXVECTOR3(-1090.0f + rand() % (2 * 5), 0, -950.0f + nCount * 90.0f + rand() % (2 * 20)), D3DXVECTOR3(0, 0, 0), 4);
	}
#endif
#endif

	//�I�u�W�F�N�g
	SetObject(D3DXVECTOR3(40,0,-95),D3DXVECTOR3(0,0,0));
	SetObject(D3DXVECTOR3(100, 0, 0), D3DXVECTOR3(0, 0, 0));

	g_gameState = GAMESTATE_NORMAL;		//�ʏ��Ԃɐݒ�

	//�|�[�Y���g�p���ĂȂ���Ԃɂ���
	g_bPause = false;

	g_bMenu = false;
}

//=========================================================================================================================
// �w�i�I������
//=========================================================================================================================
void UninitGame(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//�����̏I������
	UninitExplosion();

	//�w�i�̏I������
	UninitMeshBg();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//�ǂ̏I������
	UninitWall();

	//�w�����f���̏�����
	UninitPlayer2();

	//�I�u�W�F�N�g�̏I������
	UninitObject();

	//�e�̏I������
	UninitShadow();

	//�e�̏I������
	UninitBullet();

	//���̏I������
	UninitBlood();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�r���{�[�h�̏I������
	UninitBillBoord();

	//�����̏I������
	UninitExplosion();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C���̏I������
	UninitTime();

	//�����̏I������
	UninitLength();

	//�g�̏I������
	UninitFrame();

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
		//�J�����̍X�V����
		UpdateCamera();

		//���C�g�̍X�V����
		UpdateLight();

		//�����̍X�V����
		UpdateExplosion();

		//�w�i�̍X�V����
		UpdateMeshBg();

		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshField();

		//�ǂ̍X�V����
		UpdateWall();

		//���f���̍X�V����
		//UpdatePlayer();

		//�w�����f���̏�����
		UpdatePlayer2();

		//�I�u�W�F�N�g�̍X�V����
		UpdateObject();

		//�e�̍X�V����
		UpdateShadow();

		//�r���{�[�h�̍X�V����
		UpdateBillBoord();

		//�e�̍X�V����
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�����̍X�V����
		UpdateExplosion();

		//���̍X�V����
		UpdateBlood();

		//�^�C���̍X�V����
		UpdateTime();

		//�����̍X�V����
		UpdateLength();

		//�g�̍X�V����
		UpdateFrame();

		//�X�R�A�̍X�V����
		UpdateScore();
	}
	else if (g_bPause == true)
	{//true�ɂȂ�����|�[�Y���X�V����
		//�|�[�Y�̍X�V����
		UpdatePause();
	}
	switch (g_gameState)
	{
	case GAMESTATE_NORMAL:
		break;
	case GAMESTATE_CLEAR:
	case GAMESTATE_OVER:
		g_nCounterGameState++;

		if (g_nCounterGameState >= 120)
		{
			// = GAMESTATE_NONE;
			//��ʁi���[�h�j�̐ݒ�
			SetFade(MODE_RESULT);
		}
		break;
	}
}

//=========================================================================================================================
// �w�i�`�揈��
//=========================================================================================================================
void DrawGame(void)
{
	//�J�����̕`�揈��
	SetCamera(CAMERA_TYPE_GAME);

	//�w�i�̕`�揈��
	DrawMeshBg();

	//���b�V���t�B�[���h�̕`�揈��
	DrawMeshField();

	//�ǂ̕`�揈��
	DrawWall();

	//�w�����f���̏�����
	DrawPlayer2();

	//�I�u�W�F�N�g�̕`�揈��
	DrawObject();

	//���̕`�揈��
	DrawBlood();

	//�e�̕`�揈��
	DrawShadow();

	//�r���{�[�h�̕`�揈��
	DrawBillBoord();

	//�e�̕`�揈��
	DrawBullet();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�����̕`�揈��
	DrawExplosion();

	//�g�̕`�揈��
	DrawFrame();

	//�����̕`�揈��
	DrawLength();

	//�X�R�A�̕`�揈��
	DrawScore();

	if (g_bPause == true)
	{//�|�[�Y��true��������
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