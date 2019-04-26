//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "result.h"
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
#include "serect.h"
#include "explosion.h"
#include "report.h"
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
LPDIRECT3DTEXTURE9 CResult::m_pTexture = {};
CSerect *CResult::m_pSerect = NULL;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pVtxBuff = NULL;
	m_nSetCnt = 0;
	m_nCnt = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CResult::Load(void)
{
	return S_OK;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init()
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	//デバック用　終わったらこの文を消すこと！　Managerの始まりもTITLEに戻すこと！
	//GameStateNow = CGame::GAMESTATE_CLEAR;

	//背景のテクスチャの読み込み
	CBg::Load();

	//ロゴのテクスチャの読み込み
	CLogo::Load();

	//爆発のテクスチャの読み込み
	CExplosion::Load();

	//報告のテクスチャの読み込み
	CReport::Load();

	//セレクトのテクスチャの読み込み
	m_pSerect->Load();

	//エンター指示
	//CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH - 350.0f, 650.0f, 0.0f), D3DXVECTOR2(300.0f, 70.0f), 10);

	//セレクトの生成
	m_pSerect = CSerect::Create();

	if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//ゲームクリアした場合

		//ゲームクリアのBGM
		pSound->PlaySound(CSound::SOUND_LABEL_WINERBGM);

		//背景の生成
		CBg::Create(3);
		CBg::Create(7);
		CBg::Create(6);
		CBg::Create(9);
		CBg::Create(8);

		//戦艦
		CLogo::Create(D3DXVECTOR3(340.0f, 550.0f, 0.0f), D3DXVECTOR2(240.0f, 110.0f), 25);
		CLogo::Create(D3DXVECTOR3(1050.0f, 550.0f, 0.0f), D3DXVECTOR2(200.0f, 110.0f), 11);

		//船長
		CLogo::Create(D3DXVECTOR3(1400.0f, 650.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 28);
	}
	else if (GameStateNow == CGame::GAMESTATE_OVER)
	{//ゲームオーバーした場合

		//ゲームオーバーのBGM
		pSound->PlaySound(CSound::SOUND_LABEL_GAMEOVER);

		//背景の生成
		CBg::Create(3);
		CBg::Create(7);
		CBg::Create(6);
		CBg::Create(9);
		CBg::Create(8);

		//戦艦
		CLogo::Create(D3DXVECTOR3(370.0f, 550.0f, 0.0f), D3DXVECTOR2(200.0f, 110.0f), 11);

		//船長
		CLogo::Create(D3DXVECTOR3(1400.0f, 650.0f, 0.0f), D3DXVECTOR2(140.0f, 60.0f), 29);

		//協調音
		pSound->PlaySound(CSound::SOUND_LABEL_LOSE);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//ポーズ削除
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//ゲームオーバーのBGM
	pSound->StopSound(CSound::SOUND_LABEL_GAMEOVER);
	pSound->StopSound(CSound::SOUND_LABEL_WINERBGM);

	//背景のテクスチャの破棄
	CBg::UnLoad();

	//ロゴのテクスチャの破棄
	CLogo::UnLoad();

	//爆発のテクスチャの破棄
	CExplosion::UnLoad();

	//報告のテクスチャの破棄
	CReport::UnLoad();

	//セレクトのテクスチャの破棄
	m_pSerect->UnLoad();

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
void CResult::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	//デバック用　終わったらこの文を消すこと！　Managerの始まりもTITLEに戻すこと！
	//GameStateNow = CGame::GAMESTATE_CLEAR;

	//文字を出す
	if (m_nSetCnt == 560)
	{
		CReport::Create(D3DXVECTOR3(140.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 0);

		//協調音
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}
	else if (m_nSetCnt == 610)
	{
		CReport::Create(D3DXVECTOR3(310.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 1);

		//協調音
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}
	else if (m_nSetCnt == 660)
	{
		CReport::Create(D3DXVECTOR3(480.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 2);

		//協調音
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}
	else if (m_nSetCnt == 710)
	{
		CReport::Create(D3DXVECTOR3(650.0f, 200.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 3);

		//協調音
		pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
	}

	m_nSetCnt++;

	if (GameStateNow == CGame::GAMESTATE_OVER)
	{//ゲームオーバーした場合
		
		//戦闘機
		if (m_nCnt == 130)
		{//1機目
			CLogo::Create(D3DXVECTOR3(-50.0f, 100.0f * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 22);

			//戦闘機通過音
			pSound->PlaySound(CSound::SOUND_LABEL_HIKOUKI);
		}
		else if (m_nCnt == 250)
		{//2機目
			CLogo::Create(D3DXVECTOR3(-50.0f, 150.0f * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 22);

			//戦闘機通過音
			pSound->PlaySound(CSound::SOUND_LABEL_HIKOUKI);
		}
		else if (m_nCnt == 350)
		{//3機目
			CLogo::Create(D3DXVECTOR3(-50.0f, 200.0f * 1.0f, 0.0f), D3DXVECTOR2(25.0f, 10.0f), 22);

			//戦闘機通過音
			pSound->PlaySound(CSound::SOUND_LABEL_HIKOUKI);
		}

		//爆弾
		if (m_nCnt == 270)
		{//1個目右に外す y軸の+10.0fは飛行機と被らないように飛行機の大きさを足したもの 下の3つすべてそう
			CLogo::Create(D3DXVECTOR3(520.0f, 100.0f + 10.0f, 0.0f), D3DXVECTOR2(3.0f, 15.0f), 23);

			//爆弾を落とす音
			pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
		}
		else if (m_nCnt == 310)
		{//2個目左に外す
			CLogo::Create(D3DXVECTOR3(200.0f, 150.0f + 10.0f, 0.0f), D3DXVECTOR2(3.0f, 15.0f), 23);

			//爆弾を落とす
			pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
		}
		else if (m_nCnt == 450)
		{//3個目戦艦にあてる
			CLogo::Create(D3DXVECTOR3(370.0f, 200.0f + 10.0f, 0.0f), D3DXVECTOR2(3.0f, 15.0f), 24);

			//爆弾を落とす
			pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
		}
	}
	else if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//ゲームクリアした場合
	 //爆弾
		if (m_nCnt == 200)
		{//1個目
			CLogo::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(10.0f, 1.5f), 26);

			//爆発の生成
			CExplosion::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(40, 40), 0);

			//大砲発射音
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);
		}
		else if (m_nCnt == 240)
		{//2個目
			CLogo::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(10.0f, 1.5f), 26);

			//爆発の生成
			CExplosion::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(40, 40), 0);

			//大砲発射音
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);
		}
		else if (m_nCnt == 380)
		{//3個目戦艦にあてる
			CLogo::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(10.0f, 1.5f), 27);

			//爆発の生成
			CExplosion::Create(D3DXVECTOR3(1030.0f, 555.0f, 0.0f), D3DXVECTOR2(40, 40), 0);

			//大砲発射音
			pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);
		}
	}

	if (m_nCnt == 1040)
	{//17秒後に何もしてない場合戻る
		//タイトル曲流す
		pSound->PlaySound(CSound::SOUND_LABEL_ENTERSE);
		CFade::Create(CManager::MODE_TITLE);
	}

	m_nCnt++;
}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
	
}
//=============================================================================
// テクスチャの開放処理
//=============================================================================
void CResult::UnLoad(void)
{

}
