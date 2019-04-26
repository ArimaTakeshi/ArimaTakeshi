//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "SceneBullet.h"
#include "Player.h"
#include "scene.h"
#include "enemy.h"
#include "dungeon.h"
#include "Font.h"
#include "Game.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
bool	CGame::m_bDuo = false;	//2人プレイかどうか

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	CScene::CreateAll(0, 64);
	CScene::CreateAll(1, 128);
	CScene::CreateAll(2, 16);
	CScene::CreateAll(3, 128);
	CScene::CreateAll(4, 128);
	CScene::CreateAll(5, 1280);
	CScene::CreateAll(6, 128);
	CScene::CreateAll(7, 32);

	//CSceneBullet::Load(CSceneBullet::TEX_BULLET);
	//CSceneBullet::Load(CSceneBullet::TEX_BULLET_S);
	//CScene3D::Load(CScene3D::TEX_MARKER);
	//CSceneAnim3D::Load(CSceneAnim3D::TEX_EXPLOSION);
	//CSceneAnim3D::Load(CSceneAnim3D::TEX_FIRE_EXPLOSION);

	//CScene2D::Load(CScene2D::TEXTURE_Slashing0);
	//CScene2D::Load(CScene2D::TEXTURE_LogoPause);
	//CScene2D::Load(CScene2D::TEXTURE_ITEM_TUTORIAL);
	//CScene2D::Load(CScene2D::TEXTURE_Fade000);

	//CScenePlayer::GetbShop() = false;
	//CScenePlayer *pScenePlayer = NULL;
	//if(SceneCreate(pScenePlayer, MODEL_PRIORITY)) {
	//	pScenePlayer->Set(D3DXVECTOR3(0.0f, PLAYER_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TANKD, CSceneModel::MODEL_TANKU, CSceneModel::TEX_PTN_01, CSceneModel::TEX_PTN_01, CScene::DRAW_TYPE_NORMAL);
	//}
	//if (m_bDuo)
	//{//2人組なら　二人目のプレイヤー生成
	//	if (SceneCreate(pScenePlayer, MODEL_PRIORITY)) {
	//		pScenePlayer->Set(D3DXVECTOR3(0.0f, PLAYER_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TANKD, CSceneModel::MODEL_TANKU, CSceneModel::TEX_PTN_01, CSceneModel::TEX_PTN_01, CScene::DRAW_TYPE_NORMAL);
	//	}
	//}

	//CScenePlayer::GetnStage() = 1;
	//CDungeon *pDungeon = NULL;
	//if (SceneCreate(pDungeon, DUNGEON_PRIORYITY))
	//	{ pDungeon->SetDungeon(CScenePlayer::GetnStage()); }

	CPlayer *pPlayer;
	if(SceneCreate(pPlayer, 1))
	{
		pPlayer->Set(3);
	}
	CScene2D *p2D;
	if (SceneCreate(p2D, 0))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), CScene2D::TEX_Game000);
	}

	m_state = STATE_NONE;
	m_fCntState = 0.0f;
	m_nCntTime = 0;
	m_fInterval = 100.0f;
	m_nCntType = 0;
	m_nWave = 1;

	//BGMの再生
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::LABEL_GAME000);

	return S_OK;
}
//=============================================================================
// ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
	CSound *pSound = CManager::GetSound();

	CScene2D *pScene2D;
	CSceneAnim2D *pSceneAnim2D;
	CEnemy *pEnemy;
	CEnemy::ENEMYTYPE type = CEnemy::ENEMYTYPE_NORMAL;

	CInputKeyboard	*pInputKey = CManager::GetInputKey();			//キーボード情報獲得
	//if (pInputKey->GetTrigger(DIK_RETURN))
	//{
	//	CManager::GetPlayer0()->GetfLife() -= 1.0f;
	//	if (CManager::GetPlayer0()->GetfLife() <= 0.0f) { CManager::GetPlayer0()->GetfLife() = 0.0f; }
	//}
	if (!CScene::GetbPause())
	{
		if (m_state != STATE_OVER)
		{
			if (CManager::GetPlayer0()->GetfLife() <= 0.0f)
			{
				CManager::GetPlayer0()->BindDrawType(CScene::DRAW_TYPE_NO);
				CSceneAnim2D *p2DAnim;
				if (SceneCreate(p2DAnim, 6))
				{//生成できたなら　//火花
					p2DAnim->Set(CManager::GetPlayer0()->GetPosition()[0], 80.0f, 80.0f, D3DX_PI, 3, 10, 1, 4, 100.0f, CScene2D::STATE_BIG, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Explosion999);
					p2DAnim->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
				}
				if (SceneCreate(p2DAnim, 6))
				{//生成できたなら　//火花
					p2DAnim->Set(CManager::GetPlayer0()->GetPosition()[0], 50.0f, 50.0f, D3DX_PI, 3, 10, 1, 4, 100.0f, CScene2D::STATE_BIG, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Explosion999);
					p2DAnim->BindDrawType(CScene::DRAW_TYPE_ADD);
				}
				SetState(STATE_OVER);
			}
			else
			{//生きているなら
				int nTime = 1200 + m_nWave * 60;
				if (nTime > 2000) { nTime = 2000; }
				int nInterval = (int)(m_fInterval - ((float)m_nCntTime / (float)(600)));
				if (nInterval < 1) { nInterval = 1; }
				m_nCntTime++;
				if (m_nCntTime > nTime)
				{
					pSound->Play(CSound::LABEL_WAVE);

					char aStr[64];
					CFont *pFont;

					m_nWave++;
					wsprintf(&aStr[0], "WAVE %d ", m_nWave);
					m_nCntTime = 0;
					m_fInterval -= 7.5f;
					if (m_fInterval < 1) { m_fInterval = 1; }
					if (CManager::GetPlayer0()->GetfLife() < 5) { CManager::GetPlayer0()->GetfLife() += 1; }
					if (CManager::GetPlayer0()->GetnBomb() < 3)
					{
						CManager::GetPlayer0()->GetpBomb(CManager::GetPlayer0()->GetnBomb())->BindDrawType(CScene::DRAW_TYPE_NORMAL);
						CManager::GetPlayer0()->GetnBomb() += 1;


					}

					if (SceneCreate(pFont, 6))
					{
						pFont->Set(RECT{ 0, SCREEN_HEIGHT / 2 - 10, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), &aStr[0], 2, DT_CENTER, -1, true, CFont::STATE_FADE);
						pFont->GetfCntState() = 0.05f;
					}
					for (int nCount = 0; nCount < m_nWave * 3; nCount++)
					{
						if (nCount % 8 == 0) { type = CEnemy::ENEMYTYPE_HP; }
						else if (nCount % 2 == 0) { type = CEnemy::ENEMYTYPE_NORMAL2; }
						if (SceneCreate(pEnemy, 1))
						{
							pEnemy->Set(D3DXVECTOR3(SCREEN_WIDTH + 50.0f + nCount * 2, SCREEN_HEIGHT / 6 * (float)(rand() % 5 + 1), 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_MAX, type);
						}
					}

					CManager::GetPlayer0()->GetpFont()->SetFont(&aStr[0], -1);

					switch (m_nWave)
					{
					case 2:
						if (SceneCreate(pFont, 6))
						{
							pFont->Set(RECT{ 0, SCREEN_HEIGHT / 2 - 150, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR(0.55f, 1.0f, 0.0f, 1.0f), "ボタンA：散弾が解放されました！", 2, DT_CENTER, -1, true, CFont::STATE_FADEOUT);
							pFont->GetfCntState() = 0.005f;
						}
						break;
					case 3:
						if (SceneCreate(pFont, 6))
						{
							pFont->Set(RECT{ 0, SCREEN_HEIGHT / 2 - 150, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR(0.98f, 1.0f, 0.02f, 1.0f), "ボタンY：雷弾が解放されました！", 2, DT_CENTER, -1, true, CFont::STATE_FADEOUT);
							pFont->GetfCntState() = 0.005f;
						}
						break;
					case 4:
						if (SceneCreate(pFont, 6))
						{
							pFont->Set(RECT{ 0, SCREEN_HEIGHT / 2 - 150, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR(0.0f, 0.95f, 1.0f, 1.0f), "ボタンY：氷弾が解放されました！", 2, DT_CENTER, -1, true, CFont::STATE_FADEOUT);
							pFont->GetfCntState() = 0.005f;
						}
						break;
					}
					m_nCntType = 0;
				}
				if (m_nCntTime >= 0 && m_nCntTime < 1000)
				{
					if (m_nCntTime % nInterval == 0)
					{//ランダム生成
						if (m_nCntType % 8 == 0) { type = CEnemy::ENEMYTYPE_HP; }
						else if (m_nCntType % 4 == 0) { type = CEnemy::ENEMYTYPE_SPEED; }
						else if (m_nCntType % 2 == 0) { type = CEnemy::ENEMYTYPE_NORMAL2; }

						if (SceneCreate(pEnemy, 1))
						{
							pEnemy->Set(D3DXVECTOR3(SCREEN_WIDTH + 50.0f, SCREEN_HEIGHT / 6 * (float)(rand() % 5 + 1), 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_MAX, type);
						}
						m_nCntType++;
					}
				}
			}
		}
	}
	switch (m_state)
	{
	case STATE_NONE:
		Pause();	//ポーズの更新
		break;
	case STATE_CLEAR:
		m_fCntState += 1.0f;
		switch ((int)m_fCntState)
		{
		case 60:
			if (SceneCreate(pSceneAnim2D, S2D_PRIORITY))
			{//CLEAR表記
				pSceneAnim2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 10, 3, 0.0f, CScene2D::STATE_NORMAL, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_CLEAR);
				pSceneAnim2D->BindDrawType(CScene::DRAW_TYPE_MULTIPLY);
			}
			CManager::GetSound()->Stop(CSound::LABEL_CLEAR000);
			break;
		case 1800:
			CManager::SetFade(CManager::MODE_TITLE, 0);
			break;
		}
		if (m_fCntState > 90 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) ||
			CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_TITLE, 0);
		}
		break;

	case STATE_OVER:
		m_fCntState += 1.0f;
		switch ((int)m_fCntState)
		{
		case 3:
			CManager::GetSound()->Stop();
			CManager::GetSound()->CountReset(CSound::LABEL_HIT999);
			CManager::GetSound()->Play(CSound::LABEL_HIT999);
			if (SceneCreate(pScene2D, S2D_PRIORITY + 1))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.05f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEX_OVER);
			}
			if (SceneCreate(pSceneAnim2D, S2D_PRIORITY))
			{//オーバー表記
				pSceneAnim2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 2, 10, 4, 0.0f, CScene2D::STATE_NORMAL, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_OVER2);
				pSceneAnim2D->BindDrawType(CScene::DRAW_TYPE_MULTIPLY);
			}
			for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
			{
				if (CManager::GetPlayer(nCount) != NULL)
				{
					//CManager::GetPlayer(nCount)->GetfLife()[0] = 0.0f;
				}
			}
			CManager::GetSound()->CountReset(CSound::LABEL_EXPLOSION001);
			CManager::GetSound()->Play(CSound::LABEL_EXPLOSION001);
			break;
		case 60:
			CManager::GetSound()->Play(CSound::LABEL_OVER000);
			break;
		case 1800:
			CManager::SetFade(CManager::MODE_PRACTICE, 0);
			break;
		}
		if (m_fCntState > 90 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || 
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) ||
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_PRACTICE, 0);
		}
		break;
	}
	
}
//=============================================================================
// ゲームの終了処理
//=============================================================================
void	CGame::Uninit(void)
{
	//BGMのストップ
	CSound *pSound = CManager::GetSound();
	pSound->Stop();

	for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
	{//全ポーズの破棄
		if (m_pScene2D[nCount] != NULL)
		{//生成されていれば削除
			m_pScene2D[nCount]->Uninit();
			m_pScene2D[nCount] = NULL;
		}
	}
}
//=============================================================================
// ゲームの状態変更処理
//=============================================================================
void	CGame::SetState(STATE state)
{
	CScene2D *pScene2D;

	if (m_state == STATE_NONE)
	{//通常状態なら
		m_state = state;
		switch (m_state)
		{
		case STATE_CLEAR:
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEXTURE_MAX);
			}
			break;
		case STATE_OVER:
			m_fCntState = 0.0f;
			break;
		}
	}
}
//=============================================================================
// ゲームのポーズ処理
//=============================================================================
void	CGame::Pause(void)
{
	if (CManager::GetFade()->GetState() == CFade::STATE_FADE_NONE)
	{
		CSound *pSound = CManager::GetSound();					//サウンドのポインタを取得
		CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
		CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
		CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得
		bool bSelect = false;
		bool bPause = true;

		if (!CScene::GetbPause())
		{//ポーズでない
			if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START))
			{//ポーズ起動
				CScene::GetbPause() = true;
				bSelect = true;
				m_nSelect = 3;

				if (SceneCreate(m_pScene2D[0], PAUSE_PRIORITY))
				{//画面暗くする
					m_pScene2D[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
						D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.65f), CScene2D::TEXTURE_MAX);
				}
				if (SceneCreate(m_pScene2D[1], PAUSE_PRIORITY))
				{//上セレクト　コンテニュー
					m_pScene2D[1]->Set(D3DXVECTOR3(GAME_PAUSE_LOGOX * 0.5f, GAME_PAUSE_LOGOY * 0.8f, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 0, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoPause);
				}
				if (SceneCreate(m_pScene2D[3], PAUSE_PRIORITY))
				{//上セレクト　コンテニュー
					m_pScene2D[3]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 1, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoPause);
				}
				if (SceneCreate(m_pScene2D[4], PAUSE_PRIORITY))
				{//下セレクト　リタイア
					m_pScene2D[4]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL * 2, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 2, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoPause);
				}
				if (SceneCreate(m_pScene2D[5], PAUSE_PRIORITY))
				{//マーカー
					(m_pScene2D[5]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - GAME_PAUSE_LOGOX, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 100.0f, CScene2D::STATE_FLASH2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Marker));
				}
			}
		}
		else if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START)
			|| pInputPad0->GetTrigger(INPUT_B) || pInputPad1->GetTrigger(INPUT_B))
		{//ポーズ止め
			bPause = false;
		}

		if (CScene::GetbPause())
		{//ポーズ中
			if (pInputKey->GetTPress(DIK_UP) || 
				pInputPad0->GetTPress(INPUT_UP) || pInputPad0->GetTPress(INPUT_LS_U) ||
				pInputPad1->GetTPress(INPUT_UP) || pInputPad1->GetTPress(INPUT_LS_U))
			{ m_nSelect = (m_nSelect - 3 + 1) % 2 + 3; bSelect = true; }

			if (pInputKey->GetTPress(DIK_DOWN) || 
				pInputPad0->GetTPress(INPUT_DOWN) || pInputPad0->GetTPress(INPUT_LS_D) ||
				pInputPad1->GetTPress(INPUT_DOWN) || pInputPad1->GetTPress(INPUT_LS_D))
			{ m_nSelect = (m_nSelect - 3 + 1) % 2 + 3;  bSelect = true; }

			if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A) || pInputPad1->GetTrigger(INPUT_A))
			{
				pSound->Play(CSound::LABEL_EXPLOSION001);
				if (m_nSelect == 3) { bPause = false; }
				else if (m_nSelect == 4) { CManager::SetFade(CManager::MODE_TITLE, 0); CScene::GetbPause() = false; return; }
			}

			if (!bPause)
			{//ポーズが終了した
				CScene::GetbPause() = false;

				for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
				{//全ポーズの破棄
					if (m_pScene2D[nCount] != NULL)
					{//生成されていれば削除
						m_pScene2D[nCount]->Uninit();
						m_pScene2D[nCount] = NULL;
					}
				}
			}
			else if (bSelect)
			{//状態の更新
				CSceneAnim2D *p2DAnim;
				pSound->Play(CSound::LABEL_HIT999);
				for (int nCount = 3; nCount <= 4; nCount++)
				{
					if (m_nSelect == nCount)
					{ //選択されている
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_BIG;
					}
					else
					{ //選択されてない
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_SMALL;
					}
				}
				m_pScene2D[5]->SetPosition(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(-GAME_PAUSE_LOGOX * 1.5f, 0.0f, 0.0f));
				//光エフェクト
				if (SceneCreate(p2DAnim, PAUSE_PRIORITY))
				{
					p2DAnim->Set(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 200.0f, D3DX_PI, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
						CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Slashing0);
					p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
				}
			}
		}
	}//フェード確認

}