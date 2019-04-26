//=============================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "gan.h"
#include "effect.h"
#include "time.h"
#include "fade.h"
#include "game.h"
#include "explosion.h"
#include "damage.h"
#include "life.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1			"data\\TEXTURE\\PlayerButtleShip.png"		//読み込むテクスチャファイル
#define	TEXTURE_WIDTH			(25)										//画像の横サイズ
#define TEXTURE_HEIGHT			(85)										//画像の縦サイズ
#define SINCOS_ANGLE_135		(0.75f)										//sin,cos角度（0.75）				
#define SINCOS_ANGLE_90			(0.5f)										//sin,cos角度（0.5）
#define SINCOS_ANGLE_45			(0.25f)										//sin,cos角度（0.25）
#define SINCOS_ANGLE_0			(0.0f)										//sin,cos角度（0.0）
#define SHIP_ROT				(0.45f)										//角度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[MAX_TEXTURE] = {};
float CPlayer::m_fLife = 0.0f;
float CPlayer::m_fMaxLife = 0.0f;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CPlayer::CPlayer() : CScene2D(3)//優先優位イニシャライズ
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterState = 0;
	m_state = PLAYERSTATE_NORMAL;
	CGame::GetPlayer() = this;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CPlayer::~CPlayer()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//銃を設置する
	CGan::Create(D3DXVECTOR2(12.0f, 30.0f), CGan::GANTYPE_PLAYER, CGan::GAN_CANNON, 0);

	CScene2D::Init();

	//種類の設定
	CScene::SetObjType(CScene::OBJTYPE_PLAYER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	CGame::GetPlayer() = NULL;
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	CScene2D::Update();

	float nPlayerSpeed = 0.5f;

	//カラーの宣言と初期化
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	
	//位置の代入
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//移動量の代入
	D3DXVECTOR3 move;
	move = GetMove();

	//エフェクトの生成
	//CEffect::Create(pos, D3DXVECTOR2(30, 30), -25.0f, 20, CEffect::EFFECTTYPE_RIPPLE, 0);
	
	//プレイヤーがエリア外にでない処理
	if (pos.x - m_Size.x < 320)
	{//画面反対側に移動（左）
		pos.x = 320 + m_Size.x;
	}
	if (pos.x + m_Size.x > SCREEN_WIDTH - 320)
	{//画面反対側に移動（右）
		pos.x = SCREEN_WIDTH - 320 - m_Size.x;
	}
	if (pos.y - m_Size.y < 0)
	{//画面反対側に移動（上）
		pos.y = m_Size.y;
	}
	if (pos.y + m_Size.y > SCREEN_HEIGHT)
	{//画面反対側に移動（下） 
		pos.y = SCREEN_HEIGHT - m_Size.y;
	}

	// 長さを出す
	m_fLength = sqrtf((m_Size.x + m_Size.x) * (m_Size.y + m_Size.y));
	// 角度を出す
	m_fAngle = atan2f(m_Size.x / 2, m_Size.y / 2);

	//移動方向処理
	if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
	{//任意のキー（Aキー、左キー）を押した場合

		if (m_rot.x < SHIP_ROT && m_rot.y < SHIP_ROT)
		{
			//左回転
			m_rot.x += 0.009f;
			m_rot.y += 0.009f;
		}
		else
		{
			//左回転
			m_rot.x = SHIP_ROT;
			m_rot.y = SHIP_ROT;
		}

		move.x += sinf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
		move.y += cosf(-D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
	}
	else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
	{//任意のキー（Dキー、右キー）を押した場合

		if (m_rot.x > -SHIP_ROT && m_rot.y > -SHIP_ROT)
		{
			//左回転
			m_rot.x -= 0.009f;
			m_rot.y -= 0.009f;
		}
		else
		{
			//左回転
			m_rot.x = -SHIP_ROT;
			m_rot.y = -SHIP_ROT;
		}
		
		move.x += sinf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
		move.y += cosf(D3DX_PI * SINCOS_ANGLE_90) * nPlayerSpeed;
	}
	//キーを離したら
	else if (m_rot.x <= SHIP_ROT && m_rot.y <= SHIP_ROT || m_rot.x >= -SHIP_ROT && m_rot.y >= -SHIP_ROT)
	{//現在の角度が0.45以下または以上の場合　初期値である0.0fに角度を戻す
		if (m_rot.x <= SHIP_ROT && m_rot.y <= SHIP_ROT)
		{//左に傾いていたら
			if (m_rot.x > 0.0f && m_rot.y > 0.0f)
			{
				m_rot.x -= 0.018f;
				m_rot.y -= 0.018f;
			}
		}
		if (m_rot.x >= -SHIP_ROT && m_rot.y >= -SHIP_ROT)
		{//右に傾いていたら
			if (m_rot.x < 0.0f && m_rot.y < 0.0f)
			{
				m_rot.x += 0.018f;
				m_rot.y += 0.018f;
			}
		}	
	}

	//状態確認
	switch (m_state)
	{
	case PLAYERSTATE_NORMAL:	//通常状態
		break;
	case PLAYERSTATE_DAMAGE:	//ダメージ状態
		//状態をカウント
		m_nCounterState--;

		if (m_nCounterState <= 0)
		{//状態カウント終了
			//色をもとに戻す
			Color[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Color[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Color[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Color[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//状態変化
			m_state = PLAYERSTATE_NORMAL;
		}
		break;
	case PLAYERSTATE_DEAHT:		//死亡状態
		//状態をカウント
		m_nCounterState--;
		break;
	}

	//位置を移動に代入
	pos.x += move.x;
	pos.y += move.y;

	//減速処理
	move.x += (0.0f - move.x) * 0.125f;
	move.y += (0.0f - move.y) * 0.125f;

	//カラーの割り当て
	CScene2D::SetColor(&Color[0]);

	//プレイヤーの位置とサイズ
	CScene2D::Set(pos,D3DXVECTOR2(m_Size.x, m_Size.y));

	//画像の回転
	CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);

	//移動量を割り当てる
	CScene2D::SetMove(move);
}
//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,float fLife)
{
	CPlayer *pPlayer = NULL;

	//NULLチェック
	if (pPlayer == NULL)
	{//メモリの動的確保

		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			//オブジェクトクラスの生成
			pPlayer->Init();
			//テクスチャを割り当てる
			pPlayer->BindTexture(m_pTexture[0]);
			//HPを割り当てる
			pPlayer->m_fLife = fLife;
			//最大HPの割り当て
			pPlayer->m_fMaxLife = fLife;
			//大きさと位置
			pPlayer->SetPosition(pos);
			//サイズ
			pPlayer->m_Size = size;
		}
	}
	return pPlayer;
}
//===============================================================================
// プレイヤーのダメージ処理
//===============================================================================
void CPlayer::HitPlayer(float fDamage)
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//カラーの宣言と初期化
	D3DXCOLOR Color[4];
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	if (m_fLife >= 1)
	{//ライフが１以上の時にダメージの処理を通す

		//HPからダメージ分を引く
		m_fLife -= fDamage;

		//ライフゲージから減らす
		CLife::AddLife(-(int)fDamage);

		//ダメージの数値を表示
		CDamage::Create();
		CDamage::AddDamage((int)fDamage);

		//HPが０以下の時の保険
		if (m_fLife <= 0)
		{
			m_fLife = 0;
		}
	}

	if (m_fLife <= 0)
	{//ライフが０以下の時
		//爆発音
		pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION000);
		//状態の代入
		m_state = PLAYERSTATE_DEAHT;	//死亡
		//プレイヤーの位置とサイズ
		CScene2D::SetPosition(pos);
		//ダメージ時間
		m_nCounterState = 30;
		//消える処理
		CExplosion::Create(pos, m_Size, 1);
		//エフェクトの生成
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 21, CEffect::EFFECTTYPE_RIPPLE, 0);
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 24, CEffect::EFFECTTYPE_RIPPLE, 0);
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 27, CEffect::EFFECTTYPE_RIPPLE, 0);
		CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 30, CEffect::EFFECTTYPE_RIPPLE, 0);
		m_fLife = 0;
		//ゲームからリザルトへ
		CGame::SetGameState(CGame::GAMESTATE_OVER);

		//プレイヤーの破棄
		CPlayer::Uninit();
	}
	else
	{//ライフが０以上の時
		//状態の代入
		m_state = PLAYERSTATE_DAMAGE;	//ダメージ
		//ダメージ時間
		m_nCounterState = 30;

		//テクスチャ設定
		Color[0] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		Color[1] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		Color[2] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);
		Color[3] = D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f);

		//カラーの割り当て
		CScene2D::SetColor(&Color[0]);
	}
}

//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CPlayer::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CPlayer::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
