//=============================================================================
//
// ゲームの流れの処理 [main.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "main.h"
#include "player.h"		//プレイヤー
#include "input.h"		//キーボード
#include "fade.h"		//フェード
#include "Result.h"		//リザルト
#include "Title.h"		//タイトル
#include "Game.h"		//ゲーム
#include "serect.h"		//セレクト
#include "sound.h"		//サウンド
#include "tutorial.h"	//チュートリアル
#include "ranking.h"	//ランキング
#include "Game.h"		//ゲーム
#include "menu.h"		//メニュー

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"WindowClass"					// ウインドウクラスの名前
#define WINDOW_NAME		"Coin"		// ウインドウの名前(キャプション名)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;		//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;				//一番最初の流れ

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;				//現在時刻
	DWORD dwExecLastTime;				//最後に処理した時刻
	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		//現在時刻を取得

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//指定したクライアント領域を確保するために必要なウインドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを生成してから行う)
	if (FAILED(Init(hInstance, hWnd, TRUE)))		//FALSE.TRUE
	{
		return -1;
	}
	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if (msg.message == WM_QUIT)
			{// "WM_QUIT"メッセージが送られてきたらループを抜ける
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			dwCurrentTime = timeGetTime();		//現在時刻を取得
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//６０分の１
				dwExecLastTime = dwCurrentTime; //処理した時刻を保存

				// 更新処理
				Update();

				// 描画処理
				Draw();
			}
		}
	}

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}
//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		// "WM_QUIT"メッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			// ウィンドウを破棄する("WM_DESTROY"メッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	// 既定の処理を返す
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//宣言
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D -> GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファの形式
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = TRUE;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート(現在の速度に合わせる)
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)

	// Direct3Dデバイスの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
									D3DDEVTYPE_HAL,							// デバイスタイプ
									hWnd,									// フォーカスするウインドウへのハンドル
									D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイス作成制御の組み合わせ
									&d3dpp,									// デバイスのプレゼンテーションパラメータ
									&g_pD3DDevice)))						// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp,
										&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp,
											&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//キーボード初期化処理
	InitKeyboard(hInstance, hWnd);
	//レンダーステートの設定

	//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//TEXTUREステート設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//サウンドの設定
	InitSound(hWnd);

	//フェードの設定
	InitFade(g_mode);

	//モードの設定
	SetMode(g_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//サウンド終了処理
	UninitSound();

	//キーボード終了処理
	UninitKeyboard();

	//タイトル
	UninitTitle();

	//セレクト
	UninitSerect();

	//チュートリアル
	UninitTutorial();

	//ゲーム
	UninitGame();

	//リザルト
	UninitResult();

	//ランキング
	UninitRanking();

	//フェード
	UninitFade();

	// Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	// Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D -> Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//キーボード更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル
		UpdateTitle();
		break;
	case MODE_SERECT:	//セレクト
		UpdateSerect();
		break;
	case MODE_TUTORIAL:	//チュートリアル
		UpdateTutorial();
		break;
	case MODE_GAME:		//ゲーム
		UpdateGame();
		break;
	case MODE_RESULT:	//リザルト
		UpdateResult();
		break;
	case MODE_RANKING:	//ランキング
		UpdateRanking();
		break;
	}

	//フェードの更新
	UpdateFade();
}
//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice ->Clear(0,
						NULL,
						(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
						D3DCOLOR_RGBA(150, 50, 100, 0),
						1.0f,
						0);
	//描画の開始
	if(SUCCEEDED(g_pD3DDevice -> BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:	//タイトル
			DrawTitle();
			break;
		case MODE_SERECT:	//セレクト
			DrawSerect();
			break;
		case MODE_TUTORIAL:	//チュートリアル
			DrawTutorial();
			break;
		case MODE_GAME:		//ゲーム
			DrawGame();
			break;
		case MODE_RESULT:	//リザルト
			DrawResult();
			break;
		case MODE_RANKING:	//ランキング
			DrawRanking();
			break;
		}
		//フェードの描画処理
		DrawFade();
		
		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
// モードの設定処理
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:	//タイトル
		UninitTitle();
		break;
	case MODE_SERECT:	//セレクト
		UninitSerect();
		//タイトル&セレクト曲をとめる
		StopSound(SOUND_LABEL_BGM005);
		break;
	case MODE_TUTORIAL:	//チュートリアル
		UninitTutorial();
		//チュートリアルの曲を止める
		StopSound(SOUND_LABEL_BGM003);
		break;
	case MODE_GAME:		//ゲーム
		UninitGame();
		StopSound(SOUND_LABEL_BGM001);
		break;
	case MODE_RESULT:	//リザルト
		UninitResult();
		//リザルト曲をとめる
		StopSound(SOUND_LABEL_BGM002);
		break;
	case MODE_RANKING:	//ランキング
		UninitRanking();
		StopSound(SOUND_LABEL_SE_RANKING);
		break;
	}

	g_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:	//タイトル
		InitTitle();
		//タイトル曲
		PlaySound(SOUND_LABEL_BGM005);
		break;
	case MODE_SERECT:	//セレクト
		InitSerect();
		break;
	case MODE_TUTORIAL:	//チュートリアル
		//チュートリアル曲
		PlaySound(SOUND_LABEL_BGM003);
		InitTutorial();
		break;
	case MODE_GAME:		//ゲーム
		InitGame();
		//ゲーム曲
		PlaySound(SOUND_LABEL_BGM001);
		break;
	case MODE_RESULT:	//リザルト
		InitResult();
		//リザルト曲
		PlaySound(SOUND_LABEL_BGM002);
		break;
	case MODE_RANKING:	//ランキング
		InitRanking();
		//ランキングの音
		PlaySound(SOUND_LABEL_SE_RANKING);
		break;
	}			//現在のモードに切り替える
}

MODE *GetMode(void)
{
	return &g_mode;
}
