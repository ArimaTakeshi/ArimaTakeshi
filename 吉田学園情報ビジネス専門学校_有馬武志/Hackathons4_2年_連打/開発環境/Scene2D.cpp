//=============================================================================
//
// レンダリング処理 [Scene2D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CScene2D::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CScene2D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み 
			case TEXTURE_Title:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TITLE/BG000.jpg", &m_pTexture[tex]);			break; 
			case TEXTURE_TitleLogo:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TITLE/Title001.png", &m_pTexture[tex]);			break;
			case TEXTURE_Select:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/BG002.jpg", &m_pTexture[tex]);			break;
			case TEXTURE_VsSelect:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/vsSelect_BG000.jpg", &m_pTexture[tex]);	break;
			case TEXTURE_VsSelect2:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/vsSelect_BG001.jpg", &m_pTexture[tex]);	break;
			case TEXTURE_LogoPress:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Logo002.png", &m_pTexture[tex]);				break;
			case TEXTURE_LogoPause:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/pause.png", &m_pTexture[tex]);				break;
			case TEXTURE_LogoSelect:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Logo000.png", &m_pTexture[tex]);				break; 
			case TEXTURE_LogoVersus:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/Info_Logo.png", &m_pTexture[tex]);		break;
			case TEXTURE_LogoVsEnd:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/EndLogo.jpg", &m_pTexture[tex]);			break;
			case TEXTURE_Marker:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Marker000.png", &m_pTexture[tex]);			break;
			case TEXTURE_Select2:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Select100.jpg", &m_pTexture[tex]);		break;
			case TEXTURE_Window:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Window000.jpg", &m_pTexture[tex]);		break;
			case TEXTURE_Slashing0:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/leffect132_.jpg", &m_pTexture[tex]);		break;
			case TEXTURE_Slashing1:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/SELECT/Window000.jpg", &m_pTexture[tex]);		break; 
			case TEXTURE_Fade000:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Fade000.jpg", &m_pTexture[tex]);				break;
			case TEXTURE_TUTORIAL:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Help000.jpg", &m_pTexture[tex]);				break;
			case TEXTURE_ITEM_TUTORIAL:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Item_Tutorial000.jpg", &m_pTexture[tex]);	break; 
			case TEX_UIWindow:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Font_Window000.png", &m_pTexture[tex]);		break;
			case TEX_VSWindow:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Window.png", &m_pTexture[tex]);				break;
			case TEX_CLEAR:				D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/congratulations.jpg", &m_pTexture[tex]);		break;
			case TEX_OVER:				D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/GameOver000.jpg", &m_pTexture[tex]);			break; 
			case TEX_OVER2:				D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Fade001.jpg", &m_pTexture[tex]);				break; 
			case TEXTURE_TimeUp:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/TimeUp.png", &m_pTexture[tex]);				break; 
			case TEX_SPARK:				D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Effect200.jpg", &m_pTexture[tex]);break;
			case TEXTURE_Title000hand:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TITLE/te000.png", &m_pTexture[tex]);			break; 
			case TEXTURE_Title001hand:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/TITLE/te001.png", &m_pTexture[tex]);			break; 
			case TEX_Game000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/GameBG000.jpg", &m_pTexture[tex]);					break;
			case TEX_Result000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/HighLivingTime001.png", &m_pTexture[tex]);			break;
			case TEX_Result001:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/HighLivingTime001.png", &m_pTexture[tex]);			break; 
			case TEX_Result002:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/NowLivingTime001.png", &m_pTexture[tex]);			break; 
			case TEX_Bullet999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Bullet000.png", &m_pTexture[tex]);			break; 
			case TEX_Player999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/Player.png", &m_pTexture[tex]);			break; 
			case TEX_Enemy999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/zombi.png", &m_pTexture[tex]);			break;
			case TEX_Explosion999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/explosion.jpg", &m_pTexture[tex]);			break; 
			case TEX_Over999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/GameOverBG.jpg", &m_pTexture[tex]);			break; 
			case TEX_Bomb999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/item000.png", &m_pTexture[tex]);			break;
			case TEX_A999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PressAButton.png", &m_pTexture[tex]);			break;
			case TEX_T999:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/Tutorial.jpg", &m_pTexture[tex]);			break;



			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CScene2D::UnLoad(void)
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
void CScene2D::Set(D3DXVECTOR3 pos, float fLengthX, float fLengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture)
{
	m_pos = pos;
	m_col = col;

	m_pTex = Load(Texture);
	m_fLengthX = fLengthX;
	m_fLengthY = fLengthY;
	m_fCntState = fCntState;
	m_state = state;
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
HRESULT  CScene2D::Init(void)
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

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	float fRot = 0.0f;
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
void CScene2D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{// 頂点バッファの破棄
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		float fWKstate;

		switch (m_state)
		{
		case STATE_FADEOUT2:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDE_OUT1:
			m_pos.y += powf(m_col.a * 5.0f, 2);
			SetPosition(m_pos);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_SLIDE_OUT2:
			m_pos.y -= powf(m_col.a * 5.0f, 2);
			SetPosition(m_pos);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { Uninit(); return; }
			SetColor(m_col);
			break;
		case STATE_SLIDE_IN:
			m_pos.x += (1.0f - m_col.a) * 30.0f;
			SetPosition(m_pos);
		case STATE_FADEIN:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADEIN5:
			m_col.a += m_fCntState;
			if (m_col.a >= 0.5f) { m_col.a = 0.5f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADE:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
			SetColor(m_col);
			break;
		case STATE_FLOW0: PlusUV(D3DXVECTOR2(0.0005f, 0.0005f)); break;
		case STATE_FLOW1: PlusUV(D3DXVECTOR2(0.00075f, 0.0005f)); break;
		case STATE_FLOW2: PlusUV(D3DXVECTOR2(0.0f, 0.0005f)); break;
		case STATE_FLASH:
			m_fCntState = m_fCntState + 1.0f;
			fWKstate = m_fCntState * 0.01f;
			SetColor(D3DXCOLOR(fWKstate, fWKstate, fWKstate, 1.0f));
			if (m_fCntState >= 100.0f) { m_state = STATE_FLASH2; m_fCntState = 100.0f; }
			break;
		case STATE_FLASH2:
			m_fCntState = m_fCntState - 1.5f;
			fWKstate = m_fCntState * 0.01f;
			SetColor(D3DXCOLOR(fWKstate, fWKstate, fWKstate, 1.0f));
			if (m_fCntState <= 25.0f) { m_state = STATE_FLASH; m_fCntState = 25.0f; }
			break;
		case STATE_BIG:
			if (m_fCntState < 120.0f)
			{
				m_fCntState += 4.0f;
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		case STATE_SMALL:
			if (m_fCntState > 80.0f)
			{
				m_fCntState -= 4.0f;
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		case STATE_COL_FLOW:
			if (m_fCntState > m_fLengthX)
			{//長さが足りない
				m_fLengthX += 5.0f;
				if (m_fCntState <= m_fLengthX)
				{//長さが一致した
					m_fLengthX = m_fCntState;
				}
				SetGageUV(m_fCntState);
				SetGage(m_fLengthX, true);
				SetSideAlpha(-1.0f, 0.0f, 1);
			}
			else
			{//長さ十分
				SetSideAlpha(0.1f, 0.0f, 1);
			}

			break;
		}
	}
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();

	//描画方法設定
	if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

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

	switch (m_state)
	{
	case STATE_ZCLEAR://Ｚバッファのクリア
		CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
		break;
	}
}
//=============================================================================
// 頂点カラーの設定
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
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
// 頂点情報の設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	float fRot = D3DX_PI;
	m_pos = pos;

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
void CScene2D::SetPosition2(float fSize)
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
//    * 分割数からUV座標変更 *
//==================================================================================================//
void CScene2D::SetUV(int nUV, int nUV_X, int nUV_Y)
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
//    * UVをゲージ型に変更 *
//==================================================================================================//
void	CScene2D::SetGageUV(float fMaxLengthX)
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
void CScene2D::SetGage(float fLengthX, bool bDirection)
{
	//Vtxの変更
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	m_fLengthX = fLengthX;

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX), -m_fLengthY, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f), -m_fLengthY, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX), m_fLengthY, 0.0f) + m_pos;
	pVtx[3].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f), m_fLengthY, 0.0f) + m_pos;

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点情報の設定
//=============================================================================
void CScene2D::PlusUV(D3DXVECTOR2 fUV)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].tex += fUV;
	pVtx[1].tex += fUV;
	pVtx[2].tex += fUV;
	pVtx[3].tex += fUV;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 頂点カラー透明度(左右)の設定
//=============================================================================
void	CScene2D::SetSideAlpha(float fCol, float fMinCol, int nID)
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
// アニメーションポリゴンの設定
//=============================================================================
void	CSceneAnim2D::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed,
	float fCntState, STATE state, CSceneAnim3D::ANIMATION animation, D3DXCOLOR col, CScene2D::TEXTURE Texture)
{
	CScene2D::Set(pos, fLengthX, flengthY, fRot, nPtnAnim, nPtnWide, nPtnHeight, fCntState, state, col, Texture);
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
void	CSceneAnim2D::Update(void)
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

	CScene2D::Update();
}