//=============================================================================
//
// 3Dポリゴン処理 [3DPolygon.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"3DPolygon.h"
#include "camera.h"

#include"Renderer.h"
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
LPDIRECT3DTEXTURE9	C3D::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ
LPDIRECT3DTEXTURE9	CAnim3D::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*C3D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			 //ラビリンス//***********************************************************************
			case TEX_SHADOW:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/effect000.jpg", &m_pTexture[tex]);		break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	C3D::UnLoad(void)
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
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT C3D::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	m_pVtxBuff = NULL;
	m_pTex = NULL;

	// 頂点情報の作成
	MakeVertex(pD3DDevice);

	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void C3D::Uninit(void)
{
	// 頂点バッファの開放;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	delete this;
}

//=============================================================================
// 更新処理
//=============================================================================
void C3D::Update(void)
{
	switch (m_state)
	{
	case STATE_UVFLOW_1:
		m_fCntState += 0.01f;
	case STATE_UVFLOW_0:
		m_fCntState += 0.02f;
		//UVの設定
		VERTEX_3D *pVtx;

		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		pVtx[0].tex = D3DXVECTOR2(0.0f + m_fCntState, 0.0f + m_fCntState);
		pVtx[1].tex = D3DXVECTOR2(1.0f + m_fCntState, 0.0f + m_fCntState);
		pVtx[2].tex = D3DXVECTOR2(0.0f + m_fCntState, 1.0f + m_fCntState);
		pVtx[3].tex = D3DXVECTOR2(1.0f + m_fCntState, 1.0f + m_fCntState);

		//頂点バッファのアンロック
		m_pVtxBuff->Unlock();
	case STATE_FADESPIN:
		m_fCntState += 0.05f;
		m_rot.y += D3DX_PI * 0.03f;
		if (m_fCntState >= 1.0f) { Uninit(); return; }
		m_col.a = 1.0f - m_fCntState;//透明度変更
		m_fLengthX *= 1.0f + ((1.0f - m_fCntState) * 0.25f);
		m_fLengthZ *= 1.0f + ((1.0f - m_fCntState) * 0.25f);
		SetColor(m_col);
		SetSize(m_fLengthX, m_fLengthZ);
		break;
	case STATE_FADEOUT:
		m_fCntState += 0.05f;
		m_col.a = 1.0f - m_fCntState;//透明度変更
		if (m_col.a < 0.0f) { m_col.a = 0.0f; }
		SetColor(m_col);
		if (m_fCntState >= 1.0f) { Uninit(); return; }
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void C3D::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DXMATRIX	mtxWorld;		//ワールドマトリックス

	CScene::DrawPrepare(m_DrawType, pD3DDevice);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	if (m_pTex != NULL)
	{//テクスチャの設定
		pD3DDevice->SetTexture(0, m_pTex[0]);
	}//テクスチャ削除

	// ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void C3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 設定
//=============================================================================
void C3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_pTex == NULL) { m_pTex = Load(nType); };
			m_col = col;

			m_pos = pos;
			m_rot = rot;
			m_fLengthX = fLengthX;
			m_fLengthZ = fLengthZ;
			m_DrawType = DrawType;

			pVtx[0].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, m_fLengthZ);
			pVtx[1].pos = D3DXVECTOR3(m_fLengthX, 0.1f, m_fLengthZ);
			pVtx[2].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, -m_fLengthZ);
			pVtx[3].pos = D3DXVECTOR3(m_fLengthX, 0.1f, -m_fLengthZ);

			//頂点カラーの設定
			pVtx[0].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			pVtx[1].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			pVtx[2].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			pVtx[3].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
			//UVの設定
			pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
			pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 色の設定
