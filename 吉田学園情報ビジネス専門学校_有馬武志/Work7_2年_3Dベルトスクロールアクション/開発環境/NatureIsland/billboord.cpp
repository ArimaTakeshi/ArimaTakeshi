//=============================================================================
//
// ビルボードの処理 [scene2D.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "billboord.h"
#include "manager.h"
#include "renderer.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILL_TEXTURE_NAME_1		"data\\TEXTURE\\billgrass.png"				//読み込むテクスチャファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3DTEXTURE9	CBillBoord::m_pTexture[MAX_BILLBOORD_TEX] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CBillBoord::CBillBoord() : CScene3D(4, CScene::OBJTYPE_BILLBOORD)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_bOnOff = false;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CBillBoord::~CBillBoord()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBillBoord::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CScene3D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBillBoord::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CBillBoord::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	//位置の初期化
	D3DXVECTOR3 pos = CScene3D::GetPosition();

	//ビルボード
	CScene3D::SetPosition(pos);
}
//=============================================================================
// 描画処理
//=============================================================================
void CBillBoord::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//CScene3D::Draw();

	//位置の初期化
	D3DXVECTOR3 BillPos = CScene3D::GetPosition();
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//近くのモデル以外を消す
	if (BillPos.x + 1500.0f >= PlayerPos.x && BillPos.x - 1300.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		CScene3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		CScene3D::Draw();
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CBillBoord * CBillBoord::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nTexType)
{
	CBillBoord *pBillBoord = NULL;

	//NULLチェック
	if (pBillBoord == NULL)
	{//メモリの動的確保

		pBillBoord = new CBillBoord;

		if (pBillBoord != NULL)
		{
			//オブジェクトクラスの生成
			pBillBoord->Init();
			//テクスチャの割り当て
			pBillBoord->BindTexture(m_pTexture[nTexType]);
			//位置の割り当て
			pBillBoord->SetPosSize(pos, size);
		}
	}

	return pBillBoord;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CBillBoord::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,BILL_TEXTURE_NAME_1,&m_pTexture[0]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CBillBoord::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD_TEX; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
