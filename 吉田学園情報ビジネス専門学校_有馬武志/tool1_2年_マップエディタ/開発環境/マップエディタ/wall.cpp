//=============================================================================
//
// 壁処理 [wall.cpp]
// Author : 有馬 武志
//
//=============================================================================
#include "wall.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "game.h"
#include "player.h"
#include "markwall.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define WALL_TEX_1	"data\\TEXTURE\\wall\\wall000.jpg"			// テクスチャの名前
#define WALL_TEX_2	"data\\TEXTURE\\wall\\wall001.jpg"			// テクスチャの名前
#define WALL_TEX_3	"data\\TEXTURE\\wall\\field03.jpg"			// テクスチャの名前
#define WALL_TEX_4	"data\\TEXTURE\\wall\\rock_003.jpg"			// テクスチャの名前
#define WALL_TEX_5	"data\\TEXTURE\\wall\\soil.jpg"				// テクスチャの名前
#define WALL_TEX_6	"data\\TEXTURE\\wall\\scarp02.jpg"			// テクスチャの名前
#define WALL_TEX_7	"data\\TEXTURE\\wall\\wallRock.jpg"			// テクスチャの名前
#define WALL_TEX_8	"data\\TEXTURE\\wall\\Black.jpg"			// テクスチャの名前
#define WALL_TEX_9	"data\\TEXTURE\\wall\\wall000.png"			// テクスチャの名前

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CWall::m_pTexture[MAX_WALL_TEX] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CWall::CWall() : CScene3D(WALL_PRIOTITY, CScene::OBJTYPE_WALL)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CWall::~CWall()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWall::Init()
{
	//初期化処理
	CScene3D::Init();

	//種類の設定
	SetTypeNumber(TYPE_WALL);

	if (m_nType == 9)
	{
		CScene3D::SetNor(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWall::Uninit(void)
{
	CScene3D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CWall::Update(void)
{
	CScene3D::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void CWall::Draw(void)
{
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//近くの壁以外を消す
	if (m_pos.x + 2000.0f >= PlayerPos.x && m_pos.x - 2000.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		//3DモデルのDraw
		CScene3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		CScene3D::Draw();
	}
}
//=============================================================================
// 生成処理
//=============================================================================
CWall * CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nTexType)
{
	CWall *pWall = NULL;

	//NULLチェック
	if (pWall == NULL)
	{//メモリの動的確保

		pWall = new CWall;

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
			//テクスチャの設定
			pWall->BindTexture(m_pTexture[nTexType]);
			//位置と回転とサイズ
			pWall->SetWall(pos, rot, size);

			//ファイル用
			pWall->m_fWidthDivide = size.x;
			pWall->m_fHightDivide = size.y;
			pWall->m_rot = rot;
			pWall->m_nTexType = nTexType;
		}
	}

	return pWall;
}
//=============================================================================
// 壁の当たり判定
//=============================================================================
void CWall::CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fDepth)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CScene *pScene;
	
	//プライオリティーチェック
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_WALL)
			{// posとrotを取得
				D3DXVECTOR3 WallPos = ((CScene3D*)pScene)->GetPosition();
				D3DXVECTOR3 WallRot = ((CScene3D*)pScene)->GetRotation();
				D3DXVECTOR2 WallSize = ((CScene3D*)pScene)->GetSize();

				if (WallRot.y == (0.0f * D3DX_PI))
				{// Z向きの壁
					if (pPos->x <= WallPos.x + WallSize.x + 18.5f
						&& pPos->x >= WallPos.x - WallSize.x - 18.5f)
					{// 壁と同じz軸に存在している
						if (pPos->z <= WallPos.z + WallSize.x + 18.5f
							&& pPos->z >= WallPos.z - WallSize.x - 18.5f)
						{// 壁と同じx軸に存在している
							if (pPos->y < WallPos.y + WallSize.y && pPos->y + 100.0f >= WallPos.y)
							{// 壁よりも低い
								if (pPos->z >= WallPos.z - fDepth
									&& pPosOld->z <= WallPos.z - fDepth)
								{// 手前から壁を貫通した
									pPos->z = WallPos.z - fDepth;
								}
								else if (pPos->z <= WallPos.z + fDepth
									&& pPosOld->z >= WallPos.z + fDepth)
								{// 奥から壁を貫通した
									pPos->z = WallPos.z + fDepth;
								}
							}
						}
					}
				}			
				else if (WallRot.y == (0.5f * D3DX_PI))
				{// X向きの壁
					if (pPos->x <= WallPos.x + WallSize.x + 18.5f
						&& pPos->x >= WallPos.x - WallSize.x - 18.5f)
					{// 壁と同じz軸に存在している
						if (pPos->z <= WallPos.z + WallSize.x + 18.5f
							&& pPos->z >= WallPos.z - WallSize.x - 18.5f)
						{// 壁と同じx軸に存在している
							if (pPos->y < WallPos.y + WallSize.y && pPos->y + 100.0f >= WallPos.y)
							{// 壁よりも低い
								if (pPos->x >= WallPos.x - fDepth
									&& pPosOld->x <= WallPos.x - fDepth)
								{// 手前から壁を貫通した
									pPos->x = WallPos.x - fDepth;
								}
								else if (pPos->x <= WallPos.x + fDepth
									&& pPosOld->x >= WallPos.x + fDepth)
								{// 奥から壁を貫通した
									pPos->x = WallPos.x + fDepth;
								}
							}
						}
					}
				}
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//=============================================================================
// 読み込み処理
//=============================================================================
HRESULT CWall::Load(void)
{
	// デバイス取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャ生成
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_4, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_5, &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_6, &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_7, &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_8, &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, WALL_TEX_9, &m_pTexture[8]);

	return S_OK;
}

//=============================================================================
// 開放処理
//=============================================================================
void CWall::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_WALL_TEX; nCount++)
	{
		// テクスチャ破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//===============================================================================
// ファイルにセーブ
//===============================================================================
void CWall::TextSave(void)
{
	int nMarkWall = CMarkWall::GetWallNum();

	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(WALL_PRIOTITY);

	//ファイルのポインタ
	FILE *pFile;

	//ファイル読み取り設定
	pFile = fopen(WALL_NAME, "wb");

	//プレイヤーのテキストデータの読み込み
	if (pFile != NULL)
	{
		//説明文
		fprintf(pFile, "#====================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#　マップの壁配置のエディタ [wall.txt]\n");
		fprintf(pFile, "#　制作者 : 有馬　武志\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#====================================================\n\n");
		//置いたオブジェクトの数
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#　壁の設置数\n");
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "WALL_SETNUM = ");
		fprintf(pFile, "%d\n\n", nMarkWall);
		//説明文
		fprintf(pFile, "#----------------------------------------------------\n");
		fprintf(pFile, "#　壁の設置情報\n");
		fprintf(pFile, "#----------------------------------------------------\n");

		//NULLチェック
		while (pScene != NULL)
		{
			//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
			CScene *pSceneNext = pScene->GetNext();

			if (pScene->GetDeath() == false)
			{
				//タイプがオブジェクトだったら
				if (pScene->GetObjType() == OBJTYPE_WALL)
				{
					//開始のための宣言
					fprintf(pFile, "WALL_START\n");
					//位置を入れる
					fprintf(pFile, "	POS = ");
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_pos.x);
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_pos.y);
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_pos.z);
					//回転を入れる
					fprintf(pFile, "	ROT = ");
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_rot.x);
					fprintf(pFile, "%.2f ", ((CWall*)pScene)->m_rot.y);
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_rot.z);
					//Xサイズを入れる
					fprintf(pFile, "	WIDTH = ");
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_fWidthDivide);
					//Yサイズを入れる
					fprintf(pFile, "	HIGHT = ");
					fprintf(pFile, "%.2f\n", ((CWall*)pScene)->m_fHightDivide);
					//テクスチャの種類を入れる
					fprintf(pFile, "	TEXTURE = ");
					fprintf(pFile, "%d\n", ((CWall*)pScene)->m_nTexType);
					//開始のための宣言
					fprintf(pFile, "WALL_END\n\n");
				}
			}

			//Nextに次のSceneを入れる
			pScene = pSceneNext;
		}

		//ファイルを閉じる
		fclose(pFile);
	}
}

