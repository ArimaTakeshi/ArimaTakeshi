//=============================================================================
//
// �����_���[���� [renderer.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "imgui_arima.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//=============================================================================
// ���C���֐�
//=============================================================================

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CRenderer::CRenderer()
{
	//�l���N���A
	m_pD3D = NULL;
	m_pD3DDevice = NULL;

	m_bDebguONOFF = true;

#ifdef _DEBUG
	//m_pFont = NULL;
#endif

}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CRenderer::~CRenderer()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));								// ���[�N���[���N���A
	m_d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	m_d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	m_d3dpp.Windowed = true;											// �E�B���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	//Imugi��Init
	m_pImgui_Arima->Init(hWnd,m_pD3DDevice);

	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
																			
	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

																			//�n�[�h�E�F�A�̔\�͂�\���\����
	//D3DCAPS9 caps;

	////�t�H�O�p�����[�^
	//const FLOAT fogStart = 300;
	//const FLOAT fogEnd = 2000;

	//ZeroMemory(&caps, sizeof(D3DCAPS9));

	//m_pD3DDevice->GetDeviceCaps(&caps);
	//m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);								//�t�H�O���g�p����
	//m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, D3DCOLOR_ARGB(130, 180, 255, 180));	//�t�H�O�̐F��ݒ肷��
	//m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);						//���_�t�H�O���g�p���Ȃ�
	//m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);					//�t�H�O�̓K�p���@
	//m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&fogStart));				//�t�H�O�̊J�n�ʒu
	//m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&fogEnd));					//�t�H�O�̏I���ʒu


	m_bOnOff = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	//if (m_pFont != NULL)
	//{
	//	m_pFont->Release();
	//	m_pFont = NULL;
	//}
#endif
	//Imgui�̏I������
	m_pImgui_Arima->Uninit();

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	//�S�Ă̍X�V����
	CScene::UpdateAll();

	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	if (pCInputKeyBoard != NULL)
	{
		if (m_pImgui_Arima->GetFillMode() == 1)
		{//���̏�		
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, 2);						// ���C���[�t���[���w��
		}
		if (m_pImgui_Arima->GetFillMode() == 0)
		{//���̏�		
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, 0);						// ���C���[�t���[���w��
		}
	}

	//Imgui�̍X�V����
	m_pImgui_Arima->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	//���͏��
	CCamera *pCamera = CManager::GetCamera();
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	if (pCamera != NULL)
	{
		//�J�����̐���
		pCamera->SetCamera();
	}

	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(100, 100, 255, 255),
		1.0f,
		0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
	
		//�S�Ă̕`��
		CScene::DrawAll();

#ifdef _DEBUG
		int nFps = GetFps();

		if (pCInputKeyBoard->GetKeyboardPress(DIK_F3) == true)
		{//���̏�		
			m_bDebguONOFF = true;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_F4) == true)
		{//���̏�		
			m_bDebguONOFF = false;
		}

		if (m_bDebguONOFF == true)
		{
			CDebugProc::Draw();
		}
#endif
		//imgui�̕`�揈��
		m_pImgui_Arima->Draw();

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}
	else
	{
		MessageBox(0, "Draw�̏�����NULL", "�x��", MB_OK);
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	HRESULT result = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	//imgui
	m_pImgui_Arima->DeviceObjects(result,m_pD3DDevice, m_d3dpp);
}