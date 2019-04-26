//=============================================================================
//
// ダメージ処理 [damage.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "damage.h"
#include "number.h"
#include "player.h"
#include <string>
#include <time.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SIZE_X		(SCREEN_WIDTH)
#define SIZE_Y		(SCREEN_HEIGHT)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CNumber *CDamage::m_apNumber[MAX_DAMAGE_NUMBER] = {};
int CDamage::m_nDamage = 0;

//=============================================================================
//デフォルトコンストラクタ
//=============================================================================
CDamage::CDamage() : CScene(5)//優先優位イニシャライズ
{
	m_nDamage = 0;
	m_nCount = 0;
	m_fLife = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
//デストラクタ
//=============================================================================
CDamage::~CDamage()
{

}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CDamage::Init(void)
{
	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();

	if (pPlayer != NULL)
	{
		m_pos = pPlayer->GetPosition();
	}

	//文字のタイプを入れる
	CNumber::SetType(CNumber::TYPE_DAMAGE);

	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		//if (m_apNumber[nCnt] == NULL)
		{
			m_apNumber[nCnt] = new CNumber;

			//if (m_apNumber[nCnt] != NULL)
			{
				m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (nCnt * 20.0f), m_pos.y + 10.0f, 0));
			}
		}
	}

	return S_OK;
}
//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CDamage::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->Uninit();
			delete m_apNumber[nCnt];
			m_apNumber[nCnt] = {};
		}
	}

	//自分自身の破棄
	Release();
}
//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CDamage::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Update();
	}
	if (m_nCount >= 15)
	{
		//自分自身の破棄
		Release();
	}
	else if (m_nCount == 16)
	{
		m_nCount = 0;
	}

	m_nCount++;
}
//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CDamage::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->Draw();
	}
}

//=============================================================================
//ポリゴンの生成処理
//=============================================================================
CDamage *CDamage::Create(void)
{
	CDamage *pDamage = {};

	if (pDamage == NULL)
	{//NULLだったら

	 //メモリの動的確保
		pDamage = new CDamage;

		if (pDamage != NULL)
		{//NULLじゃなかったら
			//ポリゴンの初期化処理
			pDamage->Init();
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULLじゃないです", "警告", MB_OK);
	}

	return pDamage;
}
//==============================================================================
// スコアの加算
//==============================================================================
void CDamage::AddDamage(int nValue)
{
	m_nDamage = nValue;		//スコアを代入

	int nDamage = m_nDamage;

	for (int nCnt = 0; nCnt < MAX_DAMAGE_NUMBER; nCnt++)
	{
		m_apNumber[nCnt]->SetNumber(nDamage);
		nDamage /= 10;
	}
}
//==============================================================================
// スコアの情報
//==============================================================================
int CDamage::GetDamage(void)
{
	return m_nDamage;
}