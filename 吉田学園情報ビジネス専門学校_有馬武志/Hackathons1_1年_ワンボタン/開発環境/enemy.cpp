//=========================================================================================================================
// 
// 敵処理 [enemy.cpp]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "enemy.h"			// 敵
#include "sound.h"			// サウンド

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_ENEMY_TEXTURE				(6)									// 敵の種類
#define ENEMY_TEXTURE_NAME_1			"data\\TEXTURE\\Zako01.png"		// 読み込むテクスチャファイル1
#define ENEMY_TEXTURE_NAME_2			"data\\TEXTURE\\Zako02.png"		// 読み込むテクスチャファイル2
#define ENEMY_TEXTURE_NAME_3			"data\\TEXTURE\\Zako03.png"		// 読み込むテクスチャファイル3
#define ENEMY_TEXTURE_NAME_4			"data\\TEXTURE\\Boss01.png"		// 読み込むテクスチャファイル4
#define ENEMY_TEXTURE_NAME_5			"data\\TEXTURE\\Boss02.png"		// 読み込むテクスチャファイル5
#define ENEMY_TEXTURE_NAME_6			"data\\TEXTURE\\Boss03.png"		// 読み込むテクスチャファイル5

#define ENEMY_TEXTURE_SPEED				(15)								// テクスチャアニメーションスピード
#define ENEMY_TEXTURE_PATTERN			(1)									// テクスチャアニメーションパターン数
#define ENEMY_TEXTURE_UV_U				(1.0f)								// テクスチャアニメーションU範囲
#define ENEMY_TEXTURE_UV_V				(1.0f)								// テクスチャアニメーションV範囲
#define ENEMY_SPEED						(10)								// 敵移動速度

//*************************************************************************************************************************
// グローバル変数宣言
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9			g_apTextureEnemy[MAX_ENEMY_TEXTURE] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffEnemy = NULL;							// 頂点バッファへのポインタ
Enemy						g_aEnemy[MAX_ENEMY];							// 敵の情報

