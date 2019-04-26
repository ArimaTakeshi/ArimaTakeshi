//=============================================================================
//
// �Q�[������ [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�Z�[�u���[�h�̈�
#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Game.h"
#include "Practice.h"
#include "sound.h"
#include "Font.h"

//=============================================================================
// �Q�[���̏���������
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
	{//Save�@����
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
		wsprintf(&aStr[0], "%d.%d �b", nTime[0] / 60, nTime[0] % 60 / 6);
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 6 * 2, SCREEN_WIDTH / 5 * 3 + 200, SCREEN_HEIGHT }, D3DXCOLOR(0.98f, 1.0f, 0.02f, 1.0f), &aStr[0], 1, DT_RIGHT, -1, true, (bRankIn ? CFont::STATE_RANKIN : CFont::STATE_NONE));
	}
	if (SceneCreate(pFont, 6))
	{
		wsprintf(&aStr[0], "%d.%d �b", nTime[1] / 60, nTime[1] % 60 / 6);
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 6 * 4 + 50, SCREEN_WIDTH / 5 * 3 + 200, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), &aStr[0], 1, DT_RIGHT, -1, true, CFont::STATE_NONE);
	}

	pFile = fopen("data/TEXT/Time.bin", "wb");

	if (pFile != NULL)
	{//Save�@����
		fwrite(&nTime[0], sizeof(int), 1, pFile);
		fwrite(&nTime[1], sizeof(int), 1, pFile);
		fclose(pFile);
	}

	//BGM�̍Đ�
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::LABEL_RESULT000);
	return S_OK;
}
//=============================================================================
// �Q�[���̍X�V����
//=============================================================================
void CPractice::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//�W���C�p�b�h���l��

	m_fCntState += 1.0f;

	if (m_fCntState > 90.0f)
	{
		if ((pInputKey->GetAllTrigger() || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger()) && CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
		{//�Z���N�g��
			CManager::GetSound()->Play(CSound::LABEL_RETURN);
			CManager::SetFade(CManager::MODE_TITLE, 0);
		}
	}
}
//=============================================================================
// �Q�[���̏I������
//=============================================================================
void	CPractice::Uninit(void)
{
	//BGM�̃X�g�b�v
	CSound *pSound = CManager::GetSound();
	pSound->Stop();
}
