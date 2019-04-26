//=============================================================================
//
// ポリゴン処理 [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include"Scene2D.h"
#include"enemy.h"
#include"player.h"

#include "manager.h"
#include "Game.h"
#include"Renderer.h"

#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DAMAGE_CLEAR	(10)		// ダメージ解除

#define ICE_CLEAR		(150)		// 凍った解除

#define FIRE_CLEAR		(60)		// 燃えた解除
#define FIRE_INTERVAL	(20)		// 燃える間隔

#define STAN_CLEAR		(60)		// 痺れた解除
#define STAN_INTERVAL	(60)		// 痺れる間隔

#define ENEMY_END		(0.0f)		// 敵ゴール地点

//=============================================================================
// 設定処理
//=============================================================================
void CEnemy::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture, ENEMYTYPE enemyType)
{//メンバ変数に代入
	CScene2D::Set(pos, 40.0f, flengthY, fRot, nUV, nUV_X, nUV_Y, fCntState, state, col, Texture);

	m_enemyType = enemyType;		// 敵タイプ設定

	m_state = ENEMYSTATE_NORMAL;	// 状態
	m_nCntState = 0;				// 状態カウント

	switch (m_enemyType)
	{// タイプによって体力、速度設定
	case ENEMYTYPE_NORMAL:			// 通常
		m_nLife = 1000;
		m_nSpeed = -1.25f;
		break;
	case ENEMYTYPE_NORMAL2:			// 通常
		m_nLife = 1500;
		m_nSpeed = -2.0f;
		break;
	case ENEMYTYPE_HP:				// 体力
		m_nLife = 3000;
		m_nSpeed = -0.75f;
		break;
	case ENEMYTYPE_SPEED:			// 速度
		m_nLife = 750;
		m_nSpeed = -4.0f;
		break;
	}
	SetUV(m_enemyType, ENEMYTYPE_MAX, 1);
	BindTexture(CScene2D::Load(CScene2D::TEX_Enemy999));
	m_fRot = (rand() % (int)(D3DX_PI * 200)) * 0.01f;
}
//=============================================================================
// 更新処理
//=============================================================================
void	CEnemy::Update(void)
{
	CSound *pSound = CManager::GetSound();			//BGMの再生
	CPlayer *pPlayer = CManager::GetPlayer0();
	D3DXVECTOR3 *pos = CScene2D::GetPosition();			// 位置取得
	float		fLengthX = CScene2D::GetfLengthX();		// Xサイズ取得
	float		fLengthY = CScene2D::GetfLengthY();		// Yサイズ取得
	bool		bDelete = false;						// 破棄する
	float		nSpeed = m_nSpeed;						// 速度
	D3DXCOLOR	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);// 色

	switch (m_state)
	{// 状態
	case ENEMYSTATE_NORMAL:			// 通常
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// デフォルトカラー

		break;
	case ENEMYSTATE_DAMAGE:			// ダメージ
		m_nCntState++;						// 状態カウント

		col = D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f);		// 色変更

		if (DAMAGE_CLEAR < m_nCntState)
		{// 一定カウントで
			m_state = ENEMYSTATE_NORMAL;	// 状態
			m_nCntState = 0;				// 状態カウント
			col = D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f);	// ダメージカラー
		}

		break;
	case ENEMYSTATE_ICE:			// 凍った		
		m_nCntState++;						// 状態カウント

		nSpeed = 0.0f;						// 止める

		col = D3DXCOLOR(0.6f, 0.85f, 0.9f, 1.0f);	// デフォルトカラー

		if (ICE_CLEAR < m_nCntState)
		{// 一定カウントで
			m_state = ENEMYSTATE_NORMAL;	// 状態
			m_nCntState = 0;				// 状態カウント
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// デフォルトカラー
		}

		break;
	case ENEMYSTATE_FIRE:			// 燃えた
		m_nCntState++;						// 状態カウント

		if (m_nCntState % FIRE_INTERVAL < (FIRE_INTERVAL * 0.5f))
		{// 一定間隔で
			if (m_nCntState % (int)(FIRE_INTERVAL * 0.5f) == 1)
			{// 一定間隔で
				bDelete = SetDamage(1, 0);	// ダメージ処理
			}

			col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	// ダメージカラー
		}
		else
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// デフォルトカラー
		}

		if (FIRE_CLEAR < m_nCntState)
		{// 一定カウントで
			m_state = ENEMYSTATE_NORMAL;	// 状態
			m_nCntState = 0;				// 状態カウント
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// デフォルトカラー
		}

		break;
	case ENEMYSTATE_STAN:			// 痺れた
		m_nCntState++;						// 状態カウント

		if (m_nCntState % STAN_INTERVAL < (STAN_INTERVAL * 0.5f))
		{// 一定間隔で
			nSpeed = 0.0f;					// 止める
			col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);	// スタンカラー
		}
		else
		{
			col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// デフォルトカラー
		}

		if (STAN_CLEAR < m_nCntState)
		{// 一定カウントで
			m_state = ENEMYSTATE_NORMAL;	// 状態
			m_nCntState = 0;				// 状態カウント
		}

		break;
	}

	if (m_state != ENEMYSTATE_ICE && CManager::GetGame()->GetState() != CGame::STATE_OVER)
	{// 凍った状態以外
		if (pPlayer != NULL)
		{// プレイヤーがいる
			if (pos->y - fLengthY < pPlayer->GetPosition()->y && pPlayer->GetPosition()->y < pos->y + fLengthY)
			{// Y範囲
				if (pos->x - fLengthX <= pPlayer->GetPosition()->x + pPlayer->GetfLengthX())
				{// プレイヤーより進んだら
					nSpeed = 0.0f;			// 止める
					if (pPlayer->GetnInvincible() <= 0)
					{//Damage
						pPlayer->GetfLife() -= 1.0f;
						pPlayer->GetnInvincible() = 60;
						pPlayer->SetColor(D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f));
						pSound->Play(CSound::LABEL_DAMAGE);
					}
				}
			}
		}
	}

	pos->x += nSpeed;					// 移動処理
	m_fRot += D3DX_PI * 0.01f;
	if (bDelete == false)
	{
		CScene2D::SetPosition(*pos);	// 位置設定
		CScene2D::SetColor(col);		// 色変更

		if (pos->x - fLengthX < ENEMY_END)
		{// 一定位置まで行ったら
			CManager::GetGame()->SetState(CGame::STATE_OVER);
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void	CEnemy::Draw(void)
{
	D3DXVECTOR3 pos = GetPosition()[0];
	SetPosition(GetPosition()[0] + D3DXVECTOR3(0.0f, cosf(m_fRot), 0.0f) * 10.0f);
	CScene2D::Draw();
	SetPosition(pos);
}
