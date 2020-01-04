//=============================================================================
//
// �n�ʏ��� [ground.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "ground.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "mesh.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define GROUND_TEX_1		"data\\TEXTURE\\�g���b�v\\�]�[��.jpg"		// �g���b�v�]�[���p�e�N�X�`��
#define GROUND_TEX_2		"data\\TEXTURE\\�g���b�v\\yazirusi000.png"	// �g���b�v�]�[���p�e�N�X�`��
#define GROUND_TEX_3		"data\\TEXTURE\\�g���b�v\\next.png"			// �g���b�v�]�[���p�e�N�X�`��
#define GROUND_TEX_4		"data\\TEXTURE\\�g���b�v\\break.png"		// �g���b�v�]�[���p�e�N�X�`��
#define GROUND_MOVE_SPEED	(0.002f)									// �e�N�X�`���̈ړ����x�̒����p

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CGround::m_pTexture[MAX_GROUND_TEX] = {};
LPDIRECT3DVERTEXBUFFER9	CGround::m_pVtxBuff = NULL;
bool CGround::m_bTrap = false;
bool CGround::m_bSafety = false;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGround::CGround() : CScene3D(GROUND_PRIOTITY, CScene::OBJTYPE_GROUND)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_fTexMoveSpeed = 0.0f;
	m_bLight = false;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGround::~CGround()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGround::Init()
{
	CScene3D::Init();

	//��ނ̐ݒ�
	SetTypeNumber(TYPE_GROUND);
	m_fTexMoveSpeed = GROUND_MOVE_SPEED;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CGround::Uninit(void)
{
	m_bTrap = false;

	CScene3D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CGround::Update(void)
{
	CScene3D::Update();

	//�ϐ�
	D3DXVECTOR2 UV[4];
	D3DXCOLOR col[4];

	m_nCnt++;

	if (m_rot.x != 0.0f)
	{
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.025f), 1.0f);
		UV[1] = D3DXVECTOR2(0.0f - (m_nCnt * 0.025f), 0.0f);
		UV[2] = D3DXVECTOR2(1.0f - (m_nCnt * 0.025f), 1.0f);
		UV[3] = D3DXVECTOR2(1.0f - (m_nCnt * 0.025f), 0.0f);

		CScene3D::SetNor(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	else if (m_rot.z != 0.0f)
	{
		UV[0] = D3DXVECTOR2(0.0f + (m_nCnt * 0.025f), 0.0f);
		UV[1] = D3DXVECTOR2(1.0f + (m_nCnt * 0.025f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f + (m_nCnt * 0.025f), 1.0f);
		UV[3] = D3DXVECTOR2(1.0f + (m_nCnt * 0.025f), 1.0f);
	}
	else
	{
		if (m_move.x != 0.0f)
		{// �e�N�X�`���ݒ�@���E�ɗ����
			UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 0.0f);
			UV[1] = D3DXVECTOR2(1.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 0.0f);
			UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 1.0f);
			UV[3] = D3DXVECTOR2(1.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 1.0f);
		}
		if (m_move.z != 0.0f)
		{// �e�N�X�`���ݒ� �㉺�ɗ����
			UV[0] = D3DXVECTOR2(0.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 1.0f);
			UV[1] = D3DXVECTOR2(0.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 0.0f);
			UV[2] = D3DXVECTOR2(1.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 1.0f);
			UV[3] = D3DXVECTOR2(1.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 0.0f);
		}
		if (m_move.z == 0.0f && m_move.x == 0.0f)
		{// �e�N�X�`���ݒ� �����Ȃ�
			UV[0] = D3DXVECTOR2(0.0f, 0.0f);
			UV[1] = D3DXVECTOR2(1.0f, 0.0f);
			UV[2] = D3DXVECTOR2(0.0f, 1.0f);
			UV[3] = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	//���b�g�]�[���̐F�ύX
	if (m_nType == 0)
	{
		//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		m_fColorCount -= 0.009f;

		if (m_fColorCount < 0.5f)
		{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			m_fColorCount = 0.9f;
		}

		//�Z���T�[�ɂ����������ǂ����ŐF��ς���
		if (m_bTrap == false)
		{//��
			col[0] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
			col[1] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
			col[2] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
			col[3] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
		}
		else  if (m_bTrap == true)
		{//��
			col[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
			col[1] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
			col[2] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
			col[3] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		}
	}
	//�Z�[�t�e�B�[�]�[���̐F�ύX
	if (m_nType == 1)
	{
		//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		m_fColorCount -= 0.009f;

		if (m_fColorCount < 0.5f)
		{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			m_fColorCount = 0.9f;
		}

		col[0] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
		col[1] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
		col[2] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
		col[3] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
	}
	//�Z�[�t�e�B�[�]�[���̐F�ύX
	if (m_nType == 2)
	{
		m_fColorCount = 0.7f;

		col[0] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);
		col[1] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);
		col[2] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);
		col[3] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);

		if (m_nLightCounter > 320)
		{
			m_nLightCounter = 0;
		}
		else if (m_nLightCounter > 260)
		{
			m_pos.z += 0.0f;
		}
		else if (m_nLightCounter > 160)
		{
			m_pos.z -= 5.0f;
		}
		else if (m_nLightCounter > 100)
		{
			m_pos.z += 0.0f;
		}
		else if (m_nLightCounter >= 0)
		{
			m_pos.z += 5.0f;
		}

		m_nLightCounter++;
	}

	//�Z�[�t�e�B�[�]�[���̐F�ύX
	if (m_nType == 3)
	{
		//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		m_fColorCount -= 0.009f;

		if (m_fColorCount < 0.5f)
		{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			m_fColorCount = 0.9f;
		}


		col[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		col[1] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		col[2] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		col[3] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
	}

	//�w�i��UV
	CScene3D::SetUV(&UV[0]);
	CScene3D::SetColor(&col[0]);
	CScene3D::SetPosition(m_pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGround::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	if (m_nType == 3)
	{
		//�t�H�O���g�p���Ȃ�
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}

	CScene3D::Draw();
	
	if (m_nType == 3)
	{
		//�t�H�O���g�p���Ȃ�
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CGround * CGround::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nType, int nTextureType)
{
	CGround *pGround = NULL;

	//NULL�`�F�b�N
	if (pGround == NULL)
	{//�������̓��I�m��

		pGround = new CGround;

		if (pGround != NULL)
		{
			//����������
			pGround->Init();
			//�����蔻��p
			pGround->m_size = size;
			//��ނ̐ݒ�
			pGround->m_nType = nType;
			//�e�N�X�`���̎��
			pGround->SetTexType(0);
			//�ʒu�Ƒ傫���̐ݒ�
			pGround->SetGroundPosSize(pos, size);
			pGround->m_pos = pos;
			// �ړ��ʂ̐ݒ�
			pGround->SetMove(move);
			pGround->m_move = move;
			// �p�x�̐ݒ�
			pGround->SetRotation(rot * D3DX_PI);
			pGround->m_rot = rot;
			//�e�N�X�`���̐ݒ�
			pGround->BindTexture(m_pTexture[nTextureType]);
		}
	}

	return pGround;
}
//=============================================================================
// ���̓����蔻��
//=============================================================================
void CGround::CollisionGround(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	// pos���擾
	D3DXVECTOR3 GroundPos = CScene3D::GetPosition();
	D3DXVECTOR3 GroundRot = CScene3D::GetRotation();
	D3DXVECTOR3 GroundMove = CScene3D::GetMove();
	D3DXVECTOR2 GroundSize = CScene3D::GetSize();

	//�T�E���h�̏��
	CSound *pSound = CManager::GetSound();

	CScene *pScene;

	if (pPos->x <= GroundPos.x + GroundSize.x
		&& pPos->x >= GroundPos.x - GroundSize.x)
	{// ���Ɠ���z���ɑ��݂��Ă���
		if (pPos->z <= GroundPos.z + GroundSize.y
			&& pPos->z >= GroundPos.z - GroundSize.y)
		{// ���Ɠ���x���ɑ��݂��Ă���
			if (GroundRot == D3DXVECTOR3(0.0f, 0.0f, 0.0f) && pPos->y < GroundPos.y)
			{// ���ɐG��Ă���
				/*pMove->x += GroundMove.x;
				pMove->y += GroundMove.y;
				pMove->z += GroundMove.z;*/

				//if (pPosOld->y > GroundPos.y)
				{
					if (m_nType == 0)
					{
						if (CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SNEAK && m_bTrap == false || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SQUAT && m_bTrap == false || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_TIRED && m_bTrap == false)
						{
							m_bTrap = false;
						}
						else if (CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SNEAK || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SQUAT || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_TIRED)
						{
							m_bTrap = true;

							//�v���C�I���e�B�[�`�F�b�N
							pScene = CScene::GetTop(2);

							//NULL�`�F�b�N
							while (pScene != NULL)
							{
								//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
								CScene *pSceneNext = pScene->GetNext();

								if (pScene->GetDeath() == false)
								{//�^�C�v���ǂ�������
									if (pScene->GetObjType() == OBJTYPE_ENEMY)
									{
										//�G�ɔ���������
										((CEnemy*)pScene)->SetPattern(2);

										//�������̉�
										pSound->PlaySound(CSound::SOUND_LABEL_SE_TRAP);
									}
								}
								//Next�Ɏ���Scene������
								pScene = pSceneNext;
							}
						}
					}
					else if (m_nType == 1)
					{//�Z�[�t�e�B�]�[��
						if (CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SNEAK || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SQUAT || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_TIRED)
						{
							m_bSafety = true;
						}
						else if (CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SNEAK || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SQUAT || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_TIRED)
						{
							m_bSafety = false;
						}
					}
					else if (m_nType == 2)
					{//���C�g
						
						m_bLight = true;

						if (m_bSafety == false)
						{
							//�v���C�I���e�B�[�`�F�b�N
							pScene = CScene::GetTop(2);

							//NULL�`�F�b�N
							while (pScene != NULL)
							{
								//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
								CScene *pSceneNext = pScene->GetNext();

								if (pScene->GetDeath() == false)
								{//�^�C�v���ǂ�������
									if (pScene->GetObjType() == OBJTYPE_ENEMY)
									{
										//�G�ɔ���������
										((CEnemy*)pScene)->SetPattern(2);

										//�������̉�
										pSound->PlaySound(CSound::SOUND_LABEL_SE_TRAP);
									}
								}
								//Next�Ɏ���Scene������
								pScene = pSceneNext;
							}
						}
						else if(m_bSafety == true)
						{
							m_bLight = false;
						}
						else if (m_bSafety == false || m_bLight == true)
						{
							//�v���C�I���e�B�[�`�F�b�N
							pScene = CScene::GetTop(2);

							//NULL�`�F�b�N
							while (pScene != NULL)
							{
								//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
								CScene *pSceneNext = pScene->GetNext();

								if (pScene->GetDeath() == false)
								{//�^�C�v���ǂ�������
									if (pScene->GetObjType() == OBJTYPE_ENEMY)
									{
										//�G�ɔ���������
										((CEnemy*)pScene)->SetPattern(2);

										//�������̉�
										pSound->PlaySound(CSound::SOUND_LABEL_SE_TRAP);
									}
								}
								//Next�Ɏ���Scene������
								pScene = pSceneNext;
							}
						}
					}
				}

				CDebugProc::Print("bTrap = %s\n", m_bTrap ? "true": "false");
				CDebugProc::Print("m_bSafety = %s\n", m_bSafety ? "true" : "false");

				//CDebugProc::Print("GroundMove.x = %.1f ,GroundMove.y = %.1f, GroundMove.z = %.1f\n", GroundMove.x, GroundMove.y, GroundMove.z);
				//CDebugProc::Print("GroundSize.x = %.1f ,GroundSize.y = %.1f\n\n", GroundSize.x, GroundSize.y);
			}
		}
	}
}
//=============================================================================
// �}�b�v�ړ��̍ۂ̍폜
//=============================================================================
void CGround::DeleteGround(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(GROUND_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_GROUND)
			{
				pScene->Uninit();
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//=============================================================================
// �ǂݍ��ݏ���
//=============================================================================
HRESULT CGround::Load(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`������
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_4, &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// �J������
//=============================================================================
void CGround::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_GROUND_TEX; nCount++)
	{
		// �e�N�X�`���j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}