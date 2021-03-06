//=============================================================================
//
// 餌の処理 [feed.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "scene.h"
#include "feed.h"
#include "manager.h"
#include "object.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "shadow.h"
#include "tutorial.h"
#include "particle.h"
#include "scene3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_SPEED				(5.0f)
#define OBJCT_ANGLE_REVISION	(0.2f)		// 角度補正
#define EFFECT_HIGHT			(250.0f)	// エミッターの高さ
#define FOUNTAIN_UP				(20.0f)		// 噴水の上昇させる値
#define GET_TIME				(50)		// 餌の消えている時間
#define EFFECT_TIME				(30)		// エフェクトが出る時間

//更新範囲
#define FOUNTAIN_LENGTH			(15000)		//噴水の更新範囲
#define LEAF_LENGTH				(10500)		//葉の更新処理
#define WOOD_LENGTH				(8000)		//木をビルボードに入れ替える距離
#define FLOWER_LENGTH			(5500)		//花壇の描画範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
D3DXVECTOR3 CFeed::m_VtxMaxModel[FEEDTYPE_MAX] = {};
D3DXVECTOR3 CFeed::m_VtxMinModel[FEEDTYPE_MAX] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CFeed::CFeed() : CModel3D(FEED_PRIOTITY, CScene::OBJTYPE_FEED)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_feedType = FEEDTYPE::FEEDTYPE_ATTACK;
	m_nCntGetTimer = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CFeed::~CFeed() {}

