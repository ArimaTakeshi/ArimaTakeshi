//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 杉本涼
//
//=============================================================================
#include "camera.h"
#include "mesh.h"
#include "SceneModel.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "light.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define		DISTANCE		(250)			//注視点と視点の距離
#define		CAMERA_MOVE		(0.8f)			//カメラの移動速度
#define		ROTPOOR_RY		(80)			//注視点上下 +下, -上
#define		ROTPOOR_VY		(80)				//カメラ本体 +上, -下

//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
CCamera_Manager::Info CCamera_Manager::m_info;			//カメラ情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera::Init(void)
{
	m_Type = CCamera::CAMERA_TYPE_OBJ;

	m_posV = D3DXVECTOR3(0.0f, 200.0f, 200.0f);				//視点
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.1f);				//注視点
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//ナニコレ(笑)
	m_rot = D3DXVECTOR3(D3DX_PI * 0.035f, D3DX_PI, 0.0f);	//角度
	m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//追従するカメラの場所
	m_fDistance = DISTANCE;									//視点と注視点の距離

	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	SetViewport(0, 0, 0, 0);
}
//=============================================================================
// カメラの描画処理
//=============================================================================
void CCamera::Draw(void)
{
	SetCamera(m_posV);
	//CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
	CScene::DrawObj(CManager::GetRenderer()->GetDevice());
}
//=============================================================================
// カメラのセット処理
//=============================================================================
void CCamera::SetCamera(D3DXVECTOR3 WKposV)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// ビューポートの設定
	pDevice->SetViewport(&m_viewport);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//画角
		(float)m_viewport.Width /
		(float)m_viewport.Height,
		10.0f,
		24800.0f);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView, &WKposV, &m_posR, &m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);

	CCamera_Manager::GetInfo().pCamera = this;
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "posV %.1f　%.1f　%.1f\n", WKposV.x, WKposV.y, WKposV.z);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "posR %.1f　%.1f　%.1f\n", m_posR.x, m_posR.y, m_posR.z);

}
//=============================================================================
// 3Dの描画処理落ち対策処理
//=============================================================================
bool CCamera::DrawCheck(D3DXVECTOR3 &pos, float fLength)
{//注視点から見て一定範囲内なら描画
	D3DXVECTOR3 WKpos = m_posV + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * fLength;
	float fAngle = atan2f(WKpos.x - pos.x, WKpos.z - pos.z) - m_rot.y;

	if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	if (fAngle >= -D3DX_PI * (DRAW_ANGLEP / 180) && fAngle <= +D3DX_PI * (DRAW_ANGLEP / 180))
	{//カメラの向き通りなら
		float fDistance = powf(m_posR.x - pos.x, 2) + powf(m_posR.z - pos.z, 2);
		if (fDistance < fLength + DRAW_DISTANCE) { return true; }
	}

	return false;
}
//=============================================================================
// 3Dの描画処理落ち対策処理
//=============================================================================
void CCamera::SetViewport(int left, int up, int right, int bottom)
{
	m_viewport.X = (DWORD)left;
	m_viewport.Y = (DWORD)up;
	m_viewport.Width = (DWORD)right;
	m_viewport.Height = (DWORD)bottom;
}

