//==================================================================================================//
//
//    * [dungeon.cpp] *
//    * Author Ryo Sugimoto *
//
//==================================================================================================//
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用

#include "dungeon.h"
#include "camera.h"
#include "scene.h"

#include "player.h"
#include "enemy.h"
#include "mesh.h"
#include "SceneModel.h"
#include "SceneAnim3D.h"
//==================================================================================================//
//    * マクロ定義 *
//==================================================================================================//
#define MAX_ROAD		(4)
#define MAX_ROOM		(MAX_ROAD * 5)
#define MAX_ROAD_INFO	(3)
#define MAX_ROOM_INFO	(4)

//==================================================================================================//
//    * 静的メンバ変数宣言 *
//==================================================================================================//

//==================================================================================================//
//    * 生成関数 *
//==================================================================================================//
HRESULT CDungeon::Init(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();

	//設定
	CScene::SetObjType(OBJTYPE_DUNGEON);

	m_BGM = CSound::LABEL_MAX;

	m_bEnd = false;
	m_nQuake = 0;
	m_nLevel = 0;
	m_fCntPlus = 0.0f;
	m_fCntState = 0.0f;
	CManager::GetpDungeon() = this;
	return S_OK;
}
//==================================================================================================//
//    * 生成関数 *
//==================================================================================================//
void CDungeon::Uninit(void)
{
	if (m_BGM != CSound::LABEL_MAX) { CManager::GetSound()->Stop(m_BGM); m_BGM = CSound::LABEL_MAX; }
	CManager::GetpDungeon() = NULL;
	Release();
}
//==================================================================================================//
//    * 更新関数 *
//==================================================================================================//
void CDungeon::Update(void)
{
	if (m_fCntPlus > 0.0f)
	{//マップ切り替え中
		m_fCntState += m_fCntPlus;
		if (m_fCntState > 1.0f)
		{
			m_fCntPlus = 0.0f;
			switch (m_Type)
			{
			case TYPE_RAND: SetDungeon_Rand(); break;
			case TYPE_BOSS: SetDungeon_Boss(); break;
			}
		}
	}
}
//==================================================================================================//
//    * 描画関数 *
//==================================================================================================//
void CDungeon::Draw(void)
{

}
//==================================================================================================//
//    * マップの切り替え処理 *
//==================================================================================================//
void CDungeon::ChangeMap(TYPE type)
{
	if (m_fCntPlus == 0.0f)
	{
		CScene2D *p2D;
		if (SceneCreate(p2D, S2D_PRIORITY))
		{
			p2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),
				SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.05f, CScene2D::STATE_FADE,
				D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene::TEX_MAX);
		}
		m_Type = type;
		m_fCntPlus = 0.05f;
		m_fCntState = 0.0f;
	}
}
//==================================================================================================//
//    * ランダムダンジョンの初期化 *
//==================================================================================================//
void CDungeon::InitDungeon(void)
{
	m_bEnd = true;
	CScene::BreakObject(CScene::OBJTYPE_MESH);
	CScene::BreakObject(CScene::OBJTYPE_OBJ);
	CScene::BreakObject(CScene::OBJTYPE_ENEMY);
}
//==================================================================================================//
//    * ランダムダンジョン作成 *
//==================================================================================================//
void CDungeon::SetDungeon_Rand(void)
{
	int		nCntRoad[2];				//現在の道生成数	: 次生成数 
	int		nCntRoom[2];				//現在の部屋生成数	: 次生成数 
	float	fRoadC[MAX_ROAD][MAX_ROAD_INFO];		//道の情報
	float	fRoomC[MAX_ROAD * 4][MAX_ROOM_INFO];	//部屋の情報	0:位置, 1:角度, 2:高さ, 3:生成部類
	bool	bRoom = true;				//通路生成かルーム生成か
	bool	bEnd = false;				//通路終了時

	int		nPos;
	int		nRot;

	int		nMapChip[MAP_SIZE][MAP_SIZE];
	CMesh	*pField = NULL;
	CMesh	*pCeiling = NULL;
	int *pMap = NULL;

	do
	{//ランダム生成が正常終了するまで
		nPos = MAP_SIZE / 2 + (MAP_SIZE / 2 * MAP_SIZE);
		nRot = 1;
		nCntRoad[0] = 0; nCntRoad[1] = 0;
		nCntRoom[0] = 0; nCntRoom[1] = 1;
		InitDungeon();//ダンジョン初期化
		if (SceneCreate(pField, MESH_PRIORITY)) 
		{ //床の生成
			pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true); 
			pField->BindTexture(Load(TEX_Dungeon));
		}
		if (SceneCreate(pCeiling, MESH_PRIORITY)) 
		{ //天井の生成
			pCeiling->Set(CMesh::TYPE_CEILING, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -MAP_SIZE * CHIP_SIZE - CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, false); 
			pCeiling->BindTexture(Load(TEX_Dungeon));
		}

		//マップを全部壁に
		pMap = &nMapChip[0][0];
		for (int nCount = 0; nCount < MAP_SIZE * MAP_SIZE; nCount++) { pMap[nCount] = 0; }

		//pMap[MAP_SIZE + 1] = 1;			//道に変える
		nPos = MAP_SIZE / 2 + ((MAP_SIZE / 8) * MAP_SIZE);
		fRoomC[0][0] = (float)nPos; fRoomC[0][1] = (float)nRot; fRoomC[0][2] = 30.0f; fRoomC[0][3] = 0.0f;

		do
		{//部屋と通路が全生成されるまで
			if (bRoom)
			{
				if (nCntRoom[0] == nCntRoom[1]) { bRoom = false; if (bEnd) { break; } }
				else
				{//部屋の生成
					//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "ルーム%d生成\n", nCntRoom[0]);
					SetRoom(pMap, &fRoomC[0][0], &fRoadC[0][0], &nCntRoom[0], &nCntRoad[0], pField, pCeiling);
					nCntRoom[0]++;
				}
				bEnd = false;
			}
			else
			{
				if (nCntRoad[0] == nCntRoad[1]) { bRoom = true; bEnd = true; }
				else
				{//道の生成
					//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "ロード%d生成\n", nCntRoad[0]);
					SetRoad(pMap, &fRoomC[0][0], &fRoadC[0][0], &nCntRoom[0], &nCntRoad[0], pField, pCeiling);
					nCntRoad[0]++;
				}
			}
			if (!m_bEnd)
			{ 
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "範囲外終了\n");
			break;
			}
		} while (1);
		if (SetWall(&nMapChip[0][0]) != 1) 
		{ 
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "壁多数終了\n");
			m_bEnd = false;
		}
	} while (!m_bEnd);

	pField->UpField(pMap, FIELD_DOWN);
	pCeiling->UpField(pMap, -FIELD_DOWN);
	CSceneObjct::SetObjField();

	pField->SetNor();
	pCeiling->SetNor();

	//BGMの再生
	if (m_BGM != CSound::LABEL_MAX) { CManager::GetSound()->Stop(m_BGM); }
	m_BGM = CSound::LABEL_FIELD000;
	CManager::GetSound()->Play(m_BGM);

	CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "ランダン生成終了\n");
}
//==================================================================================================//
//    * ボス戦作成 *
//==================================================================================================//
void CDungeon::SetDungeon_Boss(void)
{
	bool	bRoom = true;				//通路生成かルーム生成か
	bool	bEnd = false;				//通路終了時

	int		nPos, nWKPos;
	int		nRot;
	int		nPlusX = 0, nPlusZ = 0;

	int		nMapChip[MAP_SIZE][MAP_SIZE];
	CMesh	*pField = NULL;
	CMesh	*pCeiling = NULL;
	int *pMap = NULL;

	do
	{//ランダム生成が正常終了するまで
		nPos = MAP_SIZE / 2 + (MAP_SIZE / 2 * MAP_SIZE);
		nRot = 1;
		InitDungeon();//ダンジョン初期化
		if (SceneCreate(pField, MESH_PRIORITY))
		{ //床の生成
			pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true);
			pField->BindTexture(Load(TEX_Dungeon));
		}
		if (SceneCreate(pCeiling, MESH_PRIORITY))
		{ //天井の生成
			pCeiling->Set(CMesh::TYPE_CEILING, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -MAP_SIZE * CHIP_SIZE - CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, false);
			pCeiling->BindTexture(Load(TEX_Dungeon));
		}

		//マップを全部壁に
		pMap = &nMapChip[0][0];
		for (int nCount = 0; nCount < MAP_SIZE * MAP_SIZE; nCount++) { pMap[nCount] = 0; }

		//位置初期化
		nPos = MAP_SIZE / 2 + ((MAP_SIZE / 2) * MAP_SIZE);

		//掘る
		SetDig(pMap, nPos, nRot, -6, -6, 6, 6, 0.0f, 0.0f, 1, pField, pCeiling);
		SetDig(pMap, nPos, nRot, -6, 0, 6, 6, 0.0f, 0.0f, 1, pField, pCeiling);
		SetDig(pMap, nPos, nRot, 0, -6, 6, 6, 0.0f, 0.0f, 1, pField, pCeiling);
		SetDig(pMap, nPos, nRot, 0, 0, 6, 6, 0.0f, 0.0f, 1, pField, pCeiling);

		//敵配置
		nPlusX = 0; nPlusZ = -3; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetEnemy(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE, -100.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_BOX_Sword, CEnemy::TYPE_TITLE);

		//自機配置
		nPlusX = 0; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetPpos(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE, -100.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));

		if (SetWall(&nMapChip[0][0]) != 1)
		{
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "壁多数終了\n");
			m_bEnd = false;
		}
	} while (!m_bEnd);

	pField->UpField(pMap, FIELD_DOWN);
	pCeiling->UpField(pMap, -FIELD_DOWN);
	CSceneObjct::SetObjField();

	pField->SetNor();
	pCeiling->SetNor();

	//BGMの再生
	if (m_BGM != CSound::LABEL_MAX) { CManager::GetSound()->Stop(m_BGM); }
	m_BGM = CSound::LABEL_BOSS000;
	CManager::GetSound()->Play(m_BGM);
	CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "ランダン生成終了\n");
}
//==================================================================================================//
//    * マス分掘る *
//==================================================================================================//
void CDungeon::SetDig(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLengthX, int nLengthZ, float fHeight, float fPHeight, int nChip, CMesh *pField, CMesh *pCeiling)
{//変数 * 変数で掘る
	int nZPos;
	int nXPos;
	int nDig[100];
	float fSHeight[100];
	int nMaxDig = 0;

	SpinDig(nRot, nPlusX, nPlusZ);
	nPos += nPlusZ + nPlusX;
	for (int nCountZ = 0; nCountZ < nLengthX; nCountZ++)
	{
		for (int nCountX = 0; nCountX < nLengthZ; nCountX++)
		{
			nZPos = nCountZ; nXPos = nCountX;
			SpinDig(nRot, nZPos, nXPos);
			if(nPos + nXPos + nZPos < MAP_SIZE * MAP_SIZE && nPos + nXPos + nZPos >= 0)
			{ 
				nMap[nPos + nXPos + nZPos] = nChip;
				nDig[nMaxDig] = nPos + nXPos + nZPos;	//位置保存
				fSHeight[nMaxDig] = fHeight + nCountX * fPHeight;
				nMaxDig++;								//量保存
			}
		}
	}
	//起伏天井一定化
	if (!pField->SetField(&nDig[0], nMaxDig, &fSHeight[0], (fPHeight == 0))) { m_bEnd = false; }
	if (!pCeiling->SetField(&nDig[0], nMaxDig, &fSHeight[0], (fPHeight == 0))) { m_bEnd = false; }
}
//==================================================================================================//
//    * マス分メッシュ上下 *
//==================================================================================================//
void CDungeon::SetMesh(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLength, float fHeight, CMesh *pField, CMesh *pCeiling)
{//変数 * 変数で掘る
	int nZPos;
	int nXPos;

	SpinDig(nRot, nPlusZ, nPlusX);
	nPos += nPlusZ + nPlusX;
	for (int nCountZ = 0; nCountZ < nLength; nCountZ++)
	{
		for (int nCountX = 0; nCountX < nLength; nCountX++)
		{
			nZPos = nCountZ; nXPos = nCountX;
			SpinDig(nRot, nZPos, nXPos);
			if (nPos + nXPos + nZPos < MAP_SIZE * MAP_SIZE && nPos + nXPos + nZPos >= 0) { nMap[nPos + nXPos + nZPos] = 1; }
		}
	}
}

