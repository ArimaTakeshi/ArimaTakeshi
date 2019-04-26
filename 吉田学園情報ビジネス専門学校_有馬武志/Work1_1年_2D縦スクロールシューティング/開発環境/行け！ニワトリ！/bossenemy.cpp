//=========================================================================================================================
//
// 敵処理 [bossenemy.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "bossenemy.h"		//敵
#include "explosion.h"		//爆発
#include "bullet.h"			//弾
#include "Game.h"			//ゲーム
#include "score.h"			//スコア
#include "sound.h"			//サウンド
#include "bossenemy.h"		//ボス
#include "player.h"			//プレイヤー
//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_TYPE_BOSSENEMY					(1)									// 敵の種類
#define BOSSENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\enemy000.png"	//読み込むテクスチャファイル1
#define BOSSENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\enemy000.png"		//読み込むテクスチャファイル2
#define BOSSENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\enemy000.png"		//読み込むテクスチャファイル3
#define BOSSENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\enemy000.png"		//読み込むテクスチャファイル4
#define BOSSENEMY_TEXTURE_UV_U				(1.0f)								//テクスチャアニメーションU範囲
#define BOSSENEMY_TEXTURE_UV_V				(1.0f)								//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBossEnemy[MAX_TYPE_BOSSENEMY] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBossEnemy = NULL;								//頂点バッファへのポインタ
BossEnemy g_aBossEnemy[MAX_ENEMY];												//敵の情報

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
void InitBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBossEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//敵の情報の初期化
	for (int nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{//敵をカウント
		g_aBossEnemy[nCntBossEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBossEnemy[nCntBossEnemy].move = D3DXVECTOR3(0.0f, 2.0f, 0.0f);
		g_aBossEnemy[nCntBossEnemy].nType = 0;
		g_aBossEnemy[nCntBossEnemy].bUse = false;
		g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_NORMAL;
		g_aBossEnemy[nCntBossEnemy].nCounterState = 0;
		g_aBossEnemy[nCntBossEnemy].nLife = 0;			//敵の体力
	}

	//テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_1,
		&g_apTextureBossEnemy[0]
	);
	/*D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_2,
		&g_apTextureBossEnemy[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_3,
		&g_apTextureBossEnemy[2]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		BOSSENEMY_TEXTURE_NAME_4,
		&g_apTextureBossEnemy[3]
	);*/

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBossEnemy,
		NULL
	);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(BOSSENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,BOSSENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BOSSENEMY_TEXTURE_UV_U,BOSSENEMY_TEXTURE_UV_V);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBossEnemy->Unlock();
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitBossEnemy(void)
{
	int nCntTex;

	//テクスチャの開放
	for (nCntTex = 0; nCntTex < MAX_TYPE_BOSSENEMY; nCntTex++)
	{
		if (g_apTextureBossEnemy[nCntTex] != NULL)
		{
			g_apTextureBossEnemy[nCntTex]->Release();
			g_apTextureBossEnemy[nCntTex] = NULL;
		}
	}

	//頂点バッファの開放
	if (g_pVtxBuffBossEnemy != NULL)
	{
		g_pVtxBuffBossEnemy->Release();
		g_pVtxBuffBossEnemy = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateBossEnemy(void)
{
	int nCntBossEnemy;

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	Player *pPlayer;

	pPlayer = GetPlayer();

	for (nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{
		if (g_aBossEnemy[nCntBossEnemy].bUse == true)	//敵が使用されている
		{
			//ボスのスピード
			g_aBossEnemy[nCntBossEnemy].pos.y += g_aBossEnemy[nCntBossEnemy].move.y;

			//頂点設定
			pVtx[nCntBossEnemy * 4].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 90, g_aBossEnemy[nCntBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 90, g_aBossEnemy[nCntBossEnemy].pos.y - 90, 0.0f);
			pVtx[nCntBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 90, g_aBossEnemy[nCntBossEnemy].pos.y + 90, 0.0f);
			pVtx[nCntBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 90, g_aBossEnemy[nCntBossEnemy].pos.y + 90, 0.0f);

			//止まる処理
			if (g_aBossEnemy[nCntBossEnemy].pos.y >= 200)
			{
				g_aBossEnemy[nCntBossEnemy].move.y = 0;

				//攻撃スピード
				static int nCount = 0;

				switch (g_aBossEnemy[nCntBossEnemy].state)
				{
				case BOSSENEMYSTATE_NORMAL:
					g_aBossEnemy[nCntBossEnemy].nCounterState++;

					nCount++;
					//敵の弾のランダム
					if (rand() % 10 == 0)
					if(nCount % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;
						

						
						//敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.0f, cosf(D3DX_PI + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.0f, cosf(D3DX_PI * 0 + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						//敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.0f, cosf(D3DX_PI + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.0f, cosf(D3DX_PI * 0 + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.0f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//追尾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, cosf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						/*SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  2.0f, cosf(D3DX_PI - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  2.0f, cosf(D3DX_PI * 0 - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  2.0f, cosf(D3DX_PI * 0.5f - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  2.0f, cosf(D3DX_PI * -0.5f - nAngle2) *  2.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);*/
					}
					break;

				case BOSSENEMYSTATE_DAMAGE:
					g_aBossEnemy[nCntBossEnemy].nCounterState--;
					if (g_aBossEnemy[nCntBossEnemy].nCounterState <= 0)
					{
						g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_NORMAL;

						//頂点カラー設定
						pVtx[nCntBossEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
						pVtx[nCntBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}

					//敵の弾のランダム
					if (rand() % 10 == 0)
					{
						static float nAngle = 0.05f;
						static float nAngle2 = nAngle;
						nAngle2 += nAngle;

						//敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						

						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 2.5f, cosf(D3DX_PI + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 2.5f, cosf(D3DX_PI * 0 + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 2.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//紫敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  4.5f, cosf(D3DX_PI + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) *  4.5f, cosf(D3DX_PI * 0 + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

						//敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) * 1.5f, cosf(D3DX_PI - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 1.5f, cosf(D3DX_PI * 0 - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f - nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  2.5f, cosf(D3DX_PI - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  2.5f, cosf(D3DX_PI * 0 - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  2.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  2.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

						//紫敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  4.5f, cosf(D3DX_PI - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) *  4.5f, cosf(D3DX_PI * 0 - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  4.5f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);



						//紫　回転　敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI - nAngle2) *  3.0f, cosf(D3DX_PI - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 - nAngle2) * 3.0f, cosf(D3DX_PI * 0 - nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f - nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f - nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);



						//紫　回転　敵の弾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);


						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) *  3.0f, cosf(D3DX_PI + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 3.0f, cosf(D3DX_PI * 0 + nAngle2) * 3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * 0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) *  3.0f, cosf(D3DX_PI * -0.5f + nAngle2) *  3.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f), BULLETTYPE_ENEMY);

						//追尾
						SetBullet(g_aBossEnemy[nCntBossEnemy].pos, D3DXVECTOR3(sinf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, cosf(atan2f(-g_aBossEnemy[nCntBossEnemy].pos.x - -pPlayer->pos.x, -g_aBossEnemy[nCntBossEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
					}
					break;
				}
			}
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffBossEnemy->Unlock();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawBossEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスポインタ

								//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBossEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{//敵をカウント
		if (g_aBossEnemy[nCntBossEnemy].bUse == true)
		{//敵がいる場合
		 // テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBossEnemy[g_aBossEnemy[nCntBossEnemy].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBossEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// 敵の設定
//=========================================================================================================================
void SetBossEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntBossEnemy;		//敵カウント

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

								//頂点バッファをロック
	g_pVtxBuffBossEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntBossEnemy = 0; nCntBossEnemy < MAX_ENEMY; nCntBossEnemy++)
	{//敵をカウント
		if (g_aBossEnemy[nCntBossEnemy].bUse == false)
		{//爆発が使用されていない
			g_aBossEnemy[nCntBossEnemy].pos = pos;			//pos値代入
			g_aBossEnemy[nCntBossEnemy].nType = nType;		//nType値代入
			g_aBossEnemy[nCntBossEnemy].bUse = true;		//使用している状態にする
			g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_NORMAL;
			g_aBossEnemy[nCntBossEnemy].nCounterState = 0;
			g_aBossEnemy[nCntBossEnemy].nLife = 250;			//敵の体力

																		//頂点設定
			pVtx[nCntBossEnemy * 4].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 150, g_aBossEnemy[nCntBossEnemy].pos.y - 150, 0.0f);
			pVtx[nCntBossEnemy * 4 + 1].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 150, g_aBossEnemy[nCntBossEnemy].pos.y - 150, 0.0f);
			pVtx[nCntBossEnemy * 4 + 2].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x - 150, g_aBossEnemy[nCntBossEnemy].pos.y + 150, 0.0f);
			pVtx[nCntBossEnemy * 4 + 3].pos = D3DXVECTOR3(g_aBossEnemy[nCntBossEnemy].pos.x + 150, g_aBossEnemy[nCntBossEnemy].pos.y + 150, 0.0f);

			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffBossEnemy->Unlock();
}

//=========================================================================================================================
// 敵の取得
//=========================================================================================================================
BossEnemy *GetBossEnemy(void)
{
	return &g_aBossEnemy[0];
}
//=========================================================================================================================
// 敵のダメージ処理
//=========================================================================================================================
void HitBossEnemy(int nCntBossEnemy, int nDamage)
{

	g_aBossEnemy[nCntBossEnemy].nLife -= nDamage;
	if (g_aBossEnemy[nCntBossEnemy].nLife <= 0)
	{
		//爆発音
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		//爆発
		SetExplosion(g_aBossEnemy[nCntBossEnemy].pos, D3DXCOLOR(255, 255, 255, 255));
		g_aBossEnemy[nCntBossEnemy].bUse = false;

		MODE pMode;
		pMode = *GetMode();

		if (pMode == MODE_GAME)
		{
			//敵の得点
			AddScore(1234567);

			//秒数カウンター
			int nCount = 0;

			if ((nCount % 250) == 0)
			{//敵が全滅したら
				SetGameState(GAMESTATE_CLEAR);
			}
		}
	}
	else
	{
		VERTEX_2D *pVtx;			//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBossEnemy->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		g_aBossEnemy[nCntBossEnemy].state =BOSSENEMYSTATE_DAMAGE;
		g_aBossEnemy[nCntBossEnemy].nCounterState = 5;		//ダメージの時間　数値が大きいほど遅くなる

		//頂点カラー設定
		pVtx[nCntBossEnemy * 4].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntBossEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntBossEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntBossEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffBossEnemy->Unlock();
	}
}
