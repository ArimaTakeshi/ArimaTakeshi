//=============================================================================
//
// ゲージの処理 [gauge.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "gauge.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_GAUGE_NAME_1	"data\\TEXTURE\\Life0001.png"	//読み込むテクスチャファイル
#define BG_TEXTURE_UV_U			(1.0f)							//テクスチャアニメーションU範囲
#define BG_TEXTURE_UV_V			(1.0f)							//テクスチャアニメーションV範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 CGauge::m_pTexture[NUM_TEXTURE_GAUGE] = {};
LPDIRECT3DVERTEXBUFFER9 CGauge::m_pVtxBuff = NULL;
int CGauge::m_nCntSubtraction = 0;
CGauge::Gauge CGauge::m_aGauge[NUM_POLYGON_GAUGE] = {};
int CGauge::m_nMaxGauge = 0;
bool CGauge::m_bGaugeOnOff = false;
bool CGauge::m_bGaugeDownOn = false;
bool CGauge::m_bGaugeActionFade = false;
int CGauge::m_nGaugeRecastTime = 0;
bool CGauge::m_bTired = false;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CGauge::CGauge() : CScene(5)//優先優位イニシャライズ
{
	for (int nCount = 0; nCount < NUM_POLYGON_GAUGE; nCount++)
	{
		m_aGauge[nCount] = {};					//ゲージの構造体
	}
	m_nCntSubtraction = 0;						//バーを減らし始めるカウンタ
	//m_nGaugeRecastTime = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CGauge::~CGauge()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGauge::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 枠
	m_aGauge[0].pos = m_pos;
	m_aGauge[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_aGauge[0].fGauge = MAX_GAUGE;							// ゲージを最大にする
	m_aGauge[0].fLength = BAR_WIDTH_GAUGE;					// バーの長さを設定
	m_aGauge[0].nType = -1;									// テクスチャのON(0)OFF(-1)

	// バー
	for (int nCntLife = 1; nCntLife < NUM_POLYGON_GAUGE; nCntLife++)
	{
		m_aGauge[nCntLife].pos = m_pos;
		m_aGauge[nCntLife].fGauge = MAX_GAUGE;				// ゲージを最大にする
		m_aGauge[nCntLife].fLength = BAR_WIDTH_GAUGE;		// バーの長さを設定
		m_aGauge[nCntLife].nType = 0;						// テクスチャのON(0)OFF(-1)
	}

	m_aGauge[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_aGauge[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_aGauge[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// バーを減らし始めるカウンタ
	m_nCntSubtraction = 0;

	// 頂点情報の作成
	CGauge::MakeVertexGauge(pDevice);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGauge::Uninit(void)
{
	m_bGaugeOnOff = false;
	m_bGaugeDownOn = false;
	m_bTired = false;

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CGauge::Update(void)
{
	/*	g_Life[3].fLength == 現在のゲージ					（最前面に来るバー）			*/
	/*	g_Life[2].fLength == ダメージを受けて減った分のバー	（最前面から一つ後ろに来るバー）*/
	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();

	CDebugProc::Print("現在のゲージ状態 = %s\n", m_bGaugeOnOff ? "TRUE" : "FALSE");
	CDebugProc::Print("現在のゲージ状態 = %s\n", m_bGaugeDownOn ? "TRUE" : "FALSE");
	CDebugProc::Print("m_nGaugeRecastTime = %d\n", m_nGaugeRecastTime);

	//ゲージが減る
	if (m_bGaugeOnOff == true && CPlayer::GetCancelHeal() == false)
	{
		//ゲージを減らす
		CGauge::AddGauge(-0.4f);

		//点滅処理
		//選択しているカラーの値を減らしていく
		m_fCntColor -= 0.09f;

		if (m_fCntColor < 0.5f)
		{//信託しているカラーが0.5を切ったらカラーの値が増えてく
			m_fCntColor = 1.0f;
		}

		//カラーの更新処理
		CGauge::ColorUpdate(m_fCntColor);

		//ゲージを減らすためのboolをtrueにする
		m_bGaugeDownOn = true;

		if (m_aGauge[3].fGauge <= 0)
		{
			//ゲージを減っている状態をfalseにする
			m_bGaugeOnOff = false;
			
			//カラー初期化処理
			CGauge::ColorInit();
		}
	}

	if (m_bGaugeOnOff == false || CPlayer::GetCancelHeal() == true)
	{
		//ゲージを増やす
		if (m_aGauge[3].fGauge == MAX_GAUGE)
		{
			//ゲージを減らすためのboolをfalseにする
			m_bGaugeDownOn = false;

			//未来のキャンセル
			CPlayer::SetFutureCancel(false);

			CPlayer::SetCancelHeal(false);
		}
		else if (m_nGaugeRecastTime >= 180 && m_aGauge[3].fGauge <= MAX_GAUGE)
		{
			//ゲージを増やす
			CGauge::AddGauge(0.25f);
		}
		else if (m_nGaugeRecastTime <= 180)
		{
			//キャンセル回復時間
			CPlayer::SetCancelHeal(true);

			//カラー初期化処理
			CGauge::ColorInit();
		}

		//カウントは最大1500まで
		if (m_nGaugeRecastTime >= 0 && m_nGaugeRecastTime <= 1499)
		{
			//カウントを増加
			m_nGaugeRecastTime++;
		}
	}

	//==========================
	// ステージが遷移した時のみ
	//==========================
	if (pPlayer->GetCancelStageNext() == true)
	{
		//カラー初期化処理
		CGauge::ColorInit();
	}

	if (pPlayer != NULL)
	{
		if (m_aGauge[2].fLength > m_aGauge[3].fLength)
		{// ゲージと同じ値になるまで後ろのゲージを減らす
			m_nCntSubtraction++;								// ダメージバーを減らし始めるためのカウント

			if (m_nCntSubtraction >= GAUGE_SUBTRACT_TIME)
			{// 一定時間経過
				m_aGauge[2].fLength -= BAR_WIDTH_GAUGE * 0.01f;	// ダメージバーの長さを1％ずつ減らす

				VERTEX_2D *pVtx;

				// 頂点バッファをロックし、頂点情報へのポインタを取得
				m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

				//頂点座標の設定
				pVtx[(2 * 4) + 1].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength + GAUGE_DIAMOND, m_aGauge[2].pos.y, 0.0f);
				pVtx[(2 * 4) + 3].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength, m_aGauge[2].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

				// 頂点バッファをアンロックする
				m_pVtxBuff->Unlock();
			}
		}
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CGauge::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLife = 0; nCntLife < NUM_POLYGON_GAUGE; nCntLife++)
	{
		// テクスチャの設定
		if (m_aGauge[nCntLife].nType >= 0)
		{// テクスチャの指定
			pDevice->SetTexture(0, m_pTexture[m_aGauge[nCntLife].nType]);
		}
		else
		{// 0より低いとテクスチャを張らない
			pDevice->SetTexture(0, NULL);
		}

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CGauge * CGauge::Create(D3DXVECTOR3 pos)
{
	CGauge *pGauge = NULL;

	//NULLチェック
	if (pGauge == NULL)
	{//メモリの動的確保

		pGauge = new CGauge;

		if (pGauge != NULL)
		{
			//位置を入れる
			pGauge->m_pos = pos;
			//オブジェクトクラスの生成
			pGauge->Init();
		}
	}

	return pGauge;
}
//=============================================================================
// 体力の増減
//=============================================================================
void CGauge::AddGauge(float fValue)
{
	//プレイヤーの情報
	CPlayer *pPlayer = CGame::GetPlayer();

	//m_nMaxLife = pPlayer->GetMaxLife();

	m_aGauge[3].fGauge += fValue;		// ゲージを増減させる
	float fLife;

	if (m_aGauge[3].fGauge > 0.0f)
	{
		// ゲージが0より大きいとき
		fLife = (BAR_WIDTH_GAUGE * 1.0f) / ((MAX_GAUGE * 1.0f) / m_aGauge[3].fGauge);	// バーの元の長さを100%としてゲージを増減させる
	}
	else
	{
		// ゲージが0以下のとき
		fLife = 0;
		//一番上のゲージの値をとどめる
		m_aGauge[3].fGauge = 0;
		//リキャストタイム
		m_nGaugeRecastTime = 0;

		//ゲージが持つアクションフェードを起動
		m_bGaugeActionFade = true;

		//疲れるモード
		m_bTired = true;

		CPlayer::SetEnemyFutureSukill(false);

		//未来から戻す
		CPlayer::SetFuture(true);
	}

	if (m_aGauge[3].fGauge >= MAX_GAUGE)
	{
		// 最大値を超えたら戻す
		m_aGauge[3].fGauge = MAX_GAUGE;
		fLife = BAR_WIDTH_GAUGE;

		//ゲージを使えるようにする
		m_bGaugeOnOff = false;
	}

	m_aGauge[3].fLength = fLife;	// 現在のゲージバーの長さ

	m_nCntSubtraction = 0;			// ダメージバーの長さを減らし始めるためのカウンタを初期化

	//頂点情報の設定
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (fValue > 0.0f)
	{
		// 回復したとき後ろのバーも増やす
		m_aGauge[2].fLength = fLife;

		//頂点座標の設定
		pVtx[(2 * 4) + 1].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength + GAUGE_DIAMOND, m_aGauge[2].pos.y, 0.0f);
		pVtx[(2 * 4) + 3].pos = D3DXVECTOR3(m_aGauge[2].pos.x + m_aGauge[2].fLength, m_aGauge[2].pos.y + BAR_HEIGHT_GAUGE, 0.0f);
	}

	//現在のゲージ
	pVtx[(3 * 4) + 1].pos = D3DXVECTOR3(m_aGauge[3].pos.x + m_aGauge[3].fLength + GAUGE_DIAMOND, m_aGauge[3].pos.y, 0.0f);
	pVtx[(3 * 4) + 3].pos = D3DXVECTOR3(m_aGauge[3].pos.x + m_aGauge[3].fLength, m_aGauge[3].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//===============================================================================
// 頂点カラー変更
//===============================================================================
void CGauge::ColorUpdate(float fCntColor)
{
	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー設定
	pVtx[(3 * 4) + 0].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);
	pVtx[(3 * 4) + 1].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);
	pVtx[(3 * 4) + 2].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);
	pVtx[(3 * 4) + 3].col = D3DXCOLOR(1.0f, fCntColor, 0.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//===============================================================================
// 頂点カラー初期化
//===============================================================================
void CGauge::ColorInit(void)
{
	m_fCntColor = 1.0f;

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー設定
	pVtx[(3 * 4) + 0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[(3 * 4) + 1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[(3 * 4) + 2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[(3 * 4) + 3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//===============================================================================
// テクスチャの読み込み
//===============================================================================
HRESULT CGauge::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_GAUGE_NAME_1,
		&m_pTexture[0]
	);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CGauge::UnLoad(void)
{
	for (int nCount = 0; nCount < NUM_TEXTURE_GAUGE; nCount++)
	{
		//テクスチャーの破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void CGauge::MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLife;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_POLYGON_GAUGE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < NUM_POLYGON_GAUGE; nCntLife++)
	{
		//頂点座標の設定
		pVtx[(nCntLife * 4) + 0].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x + GAUGE_DIAMOND, m_aGauge[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 1].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x + BAR_WIDTH_GAUGE + GAUGE_DIAMOND, m_aGauge[nCntLife].pos.y, 0.0f);
		pVtx[(nCntLife * 4) + 2].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x, m_aGauge[nCntLife].pos.y + BAR_HEIGHT_GAUGE, 0.0f);
		pVtx[(nCntLife * 4) + 3].pos = D3DXVECTOR3(m_aGauge[nCntLife].pos.x + BAR_WIDTH_GAUGE, m_aGauge[nCntLife].pos.y + BAR_HEIGHT_GAUGE, 0.0f);

		//1.0fで固定
		pVtx[(nCntLife * 4) + 0].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 1].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 2].rhw = 1.0f;
		pVtx[(nCntLife * 4) + 3].rhw = 1.0f;

		//頂点カラー
		pVtx[(nCntLife * 4) + 0].col = m_aGauge[nCntLife].col;
		pVtx[(nCntLife * 4) + 1].col = m_aGauge[nCntLife].col;
		pVtx[(nCntLife * 4) + 2].col = m_aGauge[nCntLife].col;
		pVtx[(nCntLife * 4) + 3].col = m_aGauge[nCntLife].col;

		//テクスチャ座標
		pVtx[(nCntLife * 4) + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[(nCntLife * 4) + 1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[(nCntLife * 4) + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[(nCntLife * 4) + 3].tex = D3DXVECTOR2(0.1f, 1.0f);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}