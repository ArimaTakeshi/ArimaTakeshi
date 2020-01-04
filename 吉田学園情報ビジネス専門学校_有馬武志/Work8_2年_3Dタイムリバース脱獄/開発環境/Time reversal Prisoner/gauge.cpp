//=============================================================================
//
// �Q�[�W�̏��� [gauge.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "gauge.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_GAUGE_NAME_1	"data\\TEXTURE\\Life0001.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define BG_TEXTURE_UV_U			(1.0f)							//�e�N�X�`���A�j���[�V����U�͈�
#define BG_TEXTURE_UV_V			(1.0f)							//�e�N�X�`���A�j���[�V����V�͈�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGauge::m_pTexture[NUM_TEXTURE_GAUGE] = {};
LPDIRECT3DVERTEXBUFFER9 CGauge::m_pVtxBuff = NULL;
int CGauge::m_nCntSubtraction = 0;
CGauge::Gauge CGauge::m_aGauge[NUM_POLYGON_GAUGE] = {};
int CGauge::m_nMaxGauge = 0;
bool CGauge::m_bGaugeOnOff = false;
bool CGauge::m_bGaugeDownOn = false;
bool CGauge::m_bGaugeActionFade = false;
int CGauge::m_nGaugeRecastTime = 0;
bool CGauge::m_bTired = false;

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CGauge::CGauge() : CScene(5)//�D��D�ʃC�j�V�����C�Y
{
	for (int nCount = 0; nCount < NUM_POLYGON_GAUGE; nCount++)
	{
		m_aGauge[nCount] = {};					//�Q�[�W�̍\����
	}
	m_nCntSubtraction = 0;						//�o�[�����炵�n�߂�J�E���^
	//m_nGaugeRecastTime = 0;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CGauge::~CGauge()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CGauge::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �g
	m_aGauge[0].pos = m_pos;
	m_aGauge[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_aGauge[0].fGauge = MAX_GAUGE;							// �Q�[�W���ő�ɂ���
	m_aGauge[0].fLength = BAR_WIDTH_GAUGE;					// �o�[�̒�����ݒ�
	m_aGauge[0].nType = -1;									// �e�N�X�`����ON(0)OFF(-1)

	// �o�[
	for (int nCntLife = 1; nCntLife < NUM_POLYGON_GAUGE; nCntLife++)
	{
		m_aGauge[nCntLife].pos = m_pos;
		m_aGauge[nCntLife].fGauge = MAX_GAUGE;				// �Q�[�W���ő�ɂ���
		m_aGauge[nCntLife].fLength = BAR_WIDTH_GAUGE;		// �o�[�̒�����ݒ�
		m_aGauge[nCntLife].nType = 0;						// �e�N�X�`����ON(0)OFF(-1)
	}

	m_aGauge[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_aGauge[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_aGauge[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// �o�[�����炵�n�߂�J�E���^
	m_nCntSubtraction = 0;

	// ���_���̍쐬
	CGauge::MakeVertexGauge(pDevice);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CGauge::Uninit(void)
{
	m_bGaugeOnOff = false;
	m_bGaugeDownOn = false;
	m_bTired = false;

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
void CGauge::Update(void)
{
	/*	g_Life[3].fLength == ���݂̃Q�[�W					�i�őO�ʂɗ���o�[�j			*/
	/*	g_Life[2].fLength == �_���[�W���󂯂Č��������̃o�[	�i�őO�ʂ������ɗ���o�[�j*/
	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();

	CDebugProc::Print("���݂̃Q�[�W��� = %s\n", m_bGaugeOnOff ? "TRUE" : "FALSE");
	CDebugProc::Print("���݂̃Q�[�W��� = %s\n", m_bGaugeDownOn ? "TRUE" : "FALSE");
	CDebugProc::Print("m_nGaugeRecastTime = %d\n", m_nGaugeRecastTime);

	//�Q�[�W������
	if (m_bGaugeOnOff == true && CPlayer::GetCancelHeal() == false)
	{
		//�Q�[�W�����炷
		CGauge::AddGauge(-0.4f);

		//�_�ŏ���
		//�I�����Ă���J���[�̒l�����炵�Ă���
		m_fCntColor -= 0.09f;

		if (m_fCntColor < 0.5f)
		{//�M�����Ă���J���[��0.5��؂�����J���[�̒l�������Ă�
			m_fCntColor = 1.0f;
		}

		//�J���[�̍X�V����
		CGauge::ColorUpdate(m_fCntColor);

		//�Q�[�W�����炷���߂�bool��true�ɂ���
		m_bGaugeDownOn = true;

		if (m_aGauge[3].fGauge <= 0)
		{
			//�Q�[�W�������Ă����Ԃ�false�ɂ���
			m_bGaugeOnOff = false;
			
			//�J���[����������
			CGauge::ColorInit();
		}
	}

	if (m_bGaugeOnOff == false || CPlayer::GetCancelHeal() == true)
	{
		//�Q�[�W�𑝂₷
		if (m_aGauge[3].fGauge == MAX_GAUGE)
		{
			//�Q�[�W�����炷���߂�bool��false�ɂ���
			m_bGaugeDownOn = false;

			//�����̃L�����Z��
			CPlayer::SetFutureCancel(false);

			CPlayer::SetCancelHeal(false);
		}
		else if (m_nGaugeRecastTime >= 180 && m_aGauge[3].fGauge <= MAX_GAUGE)
		{
			//�Q�[�W�𑝂₷
			CGauge::AddGauge(0.25f);
		}
		else if (m_nGaugeRecastTime <= 180)
		{
			//�L�����Z���񕜎���
			CPlayer::SetCancelHeal(true);

			//�J���[����������
			CGauge::ColorInit();
		}

		//�J�E���g�͍ő�1500�܂�
		if (m_nGaugeRecastTime >= 0 && m_nGaugeRecastTime <= 1499)
		{
			//�J�E���g�𑝉�
			m_nGaugeRecastTime++;
		}
	}

	//==========================
	// �X�e�[�W���J�ڂ������̂�
	//==========================
	if (pPlayer->GetCancelStageNext() == true)
	{
		//�J���[����������
		CGauge::ColorInit();
	}

	if (pPlayer != NULL)
	{
		if (m_aGauge[2].fLength > m_aGauge[3].fLength)
		{// �Q�[�W�Ɠ����l�ɂȂ�܂Ō��̃Q�[�W�����炷
			m_nCntSubtraction++;								// �_���[�W�o�[�����炵�n�߂邽�߂̃J�E���g

			if (m_nCntSubtraction >= GAUGE_SUBTRACT_TIME)
			{// ��莞�Ԍo��
				m_aGauge[2].fLength -= BAR_WIDTH_GAUGE * 0.01f;	// �_���[�W�o�[�̒�����1�������炷

				VERTEX_2D *pVtx;

				// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//���_���W�̐ݒ�
				pVtx[(2 * 4) + 1].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength + GAUGE_DIAMOND, m_aGauge[2].pos.y, 0.0f);
				pVtx[(2 * 4) + 3].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength, m_aGauge[2].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

				// ���_�o�b�t�@���A�����b�N����
				m_pVtxBuff->Unlock();
			}
		}
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CGauge::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLife = 0; nCntLife < NUM_POLYGON_GAUGE; nCntLife++)
	{
		// �e�N�X�`���̐ݒ�
		if (m_aGauge[nCntLife].nType >= 0)
		{// �e�N�X�`���̎w��
			pDevice->SetTexture(0, m_pTexture[m_aGauge[nCntLife].nType]);
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
CGauge * CGauge::Create(D3DXVECTOR3 pos)
{
	CGauge *pGauge = NULL;

	//NULL�`�F�b�N
	if (pGauge == NULL)
	{//�������̓��I�m��

		pGauge = new CGauge;

		if (pGauge != NULL)
		{
			//�ʒu������
			pGauge->m_pos = pos;
			//�I�u�W�F�N�g�N���X�̐���
			pGauge->Init();
		}
	}

	return pGauge;
}
//=============================================================================
// �̗͂̑���
//=============================================================================
void CGauge::AddGauge(float fValue)
{
	//�v���C���[�̏��
	CPlayer *pPlayer = CGame::GetPlayer();

	//m_nMaxLife = pPlayer->GetMaxLife();

	m_aGauge[3].fGauge += fValue;		// �Q�[�W�𑝌�������
	float fLife;

	if (m_aGauge[3].fGauge > 0.0f)
	{
		// �Q�[�W��0���傫���Ƃ�
		fLife = (BAR_WIDTH_GAUGE * 1.0f) / ((MAX_GAUGE * 1.0f) / m_aGauge[3].fGauge);	// �o�[�̌��̒�����100%�Ƃ��ăQ�[�W�𑝌�������
	}
	else
	{
		// �Q�[�W��0�ȉ��̂Ƃ�
		fLife = 0;
		//��ԏ�̃Q�[�W�̒l���Ƃǂ߂�
		m_aGauge[3].fGauge = 0;
		//���L���X�g�^�C��
		m_nGaugeRecastTime = 0;

		//�Q�[�W�����A�N�V�����t�F�[�h���N��
		m_bGaugeActionFade = true;

		//���郂�[�h
		m_bTired = true;

		CPlayer::SetEnemyFutureSukill(false);

		//��������߂�
		CPlayer::SetFuture(true);
	}

	if (m_aGauge[3].fGauge >= MAX_GAUGE)
	{
		// �ő�l�𒴂�����߂�
		m_aGauge[3].fGauge = MAX_GAUGE;
		fLife = BAR_WIDTH_GAUGE;

		//�Q�[�W���g����悤�ɂ���
		m_bGaugeOnOff = false;
	}

	m_aGauge[3].fLength = fLife;	// ���݂̃Q�[�W�o�[�̒���

	m_nCntSubtraction = 0;			// �_���[�W�o�[�̒��������炵�n�߂邽�߂̃J�E���^��������

	//���_���̐ݒ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (fValue > 0.0f)
	{
		// �񕜂����Ƃ����̃o�[�����₷
		m_aGauge[2].fLength = fLife;

		//���_���W�̐ݒ�
		pVtx[(2 * 4) + 1].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength + GAUGE_DIAMOND, m_aGauge[2].pos.y, 0.0f);
		pVtx[(2 * 4) + 3].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength, m_aGauge[2].pos.y + BAR_HEIGHT_GAUGE, 0.0f);
	}

	//���݂̃Q�[�W
	pVtx[(3 * 4) + 1].pos = D3DXVECTOR3(m_aGauge[3].pos.x + m_aGauge[3].fLength + GAUGE_DIAMOND, m_aGauge[3].pos.y, 0.0f);
	pVtx[(3 * 4) + 3].pos = D3DXVECTOR3(m_aGauge[3].pos.x + m_aGauge[3].fLength, m_aGauge[3].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//===============================================================================
// ���_�J���[�ύX
//===============================================================================
void CGauge::ColorUpdate(float fCntColor)
{
	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�ݒ�
	pVtx[(3 * 4) + 0].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);
	pVtx[(3 * 4) + 1].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);
	pVtx[(3 * 4) + 2].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);
	pVtx[(3 * 4) + 3].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//===============================================================================
// ���_�J���[������
//===============================================================================
void CGauge::ColorInit(void)
{
	m_fCntColor = 1.0f;

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�ݒ�
	pVtx[(3 * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[(3 * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[(3 * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[(3 * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CGauge::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_GAUGE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CGauge::UnLoad(void)
{
	for (int nCount = 0; nCount < NUM_TEXTURE_GAUGE; nCount++)
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
void CGauge::MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLife;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_POLYGON_GAUGE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���ւ̃|�C���^
	VERTEX_2D*pVtx;

	//�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_POLYGON_GAUGE; nCntLife++)
	{
		//���_���W�̐ݒ�
		pVtx[(nCntLife * 4) + 0].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x + GAUGE_DIAMOND, m_aGauge[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 1].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x + BAR_WIDTH_GAUGE + GAUGE_DIAMOND, m_aGauge[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 2].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x, m_aGauge[nCntLife].pos.y + BAR_HEIGHT_GAUGE, 0.0f);
		pVtx[(nCntLife * 4) + 3].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x + BAR_WIDTH_GAUGE, m_aGauge[nCntLife].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

		//1.0f�ŌŒ�
		pVtx[(nCntLife * 4) + 0].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 1].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 2].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 3].rhw = 1.0f;

		//���_�J���[
		pVtx[(nCntLife * 4) + 0].col = m_aGauge[nCntLife].col;
		pVtx[(nCntLife * 4) + 1].col = m_aGauge[nCntLife].col;
		pVtx[(nCntLife * 4) + 2].col = m_aGauge[nCntLife].col;
		pVtx[(nCntLife * 4) + 3].col = m_aGauge[nCntLife].col;

		//�e�N�X�`�����W
		pVtx[(nCntLife * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCntLife * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCntLife * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCntLife * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}