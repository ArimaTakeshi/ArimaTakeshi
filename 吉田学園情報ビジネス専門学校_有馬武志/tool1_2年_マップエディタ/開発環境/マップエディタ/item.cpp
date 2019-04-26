//=============================================================================
//
// アイテム処理 [item.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "time.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ITEM_NAME000		 "data\\MODEL\\Apple.x"		//テクスチャのファイル名
#define ITEM_NAME001		 "data\\MODEL\\Banana.x"		//テクスチャのファイル名
#define ITEM_ROT			(0.1f)
#define ITEM_MOVE_Y_UP		(0.3f)
#define ITEM_MOVE_Y_DOWN	(0.5f)

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH			CItem::m_pMesh[MAX_ITEM_TYPE] = {};				//メッシュ情報へのポインタ
LPD3DXBUFFER		CItem::m_pBuffMat[MAX_ITEM_TYPE] = {};			//マテリアル情報へのポインタ
DWORD				CItem::m_nNumMat[MAX_ITEM_TYPE] = {};			//マテリアルの情報数
LPDIRECT3DTEXTURE9	CItem::m_pTexture[MAX_ITEM_TYPE] = {};			//テクスチャ情報

//===============================================================================
//　コンストラクタ
//===============================================================================
CItem::CItem() : CModel3D(4, CScene::OBJTYPE_ITEM)
{
	m_aItem.nType = 0;
	m_move = D3DXVECTOR3(0, 0, 0);
	m_pos = D3DXVECTOR3(0, 0, 0);
	m_posold = D3DXVECTOR3(0, 0, 0);
	m_nMoveTimer = 0;
}

//===============================================================================
//　デストラクタ
//===============================================================================
CItem::~CItem()
{
}

//===============================================================================
//　アイテムの生成
//===============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, int type)
{
	CItem *pItem = NULL;

	//NULLチェック
	if (pItem == NULL)
	{//メモリの動的確保
		pItem = new CItem;
		if (pItem != NULL)
		{
			pItem->BindModel(m_pMesh[type], m_pBuffMat[type], m_nNumMat[type], m_pTexture[type]);
			//種類を割り当てる
			pItem->m_aItem.nType = type;
			switch (pItem->m_aItem.nType)
			{
			case 0:
				pItem->m_aItem.ItemType = ITEMTYPE_APPLE;
				break;
			case 1:
				pItem->m_aItem.ItemType = ITEMTYPE_BANANA;
				break;
			}
			//座標を設定
			pItem->m_pos = pos;
			//オブジェクトクラスの生成
			pItem->Init();
		}
	}
	return pItem;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CItem::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_move = D3DXVECTOR3(0, 0, 0);
	m_posold = D3DXVECTOR3(0, 0, 0);

	//3DモデルのInit
	CModel3D::Init();

	//位置の代入
	CModel3D::SetPosition(m_pos);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CItem::Uninit(void)
{
	//3DモデルのUninit
	CModel3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CItem::Update(void)
{
	//3DモデルのUpdate
	CModel3D::Update();
	//位置の初期化
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	D3DXVECTOR3 rot = CModel3D::GetRot();

	//タイマーを加算
	m_nMoveTimer++;

	if (m_nMoveTimer <= 60)
	{	//フレーム数 (60) * 移動量(0.3f) = 18	※合わせる
		pos.y += ITEM_MOVE_Y_UP;
	}
	else if (m_nMoveTimer >= 60 && m_nMoveTimer <= 120)
	{
		//フレーム数 (36) * 移動量(0.5f) = 18
		pos.y -= ITEM_MOVE_Y_UP;
	}
	else
	{
		m_nMoveTimer = 0;
	}

	//アイテムごとの回転
	switch (m_aItem.ItemType)
	{
	case ITEMTYPE_APPLE:
		//回転の加算
		rot.y += ITEM_ROT;
		break;
	case ITEMTYPE_BANANA:
		//回転の加算
		rot.y += ITEM_ROT / 2;
		break;
	}

	//回転の代入
	CModel3D::SetRot(rot);

	//位置の代入
	CModel3D::SetPosition(pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CItem::Draw(void)
{
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//近くの壁以外を消す
	if (m_pos.x + 700.0f >= PlayerPos.x && m_pos.x - 650.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		//3DモデルのDraw
		CModel3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		//3DモデルのDraw
		CModel3D::Draw();
	}
}

//*****************************************************************************
//アイテムポインタ処理
//*****************************************************************************
CItem::ITEM *CItem::GetItem(void)
{
	return &m_aItem;
}
//*****************************************************************************
//アイテムとの当たり判定処理
//*****************************************************************************
bool CItem::CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	bool bLand = false;
	//プレイヤーの取得
	CPlayer *pPlayer;
	pPlayer = CGame::GetPlayer();
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXVECTOR3 ItemVtxMax = CModel3D::VtxMax();
	D3DXVECTOR3 ItemVtxMin = CModel3D::VtxMin();
#if 1			//モデルのY幅の中
	if (pPos->y < m_pos.y + ItemVtxMax.y
		&& pPos->y + 100.0f > m_pos.y + ItemVtxMin.y)
	{
		//モデルのZ幅の中
		if (pPos->z < m_pos.z + ItemVtxMax.z
			&& pPos->z + 10.0f  > m_pos.z + ItemVtxMin.z)
		{
			//モデルのX幅の中
			if (pPos->x < m_pos.x + ItemVtxMax.x
				&& pPos->x + 10.0f > m_pos.x + ItemVtxMin.x)
			{
				//当たり判定
				bLand = true;

				CSound *pSound = CManager::GetSound();
				pSound->PlaySound(CSound::SOUND_LABEL_SE_ITEMGET);

				//アイテムごとの回転
				//switch (m_aItem.ItemType)
				{
			
				}

#endif
			}
		}
	}
	return bLand;
}

//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CItem::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX(ITEM_NAME000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(ITEM_NAME001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < MAX_ITEM_TYPE; nCnt++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		// テクスチャの読み込み
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			m_pTexture[nCnt] = NULL;

			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// テクスチャの設定
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					pMat[nCntMatTex].pTextureFilename,	// ファイルの名前
					&m_pTexture[nCnt]);					// テクスチャへのポインタ
			}
		}
	}
	return S_OK;
}

//===============================================================================
// テクスチャの破棄
//===============================================================================
void CItem::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_ITEM_TYPE; nCount++)
	{
		// メッシュの開放
		if (m_pMesh[nCount] != NULL)
		{
			m_pMesh[nCount]->Release();
			m_pMesh[nCount] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMat[nCount] != NULL)
		{
			m_pBuffMat[nCount]->Release();
			m_pBuffMat[nCount] = NULL;
		}
	}
}