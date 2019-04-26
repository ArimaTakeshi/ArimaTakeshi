//=============================================================================
//
// エネミー処理 [enemy.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "motion.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "camera.h"
#include "Game.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//==================================================================================================//
//    * エネミーのセット関数 *
//==================================================================================================//
void CEnemy::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, TYPE Etype, int nLevel)
{
	CCharacter::Set(pos, rot, Mtype);
	m_Type = Etype;
	GetnLevel() = nLevel;
	SetStatus();

	switch (m_Type)
	{
	case TYPE_NONE:		GetfMaxLife() *= 0.35f; GetfLife() *= 0.35f; break;
	case TYPE_TITLE:	GetfMaxLife() *= 3.0f; GetfLife() *= 3.0f; GetfAtk() *= 0.65f; break;
	}
}
//=============================================================================
// エネミーの初期化処理
//=============================================================================
HRESULT  CEnemy::Init(void)
{
	CCharacter::Init();
	SetObjType(CScene::OBJTYPE_ENEMY);
	bFight = false;
	bAlarm = false;
	GetTeam() = CCharacter::TEAM_ENEMY;
	return S_OK;
}
//=============================================================================
// エネミーの更新処理
//=============================================================================
void CEnemy::Update(void)
{
	CPlayer		*&pPlayer = CManager::GetPlayer(0);
	float	fMove = 0.0f;	//移動方向計算用
	bool bMove = false;
	if (pPlayer != NULL)
	{
		D3DXVECTOR3 &m_pos = Getpos();
		D3DXVECTOR3 playerPos0 = CManager::GetPlayer(0)->Getpos();
		D3DXVECTOR3 playerPos1;
		float fDistance0 = DRAW_DISTANCE;
		float fDistance1 = DRAW_DISTANCE;

		fDistance0 = powf(playerPos0.x - m_pos.x, 2) + powf(playerPos0.z - m_pos.z, 2);
		if (CManager::GetbDuo())
		{
			playerPos1 = CManager::GetPlayer(1)->Getpos();
			fDistance1 = powf(playerPos1.x - m_pos.x, 2) + powf(playerPos1.z - m_pos.z, 2);
		}
		if (fDistance0 >= DRAW_DISTANCE && fDistance1 >= DRAW_DISTANCE)
		{
			return;
		}

		if (fDistance1 < fDistance0 && CManager::GetbDuo())
		{//2Pのほうが近い場合2Pロック
			fDistance0 = fDistance1;
			playerPos0 = playerPos1;
		}

		if (CManager::GetGame()->GetState() == CGame::STATE_CLEAR) { return; }
		bMove = true;
		if (!bAlarm && fDistance0 < 200.0f * 200.0f && pPlayer->GetfLife() > 0.0f)
		{
			bAlarm = true;
			CManager::GetSound()->Play(CSound::LABEL_CHARGE000);
			CScene2D *p2D;
			if (SceneCreate(p2D, 6))
			{
				p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 500.0f, 200.0f, D3DX_PI, 0, 1, 1, 0.005f, CScene2D::STATE_FADEOUT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Alarm);
			}
			//効果音
		}
		if (fDistance0 < 100.0f * 100.0f && pPlayer->GetfLife() > 0.0f) 
		{ 
			if (pPlayer->GetMode() != CPlayer::MODE_HIDE)
			{ 
				pPlayer->GetMode() = CPlayer::MODE_FIGHT;
				pPlayer->GetpLockChar() = this;
				pPlayer->GetnBreak() = 0;
				SetNextMotion(MOTION_ATTACK); 
				bFight = true;
			}
		}

		if (bMove)
		{//動いているなら
			float &fRot = GetfRot();
			fRot = D3DX_PI * -0.5f;
			if (bFight) { fRot = atan2f(m_pos.x - playerPos0.x, m_pos.z - playerPos0.z) + fMove; }	//移動方向計算
			if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2; }
			if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2; }
		}
	}
	CCharacter::Update(bMove);

	Getpos().y = 20.0f;
	if (Getpos().x > 450.0f) { Getpos().x = -450.0f; bAlarm = false; }
}
//=============================================================================
// エネミーの描画処理
//=============================================================================
void	CEnemy::Draw(void)
{
	if (CManager::GetCamera()->DrawCheck(Getpos(), 1800.0f))
	{
		CCharacter::Draw();
		CCharacter::DrawGage();
	}
}
//=============================================================================
// エネミーの死亡処理
//=============================================================================
void	CEnemy::Dead(void)
{
	CCharacter::Dead();
}
//=============================================================================
// エネミーの消失処理
//=============================================================================
void	CEnemy::Over(void)
{
	switch (m_Type)
	{
	case TYPE_NONE: break;
	case TYPE_TITLE: CManager::GetGame()->SetState(CGame::STATE_CLEAR); break;
	}
	CCharacter::Over();
}
