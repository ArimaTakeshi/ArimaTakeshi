//=============================================================================
//
// 2Dゲージ処理 [2DGage.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall突破
#include <stdio.h>				//セーブロードの為
#include "main.h"
#include "2DPolygon.h"
#include "2DGage.h"
#include "Player.h"
#include "Bullet.h"
#include "renderer.h"
#include "manager.h"
#include "Font.h"
#include "Number.h"
#include "Game.h"

#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int		CPlayer::m_nStage;		//ステージ番号
CFont	*CPlayer::m_pFont2;		//ステージ番号
int		CPlayer::m_nTime;		//ステージ番号

//==================================================================================================//
//    * ゲージのセット関数 *
//==================================================================================================//
void	CPlayer::Set(int nLane)
{
	m_fLane = (float)nLane;
	m_nInvincible = 0;
	CScene2D::Set(D3DXVECTOR3(100.0f, SCREEN_HEIGHT / 6 * (float)nLane, 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 3, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Player999);
	m_fLife = 5;
	m_fMaxLife = 5;
	m_nBomb = 1;
}
//=============================================================================
// ゲージの初期化処理
//=============================================================================
HRESULT  CPlayer::Init(void)
{
	CManager::GetPlayer0() = this;

	m_fLPlus = 0.0f;
	m_nWait = 0;
	m_fLane = 0.0f;
	CScene2D::Init();

	if (m_pLifeGage == NULL)
	{
		if (Create(m_pLifeGage))
		{
			m_pLifeGage->Set(D3DXVECTOR3(130.0f, 30.0f, 0.0f), SCREEN_WIDTH / 3, 20.0f, &m_fLife, &m_fMaxLife, true, C2DGage::STATE_LIFE);
		}
	}

	if (m_pIcon == NULL)
	{
		if (Create(m_pIcon))
		{
			m_pIcon->Set(D3DXVECTOR3(80.0f, 30.0f, 0.0f), 40.0f, 40.0f, D3DX_PI, 0, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_Icon);
		}
	}

	if (SceneCreate(m_pFont, 6))
	{
		m_pFont->Set(RECT{ SCREEN_WIDTH / 4 * 3, 10, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR(0.98f, 1.0f, 0.02f, 1.0f), "WAVE 1", 1, DT_RIGHT, -1, true, CFont::STATE_NONE);
	}

	CScene2D *p2D;
	if (SceneCreate(p2D, 5))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, 30.0f, 0.0f), SCREEN_WIDTH / 2, 30.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f), CScene2D::TEXTURE_MAX);
	}

	if (SceneCreate(m_pFont2, 6))
	{
		m_pFont2->Set(RECT{ SCREEN_WIDTH / 2 + 180, 10, SCREEN_WIDTH, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "経過時間：0.0秒", 1, DT_LEFT, -1, true, CFont::STATE_NONE);
	}

	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (m_pBomb[nCount] == NULL)
		{
			if (Create(m_pBomb[nCount]))
			{
				m_pBomb[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + nCount * 45.0f, 30.0f, 0.0f), 20.0f, 20.0f, D3DX_PI, 0, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEXTURE_MAX);
				m_pBomb[nCount]->BindTexture(CScene2D::Load(CScene2D::TEX_Bomb999));
				m_pBomb[nCount]->BindDrawType(CScene::DRAW_TYPE_NO);
			}
		}
		
	}
	m_pBomb[0]->BindDrawType(CScene::DRAW_TYPE_NORMAL);

	m_nTime = 0;
	return S_OK;
}
//=============================================================================
// ゲージの終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	FILE *pFile;

	int nTime = 0;
	pFile = fopen("data/TEXT/Time.bin", "rb");
	if (pFile != NULL)
	{//Save　成功
		fread(&nTime, sizeof(int), 1, pFile);
		fclose(pFile);
	}

	pFile = fopen("data/TEXT/Time.bin", "wb");
	if (pFile != NULL)
	{//Save　成功
		fwrite(&nTime, sizeof(int), 1, pFile);
		fwrite(&m_nTime, sizeof(int), 1, pFile);
		fclose(pFile);
	}

	if (m_pIcon != NULL) { m_pIcon->Uninit(); m_pIcon = NULL; }
	if (m_pLifeGage != NULL) { m_pLifeGage->Uninit(); m_pLifeGage = NULL; }
	CScene2D::Uninit() ;
	CManager::GetPlayer0() = NULL;
}

