//=============================================================================
//
// チュートリアルの処理 [tutorial.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "tutorial.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "logo.h"
#include "guide.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init()
{
	//===================================
	//		 Loadの読み込み場所
	//===================================
	//フェードのテクスチャの読み込み
	CFade::Load();
	CLogo::Load();
	CGuide::Load();

	//生成場所
	//CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), 5,0);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR2(640, 360), 15, 0);

	//CGuide::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 300.0f, SCREEN_HEIGHT / 2 + 290.0f, 0.0f), D3DXVECTOR2(300.0f, 60.0f), 13);


	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//===================================
	//	　　UnLoadの破棄する場所
	//===================================
	CLogo::UnLoad();
	CGuide::UnLoad();

	//フェード以外削除
	CScene::NotFadeReleseAll();
}
//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//フェードのポイント
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputMouse->GetMouseTrigger(0) == true)
	{//タイトルからゲームへ
	 //フェードが始まったら
		if (pFade == CFade::FADE_NONE)
		{
			//ポーズの選択の決定音
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
			CFade::Create(CManager::MODE_GAME);
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
