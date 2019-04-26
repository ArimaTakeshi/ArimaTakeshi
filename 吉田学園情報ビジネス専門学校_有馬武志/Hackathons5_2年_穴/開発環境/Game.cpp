//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Scene.h"
#include"Scene2D.h"
#include "manager.h"
#include "scene.h"
#include "Effect.h"
#include "player.h"
#include "SceneModel.h"
#include "mesh.h"
#include "dungeon.h"
#include "Font.h"

#include "Game.h"
#include "camera.h"
#include "light.h"
#include "wind.h"
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
	m_state = STATE_NONE;
	m_fCntState = 0.0f;

	CMotion::Load();
	CCharacter::Load();
	m_nQuiz = rand() % 6;
	switch (m_nQuiz)
	{
	case 0: m_nAnswer = 1; strcpy(&m_char[0], "Answer  B：スノーボード"); break;
	case 1: m_nAnswer = 0; strcpy(&m_char[0], "Answer  A：いぬ"); break;
	case 2: m_nAnswer = 2; strcpy(&m_char[0], "Answer  X：田中章"); break;
	case 3: m_nAnswer = 1; strcpy(&m_char[0], "Answer  B：大乱闘スマッシュブラザーズ SPECIAL"); break;
	case 4: m_nAnswer = 0; strcpy(&m_char[0], "Answer  A：TAKASHI"); break;
	case 5: m_nAnswer = 1; strcpy(&m_char[0], "Answer  X：スーパースターソルジャー"); break;
	}
	CLight *pLight;			Create(pLight);		//ライトの生成
	CWind_Manager *pWind;	Create(pWind);		//風の生成
	bool	&bDuo = CManager::GetbDuo();
	bDuo = false;
	CPlayer *pChar;
	//CSceneAnim2D *p2D;
	CCamera_Play *pCamera;

	//if (SceneCreate(p2D, CHAR_PRIORITY))
	//{//後ろ背景
	//	p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 10, 2, 0.0f,
	//		CScene2D::STATE_ZCLEAR, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_G_EXPLOSION);
	//}
	for (int nCount = 0; nCount < (bDuo ? 2 : 1); nCount++)
	{//キャラの生成
		pCamera = CCamera_Manager::Create_Play(nCount);
		pCamera->GetChar()->SetViewport(0, nCount * 360, 1280, (bDuo ? 360 : 720));
		pCamera->GetObj()->SetViewport(0, nCount * 360, 1280, (bDuo ? 360 : 360));
		pCamera->GetObj()->GetposV() = D3DXVECTOR3(1130.0f, 100.0f, 20.0f + nCount * 1000.0f);
		pCamera->GetObj()->GetposR() = D3DXVECTOR3(1130.0f, 0.0f, 19.0f + nCount * 1000.0f);

		if (SceneCreate(pChar, CHAR_PRIORITY))
		{
			pChar->Set(D3DXVECTOR3(0.0f, 0.0f, -50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_BOX_Sword);
		}
	}

	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY))
	{
		pEnemy->Set(D3DXVECTOR3(-500.0f, 20.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_BOX_Stick, CEnemy::TYPE_NONE, 0);
	}

	CSceneModel *pModel;
	if (SceneCreate(pModel, 0))
	{
		pModel->Set(D3DXVECTOR3(0.0f, 65.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_Frame, CScene::DRAW_TYPE_NORMAL, false);
	}
	if (SceneCreate(pModel, 0))
	{
		pModel->Set(D3DXVECTOR3(0.0f, -15.0f, 76.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_Room, CScene::DRAW_TYPE_NORMAL, false);
	}
	if (SceneCreate(pModel, 0)) { pModel->Set(D3DXVECTOR3(0.0f, 65.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_FrameV, CScene::DRAW_TYPE_NORMAL, false); }
	if (SceneCreate(pModel, 0)) { pModel->Set(D3DXVECTOR3(26.0f, 65.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_FrameV, CScene::DRAW_TYPE_NORMAL, false); }
	if (SceneCreate(pModel, 0)) { pModel->Set(D3DXVECTOR3(-26.0f, 65.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_FrameV, CScene::DRAW_TYPE_NORMAL, false); }

	if (SceneCreate(pModel, 0)) { pModel->Set(D3DXVECTOR3(0.0f, 65.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_FrameC, CScene::DRAW_TYPE_NORMAL, false); }
	if (SceneCreate(pModel, 0)) { pModel->Set(D3DXVECTOR3(0.0f, 91.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_FrameC, CScene::DRAW_TYPE_NORMAL, false); }
	if (SceneCreate(pModel, 0)) { pModel->Set(D3DXVECTOR3(0.0f, 39.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_FrameC, CScene::DRAW_TYPE_NORMAL, false); }

	int nCountF = 0;
	for (int nCntY = 0; nCntY < 4; nCntY++)
	{
		for (int nCntX = 0; nCntX < 4; nCntX++)
		{
			if (SceneCreate(m_p3D[nCountF], 2))
			{
				m_p3D[nCountF]->Set(D3DXVECTOR3(-37.0f, 28.0f, 100.0f) + D3DXVECTOR3(nCntX * 25.0f, nCntY * 25.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(12.0f, 12.0f, 0.0f), CScene::TEX_Paper, 0, 1, 1, false, CScene::DRAW_TYPE_NORMAL);
			}
			nCountF++;
		}
	}
	CScene3D *p3DA;
	if (SceneCreate(p3DA, 0))
	{
		p3DA->Set(D3DXVECTOR3(0.0f, 65.0f, 101.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),
			CScene::TEX_Quiz, m_nQuiz, 6, 1, false, CScene::DRAW_TYPE_NORMAL);
	}

	//CDungeon *pDungeon;
	//if (SceneCreate(pDungeon, DUNGEON_PRIORYITY)) { pDungeon->SetDungeon_Boss(); }
	//CDungeon::SetDungeon_Boss(0);

	//CMesh *pMesh;
	//if (SceneCreate(pMesh, 0))
	//{
	//	pMesh->Set(CMesh::TYPE_CEILING, D3DXVECTOR3(0.0f, 50.0f, 0.0f), 50, 50);
	//}
	//if (SceneCreate(pMesh, 0))
	//{
	//	pMesh->Set(CMesh::TYPE_WALL, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50, 50);
	//}
	CManager::GetSound()->Play(CSound::LABEL_FIELD000);
	return S_OK;
}
//=============================================================================
// ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得

	//if (pInputKey->GetTrigger(DIK_C))
	//{
	//	CDungeon::SetDungeon_Rand(0);
	//}
	if (pInputKey->GetPress(DIK_2))
	{
		CManager::SetFade(CManager::MODE_PRACTICE, 0);
	}
	if (pInputKey->GetPress(DIK_1))
	{
		CManager::SetFade(CManager::MODE_GAME, 0);
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
			CScene2D *p2D;
			if (SceneCreate(p2D, 6))
			{
				p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.01f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene::TEX_CLEAR);
			}
			break;
		case 1800: CManager::SetFade(CManager::MODE_TITLE, 0); break;
		}
		if (m_fCntState > 180 && (
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
		case 2:
			break;
		case 60:
			CManager::GetSound()->Play(CSound::LABEL_OVER000);
			CScene2D *p2D;
			if (SceneCreate(p2D, 6))
			{
				p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.01f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene::TEX_OVER);
			}
			CFont *pFont;
			if (SceneCreate(pFont, 6))
			{
				pFont->Set(RECT{ 100, 350, SCREEN_WIDTH - 100, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), &m_char[0], 2, DT_CENTER, 0, true, CFont::STATE_NONE);
			}
			break;
		case 1800:
			CManager::SetFade(CManager::MODE_TITLE, 0);
			break;
		}
		if (m_fCntState > 90 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || 
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) ||
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_TITLE, 0);
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

	CManager::GetCamera()->Uninit();
	CManager::GetLight()->Uninit();
}
//=============================================================================
// ゲームの状態変更処理
//=============================================================================
void	CGame::SetState(STATE state)
{
	CScene2D *pScene2D;
	CManager::GetSound()->Stop(CSound::LABEL_FIELD000);

	if (m_state == STATE_NONE)
	{//通常状態なら
		m_state = state;
		switch (m_state)
		{
		case STATE_CLEAR:
			CManager::GetSound()->Play(CSound::LABEL_Correct);
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		case STATE_OVER:
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}

			break;
		}
	}
}
//=============================================================================
// ゲームのポーズ処理
//=============================================================================
void	CGame::Pause(void)
{
	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
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
				CManager::GetSound()->Play(CSound::LABEL_GUARD);
				CScene::GetbPause() = true;
				bSelect = true;
				m_nSelect = 3;

				if (SceneCreate(m_pScene2D[0], PAUSE_PRIORITY))
				{//画面暗くする
					m_pScene2D[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
						D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.65f), CScene::TEX_MAX);
				}
				if (SceneCreate(m_pScene2D[1], PAUSE_PRIORITY))
				{//上チュートリアル
					m_pScene2D[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, PAUSE_LENGTH, 0.0f), SCREEN_WIDTH / 2, PAUSE_LENGTH,
						D3DX_PI, 0, 1, 2, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX);
				}
				if (SceneCreate(m_pScene2D[2], PAUSE_PRIORITY))
				{//下チュートリアル
					m_pScene2D[2]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PAUSE_LENGTH, 0.0f), SCREEN_WIDTH / 2, PAUSE_LENGTH,
						D3DX_PI, 1, 1, 2, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX);
				}
				if (SceneCreate(m_pScene2D[3], PAUSE_PRIORITY))
				{//上セレクト　コンテニュー
					m_pScene2D[3]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 0, 1, 2, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[4], PAUSE_PRIORITY))
				{//下セレクト　リタイア
					m_pScene2D[4]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 1, 1, 2, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[5], PAUSE_PRIORITY))
				{//マーカー
					(m_pScene2D[5]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - GAME_PAUSE_LOGOX, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 100.0f, CScene2D::STATE_FLASH2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PHand));
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
				CManager::GetSound()->Play(CSound::LABEL_RETURN);
				if (m_nSelect == 3) { bPause = false; }
				else if (m_nSelect == 4) { CManager::SetFade(CManager::MODE_TITLE, 0); CScene::GetbPause() = false; return; }
			}

			if (!bPause)
			{//ポーズが終了した
				CScene::GetbPause() = false;
				CManager::GetSound()->Play(CSound::LABEL_GUARD);

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
				CManager::GetSound()->Play(CSound::LABEL_GUARD);
				//CSceneAnim2D *p2DAnim;
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
				////光エフェクト
				//if (SceneCreate(p2DAnim, PAUSE_PRIORITY))
				//{
				//	p2DAnim->Set(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 200.0f, D3DX_PI, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
				//		CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX);
				//	p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
				//}
			}
		}
	}//フェード確認

}