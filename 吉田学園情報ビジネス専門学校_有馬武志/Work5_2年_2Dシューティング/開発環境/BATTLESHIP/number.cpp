//=============================================================================
//
// �����̏��� [number.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "number.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "score.h"
#include <string>
#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME1			"data\\TEXTURE\\number000.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME2			"data\\TEXTURE\\number001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_KILL_SIZE_X			(20)							//�e�N�X�`���c�T�C�Y
#define MAX_KILL_SIZE_Y			(30)							//�e�N�X�`�����T�C�Y
#define MAX_DAMAGE_SIZE_X		(8)								//�e�N�X�`���c�T�C�Y
#define MAX_DAMAGE_SIZE_Y		(16)							//�e�N�X�`�����T�C�Y
#define MAX_SCORE_SIZE_X		(20)							//�e�N�X�`���c�T�C�Y
#define MAX_SCORE_SIZE_Y		(30)							//�e�N�X�`�����T�C�Y
#define MAX_NONE_SIZE_X			(20)							//�e�N�X�`���c�T�C�Y
#define MAX_NONE_SIZE_Y			(30)							//�e�N�X�`�����T�C�Y
#define BG_TEXTURE_UV_U			(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V			(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture[MAX_NUMBER_TEXTURE] = {};
int CNumber::m_nType = TYPE_NONE;

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{

}
//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME1, &m_pTexture[0]);

	//�e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME2, &m_pTexture[1]);
	
	return S_OK;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();
	m_pos = pos;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (m_nType)
	{
	case TYPE_SCORE:
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_SCORE_SIZE_X, m_pos.y - MAX_SCORE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_SCORE_SIZE_X, m_pos.y - MAX_SCORE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_SCORE_SIZE_X, m_pos.y + MAX_SCORE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_SCORE_SIZE_X, m_pos.y + MAX_SCORE_SIZE_Y, 0.0f);
		break;
	case TYPE_DAMAGE:
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_DAMAGE_SIZE_X, m_pos.y - MAX_DAMAGE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_DAMAGE_SIZE_X, m_pos.y - MAX_DAMAGE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_DAMAGE_SIZE_X, m_pos.y + MAX_DAMAGE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_DAMAGE_SIZE_X, m_pos.y + MAX_DAMAGE_SIZE_Y, 0.0f);
		break;
	case TYPE_KILL:
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_KILL_SIZE_X, m_pos.y - MAX_KILL_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_KILL_SIZE_X, m_pos.y - MAX_KILL_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_KILL_SIZE_X, m_pos.y + MAX_KILL_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_KILL_SIZE_X, m_pos.y + MAX_KILL_SIZE_Y, 0.0f);
		break;
	default:
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_NONE_SIZE_X, m_pos.y - MAX_NONE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_NONE_SIZE_X, m_pos.y - MAX_NONE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_NONE_SIZE_X, m_pos.y + MAX_NONE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_NONE_SIZE_X, m_pos.y + MAX_NONE_SIZE_Y, 0.0f);
		break;
	}

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//�F�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CNumber::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�������g�̔j��
	//Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CNumber::Update(void)
{


}
//=============================================================================
// �`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	for (int nCount = 0; nCount < MAX_NUMBER_TEXTURE; nCount++)
	{
		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}
//=============================================================================
// �N���G�C�g
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X
	CNumber *pNumber = {};

	if (pNumber == NULL)
	{
		//�������𓮓I�m��
		pNumber = new CNumber;

		if (pNumber != NULL)
		{
			// �|���S���̏���������
			pNumber->Init(pos);
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);

	}

	return pNumber;
}
//=============================================================================
// �e�N�X�`���̊J������
//=============================================================================
void CNumber::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_NUMBER_TEXTURE; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
// �e�N�X�`���̐ݒu����
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2((nNumber % 10) * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nNumber % 10) * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((nNumber % 10) * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nNumber % 10) * 0.1f + 0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

