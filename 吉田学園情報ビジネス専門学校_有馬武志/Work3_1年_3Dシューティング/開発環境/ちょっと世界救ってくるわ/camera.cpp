//=============================================================================
//
// �J�������� [camera.cpp]
// Author :�@�L�n�@���u
//
//=============================================================================
#include "camera.h"		//�J����
#include "input.h"		//�L�[�{�[�h
#include "player.h"		//�v���C���[
#include "bullet.h"		//�e
#include "object.h"		//�I�u�W�F�N�g
#include "herimodel.h"	//�w�����f��
#include "sound.h"		//�T�E���h
#include "effect.h"		//�G�t�F�N�g

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_ANGLE			(0.01f)				//�J�����p�x�̈ړ���
#define MOVE_ANGLE1			(0.001f)			//�J�����p�x�̈ړ���
#define MOVE_CAMERA			(1200.0f)			//�J�����̋���
#define MOVE_OBJECT			(1000.0f)			//
//#define MOVE_CAMERA			(30.0f)			//�J�����̋���
#define CAMERA_KM			(1200.0f)			//�J�����̕`�拗��
#define MOVE_SPEED			(0.001f)			//�J�����̃X�s�[�h
#define MOVE_ANGLE2			(15.0f)				//�p�x
#define MOVE_ANGLE3			(0.03f)				//�������p�p�x

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Camera g_Camera;							//�J�����̏��
int g_nCount;								//�b���J�E���g
int g_CameraCount;							//�J�����̈ړ�����
float g_fCameraAngle = 45.0f;				//�p�x
float g_fRot;								//��]
float g_BulletMouserotf;					//�}�E�X�̈ʒu�ɒe���΂�

