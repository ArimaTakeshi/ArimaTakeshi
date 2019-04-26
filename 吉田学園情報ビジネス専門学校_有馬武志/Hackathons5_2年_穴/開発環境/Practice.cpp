//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall突破
#include <stdio.h>				//セーブロードの為
#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Game.h"
#include "Practice.h"
#include "sound.h"
#include "Font.h"

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CPractice::Init(void)
{
	int  nTime[2] = { 0, 0 };
	bool bRankIn = false;
	FILE *pFile;
	CFont *pFont;
	char aStr[64];

	pFile = fopen("data/TEXT/Time.bin", "rb");

	if (pFile != NULL)
	{//Save　成功
		fread(&nTime[0], sizeof(int), 1, pFile);
		fread(&nTime[1], sizeof(int), 1, pFile);
		fclose(pFile);
	}


	if (nTime[0] <= nTime[1])
	{
		nTime[0] = nTime[1];
		bRankIn = true;
	}
	CScene2D *p2D;
	if (SceneCreate(p2D, S2D_PRIORITY))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Press);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 1, 0.0f), SCREEN_WIDTH / 4, 65.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Press);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 3 + 50.0f, 0.0f), SCREEN_WIDTH / 4, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Press);
	}

	if (SceneCreate(pFont, 6))
	{
		wsprintf(&aStr[0], "%d.%d 秒", nTime[0] / 60, nTime[0] % 60 / 6);
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 6 * 2, SCREEN_WIDTH / 5 * 3 + 200, SCREEN_HEIGHT }, D3DXCOLOR(0.98f, 1.0f, 0.02f, 1.0f), &aStr[0], 1, DT_RIGHT, -1, true, (bRankIn ? CFont::STATE_RANKIN : CFont::STATE_NONE));
	}
	if (SceneCreate(pFont, 6))
	{
		wsprintf(&aStr[0], "%d.%d 秒", nTime[1] / 60, nTime[1] % 60 / 6);
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 6 * 4 + 50, SCREEN_WIDTH / 5 * 3 + 200, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), &aStr[0], 1, DT_RIGHT, -1, true, CFont::STATE_NONE);
	}

	pFile = fopen("data/TEXT/Time.bin", "wb");

	if (pFile != NULL)
	{//Save　成功
		fwrite(&nTime[0], sizeof(int), 1, pFile);
		fwrite(&nTime[1], sizeof(int), 1, pFile);
		fclose(pFile);
	}

	//BGMの再生
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::LABEL_RESULT000);
	return S_OK;
}
//=============================================================================
// ゲームの更新処理
//=============================================================================
void CPractice::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	m_fCntState += 1.0f;

	if (m_fCntState > 90.0f)
	{
		if ((pInputKey->GetAllTrigger() || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger()) && CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
		{//セレクトへ
			CManager::GetSound()->Play(CSound::LABEL_RETURN);
			CManager::SetFade(CManager::MODE_TITLE, 0);
		}
	}
}
//=============================================================================
// ゲームの終了処理
//=============================================================================
void	CPractice::Uninit(void)
{
	//BGMのストップ
	CSound *pSound = CManager::GetSound();
	pSound->Stop();
}
