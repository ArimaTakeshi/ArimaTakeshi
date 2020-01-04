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
#include "scene3D.h"
#include "bullet.h"
#include "wall.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\Bullet000.png"			//読み込むテクスチャファイル
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
CMeshOrbit *CBullet::m_MeshOrbit = NULL;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CBullet::CBullet() : CScene3D(BULLET_PRIOTITY, CScene::OBJTYPE_BULLET)//優先優位イニシャライズ
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_nBulletType = 0;
	m_nDamage = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
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
	CScene3D::Init();

	//軌跡の生成
	//m_MeshOrbit = CMeshOrbit::Create();

	//プレイヤーのワールドマトリックスの反映
	//m_MeshOrbit->SetMatRarent(&CScene3D::GetMatrix());

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//m_posを代入
	D3DXVECTOR3 Bulletpos = CScene3D::GetPosition();

	D3DXVECTOR3 posOld = Bulletpos;

	//軌跡の描画を開始する
	//m_MeshOrbit->SetOrbitOn(true);

	//移動量の代入
	Bulletpos += m_move;

	//移動値のセット
	CScene3D::SetMove(m_move);
	//位置のセット
	CScene3D::SetPosition(Bulletpos);

	CollisitionWall();

	//壁とのあたり判定
	if (Bulletpos.z >= 3000 || Bulletpos.z <= -3000 || Bulletpos.x >= 3000 || Bulletpos.x <= -3000)
	{
		//弾の終了処理
		CBullet::Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//RIGHTをオフ
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	CScene3D::Draw();

	//RIGHTをオン
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//===============================================================================
//　クリエイト
//===============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 move,D3DXVECTOR2 size, int type)
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
			pBullet->BindTexture(m_pTexture[type]);
			//種類を割り当てる
			pBullet->m_nType = type;
			//移動量の割り当て
			pBullet->m_move = move;
			//弾の位置とサイズを指定
			pBullet->SetPosSize(pos,size);
			//当たり判定用のサイズを取得
			pBullet->m_Size = size;
			//向きを入れる
			pBullet->m_rot = rot;
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
	D3DXCreateTextureFromFile(pDevice,TEXTURE_NAME_1,&m_pTexture[0]);

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
//===============================================================================
// 弾の当たり判定
//===============================================================================
bool CBullet::CollisitionBullet(D3DXVECTOR3 *pPos,float fSize)
{
	//m_posを代入
	D3DXVECTOR3 Bulletpos = CScene3D::GetPosition();

	//当たったか当たってないかの状態
	bool bHit = false;

	//弾のあたり判定
	if (Bulletpos.x + m_Size.x >= pPos->x - fSize &&Bulletpos.x - m_Size.x <= pPos->x + fSize &&
		Bulletpos.z + m_Size.x >= pPos->z - fSize &&Bulletpos.z - m_Size.x <= pPos->z + fSize)
	{
		//当たったよ！
		bHit = true;
	}

	//位置のセット
	CScene3D::SetPosition(Bulletpos);

	return bHit;
}
//=============================================================================
//	壁の当たり判定
//=============================================================================
void CBullet::CollisitionWall(void)
{
	CScene *pScene;

	//m_posを代入
	D3DXVECTOR3 Bulletpos = CScene3D::GetPosition();

	//プライオリティーチェック
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_WALL)
			{
				((CWall*)pScene)->CollisionWall(&m_pos, &Bulletpos, &m_move, 20.0f);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}