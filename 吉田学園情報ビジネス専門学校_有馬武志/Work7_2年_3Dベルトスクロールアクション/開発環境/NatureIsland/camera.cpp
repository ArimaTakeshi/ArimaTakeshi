//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "game.h"
#include "title.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MOVE_CAMERA			(3.0f)			//カメラの移動量
#define MOVE_ANGLE			(0.01f)			//カメラ角度の移動量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CPlayer *CCamera::m_pPlayer = NULL;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//視点の初期値
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//向き
	m_fAngle = 0.0f;
	m_fCameraAngle = 45.0f;								//角度
	m_CameraCount = 0;									//カメラの数初期化
	m_fRot = 0;											//カメラの向き初期化
	m_fLength = m_posV.z - m_posR.z;					//長さの計算　（VのｚからRのｚをひく）
	m_nType = CAMERA_TYPE_NONE;							//種類
	m_nCntTitle = 0;
	m_bReset = false;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CCamera::~CCamera()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCamera::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);		//視点の初期値
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き

	m_fLength = m_posV.z - m_posR.z;					//長さの計算　（VのｚからRのｚをひく）
	m_fRange = m_posV.y - m_posR.y;						//長さの計算　（VのｚからRのｚをひく）
	m_nCntTitle = 0;
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CCamera::Uninit(void)
{

}
//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	CManager::MODE pMode = CManager::GetMode();

	if (pMode == CManager::MODE_TITLE)
	{
		CTitle::TYPE pTitleType = CTitle::GetType();

		if (m_bReset == false)
		{
			m_posV = D3DXVECTOR3(0.0f, 300.0f, -550.0f);		//視点の初期値
			m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
			m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き
			m_bReset = true;
		}
		if (pTitleType == CTitle::TYPE_SKIP)
		{
			m_nCntTitle = 250;
		}
		m_nCntTitle++;
		if (m_nCntTitle >= 250)
		{
			//============================
			//     視点の右移動
			//============================
			m_posV.x += sinf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			//m_posRに代入
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;

			// 上
			m_posV.y += 0.5f;
			m_posR.y += 0.5f;
		}
		if (m_posV.x >= 10500.0f)
		{
			m_bReset = false;
		}
	}
	else if (pMode == CManager::MODE_GAME)
	{
		//プレイヤーのposを代入
		D3DXVECTOR3 PlayerPos = m_pPlayer->GetPos();
		D3DXVECTOR3 PlayerRot = m_pPlayer->GetRot();

#ifdef _DEBUG

		//============================
		//     視点の左右前後移動
		//============================
		if (pCInputKeyBoard->GetKeyboardPress(DIK_RIGHT) == true)//右矢印キーを押したとき
		{//右移動							　　　↓角度　　　　↓移動量
			m_posV.x += sinf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * 0.5f) + m_fAngle) * MOVE_CAMERA;
			//m_posRに代入
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_LEFT) == true)//左矢印キーを押したとき
		{//左移動									↓角度　　　↓移動量
			m_posV.x += sinf((D3DX_PI * -0.5f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * -0.5f) + m_fAngle) * MOVE_CAMERA;
			//m_posRに代入
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_UP) == true)//上矢印キーを押したとき
		{//前移動								  ↓角度　　　　↓移動量
			m_posV.x += sinf((D3DX_PI * 0.0f) + m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI * 0.0f) + m_fAngle) * MOVE_CAMERA;
			//m_posRに代入
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;

		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_DOWN) == true)//下矢印キーを押したとき
		{//後移動						  ↓角度　　　　↓移動量
			m_posV.x += sinf((D3DX_PI)+m_fAngle) * MOVE_CAMERA;
			m_posV.z += cosf((D3DX_PI)+m_fAngle) * MOVE_CAMERA;
			//m_posRに代入
			m_posR.x = m_posV.x - sinf(m_fAngle) * m_fLength;
			m_posR.z = m_posV.z - cosf(m_fAngle) * m_fLength;
		}
		//============================
		//        視点移動
		//============================
		if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD1) == true)
		{//Cキーを押したとき　　　↓角度の移動量
			m_fAngle += MOVE_ANGLE;
			if (m_fAngle > D3DX_PI)
			{//左周り
				m_fAngle = -D3DX_PI;
			}
			//g_Camera.posVにD3DXVECTOR3のsinとcosを代入
			m_posV = D3DXVECTOR3(m_posR.x + sinf(m_fAngle) * m_fLength, m_posV.y, m_posR.z + cosf(m_fAngle) * m_fLength);
		}
		if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD2) == true)
		{//Vキーを押したとき　　　↓角度の移動量
			m_fAngle -= MOVE_ANGLE;
			if (m_fAngle < -D3DX_PI)
			{//右周り
				m_fAngle = D3DX_PI;
			}
			//g_Camera.posVにD3DXVECTOR3のsinとcosを代入
			m_posV = D3DXVECTOR3(m_posR.x + sinf(m_fAngle) * m_fLength, m_posV.y, m_posR.z + cosf(m_fAngle) * m_fLength);
		}

		if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD7) == true)
		{//Vキーを押したとき　　　↓角度の移動量
			m_posV.y += 2.0f;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_NUMPAD8) == true)
		{//Vキーを押したとき　　　↓角度の移動量
			m_posV.y -= 2.0f;
		}
