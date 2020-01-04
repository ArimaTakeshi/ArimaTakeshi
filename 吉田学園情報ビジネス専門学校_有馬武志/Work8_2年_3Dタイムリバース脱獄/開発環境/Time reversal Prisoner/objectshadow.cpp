//=============================================================================
//
// オブジェクトの処理 [objectshadow.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "objectshadow.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "shadow.h"
#include "logo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_WALK			(0.2f)
#define MODEL_RAN			(1.0f)
#define MODEL_SQUAT			(0.1f)
#define MODEL_SNEAK			(0.1f)

#define MODEL_NAME_1	"data\\MODEL\\shadow001.x"			//読み込むテクスチャファイル

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(25)			// プレイヤーの幅調整用
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
LPD3DXMESH CObjectShadow::m_pMeshModel[MAX_OBJECTSHADOW] = {};						//メッシュ情報へのポインタ
LPD3DXBUFFER CObjectShadow::m_pBuffMatModel[MAX_OBJECTSHADOW] = {};					//マテリアルの情報へのポインタ
DWORD CObjectShadow::m_nNumMatModel[MAX_OBJECTSHADOW] = {};							//マテリアルの情報数
LPDIRECT3DTEXTURE9 CObjectShadow::m_pMeshTextures[MAX_OBJECTSHADOW_TEXTURE] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CObjectShadow::CObjectShadow() : CModel3D(OBJECTSHADOW_PRIOTITY,CScene::OBJTYPE_SHADOWMODEL)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStageCount = 0;
	m_bStageNext = false;
	m_pVtxBuff = NULL;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CObjectShadow::~CObjectShadow()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObjectShadow::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3DモデルのInit
	CModel3D::Init();
	
	// 位置の初期化
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//位置の代入
	CModel3D::SetPosition(pos);

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

	// 頂点情報を設定
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObjectShadow::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CLogo::UnLoad();

	//3DモデルのUninit
	CModel3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObjectShadow::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	//3DモデルのUpdate
	CModel3D::Update();
	//位置の初期化
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの代入
	D3DXVECTOR3 &rot = CModel3D::GetRot();
	// MOVETYPEの設定
	MOVETYPE MoveType = CModel3D::GetMoveType();
	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	CCamera *pCamera = CManager::GetCamera();

	//半径
	float fRadius = 10.0f;
	//円周
	float fCircumference = (((D3DX_PI * 2.0f) * fRadius));

	// 各種情報の代入
	if (CGame::GetPlayer() != NULL)
	{
		CModel3D::SetPosition(CGame::GetPlayer()->GetPos());
	}

	CModel3D::SetMove(move);
	CModel3D::SetMoveType(MoveType);
}
//=============================================================================
// 描画処理
//=============================================================================
void CObjectShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ステンシルテストを有効に
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//画面には描画しない
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0);		//デフォルトは0x0000000f

	//ステンシルバッファの設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);			//全員OK
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);		//ステンシルテストとZテスト合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);		//ステンシルテストが合格と不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);		//ステンシルテストが不合格
	
	//表面カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//影のモデル描画
	CModel3D::Draw();

	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						//対象と比較
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);		//1番目をキープ
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		//ステンシルテストとZテスト合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		//ステンシルテストが合格とZテスト不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);		//ステンシルテストが不合格
	
	//裏面カリング
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//影のモデル描画
	CModel3D::Draw();

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);		//デフォルトは0x0000000f

	//ステンシルを戻す
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						//対象と比較
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);		//全員OK
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		//ステンシルテストとZテスト合格
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		//ステンシルテストが合格とZテスト不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		//ステンシルテストが不合格

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ステンシルテストを無効に
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

}
//===============================================================================
//　クリエイト
//===============================================================================
CObjectShadow * CObjectShadow::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, float move, int nTexType,int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObjectShadow *pObject = NULL;

	// NULLチェック
	if (pObject == NULL)
	{// メモリの動的確保

		pObject = new CObjectShadow;

		if (pObject != NULL)
		{
			// 種類の設定
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// オブジェクトごとの設定用タイプ
			pObject->m_nType = nObjectType;
			// オブジェクトクラスの生成
			pObject->Init();
			// 位置を代入
			pObject->SetPosition(pos);
			// 回転を反映
			pObject->SetRot(rot);
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
HRESULT CObjectShadow::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;							

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[0], NULL, &m_nNumMatModel[0], &m_pMeshModel[0]);

	for (int nCount = 0; nCount < MAX_OBJECTSHADOW; nCount++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\.jpg", &m_pMeshTextures[0]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CObjectShadow::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_OBJECTSHADOW; nCount++)
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
	for (int nCntTex = 0; nCntTex < MAX_OBJECTSHADOW_TEXTURE; nCntTex++)
	{
		if (m_pMeshTextures[nCntTex] != NULL)
		{
			m_pMeshTextures[nCntTex]->Release();
			m_pMeshTextures[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//	ステージ移動時に初期化するため
//=============================================================================
void CObjectShadow::DeleteObject(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				pScene->Uninit();
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//===============================================================================
// 当たり判定
//===============================================================================
bool CObjectShadow::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;
	//あたっているかあたってないか
	bool bLand = false;
	//当たり判定の保存
	int nCollision = m_nCollision;
	//モードの情報
	CManager::MODE pMode = CManager::GetMode();
	//カメラの情報
	CCamera *pCamera = CManager::GetCamera();
	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	switch (m_nCollision)
	{
	case 1:

		// 各種情報の取得
		D3DXVECTOR3 Playerpos = *pPos;						// プレイヤーの初期位置
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// 位置
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();		// 移動量
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// 動きのタイプ
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();			// モデルの最大値
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();			// モデルの最小値

		D3DXVECTOR3 ModelMax = CModel3D::VtxMax();	// 位置込みの最大値
		D3DXVECTOR3 ModelMin = CModel3D::VtxMin();	// 位置込みの最小値

		//計算前用
		D3DXVECTOR3 WkMax = ModelMax;
		D3DXVECTOR3 WkMin = ModelMin;

		//角度
		D3DXVECTOR3 rot = CModel3D::GetRot();
		bool		bHit = false;

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

		//モデルの向きによって当たり判定のMAXとMINを変える
		if (rot.y == 1.57f)
		{//右向き
			ModelMin.z = WkMax.x * -1.0f;
			ModelMax.z = WkMin.x * -1.0f;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -1.57f)
		{
			ModelMax.z = WkMax.x;
			ModelMin.z = WkMin.x;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -3.14f || rot.y == 3.14f)
		{
			ModelMin.x = WkMax.x * -1.0f;
			ModelMax.x = WkMin.x * -1.0f;
			ModelMin.z = WkMax.z * -1.0f;
			ModelMax.z = WkMin.z * -1.0f;
		}
		ModelMax += ModelPos;
		ModelMin += ModelPos;

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
			}
		}

		if (pPos->y - PLAYER_HEIGHT <= ModelMax.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
		{// オブジェクト横との当たり判定
			if (pPos->x - PLAYER_DEPTH <= ModelMax.x && pPos->x + PLAYER_DEPTH >= ModelMin.x)
			{// オブジェクト横との当たり判定
				if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
				{//MAX 縦上
					pPos->z = ModelMax.z + PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
				{//MIN 縦下
					pPos->z = ModelMin.z - PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
			}
			if (pPos->z - PLAYER_DEPTH <= ModelMax.z && pPos->z + PLAYER_DEPTH >= ModelMin.z)
			{// オブジェクト横との当たり判定 
				if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
				{//MAX 横右
					pPos->x = ModelMax.x + PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
				{//MIN 横左
					pPos->x = ModelMin.x - PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
			}
		}


		if (m_nType == 2 && bHit == true)
		{// マップ移動時専用オブジェクト
			if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(59.0f, 146.0f, 568.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-199.0f, 0.0f, 140.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_3)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(905.0f, 190.0f, 540.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(635.0f, 0.0f, 680.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_4)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(470.0f, 240.0f, 660.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(845.0f, 0.0f, -160.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_5)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(-1040.0f, 170.0f, 400.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-740.0f, 0.0f, 280.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_6)
			{
				if (CFade::GetFade() == CFade::FADE_NONE)
				{//Pキーが押されたら
					//新規追加
					CManager::SetGameScore(CTime::GetTime());
					CManager::RankingScore(CTime::GetTime());

					//ステージ遷移の際のスキルキャンセル
					CPlayer::SetCancelStageNext(true);

					CGame::SetGameState(CGame::GAMESTATE_CLEAR);
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