//==================================================================================================//
//    * マス分回転 *
//==================================================================================================//
void CDungeon::SpinDig(int &nRot, int &nLengthZ, int &nLengthX)
{
	switch (nRot)
	{
	case 0:	//前
		nLengthZ = nLengthZ * MAP_SIZE;
		nLengthX = nLengthX;
		break;
	case 1:	//右
		nLengthZ = nLengthZ;
		nLengthX = nLengthX * -MAP_SIZE;
		break;
	case 2:	//後ろ
		nLengthZ = nLengthZ * -MAP_SIZE;
		nLengthX = -nLengthX;
		break;
	case 3:	//左
		nLengthZ = -nLengthZ;
		nLengthX = nLengthX * MAP_SIZE;
		break;
	}
}
//==================================================================================================//
//    * ルームの作成 *
//==================================================================================================//
void CDungeon::SetRoom(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling)
{
	int nPlus = nCntRoom[0] * MAX_ROOM_INFO;
	int nPlusX = 0, nPlusZ = 0;
	int nPos = (int)fRoomC[nPlus];
	int nWKPos = nPos;
	int nRot = (int)fRoomC[nPlus + 1];
	int nRoom = rand() % 4 + 1;
	int nWKData;

	//初期確認
	if(nCntRoom[0] == 0) { nRoom = 0; }
	else if (fRoomC[nPlus + 3] != 0.0f)
	{ nRoom = rand() % 3 + 1; }	//小ルームのみに変換
	switch (nRoom)
	{
	case 0:
		SetDig(nMap, nWKPos, nRot, -1, -1, 1, 3, fRoomC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 0, -3, 1, 6, fRoomC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, -2, 1, 2, fRoomC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		//プレイヤーセット
		SetPpos(D3DXVECTOR3((nPos % MAP_SIZE) * -CHIP_SIZE, -100.0f, (nPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//部屋生成
		nPlusX = 0; nPlusZ = -4; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 2) % 4), fRoomC[nPlus + 2], 1.0f);
		break;
	case 1:
		//掘る
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 2, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 5, 7, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -3, 3, 7, 5, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);

		//オブジェクト設置
		nPlusX = 0; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));

		
		if (fRoomC[nPlus + 3] >= 0.0f)
		{//通路生成
			nWKData = rand() % 3 * 10 + rand() % 2;
			if (nWKData % 10 == 0 || (nWKData % 10 + nWKData / 10) % 3 == 0)
			{
				nPlusX = 0; nPlusZ = 9; SpinDig(nRot, nPlusX, nPlusZ);
				SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoomC[nPlus + 2]);
			}
			if (nWKData % 10 == 1 || (nWKData % 10 + nWKData / 10) % 3 == 1)
			{
				nPlusX = 4; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
				SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoomC[nPlus + 2]);
			}
			if (nWKData % 10 == 2 || (nWKData % 10 + nWKData / 10) % 3 == 2)
			{
				nPlusX = -4; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
				SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoomC[nPlus + 2]);
			}
		}
		break;
	case 2:
		SetDig(nMap, nWKPos, nRot, -1, 0, 2, 6, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 6, 2, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 3, 5, 4, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		//オブジェクト設置
		nPlusX = 1; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		if (fRoomC[nPlus + 3] >= 0.0f)
		{//通路生成
			nPlusX = 3; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoomC[nPlus + 2]);
			nPlusX = -3; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoomC[nPlus + 2]);
		}
		break;
	case 3:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 4, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 1, 3, 4, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		//オブジェクト設置
		nPlusX = -1; nPlusZ = 2; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		if (fRoomC[nPlus + 3] >= 0.0f)
		{//通路生成
			nPlusX = 0; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoomC[nPlus + 2]);
		}
		break;
	case 4:
		//掘る
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 2, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 9, 11, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -3, 3, 8, 5, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, 12, 3, 1, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);

		//オブジェクト設置
		nPlusX = 3; nPlusZ = 7; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom2(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE), ChangeRot(nRot));

		if (fRoomC[nPlus + 3] >= 0.0f)
		{//通路生成
			nPlusX = -4; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoomC[nPlus + 2]);
			nPlusX = 1; nPlusZ = 13; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoomC[nPlus + 2]);
			//隠し部屋
			nPlusX = 7; nPlusZ = 6; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoomC[nPlus + 2], -1.0f);
		}
		break;
	}
}
//==================================================================================================//
//    * ルームの作成 *
//==================================================================================================//
void CDungeon::SetRoad(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling)
{
	int nPlus = nCntRoad[0] * MAX_ROAD_INFO;
	int nPlusX = 0, nPlusZ = 0;
	int nPos = (int)fRoadC[nPlus];
	int nWKPos = nPos;
	int nRot = (int)fRoadC[nPlus + 1];
	int nRoom = rand() % 3;
	float fWKHeight = rand() % 2 * 70.0f - 35.0f;

	if (nCntRoad[0] == MAX_ROAD - 1) { nRoom = 5; }
	switch (nRoom)
	{
	case 0:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 5, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 3, 1, 3, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		//オブジェ
		nPlusX = 0; nPlusZ = 4; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		nPlusX = -1; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//ルーム
		nPlusX = -1; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoadC[nPlus + 2] + fWKHeight * 5, 0.0f);
		break;
	case 1:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 4, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 3, 1, 2, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 4, 2, 1, fRoadC[nPlus + 2] + fWKHeight * 4, fWKHeight, 1, pField, pCeiling);
		//オブジェ
		nPlusX = -1; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//ルーム
		nPlusX = -3; nPlusZ = 4; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoadC[nPlus + 2] + fWKHeight * 5, 0.0f);
		break;
	case 2:
		fWKHeight = rand() % 2 * 30.0f - 15.0f;
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 2, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, 1, 1, 2, fRoadC[nPlus + 2] + fWKHeight * 1, fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 2, 1, 1, 3, fRoadC[nPlus + 2] + fWKHeight * 1, fWKHeight, 1, pField, pCeiling);
		//オブジェ
		nPlusX = 2; nPlusZ = 1; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//ルーム
		nPlusX = 2; nPlusZ = 4; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoadC[nPlus + 2] + fWKHeight * 4, 0.0f);
		break;
	case 3:
		//fWKHeight = rand() % 2 * 100.0f - 50.0f;
		//SetDig(nMap, nWKPos, nRot, 0, 0, 1, 3, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		//SetDig(nMap, nWKPos, nRot, 0, 5, 3, 1, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		//SetDig(nMap, nWKPos, nRot, -1, 4, 2, 1, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		//SetDig(nMap, nWKPos, nRot, -3, 3, 4, 1, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		////オブジェ
		//nPlusX = 2; nPlusZ = 1; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		//SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		////ルーム
		//nPlusX = 3; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
		//SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoadC[nPlus + 2] + fWKHeight * 3);
		//nPlusX = -4; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
		//SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoadC[nPlus + 2] + fWKHeight * 3);
		//break;
	case 5:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 5, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, 2, 1, 2, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 2, 1, 3, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 1, 3, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		nPlusX = -1; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
		nWKPos = nPos + nPlusZ + nPlusX;
		SetGpos(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE, fRoadC[nPlus + 2], (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		break;
	}
}
//==================================================================================================//
//    * 部屋セット準備処理 *
//==================================================================================================//
void CDungeon::SettingRoom(float *fRoomC, int *nCntRoom, float fPos, float fRot, float fHeight, float fState)
{
	if (nCntRoom[1] < MAX_ROOM)
	{
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 0] = fPos;
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 1] = fRot;
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 2] = fHeight;
		//if (fState >= 0.0f) { fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 2] += (rand() % 2 * 100.0f) - 50.0f; }
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 3] = fState;
		nCntRoom[1]++;
	}
}
//==================================================================================================//
//    * 道セット準備処理 *
//==================================================================================================//
void CDungeon::SettingRoad(float *fRoadC, int *nCntRoad, float fPos, float fRot, float fHeight)
{
	if (nCntRoad[1] < MAX_ROAD)
	{
		fRoadC[nCntRoad[1] * MAX_ROAD_INFO + 0] = fPos;
		fRoadC[nCntRoad[1] * MAX_ROAD_INFO + 1] = fRot;
		fRoadC[nCntRoad[1] * MAX_ROAD_INFO + 2] = fHeight + (rand() % 2 * 100.0f) - 50.0f;
		nCntRoad[1]++;
	}
}
//==================================================================================================//
//    * 壁作成時の角度float化 *
//==================================================================================================//
float CDungeon::ChangeRot(int &nRot)
{
	switch (nRot)
	{
	case 2: return 0.0f;
	case 3: return D3DX_PI * 0.5f;
	case 0: return D3DX_PI;
	case 1: return D3DX_PI * -0.5f;
	}
	return 0.0f;
}
//==================================================================================================//
//    * 全壁の作成 *
//==================================================================================================//
int CDungeon::SetWall(int *nMap)
{
	int nCntWall = 0;		//現在地
	int nPos = -1;		//現在地
	int nRot = -1;		//進行方向
	int nFRot = -1;		//床方向

	int nBranch = -1;	//分記法
	int nPosold = -1;	//前の現在地
	int nRotold = -1;	//前の進行方向
	int nFRotold = -1;	//前の進行方向

	int nMoveR, nMoveF;	//進行方向と床方向による移動量
	bool bTop = true;	//終了分岐用

	int nNumVrx = 0;	//次回使用頂点
	float fWKRot = 0.0f;//頂点代入時の角度変換用
	float fWKFRot = 0.0f;//頂点代入時の角度変換用
	D3DXVECTOR3 vtx[MAP_SIZE * MAP_SIZE / 2];

	float fDistance;
	while (1)
	{//生成が終わるまでループ
		int nPos = -1;	//現在地をリセット
		nNumVrx = 0;
		//生成していない壁を探す
		for (int nCount = 0; nCount < MAP_SIZE * MAP_SIZE; nCount++)
		{//下が床なのを探す == 1
			if (nMap[nCount] == 1)
			{//現在が床
				if (nMap[nCount - MAP_SIZE] == 0)
				{//その上が壁なら
					nPos = nCount - MAP_SIZE;	//現在地代入
					nRot = (bTop ? 1 : 3);
					nFRot = 0;					//床方向は上
					break;
				}
			}
		}

		if (nPos == -1) { break; }	//床がなければ終了
		int nNumVrx = 0;
		nBranch = -1;
		fDistance = (bTop ? (CHIP_SIZE / 2) : (CHIP_SIZE / 6));

		do
		{//同じ場所に着くまでループ
			//点を打つ
			fWKFRot = ChangeRot(nFRot);
			vtx[nNumVrx] = D3DXVECTOR3((nPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE)
				+ D3DXVECTOR3(sinf(fWKFRot), 0.0f, cosf(fWKFRot)) * fDistance;

			nNumVrx++;	//頂点数の増加

			//探す手順と同じ状態なら壁削除
			if ((bTop ? nRot == 1 : nRot == 3) && nFRot == 0) { nMap[nPos] = -1; }

			nPosold = nPos;		//前の位置に代入
			nRotold = nRot;		//前の進行方向に代入
			nFRotold = nFRot;	//前の床方向を代入

			//進行
			nMoveR = 1; nMoveF = 1;
			SpinDig(nRot, nMoveR, nBranch);	//進行方向による移動値計算
			SpinDig(nFRot, nMoveF, nBranch);//床方向による移動値計算

			if (nMap[nPos + nMoveR + nMoveF] != 1)
			{//進行中に壁にぶつかった！
				nBranch = 0;				//衝突分岐の保存
				nPos = nPos + nMoveR + nMoveF;	//位置の更新
				nRot = (bTop ? nFRot : nFRot);
				nFRot = (bTop ? (nRotold + 2) % 4 : (nRotold + 2) % 4);
			}
			else if (nMap[nPos + nMoveR] == 1)
			{//進行方向が床！
				nBranch = 1;				//曲がる～ん分岐の保存
				nRot = (bTop ? (nFRot + 2) % 4 : nFRot);
				nFRot = (bTop ? nRotold : (nRotold + 2) % 4);
			}
			else
			{//曲がらない
				nBranch = 2;				//ストレート分岐の保存
				nPos = nPos + nMoveR;			//位置の更新
			}


			if (nBranch == 1)
			{//曲がる～ん分岐なら
				fWKRot = ChangeRot(nRotold);	//前の点から前の進行方向へ
				vtx[nNumVrx] = vtx[nNumVrx - 1] + D3DXVECTOR3(sinf(fWKRot), 0.0f, cosf(fWKRot)) * (CHIP_SIZE / 8) * (bTop ? 1.0f : -1.0f);

				fWKFRot = ChangeRot(nFRot);//次の点から前の床方向へ
				fWKRot = ChangeRot(nFRotold);	//前の点から前の進行方向へ
				vtx[nNumVrx + 1] = D3DXVECTOR3((nPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE)
					+ D3DXVECTOR3(sinf(fWKFRot), 0.0f, cosf(fWKFRot)) * fDistance
					+ D3DXVECTOR3(sinf(fWKRot), 0.0f, cosf(fWKRot)) * (fDistance / 4);
				nNumVrx += 2;	//頂点数の増加
			}
		} while (nMap[nPos] != -1 || nFRot != 0 || nRot != (bTop ? 1 : 3));	//既に通った道なら

		//メッシュを生成し頂点を代入
		CMesh *pMesh;
		if (SceneCreate(pMesh, MESH_PRIORITY))
		{
			nCntWall++;
			pMesh->Set(CMesh::TYPE_WALL, D3DXVECTOR3(0.0f, -1000.0f, 0.0f), 10, nNumVrx, (bTop ? true : false));
			pMesh->SetWall(&vtx[0]);
			pMesh->BindTexture(Load(TEX_Dungeon));
			pMesh->SetNor();
			//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "メッシュ作成 XZ%d, Y %d %s\n", 20, nNumVrx, (bTop ? "トップ": "NO"));
			bTop = false;
		}
	}
	//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "壁 %d\n", nCntWall);
	return nCntWall;
}
//==================================================================================================//
//	* プレイヤーの位置変更 *
//==================================================================================================//
void CDungeon::SetPpos(D3DXVECTOR3 pos)
{
	for (int nCount = 0; nCount < (CManager::GetbDuo() ? 2 : 1); nCount++)
	{
		CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(nCount)->GetChar();
		CManager::GetPlayer(nCount)->Getpos() = pos;
		CManager::GetPlayer(nCount)->Getposold() = pos;
		CManager::GetPlayer(nCount)->Getrot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CManager::GetPlayer(nCount)->GetbReset() = true;

		pCamera->GetRot().y = 0.0f;
	}
}
//==================================================================================================//
// * ゴール地点設置 *
//==================================================================================================//
void CDungeon::SetGpos(D3DXVECTOR3 pos)
{
	CSceneObjct *pObject;
	CSceneAnimEffect *p3D;
	if (SceneCreate(pObject, MODEL_PRIORITY))
	{//オブジェの設置
		pObject->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_Gate, false, CSceneObjct::USE_MAX);
	}
	if (SceneCreate(p3D, S3D_PRIORITY))
	{
		p3D->Set(D3DXVECTOR3(0.0f, 20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(150.0f, 0.0f, 150.0f),
			CScene::TEX_GateE, false, CScene::DRAW_TYPE_OVERLAY, 0, 5, 2, 6, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_NORMAL,
			&pObject->GetPosition(), pObject);
	}
}
//==================================================================================================//
//	* プレイヤーの位置変更 *
//==================================================================================================//
void CDungeon::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, CEnemy::TYPE Etype)
{
	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY)) { pEnemy->Set(pos, rot, Mtype, Etype, m_nLevel); }
}
//==================================================================================================//
//    * ルームオブジェ小の作成 *
//==================================================================================================//
void CDungeon::SetObjRoom(D3DXVECTOR3 pos)
{
	CSceneObjct *pObject;
	float		fRot = (rand() % 8) * (D3DX_PI * 0.25f);
	CSceneModel::MODEL model = ((CSceneModel::MODEL)(CSceneModel::MODEL_STEEL));

	if (SceneCreate(pObject, MODEL_PRIORITY)) { pObject->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_STEEL_B, true, CSceneObjct::USE_MAX); }
	
	for (int nCntObj = 0; nCntObj < 3; nCntObj++)
	{
		fRot += D3DX_PI * 0.1f;
		for (int nCount = 0; nCount < 4; nCount++)
		{
			if (SceneCreate(pObject, MODEL_PRIORITY))
			{//オブジェの設置
				pObject->Set(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 400.0f,
					D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), model, true, CSceneObjct::USE_MAX);
			}
			if (nCntObj == 1)
			{//敵の設置
				SetEnemy(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 300.0f,
					D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), CMotion::TYPE_BOX_Stick, CEnemy::TYPE_NONE);
			}
		}
	}
}
//==================================================================================================//
//    * ルームオブジェ中の作成 *
//==================================================================================================//
void CDungeon::SetObjRoom2(D3DXVECTOR3 pos, float fRot)
{
	CSceneObjct *pObject;
	CSceneModel::MODEL model = ((CSceneModel::MODEL)(CSceneModel::MODEL_STEEL));

	if (SceneCreate(pObject, MODEL_PRIORITY)) { pObject->Set(pos, D3DXVECTOR3(0.0f, (rand() % 628) * 0.01f, 0.0f), CSceneModel::MODEL_STEEL_B, true, CSceneObjct::USE_MAX); }

	for (int nCntObj = 0; nCntObj < 3; nCntObj++)
	{
		fRot += D3DX_PI * 0.1f;
		for (int nCount = 0; nCount < 4; nCount++)
		{
			if (SceneCreate(pObject, MODEL_PRIORITY))
			{
				pObject->Set(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 400.0f,
					D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), model, true, CSceneObjct::USE_MAX);
			}
		}
	}

	for (int nCntObj = 0; nCntObj < 6; nCntObj++)
	{
		fRot += D3DX_PI * 0.05f;
		for (int nCount = 0; nCount < 4; nCount++)
		{
			if (SceneCreate(pObject, MODEL_PRIORITY))
			{
				pObject->Set(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 1100.0f,
					D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), CSceneModel::MODEL_STONE, true, CSceneObjct::USE_MAX);
			}
		}
	}
}
//==================================================================================================//
//    * ロードオブジェの作成 *
//==================================================================================================//
void CDungeon::SetObjRoad(D3DXVECTOR3 pos)
{
	CSceneObjct *pObject;
	float fRand = (rand() % 628) * 0.01f;
	if (SceneCreate(pObject, MODEL_PRIORITY))
	{
		pObject->Set(pos + D3DXVECTOR3(sinf(fRand), 0.0f, cosf(fRand)) * 30.0f,
			D3DXVECTOR3(0.0f, (rand() % 628) * 0.01f, 0.0f), CSceneModel::MODEL_STONE, true, CSceneObjct::USE_MAX);
	}
}
//==================================================================================================//
//    * エントランスオブジェの作成 *
//==================================================================================================//
void CDungeon::SetObjEntrance(D3DXVECTOR3 pos)
{

}