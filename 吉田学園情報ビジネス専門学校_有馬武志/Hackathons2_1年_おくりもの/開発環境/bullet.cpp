//=========================================================================================================//
//
// [弾発射]->弾移動処理 [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"				//爆発を呼ぶため
#include "enemy.h"				//敵の場所確認のため
#include "sound.h"

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define BULLET_VERTEX_NUM			(4)					// 頂点の数
#define BULLET_PRIMITIVE_NUM		(2)					// プリミティブの数
#define BULLET_TextureName		"data/TEXTURE/AllPresent.png"
#define BULLET_MAX_Texture			(1)					//画像の種類
#define	MAX_BULLET			(128)				// 弾の最大数
#define HIT_PLUS			(3.0f)				//敵Hit判定の弾の大きさの倍率
#define HIT_SAFE			(0.55f)				//自機Hit判定の弾の大きさの倍率
#define KNIFE_STEEP			(D3DX_PI * -0.55f)	//ナイフの初期角度
#define KNIFE_STEEPENEMY	(D3DX_PI * -0.45f)	//ナイフの初期角度
#define BULLET_SLIP			(0.15f)				//弾の滑り
#define BULLET_DELETE		(0)
#define BULLET_DELETE1		(1)

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureBullet[2] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// 頂点バッファへのポインタ		