//=============================================================================
// ゲージの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CSound *pSound = CManager::GetSound();			//BGMの再生
	CInputKeyboard	*pInputKey = CManager::GetInputKey();			//キーボード情報獲得
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(m_nID);	//ジョイパッド情報獲得
	CBullet *pBullet;

	if (m_nWait > 0) { m_nWait--; m_fLane += m_fLPlus; }
	else
	{
		SetUV(0, 1, 3);

		if ((pInputKey->GetPress(DIK_UP) || pInputKey->GetPress(DIK_W) ||
			pInputPad->GetPress(INPUT_UP) || pInputPad->GetPress(INPUT_LS_U))
			&& m_fLane > 2.0f)
		{
			m_fLPlus = -0.1f; m_nWait = 10; SetUV(1, 1, 3);
			pSound->Play(CSound::LABEL_WALK);
		}
		else if ((pInputKey->GetPress(DIK_DOWN) || pInputKey->GetPress(DIK_S) ||
			pInputPad->GetPress(INPUT_DOWN) || pInputPad->GetPress(INPUT_LS_D))
			&& m_fLane < 4.0f)
		{
			m_fLPlus = 0.1f; m_nWait = 10; SetUV(2, 1, 3);
			pSound->Play(CSound::LABEL_WALK);
		}

		if (pInputPad->GetTrigger(INPUT_B)) { if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane, 0, 0); } 	pSound->Play(CSound::LABEL_SHOT);		}
		else if (pInputPad->GetTrigger(INPUT_A) && CManager::GetGame()->GetnWave() > 1)
		{
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane, 1, 0); }
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane + 0.2f, 1, 0); }
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane - 0.2f, 1, 0); }
			pSound->Play(CSound::LABEL_SHOT);
		}
		else if (pInputPad->GetTrigger(INPUT_Y) && CManager::GetGame()->GetnWave() > 2)
		{
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane, 2, 0); }
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane + 1, 2, 0); }
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane - 1, 2, 0); }
			pSound->Play(CSound::LABEL_SHOT);
		}
		else if (pInputPad->GetTrigger(INPUT_X) && CManager::GetGame()->GetnWave() > 3) 
		{ 
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane + 1, 3, 0); } pSound->Play(CSound::LABEL_SHOT);
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane - 1, 3, 0); } pSound->Play(CSound::LABEL_SHOT);
		}
		else if (pInputPad->GetTrigger(INPUT_L1) && m_nBomb > 0)
		{
			m_nBomb--;
			m_pBomb[m_nBomb]->BindDrawType(CScene::DRAW_TYPE_NO);
			if (SceneCreate(pBullet, 5)) { pBullet->Set(m_fLane, 4, 1); } pSound->Play(CSound::LABEL_SHOT);
		}
	}

	SetPosition(D3DXVECTOR3(100.0f, SCREEN_HEIGHT / 6 * m_fLane, 0.0f));

	if (m_pLifeGage != NULL) { m_pLifeGage->Update(); }

	if (m_fLife > 0.0f) { m_nTime++; }
	
	if (m_nInvincible > 0) { m_nInvincible--; }

	D3DXCOLOR col = GetColor()[0];
	col += (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) - col) * 0.05f;
	SetColor(col);
	char aStr[64];
	wsprintf(&aStr[0], "経過時間：%d.%d秒", m_nTime / 60, m_nTime % 60 / 6);
	if (m_pFont2 != NULL) { m_pFont2->SetFont(&aStr[0], -1); }
}
//=============================================================================
// ゲージの更新処理
//=============================================================================
void	CPlayer::DrawUI(void)
{
	if (m_pLifeGage != NULL) { m_pLifeGage->Draw(); }
	if (m_pIcon != NULL) { m_pIcon->Draw(); }
	for (int nCount = 0; nCount < 3; nCount++)
	{
		if (m_pBomb[nCount] != NULL)
		{
			m_pBomb[nCount]->Draw();
		}

	}
}