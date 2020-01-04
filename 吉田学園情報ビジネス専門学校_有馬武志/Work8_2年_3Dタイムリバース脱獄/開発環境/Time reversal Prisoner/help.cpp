//=============================================================================
//
// ヘルプの処理 [help.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "help.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_NAME_0			"data\\TEXTURE\\案内\\案内1.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_1			"data\\TEXTURE\\案内\\案内2.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_2			"data\\TEXTURE\\案内\\案内3.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_3			"data\\TEXTURE\\案内\\案内4.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_4			"data\\TEXTURE\\案内\\案内6.png"		//読み込むテクスチャファイル

#define MAX_HELP				(128)							//ヘルプの最大数
#define HELP_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define HELP_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲
#define HELP_SPEED				(0.003f)						//ヘルプスピード

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CHelp::m_pTexture[MAX_HELP_TEXTURE] = {};
bool			   CHelp::m_bPause = false;
bool			   CHelp::m_bSerectEnd = false;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CHelp::CHelp(int nPriority,CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
	m_SelectColor = 0.0f;
	m_nCntState = 0;
	m_SelectNum = 0;
	m_nTxtureNumber = 0;
	m_nSize = D3DXVECTOR2(0.0f,0.0f);
}
//===============================================================================
//　デストラクタ
//===============================================================================
CHelp::~CHelp()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CHelp::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_SelectNum = 0;
	m_SelectColor = 1.0f;

	// 頂点情報を設定
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(40.0f, 40.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1240.0f , 40.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(40.0f, 680.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1240.0f, 680.0f, 0.0f);
	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(HELP_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, HELP_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(HELP_TEXTURE_UV_U, HELP_TEXTURE_UV_V);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CHelp::Uninit(void)
{
	//選んでる状態を戻す
	m_bSerectEnd = false;

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自身の削除
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CHelp::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoypad = CManager::GetInputJoyPad();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//フェードのポイント
	CFade::FADE pFade = CFade::GetFade();

	if (pCInputKeyBoard->GetKeyboardTrigger(DIK_RETURN) == true || pCInputMouse->GetMouseTrigger(0) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_B) == true || pCInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && m_bSerectEnd == false)
	{
		m_bSerectEnd = true;

		//ヘルプを閉じる
		CGame::SetHelp(false);

		if (pFade == CFade::FADE_NONE)
		{
			//ヘルプの選択の決定音
			pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE_SELECT);
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CHelp::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//ステージ移動の際にテクスチャ変更
	if (pStageNum == CGame::STAGENUM_1)
	{
		m_nTxtureNumber = 0;
	}
	else if (pStageNum == CGame::STAGENUM_2)
	{
		m_nTxtureNumber = 1;
	}
	else if (pStageNum == CGame::STAGENUM_3)
	{
		m_nTxtureNumber = 2;
	}
	else if (pStageNum == CGame::STAGENUM_4)
	{
		m_nTxtureNumber = 3;
	}
	else if (pStageNum == CGame::STAGENUM_5)
	{
		m_nTxtureNumber = 3;
	}
	else if (pStageNum == CGame::STAGENUM_6)
	{
		m_nTxtureNumber = 4;
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexture[m_nTxtureNumber]);
	//pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//===============================================================================
//　クリエイト
//===============================================================================
CHelp * CHelp::Create()
{
	CHelp *pPause = NULL;

	//NULLチェック
	if (pPause == NULL)
	{//メモリの動的確保

		pPause = new CHelp;

		if (pPause != NULL)
		{
			//オブジェクトクラスの生成
			pPause->Init();
		}
	}

	return pPause;
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CHelp::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_0, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_1, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_2, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_3, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_4, &m_pTexture[4]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CHelp::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_HELP_TEXTURE; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}