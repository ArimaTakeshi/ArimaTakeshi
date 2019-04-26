//=========================================================================================================================
//
// 弾処理 [bullet.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "bullet.h"		//弾
#include "explosion.h"	//爆発
#include "enemy.h"		//敵
#include "player.h"		//プレイヤー
#include "minibossenemy.h"//中ボス
#include "effect.h"		//エフェクト
#include "bossenemy.h"	//ボス
#include "sound.h"		//サウンド

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define BULLET_TEXTURE_NAME			"data\\TEXTURE\\たまご.png"			//読み込むテクスチャファイル
#define BULLET_LIFE					(150)								//弾の寿命
#define BULLET_TEXTURE_UV_U			(1.0f)								//弾アニメーションU範囲
#define BULLET_TEXTURE_UV_V			(1.0f)								//弾アニメーションV範囲

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファへのポインタ
Bullet g_aBullet[MAX_BULLET];						//弾の情報

//=========================================================================================================================
// 弾初期化処理
//=========================================================================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ
	int nCntBullet;					//弾カウント

	//デバイスの取得
	pDevice = GetDevice();

	//弾の情報の初期化
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aBullet[nCntBullet].nLife = BULLET_LIFE;
		g_aBullet[nCntBullet].bUse = false;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		BULLET_TEXTURE_NAME,
		&g_pTextureBullet
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//弾をカウント
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
		pVtx[1].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, BULLET_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(BULLET_TEXTURE_UV_U, BULLET_TEXTURE_UV_V);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================================
// 弾終了処理
//=========================================================================================================================
void UninitBullet(void)
{
	//テクスチャーの破棄
	if (g_pTextureBullet!= NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet= NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffBullet!= NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet= NULL;
	}
}

