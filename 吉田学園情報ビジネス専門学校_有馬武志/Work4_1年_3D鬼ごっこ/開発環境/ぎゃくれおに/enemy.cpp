//=============================================================================
//
// 敵処理 [enemy.cpp]
// Author : 有馬 武志　＆　箱崎
//
//=============================================================================
#include "enemy.h"		//敵
#include "input.h"		//キーボード
#include "camera.h"		//カメラ
#include "shadow.h"		//影
#include "bullet.h"		//弾
#include "object.h"		//オブジェクト
#include "player.h"		//プレイヤー
#include "player2.h"	//プレイヤー２
#include "fade.h"		//フェード
#include "effect.h"		//エフェクト
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME		"data\\MODEL\\オニ_街灯.x"			//読み込むテクスチャファイル
#define MODEL_NAME1		"data\\MODEL\\オニ_ダンボール.x"	//読み込むテクスチャファイル
#define MODEL_NAME2		"data\\MODEL\\オニ_ゴミ箱.x"		//読み込むテクスチャファイル
#define ENEMYMODEL_SPEED (1.1f)								//敵スピード
#define ENEMY_SPEED		(5.5f)								//敵のスピード
#define MAX_ENEMY_TYPE	(3)									//敵の種類

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Enemy g_Enemy[MAX_ENEMY_TYPE];			//敵
float g_fJoyStickAngle;

