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
#include "minibossenemy.h"		//中ボス
#include "explosion.h"			//爆発
#include "bullet.h"				//弾
#include "Game.h"				//ゲーム
#include "score.h"				//スコア
#include "sound.h"				//サウンド
#include "player.h"				//プレイヤー

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_TYPE_ENEMY					(4)									// 敵の種類
#define ENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\enemy000.png"		//読み込むテクスチャファイル1
#define ENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\enemy001.png"		//読み込むテクスチャファイル2
#define ENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\enemy002.png"		//読み込むテクスチャファイル3
#define ENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\enemy003.png"		//読み込むテクスチャファイル4
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
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 5;			//敵の体力
		g_nNumEnemy = 0;						//敵の総数クリア
	}

	//テクスチャの読み込み(４体分)
	D3DXCreateTextureFromFile
	(
		pDevice,
		ENEMY_TEXTURE_NAME_1,
		&g_apTextureEnemy[0]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		ENEMY_TEXTURE_NAME_2,
		&g_apTextureEnemy[1]
	);
	D3DXCreateTextureFromFile
	(
		pDevice,
		ENEMY_TEXTURE_NAME_3,
		&g_apTextureEnemy[2]
	);
	D3DXCreateTextureFromFile
	(
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
	//チュートリアルのHP
	if (pMode == MODE_PLAYTUTORIAL)
	{
		g_aEnemy[0].nLife = 100000;
	}

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)	//敵が使用されている
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				g_aEnemy[nCntEnemy].nCounterState++;

				//敵の弾のランダム
				if (rand() % 200 == 0)
				{
					static float nAngle = 0.05f;
					static float nAngle2 = nAngle;
					nAngle2 += nAngle;

					//極注意（3時間のデバック）
					//一人じゃ無理（提供：天才方）
					//何個も同じものを置くと重なってしまうため、注意が必要
					//↓↓
					//敵の弾
					SetBullet(g_aEnemy[nCntEnemy].pos ,D3DXVECTOR3(sinf(atan2f(-g_aEnemy[nCntEnemy].pos.x - -pPlayer->pos.x, -g_aEnemy[nCntEnemy].pos.y - -pPlayer->pos.y)) * 1.5f,cosf(atan2f(-g_aEnemy[nCntEnemy].pos.x - -pPlayer->pos.x, -g_aEnemy[nCntEnemy].pos.y - -pPlayer->pos.y)) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f) , BULLETTYPE_ENEMY);

					//敵の弾
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI + nAngle2) * 1.5f, cosf(D3DX_PI + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0 + nAngle2) * 1.5f, cosf(D3DX_PI * 0 + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * 0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f + nAngle2) * 1.5f, cosf(D3DX_PI * -0.5f + nAngle2) * 1.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f), BULLETTYPE_ENEMY);

							
				}
				break;

			case ENEMYSTATE_DAMAGE:
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//頂点カラー設定
					pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
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
			g_aEnemy[nCntEnemy].nLife = 5;			//敵の体力

			//頂点設定
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y - 30, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y - 30, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - 30, g_aEnemy[nCntEnemy].pos.y + 30, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + 30, g_aEnemy[nCntEnemy].pos.y + 30, 0.0f);

			g_nNumEnemy++;							//敵の総数を加算する
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
//=========================================================================================================================
// 敵のダメージ処理
//=========================================================================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{


	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		//爆発音
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		//爆発
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(255,255,255,255));
		g_aEnemy[nCntEnemy].bUse = false;

		MODE pMode;
		pMode = *GetMode();
		if (pMode == MODE_GAME)
		{
			//敵の得点
			AddScore(12500);

			g_nNumEnemy--;						//敵の総数を減らす
			if (g_nNumEnemy <= 0)
			{//敵が全滅したら
				SetMiniBossEnemy(D3DXVECTOR3(SCREEN_WIDTH / 2, -100.0f, 0.0f), 0);
			}
		}
	}
	else
	{
		VERTEX_2D *pVtx;			//頂点情報へのポインタ

		MODE pMode;
		pMode = *GetMode();

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;		//ダメージの時間　数値が大きいほど遅くなる

		if (pMode == MODE_GAME)
		{
			AddScore(10);
		}

		//頂点カラー設定+
		pVtx[nCntEnemy * 4].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		pVtx[nCntEnemy * 4 + 3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);

		//頂点バッファをアンロック
		g_pVtxBuffEnemy->Unlock();
	}
}
