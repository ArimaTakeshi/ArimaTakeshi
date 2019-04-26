//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 杉本涼
//
//=============================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "ScenePlayer.h"
#include "dungeon.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		DISTANCE		(200)			//注視点と視点の距離
#define		CAMERA_MOVE		(0.8f)			//カメラの移動速度
#define		ROTPOOR_RY		(30)			//注視点上下 +下, -上
#define		ROTPOOR_VY		(50)				//カメラ本体 +上, -下

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CCamera::Info CCamera::m_info;			//カメラ情報
CCamera CCamera::camera;			//カメラ

//=============================================================================
// コンストラクタ
//=============================================================================
CCamera::CCamera(){}
//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera() {}
//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::Init(void)
{
	camera.m_nCntTime = 0;
	camera.m_nCntState = 0;
	camera.m_info.scene = SCENE_TYPE_NO;
	camera.m_info.state = STATE_GAME;
	camera.m_info.ViewC = VIEW_FOLLOW;
	camera.m_info.ViewS = SCENE_VIEW_NORMAL;

	camera.m_posV = D3DXVECTOR3(0.0f, 100.0f, 0.0f);					//視点
	camera.m_posR = D3DXVECTOR3(0.0f, 0.0f - ROTPOOR_RY, 0.1f);		//注視点
	camera.m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//ナニコレ(笑)
	camera.m_goal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//目的
	camera.m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);					//角度
	camera.m_addpos = D3DXVECTOR3(0.0f, ROTPOOR_VY, 0.0f);			//カメラ独立移動
	camera.m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//追従するカメラの場所
	camera.m_fDistance = DISTANCE;									//視点と注視点の距離

	camera.m_fGMagnification = 0.25f;
	camera.m_nCntModel = -1;

}

//=============================================================================
// カメラの終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Update(void)
{
	if (m_info.state == STATE_GAME)
	{
		//カメラの更新
		CScenePlayer *pPlayer = CManager::GetPlayer(0);
		bool		bMove = false;	//カメラ移動の有無
		if (pPlayer != NULL && CManager::GetDungeon() != NULL)
		{
			if (pPlayer->GetnStage() != BOSS_STAGE && CManager::GetDungeon()->GetShop() != 1 && CScenePlayer::GetbCamera())
			{//カメラを動かしてよいなら
				D3DXVECTOR3 posold = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
				D3DXVECTOR3 posC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				int			nNumPlayer = 0;
				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{//プレイヤー分回る
					pPlayer = CManager::GetPlayer(nCount);
					if (pPlayer != NULL)
					{//生成されているなら
						if (pPlayer->GetfLife()[0] > 0.0f)
						{//生きているなら
							posC += D3DXVECTOR3(pPlayer->GetPositionOld()[0].x, 20.0f, pPlayer->GetPositionOld()[0].z);
							posold.x += pPlayer->GetPositionOld()[0].x + sinf(pPlayer->GetRotationU()[0].y) * 10.0f;
							posold.z += pPlayer->GetPositionOld()[0].z + cosf(pPlayer->GetRotationU()[0].y) * 10.0f;
							bMove = true;
							nNumPlayer++;
						}
					}
				}
				if (bMove)
				{//プレイヤーが1人以上生存
					camera.m_posC = posC / (float)nNumPlayer;
					camera.m_posR += ((posold / (float)nNumPlayer) - camera.m_posR) * 0.1f;
					camera.m_posV = D3DXVECTOR3(camera.m_posR.x, camera.m_posV.y, camera.m_posR.z - 0.01f);
				}
			}
		}
	}
	else { UpdateScene(); }

	if (camera.m_rot.y > D3DX_PI) { camera.m_rot.y -= D3DX_PI * 2; }
	if (camera.m_rot.y < -D3DX_PI) { camera.m_rot.y += D3DX_PI * 2; }

	//if (g_camera.nCntModel > -1)
	//{//追従の場所の更新
	//	MODEL_INFO *model = GetModel_Info();
	//	g_camera.targetpos += (model[g_camera.nCntModel].set.pos + (model[g_camera.nCntModel].set.pos - model[g_camera.nCntModel].set.posold) * 10.0f - g_camera.targetpos) * 0.08f;
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y < -50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y - 50; }
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y > 50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y + 50; }
	//}
	//g_camera.posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + g_camera.targetpos + g_camera.addpos;	//見る場所 + 水平移動分

	//視点　自分 + (角度 * 距離) + 水平移動分
	//g_camera.goal = D3DXVECTOR3(
	//	g_camera.targetpos.x + (sinf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x),						//X軸
	//	g_camera.targetpos.y + sinf(g_camera.rot.x) * g_camera.fDistance + ROTPOOR_VY,									//Y軸
	//	g_camera.targetpos.z + (cosf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x)) + g_camera.addpos;	//Z軸

	//g_camera.posV += (g_camera.goal - g_camera.posV) * g_camera.fGMagnification;
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::Reset(void)
{
	//if (g_camera.nCntModel > -1)
	//{//追従の場所の更新
	//	MODEL_INFO *model = GetModel_Info();
	//	g_camera.targetpos += (model[g_camera.nCntModel].set.pos + (model[g_camera.nCntModel].set.pos - model[g_camera.nCntModel].set.posold) * 1.0f - g_camera.targetpos);
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y < -50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y - 50; }
	//	if (g_camera.targetpos.y - model[g_camera.nCntModel].set.pos.y > 50) { g_camera.targetpos.y = model[g_camera.nCntModel].set.pos.y + 50; }
	//}
	//g_camera.goal = D3DXVECTOR3(
	//	g_camera.targetpos.x + (sinf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x),						//X軸
	//	g_camera.targetpos.y + sinf(g_camera.rot.x) * g_camera.fDistance + ROTPOOR_VY,									//Y軸
	//	g_camera.targetpos.z + (cosf(g_camera.rot.y) * g_camera.fDistance) * cosf(g_camera.rot.x)) + g_camera.addpos;	//Z軸

	//g_camera.posV += (g_camera.goal - g_camera.posV) * 1.0f;
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	
	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&camera.m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&camera.m_mtxProjection,
		D3DXToRadian(15.0f),	//画角
		(float)SCREEN_WIDTH /
		(float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &camera.m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&camera.m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&camera.m_mtxView, &camera.m_posV, &camera.m_posR, &camera.m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &camera.m_mtxView);
}
//=============================================================================
// カメラの当たり判定処理
//=============================================================================
void CCamera::Collision(D3DXVECTOR3 *pos, float fLengthX, float fLengthZ)
{
	if (m_posC.x + 85.0f < pos->x) { pos->x = m_posC.x + 85.0f; }
	else if (m_posC.x - 85.0f > pos->x) { pos->x = m_posC.x - 85.0f; }
	if (m_posC.z + 45.0f < pos->z) { pos->z = m_posC.z + 45.0f; }
	else if (m_posC.z - 45.0f > pos->z) { pos->z = m_posC.z - 45.0f; }
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera::SetScene(SCENE_TYPE type)
{
	camera.m_nCntState = 0;
	camera.m_nCntTime = 0;
	camera.m_info.state = STATE_MOVIE;
	camera.m_info.scene = type;
}
//=============================================================================
// シーン再生処理
//=============================================================================
void CCamera::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//シーン再生
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//エラー処理用
			Init();
			camera.m_nCntModel = 0;
			break;

		case SCENE_TYPE_BOSS:	//ボス前
			//Scene_BOSS();
			break;
		}
	}
}
//=============================================================================
// カメラ情報取得処理
//=============================================================================
CCamera::Info *CCamera::GetCamera(void)
{
	return &m_info;
}