//=============================================================================
// �J�����̏���������
//=============================================================================
void InitCamera(void)
{
	//�v���C���[�̏��
	Object pObject = *GetObject();

	g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f, -400.0f);			//���_�̏����l
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
	g_Camera.vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);				//�@���̌���
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	//g_Camera.rot.y = 0.0f;									//�p�x
	g_Camera.fLength = g_Camera.posV.z - g_Camera.posR.z;		//�����̌v�Z�@�iV�̂�����R�̂����Ђ��j
	g_Camera.nType = CAMERA_TYPE_NONE;							//���
	g_fCameraAngle = 45.0f;										//�p�x
	g_CameraCount = 0;											//�J�����̐�������
	g_fRot = 0;													//�J�����̌���������
	g_BulletMouserotf = 0.0f;									//�}�E�X�̈ʒu�ɒe���΂�������
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera()
{
	//�}�E�X�̏��
	DIMOUSESTATE2 pMouse = GetMousePointer();

	//�v���C���[�̏��
	Object *pObject = GetObject();

	Player *pPlayer = GetPlayer();

	Player2 *pPlayer2 = GetPlayer2();

	Bullet *pBullet = GetBullet();

	static int nCount = 0;
	float fRot;

	//g_Camera.posV = pObject->pos;
	////g_Camera.posR�ɑ���@�@�@�@�@�@�@�@�@�@�@�@�@	���p�x�@�@�@�@�@��R�Ƃ̋���
	//g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fLength;
	//g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fLength;

	////============================
	////��s�@�̌��ɃJ�������s���悤�ɂ��鏈��
	////============================
	if (g_Camera.nType == CAMERA_TYPE_GAME)
	{//�Q�[�����J����
		//=============================
		//�@ �@�}�E�X�ŃJ��������
		//=============================
		//�����_�ʒu�ύX
		if (pMouse.lY < 0)
		{//Y���W
			g_Camera.posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
		}
		if (pMouse.lY > 0)
		{//Y���W
			g_Camera.posR.y -= cosf(D3DX_PI * 0.0f) * (pMouse.lY / 2.0f);
		}
		if (pMouse.lX < 0)
		{//X���W
			g_Camera.rot.y += (pMouse.lX / 600.0f);
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		}
		if (pMouse.lX > 0)
		{//X���W
			g_Camera.rot.y += (pMouse.lX / 600.0f);
			g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
			g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		}

		g_Camera.posR.x = g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength;
		g_Camera.posR.z = g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength;
		{
			//============================
			//      �e���o������
			//============================

			//�b���J�E���g
			nCount++;

			g_BulletMouserotf += -pMouse.lY / 30.0f;

			//�e�̏o��X�s�[�h
			if (nCount % 8 == 0)
			{
				if (GetMousePress(0) == true)
				{//�e���o��
					fRot = atan2f(powf(g_Camera.posR.y - g_Camera.posV.y, 2), powf(g_Camera.posR.x - g_Camera.posV.x, 2) + powf(g_Camera.posR.z - g_Camera.posV.z, 2));
					SetBullet(D3DXVECTOR3(g_Camera.posV.x + sinf(g_Camera.rot.y) * 0.0f, g_Camera.posV.y - sinf(fRot) * 0.0f - 0.0f, g_Camera.posV.z + cosf(g_Camera.rot.y) * 0.0f), g_Camera.rot
						,D3DXVECTOR3((sinf(g_Camera.rot.y - D3DX_PI) * -20.0f) * cosf(fRot), sinf(fRot) * -20.0f, (cosf(g_Camera.rot.y - D3DX_PI) * -20.0f) * cosf(fRot)));
					PlaySound(SOUND_LABEL_SE_SHOOT);
				}
			}
		}
		{
			//============================
			//    ���f���̈ʒu�̑��
			//============================

			//�J�����ɔ�s�@����������
			pObject[1].pos = g_Camera.posV;

			//�J�����ɏe����������
			//pObject[2].pos = g_Camera.posV;

			//�J�����̉�]�Ɣ�s�@�̉�]�������l�łȂ���΂Ȃ�Ȃ�
			pObject[1].rot.y += MOVE_SPEED;
		}
		{
			//=============================
			//          ��s�@
			//=============================

			//��]������
			g_fRot += MOVE_ANGLE1;

			if (g_fRot > D3DX_PI)
			{//������
				g_fRot = -D3DX_PI;
			}
			//============================
			//�����_���v���C���[�ɒǏ]�悤�ɂ���
			//============================
			//g_Camera.posR.x = pPlayer->pos.x;
			//g_Camera.posR.z = pPlayer->pos.z;
			//���_���v���C���[�ɒǏ]�悤�ɂ���
			g_Camera.posV.x = pPlayer->pos.x - sinf(g_fRot)* MOVE_CAMERA;
			g_Camera.posV.z = pPlayer->pos.z - cosf(g_fRot)* MOVE_CAMERA;
		}
	}
	if (g_Camera.nType == CAMERA_TYPE_DEMO)
	{//�^�C�g���̃J����
		if (g_CameraCount >= 0 && g_CameraCount <= 399)
		{//�����_�����_�ɍ����
			g_Camera.rot.y += MOVE_ANGLE1;
			if (g_Camera.rot.y > D3DX_PI)
			{//������
				g_Camera.rot.y = -D3DX_PI;
			}
			//g_Camera.posV��D3DXVECTOR3��sin��cos����
			g_Camera.posV = D3DXVECTOR3(g_Camera.posR.x + sinf(g_Camera.rot.y) * g_Camera.fLength, g_Camera.posV.y, g_Camera.posR.z + cosf(g_Camera.rot.y) * g_Camera.fLength);
		}
		if (g_CameraCount == 400)
		{//�J�����̈ʒu�������l�ɖ߂��A�p�x���߂�
			g_Camera.rot.y = 0;
			g_Camera.posV = D3DXVECTOR3(-100.0f, 50.0f, -180.0f);			//���_�̏����l
			g_Camera.posR = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);				//�����_�̏����l
		}
		if (g_CameraCount >= 401 && g_CameraCount <= 799)
		{//�J�����������^�e�ړ�������
			g_Camera.rot.y = 0;
			g_Camera.posV.z += 0.5f;
			g_Camera.posR.z += 0.5f;
		}
		if (g_CameraCount == 800)
		{//�J�����̈ʒu������������
			g_Camera.rot.y = 0;
			g_Camera.posV = D3DXVECTOR3(0.0f, 300.0f, 0.0f);			//���_�̏����l
			g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
		}
		if (g_CameraCount >= 801 && g_CameraCount <= 1199)
		{//���_�����_�ɉE���
			g_Camera.rot.y += MOVE_ANGLE1;
			if (g_Camera.rot.y > D3DX_PI)
			{//�E�����3.14�𒴂�����
				g_Camera.rot.y = -D3DX_PI;
			}
			//g_Camera.posR��D3DXVECTOR3��sin��cos���
			g_Camera.posR = D3DXVECTOR3(g_Camera.posV.x - sinf(g_Camera.rot.y) * g_Camera.fLength, g_Camera.posR.y, g_Camera.posV.z - cosf(g_Camera.rot.y) * g_Camera.fLength);
		}
		if (g_CameraCount == 1200)
		{//�ŏ��̃��[�v�ɖ߂�
			g_Camera.rot.y = 0.0f;
			g_Camera.posV = D3DXVECTOR3(0.0f, 50.0f, -150.0f);			//���_�̏����l
			g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_�̏����l
			g_CameraCount = 0;
		}
		//�t���[���J�E���g
		g_CameraCount++;
	}
	if (g_Camera.nType == CAMERA_TYPE_RANKING_DEMO)
	{//�����L���O�ł̃J����
		//R�͒����_
		//V�͎��_
		if (g_CameraCount >= 0 && g_CameraCount <= 1)
		{//�w���R�v�^�[�̏����l
			g_Camera.rot.y = 0;
			g_Camera.posV = D3DXVECTOR3(-50.0f, 50.0f, -180.0f);	//���_�̏����l
			g_Camera.posR = D3DXVECTOR3(-500.0f, 1000.0f, 0.0f);	//�����_�̏����l
			pPlayer2->pos = D3DXVECTOR3(-150.0f, 300.0f, -300.0f);	//�w���̏������ʒu
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//�w���̃v���y������]
		}
		if (g_CameraCount >= 2 && g_CameraCount <= 79)
		{//�O�Ɉړ��iZ����
			pPlayer2->pos.z += 3.8f;								//�w����O�i������
			g_Camera.posR.x += 5;									//�J�����̉����ړ�
			g_Camera.posR.y -= 10;									//�J�����̏c���ړ�
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//�w���̃v���y������]
		}
		if (g_CameraCount >= 80 && g_CameraCount <= 179)
		{//��~�i�w������l�������
			g_Camera.posR = D3DXVECTOR3(-110.0f, 220.0f, 0.0f);		//�J�����̈ʒu���~�߂�
			//pPlayer2->pos = D3DXVECTOR3(-150.0f, 300.0f, -3.5f);	//�w���̎~�܂�ʒu
			pPlayer2->pos.z += 0.1f;								//�w���̊���
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE3;		//�w���̃v���y������]
		}
		if (g_CameraCount >= 180 && g_CameraCount <= 219)
		{//�v���C���[�������Ă����炻�̃v���C���[�Ɏ��_�����
			pPlayer2->pos.z += 3.8f;								//�܂��i�s������
			g_Camera.posR.y -= 5;									//�J���������ɉ�����
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//�w���̃v���y������]
		}
		if (g_CameraCount >= 220 && g_CameraCount <= 800)
		{//�w����O�i�����Ă���
			pPlayer2->pos.z += 3.8f;								//�w����i�s������
			pPlayer2->aModel[1].InitHeriRot.y += MOVE_ANGLE2;		//�w���̃v���y������]
		}
		//�t���[���J�E���g
		g_CameraCount++;
	}
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(CAMERATYPE CameraType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_Camera.nType = CameraType;

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH
	(
		&g_Camera.mtxProjection,
		D3DXToRadian(g_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		7500
	);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,&g_Camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView,
					   &g_Camera.posV,
					   &g_Camera.posR,
		               &g_Camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);
}
//=============================================================================
//	�J�����̎擾
//=============================================================================
Camera *GetCamera(void)
{
	return &g_Camera;
}