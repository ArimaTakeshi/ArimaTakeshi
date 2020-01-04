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
#include "billboord.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LOGO_TEXTURE_NAME_1		"data\\TEXTURE\\State\\none.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_2		"data\\TEXTURE\\State\\qusetion000.png"		//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_3		"data\\TEXTURE\\State\\exclamation000.png"	//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_4		"data\\TEXTURE\\State\\attack000.png"		//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_5		"data\\TEXTURE\\fram.png"					//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_6		"data\\TEXTURE\\State\\Stealth.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_7		"data\\TEXTURE\\State\\Hidden.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_8		"data\\TEXTURE\\State\\Caution.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_9		"data\\TEXTURE\\State\\Danger.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_10	"data\\TEXTURE\\案内\\コントローラー.png"	//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_11	"data\\TEXTURE\\案内\\案内1.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_12	"data\\TEXTURE\\案内\\案内2.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_13	"data\\TEXTURE\\案内\\案内3.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_14	"data\\TEXTURE\\案内\\案内4.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_15	"data\\TEXTURE\\案内\\案内6.png"			//読み込むテクスチャファイル
#define LOGO_TEXTURE_NAME_16	"data\\TEXTURE\\Tutorial.jpg"				//読み込むテクスチャファイル

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
int CLogo::m_nNextType = 0;
int CLogo::m_nNextFont = 0;

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
	m_nStateFont = 0;
	m_nStateType = 0;
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

	//表示状態のステータスのみに反映
	if (m_nType >= 0 && m_nType <= 3)
	{
		if (m_nStateType != m_nNextType)
		{
			m_nStateType = m_nNextType;
			//状態の値を入れる
			m_nType = m_nStateType;
		}
		//値の初期化
		m_nNextType = 0;
	}
	//表示状態のフォントのみに反映
	if (m_nType >= 5 && m_nType <= 8)
	{
		if (m_nStateFont != m_nNextFont)
		{
			m_nStateFont = m_nNextFont;
			//状態の値を入れる
			m_nType = m_nStateFont;
		}
		//値の初期化
		m_nNextFont = 5;
	}

	switch (m_nType)
	{
	case 0:
		//何もない状態の表示
		BindTexture(m_pTexture[0]);
		break;
	case 1:
		//ビックリマークの表示
		BindTexture(m_pTexture[1]);
		break;
	case 2:
		//発見の表示
		BindTexture(m_pTexture[2]);
		break;
	case 3:
		//見失う表示
		BindTexture(m_pTexture[3]);
		break;
	case 5:
		//Caution表示
		BindTexture(m_pTexture[5]);
		break;
	case 6:
		//Danger表示
		BindTexture(m_pTexture[6]);
		break;
	case 7:
		//hidden表示
		BindTexture(m_pTexture[7]);
		break;
	case 8:
		//Stealth表示
		BindTexture(m_pTexture[8]);
		break;
	}
	
	//変形できる
	if (m_nTransformType == 1)
	{
		if (m_nType == 4)
		{//フレーム
			CScene2D::SetPosDiamond(pos, m_size, D3DXVECTOR4(25.0f, 25.0f, 3.0f, 3.0f));
		}
	}


	//位置を更新(移動)
	pos.x += move.x;
	pos.y += move.y;

	if (m_nTransformType == 0)
	{
		//ロゴの位置とサイズ
		CScene2D::SetPosSize(pos, m_size);
		//ロゴの位置とサイズ
		CScene2D::SetMove(move);
		//回転処理
		//CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();

	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType,int nTransformType)
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
			//変形できる種類
			pLogo->m_nTransformType = nTransformType;
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
//　状態の優先順位
//===============================================================================
void CLogo::SetLogoState(int nStateType, int nStateFont)
{
	//アイコンの優先順位
	if (m_nNextType <= nStateType)
	{
		m_nNextType = nStateType;
	}
	//フォントの優先順位
	if (m_nNextFont <= nStateFont)
	{
		m_nNextFont = nStateFont;
	}
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
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_9, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_10, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_11, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_12, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_13, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_14, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_15, &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, LOGO_TEXTURE_NAME_16, &m_pTexture[15]);

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