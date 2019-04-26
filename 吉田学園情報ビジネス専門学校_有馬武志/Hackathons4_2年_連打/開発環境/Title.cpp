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
	m_fCntState = 0.0f;	//���ԏ�����

						//�{�̘̂g����
	CScene::CreateAll(0, 8);
	CScene::CreateAll(1, 8);
	CScene::CreateAll(2, 8);
	CScene::CreateAll(3, 8);
	CScene::CreateAll(4, 8);
	CScene::CreateAll(5, 8);
	CScene::CreateAll(6, 8);
	CScene::CreateAll(7, 8);

	CScene2D *p2D;

	if (SceneCreate(p2D, S2D_PRIORITY))//�w�i
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Title);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//����1
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_FLOW0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.65f), CScene2D::TEXTURE_MAX);
		p2D->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
		p2D->BindTexture(C2D::Load(C2D::TEX_Cloud1));
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//����2
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_FLOW1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.025f), CScene2D::TEXTURE_MAX);
		p2D->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
		p2D->BindTexture(C2D::Load(C2D::TEX_Cloud2));
	}
	if (SceneCreate(m_p2DTitle, S2D_PRIORITY))
	{
		m_p2DTitle->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3.0f, 0.0f), SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_BIG, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_TitleLogo);
	}
	if (SceneCreate(m_p2DLogo, S2D_PRIORITY))//Press Any Button
	{
		m_p2DLogo->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10 * 8.5, 0.0f), SCREEN_WIDTH / 3, SCREEN_HEIGHT / 10, D3DX_PI, 0, 1, 1, 0.01f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_LogoPress);
		m_p2DLogo->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//��ڂ̎�`
		p2D->Set(D3DXVECTOR3(300.0f, 380.0f, 0.0f), 150.0f, 150.0f, D3DX_PI, 0, 1, 1, 0.009f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_Title000hand);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//��ڂ̎�`
		p2D->Set(D3DXVECTOR3(980.0f, 150.0f, 0.0f), 150.0f, 150.0f, D3DX_PI, 0, 1, 1, 0.007f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_Title001hand);
	}

	//BGM�̍Đ�
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::LABEL_TITLE000);

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

	if (m_fCntState <= 90.0f)
	{//�X�L�b�v
		if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger())
		{
			m_p2DLogo->GetState()[0] = CScene2D::STATE_FLASH;
			m_fCntState = 91.0f;
			m_p2DTitle->GetColor()[0].a = 1.0f;
			m_p2DLogo->GetColor()[0].a = 1.0f;
		}
	}
	if (m_fCntState == 91.0f)
	{
		m_p2DLogo->GetState()[0] = CScene2D::STATE_FLASH2;
		m_p2DLogo->GetfCntState()[0] = 100.0f;
	}
	if (m_fCntState > 90.0f)
	{
		if ((pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetAllTrigger() || pInputPad1->GetAllTrigger()) && CManager::GetFade()->GetState() == CFade::STATE_FADE_NONE)
		{//�Z���N�g��
			pSound->Play(CSound::LABEL_ENTER);
			CManager::SetFade(CManager::MODE_SELECT, 0);
		}
	}
}
//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void	CTitle::Uninit(void)
{

}