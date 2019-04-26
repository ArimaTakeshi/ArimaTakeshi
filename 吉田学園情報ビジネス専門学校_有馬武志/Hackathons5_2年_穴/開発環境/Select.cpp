//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"Font.h"
#include"camera.h"
#include "manager.h"
#include "Select.h"
#include "Game.h"
#include "sound.h"

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
HRESULT CSelect::Init(void)
{
	CCamera_Char *pCamera = CCamera_Manager::Create_Event();
	pCamera->SetViewport(0, 0, 1280, 720);
	pCamera->GetposR() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pCamera->GetposV() = D3DXVECTOR3(0.0f, 75.0f, 250.0f);

	CScene2D *p2D;
	if (SceneCreate(p2D, 0))
	{//背景
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 1, 0.05f,
			CScene2D::STATE_BG_FLOW, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Select);
	}

	if (m_pUI == NULL) { SceneCreate(m_pUI, 1); };
	//BGMの再生
	CManager::GetSound()->Play(CSound::LABEL_PRACTICE000);

	return S_OK;
}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CSelect::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	{
		if ((pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger()) && CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
		{//セレクトへ
			
		}
	}//フェード中でない
}
//=============================================================================
// セレクトの終了処理
//=============================================================================
void	CSelect::Uninit(void)
{
	if (m_pUI != NULL) { m_pUI->Uninit(); m_pUI = NULL; }
	//BGMのストップ
	CManager::GetSound()->Stop(CSound::LABEL_PRACTICE000);
}
//=============================================================================
// セレクトUIの初期化処理
//=============================================================================
HRESULT CSelect_UI::Init(void)
{
	m_p3D = NULL;
	SetSelect(SELECT_FIRST);

	for (int nCount = 0; nCount < 2; nCount++)
	{
		if (SceneCreate(m_p2D[nCount], S2D_PRIORITY))
		{
			m_p2D[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.15f + (SCREEN_WIDTH * 0.7f) * nCount, SCREEN_HEIGHT * 0.85f, 0.0f), 200.0f, 100.0f, D3DX_PI * -0.5f + D3DX_PI * nCount
				, 0, 10, 1, 15, 0.0f, CScene2D::STATE_NORMAL, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Arrow);
			m_p2D[nCount]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
		}
	}
	
	if (SceneCreate(m_pScene2D, S2D_PRIORITY))
	{
		m_pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100.0f, 0.0f), 350.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_FLASH,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PressA);
	}

	return S_OK;
}
//=============================================================================
// セレクトUIの初期化処理
//=============================================================================
void CSelect_UI::Uninit(void)
{
	if (m_p3D != NULL)
	{
		for (int nCount = 0; nCount < m_nMax3D; nCount++) { m_p3D[nCount]->Uninit(); }
		m_p3D = NULL; m_nMax3D = 0;
	}
	CScene::Uninit();
}
//=============================================================================
// セレクトUIの初期化処理
//=============================================================================
void CSelect_UI::Update(void)
{
	C3D		*p3D;
	int		nSelect = 0;
	float	fAngle, fCol;
	float	fMaxAngle = D3DX_PI * 2.0f / m_nMax3D;
	bool	bSelect = false;
	CSound *pSound = CManager::GetSound();					//サウンドのポインタを取得
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	if (pInputKey->GetTPress(DIK_LEFT) ||
		pInputPad0->GetTPress(INPUT_LEFT) || pInputPad0->GetTPress(INPUT_LS_L) ||
		pInputPad1->GetTPress(INPUT_LEFT) || pInputPad1->GetTPress(INPUT_LS_L))
	{//左へ
		if((int)((m_fGAngle * 1.05f) / ((D3DX_PI * 2.0f) / m_nMax3D)) != 0){ nSelect = -1; bSelect = true; }
	}

	if (pInputKey->GetTPress(DIK_RIGHT) ||
		pInputPad0->GetTPress(INPUT_RIGHT) || pInputPad0->GetTPress(INPUT_LS_R) ||
		pInputPad1->GetTPress(INPUT_RIGHT) || pInputPad1->GetTPress(INPUT_LS_R))
	{//右へ
		if ((int)((m_fGAngle * 1.05f) / ((D3DX_PI * 2.0f) / m_nMax3D)) != m_nMax3D - 1) { nSelect = 1; bSelect = true; }
	}

	if (bSelect)
	{//選択肢を変更された
		CManager::GetSound()->Play(CSound::LABEL_GUARD);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (SCREEN_WIDTH * 0.35f) * -nSelect, SCREEN_HEIGHT * 0.5f, 0.0f);
		//pos += D3DXVECTOR3((rand() % 200 + 1) * 0.01f - 1.0f, (rand() % 200 + 1) * 0.01f - 1.0f, 0.0f) * 100.0f;

		m_fGAngle += nSelect * fMaxAngle;
		if (m_fGAngle < 0.0f) { m_fGAngle = 0.0f; }
		if (m_fGAngle >= D3DX_PI * 2.0f) { m_fGAngle = D3DX_PI * 2.0f - fMaxAngle; }
	}
	nSelect = (int)((m_fGAngle * 1.05f) / ((D3DX_PI * 2.0f) / m_nMax3D));

	m_fAngle += (m_fGAngle - m_fAngle) * 0.1f;	//角度を目標へ
	for (int nCount = 0; nCount < m_nMax3D; nCount++)
	{//選択肢ポリゴンを回転させる
		fAngle = fMaxAngle * -m_p3D[nCount]->GetRotation().y + m_fAngle;
		m_p3D[nCount]->GetPosition() = D3DXVECTOR3(sinf(fAngle), 0.3f, cosf(fAngle)) * 115.0f;
		fCol = 1.0f + (m_p3D[nCount]->GetPosition().z - 100.0f) * 0.0025f;
		m_p3D[nCount]->SetColor(D3DXCOLOR(fCol, fCol, fCol, 1.0f));
	}

	//条件で矢印を隠す
	if (nSelect == 0) { m_p2D[0]->BindDrawType(CScene::DRAW_TYPE_NO); }
	else { m_p2D[0]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT); }
	if (nSelect == m_nMax3D - 1) 
	{ 
		m_pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_p2D[1]->BindDrawType(CScene::DRAW_TYPE_NO);
	}
	else 
	{
		m_pScene2D->BindDrawType(CScene::DRAW_TYPE_NO);
		m_p2D[1]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
	}

	//ソート
	for (int nCount = 1; nCount < m_nMax3D; nCount++)
	{
		for (int nCount2 = 0; nCount2 < nCount; nCount2++)
		{
			if (m_p3D[nCount]->GetPosition().z < m_p3D[nCount2]->GetPosition().z)
			{//距離が遠いほうが先に
				p3D = m_p3D[nCount];
				m_p3D[nCount] = m_p3D[nCount2];
				m_p3D[nCount2] = p3D;
			}
		}
	}

	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE && nSelect == m_nMax3D - 1)
	{
		if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A) || pInputPad1->GetTrigger(INPUT_A))
		{
			CManager::GetSound()->Play(CSound::LABEL_RETURN);
			CManager::SetFade(CManager::MODE_GAME, 0);
		}
	}
	if (pInputKey->GetTrigger(DIK_BACKSPACE) || pInputPad0->GetTrigger(INPUT_B) || pInputPad1->GetTrigger(INPUT_B))
	{
		CManager::GetSound()->Play(CSound::LABEL_RETURN);
		CManager::SetFade(CManager::MODE_TITLE, 0);
	}
}
//=============================================================================
// セレクトUIの初期化処理
//=============================================================================
void CSelect_UI::Draw(void)
{
	if (m_p3D != NULL)
	{
		for (int nCount = 0; nCount < m_nMax3D; nCount++) { m_p3D[nCount]->Draw(); }
	}
}
//=============================================================================
// セレクトの設定処理
//=============================================================================
void	CSelect_UI::SetSelect(SELECT select)
{
	float fMaxAngle = D3DX_PI * 2.0f;
	m_Select = select;

	if (m_p3D != NULL) 
	{ 
		for (int nCount = 0; nCount < m_nMax3D; nCount++) { m_p3D[nCount]->Uninit(); }
		m_p3D = NULL; m_nMax3D = 0;
	}

	m_fAngle = 0.0f;
	m_fGAngle = 0.0f;
	if (m_p3D == NULL)
	{
		switch (select)
		{
		case SELECT_FIRST:
			m_nMax3D = 4;
			m_p3D = new C3D*[m_nMax3D];
			fMaxAngle /= (float)m_nMax3D;
			for (int nCount = 0; nCount < m_nMax3D; nCount++)
			{ 
				m_p3D[nCount] = new C3D;
				m_p3D[nCount]->Init();
				m_p3D[nCount]->Set(D3DXVECTOR3(sinf(fMaxAngle * nCount), 0.0f, cosf(fMaxAngle * nCount)) * 100.0f, D3DXVECTOR3(0.0f, (float)nCount, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(60.0f, 60.0f, 0.0f), nCount, 4, 1, CScene::DRAW_TYPE_NORMAL, CScene::TEX_Select0, true);
			}

			break;
		}
	}
}