//=============================================================================
//
// 数字の処理 [title.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "title.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "bullet.h"
#include "bg.h"
#include "score.h"
#include "title.h"
#include "fade.h"
#include "logo.h"
#include "sound.h"
#include <string>
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME			"data\\TEXTURE\\.png"			//読み込むテクスチャファイル
#define MAX_SIZE_X				(500)							//テクスチャ縦サイズ
#define MAX_SIZE_Y				(600)							//テクスチャ横サイズ
#define BG_TEXTURE_UV_U			(1.0f)							//テクスチャアニメーションU範囲
#define BG_TEXTURE_UV_V			(1.0f)							//テクスチャアニメーションV範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = {};

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_nCnt = 0;
	m_nCount = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}
//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CTitle::Load(void)
{
	return S_OK;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init()
{
	//背景テクスチャの生成
	CBg::Load();

	//ロゴテクスチャの生成
	CLogo::Load();

	////背景の生成
	CBg::Create(3);
	CBg::Create(7);
	CBg::Create(6);
	CBg::Create(9);
	CBg::Create(8);

	//ロゴの生成
	for (int nCount = 0; nCount < 10; nCount++)
	{
		CLogo::Create(D3DXVECTOR3(140.0f + nCount * 110.0f, -150.0f, 0.0f), D3DXVECTOR2(50.0f, 100.0f), nCount);
	}

	//戦艦
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH - 170.0f, 550.0f, 0.0f), D3DXVECTOR2(200.0f, 110.0f), 11);

	//エンター指示
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600.0f, 0.0f), D3DXVECTOR2(300.0f, 70.0f), 10);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//背景テクスチャの破棄
	CBg::UnLoad();

	//ロゴテクスチャの破棄
	CLogo::UnLoad();

	//順位を確認
	for (int nCnPri = 0; nCnPri < 7; nCnPri++)
	{
		//オブジェクトの総数を確認
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene *pScene = CScene::GetScene(nCnPri, nCntScene);

			if (pScene != NULL)
			{
				pScene->Uninit();
			}
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//フェードのポイント
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardAny(1) == true || pCInputMouse->GetMouseTrigger(0) == true)
	{//タイトルからゲームへ
		if (m_nCount >= 1)
		{
			//フェードが始まったら
			if (pFade == CFade::FADE_NONE)
			{
				//タイトル曲流す
				pSound->PlaySound(CSound::SOUND_LABEL_ENTERSE);
			}
			CFade::Create(CManager::MODE_TUTORIAL);
		}
		m_nCount++;
	}

	//戦闘機
	if (m_nCnt == 260)
	{
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH + 50.0f, 100.0f + rand()%200 * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 12);

		if (rand() % 2 == 0)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH + rand()%300 * 1.0f, 100.0f + rand() % 200 * 1.0f, 0.0f), D3DXVECTOR2(13.0f, 5.0f), 12);
		}
	}
	else if(m_nCnt >= 261)
	{
		m_nCnt = 0;
	}

	m_nCnt++;
}
//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{
	
}
//=============================================================================
// テクスチャの開放処理
//=============================================================================
void CTitle::UnLoad(void)
{

}
