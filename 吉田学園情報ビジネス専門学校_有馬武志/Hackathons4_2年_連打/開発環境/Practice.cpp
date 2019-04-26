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
#include "SceneBullet.h"
#include "ScenePlayer.h"
#include "scene.h"
#include "dungeon.h"
#include "Game.h"
#include "Practice.h"
#include "sound.h"
#include "Font.h"

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CPractice::Init(void)
{
	CScene::CreateAll(0, 64);
	CScene::CreateAll(1, 64);
	CScene::CreateAll(2, 16);
	CScene::CreateAll(3, 128);
	CScene::CreateAll(4, 128);
	CScene::CreateAll(5, 1280);
	CScene::CreateAll(6, 128);
	CScene::CreateAll(7, 32);

	int  nTime[2] = {0, 0};
	bool bRankIn = false;
	CFont *pFont;
	char aStr[64];
	FILE *pFile;

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

	if (SceneCreate(pFont, 6))
	{
		wsprintf(&aStr[0], "%d.%d 秒", nTime[0] / 60, nTime[0] % 60 / 6);
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 6 * 2, SCREEN_WIDTH / 5 * 3 + 200, SCREEN_HEIGHT }, D3DXCOLOR(0.98f, 1.0f, 0.02f, 1.0f), &aStr[0], 2, DT_RIGHT, -1, true, (bRankIn ? CFont::STATE_RANKIN : CFont::STATE_NONE));
	}
	if (SceneCreate(pFont, 6))
	{
		wsprintf(&aStr[0], "%d.%d 秒", nTime[1] / 60, nTime[1] % 60 / 6);
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 6 * 4 + 50, SCREEN_WIDTH / 5 * 3 + 200, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), &aStr[0], 3, DT_RIGHT, -1, true, CFont::STATE_NONE);
	}

	CScene2D *p2D;
	if(SceneCreate(p2D, 3))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Over999);
	}
	if (SceneCreate(p2D, 5))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 1, 0.0f), SCREEN_WIDTH / 4, 65.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Result001);
	}
	if (SceneCreate(p2D, 5))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 3 + 50.0f, 0.0f), SCREEN_WIDTH / 4, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_Result002);
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
	CInputKeyboard	*pInputKey = CManager::GetInputKey();			//キーボード情報獲得
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得

	if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(INPUT_A) || pInputPad->GetTrigger(INPUT_A))
	{
		CManager::SetFade(CManager::MODE_TITLE, 0);
	}

}
//=============================================================================
// ゲームの終了処理
//=============================================================================
void	CPractice::Uninit(void)
{
	//BGMの再生
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::LABEL_RESULT000);
}
