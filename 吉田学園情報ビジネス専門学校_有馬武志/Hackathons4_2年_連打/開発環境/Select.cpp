//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"Font.h"
#include "manager.h"
#include "Select.h"
#include "Game.h"
#include "sound.h"

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
HRESULT CSelect::Init(void)
{
	CScene::CreateAll(0, 8);
	CScene::CreateAll(1, 8);
	CScene::CreateAll(2, 8);
	CScene::CreateAll(3, 32);
	CScene::CreateAll(4, 8);
	CScene::CreateAll(5, 8);
	CScene::CreateAll(6, 32);
	CScene::CreateAll(7, 8);

	CScene2D *p2D;

	//�w�i
	if (SceneCreate(p2D, S2D_PRIORITY))
	 { p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_T999); }
	if (SceneCreate(p2D, S2D_PRIORITY))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 4 * 3, SCREEN_HEIGHT  - 80.0f, 0.0f), SCREEN_WIDTH / 5, SCREEN_HEIGHT / 15, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_A999);
	}

	return S_OK;
}
//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CSelect::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//�W���C�p�b�h���l��

	if (CManager::GetFade()->GetState() == CFade::STATE_FADE_NONE)
	{
		if ((pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A)) && CManager::GetFade()->GetState() == CFade::STATE_FADE_NONE)
		{//�Z���N�g��
			pSound->Play(CSound::LABEL_ENTER);
			CManager::SetFade(CManager::MODE_GAME, 0);
		}
	}//�t�F�[�h���łȂ�
}
//=============================================================================
// �Z���N�g�̏I������
//=============================================================================
void	CSelect::Uninit(void)
{
	//BGM�̍Đ�
	CSound *pSound = CManager::GetSound();
	pSound->Stop(CSound::LABEL_TITLE000);
}