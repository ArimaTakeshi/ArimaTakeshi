//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include"Scene.h"
#include"SceneModel.h"
#include "SceneAnim3D.h"
#include "player.h"
#include "dungeon.h"
#include"mesh.h"
#include"Renderer.h"
#include "manager.h"
#include "camera.h"
#include "light.h"
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
CSceneModel::MODEL_DRAW *CSceneModel::m_Model_Draw[MODEL_MAX] = {};	//���f���ւ̃|�C���^

//==================================================================================================//
//    * ���f�������֐� *
//==================================================================================================//
void	CSceneModel::LoadModel(MODEL model, LPDIRECT3DTEXTURE9 &tex)
{
	if (model < MODEL_MAX)
	{//�͈͊m�F
		switch (model)
		{
		case MODEL_FENCE:		tex = Load(TEX_Fence); break;
		case MODEL_BOX:			tex = Load(TEX_Fence); break;
		case MODEL_STONE:		tex = Load(TEX_Stone); break;
		case MODEL_STONE_S:		tex = Load(TEX_Stone); break;
		case MODEL_STEEL:		tex = Load(TEX_Steel); break;
		case MODEL_STEEL_B:		tex = Load(TEX_Steel); break;
		case MODEL_SATELLITE:	tex = Load(TEX_Satellite); break;
		case MODEL_Gate:		tex = Load(TEX_Steel); break;
		case MODEL_POS_MAG:		tex = Load(TEX_Pos_Mag); break; 
		case MODEL_POS_NEE:		tex = Load(TEX_Pos_Nee); break;
		case MODEL_Earth:		tex = Load(TEX_Pos_Nee); break;
		case MODEL_Frame:		
		case MODEL_FrameV:
		case MODEL_FrameC:
			tex = Load(TEX_Door); break;
		case MODEL_Room: 
			tex = Load(TEX_Room); break;
		}

		if (m_Model_Draw[model] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			char	aStr[64];
			m_Model_Draw[model] = new MODEL_DRAW;
			switch (model)
			{//�ǂݍ���
			case MODEL_FENCE:		strcpy(&aStr[0], "data/MODEL/OBJECT/Fence.x");			break;
			case MODEL_BOX:			strcpy(&aStr[0], "data/MODEL/OBJECT/Box.x");			break; 
			case MODEL_STONE:		strcpy(&aStr[0], "data/MODEL/OBJECT/stone.x");			break;
			case MODEL_STONE_S:		strcpy(&aStr[0], "data/MODEL/OBJECT/stone_S.x");		break;
			case MODEL_STEEL:		strcpy(&aStr[0], "data/MODEL/OBJECT/steel.x");			break;
			case MODEL_STEEL_B:		strcpy(&aStr[0], "data/MODEL/OBJECT/steel_block.x");	break; 
			case MODEL_Gate:		strcpy(&aStr[0], "data/MODEL/OBJECT/Portal.x");			break; 
			case MODEL_SATELLITE:	strcpy(&aStr[0], "data/MODEL/EFFECT/Satellite.x");		break;
			case MODEL_POS_MAG:		strcpy(&aStr[0], "data/MODEL/EFFECT/Position_Magnetic000.x");	break; 
			case MODEL_POS_NEE:		strcpy(&aStr[0], "data/MODEL/EFFECT/Position_Needle000.x");		break; 
			case MODEL_Earth:		strcpy(&aStr[0], "data/MODEL/Hand.x");		break;
			case MODEL_Frame:		strcpy(&aStr[0], "data/MODEL/Door_ Frame.x");		break;
			case MODEL_FrameV:		strcpy(&aStr[0], "data/MODEL/Door_ Inside_Vertical.x");		break; 
			case MODEL_FrameC:		strcpy(&aStr[0], "data/MODEL/Door_ Inside_Horizontal.x");		break;
			case MODEL_Room:		strcpy(&aStr[0], "data/MODEL/Room.x");		break;
			}
			D3DXLoadMeshFromX(&aStr[0], D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
		}
	}
}
//==================================================================================================//
//    * ���f�������֐� *
//==================================================================================================//
void	CSceneModel::UnLoadModel(void)
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
HRESULT	CSceneModel::Init(void)
{
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_pTex = NULL;
	m_fCntState = 0.0f;
	m_Model = MODEL_MAX;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void	CSceneModel::Update(void)
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
// �}�g���b�N�X�ݒ菈��
//=============================================================================
void	CSceneModel::SetMtx(void)
{
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
}
//=============================================================================
// �`�揈��
//=============================================================================
void	CSceneModel::Draw(void)
{
	if (m_Model != MODEL_MAX)
	{
		D3DXVECTOR3 length;
		GetLength(m_Model, length);
		if (CManager::GetCamera()->DrawCheck(m_pos, powf(length.x, 2) + powf(length.z, 2)))
		{
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();

			if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

			// ���[���h�}�g���b�N�X�̐ݒ�
			pD3DDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

			if (m_pTex != NULL)
			{//�e�N�X�`���̐ݒ�
				pD3DDevice->SetTexture(0, m_pTex);
			}

			DrawModel();

			//CSceneModel::SetShadow();
			//CScene::DrawPrepare(CScene::DRAW_TYPE_SUBTRACT, pD3DDevice);
			//pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			//DrawModel();
			//pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		}
	}
}
//=============================================================================
// ���f���`�揈��
//=============================================================================
void	CSceneModel::DrawModel(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^

	// ���݂̃}�e���A�����擾
	pD3DDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_Model_Draw[m_Model]->pBuffMatModel->GetBufferPointer();

	// �}�e���A���̐ݒ�
	pMat = (D3DXMATERIAL*)m_Model_Draw[m_Model]->pBuffMatModel->GetBufferPointer();

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	for (int nCountData = 0; nCountData < (int)m_Model_Draw[m_Model]->nNumMatModel; nCountData++)
	{
		pMat[nCountData].MatD3D.Diffuse = m_col; //�����x�ݒ�
		pD3DDevice->SetMaterial(&pMat[nCountData].MatD3D);
		// ���f��(�p�[�c)�̕`��
		m_Model_Draw[m_Model]->MeshModel->DrawSubset(nCountData);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pD3DDevice->SetMaterial(&matDef);
	pD3DDevice->SetTexture(0, NULL);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void	CSceneModel::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, DRAW_TYPE DrawType, bool bHit)
{
	m_pos = pos;
	m_rot = rot;
	m_col = col;
	m_Model = model;
	m_DrawType = DrawType;
	
	//���f���̂����蔻��̗L��
	if(!bHit){ CScene::SetObjType(OBJTYPE_OBJ_NO); }

	//���f���Ɖ摜����
	LoadModel(m_Model, m_pTex);
	SetMtx();

}
//=============================================================================
// ���f���̑傫�����l��
//=============================================================================
void	CSceneModel::GetLength(MODEL model, D3DXVECTOR3 &length)
{
	switch (model)
	{
	case MODEL_FENCE:	length = D3DXVECTOR3(10.0f, 50.0f, 50.0f); break;
	case MODEL_BOX:		length = D3DXVECTOR3(30.0f, 30.0f, 30.0f); break; 
	case MODEL_STONE:	length = D3DXVECTOR3(100.0f, 400.0f, 100.0f); break;
	case MODEL_STONE_S:	length = D3DXVECTOR3(35.0f, 35.0f, 25.0f); break;
	case MODEL_STEEL:	length = D3DXVECTOR3(35.0f, 20.0f, 65.0f); break;
	case MODEL_STEEL_B:	length = D3DXVECTOR3(100.0f, 100.0f, 100.0f); break;
	}
}
//=============================================================================
// �Z�b�g���̍������l��
//=============================================================================
float	CSceneModel::GetHeight(MODEL model)
{
	switch (model)
	{
	case MODEL_FENCE:
	case MODEL_BOX:
	case MODEL_STONE:
	case MODEL_STONE_S:
	case MODEL_STEEL:
	case MODEL_STEEL_B:
		return 0.0f;
	case MODEL_Gate:	return 300.0f;
	case MODEL_Earth:	return 50.0f;
	}
	return 0.0f;
}
//=============================================================================
//�e�̕`��
//=============================================================================
void CSceneModel::SetShadow(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

																		// ���[���h�}�g���b�N�X�̐ݒ�
	D3DXMATRIX	mtxShadow;
	D3DXMATRIX	WKmtx;
	D3DXPLANE	planeField;
	D3DXVECTOR4	vecLight;
	D3DXVECTOR3	pos, posold, WKpos, normal;
	bool		WKbJump = false;
	int			nWKCount = 0;
	D3DLIGHT9 &light = CManager::GetLight()->Getlight(0);

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	pDevice->GetTransform(D3DTS_WORLD, &WKmtx);
	vecLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);
	pos = D3DXVECTOR3(WKmtx._41, -99999.0f, WKmtx._43);
	posold = D3DXVECTOR3(0.0f, WKmtx._42, 0.0f);
	WKpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	//�N���ɍ��킹��
	CMesh::MeshCollisionField(pos, posold, WKpos, WKpos, WKpos, WKbJump);
	//CSceneObjct::CollisionAll(pos, posold, WKpos, WKpos, WKpos, nWKCount, WKbJump, false);	//�I�u�W�F�N�g
	pos = D3DXVECTOR3(0.0f, pos.y + 1.0f, 0.0f);
	//pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e����
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//�e��ړI�̕��̂ɂ����t����
	D3DXMatrixMultiply(&WKmtx, &WKmtx, &mtxShadow);
	pDevice->SetTransform(D3DTS_WORLD, &WKmtx);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void	CSceneObjct::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL model, bool bHit, USE use)
{
	CScene::SetObjType(OBJTYPE_OBJ);
	CSceneModel::Set(pos, rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), model, CScene::DRAW_TYPE_NORMAL, bHit);
	m_use = use;
}
//=============================================================================
// �X�V����
//=============================================================================
void	CSceneObjct::Update(void)
{
	D3DXCOLOR &col = GetColor();
	CSceneModel::STATE &state = GetState();

	switch (state)
	{
	case STATE_FADEIN:	//���񂾂񖾂邭
		col.a += 0.03f;
		if (col.a >= 1.0f) { col.a = 1.0f; state = CSceneModel::STATE_NORMAL; }
		break;
	case STATE_FADEOUT:	//���񂾂�Â�
		col.a -= 0.03f;
		if (col.a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FADE:	//���񂾂񖾂邭->�Â��Ȃ������
		col.a += 0.03f;
		if (col.a >= 1.0f) { col.a = 1.0f; state = CSceneModel::STATE_FADEOUT; }
		break;
	}

	if (GetModel() == MODEL_Gate)
	{//���f�����Q�[�g�ł���
		//�v���C���[������
		CPlayer *&pPlayer = CManager::GetPlayer(0);
		if (pPlayer == NULL) { return; }
		//�v���C���[���߂��ɂ����
		D3DXVECTOR3 &m_pos = GetPosition();
		D3DXVECTOR3 &playerPos0 = pPlayer->Getpos();
		float fDistance0 = 5000.0f;
		float fDistance1 = 5000.0f;

		fDistance0 = powf(playerPos0.x - m_pos.x, 2) + powf(playerPos0.z - m_pos.z, 2);
		if (CManager::GetbDuo())
		{
			D3DXVECTOR3 &playerPos1 = CManager::GetPlayer(1)->Getpos();
			fDistance1 = powf(playerPos1.x - m_pos.x, 2) + powf(playerPos1.z - m_pos.z, 2);
		}
		if (fDistance0 <= 40.0f * 40.0f || fDistance1 <= 40.0f * 40.0f)
		{
			CManager::GetpDungeon()->ChangeMap(CDungeon::TYPE_BOSS);
		}
	}
}
//=============================================================================
// �I�u�W�F���Ƃ̏I������
//=============================================================================
void	CSceneObjct::DropUninit(void)
{
	//float fRand;

	//switch (m_use)
	//{
	//case USE_DROP:		if (rand() % 8 == 0) { DropItem(GetPosition()[0], 100, 15); } break;
	//case USE_DROP10:	if (!DropExplosion()) { return; }
	//case USE_DROP00:	DropItem(GetPosition()[0], 25, 10); break;
	//case USE_DROP11:	if (!DropExplosion()) { return; }
	//case USE_DROP01:	fRand = (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f; for (int nCount = 0; nCount < 2; nCount++)
	//{ DropItem(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + D3DX_PI * nCount), 0.0f, cosf(fRand + D3DX_PI * nCount)) * 5.0f, 6, 10); } break;
	//case USE_DROP12:	if (!DropExplosion()) { return; }
	//case USE_DROP02:	fRand = (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f; for (int nCount = 0; nCount < 3; nCount++)
	//{ DropItem(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + (D3DX_PI * 2 / 3) * nCount), 0.0f, cosf(fRand + (D3DX_PI * 2 / 3) * nCount)) * 5.0f, 8, 15); } break;
	//}
	CSceneModel::Uninit();
}
//=============================================================================
// �����h���b�v
//=============================================================================
bool	CSceneObjct::DropExplosion(void)
{
	if (GetColor().g <= 0.0f)
	{//����
		return true;
	}
	else
	{//�҂�
		if (GetColor().g > 0.1f) { GetColor() = D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f); }
	}
	return false;
}
//=============================================================================
//�A�C�e���h���b�v�֐�
//=============================================================================
void	CSceneObjct::DropItem(D3DXVECTOR3 &pos, int nPercent, int nLucky)
{

}
//=============================================================================
//�����蔻�� �I�u�W�F�N�g��T��
//=============================================================================
bool	CSceneObjct::CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	bool bLand = false;
	int nCount = nCntHit;
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_OBJ)
		{//���b�V������
			bLand = ((CSceneObjct*)pScene)->Collision(pos, posold, move, length, FNor, nCntHit, bJump, bReflection);
		}
		pScene = pScene->GetpNext();
	}

	return bLand;
}
//=============================================================================
//�����蔻��
//=============================================================================
bool	CSceneObjct::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	bool bLand = false;
	CSceneModel::MODEL WKmodel = GetModel();
	D3DXVECTOR3 lengthX; GetLength(GetModel(), lengthX);	//���f���̕��l��
	D3DXVECTOR3 m_pos = GetPosition();
	float fDistance = powf(lengthX.x, 2) + powf(lengthX.z, 2);	//���_���璸�_�܂ł̋����l��
	if (powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2) < fDistance * 2.0f)
	{//�͈͓��Ȃ�
		fDistance = sqrtf(fDistance);
		int  nHit;
		float fHeight = pos.y;
		float fWKLength = 0.0f;
		float m_frot = GetRotation().y;
		float fRot = atan2f(lengthX.x, lengthX.z);			//���_�̊p�x�����߂�
		D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 WKpos = pos;
		D3DXVECTOR3 Vtx[8];										//����p8���_�p��
		bool bJudge = false;

		//����, �E��, ����, �E���̏�
		Vtx[2] = D3DXVECTOR3(sinf(m_frot - fRot), 0.0f, cosf(m_frot - fRot)) * fDistance + m_pos;
		Vtx[3] = D3DXVECTOR3(sinf(m_frot + fRot), 0.0f, cosf(m_frot + fRot)) * fDistance + m_pos;
		Vtx[1] = D3DXVECTOR3(sinf(m_frot + fRot + D3DX_PI), 0.0f, cosf(m_frot + fRot + D3DX_PI)) * fDistance + m_pos;
		Vtx[0] = D3DXVECTOR3(sinf(m_frot - fRot + D3DX_PI), 0.0f, cosf(m_frot - fRot + D3DX_PI)) * fDistance + m_pos;

		Vtx[6] = Vtx[2] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * -0.25f), 0.0f, cosf(m_frot + D3DX_PI * -0.25f)) * (length.x);
		Vtx[7] = Vtx[3] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * 0.25f), 0.0f, cosf(m_frot + D3DX_PI * 0.25f)) * (length.x);
		Vtx[5] = Vtx[1] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * -0.75f), 0.0f, cosf(m_frot + D3DX_PI * -0.75f)) * (length.x);
		Vtx[4] = Vtx[0] + D3DXVECTOR3(sinf(m_frot + D3DX_PI * 0.75f), 0.0f, cosf(m_frot + D3DX_PI * 0.75f)) * (length.x);
		
		if (CMesh::FieldCheck(Vtx[6], Vtx[7], Vtx[5], Vtx[4], WKpos))
		{//�l�p�`�͈͓�
			fHeight = CMesh::FieldCollision(Vtx[2], Vtx[3], Vtx[1], Vtx[0], WKpos, pos, WKnor);
			if (fHeight - lengthX.y - length.y < pos.y && fHeight - lengthX.y - length.y >= posold.y) 
			{//�V��
				pos.y = fHeight - lengthX.y - length.y;
			}
			else
			{//��
				if (fHeight + lengthX.y > pos.y && fHeight + lengthX.y <= posold.y + (bJump ? 5.0f : 0.0f))
				{
					pos.y = fHeight + lengthX.y;
					FNor = WKnor;
					move.y = 0.0f;
					bJump = true;
					bJudge = true;
				}
			}
		}
		if (!bJudge)
		{
			for (int nCount = 0; nCount < 4; nCount++)
			{//4��������
				//��
				nHit = CMesh::WallCollision(Vtx[nCount % 4], Vtx[(nCount + 1) % 4], WKpos, posold, move, length.x, nCntHit, bReflection);
				if (nHit != 0)
				{//XZ�œ�������
				 //�O�ςłx�`�F�b�N
					float fDistance2[2];
					float fAngle[3];

					fDistance2[0] = sqrtf(powf((WKpos.x - posold.x), 2) + powf((WKpos.z - posold.z), 2));	//�I�u�W�F
					fDistance2[1] = sqrtf(powf((pos.x - posold.x), 2) + powf((pos.z - posold.z), 2));		//�Ώ�

					fAngle[0] = atan2f(fDistance2[0], (GetPosition().y + lengthX.y * 0.9f) - (pos.y - (bReflection ? length.y : 0.0f)));
					fAngle[1] = atan2f(fDistance2[0], (GetPosition().y - lengthX.y) - (pos.y + (bReflection ? length.y : 0.0f)));
					fAngle[2] = 1.57f;
					if (CMesh::AngleCheck(fAngle[2], fAngle[0]) > 0 && CMesh::AngleCheck(fAngle[2], fAngle[1]) < 0)
					{//Y�͈͓�
						pos.x = WKpos.x;
						pos.z = WKpos.z;
					}
					else
					{//Y�͈͊O�ׂ̈��̃I�u�W�F�N�g�͖���
						break;
					}
					bJudge = false;
				}
				if (nHit == 2) { break; }
			}
		}
	}//if(�͈͓��Ȃ�)

	return bLand;
}
//=============================================================================
//�����蔻��
//=============================================================================
void	CSceneObjct::SetObjField(void)
{
	bool bLand = false;
	CScene *pScene = CScene::GetTop(MODEL_PRIORITY);
	D3DXVECTOR3 WKpos, pos, posold, nor, length;
	bool bJump = true;
	length = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_OBJ || pScene->GetObjType() == OBJTYPE_OBJ_NO)
		{//���b�V������
			pos = ((CSceneObjct*)pScene)->GetPosition();
			posold = pos;
			pos.y = -10000.0f;
			posold.y = 10000.0f;
			CMesh::MeshCollisionField(pos, posold, WKpos, length, nor, bJump);
			switch (((CSceneObjct*)pScene)->GetModel())
			{
			case MODEL_STONE:	pos.y -= 65.0f; break;
			case MODEL_Earth:	pos.y += 10.0f; break;
			case MODEL_Gate:
			case MODEL_FENCE:
			case MODEL_BOX:
			case MODEL_STONE_S:
			case MODEL_STEEL:
			case MODEL_STEEL_B:
				break;

			}
			((CSceneObjct*)pScene)->GetPosition().y = pos.y;
			((CSceneObjct*)pScene)->SetMtx();
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//�q���̐ݒ�
//=============================================================================
void	CSatellite::Set(D3DXMATRIX &pMtx, D3DXVECTOR3 rot, D3DXCOLOR col, MODEL model, D3DXVECTOR3 &move, float &fFrame, float fRot, float fDistance, bool &bDelete)
{
	m_pMtx = &pMtx;	m_bDelete = &bDelete;		m_pmove = &move;		m_pfFrame = &fFrame;
	m_fRot = fRot;	m_fDistance = fDistance;
	m_fMoveRot = 0.0f;

	D3DXVECTOR3 WKpos = D3DXVECTOR3(pMtx._41, pMtx._42, pMtx._43) + D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * m_fDistance;
	CSceneModel::Set(WKpos,rot, col, model, CScene::DRAW_TYPE_NORMAL, false);

	SetMtx();
	SetObjType(CScene::OBJTYPE_Satellite);
}
//=============================================================================
//�q���̍X�V
//=============================================================================
void	CSatellite::Update(void)
{
	m_fRot			 += ((sqrtf(m_pmove->x * m_pmove->x + m_pmove->z * m_pmove->z) * 0.75f + 1.0f) * 0.0035f) * D3DX_PI;
	GetRotation().y	 += (m_pfFrame[0] * 0.01f) * D3DX_PI;
	m_fMoveRot += D3DX_PI * 0.01f;

	GetPosition()	 = D3DXVECTOR3(m_pMtx->_41, m_pMtx->_42 + cosf(m_fRot * 2.0f) * 10.0f, m_pMtx->_43) + D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * m_fDistance;
}
//=============================================================================
//�q���̕`��
//=============================================================================
void	CSatellite::Draw(void)
{
	SetMtx();
	CSceneModel::Draw();
}
//=============================================================================
//�q���̍폜�m�F�Ɣj��
//=============================================================================
void CSatellite::Delete(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(SATELLITE_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_Satellite)
		{//���b�V������
			if (((CSatellite*)pScene)->m_bDelete[0])
			{
				pScene->Uninit();
			}
		}
		pScene = pScene->GetpNext();
	}
}

//=============================================================================
//�q���̃��Z�b�g
//=============================================================================
void CSatellite::ReSet(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(SATELLITE_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_Satellite)
		{//���b�V������
			D3DXMATRIX *&m_pMtx = ((CSatellite*)pScene)->GetpMtx();
			float &m_fRot = ((CSatellite*)pScene)->GetfRot();
			((CSatellite*)pScene)->GetPosition() = D3DXVECTOR3(m_pMtx->_41, m_pMtx->_42, m_pMtx->_43) + D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * ((CSatellite*)pScene)->m_fDistance;
		}
		pScene = pScene->GetpNext();
	}
}