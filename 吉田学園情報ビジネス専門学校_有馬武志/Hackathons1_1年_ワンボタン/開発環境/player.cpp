//=========================================================================================================//
//
// 自機 処理 [player.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "input.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "enemy.h"
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点BUFFERへのポインタ
PLAYER g_Player;
int g_nAppears;

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define PLAYER_TextureName		"data/TEXTURE/player000.png"	//TEXTUREの名前
#define VERTEX_NUM				(4)				// 頂点の数
#define PRIMITIVE_NUM			(2)				// プリミティブの数
#define RECAST_TIME				(4)				//弾の発射速度

#define MOVEPOLYGON				(1.0f)			//ポリゴンの進む速さ
#define SLIPPLAYER				(0.12f)
#define WIDETEXTURE				(0.5f)			//TEXTUREの幅
#define HEIGHTTEXTURE			(1.0f)			//TEXTUREの高さ
#define FIELD					(SCREEN_HEIGHT / 10 * 8)


//=========================================================================================================//
// * プレイヤーの描画処理1	初期化処理
//=========================================================================================================//
void InitPlayer(void)
{
	srand((unsigned int)time(0));
	LPDIRECT3DDEVICE9 pDevice;	
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3{ 0.0f, FIELD, 0.0f };		//ポリゴンの中心
	g_Player.move = D3DXVECTOR3{ 0,0,0.0f };	//ポリゴンの移動
	g_Player.nHP = 100;
	g_Player.nLevel = 1;
	g_Player.nMAX_HP = 100;
	g_Player.nAttack = 10;
	g_Player.nDefense = 5;
	g_Player.nJump = 0;
	g_Player.nCntAnim = 0;
	g_Player.nPtnAnim = 0;
	g_Player.nMeter = 0;
	g_Player.nEXP = 0;
	g_Player.nGold = 0;
	g_Player.nScore = 0;
	g_Player.nMAX_EXP = 50;
	g_Player.fAngle = D3DX_PI;
	g_Player.bMove = false;
	g_Player.bUse = true;

	g_nAppears = 0;

	D3DXCreateTextureFromFile(pDevice, PLAYER_TextureName, &g_pTexturePlayer);

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * VERTEX_NUM,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// A = 透明度
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(WIDETEXTURE, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, HEIGHTTEXTURE);
	pVtx[3].tex = D3DXVECTOR2(WIDETEXTURE, HEIGHTTEXTURE);

	//頂点BUFFERをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//=========================================================================================================//
// * プレイヤーの描画処理2	終了処理
//=========================================================================================================//
void UninitPlayer(void)
{//テクスチャの破棄
	g_Player.bUse = false;
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//=========================================================================================================//
// * プレイヤーの描画処理3	更新処理
//=========================================================================================================//
void UpdatePlayer(void)
{
	int nCntEnemy;
	static int nCntTime;
	char aStr[256];

	if (g_Player.bUse == true)
	{
		nCntTime++;
		if (nCntTime % 30 == 0 && g_Player.nHP < g_Player.nMAX_HP) { g_Player.nHP++; }
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
		//頂点BUFFERをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		g_Player.nCntAnim++;
		if (GetKeyboardTrigger(DIK_RETURN) == true && g_Player.nJump < 2)
		{//ジャンプは2回まで
			g_Player.move.y = -20.0f;
			g_Player.nJump++;
			PlaySound(SOUND_LABEL_BOTTON001);
		}
		if (g_Player.nJump == 2) { g_Player.fAngle -= 0.13f; }
		if (g_Player.pos.y < FIELD) { g_Player.move.y += 1.0f; }

		if (g_Player.pos.x > SCREEN_WIDTH / 3)
		{
			g_Player.bMove = true;
			g_Player.move.x = 0.0f;
			g_Player.nMeter++;
			EnemyAppears();
		}
		else
		{
			g_Player.bMove = false;
			g_Player.move.x += 1.5f;
		}

		g_Player.pos += g_Player.move;//x移動のみ
		//移動量低下(空気抵抗等のつもり)
		g_Player.move.x += (0.0f - g_Player.move.x) * BULLET_SLIP;
		if (g_Player.pos.y > FIELD)
		{
			g_Player.pos.y = FIELD;
			g_Player.nJump = 0;
			g_Player.fAngle = D3DX_PI;
		}

		//頂点座標の設定
		//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);

		Enemy *pEnemy = GetEnemy();
		for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
		{
			if (pEnemy[nCntEnemy].bUse == true)
			{
				if (HitAim(pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].nSize) == true && pEnemy[nCntEnemy].State != ENEMYSTATE_DAMAGE)
				{//当たっているなら
					g_Player.pos.y = FIELD;
					g_Player.nJump = 0;
					g_Player.fAngle = D3DX_PI;
					g_Player.move.x = 0.0f;
					g_Player.move.x -= 20.0f;
					g_Player.pos.x -= 50;
					HitEnemy(nCntEnemy, g_Player.nAttack);
					HitPlayer(pEnemy[nCntEnemy].nAtk);
					PlaySound(SOUND_LABEL_BOTTON000);
				}
			}
		}

		pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fAngle) * PLAYER_POSY3) + (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y - (sinf(g_Player.fAngle) * PLAYER_POSX3) + (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fAngle) * PLAYER_POSY3) - (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y + (sinf(g_Player.fAngle) * PLAYER_POSX3) + (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fAngle) * PLAYER_POSY3) + (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y - (sinf(g_Player.fAngle) * PLAYER_POSX3) - (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fAngle)* PLAYER_POSY3) - (cosf(g_Player.fAngle) * PLAYER_POSX3), g_Player.pos.y + (sinf(g_Player.fAngle) * PLAYER_POSX3) - (cosf(g_Player.fAngle) * PLAYER_POSY3), 0.0f);

		if ((g_Player.nCntAnim % 10) == 0)
		{// アニメーション速度
			g_Player.nPtnAnim = (g_Player.nPtnAnim + 1) % 2;		// パターンNo.更新
																													// テクスチャ設定
			pVtx[0].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim + 0.5f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f * g_Player.nPtnAnim + 0.5f, 1.0f);
		}

		//頂点BUFFERをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
	wsprintf(&aStr[0], "%d / %d", g_Player.nHP, g_Player.nMAX_HP);
	ChangeFont(true, &aStr[0], 4, FONTSTATE_NONE);
	wsprintf(&aStr[0], "%d", g_Player.nGold);
	ChangeFont(true, &aStr[0], 7, FONTSTATE_NONE);
	wsprintf(&aStr[0], "SCORE：%d", g_Player.nScore);
	ChangeFont(true, &aStr[0], 6, FONTSTATE_NONE);
	wsprintf(&aStr[0], "次のレベルまで %d", g_Player.nMAX_EXP - g_Player.nEXP);
	ChangeFont(true, &aStr[0], 5, FONTSTATE_NONE);
	wsprintf(&aStr[0], "Lv %d", g_Player.nLevel);
	ChangeFont(true, &aStr[0], 8, FONTSTATE_NONE);
}
//=========================================================================================================//
// * 弾の当たり判定
//=========================================================================================================//
bool HitAim(D3DXVECTOR3 aim, int nLength)
{
	float fLengthX;			//弾の中心から目標の中心までの距離X
	float fLengthY;			//弾の中心から目標の中心までの距離Y
	float fLengthAim;		//目標までの距離(斜)
	float fAimSteep = 1.0;	//目標までの角度 -> 初期化
	float fSteep[2] = { 1.0f, 1.0f };	//X軸のマイナスの保存用 -> 初期化

	float fPercentY = 1.0f;		//楕円時のYの倍率
	float fPercentX = 1.0f;		//楕円時のXの倍率

	fLengthX = aim.x - g_Player.pos.x;	//差Xを代入
	fLengthY = aim.y - g_Player.pos.y;	//差Yを代入
	if (fLengthX < 0.0f)
	{//Xの値がマイナスならプラスに
		fLengthX *= -1;	//X反転
		fSteep[0] *= -1;	//X方向マイナスを保存
	}
	if (fLengthY < 0.0f)
	{//Yの値がマイナスならプラスに
		fLengthY *= -1;		//Y反転
		fSteep[1] *= -1;	//Y方向マイナスを保存
	}


	//距離(斜)を2乗の状態で代入
	fLengthAim = (fLengthX * fLengthX) + (fLengthY * fLengthY);
	fLengthAim -= nLength * nLength;

	
	if (fLengthAim < 60 * 60)
	{//判定　2乗された状態なので
		return true;
	}
	else
	{
		return false;
	}
}
//=========================================================================================================//
// * プレイヤーの描画処理4	描画処理
//=========================================================================================================//
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスを取得する
	pDevice = GetDevice();

	//頂点BUFFERをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定

									//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの描画
	if (g_Player.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	}

}
//=========================================================================================================//
// * プレイヤーの情報代入処理
//=========================================================================================================//
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
//=========================================================================================================//
// * プレイヤーの描画処理4	描画処理
//=========================================================================================================//
void EnemyAppears(void)
{
	if (g_Player.nMeter == 1 && g_nAppears == 0)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 50 && g_nAppears == 1)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 150 && g_nAppears == 2)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 300 && g_nAppears == 3)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 330 && g_nAppears == 4)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 430 && g_nAppears == 5)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 530 && g_nAppears == 6)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 600 && g_nAppears == 7)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 610 && g_nAppears == 8)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 20, 20, 20, 40, 200, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 620 && g_nAppears == 9)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 680 && g_nAppears == 10)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 750 && g_nAppears == 11)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 800 && g_nAppears == 12)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 900 && g_nAppears == 13)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 910 && g_nAppears == 14)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 920 && g_nAppears == 15)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 930 && g_nAppears == 16)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1100 && g_nAppears == 17)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1150 && g_nAppears == 18)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1180 && g_nAppears == 19)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1200 && g_nAppears == 20)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD - 100, 0.0f), 3, 200, 90, 40, 20, 500, 300, 3000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1220 && g_nAppears == 21)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1225 && g_nAppears == 22)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1230 && g_nAppears == 23)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1270 && g_nAppears == 24)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1370 && g_nAppears == 25)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1375 && g_nAppears == 26)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1380 && g_nAppears == 27)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1385 && g_nAppears == 28)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1390 && g_nAppears == 29)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1450 && g_nAppears == 30)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1480 && g_nAppears == 31)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1510 && g_nAppears == 32)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1515 && g_nAppears == 33)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1520 && g_nAppears == 34)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1525 && g_nAppears == 35)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD - 100, 0.0f), 4, 250, 130, 70, 40, 700, 500, 5000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1600 && g_nAppears == 36)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1605 && g_nAppears == 37)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1610 && g_nAppears == 38)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1615 && g_nAppears == 39)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1620 && g_nAppears == 40)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1625 && g_nAppears == 41)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1630 && g_nAppears == 42)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1730 && g_nAppears == 43)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 80, 40, 40, 100, 500, 30000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1770 && g_nAppears == 44)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 1, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1950 && g_nAppears == 45)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 0, 40, 10, 5, 5, 10, 5, 300, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1955 && g_nAppears == 46)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1955 && g_nAppears == 47)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 1, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1960 && g_nAppears == 48)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 1, 40, 40, 20, 20, 40, 20, 15000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1965 && g_nAppears == 49)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD + 10, 0.0f), 2, 40, 80, 40, 40, 100, 500, 30000, ENEMYTYPE_NORMALENEMY);
	}
	if (g_Player.nMeter == 1990 && g_nAppears == 50)
	{//敵の出現
		g_nAppears++;
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH, FIELD - 120, 0.0f), 5, 300, 100, 50, 30, 1000, 5000, 100000, ENEMYTYPE_BOSSENEMY);
	}
}
//=========================================================================================================================
// 敵の弾当たり処理
//=========================================================================================================================
void HitPlayer(int nAtk)
{
	int nDamage;
	int nRand;
	char aStr[256];

	nRand = rand() % 15 + 45;
	PLAYER *pPlayer = GetPlayer();

	// ライフが減少
	nDamage = nAtk - (g_Player.nDefense * nRand / 100);
	if (nDamage < 0) { nDamage = 0; }
	g_Player.nHP -= nDamage;
	wsprintf(&aStr[0], "%d", nDamage);
	SetFont(RECT{ (int)g_Player.pos.x - 50 , (int)g_Player.pos.y - 50, (int)g_Player.pos.x + 50, (int)g_Player.pos.y }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 2, FONTSTATE_RANKDELETE);

	g_Player.nScore += nDamage;
	g_Player.nGold += nDamage;

	AddScore(SCORETYPE_RNKING_NO1, g_Player.nScore);

	if (g_Player.nHP < 1)
	{// ライフが0以下になった場合
		g_Player.bUse = false;				// 使用してない状態
		g_Player.nHP = 0;
		g_Player.bMove = false;
		g_Player.nScore += g_Player.nMeter;
		SetGameState(GAMESTATE_END, MODE_RESULT, 150);
	}
}