//===============================================================================
//　生成
//===============================================================================
CFeed * CFeed::Create(D3DXVECTOR3 pos, int nZone, int nType)
{
	CFeed *pFeed = NULL;
	D3DXCOLOR col;

	// NULLチェック
	if (pFeed == NULL)
	{// メモリの動的確保

		pFeed = new CFeed;

		if (pFeed != NULL)
		{
			// モデルの設定
			pFeed->SetModelType(nType + MODEL_TYPE_FEED_K);
			// テクスチャの設定
			pFeed->SetTextureType(nType + TEXTURE_TYPE_FEED_K);
			//種類の代入
			pFeed->m_feedType = (FEEDTYPE)nType;
			// オブジェクトクラスの生成
			pFeed->Init();
			// 位置を代入
			pFeed->SetPosition(pos);

			pFeed->m_pPin = C3DPolygon::Create(C3DPolygon::TYPE_Pin, pos, INIT_VECTOR, 5);
			pFeed->m_pLight = C3DAnim::Create(C3DPolygon::TYPE_Light, pos, INIT_VECTOR, 5);
			switch (nType)
			{
			case FEEDTYPE_ATTACK:	col = D3DXCOLOR(1.0f, 0.1f, 0.03f, 1.0f);	break;
			case FEEDTYPE_ANNOY:	col = D3DXCOLOR(0.0f, 0.368f, 1.0f, 1.0f);	break;
			case FEEDTYPE_SPEED:	col = D3DXCOLOR(1.0f, 0.98f, 0.02f, 1.0f);	break;
			}
			if (pFeed->m_pPin != NULL) { pFeed->m_pPin->SetColor(col); }
			if (pFeed->m_pLight != NULL) { pFeed->m_pLight->SetColor(col); }
		}
	}

	return pFeed;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFeed::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3DモデルのInit
	CModel3D::Init();

	// 位置の初期化
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_feedType)
	{
	case FEEDTYPE::FEEDTYPE_ATTACK:	m_rot.x = 0.7f;	break;
	case FEEDTYPE::FEEDTYPE_ANNOY:	break;
	case FEEDTYPE::FEEDTYPE_SPEED:	m_rot.x = -0.7f; break;
	}

	//位置の代入
	CModel3D::SetPosition(pos);

	//変数の初期化
	m_bGet = true;
	m_bEffect = false;
	m_nCntGetTimer = 0;
	m_nCntEffectTimer = 0;
	m_pPin = NULL;
	m_pLight = NULL;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFeed::Uninit(void)
{
	//if (m_pPin != NULL) { m_pPin->Uninit(); m_pPin = NULL; }
	//if (m_pLight != NULL) { m_pLight->Uninit(); m_pLight = NULL; }

	//3DモデルのUninit
	CModel3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CFeed::Update(void)
{
	D3DXVECTOR3 pos = CModel3D::GetPosition();

	CModel3D::Update();

	m_rot.y += 0.007f;

	if (m_bGet == false)
	{// 取れないとき
		m_nCntGetTimer++;

		if (m_nCntGetTimer > GET_TIME)
		{
			if (m_pLight != NULL) { m_pLight->GetDrawType() = C2D::DRAW_TYPE_ADD; }
			m_bGet = true;
			m_nCntGetTimer = 0;
		}
		if (m_nCntGetTimer > GET_TIME - 15)
		{
			if (m_bEffect == false)
			{
				m_bEffect = true;
			}
		}
	}

	if (m_bEffect == true)
	{// エフェクトを出す
		if (m_nCntEffectTimer < EFFECT_TIME)
		{
			if (m_nCntEffectTimer % 5 == 0)
			{
				D3DXVECTOR2 fSize;

				fSize.x = 15.0f + (float)(CServer::Rand() % 3);
				fSize.y = 15.0f + (float)(CServer::Rand() % 3);

				CParticle::Create(D3DXVECTOR3(pos.x, pos.y - 10.0f, pos.z),
					D3DXVECTOR3(sinf((CServer::Rand() % 628) / 100.0f) * ((CServer::Rand() % 2 + 1)), 0.0f, cosf((CServer::Rand() % 628) / 100.0f) * ((CServer::Rand() % 2 + 1))),
					D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
					fSize,
					20,
					CParticle::TEXTURE_SMOKE,
					CParticle::TYPE_TURN,
					0);
			}
			m_nCntEffectTimer++;
		}
		else if (m_nCntEffectTimer >= EFFECT_TIME)
		{
			m_nCntEffectTimer = 0;
			m_bEffect = false;
		}

	}


	CModel3D::SetPosition(pos);
	CModel3D::SetRot(m_rot);
}
//=============================================================================
// 描画処理
//=============================================================================
void CFeed::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//位置の初期化
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//頂点法線の自動正規化
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	if (m_bGet == true)
	{
		//描画処理
		CModel3D::Draw();
	}


	//頂点法線の自動正規化
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CFeed::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	int			nNumVtx = 0;						//頂点数
	DWORD		sizeFVF;							//頂点フォーマットのサイズ
	BYTE		*pVtxBuff;							//頂点バッファへのポインタ

													//モデルの最大値・最小値を取得する
	for (int nCntModel = 0; nCntModel < FEEDTYPE_MAX; nCntModel++)
	{
		m_VtxMaxModel[nCntModel] = D3DXVECTOR3(-10000, -10000, -10000);	//最大値
		m_VtxMinModel[nCntModel] = D3DXVECTOR3(10000, 10000, 10000);	//最小値

		CModel3D::MODEL_TYPE type;
		switch (nCntModel)
		{
		case FEEDTYPE_ATTACK:	type = MODEL_TYPE_FEED_K;	break;
		case FEEDTYPE_ANNOY:	type = MODEL_TYPE_FEED_B;	break;
		case FEEDTYPE_SPEED:	type = MODEL_TYPE_FEED_S;	break;
		}

		LPD3DXMESH &Mesh = MeshLoad(type);

		if (Mesh != NULL)
		{
			//頂点数を取得
			nNumVtx = Mesh->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(Mesh->GetFVF());

			//頂点バッファのロック
			Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

																//最大値
				if (vtx.x > m_VtxMaxModel[nCntModel].x)
				{
					m_VtxMaxModel[nCntModel].x = vtx.x;
				}
				if (vtx.y > m_VtxMaxModel[nCntModel].y)
				{
					m_VtxMaxModel[nCntModel].y = vtx.y;
				}
				if (vtx.z > m_VtxMaxModel[nCntModel].z)
				{
					m_VtxMaxModel[nCntModel].z = vtx.z;
				}
				//最小値
				if (vtx.x < m_VtxMinModel[nCntModel].x)
				{
					m_VtxMinModel[nCntModel].x = vtx.x;
				}
				if (vtx.y < m_VtxMinModel[nCntModel].y)
				{
					m_VtxMinModel[nCntModel].y = vtx.y;
				}
				if (vtx.z < m_VtxMinModel[nCntModel].z)
				{
					m_VtxMinModel[nCntModel].z = vtx.z;
				}

				//サイズ文のポインタを進める
				pVtxBuff += sizeFVF;
			}

			//頂点バッファのアンロック
			Mesh->UnlockVertexBuffer();
		}
	}

	return S_OK;
}

