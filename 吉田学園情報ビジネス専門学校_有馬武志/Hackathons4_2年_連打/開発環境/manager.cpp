//=============================================================================
//
// マネージャー処理 [Manager.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "sound.h"

#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "ScenePlayer.h"
#include "SceneBullet.h"
#include "dungeon.h"
#include "player.h"

#include "renderer.h"
#include "manager.h"

#include "Title.h"
#include "Select.h"
#include "Game.h"
#include "vsSelect.h"
#include "Versus.h"
#include "Practice.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CRenderer		*CManager::m_pRenderer = NULL; 
CInputKeyboard	*CManager::m_pInputKey = NULL;
CInputJoyPad	*CManager::m_pJoyPad[JOYPAD_MAX] = {};
CScenePlayer	*CManager::m_pPlayer[MAX_PLAYER] = {};
CPlayer			*CManager::m_pPlayer0;
CDungeon		*CManager::m_pDungeon = NULL;
CManager::MODE	CManager::m_mode;
CManager::MODE	CManager::m_NextMode;
CFade			CManager::m_Fade;
CSound			*CManager::m_pSound = NULL;
int				CManager::m_nEndCount;

CTitle			*CManager::m_pTitle;
CSelect			*CManager::m_pSelect;
CGame			*CManager::m_pGame;
CvsSelect		*CManager::m_pvsSelect;
CVersus			*CManager::m_pVersus;
CPractice		*CManager::m_pPractice;		//ゲーム処理
//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager(void) 
{
	if (m_pRenderer == NULL)
	{//レンダラーの生成
		m_pRenderer = new CRenderer;
	}
	if (m_pInputKey == NULL)
	{//キーボードの生成
		m_pInputKey = new CInputKeyboard;
	}
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++)
	{//ジョイパッドの最大数回転
		if (m_pJoyPad[nCount] == NULL)
		{//ジョイパッドの生成
			m_pJoyPad[nCount] = new CInputJoyPad;
		}
	}

	// サウンドクラスの生成
	if (m_pSound == NULL)
	{
		m_pSound = new CSound;
	}

	m_nEndCount = -1;
	m_pTitle = NULL;
	m_pSelect = NULL;
	m_pGame = NULL;
	m_pPractice = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager(void) {}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT  CManager::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_pInputKey->Init(hInstance, hWnd);	//キーボード初期化
	m_pSound->Init(hWnd);
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++) { m_pJoyPad[nCount]->Init(); }

	CLight light; light.InitLight();
	CCamera::Init();

	m_mode = MODE_TITLE;
	m_NextMode = MODE_TITLE;
	SetMode();
	m_Fade.Init(CFade::STATE_OUT);
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CManager::Uninit(void)
{
	CScene::ReleaseAll();
	m_Fade.Uninit();
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++) { m_pJoyPad[nCount]->Uninit(); }

	if (m_pRenderer != NULL)
	{//レンダラーの削除
		m_pRenderer->UninitAll();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pInputKey != NULL)
	{//キーボードの削除
		m_pInputKey->Uninit();
		delete m_pInputKey;
		m_pInputKey = NULL;
	}
	if (m_pSound != NULL)
	{//サウンドの削除
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}
	delete this;

}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CManager::Update(void)
{
	m_pSound->CountUp();
	m_Fade.Update();
	CCamera::Update();
	m_pInputKey->Update();
	m_pInputKey->GetCount();
	for (int nCount = 0; nCount < JOYPAD_MAX; nCount++) { m_pJoyPad[nCount]->Update(); }

	CScene::UpdateAll();

	switch (m_mode)
	{//モード切替
	case MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Update(); }
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL) { m_pSelect->Update(); }
		break;
	case MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Update(); }
		break;
	case MODE_VS_SELECT:
		if (m_pvsSelect != NULL) { m_pvsSelect->Update(); }
		break;
	case MODE_VERSUS:
		if (m_pVersus != NULL) { m_pVersus->Update(); }
		break;
	case MODE_PRACTICE:
		if (m_pPractice != NULL) { m_pPractice->Update(); }
		break;
	}

	if (m_nEndCount >= 0)
	{
		m_nEndCount--;
		if (m_nEndCount == -1) { m_Fade.Init(CFade::STATE_NOR_FADE); }
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CManager::Draw(void)
{
	m_pRenderer->Draw();
}
//=============================================================================
// フェードセット処理
//=============================================================================
void CManager::SetFade(MODE mode, int nEndCount)
{
	if (m_nEndCount < 0)
	{
		m_NextMode = mode;
		m_nEndCount = nEndCount;
	}
}
//=============================================================================
//　モード切替
//=============================================================================
void CManager::SetMode(void)
{
	CScene::GetnCntStart() = 0;
	switch (m_mode)
	{//モード切替
	case MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Uninit(); delete m_pTitle; m_pTitle = NULL; }
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL) { m_pSelect->Uninit(); delete m_pSelect; m_pSelect = NULL; }
		break;
	case MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Uninit(); delete m_pGame; m_pGame = NULL; }
		break;
	case MODE_VS_SELECT:
		if (m_pvsSelect != NULL) { m_pvsSelect->Uninit(); delete m_pvsSelect; m_pvsSelect = NULL; }
		break;
	case MODE_VERSUS:
		if (m_pVersus != NULL) { m_pVersus->Uninit(); delete m_pVersus; m_pVersus = NULL; }
		break;
	case MODE_PRACTICE:
		if (m_pPractice != NULL) { m_pPractice->Uninit(); delete m_pPractice; m_pPractice = NULL; }
		break;
	}

	CScene::ReleaseAll();

	m_mode = m_NextMode;
	switch (m_mode)
	{//モード切替
	case MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Uninit(); delete m_pTitle; m_pTitle = NULL; }
		Create(m_pTitle);
		break;
	case MODE_SELECT:
		if (m_pSelect != NULL) { m_pSelect->Uninit(); delete m_pSelect; m_pSelect = NULL; }
		Create(m_pSelect);
		break;
	case MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Uninit(); delete m_pGame; m_pGame = NULL; }
		Create(m_pGame);
		break;
	case MODE_VS_SELECT:
		if (m_pvsSelect != NULL) { m_pvsSelect->Uninit(); delete m_pvsSelect; m_pvsSelect = NULL; }
		Create(m_pvsSelect);
		break;
	case MODE_VERSUS:
		if (m_pVersus != NULL) { m_pVersus->Uninit(); delete m_pVersus; m_pVersus = NULL; }
		Create(m_pVersus);
		break;
	case MODE_PRACTICE:
		if (m_pPractice != NULL) { m_pPractice->Uninit(); delete m_pPractice; m_pPractice = NULL; }
		Create(m_pPractice);
		break;
	}
}
//=============================================================================
//　ランダムで生存プレイヤー取得
//=============================================================================
CScenePlayer *&CManager::GetRandPlayer(void)
{
	//生存確認
	if (m_pPlayer[1] == NULL)
	{//2人生成されている
		return m_pPlayer[0];
	}
	else if (m_pPlayer[1]->GetfLife()[0] == 0.0f)
	{//2人目が死亡している
		return m_pPlayer[0];
	}
	else if (m_pPlayer[0]->GetfLife()[0] == 0.0f)
	{//1人目が死亡している
		return m_pPlayer[1];
	}

	//プレイヤーが全員生きている
	return m_pPlayer[rand() % MAX_PLAYER];
}
//=============================================================================
//　近くにいる生存プレイヤー取得
//=============================================================================
CScenePlayer *&CManager::GetNearPlayer(D3DXVECTOR3 pos)
{
	if (m_pPlayer[1] == NULL)
	{//2人生成されている
		return m_pPlayer[0];
	}
	else if (m_pPlayer[1]->GetfLife()[0] == 0.0f)
	{//2人目が死亡している
		return m_pPlayer[0];
	}
	else if (m_pPlayer[0]->GetfLife()[0] == 0.0f)
	{//1人目が死亡している
		return m_pPlayer[1];
	}

	//プレイヤーが全員生きている
	D3DXVECTOR3 pos0 = m_pPlayer[0]->GetPositionOld()[0], pos1 = m_pPlayer[1]->GetPositionOld()[0];

	//2人比較して小さいほうを返す
	if (powf(pos.x - pos0.x, 2) + powf(pos.z - pos0.z, 2) < powf(pos.x - pos1.x, 2) + powf(pos.z - pos1.z, 2))
	{
		return m_pPlayer[0];
	}
	else { return m_pPlayer[1]; }

	return m_pPlayer[0];
}
//=============================================================================
//　近くにいる生存プレイヤー取得
//=============================================================================
CScenePlayer *&CManager::GetNearPlayer(D3DXVECTOR3 pos, float &fDistance)
{
	if (m_pPlayer[1] == NULL)
	{//2人生成されている
		return m_pPlayer[0];
	}
	else if (m_pPlayer[1]->GetfLife()[0] == 0.0f)
	{//2人目が死亡している
		return m_pPlayer[0];
	}
	else if (m_pPlayer[0]->GetfLife()[0] == 0.0f)
	{//1人目が死亡している
		return m_pPlayer[1];
	}

	//プレイヤーが全員生きている
	D3DXVECTOR3 pos0 = m_pPlayer[0]->GetPositionOld()[0],
				pos1 = m_pPlayer[1]->GetPositionOld()[0];
	float		fDistance0 = (powf(pos.x - pos0.x, 2) + powf(pos.z - pos0.z, 2)),
				fDistance1 = powf(pos.x - pos1.x, 2) + powf(pos.z - pos1.z, 2);

	//2人比較して小さいほうを返す
	fDistance = powf(pos.x - pos0.x, 2) + powf(pos.z - pos0.z, 2);
	if (fDistance0 < fDistance1)
	{
		fDistance = fDistance0; 
		return m_pPlayer[0];
	}
	else 
	{ 
		fDistance = fDistance0; 
		return m_pPlayer[1];
	}

	return m_pPlayer[0];
}
