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
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOGO_TEXTURE_NAME_1		"data\\TEXTURE\\second.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_2		"data\\TEXTURE\\timeback.png"		//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_3		"data\\TEXTURE\\tutorial.png"		//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_4		"data\\TEXTURE\\tutorial000.png"	//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_5		"data\\TEXTURE\\tutorial001.png"	//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_6		"data\\TEXTURE\\チュートリアル.jpg"	//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_7		"data\\TEXTURE\\PressAny.png"		//読み込むテクスチャファイル

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
CLogo::CLogo() : CScene2D(5, CScene::OBJTYPE_LOGO)//優先優位イニシャライズ
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntTutorial = 0;
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
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//位置の割り当て
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//移動量の割り当て
	D3DXVECTOR3 move;
	move = GetMove();

	m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y ));
	// 角度を出す
	m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

	m_rot.x += 0.02f;
	m_rot.y += 0.02f;

	//位置を更新(移動)
	pos.x += move.x;
	pos.y += move.y;

	if (m_nType == 2)
	{
		//一度のみ入る
		if (m_bOneCnt == false)
		{
			if (pos.x <= 160.0f)
			{//右に動かす
				move.x = 5;
			}
			else if (pos.x >= 160.0f)
			{//一度止める
				move.x = 0.0f;
				m_bOneCnt = true;
			}
		}
		//4秒後画面外に戻す
		if (m_nCntTutorial == 340)
		{//左に動かす
			move.x -= 5;
		}
		else if (m_nCntTutorial == 440)
		{
			//テクスチャの変更
			BindTexture(m_pTexture[3]);

			m_bOneCnt = false;
		}

		//4秒後画面外に戻す
		if (m_nCntTutorial == 780)
		{//左に動かす
			move.x -= 5;
		}
		else if (m_nCntTutorial == 880)
		{
			//テクスチャの変更
			BindTexture(m_pTexture[4]);

			m_bOneCnt = false;
		}

	}

	m_nCntTutorial++;

	//ロゴの位置とサイズ
	CScene2D::SetPosSize(pos,m_size);
	//ロゴの位置とサイズ
	CScene2D::SetMove(move);
	//回転処理
	//CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);

	//============================
	//     デバック用生成
	//============================
	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_1) == true)
	{
		Uninit();
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
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_7, &m_pTexture[6]);

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