//=========================================================================================================================
// 弾更新処理
//=========================================================================================================================
void UpdateBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ
	int nCntBullet;					//弾カウント
	
	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//弾をカウント
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			int nCntEnemy;		//敵カウント
			Enemy *pEnemy;		//敵ポインタ
			MiniBossEnemy *pMiniBossEnemy;	//ミニボスのポインタ
			BossEnemy *pBossEnemy;
		
			//敵の取得
			pEnemy = GetEnemy();

			//ミニボスの取得
			pMiniBossEnemy = GetMiniBossEnemy();

			//ボスの取得
			pBossEnemy = GetBossEnemy();

			//一定時間で減少
			g_aBullet[nCntBullet].nLife--;

			//移動値代入
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;	

			//頂点設定
			pVtx[nCntBullet * 4].pos	 = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 29, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 4, g_aBullet[nCntBullet].pos.y - 29, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 15, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 4, g_aBullet[nCntBullet].pos.y - 15, 0.0f);
			//頂点カラー設定
			pVtx[nCntBullet * 4].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);

			//
			//
			//種類
			//
			//
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)	//プレイヤーの弾
			{
				/*//打った時の音
				PlaySound(SOUND_LABEL_SE_SHOT);*/
				/*エフェクト
				SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 5.0f, 10);*/

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{
						if (pEnemy->pos.x - 25 < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + 25 > g_aBullet[nCntBullet].pos.x && pEnemy->pos.y - 25 < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + 25 > g_aBullet[nCntBullet].pos.y)
						{
							//ヒット音
							PlaySound(SOUND_LABEL_SE_HIT000);
							//ダメージ

							HitEnemy(nCntEnemy, 1);
							g_aBullet[nCntBullet].bUse = false;		//使用していない状態
						}
					}
				}
				if (pMiniBossEnemy->bUse == true)
				{
					if (pMiniBossEnemy->move.y == 0)
					{
						if (pMiniBossEnemy->pos.x - 70 < g_aBullet[nCntBullet].pos.x && pMiniBossEnemy->pos.x + 70 > g_aBullet[nCntBullet].pos.x && pMiniBossEnemy->pos.y - 70 < g_aBullet[nCntBullet].pos.y && pMiniBossEnemy->pos.y + 90 > g_aBullet[nCntBullet].pos.y)
						{
							//ヒット音
							PlaySound(SOUND_LABEL_SE_HIT000);
							//ダメージ
							HitMiniBossEnemy(0, 1);
							g_aBullet[nCntBullet].bUse = false;		//使用していない状態
						}
					}
				}
				if (pBossEnemy->bUse == true)
				{
					if (pBossEnemy->move.y == 0)
					{
						if (pBossEnemy->pos.x - 90 < g_aBullet[nCntBullet].pos.x && pBossEnemy->pos.x + 90 > g_aBullet[nCntBullet].pos.x && pBossEnemy->pos.y - 90 < g_aBullet[nCntBullet].pos.y && pBossEnemy->pos.y + 90 > g_aBullet[nCntBullet].pos.y)
						{
							//ヒット音
							PlaySound(SOUND_LABEL_SE_HIT000);
							//ダメージ
							HitBossEnemy(0, 1);
							g_aBullet[nCntBullet].bUse = false;		//使用していない状態
						}
					}
				}
				if (g_aBullet[nCntBullet].nLife <= 0)
				{//ライフが0以下になった場合
					/*SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));*/
					g_aBullet[nCntBullet].bUse = false;		//使用していない状態
				}

				if (g_aBullet[nCntBullet].pos.y < -0.1 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT + 0.1 || g_aBullet[nCntBullet].pos.x < -0.1 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 0.1)
				{//画面外の場合
					g_aBullet[nCntBullet].bUse = false;		//使用していない状態
				}
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
			{
				//int nCntPlayer;
				Player *pPlayer;

				//プレイヤーの取得
				pPlayer = GetPlayer();

				/*for (nCntPlayer = 0; nCntPlayer < MAX_ENEMY; nCntPlayer++, pPlayer++)
				{*/

					if (pPlayer->bUse == true)
					{
						if (pPlayer->pos.x - 5 < g_aBullet[nCntBullet].pos.x && pPlayer->pos.x + 5 > g_aBullet[nCntBullet].pos.x && pPlayer->pos.y - 5 < g_aBullet[nCntBullet].pos.y && pPlayer->pos.y + 5 > g_aBullet[nCntBullet].pos.y)
						{
							//ヒット音
							PlaySound(SOUND_LABEL_SE_HIT001);
							//ダメージ
							HitPlayer(1);
							g_aBullet[nCntBullet].bUse = false;		//使用していない状態
						}
					}
				/*}*/

				
			}

			if (g_aBullet[nCntBullet].pos.y < -10 || g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT + 10 || g_aBullet[nCntBullet].pos.x < -10 || g_aBullet[nCntBullet].pos.x > SCREEN_WIDTH + 10)
			{//画面外の場合
				g_aBullet[nCntBullet].bUse = false;		//使用していない状態
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}

//=========================================================================================================================
// 弾描画処理
//=========================================================================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ
	int nCntBullet;					//弾カウント

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffBullet, 
		0, 
		sizeof(VERTEX_2D)
	);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

	//ポリゴンの描画
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//弾をカウント
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾がある場合
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}
//=========================================================================================================================
// 弾の設定処理
//=========================================================================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, BULLETTYPE Type)
{
	int nCntBullet;			//弾カウント

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffBullet->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//弾をカウント
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されていない場合
			g_aBullet[nCntBullet].pos = pos;		//pos値代入
			g_aBullet[nCntBullet].move = move;		//move値代入
			g_aBullet[nCntBullet].col = col;		//color値代入
			g_aBullet[nCntBullet].type = Type;
			g_aBullet[nCntBullet].nLife = BULLET_LIFE;		//ライフ設定
			g_aBullet[nCntBullet].bUse = true;		//使用している状態にする

			//頂点設定
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y - 10, 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10, g_aBullet[nCntBullet].pos.y + 10, 0.0f);
			//頂点カラー設定
			pVtx[nCntBullet * 4].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);
			pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(g_aBullet[nCntBullet].col.r, g_aBullet[nCntBullet].col.g, g_aBullet[nCntBullet].col.b, g_aBullet[nCntBullet].col.a);

			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffBullet->Unlock();
}
//=========================================================================================================================
// バレットの取得処理
//=========================================================================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}