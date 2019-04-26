//=============================================================================
//
// �����̏��� [number.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "polygon.h"
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
#define TEXTURE_NAME			"data\\TEXTURE\\number001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define MAX_SIZE_X				(20)							//�e�N�X�`���c�T�C�Y
#define MAX_SIZE_Y				(30)							//�e�N�X�`�����T�C�Y
#define BG_TEXTURE_UV_U			(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V			(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPolygon::m_pTexture = {};

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	m_pVtxBuff = NULL;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{

}
//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CPolygon::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�C���X�^���X
	CManager Manager;

	//�f�o�C�X���擾
	pDevice = Manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME, &m_pTexture);

	return S_OK;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CPolygon::Init(D3DXVECTOR3 pos)
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

	// ���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - MAX_SIZE_X, m_pos.y - MAX_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + MAX_SIZE_X, m_pos.y - MAX_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - MAX_SIZE_X, m_pos.y + MAX_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + MAX_SIZE_X, m_pos.y + MAX_SIZE_Y, 0.0f);

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
void CPolygon::Uninit(void)
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
void CPolygon::Update(void)
{


}
//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
// �N���G�C�g
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos)
{
	//�C���X�^���X
	CPolygon *pNumber = {};

	if (pNumber == NULL)
	{
		//�������𓮓I�m��
		pNumber = new CPolygon;

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
void CPolygon::UnLoad(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
//=============================================================================
// �e�N�X�`���̐ݒu����
//=============================================================================
void CPolygon::SetNumber(int nNumber)
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

