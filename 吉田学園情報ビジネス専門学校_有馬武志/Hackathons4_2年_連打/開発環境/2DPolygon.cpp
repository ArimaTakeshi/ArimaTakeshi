//=============================================================================
//
// 2DPolygon処理 [2DPolygon.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "2DPolygon.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SLIDE_SPEED	(10.0f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	C2D::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*C2D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			case TEX_SCORE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/number000.png", &m_pTexture[tex]);					break;
			case TEX_PIcon:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/PIcon.png", &m_pTexture[tex]);						break;
			case TEX_Darkness:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/frameeffects003s.jpg", &m_pTexture[tex]);	break;
			case TEX_Cloud1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/pipo-fog018.jpg", &m_pTexture[tex]);			break;
			case TEX_Cloud2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/pipo-fog017.jpg", &m_pTexture[tex]);			break;
			case TEX_UI000:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/UI_000.png", &m_pTexture[tex]);						break;
			case TEX_UI001:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/UI_001.png", &m_pTexture[tex]);						break; 
			case TEX_Blood000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/blood.jpg", &m_pTexture[tex]);				break; 
			case TEX_BossLabel:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BOSS/Boss_Label.jpg", &m_pTexture[tex]);				break; 
			case TEX_Versus:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/VS.png", &m_pTexture[tex]);							break;
			case TEX_VsSelect:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/Window.png", &m_pTexture[tex]);					break;
			case TEX_Type:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/TYPE.png", &m_pTexture[tex]);					break; 
			case TEX_Stage:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/Stage000.jpg", &m_pTexture[tex]);				break;
			case TEX_Icon:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/Player_Icon.png", &m_pTexture[tex]);				break;

			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	C2D::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * 入力関数 *
//==================================================================================================//
void C2D::Set(D3DXVECTOR3 pos, float fLengthX, float fLengthY, float fRot, int nUV, int nUV_X, int nUV_Y, D3DXCOLOR col, TEXTURE Texture)
{
	m_pos = pos;
		m_pTex = Load(Texture);
		m_fLengthX = fLengthX;
		m_fLengthY = fLengthY;
		m_DrawType = CScene::DRAW_TYPE_NORMAL;
		
		//Vtxの変更
		VERTEX_2D *pVtx;		//頂点情報へのポインタ

								//頂点BUFFERをロックし、頂点情報へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);

		//カラー設定
		pVtx[0].col = col;	// A = 透明度
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		//テクスチャ座標設定
		pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
		pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
		pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
		pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

		//頂点BUFFERをアンロックする
		m_pVtxBuff->Unlock();
}
//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT  C2D::Init(void)
{
	// ポリゴンの位置を設定
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	m_fLengthX = 50;
	m_fLengthY = 50;
	CManager::GetRenderer();

	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	// 頂点バッファの生成
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	float fRot = 0.0f;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void C2D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	delete this;
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void C2D::Update(void)
{

}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void C2D::Draw(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; };

	//頂点BUFFERをデバイスのデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pD3DDevice->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定

										//テクスチャの設定
	if (m_pTex != NULL)
	{//テクスチャの設定
		pD3DDevice->SetTexture(0, m_pTex[0]);
	}//テクスチャ削除

	//ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->SetTexture(0, NULL);

}
//=============================================================================
// 頂点情報の設定
//=============================================================================
void C2D::SetPosition(float fRot)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点倍率の設定
//=============================================================================
void C2D::SetPosition2(float fSize)
{
	VERTEX_2D *pVtx;
	float fLengthX = m_fLengthX * fSize;
	float fLengthY = m_fLengthY * fSize;
	float fRot = D3DX_PI;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * fLengthY) + (cosf(fRot) * fLengthX), m_pos.y - (sinf(fRot) * fLengthX) + (cosf(fRot) * fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * fLengthY) - (cosf(fRot) * fLengthX), m_pos.y + (sinf(fRot) * fLengthX) + (cosf(fRot) * fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * fLengthY) + (cosf(fRot) * fLengthX), m_pos.y - (sinf(fRot) * fLengthX) - (cosf(fRot) * fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * fLengthY) - (cosf(fRot) * fLengthX), m_pos.y + (sinf(fRot) * fLengthX) - (cosf(fRot) * fLengthY), 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * UV変更 *
//==================================================================================================//
void C2D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtxの変更
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * UV変更 *
//==================================================================================================//
void C2D::SetUV_Camera(float fUV_X, float fUV_Y, float fDiameter)
{
	//Vtxの変更
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	D3DXVECTOR3 pos = CCamera::camera.m_posV;
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2((pos.x * fDiameter) + fUV_X, (pos.z * (-fDiameter * 1.65f)) + fUV_Y);
	pVtx[1].tex = D3DXVECTOR2((pos.x * fDiameter) + 1.0f + fUV_X, (pos.z * (-fDiameter * 1.65f)) + fUV_Y);
	pVtx[2].tex = D3DXVECTOR2((pos.x * fDiameter) + fUV_X, (pos.z * (-fDiameter * 1.65f)) + 1.0f + fUV_Y);
	pVtx[3].tex = D3DXVECTOR2((pos.x * fDiameter) + 1.0f + fUV_X, (pos.z * (-fDiameter * 1.65f)) + 1.0f + fUV_Y);


	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * UVをゲージ型に変更 *
//==================================================================================================//
void	C2D::SetGageUV(float fMaxLengthX)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_fLengthX / fMaxLengthX), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_fLengthX / fMaxLengthX), 1.0f);


	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * ゲージ型に変更 *
