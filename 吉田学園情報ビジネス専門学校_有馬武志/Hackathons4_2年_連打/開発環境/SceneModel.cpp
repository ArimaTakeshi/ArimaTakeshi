//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "ScenePlayer.h"
#include"SceneModel.h"
#include "SceneAnim3D.h"
#include "dungeon.h"
#include"Renderer.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	CSceneModel::m_pTexture[TEXTURE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CSceneModel::MODEL_DRAW *CSceneModel::m_Model_Draw[MODEL_MAX] = {};	//���f���ւ̃|�C���^

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	*CSceneModel::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ���
			 //��//***********************************************************************
			case TEX_BOX_00:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Box00.jpg", &m_pTexture[tex]);			break;
			case TEX_BOX_01:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Box01.jpg", &m_pTexture[tex]);			break;
			case TEX_BOX_02:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Box02.jpg", &m_pTexture[tex]);			break;
			case TEX_BOX_10:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Box10.jpg", &m_pTexture[tex]);			break;
			case TEX_BOX_11:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Box11.jpg", &m_pTexture[tex]);			break;
			case TEX_BOX_12:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Box12.jpg", &m_pTexture[tex]);			break;
				//��Ԗ͗l//***********************************************************************
			case TEX_PTN_01:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_000.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_02:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_001.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_03:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_002.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_04:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_003.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_05:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_004.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_06:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_005.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_07:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_006.jpg", &m_pTexture[tex]);	break;
			case TEX_PTN_08:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_007.jpg", &m_pTexture[tex]);	break;
				//��Ԗ͗l//***********************************************************************
			case TEX_OBJ_00:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/OBJECT/Steel000.jpg", &m_pTexture[tex]);	break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	CSceneModel::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//�S�摜�j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//==================================================================================================//
