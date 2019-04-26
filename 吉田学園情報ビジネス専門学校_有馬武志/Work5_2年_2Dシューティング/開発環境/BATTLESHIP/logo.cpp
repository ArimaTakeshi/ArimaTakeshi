//=============================================================================
//
// ロゴの処理 [logo.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "logo.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1		"data\\TEXTURE\\B.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_2		"data\\TEXTURE\\A.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_3		"data\\TEXTURE\\T.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_4		"data\\TEXTURE\\T.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_5		"data\\TEXTURE\\L.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_6		"data\\TEXTURE\\E.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_7		"data\\TEXTURE\\S.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_8		"data\\TEXTURE\\H.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_9		"data\\TEXTURE\\I.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_10		"data\\TEXTURE\\P.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_11		"data\\TEXTURE\\PressAny.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_12		"data\\TEXTURE\\TitleButtleship.png"//読み込むテクスチャファイル
#define TEXTURE_NAME_13		"data\\TEXTURE\\TitleSentouki.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_23		"data\\TEXTURE\\EnemySentouki.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_14		"data\\TEXTURE\\tutorial003.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_15		"data\\TEXTURE\\tutorial001.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_16		"data\\TEXTURE\\tutorial002.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_21		"data\\TEXTURE\\tutorial003.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_29		"data\\TEXTURE\\tutorial004.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_17		"data\\TEXTURE\\instruction000.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_18		"data\\TEXTURE\\instruction001.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_19		"data\\TEXTURE\\instruction002.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_20		"data\\TEXTURE\\instruction003.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_22		"data\\TEXTURE\\instruction004.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_27		"data\\TEXTURE\\instruction005.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_28		"data\\TEXTURE\\instruction006.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_24		"data\\TEXTURE\\Bullet0003.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_26		"data\\TEXTURE\\Bullet0004.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_25		"data\\TEXTURE\\kuubo.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_30		"data\\TEXTURE\\hea.png"			//読み込むテクスチャファイル
#define MIN_POS				(230.0f)							//最低位置
#define DOWNSPD				(5.0f)								//落下スピード
#define SKYSPD				(4.0f)								//飛行機の飛行スピード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CLogo::CLogo() : CScene2D(4)//優先優位イニシャライズ
{
	m_nCnt = 15;
	m_nCntTutorial = 0;
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntShip = 0;
	m_nExplosionCnt = 0;
	m_nCntShipDown = 0;
	m_bOneCnt = false;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CLogo::~CLogo()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogo::Init(void)
{
	CScene2D::Init();

	D3DXCOLOR Color[4];

	for (int nCount = 0; nCount < 4; nCount++)
	{//それ以外の場合すべての初期化
		Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogo::Update(void)
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	D3DXCOLOR Color[4];

	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();

	//ゲームの状態の確認
	CGame::GAMESTATE GameState = CGame::GetGameState();

	//マウスのposを入れる箱
	D3DXVECTOR3 mousepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//マウスの座標を取得
	mousepos = *CInputMouse::GetMousePos();

	//デバック用　終わったらこの文を消すこと！　Managerの始まりもTITLEに戻すこと！
	//GameState = CGame::GAMESTATE_CLEAR;

	//移動量の割り当て
	D3DXVECTOR3 move;
	move = GetMove();

	//位置の割り当て
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//変数宣言
	int nFrame = 15; //間隔
	m_nCnt++;

	//タイトルロゴを落とす
	for (int nCount = 0; nCount < 10; nCount++)
	{
		if (m_nType == nCount)
		{
			if (pos.y < MIN_POS && m_nCnt >= (nFrame * nCount + 1))
			{
				move = D3DXVECTOR3(0.0f, DOWNSPD, 0.0f);
			}
			else
			{//一定の位置を超えたら止まる
				move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}

	if (m_nType == 11 || m_nType == 25)
	{//戦艦と空母のみ使用

		// 長さを出す
		m_fLength = sqrtf((m_size.x / 2 + m_size.x / 2) * (m_size.y / 2 + m_size.y / 2));
		// 角度を出す
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

		if (m_nCntShip == 120)
		{
			//カウンターを0に戻す
			m_nCntShip = 0;
		}
		else if (m_nCntShip >= 60)
		{
			//右回転
			m_rot.x -= 0.0003f;
			m_rot.y -= 0.0003f;
		}
		else if (m_nCntShip >= 0)
		{
			//左回転
			m_rot.x += 0.0003f;
			m_rot.y += 0.0003f;
		}

		//カウンターの増加
		m_nCntShip++;
	}

	//味方飛行機
	if (m_nType == 12)
	{
		move = D3DXVECTOR3(-SKYSPD, 0.0f, 0.0f);
	}
	//敵飛行機
	if (m_nType == 22)
	{
		move = D3DXVECTOR3(SKYSPD, 0.0f, 0.0f);
	}
	//オーバー時の爆弾の動き
	if (m_nType == 23 || m_nType == 24 && GameState == CGame::GAMESTATE_OVER)
	{
		move = D3DXVECTOR3(0.0f, SKYSPD, 0.0f);
	}
	//クリア時の爆弾の動き
	if (m_nType == 26 || m_nType == 27 && GameState == CGame::GAMESTATE_CLEAR)
	{
		move = D3DXVECTOR3(-SKYSPD, 0.2f, 0.0f);

		// 長さを出す
		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// 角度を出す
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

		//左回転
		m_rot.x += 0.001f;
		m_rot.y += 0.001f;
	}

	if (m_nType == 28 || m_nType == 29)
	{//報告文
	 //一度のみ入る
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1135.0f)
			{//右に動かす
				move.x = -5;
			}
			else if (pos.x <= 1135.0f)
			{//一度止める
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
	}

	//位置を更新(移動)
	pos.x += move.x;
	pos.y += move.y;


	//クロスヘア
	if (m_nType == 31)
	{
		//自身のPOSにマウスのPOSを入れる
		pos = mousepos;
	}

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	if (pCInputKeyBoard->GetKeyboardAny(1) == true || pCInputMouse->GetMouseTrigger(0) == true)
	{//タイトルロゴを落とす
		for (int nCount = 0; nCount < 10; nCount++)
		{
			if (m_nType == nCount)
			{
				pos.y = MIN_POS;
			}
		}
	}

	//★☆★☆チュートリアル★☆★☆
	if (m_nType == 16 && GameMode == CManager::MODE_TUTORIAL)
	{//チュートリアル指示表示

		//一度のみ入る
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1135.0f)
			{//右に動かす
				move.x = -5;
			}
			else if (pos.x <= 1135.0f)
			{//一度止める
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
		//８秒後画面外に戻す
		if (m_nCntTutorial == 500)
		{//左に動かす
			move.x = 5;
		}
		else if (m_nCntTutorial == 600)
		{
			//テクスチャの変更
			BindTexture(m_pTexture[17]);

			//もう一度上記の動きをするが、nCntは進んだままなので2回目はそのまま止まる
			m_bOneCnt = false;
		}
	}

	//★☆★☆ゲーム★☆★☆
	if (m_nType == 18 && GameMode == CManager::MODE_GAME)
	{//ゲーム指示表示
		//一度のみ入る
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1135.0f)
			{//右に動かす
				move.x = -5;
			}
			else if (pos.x <= 1135.0f)
			{//一度止める
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
		//4秒後画面外に戻す
		if (m_nCntTutorial == 240)
		{//左に動かす
			move.x = 5;
		}
		else if (m_nCntTutorial == 340)
		{
			//テクスチャの変更
			BindTexture(m_pTexture[19]);

			m_bOneCnt = false;
		}
		else if (m_nCntTutorial == 640)
		{//左に動かす
			move.x = 5;
		}
		else if (m_nCntTutorial == 740)
		{
			//テクスチャの変更
			BindTexture(m_pTexture[21]);

			//もう一度上記の動きをするが、nCntは進んだままなので3回目はそのまま止まる
			m_bOneCnt = false;
		}
		else if (m_nCntTutorial == 830)
		{
			//さあ！いくぞ！
			pSound->PlaySound(CSound::SOUND_LABEL_GO);
		}
	}

	if (m_nType == 20)
	{//チュートリアル指示表示
		if (m_bOneCnt == false)
		{
			if (pos.x >= 1130.0f && m_nCntTutorial == 460)
			{//右に動かす
				move.x = -5;
			}
			else if (pos.x <= 1130.0f)
			{//一度止める
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
	}

	//カウントの増加
	m_nCntTutorial++;
	
	if (m_nType == 10 || m_nType == 13)
	{//点滅処理
		//選択しているカラーの値を減らしていく
		m_col.a -= 0.015f;

		if (m_col.a < 0.1f)
		{//信託しているカラーが0.5を切ったらカラーの値が増えてく
			m_col.a = 1.0f;
		}

		// 頂点カラー設定
		for(int nCount = 0;nCount < 4;nCount++)
		{
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a);
		}
	}
	else if (m_nType == 22 || m_nType == 25)
	{//敵の飛行機の色
		// 頂点カラー設定
		for (int nCount = 0; nCount < 4; nCount++)
		{
			// 頂点カラー設定
			Color[nCount] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
		}
	}
	else
	{
		// 頂点カラー設定
		for (int nCount = 0; nCount < 4; nCount++)
		{
			// 頂点カラー設定
			Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	//★☆★☆リザルト★☆★☆
	if (GameMode == CManager::MODE_RESULT)
	{//ゲーム指示表示
		if (m_nType == 11 && GameState == CGame::GAMESTATE_OVER)
		{//ゲームオーバー

			if (m_nCntShipDown >= 551)
			{
				//左回転
				m_rot.x -= 0.001f;
				m_rot.y -= 0.001f;

				//船を沈める
				pos.y += 0.05f;

				if (m_nType == 11)
				{
					//選択しているカラーの値を減らしていく
					m_col.a -= 0.005f;

					// 頂点カラー設定
					for (int nCount = 0; nCount < 4; nCount++)
					{
						Color[nCount] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a);
					}
				}
			}
		}
		else if (m_nType == 25 && GameState == CGame::GAMESTATE_CLEAR)
		{//ゲームクリア
			if (m_nCntShipDown >= 551)
			{
				//左回転
				m_rot.x += 0.001f;
				m_rot.y += 0.001f;

				//船を沈める
				pos.y += 0.05f;

				if (m_nType == 25)
				{
					//選択しているカラーの値を減らしていく
					m_col.a -= 0.005f;

					// 頂点カラー設定
					for (int nCount = 0; nCount < 4; nCount++)
					{
						Color[nCount] = D3DXCOLOR(1.0f, 0.6f, 0.6f, m_col.a);
					}
				}
			}
		}
		//カウンターの増加
		m_nCntShipDown++;
	}

	//色
	CScene2D::SetColor(&Color[0]);
	//ロゴの位置とサイズ
	CScene2D::Set(pos,m_size);
	//ロゴの位置とサイズ
	CScene2D::SetMove(move);

	if (m_nType == 11 || m_nType == 25 || m_nType == 26 || m_nType == 27)
	{//回転処理を入れている種類のみ
		CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}

	if (m_nType == 23 || m_nType == 24 && GameState == CGame::GAMESTATE_OVER)
	{//敵戦闘機が落とす爆弾の終了処理
		if (pos.y > 550.0f && m_nType == 23)
		{
			//500超えたら爆発
			CLogo::Uninit();

			//消える処理
			CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - rand()% 50, 0.0f), D3DXVECTOR2(50.0f, 100.0f), 6);

			//水柱音
			pSound->PlaySound(CSound::SOUND_LABEL_MIZUBASIRA);
		}
		if (pos.y > 550.0f && m_nType == 24)
		{
			//550超えたら爆発
			CLogo::Uninit();

			//爆発の処理
			CExplosion::Create(D3DXVECTOR3(pos.x + 40.0f, pos.y + 10.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 40.0f, pos.y + 15.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(pos, D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x + 60.0f, pos.y - 25.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 60.0f, pos.y + 20.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);

			//爆発音
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION000);
		}
	}
	if (m_nType == 26 || m_nType == 27 || m_nType == 28 && GameState == CGame::GAMESTATE_CLEAR)
	{//戦艦が打つ爆弾の終了処理
		if (pos.x < 370.0f && m_nType == 26)
		{
			//500超えたら爆発
			CLogo::Uninit();

			//消える処理
			CExplosion::Create(D3DXVECTOR3(pos.x, pos.y - rand() % 50, 0.0f), D3DXVECTOR2(50.0f, 100.0f), 6);

			//水柱音
			pSound->PlaySound(CSound::SOUND_LABEL_MIZUBASIRA);
		}
		if (pos.x < 370.0f && m_nType == 27)
		{
			//550超えたら爆発
			CLogo::Uninit();

			//爆発の処理
			CExplosion::Create(D3DXVECTOR3(pos.x + 40.0f, pos.y + 10.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 40.0f, pos.y + 15.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(pos, D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x + 60.0f, pos.y - 25.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);
			CExplosion::Create(D3DXVECTOR3(pos.x - 60.0f, pos.y + 20.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 7);

			//爆発音
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION000);
		}
	}

	if (m_nType == 11 || m_nType == 25)
	{//沈む戦艦
		if (m_col.a < 0.001f)
		{//カラーが透明になったら
			CLogo::Uninit();
		}
	}
	if (pos.x - m_size.x < -500)
	{//左画面の-500にいったら消す
		CLogo::Uninit();
	}
	if (pos.x - m_size.x > 1600)
	{//右画面の1600にいったら消す
		CLogo::Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CLogo *pLogo = NULL;

	//NULLチェック
	if (pLogo == NULL)
	{//メモリの動的確保

		pLogo = new CLogo;

		if (pLogo != NULL)
		{
			//種類を割り当てる
			pLogo->m_nType = nType;
			//オブジェクトクラスの生成
			pLogo->Init();
			//テクスチャを割り当てる
			pLogo->BindTexture(m_pTexture[nType]);
			//位置を割り当てる
			pLogo->SetPosition(pos);
			//サイズの割り当て
			pLogo->m_size = size;
		}
	}

	return pLogo;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CLogo::Load(void)
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
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_7,
		&m_pTexture[6]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_8,
		&m_pTexture[7]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_9,
		&m_pTexture[8]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_10,
		&m_pTexture[9]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_11,
		&m_pTexture[10]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_12,
		&m_pTexture[11]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_13,
		&m_pTexture[12]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_14,
		&m_pTexture[13]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_15,
		&m_pTexture[14]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_16,
		&m_pTexture[15]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_17,
		&m_pTexture[16]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_18,
		&m_pTexture[17]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_19,
		&m_pTexture[18]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_20,
		&m_pTexture[19]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_21,
		&m_pTexture[20]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_22,
		&m_pTexture[21]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_23,
		&m_pTexture[22]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_24,
		&m_pTexture[23]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_24,
		&m_pTexture[24]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_25,
		&m_pTexture[25]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_26,
		&m_pTexture[26]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_26,
		&m_pTexture[27]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_27,
		&m_pTexture[28]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_28,
		&m_pTexture[29]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_29,
		&m_pTexture[30]
	);
	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_30,
		&m_pTexture[31]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CLogo::UnLoad(void)
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