//==================================================================================================//
void C2D::SetGage(float fLengthX, bool bDirection)
{
	//Vtxの変更
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	m_fLengthX = fLengthX;

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX)	,-m_fLengthY, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f)	,-m_fLengthY, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX)	,m_fLengthY, 0.0f)	+ m_pos;
	pVtx[3].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f)	,m_fLengthY, 0.0f)	+ m_pos;

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void C2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点カラー透明度(左右)の設定
//=============================================================================
void	C2D::SetSideAlpha(float fCol, float fMinCol, int nID)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	D3DXCOLOR col = pVtx[0 + nID].col;
	col.a += fCol;
	if (col.a >= 1.0f) { col.a = 1.0f; }
	if (col.a <= fMinCol) { col.a = fMinCol; }

	pVtx[0 + nID].col = col;
	pVtx[2 + nID].col = col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void C2D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	for (int nCount = 0; nCount < 4; nCount++) { pVtx[nCount].tex += uv; }

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// アニメーションポリゴンの設定
//=============================================================================
void	C2DAnim::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed,
	CSceneAnim3D::ANIMATION animation, D3DXCOLOR col, C2D::TEXTURE Texture)
{
	C2D::Set(pos, fLengthX, flengthY, fRot, nPtnAnim, nPtnWide, nPtnHeight, col, Texture);
	m_animation = animation;
	m_nCntAnim = 0;
	m_nPtnAnim = nPtnAnim;
	m_nPtnWide = nPtnWide;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
}
//=============================================================================
// アニメーションポリゴンの更新処理
//=============================================================================
void	C2DAnim::Update(void)
{
	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV変更
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//画像の範囲外
			if (m_animation == CSceneAnim3D::ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}//アニメーション更新
		SetUV(m_nPtnAnim, m_nPtnWide, m_nPtnHeight);
	}
}

//=============================================================================
// カメラ付き添いポリゴンの設定処理
//=============================================================================
void C2DCameraBG::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, float fUV_X, float fUV_Y, float fDiameter, D3DXCOLOR col, C2D::TEXTURE Texture)
{
	C2D::Set(pos, fLengthX, flengthY, fRot, 0, 1, 1, col, Texture);
	m_fUV_X = 0.0f;
	m_fUV_Y = 0.0f;
	m_fUV_XPlus = fUV_X;
	m_fUV_YPlus = fUV_Y;
	m_fDiameter = fDiameter;
}
//=============================================================================
// カメラ付き添いポリゴンの更新処理
//=============================================================================
void	C2DCameraBG::Update(void)
{
	m_fUV_X += m_fUV_XPlus;
	m_fUV_Y += m_fUV_YPlus;
	SetUV_Camera(m_fUV_X, m_fUV_Y, m_fDiameter);
}

//==================================================================================================//
//    * 入力関数 *
//==================================================================================================//
void C2DPolygon::Set(D3DXVECTOR3 pos, float fLengthX, float fLengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture)
{
	m_col = col;
	m_fCntState = fCntState;
	m_state = state;
	C2D::Set(pos, fLengthX, fLengthY, fRot, nUV, nUV_X, nUV_Y, col, Texture);
}
//=============================================================================
// 通常ポリゴンの更新処理
//=============================================================================
void	C2DPolygon::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		switch (m_state)
		{
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADEIN:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADE:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
			SetColor(m_col);
			break;
		case STATE_SLIDEIN:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * (1.0f - m_col.a), 2), 0.0f, 0.0f);
			SetPosition(D3DX_PI);
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDEOUT:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * m_col.a, 2), 0.0f, 0.0f);
			SetPosition(D3DX_PI);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDEIN2:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * (1.0f - m_col.a), 2), powf(SLIDE_SPEED * (1.0f - m_col.a), 2), 0.0f);
			SetPosition(D3DX_PI);
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDEOUT2:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * m_col.a, 2), powf(SLIDE_SPEED * m_col.a, 2), 0.0f);
			SetPosition(D3DX_PI);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_BIG:
			if (m_fCntState < 120.0f)
			{
				m_fCntState += 8.0f;
				if (m_fCntState >= 120.0f) { m_fCntState = 120.0f; }
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		case STATE_SMALL:
			if (m_fCntState > 80.0f)
			{
				m_fCntState -= 8.0f;
				if (m_fCntState <= 80.0f) { m_fCntState = 80.0f; }
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		}
	}
}