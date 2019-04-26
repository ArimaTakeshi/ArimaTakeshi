//=========================================================================================================================
//
// 敵処理 [enemy.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "enemy.h"				//敵
#include "explosion.h"			//爆発
#include "Game.h"				//ゲーム
#include "score.h"				//スコア
#include "sound.h"				//サウンド
#include "player.h"				//プレイヤー

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_TYPE_ENEMY					(4)									// 敵の種類
#define ENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\エビフライ.png"		//読み込むテクスチャファイル1
#define ENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\.png"				//読み込むテクスチャファイル2
#define ENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\.png"				//読み込むテクスチャファイル3
#define ENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\.png"				//読み込むテクスチャファイル4
#define ENEMY_HEIGHT					(40)
#define ENEMY_WIDTH						(30)
#define ENEMY_TEXTURE_UV_U				(1.0f)								//テクスチャアニメーションU範囲
#define ENEMY_TEXTURE_UV_V				(1.0f)								//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//頂点バッファへのポインタ
Enemy g_aEnemy[MAX_ENEMY];										//敵の情報
int g_nNumEnemy;												//敵の総数

//=========================================================================================================================
// 初期化処理
//=========================================================================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//敵の情報の初期化
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//敵をカウント
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(3, 3, 3);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 5;			//敵の体力
		g_nNumEnemy = 0;						//敵の総数クリア
	}

	//テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile
	(//１枚目の画像
		pDevice,
		ENEMY_TEXTURE_NAME_1,
		&g_apTextureEnemy[0]
	);
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		ENEMY_TEXTURE_NAME_2,
		&g_apTextureEnemy[1]
	);
	D3DXCreateTextureFromFile
	(//３枚目の画像
		pDevice,
		ENEMY_TEXTURE_NAME_3,
		&g_apTextureEnemy[2]
	);
	D3DXCreateTextureFromFile
	(//４枚目の画像
		pDevice,
		ENEMY_TEXTURE_NAME_4,
		&g_apTextureEnemy[3]
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
		&g_pVtxBuffEnemy,
		NULL
	);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock
	(
		0, 
		0, 
		(void**)&pVtx, 
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
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
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// 終了処理
//=========================================================================================================================
void UninitEnemy(void)
{
	int nCntTex;

	//テクスチャの開放
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=========================================================================================================================
// 更新処理
//=========================================================================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	//頂点情報の作成
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//モードの取得
	MODE pMode;
	pMode = *GetMode();
	//プレイヤーの取得
	Player *pPlayer;
	pPlayer = GetPlayer();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)	//敵が使用されている
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
			//	g_aEnemy[nCntEnemy].move.x = (sinf(atan2(-pPlayer->pos.x - -pPlayer->pos.x, -pPlayer->pos.y - -pPlayer->pos.y))* 0.1f);
			//	g_aEnemy[nCntEnemy].move.x = (cosf(atan2(-pPlayer->pos.x - -pPlayer->pos.x, -pPlayer->pos.y - -pPlayer->pos.y))* 0.1f);

				break;
			case ENEMYSTATE_DAMAGE:
				break;
			}	
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//敵をカウント
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//敵がいる場合
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// 敵の設定
//=========================================================================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;		//敵カウント

	VERTEX_2D *pVtx;			//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//敵をカウント
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//爆発が使用されていない
			g_aEnemy[nCntEnemy].pos = pos;			//pos値代入
			g_aEnemy[nCntEnemy].nType = nType;		//nType値代入
			g_aEnemy[nCntEnemy].bUse = true;		//使用している状態にする
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;	
			g_aEnemy[nCntEnemy].nCounterState = 0;

			//頂点設定
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y - ENEMY_HEIGHT, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_WIDTH, g_aEnemy[nCntEnemy].pos.y + ENEMY_HEIGHT, 0.0f);

			//敵の総数を加算する
			g_nNumEnemy++;							
			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}
//=========================================================================================================================
// 敵の取得
//=========================================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
//============================================
//
//============================================
void DeleteEnemy(void)
{
	//敵の情報の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{//敵をカウント
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_aEnemy[nCntEnemy].nType = 0;
			g_aEnemy[nCntEnemy].bUse = false;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].nLife = 5;			//敵の体力
			g_nNumEnemy = 0;						//敵の総数クリア
		}
	}
}
