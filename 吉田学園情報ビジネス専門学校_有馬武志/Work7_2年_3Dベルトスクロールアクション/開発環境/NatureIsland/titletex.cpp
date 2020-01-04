//=============================================================================
//
// タイトルテキストの処理 [titletex.cpp]
// Author : 荒谷由朗
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "title.h"
#include "titletex.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_TEXTURE_NAME_0		"data\\TEXTURE\\title\\.jpg"					// 落ち葉(仮)
#define TITLE_TEXTURE_NAME_1		"data\\TEXTURE\\title\\green0.png"				// 草
#define TITLE_TEXTURE_NAME_2		"data\\TEXTURE\\title\\titleboard.png"			// タイトル
#define TITLE_TEXTURE_NAME_3		"data\\TEXTURE\\title\\flash.png"				// 光
#define TITLE_TEXTURE_NAME_4		"data\\TEXTURE\\title\\title000.jpg"			// 草背景
#define TITLE_TEXTURE_NAME_5		"data\\TEXTURE\\title\\inSUMMER.png"			// サブタイトル
#define TITLE_TEXTURE_NAME_6		"data\\TEXTURE\\title\\nature_n.png"			//「N」
#define TITLE_TEXTURE_NAME_7		"data\\TEXTURE\\title\\nature_a.png"			//「a」
#define TITLE_TEXTURE_NAME_8		"data\\TEXTURE\\title\\nature_t.png"			//「t」
#define TITLE_TEXTURE_NAME_9		"data\\TEXTURE\\title\\nature_u.png"			//「u」
#define TITLE_TEXTURE_NAME_10		"data\\TEXTURE\\title\\nature_r.png"			//「r」
#define TITLE_TEXTURE_NAME_11		"data\\TEXTURE\\title\\nature_e.png"			//「e」
#define TITLE_TEXTURE_NAME_12		"data\\TEXTURE\\title\\island_i(large).png"		//「I」
#define TITLE_TEXTURE_NAME_13		"data\\TEXTURE\\title\\island_s.png"			//「s」
#define TITLE_TEXTURE_NAME_14		"data\\TEXTURE\\title\\island_i(small).png"		//「l」
#define TITLE_TEXTURE_NAME_15		"data\\TEXTURE\\title\\island_a.png"			//「a」
#define TITLE_TEXTURE_NAME_16		"data\\TEXTURE\\title\\island_n.png"			//「n」
#define TITLE_TEXTURE_NAME_17		"data\\TEXTURE\\title\\island_d.png"			//「d」
#define TITLE_TEXTURE_NAME_18		"data\\TEXTURE\\title\\PressAny.png"			// AnyButton(仮)
#define TITLE_TEXTURE_NAME_19		"data\\TEXTURE\\title\\green1.png"				// 草
#define TITLE_TEXTURE_NAME_20		"data\\TEXTURE\\title\\green2.png"				// 草
#define TITLE_TEXTURE_NAME_21		"data\\TEXTURE\\title\\green3.png"				// 草
#define TITLE_TEXTURE_NAME_22		"data\\TEXTURE\\title\\leaf000.png"				// 落ち葉

