//=============================================================================
//
// imgui�̏��� [imgui.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "imgui_arima.h"
#include "markmeshfield.h"
#include "markobject.h"
#include "markwall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
//���[�h�ύX���̒l
int			CImgui_Arima::m_nFillMode = 0;
int			CImgui_Arima::m_nPlayerMode = 0;
int			CImgui_Arima::m_nSetMode = 0;

//�I�u�W�F�N�g�ݒ�
D3DXVECTOR3	CImgui_Arima::m_ObjectPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3	CImgui_Arima::m_ObjectRot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
int			CImgui_Arima::m_nObjectType = 0;
int			CImgui_Arima::m_nObjectClicked = 0;
bool		CImgui_Arima::m_bObjectCollition = true;
bool		CImgui_Arima::m_bSetObject = false;

//�t�B�[���h�ݒ�
D3DXVECTOR3 CImgui_Arima::m_FieldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR4 CImgui_Arima::m_FieldVtxHeight = D3DXVECTOR4(0.0f, 0.0f, 0.0f,0.0f);
int			CImgui_Arima::m_nFieldWidthDivide = 5;
int			CImgui_Arima::m_nFieldHeightDivide = 5;
int			CImgui_Arima::m_nFieldTextureType = 0;
int			CImgui_Arima::m_nFieldWidthLength = 500;
int			CImgui_Arima::m_nFieldHeightLength = 500;
int			CImgui_Arima::m_nFieldClicked = 0;
bool		CImgui_Arima::m_bSetField = false;

//�E�H�[���ݒ�
D3DXVECTOR3 CImgui_Arima::m_WallPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CImgui_Arima::m_WallRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int			CImgui_Arima::m_nWallWidthLength = 100;
int			CImgui_Arima::m_nWallHeightLength = 200;
int			CImgui_Arima::m_nWallTextureType = 0;
int			CImgui_Arima::m_nWallClicked = 0;
bool		CImgui_Arima::m_bSetWall = false;

