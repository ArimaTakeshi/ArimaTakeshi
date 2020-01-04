//=============================================================================
//
// �I�u�W�F�N�g�̏��� [object.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "object.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME_1	"data\\MODEL\\saku000.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_2	"data\\MODEL\\saku001.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_3	"data\\MODEL\\wall000.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_4	"data\\MODEL\\wall001.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_5	"data\\MODEL\\bed.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_6	"data\\MODEL\\peple.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_7	"data\\MODEL\\stair.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_8	"data\\MODEL\\���̋@.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_9	"data\\MODEL\\��.x"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_10	"data\\MODEL\\grass.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_11	"data\\MODEL\\TreeU.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_12	"data\\MODEL\\TreeD.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_13	"data\\MODEL\\saku003.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_14	"data\\MODEL\\WoodenDesk.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_15	"data\\MODEL\\WoodenChair.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_16	"data\\MODEL\\�i�{�[��.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_17	"data\\MODEL\\Extinguisher.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_18	"data\\MODEL\\locker.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_19	"data\\MODEL\\door.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_20	"data\\MODEL\\SmallWoodenDesk.x"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_21	"data\\MODEL\\�S�~��.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_22	"data\\MODEL\\counter.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_23	"data\\MODEL\\fence.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_24	"data\\MODEL\\security.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_25	"data\\MODEL\\floor.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_26	"data\\MODEL\\smallfence.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_27	"data\\MODEL\\ArmoredCar.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_28	"data\\MODEL\\gate.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_29	"data\\MODEL\\prison.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_30	"data\\MODEL\\tower.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_31	"data\\MODEL\\cone.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MODEL_NAME_32	"data\\MODEL\\Generator.x"			//�ǂݍ��ރe�N�X�`���t�@�C��

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(25)			// �v���C���[�̕������p
#define PLAYER_HEIGHT	(100.0f)		// �v���C���[�̔w�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CObject::m_pMeshModel[MAX_OBJECT] = {};						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CObject::m_pBuffMatModel[MAX_OBJECT] = {};					//�}�e���A���̏��ւ̃|�C���^
DWORD CObject::m_nNumMatModel[MAX_OBJECT] = {};							//�}�e���A���̏��
LPDIRECT3DTEXTURE9 CObject::m_pMeshTextures[MAX_OBJECT_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CObject::CObject() : CModel3D(OBJECT_PRIOTITY,CScene::OBJTYPE_OBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStageCount = 0;
	m_bStageNext = false;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CObject::~CObject()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CObject::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3D���f����Init
	CModel3D::Init();
	
	// �ʒu�̏�����
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nType == 13)
	{
		//�e�̕`��
		//m_pShadow = CShadow::Create(pos, 50.0f, 50.0f, 0);
	}
	else if (m_nType == 14)
	{
		//�e�̕`��
		//m_pShadow = CShadow::Create(pos, 50.0f, 50.0f, 0);
	}


	//�ʒu�̑��
	CModel3D::SetPosition(pos);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
	if (m_nType == 13 && m_nType == 14)
	{
		//�e��j��
		//m_pShadow->Uninit();
	}

	//3D���f����Uninit
	CModel3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	//3D���f����Update
	CModel3D::Update();
	//�ʒu�̏�����
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̑��
	D3DXVECTOR3 &rot = CModel3D::GetRot();
	// MOVETYPE�̐ݒ�
	MOVETYPE MoveType = CModel3D::GetMoveType();
	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//���a
	float fRadius = 10.0f;
	//�~��
	float fCircumference = (((D3DX_PI * 2.0f) * fRadius));

	//�e�̍�����ێ����Ă���
	//float fMeshHeight = m_pShadow->GetShadowHeight();

	switch (MoveType)
	{
	case MOVETYPE_X_MOVE:
		// X���ړ�
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Y_MOVE:
		// Y���ړ�
		if (m_nCount <= 120)
		{
			move.y += m_move.y;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.y -= m_move.y;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Z_MOVE:
		// Z���ړ�
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		break;

	case MOVETYPE_ROTATION_X:
		// X���ŉ�]���Ȃ���Z���ړ�
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.x += 0.1f;
		break;

	case MOVETYPE_ROTATION_Z:
		// Z���ŉ�]���Ȃ���X���ړ�
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.z += 0.1f;
		break;
	case MOVETYPE_CONT:
		//�ړ�����
		if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
		{
			//��]�̊������狗�����o��
			m_Spin.z += -0.005f * D3DX_PI;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
		{
			//��]�̊������狗�����o��
			m_Spin.z += 0.005f * D3DX_PI;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
		{
			//��]�̊������狗�����o��
			m_Spin.x += 0.005f * D3DX_PI;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
		{
			//��]�̊������狗�����o��
			m_Spin.x += -0.005f * D3DX_PI;
		}
		else
		{
			m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		//�p�x��
		rot.z += m_Spin.z;
		rot.x += m_Spin.x;

		pos.x -= (m_Spin.z / (D3DX_PI * 2.0f)) * fCircumference;
		pos.z -= (-m_Spin.x / (D3DX_PI * 2.0f)) * fCircumference;

		//����
		m_Spin.x *= 0.95f;
		m_Spin.z *= 0.95f;

		break;
	}

	//�X�e�[�W�J�ڂ����������Ƃ�
	if (m_bStageNext == true)
	{
		//1�b��Ƀt�F�[�h
		if (m_nStageCount == 60)
		{
			//�X�e�[�W�ړ�
			if (pStageNum == CGame::STAGENUM_1)
			{
				CFade::Create(CGame::STAGENUM_2);
			}
			else if (pStageNum == CGame::STAGENUM_2)
			{
				CFade::Create(CGame::STAGENUM_3);
			}
			else if (pStageNum == CGame::STAGENUM_3)
			{
				CFade::Create(CGame::STAGENUM_4);
			}
			else if (pStageNum == CGame::STAGENUM_4)
			{
				CFade::Create(CGame::STAGENUM_5);
			}
			else if (pStageNum == CGame::STAGENUM_5)
			{
				CFade::Create(CGame::STAGENUM_6);
			}

			//�X�e�[�W�J�ڂ����Ă��Ȃ���Ԃɂ���
			m_bStageNext = false;
			//�J�E���g������������
			m_nStageCount = 0;

		}
		//�J�E���g�𑝂�
		m_nStageCount++;
	}

	// �ړ��ʂ̑��
	pos += move;


	// �e����̑��
	CModel3D::SetPosition(pos);
	CModel3D::SetMove(move);
	CModel3D::SetMoveType(MoveType);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�ʒu�̏�����
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�}�b�v�ړ�����p�̃I�u�W�F�N�g�ȊO��`�悷��
	if (m_nType != 2)
	{
		CModel3D::Draw();
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, float move, int nTexType,int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObject *pObject = NULL;

	// NULL�`�F�b�N
	if (pObject == NULL)
	{// �������̓��I�m��

		pObject = new CObject;

		if (pObject != NULL)
		{
			// ��ނ̐ݒ�
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// �I�u�W�F�N�g���Ƃ̐ݒ�p�^�C�v
			pObject->m_nType = nObjectType;
			// �I�u�W�F�N�g�N���X�̐���
			pObject->Init();
			// �ʒu����
			pObject->SetPosition(pos);
			// ��]�𔽉f
			pObject->SetRot(rot);
			// �����̎�ނƈړ��ʂ�ݒ�
			pObject->SetMoveType(nMovetype);
			pObject->m_move = D3DXVECTOR3(move, move, move);
			// �R���W������ONOFF
			pObject->m_nCollision = nCollision;
		}
	}

	return pObject;
}
//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;							

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[0], NULL, &m_nNumMatModel[0], &m_pMeshModel[0]);
	D3DXLoadMeshFromX(MODEL_NAME_2, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[1], NULL, &m_nNumMatModel[1], &m_pMeshModel[1]);
	D3DXLoadMeshFromX(MODEL_NAME_3, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[2], NULL, &m_nNumMatModel[2], &m_pMeshModel[2]);
	D3DXLoadMeshFromX(MODEL_NAME_4, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[3], NULL, &m_nNumMatModel[3], &m_pMeshModel[3]);
	D3DXLoadMeshFromX(MODEL_NAME_5, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[4], NULL, &m_nNumMatModel[4], &m_pMeshModel[4]);
	D3DXLoadMeshFromX(MODEL_NAME_6, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[5], NULL, &m_nNumMatModel[5], &m_pMeshModel[5]);
	D3DXLoadMeshFromX(MODEL_NAME_7, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[6], NULL, &m_nNumMatModel[6], &m_pMeshModel[6]);
	D3DXLoadMeshFromX(MODEL_NAME_8, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[7], NULL, &m_nNumMatModel[7], &m_pMeshModel[7]);
	D3DXLoadMeshFromX(MODEL_NAME_9, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[8], NULL, &m_nNumMatModel[8], &m_pMeshModel[8]);
	D3DXLoadMeshFromX(MODEL_NAME_10, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[9], NULL, &m_nNumMatModel[9], &m_pMeshModel[9]);
	D3DXLoadMeshFromX(MODEL_NAME_11, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[10], NULL, &m_nNumMatModel[10], &m_pMeshModel[10]);
	D3DXLoadMeshFromX(MODEL_NAME_12, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[11], NULL, &m_nNumMatModel[11], &m_pMeshModel[11]);
	D3DXLoadMeshFromX(MODEL_NAME_13, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[12], NULL, &m_nNumMatModel[12], &m_pMeshModel[12]);
	D3DXLoadMeshFromX(MODEL_NAME_14, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[13], NULL, &m_nNumMatModel[13], &m_pMeshModel[13]);
	D3DXLoadMeshFromX(MODEL_NAME_15, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[14], NULL, &m_nNumMatModel[14], &m_pMeshModel[14]);
	D3DXLoadMeshFromX(MODEL_NAME_16, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[15], NULL, &m_nNumMatModel[15], &m_pMeshModel[15]);
	D3DXLoadMeshFromX(MODEL_NAME_17, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[16], NULL, &m_nNumMatModel[16], &m_pMeshModel[16]);
	D3DXLoadMeshFromX(MODEL_NAME_18, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[17], NULL, &m_nNumMatModel[17], &m_pMeshModel[17]);
	D3DXLoadMeshFromX(MODEL_NAME_19, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[18], NULL, &m_nNumMatModel[18], &m_pMeshModel[18]);
	D3DXLoadMeshFromX(MODEL_NAME_20, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[19], NULL, &m_nNumMatModel[19], &m_pMeshModel[19]);
	D3DXLoadMeshFromX(MODEL_NAME_21, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[20], NULL, &m_nNumMatModel[20], &m_pMeshModel[20]);
	D3DXLoadMeshFromX(MODEL_NAME_22, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[21], NULL, &m_nNumMatModel[21], &m_pMeshModel[21]);
	D3DXLoadMeshFromX(MODEL_NAME_23, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[22], NULL, &m_nNumMatModel[22], &m_pMeshModel[22]);
	D3DXLoadMeshFromX(MODEL_NAME_24, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[23], NULL, &m_nNumMatModel[23], &m_pMeshModel[23]);
	D3DXLoadMeshFromX(MODEL_NAME_25, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[24], NULL, &m_nNumMatModel[24], &m_pMeshModel[24]);
	D3DXLoadMeshFromX(MODEL_NAME_26, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[25], NULL, &m_nNumMatModel[25], &m_pMeshModel[25]);
	D3DXLoadMeshFromX(MODEL_NAME_27, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[26], NULL, &m_nNumMatModel[26], &m_pMeshModel[26]);
	D3DXLoadMeshFromX(MODEL_NAME_28, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[27], NULL, &m_nNumMatModel[27], &m_pMeshModel[27]);
	D3DXLoadMeshFromX(MODEL_NAME_29, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[28], NULL, &m_nNumMatModel[28], &m_pMeshModel[28]);
	D3DXLoadMeshFromX(MODEL_NAME_30, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[29], NULL, &m_nNumMatModel[29], &m_pMeshModel[29]);
	D3DXLoadMeshFromX(MODEL_NAME_31, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[30], NULL, &m_nNumMatModel[30], &m_pMeshModel[30]);
	D3DXLoadMeshFromX(MODEL_NAME_32, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[31], NULL, &m_nNumMatModel[31], &m_pMeshModel[31]);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\iron000.jpg", &m_pMeshTextures[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall003.jpg", &m_pMeshTextures[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall001.jpg", &m_pMeshTextures[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cona.jpg", &m_pMeshTextures[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\si-tu.jpg", &m_pMeshTextures[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bender.jpg", &m_pMeshTextures[5]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\grass.png", &m_pMeshTextures[6]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�t����.jpg", &m_pMeshTextures[7]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bark-texture.png", &m_pMeshTextures[8]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�؂̔e�N�X�`��.jpg", &m_pMeshTextures[9]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gerador3.jpg", &m_pMeshTextures[10]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CObject::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
	//�e�N�X�`��
	for (int nCntTex = 0; nCntTex < MAX_OBJECT_TEXTURE; nCntTex++)
	{
		if (m_pMeshTextures[nCntTex] != NULL)
		{
			m_pMeshTextures[nCntTex]->Release();
			m_pMeshTextures[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//	�X�e�[�W�ړ����ɏ��������邽��
//=============================================================================
void CObject::DeleteObject(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				pScene->Uninit();
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//===============================================================================
// �����蔻��
//===============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;
	//�������Ă��邩�������ĂȂ���
	bool bLand = false;
	//�����蔻��̕ۑ�
	int nCollision = m_nCollision;
	//���[�h�̏��
	CManager::MODE pMode = CManager::GetMode();
	//�J�����̏��
	CCamera *pCamera = CManager::GetCamera();
	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	switch (m_nCollision)
	{
	case 1:

		// �e����̎擾
		D3DXVECTOR3 Playerpos = *pPos;						// �v���C���[�̏����ʒu
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// �ʒu
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();		// �ړ���
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// �����̃^�C�v
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();			// ���f���̍ő�l
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();			// ���f���̍ŏ��l

		D3DXVECTOR3 ModelMax = CModel3D::VtxMax();	// �ʒu���݂̍ő�l
		D3DXVECTOR3 ModelMin = CModel3D::VtxMin();	// �ʒu���݂̍ŏ��l

		//�v�Z�O�p
		D3DXVECTOR3 WkMax = ModelMax;
		D3DXVECTOR3 WkMin = ModelMin;

		//�p�x
		D3DXVECTOR3 rot = CModel3D::GetRot();
		bool		bHit = false;

		// �ړ��ʂ̕ێ�
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		//���f���̌����ɂ���ē����蔻���MAX��MIN��ς���
		if (rot.y == 1.57f)
		{//�E����
			ModelMin.z = WkMax.x * -1.0f;
			ModelMax.z = WkMin.x * -1.0f;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -1.57f)
		{
			ModelMax.z = WkMax.x;
			ModelMin.z = WkMin.x;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -3.14f || rot.y == 3.14f)
		{
			ModelMin.x = WkMax.x * -1.0f;
			ModelMax.x = WkMin.x * -1.0f;
			ModelMin.z = WkMax.z * -1.0f;
			ModelMax.z = WkMin.z * -1.0f;
		}
		ModelMax += ModelPos;
		ModelMin += ModelPos;

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Z�͈͓̔��ɂ���		
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// X�͈͓̔��ɂ���
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// �I�u�W�F�N�g�̏ォ�瓖����ꍇ
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X�ړ�����
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z�ړ�����
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// �I�u�W�F�N�g�̉����瓖����ꍇ
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}
			}
		}

		if (pPos->y - PLAYER_HEIGHT <= ModelMax.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
		{// �I�u�W�F�N�g���Ƃ̓����蔻��
			if (pPos->x - PLAYER_DEPTH <= ModelMax.x && pPos->x + PLAYER_DEPTH >= ModelMin.x)
			{// �I�u�W�F�N�g���Ƃ̓����蔻��
				if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
				{//MAX �c��
					pPos->z = ModelMax.z + PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
				{//MIN �c��
					pPos->z = ModelMin.z - PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
			}
			if (pPos->z - PLAYER_DEPTH <= ModelMax.z && pPos->z + PLAYER_DEPTH >= ModelMin.z)
			{// �I�u�W�F�N�g���Ƃ̓����蔻�� 
				if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
				{//MAX ���E
					pPos->x = ModelMax.x + PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
				{//MIN ����
					pPos->x = ModelMin.x - PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
			}
		}


		if (m_nType == 2 && bHit == true)
		{// �}�b�v�ړ�����p�I�u�W�F�N�g
			if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(59.0f, 146.0f, 568.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-199.0f, 0.0f, 140.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_3)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(905.0f, 190.0f, 540.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(635.0f, 0.0f, 680.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_4)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(470.0f, 240.0f, 660.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(845.0f, 0.0f, -160.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_5)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(-1040.0f, 170.0f, 400.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-740.0f, 0.0f, 280.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_6)
			{
				if (CFade::GetFade() == CFade::FADE_NONE)
				{//P�L�[�������ꂽ��
					//�V�K�ǉ�
					CManager::SetGameScore(CTime::GetTime());
					CManager::RankingScore(CTime::GetTime());

					//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
					CPlayer::SetCancelStageNext(true);

					CGame::SetGameState(CGame::GAMESTATE_CLEAR);
				}
			}
		}

		// �ʒu�̑��
		CModel3D::SetPosition(ModelPos);
		// �ړ��ʂ̑��
		m_ModelMove = ModelMove;

		break;
	}

	return bLand;
}