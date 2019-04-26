//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CSound *CManager::m_pSound = NULL;
CInputKeyBoard *CManager::m_pInputKeyBoard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CCamera *CManager::m_pCamera = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CGame *CManager::m_pGame = NULL;
CInputJoypad *CManager::m_pJoyPad = NULL;

//ゲームの一番最初
CManager::MODE CManager::m_mode = MODE_GAME;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CManager::CManager()
{

}
//===============================================================================
//　デストラクタ
//===============================================================================
CManager::~CManager()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindows)
{
	//NULLチェック
	if (m_pRenderer == NULL)
	{
		//動的確保
		m_pRenderer = new CRenderer;

		//NULLチェック
		if (m_pRenderer != NULL)
		{
			// 初期化処理
			if (FAILED(m_pRenderer->Init(hWnd, bWindows)))		//FALSE.TRUE
			{
				return -1;
			}
		}
		else
		{//警告文
			MessageBox(0, "警告：メモリがないです", "警告", MB_OK);
		}
	}
	else
	{//警告文
		MessageBox(0, "警告：何かが入ってます", "警告", MB_OK);
	}

	//キーボード生成
	m_pInputKeyBoard = CInputKeyBoard::Create(hInstance, hWnd);

	//マウス生成
	m_pInputMouse = CInputMouse::Create(hInstance, hWnd);

	//ジョイパッド生成
	m_pJoyPad = CInputJoypad::Create(hInstance, hWnd);

	//NULLチェック
	if (m_pSound == NULL)
	{
		//サウンドの動的確保
		m_pSound = new CSound;

		//NULLチェック
		if (m_pSound != NULL)
		{
			//サウンドの初期化処理
			m_pSound->InitSound(hWnd);
		}
	}

	//NULLチェック
	if (m_pCamera == NULL)
	{
		//カメラの動的確保
		m_pCamera = new CCamera;

		//NULLチェック
		if (m_pCamera != NULL)
		{
			//サウンドの初期化処理
			m_pCamera->Init(hInstance, hWnd);
		}
	}

	//NULLチェック
	if (m_pLight == NULL)
	{
		//ライトの動的確保
		m_pLight = new CLight;

		//NULLチェック
		if (m_pLight != NULL)
		{
			//サウンドの初期化処理
			m_pLight->Init(hInstance, hWnd);
		}
	}

	//NULLチェック
	if (m_pDebugProc == NULL)
	{
		//デバックフォント
		m_pDebugProc = new CDebugProc;

		//NULLチェック
		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}

	//モードの設定
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//全ての削除
	CScene::ReleseAll();

	//Sound　NULLチェック
	if (m_pSound != NULL)
	{
		//サウンドの終了処理
		m_pSound->UninitSound();
		//メモリの解放
		delete m_pSound;
		m_pSound = NULL;
	}

	//Renderer NULLチェック
	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();
		//メモリの解放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//pCInput NULLチェック
	if (m_pInputKeyBoard != NULL)
	{
		// 終了処理
		m_pInputKeyBoard->Uninit();
		//メモリの解放
		delete m_pInputKeyBoard;
		m_pInputKeyBoard = NULL;
	}

	//マウスInputの NULLチェック
	if (m_pInputMouse != NULL)
	{
		// 終了処理
		m_pInputMouse->Uninit();
		//メモリの解放
		delete m_pInputMouse;
		m_pInputMouse = NULL;
	}

	//マウスInputの NULLチェック
	if (m_pJoyPad != NULL)
	{
		// 終了処理
		m_pJoyPad->Uninit();
		//メモリの解放
		delete m_pJoyPad;
		m_pJoyPad = NULL;
	}


	//カメラの終了処理
	if(m_pCamera != NULL)
	{
		// 終了処理
		m_pCamera->Uninit();
		//メモリの解放
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//ライトの終了処理
	if (m_pLight != NULL)
	{
		// 終了処理
		m_pLight->Uninit();
		//メモリの解放
		delete m_pLight;
		m_pLight = NULL;
	}

	//フォントの終了処理
	if (m_pDebugProc != NULL)
	{
		// 終了処理
		m_pDebugProc->Uninit();
		//メモリの解放
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// 更新処理
	m_pRenderer->Update();

	// キーボード更新処理
	m_pInputKeyBoard->Update();

	//マウス更新処理
	m_pInputMouse->Update();

	//ジョイパッド更新処理
	m_pJoyPad->Update();

	//ライトの更新処理
	m_pLight->Update();

	//カメラの更新処理
	m_pCamera->Update();

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();


	switch (m_mode)
	{
	case MODE_GAME:		//ゲーム
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	}

	//モードの切り替わり時、その中でReleaseAllしています。
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// 描画処理
	m_pRenderer->Draw();

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	//描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		switch (m_mode)
		{
		case MODE_GAME:		//ゲーム
			if (m_pGame != NULL)
			{
				m_pGame->Draw();
			}
			break;
		}
		// 描画の終了
		pDevice->EndScene();
	}
}
//=============================================================================
// モードの設定処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case MODE_GAME:		//ゲーム
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
			CCamera::Delete();
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_NATURE);
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_GAME);
		}
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_GAME:		//ゲーム
		if (m_pGame == NULL)
		{//メモリを動的確保
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				m_pGame->Init();
				m_pSound->StopSound();
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_NATURE);
				m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
			}
		}
		break;
	}
}