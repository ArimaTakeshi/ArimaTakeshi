//=============================================================================
//
// バレットの処理 [bullet.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "damage.h"
#include "2Dobject.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\Bullet0000.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_2	"data\\TEXTURE\\Bullet0001.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_3	"data\\TEXTURE\\Bullet0002.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_4	"data\\TEXTURE\\Bullet0003.png"			//読み込むテクスチャファイル
#define BULLET_X		(2)										//横の大きさ
#define	BULLET_Y		(10)									//縦の大きさ
#define DAMAGE			(1)										//ダメージ量
#define CANNON			(5)										//大砲のダメージ量
#define SKYCANNON		(1)										//対空砲のダメージ量
#define TORPEDO			(50)									//魚雷のダメージ量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CBullet::CBullet() : CScene2D(3)//優先優位イニシャライズ
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_nBulletType = 0;
	m_nDamage = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Petype = PLAYER_SHIP;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	//オブジェクトの種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	//当たったかあたってないかの判定
	bool bHit;

	//敵の情報
	CEnemy *pEnemy = CGame::GetEnemy();

	//m_posを代入
	D3DXVECTOR3 Bulletpos = CScene2D::GetPosition();

	//移動量の代入
	Bulletpos += m_move;

	//弾の位置とサイズ
	Set(Bulletpos,m_Size);

	//プレイヤーだった場合
	if (m_nType == BULLETTYPE_PLAYER || m_nType == BULLETTYPE_ENEMY)
	{
		//ダメージの変更
     	if (m_nBulletType == CBullet::GAN_CANNON)
		{//大砲弾
			m_nDamage = CANNON;
		}
		else if (m_nBulletType == CBullet::GAN_SKYCANNON)
		{//対空砲
			m_nDamage = SKYCANNON;
		}
		else if (m_nBulletType == CBullet::GAN_TORPEDO)
		{//魚雷弾
			m_nDamage = TORPEDO;
		}
	}

	//ダメージの代入
	int nDamage = m_nDamage;

	//順位を確認
	for (int nCnPri = 0; nCnPri < NUM_PRIORITY; nCnPri++)
	{
		//オブジェクトの総数を確認
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene2D *pScene;

			pScene = (CScene2D*)CScene::GetScene(nCnPri, nCntScene);

			if (pScene != NULL)
			{//NULLチェック
				//ローカルで作る
				CScene::OBJTYPE ObjType;

				//オブジェクトのシーンを取得
				ObjType = pScene->GetObjType();

				//当たり判定
				if (ObjType == CScene::OBJTYPE_PLAYER && m_nType == BULLETTYPE_ENEMY)
				{//★☆★☆敵の弾の処理☆★☆★

					//型をエネミーに入れる
					CPlayer *pPlayer = (CPlayer*)pScene;

					//敵の弾の判別
					if (m_nBulletType == CBullet::GAN_CANNON && m_nType == BULLETTYPE_ENEMY || m_nBulletType == CBullet::GAN_TORPEDO && m_nType == BULLETTYPE_ENEMY || m_nBulletType == CBullet::GAN_SKYCANNON && m_nType == BULLETTYPE_ENEMY)
					{
						if (pScene->GetPosition().x - pPlayer->GetSize()->x < Bulletpos.x && pScene->GetPosition().x + pPlayer->GetSize()->x > Bulletpos.x &&
							pScene->GetPosition().y - pPlayer->GetSize()->y < Bulletpos.y && pScene->GetPosition().y + pPlayer->GetSize()->y > Bulletpos.y)
						{//当たり判定

							//弾の終了処理
							CBullet::Uninit();

							if (m_nBulletType == CBullet::GAN_TORPEDO)
							{
								//爆発の生成
								CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 5);
							}
							else
							{
								//爆発の生成
								CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 0);
							}
							//プレイヤーへのダメージの処理
							pPlayer->HitPlayer(nDamage * 1.0f);
						}
					} 
				}
				else if (ObjType == CScene::OBJTYPE_ENEMY && m_nType == BULLETTYPE_PLAYER)
				{//★☆★☆プレイヤーの弾の処理☆★☆★
				
					bHit = true;

					//型をエネミーに入れる
					CEnemy *pEnemy = (CEnemy*)pScene;

 					switch (m_nBulletType)
					{//機体と弾を判別
					case GANTYPE_BULLET::GAN_CANNON:		//大砲の場合
						if (pEnemy->GetType() == CEnemy::ENEMYTYPE_SUBMARINE)
						{//潜水艦には当たらない
							bHit = false;
						}
						break;
					case GANTYPE_BULLET::GAN_SKYCANNON:		//対空砲の場合
						if (pEnemy->GetType() == CEnemy::ENEMYTYPE_SUBMARINE)
						{//潜水艦には当たらない
							bHit = false;
						}
						break;
					case GANTYPE_BULLET::GAN_TORPEDO:		//魚雷の場合
						if (pEnemy->GetType() == CEnemy::ENEMYTYPE_DIGHTER)
						{//戦闘機にはあたらない
							bHit = false;
						}
						break;
					}

					if (bHit)
					{//あたっていい機体なら
						if (pScene->GetPosition().x - pEnemy->GetSize()->x < Bulletpos.x && pScene->GetPosition().x + pEnemy->GetSize()->x > Bulletpos.x &&
							pScene->GetPosition().y - pEnemy->GetSize()->y < Bulletpos.y && pScene->GetPosition().y + pEnemy->GetSize()->y > Bulletpos.y)
						{//当たり判定

							//弾の終了処理
							CBullet::Uninit();

							//爆発の生成
							//CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 0);

							//敵へのダメージの処理
							pEnemy->HitEnemy(nDamage);
						}
					}
				}
				else if (ObjType == CScene2D::OBJTYPE_2DOBJECT)
				{//★☆★☆オブジェクトの処理☆★☆★

					 //型をオブジェクトに入れる
					C2DObject *p2DObject = (C2DObject*)pScene;

					if (pScene->GetPosition().x - p2DObject->GetSize()->x < Bulletpos.x && pScene->GetPosition().x + p2DObject->GetSize()->x > Bulletpos.x &&
						pScene->GetPosition().y - p2DObject->GetSize()->y < Bulletpos.y && pScene->GetPosition().y + p2DObject->GetSize()->y > Bulletpos.y)
					{//当たり判定

						//弾の終了処理
						CBullet::Uninit();

						//爆発の生成
						CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 0);

						//オブジェクトへのダメージ
						p2DObject->HitObject(nDamage);
					}
				}
			}
		}
	}

	if (Bulletpos.y < m_Size.y || Bulletpos.y > SCREEN_HEIGHT - m_Size.y || Bulletpos.x < 300 + m_Size.x || Bulletpos.x > SCREEN_WIDTH - 300 - m_Size.x)
	{//画面外の場合
		//弾の終了処理
		CBullet::Uninit();

		//爆発の生成
		CExplosion::Create(Bulletpos,D3DXVECTOR2(20, 20), 0);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size, BULLETTYPE type, GANTYPE_BULLET bullettype , PETYPE petype,int nBulletType)
{
	CBullet *pBullet = NULL;

	//NULLチェック
	if (pBullet == NULL)
	{//メモリの動的確保

		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			//オブジェクトクラスの生成
			pBullet->Init();
			//テクスチャを割り当てる
			pBullet->BindTexture(m_pTexture[nBulletType]);
			//種類を割り当てる
			pBullet->m_nType = type;
			//サイズの割り当て
			pBullet->m_Size = size;
			//移動量の割り当て
			pBullet->m_move = move;
			//弾の判別
			pBullet->m_nBulletType = bullettype;
			//敵か自分かの判別
			pBullet->m_Petype = petype;
			//弾を設置
			pBullet->SetPosition(pos);
		}
	}
	return pBullet;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CBullet::Load(void)
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
void CBullet::UnLoad(void)
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