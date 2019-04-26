//=========================================================================================================//
//
// 自機 処理 [player.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "sound.h"
#include "fade.h"
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点BUFFERへのポインタ
PLAYER g_Player;

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define PLAYER_TextureName		"data/TEXTURE/santa.png"	//TEXTUREの名前
#define VERTEX_NUM				(4)				// 頂点の数
#define PRIMITIVE_NUM			(2)				// プリミティブの数
#define RECAST_TIME				(4)				//弾の発射速度

#define MOVEPOLYGON				(1.0f)			//ポリゴンの進む速さ
#define SLIPPLAYER				(0.12f)
#define PLAYERSPEED				(4.0f)
#define WIDETEXTURE				(1.0f)			//TEXTUREの幅
#define HEIGHTTEXTURE			(1.0f)			//TEXTUREの高さ
#define PtnWide					(3)
#define PtnHeight				(1)
#define PtnSpeed				(10)
#define PLAYER_RUN				(1.4f)
#define PLAYER_FATK				(2.0f)			//地上の攻撃補正

//=========================================================================================================//
// * プレイヤーの描画処理1	初期化処理
//=========================================================================================================//
void InitPlayer(void)
{
	srand((unsigned int)time(0));
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	g_Player.pos = g_Player.respawn;		//ポリゴンの中心
	g_Player.posold = g_Player.pos;		//ポリゴンの中心
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Player.fMove = 0.0f;
	g_Player.state = PLAYERSTATE_NORMAL;
	g_Player.nScore = 0;
	g_Player.nCntState[0] = 0;
	g_Player.nCntState[1] = 0;
	g_Player.nCntAnim = 0;
	g_Player.bUse = true;
	g_Player.nVibration = 0;
	g_Player.bRun = false;
	g_Player.nEXP = g_Player.nEXPold;
	g_Player.nMAXEXP = g_Player.nMAXEXPold;
	g_Player.nLevel = g_Player.nLevelold;
	g_Player.nMaxLife = 1200 + g_Player.nLevel * 160;
	for (int nCount = 0; nCount < 10; nCount++) { g_Player.bPowerUP[nCount] = g_Player.bPowerUPold[nCount]; }
	for (int nCount = 0; nCount < 10; nCount++) { if (g_Player.bPowerUP[nCount] == true) { g_Player.nMaxLife += 1000; } }
	g_Player.nLife = g_Player.nLifeold;

	g_Player.nAttack = 128 + g_Player.nLevel * 17;
	g_Player.nDefense = 97 + g_Player.nLevel * 13;
	g_Player.nJump = 0;
	g_Player.nCntAnim = 0;
	g_Player.nPtnAnim = 0;
	g_Player.nClear = 0;
	g_Player.nAnimSpeed = PtnSpeed;
	g_Player.nAngle = 0;
	g_Player.fSkyWait = 1.0f;
	g_Player.nLengthX = PLAYER_POSX3;
	g_Player.fSteep = D3DX_PI;
	g_Player.bFall = false;
	g_Player.nPresent[0] = rand() % 4;
	g_Player.nPresent[1] = rand() % 4;
	g_Player.nPresent[2] = rand() % 4;


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
// * プレイヤー	初期化処理 リス時初期化されたら困るもの
//=========================================================================================================//
void InitPlayer0(void)
{
	//g_Player.respawn = D3DXVECTOR3{ 7150, FIELD - 1505, 0.0f };
	g_Player.respawn = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
	g_Player.nEXPold = 0;
	g_Player.nMAXEXPold = 100;
	g_Player.nLifeold = 1360;
	g_Player.nTime[0] = 1800;
	g_Player.nTime[1] = 0;
	g_Player.nLevelold = 1;
	g_Player.nMAXEXP = 100;
	for (int nCount = 0; nCount < 10; nCount++) { g_Player.bPowerUP[nCount] = false; }
	for (int nCount = 0; nCount < 10; nCount++) { g_Player.bClock[nCount] = false; }
	for (int nCount = 0; nCount < 10; nCount++) { g_Player.bPowerUPold[nCount] = false; }
	for (int nCount = 0; nCount < 10; nCount++) { g_Player.bClockold[nCount] = false; }
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
	static int nRunTime = 0;
	static int nTime = 30;
	float fRun = PLAYERSPEED;
	int nCntEnemy;
	int nCntBullet;
	int nCollisionX;
	int nCollisionY;
	char aStr[256];

	SetBullet(D3DXVECTOR3(850.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_SINGLE, D3DX_PI, 0.0f, 20, 20, g_Player.nPresent[0], g_Player.nAttack, 0.0f, BULLETTYPE_PLAYER, 0);
	SetBullet(D3DXVECTOR3(900.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_SINGLE, D3DX_PI, 0.0f, 20, 20, g_Player.nPresent[1], g_Player.nAttack, 0.0f, BULLETTYPE_PLAYER, 0);
	SetBullet(D3DXVECTOR3(950.0f, 30.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_SINGLE, D3DX_PI, 0.0f, 20, 20, g_Player.nPresent[2], g_Player.nAttack, 0.0f, BULLETTYPE_PLAYER, 0);
	nTime++;

	if (g_Player.nClear <= 0)
	{//未クリア
		if (g_Player.nEXP >= g_Player.nMAXEXP)
		{//レベルアップした場合
			while (1)
			{
				PlaySound(SOUND_LABEL_LEVELUP);
				SetWindow(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - g_Player.nCollisionY, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 150, 30, 10, 0, 0, WINDOWSTATE_LEVELUP, WINDOWUSE_NORMAL);
				g_Player.nLevel++;
				g_Player.nEXP -= g_Player.nMAXEXP;
				g_Player.nMAXEXP = g_Player.nMAXEXP * 115 / 100;
				g_Player.nMaxLife += 160;
				g_Player.nLife += 160;
				g_Player.nAttack = 128 + g_Player.nLevel * 17;
				g_Player.nDefense = 109 + g_Player.nLevel * 13;

				if (g_Player.nEXP < g_Player.nMAXEXP) { break; }
			}
		}

		if (g_Player.bUse == true)
		{
			VERTEX_2D *pVtx;		//頂点情報へのポインタ
									//頂点BUFFERをロックし、頂点情報へのポインタを取得
			g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

			g_Player.posold = g_Player.pos;
			g_Player.nCntAnim++;
			g_Player.nCntState[0]--;
			g_Player.nVibration--;
			if (g_Player.state != PLAYERSTATE_DOWN) { g_Player.nCntState[1] = 0; }
			switch (g_Player.state)
			{
			case PLAYERSTATE_DNORMAL:
				if (g_Player.nCntState[0] == 0) { g_Player.state = PLAYERSTATE_NORMAL; }
				break;
			case PLAYERSTATE_SKYATTACK:
				g_Player.fSteep += D3DX_PI * 0.1f;

				if (g_Player.nCntState[0] < 1)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
					g_Player.fSteep = D3DX_PI;
				}
				break;
			case PLAYERSTATE_WAIT:
				//g_Player.nCntState[0]++;
				//g_Player.fSteep = D3DX_PI;
				//if (g_Player.nJump == 0)
				//{ 
				//	PlaySound(SOUND_LABEL_ATTACK004);
				//	g_Player.state = PLAYERSTATE_NORMAL;
				//	SetBullet(D3DXVECTOR3(g_Player.pos.x + sinf(D3DX_PI * 0.25f - D3DX_PI * 0.5f * g_Player.nAngle) * 100, g_Player.pos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_NORMAL, D3DX_PI * 0.5f - D3DX_PI * g_Player.nAngle, 0.0f, 30, 100, 11, g_Player.nAttack, 3.0f, BULLETTYPE_PLAYER, 0);
				//	SetExplosion(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 10, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 50, 7, 1, 1, 5, g_Player.nAttack * 2, ANIMATION_NORMAL, EXPLOSIONSTATE_EHIT, USETYPE_PLAYER, 0, D3DX_PI);
				//}
				break;
			case PLAYERSTATE_SATTACK:
				//g_Player.nCntState[0]++;
				//if (g_Player.nAngle == PLAYERANGLE_RIGHT) { g_Player.fSteep = D3DX_PI * 0.75f; }
				//else { g_Player.fSteep = D3DX_PI * -0.75f; }
				//if (g_Player.nJump == 0) { g_Player.state = PLAYERSTATE_NORMAL; }
				break;
			case PLAYERSTATE_FALL:
				g_Player.pos.y += 2;
				g_Player.posold.y -= 16;
				if (g_Player.nCntState[0] < 1) { g_Player.state = PLAYERSTATE_NORMAL; }
				break;
			case PLAYERSTATE_DOWN:
				if (g_Player.nCntState[0] < 1)
				{
					//g_Player.pos.y -= 14;
					g_Player.posold.y -= 16;
					//g_Player.move.y -= 5.0f;
					//g_Player.posold.y = g_Player.pos.y;
					g_Player.nCntState[0] = 1;
					g_Player.state = PLAYERSTATE_NORMAL;
					g_Player.nPtnAnim = 0;
				}
				break;
			case PLAYERSTATE_CATCH:
				//g_Player.fSteep = D3DX_PI;
				//g_Player.fSkyWait = 1.0f;
				//g_Player.nJump = 1;
				//g_Player.nPtnAnim = 9;
				//if (g_Player.nJump == 0) { g_Player.state = PLAYERSTATE_NORMAL; }
				break;
			case PLAYERSTATE_CLIMBR:
				//g_Player.fSteep -= D3DX_PI * 0.2f;
			case PLAYERSTATE_CLIMBL:
				//g_Player.fSteep += D3DX_PI * 0.1f;
			case PLAYERSTATE_KNOCKBACK:
				if (g_Player.move.y > 0.0f)
				{
					g_Player.bUse = false;
					SetFade(MODE_RESULT, 0);
				}
				break;
			case PLAYERSTATE_BACK:
				//無敵状態カウント
			case PLAYERSTATE_ATTACK:
				if (g_Player.nCntState[0] < 1)
				{
					g_Player.state = PLAYERSTATE_NORMAL;
					g_Player.nPtnAnim = 0;
				}
				break;
			case PLAYERSTATE_INVINCBLE:
				if (g_Player.nCntState[0] < 1) { g_Player.state = PLAYERSTATE_NORMAL; }
				break;
			}
			//if (g_Player.nJump == 0) { g_Player.fSteep = D3DX_PI; }
			nRunTime--;
			g_Player.nLengthY = PLAYER_POSY3;
			g_Player.nCollisionY = PLAYER_CollisionY;
			g_Player.nLengthX = PLAYER_POSX3;
			g_Player.nCollisionX = PLAYER_CollisionX;

			if (g_Player.state != PLAYERSTATE_BACK && g_Player.state != PLAYERSTATE_CATCH && g_Player.nLife > 0)
			{//崖つかまりでもノックBACK状態でもないなら
				GetKeyboardQuick(DIK_A, false);

				if (g_Player.nJump < 2)
				{//ジャンプは2回まで
					if (GetKeyboardTrigger(DIK_SPACE) == true || GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true)
					{
						PlaySound(SOUND_LABEL_JUMP000);
						g_Player.nJump++;
						g_Player.move.y = -16.0f;
						g_Player.bFall = false;
						g_Player.nPtnAnim = 2;
						g_Player.fSkyWait = 1.0f;
						if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true) { g_Player.fMove = 5.0f; }
						else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true) { g_Player.fMove = -5.0f; }
						else { g_Player.fMove = 0.0f; }
						if (g_Player.bRun == true) { g_Player.fMove *= PLAYER_RUN; }
						if (g_Player.state == PLAYERSTATE_DNORMAL)
						{
							g_Player.state = PLAYERSTATE_NORMAL;
							g_Player.nJump = 1;
						}
					}
				}

				if (GetKeyboardTrigger(DIK_Z) == true)
				{//攻撃
					SetExplosion(D3DXVECTOR3(g_Player.pos.x + sinf(D3DX_PI * 0.25f - D3DX_PI * 0.5f * g_Player.nAngle) * 30, g_Player.pos.y + cosf(D3DX_PI * 0.75f) * 30, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 5, 2, 2, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
					g_Player.nCntState[1] = 0;
					if (nTime > 8) { PlaySound(SOUND_LABEL_ATTACK001); nTime = 0; }
					g_Player.state = PLAYERSTATE_SKYATTACK;
					g_Player.nCntState[0] = 12;
					//g_Player.fSkyWait = 0.0f + (g_Player.nCntState[0] * -1) * 0.0075f;
					//g_Player.nPtnAnim = 6;
					SetBullet(D3DXVECTOR3(g_Player.pos.x + sinf(D3DX_PI * 0.25f - D3DX_PI * 0.5f * g_Player.nAngle) * 30, g_Player.pos.y, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_NONE, D3DX_PI * 0.5f, 0.0f, 20, 20, g_Player.nPresent[0], g_Player.nAttack, 3.0f, BULLETTYPE_PLAYER, 0);

					g_Player.nPresent[0] = g_Player.nPresent[1];
					g_Player.nPresent[1] = g_Player.nPresent[2];
					g_Player.nPresent[2] = rand() % 4;
				}
				else if (GetKeyboardTrigger(DIK_X) == true)
				{//攻撃
					SetExplosion(D3DXVECTOR3(g_Player.pos.x + sinf(D3DX_PI * 0.25f - D3DX_PI * 0.5f * g_Player.nAngle) * 30, g_Player.pos.y + cosf(D3DX_PI * 0.75f) * 30, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 5, 2, 2, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
					g_Player.nCntState[1] = 0;
					if (nTime > 8) { PlaySound(SOUND_LABEL_ATTACK001); nTime = 0; }
					g_Player.state = PLAYERSTATE_SKYATTACK;
					g_Player.nCntState[0] = 12;
					//g_Player.fSkyWait = 0.0f + (g_Player.nCntState[0] * -1) * 0.0075f;
					//g_Player.nPtnAnim = 6;
					SetBullet(D3DXVECTOR3(g_Player.pos.x + sinf(D3DX_PI * 0.25f - D3DX_PI * 0.5f * g_Player.nAngle) * 30, g_Player.pos.y + cosf(D3DX_PI * 0.75f) * 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), BULLETSTATE_GRAVITY, D3DX_PI * 0.5f, 0.0f, 20, 20, g_Player.nPresent[0], g_Player.nAttack, 2.5f, BULLETTYPE_PLAYER, 0);
					g_Player.nPresent[0] = g_Player.nPresent[1];
					g_Player.nPresent[1] = g_Player.nPresent[2];
					g_Player.nPresent[2] = rand() % 4;
				}

				if (g_Player.nClear == 0)
				{
					g_Player.pos.x += 2.0f;
					if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
					{//D, →で右移動
						g_Player.pos.x += fRun;
						g_Player.nAngle = PLAYERANGLE_RIGHT;
					}
					else if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
					{//A, ←で右移動
						g_Player.pos.x -= fRun;
						g_Player.nAngle = PLAYERANGLE_RIGHT;
					}
				}
			}
			//if (g_Player.nJump != 0 && g_Player.bFall == false) { g_Player.move.x = g_Player.fMove; }
			//if (g_Player.fSkyWait > 1.0f || g_Player.state != PLAYERSTATE_SATTACK) { g_Player.fSkyWait = 1.0f; }
			g_Player.move.y += 0.8f * g_Player.fSkyWait;//重力
			g_Player.pos += g_Player.move;//x移動のみ
			//g_Player.fSkyWait += (1.0f - g_Player.fSkyWait) * 0.03f;	//1.0fに近づける
			//g_Player.pos.x += g_Player.fRide;
			g_Player.fRide = 0.0f;

			if (g_Player.nJump == 0 && g_Player.state == PLAYERSTATE_NORMAL && g_Player.nCntAnim % g_Player.nAnimSpeed == 0) { g_Player.nPtnAnim = (g_Player.nPtnAnim + 1) % 3; }
			if (g_Player.bRun == true) { g_Player.nAnimSpeed = 3; }
			else { g_Player.nAnimSpeed = PtnSpeed; }

			//移動量低下(空気抵抗等のつもり)
			if(g_Player.nClear == 0){ g_Player.move.x = 0.0f; }

			if (CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move, &g_Player.fRide, true, &g_Player.state, g_Player.nCollisionX, g_Player.nCollisionY, 0, USETYPE_PLAYER) == true) { g_Player.nJump = 0; }
			else if (g_Player.nJump == 0)
			{
				g_Player.nJump = 1;
				g_Player.bFall = true;
				//if (g_Player.state != PLAYERSTATE_ATTACK && g_Player.state != PLAYERSTATE_WAIT && g_Player.state != PLAYERSTATE_SKYATTACK && g_Player.state != PLAYERSTATE_SATTACK && g_Player.state != PLAYERSTATE_CATCH) { g_Player.nPtnAnim = 8; }
			}
			if (g_Player.state == PLAYERSTATE_DOWN) { g_Player.pos.y += PLAYER_POSY3 / 2; }
			//SafetynBlock(&g_Player.pos, nLengthX, nLengthY);
			CollisionItem();

			if (g_Player.state != PLAYERSTATE_KNOCKBACK && g_Player.state != PLAYERSTATE_INVINCBLE)
			{
				Enemy *pEnemy = GetEnemy();
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy[nCntEnemy].bUse == true && pEnemy[nCntEnemy].pos.x - pEnemy[nCntEnemy].nCollisionX <= SCREEN_WIDTH && pEnemy[nCntEnemy].pos.x + pEnemy[nCntEnemy].nCollisionX >= 0 && pEnemy[nCntEnemy].pos.y - pEnemy[nCntEnemy].nCollisionY <= SCREEN_HEIGHT && pEnemy[nCntEnemy].pos.y + pEnemy[nCntEnemy].nCollisionY >= 0)
					{//敵がいる
						nCollisionX = pEnemy[nCntEnemy].nSize - pEnemy[nCntEnemy].nCollisionX;
						nCollisionY = pEnemy[nCntEnemy].nSize - pEnemy[nCntEnemy].nCollisionY;
						if (HitAim(g_Player.pos, g_Player.nCollisionX, g_Player.nCollisionY, g_Player.fSteep, pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].nSize) == true)
						{//敵と当たっている
							if (g_Player.state == PLAYERSTATE_WAIT && g_Player.pos.y < pEnemy[nCntEnemy].pos.y)
							{
								g_Player.move.y = -16.0f;
								g_Player.bFall = true;
								g_Player.nPtnAnim = 10;
								g_Player.fSkyWait = 1.0f;
								g_Player.fSteep = D3DX_PI;
								PlaySound(SOUND_LABEL_ATTACK004);
								g_Player.state = PLAYERSTATE_INVINCBLE;
								g_Player.nCntState[0] = 10;
								SetExplosion(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 10, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 50, 7, 1, 1, 5, g_Player.nAttack, ANIMATION_NORMAL, EXPLOSIONSTATE_EHIT, USETYPE_PLAYER, 0, D3DX_PI);
							}
							else { HitPlayer(pEnemy[nCntEnemy].nAtk * 2, pEnemy[nCntEnemy].pos.x - g_Player.pos.x, nCntEnemy); }
						}
					}
				}
			}

			//頂点座標の設定
			//if (g_Player.nAngle == PLAYERANGLE_LEFT) { g_Player.fSteep *= -1; }
			pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fSteep) * g_Player.nLengthY) + (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y - (sinf(g_Player.fSteep) * g_Player.nLengthX) + (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fSteep) * g_Player.nLengthY) - (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y + (sinf(g_Player.fSteep) * g_Player.nLengthX) + (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fSteep) * g_Player.nLengthY) + (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y - (sinf(g_Player.fSteep) * g_Player.nLengthX) - (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fSteep) * g_Player.nLengthY) - (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y + (sinf(g_Player.fSteep) * g_Player.nLengthX) - (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
			//if (g_Player.nAngle == PLAYERANGLE_LEFT) { g_Player.fSteep *= -1; }
			//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
			//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
			//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
			//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);

			pVtx[0].tex = D3DXVECTOR2((g_Player.nPtnAnim % PtnWide) * (1.0f / PtnWide), 0.0f);
			pVtx[1].tex = D3DXVECTOR2((g_Player.nPtnAnim % PtnWide) * (1.0f / PtnWide) + (1.0f / PtnWide), 0.0f);
			pVtx[2].tex = D3DXVECTOR2((g_Player.nPtnAnim % PtnWide) * (1.0f / PtnWide), 1.0f);
			pVtx[3].tex = D3DXVECTOR2((g_Player.nPtnAnim % PtnWide) * (1.0f / PtnWide) + (1.0f / PtnWide), 1.0f);

			//頂点BUFFERをアンロックする
			g_pVtxBuffPlayer->Unlock();

			g_Player.nTime[1]++;
		}
		wsprintf(&aStr[0], "L.V %d    HP %d / %d", g_Player.nLevel, g_Player.nLife, g_Player.nMaxLife);
		ChangeFont(true, &aStr[0], 0, FONTSTATE_NONE, D3DCOLOR_RGBA(255, 255, 255, 255));
		wsprintf(&aStr[0], "SCORE %d", g_Player.nScore);
		ChangeFont(true, &aStr[0], 2, FONTSTATE_NONE, D3DCOLOR_RGBA(255, 255, 255, 255));
		wsprintf(&aStr[0], "TIME %d.%d", g_Player.nTime[0] / 10, g_Player.nTime[0] % 10);
		ChangeFont(true, &aStr[0], 3, FONTSTATE_NONE, D3DCOLOR_RGBA(255, 255, 5, 255));
	}
	else if (g_Player.nClear == 1)
	{//走る
		g_Player.pos.x += fRun * 2.5f;
		if (g_Player.nJump == 0 && g_Player.state == PLAYERSTATE_NORMAL && g_Player.nCntAnim % g_Player.nAnimSpeed == 0) { g_Player.nPtnAnim = (g_Player.nPtnAnim + 1) % 3; }
		if(g_Player.pos.x > SCREEN_WIDTH)
		{
			g_Player.nClear = 2;
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 0.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 0, 0, WINDOWSTATE_FADEIN, WINDOWUSE_NORMAL);
		}
	}
	else
	{//Clear画面
		g_Player.nClear++;
		g_Player.pos.x += fRun * 2.5f;
		if(g_Player.nClear == 120){ SetFade(MODE_RESULT, 0); }
	}
}

//=========================================================================================================//
// * プレイヤーの描画処理4	描画処理
//=========================================================================================================//
void DrawPlayer(void)
{
	if (g_Player.pos.x <= 0.0f)
	{
		g_Player.pos.x = 0.0f;
		CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move, &g_Player.fRide, true, &g_Player.state, g_Player.nCollisionX, g_Player.nCollisionY, 0, USETYPE_PLAYER);
		if (g_Player.pos.x < 0.0f) { g_Player.nLife = 0; }
	}
	if (g_Player.pos.x > SCREEN_WIDTH && g_Player.nClear == 0)
	{
		g_Player.pos.x = SCREEN_WIDTH;
	}

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
void SettingPlayer(void)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	CollisionBlock(&g_Player.pos, &g_Player.posold, &g_Player.move, NULL, false, &g_Player.state, g_Player.nCollisionX, g_Player.nCollisionY, 0, USETYPE_PLAYER);

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y - PLAYER_POSY3, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + PLAYER_POSX3, g_Player.pos.y + PLAYER_POSY3, 0.0f);
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fSteep) * g_Player.nLengthY) + (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y - (sinf(g_Player.fSteep) * g_Player.nLengthX) + (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x + (sinf(g_Player.fSteep) * g_Player.nLengthY) - (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y + (sinf(g_Player.fSteep) * g_Player.nLengthX) + (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fSteep) * g_Player.nLengthY) + (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y - (sinf(g_Player.fSteep) * g_Player.nLengthX) - (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x - (sinf(g_Player.fSteep) * g_Player.nLengthY) - (cosf(g_Player.fSteep) * g_Player.nLengthX), g_Player.pos.y + (sinf(g_Player.fSteep) * g_Player.nLengthX) - (cosf(g_Player.fSteep) * g_Player.nLengthY), 0.0f);


	//頂点BUFFERをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//=========================================================================================================================
// 敵の弾当たり処理
//=========================================================================================================================
void HitPlayer(int nAtk, float fAngle, int nCntEnemy)
{
	if (g_Player.nLife > 0)
	{
		char aStr[256];
		int nDamage;
		int nRand[2];
		nRand[0] = rand() % 10 + 100;	//ディフェンスランド
		nRand[1] = rand() % 5 + 55;	//ディフェンスランド
		PLAYER *pPlayer = GetPlayer();
		Enemy *pEnemy = GetEnemy();
		//float fSteep = atan2f(pEnemy[nCntEnemy].pos.x - g_Player.pos.x, pEnemy[nCntEnemy].pos.y - pPlayer[0].pos.y);
		//float nTargetLengthX = sinf(g_Player.fSteep) * g_Player.nCollisionX + sinf(g_Player.fSteep) * g_Player.nCollisionY;
		//float nTargetLengthY = cosf(g_Player.fSteep) * g_Player.nCollisionX + cosf(g_Player.fSteep) * g_Player.nCollisionY;
		//float fPercentX;
		//float fPercentY;

		//if (nTargetLengthY > nTargetLengthX || nTargetLengthY < nTargetLengthX)
		//{//ポリゴンのXYの比率に応じて角度取り直し
		//	if (nTargetLengthY > nTargetLengthX)
		//	{//Y軸が長い場合　Yの比率保存
		//		fPercentX = sinf(fSteep) * nTargetLengthY / nTargetLengthX;
		//		fPercentY = cosf(fSteep) * 1.0f;
		//	}
		//	if (nTargetLengthY < nTargetLengthX)
		//	{//X軸が長い場合　Xの比率保存
		//		fPercentX = sinf(fSteep) * 1.0f;
		//		fPercentY = cosf(fSteep) * nTargetLengthX / nTargetLengthY;
		//	}
		//	fSteep = atan2f(fPercentX, fPercentY);//角度取り直し
		//}

		// ライフが減少
		if (g_Player.state == PLAYERSTATE_DOWN)
		{ 
			g_Player.posold.y -= 16;
			g_Player.pos.y -= 30;
		}
		nDamage = (nAtk * nRand[0] / 100) - (g_Player.nDefense * nRand[1] / 100);
		if (nDamage < 0) { nDamage = 1; }
		g_Player.nLife -= nDamage;
		//SetDigital(D3DXVECTOR3(250, SCREEN_HEIGHT * 0.6f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.0f), DIGITALSTATE_DAMAGE, 30, 45, nDamage);
		SetExplosion(g_Player.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30, 30, 5, 1, 2, 2, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		if (g_Player.nLife <= 0)
		{// ライフが0以下になった場合
			//SetGameState(GAMESTATE_END, MODE_RESULT, 100);
			for (int nCount = 0; nCount < 10; nCount++) { if (g_Player.bClock[nCount] == true && g_Player.bClockold[nCount] == false) { g_Player.nTime[0] -= 3000; } }
			for (int nCount = 0; nCount < 10; nCount++) { g_Player.bClock[nCount] = g_Player.bClockold[nCount]; }
			StopSound();
			PlaySound(SOUND_LABEL_DEATH);
			g_Player.nLife = 0;
			wsprintf(&aStr[0], "TIME %d.%d", g_Player.nTime[0] / 10, g_Player.nTime[0] % 10);
			if (g_Player.nTime[0] > 600) { ChangeFont(true, &aStr[0], 3, FONTSTATE_NONE, D3DCOLOR_RGBA(255, 255, 5, 255)); }
			else { ChangeFont(true, &aStr[0], 3, FONTSTATE_NONE, D3DCOLOR_RGBA(30, 0, 0, 255)); }
			if(g_Player.nTime[0] > 0){ SetFade(MODE_GAME, 1); }
		}
		else
		{// ライフが1以上の場合
			g_Player.state = PLAYERSTATE_DAMAGE;	// 状態変化
			g_Player.nCntState[0] = 5;					// 状態カウンタ

			if (g_Player.nMaxLife / 7 < nDamage) { PlaySound(SOUND_LABEL_Damage002); }		//Damage大
			else if (g_Player.nMaxLife / 11 < nDamage) { PlaySound(SOUND_LABEL_Damage001); }//Damage中
			else { PlaySound(SOUND_LABEL_Damage000); }										//Damage小
			// 色変更
			//g_Player.col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		}
		if (fAngle > 0)
		{
			g_Player.fSteep = D3DX_PI * -0.8f;
		}//右側に当たっている
		else
		{
			g_Player.fSteep = D3DX_PI * 0.8f;
		}
		g_Player.nVibration = 15;
		g_Player.state = PLAYERSTATE_KNOCKBACK;
		g_Player.nClear = -1;
		g_Player.move.y = -35;
		g_Player.move.x = -15;
		g_Player.pos.y -= 1;
		g_Player.nJump = 2;
		g_Player.bFall = false;
		g_Player.nPtnAnim = 11;
		g_Player.fSkyWait = 1.0f;
		SettingPlayer();
	}
}
//=========================================================================================================//
// * プレイヤーの情報代入処理
//=========================================================================================================//
PLAYER *GetPlayer(void)
{
	return &g_Player;
}