//=========================================================================================================//
// * 背景の描画処理1	初期化処理
//=========================================================================================================//
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBullet;

	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	// 弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//g_aBullet[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aBullet[nCntBullet].steep = 0.0f;
		//g_aBullet[nCntBullet].nType = 0;
		//g_aBullet[nCntBullet].nAtkType = 0;
		//g_aBullet[nCntBullet].nShot = 0;
		//g_aBullet[nCntBullet].nLengthX = 0;
		//g_aBullet[nCntBullet].nLengthY = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, BULLET_TextureName, &g_pTextureBullet[0]);

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * BULLET_VERTEX_NUM * MAX_BULLET,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		/*pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);*/

		pVtx[nCntBullet * 4].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 1].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 2].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 3].rhw = 1.0f;

		//カラー設定
		pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = 透明度
		pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標設定
		pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点BUFFERをアンロックする
	g_pVtxBuffBullet->Unlock();
}
//=========================================================================================================//
// * 背景の描画処理2	終了処理
//=========================================================================================================//
void UninitBullet(void)
{//テクスチャの破棄
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < BULLET_MAX_Texture; nCntTexture++)
	{
		if (g_pTextureBullet[nCntTexture] != NULL)
		{
			g_pTextureBullet[nCntTexture]->Release();
			g_pTextureBullet[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//=========================================================================================================//
// * 背景の描画処理3	更新処理
//=========================================================================================================//
void UpdateBullet(void)
{
	static int nCntTime = 100;
	static int nCntGuard = 100;
	int nCntBullet;			//弾数える～
	int nCntEnemy;
	bool bHit;
	Enemy *pEnemy = GetEnemy();

	Bullet *g_aBullet;
	PLAYER *pPlayer;
	g_aBullet = GetBullet();
	pPlayer = GetPlayer();
	nCntTime++;
	nCntGuard++;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{

		if (g_aBullet[nCntBullet].bUse == true)
		{//弾を前に飛ばす
		 //MessageBox(0, "本当すか？", "終了", MB_YESNO);
			g_aBullet[nCntBullet].posold = g_aBullet[nCntBullet].pos;
			g_aBullet[nCntBullet].nCntState++;
			switch (g_aBullet[nCntBullet].state)
			{
			case BULLETSTATE_NONE:			//普通に飛ぶ
				g_aBullet[nCntBullet].nCntState++;
				g_aBullet[nCntBullet].move.x += g_aBullet[nCntBullet].fSpeed;
				SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 80, 50, 5, 2, 2, 1, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
				if (g_aBullet[nCntBullet].nCntState > 60)
				{ 
					g_aBullet[nCntBullet].state = BULLETSTATE_DELETE;
					SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 2, 2, 0, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
				}
				g_aBullet[nCntBullet].steep += D3DX_PI * 0.2f;
				break;
			case BULLETSTATE_GRAVITY:
				SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30, 30, 5, 1, 2, 2, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);

				g_aBullet[nCntBullet].nCntState++;
				g_aBullet[nCntBullet].move.y += 1.0f;
				g_aBullet[nCntBullet].move.x += g_aBullet[nCntBullet].fSpeed;
				g_aBullet[nCntBullet].fSpeed -= g_aBullet[nCntBullet].fSpeed * 0.05f;
				g_aBullet[nCntBullet].steep += D3DX_PI * 0.2f;
				if (g_aBullet[nCntBullet].fSpeed < 0.0f) { g_aBullet[nCntBullet].fSpeed = 0.1f; }
				if (g_aBullet[nCntBullet].pos.y > SCREEN_HEIGHT) { g_aBullet[nCntBullet].state = BULLETSTATE_DELETE; }
				break;
			case BULLETSTATE_NORMAL:
				g_aBullet[nCntBullet].nCntState++;
				g_aBullet[nCntBullet].move += D3DXVECTOR3(sinf(g_aBullet[nCntBullet].steep), cosf(g_aBullet[nCntBullet].steep), 0.0f) * g_aBullet[nCntBullet].fSpeed;
				if (g_aBullet[nCntBullet].nCntState > 60) { g_aBullet[nCntBullet].state = BULLETSTATE_DELETE; }
				break;
			case BULLETSTATE_DELETE:		//消えていく

				g_aBullet[nCntBullet].move += D3DXVECTOR3(sinf(g_aBullet[nCntBullet].steep), cosf(g_aBullet[nCntBullet].steep), 0.0f) * g_aBullet[nCntBullet].fSpeed * g_aBullet[nCntBullet].col.a * 0.5f;
				g_aBullet[nCntBullet].col.a -= 1.0f;
				//pVtx[nCntBullet * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);	// A = 透明度
				//pVtx[nCntBullet * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);
				//pVtx[nCntBullet * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);
				//pVtx[nCntBullet * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_aBullet[nCntBullet].fcolA);
				if (g_aBullet[nCntBullet].col.a <= 0.0f) { g_aBullet[nCntBullet].bUse = false; }
				break;
			case BULLETSTATE_SINGLE:	//1Fで消える　画像のみ
				g_aBullet[nCntBullet].bUse = false;
				break;
			case BULLETSTATE_THIRD:		//3Fで消える
				if(g_aBullet[nCntBullet].nCntState > 2){ g_aBullet[nCntBullet].bUse = false; }
				break;
			case BULLETSTATE_FIFTH:		//5Fで消える
				if (g_aBullet[nCntBullet].nCntState > 4) { g_aBullet[nCntBullet].bUse = false; }
				break;
			}
			g_aBullet[nCntBullet].steep += g_aBullet[nCntBullet].fCurve;
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			//移動量低下(空気抵抗等のつもり)
			g_aBullet[nCntBullet].move.x += (0.0f - g_aBullet[nCntBullet].move.x) * BULLET_SLIP;
			g_aBullet[nCntBullet].move.y += (0.0f - g_aBullet[nCntBullet].move.y) * BULLET_SLIP;

			//if (g_aBullet[nCntBullet].pos.y + g_aBullet[nCntBullet].nLengthY <= -BULLET_DELETE || g_aBullet[nCntBullet].pos.y - g_aBullet[nCntBullet].nLengthY >= SCREEN_HEIGHT + BULLET_DELETE || g_aBullet[nCntBullet].pos.x + g_aBullet[nCntBullet].nLengthX <= -BULLET_DELETE || g_aBullet[nCntBullet].pos.x - g_aBullet[nCntBullet].nLengthX >= SCREEN_WIDTH + BULLET_DELETE)
			//{//画面外+200の弾を消す
			//	g_aBullet[nCntBullet].bUse = false;
			//}

			if (g_aBullet[nCntBullet].nShot == BULLETTYPE_PLAYER && g_aBullet[nCntBullet].state != BULLETSTATE_DELETE && g_aBullet[nCntBullet].state != BULLETSTATE_GRAVITY&& g_aBullet[nCntBullet].state != BULLETSTATE_SINGLE)
			{//自機が撃った弾なら
				pEnemy = GetEnemy();
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{//敵の数だけ回る
					if (pEnemy[nCntEnemy].bUse == true && pEnemy[nCntEnemy].nCounterDamage < 0)
					{//敵がいる！
						bHit = HitAim(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].nLengthX, g_aBullet[nCntBullet].nLengthY, g_aBullet[nCntBullet].steep, pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].nSize);
						if (bHit == true)
						{//弾が当たってる
							HitEnemy(nCntEnemy, g_aBullet[nCntBullet].nAtk, pPlayer[0].pos.x - pEnemy[nCntEnemy].pos.x, USETYPE_PLAYER);
							g_aBullet[nCntBullet].bUse = false;
							if (g_aBullet[nCntBullet].nType == 9)
							{//爆発
								PlaySound(SOUND_LABEL_ATTACK004);
								SetExplosion(D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y - 110, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f), 30, 150, 10, 1, 2, 0, g_aBullet[nCntBullet].nAtk, ANIMATION_NORMAL, EXPLOSIONSTATE_EHIT, USETYPE_IGNORE, 0, D3DX_PI); }
						}//ヒット判定
					}//敵存在判定
				}//for括弧
			}
			else if(g_aBullet[nCntBullet].nShot == BULLETTYPE_ENEMY && g_aBullet[nCntBullet].state != BULLETSTATE_DELETE)
			{//敵が撃った球なら
				if (pPlayer[0].bUse == true && g_aBullet[nCntBullet].col.a == 1.0f)
				{//自機がいる！
					bHit = HitAim(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].nLengthX, g_aBullet[nCntBullet].nLengthY, g_aBullet[nCntBullet].steep, pPlayer[0].pos, pPlayer[0].nCollisionX);
					if (bHit == true)
					{//弾が当たってる
						//g_aBullet[nCntBullet].bUse = false;
						HitPlayer(g_aBullet[nCntBullet].nAtk, g_aBullet[nCntBullet].pos.x - pPlayer[0].pos.x, g_aBullet[nCntBullet].nCntEnemy);
					}//ヒット判定
				}
			}//自機存在判定
			if (g_aBullet[nCntBullet].bUse == true && HitBullet(g_aBullet[nCntBullet]) == true && g_aBullet[nCntBullet].nShot != BULLETTYPE_EFFECT)
			{//ブロックに当たった
				g_aBullet[nCntBullet].bUse = false;
			}
		}
	}
}
//=========================================================================================================//
// * 弾の当たり判定
//=========================================================================================================//
bool HitAim(D3DXVECTOR3 MyPos, int nMyLengthX, int nMyLengthY, float fMyAngle, D3DXVECTOR3 aim, int nLength)
{
	//HitAim(Bullet pBullet, D3DXVECTOR3 aim, int nLength)

		float fLengthX;			//弾の中心から目標の中心までの距離X
		float fLengthY;			//弾の中心から目標の中心までの距離Y
		float fLengthAim;		//目標までの距離(斜)
		float fAimSteep = 1.0;	//目標までの角度 -> 初期化
		float fBullSteep;		//弾の角度
		float fLengthBX;		//弾の有効の幅X
		float fLengthBY;		//弾の有効の幅Y
		float fLengthB;			//弾の有効の幅(合計)
		float fSteep[2] = { 1.0f, 1.0f };	//X軸のマイナスの保存用 -> 初期化

		float fPercentY = 1.0f;		//楕円時のYの倍率
		float fPercentX = 1.0f;		//楕円時のXの倍率

		fLengthX = aim.x - MyPos.x;	//差Xを代入
		fLengthY = aim.y - MyPos.y;	//差Yを代入
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

		//％で目標への角度->sin, cosに変換 100％が1.57とする
		fAimSteep = fLengthY / (fLengthX + fLengthY) * (D3DX_PI / 2) * fSteep[1];
		fAimSteep = (D3DX_PI / 2 + fAimSteep) * fSteep[0];
		//fAimSteep = atan2f(fLengthX * fSteep[0], fLengthY * fSteep[1]);

		//弾の角度と目標の角度の合成
		fBullSteep = fMyAngle;
		if (fBullSteep < 0)
		{//補正の必要がない場合
			fBullSteep = D3DX_PI + fBullSteep;
			fAimSteep -= fBullSteep;
		}
		else
		{//弾の角度を最小値に戻す
			fBullSteep = D3DX_PI - fBullSteep;
			fAimSteep += fBullSteep;
		}

		if (nMyLengthY > nMyLengthX || nMyLengthY < nMyLengthX)
		{//ポリゴンのXYの比率に応じて角度取り直し
			if (nMyLengthY > nMyLengthX)
			{//Y軸が長い場合　Yの比率保存
				fPercentX = sinf(fAimSteep) * nMyLengthY / nMyLengthX;
				fPercentY = cosf(fAimSteep) * 1.0f;
			}
			if (nMyLengthY < nMyLengthX)
			{//X軸が長い場合　Xの比率保存
				fPercentX = sinf(fAimSteep) * 1.0f;
				fPercentY = cosf(fAimSteep) * nMyLengthX / nMyLengthY;
			}

			fAimSteep = 1;	//角度初期化
			fSteep[0] = 1;	//マイナス保存用も初期化
			if (fPercentX < 0.0f)
			{//X軸のマイナス保存
				fPercentX *= -1;
				fSteep[0] = -1;
			}
			if (fPercentY < 0.0f)
			{//Y軸のマイナス保存
				fPercentY *= -1;
				fAimSteep = -1;
			}
			//％で目標への角度->sin, cosに変換 100％が1.57とする 楕円生成
			fAimSteep = fPercentY / (fPercentX + fPercentY) * (D3DX_PI / 2) * fAimSteep;
			fAimSteep = (D3DX_PI / 2 + fAimSteep) * fSteep[0];
		}

		fLengthBY = cosf(fAimSteep) * nMyLengthY;
		fLengthBX = sinf(fAimSteep) * nMyLengthX;

		fLengthB = (fLengthBX + fLengthBY) * (fLengthBX + fLengthBY);	//弾の有効な幅(合計)を代入

		if (fLengthAim < fLengthB)
		{//判定　2乗された状態なので
			return true;
		}
		else
		{
			return false;
		}
	}

