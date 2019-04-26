//=============================================================================
//
// タイトル処理 [Title.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "sound.h"
#include "Title.h"

//=============================================================================
// タイトルの初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_fCntState = 0.0f;	//時間初期化

						//本体の枠生成
	CScene::CreateAll(0, 8);
	CScene::CreateAll(1, 8);
	CScene::CreateAll(2, 8);
	CScene::CreateAll(3, 8);
	CScene::CreateAll(4, 8);
	CScene::CreateAll(5, 8);
	CScene::CreateAll(6, 8);
	CScene::CreateAll(7, 8);

	CScene2D *p2D;

	if (SceneCreate(p2D, S2D_PRIORITY))//背景
	{
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Title);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//砂埃1
		p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_FLOW0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.65f), CScene2D::TEXTURE_MAX);
		p2D->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
		p2D->BindTexture(C2D::Load(C2D::TEX_Cloud1));
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//砂埃2
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
	{//一個目の手形
		p2D->Set(D3DXVECTOR3(300.0f, 380.0f, 0.0f), 150.0f, 150.0f, D3DX_PI, 0, 1, 1, 0.009f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_Title000hand);
	}
	if (SceneCreate(p2D, S2D_PRIORITY))
	{//二個目の手形
		p2D->Set(D3DXVECTOR3(980.0f, 150.0f, 0.0f), 150.0f, 150.0f, D3DX_PI, 0, 1, 1, 0.007f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_Title001hand);
	}

	//BGMの再生
	CSound *pSound = CManager::GetSound();
	pSound->Play(CSound::LABEL_TITLE000);

	return S_OK;
}
//=============================================================================
// タイトルの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	m_fCntState += 1.0f;

	if (m_fCntState <= 90.0f)
	{//スキップ
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
		{//セレクトへ
			pSound->Play(CSound::LABEL_ENTER);
			CManager::SetFade(CManager::MODE_SELECT, 0);
		}
	}
}
//=============================================================================
// タイトルの終了処理
//=============================================================================
void	CTitle::Uninit(void)
{

}