//=============================================================================
//
// ポリゴン処理 [SceneAnim3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"SceneAnim3D.h"
#include"Renderer.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneAnim3D::Init(void)
{
	CScene3D::Init();
	m_animation = ANIMATION_NORMAL;
	m_nCntAnim = -1;
	m_nPtnAnim = 0;
	m_nPtnWide = 1;
	m_nPtnHeight = 1;
	m_nPtnSpeed = 1;
	return S_OK;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneAnim3D::Update(void)
{//アニメーション
	VERTEX_3D *pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXVECTOR3 &pos = GetPosition();	D3DXVECTOR3 &rot = GetRotation();	D3DXCOLOR	&col = GetColor();
	D3DXVECTOR3 &length = GetLength();
	STATE &m_state = GetState();

	if (m_state == STATE_STOP)
	{
		float &m_fCntState = GetfCntState();
		D3DXCOLOR &m_col = GetColor();
		m_col.r -= m_fCntState;
		if (m_col.r < 0.0f) { m_col.r = 1.0f; m_col.a = 1.0f; m_state = STATE_NORMAL; }
		return;
	}

 //頂点バッファをロックし、頂点データへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV変更
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//画像の範囲外
			if (m_animation == ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}

		//UVの設定
		pVtx[0].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[1].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[2].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
		pVtx[3].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
	}

	CScene3D::Update();

	//頂点バッファのアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// 設定処理
//=============================================================================
void CSceneAnim3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, bool bBillBoard,
	DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state)
{
	CScene3D::Set(pos, rot, col, length, CScene3D::TEX_MAX, nPtnAnim, nPtnWide, nPtnHeight, bBillBoard, DrawType);
	BindTexture(Load(nType));
	m_animation = animation;
	GetState() = state;
	GetfCntState() = 0.0f;
	m_nCntAnim = -1;
	m_nPtnAnim = nPtnAnim;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
	m_nPtnWide = nPtnWide;
}
//=============================================================================
// 設定処理
//=============================================================================
void CSceneAnimEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, bool bBillBoard,
	DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CSceneAnim3D::Set(pPos[0], rot, col, length, nType, bBillBoard, DrawType, nPtnAnim, nPtnWide, nPtnHeight, nPtnSpeed, animation, state);
	m_pPos = pPos;
	m_pScene = pScene;
	m_Distance = pos;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneAnimEffect::Update()
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition() = m_pPos[0] + m_Distance; SetMtx(); }
	CSceneAnim3D::Update();
}
