//==================================================================================================//
//
//    * [dungeon.cpp] *
//    * Author Ryo Sugimoto *
//
//==================================================================================================//
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用

#include "manager.h"
#include "scene.h"
#include "scene3D.h"
#include "sceneAnim3D.h"
#include "sceneModel.h"
#include "ScenePlayer.h"
#include "SceneEnemy.h"
#include "SceneBoss.h"
#include "3DNumber.h"
#include "Font.h"
#include "camera.h"
#include "dungeon.h"
#include "camera.h"
#include "collision.h"

#include "Game.h"
#include "Versus.h"
//==================================================================================================//
//    * マクロ定義 *
//==================================================================================================//
#define MAP_SIZE		(30.0f)
#define CHIP_UV			(CHIP_SIZE * 0.5f)
#define CHIP_BIG		(CHIP_UV * 2.0f * 120.0f)
#define MAX_VTX			(3)

#define TEX_STAGE0		(BOSS_STAGE - 2)
#define TEX_STAGE1		(BOSS_STAGE - 1)
#define TEX_STAGE2		(BOSS_STAGE)

#define DUNGEON_TIME	(60 * 180 + 1)
#define SHOP_TIME	(60 * 180 + 1)
#define VERSUS_TIME	(60 * 120 + 1)

//==================================================================================================//
//    * 静的メンバ変数宣言 *
//==================================================================================================//
LPDIRECT3DTEXTURE9		CDungeon::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ
CSceneModel::MODEL_DRAW *CDungeon::m_Model_Draw[MODEL_MAX] = {};	//モデルへのポインタ
C2DAnim					*CDungeon::m_pFrontBG[MAP_MAX_EFFECT];	//前側の背景
CSceneDungeonBG			*CDungeon::m_pBG = NULL;		//弾の後ろ背景