#define TITLE_STERT (400)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CTitletex::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CTitletex::CTitletex() : CScene2D(4)//優先優位イニシャライズ
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_sizeDest = D3DXVECTOR2(0.0f, 0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
	m_nCntflame = 0;
	m_nCntDelete = 0;
	m_nBlink = false;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CTitletex::~CTitletex()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitletex::Init(void)
{
	srand((unsigned int)time(0));
	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTitletex::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTitletex::Update(void)
{
	// 入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();
	// 位置の取得
	D3DXVECTOR3 pos = GetPosition(), posAngle;
	D3DXVECTOR2 sizeAngle;
	D3DXCOLOR col[4];

	CTitle::TYPE pTitleType = CTitle::GetType();

	if (m_nType == 0 || m_nType == 1)
	{// 草(gleen0.png)
		BindTexture(m_pTexture[1]);

		// 目的の更新
		if (m_nType == 0)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();					// 座標の取得
				m_posDest.x -= 185.0f;						// 移動量
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);	// 拡大量
			}
		}
		else if (m_nType == 1)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();					// 座標の取得
				m_posDest.x += 185.0f;						// 移動量
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);	// 拡大量
			}
		}

		// 徐々に動かす
		// 位置---------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.x > D3DX_PI)
		{
			posAngle.x -= D3DX_PI * 2.0f;
		}
		else if (posAngle.x < -D3DX_PI)
		{
			posAngle.x += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// サイズ-------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 19)
	{// 草(gleen1.png)
		BindTexture(m_pTexture[19]);

		// 目的の更新
		if (m_nCntflame % 60 == 0)
		{
			m_posDest = GetPosition();					   // 座標の取得
			m_posDest.y += 35.0f;						   // 移動量
			m_sizeDest += D3DXVECTOR2(90.0f, 0.0f);		   // 拡大量
		}
		// 徐々に動かす
		// 位置---------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.y > D3DX_PI)
		{
			posAngle.y -= D3DX_PI * 2.0f;
		}
		else if (posAngle.y < -D3DX_PI)
		{
			posAngle.y += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// サイズ-------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 20 || m_nType == 22)
	{// 草(gleen2.png)
		BindTexture(m_pTexture[20]);

		// 目的の更新
		if (m_nType == 20)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // 座標の取得
				m_posDest.x -= 120.0f;					   // 移動量
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);   // 拡大量
			}
		}
		else if (m_nType == 22)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // 座標の取得
				m_posDest.x += 120.0f;					   // 移動量
				m_sizeDest += D3DXVECTOR2(20.0f, 20.0f);   // 拡大量
			}
		}

		// 徐々に動かす
		// 位置----------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.x > D3DX_PI)
		{
			posAngle.x -= D3DX_PI * 2.0f;
		}
		else if (posAngle.x < -D3DX_PI)
		{
			posAngle.x += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// サイズ--------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 21 || m_nType == 23)
	{// 草(gleen3.png)
		BindTexture(m_pTexture[21]);

		// 目的の更新
		if (m_nType == 21)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // 座標の取得
				m_posDest.x -= 60.0f;					   // 移動量
				m_sizeDest += D3DXVECTOR2(10.0f, 20.0f);   // 拡大量
			}
		}
		else if (m_nType == 23)
		{
			if (m_nCntflame % 60 == 0)
			{
				m_posDest = GetPosition();				   // 座標の取得
				m_posDest.x += 60.0f;					   // 移動量
				m_sizeDest += D3DXVECTOR2(10.0f, 20.0f);   // 拡大量
			}
		}

		// 徐々に動かす
		// 位置----------------------------------------------
		posAngle = m_posDest - pos;
		if (posAngle.x > D3DX_PI)
		{
			posAngle.x -= D3DX_PI * 2.0f;
		}
		else if (posAngle.x < -D3DX_PI)
		{
			posAngle.x += D3DX_PI * 2.0f;
		}
		pos += (posAngle / 60);
		// サイズ--------------------------------------------
		sizeAngle = m_sizeDest - m_size;
		if (sizeAngle.y > D3DX_PI)
		{
			sizeAngle.y -= D3DX_PI * 2.0f;
		}
		else if (sizeAngle.y < -D3DX_PI)
		{
			sizeAngle.y += D3DX_PI * 2.0f;
		}
		m_size += (sizeAngle / 60);
	}
	else if (m_nType == 2)
	{// タイトルロゴ
		if (pTitleType == CTitle::TYPE_NONE)
		{// スキップ状態かどうか
			if (m_nCntflame >= TITLE_STERT)
			{// 光が消えた後
				if (m_nCntflame == TITLE_STERT)
				{
					m_posDest = GetPosition();							   // 座標の取得
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);	   // 移動量
				}
				// 位置-------------------------------------------------
				posAngle = m_posDest - pos;
				if (posAngle.x > D3DX_PI)
				{
					posAngle.x -= D3DX_PI * 2.0f;
				}
				else if (posAngle.x < -D3DX_PI)
				{
					posAngle.x += D3DX_PI * 2.0f;
				}
				pos += (posAngle / 60);
			}
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{// スキップ状態だったとき
			pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f);
		}
	}
	else if (m_nType == 3)
	{// 光
		if ((m_nCounterAnim % 200) == 0)		// アニメーションの速さを変えられる
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			if (m_nPatternAnim >= 10)
			{// 最後のアニメーションで固定する
				m_nPatternAnim = 9;
			}
			CScene2D::SetTexture(m_nPatternAnim, 1, 10);
		}
		if (m_nCntflame >= 100)
		{// 徐々に薄くする
			m_nCntDelete++;
			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.01f));
		}
		else
		{// 色の初期値
			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		CScene2D::SetColor(&col[0]);
	}
	else if (m_nType == 5)
	{// サブタイトル
		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// 角度を出す
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);
		m_rot.x = 0.1f;
		m_rot.y = 0.1f;

		if (pTitleType == CTitle::TYPE_NONE)
		{// スキップ状態かどうか
			if (m_nCntflame >= 10)
			{// 徐々に大きく
				if (m_size.x > 230.0f)
				{
					m_size -= D3DXVECTOR2(8.0f, 8.0f);
				}
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
			}
			else
			{
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
			}
			CScene2D::SetColor(&col[0]);
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{
			m_size = D3DXVECTOR2(230.0f, 150.0f);
			m_nCntDelete++;
			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.5f);
			CScene2D::SetColor(&col[0]);
		}
	}
	else if (m_nType == 6 || m_nType == 7 || m_nType == 8 || m_nType == 9 || m_nType == 10 || m_nType == 11
		|| m_nType == 12 || m_nType == 13 || m_nType == 14 || m_nType == 15 || m_nType == 16 || m_nType == 17)
	{// 文字
		if (pTitleType == CTitle::TYPE_NONE)
		{
			switch (m_nType)
			{
			case 6:
				if (m_nCntflame == TITLE_STERT + 100)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 100)
				{
					// 位置
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 7:
				if (m_nCntflame == TITLE_STERT + 110)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 110)
				{
					// 位置
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 8:
				if (m_nCntflame == TITLE_STERT + 120)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 120)
				{
					// 位置
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 9:
				if (m_nCntflame == TITLE_STERT + 130)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 130)
				{
					// 位置
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 10:
				if (m_nCntflame == TITLE_STERT + 140)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 140)
				{
					// 位置
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;
			case 11:
				if (m_nCntflame == TITLE_STERT + 150)
				{
					m_posDest = GetPosition();
					m_posDest = pos + D3DXVECTOR3(0.0f, 350.0f, 0.0f);
				}
				else if (m_nCntflame >= TITLE_STERT + 150)
				{
					// 位置
					posAngle = m_posDest - pos;
					if (posAngle.x > D3DX_PI)
					{
						posAngle.x -= D3DX_PI * 2.0f;
					}
					else if (posAngle.x < -D3DX_PI)
					{
						posAngle.x += D3DX_PI * 2.0f;
					}
					pos += (posAngle / 60);
				}
				break;

			case 12:
				// 徐々に大きく
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 13:
				// 徐々に大きく
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 14:
				// 徐々に大きく
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 15:
				// 徐々に大きく
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 16:
				// 徐々に大きく
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			case 17:
				// 徐々に大きく
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_nCntDelete * 0.01f);
				CScene2D::SetColor(&col[0]);
				break;
			}
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{// スキップ時
			switch (m_nType)
			{
			case 6:
				pos = D3DXVECTOR3(340.0f, 140.0f, 0.0f);
				break;
			case 7:
				pos = D3DXVECTOR3(405.0f, 155.0f, 0.0f);
				break;
			case 8:
				pos = D3DXVECTOR3(455.0f, 140.0f, 0.0f);
				break;
			case 9:
				pos = D3DXVECTOR3(510.0f, 152.0f, 0.0f);
				break;
			case 10:
				pos = D3DXVECTOR3(570.0f, 153.0f, 0.0f);
				break;
			case 11:
				pos = D3DXVECTOR3(620.0f, 153.0f, 0.0f);
				break;

			case 12:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 13:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 14:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 15:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 16:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			case 17:
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				CScene2D::SetColor(&col[0]);
				break;
			}
		}
	}
	else if (m_nType == 18)
	{// PressAny
		if (pTitleType == CTitle::TYPE_NONE)
		{
			if (m_nCntflame >= TITLE_STERT + 500)
			{
				if (m_nBlink == false)
				{
					m_nCntDelete++;
					col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
					if (col[0].a <= 0.25f)
					{
						m_nCntDelete = 0;
						m_nBlink = true;
					}
				}
				else if (m_nBlink == true)
				{
					m_nCntDelete++;
					col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
					if (col[0].a >= 1.0f)
					{
						m_nCntDelete = 0;
						m_nBlink = false;
					}
				}
				CScene2D::SetColor(&col[0]);
			}
			else
			{
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				CScene2D::SetColor(&col[0]);
			}
		}
		else if (pTitleType == CTitle::TYPE_SKIP)
		{
			if (m_nBlink == false)
			{//	カラーを薄くする
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f - (m_nCntDelete * 0.02f));
				if (col[0].a <= 0.25f)
				{
					m_nCntDelete = 0;
					m_nBlink = true;
				}
			}
			else if (m_nBlink == true)
			{//	カラーを濃くする
				m_nCntDelete++;
				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f + (m_nCntDelete * 0.02f));
				if (col[0].a >= 1.0f)
				{
					m_nCntDelete = 0;
					m_nBlink = false;
				}
			}
			CScene2D::SetColor(&col[0]);
		}
	}
	else if(m_nType == 24)
	{// 落ち葉(大)
		BindTexture(m_pTexture[22]);

		if ((m_nCounterAnim % 100) == 0)		// アニメーションの速さを変えられる
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 10, 6);
		}

		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// 角度を出す
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);
		m_rot.x = 0.1f;
		m_rot.y = 0.1f;

		pos.x += 13.0f;		// 移動量(X)
		pos.y += -4.0f;		// 移動量(Y)
	}
	else if (m_nType == 25)
	{// 落ち葉(小)
		BindTexture(m_pTexture[22]);

		if ((m_nCounterAnim % 100) == 0)		// アニメーションの速さを変えられる
		{
			m_nPatternAnim = (m_nPatternAnim + 1);

			CScene2D::SetTexture(m_nPatternAnim, 10, 6);
		}

		m_fLength = sqrtf((m_size.x + m_size.x) * (m_size.y + m_size.y));
		// 角度を出す
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);
		m_rot.x = 0.1f;
		m_rot.y = 0.1f;

		pos.x += 11.0f;		// 移動量(X)
		pos.y += -5.0f;		// 移動量(Y)
	}
	else if (m_nType == 26)
	{// 草背景
		BindTexture(m_pTexture[4]);
	}

	if (m_nType == 5 || m_nType == 24 || m_nType == 25)
	{
		// 回転処理
		CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}
	else
	{
		CScene2D::SetPosSize(pos, m_size);
	}

	// 終了処理==================================================================================
	if (m_nType == 0 || m_nType == 1 || m_nType == 19 ||
		m_nType == 20 || m_nType == 21 || m_nType == 22 || m_nType == 23)
	{// 草
		if (m_nCntflame == 200)
		{
			Uninit();
		}
	}
	else if (m_nType == 3)
	{// 光
		if (m_nCntflame == 400)
		{
			Uninit();
		}
	}
	else if (m_nType == 24 || m_nType == 25)
	{
		if (pos.x >= SCREEN_WIDTH)
		{
			Uninit();
		}
	}
	else if (m_nType == 26)
	{		
		if (m_nCntflame == 250)
		{
			Uninit();
		}
	}
	if (pTitleType == CTitle::TYPE_SKIP)
	{
		if (m_nType == 0 || m_nType == 1 || m_nType == 3 || m_nType == 19
			|| m_nType == 20 || m_nType == 21 || m_nType == 22 || m_nType == 23 || m_nType == 26)
		{
			Uninit();
		}
	}

	m_nCntflame++;		// カウンターの更新
}
//=============================================================================
// 描画処理
//=============================================================================
void CTitletex::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CTitletex * CTitletex::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, int nType)
{
	CTitletex *pTitleTEX = NULL;

	//NULLチェック
	if (pTitleTEX == NULL)
	{//メモリの動的確保

		pTitleTEX = new CTitletex;

		if (pTitleTEX != NULL)
		{
			//種類を割り当てる
			pTitleTEX->m_nType = nType;
			//オブジェクトクラスの生成
			pTitleTEX->Init();
			//テクスチャを割り当てる
			pTitleTEX->BindTexture(m_pTexture[nType]);
			//位置を割り当てる
			pTitleTEX->SetPosition(pos);
			//サイズの割り当て
			pTitleTEX->m_size = size;
			pTitleTEX->m_sizeDest = size;
		}
	}

	return pTitleTEX;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CTitletex::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_3, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_4, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_5, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_6, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_7, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_8, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_9, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_10, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_11, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_12, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_13, &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_14, &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_15, &m_pTexture[15]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_16, &m_pTexture[16]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_17, &m_pTexture[17]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_18, &m_pTexture[18]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_19, &m_pTexture[19]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_20, &m_pTexture[20]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_21, &m_pTexture[21]);
	D3DXCreateTextureFromFile(pDevice, TITLE_TEXTURE_NAME_22, &m_pTexture[22]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CTitletex::UnLoad(void)
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