//=============================================================================
void	C3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//頂点カラーの設定
	pVtx[0].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[1].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[2].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）
	pVtx[3].col = m_col;  //色の指定（0.0f ～ 1.0f）&透明度（0.0f　～　1.0f）

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 色の設定
//=============================================================================
void	C3D::SetSize(float fLengthX, float fLengthZ)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//値を代入
	m_fLengthX = fLengthX;
	m_fLengthZ = fLengthZ;

	pVtx[0].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, m_fLengthZ);
	pVtx[1].pos = D3DXVECTOR3(m_fLengthX, 0.1f, m_fLengthZ);
	pVtx[2].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, -m_fLengthZ);
	pVtx[3].pos = D3DXVECTOR3(m_fLengthX, 0.1f, -m_fLengthZ);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// エフェクトの設定
//=============================================================================
void C3DEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
	TEXTURE nType, int nUV, int nUV_X, int nUV_Y, CScene::DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene)
{
	C3D::Set(pos, rot, col, fLengthX, fLengthZ, nType, nUV, nUV_X, nUV_Y, DrawType);
	m_pPos = pPos;
	m_pScene = pScene;
}
//=============================================================================
// エフェクトの更新
//=============================================================================
void C3DEffect::Update(void)
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition()[0] = m_pPos[0]; }
	C3D::Update();
}
//=============================================================================
// 描画処理
//=============================================================================
void C3DEffect::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DXMATRIX	mtxWorld;		//ワールドマトリックス
	D3DXVECTOR3 m_pos = GetPosition()[0];
	D3DXVECTOR3 m_rot = GetRotation()[0];

	CScene::DrawPrepare(GetDrawType(), pD3DDevice);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	if (GetTexture() != NULL)
	{//テクスチャの設定
		pD3DDevice->SetTexture(0, GetTexture()[0]);
	}//テクスチャ削除

	 // ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pD3DDevice->SetTexture(0, NULL);
}

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CAnim3D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			 //戦車//***********************************************************************
			case TEX_BARRIER:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/barrier000.jpg", &m_pTexture[tex]);		break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CAnim3D::UnLoad(void)
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
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CAnim3D::Init(void)
{
	C3D::Init();
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
void CAnim3D::Update(void)
{//アニメーション
	VERTEX_3D *pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	STATE *state = GetState();			float *fCntState = GetfCntState();

	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV変更
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//画像の範囲外
			if (m_animation == ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}

		//頂点バッファをロックし、頂点データへのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//UVの設定
		pVtx[0].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide), (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[1].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide), (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[2].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide), (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
		pVtx[3].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide), (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));

		//頂点バッファのアンロック
		pVtxBuff->Unlock();
	}
}
//==================================================================================================//
//    * UV変更 *
//==================================================================================================//
void C3D::SetUV(int nUV, int nUV_X, int nUV_Y)
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
//=============================================================================
// UV加算処理
//=============================================================================
void	C3D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標設定
	pVtx[0].tex += uv;
	pVtx[1].tex += uv;
	pVtx[2].tex += uv;
	pVtx[3].tex += uv;

	//頂点BUFFERをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 設定処理
//=============================================================================
void CAnim3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
	TEXTURE nType, CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state)
{
	C3D::Set(pos, rot, col, fLengthX, fLengthZ, C3D::TEXTURE_MAX, nPtnAnim, nPtnWide, nPtnHeight, DrawType);
	BindTexture(Load(nType));
	m_animation = animation;
	GetState()[0] = state;
	GetfCntState()[0] = 0.0f;
	m_nCntAnim = -1;
	m_nPtnAnim = nPtnAnim;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
	m_nPtnWide = nPtnWide;
}
//=============================================================================
// 設定処理
//=============================================================================
void CAnim3DEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
	TEXTURE nType, CScene::DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CAnim3D::Set(pos, rot, col, fLengthX, fLengthZ, nType, DrawType, nPtnAnim, nPtnWide, nPtnHeight, nPtnSpeed, animation, state);
	m_pPos = pPos;
	m_pScene = pScene;
}
//=============================================================================
// 更新処理
//=============================================================================
void CAnim3DEffect::Update()
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition()[0] = m_pPos[0]; }
	CAnim3D::Update();
}