CNumber					*CDungeon::m_pTimer = NULL;	//タイマー

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CDungeon::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			case TEX_FIELD_0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/FIELD/Field_000.jpg", &m_pTexture[tex]);	break;
			case TEX_FIELD_1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/FIELD/Field_001.jpg", &m_pTexture[tex]);	break;
			case TEX_WALL_0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/WALL/998_stone_.jpg", &m_pTexture[tex]);	break;
			case TEX_WALL_1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/WALL/997_stone_s.jpg", &m_pTexture[tex]);	break;
			case TEX_WALL_2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/WALL/999_stone_s.jpg", &m_pTexture[tex]);	break;
			case TEX_RIVER_0:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/RIVER/sea000.jpg", &m_pTexture[tex]);		break;
			case TEX_RIVER_1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/RIVER/river000.jpg", &m_pTexture[tex]);		break;
			}
		}
		return &m_pTexture[tex];
	}
	return &m_pTexture[TEXTURE_MAX - 1];
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CDungeon::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * モデル生成関数 *
//==================================================================================================//
void CDungeon::LoadModel(MODEL model)
{
	if (model < MODEL_MAX)
	{//範囲確認
		if (m_Model_Draw[model] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			m_Model_Draw[model] = new MODEL_DRAW;
			switch (model)
			{//読み込み
			case MODEL_FIELD:
				D3DXLoadMeshFromX("data/MODEL/Field_000.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			case MODEL_WALL:
				D3DXLoadMeshFromX("data/MODEL/Wall_000.x",
					D3DXMESH_SYSTEMMEM, pD3DDevice, NULL, &m_Model_Draw[model]->pBuffMatModel, NULL, &m_Model_Draw[model]->nNumMatModel, &m_Model_Draw[model]->MeshModel);
				break;
			}
		}
	}
}
//==================================================================================================//
//    * モデル生成関数 *
//==================================================================================================//
void CDungeon::UnLoadModel(void)
{
	for (int nCount = 0; nCount < MODEL_MAX; nCount++)
	{
		if (m_Model_Draw[nCount] != NULL)
		{
			// メッシュの開放
			if (m_Model_Draw[nCount]->MeshModel != NULL)
			{
				m_Model_Draw[nCount]->MeshModel->Release();
				m_Model_Draw[nCount]->MeshModel = NULL;
			}

			// マテリアルの開放
			if (m_Model_Draw[nCount]->pBuffMatModel != NULL)
			{
				m_Model_Draw[nCount]->pBuffMatModel->Release();
				m_Model_Draw[nCount]->pBuffMatModel = NULL;
			}
			delete m_Model_Draw[nCount]; m_Model_Draw[nCount] = NULL;
		}
	}
}

//==================================================================================================//
//    * 生成関数 *
//==================================================================================================//
HRESULT CDungeon::Init(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	float	fCol;

	//設定
	CManager::GetDungeon() = this;
	CScene::SetObjType(OBJTYPE_DUNGEON);

	//画像生成
	Load(TEX_FIELD_0);
	Load(TEX_FIELD_1);
	Load(TEX_RIVER_0);
	Load(TEX_RIVER_1);
	//モデル生成
	LoadModel(MODEL_FIELD);
	LoadModel(MODEL_WALL);
	m_BGM = CSound::LABEL_MAX;

	m_nMapChip = NULL;
	m_bManager = true;
	m_nShop = 0;
	m_nQuake = 0;

	// 頂点バッファを生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_VTX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_VTX; nCount++)
	{//地面　池1、2、後ろ壁　合計4つ
		switch (nCount)
		{
		case 0://池1
			fCol = 1.0f;
			break;
		case 1://池2
			fCol = 0.5f;
			break;
		case 2://場外
			fCol = 1.0f;
			break;
		}

		//pos
		pVtx[nCount * 4].pos = D3DXVECTOR3(-CHIP_BIG, 0.0f, CHIP_BIG);
		pVtx[nCount * 4 + 1].pos = D3DXVECTOR3(CHIP_BIG, 0.0f, CHIP_BIG);
		pVtx[nCount * 4 + 2].pos = D3DXVECTOR3(-CHIP_BIG, 0.0f, -CHIP_BIG);
		pVtx[nCount * 4 + 3].pos = D3DXVECTOR3(CHIP_BIG, 0.0f, -CHIP_BIG);
		//法線の設定
		pVtx[nCount * 4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCount * 4 + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCount * 4 + 2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCount * 4 + 3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCount * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fCol);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[nCount * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fCol);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[nCount * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fCol);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
		pVtx[nCount * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fCol);  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
																	   //テクスチャ座標
		pVtx[nCount * 4 + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCount * 4 + 1].tex = D3DXVECTOR2((CHIP_BIG / CHIP_UV), 0.0f);
		pVtx[nCount * 4 + 2].tex = D3DXVECTOR2(0.0f, 0.5f + (CHIP_BIG / CHIP_UV));
		pVtx[nCount * 4 + 3].tex = D3DXVECTOR2((CHIP_BIG / CHIP_UV), 0.5f + (CHIP_BIG / CHIP_UV));
	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	if (m_pBG == NULL) { SceneCreate(m_pBG, DBG_PRIORYITY); }

	//エフェクトの初期化
	for (int nCount = 0; nCount < MAP_MAX_EFFECT; nCount++)
	{
		if (m_pFrontBG[nCount] == NULL)
		{//背景エフェクト
			if(Create(m_pFrontBG[nCount]))
			{
				switch (nCount)
				{
				case 0://内側
					m_pFrontBG[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2 * 1.1f, SCREEN_HEIGHT / 2 * 1.1f, D3DX_PI, 5, 2, 5, 4, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), C2D::TEX_Darkness);
					m_pFrontBG[nCount]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
					break;
				case 1://外側
					m_pFrontBG[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2 * 1.25f, SCREEN_HEIGHT / 2 * 1.25f, D3DX_PI, 0, 2, 5, 6, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f), C2D::TEX_Darkness);
					m_pFrontBG[nCount]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
					break;
				case 2://外側
					m_pFrontBG[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2 * 1.0f, SCREEN_HEIGHT / 2 * 1.0f, D3DX_PI, 0, 2, 10, 6, CSceneAnim3D::ANIMATION_LOOP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), C2D::TEX_Blood000);
					m_pFrontBG[nCount]->BindDrawType(CScene::DRAW_TYPE_ADD);
					break;

				}
			}
		}
	}
	if (m_pTimer == NULL)
	{//タイマー
		Create(m_pTimer); if (m_pTimer != NULL)
		{
			m_pTimer->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 35.0f, 0.0f), 15.0f, 30.0f, 0, 3, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_TIMER);
		}
	}
	return S_OK;
}
//==================================================================================================//
//    * 生成関数 *
//==================================================================================================//
void CDungeon::Uninit(void)
{
	CDungeon::UnLoad();	//画像の解放
	for (int nCount = 0; nCount < MAP_MAX_EFFECT; nCount++)
	{//背景の削除
		if (m_pFrontBG[nCount] != NULL) { m_pFrontBG[nCount]->Uninit(); m_pFrontBG[nCount] = NULL; }
	}
	if (m_pTimer != NULL) { m_pTimer->Uninit(); m_pTimer = NULL; }
	if (m_pBG != NULL) { m_pBG->Uninit(); m_pBG = NULL; }
	if (m_p3DBG != NULL) { m_p3DBG->Uninit(); m_p3DBG = NULL; }

	// 頂点バッファの開放;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	if (m_nMapChip != NULL)
	{//既にメモリが使われているなら
		for (int nCount = 0; nCount < m_nMemory; nCount++)
		{//一つ一つのintを削除
			delete m_nMapChip[nCount];
		}//本体削除
		delete[] m_nMapChip; m_nMapChip = NULL;
	}

	CManager::GetDungeon() = NULL;
	Release();
}
//==================================================================================================//
//    * 更新関数 *
//==================================================================================================//
void CDungeon::Update(void)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	{//池1、2　合計2つ  //テクスチャ座標
		for(int nPlus = 0;nPlus < 4;nPlus++)	{ pVtx[0 * 4 + nPlus].tex += D3DXVECTOR2(0.0f, 0.004f);}
		for (int nPlus = 0; nPlus < 4; nPlus++) { pVtx[1 * 4 + nPlus].tex += D3DXVECTOR2(0.004f, 0.004f); }
	}
	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//エフェクトの更新
	for (int nCount = 0; nCount < MAP_MAX_EFFECT; nCount++)
	{//闇
		if (m_pFrontBG[nCount] != NULL) { m_pFrontBG[nCount]->Update(); }
	}
	if (m_p3DBG != NULL)
	{//ボス背景
		if (m_p3DBG->GetState()[0] == C3D::STATE_NORMAL) { m_p3DBG->Uninit(); m_p3DBG = NULL; return; }
		m_p3DBG->Update();
	}
	if (m_nQuake > 0) 
	{ 
		m_nQuake--;
		//if (m_nQuake == 0) { CManager::GetSound()->Stop(CSound::LABEL_QUAKE); }
	}
	if (m_pTimer != NULL)
	{ 
		m_pTimer->Update();
		if (m_pTimer->GetnNumber() == 0)
		{//時間切れ
			switch (CManager::GetMode()[0])
			{//現在のモードで分岐
			case CManager::MODE_GAME://ゲームなら　ゲームオーバー
				if (CManager::GetGame()->GetState() == CGame::STATE_NONE)
				{//クリア状態でないなら
					CScene2D	*pScene2D;
					if (SceneCreate(pScene2D, S2D_PRIORITY))
					{//2Dポリゴンを生成
						pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, D3DX_PI, 0, 1, 1, 0.01f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_TimeUp);
					}
					CManager::GetGame()->SetState(CGame::STATE_OVER);
				}
				break;
			case CManager::MODE_VERSUS:
				if (CManager::GetVersus()->GetState() == CVersus::STATE_NONE)
				{//クリア状態でないなら
					CScene2D	*pScene2D;
					if (SceneCreate(pScene2D, S2D_PRIORITY))
					{//2Dポリゴンを生成
						pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, D3DX_PI, 0, 1, 1, 0.01f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_TimeUp);
					}
					CManager::GetVersus()->SetState(CVersus::STATE_DRAW);
				}
				break;
			}
		}
		else if (m_pTimer->GetnNumber() < 60 * 30)
		{
			int nSpeed = 60;
			if		(m_pTimer->GetnNumber() < 60 * 5) { nSpeed = 5; }
			else if	(m_pTimer->GetnNumber() < 60 * 10) { nSpeed = 15; }
			else if (m_pTimer->GetnNumber() < 60 * 20) { nSpeed = 30; }

			if ((m_pTimer->GetnNumber() / nSpeed) % 2 == 0) { m_pTimer->SetColor(D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f)); }
			else											{ m_pTimer->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
		}
	}
}
//==================================================================================================//
//    * 描画関数 *
//==================================================================================================//
void CDungeon::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	//場外の描画
	int nVtx = 2;
	CScene::DRAW_TYPE DrawType = CScene::DRAW_TYPE_NORMAL;
	TEXTURE Texture = m_WallTex;
	D3DXVECTOR3		posQuake = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (m_nQuake > 0 && !CScene::GetbPause()) { posQuake = D3DXVECTOR3((rand() % 201 - 100) * (m_nQuake * 0.001f), 0.0f, (rand() % 201 - 100) * (m_nQuake * 0.001f)); }

	D3DXVECTOR3		pos = D3DXVECTOR3(-CHIP_BIG - CHIP_UV, 75.9f, ((m_nMemory / m_nMaxX) / 2) * -CHIP_SIZE) + posQuake;
	DrawChip(nVtx, DrawType, Texture, pos);//左面
	pos = D3DXVECTOR3(CHIP_BIG + CHIP_UV + (CHIP_SIZE * (m_nMaxX - 1)), 75.9f, ((m_nMemory / m_nMaxX) / 2) * -CHIP_SIZE) + posQuake;
	DrawChip(nVtx, DrawType, Texture, pos);//右面
	pos = D3DXVECTOR3((m_nMaxX / 2) * CHIP_SIZE, 75.9f, CHIP_BIG + CHIP_UV - 0.0f) + posQuake;
	DrawChip(nVtx, DrawType, Texture, pos);//上面
	pos = D3DXVECTOR3((m_nMaxX / 2) * CHIP_SIZE, 75.9f, -CHIP_BIG - CHIP_UV - (CHIP_SIZE * ((m_nMemory / m_nMaxX) - 1))) + posQuake;
	DrawChip(nVtx, DrawType, Texture, pos);//下面


	int nPosX = (int)(CCamera::camera.m_posV.x / CHIP_SIZE);
	int nPosZ = (int)((CCamera::camera.m_posV.z / CHIP_SIZE) * -1);

	//表示
	for (int nCountZ = 0; nCountZ < m_nMemory / m_nMaxX; nCountZ++)
	{//Z軸回転
		for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{//X軸回転
			if (nPosX > nCountX - DRAW_NumChipX && nPosX < nCountX + DRAW_NumChipX &&
				nPosZ > nCountZ - DRAW_NumChipZ && nPosZ < nCountZ + DRAW_NumChipZ)
			{//カメラの近くなら
				if (m_nMapChip[nCountX + (nCountZ * m_nMaxX)][0] != 5)
				{//川以外なら
					ChipPrepare(nCountX + (nCountZ * m_nMaxX), posQuake);
				}
			}
		}
	}//描画

	//川の描画
	nVtx = 0;
	 Texture = TEX_RIVER_1;
	 pos = D3DXVECTOR3((m_nMaxX / 2) * CHIP_SIZE, 0.0f, ((m_nMemory / m_nMaxX) / 2) * -CHIP_SIZE);
	 DrawChip(nVtx, DrawType, Texture, pos);//最下層

	nVtx = 1;
	Texture = TEX_RIVER_0;
	pos.y = 14.5f;
	DrawChip(nVtx, DrawType, Texture, pos);//上部

	DrawType = CScene::DRAW_TYPE_ADD;
	pos.y = 15.0f;
	DrawChip(nVtx, DrawType, Texture, pos);//上部加算

	if (m_p3DBG != NULL)
	{//ボスBG
		m_p3DBG->Draw();
	}
}
//==================================================================================================//
//    * チップ描画準備関数 *
//==================================================================================================//
void CDungeon::ChipPrepare(int nChip, D3DXVECTOR3 &pos0)
{
	MODEL model;
	CScene::DRAW_TYPE DrawType;
	TEXTURE Texture;
	D3DXVECTOR3		pos = D3DXVECTOR3((nChip % m_nMaxX) * CHIP_SIZE, 0.0f, (nChip / m_nMaxX) * -CHIP_SIZE) + pos0;

	switch (m_nMapChip[nChip][0])
	{//チップごと分岐
	case 0://壁
		model = MODEL_WALL;
		DrawType = DRAW_TYPE_NORMAL;
		Texture = m_WallTex;
		//pos.y = -30.0f;
		DrawChipModel(model, DrawType, Texture, pos);
		break;
	case 1://道
	case 98:
	case 99:
		model = MODEL_FIELD;
		DrawType = CScene::DRAW_TYPE_NORMAL;
		Texture = TEX_FIELD_0;
		DrawChipModel(model, DrawType, Texture, pos);
		break;
	case 6://オブジェ
	case 7:
	case 97:
		model = MODEL_FIELD;
		DrawType = CScene::DRAW_TYPE_NORMAL;
		Texture = TEX_FIELD_1;
		DrawChipModel(model, DrawType, Texture, pos);
		break;
	}


}
//==================================================================================================//
//    * チップ描画関数 *
//==================================================================================================//
void CDungeon::DrawChip(int& nVtx, CScene::DRAW_TYPE& DrawType, TEXTURE& Texture, D3DXVECTOR3& pos)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX			mtxWorld;	//ワールドマトリックス
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	if (Texture != TEXTURE_MAX)
	{//テクスチャの設定
		pD3DDevice->SetTexture(0, m_pTexture[Texture]);
	}//テクスチャ削除

	 // ポリゴンの描画
	//CScene::DrawPrepare(CScene::DRAW_TYPE_NORMAL, pD3DDevice);
	//pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * 4, 2);
	CScene::DrawPrepare(DrawType, pD3DDevice);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nVtx * 4, 2);
	pD3DDevice->SetTexture(0, NULL);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * チップモデル描画関数 *