//=========================================================================================================================
// 敵初期化処理
//=========================================================================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得
	int nCntEnemy;		// 敵カウント

	// 敵の情報の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵をカウント
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 敵中心値
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 敵移動値
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 敵色
		g_aEnemy[nCntEnemy].nTexNum = 0;									// 敵種類
		g_aEnemy[nCntEnemy].nLife = 0;										// 敵体力
		g_aEnemy[nCntEnemy].Type = ENEMYTYPE_NORMALENEMY;					// 敵クラス
		g_aEnemy[nCntEnemy].State = ENEMYSTATE_NOMAL;						// 敵状態
		g_aEnemy[nCntEnemy].nCounterState = 0;								// 敵状態カウント
		g_aEnemy[nCntEnemy].nCounterAnim = 0;								// 敵カウンタアニメーション
		g_aEnemy[nCntEnemy].nPatternAnim = 0;								// 敵パターンアニメーション
		g_aEnemy[nCntEnemy].bUse = false;									// 敵使用しているか
	}

	// テクスチャの読み込み(５)
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_1, &g_apTextureEnemy[0]);// 敵1
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_2, &g_apTextureEnemy[1]);// 敵2
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_3, &g_apTextureEnemy[2]);// 敵3
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_4, &g_apTextureEnemy[3]);// 敵4
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_5, &g_apTextureEnemy[4]);// 敵5
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME_6, &g_apTextureEnemy[5]);// 敵5

	// 頂点バッファを生成
    pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL
	);

	// 頂点情報の作成
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock
	(
		0, 
		0, 
		(void**)&pVtx, 
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵をカウント
		// 頂点設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		// 1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		// 頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		// テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENEMY_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);

		pVtx += 4;	// 頂点データのポインタを４つ分進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// 敵終了処理
//=========================================================================================================================
void UninitEnemy(void)
{
	int nCntTex;		// テクスチャカウンタ

	// テクスチャの破棄
	for(nCntTex = 0; nCntTex < MAX_ENEMY_TEXTURE; nCntTex++)
	{// テクスチャカウンタ
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	// 頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=========================================================================================================================
// 敵更新処理
//=========================================================================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;						// 敵カウント

	VERTEX_2D *pVtx;					// 頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵をカウント
		if (g_aEnemy[nCntEnemy].bUse == true)
		{// 敵が使用されている場合
			switch (g_aEnemy[nCntEnemy].State)
			{// 敵状態
			case ENEMYSTATE_NOMAL:	// 通常状態
				break;
			case ENEMYSTATE_DAMAGE:	// ダメージ状態
				g_aEnemy[nCntEnemy].nCounterState--;	// 状態をカウント

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{// 状態カウント終了
					// 色変更
					g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// 状態変化
					g_aEnemy[nCntEnemy].State = ENEMYSTATE_NOMAL;
				}
				break;
			}
			
			if (-100 > g_aEnemy[nCntEnemy].pos.x || SCREEN_WIDTH + 100 < g_aEnemy[nCntEnemy].pos.x || -100 > g_aEnemy[nCntEnemy].pos.y || SCREEN_HEIGHT + 100 < g_aEnemy[nCntEnemy].pos.y)
			{// 画面外の場合
				g_aEnemy[nCntEnemy].bUse = false;
				if (g_aEnemy[nCntEnemy].Type == ENEMYTYPE_BOSSENEMY)
				{
					SetGameState(GAMESTATE_END, MODE_RESULT, 150);
				}
			}

			g_aEnemy[nCntEnemy].nCounterAnim++;		// カウンター加算

			if ((g_aEnemy[nCntEnemy].nCounterAnim % ENEMY_TEXTURE_SPEED) == 0)
			{// アニメーション速度
				g_aEnemy[nCntEnemy].nPatternAnim = (g_aEnemy[nCntEnemy].nPatternAnim + 1) % ENEMY_TEXTURE_PATTERN;		// パターンNo.更新

				// テクスチャ設定
				pVtx[nCntEnemy * 4].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim, 0.0f);
				pVtx[nCntEnemy * 4 + 1].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim + ENEMY_TEXTURE_UV_U, 0.0f);
				pVtx[nCntEnemy * 4 + 2].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim, ENEMY_TEXTURE_UV_V);
				pVtx[nCntEnemy * 4 + 3].tex = D3DXVECTOR2(ENEMY_TEXTURE_UV_U * g_aEnemy[nCntEnemy].nPatternAnim + ENEMY_TEXTURE_UV_U, ENEMY_TEXTURE_UV_V);
			}
			PLAYER *pPlayer = GetPlayer();
			if (pPlayer[0].bMove == true)
			{
				g_aEnemy[nCntEnemy].move.x -= 1.5f;
			}
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
			g_aEnemy[nCntEnemy].move.x += (0.0f - g_aEnemy[nCntEnemy].move.x) * BULLET_SLIP;

			// 頂点設定
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
			// 頂点カラー設定
			pVtx[nCntEnemy * 4].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 1].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 2].col = g_aEnemy[nCntEnemy].col;
			pVtx[nCntEnemy * 4 + 3].col = g_aEnemy[nCntEnemy].col;
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// 描画処理
//=========================================================================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	int nCntEnemy;		// 敵カウント

	// 頂点バッファをデバイスのデータストリームにバインド
    pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffEnemy,
		0,
		sizeof(VERTEX_2D)
	);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵をカウント
		if (g_aEnemy[nCntEnemy].bUse == true)
		{// 敵がいる場合
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nTexNum]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//=========================================================================================================================
// 敵の設定処理
//=========================================================================================================================
void SetEnemy(D3DXVECTOR3 pos, int nTexNum, int nSize, int nLife, int nAtk, int nDff, int nEXP, int nGold, int nScore, ENEMYTYPE Type)
{
	int nCntEnemy;				// 敵カウント

	VERTEX_2D *pVtx;			// 頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffEnemy->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// 敵をカウント
		if (g_aEnemy[nCntEnemy].bUse == false)
		{// 敵が使用されていない
			g_aEnemy[nCntEnemy].pos = pos;									// 位置設定
			g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 敵移動値
			g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 色
			g_aEnemy[nCntEnemy].nTexNum = nTexNum;							// テクスチャ番号設定
			g_aEnemy[nCntEnemy].nSize = nSize;								// 大きさ設定
			g_aEnemy[nCntEnemy].nLife = nLife;								// 体力設定
			g_aEnemy[nCntEnemy].Type = Type;								// 敵種類を設定
			g_aEnemy[nCntEnemy].nAtk = nAtk;
			g_aEnemy[nCntEnemy].nDff = nDff;
			g_aEnemy[nCntEnemy].nEXP = nEXP;
			g_aEnemy[nCntEnemy].nGold = nGold;
			g_aEnemy[nCntEnemy].nScore;
			g_aEnemy[nCntEnemy].State = ENEMYSTATE_NOMAL;					// 状態を設定
			g_aEnemy[nCntEnemy].nCounterState = 0;							// 状態カウンタ初期値設定
			g_aEnemy[nCntEnemy].nCounterAnim = 0;							// カウンター初期値設定
			g_aEnemy[nCntEnemy].nPatternAnim = 0;							// パターンNo.初期値設定
			g_aEnemy[nCntEnemy].bUse = true;								// 使用している状態にする

			// 頂点設定
			pVtx[nCntEnemy * 4].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y - g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);
			pVtx[nCntEnemy * 4 + 3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + g_aEnemy[nCntEnemy].nSize, g_aEnemy[nCntEnemy].pos.y + g_aEnemy[nCntEnemy].nSize, 0.0f);

			break;
		}
	}

	// 頂点バッファをアンロック
	g_pVtxBuffEnemy->Unlock();
}

