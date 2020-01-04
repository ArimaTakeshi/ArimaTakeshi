//=============================================================================
//
// ガイドの処理 [guide.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "guide.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "billboord.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GUIDE_TEXTURE_NAME_1		"data\\TEXTURE\\案内\\ポーズ.png"				//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_2		"data\\TEXTURE\\案内\\B3第2収容棟.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_3		"data\\TEXTURE\\案内\\B2全集階層食堂.png"		//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_4		"data\\TEXTURE\\案内\\B1囚人用廊下.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_5		"data\\TEXTURE\\案内\\B1囚人審査路.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_6		"data\\TEXTURE\\案内\\F1囚人用玄関.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_7		"data\\TEXTURE\\案内\\地上運動所.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_8		"data\\TEXTURE\\案内\\マップ.png"				//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_9		"data\\TEXTURE\\案内\\現在の位置.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_10		"data\\TEXTURE\\案内\\星.png"					//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_11		"data\\TEXTURE\\案内\\顔.png"					//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_12		"data\\TEXTURE\\案内\\Rewind time.png"			//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_13		"data\\TEXTURE\\title.png"						//読み込むテクスチャファイル
#define GUIDE_TEXTURE_NAME_14		"data\\TEXTURE\\PressAButton.png"				//読み込むテクスチャファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGuide::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CGuide::CGuide() : CScene2D(5, CScene::OBJTYPE_GUIDE)//優先優位イニシャライズ
{
	m_nType = 0;
	m_size = D3DXVECTOR2(0.0f,0.0f);
	m_fLength = 0.0f;
	m_fAngle = 0.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntBandTimer = 0;
	m_nCntStar = 0;
	m_fColorCount = 0.0f;
	m_bOneCnt = false;
	m_bPressA = false;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CGuide::~CGuide()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGuide::Init(void)
{
	m_fColorCount = 0;

	CScene2D::Init();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGuide::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGuide::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	CSound *pSound = CManager::GetSound();

	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//位置の割り当て
	D3DXVECTOR3 pos;
	pos = GetPosition();

	//移動量の割り当て
	D3DXVECTOR3 move;
	move = GetMove();

	//色の割り当て
	D3DXCOLOR col[4];

	//モード
	CManager::MODE pMode = CManager::GetMode();
	
	//マップ上の星の位置
	if (m_nType == 9)
	{
		// 長さを出す
		m_fLength = sqrtf((m_size.x / 2 + m_size.x / 2) * (m_size.y / 2 + m_size.y / 2));
		// 角度を出す
		m_fAngle = atan2f(m_size.x / 2, m_size.y / 2);

		if (m_nCntStar == 60)
		{
			//カウンターを0に戻す
			m_nCntStar = 0;
		}
		else if (m_nCntStar >= 30)
		{
			//右回転
			m_rot.x -= 0.01f;
			m_rot.y -= 0.01f;
		}
		else if (m_nCntStar >= 0)
		{
			//左回転
			m_rot.x += 0.01f;
			m_rot.y += 0.01f;
		}

		//カウンターの増加
		m_nCntStar++;

		switch (pStageNum)
		{
		case CGame::STAGENUM_1:
			pos = D3DXVECTOR3(1130.0f, 665.0f, 0.0f);
			break;
		case CGame::STAGENUM_2:
			pos = D3DXVECTOR3(1225.0f, 595.0f, 0.0f);
			break;
		case CGame::STAGENUM_3:
			pos = D3DXVECTOR3(1140.0f, 535.0f, 0.0f);
			break;
		case CGame::STAGENUM_4:
			pos = D3DXVECTOR3(1225.0f, 480.0f, 0.0f);
			break;
		case CGame::STAGENUM_5:
			pos = D3DXVECTOR3(1150.0f, 415.0f, 0.0f);
			break;
		case CGame::STAGENUM_6:
			pos = D3DXVECTOR3(1165.0f, 330.0f, 0.0f);
			break;
		}
	}

	if (pMode == CManager::MODE_TITLE)
	{
		if (m_nType == 13)
		{
			if (pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_A) == true || pCInputJoyPad->GetTrigger(CInputJoypad::BUTTON_B) == true || pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true)
			{
				//Aボタンが押された
				m_bPressA = true;
			}
			
			if (m_bPressA == true)
			{
				//点滅処理
				//選択しているカラーの値を減らしていく
				m_fColorCount -= 0.09f;

				if (m_fColorCount < 0.5f)
				{//信託しているカラーが0.5を切ったらカラーの値が増えてく
					m_fColorCount = 1.0f;
				}

				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			}
			else if (m_bPressA == false)
			{
				//点滅処理
				//選択しているカラーの値を減らしていく
				m_fColorCount -= 0.009f;

				if (m_fColorCount < 0.5f)
				{//信託しているカラーが0.5を切ったらカラーの値が増えてく
					m_fColorCount = 1.0f;
				}

				col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
				col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			}

			CScene2D::SetColor(&col[0]);
		}

		if (m_nType == 12)
		{
			//点滅処理
			//選択しているカラーの値を減らしていく
			m_fColorCount += 0.009f;

			if (m_fColorCount > 1.0f)
			{//信託しているカラーが0.5を切ったらカラーの値が増えてく
				m_fColorCount = 1.0f;
			}

			col[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			col[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			col[2] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
			col[3] = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorCount);
		}
	}
	else
	{
		//点滅状態を初期化
		m_bPressA = false;
	}

	//案内表記
	if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2 || pStageNum == CGame::STAGENUM_3 || pStageNum == CGame::STAGENUM_4 || pStageNum == CGame::STAGENUM_5 || pStageNum == CGame::STAGENUM_6)
	{
		//案内表記の表示
		if (m_nType != 0 && m_nType != 7 && m_nType != 8 && m_nType != 9 && m_nType != 10 && m_nType != 11 && m_nType != 12 && m_nType != 13)
		{
			if (m_nCntMapGuideTimer >= 200)
			{//左に動かす
				move.x = -40;
			}
			else if (m_nCntMapGuideTimer >= 80)
			{//左に動かす
				if (pos.x >= SCREEN_WIDTH / 2)
				{//右に動かす
					move.x = -40;
				}
				else if (pos.x <= SCREEN_WIDTH / 2)
				{//一度止める
					move.x = 0.0f;
				}
			}

			m_nCntMapGuideTimer++;
		}
	}

	//位置を更新(移動)
	pos.x += move.x;
	pos.y += move.y;

	if (m_nType != 9)
	{
		//ロゴの位置とサイズ
		CScene2D::SetPosSize(pos, m_size);
		//ロゴの位置とサイズ
		CScene2D::SetMove(move);
	}
	else if (m_nType == 9)
	{//回転処理を入れている種類のみ
		CScene2D::SetSpin(pos, m_fAngle, m_fLength, m_rot);
	}

	if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2 || pStageNum == CGame::STAGENUM_3 || pStageNum == CGame::STAGENUM_4 || pStageNum == CGame::STAGENUM_5 || pStageNum == CGame::STAGENUM_6)
	{
		//案内帯の出現
		if (m_nType == 0)
		{
			if (m_nCntBandTimer >= 240)
			{//帯の縮小
				m_size.y -= 5.0f;

				if (m_size.x == 0.0f || m_size.y == 0.0f)
				{
					//サイズが見えなくなった時に削除する
					CGuide::Uninit();

					m_nCntBandTimer = 0;
				}
			}
			else if (m_nCntBandTimer >= 60)
			{//帯の出現
				if (m_size.y < 100.0f / 2)
				{// 指定の高さまで太くする
					m_size.y += 5.0f;
					// 幅を画面幅に
					m_size.x = SCREEN_WIDTH;
				}
			}
			//カウントを増加
			m_nCntBandTimer++;
		}
	}

	//画面左に進み続けた場合
	if (pos.x <= -1280.0f)
	{
		//削除
		CGuide::Uninit();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CGuide::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//　クリエイト
//===============================================================================
CGuide * CGuide::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,int nType)
{
	CGuide *pGuide = NULL;

	//NULLチェック
	if (pGuide == NULL)
	{//メモリの動的確保

		pGuide = new CGuide;

		if (pGuide != NULL)
		{
			//種類を割り当てる
			pGuide->m_nType = nType;
			//オブジェクトクラスの生成
			pGuide->Init();
			//テクスチャを割り当てる
			pGuide->BindTexture(m_pTexture[nType]);
			//位置を割り当てる
			pGuide->SetPosition(pos);
			//サイズの割り当て
			pGuide->m_size = size;
		}
	}

	return pGuide;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CGuide::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_1,&m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_9, &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_10, &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_11, &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_12, &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_13, &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, GUIDE_TEXTURE_NAME_14, &m_pTexture[13]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CGuide::UnLoad(void)
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