#endif

		//視点・注視点の更新
		m_posVDest.x = PlayerPos.x + sinf(m_rot.y) * m_fLength;
		m_posVDest.y = PlayerPos.y + m_fRange;
		m_posVDest.z = PlayerPos.z + cosf(m_rot.y) * m_fLength;

		m_posRDest.x = PlayerPos.x - sinf(PlayerRot.y) * 1.0f;
		m_posRDest.y = PlayerPos.y;
		m_posRDest.z = PlayerPos.z - cosf(PlayerRot.y) * 1.0f;

		m_posV.x += (m_posVDest.x - m_posV.x) * 0.3f;
		m_posV.y += (m_posVDest.y - m_posV.y) * 0.3f;
		m_posR += (m_posRDest - m_posR) * 0.3f;
		//移動のデバック用
		//CDebugProc::Print("カメラ操作方法 【↑　前移動】【←　左移動】【↓　後移動】【→　右移動】【NUM 1 左回転】【NUM 2　右回転】\n");
		//カメラのデバック位置
		//CDebugProc::Print("カメラposVの位置 :【%.1f】【%.1f】【%.1f】\n", m_posV.x, m_posV.y, m_posV.z);
		//CDebugProc::Print("カメラposRの位置 :【%.1f】【%.1f】【%.1f】\n", m_posR.x, m_posR.y, m_posR.z);
	}
	else if (pMode == CManager::MODE_RESULT || pMode == CManager::MODE_RANKING)
	{
#if 1
		m_posV = D3DXVECTOR3(0.0f, 50.0f, -550.0f);		//視点
		m_posR = D3DXVECTOR3(0.0f, 50.0f, 0.0f);				//注視点
#endif
	}
}
//=============================================================================
//　カメラの生成
//=============================================================================
void CCamera::SetCamera()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH
	(
		&m_mtxProjection,
		D3DXToRadian(m_fCameraAngle),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		10000
	);

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}
void CCamera::Delete(void)
{
	CCamera *pCamere = CManager::GetCamera();
	pCamere->m_posV = D3DXVECTOR3(0.0f, 300.0f, -500.0f);	//視点の初期値
	pCamere->m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//注視点の初期値
	pCamere->m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//法線の向き

	pCamere->m_fLength = pCamere->m_posV.z - pCamere->m_posR.z;					//長さの計算　（VのｚからRのｚをひく）
	pCamere->m_fRange = pCamere->m_posV.y - pCamere->m_posR.y;					//長さの計算　（VのｚからRのｚをひく）
	pCamere->m_nCntTitle = 0;
}