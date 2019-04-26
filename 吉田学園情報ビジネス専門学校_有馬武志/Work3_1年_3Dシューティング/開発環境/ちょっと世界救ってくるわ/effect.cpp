//=========================================================================================================================
//
// エフェクト処理 [effect.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
//インクルードファイル
//*************************************************************************************************************************
#include "effect.h"		//エフェクト
#include "shadow.h"		//影
#include "input.h"		//キーボード

//*************************************************************************************************************************
//マクロ定義
//*************************************************************************************************************************
#define	MAX_EFFECT				(10000)									//エフェクトの最大数
#define	TEXTURE_EFFECT_NAME		"data\\TEXTURE\\effect000.jpg"			//読み込むテクスチャファイル名
#define	TEXTURE_EFFECT_NAME1	"data\\TEXTURE\\kemuri.jpg"				//読み込むテクスチャファイル名
#define	TEXTURE_EFFECT_NAME2	"data\\TEXTURE\\hi.jpg"					//読み込むテクスチャファイル名
#define	MAX_TEX					(3)										//種類

//*************************************************************************************************************************
//グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9				g_pTextureEffect[MAX_TEX] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffEffect = NULL;				//頂点バッファへのポインタ
EFFECT							g_Effect[MAX_EFFECT];					//エフェクトの情報
int								g_nCntEffectState;						//状態カウンタ
int								g_nCountTime;							//秒数カウント

//=========================================================================================================================
//エフェクト初期化処理
//=========================================================================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスを取得
	int nCntEffect;		//エフェクトカウンタ

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//エフェクトをカウント
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Effect[nCntEffect].Type = EFFECTTYPE_NONE;
		g_Effect[nCntEffect].fRadius = 0.0f;
		g_Effect[nCntEffect].nLife = 0;
		g_Effect[nCntEffect].bUse = false;
	}
	g_nCntEffectState = 0;			//状態を初期化
	g_nCountTime = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//１枚目の画像
		pDevice,
		TEXTURE_EFFECT_NAME,
		&g_pTextureEffect[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		TEXTURE_EFFECT_NAME1,
		&g_pTextureEffect[1]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		TEXTURE_EFFECT_NAME1,
		&g_pTextureEffect[2]
	);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL
	);

	//頂点情報の作成
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//エフェクトをカウント
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);
		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//エフェクト終了処理
