//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "motion.h"
#include "player.h"
#include "bullet.h"
#include "Effect.h"
#include "Number.h"
#include "SceneModel.h"
#include "mesh.h"
#include "2DGage.h"
#include "2DPolygon.h"
#include "Font.h"
#include "camera.h"
#include "light.h"
#include "Game.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAGE_LENGTH		(400.0f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
int		CPlayer::m_nNumPlayer = 0;	//プレイヤーの総数カウント

//==================================================================================================//
//    * プレイヤーのセット関数 *
//==================================================================================================//
void CPlayer::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)	//ゲージセット処理
{
	//CSatellite *pSatellite;
	//CMeshOrbit *pOrbit;

	CCharacter::Set(pos, rot, type);
	//Draw();

	//for (int nCount = 0; nCount < 4; nCount++)
	//{
	//	if (SceneCreate(pSatellite, SATELLITE_PRIORITY))
	//	{
	//		pSatellite->Set(GetpParts()[0]->GetBone()[0].GetMtx(), D3DXVECTOR3(0.0f, nCount * D3DX_PI * 0.5f - D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), CSceneModel::MODEL_SATELLITE,
	//			Getmove(), GetfSumFrame(), (nCount * 0.5f) * D3DX_PI, 50.0f, GetbDeath());
	//	}

	//	CMeshOrbit *pOrbit;
	//	if (SceneCreate(pOrbit, ORBIT_PRIORITY))
	//	{
	//		pOrbit->Set(pSatellite->GetmtxWorld(), D3DXVECTOR3(2.0f, 10.0f, 0.0f), D3DXVECTOR3(-2.0f, 10.0f, 0.0f), GetbDeath(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Orbit);
	//		pOrbit->GetDrawType() = CScene::DRAW_TYPE_ADD;
	//	}
	//	if (SceneCreate(pOrbit, ORBIT_PRIORITY))
	//	{
	//		pOrbit->Set(pSatellite->GetmtxWorld(), D3DXVECTOR3(2.0f, -10.0f, 0.0f), D3DXVECTOR3(-2.0f, -10.0f, 0.0f), GetbDeath(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Orbit);
	//		pOrbit->GetDrawType() = CScene::DRAW_TYPE_SUBTRACT;
	//	}
	//}
	if (SceneCreate(m_pUI, 6)) { m_pUI->Set(this); }	//UIの生成

	CCamera_Char *pCamera = CManager::GetCamera()->GetPlay(m_nID)->GetChar();
	pCamera->GetpChare() = &Getpos();
	pCamera->GetpMove() = &Getposold();
	pCamera->GetpDistance() = &m_fDistance;
	D3DXVECTOR3 &Crot = pCamera->GetRot();
	Crot.y = 0.0f;
	pCamera->Reset();

	if (SceneCreate(m_pModel, 0))
	{
		m_pModel->Set(pos + D3DXVECTOR3(0.0f, 70.0f, 50.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_Earth, CScene::DRAW_TYPE_NORMAL, false);
	}
}
//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT  CPlayer::Init(void)
{
	CCharacter::Init();
	SetObjType(CScene::OBJTYPE_PLAYER);
	GetTeam() = CCharacter::TEAM_PLAYER;
	m_nID = m_nNumPlayer;
	m_nNumPlayer++;

	m_fRatio = 1.0f;
	m_fBase = 29.5f;
	m_fDistance = m_fBase * m_fRatio;
	m_Mode = MODE::MODE_START;
	m_nCntState = 0;
	m_nBreak = 0;
	m_nBreak2 = 1;
	CManager::GetPlayer(m_nID) = this;
	return S_OK;
}
//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void  CPlayer::Uninit(void)
{
	m_nNumPlayer--;
	CManager::GetPlayer(m_nID) = NULL;
	if (m_pUI != NULL) { m_pUI->Uninit(); }
	CCharacter::Uninit();
	CSatellite::Delete();	//衛星の削除
	CMeshOrbit::Delete();	//オービットの削除
	CLineEffect::Delete();
}
//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(m_nID)->GetChar();
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(m_nID);	//ジョイパッド情報獲得
	CInputKeyboard *pInputKey = CManager::GetInputKey();
	D3DXVECTOR3 &Crot = pCamera->GetRot();
	bool	bMove = false;

	if (GetfLife() > 0.0f)
	{
		m_pModel->GetDrawType() = CScene::DRAW_TYPE_NO;
		switch (m_Mode)
		{
		case MODE_START:
			m_nCntState++;
			if (m_nCntState > 60)
			{
				m_nCntState = 0;
				m_Mode = MODE_BREAK;
			}
			break;
		case MODE_HIDE:
			m_fBase = 29.5f;
			Getpos().z += (80.0f - Getpos().z) * 0.1f;
			Crot.y += (0.0f - Crot.y) * 0.1f;
			if (CManager::GetInputKey()->GetTrigger(DIK_J) || pInputPad->GetTrigger(INPUT_A)) { m_Mode = MODE_BREAK; }
			break;
		case MODE_BREAK:
			m_fBase = 20.0f;
			Getpos().z += (-50.0f - Getpos().z) * 0.1f;
			Crot.y += (D3DX_PI - Crot.y) * 0.1f;
			Break();
			if (m_nBreak != 2)
			{
				if (CManager::GetInputKey()->GetTrigger(DIK_K) || pInputPad->GetTrigger(INPUT_R1)) { m_Mode = MODE_HIDE; }
			}
			break;
		case MODE_FIGHT:
			break;
		}
	}
	CCharacter::Update(false);

	//カメラ間隔の更新
	LockUpdate();
	//float fValue = 0.0f;
	//if (CManager::GetInputKey()->GetPress(DIK_UP) || pInputPad->GetPress(INPUT_UP))		{ fValue = -2.0f; }
	//if (CManager::GetInputKey()->GetPress(DIK_DOWN) || pInputPad->GetPress(INPUT_DOWN)) { fValue =  2.0f; }
	//m_fBase += fValue;

	//if (m_fBase < 1.0f) { m_fBase = 1.0f; }
	//if (m_fBase > 600.0f) { m_fBase = 600.0f; }

	//m_fDistance = m_fBase * m_fRatio;

	//if (pInputPad->GetStickDefeat(1))
	//{
	//	Crot.y += D3DX_PI * 0.01f * (pInputPad->GetnStickX(1) *  0.00004f);
	//	Crot.x += D3DX_PI * 0.01f * (pInputPad->GetnStickY(1) * -0.000015f);
	//}
	//if (Crot.y > D3DX_PI) { Crot.y -= D3DX_PI * 2; }
	//if (Crot.y < -D3DX_PI) { Crot.y += D3DX_PI * 2; }
	//if (Crot.x > D3DX_PI * 0.3f) { Crot.x = D3DX_PI * 0.3f; }
	//if (Crot.x < -D3DX_PI * 0.3f) { Crot.x = -D3DX_PI * 0.3f; }
}
//=============================================================================
// ロックオンの更新処理
//=============================================================================
void	CPlayer::LockUpdate(void)
{
	CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(m_nID)->GetChar();
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(m_nID);	//ジョイパッド情報獲得
	CInputKeyboard *pInputKey = CManager::GetInputKey();
	CSound *&pSound = CManager::GetSound();
	D3DXVECTOR3 &m_pos = Getpos();

	//if (GetpLockChar() != NULL)
	//{
	//	CScene *WKpScene = NULL;	//一時的保管用

	//	if (pInputKey->GetTrigger(DIK_F) || pInputPad->GetTrigger(INPUT_L1))
	//	{ //ロックオン解除
	//		pSound->Play(CSound::LABEL_LOCKCANSEL);
	//		LockCancel();
	//		//m_pUI->GetpLockOn()->GetfCntState() = 0.0f;
	//	}
	//	else if ((pInputKey->GetPress(DIK_X) && pInputKey->GetPress(DIK_C)) || 
	//		(pInputPad->GetPress(INPUT_L2) && pInputPad->GetPress(INPUT_R2))) { WKpScene = LockChar(CCharacter::LOCK_NEAR); }
	//	else if (pInputKey->GetTrigger(DIK_X) || pInputPad->GetTrigger(INPUT_L2)) { WKpScene = LockChar(CCharacter::LOCK_LEFT); }
	//	else if (pInputKey->GetTrigger(DIK_C) || pInputPad->GetTrigger(INPUT_R2)) { WKpScene = LockChar(CCharacter::LOCK_RIGHT); }

	//	if (GetpLockChar() != NULL)
	//	{ //キャンセルされていない
	//		if (WKpScene != NULL)
	//		{//切り替え成功
	//			pSound->Play(CSound::LABEL_LOCKCANSEL);
	//			GetpLockChar() = WKpScene;
	//		}
	//		else
	//		{//切り替え失敗
	//			//pSound
	//		}
	//	}
	//}
	//else
	//{
	//	if (pInputKey->GetTrigger(DIK_F) || pInputPad->GetTrigger(INPUT_L1) || pInputPad->GetTrigger(INPUT_L2) || pInputPad->GetTrigger(INPUT_R2))
	//	{ //ロックオン
	//		GetpLockChar() = LockChar(CCharacter::LOCK_FIRST);
	//		if (GetpLockChar() != NULL) { pSound->Play(CSound::LABEL_LOCKON); }
	//	}
	//	else
	//	{
	//		LockChar(CCharacter::LOCK_NO);
	//	}
	//}

	//ロックしているなら
	if (GetpLockChar() != NULL)
	{//キャラロック処理
		CScene *pScene = GetpLockChar();
		D3DXVECTOR3 *pos = GetpLockChar()->Getpos();
		D3DXVECTOR3 WKpos;
		D3DXVECTOR3 &Crot = pCamera->GetRot();
		float fWKangle;

		WKpos = (m_pos + D3DXVECTOR3(0.0f, 500.0f, 0.0f)) - pos[0];
		fWKangle = atan2f(WKpos.x, WKpos.z);
		fWKangle -= Crot.y;

		if (fWKangle > D3DX_PI) { fWKangle -= D3DX_PI * 2.0f; }
		else if (fWKangle < -D3DX_PI) { fWKangle += D3DX_PI * 2.0f; }
		Crot.y += fWKangle * 0.2f;//差分を％で詰める
		if (Crot.y > D3DX_PI) { Crot.y -= D3DX_PI * 2.0f; }
		else if (Crot.y < -D3DX_PI) { Crot.y += D3DX_PI * 2.0f; }

		fWKangle = atan2f(powf(WKpos.y, 2), powf(WKpos.x, 2) + powf(WKpos.z, 2));
		fWKangle -= Crot.x;

		if (fWKangle > D3DX_PI) { fWKangle -= D3DX_PI * 2.0f; }
		else if (fWKangle < -D3DX_PI) { fWKangle += D3DX_PI * 2.0f; }
		Crot.x += fWKangle * 0.2f;//差分を％で詰める
		if (Crot.x > 0.3f) { Crot.x = 0.3f; }
		else if (Crot.x < -0.3f) { Crot.x = -0.3f; }
	}
}
//=============================================================================
// 地上空中による予約モーションの変更処理
//=============================================================================
void	CPlayer::ChangeMotion(void)
{
	if (!GetbJump())
	{
		int &nNumMotion1 = GetnNumMotion(1);
		switch (nNumMotion1)
		{
		case MOTION_BOOST:		nNumMotion1 = -1; break;
		case MOTION_ATTACK:		nNumMotion1 = MOTION_ATTACK + 6;		break;	//地弱	->	空弱
		case MOTION_ATTACK + 1: nNumMotion1 = MOTION_ATTACK + 1 + 6;	break;	//地前弱->	空前弱
		case MOTION_ATTACK + 2: nNumMotion1 = MOTION_ATTACK + 2 + 6;	break;	//地後弱->	空後弱

		case MOTION_ATTACK + 3: nNumMotion1 = MOTION_ATTACK + 3 + 7;	break;	//地強	->	空強
		case MOTION_ATTACK + 4: nNumMotion1 = MOTION_ATTACK + 4 + 7;	break;	//地前強->	空前強
		case MOTION_ATTACK + 5: nNumMotion1 = MOTION_ATTACK + 5 + 7;	break;	//地後強->	空後強
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void	CPlayer::Draw(void)
{
	CCharacter::Draw();
	if (CManager::GetCamera()->GetInfo().pCamera->GetnNumCamera() != m_nID)
	{//自身と同じカメラでないなら
		CCharacter::DrawGage();
	}

	if (m_bReset)
	{
		CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(m_nID)->GetChar();
		m_bReset = false;
		CSatellite::ReSet();
		CMeshOrbit::ReSetAll();
		pCamera->Reset();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void	CPlayer::Break(void)
{
	m_pModel->GetDrawType() = CScene::DRAW_TYPE_NORMAL;
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(m_nID);	//ジョイパッド情報獲得
	CInputKeyboard *pInputKey = CManager::GetInputKey();
	D3DXVECTOR3 &pos = m_pModel->GetPosition();
	switch (m_nBreak)
	{
	case 0:	//横
		pos.z += (50.0f - pos.z) * 0.1f;
		pos.y += (105.0f - pos.y) * 0.1f;
		pos.x += 0.5f * m_nBreak2;
		if (pos.x > 55.0f) { pos.x = 55.0f; m_nBreak2 *= -1; }
		if (pos.x < -55.0f) { pos.x = -55.0f; m_nBreak2 *= -1; }
		if (pInputKey->GetTrigger(DIK_J) || pInputPad->GetTrigger(INPUT_A)) { m_nBreak = 1; m_nBreak2 = -1; }
		break;
	case 1:	//縦
		pos.z += (50.0f - pos.z) * 0.1f;
		pos.y += 0.5f * m_nBreak2;
		if (pos.y > 120.0f) { pos.y = 120.0f; m_nBreak2 *= -1; }
		if (pos.y < 10.0f) { pos.y = 10.0f; m_nBreak2 *= -1; }
		if (pInputKey->GetTrigger(DIK_J) || pInputPad->GetTrigger(INPUT_A)) 
		{ 
			m_nCntBreak = 0;
			m_nBreak = 2;
		}
		break;
	case 2:	//刺す
		m_nCntBreak++;
		if (m_nCntBreak == 10)
		{
			//演出
			float wood = 2.0f;
			if ((pos.x > 0.0f - wood && pos.x < 0.0f + wood) ||
				(pos.x > 26.0f - wood && pos.x < 26.0f + wood) ||
				(pos.x > 52.0f - wood) ||
				(pos.x > -26.0f - wood && pos.x < -26.0f + wood) || 
				(pos.x < -52.0f + wood) ||
				(pos.y > 65.0f - wood && pos.y < 65.0f + wood) || 
				(pos.y > 91.0f - wood && pos.y < 91.0f + wood) ||
				(pos.y > 117.0f - wood) ||
				(pos.y > 39.0f - wood && pos.y < 39.0f + wood) ||
				(pos.y < 13.0f + wood))
			{//XZアウト
				GetfLife() -= 50.0f;
				if (GetfLife() <= 0.0f)
				{
					Dead();
				}
				else
				{
					CManager::GetSound()->Play(CSound::LABEL_StabMiss);
				}
			}
			else
			{
				int nX, nY;
				nX = (int)(pos.x + 52.0f) / 26;
				nY = (int)(pos.y - 13.0f) / 26;
				//nY = (nY - 3) * -1;
				CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "X %d Y %d A %d\n", nX, nY, nY * 4 + nX);
				CScene3D *&p3D = CManager::GetGame()->Get3D(nY * 4 + nX);
				if (p3D->GetObjType() == OBJTYPE_NONE)
				{//穴が開いていない
					p3D->SetObjType(OBJTYPE_NONE2);
					p3D->BindTexture(CScene::Load(CScene::TEX_Hole));
					CManager::GetSound()->Play((CSound::LABEL)((int)CSound::LABEL_Stab0 + (rand() % 4)));
					//エフェクト
					CScene2D *p2D;
					if (SceneCreate(p2D, 6))
					{
						p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.05f, CScene2D::STATE_FADEOUT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_HIT99);
					}
					break;
				}
			}
		}
		if (m_nCntBreak > 60)
		{
			pos.z += (50.0f - pos.z) * 0.1f;
			if (pos.z < 55.0f) { m_nBreak = 0; }
		}
		else
		{
			pos.z += (100.0f - pos.z) * 0.3f;
		}
		break;
	}
	m_pModel->SetMtx();

	//
}
//=============================================================================
// プレイヤーの回答処理
//=============================================================================
void	CPlayer::Answer(void)
{

}
//=============================================================================
// プレイヤーの死亡処理
//=============================================================================
void	CPlayer::Dead(void)
{
	GetfLife() = 0.0f;
	CManager::GetSound()->Stop();
	CCharacter::Dead();
	CManager::GetSound()->Play(CSound::LABEL_Damage);
	CManager::GetGame()->SetState(CGame::STATE_OVER);
}
//=============================================================================
// 消失処理
//=============================================================================
void	CPlayer::Over(void)
{
	CCharacter::Over();
}
//=============================================================================
// ライト 色変更処理
//=============================================================================
void CPlayer::SetLightCol(D3DXCOLOR col)
{
	CManager::GetLight()->GetCol(m_nID + 1) = col;
}
//=============================================================================
// ライト 強さ変更処理
//=============================================================================
void CPlayer::SetLightStr(float fGoal, float fFrame)
{
	CManager::GetLight()->SetStrength(fGoal, fFrame, m_nID + 1);
}
//***************************************************************************//
//=============================================================================
//プレイヤーUIの設定処理
//=============================================================================
//***************************************************************************//
void	CPlayer_UI::Set(CPlayer *pPlayer)
{
	//CManager::GetbDuo() = true;
	m_bHelp = true;
	float fPosY = SCREEN_HEIGHT / 2 + 50.0f;
	float fPosY2 = SCREEN_HEIGHT;
	m_pPlayer = pPlayer;
	if (CManager::GetGame() == NULL) { return; }

	if (CManager::GetbDuo())
	{//2人プレイ
		fPosY = SCREEN_HEIGHT / 4.0f + (SCREEN_HEIGHT / 2.0f) * pPlayer->GetnID();
		fPosY2 = SCREEN_HEIGHT / 2.0f * (pPlayer->GetnID() + 1.0f);
	}
	//ヘルプ
	if (Create(m_p2DHelp))
	{
		m_p2DHelp->Set(D3DXVECTOR3(SCREEN_WIDTH - (SCREEN_WIDTH / 8), fPosY2 - SCREEN_HEIGHT / 8, 0.0f),
			SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8, D3DX_PI, 0, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_p2DHelp->BindTexture(CScene::Load(CScene::TEX_Help));
		m_p2DHelp->BindDrawType((m_bHelp ? CScene::DRAW_TYPE_NORMAL : CScene::DRAW_TYPE_NO));
	}
	//ヘルプ文字
	if (SceneCreate(m_pFont, 6))
	{
		m_pFont->Set(RECT{ SCREEN_WIDTH / 4 * 3, (int)fPosY2 - (m_bHelp ? 200 : 30), SCREEN_WIDTH, SCREEN_HEIGHT },
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), (m_bHelp ? "[SELECT]ヘルプを閉じる" : "[SELECT]ヘルプを開く"),
			0, DT_CENTER, -1, true, CFont::STATE_NONE);
	}
	////ゲージ
	if (Create(m_pLife))
	{
		m_pLife->Set(D3DXVECTOR3(SCREEN_WIDTH / 4 - (GAGE_LENGTH / 2) - 20.0f , fPosY - 375.0f, 0.0f)
			, GAGE_LENGTH, 20.0f, &pPlayer->GetfLife(), &pPlayer->GetfMaxLife(), 0, C2DGage::STATE_LIFE);
	}
	if (Create(m_pTime))
	{
		m_pTime->Set(D3DXVECTOR3(D3DXVECTOR3(SCREEN_WIDTH / 2, fPosY - 375.0f, 0.0f)), 10.0f, 20.0f, 60 * 120, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_TIMER);
	}
	//if (Create(m_pSP))
	//{
	//	m_pSP->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - (GAGE_LENGTH / 2), fPosY + 155.0f, 0.0f)
	//		, GAGE_LENGTH, 3.0f, &pPlayer->GetfSP(), &pPlayer->GetfMaxSP(), 0, C2DGage::STATE_SP);
	//}
	//if (Create(m_pStamina))
	//{
	//	m_pStamina->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - ((GAGE_LENGTH / 2) * 0.5f), fPosY + 125.0f, 0.0f)
	//		, GAGE_LENGTH * 0.5f, 2.0f, &pPlayer->GetfStamina(), &pPlayer->GetfMaxStamina(), 0, C2DGage::STATE_STAMINA);
	//}
	//装飾
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < 1; nCount++)
	{
		if (Create(m_p2DDeco[nCount]))
		{
			switch (nCount)
			{
			case 0: pos = D3DXVECTOR3(60.0f, 60.0f, 0.0f); break;
			case 1: pos = D3DXVECTOR3(SCREEN_WIDTH / 2, fPosY + 155.0f, 0.0f); break;
			}
			m_p2DDeco[nCount]->Set(pos, 50.0f, 50.0f, D3DX_PI, 0, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_p2DDeco[nCount]->BindTexture(CScene::Load(CScene::TEX_Icon_TKS));
		}
	}

	if (Create(m_p2DSelect))
	{
		m_p2DSelect->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6 * 5, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 6, D3DX_PI, 0, 1, 1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f));
	}
	for (int nCount = 0; nCount < 4; nCount++)
	{
		if (SceneCreate(m_pSelect[nCount], 6))
		{
			char aStr[128] = "";
			int nData = CManager::GetGame()->GetnQuiz();
			switch (CManager::GetGame()->GetnQuiz())
			{
			case 0:
				switch (nCount)
				{
				case 0: strcpy(&aStr[0], "A: スケートボード"); break;
				case 1: strcpy(&aStr[0], "B: スノーボード"); break;
				case 2: strcpy(&aStr[0], "X: キックボード"); break;
				case 3: strcpy(&aStr[0], "Y: タマゴボーロ"); break;
				}
				break;
			case 1:
				switch (nCount)
				{
				case 0: strcpy(&aStr[0], "A: いぬ"); break;
				case 1: strcpy(&aStr[0], "B: うし"); break;
				case 2: strcpy(&aStr[0], "X: うま"); break;
				case 3: strcpy(&aStr[0], "Y: しまうま"); break;
				}
				break;
			case 2:
				switch (nCount)
				{
				case 0: strcpy(&aStr[0], "A: 田中昌"); break;
				case 1: strcpy(&aStr[0], "B: 田中彰"); break;
				case 2: strcpy(&aStr[0], "X: 田中章"); break;
				case 3: strcpy(&aStr[0], "Y: 覇王アキラ丸"); break;
				}
				break;
			case 3:
				switch (nCount)
				{
				case 0: strcpy(&aStr[0], "A: 大乱闘スマッシュブラザーズ X"); break;
				case 1: strcpy(&aStr[0], "B: 大乱闘スマッシュブラザーズ SPECIAL"); break;
				case 2: strcpy(&aStr[0], "X: 大乱闘スマッシュブラザーズ for Nintendo 3DS/Wii U"); break;
				case 3: strcpy(&aStr[0], "Y: 大乱闘スマッシュブラザーズ for Nintendo Switch"); break;
				}
				break;
			case 4:
				switch (nCount)
				{
				case 0: strcpy(&aStr[0], "A: TAKASHI"); break;
				case 1: strcpy(&aStr[0], "B: TAKESHI"); break;
				case 2: strcpy(&aStr[0], "X: TAKACY"); break;
				case 3: strcpy(&aStr[0], "Y: TAKUTY"); break;
				}
				break;
			case 5:
				switch (nCount)
				{
				case 0: strcpy(&aStr[0], "A: グラディウス"); break;
				case 1: strcpy(&aStr[0], "B: スーパースターソルジャー"); break;
				case 2: strcpy(&aStr[0], "X: R - TYPE"); break;
				case 3: strcpy(&aStr[0], "Y: ツインビー"); break;
				}
				break;
			}
			m_pSelect[nCount]->Set(RECT{ 100, nCount * 50 + 500, SCREEN_WIDTH - 100, SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), &aStr[0], 1, DT_CENTER, 0, true, CFont::STATE_NONE);
		}
	}
	//if (SceneCreate(m_pModel, OBJ_PRIORITY))
	//{//方位磁針(本体)の作成
	//	m_pModel->Set(D3DXVECTOR3(1000.0f, 0.0f, m_pPlayer->GetnID() * 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	//		, CSceneModel::MODEL_POS_MAG, CScene::DRAW_TYPE_ZNORMAL, false);
	//	m_pModel->SetObjType(CScene::OBJTYPE_OTHER);
	//}
	//if (SceneCreate(m_pNeedle, OBJ_PRIORITY))
	//{//方位磁針(針)の作成
	//	m_pNeedle->Set(D3DXVECTOR3(1000.0f, 0.0f, m_pPlayer->GetnID() * 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	//		, CSceneModel::MODEL_POS_NEE, CScene::DRAW_TYPE_ZNORMAL, false);
	//	m_pNeedle->SetObjType(CScene::OBJTYPE_OTHER);
	//}

	//if (SceneCreate(m_pLockOn, OBJ_PRIORITY))
	//{//ロックオンマーカーの作成
	//	m_pLockOn->Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f)
	//		, CScene::TEX_Lock_On, 1, 2, 1, true, CScene::DRAW_TYPE_NO, NULL, (pPlayer->GetnID() + 1) % 2);
	//	m_pLockOn->SetObjType(CScene::OBJTYPE_UI);
	//}

	//if (m_pMotion_UI == NULL)
	//{//モーションUIの作成
	//	m_pMotion_UI = new Motion_UI[MAX_MotionUI];
	//	m_pMotion_UI[0].Set(pPlayer, D3DXVECTOR3(400.0f, fPosY - 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK		, 0, Motion_UI::TYPE_GROUND);
	//	m_pMotion_UI[1].Set(pPlayer, D3DXVECTOR3(400.0f, fPosY, 0.0f)			, CCharacter::MOTION_ATTACK + 1	, 3, Motion_UI::TYPE_GROUND);
	//	m_pMotion_UI[2].Set(pPlayer, D3DXVECTOR3(400.0f, fPosY + 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 2	, 6, Motion_UI::TYPE_GROUND);
	//	m_pMotion_UI[3].Set(pPlayer, D3DXVECTOR3(350.0f, fPosY - 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 3	, 1, Motion_UI::TYPE_GROUND);
	//	m_pMotion_UI[4].Set(pPlayer, D3DXVECTOR3(350.0f, fPosY, 0.0f)			, CCharacter::MOTION_ATTACK + 4	, 4	, Motion_UI::TYPE_GROUND);
	//	m_pMotion_UI[5].Set(pPlayer, D3DXVECTOR3(350.0f, fPosY + 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 5	, 7, Motion_UI::TYPE_GROUND);

	//	m_pMotion_UI[6].Set(pPlayer, D3DXVECTOR3(300.0f, fPosY - 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 6	, 0, Motion_UI::TYPE_SKY);
	//	m_pMotion_UI[7].Set(pPlayer, D3DXVECTOR3(300.0f, fPosY, 0.0f)			, CCharacter::MOTION_ATTACK + 7	, 3, Motion_UI::TYPE_SKY);
	//	m_pMotion_UI[8].Set(pPlayer, D3DXVECTOR3(300.0f, fPosY + 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 8	, 6, Motion_UI::TYPE_SKY);
	//	m_pMotion_UI[9].Set(pPlayer, D3DXVECTOR3(250.0f, fPosY - 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 10, 1, Motion_UI::TYPE_SKY);
	//	m_pMotion_UI[10].Set(pPlayer, D3DXVECTOR3(250.0f, fPosY, 0.0f)			, CCharacter::MOTION_ATTACK + 11, 4, Motion_UI::TYPE_SKY);
	//	m_pMotion_UI[11].Set(pPlayer, D3DXVECTOR3(250.0f, fPosY + 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 12, 7, Motion_UI::TYPE_SKY);

	//	m_pMotion_UI[12].Set(pPlayer, D3DXVECTOR3(450.0f, fPosY - 50.0f, 0.0f)	, 5								, 2, Motion_UI::TYPE_NO);
	//	m_pMotion_UI[13].Set(pPlayer, D3DXVECTOR3(450.0f, fPosY, 0.0f)			, CCharacter::MOTION_ATTACK + 13, 5, Motion_UI::TYPE_NO);
	//	m_pMotion_UI[14].Set(pPlayer, D3DXVECTOR3(450.0f, fPosY + 50.0f, 0.0f)	, CCharacter::MOTION_ATTACK + 14, 8, Motion_UI::TYPE_NO);
	//}
	//CManager::GetbDuo() = false;
}
//=============================================================================
//ゲージセット処理
//=============================================================================
HRESULT	CPlayer_UI::Init(void)
{
	m_pLockOn = NULL;
	m_pLife = NULL;
	m_pModel = NULL;
	m_pNeedle = NULL;
	m_pPlayer = NULL;
	m_pSP = NULL;
	m_pMotion_UI = NULL;
	m_pStamina = NULL;
	m_pFont = NULL;
	m_p2DHelp = NULL;
	m_bHelp = true;
	m_pTime = NULL;
	for (int nCount = 0; nCount < MAX_UIDeco; nCount++) { m_p2DDeco[nCount] = NULL; }
	return S_OK;
}
//=============================================================================
//プレイヤーUIの終了処理
//=============================================================================
void	CPlayer_UI::Uninit(void)
{
	if (m_pLife != NULL) { m_pLife->Uninit(); }
	if (m_pSP != NULL) { m_pSP->Uninit(); }
	if (m_pStamina != NULL) { m_pStamina->Uninit(); }
	for (int nCount = 0; nCount < MAX_UIDeco; nCount++) { if (m_p2DDeco[nCount] != NULL) { m_p2DDeco[nCount]->Uninit(); } }
	if (m_pLockOn != NULL) { m_pLockOn->Uninit(); }
	if (m_pModel != NULL) { m_pModel->Uninit(); }
	if (m_pNeedle != NULL) { m_pNeedle->Uninit(); }
	if (m_p2DHelp != NULL) { m_p2DHelp->Uninit(); }
	if (m_p2DSelect != NULL) { m_p2DSelect->Uninit(); }
	if (m_pTime != NULL) { m_pTime->Uninit(); }
	if (m_pMotion_UI != NULL)
	{//モーションUIの削除
		for (int nCount = 0; nCount < MAX_MotionUI; nCount++) { m_pMotion_UI[nCount].Uninit(); }
		delete[] m_pMotion_UI;
	}
	if (m_pFont != NULL) { m_pFont->Uninit(); }
	CScene::Uninit();
}
//=============================================================================
//プレイヤーUIの更新処理
//=============================================================================
void	CPlayer_UI::Update(void)
{
	if (CManager::GetGame() == NULL) { return; }
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(m_pPlayer->GetnID());	//ジョイパッド情報獲得
	CInputKeyboard *pInputKey = CManager::GetInputKey();

	if (m_pLife != NULL) { m_pLife->Update(); }
	if (m_pSP != NULL) { m_pSP->Update(); }
	if (m_pStamina != NULL) { m_pStamina->Update(); }
	for (int nCount = 0; nCount < MAX_UIDeco; nCount++) { if (m_p2DDeco[nCount] != NULL) { m_p2DDeco[nCount]->Update(); } }
	if (m_p2DHelp != NULL) { m_p2DHelp->Update(); }
	if (m_p2DSelect != NULL) { m_p2DSelect->Update(); }
	if (m_pTime != NULL) { m_pTime->Update(); }

	if (m_pNeedle != NULL)
	{//針の更新
		m_pNeedle->GetRotation().y = m_pPlayer->Getrot().y;
		m_pNeedle->SetMtx();
	}
	if (m_pMotion_UI != NULL)
	{//モーションUIの更新
		for (int nCount = 0; nCount < MAX_MotionUI; nCount++) { m_pMotion_UI[nCount].Update(); }
	}

	if (pInputKey->GetTrigger(DIK_F2) || pInputPad->GetTrigger(INPUT_BACK)) 
	{//ヘルプの開け閉じ
		//文字 場所と内容の変更
		float fPosY2 = SCREEN_HEIGHT / 2.0f * (m_pPlayer->GetnID() + 1.0f + (CManager::GetbDuo() ? 0.0f : 1.0f));
		m_bHelp = (m_bHelp ? false : true);
		m_pFont->GetRect() = RECT{ SCREEN_WIDTH / 4 * 3, (int)fPosY2 - (m_bHelp ? 200 : 30), SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->SetFont((m_bHelp ? "[SELECT]ヘルプを閉じる" : "[SELECT]ヘルプを開く"), -1);
		//画像の描画ON/OFF
		m_p2DHelp->BindDrawType((m_bHelp ? CScene::DRAW_TYPE_NORMAL : CScene::DRAW_TYPE_NO));
	}

	if ((pInputKey->GetPress(DIK_L) || pInputPad->GetPress(INPUT_L1)) && m_pPlayer->GetfLife() >= 0.0f)
	{
		if (pInputKey->GetTrigger(DIK_L) || pInputPad->GetTrigger(INPUT_L1)) { CManager::GetSound()->Play(CSound::LABEL_Question); }
		m_p2DSelect->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		for (int nCount = 0; nCount < 4; nCount++) { m_pSelect[nCount]->GetbDisplay() = true; }
		bool bAnswer = false;
		int  nAnswer;
		if (pInputKey->GetTrigger(DIK_Z) || pInputPad->GetTrigger(INPUT_A)) { nAnswer = 0; bAnswer = true; }
		if (pInputKey->GetTrigger(DIK_X) || pInputPad->GetTrigger(INPUT_B)) { nAnswer = 1; bAnswer = true; }
		if (pInputKey->GetTrigger(DIK_C) || pInputPad->GetTrigger(INPUT_X)) { nAnswer = 2; bAnswer = true; }
		if (pInputKey->GetTrigger(DIK_V) || pInputPad->GetTrigger(INPUT_Y)) { nAnswer = 3; bAnswer = true; }

		if (bAnswer)
		{
			if (CManager::GetGame()->GetnAnswer() == nAnswer) { CManager::GetGame()->SetState(CGame::STATE_CLEAR); }
			else { m_pPlayer->Dead(); CManager::GetSound()->Play(CSound::LABEL_Incorrect); }
		}
	}
	else
	{
		m_p2DSelect->BindDrawType(CScene::DRAW_TYPE_NO);
		for (int nCount = 0; nCount < 4; nCount++) { m_pSelect[nCount]->GetbDisplay() = false; }
	}

	if (m_pTime->GetnNumber() <= 0) { if (m_pPlayer->GetfLife() > 0.0f) { m_pPlayer->Dead(); } }
}
//=============================================================================
//プレイヤーUIの描画処理
//=============================================================================
void	CPlayer_UI::Draw(void)
{
	if (m_pLife != NULL) { m_pLife->Draw(); }
	if (m_pSP != NULL) { m_pSP->Draw(); }
	if (m_pStamina != NULL) { m_pStamina->Draw(); }
	for (int nCount = 0; nCount < MAX_UIDeco; nCount++) { if (m_p2DDeco[nCount] != NULL) { m_p2DDeco[nCount]->Draw(); } }
	if (m_pMotion_UI != NULL) { for (int nCount = 0; nCount < MAX_MotionUI; nCount++) { m_pMotion_UI[nCount].Draw(); } }
	if (m_p2DSelect != NULL) { m_p2DSelect->Draw(); }
	if (m_p2DHelp != NULL) { m_p2DHelp->Draw(); }
	if (m_pTime != NULL) { m_pTime->Draw(); }
}
//=============================================================================
//ロックオン使用時のUI処理
//=============================================================================
void	CPlayer_UI::SetLockOn(LOCK lock, D3DXVECTOR3 *pos)
{
	if (m_pLockOn != NULL)
	{
		switch (lock)
		{
		case LOCK_CANCEL:

		case LOCK_NO:
			if (pos != NULL)
			{//仮ロック
				m_pLockOn->GetState() = CScene3D::STATE_LOCK_0;
				m_pLockOn->BindDrawType(CScene::DRAW_TYPE_ZADD);
				m_pLockOn->GetpPos() = pos;
				m_pLockOn->GetLength() = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
				m_pLockOn->SetUV(1, 2, 1);
			}
			else 
			{//ロック無し
				m_pLockOn->BindDrawType(CScene::DRAW_TYPE_NO);
				m_pLockOn->GetpPos() = NULL; 
			}
			break;
		case LOCK_START:	//ロックオン状態へ
			m_pLockOn->GetState() = CScene3D::STATE_LOCK_1;
			m_pLockOn->GetfCntState() = 50.0f;
			m_pLockOn->BindDrawType(CScene::DRAW_TYPE_ZADD);
			m_pLockOn->GetpPos() = pos;
			m_pLockOn->GetLength() = D3DXVECTOR3(15.0f, 15.0f, 0.0f);
			m_pLockOn->SetUV(0, 2, 1);
			break;
		case LOCK_ON:	//ロックオン切り替え
			m_pLockOn->BindDrawType(CScene::DRAW_TYPE_ZADD);
			m_pLockOn->GetpPos() = pos;
			m_pLockOn->GetLength() = D3DXVECTOR3(15.0f, 15.0f, 0.0f);
			m_pLockOn->SetSize(m_pLockOn->GetLength());
			m_pLockOn->SetUV(0, 2, 1);
			break;
		}
		m_pLockOn->SetSize(m_pLockOn->GetLength());
	}
}

//***************************************************************************//
//=============================================================================
// Motion_UIの初期化処理
//=============================================================================
//***************************************************************************//
HRESULT	Motion_UI::Init(void)
{
	m_p2D = NULL;
	m_pNumber = NULL;
	m_pGage = NULL;
	m_pPlayer = NULL;

	return S_OK;
}
//=============================================================================
// Motion_UIの終了処理
//=============================================================================
void	Motion_UI::Uninit(void)
{
	if (m_p2D != NULL) { m_p2D->Uninit(); }
	if (m_pNumber != NULL) { m_pNumber->Uninit(); }
	if (m_pGage != NULL) { m_pGage->Uninit(); }
}
//=============================================================================
// Motion_UIの更新処理
//=============================================================================
void	Motion_UI::Update(void)
{
	//参照するモーションのウェイトタイムが0より上の場合
	//int &nMaxWaitTime = CMotion::GetMotion(m_pPlayer->GetType())->GetOneMotion()[m_nID].GetnWaitTime();
	float  &fWaitTime  = m_pPlayer->GetpWaitMotion()[m_nID];
	bool &bUseMotion = m_pPlayer->GetpUseMotion()[m_nID];

	m_pNumber->SetNumber((int)fWaitTime);
	if (bUseMotion || !CCharacter::CheckSP(m_pPlayer->GetType(), m_nID, m_pPlayer->GetfSP()))
	{//待ち中
		m_p2D->GetColor() = D3DXCOLOR(0.35f, 0.35f, 0.35f, m_p2D->GetColor().a);
		m_p2D->SetColor(m_p2D->GetColor());
	}
	else
	{
		if (m_p2D->GetColor().r != 1.0f)
		{//解放演出
			m_p2D->GetColor() = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_p2D->GetColor().a);
			m_p2D->SetColor(m_p2D->GetColor());
		}
	}

	switch (m_Type)
	{
	case TYPE_GROUND:
		if (m_pPlayer->GetbJump()) 
		{ 
			m_p2D->GetState() = C2DPolygon::STATE_MEDIUM; 
			m_p2D->GetColor().a = 1.0f;
		}
		else						
		{ 
			m_p2D->GetState() = C2DPolygon::STATE_SMALL;
			m_p2D->GetColor().a = 0.35f;
		}
		m_p2D->SetColor(m_p2D->GetColor());
		break;
	case TYPE_SKY:
		if (m_pPlayer->GetbJump())	
		{ 
			m_p2D->GetState() = C2DPolygon::STATE_SMALL; 
			m_p2D->GetColor().a = 0.35f;
		}
		else						
		{ 
			m_p2D->GetState() = C2DPolygon::STATE_MEDIUM; 
			m_p2D->GetColor().a = 1.0f;
		}
		m_p2D->SetColor(m_p2D->GetColor());
		break;
	}

	if (m_p2D != NULL) { m_p2D->Update(); }
	if (m_pNumber != NULL) { m_pNumber->Update(); }
	if (m_pGage != NULL) { m_pGage->Update(); }
}
//=============================================================================
// Motion_UIの更新処理
//=============================================================================
void	Motion_UI::Draw(void)
{
	if (m_p2D != NULL) { m_p2D->Draw(); }
	if (m_pGage != NULL) { m_pGage->Draw(); }
	if (m_pNumber != NULL) { m_pNumber->Draw(); }
}
//=============================================================================
// Motion_UIの設定処理
//=============================================================================
void	Motion_UI::Set(CPlayer *pPlayer, D3DXVECTOR3 pos, int nID, int nUV, TYPE type)
{
	COneMotion *&OneMotion = CMotion::GetMotion(pPlayer->GetType())->GetOneMotion();
	m_Type = type;
	m_pPlayer = pPlayer;
	m_pos = pos;
	m_nID = nID;

	if (Create(m_p2D))
	{
		m_p2D->Set(pos, 20.0f, 20.0f, D3DX_PI, nUV, 3, 3, 100.0f, C2DPolygon::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_p2D->BindTexture(CScene::Load(CScene::TEX_Button_UI));
	}
	if (Create(m_pGage))
	{
		m_pGage->Set(pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f),
			40.0f, 20.0f, &pPlayer->GetpWaitMotion()[nID], &OneMotion[nID].GetfWaitTime(), 3, C2DGage::STATE_CHARGE);
	}
	if (Create(m_pNumber))
	{
		m_pNumber->Set(pos + D3DXVECTOR3(7.0f, 0.0f, 0.0f), 7.0f, 14.0f, 0, 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), CNumber::STATE_CHARGE);
	}
}


