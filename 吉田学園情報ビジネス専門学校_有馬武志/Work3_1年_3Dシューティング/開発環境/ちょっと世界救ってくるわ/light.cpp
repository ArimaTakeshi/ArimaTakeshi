//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 
//
//=============================================================================
#include "light.h"		//ライト

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_LIGHT		(3)			//ライトの最大数

//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DLIGHT9 g_Light[MAX_LIGHT];		//ライトの情報
//int g_nCntDiffuse = 0;				//秒数カウント

//=============================================================================
// ライトの初期化処理
//=============================================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXVECTOR3 vecDir[MAX_LIGHT];

	// ライトの方向の設定
	/*vecDir[0] = D3DXVECTOR3(0.2f, -1.0f, -0.4f);
	vecDir[1] = D3DXVECTOR3(0.0f, -1.0f, -0.4f);
	vecDir[2] = D3DXVECTOR3(-0.2f, -1.0f, -0.4f);*/

	//// ライトの方向の設定
	vecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	vecDir[1] = D3DXVECTOR3(-0.18f, -0.88f, -0.44f);
	vecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);


	//if (g_nCntDiffuse >= 0 && g_nCntDiffuse <= 599)
	{
		//// ライトの拡散光を設定
		//g_Light[0].Diffuse = D3DXCOLOR(0.45f, 0.45f, 0.45f, 0.40f);
		//g_Light[1].Diffuse = D3DXCOLOR(0.45f, 0.45f, 0.45f, 0.40f);
		//g_Light[2].Diffuse = D3DXCOLOR(0.45f, 0.45f, 0.40f, 0.40f);

		//// ライトの拡散光を設定
		//g_Light[0].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
		//g_Light[1].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);
		//g_Light[2].Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.6f);

		//デバック用
		// ライトの拡散光を設定0.35f,1.0f
		g_Light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	//if (g_nCntDiffuse >= 600 && g_nCntDiffuse <= 699)
	//{
	//	// ライトの拡散光を設定
	//	g_Light[0].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	//	g_Light[1].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	//	g_Light[2].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f);
	//}
	//if (g_nCntDiffuse == 700)
	//{
	//	g_nCntDiffuse = 0;
	//}
	//g_nCntDiffuse++;

	// ライトをクリアする
	ZeroMemory(&g_Light, sizeof(D3DLIGHT9));

	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		// ライトの種類を設定
		g_Light[nCount].Type = D3DLIGHT_DIRECTIONAL;

		//正規化する
		D3DXVec3Normalize(&vecDir[nCount], &vecDir[nCount]);
		g_Light[nCount].Direction = vecDir[nCount];

		// ライトを設定する ↓これを入れないと、ライトが全部使えない
		pDevice->SetLight(nCount, &g_Light[nCount]);

		// ライトを有効にする
		pDevice->LightEnable(nCount, TRUE);
	}

}

//=============================================================================
// ライトの終了処理
//=============================================================================
void UninitLight(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void UpdateLight(void)
{
}