//=========================================================================================================================
void UninitEffect(void)
{
	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//テクスチャの破棄
		if (g_pTextureEffect[nCount] != NULL)
		{
			g_pTextureEffect[nCount] ->Release();
			g_pTextureEffect[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=========================================================================================================================
//エフェクト更新処理
//=========================================================================================================================
void UpdateEffect(void)
{
	//エフェクトカウンタ
	int nCntEffect;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//エフェクトをカウント
		if (g_Effect[nCntEffect].bUse == true)
		{//エフェクトが使用されている場合

			//影がついてくる
			//SetPositionShadow(g_Effect[nCntEffect].nIdxShadow, g_Effect[nCntEffect].pos, g_Effect[nCntEffect].rot);

			if (g_Effect[nCntEffect].Type == EFFECTTYPE_BULLET)
			{//弾エフェクトの場合
				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				//g_Effect[nCntEffect].nLife--;
				g_Effect[nCntEffect].fRadius -= 0.2f;

				if (/*g_Effect[nCntEffect].nLife <= 0 || */g_Effect[nCntEffect].fRadius <= 0)
				{//ライフが0以下の場合
					g_Effect[nCntEffect].bUse = false;

					//使っている影をfalse
					//DeleteShadow(g_Effect[nCntEffect].nIdxShadow);
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_Effect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{//爆発エフェクトの場合
				 //頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.5f;
				}

				if (g_Effect[nCntEffect].fRadius <= 0)
				{//ライフが0以下の場合
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_ERUPTION)
			{//噴火エフェクトの場合
				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				//moveに重力
				g_Effect[nCntEffect].move.y -= 0.05f;
				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				//バウンドの処理
				if (g_Effect[nCntEffect].pos.y <= 0)
				{
					g_Effect[nCntEffect].move.y = (g_Effect[nCntEffect].posOld.y - g_Effect[nCntEffect].pos.y) * 2;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//ライフが0以下の場合
					//SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE)
			{//煙エフェクトの場合
				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				//バウンドの処理
				if (g_Effect[nCntEffect].pos.y <= 0)
				{
					g_Effect[nCntEffect].move.y = (g_Effect[nCntEffect].posOld.y - g_Effect[nCntEffect].pos.y) * 2;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//ライフが0以下の場合
					//SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_FIRE)
			{//火エフェクトの場合
				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 1.0f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 1.0f;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//ライフが0以下の場合
				 //SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_POWDER)
			{//火の粉エフェクトの場合
				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				if (g_Effect[nCntEffect].fRadius <= 0)
				{//ライフが0以下の場合
					//SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SNOW)
			{//雪エフェクトの場合
				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);

			 //g_Effect[nCntEffect].nLife--;
				//moveに重力
				g_Effect[nCntEffect].move.y = -1.0f;
				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				//g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					//g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					//g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				if (g_Effect[nCntEffect].pos.y <= 0)
				{//ライフが0以下の場合
				 //SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_RAIN)
			{//雨エフェクトの場合
			 //g_Effect[nCntEffect].nLife--;

				//頂点設定
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius - 20, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius -20, 0.0f);

				//moveに重力
				g_Effect[nCntEffect].move.y = -3.0f;
				g_Effect[nCntEffect].move.x = 0;
				g_Effect[nCntEffect].move.z = 0;
				g_Effect[nCntEffect].pos += g_Effect[nCntEffect].move;	//移動値代入

				//g_Effect[nCntEffect].nLife--;				//寿命減少

				//半径減少
				if (g_Effect[nCntEffect].nLife > 0)
				{
					//g_Effect[nCntEffect].fRadius -= 0.05f;
				}
				else
				{
					//g_Effect[nCntEffect].fRadius -= 0.5f;
				}
				if (g_Effect[nCntEffect].pos.y <= 0)
				{//ライフが0以下の場合
				 //SetParticleEffect(D3DXVECTOR3(0, 0, 0), EFFECTTYPE_ERUPTION, 50, 3.0f, 20);
					g_Effect[nCntEffect].bUse = false;
				}
			}
		}
	}
	//
	//右３
	//
	{//道上
	 //煙エフェクト
	 SetParticleEffect(D3DXVECTOR3(940.0f, 0.0f, 960.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
	 //炎エフェクト
	 SetParticleEffect(D3DXVECTOR3(940.0f, 0.0f, 960.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	{//道上
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(860.0f, 0.0f, 560.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(860.0f, 0.0f, 560.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(900.0f, 0.0f, 260.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(900.0f, 0.0f, 260.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(950.0f, 0.0f, -340.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(950.0f, 0.0f, -340.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(850.0f, 0.0f, -740.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(850.0f, 0.0f, -740.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(920.0f, 0.0f, -1140.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(920.0f, 0.0f, -1140.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//右２
	//
	{//道上
	 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(1160.0f, 0.0f, 560.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(1160.0f, 0.0f, 560.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(1200.0f, 0.0f, 260.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(1200.0f, 0.0f, 260.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(1250.0f, 0.0f, -340.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(1250.0f, 0.0f, -340.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(1150.0f, 0.0f, -740.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(1150.0f, 0.0f, -740.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//右１
	//
	{//道上
	 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(540.0f, 0.0f, 960.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(540.0f, 0.0f, 960.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(460.0f, 0.0f, 560.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(460.0f, 0.0f, 560.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(500.0f, 0.0f, 260.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(500.0f, 0.0f, 260.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(550.0f, 0.0f, -340.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(550.0f, 0.0f, -340.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(450.0f, 0.0f, -740.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(450.0f, 0.0f, -740.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(520.0f, 0.0f, -1140.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(520.0f, 0.0f, -1140.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//真ん中
	//
	{//道上
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(240.0f, 0.0f, 1060.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(240.0f, 0.0f, 1060.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(200.0f, 0.0f, 120.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(200.0f, 0.0f, 120.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(160.0f, 0.0f, -120.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(160.0f, 0.0f, -120.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(230.0f, 0.0f, -440.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(230.0f, 0.0f, -440.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(200.0f, 0.0f, -1140.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(200.0f, 0.0f, -1140.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//真ん中
	//
	{//道上
	 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-140.0f, 0.0f, 1060.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-140.0f, 0.0f, 1060.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-100.0f, 0.0f, 120.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-100.0f, 0.0f, 120.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-160.0f, 0.0f, -120.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-160.0f, 0.0f, -120.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-130.0f, 0.0f, -440.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-130.0f, 0.0f, -440.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-80.0f, 0.0f, -1140.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(-80.0f, 0.0f, -1140.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-130.0f, 0.0f, -1340.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(-130.0f, 0.0f, -1340.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//左１
	//
	{//道上
	 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-540.0f, 0.0f, 960.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-540.0f, 0.0f, 960.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-460.0f, 0.0f, 560.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-460.0f, 0.0f, 560.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-500.0f, 0.0f, 260.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-500.0f, 0.0f, 260.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-550.0f, 0.0f, -340.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-550.0f, 0.0f, -340.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-450.0f, 0.0f, -740.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(-450.0f, 0.0f, -740.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-520.0f, 0.0f, -1140.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(-520.0f, 0.0f, -1140.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//左２
	//
	{//道上
	 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-840.0f, 0.0f, 960.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-840.0f, 0.0f, 960.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-760.0f, 0.0f, 560.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-760.0f, 0.0f, 560.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-800.0f, 0.0f, 260.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-800.0f, 0.0f, 260.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-850.0f, 0.0f, -340.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-850.0f, 0.0f, -340.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-750.0f, 0.0f, -740.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(-750.0f, 0.0f, -740.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		//煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-820.0f, 0.0f, -1140.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェク
		SetParticleEffect(D3DXVECTOR3(-820.0f, 0.0f, -1140.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	//
	//左３
	//
	{//道上
	 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-1140.0f, 0.0f, 860.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-1140.0f, 0.0f, 860.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-1100.0f, 0.0f, 120.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-1100.0f, 0.0f, 120.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-1060.0f, 0.0f, -120.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-1060.0f, 0.0f, -120.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
		 //煙エフェクト
		SetParticleEffect(D3DXVECTOR3(-1130.0f, 0.0f, -440.0f), EFFECTTYPE_SMOKE, 1, 15, 50, 1);
		//炎エフェクト
		SetParticleEffect(D3DXVECTOR3(-1130.0f, 0.0f, -440.0f), EFFECTTYPE_FIRE, 3, 15, 10, 2);
	}
	/*if (g_nCountTime >= 600 && g_nCountTime <= 1199)
	{*/
		//雨のエフェクト
		SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
		SetBulletEffect(D3DXVECTOR3(-1500.0f + rand() % (2 * 1500), 600.0f, -1500.0f + rand() % (2 * 1500)), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EFFECTTYPE_RAIN, 0.1f, 500, 0);
	/*}
	if (g_nCountTime == 1200)
	{
		g_nCountTime = 0;
	}*/
	g_nCountTime++;

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//エフェクト描画処理
//=========================================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスを取得
	int nCntEffect;		//エフェクトカウンタ

	D3DXMATRIX mtxRot, mtxTrans, mtxView;		//計算用マトリックス

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_Effect[nCntEffect].bUse == true)
		{//エフェクトが使用されている場合
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Effect[nCntEffect].mtxWorld);

			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//逆行列を設定
			g_Effect[nCntEffect].mtxWorld._11 = mtxView._11;
			g_Effect[nCntEffect].mtxWorld._12 = mtxView._21;
			g_Effect[nCntEffect].mtxWorld._13 = mtxView._31;
			g_Effect[nCntEffect].mtxWorld._21 = mtxView._12;
			g_Effect[nCntEffect].mtxWorld._22 = mtxView._22;
			g_Effect[nCntEffect].mtxWorld._23 = mtxView._32;
			g_Effect[nCntEffect].mtxWorld._31 = mtxView._13;
			g_Effect[nCntEffect].mtxWorld._32 = mtxView._23;
			g_Effect[nCntEffect].mtxWorld._33 = mtxView._33;

			//回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Effect[nCntEffect].rot.y, g_Effect[nCntEffect].rot.x, g_Effect[nCntEffect].rot.z);

			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxRot);						//保存

			//位置を反映																													//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_Effect[nCntEffect].mtxWorld, &g_Effect[nCntEffect].mtxWorld, &mtxTrans);						//保存

			//ワールドマトリックスの設定																														//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCntEffect].mtxWorld);

			//アルファテスト
			pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

			//アルファテスト処理
			//デフォルトの場合FALSEになっているからTRUEにする
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//比較方法（より大きい））
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			if (g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE)
			{
				//減算合成の設定
				pDevice->SetRenderState
				(
					D3DRS_BLENDOP,
					D3DBLENDOP_REVSUBTRACT
				);
				pDevice->SetRenderState
				(
					D3DRS_SRCBLEND,
					D3DBLEND_SRCALPHA
				);
				pDevice->SetRenderState
				(
					D3DRS_DESTBLEND,
					D3DBLEND_ONE

				);
			}
			else
			{
				//αブレンディングを加算合成に設定
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect[g_Effect[nCntEffect].nType]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);

			//αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//デフォルトの場合FALSEになっているからTRUEにするc
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//比較方法（より大きい））
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		}
	}

}

//=========================================================================================================================
//弾エフェクト設定処理
//=========================================================================================================================
void SetBulletEffect(D3DXVECTOR3 pos, D3DXCOLOR col, EFFECTTYPE Type, float fRadius, int nLife,int nType)
{
	int nCntEffect;			//エフェクトカウンタ

	VERTEX_3D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//エフェクトをカウント
		if (g_Effect[nCntEffect].bUse == false)
		{//エフェクトが使用されていない
			g_Effect[nCntEffect].pos = pos;			//pos値代入
			g_Effect[nCntEffect].col = col;			//col値代入
			g_Effect[nCntEffect].Type = Type;		//種類設定
			g_Effect[nCntEffect].fRadius = fRadius;	//半径設定
			g_Effect[nCntEffect].nLife = nLife;		//寿命設定
			g_Effect[nCntEffect].nType = nType;		//種類
			g_Effect[nCntEffect].bUse = true;		//使用している状態

			//頂点設定
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			//頂点カラー設定
			pVtx[nCntEffect * 4].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_Effect[nCntEffect].col;
			//法線ベクトル
			pVtx[nCntEffect * 4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[nCntEffect * 4 + 1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[nCntEffect * 4 + 2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[nCntEffect * 4 + 3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
//パーティクルエフェクト設定処理
//=========================================================================================================================
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nType)
{
	//エフェクトカウンタ
	int nCntEffect;
	//エフェクト個数カウンタ
	int nCount = 0;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{//エフェクトをカウント
		if (g_Effect[nCntEffect].bUse == false)
		{//エフェクトが使用されていない
			g_Effect[nCntEffect].pos = pos;			//pos値代入
			g_Effect[nCntEffect].Type = Type;		//種類設定
			g_Effect[nCntEffect].nLife = nLife;		//寿命設定
			g_Effect[nCntEffect].nType = nType;		//種類
			g_Effect[nCntEffect].bUse = true;		//使用している状態

			if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_Effect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				//移動ランダム化
				g_Effect[nCntEffect].move.x = sinf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
				g_Effect[nCntEffect].move.y = cosf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
				g_Effect[nCntEffect].move.z = tanf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_ERUPTION || g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE || g_Effect[nCntEffect].Type == EFFECTTYPE_FIRE || g_Effect[nCntEffect].Type == EFFECTTYPE_POWDER)
			{
				//移動ランダム化
				//g_Effect[nCntEffect].move.x = sinf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);
				g_Effect[nCntEffect].move.y = cosf((rand() % 100) / 100.0f) * ((rand() % 4) + 1);
				//g_Effect[nCntEffect].move.z = tanf((rand() % 800) / 100.0f) * ((rand() % 4) + 1);

				g_Effect[nCntEffect].move.x = sinf((-D3DX_PI * (nCntEffect * (1.0f / (20 / 2)))))* 0.5f;
				//g_Effect[nCntEffect].move.y = 30.0f;
				//pVtx[頂点番号].y = 縦のカウント回数　* 縦の幅
				g_Effect[nCntEffect].move.z = cosf((-D3DX_PI * (nCntEffect * (1.0f / (20 / 2)))))* 0.5f;
			}

 			int nNumber = rand() % 4 + 1;

			//col値代入
			if (g_Effect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.8f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(0.8f, 0.5f, 0.3f, 0.8f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 0.8f, 0.8f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 0.8f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.8f, 0.6f, 0.8f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_ERUPTION)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SMOKE)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_SNOW)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_RAIN)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_FIRE)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
			}
			else if (g_Effect[nCntEffect].Type == EFFECTTYPE_POWDER)
			{
				if (nNumber == 1) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f); }
				if (nNumber == 2) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.6f, 0.0f, 1.0f); }
				if (nNumber == 3) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f); }
				if (nNumber == 4) { g_Effect[nCntEffect].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f); }
			}

			g_Effect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	//半径設定

			//頂点設定
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, -g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_Effect[nCntEffect].fRadius, g_Effect[nCntEffect].fRadius, 0.0f);
			//頂点カラー設定
			pVtx[nCntEffect * 4].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_Effect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_Effect[nCntEffect].col;

			//カウントを足す
			nCount++;
			if (nCount == nSetMax)
			{//個数が最大数になった場合
				//影をつける
				//g_Effect[nCount].nIdxShadow = SetShadow(g_Effect[nCount].pos, g_Effect[nCount].rot, 2, 2);
				break;
			}
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();
}