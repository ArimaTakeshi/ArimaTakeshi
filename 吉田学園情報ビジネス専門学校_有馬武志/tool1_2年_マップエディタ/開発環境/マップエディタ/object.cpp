//=============================================================================
//
// �I�u�W�F�N�g�̏��� [object.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "markobject.h"
#include "object.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXT_OBJECTNAME	"data\\TEXT\\�X�e�[�W�t���b�g\\objecy.txt"	//�ǂݍ��ރe�L�X�g�t�@�C��
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
#define PLAYER_DEPTH	(10)			// �v���C���[�̕������p
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
	m_nSetObjectNum = 0;
	m_nTexType = 0;
	m_nCollision = 1;
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

	//�ʒu�̑��
	CModel3D::SetPosition(pos);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
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

	//���a
	float fRadius = 10.0f;
	//�~��
	float fCircumference = (((D3DX_PI * 2.0f) * fRadius));

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
	//3D���f����Draw
	CModel3D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float move, int nTexType,int nObjectType, MOVETYPE nMovetype,int nCollision)
{
	CObject *pObject = NULL;

	// NULL�`�F�b�N
	if (pObject == NULL)
	{// �������̓��I�m��

		pObject = new CObject;

		if (pObject != NULL)
		{
			pObject->m_nTexType = nTexType;
			// ��ނ̐ݒ�
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// �I�u�W�F�N�g�N���X�̐���
			pObject->Init();
			// �I�u�W�F�N�g���Ƃ̐ݒ�p�^�C�v
			pObject->m_nType = nObjectType;
			//����������
			pObject->m_rot = rot;
			//��]�𔽉f
			pObject->SetRot(pObject->m_rot);
			// �ʒu����
			pObject->SetPosition(pos);
			// �ʒu��`��
			pObject->m_pos = pos;
			// �����̎�ނƈړ��ʂ�ݒ�
			pObject->SetMoveType(nMovetype);
			//�ړ���
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
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\iron000.jpg",&m_pMeshTextures[0]);
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\wall\\wall003.jpg", &m_pMeshTextures[1]);
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\wall\\wall001.jpg", &m_pMeshTextures[2]);
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
//===============================================================================
// �����蔻��
//===============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//�������Ă��邩�������ĂȂ���
	bool bLand = false;
	int nCollision = m_nCollision;
	CManager::MODE pMode = CManager::GetMode();

	switch (m_nCollision)
	{
	case 1:

		// �e����̎擾
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// �ʒu
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();		// �ړ���
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// �����̃^�C�v
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();			// ���f���̍ő�l
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();			// ���f���̍ŏ��l

		D3DXVECTOR3 ModelMax = CModel3D::GetPosition() + CModel3D::VtxMax();	// �ʒu���݂̍ő�l
		D3DXVECTOR3 ModelMin = CModel3D::GetPosition() + CModel3D::VtxMin();	// �ʒu���݂̍ŏ��l

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

				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{// �I�u�W�F�N�g���Ƃ̓����蔻��
					//CDebugProc::Print("���f���̉E�� : %.1f\n", ModelMax.x);
					//CDebugProc::Print("���f���̍��� : %.1f\n", ModelMin.x);
					//CDebugProc::Print("���f���̉��� : %.1f\n", ModelMax.z);
					//CDebugProc::Print("���f���̎�O�� : %.1f\n", ModelMin.z);
					//CDebugProc::Print("���f���̒��_�� : %.1f\n", ModelMax.y);
					//CDebugProc::Print("���f���̑����� : %.1f\n", ModelMin.y);

					if (ModelMoveType == MOVETYPE_X_MOVE || ModelMoveType == MOVETYPE_ROTATION_Z)
					{// X�ړ��I�u�W�F�N�g
						if (pPosOld->x - (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x) >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE �E\n");
						}
						else if (pPosOld->x + (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x) <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��O\n");
						}
					}
					else if (ModelMoveType == MOVETYPE_Z_MOVE || ModelMoveType == MOVETYPE_ROTATION_X)
					{// Z�ړ��I�u�W�F�N�g
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE �E\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}

						if (pPosOld->z - (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z) >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��\n");
						}
						else if (pPosOld->z + (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z) <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE ��O\n");
						}
					}
					else
					{// ���ړ��I�u�W�F�N�g
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x + m_rot.x && pPos->x - PLAYER_DEPTH < ModelMax.x + m_rot.x)
						{// �E���甲�����ꍇ
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							
							//�������Ă�Œ������ƍ폜
							if (pCInputKeyBoard->GetKeyboardPress(DIK_DELETE) == true)
							{
								CMarkObject::SetObjectNum(CMarkObject::GetObjectNum() - 1);
								CObject::Uninit();
							}
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// �����甲�����ꍇ
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//�������Ă�Œ������ƍ폜
							if (pCInputKeyBoard->GetKeyboardPress(DIK_DELETE) == true)
							{
								CMarkObject::SetObjectNum(CMarkObject::GetObjectNum() - 1);
								CObject::Uninit();
							}
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// �����甲�����ꍇ
							pPos->z = ModelMax.z + PLAYER_DEPTH + 0.1f;
							//�������Ă�Œ������ƍ폜
							if (pCInputKeyBoard->GetKeyboardPress(DIK_DELETE) == true)
							{
								CMarkObject::SetObjectNum(CMarkObject::GetObjectNum() - 1);
								CObject::Uninit();
							}
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// ��O���甲�����ꍇ
							pPos->z = ModelMin.z - PLAYER_DEPTH - 0.1f;
							//�������Ă�Œ������ƍ폜
							if (pCInputKeyBoard->GetKeyboardPress(DIK_DELETE) == true)
							{
								CMarkObject::SetObjectNum(CMarkObject::GetObjectNum() - 1);
								CObject::Uninit();
							}
						}
					}
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
//===============================================================================
// �t�@�C���ɃZ�[�u
//===============================================================================
void CObject::TextSave(void)
{
	int nMarkObject = CMarkObject::GetObjectNum();

	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//�t�@�C���̃|�C���^
	FILE *pFile;

	//�t�@�C���ǂݎ��ݒ�
	pFile = fopen(TEXT_OBJECTNAME, "wb");

	//�v���C���[�̃e�L�X�g�f�[�^�̓ǂݍ���
	if (pFile != NULL)
	{
		//������
		fprintf(pFile, "#====================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#�@�}�b�v�̃I�u�W�F�N�g�z�u�̃G�f�B�^ [objecy.txt]\n");
		fprintf(pFile, "#�@����� : �L�n�@���u\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================\n\n");
		//�u�����I�u�W�F�N�g�̐�
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#�@�I�u�W�F�N�g�̐ݒu��\n");
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "OBJECT_SETNUM = ");
		fprintf(pFile, "%d\n\n", nMarkObject);
		//������
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#�@�I�u�W�F�N�g�̐ݒu���\n");
		fprintf(pFile, "#----------------------------------------------------\n");

		//NULL�`�F�b�N
		while (pScene != NULL)
		{
			//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
			CScene *pSceneNext = pScene->GetNext();

			if (pScene->GetDeath() == false)
			{
				//�^�C�v���I�u�W�F�N�g��������
				if (pScene->GetObjType() == OBJTYPE_OBJECT)
				{
					//�J�n�̂��߂̐錾
					fprintf(pFile, "OBJECT_START\n");
					//��ނ�����
					fprintf(pFile, "	TYPE = ");
					fprintf(pFile, "%d\n", ((CObject*)pScene)->m_nType);
					//�e�N�X�`���̎�ނ�����
					fprintf(pFile, "	TEXTURETYPE = ");
					fprintf(pFile, "%d\n", ((CObject*)pScene)->m_nTexType);
					//�����蔻�������
					fprintf(pFile, "	COLLISION = ");
					fprintf(pFile, "%d\n", ((CObject*)pScene)->m_nCollision);
					//�ʒu������
					fprintf(pFile, "	POS = ");
					fprintf(pFile, "%.2f ", ((CObject*)pScene)->m_pos.x);
					fprintf(pFile, "%.2f ", ((CObject*)pScene)->m_pos.y);
					fprintf(pFile, "%.2f\n", ((CObject*)pScene)->m_pos.z);
					//����������
					fprintf(pFile, "	ROT = ");
					fprintf(pFile, "%.2f ", ((CObject*)pScene)->GetRot().x);
					fprintf(pFile, "%.2f ", ((CObject*)pScene)->GetRot().y);
					fprintf(pFile, "%.2f\n", ((CObject*)pScene)->GetRot().z);		
					//�J�n�̂��߂̐錾
					fprintf(pFile, "OBJECT_END\n\n");
				}
			}

			//Next�Ɏ���Scene������
			pScene = pSceneNext;
		}

		//�t�@�C�������
		fclose(pFile);
	}
}