//=============================================================================
// 初期化処理
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(//街灯
		MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy[0].pBuffMatEnemy,
		NULL,
		&g_Enemy[0].nNumMatEnemy,
		&g_Enemy[0].pMeshEnemy
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(//段ボール
		MODEL_NAME1,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy[1].pBuffMatEnemy,
		NULL,
		&g_Enemy[1].nNumMatEnemy,
		&g_Enemy[1].pMeshEnemy
	);
	// Xファイルの読み込み
	D3DXLoadMeshFromX
	(//ゴミ箱
		MODEL_NAME2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_Enemy[2].pBuffMatEnemy,
		NULL,
		&g_Enemy[2].nNumMatEnemy,
		&g_Enemy[2].pMeshEnemy
	);

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE * pVtxBuff;	//頂点バッファへのポインタ

	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		g_Enemy[nCount].posOld = D3DXVECTOR3(0, 0, 0);
		g_Enemy[nCount].nCntPlayer = 2;
		g_Enemy[nCount].pos = D3DXVECTOR3(2000, 20, -4100);
		g_Enemy[nCount].rot = D3DXVECTOR3(0, 0, 0);
		g_Enemy[nCount].move = D3DXVECTOR3(0, 0, 0);
		g_Enemy[nCount].bUse = false;

		//最大値と最小値
		g_Enemy[nCount].vtxMinModel = D3DXVECTOR3(10000, 10000, 10000);
		g_Enemy[nCount].vtxMaxModel = D3DXVECTOR3(-10000, -10000, -10000);

		//頂点数を取得
		nNumVtx = g_Enemy[nCount].pMeshEnemy->GetNumVertices();

		//頂点フォーマットのサイズ
		sizeFVF = D3DXGetFVFVertexSize(g_Enemy[nCount].pMeshEnemy->GetFVF());

		//頂点フォーマットをロック
		g_Enemy[nCount].pMeshEnemy->LockVertexBuffer(D3DLOCK_READONLY, (void**)& pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{	//頂点座標の代入
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			//最小値
			if (vtx.x < g_Enemy[nCount].vtxMinModel.x)
			{
				g_Enemy[nCount].vtxMinModel.x = vtx.x;
			}
			if (vtx.z < g_Enemy[nCount].vtxMinModel.z)
			{
				g_Enemy[nCount].vtxMinModel.z = vtx.z;
			}

			//最大値
			if (vtx.x > g_Enemy[nCount].vtxMaxModel.x)
			{
				g_Enemy[nCount].vtxMaxModel.x = vtx.x;
			}
			if (vtx.z > g_Enemy[nCount].vtxMaxModel.z)
			{
				g_Enemy[nCount].vtxMaxModel.z = vtx.z;
			}

			pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
		}

		//頂点バッファをアンロック
		g_Enemy[nCount].pMeshEnemy->UnlockVertexBuffer();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		// メッシュの開放
		if (g_Enemy[nCount].pMeshEnemy != NULL)
		{
			g_Enemy[nCount].pMeshEnemy->Release();
			g_Enemy[nCount].pMeshEnemy = NULL;
		}
		// マテリアルの開放
		if (g_Enemy[nCount].pBuffMatEnemy != NULL)
		{
			g_Enemy[nCount].pBuffMatEnemy->Release();
			g_Enemy[nCount].pBuffMatEnemy = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	//カメラの情報
	Camera *pCamera = GetCamera();

	//プレイヤーの取得
	Player * pPlayer = GetPlayer();

	//プレイヤー2の取得
	Player2 * pPlayer2 = GetPlayer2();

	//フェードを取得
	FADE pFade = GetFade();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		if (GetKeyboardTrigger(DIK_NUMPAD7) == true || GetJoyPadTrigger(0, 2) == true)
		{
			//エフェクト
			SetParticleEffect(g_Enemy[nCount].pos, EFFECTTYPE_EXPLOSION2, 50, 30, 5, 0);

			PlaySound(SOUND_LABEL_SE_HENNSIN);
			// Xファイルの読み込み
			D3DXLoadMeshFromX
			(
				MODEL_NAME,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCount].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCount].nNumMatEnemy,
				&g_Enemy[nCount].pMeshEnemy
			);
		}
		else if (GetKeyboardTrigger(DIK_NUMPAD8) == true || GetJoyPadTrigger(1, 2) == true)
		{
			//エフェクト
			SetParticleEffect(g_Enemy[nCount].pos, EFFECTTYPE_EXPLOSION2, 50, 30, 5, 0);

			PlaySound(SOUND_LABEL_SE_HENNSIN);
			// Xファイルの読み込み
			D3DXLoadMeshFromX
			(
				MODEL_NAME1,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCount].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCount].nNumMatEnemy,
				&g_Enemy[nCount].pMeshEnemy
			);
		}
		else if (GetKeyboardTrigger(DIK_NUMPAD9) == true || GetJoyPadTrigger(2, 2) == true)
		{
			//エフェクト
			SetParticleEffect(g_Enemy[nCount].pos, EFFECTTYPE_EXPLOSION2, 50, 30, 5, 0);

			PlaySound(SOUND_LABEL_SE_HENNSIN);
			// Xファイルの読み込み
			D3DXLoadMeshFromX
			(
				MODEL_NAME2,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_Enemy[nCount].pBuffMatEnemy,
				NULL,
				&g_Enemy[nCount].nNumMatEnemy,
				&g_Enemy[nCount].pMeshEnemy
			);
		}
		
		//前回の位置を保存
		g_Enemy[nCount].posOld = g_Enemy[nCount].pos;

		//壁のあたり判定
		if (g_Enemy[nCount].pos.z >= 200)
		{//上
			g_Enemy[nCount].pos.z = 200;
		}
		if (g_Enemy[nCount].pos.z <= -4200)
		{//下
			g_Enemy[nCount].pos.z = -4200;
		}
		if (g_Enemy[nCount].pos.x >= 4200)
		{//右
			g_Enemy[nCount].pos.x = 4200;
		}
		if (g_Enemy[nCount].pos.x <= -200)
		{//左
			g_Enemy[nCount].pos.x = -200;
		}

		//移動処理
		if (GetKeyboardPress(DIK_UP) == true)
		{//矢印の上							↓上移動
			if (GetKeyboardPress(DIK_RIGHT) == true)
			{
				g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//その方向に向く
				g_Enemy[nCount].rot.y = ((D3DX_PI * -0.75f) + pCamera->rot.y);
			}
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{
				g_Enemy[nCount].move.x += sinf((-D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((-D3DX_PI * 0.25f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//その方向に向く
				g_Enemy[nCount].rot.y = ((D3DX_PI * 0.75f) + pCamera->rot.y);
			}
			else
			{
				g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//その方向に向く
				g_Enemy[nCount].rot.y = ((D3DX_PI * -1.0f) + pCamera->rot.y);
			}
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//矢印の下							 ↓上移動
			if (GetKeyboardPress(DIK_RIGHT) == true)
			{
				g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//その方向に向く
				g_Enemy[nCount].rot.y = ((D3DX_PI * -0.25f) + pCamera->rot.y);
			}
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{
				g_Enemy[nCount].move.x += sinf((-D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((-D3DX_PI * 0.75f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//その方向に向く
				g_Enemy[nCount].rot.y = ((D3DX_PI * 0.25f) + pCamera->rot.y);
			}
			else
			{
				g_Enemy[nCount].move.x += sinf((-D3DX_PI * 1.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				g_Enemy[nCount].move.z += cosf((-D3DX_PI * 1.0f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
				//その方向に向く
				g_Enemy[nCount].rot.y = ((D3DX_PI * 0.0f) + pCamera->rot.y);
			}
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{//矢印の右							↓ 右移動
			g_Enemy[nCount].move.x += sinf((D3DX_PI * 0.5f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
			g_Enemy[nCount].move.z += cosf((D3DX_PI * 0.5f) + pCamera->rot.y)* ENEMYMODEL_SPEED;
			//その方向に向く
			g_Enemy[nCount].rot.y = ((D3DX_PI * -0.5f) + pCamera->rot.y);
		}
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{//矢印の左							 ↓ 左移動
			g_Enemy[nCount].move.x += sinf((-D3DX_PI * 0.5f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
			g_Enemy[nCount].move.z += cosf((-D3DX_PI * 0.5f) + pCamera->rot.y) * ENEMYMODEL_SPEED;
			//その方向に向く
			g_Enemy[nCount].rot.y = ((D3DX_PI * 0.5f) + pCamera->rot.y);
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, 2) == true || GetJoyPadPress(DIJS_BUTTON_11, 2) == true || GetJoyPadPress(DIJS_BUTTON_12, 2) == true || GetJoyPadPress(DIJS_BUTTON_13, 2) == true)
		{//ジョイコン
			g_Enemy[nCount].pos.x -= sinf(pCamera->fAngle - GetJotPadRightStick(2)) * ENEMY_SPEED;
			g_Enemy[nCount].pos.z -= cosf(pCamera->fAngle - GetJotPadRightStick(2)) * ENEMY_SPEED;

			g_Enemy[nCount].rot.y = pCamera->fAngle - GetJotPadRightStick(2);
		}

		//位置を移動に代入
		g_Enemy[nCount].pos += g_Enemy[nCount].move;

		//慣性をつける
		g_Enemy[nCount].move.x += (0.0f - g_Enemy[nCount].move.x) * 0.2f;
		g_Enemy[nCount].move.z += (0.0f - g_Enemy[nCount].move.z) * 0.2f;

		//あたり判定
		CollisionObject(&g_Enemy[nCount].pos, &g_Enemy[nCount].posOld, &g_Enemy[nCount].move);

		//オブジェクトのあたり判定
		CollisionObject(&g_Enemy[nCount].pos, &g_Enemy[nCount].posOld, &g_Enemy[nCount].move);


		if (pPlayer->nCntPlayer <= 0 && pPlayer2->nCntPlayer2 <= 0)
		{	//プレイヤー1とプレイヤー2が捕まったらゲームオーバー
			if (pFade != FADE_OUT)
			{	//フェードアウト中にEnterキーを押せなくする
				//モード設定
				SetGameState(GAMESTATE_OVER);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算洋間鳥kk数
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	for (int nCount = 0; nCount < MAX_ENEMY_TYPE; nCount++)
	{
		if (nCount == 0)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[nCount].mtxWorldEnemy);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[nCount].rot.y, g_Enemy[nCount].rot.x, g_Enemy[nCount].rot.z);

			D3DXMatrixMultiply(&g_Enemy[nCount].mtxWorldEnemy, &g_Enemy[nCount].mtxWorldEnemy, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Enemy[nCount].pos.x, g_Enemy[nCount].pos.y, g_Enemy[nCount].pos.z);

			D3DXMatrixMultiply(&g_Enemy[nCount].mtxWorldEnemy, &g_Enemy[nCount].mtxWorldEnemy, &mtxTrans);

			// ワールドマトリックスの設3定
			pDevice->SetTransform(D3DTS_WORLD, &g_Enemy[nCount].mtxWorldEnemy);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_Enemy[nCount].pBuffMatEnemy->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Enemy[nCount].nNumMatEnemy; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャをNULLにする
				pDevice->SetTexture(0, NULL);

				//pDevice->SetTexture(0, g_Enemy[].nNumMatEnemy);

				// 敵(パーツ)の描画
				g_Enemy[nCount].pMeshEnemy->DrawSubset(nCntMat);
			}
		}
	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}
//=============================================================================
// プレイヤーの当たり判定	 （プレイヤー1）
//=============================================================================
bool CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld, D3DXVECTOR3  * pMove)
{
	//プレイヤーの取得
	Player *pPlayer = GetPlayer();

	bool bLand = false;						//最初は捕まってない状態

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TYPE; nCntEnemy++)
	{
		if (pPlayer->bUse == true)
		{
			bLand = false;

			if (g_Enemy[nCntEnemy].pos.x > pPlayer->pos.x - 20
				&& g_Enemy[nCntEnemy].pos.x < pPlayer->pos.x + 20
				&& g_Enemy[nCntEnemy].pos.z > pPlayer->pos.z - 20
				&& g_Enemy[nCntEnemy].pos.z < pPlayer->pos.z + 20)
			{
				pPlayer->nCntPlayer -= 1;
				bLand = true;								//捕まった状態にする
				pPlayer->bUse = false;
				//使っている影をfalse
				DeleteShadow(pPlayer->nIdxShadow);

				PlaySound(SOUND_LABEL_SE_BUTUKARU);
				//エフェクト
				SetParticleEffect(pPlayer->pos, EFFECTTYPE_EXPLOSION, 200, 10, 5, 0);
				break;										//捕まったらif文抜ける
			}
		}
	}

	return bLand;
}

//=============================================================================
// プレイヤー2の当たり判定	（プレイヤー2）
//=============================================================================
bool CollisionEnemy2(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//プレイヤー2の取得
	Player2 *pPlayer2 = GetPlayer2();

	Enemy *pEnemy = GetEnemy();

	bool bLand = false;

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY_TYPE; nCntEnemy++)
	{
		if (pPlayer2->bUse == true)
		{
			if (g_Enemy[nCntEnemy].pos.x > pPlayer2->pos.x - 20
				&& g_Enemy[nCntEnemy].pos.x < pPlayer2->pos.x + 20
				&& g_Enemy[nCntEnemy].pos.z > pPlayer2->pos.z - 20
				&& g_Enemy[nCntEnemy].pos.z < pPlayer2->pos.z + 20)
			{
				pPlayer2->nCntPlayer2 -= 1;
				bLand = true;								//捕まった状態にする
				pPlayer2->bUse = false;
				//使っている影をfalse
				DeleteShadow(pPlayer2->nIdxShadow2);

				PlaySound(SOUND_LABEL_SE_BUTUKARU);
				//エフェクト
				SetParticleEffect(pPlayer2->pos, EFFECTTYPE_EXPLOSION, 200, 10, 5, 0);
				break;										//捕まったらif文抜ける
			}
		}
	}
	return bLand;

}
//=========================================================================================================================
// 敵の取得処理
//=========================================================================================================================
Enemy *GetEnemy(void)
{
	return &g_Enemy[0];
}
