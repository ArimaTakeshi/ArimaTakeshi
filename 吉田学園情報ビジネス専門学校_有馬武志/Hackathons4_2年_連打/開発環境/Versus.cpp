//=============================================================================
//
// �o�[�T�X�̏��� [Versus.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "SceneBullet.h"
#include "ScenePlayer.h"
#include "scene.h"
#include "dungeon.h"
#include "Versus.h"
#include "vsSelect.h"
#include "sound.h"

//=============================================================================
// �o�[�T�X�̏���������
//=============================================================================
HRESULT CVersus::Init(void)
{
	CScene::CreateAll(0, 64);
	CScene::CreateAll(1, 64);
	CScene::CreateAll(2, 16);
	CScene::CreateAll(3, 128);
	CScene::CreateAll(4, 128);
	CScene::CreateAll(5, 1280);
	CScene::CreateAll(6, 128);
	CScene::CreateAll(7, 32);

	CSceneBullet::Load(CSceneBullet::TEX_BULLET);
	CSceneBullet::Load(CSceneBullet::TEX_BULLET_S);
	CScene3D::Load(CScene3D::TEX_MARKER);
	CSceneAnim3D::Load(CSceneAnim3D::TEX_EXPLOSION);
	CSceneAnim3D::Load(CSceneAnim3D::TEX_FIRE_EXPLOSION);

	CScenePlayer::GetbShop() = false;

	int nStage = 0;
	CvsSelect::LoadVS(nStage);

	m_state = STATE_NONE;
	SetState(STATE_START);

	CScenePlayer::GetnStage() = 1;
	CDungeon *pDungeon = NULL;
	if (SceneCreate(pDungeon, DUNGEON_PRIORYITY))
	{
		pDungeon->SetVersus(nStage);
	}

	CScene2D::Load(CScene2D::TEXTURE_Slashing0);
	CScene2D::Load(CScene2D::TEXTURE_LogoPause);
	CScene2D::Load(CScene2D::TEXTURE_ITEM_TUTORIAL);
	return S_OK;
}
//=============================================================================
// �o�[�T�X�̍X�V����
//=============================================================================
void CVersus::Update(void)
{
	switch (m_state)
	{
	case STATE_START:
		UpdateStart();	//�J�n�̍X�V
		break;
	case STATE_NONE:
		Pause();	//�|�[�Y�̍X�V
		break;
	case STATE_P1_WIN:
	case STATE_P2_WIN:
	case STATE_DRAW:
		UpdateEnd();
		break;

	case STATE_TIME_UP:
		break;


	}

	bool bDead[2] = {false, false};

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (CManager::GetPlayer(nCount)->GetfLife()[0] == 0.0f)
		{//1P�����񂾁I
			bDead[nCount] = true;
		}
	}

	if (bDead[0] && bDead[1]) { SetState(STATE_DRAW); }
	else if (bDead[0]) { SetState(STATE_P2_WIN); }
	else if (bDead[1]) { SetState(STATE_P1_WIN); }
}
//=============================================================================
// �o�[�T�X�̏I������
//=============================================================================
void	CVersus::Uninit(void)
{
	//BGM�̃X�g�b�v
	CSound *pSound = CManager::GetSound();
	pSound->Stop();

	for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
	{//�S�|�[�Y�̔j��
		if (m_pScene2D[nCount] != NULL)
		{//��������Ă���΍폜
			m_pScene2D[nCount]->Uninit();
			m_pScene2D[nCount] = NULL;
		}
	}
}
//=============================================================================
// �o�[�T�X�̏�ԕύX����
//=============================================================================
void	CVersus::SetState(STATE state)
{
	if (m_state == STATE_NONE)
	{//�ʏ��ԂȂ�
		m_state = state;
		m_fCntState = 0.0f;
		switch (m_state)
		{
		case STATE_P1_WIN:
			break;

		case STATE_P2_WIN:
			break;
		case STATE_DRAW:
			break;
		case STATE_TIME_UP:
			break;
		}
	}
}
//=============================================================================
// �o�[�T�X�̊J�n�O��������
//=============================================================================
void	CVersus::UpdateStart()
{
	CSceneAnim2D *p2DAnim;

	m_fCntState += 1.0f;
	switch ((int)m_fCntState)
	{
	case 1:
		//VS���S���������\�� * 2
		if (SceneCreate(m_p2DStart[0], 6))
		{//BG�̐���
			m_p2DStart[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT / 2, 0.0f), 100.0f, 200.0f, D3DX_PI, 0, 2, 1, 0.0075f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_MAX);
			m_p2DStart[0]->BindTexture(C2D::Load(C2D::TEX_Versus));
		}
		if (SceneCreate(m_p2DStart[1], 6))
		{//BG�̐���
			m_p2DStart[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, SCREEN_HEIGHT / 2, 0.0f), 100.0f, 200.0f, D3DX_PI, 1, 2, 1, 0.0075f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_MAX);
			m_p2DStart[1]->BindTexture(C2D::Load(C2D::TEX_Versus));
		}
		CScene::GetnCntStart() = 6;
		break;
	case 240:
		//VS���S�c�ɐ؂��
		m_p2DStart[0]->GetState()[0] = CScene2D::STATE_SLIDE_OUT1;
		m_p2DStart[0]->GetfCntState()[0] = 0.05f;
		m_p2DStart[1]->GetState()[0] = CScene2D::STATE_SLIDE_OUT2;
		m_p2DStart[1]->GetfCntState()[0] = 0.05f;
		//�a���A�j���[�V����
		//���G�t�F�N�g
		if (SceneCreate(p2DAnim, S2D_PRIORITY))
		{
			p2DAnim->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH * 1.25f, SCREEN_HEIGHT * 1.25f, D3DX_PI * 0.5f, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
				CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Slashing0);
			p2DAnim->BindDrawType(CScene::DRAW_TYPE_ADD);
		}
		m_state = STATE_NONE;
		m_fCntState = 0.0f;
		CScene::GetnCntStart() = 0;
		CManager::GetDungeon()->SetQuake(60);
		break;
	}

	CManager::GetPlayer(0)->EffectUpdate();
	CManager::GetPlayer(0)->PEffectUpdate();
	CManager::GetPlayer(1)->EffectUpdate();
	CManager::GetPlayer(1)->PEffectUpdate();
}
//=============================================================================
// �o�[�T�X�̏I���O��������
//=============================================================================
void	CVersus::UpdateEnd()
{
	CScene2D *pScene2D;
	CSceneAnim2D *pSceneAnim2D;
	int	nWKData = 0;

	m_fCntState += 1.0f;
	switch ((int)m_fCntState)
	{
	case 2:
		CManager::GetSound()->Stop();

		if (SceneCreate(pScene2D, S2D_PRIORITY + 1))
		{//Logo
			pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
				D3DX_PI, 0, 1, 1, 0.05f, CScene2D::STATE_FADEIN, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEXTURE_MAX);
		}

		switch (m_state)
		{
		case STATE_P1_WIN:
		case STATE_P2_WIN:
			switch (m_state)
			{
			case STATE_P1_WIN: nWKData = 0; break;
			case STATE_P2_WIN: nWKData = 1; break;
			}
			if (SceneCreate(pScene2D, S2D_PRIORITY + 1))
			{//Logo
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
					D3DX_PI, 0, 1, 2, 0.05f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_LogoVsEnd);
			}
			if (SceneCreate(pScene2D, S2D_PRIORITY + 1))
			{//Logo
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 6,
					D3DX_PI, nWKData, 2, 1, 0.05f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_MAX);
				pScene2D->BindTexture(C2D::Load(C2D::TEX_PIcon));
			}
			break;
		case STATE_DRAW:
			if (SceneCreate(pScene2D, S2D_PRIORITY + 1))
			{//Logo
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6,
					D3DX_PI, 1, 1, 2, 0.05f, CScene2D::STATE_FADEIN, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CScene2D::TEXTURE_LogoVsEnd);
			}
			break;
		}
		if (SceneCreate(pSceneAnim2D, S2D_PRIORITY))
		{//�����a��
			pSceneAnim2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
				D3DX_PI, 0, 2, 10, 4, 0.0f, CScene2D::STATE_NORMAL, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_OVER2);
			pSceneAnim2D->BindDrawType(CScene::DRAW_TYPE_MULTIPLY);
		}

		CScene::GetnCntStart() = 2;
		break;
	case 60:
		break;
	case 1800:
		CManager::SetFade(CManager::MODE_VS_SELECT, 0);
		break;
	}
	if (m_fCntState > 90 && (
		CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || 
		CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) ||
		CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
		CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
	{
		CManager::SetFade(CManager::MODE_VS_SELECT, 0);
	}
}
//=============================================================================
// �o�[�T�X�̃|�[�Y����
//=============================================================================
void	CVersus::Pause(void)
{
	if (CManager::GetFade()->GetState() == CFade::STATE_FADE_NONE)
	{
		CSound *pSound = CManager::GetSound();					//�T�E���h�̃|�C���^���擾
		CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
		CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
		CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//�W���C�p�b�h���l��
		bool bSelect = false;
		bool bPause = true;

		if (!CScene::GetbPause())
		{//�|�[�Y�łȂ�
			if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START))
			{//�|�[�Y�N��
				CScene::GetbPause() = true;
				bSelect = true;
				m_nSelect = 3;

				if (SceneCreate(m_pScene2D[0], PAUSE_PRIORITY))
				{//��ʈÂ�����
					m_pScene2D[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
						D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.65f), CScene2D::TEXTURE_MAX);
				}
				if (SceneCreate(m_pScene2D[1], PAUSE_PRIORITY))
				{//��`���[�g���A��
					m_pScene2D[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, PAUSE_LENGTH, 0.0f), SCREEN_WIDTH / 2, PAUSE_LENGTH,
						D3DX_PI, 0, 1, 2, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_ITEM_TUTORIAL);
				}
				if (SceneCreate(m_pScene2D[2], PAUSE_PRIORITY))
				{//���`���[�g���A��
					m_pScene2D[2]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PAUSE_LENGTH, 0.0f), SCREEN_WIDTH / 2, PAUSE_LENGTH,
						D3DX_PI, 1, 1, 2, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_ITEM_TUTORIAL);
				}
				if (SceneCreate(m_pScene2D[3], PAUSE_PRIORITY))
				{//��Z���N�g�@�R���e�j���[
					m_pScene2D[3]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 0, 1, 2, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoPause);
				}
				if (SceneCreate(m_pScene2D[4], PAUSE_PRIORITY))
				{//���Z���N�g�@���^�C�A
					m_pScene2D[4]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 1, 1, 2, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoPause);
				}
				if (SceneCreate(m_pScene2D[5], PAUSE_PRIORITY))
				{//�}�[�J�[
					(m_pScene2D[5]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - GAME_PAUSE_LOGOX, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 100.0f, CScene2D::STATE_FLASH2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Marker));
				}
			}
		}
		else if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START)
			|| pInputPad0->GetTrigger(INPUT_B) || pInputPad1->GetTrigger(INPUT_B))
		{//�|�[�Y�~��
			bPause = false;
		}

		if (CScene::GetbPause())
		{//�|�[�Y��
			if (pInputKey->GetTPress(DIK_UP) ||
				pInputPad0->GetTPress(INPUT_UP) || pInputPad0->GetTPress(INPUT_LS_U) ||
				pInputPad1->GetTPress(INPUT_UP) || pInputPad1->GetTPress(INPUT_LS_U))
			{
				m_nSelect = (m_nSelect - 3 + 1) % 2 + 3; bSelect = true;
			}

			if (pInputKey->GetTPress(DIK_DOWN) ||
				pInputPad0->GetTPress(INPUT_DOWN) || pInputPad0->GetTPress(INPUT_LS_D) ||
				pInputPad1->GetTPress(INPUT_DOWN) || pInputPad1->GetTPress(INPUT_LS_D))
			{
				m_nSelect = (m_nSelect - 3 + 1) % 2 + 3;  bSelect = true;
			}

			if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A) || pInputPad1->GetTrigger(INPUT_A))
			{
				if (m_nSelect == 3) { bPause = false; }
				else if (m_nSelect == 4) { CManager::SetFade(CManager::MODE_VS_SELECT, 0); CScene::GetbPause() = false; return; }
			}

			if (!bPause)
			{//�|�[�Y���I������
				CScene::GetbPause() = false;

				for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
				{//�S�|�[�Y�̔j��
					if (m_pScene2D[nCount] != NULL)
					{//��������Ă���΍폜
						m_pScene2D[nCount]->Uninit();
						m_pScene2D[nCount] = NULL;
					}
				}
			}
			else if (bSelect)
			{//��Ԃ̍X�V
				CSceneAnim2D *p2DAnim;
				for (int nCount = 3; nCount <= 4; nCount++)
				{
					if (m_nSelect == nCount)
					{ //�I������Ă���
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_BIG;
					}
					else
					{ //�I������ĂȂ�
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_SMALL;
					}
				}
				m_pScene2D[5]->SetPosition(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(-GAME_PAUSE_LOGOX * 1.5f, 0.0f, 0.0f));
				//���G�t�F�N�g
				if (SceneCreate(p2DAnim, PAUSE_PRIORITY))
				{
					p2DAnim->Set(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 200.0f, D3DX_PI, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
						CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Slashing0);
					p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
				}
			}
		}
	}//�t�F�[�h�m�F
}