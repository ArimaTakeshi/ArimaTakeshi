//=============================================================================
//
// ポリゴン処理 [explosion.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "explosion.h"		//爆発
#include "shadow.h"			//影

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define EXPLOSION_TEXTURE_NAME		"data\\TEXTURE\\explosion000.png"		//読み込むテクスチャファイル
#define EXPLOSION_TEXTURE_SPEED		(5)										//テクスチャアニメーションスピード
#define EXPLOSION_TEXTURE_PATTERN	(8)										//テクスチャアニメーションパターン数
#define EXPLOSION_TEXTURE_UV_U		(0.125f)								//テクスチャアニメーションU範囲
#define EXPLOSION_TEXTURE_UV_V		(1.0f)									//テクスチャアニメーションV範囲
#define MAX_EXPLOSION				(100)									//爆発の最大数
	
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//頂点バッファ
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	//テクスチャへのポインタ
Explosion g_Explosion[MAX_EXPLOSION];				//爆発の情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//全カウントを回す
		g_Explosion[nCount].rotExplosion = D3DXVECTOR3(0, 0, 0);	//向き
		g_Explosion[nCount].posExplosion = D3DXVECTOR3(0, 0, 0);	//位置
		g_Explosion[nCount].nCounterAnim = 0;						//カウンター初期値設定
		g_Explosion[nCount].nPatteunAnim = 0;						//パターンNo.初期値設定
		g_Explosion[nCount].bUse = false;							//使用しているかどうか
	}

	//頂点情報
	MakeVertexExplosion(pDevice);

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitExplosion(void)
{
	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureExplosion != NULL)
		{
			g_pTextureExplosion->Release();
			g_pTextureExplosion = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateExplosion(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	//爆発カウント
	int nCntExplosion;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;	

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{//爆発をカウント
		if (g_Explosion[nCntExplosion].bUse == true)
		{//弾が使用されている
			g_Explosion[nCntExplosion].nCounterAnim++;		//カウンター加算

			if ((g_Explosion[nCntExplosion].nCounterAnim % EXPLOSION_TEXTURE_SPEED) == 0)
			{//アニメーション速度
				g_Explosion[nCntExplosion].nPatteunAnim = (g_Explosion[nCntExplosion].nPatteunAnim + 1) % EXPLOSION_TEXTURE_PATTERN;		//パターンNo.更新

				//テクスチャ設定
				pVtx[nCntExplosion * 4].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim, 0.0f);
				pVtx[nCntExplosion * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, 0.0f);
				pVtx[nCntExplosion * 4 + 2].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim, EXPLOSION_TEXTURE_UV_V);
				pVtx[nCntExplosion * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCntExplosion].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

				if (g_Explosion[nCntExplosion].nPatteunAnim == EXPLOSION_TEXTURE_PATTERN - 1)
				{//アニメーションが最後までいった場合
					g_Explosion[nCntExplosion].bUse = false;		//使用していない状態
				}
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawExplosion(void)
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

	//デフォルトの場合FALSEになっているからTRUEにする
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//比較方法（より大きい））

	//ポリゴンの描画
	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//爆発をカウント
		if (g_Explosion[nCount].bUse == true)
		{//爆発がある場合

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Explosion[nCount].mtxWorldExplosion);

			//爆発
			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//逆行列を設定
			g_Explosion[nCount].mtxWorldExplosion._11 = mtxView._11;
			g_Explosion[nCount].mtxWorldExplosion._12 = mtxView._21;
			g_Explosion[nCount].mtxWorldExplosion._13 = mtxView._31;
			g_Explosion[nCount].mtxWorldExplosion._21 = mtxView._12;
			g_Explosion[nCount].mtxWorldExplosion._22 = mtxView._22;
			g_Explosion[nCount].mtxWorldExplosion._23 = mtxView._32;
			g_Explosion[nCount].mtxWorldExplosion._31 = mtxView._13;
			g_Explosion[nCount].mtxWorldExplosion._32 = mtxView._23;
			g_Explosion[nCount].mtxWorldExplosion._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Explosion[nCount].posExplosion.x, g_Explosion[nCount].posExplosion.y, g_Explosion[nCount].posExplosion.z);

			D3DXMatrixMultiply(&g_Explosion[nCount].mtxWorldExplosion, &g_Explosion[nCount].mtxWorldExplosion, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Explosion[nCount].mtxWorldExplosion);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//アルファテスト処理
	//デフォルトの場合FALSEになっているからTRUEにする
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//比較方法（より大きい））

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		EXPLOSION_TEXTURE_NAME,
		&g_pTextureExplosion
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//全カウントを回す
	 //頂点座
		pVtx[0].pos = D3DXVECTOR3(-10, 10, 0);
		pVtx[1].pos = D3DXVECTOR3(10, 10, 0);
		pVtx[2].pos = D3DXVECTOR3(-10, -10, 0);
		pVtx[3].pos = D3DXVECTOR3(10, -10, 0);
		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロックする
	g_pVtxBuffExplosion->Unlock();
}
//=============================================================================
// 爆発の作成
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffExplosion->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_EXPLOSION; nCount++)
	{//全テクスチャのカウント
		if (g_Explosion[nCount].bUse == false)
		{
			g_Explosion[nCount].posExplosion = pos;			//pos値代入
			g_Explosion[nCount].rotExplosion = rot;			//rot値代入
			g_Explosion[nCount].nCounterAnim = 0;			//カウンター初期値設定
			g_Explosion[nCount].nPatteunAnim = 0;			//パターンNo.初期値設定
			g_Explosion[nCount].bUse = true;				//使用している状態にする

			//テクスチャ設定
			pVtx[nCount * 4].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim, 0.0f);
			pVtx[nCount * 4 + 1].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, 0.0f);
			pVtx[nCount * 4 + 2].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim, EXPLOSION_TEXTURE_UV_V);
			pVtx[nCount * 4 + 3].tex = D3DXVECTOR2(EXPLOSION_TEXTURE_UV_U * g_Explosion[nCount].nPatteunAnim + EXPLOSION_TEXTURE_UV_U, EXPLOSION_TEXTURE_UV_V);

			//影をつける
			//SetShadow(g_Explosion[nCount].posExplosion, g_Explosion[nCount].rotExplosion, 10.0f, 10.0f);
			break;
		}
	}
	//頂点バッファのアンロックする
	g_pVtxBuffExplosion->Unlock();
}
