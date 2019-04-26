//=============================================================================
//
// レンダリング処理 [renderer.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "SceneModel.h"
#include "SceneBullet.h"
#include "Player.h"
#include "SceneEnemy.h"
#include "SceneBoss.h"
#include "dungeon.h"
#include "Font.h"

#include "2DPolygon.h"
#include "2DGage.h"
#include "3DPolygon.h"

#include "collision.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CScene	**CScene::m_PScene[MAX_SCENE] = {};			// 動的確保用
int		CScene::m_nNumAll[MAX_SCENE] = {0, 0, 0, 0, 0, 0, 0, 0};		// 生成したの数
int		CScene::m_nMemoryAll[MAX_SCENE] = { 0, 0, 0, 0, 0, 0, 0, 0 };	// 生成上限数
int		CScene::m_nDraw = 0;					// 現在の描画状態
int		CScene::m_nCntStart = 0;				// 現在の描画状態
bool	CScene::m_bPause = false;				//ポーズの有無
//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPrioryity)
{
	for (int nCount = 0; nCount < m_nMemoryAll[nPrioryity]; nCount++)
	{
		if (m_PScene[nPrioryity][nCount] == NULL)
		{
			m_PScene[nPrioryity][nCount] = this;
			m_nID = nCount;
			m_nPriority = nPrioryity;
			m_nNumAll[nPrioryity]++;	//総数++
			SetObjType(OBJTYPE_NONE);
			return;
		}
	}
	MessageBox(0, "エラー", "Sceneのコンストラクタ漏れてるよ", MB_OK);
}
//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene(void) {}

//==================================================================================================//
//    * 全解放関数 *
//==================================================================================================//
void CScene::ReleaseAll(void)
{
	CSceneBullet::UnLoad();
	CScene2D::UnLoad();
	CScene3D::UnLoad();
	CSceneAnim3D::UnLoad();
	CSceneModel::UnLoadModel();
	CDungeon::UnLoadModel();
	CDungeon::UnLoad();
	CSceneBoss::UnLoad();

	C2D::UnLoad();
	C2DGage::UnLoad();
	C3D::UnLoad();
	CFont::UnLoad();
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_PScene[nCntScene] != NULL)
		{//本体に何か入っているなら
			for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
			{//生成した全て回転
				if (m_PScene[nCntScene][nCount] != NULL)
				{//何か入っているなら終了とメモリ削除
					m_PScene[nCntScene][nCount][0].Uninit();
				}
			}
			delete[] m_PScene[nCntScene]; m_PScene[nCntScene] = NULL;
			m_nMemoryAll[nCntScene] = 0;	//空きリセット
			m_nNumAll[nCntScene] = 0;		//総数リセット
		}
	}
}
//==================================================================================================//
//    * 本体生成関数 *
//==================================================================================================//
void CScene::CreateAll(int nPrioryity, int nNumber)
{//最大枠生成
	CScene::m_PScene[nPrioryity] = new CScene*[nNumber]; CScene::m_nMemoryAll[nPrioryity] = nNumber;
	for (int nCount = 0; nCount < CScene::m_nMemoryAll[nPrioryity]; nCount++) { CScene::m_PScene[nPrioryity][nCount] = NULL; }
}