//==================================================================================================//
void CDungeon::DrawChipModel(MODEL& model, CScene::DRAW_TYPE& DrawType, TEXTURE& Texture, D3DXVECTOR3& pos)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;		//計算用マトリックス
	D3DMATERIAL9		matDef;					//現在のマテリアル保存用
	D3DXMATERIAL		*pMat;					//マテリアルデータへのポインタ
	D3DXMATRIX			mtxWorld;	//ワールドマトリックス

	CScene::DrawPrepare(DrawType, pD3DDevice);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 現在のマテリアルを取得
	pD3DDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_Model_Draw[model]->pBuffMatModel->GetBufferPointer();
	//テクスチャの設定
	pD3DDevice->SetTexture(0, m_pTexture[Texture]);

	// マテリアルデータへのポインタを取得
	for (int nCountData = 0; nCountData < (int)m_Model_Draw[model]->nNumMatModel; nCountData++)
	{
		// マテリアルの設定
		pMat = (D3DXMATERIAL*)m_Model_Draw[model]->pBuffMatModel->GetBufferPointer();
		//pMat[nCountData].MatD3D.Diffuse.a = fCola; //透明度設定
		pD3DDevice->SetMaterial(&pMat[nCountData].MatD3D);
		// モデル(パーツ)の描画
		m_Model_Draw[model]->MeshModel->DrawSubset(nCountData);
	}

	// マテリアルをデフォルトに戻す
	pD3DDevice->SetMaterial(&matDef);
	pD3DDevice->SetTexture(0, NULL);
}
//==================================================================================================//
//    * 対戦用ステージセット関数 *
//==================================================================================================//
void CDungeon::SetVersus(int nSelect)
{
	SetColBG(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//暗闇を晴らす

	m_nMaxX = (int)(BOSSMAP_SIZEX);				//マップサイズX
	int		nMaxSizeZ = (int)(BOSSMAP_SIZEZ);	//マップサイズZ

	InitDungeon(m_nMaxX * nMaxSizeZ);
	m_WallTex = TEX_WALL_0; Load(TEX_WALL_0);

	for (int nMapZ = 1; nMapZ < nMaxSizeZ - 2; nMapZ++)
	{
		for (int nMapX = 1; nMapX < m_nMaxX - 2; nMapX++)
		{
			m_nMapChip[nMapX + (nMapZ * m_nMaxX)][0] = 1;			//道に変える
		}
	}

	switch (nSelect)
	{//ステージ生成
	case 0:		SetVersus0();	break;
	case 1:		SetVersus1();	break;
	case 2:		SetVersus2();	break;
	}

	CCamera::camera.m_posR = DUNGEON_CENTER;
	CCamera::camera.m_posV = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, CAMERA_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - 0.01f);
	m_nShop = 1;	//カメラ固定

	if (m_pTimer != NULL) 
	{ 
		m_pTimer->SetNumber(VERSUS_TIME);
		m_pTimer->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
//==================================================================================================//
//    * ダンジョンセット関数 *
//==================================================================================================//
void CDungeon::SetDungeon(int nStage)
{
	//階層が変わった！
	CScenePlayer *pPlayer = CManager::GetPlayer(0);
	for (int nCount = 0; nCount < pPlayer->GetnNumPlayer(); nCount++)
	{//プレイヤー分回る
		//HP回復 or バリア復活
		pPlayer = CManager::GetPlayer(nCount);
		if (pPlayer != NULL)
		{
			pPlayer->Heel(0.5f, false);
			pPlayer->Heal();
		}
	}
	if (m_pTimer != NULL) 
	{ 
		m_pTimer->SetNumber(DUNGEON_TIME);
		m_pTimer->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_BGM == CSound::LABEL_MAX)
	{
		//m_BGM = (CSound::LABEL)((int)CSound::LABEL_FIELD000 + (rand() % (CSound::LABEL_FIELD003 - CSound::LABEL_FIELD000 + 1)));
		CManager::GetSound()->Play(m_BGM);
	}

	//SetDungeon_Boss(nStage);
	//SetDungeon_Shop(1);

	if (nStage == BOSS_STAGE) { SetDungeon_Boss(nStage); }
	else { SetDungeon_Rand(nStage); }
}
//==================================================================================================//
//    * ダンジョンの初期化 *
//==================================================================================================//
void CDungeon::InitDungeon(int nMemory)
{
	if (m_nMapChip != NULL)
	{//既にメモリが使われているなら
		for (int nCount = 0; nCount < m_nMemory; nCount++)
		{//一つ一つのintを削除
			delete m_nMapChip[nCount];
		}//本体削除
		delete[] m_nMapChip;
		m_nMapChip = NULL;

		BreakObject(CSceneObjct::OBJTYPE_BOSS);
		BreakObject(CSceneObjct::OBJTYPE_ENEMY);
		BreakObject(CSceneObjct::OBJTYPE_BULLET);
		BreakObject(CSceneObjct::OBJTYPE_BULLET2);
		BreakObject(CSceneObjct::OBJTYPE_OBJ);
		BreakObject(CSceneObjct::OBJTYPE_OBJ_NO);
		BreakObject(CSceneObjct::OBJTYPE_NONE);
		BreakObject(CSceneObjct::OBJTYPE_NUMBER);
		BreakObject(CSceneObjct::OBJTYPE_SALE);
		BreakObject(CSceneObjct::OBJTYPE_ANIM3D); 
	}
	m_nMemory = nMemory;
	m_nMapChip = new int*[m_nMemory];
	for (int nCount = 0; nCount < m_nMemory; nCount++)
	{
		m_nMapChip[nCount] = new int;
		m_nMapChip[nCount][0] = 0;
	}

	if (m_p3DBG != NULL) { m_p3DBG->Uninit(); m_p3DBG = NULL; }

	//ステージ数による壁画像の変更
	if (CScenePlayer::GetnStage() < TEX_STAGE0) { m_WallTex = TEX_WALL_0; Load(TEX_WALL_0); }
	else if (CScenePlayer::GetnStage() < TEX_STAGE1) { m_WallTex = TEX_WALL_1; Load(TEX_WALL_1); }
	else { m_WallTex = TEX_WALL_2; Load(TEX_WALL_2); }
}
//==================================================================================================//
//    * 練習用マップ作成 *
//==================================================================================================//
void CDungeon::SetPractice(void)
{
	SetColBG(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//暗闇を晴らす

	m_nMaxX = (int)(BOSSMAP_SIZEX);				//マップサイズX
	int		nMaxSizeZ = (int)(BOSSMAP_SIZEZ);	//マップサイズZ
	int nCount;
	CSceneObjct *pSceneModel;

	InitDungeon(m_nMaxX * nMaxSizeZ);

	for (int nMapZ = 1; nMapZ < nMaxSizeZ - 2; nMapZ++)
	{
		for (int nMapX = 1; nMapX < m_nMaxX - 2; nMapX++)
		{
			m_nMapChip[nMapX + (nMapZ * m_nMaxX)][0] = 1;			//道に変える
		}
	}

	m_nMapChip[2 + (1 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[2 + ((nMaxSizeZ - 3) * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[1 + (1 * m_nMaxX)][0] = 6;			//池に変える
	m_nMapChip[1 + ((nMaxSizeZ - 3) * m_nMaxX)][0] = 6;			//池に変える

	m_nMapChip[(m_nMaxX - 5) + (3 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[(m_nMaxX - 4) + (3 * m_nMaxX)][0] = 0;			//壁に変える
	m_nMapChip[(m_nMaxX - 4) + (4 * m_nMaxX)][0] = 0;			//壁に変える

	nCount = 1 + (1 * m_nMaxX);
	if (SceneCreate(pSceneModel, MODEL_PRIORITY))
	{
		pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), PLAYER_Y, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_BOX_2, CSceneModel::TEX_BOX_12, CScene::DRAW_TYPE_NORMAL, true, CSceneObjct::USE_DROP12);
	}
	if (SceneCreate(pSceneModel, MODEL_PRIORITY))
	{
		nCount = 1 + ((nMaxSizeZ - 3) * m_nMaxX);
		pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), PLAYER_Y, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_BOX_2, CSceneModel::TEX_BOX_01, CScene::DRAW_TYPE_NORMAL, true, CSceneObjct::USE_DROP01);
	}
	SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE + CHIP_SIZE * 1.75f), (rand() % 2) * 5 + 10);

	CScenePlayer *pScenePlayer;
	pScenePlayer = CManager::GetPlayer(0);
	if (pScenePlayer != NULL)
	{
		pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, PLAYER_Y, ((BOSSMAP_SIZEZ / 5) * 3.5f) * -CHIP_SIZE + (CHIP_SIZE / 2));
		pScenePlayer->GetPositionOld()[0] = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, PLAYER_Y, ((BOSSMAP_SIZEZ / 5) * 3.5f) * -CHIP_SIZE + (CHIP_SIZE / 2));
		pScenePlayer->GetScore()->AddNumber(999999);
	}

	CCamera::camera.m_posR = DUNGEON_CENTER;
	CCamera::camera.m_posV = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, CAMERA_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - 0.01f);

}
//==================================================================================================//
//    * 対戦用マップ 0番 作成 *
//==================================================================================================//
void CDungeon::SetVersus0(void)
{
	m_nMapChip[5 + (1 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[6 + (1 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[5 + (5 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[6 + (5 * m_nMaxX)][0] = 5;			//池に変える

	//m_nMapChip[1 + (1 * m_nMaxX)][0] = 6;			//池に変える
	//m_nMapChip[1 + ((nMaxSizeZ - 3) * m_nMaxX)][0] = 6;			//池に変える

	//m_nMapChip[(m_nMaxX - 5) + (3 * m_nMaxX)][0] = 5;			//池に変える

	m_nMapChip[3 + (3 * m_nMaxX)][0] = 0;			//壁に変える
	m_nMapChip[8 + (3 * m_nMaxX)][0] = 0;			//壁に変える

	m_nMapChip[1 + (1 * m_nMaxX)][0] = 0;			//壁に変える
	m_nMapChip[1 + (5 * m_nMaxX)][0] = 0;			//壁に変える
	m_nMapChip[10 + (1 * m_nMaxX)][0] = 0;			//壁に変える
	m_nMapChip[10 + (5 * m_nMaxX)][0] = 0;			//壁に変える
	//m_nMapChip[(m_nMaxX - 4) + (4 * m_nMaxX)][0] = 0;			//壁に変える


	CScenePlayer *pScenePlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		pScenePlayer = CManager::GetPlayer(nCount);
		if (pScenePlayer != NULL)
		{
			switch (nCount)
			{
			case 0:
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX) * CHIP_SIZE - CHIP_SIZE - CHIP_SIZE * 10, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
				pScenePlayer->GetPositionOld()[0] = pScenePlayer->GetPosition()[0];
				pScenePlayer->GetRotation()[0].y = -D3DX_PI * 0.5f;
				pScenePlayer->GetRotationU()[0].y = -D3DX_PI * 0.5f;
				break;
			case 1:
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX)* CHIP_SIZE - CHIP_SIZE - CHIP_SIZE * 3, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
				pScenePlayer->GetPositionOld()[0] = pScenePlayer->GetPosition()[0];
				pScenePlayer->GetRotation()[0].y = D3DX_PI * 0.5f;
				pScenePlayer->GetRotationU()[0].y = D3DX_PI * 0.5f;
				break;
			}
			pScenePlayer->EffectUpdate();
			pScenePlayer->PEffectUpdate();
		}
	}
}
//==================================================================================================//
//    * 対戦用マップ 1番 作成 *
//==================================================================================================//
void CDungeon::SetVersus1(void)
{
	m_nMapChip[4 + (2 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[5 + (2 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[6 + (2 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[7 + (2 * m_nMaxX)][0] = 5;			//池に変える

	m_nMapChip[4 + (3 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[7 + (3 * m_nMaxX)][0] = 5;			//池に変える

	m_nMapChip[4 + (4 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[5 + (4 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[6 + (4 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[7 + (4 * m_nMaxX)][0] = 5;			//池に変える

	m_nMapChip[1 + (1 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[1 + (5 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[10 + (1 * m_nMaxX)][0] = 5;			//池に変える
	m_nMapChip[10 + (5 * m_nMaxX)][0] = 5;			//池に変える

	m_nMapChip[5 + (3 * m_nMaxX)][0] = 0;			//壁に変える
	m_nMapChip[6 + (3 * m_nMaxX)][0] = 0;			//壁に変える

	CScenePlayer *pScenePlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		pScenePlayer = CManager::GetPlayer(nCount);
		if (pScenePlayer != NULL)
		{
			switch (nCount)
			{
			case 0:
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX) * CHIP_SIZE - CHIP_SIZE - CHIP_SIZE * 10, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
				pScenePlayer->GetPositionOld()[0] = pScenePlayer->GetPosition()[0];
				pScenePlayer->GetRotation()[0].y = D3DX_PI * 0.5f;
				pScenePlayer->GetRotationU()[0].y = D3DX_PI * 0.5f;
				break;
			case 1:
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX)* CHIP_SIZE - CHIP_SIZE - CHIP_SIZE * 3, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
				pScenePlayer->GetPositionOld()[0] = pScenePlayer->GetPosition()[0];
				pScenePlayer->GetRotation()[0].y = -D3DX_PI * 0.5f;
				pScenePlayer->GetRotationU()[0].y = -D3DX_PI * 0.5f;
				break;
			}
			pScenePlayer->EffectUpdate();
			pScenePlayer->PEffectUpdate();
		}
	}
}
//==================================================================================================//
//    * 対戦用マップ 2番 作成 *
//==================================================================================================//
void CDungeon::SetVersus2(void)
{
	for (int nCount = 1; nCount < 6; nCount++)
	{
		m_nMapChip[5 + (nCount * m_nMaxX)][0] = 5;			//池に変える
		m_nMapChip[6 + (nCount * m_nMaxX)][0] = 5;			//池に変える
		m_nMapChip[1 + (nCount * m_nMaxX)][0] = 0;			//池に変える
		m_nMapChip[2 + (nCount * m_nMaxX)][0] = 0;			//池に変える
		m_nMapChip[9 + (nCount * m_nMaxX)][0] = 0;			//池に変える
		m_nMapChip[10 + (nCount * m_nMaxX)][0] = 0;			//池に変える
	}

	CScenePlayer *pScenePlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		pScenePlayer = CManager::GetPlayer(nCount);
		if (pScenePlayer != NULL)
		{
			switch (nCount)
			{
			case 0:
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX)* CHIP_SIZE - CHIP_SIZE - CHIP_SIZE * 9, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
				pScenePlayer->GetPositionOld()[0] = pScenePlayer->GetPosition()[0];
				pScenePlayer->GetRotation()[0].y = D3DX_PI * 0.5f;
				pScenePlayer->GetRotationU()[0].y = D3DX_PI * 0.5f;
				break;
			case 1:
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX)* CHIP_SIZE - CHIP_SIZE - CHIP_SIZE * 4, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
				pScenePlayer->GetPositionOld()[0] = pScenePlayer->GetPosition()[0];
				pScenePlayer->GetRotation()[0].y = -D3DX_PI * 0.5f;
				pScenePlayer->GetRotationU()[0].y = -D3DX_PI * 0.5f;
				break;
			}
			pScenePlayer->EffectUpdate();
			pScenePlayer->PEffectUpdate();
		}
	}
}
//==================================================================================================//
//    * ショップ作成 *
//==================================================================================================//
void CDungeon::SetDungeon_Shop(int nStatge)
{
	if (m_nShop == 0)
	{
		CScenePlayer *pPlayer = CManager::GetPlayer(0);
		for (int nCount = 0; nCount < pPlayer->GetnNumPlayer(); nCount++)
		{//プレイヤー分回る
		 //HP回復 or バリア復活
			pPlayer = CManager::GetPlayer(nCount);
			if (pPlayer != NULL)
			{
				pPlayer->Heal();
			}
		}

		SetColBG(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//暗闇を晴らす

		m_nMaxX = (int)(BOSSMAP_SIZEX);				//マップサイズX
		int		nMaxSizeZ = (int)(BOSSMAP_SIZEZ);	//マップサイズZ
		CSceneAnim3D *pSceneAnim3D;
		CScene3D		*pScene3D;
		CSceneManager	*pManager;	//店長のポインタ

		InitDungeon(m_nMaxX * nMaxSizeZ);

		for (int nMapZ = 1; nMapZ < nMaxSizeZ - 2; nMapZ++)
		{
			for (int nMapX = 1; nMapX < m_nMaxX - 2; nMapX++)
			{
				m_nMapChip[nMapX + (nMapZ * m_nMaxX)][0] = 1;			//道に変える
			}
		}

		CScenePlayer *pScenePlayer;
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{//プレイヤーの移動
			pScenePlayer = CManager::GetPlayer(nCount);
			if (pScenePlayer != NULL)
			{
				pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE + (CHIP_SIZE / 4), PLAYER_Y, ((BOSSMAP_SIZEZ / 5) * 3.5f) * -CHIP_SIZE + (CHIP_SIZE / 2)) + D3DXVECTOR3((CHIP_SIZE / 2) * -nCount, 0.0f, 0.0f);
				pScenePlayer->GetPositionOld()[0] = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE + (CHIP_SIZE / 4), PLAYER_Y, ((BOSSMAP_SIZEZ / 5) * 3.5f) * -CHIP_SIZE + (CHIP_SIZE / 2)) + D3DXVECTOR3((CHIP_SIZE / 2) * -nCount, 0.0f, 0.0f);
			}
		}

		CCamera::camera.m_posR = DUNGEON_CENTER;
		CCamera::camera.m_posV = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, CAMERA_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - 0.01f);

		if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
		{//出口
			pSceneAnim3D->Set(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, 20.1f, ((BOSSMAP_SIZEZ / 5) * 4) * -CHIP_SIZE + CHIP_SIZE),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CHIP_SIZE * 0.3f, CHIP_SIZE * 0.3f, CSceneAnim3D::TEX_GOAL, CScene::DRAW_TYPE_ADD, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_SHOP);
		}
		
		if (SceneCreate(pScene3D, DUNGEON_PRIORYITY + 1))
		{//マットの配置
			pScene3D->Set(DUNGEON_CENTER,
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CHIP_SIZE * 3.0f, CHIP_SIZE * 1.5f, CScene3D::TEX_MATTE, 0, 1, 1, CScene::DRAW_TYPE_NORMAL);
			pScene3D->SetUVPattern(10.0f, 10.0f);
		}
		
		if (SceneCreate(pManager, SBOSS_PRIORITY))
		{//店長の配置
			pManager->Set(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE + CHIP_SIZE * 0.75f));
		}

		//商品配置 上
		SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE + CHIP_SIZE * 1.25f, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE + CHIP_SIZE * 0.75f), (rand() % 2) * 5 + 10);
		SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE * 3.25f, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE + CHIP_SIZE * 0.75f), (rand() % 2) * 5 + 10);

		//商品配置 下
		SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE * 3.25f, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - CHIP_SIZE * 0.75f), (rand() % 3) * 5);
		SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE * 1.75f, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - CHIP_SIZE * 0.75f), (rand() % 3) * 5);
		SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE * 0.25f, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - CHIP_SIZE * 0.75f), (rand() % 3) * 5);
		SetShop_Item(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE + CHIP_SIZE * 1.25f, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - CHIP_SIZE * 0.75f), (rand() % 3) * 5);

		m_nShop = 1;
		CSound *pSound = CManager::GetSound();
		pSound->Stop(m_BGM);
		//pSound->Play(CSound::LABEL_SHOP000);

		//ショップの時間
		if (m_pTimer != NULL) 
		{ 
			m_pTimer->SetNumber(SHOP_TIME); 
			m_pTimer->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
	else 
	{ 
		CSound *pSound = CManager::GetSound();
		//pSound->Stop(CSound::LABEL_SHOP000);
		//m_BGM = (CSound::LABEL)((int)CSound::LABEL_FIELD000 + (rand() % (CSound::LABEL_FIELD003 - CSound::LABEL_FIELD000 + 1)));
		pSound->Play(m_BGM);

		CScenePlayer::GetnStage()++; m_nShop = 2; 
		SetDungeon(nStatge + 1);
	}
}
//==================================================================================================//
//    * ボスステージ作成 *
//==================================================================================================//
void CDungeon::SetDungeon_Boss(int nStatge)
{
	SetColBG(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	//暗闇を晴らす

	m_nMaxX = (int)(BOSSMAP_SIZEX);				//マップサイズX
	int		nMaxSizeZ = (int)(BOSSMAP_SIZEZ);	//マップサイズZ

	InitDungeon(m_nMaxX * nMaxSizeZ);

	if (m_nMapChip != NULL)
	{
		for (int nMapZ = 1; nMapZ < nMaxSizeZ - 2; nMapZ++)
		{
			for (int nMapX = 1; nMapX < m_nMaxX - 2; nMapX++)
			{
				m_nMapChip[nMapX + (nMapZ * m_nMaxX)][0] = 1;			//道に変える
			}
		}
	}

	CSceneBoss01	*pBoss;	//ボスのポインタ
	if (SceneCreate(pBoss, SBOSS_PRIORITY))
	{//ボスの配置
		pBoss->Set(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, PLAYER_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE + CHIP_SIZE * 0.75f));
	}
	CManager::GetSound()->Stop(m_BGM);
	m_BGM = CSound::LABEL_MAX;

	CScenePlayer *pScenePlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{//プレイヤーの移動
		pScenePlayer = CManager::GetPlayer(nCount);
		if (pScenePlayer != NULL)
		{
			pScenePlayer->GetPosition()[0] = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - (CHIP_SIZE / 2), PLAYER_Y, ((BOSSMAP_SIZEZ / 5) * 3.5f) * -CHIP_SIZE + (CHIP_SIZE / 2)) + D3DXVECTOR3((CHIP_SIZE / 2) * -nCount, 0.0f, 0.0f);
			pScenePlayer->GetPositionOld()[0] = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - (CHIP_SIZE / 2), PLAYER_Y, ((BOSSMAP_SIZEZ / 5) * 3.5f) * -CHIP_SIZE + (CHIP_SIZE / 2)) + D3DXVECTOR3((CHIP_SIZE / 2) * -nCount, 0.0f, 0.0f);
		}
	}
	CCamera::camera.m_posR = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, 20.1f, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE);
	CCamera::camera.m_posV = D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, CAMERA_Y, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE - 0.01f);
}
//==================================================================================================//
//    * ランダムダンジョン作成 *
//==================================================================================================//
void CDungeon::SetDungeon_Rand(int nStatge)
{
	SetColBG(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//暗闇の出現
	//printf("\n ( ◎:スタート / △:ゴール / ■:道 / ◆:宝箱 / ●:街 / 〇:池 )\n");
	//ランダム使用可能に
	srand((unsigned int)time(0));

	m_nMaxX = (int)(((rand() % 3) * 0.25f + 1) * MAP_SIZE);//マップサイズX
	int		nMaxSizeZ = (int)(((rand() % 3) * 0.25f + 1) * MAP_SIZE);	//マップサイズZ
	int		nDig = (int)((m_nMaxX * nMaxSizeZ) * 0.15);	//掘る回数
	float fItem = 0.5f;

	int		nMaxDig = nDig;	//掘る回数
	int		nPosX = (m_nMaxX / 2);
	int		nPosZ = (nMaxSizeZ / 2);
	int		nPosOldX;
	int		nPosOldZ;
	int		nSCheck;	//スタート地点
	int		nGCheck;	//ゴール地点

	int nBaseX = nPosX, nBaseZ = nPosZ;

	//int		nDigPtn = 0;			//掘り方
	int		nCntExpand = rand() % nMaxDig / (rand() % 3 + 1);				//次の入れ替えまで
	int		nExpand = 0;			//拡大方法
	int		nExpAngle = rand() % 4;			//角度

	int		nCntWallR = 0;			//壁に当たった回数
	int		nRand = 0;
	int		nRand1;
	int		nRand0 = 0;
	int		nRandRoom = 3;
	int		nRandRoom0 = 0;
	int		nCheck;
	int		nCntItem = 0;
	int		nCntEnemy = 0;
	int		nCntTrap = 0;

	bool	bDig;
	int		nState = 0;		//掘る状態
	CSceneObjct *pSceneModel;

	bool bEnd = false;

	InitDungeon(m_nMaxX * nMaxSizeZ);

	m_nMapChip[nPosX + (nPosZ * m_nMaxX)][0] = 1;			//道に変える
	do
	{
		nDig--;
		nPosOldX = nPosX;
		nPosOldZ = nPosZ;
		bDig = false;

		while (1)
		{
			nRand0--;
			if (nRand0 < 0)
			{//掘る方向を変える
				nRand0 = rand() % nRandRoom + nRandRoom0;
				nRand1 = nRand;
				while (1)
				{//ランドで方向設定
					nRand = rand() % 4;
					if (nRand % 2 != nRand1 % 2) { break; }
				}
			}
			if (nRand == 0) { nPosX++; }
			else if (nRand == 2) { nPosX--; }
			else if (nRand == 1) { nPosZ++; }
			else { nPosZ--; }
			if (nPosX < 2 || nPosX >= m_nMaxX - 2 || nPosZ < 2 || nPosZ >= nMaxSizeZ - 2)
			{//壁なら
				nCntWallR++;
				nRand0 = 0;
				if (nCntWallR > 3 && nState != 2)
				{//前回の位置へ
					nCntWallR = 0;
					nPosX = nPosOldX;
					nPosZ = nPosOldZ;
				}
				else
				{//初期位置へ
					nPosX = nBaseX;
					nPosZ = nBaseZ;
					//アイテム
					//if(個数に応じて出現率低下)
					if (rand() % ((nCntItem + 1) * 10) < 10)
					{
						nCntItem++;
						SetObject(nPosOldX + (nPosOldZ * m_nMaxX), CSceneModel::MODEL_BOX_1);
					}
				}
			}
			nCheck = nPosX + (nPosZ * m_nMaxX);
			if (m_nMapChip[nCheck][0] == 0 || m_nMapChip[nCheck][0] == 99) { break; }
		}

		if (nCheck > 0)
		{//-でないなら 掘る
			if (m_nMapChip[nCheck][0] == 0)
			{//何もない場所なら追加で掘る
				SetExpand(nCheck, nExpand, nExpAngle);
			}
			nCntWallR = 0;
			m_nMapChip[nCheck][0] = 1;			//道に変える
			if (nState == 1) { nState = 2; nSCheck = nCheck; }
			if (nState == 4) { nState = 5; nGCheck = nCheck; }

			if ((nMaxDig - nDig) % 200 == 0)
			{//200回ごと
				if (nCntItem > 0) { nCntItem--; };
				if (nCntEnemy > 0) { nCntEnemy--; }
				nBaseX = nPosX; nBaseZ = nPosZ;
			}
		}

		if (nDig > nMaxDig * 0.9 || nDig > nMaxDig - 5) { nState = 0; nRandRoom = rand() % 3 + 2; nRandRoom0 = 1; }
		else if (nState == 0) { nState = 1; nRandRoom = rand() % 3 + 2; nRandRoom0 = 1; }
		else if (nDig > nMaxDig * 0.4f) {}
		else if (nState == 2) { nState = 3; nRandRoom = rand() % 3 + 2; nRandRoom0 = 1; }
		else if (nDig > nMaxDig * 0.05 && nDig > 2) {}
		else if (nState == 3) { nState = 4; nRandRoom = 1; nRandRoom0 = 1; nRand0 = 0; }

		nCntExpand--;
		if (nCntExpand < 0)
		{ //掘り方ランド
		  //nCntExpand = rand() % nMaxDig / (rand() % 3 + 1);
			nCntExpand = 10;
			nExpand = rand() % 1;
			nExpAngle = rand() % 4;
		}

	} while (nDig > 1);

	//フィールドの変換
	ConvertField();

	//スタート地点との差を図りやり直しか定義
	if ((m_nMaxX * 0.2f > (nSCheck % m_nMaxX) - (nGCheck % m_nMaxX) && m_nMaxX * -0.2f < (nSCheck % m_nMaxX) - (nGCheck % m_nMaxX)) ||
		nMaxSizeZ * 0.2f > (nSCheck / m_nMaxX) - (nGCheck / m_nMaxX) && nMaxSizeZ * -0.2f < (nSCheck / m_nMaxX) - (nGCheck / m_nMaxX))
	{
		do
		{//遠くなるまで繰り返し
			for (int nCountZ = 0; nCountZ < nMaxSizeZ; nCountZ++)
			{
				for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
				{
					if (m_nMapChip[nCountX + (nCountZ * m_nMaxX)][0] == 1 ||
						m_nMapChip[nCountX + (nCountZ * m_nMaxX)][0] == 99)
					{//道なら
						if (rand() % nMaxDig == 0)
						{
							if (rand() % 2 == 0) { nSCheck = nCountX + (nCountZ * m_nMaxX); }
							else { nGCheck = nCountX + (nCountZ * m_nMaxX); }
						}
					}
				}
			}
		} while ((m_nMaxX * 0.2f > (nSCheck % m_nMaxX) - (nGCheck % m_nMaxX) && m_nMaxX * -0.2f < (nSCheck % m_nMaxX) - (nGCheck % m_nMaxX)) ||
			nMaxSizeZ * 0.2f > (nSCheck / m_nMaxX) - (nGCheck / m_nMaxX) && nMaxSizeZ * -0.2f < (nSCheck / m_nMaxX) - (nGCheck / m_nMaxX));
	}

	for (int nCount = 0; nCount < m_nMaxX * nMaxSizeZ; nCount++)
	{
		if (nSCheck != nCount && nGCheck != nCount)
		{
			if (m_nMapChip[nCount][0] == 6)
			{//変換可能なブロック オブジェ床
				if (rand() % ((nCntItem + 1) * 50) < 50)
				{ //アイテムに
					nCntItem++;
					if (rand() % 5 == 0) { SetObject(nCount, CSceneModel::MODEL_BOX_1); }
					else { SetObject(nCount, CSceneModel::MODEL_MAX); }
				}//if(rand()) Item変換
				else if (rand() % ((nCntTrap + 1) * 100) < 10)
				{//トラップに
					nCntTrap++;
					SetTrap(nCount, m_nMapChip[nCount][0]);
				}
				else if (rand() % ((nCntEnemy + 1) * 90) < 10)
				{//確率で敵セット
					nCntEnemy++;
					SetEnemy(nCount);
				}
			}//if()
			if (m_nMapChip[nCount][0] == 1 || m_nMapChip[nCount][0] == 99)
			{//確率で敵セット
				if (rand() % ((nCntEnemy + 1) * 100) < 5)
				{
					nCntEnemy++;
					SetEnemy(nCount);
				}
				else if (rand() % ((nCntTrap + 1) * 100) < 10)
				{//トラップに
					nCntTrap++;
					if (m_nMapChip[nCount][0] == 1) {}
					else {}
					SetTrap(nCount, m_nMapChip[nCount][0]);
				}
				else if (rand() % 10 == 0)
				{ //アイテムに
					SetObject(nCount, CSceneModel::MODEL_MAX);
				}//if(rand()) Item変換
			}
			if (nCount % 50 == 0)
			{
				if (nCntEnemy > 0) { nCntEnemy--; }
				if (nCntItem > 0) { nCntItem--; }
				if (nCntTrap > 0) { nCntTrap--; }
			}
		}
	}//for()

	CScenePlayer *pScenePlayer;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{//プレイヤーの移動
		pScenePlayer = CManager::GetPlayer(nCount);
		if (pScenePlayer != NULL)
		{
			pScenePlayer->GetPosition()[0] = D3DXVECTOR3((nSCheck % m_nMaxX) * CHIP_SIZE + (CHIP_SIZE / 4), PLAYER_Y, (nSCheck / m_nMaxX) * -CHIP_SIZE + (CHIP_SIZE / 4)) + D3DXVECTOR3((CHIP_SIZE / 2) * -nCount, 0.0f, (rand() % 2) * (-CHIP_SIZE / 2));
			pScenePlayer->GetPositionOld()[0] = D3DXVECTOR3((nSCheck % m_nMaxX) * CHIP_SIZE + (CHIP_SIZE / 4), PLAYER_Y, (nSCheck / m_nMaxX) * -CHIP_SIZE + (CHIP_SIZE / 4)) + D3DXVECTOR3((CHIP_SIZE / 2) * -nCount, 0.0f, (rand() % 2) * (-CHIP_SIZE / 2));
		}
	}
	CCamera::camera.m_posR = D3DXVECTOR3((nSCheck % m_nMaxX) * CHIP_SIZE, 20.1f, (nSCheck / m_nMaxX) * -CHIP_SIZE);
	CCamera::camera.m_posV = D3DXVECTOR3((nSCheck % m_nMaxX) * CHIP_SIZE, 20.1f, (nSCheck / m_nMaxX) * -CHIP_SIZE - 0.01f);
	CCollision::DestroyRange(D3DXVECTOR3((nSCheck % m_nMaxX) * CHIP_SIZE, 20.1f, (nSCheck / m_nMaxX) * -CHIP_SIZE), CHIP_SIZE * 5, CHIP_SIZE * 5, CScene::OBJTYPE_ENEMY);
	CCollision::DestroyRange(D3DXVECTOR3((nSCheck % m_nMaxX) * CHIP_SIZE, 20.1f, (nSCheck / m_nMaxX) * -CHIP_SIZE), CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_OBJ);

	//SHOP生成
	if (m_nShop == 0 && m_bManager)
	{
		int nShopX, nShopZ, nShop;
		while (1)
		{
			nShopX = (rand() % (m_nMaxX - 4)) + 2;
			nShopZ = (rand() % (nMaxSizeZ - 4)) + 2;
			nShop = nShopX + (nShopZ * m_nMaxX);
			if (m_nMapChip[nShop][0] == 1 || m_nMapChip[nShop][0] == 99)
			{
				if (nShop != nSCheck && nShop != nGCheck)
				{//SHOPの生成
					pSceneModel = NULL;
					if (SceneCreate(pSceneModel, MODEL_PRIORITY))
					{
						CCollision::DestroyRange(D3DXVECTOR3(((nShop % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nShop / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
							CHIP_SIZE * 2, CHIP_SIZE * 2, CScene::OBJTYPE_OBJ);
						CCollision::DestroyRange(D3DXVECTOR3(((nShop % m_nMaxX) * CHIP_SIZE), 20.1f, ((nShop / m_nMaxX) * -CHIP_SIZE)),
							CHIP_SIZE * 2, CHIP_SIZE * 2, CScene::OBJTYPE_ENEMY);
						pSceneModel->Set(D3DXVECTOR3(((nShop % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nShop / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_SHOP, CSceneModel::TEXTURE_MAX, CScene::DRAW_TYPE_NORMAL, true, CSceneObjct::USE_SHOP);
						pSceneModel->BindTexture(&m_pTexture[m_WallTex]);
					}
					break;
				}
			}
		}
	}//ショップ生成
	else { m_nShop = 0; }

	CSceneAnim3D *pSceneAnim3D = NULL;
//GOAL生成
	if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
	{
		pSceneAnim3D->Set(D3DXVECTOR3(((nGCheck % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nGCheck / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CHIP_SIZE * 0.3f, CHIP_SIZE * 0.3f, CSceneAnim3D::TEX_GOAL, CScene::DRAW_TYPE_SUBTRACT, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_GOAL);
	}

	//階層の表記
	CFont		*pFont;
	char		aStr[64];
	if (SceneCreate(pFont, S2D_PRIORITY + 1))
	{//生成できた！
		wsprintf(&aStr[0], "%d 階", CScenePlayer::GetnStage());
		pFont->Set(RECT{ 0, SCREEN_HEIGHT / 2 - 15, 1280, 720 }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), &aStr[0], 0, DT_CENTER, -1, true, CFont::STATE_FADE);
		pFont->GetfCntState() = 0.01f;
	}

	SetQuake(60); //切り替わり表現
}
//==================================================================================================//
//    * ショップ作成時のアイテム *
//==================================================================================================//
void CDungeon::SetShop_Item(D3DXVECTOR3 pos, int nPlus)
{
	CScene3D		*pScene3D;
	C3DNumber		*p3DNumber;
	int				nRand;
	int				nMoney = 123456;
	int				nWKMoney;		//桁数計算用
	int				nDigits;		//桁数

	if (SceneCreate(pScene3D, S3DF_PRIORITY))
	{//アイテム生成
		switch (nPlus)
		{
		case 0:		nRand = (rand() % 5) + nPlus;	break;
		case 5:		nRand = (rand() % 3) + nPlus + 2;	break;
		case 10:	nRand = (rand() % 5) + nPlus;	break;
		case 15:	nRand = (rand() % 5) + nPlus;	break;
		}
		switch (nRand)
		{//値段設定
		case 0:		nMoney = 750; break;
		case 1:		nMoney = 1000; break;
		case 2:		nMoney = 1500; break;
		case 3:		nMoney = 2500; break;
		case 4:		nMoney = 5000; break;
		case 5:		nMoney = 0; break;
		case 6:		nMoney = 0; break;
		case 7:		nMoney = 5000; break;
		case 8:		nMoney = 3000; break;
		case 9:		nMoney = 3000; break;
		case 10:	nMoney = 25000; break;
		case 11:	nMoney = 20000; break;
		case 12:	nMoney = 20000; break;
		case 13:	nMoney = 50000; break;
		case 14:	nMoney = 65000; break;
		case 15:	nMoney = 110000; break;
		case 16:	nMoney = 80000; break;
		case 17:	nMoney = 150000; break;
		case 18:	nMoney = 50000; break;
		case 19:	nMoney = 130000; break;
		}
		pScene3D->Set(pos,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), ITEM_SIZE, ITEM_SIZE, CScene3D::TEX_ITEM, nRand, 5, 4, CScene::DRAW_TYPE_NORMAL);
		pScene3D->GetState()[0] = (CScene3D::STATE)(CScene3D::STATE_S_HEEL0 + nRand);
		pScene3D->GetfCntState()[0] = (float)nMoney;
		pScene3D->SetObjType(OBJTYPE_SALE);
		if (SceneCreate(p3DNumber, S3D_PRIORITY + 3))
		{//値段表示
			nWKMoney = nMoney; nDigits = 0;
			do
			{
				nWKMoney /= 10;
				nDigits++;
			} while (nWKMoney != 0);
			p3DNumber->Set(pos + D3DXVECTOR3(ITEM_SIZE, 0.0f, -ITEM_SIZE - NUMBER_SIZE), NUMBER_SIZE / 2, NUMBER_SIZE, nMoney, nDigits, D3DXCOLOR(1.0f, 0.92f, 0.0f, 1.0f), C3DNumber::STATE_SCORE);
		}
	}
}
//==================================================================================================//
//    * ダンジョン作成時の補助パーツ *
//==================================================================================================//
void CDungeon::SetField(int nCheck)
{
	if (m_nMapChip[nCheck][0] == 0)
	{//右下
		m_nMapChip[nCheck][0] = 99;			//道に変える
	}
}
//==================================================================================================//
//    * ダンジョン作成時の拡大パーツ *
//==================================================================================================//
void CDungeon::SetExpand(int nCheck, int nType, int nAngle)
{
	//十字
	SetField(nCheck + 1);
	SetField(nCheck - 1);
	SetField(nCheck - m_nMaxX);
	SetField(nCheck + m_nMaxX);

	switch (nType)
	{//■塗りつぶし
	case 0://角度に応じた斜め一つ
		if (nAngle % 2 == 0)
		{//左
			if (nAngle < 2) { SetField(nCheck - m_nMaxX - 1); }
			else { SetField(nCheck + m_nMaxX - 1); }
		}
		else
		{//右
			if (nAngle < 2) { SetField(nCheck - m_nMaxX + 1); }
			else { SetField(nCheck + m_nMaxX + 1); }
		}
		break;
	}
}
//==================================================================================================//
//    * ダンジョン作成時の変換パーツ *
//==================================================================================================//
void CDungeon::ConvertField(void)
{
	bool bReturn;
	for (int nCount = 0; nCount < m_nMemory; nCount++)
	{
		if (m_nMapChip[nCount][0] == 99)
		{//変換可能なブロック
		 //種類 / 0:ブロック / 1:道 / 2:アイテム / 3:オブジェ 4:池
			if (rand() % 25 == 0) { m_nMapChip[nCount][0] = 6; }	//オブジェクト
			else if (rand() % 5 == 0) { m_nMapChip[nCount][0] = 5; }	//池
		}
	}

	do
	{
		bReturn = false;
		for (int nCount = 0; nCount < m_nMemory; nCount++)
		{
			if (m_nMapChip[nCount][0] == 5)
			{//変換可能な道　池に
				if (m_nMapChip[nCount + 1][0] == 99 || m_nMapChip[nCount + 1][0] == 6) { m_nMapChip[nCount + 1][0] = 5; bReturn = true; }
				if (m_nMapChip[nCount - 1][0] == 99 || m_nMapChip[nCount - 1][0] == 6) { m_nMapChip[nCount - 1][0] = 5; bReturn = true; }
				if (m_nMapChip[nCount + m_nMaxX][0] == 99 || m_nMapChip[nCount + m_nMaxX][0] == 6) { m_nMapChip[nCount + m_nMaxX][0] = 5; bReturn = true; }
				if (m_nMapChip[nCount - m_nMaxX][0] == 99 || m_nMapChip[nCount - m_nMaxX][0] == 6) { m_nMapChip[nCount - m_nMaxX][0] = 5; bReturn = true; }
			}
		}
	} while (bReturn == true);

	do
	{//オブジェ
		bReturn = false;
		for (int nCount = 0; nCount < m_nMemory; nCount++)
		{
			if (m_nMapChip[nCount][0] == 6)
			{//変換可能な道　オブジェに
				if (rand() % 6 < 3)
				{
					if (m_nMapChip[nCount + 1][0] == 1 || m_nMapChip[nCount + 1][0] == 99) { m_nMapChip[nCount + 1][0] = 6 + (rand() % 2); bReturn = true; }
					if (m_nMapChip[nCount - 1][0] == 1 || m_nMapChip[nCount - 1][0] == 1) { m_nMapChip[nCount - 1][0] = 6 + (rand() % 2); bReturn = true; }
					if (m_nMapChip[nCount + m_nMaxX][0] == 1 || m_nMapChip[nCount + m_nMaxX][0] == 99) { m_nMapChip[nCount + m_nMaxX][0] = 6 + (rand() % 2); bReturn = true; }
					if (m_nMapChip[nCount - m_nMaxX][0] == 1 || m_nMapChip[nCount - m_nMaxX][0] == 99) { m_nMapChip[nCount - m_nMaxX][0] = 6 + (rand() % 2); bReturn = true; }
				}
			}
		}
	} while (bReturn == true);
}
//==================================================================================================//
//    * ダンジョン作成時の変換パーツ *
//==================================================================================================//
void CDungeon::SetObject(int nCount, CSceneModel::MODEL model)
{
	CSceneObjct *pSceneModel;
	if (SceneCreate(pSceneModel, MODEL_PRIORITY))
	{
		CCollision::DestroyRange(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE)),
			CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_OBJ);
		CCollision::DestroyRange(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE)),
			CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_ENEMY);

		if (model == CSceneModel::MODEL_MAX)
		{//モデルランダム
			switch ((rand() % (CSceneModel::MODEL_MAX - CSceneModel::MODEL_BOX_1)) + CSceneModel::MODEL_BOX_1)
			{//モデルランダム
			case CSceneModel::MODEL_BOX_1:	//木箱
				CSceneModel::TEXTURE tex;
				CSceneObjct::USE use;

				if (rand() % 3 == 0) { tex = CSceneModel::TEX_BOX_10; use = CSceneObjct::USE_DROP10; }//苔
				else { tex = CSceneModel::TEX_BOX_00; use = CSceneObjct::USE_DROP00; }//木箱
				pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_BOX_1, tex, CScene::DRAW_TYPE_NORMAL, true, use);
				break;
			case CSceneModel::MODEL_STONE:
				pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_STONE, CSceneModel::TEXTURE_MAX, CScene::DRAW_TYPE_NORMAL, true, CSceneObjct::USE_DROP);
				pSceneModel->BindTexture(&m_pTexture[m_WallTex]);
				break;
			case CSceneModel::MODEL_STEEL:
				pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_STEEL, CSceneModel::TEX_OBJ_00, CScene::DRAW_TYPE_NORMAL, true, CSceneObjct::USE_DROP);
				break;
			case CSceneModel::MODEL_STEELBIOCK:
				pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_STEELBIOCK, CSceneModel::TEX_OBJ_00, CScene::DRAW_TYPE_NORMAL, true, CSceneObjct::USE_DROP);
				break;
			}
		}
		else
		{//宝箱
			CSceneModel::TEXTURE tex;
			CSceneObjct::USE use;

			if (rand() % 3 == 0)
			{//金
				if (rand() % 3 == 0) { tex = CSceneModel::TEX_BOX_12; use = CSceneObjct::USE_DROP12; }//苔
				else { tex = CSceneModel::TEX_BOX_02; use = CSceneObjct::USE_DROP02; }//金
			}
			else
			{//銀
				if (rand() % 3 == 0) { tex = CSceneModel::TEX_BOX_11; use = CSceneObjct::USE_DROP11; }//苔
				else { tex = CSceneModel::TEX_BOX_01; use = CSceneObjct::USE_DROP01; }//銀
			}//モデルセット
			pSceneModel->Set(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f), PLAYER_Y, ((nCount / m_nMaxX) * -CHIP_SIZE) + (rand() % 201 - 100) * (CHIP_SIZE * 0.0025f)),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_BOX_2, tex, CScene::DRAW_TYPE_NORMAL, true, use);
		}
	}
}
//==================================================================================================//
//    * ダンジョン作成時の変換パーツ *
//==================================================================================================//
void CDungeon::SetEnemy(int nCount)
{
	CSceneEnemy *pSceneEnemy;

	//近場かぶり対策　削除
	CCollision::DestroyRange(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE), PLAYER_Y, ((nCount / m_nMaxX) * -CHIP_SIZE)),
		CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_OBJ);
	CCollision::DestroyRange(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE), PLAYER_Y, ((nCount / m_nMaxX) * -CHIP_SIZE)),
		CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_ENEMY);

	if (SceneCreate(pSceneEnemy, MODEL_PRIORITY))
	{
		pSceneEnemy->Set(D3DXVECTOR3((nCount % m_nMaxX) * CHIP_SIZE, PLAYER_Y, (nCount / m_nMaxX) * -CHIP_SIZE),
			D3DXVECTOR3(0.0f, (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TANKD, CSceneModel::MODEL_TANKU,
			(CSceneModel::TEXTURE)(rand() % 8 + (int)CSceneModel::TEX_PTN_01), (CSceneModel::TEXTURE)(rand() % 8 + (int)CSceneModel::TEX_PTN_01), CScene::DRAW_TYPE_NORMAL);
	}
}
//==================================================================================================//
//    * トラップの配置 *
//==================================================================================================//
void CDungeon::SetTrap(int nCount, int nType)
{
	CScene3D	*pScene3D;

	//近場かぶり対策　削除
	CCollision::DestroyRange(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE)),
		CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_OBJ);
	CCollision::DestroyRange(D3DXVECTOR3(((nCount % m_nMaxX) * CHIP_SIZE), 20.1f, ((nCount / m_nMaxX) * -CHIP_SIZE)),
		CHIP_SIZE, CHIP_SIZE, CScene::OBJTYPE_ENEMY);

	if (SceneCreate(pScene3D, DUNGEON_PRIORYITY))
	{
		int nRand;
		if (nType != 1) { nRand = rand() % 6; }
		else { nRand = rand() % 4 + 3; }

		if (nRand > 1) { nRand++; }	//画像のずれ補正

		pScene3D->Set(D3DXVECTOR3((nCount % m_nMaxX) * CHIP_SIZE, PLAYER_Y, (nCount / m_nMaxX) * -CHIP_SIZE),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), ITEM_SIZE, ITEM_SIZE, CScene3D::TEX_TRAP, nRand, 3, 3, CScene::DRAW_TYPE_NORMAL);
		pScene3D->GetState()[0] = (CScene3D::STATE)(CScene3D::STATE_EXPLOSION0 + nRand);
	}
}
//==================================================================================================//
//    * ダンジョン全体の判定 *
//==================================================================================================//
bool CDungeon::Collision(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float fLengthX, float fLengthZ, bool &bRiver)
{
	bool bCollision = false;

	for (int nCountZ = 0; nCountZ < m_nMemory / m_nMaxX; nCountZ++)
	{//Z軸回転
		for (int nCountX = 0; nCountX < m_nMaxX; nCountX++)
		{//X軸回転
			if (m_nMapChip[nCountX + (nCountZ * m_nMaxX)][0] == 0 || (m_nMapChip[nCountX + (nCountZ * m_nMaxX)][0] == 5 && bRiver))
			{//判定のあるチップなら
				if (nCountX * CHIP_SIZE + CHIP_SIZE / 2 + fLengthX >= pos.x && nCountX * CHIP_SIZE - CHIP_SIZE / 2 - fLengthX <= pos.x)
				{//横幅が範囲内 //上下Hit 
					if (nCountZ * -CHIP_SIZE + CHIP_SIZE / 2 + fLengthZ > pos.z && nCountZ * -CHIP_SIZE + CHIP_SIZE / 2 + fLengthZ <= posold.z)
					{//上
						pos.z = nCountZ * -CHIP_SIZE + CHIP_SIZE / 2 + fLengthZ; nCountZ -= 2;
						bCollision = true; break;
					}
					else if (nCountZ * -CHIP_SIZE - CHIP_SIZE / 2 - fLengthZ < pos.z && nCountZ * -CHIP_SIZE - CHIP_SIZE / 2 - fLengthZ >= posold.z)
					{//下
						pos.z = nCountZ * -CHIP_SIZE - CHIP_SIZE / 2 - fLengthZ;
						bCollision = true;
					}
				}
				if (nCountZ * -CHIP_SIZE + CHIP_SIZE / 2 + fLengthZ > pos.z && nCountZ * -CHIP_SIZE - CHIP_SIZE / 2 - fLengthZ < pos.z)
				{//縦幅が範囲内 //横Hit
					if (nCountX * CHIP_SIZE + CHIP_SIZE / 2 + fLengthX > pos.x && nCountX * CHIP_SIZE + CHIP_SIZE / 2 + fLengthX <= posold.x)
					{//右
						pos.x = nCountX * CHIP_SIZE + CHIP_SIZE / 2 + fLengthX;
						move.x = 0.35f;
						bCollision = true;
					}
					else if (nCountX * CHIP_SIZE - CHIP_SIZE / 2 - fLengthX < pos.x && nCountX * CHIP_SIZE - CHIP_SIZE / 2 - fLengthX >= posold.x)
					{//左
						pos.x = nCountX * CHIP_SIZE - CHIP_SIZE / 2 - fLengthX;
						move.x = -0.35f;
						bCollision = true;
					}
				}
			}//判定のあるチップ
		}//X軸
	}//Z軸

	return bCollision;
}
//==================================================================================================//
//    * 弾のダンジョン全体の判定 *
//==================================================================================================//
void CDungeon::ShotCollision(CSceneBullet *pBullet)
{
	D3DXVECTOR3 pos = pBullet->GetPosition()[0];
	float		fLength = pBullet->GetfLengthX()[0];

	int nNumberX, nNumberZ, nNumber;
	
	//近く3列で判定
	for (int nCountX = 0; nCountX < 3; nCountX++)
	{//X3列
		nNumberX = (int)(pos.x / CHIP_SIZE) - 1 + nCountX;
		for (int nCountZ = 0; nCountZ < 3; nCountZ++)
		{//Z3列
			nNumberZ = (int)(pos.z / -CHIP_SIZE) - 1 + nCountZ;
			nNumber = nNumberX + (nNumberZ * m_nMaxX);
			if (nNumber < 0) { nNumber = 0; }
			if (nNumber >= m_nMemory) { nNumber = m_nMemory - 1; }

			if (m_nMapChip[nNumber][0] == 0)
			{//壁なら
				if (nNumberX * CHIP_SIZE + CHIP_SIZE / 2 + fLength > pos.x && nNumberX * CHIP_SIZE - CHIP_SIZE / 2 - fLength < pos.x &&
					nNumberZ * -CHIP_SIZE + CHIP_SIZE / 2 + fLength > pos.z && nNumberZ * -CHIP_SIZE - CHIP_SIZE / 2 - fLength < pos.z)
				{//範囲内なら
					pBullet->GetfCntState()[0] = SHOT_LIFE;
					break;
				}
			}
		}
	}
}
//==================================================================================================//
//    * ダンジョン作成時の変換パーツ *
//==================================================================================================//
void CDungeon::DrawEffect(void)
{
	for (int nCount = 0; nCount < MAP_MAX_EFFECT; nCount++)
	{//闇
		if (m_pFrontBG[nCount] != NULL) { m_pFrontBG[nCount]->Draw(); }
	}
	if (m_pTimer != NULL) { m_pTimer->Draw(); }
}
//==================================================================================================//
//    * 初期化 *
//==================================================================================================//
HRESULT	 CSceneDungeonBG::Init(void)
{
	for (int nCount = 0; nCount < MAP_MAX_EFFECT2; nCount++)
	{//弾後雲エフェクト
		if (m_pBG[nCount] == NULL)
		{//背景エフェクト
			Create(m_pBG[nCount]);
			if (m_pBG[nCount] != NULL)
			{
				switch (nCount)
				{
				case 0://内側
					m_pBG[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0.0005f, 0.0005f, 0.01f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.65f), C2D::TEX_Cloud1);
					m_pBG[nCount]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
					break;
				case 1://外側
					m_pBG[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0.00075f, 0.0005f, 0.005f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), C2D::TEX_Cloud2);
					m_pBG[nCount]->BindDrawType(CScene::DRAW_TYPE_SUBTRACT);
					break;
				}
			}
		}
	}
	SetObjType(CScene::OBJTYPE_DUNGEON);
	return S_OK;
}
//==================================================================================================//
//    * 更新 *
//==================================================================================================//
void	CDungeon:: InitBossBG(CScene3D::TEXTURE tex)
{
	if (m_p3DBG == NULL)
	{
		SceneCreate(m_p3DBG, DUNGEON_PRIORYITY);
		if (m_p3DBG != NULL)
		{
			m_p3DBG->Set(DUNGEON_CENTER + D3DXVECTOR3(0.0f, 0.01f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 110.0f, 70.0f, tex, 0, 1, 1, CScene::DRAW_TYPE_SUBTRACT);
			m_p3DBG->GetState()[0] = CScene3D::STATE_BFLOW_IN;
		}
	}
}
//==================================================================================================//
//    * 更新 *
//==================================================================================================//
void	 CSceneDungeonBG::Update(void)
{
	for (int nCount = 0; nCount < MAP_MAX_EFFECT2; nCount++)
	{//雲
		if (m_pBG[nCount] != NULL) { m_pBG[nCount]->Update(); }
	}
}
//==================================================================================================//
//    * 描画 *
//==================================================================================================//
void	 CSceneDungeonBG::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	for (int nCount = 0; nCount < MAP_MAX_EFFECT2; nCount++)
	{//雲
		if (m_pBG[nCount] != NULL) { m_pBG[nCount]->Draw(); }
	}
	// バックバッファ＆Ｚバッファのクリア
	pD3DDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
}
//==================================================================================================//
//    * 描画 *
//==================================================================================================//
void	 CSceneDungeonBG::Uninit(void)
{
	for (int nCount = 0; nCount < MAP_MAX_EFFECT2; nCount++)
	{//弾後背景の削除
		if (m_pBG[nCount] != NULL) { delete m_pBG[nCount]; }
	}
	Release();
}
//==================================================================================================//
//    * 暗闇の色変更 *
//==================================================================================================//
void CDungeon::SetColBG(D3DXCOLOR col)
{
	m_pFrontBG[0]->SetColor(col);
	m_pFrontBG[1]->SetColor(col);
}
//==================================================================================================//
//    * 血痕の色変更 *
//==================================================================================================//
void CDungeon::SetDamageBG(CScene::DRAW_TYPE shield, float fPerLife, bool bHit, int nID)
{
	float fCol = 0.0f;
	float fMinCol = 0.0f;

	if (bHit) { fCol = 1.0f; }	//ダメージ時
	else
	{//通常時
		if (shield == CScene::DRAW_TYPE_NO)
		{//シールド無し
			fCol = 1.0f;
		}
		else
		{//シールドあり
			fCol = -0.05f;
		}
	}
	
	if (fPerLife == 0.0f)
	{//死亡した
		fCol = -10.0f;
		fMinCol = 0.0f;
	}//HPが半分以下
	else if (fPerLife < 0.5f) { fMinCol = 0.3f; }


	m_pFrontBG[2]->SetSideAlpha(fCol, fMinCol, nID);
	if (CScenePlayer::GetnNumPlayer() == 1) { m_pFrontBG[2]->SetSideAlpha(fCol, fMinCol, 1); }
}