//*****************************************************************************
// �S�̐ݒ�
//*****************************************************************************
void ImGui::ShowArimaWindow(bool * p_open)
{
	//��������
	int nFillMode = CImgui_Arima::GetFillMode();
	int nPlayerMode = CImgui_Arima::GetPlayerMode();
	int nSetMode = CImgui_Arima::GetSetMode();

	//�E�B���h�E�̕`��
	static bool show_object_window = true;
	static bool show_field_window = false;
	static bool show_wall_window = false;

	if (ImGui::Begin(u8"�S�̐ݒ�", p_open))
	{
		//�`��ݒ�
		ImGui::Text(u8"�`��ݒ�");
		ImGui::RadioButton(u8"�ʏ�", &nFillMode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"���C���[�t���[��", &nFillMode, 1);
		ImGui::Separator();		//��

		//�v���C���[�Ŋm�F���[�h
		ImGui::Text(u8"�v���C���[���[�h");
		ImGui::RadioButton(u8"OFF", &nPlayerMode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"ON", &nPlayerMode, 1);
		ImGui::Separator();		//��

		//�ݒu���ύX
		ImGui::Text(u8"�ݒu���ύX");
		ImGui::RadioButton(u8"��Q��", &nSetMode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"�n��", &nSetMode, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"��", &nSetMode, 2);
		ImGui::Separator();		//��

		//�ݒu���ύX�̃��W�I�{�^���̒��g
		switch (nSetMode)
		{
		case 0:
			CImgui_Arima::ShowObjectWindow((bool*)true);
			break;
		case 1:
			CImgui_Arima::ShowFieldWindow((bool*)true);
			break;
		case 2:
			CImgui_Arima::ShowWallWindow((bool*)true);
			break;
		}

		//����Ԃ�
		CImgui_Arima::SetFillMode(nFillMode);
		CImgui_Arima::SetPlayerMode(nPlayerMode);
		CImgui_Arima::SetSetMode(nSetMode);

		ImGui::NewLine();		//��

	}

	ImGui::End();
}

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CImgui_Arima::CImgui_Arima()
{

}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CImgui_Arima::~CImgui_Arima()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CImgui_Arima::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CImgui_Arima::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//=============================================================================
// �X�V����
//=============================================================================
void CImgui_Arima::Update(void)
{
	static bool show_demo_window = false;
	static bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::ShowArimaWindow((bool*)true);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("���݂�FPS");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::EndFrame();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CImgui_Arima::Draw(void)
{
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
//=============================================================================
// 
//=============================================================================
void CImgui_Arima::DeviceObjects(HRESULT hResult, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp)
{
	// Handle loss of D3D9 device
	if (hResult == D3DERR_DEVICELOST && pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		pDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}
//=============================================================================
//  �I�u�W�F�N�g�ڍאݒ�̃E�B���h�E
//=============================================================================
IMGUI_API void CImgui_Arima::ShowObjectWindow(bool * p_open)
{
	//�^�C�g����
	ImGui::Begin(u8"��Q���̏ڍאݒ�", p_open);

	//�ʒu�ݒ�
	ImGui::Text(u8"�ʒu�̐ݒ�");
	ImGui::DragFloat3(u8"POS", m_ObjectPos);
	ImGui::Separator();		//��

	//��]�ݒ�
	ImGui::Text(u8"��]�̐ݒ�");
	ImGui::DragFloat3(u8"ROT", m_ObjectRot);
	ImGui::Separator();		//��

	//��ސݒ�
	ImGui::Text(u8"��Q���̎�ޕύX");
	// Use AlignTextToFramePadding() to align text baseline to the baseline of framed elements (otherwise a Text+SameLine+Button sequence will have the text a little too high by default)
	ImGui::AlignTextToFramePadding();
	ImGui::Text(u8"��ނ̐ݒ�:");
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (m_nObjectType > 0) { m_nObjectType--; } }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { if (m_nObjectType < 31) { m_nObjectType++; } }
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_nObjectType);
	ImGui::Separator();		//��

	//�����蔻��
	ImGui::Text(u8"�����蔻��̐ݒ�");
	ImGui::Checkbox(u8"�����蔻��", &m_bObjectCollition);
	ImGui::Separator();		//��

	//�����蔻��
	ImGui::Text(u8"�f�[�^��ۑ�");

	if (ImGui::Button(u8"��������"))
	{
		m_nObjectClicked++;
	}
	if (m_nObjectClicked & 1)
	{
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text(u8"data\\.txt�ɕۑ����܂���");
	}
	ImGui::Separator();		//��

	//�ݒu
	ImGui::Text(u8"��Q����ݒu");
	if (ImGui::Button(u8"�ݒu"))
	{
		m_bSetObject = true;
	}
	else
	{
		m_bSetObject = false;
	}
	ImGui::Separator();		//��

	ImGui::Text(u8"��Q���̐�");
	ImGui::Text(u8"�ݒu�� = %d", CMarkObject::GetObjectNum());


	ImGui::NewLine();		//��
	ImGui::End();
}
//=============================================================================
//  �t�B�[���h�ڍאݒ�̃E�B���h�E
//=============================================================================
IMGUI_API void CImgui_Arima::ShowFieldWindow(bool * p_open)
{
	//�^�C�g����
	ImGui::Begin(u8"�n�ʂ̏ڍאݒ�", p_open);

	//�ʒu�ݒ�
	ImGui::Text(u8"�ʒu�̐ݒ�");
	ImGui::DragFloat3(u8"POS", m_FieldPos);
	ImGui::Separator();		//��

	//�������ݒ�
	ImGui::Text(u8"�n�ʂ̕������ύX");

	ImGui::InputInt(u8"���̕�����", &m_nFieldWidthDivide);
	ImGui::InputInt(u8"�c�̕�����", &m_nFieldHeightDivide);
	ImGui::Separator();		//��

	//1�ȉ��ɂȂ�Ȃ��悤��
	if (m_nFieldWidthDivide < 1)
	{
		m_nFieldWidthDivide = 1;
	}
	if (m_nFieldHeightDivide < 1)
	{
		m_nFieldHeightDivide = 1;
	}

	//��ސݒ�
	ImGui::Text(u8"�����̕ύX");
	ImGui::DragInt(u8"����", &m_nFieldWidthLength);
	ImGui::DragInt(u8"�c��", &m_nFieldHeightLength);
	ImGui::Separator();		//��

	//�e���_�̍���
	ImGui::Text(u8"�e���_�̍����ύX");
	ImGui::DragFloat4(u8"���_����", m_FieldVtxHeight);
	ImGui::Separator();		//��


	//�e�N�X�`���ύX
	ImGui::Text(u8"�n�ʂ̎�ޕύX");

	ImGui::AlignTextToFramePadding();
	ImGui::Text(u8"��ނ̐ݒ�:");
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (m_nFieldTextureType > 0) { m_nFieldTextureType--; } }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { if (m_nFieldTextureType < 10) { m_nFieldTextureType++; } }
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_nFieldTextureType);
	ImGui::Separator();		//��

	//�f�[�^�̕ۑ�
	ImGui::Text(u8"�f�[�^��ۑ�");

	if (ImGui::Button(u8"��������"))
	{
		m_nFieldClicked++;
	}
	if (m_nFieldClicked  & 1)
	{
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text(u8"data\\.txt�ɕۑ����܂���");
	}
	ImGui::Separator();		//��

	//�ݒu
	ImGui::Text(u8"�n�ʂ�ݒu");
	if (ImGui::Button(u8"�ݒu"))
	{
		m_bSetField = true;
	}
	else
	{
		m_bSetField = false;
	}
	ImGui::Separator();		//��

	ImGui::Text(u8"�n�ʂ̐�");
	ImGui::Text(u8"�ݒu�� = %d", CMarkMeshField::GetMeshFieldNum());

	//ImGui::Separator();		//��

	ImGui::End();
}
//=============================================================================
//  �E�H�[���ڍאݒ�̃E�B���h�E
//=============================================================================
IMGUI_API void CImgui_Arima::ShowWallWindow(bool * p_open)
{
	//�^�C�g����
	ImGui::Begin(u8"�ǂ̏ڍאݒ�", p_open);

	//�ʒu�ݒ�
	ImGui::Text(u8"�ʒu�̐ݒ�");
	ImGui::DragFloat3(u8"POS", m_WallPos);
	ImGui::Separator();		//��

	//��]�ݒ�
	ImGui::Text(u8"��]�̐ݒ�");
	ImGui::DragFloat3(u8"ROT", m_WallRot);
	ImGui::Separator();		//��

	//�����ݒ�
	ImGui::Text(u8"�����̕ύX");
	ImGui::DragInt(u8"����", &m_nWallWidthLength);
	ImGui::DragInt(u8"�c��", &m_nWallHeightLength);
	ImGui::Separator();		//��

	//1�ȉ��ɂȂ�Ȃ��悤��
	if (m_nWallWidthLength < 1)
	{
		m_nWallWidthLength = 1;
	}
	if (m_nWallHeightLength < 1)
	{
		m_nWallHeightLength = 1;
	}

	//�e�N�X�`���ύX
	ImGui::Text(u8"�ǂ̎�ޕύX");

	ImGui::AlignTextToFramePadding();
	ImGui::Text(u8"��ނ̐ݒ�:");
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (m_nWallTextureType > 0) { m_nWallTextureType--; } }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { if (m_nWallTextureType < 10) { m_nWallTextureType++; } }
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_nWallTextureType);
	ImGui::Separator();		//��

	//�f�[�^�̕ۑ�
	ImGui::Text(u8"�f�[�^��ۑ�");

	if (ImGui::Button(u8"��������"))
	{
		m_nWallClicked++;
	}
	if (m_nWallClicked & 1)
	{
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text(u8"data\\.txt�ɕۑ����܂���");
	}
	ImGui::Separator();		//��

	//�ݒu
	ImGui::Text(u8"�ǂ�ݒu");
	if (ImGui::Button(u8"�ݒu"))
	{
		m_bSetWall = true;
	}
	else
	{
		m_bSetWall = false;
	}
	ImGui::Separator();		//��

	ImGui::Text(u8"�ǂ̐�");
	ImGui::Text(u8"�ݒu�� = %d", CMarkWall::GetWallNum());

	ImGui::End();
}
