//=========================================================================================================================
//
// 敵処理 [minibossenemy.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "minibossenemy.h"		//中ボス
#include "bossenemy.h"			//ボス
#include "explosion.h"			//爆発
#include "bullet.h"				//弾
#include "Game.h"				//ゲーム
#include "score.h"				//スコア
#include "sound.h"				//サウンド
#include "warning.h"			//ワーニング
#include "enemy.h"				//雑魚敵	

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_TYPE_MINIBOSSENEMY					(4)									// 敵の種類
#define MINIBOSSENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\enemy002.png"		//読み込むテクスチャファイル1
#define MINIBOSSENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\enemy002.png"	//読み込むテクスチャファイル2
#define MINIBOSSENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\enemy002.png"		//読み込むテクスチャファイル3
#define MINIBOSSENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\enemy002.png"		//読み込むテクスチャファイル4
#define WARNING_TEXTURE_NAME					"data\\TEXTURE\\ボス前.png"			//読み込むテクスチャファイル5
#define MINIBOSSENEMY_TEXTURE_UV_U				(1.0f)								//テクスチャアニメーションU範囲
#define MINIBOSSENEMY_TEXTURE_UV_V				(1.0f)								//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureMiniBossEnemy[MAX_TYPE_MINIBOSSENEMY] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMiniBossEnemy = NULL;							//頂点バッファへのポインタ
MiniBossEnemy g_aMiniBossEnemy[MAX_ENEMY];										//敵の情報
int g_nNumMiniBossEnemy;														//敵の総数

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
void InitMiniBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntMiniBossEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//敵の情報の初期化
	for(int nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//敵をカウント
		g_aMiniBossEnemy[nCntMiniBossEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMiniBossEnemy[nCntMiniBossEnemy].move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		g_aMiniBossEnemy[nCntMiniBossEnemy].nType = 0;
		g_aMiniBossEnemy[nCntMiniBossEnemy].bUse = false;
		g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_NORMAL;
		g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState = 0;
		g_aMiniBossEnemy[nCntMiniBossEnemy].nLife = 0;			//敵の体力
		g_nNumMiniBossEnemy = 0;								//敵の総数クリア
	}

	//テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile
	(
		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_1,
		&g_apTextureMiniBossEnemy[0]
	);
	D3DXCreateTextureFromFile
	(

		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_2,
		&g_apTextureMiniBossEnemy[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_3,
		&g_apTextureMiniBossEnemy[2]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		MINIBOSSENEMY_TEXTURE_NAME_4,
		&g_apTextureMiniBossEnemy[3]
	);

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファを生成
    pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMiniBossEnemy,
		NULL
	);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMiniBossEnemy->Lock
	(
		0, 
		0, 
		(void**)&pVtx, 
		0
	);

	for(nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//敵をカウント
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(MINIBOSSENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, MINIBOSSENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(MINIBOSSENEMY_TEXTURE_UV_U, MINIBOSSENEMY_TEXTURE_UV_V);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	/*SetEnemy(D3DXVECTOR3(200, 100, 0.0f), 0);*/

	//頂点バッファをアンロックする
	g_pVtxBuffMiniBossEnemy->Unlock();
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitMiniBossEnemy(void)
{
	int nCntTex;

	//テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_MINIBOSSENEMY; nCntTex++)
	{
		if (g_apTextureMiniBossEnemy[nCntTex] != NULL)
		{
			g_apTextureMiniBossEnemy[nCntTex]->Release();
			g_apTextureMiniBossEnemy[nCntTex] = NULL;
		}
	}

	//頂点バッファの開放
	if (g_pVtxBuffMiniBossEnemy != NULL)
	{
		g_pVtxBuffMiniBossEnemy->Release();
		g_pVtxBuffMiniBossEnemy = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateMiniBossEnemy(void)
{
	int nCntMiniBossEnemy;

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMiniBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{
		if (g_aMiniBossEnemy[nCntMiniBossEnemy].bUse == true)	//敵が使用されている
		{	 
			//ミニボスのスピード
			g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y += g_aMiniBossEnemy[nCntMiniBossEnemy].move.y;

			//頂点設定
			pVtx[nCntMiniBossEnemy * 4].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);

			//止まる処理
			if (g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y >= 200)
			{
				g_aMiniBossEnemy[nCntMiniBossEnemy].move.y = 0;

				switch (g_aMiniBossEnemy[nCntMiniBossEnemy].state)
				{
				case MINIBOSSENEMYSTATE_NORMAL:
					g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState++;

					//敵の弾のランダム
					//通常時
					if (rand() % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;

						//敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.0f, cosf(D3DX_PI + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.0f, cosf(D3DX_PI * 0 + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

					}
					break;

				case MINIBOSSENEMYSTATE_DAMAGE:
					g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState--;
					if (g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState <= 0)
					{
						g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_NORMAL;

						//頂点カラー設定
						pVtx[nCntMiniBossEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntMiniBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntMiniBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntMiniBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}

					//ダメージを与えたときの覚醒時
					if (rand() % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;

						//敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.5f, cosf(D3DX_PI + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.5f, cosf(D3DX_PI * 0 + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//紫敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  4.5f, cosf(D3DX_PI + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) *  4.5f, cosf(D3DX_PI * 0 + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

						//敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) * 1.5f, cosf(D3DX_PI - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 1.5f, cosf(D3DX_PI * 0 - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  2.5f, cosf(D3DX_PI - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  2.5f, cosf(D3DX_PI * 0 - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//紫敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  4.5f, cosf(D3DX_PI - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  4.5f, cosf(D3DX_PI * 0 - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
				


						//紫　回転　敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  3.0f, cosf(D3DX_PI - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 3.0f, cosf(D3DX_PI * 0 - nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);



						//紫　回転　敵の弾
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  3.0f, cosf(D3DX_PI + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 3.0f, cosf(D3DX_PI * 0 + nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

					
					}
					break;
				}
			}
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffMiniBossEnemy->Unlock();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawMiniBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffMiniBossEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//敵をカウント
		if (g_aMiniBossEnemy[nCntMiniBossEnemy].bUse == true)
		{//敵がいる場合
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureMiniBossEnemy[g_aMiniBossEnemy[nCntMiniBossEnemy].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMiniBossEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// 敵の設定
//=========================================================================================================================
void SetMiniBossEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntMiniBossEnemy;		//敵カウント

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffMiniBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntMiniBossEnemy = 0; nCntMiniBossEnemy < MAX_ENEMY; nCntMiniBossEnemy++)
	{//敵をカウント
		if (g_aMiniBossEnemy[nCntMiniBossEnemy].bUse == false)
		{//爆発が使用されていない
			g_aMiniBossEnemy[nCntMiniBossEnemy].pos = pos;			//pos値代入
			g_aMiniBossEnemy[nCntMiniBossEnemy].nType = nType;		//nType値代入
			g_aMiniBossEnemy[nCntMiniBossEnemy].bUse = true;		//使用している状態にする
			g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_NORMAL;
			g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState = 0;
			g_aMiniBossEnemy[nCntMiniBossEnemy].nLife = 180;			//敵の体力

			//頂点設定
			pVtx[nCntMiniBossEnemy * 4].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x - 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);
			pVtx[nCntMiniBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aMiniBossEnemy[nCntMiniBossEnemy].pos.x + 90, g_aMiniBossEnemy[nCntMiniBossEnemy].pos.y + 90, 0.0f);

			g_nNumMiniBossEnemy++;							//敵の総数を加算する
			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffMiniBossEnemy->Unlock();
}

//=========================================================================================================================
// 敵の取得
//=========================================================================================================================
MiniBossEnemy *GetMiniBossEnemy(void)
{
	return &g_aMiniBossEnemy[0];
}
//=========================================================================================================================
// 敵のダメージ処理
//=========================================================================================================================
void HitMiniBossEnemy(int nCntMiniBossEnemy, int nDamage)
{

	g_aMiniBossEnemy[nCntMiniBossEnemy].nLife -= nDamage;

	Bullet *pBullet;
	pBullet = GetBullet();

	if (g_aMiniBossEnemy[nCntMiniBossEnemy].nLife <= 0)
	{
		//爆発音
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		//爆発
		SetExplosion(g_aMiniBossEnemy[nCntMiniBossEnemy].pos, D3DXCOLOR(255,255,255,255));
		g_aMiniBossEnemy[nCntMiniBossEnemy].bUse = false;

		//敵の得点
		AddScore(156000);

		g_nNumMiniBossEnemy--;						//敵の総数を減らす
		if (g_nNumMiniBossEnemy <= 0)
		{//敵が全滅したら

			//ワーニングコール
			SetWarning();

			//ワーキング時に弾をなくす
			for (int nCount = 0; nCount < MAX_BULLET; nCount++, pBullet++)
			{
				//弾を消す
				pBullet->bUse = false;
			}
			//ボス設置
			SetBossEnemy(D3DXVECTOR3(SCREEN_WIDTH / 2, -500.0f, 0.0f), 0);
		}
	}
	else
	{
		VERTEX_2D *pVtx;			//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得

		//バグ発見　ボス倒したあとリトライのチュートリアルでエラー
		g_pVtxBuffMiniBossEnemy->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		g_aMiniBossEnemy[nCntMiniBossEnemy].state = MINIBOSSENEMYSTATE_DAMAGE;
		g_aMiniBossEnemy[nCntMiniBossEnemy].nCounterState = 5;		//ダメージの時間　数値が大きいほど遅くなる

		//頂点カラー設定
		pVtx[nCntMiniBossEnemy * 4].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntMiniBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntMiniBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntMiniBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffMiniBossEnemy->Unlock();
	}
}
