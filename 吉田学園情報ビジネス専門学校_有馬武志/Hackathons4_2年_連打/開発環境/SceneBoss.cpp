//=============================================================================
//
// ボスの処理 [SceneBoss.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include "3DPolygon.h"
#include"Renderer.h"
#include "SceneBoss.h"
#include "SceneEnemy.h"
#include "ScenePlayer.h"
#include "Font.h"

#include "dungeon.h"
#include "Game.h"
#include "manager.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BOSS01_UV (4)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CSceneBoss::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CSceneBoss::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			 //ラビリンス//***********************************************************************
			case TEX_MANAGER:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BOSS/m4.png", &m_pTexture[tex]);		break;
			case TEX_BOSS01:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BOSS/m49.png", &m_pTexture[tex]);		break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
//	テクスチャの指定解放
//=============================================================================
void	CSceneBoss::UnLoad(TEXTURE tex)
{
	if (m_pTexture[tex] != NULL)
	{
		m_pTexture[tex]->Release();
		m_pTexture[tex] = NULL;
	}
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CSceneBoss::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// ボスEffect 終了
//=============================================================================
void CSceneBossEffect::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BEfeect; nCount++)
	{//2DPolygon終了
		if (m_p2D[nCount] != NULL)
		{//生成しているなら
			m_p2D[nCount]->Uninit();
			m_p2D[nCount] = NULL;
		}
	}
	Release();
}
//=============================================================================
// ボスEffect 更新
//=============================================================================
void CSceneBossEffect::Update(void)
{
	CScene2D *p2D;
	CSound *pSound = CManager::GetSound();

	m_nCntState++;
	switch (m_nCntState)
	{
	case 10:	//エフェクト
		m_p2D[0]->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_p2D[0]->GetState()[0] = C2DPolygon::STATE_SLIDEIN;
		for (int nCount = 0; nCount < 5; nCount++)
		{
			if (SceneCreate(p2D, UI_PRIORITY))
			{
				p2D->Set(m_p2D[1]->GetPosition(), SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f, 0, 1, 1, nCount * 0.01f + 0.01f,
					CScene2D::STATE_FADEOUT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_SPARK);
				p2D->BindDrawType(CScene::DRAW_TYPE_ADD);
			}
		}
		break;
	case 40:	//エフェクト
		//pSound->Play(CSound::LABEL_HIT999);
		break;
	case 120:	//Updateを戻して散る
		GetnCntStart() = 0;
		m_p2D[0]->GetState()[0] = C2DPolygon::STATE_SLIDEOUT;
		m_p2D[0]->GetfCntState() = 0.03f;
		m_p2D[1]->GetState()[0] = C2DPolygon::STATE_SLIDEOUT2;
		m_p2D[1]->GetfCntState() = 0.05f;
		break;
	case 510:	//破棄
		Uninit();
		break;
	}

	for (int nCount = 0; nCount < MAX_BEfeect; nCount++)
	{//2DPolygon更新
		if (m_p2D[nCount] != NULL)
		{//生成しているなら
			m_p2D[nCount]->Update();
		}
	}
}
//=============================================================================
// ボスEffect 描画
//=============================================================================
void CSceneBossEffect::Draw(void)
{
	for (int nCount = 0; nCount < MAX_BEfeect; nCount++)
	{//2DPolygon描画
		if (m_p2D[nCount] != NULL)
		{//生成しているなら
			m_p2D[nCount]->Draw();
		}
	}
}
//=============================================================================
// ボスEffect 設定
//=============================================================================
void CSceneBossEffect::Set(CSceneBoss::TEXTURE tex)
{
	m_nCntStart = 0;
	GetnCntStart() = 6;
	if (m_p2D[0] == NULL)
	{//ボスアイコン
		if (Create(m_p2D[0]))
		{
			m_p2D[0]->Set(D3DXVECTOR3(-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, D3DX_PI, tex, 1, CSceneBoss::TEXTURE_MAX,
				0.027125f, C2DPolygon::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), C2D::TEX_BossLabel);
			m_p2D[0]->BindDrawType(CScene::DRAW_TYPE_NO);
		}
	}
	if (m_p2D[1] == NULL)
	{//VSロゴ
		if (Create(m_p2D[1]))
		{
			m_p2D[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - SCREEN_HEIGHT / 2, -SCREEN_HEIGHT / 4, 0.0f), SCREEN_HEIGHT / 4, SCREEN_HEIGHT / 4, D3DX_PI, 0, 1, 1,
				0.05f, C2DPolygon::STATE_SLIDEIN2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), C2D::TEX_Versus);
		}
	}
}

//=============================================================================
// ボスUI 終了
//=============================================================================
void CSceneBossUI::Uninit(void)
{//削除
	if (m_pLifeGage != NULL) { m_pLifeGage->Uninit(); m_pLifeGage = NULL; }
	if (m_p2D != NULL) { m_p2D->Uninit(); m_p2D = NULL; }
	Release();
}
//=============================================================================
// ボスUI 更新
//=============================================================================
void CSceneBossUI::Update(void)
{ 
	if (m_pLifeGage != NULL) { m_pLifeGage->Update(); } 
	if (m_p2D != NULL)		 { m_p2D->Update(); }
}
//=============================================================================
// ボスUI 描画
//=============================================================================
void CSceneBossUI::Draw(void)
{ 
	if (m_pLifeGage != NULL) { m_pLifeGage->Draw(); } 
	if (m_p2D != NULL)		 { m_p2D->Draw(); }
}

