//=============================================================================
//
// ゲーム（キャラ選択）の処理 [game.h]
// Author : Eisuke Sakagawa
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall突破
#include <string.h>				//ストリング使用のため
#include "gameCharSelect.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "fade.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CGameCharSelect::m_pTexture[CGameCharSelect::TEXTURE_MAX] = { NULL };

//=============================================================================
// コンストラクタ
//=============================================================================
CGameCharSelect::CGameCharSelect()
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーカウント
		m_pPlayerNum[nCntPlayer] = NULL;
		m_pPlayerBG[nCntPlayer] = NULL;
		m_pSelect[nCntPlayer] = NULL;
		m_pEnter[nCntPlayer] = NULL;
		m_pButton[nCntPlayer] = NULL;		// ボタン

		m_bEntry[nCntPlayer] = false;
		m_bEnter[nCntPlayer] = false;
	}
	m_pAction = NULL;					// アクション

	m_pYor = NULL;						// あなた
	m_pReturnFrame = NULL;				// 戻るフレーム
	m_pReturnButton = NULL;				// 戻る
	m_pReturnBG = NULL;					// 戻る背景
	m_pReturnTree = NULL;				// 戻る木
	m_pReturnHome = NULL;				// 戻る小屋
	m_pReturnChar = NULL;				// 戻るキャラ
	m_pReturnGrass = NULL;				// 戻る草

	m_nReturnCounter = 0;				// 戻るカウント
	m_nEntryCounter = 0;				// エントリーカウント

	m_pReady = NULL;					// 準備
	m_bReady = false;					// 準備

	m_pTutorial = NULL;					// チュートリアル
	for (int nCount = 0; nCount < MAX_HINT; nCount++)
		m_pHint[nCount] = NULL;						// ヒント
	m_pGo = NULL;						// GO

	m_nTutorialNum = 0;					// チュートリアル番号
	m_nTutorialCounter = 0;				// チュートリアルカウント

	for (int nCntChar = 0; nCntChar < MAX_CHARCTER; nCntChar++)
		m_pCharacter[nCntChar] = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGameCharSelect::~CGameCharSelect() {}

//=============================================================================
// ロード
//=============================================================================
HRESULT CGameCharSelect::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{// テクスチャカウント
		char cName[128] = {};

		switch (nCntTex)
		{
		case TEXTURE_CHAR:
			strcpy(cName, "data/TEXTURE/game/charselect/char.png");
			break;
		case TEXTURE_FRAME:
			strcpy(cName, "data/TEXTURE/game/charselect/select_frame.png");
			break;
		case TEXTURE_NUMBER:
			strcpy(cName, "data/TEXTURE/game/charselect/icon.png");
			break;
		case TEXTURE_ENTER:
			strcpy(cName, "data/TEXTURE/game/charselect/characterselect.png");
			break;
		case TEXTURE_BUTTON:
			strcpy(cName, "data/TEXTURE/Title/UI/modeselect_15.png");
			break;
		case TEXTURE_ACTION:
			strcpy(cName, "data/TEXTURE/game/charselect/charaselect00.png");
			break;
		case TEXTURE_YOU:
			strcpy(cName, "data/TEXTURE/game/charselect/modeselect_17.png");
			break;
		case TEXTURE_READY:
			strcpy(cName, "data/TEXTURE/Title/UI/areyouready.png");
			break;
		case TEXTURE_TUTORIAL:
			strcpy(cName, "data/TEXTURE/tutorial/Tutorial.jpg");
			break;
		case TEXTURE_HINT:
			strcpy(cName, "data/TEXTURE/tutorial/tutorial_hint.png");
			break;
		case TEXTURE_RETURN_BG:
			strcpy(cName, "data/TEXTURE/game/charselect/home/ground.png");
			break;
		case TEXTURE_RETURN_TREE:
			strcpy(cName, "data/TEXTURE/game/charselect/home/tree.png");
			break;
		case TEXTURE_RETURN_HOME:
			strcpy(cName, "data/TEXTURE/game/charselect/home/Chicken_House.png");
			break;
		case TEXTURE_RETURN_CHAR:
			strcpy(cName, "data/TEXTURE/game/charselect/home/Chicken_Yoko.png");
			break;
		case TEXTURE_RETURN_GRASS:
			strcpy(cName, "data/TEXTURE/game/charselect/home/grass.png");
			break;
		}

		// テクスチャの生成
		if (m_pTexture[nCntTex] == NULL)
			D3DXCreateTextureFromFile(pDevice, cName, &m_pTexture[nCntTex]);
	}

	return S_OK;
}