//=========================================================================================================//
// * 弾の描画処理4	描画処理
//=========================================================================================================//
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//// αブレンディングを加算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, 2);
	
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	// ポリゴンの描画

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) + (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX), g_aBullet[nCntBullet].pos.y + (sinf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthX) - (cosf(g_aBullet[nCntBullet].steep) * g_aBullet[nCntBullet].nLengthY), 0.0f);

			pVtx[nCntBullet * 4].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2));
			pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2) + (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2));
			pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2) + (1.0f / 2));
			pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2((g_aBullet[nCntBullet].nType % 2) * (1.0f / 2) + (1.0f / 2), (g_aBullet[nCntBullet].nType / 2) * (1.0f / 2) + (1.0f / 2));

			//カラー設定
			pVtx[nCntBullet * 4].col = g_aBullet[nCntBullet].col;	// A = 透明度
			pVtx[nCntBullet * 4 + 1].col = g_aBullet[nCntBullet].col;
			pVtx[nCntBullet * 4 + 2].col = g_aBullet[nCntBullet].col;
			pVtx[nCntBullet * 4 + 3].col = g_aBullet[nCntBullet].col;

			pDevice->SetTexture(0, g_pTextureBullet[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, BULLET_PRIMITIVE_NUM);
		}
	}

	//頂点BUFFERをアンロックする
	g_pVtxBuffBullet->Unlock();
	//// αブレンディングを元に戻す
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXCOLOR col, BULLETSTATE state, float steep, float fCurve, int nLengthX, int nLengthY, int nType, int nAtk, float fSpeed, BULLETTYPE nShot, int nCntEnemy)
{
	int nCntBullet;			//弾数えるの～
	int nClear = 255;		//透明設定のため
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			//まとめて情報を代入
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].move = D3DXVECTOR3{ 0.0f, 0.0f, 0.0f };
			g_aBullet[nCntBullet].col = col;
			g_aBullet[nCntBullet].state = state;
			g_aBullet[nCntBullet].nCntState = 0;
			g_aBullet[nCntBullet].nLengthX = nLengthX;
			g_aBullet[nCntBullet].nLengthY = nLengthY;
			g_aBullet[nCntBullet].nType = nType;
			g_aBullet[nCntBullet].nAtk = nAtk;
			g_aBullet[nCntBullet].nShot = nShot;
			g_aBullet[nCntBullet].nCntEnemy = nCntEnemy;
			g_aBullet[nCntBullet].steep = steep;
			g_aBullet[nCntBullet].fCurve = fCurve;
			g_aBullet[nCntBullet].fSpeed = fSpeed;
			g_aBullet[nCntBullet].bUse = true;
			if (g_aBullet[nCntBullet].state == BULLETSTATE_GRAVITY) { g_aBullet[nCntBullet].move.y = -25.0f; }
			break;
		}
	}
	//頂点BUFFERをアンロックする
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void StartBullet(int nCntEnemy, int nCntAtk)
{
	int nCntBullet;
	Bullet *g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].nCntEnemy == nCntEnemy && g_aBullet[nCntBullet].bUse == true)
		{
			g_aBullet[nCntBullet].nCntState = 0;
		}
	}
}
//=========================================================================================================//
// * 全Animationスクロール処理
//=========================================================================================================//
void BulletScroll(D3DXVECTOR3 move)
{
	int nCntBullet;
	Bullet *g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//スクロール
			g_aBullet[nCntBullet].pos += move;
		}
	}
}

//=============================================================================
// 弾の設定処理
//=============================================================================
void BreakBullet(void)
{
	int nCntBullet;
	Bullet *g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].bUse = false;
	}
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void BreakBullet(int nCntEnemy)
{
	int nCntBullet;
	Bullet *g_aBullet;
	g_aBullet = GetBullet();

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//指定したエネミーの弾を破壊
		if(g_aBullet[nCntBullet].nCntEnemy == nCntEnemy)
		{ 
			g_aBullet[nCntBullet].state = BULLETSTATE_DELETE;
			//ExplosionEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR{ 1.0f, 0.05f, 0.05f, 0.75f }, 100, 100, 0.1f, g_aBullet[nCntBullet].nLengthX * 0.05f, 0.1f, 1.0f);
		}
		//エフェクト欲しいな
	}
}
//=============================================================================
// 弾の取得
//=============================================================================
Bullet *GetBullet(void)
{
	static Bullet bullet[MAX_BULLET];//弾の最大数

	return &bullet[0];
}