//=============================================================================
// ボスの影生成
//=============================================================================
void CSceneBoss::InitShadow(void)
{
	if (m_p3DShadow == NULL)
	{//生成されていない
		if (Create(m_p3DShadow))
		{//影の生成
			m_p3DShadow->Set(GetPosition()[0], GetRotation()[0], GetColor()[0], GetfLengthX()[0], GetfLengthX()[0], C3D::TEX_SHADOW, 0, 1, 1, CScene::DRAW_TYPE_SUBTRACT);
		}
	}
}
//=============================================================================
// ボスの更新
//=============================================================================
void CSceneBoss::Update(void)
{
	D3DXVECTOR3 *pos = GetPosition();
	float *fCntState = GetfCntState();
	bool bRiver = true;
	if (CManager::GetNearPlayer(GetPosition()[0])->GetfLife() > 0) { fCntState[0]++; }
	else { fCntState[0] = 99999.9f; }
	if (m_fModeChange >= 0)
	{//切り替えタイミング待ちなら
		if (m_fModeChange <= fCntState[0])
		{//待ち
			GetState()[0] = CScene3D::STATE_CHANGE;
		}
	}

	switch (GetState()[0])
	{
	case CScene3D::STATE_JUMP:
		if (fCntState[0] == 1)  { SetJump(1.0f); }
		if (fCntState[0] == 20) { SetJump(1.0f); }
		break;
	}
	m_posold = pos[0];
	pos[0] += D3DXVECTOR3(m_move.x, 0.0f, m_move.z);
	m_move.x *= 0.3f; m_move.z *= 0.3f;
	m_p3DShadow->GetPosition()[0] = pos[0];

	CDungeon *pDungeon = CManager::GetDungeon();
	if (pDungeon != NULL) { m_bCollision = pDungeon->Collision(pos[0], m_posold, m_move, GetfLengthX()[0] * 0.75f, GetfLengthZ()[0] * 0.75f, bRiver); }

	if (m_bJump) { m_move.y -= 0.1f; }
	m_fPlusY += m_move.y;
	if (m_fPlusY < 0.0f)
	{//地面に着いた
		if (m_bJump) 
		{ 
			m_bJump = false;
			m_fPlusY = -m_move.y * 10.0f;
			m_move.y = 0.0f;
		}
		m_fPlusY *= 0.03f;
	}
}
//=============================================================================
// ボスの描画
//=============================================================================
void	CSceneBoss::Draw(void)
{
	if (m_p3DShadow != NULL) { m_p3DShadow->Draw(); }
	GetPosition()[0].z += m_fPlusY;
	CScene3D::Draw();
	GetPosition()[0].z -= m_fPlusY;
}
//=============================================================================
// ボスのドロップ
//=============================================================================
void CSceneBoss::DropUninit(void)
{
	float fPlayer = 0.0f;
	if (CManager::GetDungeon() != NULL) { CManager::GetDungeon()->SetQuake(30); }

	switch (m_TexType)
	{
	case TEX_BOSS01:
		if (CManager::GetMode()[0] == CManager::MODE_GAME)
		{//CLEAR状態に
			CManager::GetGame()->SetState(CGame::STATE_CLEAR);
		}
		break;
	case TEX_MANAGER:
		CScenePlayer *pPlayer;
		CSceneObjct  *pSceneModel;
		CSceneAnim3D *pSceneAnim3D;
		CSceneModel::TEXTURE tex;
		CSceneObjct::USE use;

		if (CManager::GetDungeon() != NULL) { CManager::GetDungeon()->GetbManager() = false; }

		if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
		{//出口
			pSceneAnim3D->Set(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, 20.1f, ((BOSSMAP_SIZEZ / 5) * 4) * -CHIP_SIZE + CHIP_SIZE),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CHIP_SIZE * 0.3f, CHIP_SIZE * 0.3f, CSceneAnim3D::TEX_GOAL, CScene::DRAW_TYPE_ADD, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_SHOP);
		}

		//宝箱出現
		for (int nCount = 0; nCount < 3; nCount++)
		{
			if (rand() % 3 < 2){ tex = CSceneModel::TEX_BOX_02; use = CSceneObjct::USE_DROP02; }
			else { tex = CSceneModel::TEX_BOX_01; use = CSceneObjct::USE_DROP01; }//モデルセット
			if (SceneCreate(pSceneModel, MODEL_PRIORITY))
			{
				pSceneModel->Set(DUNGEON_CENTER + D3DXVECTOR3(sinf(D3DX_PI * 0.666f * nCount), 0.0f, cosf(D3DX_PI * 0.666f * nCount)) * 10.0f,
					D3DXVECTOR3(0.0f, D3DX_PI * 0.666f * nCount, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_BOX_2, tex, CScene::DRAW_TYPE_NORMAL, true, use);
			}
		}

		//経験値
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{//プレイヤー分回転
			pPlayer = CManager::GetPlayer(nCount);
			if (pPlayer != NULL)
			{//生成されている && 生きているなら
				if (pPlayer->GetfLife()[0] > 0.0f){ fPlayer += 1.0f; }
			}
		}
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{//プレイヤー分回転
			pPlayer = CManager::GetPlayer(nCount);
			if (pPlayer != NULL)
			{//生成されている && 生きているなら
				if (pPlayer->GetfLife()[0] > 0.0f) { pPlayer->AddExp((int)((m_nLevel * 500.0f + 8000.0f) / fPlayer)); }
			}
		}
		break;
	}
	Uninit();
}
//=============================================================================
// ボスのステータス設定処理
//=============================================================================
void CSceneBoss::SetStatus(TEXTURE tex)
{
	m_TexType = tex;
	GetfCntState()[0] = 0;
	m_fModeChange = -1;
	GetState()[0] = CScene3D::STATE_WAIT;
	m_fPlusY = 0.0f;
	m_bJump = false;
	InitShadow();
	BindTexture(Load(tex));
	m_nLevel = CManager::GetPlayer(0)->GetnStage();
	switch (m_TexType)
	{
	case TEX_MANAGER:
		m_fMaxLife = 25000;
		m_fAttack =  100;
		m_fDefense = 80;
		break;
	case TEX_BOSS01:
		m_fMaxLife = 30000;
		m_fAttack = 95;
		m_fDefense = 70;
	}

	m_fMaxLife = ((m_fMaxLife * 0.032f) * m_nLevel) + m_fMaxLife;
	m_fMaxLife *= 1.0f + (CScenePlayer::GetnNumPlayer() - 1) * 0.5f;
	m_fLife = m_fMaxLife;
	m_fAttack = m_fAttack + ((m_fAttack * 0.01f) * m_nLevel);
	m_fDefense = m_fDefense + ((m_fDefense * 0.01f) * m_nLevel);
}
//=============================================================================
// UIの生成
//=============================================================================
void	CSceneBoss::CreateUI(TEXTURE tex)
{
	if (m_pUI == NULL)
	{//生成されていない
		if(SceneCreate(m_pUI, UI_PRIORITY))
		{
			C2DGage *&pGage = m_pUI->GetGage();
			C2D		*&p2D = m_pUI->Getp2D();

			if (p2D == NULL)
			{//アイコンが生成されていない
				if (Create(p2D))
				{
					p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 5 - SCREEN_WIDTH / 10 + 15.0f, SCREEN_HEIGHT - 32.5f, 0.0f), 
						SCREEN_WIDTH / 10 - 15.0f, 25.0f, D3DX_PI, tex, 1, TEXTURE_MAX, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_BossLabel);
				}
			}

			if (pGage == NULL)
			{//ゲージが生成されていない
				if (Create(pGage))
				{
					pGage->Set(D3DXVECTOR3(SCREEN_WIDTH / 5, SCREEN_HEIGHT - 32.5f, 0.0f), (SCREEN_WIDTH / 5.0f) * 4.0f - 30.0f, 25.0f, &m_fLife, &m_fMaxLife, true, C2DGage::STATE_LIFE);
				}
			}
		}//UIを生成
	}//if(NULL)
}
//=============================================================================
// 出現演出処理
//=============================================================================
void CSceneBoss::Appear(TEXTURE tex)
{
	if (CScenePlayer::GetbCamera())
	{
		CSceneBossEffect *pEffect;

		if (SceneCreate(pEffect, UI_PRIORITY))
		{//生成できたなら　演出実行
			pEffect->Set(tex);
		}
	}
}
//=============================================================================
// ダメージ処理
//=============================================================================
bool CSceneBoss::Damage(float fAtk)
{
	CSound *pSound = CManager::GetSound();

	fAtk *= (((rand() % 21) * 0.01f) + 1.0f);
	float fDef = m_fDefense * (((rand() % 21) * 0.1f) + 0.55f);
	int nDamage = (int)((fAtk / (fAtk + fDef)) * fAtk);
	if (nDamage < (int)(fAtk * 0.1f)) { nDamage = (int)(fAtk * 0.1f); }
	m_fLife -= (float)nDamage;

	if (m_fLife <= 0)
	{
		GetColor()[0].a = 0.0f;
		m_bShotDelete = false;
		CSceneBullet::BreakBullet(false);
		m_bShotDelete = true;
		return true;
	}
	else
	{
		CSceneAnim3D	*pScene3D;
		if (SceneCreate(pScene3D, SAnim3D_PRIORITY))
		{//生成できたなら　//火花
			pScene3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_HIT, CScene::DRAW_TYPE_OVERLAY,
				0, 5, 2, 8, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
		}
	}
	return false;
}
//=============================================================================
// 店長の初期化
//=============================================================================
HRESULT CSceneManager::Init(void)
{
	if (m_p2D == NULL)
	{//枠の初期化処理
		if (SceneCreate(m_p2D, FONT_PRIORITY))
		{//生成できた！
			m_p2D->Set(D3DXVECTOR3(690.0f, 215.0f, 0.0f), 100.0f, 20.0f, D3DX_PI, 0, 1, 1, 195.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_UIWindow);
			m_p2D->SetGage(0.0f, true);
		}
	}
	if (m_pFont == NULL)
	{//文字の初期化処理
		if (SceneCreate(m_pFont, FONT_PRIORITY))
		{//生成できた！
			m_pFont->Set(RECT{ 700 , 200, 1280, 720 }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), " ", 0, DT_LEFT, -1, true, CFont::STATE_NONE);
		}
	}
	CSceneBoss::Init();
	return S_OK;
}
//=============================================================================
// 店長の終了
//=============================================================================
void CSceneManager::Uninit(void)
{

	if (m_pFont != NULL)
	{//文字の終了処理
		m_pFont->Uninit();
		m_pFont = NULL;
	}
	if (m_p2D != NULL)
	{//文字の終了処理
		m_p2D->Uninit();
		m_p2D = NULL;
	}
	CScenePlayer::GetbShop() = false;
	CSceneBoss::Uninit();
	UnLoad(CSceneBoss::TEX_MANAGER);
}
//=============================================================================
// 店長の更新
//=============================================================================
void CSceneManager::Update(void)
{
	CSceneBoss::Update();
	CDungeon *pDungeon;

	if (m_Manager < MANAGER_DAMAGE && GetfLife() != GetfMaxLife())
	{//一度以上被弾している
		m_Manager = MANAGER_DAMAGE;
	}

	switch (m_Manager)
	{
	case MANAGER_START:
		if (GetfCntState()[0] == 10)
		{//入店して1秒後　ジャンプ
			m_Manager = MANAGER_WAIT;
			GetfCntState()[0] = 0;
			GetState()[0] = CScene3D::STATE_JUMP;
			m_pFont->SetFont("いらっしゃいませ～", 0);
			m_p2D->GetState()[0] = CScene2D::STATE_COL_FLOW;
			m_p2D->GetfLengthX() = 0.0f;
		}
		break;
	case MANAGER_BUY:
		m_Manager = MANAGER_WAIT;
		GetfCntState()[0] = 0;
		GetState()[0] = CScene3D::STATE_JUMP;
		m_pFont->SetFont("まいどあり～", 0);
		m_p2D->GetState()[0] = CScene2D::STATE_COL_FLOW;
		m_p2D->GetfLengthX() = 0.0f;
		break;
	case MANAGER_WAIT:
		//if (GetfCntState()[0] == 60)
		//{//入店して1秒後　ジャンプ
		//	GetfCntState()[0] = 0;
		//	GetState()[0] = CScene3D::STATE_JUMP;
		//}
		break;

	case MANAGER_DAMAGE:	//戦闘状態に
		m_Manager = MANAGER_HEEL;
		GetfCntState()[0] = 0;
		GetfModeChange() = -1;
		GetState()[0] = CScene3D::STATE_WAIT;
		//全体エフェクト
		pDungeon = CManager::GetDungeon();
		if (pDungeon != NULL){ pDungeon->InitBossBG(CScene3D::TEX_BG000); }
		CScenePlayer::GetbShop() = false;
		m_pFont->SetFont("　・　・　・　", 0);
		m_p2D->GetState()[0] = CScene2D::STATE_COL_FLOW;
		m_p2D->GetfLengthX() = 0.0f;
		break;

	case MANAGER_HEEL:
		GetfLife() = GetfMaxLife();
		if (GetfCntState()[0] == 60) { Appear(GetTexture()); }
		else if (GetfCntState()[0] == 90)
		{//エフェクト
			CSceneAnim3D	*pSceneAnim3D;
			if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
			{//生成できたなら　//エフェクト
				pSceneAnim3D->Set(GetPosition()[0],
					D3DXVECTOR3(0.0f, (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120.0f, 120.0f, CSceneAnim3D::TEX_BEFFECT, CScene::DRAW_TYPE_MULTIPLY,
					0, 2, 5, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
			}
			SetJump(1.5f);
			m_pFont->GetState() = CFont::STATE_FADEOUT2;
			m_p2D->GetState()[0] = CScene2D::STATE_FADEOUT2;
		}
		else if (GetfCntState()[0] == 120)
		{//攻撃へ
			m_Manager = MANAGER_ATK;
			CManager::GetDungeon()->SetQuake(120);
			CSceneAnim3D::BreakPolygon(CSceneAnim3D::STATE_SHOP);
			//全売り物をただのアイテムに
			BreakObject(CSceneObjct::OBJTYPE_NUMBER);
			CScene3D::BreakSale();
			m_Attack = ATTACK_START;
			GetfModeChange() = 30;
			GetfCntState()[0] = 0;
			CreateUI(GetTexture());
			m_pFont->Uninit(); m_pFont = NULL;
			m_p2D->Uninit(); m_p2D = NULL;
		}
		if (GetbJump())
		{
			GetMove().z += 0.8f;
		}
		break;

	case MANAGER_ATK:
		if (!m_bHalf && GetfLife() < GetfMaxLife() / 2)
		{//半分切った
			m_bHalf = true;
			m_Attack = ATTACK_HALF;
			GetfCntState()[0] = 0;
			GetfModeChange() = 800;
			CSceneAnim3D	*pSceneAnim3D;
			if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
			{//生成できたなら　//エフェクト
				pSceneAnim3D->Set(GetPosition()[0],
					D3DXVECTOR3(0.0f, (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120.0f, 120.0f, CSceneAnim3D::TEX_BEFFECT, CScene::DRAW_TYPE_MULTIPLY,
					0, 2, 5, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
			}
		}
		else if (GetState()[0] == CScene3D::STATE_CHANGE) 
		{
			GetState()[0] = CScene3D::STATE_WAIT;
			GetfCntState()[0] = 0;
			switch (rand() % (m_bHalf ? 4 : 3))
			{
			case 0:	m_Attack = ATTACK_0; GetfModeChange() = (m_bHalf ? 180.0f : 240.0f); break;	//150 - 180
			case 1:	m_Attack = ATTACK_1; GetfModeChange() = (m_bHalf ? 120.0f : 180.0f); break;	//60 - 120
			case 2:	m_Attack = ATTACK_2; GetfModeChange() = (m_bHalf ? 150.0f : 220.0f); break;	//60 - 120
			case 3:	m_Attack = ATTACK_3; GetfModeChange() = (m_bHalf ? 200.0f : 260.0f); break;
			}
		}
		switch (m_Attack)
		{
		case ATTACK_START:	Attack_Start(); break;
		case ATTACK_HALF:	Attack_Half();	break;
		case ATTACK_0:		Attack_0();		break;
		case ATTACK_1:		Attack_1();		break;
		case ATTACK_2:		Attack_2();		break;
		case ATTACK_3:		Attack_3();		break;
		}
		break;
	}
}
//=============================================================================
// 始めの攻撃
//=============================================================================
void CSceneManager::Attack_Start(void)
{
	CScenePairBulletSet *pPairBulletSet;

	switch ((int)GetfCntState()[0])
	{
	case 1:
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0].y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			8.0f, 8.0f, D3DX_PI * 1.1f, -10.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 500.0f, true, &GetbShotDelete(), 16 * 3 + 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 3 + 2,
				SHOT_LIFE - 300.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, GetfAtk() + 200.0f, GetRotation()[0].y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y, D3DX_PI * 0.02f, 1, 3,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 3 + 2,
				SHOT_LIFE - 300.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, GetfAtk() + 200.0f, GetRotation()[0].y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y, D3DX_PI * -0.02f, 1, 3,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
}
//=============================================================================
// 半減時の攻撃
//=============================================================================
void CSceneManager::Attack_Half(void)
{
	float fCntState = GetfCntState()[0];
	D3DXVECTOR3 pos;
	CScene3D *p3D;

	if (fCntState == 1)
	{//ジャンプと準備
		SetJump(3.0f);
		m_Target.y = 0.0f;
	}
	if (fCntState > 30)
	{//飛んだあと
		if (fCntState < 600)
		{//ひたすら攻撃
			GetfPlusY() = 50.0f;
			GetMove().y = 0.0f;
			if (fCntState > 90)
			{//攻撃開始
				if ((int)fCntState % 30 == 0)
				{//一定間隔で攻撃
					if (m_Target.y == PLAYER_Y)
					{
						CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN00, m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.0f, 0.0f, SHOT_LIFE - 10, 0.0f, 0.0f,
							15.0f, 15.0f, D3DX_PI * 1.1f, 0.0f, 1, 0, CSceneBullet::CHANGE_NO, GetfAtk() + 800, true, &GetbShotDelete(), 16 * 3 + 2);
						CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_DIFFUSION, m_Target, D3DXVECTOR3(0.0f, (rand() % 200) * 0.01f * D3DX_PI, 0.0f), GetfAngle(), true, 0.01f, 0.98f, SHOT_LIFE * 0.9f, 0.0f, 0.0f,
							2.0f, 2.0f, D3DX_PI * 1.1f, 10.0f, 4, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 200, true, &GetbShotDelete(), 16 * 1 + 2);
					}
					pos = GetPosition()[0]; m_Target = CManager::GetRandPlayer()->GetPosition()[0] + D3DXVECTOR3((float)(rand() % 200 - 100), 0.0f, (float)(rand() % 200 - 100)) * 0.1f;
					for (int nCount = 0; nCount < 3; nCount++)
					{
						if (SceneCreate(p3D, S3DF_PRIORITY))
						{//危険知らせエフェクト
							p3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 20.0f, 20,
								CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
							p3D->GetState()[0] = CScene3D::STATE_FADEOUT; p3D->BindTexture(C3D::Load(C3D::TEX_SHADOW));
						}
					}
					CSceneAnim3D	*pSceneAnim3D;
					if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
					{//生成できたなら　//エフェクト
						pSceneAnim3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 30.0f, 30.0f,
							CSceneAnim3D::TEX_MAGIC, CScene::DRAW_TYPE_OVERLAY, 0, 14, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADE);
					}
				}//if(一定間隔で攻撃)
			}//if(攻撃開始)
		}
		else if(fCntState == 630)
		{//着地
			m_Attack = ATTACK_START;
			GetfModeChange() = 30;
			GetfCntState()[0] = 0;
			CManager::GetDungeon()->SetQuake(120);
		}
	}
}
//=============================================================================
// 攻撃パターン0
//=============================================================================
void CSceneManager::Attack_0(void)
{
	CScenePairBulletSet *pPairBulletSet;
	D3DXVECTOR3 pos, Target;
	CScene3D *p3D;
	switch ((int)GetfCntState()[0])
	{
	case 1:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 3 + 2,
				SHOT_LIFE - 30.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.04f, 0.97f, GetfAtk() + 200.0f, GetRotation()[0].y - D3DX_PI * 0.666f, 10.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y, D3DX_PI * 0.04f, 1, 1,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case 46:
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 3 + 2,
				SHOT_LIFE - 30.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.04f, 0.97f, GetfAtk() + 200.0f, GetRotation()[0].y + D3DX_PI * 0.666f, 10.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y, D3DX_PI * -0.04f, 1, 1,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case 61:
		pos = GetPosition()[0]; Target = CManager::GetRandPlayer()->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		if (SceneCreate(p3D, S3DF_PRIORITY))
		{//危険知らせエフェクト
			p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 100.0f, 1.0f, cosf(GetfAngle()) * 100.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 5.0f, 100.0f,
				CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
			p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
		}
		break;
	case 91:
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_BEAM00, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.97f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			5.0f, 10.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 800, false, &GetbShotDelete(), 16 * 1 + 2);

		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_SETTING0, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0].y + D3DX_PI * 0.5f, true, 0.03f, 0.97f, SHOT_LIFE - 30.0f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.26f, 5.0f, 1, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 300, false, &GetbShotDelete(), 16 * 3 + 2);
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_SETTING0, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0].y + D3DX_PI * -0.5f, true, 0.03f, 0.97f, SHOT_LIFE - 30.0f, 0.0f, 0.0f,
			2.5f, 2.5f, D3DX_PI * 0.26f, 5.0f, 1, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 300, false, &GetbShotDelete(), 16 * 3 + 2);

		break;
	}
}
//=============================================================================
// 攻撃パターン1
//=============================================================================
void CSceneManager::Attack_1(void)
{
	D3DXVECTOR3 pos, Target;
	CScene3D *p3D;
	switch ((int)GetfCntState()[0])
	{
	case 1:
		pos = GetPosition()[0]; Target = CManager::GetRandPlayer()->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		if (SceneCreate(p3D, S3DF_PRIORITY))
		{//危険知らせエフェクト
			p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 100.0f, 1.0f, cosf(GetfAngle()) * 100.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 10.0f, 100.0f,
				CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
			p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
		}
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0].y + D3DX_PI * -0.5f, true, 0.01f, 0.97f, SHOT_LIFE * 0.7f, 0.0f, 0.0f,
			1.75f, 1.75f, D3DX_PI * 1.1f, 5.0f, 64, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 200, false, &GetbShotDelete(), 16 * 3 + 2);
		break;
	case 61:
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_BEAM00, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.05f, 0.97f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			10.0f, 20.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 800, false, &GetbShotDelete(), 16 * 1 + 2);
		break;
	}
}
//=============================================================================
// 攻撃パターン2
//=============================================================================
void CSceneManager::Attack_2(void)
{
	CScenePairBulletSet *pPairBulletSet;
	D3DXVECTOR3 pos;
	CScene3D *p3D;
	switch ((int)GetfCntState()[0])
	{
	case 1:
		pos = GetPosition()[0]; m_Target = CManager::GetRandPlayer()->GetPosition()[0];
		for (int nCount = 0; nCount < 3; nCount++)
		{
			if (SceneCreate(p3D, S3DF_PRIORITY))
			{//危険知らせエフェクト
				p3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 20.0f, 20,
					CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
				p3D->GetState()[0] = CScene3D::STATE_FADEOUT; p3D->BindTexture(C3D::Load(C3D::TEX_SHADOW));
			}
		}
		CSceneAnim3D	*pSceneAnim3D;
		if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
		{//生成できたなら　//エフェクト
			pSceneAnim3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 30.0f, 30.0f,
				CSceneAnim3D::TEX_MAGIC, CScene::DRAW_TYPE_OVERLAY, 0, 14, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADE);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0] + D3DXVECTOR3(0.0f, 2.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 1 + 2,
				SHOT_LIFE - 140, 0, 0.02f, 0.0f, D3DX_PI / 20, 0.97f, GetfAtk() + 100, GetRotation()[0].y, 10.0f, 0.1f, CSceneBullet::SET_BEAM, GetRotation()[0].y - D3DX_PI * 0.5f, D3DX_PI / 20, 1, 6,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	case 91:
		pos = CManager::GetRandPlayer()->GetPosition()[0];
		GetfAngle() = atan2f(pos.x - m_Target.x, pos.z - m_Target.z);

		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN00, m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.0f, 0.0f, SHOT_LIFE - 30, 0.0f, 0.0f,
			15.0f, 15.0f, D3DX_PI * 1.1f, 0.0f, 1, 0, CSceneBullet::CHANGE_NO, GetfAtk() + 800, false, &GetbShotDelete(), 16 * 3 + 2);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 16 * 1 + 2,
				SHOT_LIFE - 30, 0, 0.02f, 0.0f, 0.0f, 0.97f, GetfAtk() + 100.0f, GetfAngle(), 0.0f, 0.0f, CSceneBullet::SET_RANDSHOT, GetfAngle(), 0.0f, 1, 1,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
}
//=============================================================================
// 攻撃パターン3
//=============================================================================
void CSceneManager::Attack_3(void)
{
	switch ((int)GetfCntState()[0])
	{
	case 1:
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PDIFFUSION2, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0].y + D3DX_PI * 0.5f, true, 0.01f, 0.97f, SHOT_LIFE - 10.0f, 0.0f, 0.0f,
			2.0f, 2.0f, D3DX_PI * 1.1f, 5.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 200, false, &GetbShotDelete(), 16 * 3 + 2);
		break;
	}

}
//=============================================================================
// 店長のセット
//=============================================================================
void CSceneManager::Set(D3DXVECTOR3 pos)
{
	CScene3D::Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SBOSS_LENGTH * 0.85f, SBOSS_LENGTH, 
		CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ZNORMAL);
	CSceneBoss::SetStatus(TEX_MANAGER);
	GetfModeChange() = -1;
	m_Manager = MANAGER_START;
	m_bFly = true;
	m_Attack = ATTACK_START;
	m_Target = pos;
	m_bHalf = false;
	CScenePlayer::GetbShop() = true;
	CSceneAnim3D::Load(CSceneAnim3D::TEX_BEFFECT);
	CSceneAnim3D::Load(CSceneAnim3D::CSceneAnim3D::TEX_MAGIC);
}
//=============================================================================
// 店長の終了
//=============================================================================
void CSceneBoss01::Uninit(void)
{
	CSceneBoss::Uninit();
}

