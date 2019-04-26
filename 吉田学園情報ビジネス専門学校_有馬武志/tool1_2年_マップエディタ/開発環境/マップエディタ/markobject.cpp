//=============================================================================
//
// ��̃I�u�W�F�N�g�̏��� [markobject.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "markobject.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "object.h"
#include "imgui_arima.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MARK_MODEL_NAME_1	"data\\MODEL\\saku000.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_2	"data\\MODEL\\saku001.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_3	"data\\MODEL\\wall000.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_4	"data\\MODEL\\wall001.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_5	"data\\MODEL\\bed.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_6	"data\\MODEL\\peple.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_7	"data\\MODEL\\stair.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_8	"data\\MODEL\\���̋@.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_9	"data\\MODEL\\��.x"					//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_10	"data\\MODEL\\grass.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_11	"data\\MODEL\\TreeU.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_12	"data\\MODEL\\TreeD.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_13	"data\\MODEL\\saku003.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_14	"data\\MODEL\\WoodenDesk.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_15	"data\\MODEL\\WoodenChair.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_16	"data\\MODEL\\�i�{�[��.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_17	"data\\MODEL\\Extinguisher.x"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_18	"data\\MODEL\\locker.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_19	"data\\MODEL\\door.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_20	"data\\MODEL\\SmallWoodenDesk.x"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_21	"data\\MODEL\\�S�~��.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_22	"data\\MODEL\\counter.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_23	"data\\MODEL\\fence.x"				//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_24	"data\\MODEL\\security.x"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_25	"data\\MODEL\\floor.x"			    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_26	"data\\MODEL\\smallfence.x"		    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_27	"data\\MODEL\\ArmoredCar.x"		    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_28	"data\\MODEL\\gate.x"			    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_29	"data\\MODEL\\prison.x"			    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_30	"data\\MODEL\\tower.x"			    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_31	"data\\MODEL\\cone.x"			    //�ǂݍ��ރe�N�X�`���t�@�C��
#define MARK_MODEL_NAME_32	"data\\MODEL\\Generator.x"			  //�ǂݍ��ރe�N�X�`���t�@�C��

