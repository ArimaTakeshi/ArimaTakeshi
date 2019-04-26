//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "sound.h"
#include "Title.h"

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init(void)
{
	CScene2D *p2D;

	if (SceneCreate(p2D, 6))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f,
			CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Title);
	}
	if (SceneCreate(p2D, 6))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 2, 0.5f,
			CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 0.2f, 0.0f, 0.75f), CScene::TEX_Fog001);
		p2D->BindDrawType(CScene::DRAW_TYPE_ADD);
	}
	if (SceneCreate(p2D, 6))
	{//�v���X�G�j�[�{�^��
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 - 50.0f, 0.0f), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 12, D3DX_PI, 0, 1, 1, 0.05f,
			CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene::TEX_Press);
	}
	if (SceneCreate(p2D, 6))
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 3, 2, 2, 0.5f,
			CScene2D::STATE_FLOW1, D3DXCOLOR(1.0f, 0.2f, 0.0f, 1.0f), CScene::TEX_Fog000);
		p2D->BindDrawType(CScene::DRAW_TYPE_ADD);
	}
	m_fCntState = 0.0f;	//���ԏ�����

	//BGM�̍Đ�
	CManager::GetSound()->Play(CSound::LABEL_TITLE000);
	return S_OK;
}
//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
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
			CManager::SetFade(CManager::MODE_SELECT, 0);
		}
	}
}
//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void	CTitle::Uninit(void)
{
	//BGM�̃X�g�b�v
	CManager::GetSound()->Stop(CSound::LABEL_TITLE000);

}