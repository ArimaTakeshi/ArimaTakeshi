//=============================================================================
//
// オブジェクトの処理 [object.cpp]
// Author : 有馬武志 ＆　小松　啓祐
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "object.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME_1	"data\\MODEL\\floor.x"			//読み込むテクスチャファイル
#define MODEL_NAME_2	"data\\MODEL\\Balloon.x"		//読み込むテクスチャファイル
#define MODEL_NAME_3	"data\\MODEL\\rock.x"			//読み込むテクスチャファイル
#define MODEL_NAME_4	"data\\MODEL\\TreeU.x"			//読み込むテクスチャファイル
#define MODEL_NAME_5	"data\\MODEL\\TreeD.x"			//読み込むテクスチャファイル
#define MODEL_NAME_6	"data\\MODEL\\wood.x"			//読み込むテクスチャファイル
#define MODEL_NAME_7	"data\\MODEL\\StumpVer.x"		//読み込むテクスチャファイル
#define MODEL_NAME_8	"data\\MODEL\\StumpHor.x"		//読み込むテクスチャファイル
#define MODEL_NAME_9	"data\\MODEL\\StumpMoveHor.x"	//読み込むテクスチャファイル
#define MODEL_NAME_10	"data\\MODEL\\WoodPlanks.x"		//読み込むテクスチャファイル
#define MODEL_NAME_11	"data\\MODEL\\log.x"			//読み込むテクスチャファイル
#define MODEL_NAME_12	"data\\MODEL\\grass.x"			//読み込むテクスチャファイル
#define MODEL_NAME_13	"data\\MODEL\\yazirusi.x"		//読み込むテクスチャファイル
#define MODEL_NAME_14	"data\\MODEL\\house.x"			//読み込むテクスチャファイル

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(10)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(100.0f)		// プレイヤーの背の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH CObject::m_pMeshModel[MAX_OBJECT] = {};						//メッシュ情報へのポインタ
LPD3DXBUFFER CObject::m_pBuffMatModel[MAX_OBJECT] = {};					//マテリアルの情報へのポインタ
DWORD CObject::m_nNumMatModel[MAX_OBJECT] = {};							//マテリアルの情報数
LPDIRECT3DTEXTURE9 CObject::m_pMeshTextures[MAX_OBJECT_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CObject::CObject() : CModel3D(OBJECT_PRIOTITY,CScene::OBJTYPE_OBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//===============================================================================
//　デストラクタ
//===============================================================================
CObject::~CObject()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3DモデルのInit
	CModel3D::Init();
	
	// 位置の初期化
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//位置の代入
	CModel3D::SetPosition(pos);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject::Uninit(void)
{
	//3DモデルのUninit
	CModel3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//3DモデルのUpdate
	CModel3D::Update();

	//位置の初期化
	D3DXVECTOR3 pos = CModel3D::GetPosition();

	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向きの代入
	D3DXVECTOR3 rot = CModel3D::GetRot();

	// MOVETYPEの設定
	MOVETYPE MoveType = CModel3D::GetMoveType();

	switch (MoveType)
	{
	case MOVETYPE_X_MOVE:
		// X軸移動
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Y_MOVE:
		// Y軸移動
		if (m_nCount <= 120)
		{
			move.y += m_move.y;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.y -= m_move.y;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Z_MOVE:
		// Z軸移動
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		break;

	case MOVETYPE_ROTATION_X:
		// X軸で回転しながらZ軸移動
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.x += 0.1f;
		//rot.z += 0.01f;

		CModel3D::SetRot(rot);
		break;

	case MOVETYPE_ROTATION_Z:
		// Z軸で回転しながらX軸移動
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		//rot.x += 0.01f;
		rot.z += 0.1f;

		CModel3D::SetRot(rot);
		break;
	}


	//モデルのデバック位置
	//CDebugProc::Print("オブジェクトposの位置 :【%.1f】【%.1f】【%.1f】\n", pos.x, pos.y, pos.z);

	// 移動量の代入
	pos += move;

	// 各種情報の代入
	CModel3D::SetPosition(pos);
	CModel3D::SetMove(move);
	CModel3D::SetMoveType(MoveType);
}
//=============================================================================
// 描画処理
//=============================================================================
void CObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//位置の初期化
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//近くのモデル以外を消す
	if (Modelpos.x + 1450.0f >= PlayerPos.x && Modelpos.x - 1300.0f <= PlayerPos.x && pMode == CManager::MODE_GAME)
	{
		//3DモデルのDraw
		CModel3D::Draw();
	}
	else if (pMode != CManager::MODE_GAME)
	{
		CModel3D::Draw();
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos, float move, int nTexType,int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObject *pObject = NULL;

	// NULLチェック
	if (pObject == NULL)
	{// メモリの動的確保

		pObject = new CObject;

		if (pObject != NULL)
		{
			// 種類の設定
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// オブジェクトクラスの生成
			pObject->Init();
			// オブジェクトごとの設定用タイプ
			pObject->m_nType = nObjectType;
			// 位置を代入
			pObject->SetPosition(pos);
			// 動きの種類と移動量を設定
			pObject->SetMoveType(nMovetype);
			pObject->m_move = D3DXVECTOR3(move, move, move);
			// コリジョンをONOFF
			pObject->m_nCollision = nCollision;
		}
	}

	return pObject;
}
//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[0], NULL, &m_nNumMatModel[0], &m_pMeshModel[0]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_2, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[1], NULL, &m_nNumMatModel[1], &m_pMeshModel[1]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_3, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[2], NULL, &m_nNumMatModel[2], &m_pMeshModel[2]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_4, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[3], NULL, &m_nNumMatModel[3], &m_pMeshModel[3]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_5, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[4], NULL, &m_nNumMatModel[4], &m_pMeshModel[4]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_6, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[5], NULL, &m_nNumMatModel[5], &m_pMeshModel[5]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_7, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[6], NULL, &m_nNumMatModel[6], &m_pMeshModel[6]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_8, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[7], NULL, &m_nNumMatModel[7], &m_pMeshModel[7]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_9, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[8], NULL, &m_nNumMatModel[8], &m_pMeshModel[8]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_10, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[9], NULL, &m_nNumMatModel[9], &m_pMeshModel[9]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_11, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[10], NULL, &m_nNumMatModel[10], &m_pMeshModel[10]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_12, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[11], NULL, &m_nNumMatModel[11], &m_pMeshModel[11]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_13, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[12], NULL, &m_nNumMatModel[12], &m_pMeshModel[12]);
	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_14, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[13], NULL, &m_nNumMatModel[13], &m_pMeshModel[13]);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\ita.jpg",&m_pMeshTextures[0]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\rock_000.jpg",&m_pMeshTextures[1]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\葉っぱ.jpg", &m_pMeshTextures[2]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bark-texture.jpg", &m_pMeshTextures[3]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\scarp06.jpg", &m_pMeshTextures[4]);
	//テクスチャなし
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\.jpg", &m_pMeshTextures[5]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\stump_belt.jpg", &m_pMeshTextures[6]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\WoodPlanks.jpg", &m_pMeshTextures[7]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\grass.png", &m_pMeshTextures[8]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi.jpg", &m_pMeshTextures[9]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_yoko.jpg", &m_pMeshTextures[10]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_tobu.jpg", &m_pMeshTextures[11]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_mizu.jpg", &m_pMeshTextures[12]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_ue.jpg", &m_pMeshTextures[13]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\yazirusi_kaze.jpg", &m_pMeshTextures[14]);
	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\window_close.jpg", &m_pMeshTextures[15]);
	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CObject::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// メッシュの開放
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
	//テクスチャ
	for (int nCntTex = 0; nCntTex < MAX_OBJECT_TEXTURE; nCntTex++)
	{
		if (m_pMeshTextures[nCntTex] != NULL)
		{
			m_pMeshTextures[nCntTex]->Release();
			m_pMeshTextures[nCntTex] = NULL;
		}
	}
}
//===============================================================================
// 当たり判定
//===============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//あたっているかあたってないか
	bool bLand = false;
	int nCollision = m_nCollision;
	CManager::MODE pMode = CManager::GetMode();

	switch (m_nCollision)
	{
	case 1:

		// 各種情報の取得
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();	// 位置
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();	// 移動量
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// 動きのタイプ
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();	// モデルの最大値
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();	// モデルの最小値

		D3DXVECTOR3 ModelMax = CModel3D::GetPosition() + CModel3D::VtxMax();	// 位置込みの最大値
		D3DXVECTOR3 ModelMin = CModel3D::GetPosition() + CModel3D::VtxMin();	// 位置込みの最小値

		// 移動量の保持
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Zの範囲内にいる		
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// Xの範囲内にいる
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// オブジェクトの上から当たる場合
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X移動同期
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z移動同期
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// オブジェクトの下から当たる場合
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}

				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{// オブジェクト横との当たり判定
					//CDebugProc::Print("モデルの右側 : %.1f\n", ModelMax.x);
					//CDebugProc::Print("モデルの左側 : %.1f\n", ModelMin.x);
					//CDebugProc::Print("モデルの奥側 : %.1f\n", ModelMax.z);
					//CDebugProc::Print("モデルの手前側 : %.1f\n", ModelMin.z);
					//CDebugProc::Print("モデルの頂点側 : %.1f\n", ModelMax.y);
					//CDebugProc::Print("モデルの足元側 : %.1f\n", ModelMin.y);

					if (ModelMoveType == MOVETYPE_X_MOVE || ModelMoveType == MOVETYPE_ROTATION_Z)
					{// X移動オブジェクト
						if (pPosOld->x - (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x) >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// 右から抜けた場合
							pPos->x = ModelMax.x + (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE 右\n");
						}
						else if (pPosOld->x + (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x) <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// 左から抜けた場合
							pPos->x = ModelMin.x - (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE 左\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// 奥から抜けた場合
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 奥\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// 手前から抜けた場合
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 手前\n");
						}
					}
					else if (ModelMoveType == MOVETYPE_Z_MOVE || ModelMoveType == MOVETYPE_ROTATION_X)
					{// Z移動オブジェクト
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// 右から抜けた場合
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 右\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// 左から抜けた場合
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 左\n");
						}

						if (pPosOld->z - (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z) >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// 奥から抜けた場合
							pPos->z = ModelMax.z + (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE 奥\n");
						}
						else if (pPosOld->z + (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z) <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// 手前から抜けた場合
							pPos->z = ModelMin.z - (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE 手前\n");
						}
					}
					else
					{// 無移動オブジェクト
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// 右から抜けた場合
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 右\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// 左から抜けた場合
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 左\n");

							if (pMode == CManager::MODE_GAME && ModelMoveType == MOVETYPE_HOUSE)
							{// ゴールの家に触れたら
								if (CFade::GetFade() == CFade::FADE_NONE)
								{//Pキーが押されたら
								 //新規追加
									CManager::SetGameScore(CTime::GetTime());
									CManager::RankingScore(CTime::GetTime());

									CFade::Create(CManager::MODE_RESULT);
								}
							}
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// 奥から抜けた場合
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 奥\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// 手前から抜けた場合
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 手前\n");
						}
					}
				}
			}
		}

		// 位置の代入
		CModel3D::SetPosition(ModelPos);
		// 移動量の代入
		m_ModelMove = ModelMove;

		break;
	}

	return bLand;
}