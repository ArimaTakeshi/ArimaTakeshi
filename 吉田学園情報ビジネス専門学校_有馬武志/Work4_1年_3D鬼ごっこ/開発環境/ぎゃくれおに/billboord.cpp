//=============================================================================
//
// ポリゴン処理 [billboord.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "billboord.h"		//ビルボード
#include "shadow.h"			//影
#include "bullet.h"			//弾
#include "effect.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BILLBOORD_TEXTURE_NAME		"data\\TEXTURE\\tree.png"		//読み込むテクスチャファイル
#define BILLBOORD_TEXTURE_NAME1		"data\\TEXTURE\\tree000.png"	//読み込むテクスチャファイル
#define BILLBOORD_TEXTURE_NAME2		"data\\TEXTURE\\iwa.png"		//読み込むテクスチャファイル
#define BILLBOORD_TEXTURE_NAME3		"data\\TEXTURE\\tree001.png"	//読み込むテクスチャファイル
#define BILLBOORD_TEXTURE_NAME4		"data\\TEXTURE\\zonbi.png"		//読み込むテクスチャファイル
#define BILLBOORD_TEXTURE_UV_U		(0.5f)							//テクスチャアニメーションU範囲
#define BILLBOORD_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲
#define BILLBOORD_TEXTURE_SPEED		(10)							//テクスチャアニメーションスピード
#define BILLBOORD_TEXTURE_PATTERN	(2)								//テクスチャアニメーションパターン数
#define BILLBOORD_ZONBI_WID			(20)							//ゾンビの幅
#define BILLBOORD_ZONBI_HEI			(50)							//ゾンビの高さ
#define MAX_BILLBOORD				(2300)							//ビルボードの最大数
#define MAX_BILLBOORD_TEX			(5)								//最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexBillBoord(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillBoord = NULL;						//頂点バッファ
LPDIRECT3DTEXTURE9		g_pTextureBillBoord[MAX_BILLBOORD_TEX] = {};	//テクスチャへのポインタ
BillBoord g_BillBoord[MAX_BILLBOORD];									//ビルボードの情報

