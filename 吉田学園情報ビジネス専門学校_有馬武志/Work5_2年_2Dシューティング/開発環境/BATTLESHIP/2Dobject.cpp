//=============================================================================
//
// オブジェクトの処理 [2Dobject.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "2Dobject.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "bullet.h"
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1					"data\\TEXTURE\\iwa.png"	//読み込むテクスチャファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 C2DObject::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
C2DObject::C2DObject()
{
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fPlayerLife = 0;
	m_nLife = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
C2DObject::~C2DObject()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT C2DObject::Init(void)
{
	CScene2D::Init();

	//種類の設定
	CScene::SetObjType(CScene::OBJTYPE_2DOBJECT);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void C2DObject::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void C2DObject::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//オンオフの切り替え
	bool bOnOff = false;

	//位置を代入
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();

	//NULLチェック
	if (pPlayer != NULL)
	{
		//プレイヤーの体力を持ってくる
		m_fPlayerLife = pPlayer->GetLife();
	}

	//移動処理
	if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
	{//左に行く
		pos.x += 0.8f;
	}
	else if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
	{//右に行く
		pos.x -= 0.8f;
	}

	//オブジェクトの位置
	CScene2D::Set(pos, m_Size);

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
				if (ObjType == CScene::OBJTYPE_PLAYER)
				{//★☆★☆プレイヤーの処理☆★☆★

					//型をエネミーに入れる
					CPlayer *pPlayer = (CPlayer*)pScene;

					if (pScene->GetPosition().x - pPlayer->GetSize()->x < pos.x && pScene->GetPosition().x + pPlayer->GetSize()->x > pos.x &&
						pScene->GetPosition().y - pPlayer->GetSize()->y < pos.y && pScene->GetPosition().y + pPlayer->GetSize()->y > pos.y)
					{//当たり判定
						//1回のみ入る
						if (bOnOff == false)
						{
							//体力の最大分をなくす
							pPlayer->HitPlayer(m_fPlayerLife);
							//0以下の場合0を代入してそれ以下を作らない
							m_fPlayerLife = 0;
							//爆発の生成
							CExplosion::Create(pos, D3DXVECTOR2(20.0f, 20.0f), 0);

							bOnOff = true;
						}
					}
				}
				else if (ObjType == CScene::OBJTYPE_ENEMY)
				{//★☆★☆敵の処理☆★☆★

					//型をエネミーに入れる
					CEnemy *pEnemy = (CEnemy*)pScene;

					if (pScene->GetPosition().x - pEnemy->GetSize()->x < pos.x && pScene->GetPosition().x + pEnemy->GetSize()->x > pos.x &&
						pScene->GetPosition().y - pEnemy->GetSize()->y < pos.y && pScene->GetPosition().y + pEnemy->GetSize()->y > pos.y)
					{//当たり判定
						//敵の終了処理
						pEnemy->Uninit();
						//爆発の生成
						CExplosion::Create(pos, D3DXVECTOR2(30.0f, 30.0f), 0);
					}
				}
			}
		}
	}

	//岩からのダメージをプレイヤーに入れる
	pPlayer->SetLife(m_fPlayerLife);
}
//=============================================================================
// 描画処理
//=============================================================================
void C2DObject::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
C2DObject * C2DObject::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType,int nLife)
{
	C2DObject *p2DObject = NULL;

	//NULLチェック
	if (p2DObject == NULL)
	{//メモリの動的確保

		p2DObject = new C2DObject;

		if (p2DObject != NULL)
		{
			//オブジェクトクラスの生成
			p2DObject->Init();
			//種類の割り当て
			p2DObject->m_nType = nType;
			//体力の割り当て
			p2DObject->m_nLife = nLife;
			//テクスチャを割り当てる
			p2DObject->BindTexture(m_pTexture[nType]);
			//弾を設置
			p2DObject->SetPosition(pos);
			//サイズの割り当て
			p2DObject->m_Size = size;
		}
	}
	return p2DObject;
}
//===============================================================================
// オブジェクトのダメージ処理
//===============================================================================
void C2DObject::HitObject(int nDamage)
{
	//カラーの宣言と初期化
	D3DXCOLOR Color[4];

	//m_posを代入
	D3DXVECTOR3 Objectpos = CScene2D::GetPosition();

	//弾の位置とサイズ
	CScene2D::SetPosition(Objectpos);

	if (m_nLife >= 1)
	{//ライフが１以上の時にダメージの処理を通す
		//HPからダメージ分を引く
		m_nLife -= nDamage;
	}

	if (m_nLife <= 0)
	{//ライフが０以下の時
		//オブジェクトの破棄
		C2DObject::Uninit();
		//岩が壊れる
		CExplosion::Create(Objectpos, D3DXVECTOR2(30.0f, 30.0f), 4);
		//波紋
		CEffect::Create(Objectpos, D3DXVECTOR2(100.0f, 100.0f), -25.0f, 40, CEffect::EFFECTTYPE_RIPPLE, 0);
	}
}

//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT C2DObject::Load(void)
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
void C2DObject::UnLoad(void)
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