//=============================================================================
// アンロード
//=============================================================================
void CGameCharSelect::Unload(void)
{
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{// テクスチャカウント
	 //テクスチャーの破棄
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// クリエイト
//=============================================================================
CGameCharSelect *CGameCharSelect::Create(void)
{
	CGameCharSelect *pGameCharSelect = NULL;

	// メモリ確保
	if (pGameCharSelect == NULL)
		pGameCharSelect = new CGameCharSelect;

	if (pGameCharSelect != NULL)
	{// NULL以外
		pGameCharSelect->Init();	// 初期化処理
	}

	return pGameCharSelect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameCharSelect::Init()
{
	// 取得
	bool bOnine = CTitle::GetOnline();

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーカウント	
	 // プレイヤー番号
		if (m_pPlayerNum[nCntPlayer] == NULL)
		{// NULL
			m_pPlayerNum[nCntPlayer] = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pPlayerNum[nCntPlayer]->Init();
			m_pPlayerNum[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(nCntPlayer % 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_WIDTH - (SCREEN_HEIGHT * 0.25f)) - (SCREEN_HEIGHT * 0.18f),
					(nCntPlayer / 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.25f)) - (SCREEN_HEIGHT * 0.2f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.1f, SCREEN_HEIGHT * 0.05f));
			m_pPlayerNum[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pPlayerNum[nCntPlayer]->BindTexture(m_pTexture[TEXTURE_NUMBER]);
			m_pPlayerNum[nCntPlayer]->SetTexture(nCntPlayer, 5, 2, 1);
		}
		// プレイヤー背景
		if (m_pPlayerBG[nCntPlayer] == NULL)
		{// NULL
			m_pPlayerBG[nCntPlayer] = new CScene2D(5, CScene::OBJTYPE_2DPOLYGON);
			m_pPlayerBG[nCntPlayer]->Init();
			m_pPlayerBG[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(nCntPlayer % 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_WIDTH - (SCREEN_HEIGHT * 0.25f)),
					(nCntPlayer / 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.25f)),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.25f, SCREEN_HEIGHT * 0.25f));
			//m_pPlayerBG[nCntPlayer]->SetColor(&D3DXCOLOR((nCntPlayer % 2 == 0 ? 1.0f : 0.0f), (nCntPlayer / 2 % 2 == 1 ? 1.0f : 0.0f), (nCntPlayer % 4 == 1 ? 1.0f : 0.0f), 0.6f));
			m_pPlayerBG[nCntPlayer]->BindTexture(m_pTexture[TEXTURE_FRAME]);
		}
		// 選択
		if (m_pSelect[nCntPlayer] == NULL)
		{// NULL
			m_pSelect[nCntPlayer] = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pSelect[nCntPlayer]->Init();
			m_pSelect[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) +
					((SCREEN_WIDTH * (nCntPlayer / 4 == 0 ? 0.055f : 0.04f) +
					(nCntPlayer % 4 == 0 || nCntPlayer % 4 == 3 ? (SCREEN_WIDTH * (nCntPlayer / 4 == 0 ? 0.055f : 0.04f)) * 2.0f : 0.0f)) *
						(nCntPlayer / 2 % 2 == 0 ? -1.0f : 1.0f)),
						(SCREEN_HEIGHT * 0.6f) + ((SCREEN_WIDTH * 0.05f) * (nCntPlayer / 4 == 0 ? 0.0f : -1.0f)),
					0.0f),
				D3DXVECTOR2(SCREEN_WIDTH * 0.04f, SCREEN_WIDTH * 0.04f));

			m_pSelect[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pSelect[nCntPlayer]->BindTexture(m_pTexture[TEXTURE_NUMBER]);
			m_pSelect[nCntPlayer]->SetTexture(nCntPlayer, 5, 1, 1);
		}
		// 決定
		if (m_pEnter[nCntPlayer] == NULL)
		{// NULL
			m_pEnter[nCntPlayer] = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pEnter[nCntPlayer]->Init();
			m_pEnter[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(nCntPlayer % 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_WIDTH - (SCREEN_HEIGHT * 0.25f)),
					(nCntPlayer / 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.25f)) + (SCREEN_HEIGHT * 0.18f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.18f, SCREEN_HEIGHT * 0.05f));
			m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pEnter[nCntPlayer]->BindTexture(m_pTexture[TEXTURE_ENTER]);
			m_pEnter[nCntPlayer]->SetTexture(1, 1, 2, 2);
		}
		// ボタン
		if (m_pButton[nCntPlayer] == NULL)
		{// NULL
			m_pButton[nCntPlayer] = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pButton[nCntPlayer]->Init();
			m_pButton[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(nCntPlayer % 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_WIDTH - (SCREEN_HEIGHT * 0.25f)),
					(nCntPlayer / 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.25f)),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.12f, SCREEN_HEIGHT * 0.04f));
			m_pButton[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pButton[nCntPlayer]->BindTexture(m_pTexture[TEXTURE_BUTTON]);
			m_pButton[nCntPlayer]->SetUV
			(
				D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.6422f, 0.5f),
				D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(0.6422f, 1.0f)
			);
		}
	}

	// キャラクター
	/*for (int nCntChar = 0; nCntChar < MAX_CHARCTER; nCntChar++)
	{// キャラカウント
	if (m_pCharacter[nCntChar] == NULL)
	{// NULL
	m_pCharacter[nCntChar] = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
	m_pCharacter[nCntChar]->Init();
	m_pCharacter[nCntChar]->SetPosSize(
	D3DXVECTOR3(
	(SCREEN_WIDTH * 0.5f) + ((SCREEN_WIDTH * 0.053f + (nCntChar % 4 == 0 || nCntChar % 4 == 3 ? (SCREEN_WIDTH * 0.053f) * 2.0f : 0.0f)) * (nCntChar / 2 % 2 == 0 ? -1.0f : 1.0f)),
	(SCREEN_HEIGHT * 0.8f) + ((SCREEN_WIDTH * 0.053f) * (nCntChar / 4 == 0 ? -1.0f : 1.0f)),
	0.0f),
	D3DXVECTOR2(SCREEN_WIDTH * 0.05f, SCREEN_WIDTH * 0.05f));
	m_pCharacter[nCntChar]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pCharacter[nCntChar]->BindTexture(m_pTexture[TEXTURE_CHAR]);
	}
	}*/

	if (m_pAction == NULL)
	{// NULL
		m_pAction = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
		m_pAction->Init();
		m_pAction->SetPosSize(
			D3DXVECTOR3(
			(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.88f),
				0.0f),
			D3DXVECTOR2(SCREEN_HEIGHT * 0.3f, SCREEN_HEIGHT * 0.04f));
		m_pAction->BindTexture(m_pTexture[TEXTURE_ACTION]);
	}

	if (bOnine == true)
	{// オンライン
		int nClient = CServer::GetnMaxClient();		// クライアント数
		int nID = CClient::GetnID();			// クライアントID

												// あなた
		if (m_pYor == NULL)
		{// NULL
			m_pYor = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pYor->Init();
			m_pYor->SetPosSize(
				D3DXVECTOR3(
				(nID % 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_WIDTH - (SCREEN_HEIGHT * 0.25f)) + (SCREEN_HEIGHT * 0.07f),
					(nID / 2 == 0 ? 0.0f + (SCREEN_HEIGHT * 0.25f) : SCREEN_HEIGHT - (SCREEN_HEIGHT * 0.25f)) - (SCREEN_HEIGHT * 0.18f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.12f, SCREEN_HEIGHT * 0.04f));
			m_pYor->BindTexture(m_pTexture[TEXTURE_YOU]);
		}

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{// プレイヤーカウント				
		 // プレイヤー番号
			if (m_pPlayerNum[nCntPlayer] != NULL)
			{// NULL以外
				if (nCntPlayer < nClient)
					m_pPlayerNum[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			// 決定
			if (m_pEnter[nCntPlayer] != NULL)
			{// NULL以外
				m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_pEnter[nCntPlayer]->SetTexture(0, 1, 2, 2);
			}

			// 参加
			if (nCntPlayer < nClient)
				m_bEntry[nCntPlayer] = true;
		}

		// プレイヤー最大数設定
		CGame::SetMaxPlayer(nClient);
	}
	else
	{
		// もどるフレーム
		if (m_pReturnFrame == NULL)
		{// NULL
			m_pReturnFrame = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnFrame->Init();
			m_pReturnFrame->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f),
					(SCREEN_HEIGHT * 0.04f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.34f, SCREEN_HEIGHT * 0.045f));
			m_pReturnFrame->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		}

		// もどる
		if (m_pReturnButton == NULL)
		{// NULL
			m_pReturnButton = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnButton->Init();
			m_pReturnButton->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) + -(SCREEN_WIDTH * 0.12f),
					(SCREEN_HEIGHT * 0.05f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.15f, SCREEN_HEIGHT * 0.032f));
			m_pReturnButton->BindTexture(m_pTexture[TEXTURE_BUTTON]);
			m_pReturnButton->SetTexture(0, 1, 2, 1);
		}

		// もどる背景
		if (m_pReturnBG == NULL)
		{// NULL
			m_pReturnBG = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnBG->Init();
			m_pReturnBG->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.07f),
					(SCREEN_HEIGHT * 0.08f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.2f, SCREEN_HEIGHT * 0.003f));
			//m_pReturnBG->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pReturnBG->BindTexture(m_pTexture[TEXTURE_RETURN_BG]);
		}

		// もどる木
		if (m_pReturnTree == NULL)
		{// NULL
			m_pReturnTree = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnTree->Init();
			m_pReturnTree->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.07f) + (SCREEN_WIDTH * 0.01f),
					(SCREEN_HEIGHT * 0.041f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.04f, SCREEN_HEIGHT * 0.045f));
			//m_pReturnTree->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pReturnTree->BindTexture(m_pTexture[TEXTURE_RETURN_TREE]);
		}

		// もどる小屋
		if (m_pReturnHome == NULL)
		{// NULL
			m_pReturnHome = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnHome->Init();
			m_pReturnHome->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.07f) + (SCREEN_WIDTH * 0.08f),
					(SCREEN_HEIGHT * 0.042f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.06f, SCREEN_HEIGHT * 0.045f));
			//m_pReturnHome->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pReturnHome->BindTexture(m_pTexture[TEXTURE_RETURN_HOME]);
		}

		// もどるキャラ
		if (m_pReturnChar == NULL)
		{// NULL
			m_pReturnChar = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnChar->Init();
			m_pReturnChar->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.07f) + -(SCREEN_WIDTH * 0.09f),
					(SCREEN_HEIGHT * 0.052f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.03f, SCREEN_HEIGHT * 0.04f));
			//m_pReturnChar->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pReturnChar->BindTexture(m_pTexture[TEXTURE_RETURN_CHAR]);
		}

		// もどる草
		if (m_pReturnGrass == NULL)
		{// NULL
			m_pReturnGrass = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pReturnGrass->Init();
			m_pReturnGrass->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.07f) + -(SCREEN_WIDTH * 0.03f),
					(SCREEN_HEIGHT * 0.0665f),
					0.0f),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.08f, SCREEN_HEIGHT * 0.02f));
			//m_pReturnGrass->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pReturnGrass->BindTexture(m_pTexture[TEXTURE_RETURN_GRASS]);
			m_pReturnGrass->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(2.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(2.0f, 1.0f));
		}
	}

	// 準備
	if (m_pReady == NULL)
	{// NULL
		m_pReady = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
		m_pReady->Init();
		m_pReady->SetPosSize(
			D3DXVECTOR3(
			(SCREEN_WIDTH * 0.5f),
				(SCREEN_HEIGHT * 0.5f),
				0.0f),
			D3DXVECTOR2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.12f));
		m_pReady->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pReady->BindTexture(m_pTexture[TEXTURE_READY]);
	}

	// チュートリアル
	if (m_pTutorial == NULL)
	{// NULL
		m_pTutorial = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
		m_pTutorial->Init();
		m_pTutorial->SetPosSize(
			D3DXVECTOR3(
			(SCREEN_WIDTH * 1.5f),
				(SCREEN_HEIGHT * 0.5f),
				0.0f),
			D3DXVECTOR2(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.5f));
		m_pTutorial->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pTutorial->BindTexture(m_pTexture[TEXTURE_TUTORIAL]);
	}

	// ヒント
	for (int nCount = 0; nCount < MAX_HINT; nCount++)
	{
		if (m_pHint[nCount] == NULL)
		{// NULL
			m_pHint[nCount] = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
			m_pHint[nCount]->Init();
			m_pHint[nCount]->SetPosSize(
				D3DXVECTOR3
				(
				((nCount ^ 1) == 0 ? (SCREEN_HEIGHT * 0.13f) : SCREEN_WIDTH - (SCREEN_HEIGHT * 0.13f)),
					(SCREEN_HEIGHT * 0.5f),
					0.0f
				),
				D3DXVECTOR2(SCREEN_HEIGHT * 0.13f, (SCREEN_HEIGHT * 0.06f)));
			m_pHint[nCount]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_pHint[nCount]->BindTexture(m_pTexture[TEXTURE_HINT]);
			m_pHint[nCount]->SetTexture(0, 3, 1, 1);
		}
	}

	// Go
	if (m_pGo == NULL)
	{// NULL
		m_pGo = new CScene2D(6, CScene::OBJTYPE_2DPOLYGON);
		m_pGo->Init();
		m_pGo->SetPosSize(
			D3DXVECTOR3
			(
			(SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.41f),
				(SCREEN_HEIGHT * 0.12f) + (SCREEN_HEIGHT * 0.85f),
				0.0f
			),
			D3DXVECTOR2(SCREEN_HEIGHT * 0.15f, SCREEN_HEIGHT * 0.04f));
		m_pGo->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pGo->BindTexture(m_pTexture[TEXTURE_BUTTON]);
		m_pGo->SetUV
		(
			D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.6422f, 0.5f),
			D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(0.6422f, 1.0f)
		);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CGameCharSelect::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーカウント	
		if (m_pPlayerNum[nCntPlayer] != NULL)
		{// NULL以外
			m_pPlayerNum[nCntPlayer]->Uninit();	// 終了処理
			m_pPlayerNum[nCntPlayer] = NULL;	// NULLへ
		}
		if (m_pPlayerBG[nCntPlayer] != NULL)
		{// NULL以外
			m_pPlayerBG[nCntPlayer]->Uninit();	// 終了処理
			m_pPlayerBG[nCntPlayer] = NULL;		// NULLへ
		}
		if (m_pSelect[nCntPlayer] != NULL)
		{// NULL以外
			m_pSelect[nCntPlayer]->Uninit();	// 終了処理
			m_pSelect[nCntPlayer] = NULL;		// NULLへ
		}
		if (m_pEnter[nCntPlayer] != NULL)
		{// NULL以外
			m_pEnter[nCntPlayer]->Uninit();		// 終了処理
			m_pEnter[nCntPlayer] = NULL;		// NULLへ
		}
		if (m_pButton[nCntPlayer] != NULL)
		{// NULL以外
			m_pButton[nCntPlayer]->Uninit();	// 終了処理
			m_pButton[nCntPlayer] = NULL;		// NULLへ
		}
	}

	// あなた
	if (m_pAction != NULL)
	{// NULL以外
		m_pAction->Uninit();		// 終了処理
		m_pAction = NULL;			// NULLへ
	}

	// あなた
	if (m_pYor != NULL)
	{// NULL以外
		m_pYor->Uninit();			// 終了処理
		m_pYor = NULL;				// NULLへ
	}

	// もどるフレーム
	if (m_pReturnFrame != NULL)
	{// NULL以外
		m_pReturnFrame->Uninit();	// 終了処理
		m_pReturnFrame = NULL;		// NULLへ
	}
	// もどる
	if (m_pReturnButton != NULL)
	{// NULL以外
		m_pReturnButton->Uninit();	// 終了処理
		m_pReturnButton = NULL;		// NULLへ
	}
	// もどる背景
	if (m_pReturnBG != NULL)
	{// NULL以外
		m_pReturnBG->Uninit();	// 終了処理
		m_pReturnBG = NULL;		// NULLへ
	}
	// もどる木
	if (m_pReturnTree != NULL)
	{// NULL以外
		m_pReturnTree->Uninit();	// 終了処理
		m_pReturnTree = NULL;		// NULLへ
	}
	// もどる小屋
	if (m_pReturnHome != NULL)
	{// NULL以外
		m_pReturnHome->Uninit();	// 終了処理
		m_pReturnHome = NULL;		// NULLへ
	}
	// もどるキャラ
	if (m_pReturnChar != NULL)
	{// NULL以外
		m_pReturnChar->Uninit();	// 終了処理
		m_pReturnChar = NULL;		// NULLへ
	}
	// もどる草
	if (m_pReturnGrass != NULL)
	{// NULL以外
		m_pReturnGrass->Uninit();	// 終了処理
		m_pReturnGrass = NULL;		// NULLへ
	}

	// 準備
	if (m_pReady != NULL)
	{// NULL以外
		m_pReady->Uninit();		// 終了処理
		m_pReady = NULL;		// NULLへ
	}

	// チュートリアル
	if (m_pTutorial != NULL)
	{// NULL以外
		m_pTutorial->Uninit();	// 終了処理
		m_pTutorial = NULL;		// NULLへ
	}

	// ヒント
	for (int nCount = 0; nCount < MAX_HINT; nCount++)
	{
		if (m_pHint[nCount] != NULL)
		{// NULL以外
			m_pHint[nCount]->Uninit();	// 終了処理
			m_pHint[nCount] = NULL;		// NULLへ
		}
	}

	// Go
	if (m_pGo != NULL)
	{// NULL以外
		m_pGo->Uninit();	// 終了処理
		m_pGo = NULL;		// NULLへ
	}

	// キャラクター
	for (int nCntChar = 0; nCntChar < MAX_CHARCTER; nCntChar++)
	{// キャラカウント
		if (m_pCharacter[nCntChar] != NULL)
		{// NULL以外
			m_pCharacter[nCntChar]->Uninit();	// 終了処理
			m_pCharacter[nCntChar] = NULL;		// NULLへ
		}
	}

	//自身の削除
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGameCharSelect::Update(void)
{
	if (m_bReady == false)
	{
		// 取得
		bool bOnine = CTitle::GetOnline();

		if (bOnine == true)
			Online();		// オンライン
		else
			Local();		// ローカル
	}
	else
	{
		Tutorial();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CGameCharSelect::Draw(void)
{

}

//=============================================================================
// オンライン
//=============================================================================
void CGameCharSelect::Online(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoyPad_0 * pXpad = CManager::GetInputJoyPad0(0);		//ジョイパットの取得
	CSound *pSound = CManager::GetSound();						//サウンドの情報

																// プレイヤー
	CPlayer **pPlayer = NULL;
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		pPlayer = CTitle::GetPlayer();
		break;
	case CManager::MODE_GAME:
		pPlayer = CGame::GetPlayer();
		break;
	}

	// プレイヤー最大数取得
	int nMaxPlayer = CGame::GetMaxPlayer();
	// キャラ選択番号取得
	int *pnCharSelectNum = CGame::GetCharSelectNum();

	int nPlayerNum = nMaxPlayer;

	if (CFade::GetFade() == CFade::FADE_NONE)
	{// 使用していない
		for (int nCntPlayer = 0; nCntPlayer < nMaxPlayer; nCntPlayer++)
		{// プレイヤーカウント
			pXpad = CManager::GetInputJoyPad0(nCntPlayer);		//ジョイパットの取得

			if (m_bEnter[nCntPlayer] == false)
			{// 決定していない
				if (pXpad->GetTrigger(INPUT_LS_U) == true ||
					pXpad->GetTrigger(INPUT_UP) == true)
				{// 上キー
					if (pnCharSelectNum[nCntPlayer] / 4 == 0)
					{// 移動制限
					 // 次の値
						int nNext = (pnCharSelectNum[nCntPlayer] + 4) % MAX_CHARCTER;

						for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
						{// 選択カウント
							if (nCntSelect != nCntPlayer)
							{// 自分以外
								if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
									break;
							}

							if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
								pnCharSelectNum[nCntPlayer] = nNext;
						}
					}
				}
				else if (pXpad->GetTrigger(INPUT_LS_D) == true ||
					pXpad->GetTrigger(INPUT_DOWN) == true)
				{// 下キー
					if (pnCharSelectNum[nCntPlayer] / 4 == 1)
					{// 移動制限
					 // 次の値
						int nNext = (pnCharSelectNum[nCntPlayer] + 4) % MAX_CHARCTER;

						for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
						{// 選択カウント
							if (nCntSelect != nCntPlayer)
							{// 自分以外
								if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
									break;
							}

							if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
								pnCharSelectNum[nCntPlayer] = nNext;
						}

					}
				}
				if (pXpad->GetTrigger(INPUT_LS_L) == true ||
					pXpad->GetTrigger(INPUT_LEFT) == true)
				{// 左キー
					if (pnCharSelectNum[nCntPlayer] % 4 != 0)
					{// 移動制限
					 // 次の値
						int nNext = pnCharSelectNum[nCntPlayer];

						for (int nCntLine = pnCharSelectNum[nCntPlayer] % 4 - 1; 0 <= nCntLine; nCntLine--)
						{// ラインカウント
							nNext = (nNext - 1) % MAX_CHARCTER;

							for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
							{// 選択カウント
								if (nCntSelect != nCntPlayer)
								{// 自分以外
									if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
										break;
								}

								if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
									pnCharSelectNum[nCntPlayer] = nNext;
							}

							if (pnCharSelectNum[nCntPlayer] == nNext)				// 更新した
								break;
						}
					}
				}
				else if (pXpad->GetTrigger(INPUT_LS_R) == true ||
					pXpad->GetTrigger(INPUT_RIGHT) == true)
				{// 右キー
					if (pnCharSelectNum[nCntPlayer] % 4 != (4 - 1))
					{// 移動制限
					 // 次の値
						int nNext = pnCharSelectNum[nCntPlayer];

						for (int nCntLine = pnCharSelectNum[nCntPlayer] % 4 + 1; nCntLine < 4; nCntLine++)
						{// ラインカウント	
							nNext = (nNext + 1) % MAX_CHARCTER;

							for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
							{// 選択カウント
								if (nCntSelect != nCntPlayer)
								{// 自分以外
									if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
										break;
								}

								if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
									pnCharSelectNum[nCntPlayer] = nNext;
							}

							if (pnCharSelectNum[nCntPlayer] == nNext)				// 更新した
								break;
						}
					}
				}
			}

			if (pXpad->GetTrigger(INPUT_B) == true ||
				pXpad->GetTrigger(INPUT_R2) == true)
			{// 決定キー
				if (m_bEntry[nCntPlayer] == true)
				{
					m_bEnter[nCntPlayer] = (m_bEnter[nCntPlayer] ^ 1 ? true : false);

					pPlayer[pnCharSelectNum[nCntPlayer]]->SetSelectNum((int)(m_bEnter[nCntPlayer]));

					//決定音の設定
					pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
					pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
				}
			}
		}
	}

	int nChackEnter = 0;
	for (int nCntPlayer = 0; nCntPlayer < nMaxPlayer; nCntPlayer++)
	{// プレイヤーカウント
	 // 選択
		if (m_pSelect[nCntPlayer] != NULL)
		{// NULL以外
			m_pSelect[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) +
					((SCREEN_WIDTH * (pnCharSelectNum[nCntPlayer] / 4 == 0 ? 0.055f : 0.04f) +
					(pnCharSelectNum[nCntPlayer] % 4 == 0 || pnCharSelectNum[nCntPlayer] % 4 == 3 ? (SCREEN_WIDTH * (pnCharSelectNum[nCntPlayer] / 4 == 0 ? 0.055f : 0.04f)) * 2.0f : 0.0f)) *
						(pnCharSelectNum[nCntPlayer] / 2 % 2 == 0 ? -1.0f : 1.0f)),
						(SCREEN_HEIGHT * 0.6f) + ((SCREEN_WIDTH * 0.05f) * (pnCharSelectNum[nCntPlayer] / 4 == 0 ? 0.0f : -1.0f)),
					0.0f),
				D3DXVECTOR2(SCREEN_WIDTH * 0.04f, SCREEN_WIDTH * 0.04f));
			m_pSelect[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// 決定数チャック
		if (m_bEnter[nCntPlayer] == true)
		{// 決定
			nChackEnter++;

			// 決定
			if (m_pEnter[nCntPlayer] != NULL)
			{
				m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		else
		{// 選択中
		 // 決定
			if (m_pEnter[nCntPlayer] != NULL)
			{
				m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}

		if (m_pButton[nCntPlayer] != NULL)
		{// NULL以外
		 //if (m_bEntry[nCntPlayer] == true)
			m_pButton[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			//else
			//	m_pButton[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	pXpad = CManager::GetInputJoyPad0(0);		//ジョイパットの取得

												// 全員決定
	if (nMaxPlayer != 0)
	{
		if (nChackEnter == nMaxPlayer)
		{
			if (m_pReady != NULL)
				m_pReady->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true ||
				pXpad->GetTrigger(INPUT_START) == true)
			{
				m_bReady = true;
			}
		}
		else
		{
			if (m_pReady != NULL)
				m_pReady->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	// プレイヤー最大数設定
	CGame::SetMaxPlayer(nMaxPlayer);
	// キャラ選択番号設定
	CGame::SetCharSelectNum(pnCharSelectNum);

	m_nEntryCounter++;		// カウント	
}

//=============================================================================
// ローカル
//=============================================================================
void CGameCharSelect::Local(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoyPad_0 * pXpad = CManager::GetInputJoyPad0(0);		//ジョイパットの取得
	CSound *pSound = CManager::GetSound();						//サウンドの情報

																// プレイヤー
	CPlayer **pPlayer = NULL;
	switch (CManager::GetMode())
	{
	case CManager::MODE_TITLE:
		pPlayer = CTitle::GetPlayer();
		break;
	case CManager::MODE_GAME:
		pPlayer = CGame::GetPlayer();
		break;
	}
	// プレイヤー最大数取得
	int nMaxPlayer = CGame::GetMaxPlayer();
	// キャラ選択番号取得
	int *pnCharSelectNum = CGame::GetCharSelectNum();
	// コントローラー番号取得
	int *pnControllerNum = CGame::GetControllerNum();

	int nPlayerNum = nMaxPlayer;

	bool bReturnInput = false;

	if (CFade::GetFade() == CFade::FADE_NONE)
	{// 使用していない
		for (int nCntPlayer = 0; nCntPlayer < nMaxPlayer; nCntPlayer++)
		{// プレイヤーカウント
			pXpad = CManager::GetInputJoyPad0(pnControllerNum[nCntPlayer]);		//ジョイパットの取得

			if (m_bEnter[nCntPlayer] == false)
			{// 決定していない
				if (pCInputKeyBoard->GetKeyboardTrigger(DIK_W) == true ||
					pCInputKeyBoard->GetKeyboardTrigger(DIK_UP) == true ||
					pXpad->GetTrigger(INPUT_LS_U) == true ||
					pXpad->GetTrigger(INPUT_UP) == true)
				{// 上キー
					if (pnCharSelectNum[nCntPlayer] / 4 == 0)
					{// 移動制限
					 // 次の値
						int nNext = (pnCharSelectNum[nCntPlayer] + 4) % MAX_CHARCTER;

						for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
						{// 選択カウント
							if (nCntSelect != nCntPlayer)
							{// 自分以外
								if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
									break;
							}

							if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
								pnCharSelectNum[nCntPlayer] = nNext;
						}
					}
				}
				else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_S) == true ||
					pCInputKeyBoard->GetKeyboardTrigger(DIK_DOWN) == true ||
					pXpad->GetTrigger(INPUT_LS_D) == true ||
					pXpad->GetTrigger(INPUT_DOWN) == true)
				{// 下キー
					if (pnCharSelectNum[nCntPlayer] / 4 == 1)
					{// 移動制限
					 // 次の値
						int nNext = (pnCharSelectNum[nCntPlayer] + 4) % MAX_CHARCTER;

						for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
						{// 選択カウント
							if (nCntSelect != nCntPlayer)
							{// 自分以外
								if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
									break;
							}

							if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
								pnCharSelectNum[nCntPlayer] = nNext;
						}
					}
				}
				if (pCInputKeyBoard->GetKeyboardTrigger(DIK_A) == true ||
					pCInputKeyBoard->GetKeyboardTrigger(DIK_LEFT) == true ||
					pXpad->GetTrigger(INPUT_LS_L) == true ||
					pXpad->GetTrigger(INPUT_LEFT) == true)
				{// 左キー
					if (pnCharSelectNum[nCntPlayer] % 4 != 0)
					{// 移動制限
					 // 次の値
						int nNext = pnCharSelectNum[nCntPlayer];

						for (int nCntLine = pnCharSelectNum[nCntPlayer] % 4 - 1; 0 <= nCntLine; nCntLine--)
						{// ラインカウント
							nNext = (nNext - 1) % MAX_CHARCTER;

							for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
							{// 選択カウント
								if (nCntSelect != nCntPlayer)
								{// 自分以外
									if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
										break;
								}

								if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
									pnCharSelectNum[nCntPlayer] = nNext;
							}

							if (pnCharSelectNum[nCntPlayer] == nNext)				// 更新した
								break;
						}
					}
				}
				else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_D) == true ||
					pCInputKeyBoard->GetKeyboardTrigger(DIK_RIGHT) == true ||
					pXpad->GetTrigger(INPUT_LS_R) == true ||
					pXpad->GetTrigger(INPUT_RIGHT) == true)
				{// 右キー
					if (pnCharSelectNum[nCntPlayer] % 4 != (4 - 1))
					{// 移動制限
					 // 次の値
						int nNext = pnCharSelectNum[nCntPlayer];

						for (int nCntLine = pnCharSelectNum[nCntPlayer] % 4 + 1; nCntLine < 4; nCntLine++)
						{// ラインカウント	
							nNext = (nNext + 1) % MAX_CHARCTER;

							for (int nCntSelect = 0; nCntSelect < nMaxPlayer; nCntSelect++)
							{// 選択カウント
								if (nCntSelect != nCntPlayer)
								{// 自分以外
									if (pnCharSelectNum[nCntSelect] == nNext)	// 値が一致
										break;
								}

								if (nCntSelect == (nMaxPlayer - 1))			// 一致しなかったら更新
									pnCharSelectNum[nCntPlayer] = nNext;
							}

							if (pnCharSelectNum[nCntPlayer] == nNext)				// 更新した
								break;
						}
					}
				}
			}

			if (pXpad->GetTrigger(INPUT_B) == true ||
				pXpad->GetTrigger(INPUT_R2) == true)
			{// 決定キー
				if (m_bEntry[nCntPlayer] == true)
				{
					m_bEnter[nCntPlayer] = (m_bEnter[nCntPlayer] ^ 1 ? true : false);

					pPlayer[pnCharSelectNum[nCntPlayer]]->SetSelectNum((int)(m_bEnter[nCntPlayer]));

					//決定音の設定
					pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
					pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
				}
			}
		}

		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{// プレイヤーカウント
			bool bSet = false;	// コントローラーチェック用

								// 使用していないコントローラーがチェック
			for (int nCntCheck = 0; nCntCheck < nMaxPlayer; nCntCheck++)
				if (pnControllerNum[nCntCheck] == nCntPlayer)
					bSet = true;

			if (bSet == false)
			{// 使用していない
				pXpad = CManager::GetInputJoyPad0(nCntPlayer);		//ジョイパットの取得

				if (pXpad->GetTrigger(INPUT_START) == true)
				{// 決定キー
					if (m_bEntry[nPlayerNum] == false)
					{
						m_bEntry[nPlayerNum] = true;
						pnControllerNum[nPlayerNum] = nCntPlayer;
						nPlayerNum = nPlayerNum + (nPlayerNum < (MAX_PLAYER - 1) ? 1 : 0);
					}
				}
			}
		}

		if (CManager::GetAging() == true)
		{
			int nNum = CServer::Rand() % MAX_MEMBER;
			int nMax = (CServer::Rand() % 4) + 1;
			for (int nCount = 0; nCount < nMax; nCount++)
			{
				pnCharSelectNum[nCount] = (nNum + nCount) % MAX_MEMBER;
				m_bEntry[nCount] = true;
				m_bEnter[nCount] = true;
				pPlayer[pnCharSelectNum[nCount]]->SetSelectNum(1);
			}
		}

		// キーボード
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_Z) == true || (m_bEntry[0] == false && pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true))
		{
			if (m_bEntry[0] == true)
			{
				m_bEnter[0] = (m_bEnter[0] ^ 1 ? true : false);

				pPlayer[pnCharSelectNum[0]]->SetSelectNum((int)(m_bEnter[0]));

				//決定音の設定
				pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
			}
			else
			{
				m_bEntry[0] = true;
			}
		}

		// デバッグ（各決定）
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_1) == true)
		{
			if (m_bEntry[0] == true)
			{
				m_bEnter[0] = (m_bEnter[0] ^ 1 ? true : false);

				pPlayer[pnCharSelectNum[0]]->SetSelectNum((int)(m_bEnter[0]));

				//決定音の設定
				pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
			}
			else
			{
				m_bEntry[0] = true;
			}
		}
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_2) == true)
		{
			if (m_bEntry[1] == true)
			{
				m_bEnter[1] = (m_bEnter[1] ^ 1 ? true : false);

				pPlayer[pnCharSelectNum[1]]->SetSelectNum((int)(m_bEnter[1]));

				//決定音の設定
				pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
			}
			else
			{
				m_bEntry[1] = true;
			}
		}
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_3) == true)
		{
			if (m_bEntry[2] == true)
			{
				m_bEnter[2] = (m_bEnter[2] ^ 1 ? true : false);

				pPlayer[pnCharSelectNum[2]]->SetSelectNum((int)(m_bEnter[2]));

				//決定音の設定
				pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
			}
			else
			{
				m_bEntry[2] = true;
			}
		}
		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_4) == true)
		{
			if (m_bEntry[3] == true)
			{
				m_bEnter[3] = (m_bEnter[3] ^ 1 ? true : false);

				pPlayer[pnCharSelectNum[3]]->SetSelectNum((int)(m_bEnter[3]));
			
				//決定音の設定
				pSound->SetVolume(CSound::SOUND_LABEL_SE_CHARACTERSERECT, 1.3f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_CHARACTERSERECT);
			}
			else
			{
				m_bEntry[3] = true;
			}
		}

		pXpad = CManager::GetInputJoyPad0(pnControllerNum[0]);		//ジョイパットの取得

		if (pCInputKeyBoard->GetKeyboardPress(DIK_X) == true || pXpad->GetPress(INPUT_A) == true)
		{
			if (m_nReturnCounter < 90)
				m_nReturnCounter++;
			else
				CFade::Create(CManager::MODE_TITLE);

			bReturnInput = true;
		}
		else
		{
			if (0 < m_nReturnCounter)
				m_nReturnCounter -= 2;
			else
				m_nReturnCounter = 0;

			bReturnInput = false;
		}
	}

	int nChackEnter = 0;
	for (int nCntPlayer = 0; nCntPlayer < nMaxPlayer; nCntPlayer++)
	{// プレイヤーカウント
	 // プレイヤー番号
		if (m_pPlayerNum[nCntPlayer] != NULL)
		{// NULL以外
			m_pPlayerNum[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// 選択
		if (m_pSelect[nCntPlayer] != NULL)
		{// NULL以外
			m_pSelect[nCntPlayer]->SetPosSize(
				D3DXVECTOR3(
				(SCREEN_WIDTH * 0.5f) +
					((SCREEN_WIDTH * (pnCharSelectNum[nCntPlayer] / 4 == 0 ? 0.055f : 0.04f) +
					(pnCharSelectNum[nCntPlayer] % 4 == 0 || pnCharSelectNum[nCntPlayer] % 4 == 3 ? (SCREEN_WIDTH * (pnCharSelectNum[nCntPlayer] / 4 == 0 ? 0.055f : 0.04f)) * 2.0f : 0.0f)) *
						(pnCharSelectNum[nCntPlayer] / 2 % 2 == 0 ? -1.0f : 1.0f)),
						(SCREEN_HEIGHT * 0.6f) + ((SCREEN_WIDTH * 0.05f) * (pnCharSelectNum[nCntPlayer] / 4 == 0 ? 0.0f : -1.0f)),
					0.0f),
				D3DXVECTOR2(SCREEN_WIDTH * 0.04f, SCREEN_WIDTH * 0.04f));
			m_pSelect[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// 決定数チャック
		if (m_bEnter[nCntPlayer] == true)
		{// 決定
			nChackEnter++;

			// 決定
			if (m_pEnter[nCntPlayer] != NULL)
			{
				m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				m_pEnter[nCntPlayer]->SetTexture(0, 1, 2, 2);
			}
		}
		else
		{// 選択中
			if (m_pEnter[nCntPlayer] != NULL)
			{
				m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}

		if (m_pButton[nCntPlayer] != NULL)
		{// NULL以外
		 //if (m_bEntry[nCntPlayer] == true)
			m_pButton[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			//else
			//	m_pButton[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	pXpad = CManager::GetInputJoyPad0(pnControllerNum[0]);		//ジョイパットの取得

																// 全員決定
	if (nMaxPlayer != 0)
	{
		if (nChackEnter == nMaxPlayer)
		{
			if (m_pReady != NULL)
				m_pReady->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true ||
				pXpad->GetTrigger(INPUT_START) == true ||
				CManager::GetAging() == true)
			{
				m_bReady = true;
			}
		}
		else
		{
			if (m_pReady != NULL)
				m_pReady->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	int nEntryNum = 0;
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーカウント
		if (m_bEntry[nCntPlayer] == true)
			nEntryNum++;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{// プレイヤーカウント
	 // 決定
		if (nEntryNum <= nCntPlayer)
		{
			if (m_pEnter[nCntPlayer] != NULL)
			{
				int nCount = (m_nEntryCounter % 60);
				if (nCount < 20)
				{
					if (nCount < 10)
						m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - ((1.0f / 10.0f) * nCount)));
					else
						m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, ((1.0f / 10.0f) * (nCount - 10))));
				}
				else
				{
					m_pEnter[nCntPlayer]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				m_pEnter[nCntPlayer]->SetTexture(1, 1, 2, 2);
			}
		}
	}

	if (nMaxPlayer != nEntryNum)
	{// プレイヤー数が変わった
		nMaxPlayer = nEntryNum;		// プレイヤー数を更新

		for (int nCntPlayer = (nMaxPlayer - 1); 0 <= nCntPlayer; nCntPlayer--)
		{// プレイヤーカウント
			while (1)
			{// 同じ番号をなくす
				bool bCheck = false;
				for (int nCntCheck = (nMaxPlayer - 1); 0 <= nCntCheck; nCntCheck--)
				{// チェックカウント
					if (nCntPlayer != nCntCheck)
					{// 自分以外
						if (pnCharSelectNum[nCntPlayer] == pnCharSelectNum[nCntCheck])
						{// 同じ番号があった
							bCheck = true;
							break;
						}
					}
				}

				// 番号を変更 or break
				if (bCheck == true)
					pnCharSelectNum[nCntPlayer] = (pnCharSelectNum[nCntPlayer] + 1) % MAX_CHARCTER;
				else
					break;
			}

			while (1)
			{// 同じ番号をなくす
				bool bCheck = false;
				for (int nCntCheck = (nMaxPlayer - 1); 0 <= nCntCheck; nCntCheck--)
				{// チェックカウント
					if (nCntPlayer != nCntCheck)
					{// 自分以外
						if (pnControllerNum[nCntPlayer] == pnControllerNum[nCntCheck])
						{// 同じ番号があった
							bCheck = true;
							break;
						}
					}
				}

				// 番号を変更 or break
				if (bCheck == true)
					pnControllerNum[nCntPlayer] = (pnControllerNum[nCntPlayer] + 1) % MAX_PLAYER;
				else
					break;
			}
		}
	}

	// もどるキャラ
	if (m_pReturnBG != NULL)
	{// NULL以外
	 //m_pReturnBG->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, (m_nReturnCounter < 45 ? (1.0f * (float)((float)m_nReturnCounter / (float)45)) : 1.0f)));
	}
	// もどるキャラ
	if (m_pReturnChar != NULL)
	{// NULL以外
		m_pReturnChar->SetPosSize(
			D3DXVECTOR3(
			((SCREEN_WIDTH * 0.5f) + (SCREEN_WIDTH * 0.07f) + -(SCREEN_WIDTH * 0.09f)) + (((SCREEN_WIDTH * 0.09f) * 1.8f) * (float)((float)m_nReturnCounter / (float)90)),
				(SCREEN_HEIGHT * 0.052f) + ((m_nReturnCounter / 5) % 2 == 0 ? -2.0f : 0.0f),
				0.0f),
			D3DXVECTOR2(SCREEN_HEIGHT * 0.03f, SCREEN_HEIGHT * 0.04f));
		//m_pReturnChar->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, (m_nReturnCounter < 45 ? (1.0f * (float)((float)m_nReturnCounter / (float)45)) : 1.0f)));

		if (bReturnInput == true || m_nReturnCounter == 0)
			m_pReturnChar->SetUV(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		else
			m_pReturnChar->SetUV(D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	}

	// プレイヤー最大数設定
	CGame::SetMaxPlayer(nMaxPlayer);
	// キャラ選択番号設定
	CGame::SetCharSelectNum(pnCharSelectNum);
	// コントローラー設定
	CGame::SetControllerNum(pnControllerNum);

	m_nEntryCounter++;		// カウント
}

//=============================================================================
// チュートリアル
//=============================================================================
void CGameCharSelect::Tutorial(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoyPad_0 * pXpad = CManager::GetInputJoyPad0(0);		//ジョイパットの取得
	CSound *pSound = CManager::GetSound();						//サウンドの情報

																// コントローラー番号取得
	int *pnControllerNum = CGame::GetControllerNum();

	// 取得
	bool bOnine = CTitle::GetOnline();

	int nCounter = m_nTutorialCounter % 120;

	float fcol_a =
		(nCounter < 60 ?
		((float)((float)(nCounter % 60) / (float)60) / 1.0f) : 1.0f - ((float)((float)(nCounter % 60) / (float)60) / 1.0f));

	if (m_pTutorial != NULL)
	{
		float fposDest_X = (SCREEN_WIDTH * (float)(2 - m_nTutorialNum)) - (SCREEN_WIDTH * 0.5f);

		D3DXVECTOR3 pos = m_pTutorial->GetPosition();

		pos.x += (fposDest_X - pos.x) * 0.5f;

		m_pTutorial->SetPosSize(pos,
			D3DXVECTOR2(SCREEN_WIDTH * 1.5f, SCREEN_HEIGHT * 0.5f));
		m_pTutorial->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	for (int nCount = 0; nCount < MAX_HINT; nCount++)
	{
		if (m_pHint[nCount] != NULL)
		{
			if (m_nTutorialNum < 2)
			{
				if (m_nTutorialNum == nCount || m_nTutorialNum == 1)
					m_pHint[nCount]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol_a));
				else
					m_pHint[nCount]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

				m_pHint[nCount]->SetTexture((nCount ^ 1), 3, 1, 1);

				if (nCount == 0 && m_nTutorialNum == 1)
					m_pHint[nCount]->SetTexture(2, 3, 1, 1);
			}
			else
			{
				m_pHint[nCount]->SetUV(D3DXVECTOR2(0.666f, 0.0f), D3DXVECTOR2(0.333f, 0.0f), D3DXVECTOR2(0.666f, 1.0f), D3DXVECTOR2(0.333f, 1.0f));

				if (nCount == 0)
					m_pHint[nCount]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				else
					m_pHint[nCount]->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol_a));
			}
		}
	}

	if (m_pGo != NULL)
		m_pGo->SetColor(&D3DXCOLOR(1.0f, 1.0f, 1.0f, fcol_a));

	if (bOnine == true)
	{
		pXpad = CManager::GetInputJoyPad0(0);		//ジョイパットの取得

		if (pXpad->GetTrigger(INPUT_LS_L) == true ||
			pXpad->GetTrigger(INPUT_LEFT) == true)
		{
			if (0 < m_nTutorialNum)
				m_nTutorialNum--;
		}
		else if (pXpad->GetTrigger(INPUT_LS_R) == true ||
			pXpad->GetTrigger(INPUT_RIGHT) == true)
		{// 右キー
			if (m_nTutorialNum < 2)
				m_nTutorialNum++;
		}

		if (pXpad->GetTrigger(INPUT_B) == true ||
			pXpad->GetTrigger(INPUT_R2) == true ||
			pXpad->GetTrigger(INPUT_START) == true)
		{
			if (m_nTutorialNum < 2)
				m_nTutorialNum++;
			else
				CFade::Create(CGame::GAMEMODE_COURSE_VIEW);
		}
	}
	else
	{
		pXpad = CManager::GetInputJoyPad0(pnControllerNum[0]);		//ジョイパットの取得

		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_A) == true ||
			pCInputKeyBoard->GetKeyboardTrigger(DIK_LEFT) == true ||
			pXpad->GetTrigger(INPUT_LS_L) == true ||
			pXpad->GetTrigger(INPUT_LEFT) == true)
		{
			if (0 < m_nTutorialNum)
				m_nTutorialNum--;
		}
		else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_D) == true ||
			pCInputKeyBoard->GetKeyboardTrigger(DIK_RIGHT) == true ||
			pXpad->GetTrigger(INPUT_LS_R) == true ||
			pXpad->GetTrigger(INPUT_RIGHT) == true)
		{// 右キー
			if (m_nTutorialNum < 2)
				m_nTutorialNum++;
		}

		if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true ||
			pCInputKeyBoard->GetKeyboardTrigger(DIK_Z) == true ||
			pXpad->GetTrigger(INPUT_B) == true ||
			pXpad->GetTrigger(INPUT_R2) == true ||
			pXpad->GetTrigger(INPUT_START) == true ||
			CManager::GetAging() == true)
		{
			if (m_nTutorialNum < 2)
				m_nTutorialNum++;
			else
				CFade::Create(CGame::GAMEMODE_COURSE_VIEW);
		}
	}

	m_nTutorialCounter++;
}