//=========================================================================================================================
// 敵の取得
//=========================================================================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];		// 値を返す
}

//=========================================================================================================================
// 敵の弾当たり処理
//=========================================================================================================================
void HitEnemy(int nCntEnemy, int nAtk)
{
	int nDamage;
	int nRand;
	char aStr[256];
	nRand = rand() % 40 + 20;
	PLAYER *pPlayer = GetPlayer();
	int nCount;
	for (nCount = 0; nCount < MAX_ENEMY; nCount++)
	{
		g_aEnemy[nCount].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	// ライフが減少
	nDamage = nAtk - (g_aEnemy[nCntEnemy].nDff * nRand / 100);
	if (nDamage < 0) { nDamage = 1; }
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	wsprintf(&aStr[0], "%d", nDamage);
	SetFont(RECT{ (int)g_aEnemy[nCntEnemy].pos.x - 50 , (int)g_aEnemy[nCntEnemy].pos.y - 50, (int)g_aEnemy[nCntEnemy].pos.x + 50, (int)g_aEnemy[nCntEnemy].pos.y }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 3, FONTSTATE_RANKDELETE);
	pPlayer[0].nScore += nDamage;
	pPlayer[0].nGold += nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{// ライフが0以下になった場合
		g_aEnemy[nCntEnemy].bUse = false;				// 使用してない状態
		pPlayer[0].nScore += g_aEnemy[nCntEnemy].nScore;
		pPlayer[0].nEXP += g_aEnemy[nCntEnemy].nEXP;
		pPlayer[0].nGold += g_aEnemy[0].nGold;
		if (pPlayer[0].nEXP >= pPlayer[0].nMAX_EXP)
		{//レベルアップした場合
			while (1)
			{
				pPlayer[0].nLevel++;
				pPlayer[0].nEXP -= pPlayer[0].nMAX_EXP;
				pPlayer[0].nMAX_EXP = pPlayer[0].nMAX_EXP * 130 / 100;
				pPlayer[0].nMAX_HP += 15;
				pPlayer[0].nAttack += 5;
				pPlayer[0].nDefense += 3;
				pPlayer[0].nHP = pPlayer[0].nMAX_HP;
				PlaySound(SOUND_LABEL_BOTTON003);//レベルアップロゴ
				if (pPlayer[0].nEXP < pPlayer[0].nMAX_EXP) { break; }
			}
		}
		if (g_aEnemy[nCntEnemy].Type == ENEMYTYPE_BOSSENEMY)
		{
			pPlayer[0].nScore += pPlayer[0].nGold;
			pPlayer[0].nScore += pPlayer[0].nMeter;
			SetGameState(GAMESTATE_END, MODE_RESULT, 150);
		}
	}
	else
	{// ライフが1以上の場合
		g_aEnemy[nCntEnemy].State = ENEMYSTATE_DAMAGE;		// 状態変化
		g_aEnemy[nCntEnemy].nCounterState = 5;				// 状態カウンタ

		// 色変更
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
	}
}