//=============================================================================
// 初期化処理
//=============================================================================
void InitBillBoord(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//全カウントを回す
		g_BillBoord[nCount].rotBillBoord = D3DXVECTOR3(0, 0, 0);	//向き
		g_BillBoord[nCount].posBillBoord = D3DXVECTOR3(0, 0, 0);	//位置
		g_BillBoord[nCount].nCounterAnim = 0;						//カウンター初期値設定
		g_BillBoord[nCount].nPatteunAnim = 0;						//パターンNo.初期値設定
		g_BillBoord[nCount].bUse = false;							//使用しているかどうか
	}

	//頂点情報
	MakeVertexBillBoord(pDevice);

}
//=============================================================================
// 終了処理
//=============================================================================
void UninitBillBoord(void)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD_TEX; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureBillBoord[nCount] != NULL)
		{
			g_pTextureBillBoord[nCount] ->Release();
			g_pTextureBillBoord[nCount] = NULL;
		}
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBillBoord != NULL)
	{
		g_pVtxBuffBillBoord->Release();
		g_pVtxBuffBillBoord = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBillBoord(void)
{
	////デバイスポインタ
	//LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//VERTEX_3D *pVtx;	//頂点情報へのポインタ

	////弾のポインタ
	//Bullet *pBullet = GetBullet();

	////頂点バッファをロック
	//g_pVtxBuffBillBoord->Lock
	//(
	//	0,
	//	0,
	//	(void**)&pVtx,
	//	0
	//);

	//for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	//{
	//	if (g_BillBoord[nCount].bUse == true)
	//	{

	//		if (g_BillBoord[nCount].nType == 4)
	//		{
	//			g_BillBoord[nCount].nCounterAnim++;		//カウンター加算
	//			//影がついてくる
	//			SetPositionShadow(g_BillBoord[nCount].nIdxShadow, g_BillBoord[nCount].posBillBoord, g_BillBoord[nCount].rotBillBoord);

	//			if ((g_BillBoord[nCount].nCounterAnim % BILLBOORD_TEXTURE_SPEED) == 0 && g_BillBoord[nCount].nType == 4)
	//			{//アニメーション速度                                                  ↓パターンが１づつ進んでいくよ(２にすると２個ずつ進む)
	//				g_BillBoord[nCount].nPatteunAnim = (g_BillBoord[nCount].nPatteunAnim + 1) % BILLBOORD_TEXTURE_PATTERN;		//パターンNo.更新
	//																													//頂点設定
	//				pVtx[nCount * 4].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x - BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y - BILLBOORD_ZONBI_HEI, 0.0f);
	//				pVtx[nCount * 4 + 1].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x + BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y - BILLBOORD_ZONBI_HEI, 0.0f);
	//				pVtx[nCount * 4 + 2].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x - BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y + BILLBOORD_ZONBI_HEI, 0.0f);
	//				pVtx[nCount * 4 + 3].pos = D3DXVECTOR3(g_BillBoord[nCount].posBillBoord.x + BILLBOORD_ZONBI_WID, g_BillBoord[nCount].posBillBoord.y + BILLBOORD_ZONBI_HEI, 0.0f);
	//				//頂点カラー設定
	//				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//				//テクスチャ設定
	//				pVtx[nCount * 4].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim, 0.0f);
	//				pVtx[nCount * 4 + 1].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim + BILLBOORD_TEXTURE_UV_U, 0.0f);
	//				pVtx[nCount * 4 + 2].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim, BILLBOORD_TEXTURE_UV_V);
	//				pVtx[nCount * 4 + 3].tex = D3DXVECTOR2(BILLBOORD_TEXTURE_UV_U * g_BillBoord[nCount].nPatteunAnim + BILLBOORD_TEXTURE_UV_U, BILLBOORD_TEXTURE_UV_V);
	//			}
	//		}
	//	}
	//}
	////頂点バッファをアンロック
	//g_pVtxBuffBillBoord->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBillBoord(void)
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
	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//ビルボードをカウント
		if (g_BillBoord[nCount].bUse == true)
		{//ビルボードがある場合

			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_BillBoord[nCount].mtxWorldBillBoord);

			//ビルボード
			pDevice->GetTransform
			(
				D3DTS_VIEW,
				&mtxView
			);

			//逆行列を設定
			g_BillBoord[nCount].mtxWorldBillBoord._11 = mtxView._11;
			g_BillBoord[nCount].mtxWorldBillBoord._12 = mtxView._21;
			g_BillBoord[nCount].mtxWorldBillBoord._13 = mtxView._31;
			g_BillBoord[nCount].mtxWorldBillBoord._21 = mtxView._12;
			g_BillBoord[nCount].mtxWorldBillBoord._22 = mtxView._22;
			g_BillBoord[nCount].mtxWorldBillBoord._23 = mtxView._32;
			g_BillBoord[nCount].mtxWorldBillBoord._31 = mtxView._13;
			g_BillBoord[nCount].mtxWorldBillBoord._32 = mtxView._23;
			g_BillBoord[nCount].mtxWorldBillBoord._33 = mtxView._33;

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_BillBoord[nCount].posBillBoord.x, g_BillBoord[nCount].posBillBoord.y, g_BillBoord[nCount].posBillBoord.z);

			D3DXMatrixMultiply(&g_BillBoord[nCount].mtxWorldBillBoord, &g_BillBoord[nCount].mtxWorldBillBoord, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_BillBoord[nCount].mtxWorldBillBoord);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBillBoord, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBillBoord[g_BillBoord[nCount].nType]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
	//アルファテストを無効か
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexBillBoord(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１枚目
		pDevice,
		BILLBOORD_TEXTURE_NAME,
		&g_pTextureBillBoord[0]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像２枚目
		pDevice,
		BILLBOORD_TEXTURE_NAME1,
		&g_pTextureBillBoord[1]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像３枚目
		pDevice,
		BILLBOORD_TEXTURE_NAME2,
		&g_pTextureBillBoord[2]
	);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像４枚目
		pDevice,
		BILLBOORD_TEXTURE_NAME3,
		&g_pTextureBillBoord[3]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像５枚目
		pDevice,
		BILLBOORD_TEXTURE_NAME4,
		&g_pTextureBillBoord[4]
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_BILLBOORD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillBoord,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffBillBoord->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//全カウントを回す
	 //頂点座
		pVtx[0].pos = D3DXVECTOR3(-10, 30, 0);
		pVtx[1].pos = D3DXVECTOR3(10, 30, 0);
		pVtx[2].pos = D3DXVECTOR3(-10, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(10, 0, 0);

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
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファのアンロックする
	g_pVtxBuffBillBoord->Unlock();
}
//=============================================================================
// ビルボードの作成
//=============================================================================
void SetBillBoord(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nType)
{
	for (int nCount = 0; nCount < MAX_BILLBOORD; nCount++)
	{//全テクスチャのカウント
		if (g_BillBoord[nCount].bUse == false)
		{
			g_BillBoord[nCount].posBillBoord = pos;			//pos値代入
			g_BillBoord[nCount].rotBillBoord = rot;			//rot値代入
			g_BillBoord[nCount].nCounterAnim = 0;			//カウンター初期値設定
			g_BillBoord[nCount].nPatteunAnim = 0;			//パターンNo.初期値設定
			g_BillBoord[nCount].nType = nType;				//種類を代入
			g_BillBoord[nCount].bUse = true;				//使用している状態にする

			if (g_BillBoord[nCount].nType !=4)
			{
				//影をつける
				SetShadow(g_BillBoord[nCount].posBillBoord, g_BillBoord[nCount].rotBillBoord, 10.0f, 10.0f);

			}
			break;
		}
	}
}
//=========================================================================================================================
// 消すビルボード
//=========================================================================================================================
void DeleteBillBoord(int nCntBillBoord)
{
	if (g_BillBoord[nCntBillBoord].nType == 4)
	{
		//使用していない状態
		g_BillBoord[nCntBillBoord].bUse = false;

		//使っている影をfalse
		DeleteShadow(g_BillBoord[nCntBillBoord].nIdxShadow);
	}
}
//=========================================================================================================================
// ビルボードのあたり判定
//=========================================================================================================================
void CollisionBillBoord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove)
{
	//カウント
	int nCount = 0;

	//カウント
	int nCntBillBoord;

	//弾のポインタ
	Bullet *pBullet = GetBullet();



	for (int nCntBullet = 0; nCntBullet < 300; nCntBullet++)
	{
		if (pBullet[nCntBullet].bUse == true)
		{
			for (nCntBillBoord = 0; nCntBillBoord < MAX_BILLBOORD; nCntBillBoord++)
			{//アイテムをカウント
				if (g_BillBoord[nCntBillBoord].bUse == true)
				{
					if (pBullet[nCntBullet].posBullet.y - 2 < g_BillBoord[nCntBillBoord].posBillBoord.y + 30 && pBullet[nCntBullet].posBullet.y > g_BillBoord[nCntBillBoord].posBillBoord.y)
					{//あたり判定
						if (pBullet[nCntBullet].posBullet.x + 2 >= g_BillBoord[nCntBillBoord].posBillBoord.x - 15 && pBullet[nCntBullet].posBullet.x - 2 <= g_BillBoord[nCntBillBoord].posBillBoord.x + 15 && pBullet[nCntBullet].posBullet.z + 2 >= g_BillBoord[nCntBillBoord].posBillBoord.z - 15 && pBullet[nCntBullet].posBullet.z - 2 <= g_BillBoord[nCntBillBoord].posBillBoord.z + 15)
						{
							DeleteBillBoord(nCntBillBoord);
						}

					}
				}
			}
		}
	}
}
