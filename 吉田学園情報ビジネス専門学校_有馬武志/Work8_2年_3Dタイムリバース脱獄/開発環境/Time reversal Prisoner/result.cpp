//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "result.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "serect.h"
#include "player.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"
#include "wall.h"
#include "ground.h"
#include "billboord.h"
#include "effect.h"
#include "item.h"
#include "shadow.h"
#include "report.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//リザルト
#define TEXT_OBJECTNAME			"data\\TEXT\\リザルトマップ\\objecy.txt"			// 読み込むテキストファイル
#define TEXT_MESHFIELDNAME		"data\\TEXT\\リザルトマップ\\meshfield.txt"			// 読み込むテキストファイル
#define TEXT_WALLNAME			"data\\TEXT\\リザルトマップ\\wall.txt"				// 読み込むテキストファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer		*CResult::m_pPlayer		= NULL;
CSerect		*CResult::m_pSerect		= NULL;
CBillBoord	*CResult::m_pBillBoord	= NULL;
CPolygon3D	*CResult::m_pPolygon3D	= NULL;
CMeshField	*CResult::m_pMeshField	= NULL;
CObject		*CResult::m_pObject		= NULL;
CModel		*CResult::m_pModel		= NULL;
CEffect		*CResult::m_pEffect		= NULL;
CWall		*CResult::m_pWall		= NULL;
CGround		*CResult::m_pGround		= NULL;
CItem		*CResult::m_pItem		= NULL;

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CResult::CResult()
{
	m_nCnt = 0;
	m_nSetCnt = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init()
{
	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//===================================
	//		 Loadの読み込み場所
	//===================================
	//フェードのテクスチャの読み込み
	CFade::Load();

	//報告のテクスチャの読み込み
	CReport::Load();

	//セレクトのテクスチャの読み込み
	m_pSerect->Load();

	//プレイヤーのテクスチャの読み込み
	m_pPlayer->Load();

	//メッシュフィールドのテクスチャの読み込み
	m_pMeshField->Load();

	//オブジェクトのテクスチャの読み込み
	m_pObject->Load();

	//地面のテクスチャの読み込み
	m_pGround->Load();

	//壁のテクスチャの読み込み
	m_pWall->Load();

	//影のテクスチャ読み込み
	m_pShadow->Load();

	//===================================
	//		 生成
	//===================================
	//セレクトの生成
	m_pSerect = CSerect::Create(0);

	//マップを読み込む
	WallTextLoad(1);
	TextLoad(1);
	MeshTextLoad(1);

	//プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(-150.0f, -4.0f,-3300.0f));

	for (int nCount = 0; nCount < m_nSetWallNum; nCount++)
	{
		//壁の生成		
		m_pWall = CWall::Create(m_aWall[nCount].m_pos, D3DXVECTOR2(m_aWall[nCount].m_fWidthDivide, m_aWall[nCount].m_fHightDivide), m_aWall[nCount].m_rot, m_aWall[nCount].m_nTexType);
	}
	for (int nCount = 0; nCount < m_nSetObjectNum; nCount++)
	{
		//オブジェクトの生成		
		m_pObject = CObject::Create(m_Map[nCount].m_pos, m_Map[nCount].m_rot, 0.0f, m_Map[nCount].m_nTexType, m_Map[nCount].m_nType, CModel3D::MOVETYPE_NOT, m_Map[nCount].m_nCollision);
	}
	for (int nCount = 0; nCount < m_nSetMeshFieldNum; nCount++)
	{
		//フィールドの生成		
		m_pMeshField = CMeshField::Create(m_Mesh[nCount].m_pos, m_Mesh[nCount].m_nWidthDivide, m_Mesh[nCount].m_nDepthDivide, m_Mesh[nCount].m_fWidthLength, m_Mesh[nCount].m_fDepthLength, m_Mesh[nCount].m_fVtxHeight_No0, m_Mesh[nCount].m_fVtxHeight_No1, m_Mesh[nCount].m_fVtxHeight_No2, m_Mesh[nCount].m_fVtxHeight_No3, m_Mesh[nCount].m_nTexType, 0);
	}

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//===================================
	//	　　UnLoadの破棄する場所
	//===================================
	//メッシュフィールドテクスチャの破棄
	m_pMeshField->UnLoad();

	//フェードのテクスチャの破棄
	CFade::UnLoad();

	//報告のテクスチャの破棄
	CReport::UnLoad();

	//セレクトのテクスチャの破棄
	m_pSerect->UnLoad();

	//オブジェクトのテクスチャの破棄
	m_pObject->UnLoad();

	//プレイヤーのテクスチャの破棄
	m_pPlayer->UnLoad();

	//地面のテクスチャの破棄
	m_pGround->UnLoad();

	//壁のテクスチャの破棄
	m_pWall->UnLoad();

	//影のテクスチャ読み込み
	m_pShadow->UnLoad();

	//メッシュフィールドの破棄
	m_pMeshField->Uninit();
	m_pMeshField = NULL;

	//セレクトの削除
	if (m_pSerect != NULL)
	{
		m_pSerect->Uninit();
		m_pSerect = NULL;
	}

	//フェード以外を削除
	CScene::NotFadeReleseAll();
}
//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputMouse *pCInputMouse = CManager::GetInputMouse();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	//現在どんな状況か
	CGame::GAMESTATE GameStateNow = CGame::GetGameState();

	if (GameStateNow == CGame::GAMESTATE_OVER)
	{//ゲームオーバーした場合

	}
	else if (GameStateNow == CGame::GAMESTATE_CLEAR)
	{//ゲームクリアした場合
	 //文字を出す
		if (m_nSetCnt == 180)
		{
			CReport::Create(D3DXVECTOR3(140.0f, 170.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 0);

			//協調音
			//pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
		}
		else if (m_nSetCnt == 200)
		{
			CReport::Create(D3DXVECTOR3(310.0f, 170.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 1);

			//協調音
			//pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
		}
		else if (m_nSetCnt == 220)
		{
			CReport::Create(D3DXVECTOR3(480.0f, 170.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 2);

			//協調音
			//pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
		}
		else if (m_nSetCnt == 240)
		{
			CReport::Create(D3DXVECTOR3(650.0f, 170.0f, 0.0f), D3DXVECTOR2(290.0f, 320.0f), 3);

			//協調音
			//pSound->PlaySound(CSound::SOUND_LABEL_COOPERATION);
		}

		m_nSetCnt++;
	}


	if (m_nCnt == 600)
	{//9秒後に何もしてない場合戻る
		CFade::Create(CManager::MODE_TITLE);
	}

	m_nCnt++;
}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

}
//===============================================================================
// ファイルからロード
//===============================================================================
void CResult::TextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

						//どのステージを読み込むか
	int nStageLoadNumber = nLoadNumber;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_OBJECTNAME, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "OBJECT_SETNUM = ", strlen("OBJECT_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("OBJECT_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetObjectNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetObjectNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "OBJECT_START", strlen("OBJECT_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//種類のを読み込み
					if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Map[nCntObject].m_nType = atoi(pStrcur);
					}
					//種類のを読み込み
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURETYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Map[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//当たり判定を読み込み
					if (memcmp(pStrcur, "COLLISION = ", strlen("COLLISION = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("COLLISION = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Map[nCntObject].m_nCollision = atoi(pStrcur);
					}
					//POSを読み込み
					if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("POS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					//ROTを読み込み
					if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("ROT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_rot.x = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_rot.y = (float)atof(pStrcur);

						//文字数分進める
						pStrcur += nWord;
						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Map[nCntObject].m_rot.z = (float)atof(pStrcur);
					}
					else if (memcmp(pStrcur, "OBJECT_END", strlen("OBJECT_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}
}
//===============================================================================
// メッシュフィールドをファイルからロード
//===============================================================================
void CResult::MeshTextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

						//どのステージを読み込むか
	int nStageLoadNumber = nLoadNumber;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_MESHFIELDNAME, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "MESHFIELD_SETNUM = ", strlen("MESHFIELD_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("MESHFIELD_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetMeshFieldNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetMeshFieldNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "MESHFIELD_START", strlen("MESHFIELD_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//種類のを読み込み
					if (memcmp(pStrcur, "TEXTURETYPE = ", strlen("TEXTURETYPE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURETYPE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_nTexType = atoi(pStrcur);
					}
					//横の分割数を読み込み
					if (memcmp(pStrcur, "X_DIVIDE = ", strlen("X_DIVIDE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("X_DIVIDE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_nWidthDivide = atoi(pStrcur);
					}
					//縦の分割数を読み込み
					if (memcmp(pStrcur, "Z_DIVIDE = ", strlen("Z_DIVIDE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("Z_DIVIDE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_nDepthDivide = atoi(pStrcur);
					}
					//横の長さを読み込み
					if (memcmp(pStrcur, "X_LENGTH = ", strlen("X_LENGTH = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("X_LENGTH = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fWidthLength = (float)atoi(pStrcur);
					}
					//縦の長さを読み込み
					if (memcmp(pStrcur, "Z_LENGTH = ", strlen("Z_LENGTH = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("Z_LENGTH = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fDepthLength = (float)atoi(pStrcur);
					}
					//１頂点の高さ
					if (memcmp(pStrcur, "VTX0_HEIGHT = ", strlen("VTX0_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX0_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No0 = (float)atoi(pStrcur);
					}
					//２頂点の高さ
					if (memcmp(pStrcur, "VTX1_HEIGHT = ", strlen("VTX1_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX1_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No1 = (float)atoi(pStrcur);
					}
					//３頂点の高さ
					if (memcmp(pStrcur, "VTX2_HEIGHT = ", strlen("VTX2_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX2_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No2 = (float)atoi(pStrcur);
					}
					//４頂点の高さ
					if (memcmp(pStrcur, "VTX3_HEIGHT = ", strlen("VTX3_HEIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("VTX3_HEIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_Mesh[nCntObject].m_fVtxHeight_No3 = (float)atoi(pStrcur);
					}
					//POSを読み込み
					if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("POS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Mesh[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Mesh[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_Mesh[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					else if (memcmp(pStrcur, "MESHFIELD_END", strlen("MESHFIELD_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}
}
//===============================================================================
// 壁をファイルからロード
//===============================================================================
void CResult::WallTextLoad(int nLoadNumber)
{
	//ファイル用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	//どのステージを読み込むか
	int nStageLoadNumber = nLoadNumber;

	//ファイルを開く 読み込み
	pFile = fopen(TEXT_WALLNAME, "r");

	//NULLチェック
	if (pFile != NULL)
	{
		//文字列の先頭を設定
		pStrcur = ReadLine(pFile, &aLine[0]);
		//文字列を取り出す
		strcpy(aStr, pStrcur);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStrcur, "WALL_SETNUM = ", strlen("WALL_SETNUM = ")) == 0)
		{
			//頭出し
			pStrcur += strlen("WALL_SETNUM = ");
			//文字列の先頭を設定
			strcpy(aStr, pStrcur);
			//文字列抜き出し
			m_nSetWallNum = atoi(pStrcur);
		}

		//オブジェクトの数分回す
		for (int nCntObject = 0; nCntObject < m_nSetWallNum; nCntObject++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "WALL_START", strlen("WALL_START")) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					//POSを読み込み
					if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("POS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_pos.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_pos.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_pos.z = (float)atof(pStrcur);

					}
					//ROTを読み込み
					if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("ROT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_rot.x = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_rot.y = (float)atof(pStrcur);
						//文字数分進める
						pStrcur += nWord;

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_rot.z = (float)atof(pStrcur);

					}
					//WIDTHを読み込み
					if (memcmp(pStrcur, "WIDTH = ", strlen("WIDTH = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("WIDTH = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_fWidthDivide = (float)atof(pStrcur);
					}
					//HIGHTを読み込み
					if (memcmp(pStrcur, "HIGHT = ", strlen("HIGHT = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("HIGHT = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_fHightDivide = (float)atof(pStrcur);
					}
					//HIGHTを読み込み
					if (memcmp(pStrcur, "TEXTURE = ", strlen("TEXTURE = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("TEXTURE = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						//文字数を返してもらう
						nWord = PopString(pStrcur, &aStr[0]);
						//文字列変換
						m_aWall[nCntObject].m_nTexType = (int)atof(pStrcur);
					}
					else if (memcmp(pStrcur, "WALL_END", strlen("WALL_END")) == 0)
					{
						break;
					}
				}
			}
		}
	}
}
//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CResult::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char *CResult::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CResult::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += (int)strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += (int)strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}
