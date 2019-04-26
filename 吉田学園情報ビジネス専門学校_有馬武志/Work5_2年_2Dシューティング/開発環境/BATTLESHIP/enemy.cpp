//=============================================================================
//
// 敵の処理 [enemy.cpp]
// Author : 有馬武志
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanfエラー解除
#include <stdio.h>					//stdio
#include "scene.h"
#include "scene2D.h"
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "bullet.h"
#include "score.h"
#include "player.h"
#include "effect.h"
#include "time.h"
#include "game.h"
#include "sound.h"
#include "explosion.h"
#include "damage.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1			"data\\TEXTURE\\EnemyButtleShip.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_2			"data\\TEXTURE\\戦闘機.png"				//読み込むテクスチャファイル
#define TEXTURE_NAME_3			"data\\TEXTURE\\EnemySubmarine.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_4			"data\\TEXTURE\\空母.png"				//読み込むテクスチャファイル
#define	TEXTURE_SHIP_WIDTH		(25)									//戦艦の横サイズ
#define TEXTURE_SHIP_HEIGHT		(85)									//戦艦の縦サイズ
#define	TEXTURE_DIGHTER_WIDTH	(20)									//戦闘機の横サイズ
#define TEXTURE_DIGHTER_HEIGHT	(20)									//戦闘機の縦サイズ
#define RANGE_SIZE_X			(300)									//敵の索敵範囲X
#define RANGE_SIZE_Y			(300)									//敵の索敵範囲Y
#define CHASE_RANGE_SIZE_X		(600)									//敵の索敵範囲X
#define CHASE_RANGE_SIZE_Y		(600)									//敵の索敵範囲Y

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[MAX_TEXTURE] = {};
int CEnemy::m_nNumEnemy = 0;
int CEnemy::m_nNumMaxEnemy = 0;
CEnemy::Enemy CEnemy::m_Enemy[MAX_DATA] = {};
int	CEnemy::m_nCntEnemy = 0;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CEnemy::CEnemy() : CScene2D(3)//優先優位イニシャライズ
{
	m_nLife = 0;
	m_nCounterState = 0;
	m_nCount = 0;
	m_type = ENEMYTYPE_SHIP;
	m_state = ENEMYSTATE_NORMAL;
	m_fAngle = 0.0f;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumMaxEnemy = 0;
	m_nOnOffAttack = 0;
	m_nChase = 0;
	//m_nNumEnemy = 0;

	//m_nNumEnemy++;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CEnemy::~CEnemy()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(void)
{
	CScene2D::Init();

	//種類の設定
	CScene::SetObjType(CScene::OBJTYPE_ENEMY);

	//カラーの宣言と初期化
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//カラーの設定
	Color[0] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	Color[1] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	Color[2] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	Color[3] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);

	//カラーの割り当て
	CScene2D::SetColor(&Color[0]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	CScene2D::Update();

	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();

	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//NULLチェック
	if (pPlayer != NULL)
	{
		PlayerPos = pPlayer->GetPosition();
	}

	//カラーの宣言と初期化
	D3DXCOLOR Color[4];
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		Color[nCnt] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	}

	//種類の代入
	static CBullet::BULLETTYPE type = CBullet::BULLETTYPE_ENEMY;

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//初期値設定
	D3DXVECTOR3 pos;
	pos = CEnemy::GetPosition();

	//追尾するかしないか 1はする　0はしない
	if (m_nChase == 1)
	{
		//NULLチェック
		if (pPlayer != NULL)
		{
			//索敵範囲
			if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
				pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
			{
				//マウスの方角を向く
				m_fRot = atan2f(PlayerPos.x - pos.x, PlayerPos.y - pos.y);

				//回転
				CScene2D::SetRot(m_fRot, m_Size);

				//敵が追尾してくる
				m_move = D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 1.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 1.0f, 0.0f);
			}
		}
	}
	
	//移動量を追加
	pos += m_move;
	
	//状態確認
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:	//通常状態
		break;
	case ENEMYSTATE_DAMAGE:	//ダメージ状態

		//状態をカウント
		m_nCounterState--;

		if (m_nCounterState <= 0)
		{//状態カウント終了
			//色をもとに戻す
			Color[0] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
			Color[1] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
			Color[2] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
			Color[3] = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);

			//状態変化
			m_state = ENEMYSTATE_NORMAL;
		}

		break;
	case ENEMYSTATE_DEAHT:		//死亡状態
		//状態をカウント
		m_nCounterState--;
		break;
	}

	//カラーの割り当て
	CScene2D::SetColor(&Color[0]);

	//状態確認
	switch (m_type)
	{
	case ENEMYTYPE_SHIP:	//戦艦

		//大きさと位置
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));

		//波紋エフェクトの生成
		CEffect::Create(pos, D3DXVECTOR2(30,30),-25.0f, 20,CEffect::EFFECTTYPE_RIPPLE,0);

		//自動ショット
		if (m_nCount == 120 && m_nOnOffAttack == 0)
		{//弾の生成
				//NULLチェック
			if (pPlayer != NULL)
			{
				//索敵範囲
				if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
					pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
				{
					//大砲弾の音
					pSound->PlaySound(CSound::SOUND_LABEL_ENEMYCANNON);

					//追尾
					CBullet::Create(pos, D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_CANNON, CBullet::ENEMY_SHIP, 2);
				}
			}
		}
		else if (m_nCount >= 121)
		{//元に戻す
			m_nCount = 0;
		}
		//攻撃カウンターを増やす
		m_nCount++;

		break;
	case ENEMYTYPE_DIGHTER:	//戦闘機

		//大きさと位置
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));

		//煙エフェクトの生成
		CEffect::Create(D3DXVECTOR3(pos.x - 15,pos.y,pos.z),D3DXVECTOR2(3,3),2.0f, 8, CEffect::EFFECTTYPE_NOLMAL,1);
		CEffect::Create(D3DXVECTOR3(pos.x + 15, pos.y, pos.z), D3DXVECTOR2(3, 3),2.0f, 8, CEffect::EFFECTTYPE_NOLMAL,1);

		if (pos.y == 200.0f)
		{//敵を一定の位置で止める
			m_move.y = 0;
		}
		
		if (pPlayer != NULL)
		{
			//索敵範囲
			if (pos.x <= PlayerPos.x + RANGE_SIZE_X && pos.x >= PlayerPos.x - RANGE_SIZE_X &&
				pos.y <= PlayerPos.y + RANGE_SIZE_Y && pos.y >= PlayerPos.y - RANGE_SIZE_Y)
			{
				if (rand() % 20 == 0 && m_nOnOffAttack == 0)
				{//弾の生成
					//対空砲の音
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CBullet::Create(D3DXVECTOR3(pos.x + 15, pos.y, pos.z), D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::ENEMY_DIGHTER, 2);
				}
				if (rand() % 20 == 0 && m_nOnOffAttack == 0)
				{//弾の生成
					//対空砲の音
					pSound->PlaySound(CSound::SOUND_LABEL_SKYCANNON);

					CBullet::Create(D3DXVECTOR3(pos.x - 15, pos.y, pos.z), D3DXVECTOR3(sinf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, cosf(atan2f(-pos.x - -PlayerPos.x, -pos.y - -PlayerPos.y)) * 15.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_SKYCANNON, CBullet::ENEMY_DIGHTER, 2);
				}
			}
		}

		break;
	case ENEMYTYPE_SUBMARINE:	//潜水艦

		//大きさと位置
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));
		//波紋エフェクトの生成
		CEffect::Create(pos, D3DXVECTOR2(20, 20),-15.0f, 15, CEffect::EFFECTTYPE_RIPPLE,0);

		//自動ショット
		if (m_nCount == 120 && m_nOnOffAttack == 0)
		{//弾の生成
			if (pPlayer != NULL)
			{
				//索敵範囲
				if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
					pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
				{
					//魚雷砲の音
					pSound->PlaySound(CSound::SOUND_LABEL_TORPEDO);

					//通常
					CBullet::Create(pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), D3DXVECTOR2(2.0f, 10.0f), type, CBullet::GAN_TORPEDO, CBullet::ENEMY_SUBMARINE, 3);
				}
			}
		}
		else if (m_nCount >= 121)
		{//元に戻す
			m_nCount = 0;
		}
		//攻撃カウンターを増やす
		m_nCount++;

		break;
	case ENEMTTYPE_CARRIER:		//空母

		//大きさと位置
		CScene2D::Set(pos, D3DXVECTOR2(m_Size.x, m_Size.y));
		//波紋エフェクトの生成
		CEffect::Create(pos, D3DXVECTOR2(30.0f, 30.0f), -15.0f, 15, CEffect::EFFECTTYPE_RIPPLE, 0);

		if (pos.y == 200.0f)
		{//敵を一定の位置で止める
			m_move.y = 0;
		}

		if (m_nCount == 300)
		{//敵の生成
			//索敵範囲
			if (pos.x <= PlayerPos.x + CHASE_RANGE_SIZE_X && pos.x >= PlayerPos.x - CHASE_RANGE_SIZE_X &&
				pos.y <= PlayerPos.y + CHASE_RANGE_SIZE_Y && pos.y >= PlayerPos.y - CHASE_RANGE_SIZE_Y)
			{
				if (GameMode == CManager::MODE_TUTORIAL)
				{//チュートリアルの場合 攻撃しない敵の生成
					CEnemy::Create(pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 1, 0);
				}
				else if (GameMode == CManager::MODE_GAME)
				{//ゲームの場合 攻撃する敵の生成
					CEnemy::Create(D3DXVECTOR3(pos.x - 10, pos.y - 30.0f,pos.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 5, 0, 1);
					CEnemy::Create(pos, D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 10, 0, 1);
					CEnemy::Create(D3DXVECTOR3(pos.x + 10, pos.y + 30.0f, pos.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR2(20, 20), CEnemy::ENEMYTYPE_DIGHTER, 20, 0, 1);
				}
			}
		}
		else if (m_nCount >= 301)
		{//元に戻す
			m_nCount = 0;
		}

		//攻撃カウンターを増やす
		m_nCount++;

		break;
	}

	if (GameMode == CManager::MODE_TUTORIAL)
	{//チュートリアルの場合
		if (pos.y == 200.0f)
		{//敵を一定の位置で止める
			m_move.y = 0;
		}
	}

	//m_nCntEnemy++;

	//敵がエリア外の場合
	if (pos.x - m_Size.x < 0)
	{//画面反対側に移動（左）
		pos.x = m_Size.x;
	}
	if (pos.x + m_Size.x > SCREEN_WIDTH)
	{//画面反対側に移動（右）
		pos.x = SCREEN_WIDTH - m_Size.x;
	}
	if (pos.y - m_Size.y < 0)
	{//画面反対側に移動（上）
		pos.y = m_Size.y;
	}
	if (pos.y + m_Size.y > SCREEN_HEIGHT + 30)
	{//画面反対側に移動（下） 
		CEnemy::Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	//回転
	CScene2D::SetRot(m_fRot, m_Size);

	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CEnemy * CEnemy::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size,ENEMYTYPE type,int nLife,int nOnOffAttak,int nChase)
{
	CEnemy *pEnemy = NULL;

	//NULLチェック
	if (pEnemy == NULL)
	{//メモリの動的確保

		pEnemy = new CEnemy;

		if (pEnemy != NULL)
		{
			//オブジェクトクラスの生成
			pEnemy->Init();
			//テクスチャを割り当てる
			pEnemy->BindTexture(m_pTexture[type]);
			//HPを割り当てる
			pEnemy->m_nLife = nLife;
			//大きさと位置
			pEnemy->SetPosition(pos);
			//移動
			pEnemy->m_move = move;
			//サイズ
			pEnemy->m_Size = size;
			//タイプの割り当て
			pEnemy->m_type = type;
			//攻撃をするかしないかの割り当て
			pEnemy->m_nOnOffAttack = nOnOffAttak;
			//追尾するかしないか
			pEnemy->m_nChase = nChase;
			//敵の総数カウンター
			//pEnemy->m_nNumEnemy++;
		}
	}

	return pEnemy;
}
//===============================================================================
//  ファイル入出力による敵の位置を設置
//===============================================================================
void CEnemy::CreateEnemy(void)
{
	int nNumMaxEnemy = 0;
	char read[256];
	//int nCntFream = 0;

	//ファイルのポインタ
	FILE *pFile;

	//ファイル設定
	pFile = fopen(FILE_NAME, "r");

	//敵のテキストデータの読み込み
	if (pFile != NULL)
	{
		//総数のtexコメント
		fscanf(pFile, "%s", &read[0]);

		if (strcmp(&read[0], "#") == 0)
		{
			do
			{
				fscanf(pFile, "%c", &read[0]);
			} while (strcmp(&read[0], "\n") != 0);
		}

		//使う敵の数
		fscanf(pFile, "%d", &nNumMaxEnemy);	//読み込み

		for (int nCntEnemy = 0; nCntEnemy < nNumMaxEnemy; nCntEnemy++)
		{
			//敵の種類のコメント
			for (int nCount = 0; nCount < 3; nCount++) 
			{ 
				fscanf(pFile, "%s", &read[0]);

				if (strcmp(&read[0], "#") == 0) 
				{ 
					do 
					{ 
						fscanf(pFile, "%c", &read[0]); 
					}
				while (strcmp(&read[0], "\n") != 0); 
				}
			}

			//初期位置の設定
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitPos.x);		//位置X
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitPos.y);		//位置Y
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitPos.z);		//位置Z

			//初期値の動きの設定
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitMove.x);	//移動方向X
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitMove.y);	//移動方向Y
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitMove.z);	//移動方向Z

			//初期値のサイズの設定
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitSize.x);	//横幅X
			fscanf(pFile, "%f", &m_Enemy[nCntEnemy].InitSize.y);	//縦幅Y

			//敵のタイプの設定
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].EnemyType);		//タイプの代入

			//敵のHPの設定
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].nLife);			//ライフの代入

			//敵の攻撃をするかしないかの設定
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].nAttack);		//Attackするかしないか 0攻撃開始　1攻撃しない

			//追尾するかしないか
			fscanf(pFile, "%d", &m_Enemy[nCntEnemy].nChase);		//1追尾する場合   0しない場合

			//敵の生成
			//CEnemy::Create(位置・動き・サイズ・敵の種類・体力・攻撃する1 攻撃しない0以外・追尾する1 追尾しない0);
			//敵の生成  ENEMYTYPE_SHIP 戦艦0  : ENEMYTYPE_DIGHTER 戦闘機1  : ENEMYTYPE_SUBMARINE 潜水艦2  : ENEMTTYPE_CARRIER  空母3
			CEnemy::Create(m_Enemy[nCntEnemy].InitPos, m_Enemy[nCntEnemy].InitMove, m_Enemy[nCntEnemy].InitSize, m_Enemy[nCntEnemy].EnemyType, m_Enemy[nCntEnemy].nLife, m_Enemy[nCntEnemy].nAttack, m_Enemy[nCntEnemy].nChase);
		}

		fclose(pFile);	//ファイルを閉じる
	}
	else
	{//警告文
		MessageBox(0, "セーブファイルのチェックに失敗!", "警告", MB_ICONWARNING);
	}

	//敵の数を入れる
	m_nNumMaxEnemy = nNumMaxEnemy;
}
//===============================================================================
// 敵のダメージ処理
//===============================================================================
void CEnemy::HitEnemy(int nDamage)
{
	//位置の情報
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//カラーの宣言と初期化
	D3DXCOLOR Color[4];

	if (m_nLife >= 1)
	{//ライフが１以上の時にダメージの処理を通す
		//HPからダメージ分を引く
		m_nLife -= nDamage;
	}

	if (m_nLife <= 0)
	{//ライフが０以下の時
		//状態の代入
		m_state = ENEMYSTATE_DEAHT;		//死亡
		//スコア加算
		CScore::AddScore(1000);
		//撃破数を加算
		CTime::AddTime(1);
		//ダメージ時間
		m_nCounterState = 30;

		//敵の死ぬ演出
		switch (m_type)
		{
		case ENEMYTYPE_SHIP://戦艦
			//エフェクトの生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 30, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 27, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 24, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 21, CEffect::EFFECTTYPE_RIPPLE, 0);
			break;
		case ENEMYTYPE_DIGHTER://戦闘機
			//消える処理
			CExplosion::Create(pos, m_Size, 3);
			break;
		case ENEMYTYPE_SUBMARINE://潜水艦
			break;
		case ENEMTTYPE_CARRIER://空母
			//エフェクトの生成
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 30, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 27, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 24, CEffect::EFFECTTYPE_RIPPLE, 0);
			CEffect::Create(D3DXVECTOR3(pos.x, pos.y - 45.0f, pos.z), D3DXVECTOR2(70, 70), -25.0f, 21, CEffect::EFFECTTYPE_RIPPLE, 0);

			if (m_type == ENEMTTYPE_CARRIER)
			{//敵が全滅したら
				CGame::SetGameState(CGame::GAMESTATE_CLEAR);
			}
			break;
		}

		//プレイヤーの破棄
		CEnemy::Uninit();
	}
	else
	{//ライフが０以上の時
		//状態の代入
		m_state = ENEMYSTATE_DAMAGE;	//ダメージ
		//スコア加算
		CScore::AddScore(1);
		//ダメージ時間
		m_nCounterState = 30;

		//カラーの設定
		Color[0] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Color[1] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Color[2] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Color[3] = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);

		//カラーの割り当て
		CScene2D::SetColor(&Color[0]);
	}
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CEnemy::Load(void)
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

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CEnemy::UnLoad(void)
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