//=============================================================================
// 初期BOSSの更新
//=============================================================================
void CSceneBoss01::Update(void)
{
	CSceneBoss::Update();
	CDungeon *pDungeon;

	if (m_nStart < 0)
	{//まだ登場していない
		if (GetbJump() == false)
		{
			m_nStart = 0;
			CManager::GetDungeon()->SetQuake(60);
		}
	}
	else
	{//既に登場している
		if (m_nStart < 90)
		{
			m_nStart++;
			switch (m_nStart)
			{
			case 60:
				Appear(GetTexture());
				break;
			case 90:
				pDungeon = CManager::GetDungeon();
				if (pDungeon != NULL) { pDungeon->InitBossBG(CScene3D::TEX_BG000); }
				GetfLife() = GetfMaxLife();
				GetfCntState()[0] = 0;
				GetfModeChange() = 280.0f;
				m_Attack = ATTACK_3;
				CreateUI(GetTexture());
				break;
			}
		}
		else if (!m_bHalf && GetfLife() < GetfMaxLife() / 2)
		{//半分切った
			m_bHalf = true;
			m_Attack = ATTACK_HALF;
			GetfCntState()[0] = 0;
			GetfModeChange() = 800;
			CSceneAnim3D	*pSceneAnim3D;
			if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
			{//生成できたなら　//エフェクト
				pSceneAnim3D->Set(GetPosition()[0],
					D3DXVECTOR3(0.0f, (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 120.0f, 120.0f, CSceneAnim3D::TEX_BEFFECT, CScene::DRAW_TYPE_MULTIPLY,
					0, 2, 5, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
			}
		}
		else if (GetState()[0] == CScene3D::STATE_CHANGE)
		{
			GetState()[0] = CScene3D::STATE_WAIT;
			GetfCntState()[0] = 0;
			switch (rand() % (m_bHalf ? 4 : 3))
			{
			case 0:	m_Attack = ATTACK_0; GetfModeChange() = (m_bHalf ? 210.0f : 270.0f); break;	//150 - 210
			case 1:	m_Attack = ATTACK_1; GetfModeChange() = (m_bHalf ? 150.0f : 210.0f); break;	//90 - 150
			case 2:	m_Attack = ATTACK_2; GetfModeChange() = (m_bHalf ? 240.0f : 300.0f); break;	//180 - 240
			case 3:	m_Attack = ATTACK_3; GetfModeChange() = (m_bHalf ? 280.0f : 310.0f); break;
			case 4:	m_Attack = ATTACK_HALF; GetfModeChange() = (m_bHalf ? 500.0f : 500.0f); break;
			}
		}
		switch (m_Attack)
		{
		case ATTACK_START:	Attack_Start(); break;
		case ATTACK_HALF:	Attack_Half();	break;
		case ATTACK_0:		Attack_0();		break;
		case ATTACK_1:		Attack_1();		break;
		case ATTACK_2:		Attack_2();		break;
		case ATTACK_3:		Attack_3();		break;
		}
	}
}
//=============================================================================
// 初期BOSS：始めの攻撃
//=============================================================================
void CSceneBoss01::Attack_Start(void)
{
	CScenePairBulletSet *pPairBulletSet;

	switch ((int)GetfCntState()[0])
	{
	case 1:
		CManager::GetDungeon()->SetQuake(120);
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0].y, true, 0.01f, 0.97f, SHOT_LIFE * 0.5f, 0.0f, 0.0f,
			8.0f, 8.0f, D3DX_PI * 1.1f, -10.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 500.0f, true, &GetbShotDelete(), 16 * 6 + BOSS01_UV);
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 3 + BOSS01_UV,
				SHOT_LIFE - 100.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.02f, 0.97f, GetfAtk() + 200.0f, GetRotation()[0].y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y, D3DX_PI * 0.06f, 2, 8,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 2.0f, 2.0f, 16 * 3 + BOSS01_UV,
				SHOT_LIFE - 100.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.02f, 0.97f, GetfAtk() + 200.0f, GetRotation()[0].y, 10.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y, D3DX_PI * -0.06f, 2, 8,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		break;
	}
}
//=============================================================================
// 初期BOSS：半減時の攻撃
//=============================================================================
void CSceneBoss01::Attack_Half(void)
{
	float fCntState = GetfCntState()[0];
	CSceneNorBullet *pBullet;
	D3DXVECTOR3 pos, Target;
	CSceneAnim3D	*pSceneAnim3D;
	CScene3D *p3D;

	if (fCntState == 0) { GetfDef() *= 100.0f; }
	if (fCntState >= 60)
	{
		if (fCntState < 420)
		{
			if ((int)fCntState % 60 == 0)
			{
				//危険地帯生成
				pos = GetPosition()[0]; Target = CManager::GetRandPlayer()->GetPosition()[0];
				GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
				if (SceneCreate(p3D, S3DF_PRIORITY))
				{//危険知らせエフェクト
					p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 100.0f, 1.0f, cosf(GetfAngle()) * 100.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 10.0f, 100.0f,
						CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
					p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
				}
			}
			if ((int)fCntState % 60 >= 40)
			{
				if (GetbCollision())
				{//壁に当たった！
					CManager::GetDungeon()->SetQuake(60);
					GetfCntState()[0] += 59 - ((int)fCntState % 60);
					CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.9f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
						4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, 8, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 200, false, &GetbShotDelete(), 16 * 3 + 2);
				}
				else
				{
					GetMove() += D3DXVECTOR3(sinf(GetfAngle()), 0.0f, cosf(GetfAngle())) * 10.0f;
				}
				if (SceneCreate(pBullet, BULLET_PRIORITY))
				{//生成できたなら
					pBullet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 20.0f, 16 * 1 + BOSS01_UV,
						SHOT_LIFE - 10.0f, 0, 0.0f, 0.0f, D3DX_PI * 0.0f, 0.97f, CSceneBullet::CHANGE_NO, (GetfAtk() + 250.0f) * 2.0f, true, &GetbShotDelete());
				}
			}
		}
		else
		{//ジャンプ中移動
			if ((int)fCntState == 420)
			{
				pos = GetPosition()[0]; m_Target = DUNGEON_CENTER;
				m_JumpMove = (m_Target - pos) / 100;

				for (int nCount = 0; nCount < 3; nCount++)
				{
					if (SceneCreate(p3D, S3DF_PRIORITY))
					{//危険知らせエフェクト
						p3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 20.0f, 20,
							CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
						p3D->GetState()[0] = CScene3D::STATE_FADEOUT; p3D->BindTexture(C3D::Load(C3D::TEX_SHADOW));
					}
				}
				if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
				{//生成できたなら　//エフェクト
					pSceneAnim3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 30.0f, 30.0f,
						CSceneAnim3D::TEX_MAGIC, CScene::DRAW_TYPE_OVERLAY, 0, 14, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADE);
				}
				SetJump(4.98f);
				CManager::GetDungeon()->SetQuake(30);
			}
			if ((int)fCntState < 520)
			{//ジャンプ中移動
				GetPosition()[0] += m_JumpMove;
			}
			if ((int)fCntState == 519)
			{
				GetfModeChange() = 90;
				GetfCntState()[0] = 0;
				m_Attack = ATTACK_START;
				GetfDef() /= 100.0f;
			}
		}
	}
}
//=============================================================================
// 初期BOSS：攻撃パターン0
//=============================================================================
void CSceneBoss01::Attack_0(void)
{
	CSceneNorBullet *pBullet;
	CScenePairBulletSet *pPairBulletSet;

	D3DXVECTOR3 pos, Target;
	CScene3D *p3D;
	float fWKAngle;
	//突進, 自機方向小ばら撒き, ゲロビ

	if(GetfCntState()[0] > 45.0f && GetfCntState()[0] < 65.0f)
	{ 
		if (GetbCollision())
		{//壁に当たった！
			CManager::GetDungeon()->SetQuake(60);
			GetfCntState()[0] = 65.0f;
			CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.9f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
				4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 200, false, &GetbShotDelete(), 16 * 3 + 2);
		}
		else
		{ 
			GetMove() += D3DXVECTOR3(sinf(GetfAngle()), 0.0f, cosf(GetfAngle())) * 10.0f;
		}
		if (SceneCreate(pBullet, BULLET_PRIORITY))
		{//生成できたなら
			pBullet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 20.0f, 16 * 1 + BOSS01_UV,
				SHOT_LIFE - 10.0f, 0, 0.0f, 0.0f, D3DX_PI * 0.0f, 0.97f, CSceneBullet::CHANGE_NO, (GetfAtk() + 250.0f) * 2.0f, true, &GetbShotDelete());
		}
	}

	switch ((int)GetfCntState()[0])
	{
	case 1:
		pos = GetPosition()[0]; Target = CManager::GetRandPlayer()->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		if (SceneCreate(p3D, S3DF_PRIORITY))
		{//危険知らせエフェクト
			p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 100.0f, 1.0f, cosf(GetfAngle()) * 100.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 10.0f, 100.0f,
				CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
			p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
		}
		break;
	case 90:
		pos = GetPosition()[0]; Target = CManager::GetNearPlayer(GetPosition()[0])->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		fWKAngle = GetfAngle() + D3DX_PI * 0.5f;
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 3.0f, 3.0f, 16 * 3 + BOSS01_UV,
				SHOT_LIFE - 30.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.03f, 0.97f, GetfAtk() + 200.0f, fWKAngle, 10.0f, 0.1f, CSceneBullet::SET_SHOT, fWKAngle, D3DX_PI * -0.03f, 1, 2,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}

		if (SceneCreate(p3D, S3DF_PRIORITY))
		{//危険知らせエフェクト
			p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 100.0f, 1.0f, cosf(GetfAngle()) * 100.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 5.0f, 100.0f,
				CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
			p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
		}
		break;
	case 120:
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_BEAM00, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.05f, 0.97f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			5.0f, 20.0f, D3DX_PI * 0.128f, 3.0f, 1, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 800, false, &GetbShotDelete(), 16 * 1 + 2);

	}
}
//=============================================================================
// 初期BOSS：攻撃パターン1
//=============================================================================
void CSceneBoss01::Attack_1(void)
{
	CSceneNorBullet *pBullet;
	D3DXVECTOR3 pos, Target;
	CScene3D *p3D;

	if (GetfCntState()[0] > 45.0f && GetfCntState()[0] < 50.0f)
	{
		if (GetbCollision())
		{//壁に当たった！
			CManager::GetDungeon()->SetQuake(60);
			GetfCntState()[0] = 50.0f;
			CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.9f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
				4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 250, false, &GetbShotDelete(), 16 * 3 + 2);
		}
		else
		{
			GetMove() += D3DXVECTOR3(sinf(GetfAngle()), 0.0f, cosf(GetfAngle())) * 10.0f;
		}
		if (SceneCreate(pBullet, BULLET_PRIORITY))
		{//生成できたなら
			pBullet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 20.0f, 16 * 1 + BOSS01_UV,
				SHOT_LIFE - 10.0f, 0, 0.0f, 0.0f, D3DX_PI * 0.0f, 0.97f, CSceneBullet::CHANGE_NO, (GetfAtk() + 250.0f) * 2.0f, true, &GetbShotDelete());
		}
	}
	else if (GetfCntState()[0] >= 50.0f && GetfCntState()[0] < 65.0f)
	{
		m_nReplay++;
		if (m_nReplay == 2) { GetfCntState()[0] = 90; m_nReplay = 0; }
		else
		{
			GetfCntState()[0] = 35.0f;
			pos = GetPosition()[0]; Target = CManager::GetNearPlayer(GetPosition()[0])->GetPosition()[0];
			GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
			if (SceneCreate(p3D, S3DF_PRIORITY))
			{//危険知らせエフェクト
				p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 30.0f, 1.0f, cosf(GetfAngle()) * 30.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 10.0f, 30.0f,
					CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
				p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
			}
		}
	}

	switch ((int)GetfCntState()[0])
	{
	case 1:
		SetJump(0.8f);
		break;
	case 15:
		SetJump(0.8f);
		break;
	case 30:
		pos = GetPosition()[0]; Target = CManager::GetNearPlayer(GetPosition()[0])->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		if (SceneCreate(p3D, S3DF_PRIORITY))
		{//危険知らせエフェクト
			p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 30.0f, 1.0f, cosf(GetfAngle()) * 30.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 10.0f, 30.0f,
				CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
			p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
		}
		break;
	}

}
//=============================================================================
// 初期BOSS：攻撃パターン2
//=============================================================================
void CSceneBoss01::Attack_2(void)
{
	CSceneNorBullet *pBullet;
	CScenePairBulletSet *pPairBulletSet;
	D3DXVECTOR3 pos, Target;
	CSceneAnim3D	*pSceneAnim3D;
	CScene3D *p3D;

	if ((int)GetfCntState()[0] < 100)
	{//ジャンプ中移動
		GetPosition()[0] += m_JumpMove;
	}
	if (GetfCntState()[0] > 130.0f && GetfCntState()[0] < 180.0f)
	{
		if (GetbCollision())
		{//壁に当たった！
			CManager::GetDungeon()->SetQuake(60);
			GetfCntState()[0] = 180.0f;
			CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.9f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
				4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 250, false, &GetbShotDelete(), 16 * 3 + 2);
		}
		else
		{
			GetMove() += D3DXVECTOR3(sinf(GetfAngle()), 0.0f, cosf(GetfAngle())) * 10.0f;
		}
		if (SceneCreate(pBullet, BULLET_PRIORITY))
		{//生成できたなら
			pBullet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 20.0f, 16 * 1 + BOSS01_UV,
				SHOT_LIFE - 10.0f, 0, 0.0f, 0.0f, D3DX_PI * 0.0f, 0.97f, CSceneBullet::CHANGE_NO, (GetfAtk() + 250.0f) * 2.0f, true, &GetbShotDelete());
		}
	}

	switch ((int)GetfCntState()[0])
	{
	case 0: //飛ぶ
		pos = GetPosition()[0]; m_Target = CManager::GetNearPlayer(GetPosition()[0])->GetPosition()[0];
		m_JumpMove = (m_Target - pos) / 100;

		for (int nCount = 0; nCount < 3; nCount++)
		{
			if (SceneCreate(p3D, S3DF_PRIORITY))
			{//危険知らせエフェクト
				p3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 20.0f, 20,
					CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
				p3D->GetState()[0] = CScene3D::STATE_FADEOUT; p3D->BindTexture(C3D::Load(C3D::TEX_SHADOW));
			}
		}
		if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
		{//生成できたなら　//エフェクト
			pSceneAnim3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 30.0f, 30.0f,
				CSceneAnim3D::TEX_MAGIC, CScene::DRAW_TYPE_OVERLAY, 0, 14, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADE);
		}
		SetJump(4.98f);
		CManager::GetDungeon()->SetQuake(30);
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.01f, 0.99f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			3.0f, 3.0f, D3DX_PI * 1.1f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 200, false, &GetbShotDelete(), 16 * 3 + 2);
		break;
	case 100: //着地
		CManager::GetDungeon()->SetQuake(120);
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.9f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, 16, 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 250, false, &GetbShotDelete(), 16 * 3 + 2);

		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 4.0f, 8.0f, 16 * 6 + 2,
				SHOT_LIFE - 70.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.06f, 0.97f, (GetfAtk() + 250.0f) * 2, GetRotation()[0].y - D3DX_PI * 0.5f, 10.0f, 0.1f, CSceneBullet::SET_EFFECT, GetRotation()[0].y, D3DX_PI * 0.06f, 1, 1,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}
		if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
		{//生成できたなら
			pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetRotation()[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), 4.0f, 8.0f, 16 * 6 + 2,
				SHOT_LIFE - 70.0f, 0, 0.01f, 0.0f, D3DX_PI * -0.06f, 0.97f, (GetfAtk() + 250.0f) * 2, GetRotation()[0].y + D3DX_PI * 0.5f, 10.0f, 0.1f, CSceneBullet::SET_EFFECT, GetRotation()[0].y, -D3DX_PI * 0.06f, 1, 1,
				GetPosition(), NULL, &GetbShotDelete());
			pPairBulletSet->SetObjType(CScene::OBJTYPE_BULLET2);
		}

		pos = GetPosition()[0]; Target = CManager::GetNearPlayer(GetPosition()[0])->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		if (SceneCreate(p3D, S3DF_PRIORITY))
		{//危険知らせエフェクト
			p3D->Set(pos + D3DXVECTOR3(sinf(GetfAngle()) * 100.0f, 1.0f, cosf(GetfAngle()) * 100.0f), D3DXVECTOR3(0.0f, GetfAngle(), 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 15.0f, 100.0f,
				CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
			p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
		}
		break;
	}
}
//=============================================================================
// 初期BOSS：攻撃パターン3
//=============================================================================
void CSceneBoss01::Attack_3(void)
{
	CScenePairBulletSet *pPairBulletSet;
	D3DXVECTOR3 pos, Target;
	CSceneAnim3D	*pSceneAnim3D;
	CScene3D *p3D;

	if ((int)GetfCntState()[0] < 100)
	{//ジャンプ中移動
		GetPosition()[0] += m_JumpMove;
	}

	switch ((int)GetfCntState()[0])
	{
	case 0: //飛ぶ
		pos = GetPosition()[0]; m_Target = DUNGEON_CENTER;
		m_JumpMove = (m_Target - pos) / 100;

		for (int nCount = 0; nCount < 3; nCount++)
		{
			if (SceneCreate(p3D, S3DF_PRIORITY))
			{//危険知らせエフェクト
				p3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 20.0f, 20,
					CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
				p3D->GetState()[0] = CScene3D::STATE_FADEOUT; p3D->BindTexture(C3D::Load(C3D::TEX_SHADOW));
			}
		}
		if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
		{//生成できたなら　//エフェクト
			pSceneAnim3D->Set(m_Target, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 30.0f, 30.0f,
				CSceneAnim3D::TEX_MAGIC, CScene::DRAW_TYPE_OVERLAY, 0, 14, 1, 3, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADE);
		}
		SetJump(4.98f);
		CManager::GetDungeon()->SetQuake(30);
		break;
	case 100: //着地
		CManager::GetDungeon()->SetQuake(120);
		pos = GetPosition()[0]; Target = CManager::GetNearPlayer(GetPosition()[0])->GetPosition()[0];
		GetfAngle() = atan2f(Target.x - pos.x, Target.z - pos.z);
		CSceneBullet::ShotAttack(CSceneBullet::SHOT_ENEMY, CSceneBullet::ATK_PTN03, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), GetfAngle(), true, 0.03f, 0.9f, SHOT_LIFE * 0.8f, 0.0f, 0.0f,
			4.0f, 4.0f, D3DX_PI * 1.1f, 0.0f, (m_bHalf ? 16 : 16), 0, CSceneBullet::CHANGE_FAST2, GetfAtk() + 250, false, &GetbShotDelete(), 16 * 3 + 2);
		for (int nCount = 0; nCount < 2; nCount++)
		{
			if (SceneCreate(p3D, S3DF_PRIORITY))
			{//危険知らせエフェクト
				p3D->Set(pos + D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle() + nCount * D3DX_PI * 0.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f), 5.0f, 200.0f,
					CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ADD);
				p3D->GetState()[0] = CScene3D::STATE_FADEOUT;
			}
		}
		break;
	case 130:
		for (int nCount = 0; nCount < 4; nCount++)
		{
			if (SceneCreate(pPairBulletSet, BULLET_PRIORITY))
			{//生成できたなら
				pPairBulletSet->Set(CSceneBullet::SHOT_ENEMY, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, GetfAngle() -D3DX_PI * 0.5f + (D3DX_PI * nCount * 0.5f), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 5.0f, 200.0f, 16 * 0 + 2,
					SHOT_LIFE - 150.0f, 0, 0.01f, 0.0f, D3DX_PI * 0.005f, 0.97f, (GetfAtk() + 250.0f) * 2, GetRotation()[0].y - D3DX_PI * 0.5f + (D3DX_PI * nCount), 0.0f, 0.1f, CSceneBullet::SET_SHOT, GetRotation()[0].y - D3DX_PI * 0.5f + (D3DX_PI * nCount), D3DX_PI * 0.005f, 1, 300,
					GetPosition(), NULL, &GetbShotDelete());
			}
		}
		break;
	}

}
//=============================================================================
// 初期BOSSのセット
//=============================================================================
void CSceneBoss01::Set(D3DXVECTOR3 pos)
{
	CScene3D::Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SBOSS_LENGTH * 0.85f, SBOSS_LENGTH,
		CScene3D::TEXTURE_MAX, 0, 1, 1, CScene::DRAW_TYPE_ZNORMAL);
	CSceneBoss::SetStatus(TEX_BOSS01);
	GetfModeChange() = -1;
	GetMove().y = 1.0f;
	GetbJump() = true;
	GetfPlusY() = 120.0f;
	m_Attack = ATTACK_MAX;
	m_Target = pos;
	m_bHalf = false;
	m_nStart = -1;
	m_nReplay = 0;
	CSceneAnim3D::Load(CSceneAnim3D::TEX_BEFFECT);
	CSceneAnim3D::Load(CSceneAnim3D::CSceneAnim3D::TEX_MAGIC);
}