//===============================================================================
// テクスチャの破棄
//===============================================================================
void CFeed::UnLoad(void)
{

}


//===============================================================================
// 当たり判定
//===============================================================================
bool CFeed::CollisionFeed(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld)
{
	//あたっているかあたってないか
	bool bHit = false;

	if (m_bGet == false) { return bHit; }

	// 各種情報の取得
	D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// 位置
	D3DXVECTOR3 VtxMax = m_VtxMaxModel[m_feedType];			// モデルの最大値
	D3DXVECTOR3 VtxMin = m_VtxMinModel[m_feedType];			// モデルの最小値
	D3DXVECTOR3 rot = CModel3D::GetRot();

	D3DXVECTOR3 ModelMax = ModelPos + VtxMax;	// 位置込みの最大値
	D3DXVECTOR3 ModelMin = ModelPos + VtxMin;	// 位置込みの最小値

	if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
	{// Zの範囲内にいる
		if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
		{// Xの範囲内にいる
			if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
			{// オブジェクトの上から当たる場合
				bHit = true;
				m_bGet = false;
				if (m_pLight != NULL) { m_pLight->GetDrawType() = C2D::DRAW_TYPE_NO; }
			}
			else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
			{// オブジェクトの下から当たる場合
				bHit = true;
				m_bGet = false;
				if (m_pLight != NULL) { m_pLight->GetDrawType() = C2D::DRAW_TYPE_NO; }
			}

			if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
			{// オブジェクト横との当たり判定
				bHit = true;
				m_bGet = false;
				if (m_pLight != NULL) { m_pLight->GetDrawType() = C2D::DRAW_TYPE_NO; }
			}
		}
	}

	// 位置の代入
	CModel3D::SetPosition(ModelPos);

	return bHit;
}
//===============================================================================
// 当たり判定
//===============================================================================
bool CFeed::TargetFeed(CPlayer *pPlayer, float &fValue)
{
	if (m_bGet == false) { return false; }

	D3DXVECTOR3 &m_pos = GetposR();
	D3DXVECTOR3 &pos = pPlayer->Getpos();

	float fDis = sqrtf(powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2));
	if (fDis < 500.0f)
	{//距離チェック
		if (pPlayer->GetItemNum() < MAX_EGG)
		{//アイテムの当たり判定
			if (CollisionFeed(&pos, &pPlayer->Getposold())) { return true; }
		}

		if (pPlayer->GetInduction() < CPlayer::INDUCTION_ITEM || fDis <= 100.0f) { return false; }
		float fRot = atan2f(m_pos.x - pos.x, m_pos.z - pos.z);
		float &fRotY = pPlayer->Getrot().y;
		float fWK;
		fWK = fRot - fRotY;
		if (fWK < 0.0f) { fWK *= -1.0f; }

		if (fWK < D3DX_PI * 0.05f)
		{//角度チェック
			if (fValue > fWK && pPlayer->GetFeedType() != m_feedType)
			{//餌誘導
				fValue = fWK;
				pPlayer->GetfFeedRot() = fRot;
				pPlayer->GetInduction() = CPlayer::INDUCTION_ITEM;
			}
		}
	}
	return false;
}