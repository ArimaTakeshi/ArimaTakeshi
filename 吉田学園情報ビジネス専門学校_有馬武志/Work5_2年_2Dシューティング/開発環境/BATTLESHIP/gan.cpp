//=============================================================================
//
// 銃の処理 [gan.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "gan.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "game.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\PlayerGun.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_2	"data\\TEXTURE\\PlayerGunSky.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_3	"data\\TEXTURE\\PlayerGunDown.png"		//読み込むテクスチャファイル	
#define TEXTURE_NAME_4	"data\\TEXTURE\\FramPlayerGun.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_5	"data\\TEXTURE\\FramPlayerGunSky.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_6	"data\\TEXTURE\\FramPlayerGunDown.png"	//読み込むテクスチャファイル	
#define TORPEDO_COUNT	(80)									//魚雷を打つまでの時間
#define CANNON_COUNT	(80)									//大砲を打つまでの時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGan::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CGan::CGan() : CScene2D(4)//優先優位イニシャライズ
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_fLife = 0;
	m_nCount = 0;
	m_nCannonCount = 0;
	m_gantype = GAN_CANNON;
	m_nFram = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_bInitTex = false;
	m_fRot = 0.0f;
	m_fLength = 0.0f;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CGan::~CGan()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGan::Init(void)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_GAN);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGan::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGan::Update(void)
{
	CScene2D::Update();

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (pPlayer != NULL)
	{
		pos = pPlayer->GetPosition();

		//マウスのposを入れる箱
		D3DXVECTOR3 mousepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//マウスの座標を取得
		mousepos = *CInputMouse::GetMousePos();

		//マウスの方角を向く
		m_fRot = atan2f(mousepos.x - pos.x, mousepos.y - pos.y);
		
		if (m_nFram != 1)
		{//フレームじゃない場合のみ
			//回転
			CScene2D::SetRot(m_fRot, m_Size);
		}
	}

	////マウスの座標を取得
	/*POINT pt;
	GetCursorPos(&pt);*/

	//D3DXVECTOR3 pos = 

	//種類の代入
	static CBullet::BULLETTYPE type = CBullet::BULLETTYPE_PLAYER;

	if (m_nFram == 0)
	{
		//戦艦に銃を付ける
		Set(D3DXVECTOR3(pos.x, pos.y - 10, pos.z), D3DXVECTOR2(m_Size.x, m_Size.y));
	}
	else if (m_nFram == 1)
	{
		//表示武器の位置
		Set(D3DXVECTOR3(1120.0f, 570.0f, 0.0f), D3DXVECTOR2(m_Size.x, m_Size.y));
	}

	if (m_nFram == 1 && m_bInitTex == false)
	{//フレームじゃない場合のみ
		BindTexture(m_pTexture[3]);

		m_bInitTex = true;
	}

	//武器のチェンジ
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_1) == true)
	{//大砲
		//武器切り替えの音
		pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEAPON);

		m_gantype = GAN_CANNON;

		if (m_nFram == 0)
		{//武器のテクスチャ張替え
			BindTexture(m_pTexture[0]);
		}
		else
		{//フレームのテクスチャの張替え
			BindTexture(m_pTexture[3]);
		}
	}
	else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_2) == true)
	{//対空砲
		//武器切り替えの音
		pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEAPON);

		m_gantype = GAN_SKYCANNON;

		if (m_nFram == 0)
		{//武器のテクスチャ張替え
			BindTexture(m_pTexture[1]);
		}
		else
		{//フレームのテクスチャの張替え
			BindTexture(m_pTexture[4]);
		}
	}
	else if (pCInputKeyBoard->GetKeyboardTrigger(DIK_3) == true)
	{//魚雷
		//武器切り替えの音
		pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEAPON);

		m_gantype = GAN_TORPEDO;
		if (m_nFram == 0)
		{//武器のテクスチャ張替え
			BindTexture(m_pTexture[2]);
		}
		else
		{//フレームのテクスチャの張替え
			BindTexture(m_pTexture[5]);
		}
	}

	//弾の切り替え
	switch (m_gantype)
	{
	case GAN_CANNON:		//大砲
		//カウントを打ってないときにも++する　一定のnCountまできたら発射できる
		if (m_nCannonCount < CANNON_COUNT)
		{//値より小さい場合　足していく
			m_nCannonCount++;
		}
		if (m_nFram != 1)
		{//フレームじゃない場合のみ
			if (m_nCannonCount == CANNON_COUNT && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//大砲発射音
				pSound->PlaySound(CSound::SOUND_LABEL_PLAYERCANNON);

				//カウントを足す
				m_nCannonCount++;

				//発砲の爆発
				CExplosion::Create(D3DXVECTOR3(pos.x + 5, pos.y - 25, pos.z), D3DXVECTOR2(17, 17), 0);
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - 25, pos.z), D3DXVECTOR2(17, 17), 0);
				CExplosion::Create(D3DXVECTOR3(pos.x - 5, pos.y - 25, pos.z), D3DXVECTOR2(17, 17), 0);

				//弾の生成
				CBullet::Create(D3DXVECTOR3(pos.x + 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 30.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::PLAYER_SHIP, 0);
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 30.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::PLAYER_SHIP, 0);
				CBullet::Create(D3DXVECTOR3(pos.x - 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 30.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::PLAYER_SHIP, 0);
			}
			if (m_nCannonCount >= CANNON_COUNT + 1)
			{
  				m_nCannonCount = 0;
			}
		}
		break;
	case GAN_SKYCANNON:		//対空砲
		if (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true)
		{//弾の生成
			if (m_nFram != 1)
			{//フレームじゃない場合のみ
				if (rand() % 15 == 0)
				{
					//対空砲発射音
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x + 10, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x + 10, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::PLAYER_SHIP, 0);
				}
				if (rand() % 20 == 0)
				{
					//対空砲発射音
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x + 5, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x + 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::PLAYER_SHIP, 0);
				}
				if (rand() % 15 == 0)
				{
					//対空砲発射音
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x - 5, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x - 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::PLAYER_SHIP, 0);
				}
				if (rand() % 20 == 0)
				{
					//対空砲発射音
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CExplosion::Create(D3DXVECTOR3(pos.x - 10, pos.y - 25, pos.z), D3DXVECTOR2(7, 7), 2);
					CBullet::Create(D3DXVECTOR3(pos.x - 10, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 35.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::ENEMY_DIGHTER, 0);
				}
			}
		}
		break;
	case GAN_TORPEDO:		//魚雷
		//カウントを打ってないときにも++する　一定のnCountまできたら発射できる
		if (m_nCount < TORPEDO_COUNT)
		{//値より小さい場合　足していく
			m_nCount++;
		}
		else if (m_nCount < TORPEDO_COUNT * 2 && m_nCount > TORPEDO_COUNT)
		{//値より小さい場合　足していく
			m_nCount++;
		}
		else if (m_nCount < TORPEDO_COUNT * 3 && m_nCount > TORPEDO_COUNT * 2)
		{//値より小さい場合　足していく
			m_nCount++;
		}

		if (m_nFram != 1)
		{//フレームじゃない場合のみ
			if (m_nCount == TORPEDO_COUNT && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//魚雷砲発射音
				pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
				//カウントを足す
				m_nCount++;
				CExplosion::Create(D3DXVECTOR3(pos.x + 5, pos.y - 25, pos.z), D3DXVECTOR2(13, 13), 0);
				CBullet::Create(D3DXVECTOR3(pos.x + 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 5.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::PLAYER_SHIP, 1);
			}
			else if (m_nCount == TORPEDO_COUNT * 2 && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//魚雷砲発射音
				pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
				//カウントを足す
				m_nCount++;
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - 25, pos.z), D3DXVECTOR2(13, 13), 0);
				CBullet::Create(D3DXVECTOR3(pos.x, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 5.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::PLAYER_SHIP, 1);
			}
			else if (m_nCount == TORPEDO_COUNT * 3 && (pCInputKeyBoard->GetKeyboardPress(DIK_SPACE) == true || pCInputMouse->GetMousePress(0) == true))
			{
				//魚雷砲発射音
				pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);
				//カウントを足す
				m_nCount++;
				CExplosion::Create(D3DXVECTOR3(pos.x - 5, pos.y - 25, pos.z), D3DXVECTOR2(13, 13), 0);
				CBullet::Create(D3DXVECTOR3(pos.x - 5, pos.y - 20, pos.z), D3DXVECTOR3(sinf(m_fRot), cosf(m_fRot), 0.0f) * 5.0f, D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::PLAYER_SHIP, 1);
			}
			else if (m_nCount >= (TORPEDO_COUNT * 3) + 1)
			{//nCntの初期化
				m_nCount = 0;
			}
		}
		break;
	}

	//プレイヤーの体力を持ってくる
	m_fLife = pPlayer->GetLife();

	if (m_fLife <= 0)
	{//プレイヤーのHPが0になった場合武器を消す(表示武器も消える(仕様にしようかな？)
		CGan::Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CGan::Draw(void)
{
	if (m_nFram != 1)
	{//フレームじゃない場合のみ
		CScene2D::SetRot(m_fRot, m_Size);
	}

	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CGan * CGan::Create(D3DXVECTOR2 size,TYPE type,GAN gantype,int nfram)
{
	CGan *pGan = NULL;

	//NULLチェック
	if (pGan == NULL)
	{//メモリの動的確保

		pGan = new CGan;

		if (pGan != NULL)
		{
			//オブジェクトクラスの生成
			pGan->Init();
			//テクスチャを割り当てる
			pGan->BindTexture(m_pTexture[gantype]);
			//種類を割り当てる
			pGan->m_nType = type;
			//サイズの割り当て
			pGan->m_Size = size;
			//フレームかフレームじゃないか
			pGan->m_nFram = nfram;
		}
	}
	return pGan;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CGan::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[1]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_3,
		&m_pTexture[2]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_4,
		&m_pTexture[3]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_5,
		&m_pTexture[4]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_6,
		&m_pTexture[5]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CGan::UnLoad(void)
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