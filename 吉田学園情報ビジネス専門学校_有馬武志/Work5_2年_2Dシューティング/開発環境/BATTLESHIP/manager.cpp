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
#include "input.h"
#include "game.h"
#include "tutorial.h"
#include "title.h"
#include "result.h"
#include "sound.h"
#include "main.h"
#include "pause.h"

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
CInputKeyBoard *CManager::m_pInputKeyBoard = NULL;
CInputMouse *CManager::m_pInputMouse = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CSound *CManager::m_pSound = NULL;

//ゲームの一番最初
CManager::MODE CManager::m_mode = MODE_TITLE;

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
	m_pInputKeyBoard = CInputKeyBoard::Create(hInstance,hWnd);

	//マウス生成
	m_pInputMouse = CInputMouse::Create(hInstance, hWnd);

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
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	// キーボード更新処理
	m_pInputKeyBoard->Update();

	//マウス更新処理
	m_pInputMouse->Update();

	// 更新処理
	m_pRenderer->Update();

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	{//普段はfalseにしている
		switch (m_mode)
		{
		case MODE_TITLE:	//タイトル
			if (m_pTitle != NULL)
			{
				m_pTitle->Update();
			}
			break;
		case MODE_TUTORIAL:	//チュートリアル
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Update();
			}
			break;
		case MODE_GAME:		//ゲーム
			if (m_pGame != NULL)
			{
				m_pGame->Update();
			}
			break;
		case MODE_RESULT:	//リザルト
			if (m_pResult != NULL)
			{
				m_pResult->Update();
			}
			break;
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	// 描画処理
	m_pRenderer->Draw();

	LPDIRECT3DDEVICE9 pDevice;

	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	//描画の開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{
		switch (m_mode)
		{
		case MODE_TITLE:	//タイトル
			if (m_pTitle != NULL)
			{
				m_pTitle->Draw();
			}
			break;
		case MODE_TUTORIAL:	//チュートリアル
			if (m_pTutorial != NULL)
			{
				m_pTutorial->Draw();
			}
			break;
		case MODE_GAME:		//ゲーム
			if(m_pGame != NULL)
			{
				m_pGame->Draw();
			}
			break;
		case MODE_RESULT:	//リザルト
			if (m_pResult != NULL)
			{
				m_pResult->Draw();
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
	case MODE_TITLE:	//タイトル
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;

			//タイトル曲をとめる
			m_pSound->StopSound(CSound::SOUND_LABEL_TITLEBGM000);
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);

		}
		break;
	case MODE_TUTORIAL:	//チュートリアル
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;

			//チュートリアルの曲をとめる
			m_pSound->StopSound(CSound::SOUND_LABEL_TUTORIALBGM000);
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);
		}
		break;
	case MODE_GAME:		//ゲーム
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;

			//ゲームの曲をとめる
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM000);
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);
		}
		break;
	case MODE_RESULT:	//リザルト
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;

			//ゲームの曲をとめる
			m_pSound->StopSound(CSound::SOUND_LABEL_GAMEBGM001);
			m_pSound->StopSound(CSound::SOUND_LABEL_PLAYERBGM000);
		}
		break;
	}
	
	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:	//タイトル
		if (m_pTitle == NULL)
		{//メモリを動的確保
			m_pTitle = new CTitle;

			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
				//タイトルの曲流す
				m_pSound->PlaySound(CSound::SOUND_LABEL_TITLEBGM000);
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	case MODE_TUTORIAL:	//チュートリアル
		if (m_pTutorial == NULL)
		{//メモリを動的確保
			m_pTutorial = new CTutorial;

			if (m_pTutorial != NULL)
			{
				m_pTutorial->Init();

				//チュートリアルの曲流す
				m_pSound->PlaySound(CSound::SOUND_LABEL_TUTORIALBGM000);
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	case MODE_GAME:		//ゲーム
		if (m_pGame == NULL)
		{//メモリを動的確保
			m_pGame = new CGame;

			if (m_pGame != NULL)
			{
				m_pGame->Init();
				//ゲームの曲流す
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM000);
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	case MODE_RESULT:	//リザルト
		if (m_pResult == NULL)
		{//メモリを動的確保
			m_pResult = new CResult;

			if (m_pResult != NULL)
			{
				m_pResult->Init();

				//ゲームの曲流す
				m_pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM001);
				m_pSound->PlaySound(CSound::SOUND_LABEL_PLAYERBGM000);
			}
		}
		break;
	}
}