//=============================================================================
// カメラの初期化処理
//=============================================================================
void CCamera_Char::Init(void)
{
	CCamera::Init();
	m_pChar = NULL;
	m_pMove = NULL;
	m_fGMagnification = 0.1f;
	GetType() = CCamera::CAMERA_TYPE_CHAR;
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera_Char::Update(void)
{
	if (m_pChar != NULL && m_pMove != NULL)
	{//追従の場所の更新
		CInputKeyboard *pInputKey = CManager::GetInputKey();
		D3DXVECTOR3		&m_posV = GetposV();
		D3DXVECTOR3		&m_posR = GetposR();
		D3DXVECTOR3		&m_rot = GetRot();
		D3DXVECTOR3		&m_targetpos = Gettargetpos();
		float			&m_fDistance = GetfDistance();

		if (pInputKey->GetPress(DIK_U)) { m_rot.y += D3DX_PI * 0.0125f; }
		if (pInputKey->GetPress(DIK_O)) { m_rot.y -= D3DX_PI * 0.0125f; }
		if (pInputKey->GetPress(DIK_Y)) { m_rot.x += D3DX_PI * 0.0125f; }
		if (pInputKey->GetPress(DIK_H)) { m_rot.x -= D3DX_PI * 0.0125f; }
		if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
		if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 0.3f; }
		m_targetpos += (m_pChar[0] - m_targetpos) * 0.08f;

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos;	//見る場所 + 水平移動分
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//視点　自分 + (角度 * 距離) + 水平移動分
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X軸
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y軸
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z軸
		m_posV += (m_goal - m_posV) * m_fGMagnification;
		//m_posV.y = fY;
	}
}
//=============================================================================
// カメラの描画処理
//=============================================================================
void CCamera_Char::Draw(void)
{
	SetCamera();
	// バックバッファ＆Ｚバッファのクリア
	CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(150, 150, 150, 0), 1.0f, 0);
	CScene::Draw3D(CManager::GetRenderer()->GetDevice());
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera_Char::Reset(void)
{
	if (m_pChar != NULL)
	{//追従の場所の更新
		D3DXVECTOR3		&m_posV = GetposV();
		D3DXVECTOR3		&m_posR = GetposR();
		D3DXVECTOR3		&m_rot = GetRot();
		D3DXVECTOR3		&m_targetpos = Gettargetpos();
		float			&m_fDistance = GetfDistance();

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 1.0f; }
		m_targetpos = m_pChar[0];

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos;	//見る場所 + 水平移動分
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//視点　自分 + (角度 * 距離) + 水平移動分
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X軸
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y軸
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z軸
		m_posV += (m_goal - m_posV) * 1.0f;
	}

}
//=============================================================================
// カメラの設定処理
//=============================================================================
void CCamera_Char::SetCamera(void)
{
	D3DXVECTOR3		&m_posV = GetposV();
	D3DXVECTOR3		&m_posR = GetposR();
	D3DXVECTOR3		&m_vecU = GetvecU();
	D3DXVECTOR3		&m_rot = GetRot();
	D3DXVECTOR3		&m_targetpos = Gettargetpos();
	float			&m_fDistance = GetfDistance();

	D3DXVECTOR3 WKValue, WKmove;
	D3DXVECTOR3	WKlength = D3DXVECTOR3(1.0f, 10.0f, 1.0f);
	D3DXVECTOR3	WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	WKposV = m_posV;
	float		fDistance0, fDistance1;
	bool bWKJump = false;

	fDistance0 = powf(m_posV.x - m_posR.x, 2) + powf(m_posV.z - m_posR.z, 2);
	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
	WKmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int		nCount = 0;
	//CMesh::MeshCollisionCeiling(WKposV, WKValue, WKlength);
	CMesh::MeshCollisionWall(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	//CMesh::MeshCollisionField(WKposV, WKValue, WKmove, WKlength, WKnor, bWKJump);
	//WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * + 80.0f;
	//CSceneObjct::CollisionAll(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	fDistance1 = powf(WKposV.x - m_posR.x, 2) + powf(WKposV.z - m_posR.z, 2);
	WKposV.y = m_posR.y + (WKposV.y - m_posR.y) * ((fDistance1) / fDistance0);
	CCamera::SetCamera(WKposV);
}

//=============================================================================
// プレイヤーカメラの初期化処理
//=============================================================================
void CCamera_Play::Init(void)
{
	Create(m_pCamera_Obj);
	Create(m_pCamera_Char);
}
//=============================================================================
// プレイヤーカメラの終了処理
//=============================================================================
void CCamera_Play::Uninit(void)
{
	if (m_pCamera_Char != NULL) { delete m_pCamera_Char; }
	if (m_pCamera_Obj != NULL) { delete m_pCamera_Obj; }
}
//=============================================================================
// プレイヤーカメラの更新処理
//=============================================================================
void CCamera_Play::Update(void)
{
	if (m_pCamera_Char != NULL) { m_pCamera_Char->Update(); }
}
//=============================================================================
// プレイヤーカメラの描画処理
//=============================================================================
void CCamera_Play::Draw(void)
{
	if (m_pCamera_Char != NULL) { m_pCamera_Char->Draw(); }
	//if (m_pCamera_Obj != NULL) { m_pCamera_Obj->Draw(); }
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera_Manager::Init(void)
{
	m_pEvent = NULL;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_pPlay[nCount] = NULL;
	}

	CManager::GetCamera() = this;
}
//=============================================================================
// カメラ管理　全更新処理
//=============================================================================
void CCamera_Manager::Update(void)
{
	if (m_pEvent != NULL) { m_pEvent->Update(); }
	else
	{//イベントが更新中でないなら
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Update(); }
		}
	}
}
//=============================================================================
// カメラ管理(イベント)の終了処理
//=============================================================================
void CCamera_Manager::Uninit_Event(void)
{
	if (m_pEvent != NULL) { m_pEvent->Uninit(); m_pEvent = NULL; }
}
//=============================================================================
// カメラ管理の終了処理
//=============================================================================
void CCamera_Manager::Uninit(void)
{
	Uninit_Event();
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_pPlay[nCount] != NULL) 
		{ 
			//m_pPlay[nCount]->Uninit();
			delete m_pPlay[nCount];
			m_pPlay[nCount] = NULL;
		}
	}

	delete this;
	CManager::GetCamera() = NULL;
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera_Manager::Draw(void)
{
	if (m_pEvent != NULL) 
	{ 
		if (CManager::GetLight() != NULL) { CManager::GetLight()->Set(0); }
		m_pEvent->Draw(); 
	}
	else
	{//イベントが更新中でないなら
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (CManager::GetLight() != NULL) { CManager::GetLight()->Set(nCount + 1); }
			if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Draw(); }
		}
	}
}
//=============================================================================
// カメラの描画チェック処理
//=============================================================================
bool CCamera_Manager::DrawCheck(D3DXVECTOR3 &pos, float fLength)
{
	switch (m_info.pCamera->GetType())
	{
	case CCamera::CAMERA_TYPE_CHAR:
		//if (!m_info.pCamera->DrawCheck(pos, fLength)) { return false; };
		break;
	case CCamera::CAMERA_TYPE_EVENT:
	case CCamera::CAMERA_TYPE_OBJ: break;
	}
	return true;
}
//=============================================================================
// プレイヤーカメラ生成処理
//=============================================================================
CCamera_Play *&CCamera_Manager::Create_Play(int nCount)
{
	CCamera_Play *pPlay;
	CCamera_Manager *&pManager = CManager::GetCamera();

	if (pManager == NULL)
	{
		Create(pManager);
	}

	if (pManager->GetPlay(nCount) != NULL) { return pManager->GetPlay(nCount); }

	if (Create(pPlay))
	{//生成で来たらポインタを大枠に代入
		pPlay->GetChar()->GetnNumCamera() = nCount;
		pManager->GetPlay(nCount) = pPlay;
	}
	return pManager->GetPlay(nCount);
}
//=============================================================================
// プレイヤーカメラ生成処理
//=============================================================================
CCamera_Char *&CCamera_Manager::Create_Event(void)
{
	CCamera_Char *pChar;
	CCamera_Manager *&pManager = CManager::GetCamera();

	if (pManager == NULL)
	{
		Create(pManager);
	}

	if (pManager->GetEvent() != NULL) { return pManager->GetEvent(); }

	if (Create(pChar))
	{//生成で来たらポインタを大枠に代入
		pChar->GetType() = CCamera::CAMERA_TYPE_EVENT;
		pManager->GetEvent() = pChar;
	}
	return pManager->GetEvent();
}
//=============================================================================
// カメラの更新処理
//=============================================================================
void CCamera_Manager::SetScene(CCamera_Manager::SCENE_TYPE type)
{
	m_info.nCntState = 0;
	m_info.nCntTime = 0;
	m_info.state = STATE_MOVIE;
	m_info.scene = type;
}
//=============================================================================
// シーン再生処理
//=============================================================================
void CCamera_Manager::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//シーン再生
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//エラー処理用
			//Init();
			break;

		case SCENE_TYPE_BOSS:	//ボス前
			//Scene_BOSS();
			break;
		}
	}
}
