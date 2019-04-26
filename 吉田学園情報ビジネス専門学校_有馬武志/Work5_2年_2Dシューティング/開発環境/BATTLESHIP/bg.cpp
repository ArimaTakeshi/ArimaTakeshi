//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "bg.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\�C.jpg"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2		"data\\TEXTURE\\�C�P.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3		"data\\TEXTURE\\�e�_.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4		"data\\TEXTURE\\�C.jpg"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_5		"data\\TEXTURE\\Clear000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_6		"data\\TEXTURE\\Over000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_7		"data\\TEXTURE\\mountain000.png"//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_8		"data\\TEXTURE\\sky.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_9		"data\\TEXTURE\\�C�g.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_10		"data\\TEXTURE\\���l.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_11		"data\\TEXTURE\\�C.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_12		"data\\TEXTURE\\konku.jpg"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define BG_TEXTURE_UV_U		(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V		(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CBg::CBg() : CScene2D(1)//�D��D�ʃC�j�V�����C�Y
{
	m_nCnt = 0;
	m_nType = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CBg::~CBg()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(void)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BG);

	D3DXVECTOR3 VtxPos[4];
	D3DXCOLOR Color[4];

	//�f�t�H���g�e�N�X�`���ݒ�
	VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	if (m_nType == 3)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 6)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 330.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 330.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f);
	}
	else if (m_nType == 7)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, 500.0f, 0.0f);
	}
	else if (m_nType == 8)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 475.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 475.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 9)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 455.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 455.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, 600.0f, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, 600.0f, 0.0f);
	}
	else if (m_nType == 10)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 11)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}
	else if (m_nType == 12)
	{//�e�N�X�`���ݒ�
		VtxPos[0] = D3DXVECTOR3(0.0f, 570.0f, 0.0f);
		VtxPos[1] = D3DXVECTOR3(SCREEN_WIDTH, 570.0f, 0.0f);
		VtxPos[2] = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		VtxPos[3] = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	}

	//�F�̐ݒ�
	if (m_nType == 1)
	{//�e�N�X�`���ݒ�
		Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}
	else if (m_nType == 2)
	{//�e�N�X�`���ݒ�
		Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
		Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);
	}
	else if (m_nType == 8)
	{//�e�N�X�`���ݒ�
		Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
		Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f);
	}
	else
	{//����ȊO�̏ꍇ���ׂĂ̏�����
		for (int nCount = 0; nCount < 4; nCount++)
		{
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	CScene2D::SetVtxPos(&VtxPos[0]);
	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBg::Update(void)
{
	D3DXVECTOR2 UV[4];
	D3DXVECTOR3 VtxPos[4];
	D3DXVECTOR3 move;

	m_nCnt++;

	if (m_nType == 0)
	{//�e�N�X�`���ݒ� �c�X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f, 0.0f + (m_nCnt * 0.0007f));
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f + (m_nCnt * 0.0007f));
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V + (m_nCnt * 0.0007f));
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V + (m_nCnt * 0.0007f));
	}
	else if (m_nType == 1)
	{//�e�N�X�`���ݒ� �c�X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f, 0.0f - (m_nCnt * 0.0004f));
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f - (m_nCnt * 0.0004f));
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V - (m_nCnt * 0.0004f));
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V - (m_nCnt * 0.0004f));
	}
	else if (m_nType == 2)
	{//�e�N�X�`���ݒ� �c�X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f, 0.0f - (m_nCnt * 0.0002f));
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f - (m_nCnt * 0.0002f));
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V - (m_nCnt * 0.0002f));
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V - (m_nCnt * 0.0002f));
	}
	else if (m_nType == 3)
	{//�e�N�X�`���ݒ� ���X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), 0.0f );
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), 0.0f );
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V );
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V );
	}
	else if (m_nType == 6)
	{//�e�N�X�`���ݒ� ���X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 7)
	{//�e�N�X�`���ݒ� ���X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00002f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00002f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00002f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00002f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 8)
	{//�e�N�X�`���ݒ� ���X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0002f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 9)
	{//�e�N�X�`���ݒ� ���X�N���[���p
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.00003f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 10)
	{
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0007f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0007f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0007f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0007f), BG_TEXTURE_UV_V);
	}
	else if (m_nType == 11)
	{
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0004f), 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0004f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * 0.0004f), BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U - (m_nCnt * 0.0004f), BG_TEXTURE_UV_V);
	}
	else 
	{//�e�N�X�`���ݒ�
		UV[0] = D3DXVECTOR2(0.0f, 0.0f);
		UV[1] = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f);
		UV[2] = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V);
		UV[3] = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V);
	}

	//�v���C���[�̈ʒu�ƃT�C�Y
	CScene2D::SetMove(move);
	//�w�i��UV
	CScene2D::SetBg(&UV[0]);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBg::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CBg * CBg::Create(int nType)
{
	CBg *pBg = NULL;

	//NULL�`�F�b�N
	if (pBg == NULL)
	{//�������̓��I�m��

		pBg = new CBg;

		if (pBg != NULL)
		{
			//��ނ����蓖�Ă�
			pBg->m_nType = nType;
			//�I�u�W�F�N�g�N���X�̐���
			pBg->Init();
			//�e�N�X�`�������蓖�Ă�
			pBg->BindTexture(m_pTexture[nType]);
		}
	}

	return pBg;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[1]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_3,
		&m_pTexture[2]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[3]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_5,
		&m_pTexture[4]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_6,
		&m_pTexture[5]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_7,
		&m_pTexture[6]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_8,
		&m_pTexture[7]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_9,
		&m_pTexture[8]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_10,
		&m_pTexture[9]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_11,
		&m_pTexture[10]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[11]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_12,
		&m_pTexture[12]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CBg::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}