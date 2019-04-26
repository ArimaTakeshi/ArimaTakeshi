//=============================================================================
//
// 印の壁処理 [markwall.cpp]
// Author : 有馬 武志
//
//=============================================================================
#include "markwall.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "imgui_arima.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MARKWALL_TEX_1	"data\\TEXTURE\\wall\\wall000.jpg"			// テクスチャの名前
#define MARKWALL_TEX_2	"data\\TEXTURE\\wall\\wall001.jpg"			// テクスチャの名前
#define MARKWALL_TEX_3	"data\\TEXTURE\\wall\\field03.jpg"			// テクスチャの名前
#define MARKWALL_TEX_4	"data\\TEXTURE\\wall\\rock_003.jpg"			// テクスチャの名前
#define MARKWALL_TEX_5	"data\\TEXTURE\\wall\\soil.jpg"				// テクスチャの名前
#define MARKWALL_TEX_6	"data\\TEXTURE\\wall\\scarp02.jpg"			// テクスチャの名前
#define MARKWALL_TEX_7	"data\\TEXTURE\\wall\\wallRock.jpg"			// テクスチャの名前
#define MARKWALL_TEX_8	"data\\TEXTURE\\wall\\Black.jpg"			// テクスチャの名前
#define MARKWALL_TEX_9	"data\\TEXTURE\\wall\\wall000.png"			// テクスチャの名前
#define MAX_SPEED		(3.0f)										// 壁の移動速度
#define MAX_LSHIFTSPEED	(0.5f)										// 壁の移動速度

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CMarkWall::m_pTexture[MAX_MARKWALL_TEX] = {};
int CMarkWall::m_nWallNum = 0;
CWall *CMarkWall::m_pWall = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CMarkWall::CMarkWall() : CScene3D(MARKWALL_PRIOTITY, CScene::OBJTYPE_MARKWALL)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_fWidthLength = 100.0f;
	m_fHightLength = 200.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMarkWall::~CMarkWall()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMarkWall::Init()
{
	//初期化処理
	CScene3D::Init();

	//種類の設定
	SetTypeNumber(TYPE_WALL);

	if (m_nType == 9)
	{
		//CScene3D::SetNor(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMarkWall::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CMarkWall::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene3D::Update();

	//設置モード
	int nSetMode = CImgui_Arima::GetSetMode();

	//壁の向きを代入する
	m_rot = CScene3D::GetRotation();

	//編集モードを開始
	if (nSetMode == 2)
	{
		//保存用データ
		float fWallWL = m_fWidthLength;
		float fWallHL = m_fHightLength;

		//-------------------------------------
		//        Imguiから値を貰う
		//-------------------------------------
		m_pos = CImgui_Arima::GetWallPos();
		m_rot = CImgui_Arima::GetWallRot();
		m_nWallTextureNumber = CImgui_Arima::GetWallType();
		m_fWidthLength = (float)CImgui_Arima::GetWallWL();
		m_fHightLength = (float)CImgui_Arima::GetWallHL();
		m_bSetWall = CImgui_Arima::GetWallSet();

		switch (m_nWallTextureNumber)
		{
		case 0:
			//テクスチャの種類
			m_nTexType = 0;
			// ブロックコンクリート
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 1:
			//テクスチャの種類
			m_nTexType = 1;
			// 黒い壁
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 2:
			//テクスチャの種類
			m_nTexType = 2;
			// 土壁
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 3:
			//テクスチャの種類
			m_nTexType = 3;
			// 上のほうが砂利
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 4:
			//テクスチャの種類
			m_nTexType = 4;
			// 上のほうが草
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 5:
			//テクスチャの種類
			m_nTexType = 5;
			// 岩
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 6:
			//テクスチャの種類
			m_nTexType = 6;
			// 下に草が生えている岩
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 7:
			//テクスチャの種類
			m_nTexType = 7;
			// 色黒
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		case 8:
			//テクスチャの種類
			m_nTexType = 8;
			// 少し透明な壁
			CMarkWall::BindTexture(m_pTexture[m_nTexType]);
			break;
		}

		//-------------------------------------
		//         オブジェクト生成
		//-------------------------------------
		if (m_bSetWall == true)
		{
			//オブジェクトの生成
			m_pWall = CWall::Create(m_pos, m_size, m_rot, m_nTexType);
			//置いた数の計算
			m_nWallNum += 1;
		}

		//情報を渡す
		CScene3D::SetWall(m_pos, m_rot, m_size);

		//-------------------------------------
		//         縦の長さ変更を変更
		//-------------------------------------
		if (fWallHL > m_fHightLength)
		{//分割数減少
		 //削除と生成
			UninitCreate(m_pos);
		}
		if (m_fHightLength > fWallHL)
		{//分割数増加
		 //削除と生成
			UninitCreate(m_pos);
		}

		//-------------------------------------
		//         横の長さ変更を変更
		//-------------------------------------
		if (fWallWL > m_fWidthLength)
		{//分割数減少
		 //削除と生成
			UninitCreate(m_pos);
		}
		if (m_fWidthLength > fWallWL)
		{//分割数増加
		 //削除と生成
			UninitCreate(m_pos);
		}

		//位置を保存
		if (CImgui_Arima::GetWallClicked() % 2 == 1)
		{
			CDebugProc::Print("保存！");
			m_pWall->TextSave();
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CMarkWall::Draw(void)
{
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//設置モード
	int nSetMode = CImgui_Arima::GetSetMode();

	//編集モードを開始
	if (nSetMode == 2)
	{
		CScene3D::Draw();
	}
}
//=============================================================================
// 生成処理
//=============================================================================
CMarkWall * CMarkWall::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nTexType)
{
	CMarkWall *pWall = NULL;

	//NULLチェック
	if (pWall == NULL)
	{//メモリの動的確保

		pWall = new CMarkWall;

		if (pWall != NULL)
		{
			//種類の設定
			pWall->m_nType = nTexType;
			//初期化処理
			pWall->Init();
			//位置の設定
			pWall->m_pos = pos;
			//当たり判定用
			pWall->m_size = size;
			//向きの設定
			pWall->m_rot = rot;
			//テクスチャの設定
			pWall->BindTexture(m_pTexture[nTexType]);
			//横幅の代入
			pWall->m_fWidthLength = size.x;
			//縦幅の代入
			pWall->m_fHightLength = size.y;
			//位置と回転とサイズ
			pWall->SetWall(pos, rot, size);
		}
	}

	return pWall;
}
//===============================================================================
//　削除と生成
//===============================================================================
void CMarkWall::UninitCreate(D3DXVECTOR3 pos)
{
	//削除
	CMarkWall::Uninit();

	//生成
	CMarkWall::Create(pos,D3DXVECTOR2(m_fWidthLength, m_fHightLength),m_rot, m_nTexType);
}
//=============================================================================
// 読み込み処理
//=============================================================================
HRESULT CMarkWall::Load(void)
{
	// デバイス取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャ生成
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, MARKWALL_TEX_9, &m_pTexture[8]);

	return S_OK;
}

//=============================================================================
// 開放処理
//=============================================================================
void CMarkWall::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MARKWALL_TEX; nCount++)
	{
		// テクスチャ破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}