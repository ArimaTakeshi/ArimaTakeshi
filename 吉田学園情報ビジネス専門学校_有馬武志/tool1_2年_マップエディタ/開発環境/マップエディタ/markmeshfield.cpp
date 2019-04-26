//=============================================================================
//
// ��̃��b�V���̏��� [markmesh.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "markmeshfield.h"
#include "meshfield.h"
#include "mesh.h"
#include "manager.h"
#include "scene.h"
#include "model.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"
#include "imgui_arima.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MARKMESHFIELD_0		"data\\TEXTURE\\mesh\\stairs.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MARKMESHFIELD_1		"data\\TEXTURE\\mesh\\flooa000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MARKMESHFIELD_2		"data\\TEXTURE\\mesh\\field03.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_MARKMESHFIELD_3		"data\\TEXTURE\\mesh\\green2.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define MAX_VTX_NUMBER				(4)									// �I���ł��钸�_�̂���
#define MAX_LSHIFTSPEED				(0.5f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CMarkMeshField::m_pTexture[MAX_MESH_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 CMarkMeshField::m_pVtxBuff = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 CMarkMeshField::m_pIdxBuff = NULL;				// �C���f�b�N�X�ւ̃|�C���^
CMeshField *CMarkMeshField::m_pMeshField = NULL;						// ���b�V���t�B�[���h�̃|�C���^
int CMarkMeshField::m_nMarkFieldNum = 0;								// ���b�V���t�B�[���h�̌�

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CMarkMeshField::CMarkMeshField() : CMesh(MESHFIELD_PRIOTITY, CScene::OBJTYPE_MARKMESHFILED)
{
	m_fMove = 3.0f;
	m_nWidthDivide = 5;
	m_nDepthDivide = 5;
	m_fDepthLength = 500.0f;
	m_fWidthLength = 500.0f;
	m_nVtxNumber = 0;
	m_fVtxHeight_No0 = 0;
	m_fVtxHeight_No1 = 0;
	m_fVtxHeight_No2 = 0;
	m_fVtxHeight_No3 = 0;
	m_nClidked = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CMarkMeshField::~CMarkMeshField()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMarkMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CMesh::Init();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMarkMeshField::Uninit(void)
{
	CMesh::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMarkMeshField::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();

	//�ݒu���[�h
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 1)
	{
		//�ʒu�̔��f
		D3DXVECTOR3 &m_pos = CMesh::GetPosition();

		CMesh::Update();

		//�ݒu���������Ă��Ȃ���
		bool bOnOff = false;

		//�ۑ��p�f�[�^
		int nFieldWD = m_nWidthDivide;
		int nFieldHD = m_nDepthDivide;
		float fFieldWL = m_fWidthLength;
		float fFieldHL = m_fDepthLength;
		float fVtxHeight_No0 = m_fVtxHeight_No0;
		float fVtxHeight_No1 = m_fVtxHeight_No1;
		float fVtxHeight_No2 = m_fVtxHeight_No2;
		float fVtxHeight_No3 = m_fVtxHeight_No3;

		//-------------------------------------
		//        Imgui����l��Ⴄ
		//-------------------------------------
		m_pos = CImgui_Arima::GetFieldPos();
		m_nWidthDivide = CImgui_Arima::GetFieldWD();
		m_nDepthDivide = CImgui_Arima::GetFieldHD();
		m_fWidthLength = (float)CImgui_Arima::GetFieldWL();
		m_fDepthLength = (float)CImgui_Arima::GetFieldHL();
		m_Vtx = CImgui_Arima::GetFieldVtx();
		m_nSelectNum = CImgui_Arima::GetFieldType();
		m_bSetFeild = CImgui_Arima::GetFeildSet();

		m_nClidked = CImgui_Arima::GetFieldClidked();
	
		m_fVtxHeight_No0 = m_Vtx.x;
		m_fVtxHeight_No1 = m_Vtx.y;
		m_fVtxHeight_No2 = m_Vtx.z;
		m_fVtxHeight_No3 = m_Vtx.w;

		//-------------------------------------
		//         �c�̕�������ύX
		//-------------------------------------
		if (nFieldWD > m_nWidthDivide)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_nWidthDivide > nFieldWD)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         ���̕�������ύX
		//-------------------------------------
		if (nFieldHD > m_nDepthDivide)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_nDepthDivide > nFieldHD)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         �c�̒����ύX��ύX
		//-------------------------------------
		if (fFieldHL > m_fDepthLength)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fDepthLength > fFieldHL)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         ���̒����ύX��ύX
		//-------------------------------------
		if (fFieldWL > m_fWidthLength)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fWidthLength > fFieldWL)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         ���_�̍����̕ύX
		//-------------------------------------
		if (fVtxHeight_No0 > m_fVtxHeight_No0)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No0 > fVtxHeight_No0)
		{//����������
			//�폜�Ɛ���
			UninitCreate(m_pos);
		}

		if (fVtxHeight_No1 > m_fVtxHeight_No1)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No1 > fVtxHeight_No1)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}

		if (fVtxHeight_No2 > m_fVtxHeight_No2)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No2 > fVtxHeight_No2)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}

		if (fVtxHeight_No3 > m_fVtxHeight_No3)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}
		if (m_fVtxHeight_No3 > fVtxHeight_No3)
		{//����������
		 //�폜�Ɛ���
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         �e�N�X�`���̕ύX
		//-------------------------------------
		switch (m_nSelectNum)
		{
		case 0:
			//�e�N�X�`���̎��
			m_nTexType = 0;
			//�e�N�X�`���̐ݒ�
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 1:
			//�e�N�X�`���̎��
			m_nTexType = 1;
			//�e�N�X�`���̐ݒ�
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 2:
			//�e�N�X�`���̎��
			m_nTexType = 2;
			//�e�N�X�`���̐ݒ�
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 3:
			//�e�N�X�`���̎��
			m_nTexType = 3;
			//�e�N�X�`���̐ݒ�
			CMarkMeshField::BindTexture(m_pTexture[m_nTexType]);
			break;
		}

		//-------------------------------------
		//         �I�u�W�F�N�g����
		//-------------------------------------
		if (m_bSetFeild == true)
		{
			//�I�u�W�F�N�g�̐���
			m_pMeshField = CMeshField::Create(m_pos, m_nWidthDivide, m_nDepthDivide, m_fWidthLength, m_fDepthLength, m_fVtxHeight_No0, m_fVtxHeight_No1, m_fVtxHeight_No2, m_fVtxHeight_No3, m_nSelectNum, 0);
			//�u�������
			bOnOff = true;
			//�u�������̌v�Z
			m_nMarkFieldNum += 1;
		}

		//�ʒu��ۑ�
		if (CImgui_Arima::GetFieldClidked() % 2 == 1)
		{
			m_pMeshField->TextSave();
		}

		m_pos += m_move;

		//����
		m_move.x += (0.0f - m_move.x) * 0.8f;
		m_move.y += (0.0f - m_move.y) * 0.8f;
		m_move.z += (0.0f - m_move.z) * 0.8f;

	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMarkMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���C���[�̈ʒu���
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//�Q�[���̏��
	CManager::MODE pMode = CManager::GetMode();

	//�ݒu���[�h
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 1)
	{
		CMesh::Draw();
	}
}
//===============================================================================
//�@�폜�Ɛ���
//===============================================================================
void CMarkMeshField::UninitCreate(D3DXVECTOR3 pos)
{
	//�폜
	CMarkMeshField::Uninit();

	//����
	CMarkMeshField::Create(pos, m_nWidthDivide, m_nDepthDivide, m_fWidthLength, m_fDepthLength,
		m_fVtxHeight_No0, m_fVtxHeight_No1, m_fVtxHeight_No2, m_fVtxHeight_No3, m_nSelectNum, m_nVtxNumber, 0);
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CMarkMeshField * CMarkMeshField::Create(D3DXVECTOR3 pos,int nMeshX, int nMeshZ,float fMeshWidth, float fMeshDepth, float fVtx0, float fVtxMeshX, float fVtxMeshZ, float fVtxMeshXMeshZ, int nTexType, int nVtxNumber,int nMeshType)
{
	CMarkMeshField *pMeshField = NULL;

	//NULL�`�F�b�N
	if (pMeshField == NULL)
	{//�������̓��I�m��

		pMeshField = new CMarkMeshField;

		if (pMeshField != NULL)
		{
			//�ʒu�̑��
			pMeshField->SetPosition(pos);
			//���b�V���̎��
			pMeshField->SetMeshType(nMeshType);
			//���b�V���̏���e�N���X�ɓn��
			pMeshField->SetMeshInfo(nMeshX, nMeshZ, fMeshDepth, fMeshWidth);
			//���b�V���̒��_�̍���
			pMeshField->SetVtx(fVtx0, fVtxMeshX, fVtxMeshZ, fVtxMeshXMeshZ);
			//�I�u�W�F�N�g�N���X�̐���
			pMeshField->Init();
			//�e�N�X�`���̐ݒ�
			pMeshField->BindTexture(m_pTexture[nTexType]);
			//���̕���������
			pMeshField->m_nWidthDivide = nMeshX;
			//�c�̕���������
			pMeshField->m_nDepthDivide = nMeshZ;
			//�����̑��
			pMeshField->m_fWidthLength = fMeshWidth;
			//���s�̑��
			pMeshField->m_fDepthLength = fMeshDepth;
			//���݂̑I�����Ă���e�N�X�`��
			pMeshField->m_nSelectNum = nTexType;
			//���_�̔ԍ�����
			pMeshField->m_nVtxNumber = nVtxNumber;
			//�e���_�̍����̑��
			pMeshField->m_fVtxHeight_No0 = fVtx0;
			pMeshField->m_fVtxHeight_No1 = fVtxMeshX;
			pMeshField->m_fVtxHeight_No2 = fVtxMeshZ;
			pMeshField->m_fVtxHeight_No3 = fVtxMeshXMeshZ;
		}
	}

	return pMeshField;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CMarkMeshField::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_MARKMESHFIELD_3, &m_pTexture[3]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CMarkMeshField::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MESH_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