//    * ���f�������֐� *
//==================================================================================================//
void CSceneModel::LoadModel(MODEL model)
{
	if (model < MODEL_MAX)
	{//�͈͊m�F
		if (m_Model_Draw[model] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			m_Model_Draw[model] = new MODEL_DRAW;
			switch (model)
			{//�ǂݍ���
			case MODEL_TANKD:
				D3DXLoadMeshFromX("data/MODEL/Tank_D.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_TANKU:
				D3DXLoadMeshFromX("data/MODEL/Tank_U.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_SHOP:
				D3DXLoadMeshFromX("data/MODEL/shop.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_STONE:
				D3DXLoadMeshFromX("data/MODEL/stone.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_STEEL:
				D3DXLoadMeshFromX("data/MODEL/steal.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_STEELBIOCK:
				D3DXLoadMeshFromX("data/MODEL/steal_block.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_BOX_1:
				D3DXLoadMeshFromX("data/MODEL/Box_1.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_BOX_2:
				D3DXLoadMeshFromX("data/MODEL/Box_2.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			}
		}
	}
}
//==================================================================================================//
//    * ���f�������֐� *
//==================================================================================================//
void CSceneModel::UnLoadModel(void)
{
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		if (m_Model_Draw[nCount] != NULL)
		{
			// ���b�V���̊J��
			if (m_Model_Draw[nCount]->MeshModel != NULL)
			{
				m_Model_Draw[nCount]->MeshModel->Release();
				m_Model_Draw[nCount]->MeshModel = NULL;
			}

			// �}�e���A���̊J��
			if (m_Model_Draw[nCount]->pBuffMatModel != NULL)
			{
				m_Model_Draw[nCount]->pBuffMatModel->Release();
				m_Model_Draw[nCount]->pBuffMatModel = NULL;
			}
			delete m_Model_Draw[nCount]; m_Model_Draw[nCount] = NULL;
		}
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneModel::Init(void)
{
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_pTex = NULL;
	m_fCntState = 0.0f;
	m_Model = MODEL_MAX;
	CScene::SetObjType(OBJTYPE_OBJ);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneModel::Update(void)
{
	switch (m_state)
	{
	case STATE_FADEIN:	//���񂾂񖾂邭
		m_col.a += 0.03f;
		if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
		break;
	case STATE_FADEOUT:	//���񂾂�Â�
		m_col.a -= 0.03f;
		if (m_col.a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FADE:	//���񂾂񖾂邭->�Â��Ȃ������
		m_col.a += 0.03f;
		if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
		break;
		
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneModel::Draw(void)
{
	if (m_Model != MODEL_MAX)
	{
		LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
		D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
		D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
		D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
		D3DXMATRIX			mtxWorld;		//���[���h�}�g���b�N�X

		if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// ���݂̃}�e���A�����擾
		pD3DDevice->GetMaterial(&matDef);
		pMat = (D3DXMATERIAL*)m_Model_Draw[m_Model]->pBuffMatModel->GetBufferPointer();
		
		if (m_pTex != NULL)
		{//�e�N�X�`���̐ݒ�
			pD3DDevice->SetTexture(0, m_pTex[0]);
		}

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		for (int nCountData = 0; nCountData < (int)m_Model_Draw[m_Model]->nNumMatModel; nCountData++)
		{
			// �}�e���A���̐ݒ�
			pMat = (D3DXMATERIAL*)m_Model_Draw[m_Model]->pBuffMatModel->GetBufferPointer();
			pMat[nCountData].MatD3D.Diffuse = m_col; //�����x�ݒ�
			pD3DDevice->SetMaterial(&pMat[nCountData].MatD3D);
			// ���f��(�p�[�c)�̕`��
			m_Model_Draw[m_Model]->MeshModel->DrawSubset(nCountData);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pD3DDevice->SetMaterial(&matDef);
		pD3DDevice->SetTexture(0, NULL);
	}
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneModel::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, TEXTURE Type, DRAW_TYPE DrawType, bool bHit)
{
	m_pos = pos;
	m_rot = rot;
	m_col = col;
	m_Model = model;
	m_DrawType = DrawType;
	
	//���f���̂����蔻��̗L��
	if(!bHit){ CScene::SetObjType(OBJTYPE_OBJ_NO); }

	//���f���Ɖ摜����
	m_pTex = Load(Type);
	LoadModel(m_Model);
}
//=============================================================================
// ���f���̑傫�����l��
//=============================================================================
void CSceneModel::GetLength(MODEL model, float& fLengthX, float& fLengthZ)
{
	switch (model)
	{
	case MODEL_BOX_1: fLengthX = 5.0f; fLengthZ = 5.0f; break;
	case MODEL_BOX_2: fLengthX = 5.0f; fLengthZ = 5.0f; break;
	case MODEL_SHOP: fLengthX = 13.0f; fLengthZ = 13.0f; break;
	case MODEL_STONE: fLengthX = 2.0f; fLengthZ = 2.0f; break;
	case MODEL_STEELBIOCK: fLengthX = 8.0f; fLengthZ = 8.0f; break;
	case MODEL_STEEL: fLengthX = 3.0f; fLengthZ = 8.0f; break;
	case MODEL_TANKD: fLengthX = 2.5f; fLengthZ = 2.5f; break;
	case MODEL_TANKU: fLengthX = 2.5f; fLengthZ = 2.5f; break;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneObjct::Update(void)
{
	D3DXCOLOR *col = GetColor();
	CSceneModel::STATE *state = GetState();

	switch (state[0])
	{
	case STATE_FADEIN:	//���񂾂񖾂邭
		col[0].a += 0.03f;
		if (col[0].a >= 1.0f) { col[0].a = 1.0f; state[0] = CSceneModel::STATE_NORMAL; }
		break;
	case STATE_FADEOUT:	//���񂾂�Â�
		col[0].a -= 0.03f;
		if (col[0].a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FADE:	//���񂾂񖾂邭->�Â��Ȃ������
		col[0].a += 0.03f;
		if (col[0].a >= 1.0f) { col[0].a = 1.0f; state[0] = CSceneModel::STATE_FADEOUT; }
		break;
	}

	if (m_use >= USE_PTN01 && m_use <= USE_PTN18)
	{//�A�C�e���Ȃ�
		CScenePlayer	*pPlayer;
		D3DXVECTOR3		*pPlayer_pos;
		D3DXVECTOR3		*pos = GetPosition();
		float fLengthX, fLengthZ;
		GetLength(GetModel()[0], fLengthX, fLengthZ);

		//����
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{//�v���C���[����]
			pPlayer = CManager::GetPlayer(nCount);
			if (pPlayer != NULL)
			{//��������Ă���Ȃ�
				pPlayer_pos = pPlayer->GetPosition();
				if (pPlayer_pos[0].x > pos[0].x - fLengthX && pPlayer_pos[0].x < pos[0].x + fLengthX &&
					pPlayer_pos[0].z > pos[0].z - fLengthZ && pPlayer_pos[0].z < pos[0].z + fLengthZ)
				{//�͈͓��Ȃ�
					CSceneAnim3D		*pSAnim3D;				//�G�t�F�N�g�p	���@�ǔ�����
					CSceneModel::TEXTURE Type = GetTexType(m_use);
					if (m_use < USE_PTN11)
					{//�ԑ̂̌���
						pPlayer->GetTEX_TYPE(0) = Type;
						pPlayer->BindTexture(CSceneModel::Load(Type));
					}
					else
					{//�C���̌���
						pPlayer->GetTEX_TYPE(1) = Type;
						LPDIRECT3DTEXTURE9 *&pTexU = pPlayer->GetTextureU();
						pTexU = CSceneModel::Load(Type);
						pPlayer->GetpEffectU()->SetUV((int)(Type - TEX_PTN_01), 8, 1);
						pPlayer->GetnUV() = (int)(Type - TEX_PTN_01);
						if (pPlayer->GetItem() != NULL)
						{//�A�C�e��������
							if (pPlayer->GetItem()->GetType() == ITEM::TYPE_PAIR0) { pPlayer->SetItem(ITEM::TYPE_PAIR0); }
							else if (pPlayer->GetItem()->GetType() == ITEM::TYPE_PAIR1) { pPlayer->SetItem(ITEM::TYPE_PAIR1); }
						}
					}
					pPlayer->PlusLevel(0);		//���̃��x���ŃX�e�[�^�X�v�Z
					if (SceneCreate(pSAnim3D, S3D_PRIORITY))
					{//�����ł����Ȃ� �G�t�F�N�g
						pSAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_WEAPON, CScene::DRAW_TYPE_SUBTRACT,
							0, 5, 2, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
					}
					Uninit(); return;
				}
			}
		}

	}
	else
	{//�A�C�e���łȂ�
		if (GetColor()[0].g != 1.0f)
		{//�Ԃ��Ȃ��Ă���
			GetColor()[0].g -= 0.002f;
			if (GetColor()[0].g <= 0.0f) { DropUninit(); }
		}
	}
}
//=============================================================================
// �I�u�W�F���Ƃ̏I������
//=============================================================================
void CSceneObjct::DropUninit(void)
{
	CSceneAnim3D	*pSceneAnim3D;
	float fRand;

	switch (m_use)
	{
	case USE_DROP:		if (rand() % 8 == 0) { DropItem(GetPosition()[0], 100, 15); } break;
	case USE_DROP10:	if (!DropExplosion()) { return; }
	case USE_DROP00:	DropItem(GetPosition()[0], 25, 10); break;
	case USE_DROP11:	if (!DropExplosion()) { return; }
	case USE_DROP01:	fRand = (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f; for (int nCount = 0; nCount < 2; nCount++)
	{ DropItem(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + D3DX_PI * nCount), 0.0f, cosf(fRand + D3DX_PI * nCount)) * 5.0f, 6, 10); } break;
	case USE_DROP12:	if (!DropExplosion()) { return; }
	case USE_DROP02:	fRand = (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f; for (int nCount = 0; nCount < 3; nCount++)
	{ DropItem(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + (D3DX_PI * 2 / 3) * nCount), 0.0f, cosf(fRand + (D3DX_PI * 2 / 3) * nCount)) * 5.0f, 8, 15); } break;
	case USE_SHOP:
		if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
		{
			pSceneAnim3D->Set(GetPosition()[0],
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CHIP_SIZE * 0.3f, CHIP_SIZE * 0.3f, CSceneAnim3D::TEX_GOAL, CScene::DRAW_TYPE_ADD, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_SHOP);
		}
		break;
	}
	CSceneModel::Uninit();
}
//=============================================================================
// �����h���b�v
//=============================================================================
bool	CSceneObjct::DropExplosion(void)
{
	if (GetColor()[0].g <= 0.0f)
	{//����
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_TROP, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), (rand() % (int)(D3DX_PI * 100.0f)) * 0.01f,
			true, -0.05f, 0.98f, SHOT_LIFE - 6.0f, 0.1f, 0.0f,
			CHIP_SIZE, CHIP_SIZE, D3DX_PI, 0.0f, 1, 0, CSceneBullet::CHANGE_NO, CScenePlayer::GetnStage() * 20.0f + 1000.0f, true, NULL, 16 * 4 + 2);
		return true;
	}
	else
	{//�҂�
		if (GetColor()[0].g > 0.1f) { GetColor()[0] = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f); }
	}
	return false;
}
//=============================================================================
// USE���摜�ɕϊ�
//=============================================================================
CSceneModel::TEXTURE	CSceneObjct::GetTexType(USE use)
{
	switch (m_use)
	{
	case USE_PTN01: case USE_PTN11: return CSceneModel::TEX_PTN_01; break;
	case USE_PTN02: case USE_PTN12: return CSceneModel::TEX_PTN_02; break;
	case USE_PTN03: case USE_PTN13: return CSceneModel::TEX_PTN_03; break;
	case USE_PTN04: case USE_PTN14: return CSceneModel::TEX_PTN_04; break;
	case USE_PTN05: case USE_PTN15: return CSceneModel::TEX_PTN_05; break;
	case USE_PTN06: case USE_PTN16: return CSceneModel::TEX_PTN_06; break;
	case USE_PTN07: case USE_PTN17: return CSceneModel::TEX_PTN_07; break;
	case USE_PTN08: case USE_PTN18: return CSceneModel::TEX_PTN_08; break;
	}
	return CSceneModel::TEX_PTN_08;
}
//=============================================================================
//�A�C�e���h���b�v�֐�
//=============================================================================
void	CSceneObjct::DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky)
{
	CScene3D		*pScene3D;
	int				nRand;

	if (rand() % nPercent == 0)
	{//������
		if (SceneCreate(pScene3D, S3D_PRIORITY))
		{
			nRand = (rand() % 5) + nLucky;
			pScene3D->Set(D3DXVECTOR3(pos.x, PLAYER_Y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ITEM_SIZE, ITEM_SIZE, CScene3D::TEX_ITEM, nRand, 5, 4, CScene::DRAW_TYPE_NORMAL);
			pScene3D->GetState()[0] = (CScene3D::STATE)(CScene3D::STATE_HEEL0 + nRand);
		}
	}
	else
	{//�͂���
		if (SceneCreate(pScene3D, S3D_PRIORITY))
		{
			nRand = rand() % 10;
			pScene3D->Set(D3DXVECTOR3(pos.x, PLAYER_Y, pos.z),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ITEM_SIZE, ITEM_SIZE, CScene3D::TEX_ITEM, nRand, 5, 4, CScene::DRAW_TYPE_NORMAL);
			pScene3D->GetState()[0] = (CScene3D::STATE)(CScene3D::STATE_HEEL0 + nRand);
		}
	}
}