#define MODEL_SPEED     (5.0f)
#define MAX_LSHIFTSPEED (0.5f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CMarkObject::m_pMeshMarkModel[MAX_MARKOBJECT] = {};						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CMarkObject::m_pBuffMatMarkModel[MAX_MARKOBJECT] = {};					//�}�e���A���̏��ւ̃|�C���^
DWORD CMarkObject::m_nNumMatMarkModel[MAX_MARKOBJECT] = {};							//�}�e���A���̏��
LPDIRECT3DTEXTURE9 CMarkObject::m_pMeshMarkTextures[MAX_MARKOBJECT_TEXTURE] = {};	//�e�N�X�`���̏��
CObject *CMarkObject::m_pObject = NULL;
int CMarkObject::m_nMarkObjNum = 0;
bool CMarkObject::m_bCraftDelete = false;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CMarkObject::CMarkObject() : CModel3D(MARKOBJECT_PRIOTITY,CScene::OBJTYPE_MARKOBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 3.0f;
	m_nSelectCollision = 1;
	m_nTexType = 0;
	m_nCraftDeleteNumber = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CMarkObject::~CMarkObject()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMarkObject::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3D���f����Init
	CModel3D::Init();
	
	//�I�u�W�F�N�g�̃e�N�X�`���̓ǂݍ���
	m_pObject->Load();

	// �ʒu�̏�����
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ʒu�̑��
	CModel3D::SetPosition(pos);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CMarkObject::Uninit(void)
{
	//3D���f����Uninit
	CModel3D::Uninit();

	//�I�u�W�F�N�g�̃e�N�X�`���̔j��
	m_pObject->UnLoad();

}
//=============================================================================
// �X�V����
//=============================================================================
void CMarkObject::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	//3D���f����Update
	CModel3D::Update();
	//�ʒu�̏�����
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	//�����̑��
	D3DXVECTOR3 &rot = CModel3D::GetRot();

	//�ݒu���[�h
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 0)
	{
		//-------------------------------------
		//        Imgui����l��Ⴄ
		//-------------------------------------
		m_move = CImgui_Arima::GetObjectPos();
		rot = CImgui_Arima::GetObjectRot();
		m_nSelectCollision = CImgui_Arima::GetObjectCollition();
		m_nSelectNum = CImgui_Arima::GetObjectType();
		m_bSetObject = CImgui_Arima::GetObjectSet();

		//�u������Ԃ��ǂ���
		bool bOnOff = false;

		//�ʒu��ۑ�
		if (CImgui_Arima::GetObjectClidked() % 2 == 1)
		{
			CDebugProc::Print("�ۑ��I");
			m_pObject->TextSave();
		}

		//�I�u�W�F�N�g�̐���
		if (m_bSetObject == true)
		{
			//�I�u�W�F�N�g�̐���
			m_pObject = CObject::Create(pos, rot, 0.0f, m_nTexType, m_nSelectNum, CObject::MOVETYPE_NOT, m_nSelectCollision);
			//�u�������
			bOnOff = true;
			//�u�������̌v�Z
			m_nMarkObjNum += 1;
		}

		switch (m_nSelectNum)
		{
		case 0:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g��000
			CMarkObject::BindModel(m_pMeshMarkModel[0], m_pBuffMatMarkModel[0], m_nNumMatMarkModel[0], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[0], m_pBuffMatMarkModel[0], m_nNumMatMarkModel[0], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 1:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g��001
			CMarkObject::BindModel(m_pMeshMarkModel[1], m_pBuffMatMarkModel[1], m_nNumMatMarkModel[1], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[1], m_pBuffMatMarkModel[1], m_nNumMatMarkModel[1], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 2:
			//�e�N�X�`���̎��
			m_nTexType = 1;
			// �I�u�W�F�N�g��000
			CMarkObject::BindModel(m_pMeshMarkModel[2], m_pBuffMatMarkModel[2], m_nNumMatMarkModel[2], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[2], m_pBuffMatMarkModel[2], m_nNumMatMarkModel[2], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 3:
			//�e�N�X�`���̎��
			m_nTexType = 2;
			// �I�u�W�F�N�g��001
			CMarkObject::BindModel(m_pMeshMarkModel[3], m_pBuffMatMarkModel[3], m_nNumMatMarkModel[3], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[3], m_pBuffMatMarkModel[3], m_nNumMatMarkModel[3], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 4:
			//�e�N�X�`���̎��
			m_nTexType = 4;
			// �I�u�W�F�N�g�x�b�h
			CMarkObject::BindModel(m_pMeshMarkModel[4], m_pBuffMatMarkModel[4], m_nNumMatMarkModel[4], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[4], m_pBuffMatMarkModel[4], m_nNumMatMarkModel[4], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 5:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�l
			CMarkObject::BindModel(m_pMeshMarkModel[5], m_pBuffMatMarkModel[5], m_nNumMatMarkModel[5], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[5], m_pBuffMatMarkModel[5], m_nNumMatMarkModel[5], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 6:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[6], m_pBuffMatMarkModel[6], m_nNumMatMarkModel[6], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[6], m_pBuffMatMarkModel[6], m_nNumMatMarkModel[6], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 7:
			//�e�N�X�`���̎��
			m_nTexType = 5;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[7], m_pBuffMatMarkModel[7], m_nNumMatMarkModel[7], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[7], m_pBuffMatMarkModel[7], m_nNumMatMarkModel[7], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 8:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[8], m_pBuffMatMarkModel[8], m_nNumMatMarkModel[8], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[8], m_pBuffMatMarkModel[8], m_nNumMatMarkModel[8], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 9:
			//�e�N�X�`���̎��
			m_nTexType = 6;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[9], m_pBuffMatMarkModel[9], m_nNumMatMarkModel[9], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[9], m_pBuffMatMarkModel[9], m_nNumMatMarkModel[9], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 10:
			//�e�N�X�`���̎��
			m_nTexType = 7;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[10], m_pBuffMatMarkModel[10], m_nNumMatMarkModel[10], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[10], m_pBuffMatMarkModel[10], m_nNumMatMarkModel[10], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 11:
			//�e�N�X�`���̎��
			m_nTexType = 8;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[11], m_pBuffMatMarkModel[11], m_nNumMatMarkModel[11], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[11], m_pBuffMatMarkModel[11], m_nNumMatMarkModel[11], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
		case 12:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[12], m_pBuffMatMarkModel[12], m_nNumMatMarkModel[12], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[12], m_pBuffMatMarkModel[12], m_nNumMatMarkModel[12], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 13:
			//�e�N�X�`���̎��
			m_nTexType = 9;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[13], m_pBuffMatMarkModel[13], m_nNumMatMarkModel[13], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[13], m_pBuffMatMarkModel[13], m_nNumMatMarkModel[13], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 14:
			//�e�N�X�`���̎��
			m_nTexType = 9;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[14], m_pBuffMatMarkModel[14], m_nNumMatMarkModel[14], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[14], m_pBuffMatMarkModel[14], m_nNumMatMarkModel[14], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 15:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[15], m_pBuffMatMarkModel[15], m_nNumMatMarkModel[15], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[15], m_pBuffMatMarkModel[15], m_nNumMatMarkModel[15], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 16:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[16], m_pBuffMatMarkModel[16], m_nNumMatMarkModel[16], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[16], m_pBuffMatMarkModel[16], m_nNumMatMarkModel[16], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 17:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[17], m_pBuffMatMarkModel[17], m_nNumMatMarkModel[17], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[17], m_pBuffMatMarkModel[17], m_nNumMatMarkModel[17], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 18:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[18], m_pBuffMatMarkModel[18], m_nNumMatMarkModel[18], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u�������
				m_pObject->BindModel(m_pMeshMarkModel[18], m_pBuffMatMarkModel[18], m_nNumMatMarkModel[18], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 19:
			//�e�N�X�`���̎��
			m_nTexType = 9;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[19], m_pBuffMatMarkModel[19], m_nNumMatMarkModel[19], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[19], m_pBuffMatMarkModel[19], m_nNumMatMarkModel[19], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 20:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[20], m_pBuffMatMarkModel[20], m_nNumMatMarkModel[20], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[20], m_pBuffMatMarkModel[20], m_nNumMatMarkModel[20], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 21:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[21], m_pBuffMatMarkModel[21], m_nNumMatMarkModel[21], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[21], m_pBuffMatMarkModel[21], m_nNumMatMarkModel[21], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 22:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[22], m_pBuffMatMarkModel[22], m_nNumMatMarkModel[22], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[22], m_pBuffMatMarkModel[22], m_nNumMatMarkModel[22], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 23:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[23], m_pBuffMatMarkModel[23], m_nNumMatMarkModel[23], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[23], m_pBuffMatMarkModel[23], m_nNumMatMarkModel[23], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 24:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[24], m_pBuffMatMarkModel[24], m_nNumMatMarkModel[24], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[24], m_pBuffMatMarkModel[24], m_nNumMatMarkModel[24], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 25:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[25], m_pBuffMatMarkModel[25], m_nNumMatMarkModel[25], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[25], m_pBuffMatMarkModel[25], m_nNumMatMarkModel[25], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 26:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[26], m_pBuffMatMarkModel[26], m_nNumMatMarkModel[26], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[26], m_pBuffMatMarkModel[26], m_nNumMatMarkModel[26], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 27:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[27], m_pBuffMatMarkModel[27], m_nNumMatMarkModel[27], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[27], m_pBuffMatMarkModel[27], m_nNumMatMarkModel[27], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 28:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[28], m_pBuffMatMarkModel[28], m_nNumMatMarkModel[28], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[28], m_pBuffMatMarkModel[28], m_nNumMatMarkModel[28], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 29:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[29], m_pBuffMatMarkModel[29], m_nNumMatMarkModel[29], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[29], m_pBuffMatMarkModel[29], m_nNumMatMarkModel[29], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 30:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[30], m_pBuffMatMarkModel[30], m_nNumMatMarkModel[30], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[30], m_pBuffMatMarkModel[30], m_nNumMatMarkModel[30], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 31:
			//�e�N�X�`���̎��
			m_nTexType = 10;
			// �I�u�W�F�N�g�K�i
			CMarkObject::BindModel(m_pMeshMarkModel[31], m_pBuffMatMarkModel[31], m_nNumMatMarkModel[31], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//�u������ԓW����
				m_pObject->BindModel(m_pMeshMarkModel[31], m_pBuffMatMarkModel[31], m_nNumMatMarkModel[31], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		}

		// �ړ��ʂ̑��
		pos = m_move;

		// �e����̑��
		CModel3D::SetPosition(pos);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMarkObject::Draw(void)
{
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//�}�e���A���𓧖�������
	for (int nCount = 0; nCount < MAX_MARKOBJECT; nCount++)
	{
		pMat = (D3DXMATERIAL*)m_pBuffMatMarkModel[nCount]->GetBufferPointer();
		pMat->MatD3D.Diffuse.a = 0.4f;
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�ʒu�̏�����
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�ݒu���[�h
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 0)
	{
		//3D���f����Draw
		CModel3D::Draw();
	}

	//�}�e���A���̒l������������
	for (int nCount = 0; nCount < MAX_MARKOBJECT; nCount++)
	{
		pMat = (D3DXMATERIAL*)m_pBuffMatMarkModel[nCount]->GetBufferPointer();
		pMat->MatD3D.Diffuse.a = 1.0f;
	}

}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CMarkObject * CMarkObject::Create(D3DXVECTOR3 pos,int nTexType,int nObjectType)
{
	CMarkObject *pMarkObject = NULL;

	// NULL�`�F�b�N
	if (pMarkObject == NULL)
	{// �������̓��I�m��

		pMarkObject = new CMarkObject;

		if (pMarkObject != NULL)
		{
			// ��ނ̐ݒ�
			pMarkObject->BindModel(m_pMeshMarkModel[nObjectType], m_pBuffMatMarkModel[nObjectType], m_nNumMatMarkModel[nObjectType], m_pMeshMarkTextures[nTexType]);
			// �I�u�W�F�N�g�N���X�̐���
			pMarkObject->Init();
			// �I�u�W�F�N�g���Ƃ̐ݒ�p�^�C�v
			pMarkObject->m_nType = nObjectType;
			// �ʒu����
			pMarkObject->SetPosition(pos);
		}
	}

	return pMarkObject;
}
//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CMarkObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();				

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MARK_MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[0], NULL, &m_nNumMatMarkModel[0], &m_pMeshMarkModel[0]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_2, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[1], NULL, &m_nNumMatMarkModel[1], &m_pMeshMarkModel[1]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_3, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[2], NULL, &m_nNumMatMarkModel[2], &m_pMeshMarkModel[2]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_4, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[3], NULL, &m_nNumMatMarkModel[3], &m_pMeshMarkModel[3]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_5, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[4], NULL, &m_nNumMatMarkModel[4], &m_pMeshMarkModel[4]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_6, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[5], NULL, &m_nNumMatMarkModel[5], &m_pMeshMarkModel[5]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_7, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[6], NULL, &m_nNumMatMarkModel[6], &m_pMeshMarkModel[6]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_8, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[7], NULL, &m_nNumMatMarkModel[7], &m_pMeshMarkModel[7]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_9, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[8], NULL, &m_nNumMatMarkModel[8], &m_pMeshMarkModel[8]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_10, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[9], NULL, &m_nNumMatMarkModel[9], &m_pMeshMarkModel[9]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_11, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[10], NULL, &m_nNumMatMarkModel[10], &m_pMeshMarkModel[10]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_12, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[11], NULL, &m_nNumMatMarkModel[11], &m_pMeshMarkModel[11]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_13, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[12], NULL, &m_nNumMatMarkModel[12], &m_pMeshMarkModel[12]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_14, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[13], NULL, &m_nNumMatMarkModel[13], &m_pMeshMarkModel[13]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_15, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[14], NULL, &m_nNumMatMarkModel[14], &m_pMeshMarkModel[14]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_16, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[15], NULL, &m_nNumMatMarkModel[15], &m_pMeshMarkModel[15]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_17, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[16], NULL, &m_nNumMatMarkModel[16], &m_pMeshMarkModel[16]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_18, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[17], NULL, &m_nNumMatMarkModel[17], &m_pMeshMarkModel[17]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_19, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[18], NULL, &m_nNumMatMarkModel[18], &m_pMeshMarkModel[18]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_20, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[19], NULL, &m_nNumMatMarkModel[19], &m_pMeshMarkModel[19]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_21, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[20], NULL, &m_nNumMatMarkModel[20], &m_pMeshMarkModel[20]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_22, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[21], NULL, &m_nNumMatMarkModel[21], &m_pMeshMarkModel[21]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_23, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[22], NULL, &m_nNumMatMarkModel[22], &m_pMeshMarkModel[22]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_24, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[23], NULL, &m_nNumMatMarkModel[23], &m_pMeshMarkModel[23]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_25, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[24], NULL, &m_nNumMatMarkModel[24], &m_pMeshMarkModel[24]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_26, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[25], NULL, &m_nNumMatMarkModel[25], &m_pMeshMarkModel[25]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_27, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[26], NULL, &m_nNumMatMarkModel[26], &m_pMeshMarkModel[26]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_28, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[27], NULL, &m_nNumMatMarkModel[27], &m_pMeshMarkModel[27]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_29, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[28], NULL, &m_nNumMatMarkModel[28], &m_pMeshMarkModel[28]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_30, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[29], NULL, &m_nNumMatMarkModel[29], &m_pMeshMarkModel[29]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_31, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[30], NULL, &m_nNumMatMarkModel[30], &m_pMeshMarkModel[30]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_32, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[31], NULL, &m_nNumMatMarkModel[31], &m_pMeshMarkModel[31]);

	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\iron000.jpg",&m_pMeshMarkTextures[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall002.jpg", &m_pMeshMarkTextures[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall001.jpg", &m_pMeshMarkTextures[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cona.jpg", &m_pMeshMarkTextures[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\si-tu.jpg", &m_pMeshMarkTextures[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bender.jpg", &m_pMeshMarkTextures[5]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\grass.png", &m_pMeshMarkTextures[6]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�t����.jpg", &m_pMeshMarkTextures[7]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bark-texture.jpg", &m_pMeshMarkTextures[8]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\�؂̔e�N�X�`��.jpg", &m_pMeshMarkTextures[9]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gerador3.jpg", &m_pMeshMarkTextures[10]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CMarkObject::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MARKOBJECT; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMeshMarkModel[nCount] != NULL)
		{
			m_pMeshMarkModel[nCount]->Release();
			m_pMeshMarkModel[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMatMarkModel[nCount] != NULL)
		{
			m_pBuffMatMarkModel[nCount]->Release();
			m_pBuffMatMarkModel[nCount] = NULL;
		}
	}
	//�e�N�X�`��
	for (int nCntTex = 0; nCntTex < MAX_MARKOBJECT_TEXTURE; nCntTex++)
	{
		if (m_pMeshMarkTextures[nCntTex] != NULL)
		{
			m_pMeshMarkTextures[nCntTex]->Release();
			m_pMeshMarkTextures[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//	�I�u�W�F�N�g�̓����蔻��
//=============================================================================
void CMarkObject::CollisitionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
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
		{
			//�^�C�v�����b�V����������
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				//�I�u�W�F�N�g�̂����锻��
				((CObject*)pScene)->CollisionObject(pPos, pPosOld, pMove);

				CDebugProc::Print("��������\n");
			}
		}

		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}