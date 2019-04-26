//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���{��
//
//=============================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "ScenePlayer.h"
#include "dungeon.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		DISTANCE		(200)			//�����_�Ǝ��_�̋���
#define		CAMERA_MOVE		(0.8f)			//�J�����̈ړ����x
#define		ROTPOOR_RY		(30)			//�����_�㉺ +��, -��
#define		ROTPOOR_VY		(50)				//�J�����{�� +��, -��

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CCamera::Info CCamera::m_info;			//�J�������
CCamera CCamera::camera;			//�J����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCamera::CCamera(){}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera() {}
//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::Init(void)
{
	camera.m_nCntTime = 0;
	camera.m_nCntState = 0;
	camera.m_info.scene = SCENE_TYPE_NO;
	camera.m_info.state = STATE_GAME;
	camera.m_info.ViewC = VIEW_FOLLOW;
	camera.m_info.ViewS = SCENE_VIEW_NORMAL;

	camera.m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);					//���_
	camera.m_posR = D3DXVECTOR3(0.0f, 0.0f - ROTPOOR_RY, 0.1f);		//�����_
	camera.m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�i�j�R��(��)
	camera.m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ړI
	camera.m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);					//�p�x
	camera.m_addpos = D3DXVECTOR3(0.0f, ROTPOOR_VY, 0.0f);			//�J�����Ɨ��ړ�
	camera.m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�Ǐ]����J�����̏ꏊ
	camera.m_fDistance = DISTANCE;									//���_�ƒ����_�̋���

	camera.m_fGMagnification = 0.25f;
	camera.m_nCntModel = -1;

}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	if (m_info.state == STATE_GAME)
	{
		//�J�����̍X�V
		CScenePlayer *pPlayer = CManager::GetPlayer(0);
		bool		bMove = false;	//�J�����ړ��̗L��
		if (pPlayer != NULL && CManager::GetDungeon() != NULL)
		{
			if (pPlayer->GetnStage() != BOSS_STAGE && CManager::GetDungeon()->GetShop() != 1 && CScenePlayer::GetbCamera())
			{//�J�����𓮂����Ă悢�Ȃ�
				D3DXVECTOR3 posold = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
				D3DXVECTOR3 posC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				int			nNumPlayer = 0;
				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{//�v���C���[�����
					pPlayer = CManager::GetPlayer(nCount);
					if (pPlayer != NULL)
					{//��������Ă���Ȃ�
						if (pPlayer->GetfLife()[0] > 0.0f)
						{//�����Ă���Ȃ�
							posC += D3DXVECTOR3(pPlayer->GetPositionOld()[0].x, 20.0f, pPlayer->GetPositionOld()[0].z);
							posold.x += pPlayer->GetPositionOld()[0].x + sinf(pPlayer->GetRotationU()[0].y) * 10.0f;
							posold.z += pPlayer->GetPositionOld()[0].z + cosf(pPlayer->GetRotationU()[0].y) * 10.0f;
							bMove = true;
							nNumPlayer++;
						}
					}
				}
				if (bMove)
				{//�v���C���[��1�l�ȏ㐶��
					camera.m_posC = posC / (float)nNumPlayer;
					camera.m_posR += ((posold / (float)nNumPlayer) - camera.m_posR) * 0.1f;
					camera.m_posV = D3DXVECTOR3(camera.m_posR.x, camera.m_posV.y, camera.m_posR.z - 0.01f);
				}
			}
		}
	}
	else { UpdateScene(); }

	if (camera.m_rot.y > D3DX_PI) { camera.m_rot.y -= D3DX_PI * 2; }
	if (camera.m_rot.y < -D3DX_PI) { camera.m_rot.y += D3DX_PI * 2; }

	//if (g_camera.nCntModel > -1)
	//{//�Ǐ]�̏ꏊ�̍X�V
	//	MODEL_INFO *model = GetModel_Info();
	//	g_camera.targetpos += (model[g_camera.nCntModel].set.pos + (model[g_camera.nCntModel].set.pos - model[g_camera.nCntModel].set.posold) * 10.0f - g_camera.targetpos) * 0.08f;
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y < -50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y - 50; }
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y > 50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y + 50; }
	//}
	//g_camera.posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + g_camera.targetpos + g_camera.addpos;	//����ꏊ + �����ړ���

	//���_�@���� + (�p�x * ����) + �����ړ���
	//g_camera.goal = D3DXVECTOR3(
	//	g_camera.targetpos.x + (sinf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x),						//X��
	//	g_camera.targetpos.y + sinf(g_camera.rot.x) * g_camera.fDistance + ROTPOOR_VY,									//Y��
	//	g_camera.targetpos.z + (cosf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x)) + g_camera.addpos;	//Z��

	//g_camera.posV += (g_camera.goal - g_camera.posV) * g_camera.fGMagnification;
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Reset(void)
{
	//if (g_camera.nCntModel > -1)
	//{//�Ǐ]�̏ꏊ�̍X�V
	//	MODEL_INFO *model = GetModel_Info();
	//	g_camera.targetpos += (model[g_camera.nCntModel].set.pos + (model[g_camera.nCntModel].set.pos - model[g_camera.nCntModel].set.posold) * 1.0f - g_camera.targetpos);
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y < -50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y - 50; }
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y > 50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y + 50; }
	//}
	//g_camera.goal = D3DXVECTOR3(
	//	g_camera.targetpos.x + (sinf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x),						//X��
	//	g_camera.targetpos.y + sinf(g_camera.rot.x) * g_camera.fDistance + ROTPOOR_VY,									//Y��
	//	g_camera.targetpos.z + (cosf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x)) + g_camera.addpos;	//Z��

	//g_camera.posV += (g_camera.goal - g_camera.posV) * 1.0f;
}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera.m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&camera.m_mtxProjection,
		D3DXToRadian(15.0f),	//��p
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &camera.m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera.m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&camera.m_mtxView, &camera.m_posV, &camera.m_posR, &camera.m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera.m_mtxView);
}
//=============================================================================
// �J�����̓����蔻�菈��
//=============================================================================
void CCamera::Collision(D3DXVECTOR3 *pos, float fLengthX, float fLengthZ)
{
	if (m_posC.x + 85.0f < pos->x) { pos->x = m_posC.x + 85.0f; }
	else if (m_posC.x - 85.0f > pos->x) { pos->x = m_posC.x - 85.0f; }
	if (m_posC.z + 45.0f < pos->z) { pos->z = m_posC.z + 45.0f; }
	else if (m_posC.z - 45.0f > pos->z) { pos->z = m_posC.z - 45.0f; }
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::SetScene(SCENE_TYPE type)
{
	camera.m_nCntState = 0;
	camera.m_nCntTime = 0;
	camera.m_info.state = STATE_MOVIE;
	camera.m_info.scene = type;
}
//=============================================================================
// �V�[���Đ�����
//=============================================================================
void CCamera::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//�V�[���Đ�
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//�G���[�����p
			Init();
			camera.m_nCntModel = 0;
			break;

		case SCENE_TYPE_BOSS:	//�{�X�O
			//Scene_BOSS();
			break;
		}
	}
}
//=============================================================================
// �J�������擾����
//=============================================================================
CCamera::Info *CCamera::GetCamera(void)
{
	return &m_info;
}
