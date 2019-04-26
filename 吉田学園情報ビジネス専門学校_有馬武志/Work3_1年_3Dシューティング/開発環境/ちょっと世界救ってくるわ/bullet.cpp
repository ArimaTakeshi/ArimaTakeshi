//=============================================================================
//
// ポリゴン処理 [bullet.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "bullet.h"		//弾
#include "shadow.h"		//影
#include "explosion.h"	//爆発
#include "effect.h"		//エフェクト
#include "score.h"		//スコア
#include "object.h"		//オブジェクト
#include "billboord.h"	//ビルボード
#include "score.h"		//スコア
#include "input.h"		//キーボード

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_TEXTURE_NAME		"data\\TEXTURE\\bullet000.png"		//読み込むテクスチャファイル
#define MAX_BULLET				(20)								//弾の最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点バッファ
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//テクスチャへのポインタ
Bullet					g_Bullet[MAX_BULLET];		//弾の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//全カウントを回す
		g_Bullet[nCount].rotBullet = D3DXVECTOR3(0, 0, 0);	//向き
		g_Bullet[nCount].posBullet = D3DXVECTOR3(0, 0, 0);	//位置
		g_Bullet[nCount].moveBullet = D3DXVECTOR3(0, 0, 0);	//動き
		g_Bullet[nCount].bUse = false;						//使用しているかどうか
	}

	//頂点情報
	MakeVertexBullet(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBullet(void)
{
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureBullet != NULL)
		{
			g_pTextureBullet->Release();
			g_pTextureBullet = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスポインタ
	Score *pScore = GetScore();
	int nCntBullet;									//弾カウント

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{//弾をカウント
		if (g_Bullet[nCntBullet].bUse == true)
		{//弾が使用されている

			//アイテムのあたり判定
			CollisionBillBoord(&g_Bullet[nCntBullet].posBullet,&g_Bullet[nCntBullet].moveBullet);

			//エフェクト
			SetBulletEffect(g_Bullet[nCntBullet].posBullet,D3DXCOLOR(1.0f,1.0f,0.0f,1.0f),EFFECTTYPE_BULLET,3.0f, 0,0);

			//移動値代入
			g_Bullet[nCntBullet].posBullet += g_Bullet[nCntBullet].moveBullet;

			//影がついてくる
			SetPositionShadow(g_Bullet[nCntBullet].nIdxShadow, g_Bullet[nCntBullet].posBullet, g_Bullet[nCntBullet].rotBullet);

			//壁とのあたり判定
			if (g_Bullet[nCntBullet].posBullet.z >= 1500 || g_Bullet[nCntBullet].posBullet.z <= -1500 || g_Bullet[nCntBullet].posBullet.x >= 1500 || g_Bullet[nCntBullet].posBullet.x <= -1500 || g_Bullet[nCntBullet].posBullet.y <= 0 || g_Bullet[nCntBullet].posBullet.y >= 450)
			{
				//弾をfalse
				g_Bullet[nCntBullet].bUse = false;

				//使っている影をfalse
				DeleteShadow(g_Bullet[nCntBullet].nIdxShadow);

				//爆発
				SetExplosion(g_Bullet[nCntBullet].posBullet,g_Bullet[nCntBullet].rotBullet);

				//エフェクト
				//SetParticleEffect(g_Bullet[nCntBullet].posBullet, EFFECTTYPE_EXPLOSION, 50, 6.0f, 10,0);

				////スコア加算
				//AddScore(1000,SCORE_EXSPLOSION);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans,mtxView;		//計算用マトリックス


	//アルファテスト処理
	//デフォルトの場合FALSEになっているからTRUEにする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//ここの式は参照を意味し、参照した値を基準値に置き換える
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);

	//ここの式は処理を意味し、比較するという式
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ポリゴンの描画
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//弾をカウント
		if (g_Bullet[nCount].bUse == true)
		{//弾がある場合

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCount].mtxWorldBullet);

			//弾
			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//逆行列を設定
			g_Bullet[nCount].mtxWorldBullet._11 = mtxView._11;
			g_Bullet[nCount].mtxWorldBullet._12 = mtxView._21;
			g_Bullet[nCount].mtxWorldBullet._13 = mtxView._31;
			g_Bullet[nCount].mtxWorldBullet._21 = mtxView._12;
			g_Bullet[nCount].mtxWorldBullet._22 = mtxView._22;
			g_Bullet[nCount].mtxWorldBullet._23 = mtxView._32;
			g_Bullet[nCount].mtxWorldBullet._31 = mtxView._13;
			g_Bullet[nCount].mtxWorldBullet._32 = mtxView._23;
			g_Bullet[nCount].mtxWorldBullet._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCount].posBullet.x, g_Bullet[nCount].posBullet.y, g_Bullet[nCount].posBullet.z);

			D3DXMatrixMultiply(&g_Bullet[nCount].mtxWorldBullet, &g_Bullet[nCount].mtxWorldBullet, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCount].mtxWorldBullet);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}

	//アルファテストを無効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBullet(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		BULLET_TEXTURE_NAME,
		&g_pTextureBullet
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//全カウントを回す
	 //頂点座
		pVtx[0].pos = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0f, 0.0f, 0.0f);
		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロックする
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// 弾の作成
//=============================================================================
void SetBullet(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 move)
{
	for (int nCount = 0; nCount < MAX_BULLET; nCount++)
	{//全テクスチャのカウント
		if (g_Bullet[nCount].bUse == false)
		{
			g_Bullet[nCount].posBullet = pos;			//pos値代入
			g_Bullet[nCount].rotBullet = rot;			//rot値代入
			g_Bullet[nCount].moveBullet = move;			//move値代入
			g_Bullet[nCount].bUse = true;				//使用している状態にする

			//影をつける
			g_Bullet[nCount].nIdxShadow = SetShadow(g_Bullet[nCount].posBullet, g_Bullet[nCount].rotBullet, 2, 2);
			break;
		}
	}
}
//=============================================================================
//	カメラの取得
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_Bullet[0];
}