//=============================================================================
// 更新処理
//=============================================================================
void  CScene::UpdateAll(void)
{
	for (int nCntScene = (m_bPause ? MAX_SCENE - 1 : m_nCntStart); nCntScene < MAX_SCENE; nCntScene++)
	{
		if (m_PScene[nCntScene] != NULL)
		{// ポリゴンの更新処理
			for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
			{//生成された数分再生
			 //if ((*(PScene + nCount)) != NULL)
				if (m_PScene[nCntScene][nCount] != NULL)
				{//アドレスが存在するなら	//	(*PScene)->Update;
				 //(*(PScene + nCount))->Update();
				 //(*PScene)->Update;PScene++;
					m_PScene[nCntScene][nCount]->Update();
				}
			}
		}
	}
	CCollision::CollisionAll();
}
//=============================================================================
// 描画処理
//=============================================================================
void  CScene::DrawAll(LPDIRECT3DDEVICE9 &pDevice)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE - 1; nCntScene++)
	{
		if (m_PScene[nCntScene] != NULL)
		{// ポリゴンの描画処理
			if (nCntScene == BULLET_PRIORITY)
			{
				// バックバッファ＆Ｚバッファのクリア
				pDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
			}
			for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
			{//生成された数分再生
				if (m_PScene[nCntScene][nCount] != NULL)
				{//アドレスが存在するなら
					m_PScene[nCntScene][nCount]->Draw();
				}
			}
		}
	}
	CPlayer *pPlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		pPlayer = CManager::GetPlayer0();
		if (pPlayer != NULL) { pPlayer->DrawUI(); }
	}

	if (m_PScene[PAUSE_PRIORITY] != NULL)
	{// ポリゴンの描画処理
		for (int nCount = 0; nCount < m_nMemoryAll[PAUSE_PRIORITY]; nCount++)
		{//生成された数分再生
			if (m_PScene[PAUSE_PRIORITY][nCount] != NULL)
			{//アドレスが存在するなら
				m_PScene[PAUSE_PRIORITY][nCount]->Draw();
			}
		}
	}
}
//==================================================================================================//
//    * 描画準備関数 *
//==================================================================================================//
bool CScene::DrawPrepare(CScene::DRAW_TYPE DrawType, LPDIRECT3DDEVICE9 &pD3DDevice)
{
	if (DrawType == DRAW_TYPE_NO) { return true; }

	if (m_nDraw / 10 != DrawType / 10)
	{//現在のZテストと描画方法が違うなら
		if (DrawType >= CScene::DRAW_TYPE_ZNORMAL)
		{// Zテスト解除
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		}
		else
		{// Zテスト始動
			pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		}
	}
	if (m_nDraw % 10 != DrawType % 10)
	{//現在の合成方法が違うなら
		switch (DrawType % 10)
		{//ほんとは3行あることを忘れてはいけない...
		case CScene::DRAW_TYPE_NORMAL:// 通常
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case CScene::DRAW_TYPE_ADD:// αブレンディングを加算合成に設定
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_SUBTRACT:// 減算
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case CScene::DRAW_TYPE_MULTIPLY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
			break;
		case CScene::DRAW_TYPE_OVERLAY:
			pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO | D3DBLEND_ONE);
			pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		}
	}
	m_nDraw = DrawType;	//描画方法の代入

	return false;
}
//==================================================================================================//
//    * 自分削除関数 *
//==================================================================================================//
void CScene::Release()
{
	if (m_PScene[m_nPriority][m_nID] != NULL)
	{ 
		int nID = m_nID;
		int nPriority = m_nPriority;
		m_nNumAll[nPriority]--;
		delete this;
		m_PScene[nPriority][nID] = NULL;
	}
}
//=============================================================================
//	全オブジェクトを破壊
//=============================================================================
void CScene::BreakObject(void)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
		{//全シーン分回る
			if (m_PScene[nCntScene][nCount] != NULL)
			{
				m_PScene[nCntScene][nCount]->Uninit();
			}
		}
	}
}
//=============================================================================
//	指定したオブジェクトを破壊
//=============================================================================
void CScene::BreakObject(OBJTYPE obj)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		for (int nCount = 0; nCount < m_nMemoryAll[nCntScene]; nCount++)
		{//全シーン分回る
			if (m_PScene[nCntScene][nCount] != NULL)
			{
				if (obj == m_PScene[nCntScene][nCount]->GetObjType())
				{//指定のオブジェなら破壊
					m_PScene[nCntScene][nCount]->Uninit();
				}
			}
		}
	}
}
//=============================================================================
// シーンを返す
//=============================================================================
CScene **CScene::GetScene(int nPrioryity)
{
	return m_PScene[nPrioryity];
}
#ifdef _DEBUG
//=============================================================================
// FPS表示
//=============================================================================
//void CScene::DrawFPS(void)
//{
//	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	char str[256];
//
//	wsprintf(str, "FPS:%d\n", GetFPS());
//
//	// テキスト描画
//	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
//}
#endif
