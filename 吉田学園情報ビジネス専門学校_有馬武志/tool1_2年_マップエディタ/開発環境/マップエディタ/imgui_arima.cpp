//=============================================================================
//
// imguiの処理 [imgui.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "imgui_arima.h"
#include "markmeshfield.h"
#include "markobject.h"
#include "markwall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数の初期化
//*****************************************************************************
//モード変更時の値
int			CImgui_Arima::m_nFillMode = 0;
int			CImgui_Arima::m_nPlayerMode = 0;
int			CImgui_Arima::m_nSetMode = 0;

//オブジェクト設定
D3DXVECTOR3	CImgui_Arima::m_ObjectPos = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DXVECTOR3	CImgui_Arima::m_ObjectRot = D3DXVECTOR3(0.0f,0.0f, 0.0f);
int			CImgui_Arima::m_nObjectType = 0;
int			CImgui_Arima::m_nObjectClicked = 0;
bool		CImgui_Arima::m_bObjectCollition = true;
bool		CImgui_Arima::m_bSetObject = false;

//フィールド設定
D3DXVECTOR3 CImgui_Arima::m_FieldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR4 CImgui_Arima::m_FieldVtxHeight = D3DXVECTOR4(0.0f, 0.0f, 0.0f,0.0f);
int			CImgui_Arima::m_nFieldWidthDivide = 5;
int			CImgui_Arima::m_nFieldHeightDivide = 5;
int			CImgui_Arima::m_nFieldTextureType = 0;
int			CImgui_Arima::m_nFieldWidthLength = 500;
int			CImgui_Arima::m_nFieldHeightLength = 500;
int			CImgui_Arima::m_nFieldClicked = 0;
bool		CImgui_Arima::m_bSetField = false;

//ウォール設定
D3DXVECTOR3 CImgui_Arima::m_WallPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 CImgui_Arima::m_WallRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int			CImgui_Arima::m_nWallWidthLength = 100;
int			CImgui_Arima::m_nWallHeightLength = 200;
int			CImgui_Arima::m_nWallTextureType = 0;
int			CImgui_Arima::m_nWallClicked = 0;
bool		CImgui_Arima::m_bSetWall = false;

