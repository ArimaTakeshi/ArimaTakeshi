//=============================================================================
//
// �̗͂̏��� [life.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "life.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\Life001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
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
LPDIRECT3DTEXTURE9 CLife::m_pTexture[NUM_TEXTURE_LIFE] = {};
LPDIRECT3DVERTEXBUFFER9 CLife::m_pVtxBuff = NULL;
int CLife::m_nCntSubtraction = 0;
CLife::Life CLife::m_Life[NUM_POLYGON_LIFE] = {};
int CLife::m_nMaxLife = 0;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CLife::CLife() : CScene(4)//�D��D�ʃC�j�V�����C�Y
{
	for (int nCount = 0; nCount < NUM_POLYGON_LIFE; nCount++)
	{
		m_Life[nCount] = {};					//���C�t�̍\����
	}
	m_nCntSubtraction = 0;						//�o�[�����炵�n�߂�J�E���^
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CLife::~CLife()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CLife::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �g
	m_Life[0].pos = D3DXVECTOR3(15.0f, 645.0f, 0.0f);
	m_Life[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_Life[0].nLife = MAX_LIFE;							// ���C�t���ő�ɂ���
	m_Life[0].fLength = BAR_WIDTH_LIFE;					// �o�[�̒�����ݒ�
	m_Life[0].nType = -1;								// �e�N�X�`����ON(0)OFF(-1)

	// �o�[
	for (int nCntLife = 1; nCntLife < NUM_POLYGON_LIFE; nCntLife++)
	{
		m_Life[nCntLife].pos = D3DXVECTOR3(15.0f, 645.0f, 0.0f);
		m_Life[nCntLife].nLife = MAX_LIFE;				// ���C�t���ő�ɂ���
		m_Life[nCntLife].fLength = BAR_WIDTH_LIFE;		// �o�[�̒�����ݒ�
		m_Life[nCntLife].nType = 0;						// �e�N�X�`����ON(0)OFF(-1)
	}

	m_Life[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_Life[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_Life[3].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);

	// �o�[�����炵�n�߂�J�E���^
	m_nCntSubtraction = 0;

	// ���_���̍쐬
	CLife::MakeVertexLife(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLife::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLife::Update(void)
{
	/*	g_Life[3].fLength == ���݂̃��C�t					�i�őO�ʂɗ���o�[�j			*/
	/*	g_Life[2].fLength == �_���[�W���󂯂Č��������̃o�[	�i�őO�ʂ������ɗ���o�[�j*/
	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		if (m_Life[2].fLength > m_Life[3].fLength)
		{// ���C�t�Ɠ����l�ɂȂ�܂Ō��̃Q�[�W�����炷
			m_nCntSubtraction++;								// �_���[�W�o�[�����炵�n�߂邽�߂̃J�E���g

			if (m_nCntSubtraction >= SUBTRACT_TIME)
			{// ��莞�Ԍo��
				m_Life[2].fLength -= BAR_WIDTH_LIFE * 0.01f;	// �_���[�W�o�[�̒�����1�������炷

				VERTEX_2D *pVtx;

				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//���_���W�̐ݒ�
				pVtx[(2 * 4) + 1].pos = D3DXVECTOR3(m_Life[2].pos.x + m_Life[2].fLength, m_Life[2].pos.y, 0.0f);
				pVtx[(2 * 4) + 3].pos = D3DXVECTOR3(m_Life[2].pos.x + m_Life[2].fLength, m_Life[2].pos.y + BAR_HEIGHT_LIFE, 0.0f);

				// ���_�o�b�t�@���A�����b�N����
				m_pVtxBuff->Unlock();
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CLife::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLife = 0; nCntLife < NUM_POLYGON_LIFE; nCntLife++)
	{
		// �e�N�X�`���̐ݒ�
		if (m_Life[nCntLife].nType >= 0)
		{// �e�N�X�`���̎w��
			pDevice->SetTexture(0, m_pTexture[m_Life[nCntLife].nType]);
		}
		else
		{// 0���Ⴂ�ƃe�N�X�`���𒣂�Ȃ�
			pDevice->SetTexture(0, NULL);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
	}
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CLife * CLife::Create()
{
	CLife *pLife = NULL;

	//NULL�`�F�b�N
	if (pLife == NULL)
	{//�������̓��I�m��

		pLife = new CLife;

		if (pLife != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pLife->Init();
		}
	}

	return pLife;
}
//=============================================================================
// �̗͂̑���
//=============================================================================
void CLife::AddLife(int nValue)
{
	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();

	//m_nMaxLife = pPlayer->GetMaxLife();

	m_Life[3].nLife += nValue;		// ���C�t�𑝌�������
	float fLife;

	if (m_Life[3].nLife > 0)
	{// ���C�t��0���傫���Ƃ�
		fLife = (BAR_WIDTH_LIFE * 1.0f) / ((MAX_LIFE * 1.0f) / m_Life[3].nLife);	// �o�[�̌��̒�����100%�Ƃ��ă��C�t�𑝌�������
	}
	else
	{// ���C�t��0�ȉ��̂Ƃ�
		fLife = 0;
	}

	if (m_Life[3].nLife >= MAX_LIFE)
	{// �ő�l�𒴂�����߂�
		m_Life[3].nLife = MAX_LIFE;
		fLife = BAR_WIDTH_LIFE;
	}

	m_Life[3].fLength = fLife;	// ���݂̃��C�t�o�[�̒���

	m_nCntSubtraction = 0;		// �_���[�W�o�[�̒��������炵�n�߂邽�߂̃J�E���^��������

	//���_���̐ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���݂̃��C�t
	pVtx[(3 * 4) + 1].pos = D3DXVECTOR3(m_Life[3].pos.x + m_Life[3].fLength, m_Life[3].pos.y, 0.0f);
	pVtx[(3 * 4) + 3].pos = D3DXVECTOR3(m_Life[3].pos.x + m_Life[3].fLength, m_Life[3].pos.y + BAR_HEIGHT_LIFE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CLife::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CLife::UnLoad(void)
{
	for (int nCount = 0; nCount < NUM_TEXTURE_LIFE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CLife::MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLife;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_POLYGON_LIFE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_POLYGON_LIFE; nCntLife++)
	{
		//���_���W�̐ݒ�
		pVtx[(nCntLife * 4) + 0].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x, m_Life[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 1].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x + BAR_WIDTH_LIFE, m_Life[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 2].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x, m_Life[nCntLife].pos.y + BAR_HEIGHT_LIFE, 0.0f);
		pVtx[(nCntLife * 4) + 3].pos = D3DXVECTOR3(m_Life[nCntLife].pos.x + BAR_WIDTH_LIFE, m_Life[nCntLife].pos.y + BAR_HEIGHT_LIFE, 0.0f);

		//1.0f�ŌŒ�
		pVtx[(nCntLife * 4) + 0].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 1].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 2].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 3].rhw = 1.0f;

		//���_�J���[
		pVtx[(nCntLife * 4) + 0].col = m_Life[nCntLife].col;
		pVtx[(nCntLife * 4) + 1].col = m_Life[nCntLife].col;
		pVtx[(nCntLife * 4) + 2].col = m_Life[nCntLife].col;
		pVtx[(nCntLife * 4) + 3].col = m_Life[nCntLife].col;

		//�e�N�X�`�����W
		pVtx[(nCntLife * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCntLife * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCntLife * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCntLife * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}