//*****************************************************************************
// 全体設定
//*****************************************************************************
void ImGui::ShowArimaWindow(bool * p_open)
{
	//情報を入れる
	int nFillMode = CImgui_Arima::GetFillMode();
	int nPlayerMode = CImgui_Arima::GetPlayerMode();
	int nSetMode = CImgui_Arima::GetSetMode();

	//ウィンドウの描画
	static bool show_object_window = true;
	static bool show_field_window = false;
	static bool show_wall_window = false;

	if (ImGui::Begin(u8"全体設定", p_open))
	{
		//描画設定
		ImGui::Text(u8"描画設定");
		ImGui::RadioButton(u8"通常", &nFillMode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"ワイヤーフレーム", &nFillMode, 1);
		ImGui::Separator();		//線

		//プレイヤーで確認モード
		ImGui::Text(u8"プレイヤーモード");
		ImGui::RadioButton(u8"OFF", &nPlayerMode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"ON", &nPlayerMode, 1);
		ImGui::Separator();		//線

		//設置物変更
		ImGui::Text(u8"設置物変更");
		ImGui::RadioButton(u8"障害物", &nSetMode, 0); ImGui::SameLine();
		ImGui::RadioButton(u8"地面", &nSetMode, 1); ImGui::SameLine();
		ImGui::RadioButton(u8"壁", &nSetMode, 2);
		ImGui::Separator();		//線

		//設置物変更のラジオボタンの中身
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

		//情報を返す
		CImgui_Arima::SetFillMode(nFillMode);
		CImgui_Arima::SetPlayerMode(nPlayerMode);
		CImgui_Arima::SetSetMode(nSetMode);

		ImGui::NewLine();		//空白

	}

	ImGui::End();
}

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CImgui_Arima::CImgui_Arima()
{

}
//===============================================================================
//　デストラクタ
//===============================================================================
CImgui_Arima::~CImgui_Arima()
{

}
//=============================================================================
// 初期化処理
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
// 終了処理
//=============================================================================
void CImgui_Arima::Uninit(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//=============================================================================
// 更新処理
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

		ImGui::Begin("現在のFPS");                          // Create a window called "Hello, world!" and append into it.

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
// 描画処理
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
//  オブジェクト詳細設定のウィンドウ
//=============================================================================
IMGUI_API void CImgui_Arima::ShowObjectWindow(bool * p_open)
{
	//タイトル名
	ImGui::Begin(u8"障害物の詳細設定", p_open);

	//位置設定
	ImGui::Text(u8"位置の設定");
	ImGui::DragFloat3(u8"POS", m_ObjectPos);
	ImGui::Separator();		//線

	//回転設定
	ImGui::Text(u8"回転の設定");
	ImGui::DragFloat3(u8"ROT", m_ObjectRot);
	ImGui::Separator();		//線

	//種類設定
	ImGui::Text(u8"障害物の種類変更");
	// Use AlignTextToFramePadding() to align text baseline to the baseline of framed elements (otherwise a Text+SameLine+Button sequence will have the text a little too high by default)
	ImGui::AlignTextToFramePadding();
	ImGui::Text(u8"種類の設定:");
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (m_nObjectType > 0) { m_nObjectType--; } }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { if (m_nObjectType < 31) { m_nObjectType++; } }
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_nObjectType);
	ImGui::Separator();		//線

	//当たり判定
	ImGui::Text(u8"当たり判定の設定");
	ImGui::Checkbox(u8"当たり判定", &m_bObjectCollition);
	ImGui::Separator();		//線

	//当たり判定
	ImGui::Text(u8"データを保存");

	if (ImGui::Button(u8"書き込み"))
	{
		m_nObjectClicked++;
	}
	if (m_nObjectClicked & 1)
	{
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text(u8"data\\.txtに保存しました");
	}
	ImGui::Separator();		//線

	//設置
	ImGui::Text(u8"障害物を設置");
	if (ImGui::Button(u8"設置"))
	{
		m_bSetObject = true;
	}
	else
	{
		m_bSetObject = false;
	}
	ImGui::Separator();		//線

	ImGui::Text(u8"障害物の数");
	ImGui::Text(u8"設置数 = %d", CMarkObject::GetObjectNum());


	ImGui::NewLine();		//空白
	ImGui::End();
}
//=============================================================================
//  フィールド詳細設定のウィンドウ
//=============================================================================
IMGUI_API void CImgui_Arima::ShowFieldWindow(bool * p_open)
{
	//タイトル名
	ImGui::Begin(u8"地面の詳細設定", p_open);

	//位置設定
	ImGui::Text(u8"位置の設定");
	ImGui::DragFloat3(u8"POS", m_FieldPos);
	ImGui::Separator();		//線

	//分割数設定
	ImGui::Text(u8"地面の分割数変更");

	ImGui::InputInt(u8"横の分割数", &m_nFieldWidthDivide);
	ImGui::InputInt(u8"縦の分割数", &m_nFieldHeightDivide);
	ImGui::Separator();		//線

	//1以下にならないように
	if (m_nFieldWidthDivide < 1)
	{
		m_nFieldWidthDivide = 1;
	}
	if (m_nFieldHeightDivide < 1)
	{
		m_nFieldHeightDivide = 1;
	}

	//種類設定
	ImGui::Text(u8"長さの変更");
	ImGui::DragInt(u8"横幅", &m_nFieldWidthLength);
	ImGui::DragInt(u8"縦幅", &m_nFieldHeightLength);
	ImGui::Separator();		//線

	//各頂点の高さ
	ImGui::Text(u8"各頂点の高さ変更");
	ImGui::DragFloat4(u8"頂点高さ", m_FieldVtxHeight);
	ImGui::Separator();		//線


	//テクスチャ変更
	ImGui::Text(u8"地面の種類変更");

	ImGui::AlignTextToFramePadding();
	ImGui::Text(u8"種類の設定:");
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (m_nFieldTextureType > 0) { m_nFieldTextureType--; } }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { if (m_nFieldTextureType < 10) { m_nFieldTextureType++; } }
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_nFieldTextureType);
	ImGui::Separator();		//線

	//データの保存
	ImGui::Text(u8"データを保存");

	if (ImGui::Button(u8"書き込み"))
	{
		m_nFieldClicked++;
	}
	if (m_nFieldClicked  & 1)
	{
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text(u8"data\\.txtに保存しました");
	}
	ImGui::Separator();		//線

	//設置
	ImGui::Text(u8"地面を設置");
	if (ImGui::Button(u8"設置"))
	{
		m_bSetField = true;
	}
	else
	{
		m_bSetField = false;
	}
	ImGui::Separator();		//線

	ImGui::Text(u8"地面の数");
	ImGui::Text(u8"設置数 = %d", CMarkMeshField::GetMeshFieldNum());

	//ImGui::Separator();		//線

	ImGui::End();
}
//=============================================================================
//  ウォール詳細設定のウィンドウ
//=============================================================================
IMGUI_API void CImgui_Arima::ShowWallWindow(bool * p_open)
{
	//タイトル名
	ImGui::Begin(u8"壁の詳細設定", p_open);

	//位置設定
	ImGui::Text(u8"位置の設定");
	ImGui::DragFloat3(u8"POS", m_WallPos);
	ImGui::Separator();		//線

	//回転設定
	ImGui::Text(u8"回転の設定");
	ImGui::DragFloat3(u8"ROT", m_WallRot);
	ImGui::Separator();		//線

	//長さ設定
	ImGui::Text(u8"長さの変更");
	ImGui::DragInt(u8"横幅", &m_nWallWidthLength);
	ImGui::DragInt(u8"縦幅", &m_nWallHeightLength);
	ImGui::Separator();		//線

	//1以下にならないように
	if (m_nWallWidthLength < 1)
	{
		m_nWallWidthLength = 1;
	}
	if (m_nWallHeightLength < 1)
	{
		m_nWallHeightLength = 1;
	}

	//テクスチャ変更
	ImGui::Text(u8"壁の種類変更");

	ImGui::AlignTextToFramePadding();
	ImGui::Text(u8"種類の設定:");
	ImGui::SameLine();

	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { if (m_nWallTextureType > 0) { m_nWallTextureType--; } }
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { if (m_nWallTextureType < 10) { m_nWallTextureType++; } }
	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", m_nWallTextureType);
	ImGui::Separator();		//線

	//データの保存
	ImGui::Text(u8"データを保存");

	if (ImGui::Button(u8"書き込み"))
	{
		m_nWallClicked++;
	}
	if (m_nWallClicked & 1)
	{
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text(u8"data\\.txtに保存しました");
	}
	ImGui::Separator();		//線

	//設置
	ImGui::Text(u8"壁を設置");
	if (ImGui::Button(u8"設置"))
	{
		m_bSetWall = true;
	}
	else
	{
		m_bSetWall = false;
	}
	ImGui::Separator();		//線

	ImGui::Text(u8"壁の数");
	ImGui::Text(u8"設置数 = %d", CMarkWall::GetWallNum());

	ImGui::End();
}
