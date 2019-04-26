//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : 有馬　武志　＆　箱崎
//
//=============================================================================
#define	_CRT_SECURE_NO_WARNINGS		//scanfエラー解除
#include <stdio.h>					//stdio
#include "player.h"					//プレイヤー
#include "input.h"					//キーボード
#include "camera.h"					//カメラ
#include "shadow.h"					//影
#include "effect.h"					//エフェクト
#include "object.h"					//オブジェクト
#include "sound.h"					//サウンド
#include "enemy.h"
#include "time.h"
#include "explosion.h"
#include "window.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define MODEL_NAME			"data\\MODEL\\airplane000.x"	//読み込むテクスチャファイル
//#define MODEL_NAME			"data\\MODEL\\00_body.x"		//読み込むテクスチャファイル
//#define MODEL_NAME2			"data\\MODEL\\01_head.x"		//読み込むテクスチャファイル
//#define MODEL_NAME3			"data\\MODEL\\02_armR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME4			"data\\MODEL\\03_handR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME5			"data\\MODEL\\04_armL.x"		//読み込むテクスチャファイル
//#define MODEL_NAME6			"data\\MODEL\\05_handL.x"		//読み込むテクスチャファイル
//#define MODEL_NAME7			"data\\MODEL\\06_legR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME8			"data\\MODEL\\07_footR.x"		//読み込むテクスチャファイル
//#define MODEL_NAME9			"data\\MODEL\\08_legL.x"		//読み込むテクスチャファイル
//#define MODEL_NAME10			"data\\MODEL\\09_footL.x"		//読み込むテクスチャファイル
#define PLAYER1_SPEED			(5.0f)

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Player		g_Player;							//プレイヤー
int			g_nCntTimePlayer;					//プレイヤーカウンター
float		g_fJoyStickAnglePlayer1;			//
int			g_nCntTime;

//=============================================================================
// 初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルのポインタ
	FILE *pFile;
	//プレイヤーカウンター
	int nCntPlayer;

	// 位置・向きの初期設定
	g_Player.pos = D3DXVECTOR3(0, 20, 40);
	g_Player.rot = D3DXVECTOR3(0, 0, 0);
	g_Player.move = D3DXVECTOR3(0, 0, 0);
	g_Player.nCntPlayer = 1;
	g_Player.bUse = true;
	g_Player.bLand = true;
	g_Player.bDistance = false;
	g_Player.nCntDistance = 0;
	SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 0.5f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 1, 0, 1, 1, 0, WINDOW_UPDATE_GAME, WINDOWSTATE_NORMAL, WINDOWUSE_GAME, WINDOWTYPE_CENTER, WINDOW_DRAW_1);

	//ファイル設定
	pFile = fopen(FILE_NAME, "r");

	//プレイヤーの￥テキストデータの読み込み
	if (pFile != NULL)
	{
		//使うパーツ数
		fscanf(pFile, "%d", &g_Player.nMaxPartsNum);	//読み込み

														//ファイル名
		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{
			fscanf(pFile, "%s", &g_Player.aModel[nCntPlayer].FileName[0]); //読み込み
		}

		for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
		{//初期値と向き
			fscanf(pFile, "%d", &g_Player.aModel[nCntPlayer].nIdxModelParent);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.x);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.y);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitPos.z);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.x);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.y);//読み込み
			fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].InitRot.z);//読み込み
		}

		//ファイル読み込み
		fscanf(pFile, "%d", &g_Player.nMaxAnimNum);

		for (int nCntPlayerAnim = 0; nCntPlayerAnim < g_Player.nMaxPartsNum; nCntPlayerAnim++)
		{
			//フレーム数
			fscanf(pFile, "%d", &g_Player.nAnimloop[nCntPlayerAnim]);

			//キー数
			fscanf(pFile, "%d", &g_Player.nAnimKey[nCntPlayerAnim]);

			for (int nCntPlayerAnimKey = 0; nCntPlayerAnimKey < g_Player.nAnimKey[nCntPlayerAnim]; nCntPlayerAnimKey++)
			{
				fscanf(pFile, "%d", &g_Player.nAnimfram[nCntPlayerAnim][nCntPlayerAnimKey]);//読み込み

				for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
				{
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].posAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].x);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].y);		//読み込み
					fscanf(pFile, "%f", &g_Player.aModel[nCntPlayer].rotAnim[nCntPlayerAnim][nCntPlayerAnimKey].z);		//読み込み
				}
			}
		}

		fclose(pFile);	//ファイルを閉じる
	}
	else
	{
		MessageBox(0, "セーブファイルのチェックに失敗!", "警告", MB_ICONWARNING);
	}

	//xファイルの読み込み
	for (nCntPlayer = 0; nCntPlayer < g_Player.nMaxPartsNum; nCntPlayer++)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX
		(
			&g_Player.aModel[nCntPlayer].FileName[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_Player.aModel[nCntPlayer].pBuffMatModel,
			NULL,
			&g_Player.aModel[nCntPlayer].nNumMatModel,
			&g_Player.aModel[nCntPlayer].pMeshModel
		);
	}

	//影の初期化設定
	g_Player.nIdxShadow = SetShadow(g_Player.pos, g_Player.rot, 15, 15);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// メッシュの開放
		if (g_Player.aModel[nCount].pMeshModel != NULL)
		{
			g_Player.aModel[nCount].pMeshModel->Release();
			g_Player.aModel[nCount].pMeshModel = NULL;
		}
	}
	for (int nCount = 0; nCount < MAX_PARTS; nCount++)
	{
		// マテリアルの開放
		if (g_Player.aModel[nCount].pBuffMatModel != NULL)
		{
			g_Player.aModel[nCount].pBuffMatModel->Release();
			g_Player.aModel[nCount].pBuffMatModel = NULL;
		}
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//カメラの情報
	Camera *pCamera = GetCamera();

	Time *pTime = GetTime();

	//鬼の取得
	Enemy *pEnemy = GetEnemy();

	if (g_Player.bUse == true)
	{
		//フレームカウント
		g_nCntTimePlayer++;

		//前回の位置を保存
		g_Player.posOld = g_Player.pos;

		float nSpeed = 5.0f;	//速度
								//float fDiffAngle;

		//壁のあたり判定
		if (g_Player.pos.z >= 200)
		{//上
			g_Player.pos.z = 200;
		}
		if (g_Player.pos.z <= -4200)
		{//下
			g_Player.pos.z = -4200;
		}
		if (g_Player.pos.x >= 4200)
		{//右
			g_Player.pos.x = 4200;
		}
		if (g_Player.pos.x <= -200)
		{//左
			g_Player.pos.x = -200;
		}

		//移動処理
		if (GetKeyboardPress(DIK_W) == true)
		{//矢印の上							↓上移動
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_Player.move.x += sinf((D3DX_PI * 0.25f) + pCamera[0].fAngle) * MODEL_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.25f) + pCamera[0].fAngle) * MODEL_SPEED;
				//その方向に向く
				//g_Player.rot.y = (pCamera[0].fAngle);

				if (g_Player.nAnimnow != PLAYERANIM_WALK)
				{//歩くアニメーション
					g_Player.nAnimnow = PLAYERANIM_WALK;
					g_nCntTimePlayer = 0;
					g_Player.nAnimKeynow = 0;
				}
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{
				g_Player.move.x += sinf((-D3DX_PI * 0.25f) + pCamera[0].fAngle) * MODEL_SPEED;
				g_Player.move.z += cosf((-D3DX_PI * 0.25f) + pCamera[0].fAngle) * MODEL_SPEED;
				//その方向に向く
				//g_Player.rot.y = (pCamera[0].fAngle);

				if (g_Player.nAnimnow != PLAYERANIM_WALK)
				{//歩くアニメーション
					g_Player.nAnimnow = PLAYERANIM_WALK;
					g_nCntTimePlayer = 0;
					g_Player.nAnimKeynow = 0;
				}
			}
			else
			{
				g_Player.move.x += sinf((D3DX_PI * 0.0f) + pCamera[0].fAngle) * MODEL_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.0f) + pCamera[0].fAngle) * MODEL_SPEED;
				//その方向に向く
				//g_Player.rot.y = (pCamera[0].fAngle);

				if (g_Player.nAnimnow != PLAYERANIM_WALK)
				{//歩くアニメーション
					g_Player.nAnimnow = PLAYERANIM_WALK;
					g_nCntTimePlayer = 0;
					g_Player.nAnimKeynow = 0;
				}
			}
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//矢印の下							 ↓上移動
			if (GetKeyboardPress(DIK_D) == true)
			{
				g_Player.move.x += sinf((D3DX_PI * 0.75f) + pCamera[0].fAngle) * MODEL_SPEED;
				g_Player.move.z += cosf((D3DX_PI * 0.75f) + pCamera[0].fAngle) * MODEL_SPEED;
				//その方向に向く
				//g_Player.rot.y = (pCamera[0].fAngle);

				if (g_Player.nAnimnow != PLAYERANIM_WALK)
				{//歩くアニメーション
					g_Player.nAnimnow = PLAYERANIM_WALK;
					g_nCntTimePlayer = 0;
					g_Player.nAnimKeynow = 0;
				}
			}
			else if (GetKeyboardPress(DIK_A) == true)
			{
				g_Player.move.x += sinf((-D3DX_PI * 0.75f) + pCamera[0].fAngle) * MODEL_SPEED;
				g_Player.move.z += cosf((-D3DX_PI * 0.75f) + pCamera[0].fAngle) * MODEL_SPEED;
				//その方向に向く
				//g_Player.rot.y = (pCamera[0].fAngle);

				if (g_Player.nAnimnow != PLAYERANIM_WALK)
				{//歩くアニメーション
					g_Player.nAnimnow = PLAYERANIM_WALK;
					g_nCntTimePlayer = 0;
					g_Player.nAnimKeynow = 0;
				}
			}
			else
			{
				g_Player.move.x += sinf((-D3DX_PI * 1.0f) + pCamera[0].fAngle) * MODEL_SPEED;
				g_Player.move.z += cosf((-D3DX_PI * 1.0f) + pCamera[0].fAngle) * MODEL_SPEED;
				//その方向に向く
				//g_Player.rot.y = (pCamera[0].fAngle);

				if (g_Player.nAnimnow != PLAYERANIM_WALK)
				{//歩くアニメーション
					g_Player.nAnimnow = PLAYERANIM_WALK;
					g_nCntTimePlayer = 0;
					g_Player.nAnimKeynow = 0;
				}
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//矢印の右							↓ 右移動
			g_Player.move.x += sinf((D3DX_PI * 0.5f) + pCamera[0].fAngle) * MODEL_SPEED;
			g_Player.move.z += cosf((D3DX_PI * 0.5f) + pCamera[0].fAngle)* MODEL_SPEED;
			//その方向に向く
			//g_Player.rot.y = (pCamera[0].fAngle);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//歩くアニメーション
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else if (GetKeyboardPress(DIK_A) == true)
		{//矢印の左							 ↓ 左移動
			g_Player.move.x += sinf((-D3DX_PI * 0.5f) + pCamera[0].fAngle) * MODEL_SPEED;
			g_Player.move.z += cosf((-D3DX_PI * 0.5f) + pCamera[0].fAngle) * MODEL_SPEED;
			//その方向に向く
			//g_Player.rot.y = (pCamera[0].fAngle);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//歩くアニメーション
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else if (GetJoyPadPress(DIJS_BUTTON_10, 0) == true || GetJoyPadPress(DIJS_BUTTON_11, 0) == true || GetJoyPadPress(DIJS_BUTTON_12, 0) == true || GetJoyPadPress(DIJS_BUTTON_13, 0) == true)
		{//ジョイコン
			g_Player.pos.x -= sinf(pCamera[0].fAngle - GetJotPadRightStick(0)) * PLAYER1_SPEED;
			g_Player.pos.z -= cosf(pCamera[0].fAngle - GetJotPadRightStick(0)) * PLAYER1_SPEED;

			//g_Player.rot.y = pCamera[0].fAngle - GetJotPadRightStick(0);

			if (g_Player.nAnimnow != PLAYERANIM_WALK)
			{//歩くアニメーション
				g_Player.nAnimnow = PLAYERANIM_WALK;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}
		else
		{
			if (g_Player.nAnimnow != PLAYERANIM_NEUTRAL)
			{//待機モーション
				g_Player.nAnimnow = PLAYERANIM_NEUTRAL;
				g_nCntTimePlayer = 0;
				g_Player.nAnimKeynow = 0;
			}
		}

		g_Player.rot.y = (pCamera[0].fAngle + D3DX_PI);

		//位置を移動に代入
		g_Player.pos += g_Player.move;

		//慣性をつける
		g_Player.move.x += (0.0f - g_Player.move.x) * 0.2f;
		g_Player.move.z += (0.0f - g_Player.move.z) * 0.2f;

		//影がついてくる
		SetPositionShadow(g_Player.nIdxShadow, g_Player.pos, g_Player.rot);

		//あたり判定
		CollisionObject(&g_Player.pos, &g_Player.posOld, &g_Player.move);
		CollisionEnemy(&g_Player.pos, &g_Player.posOld, &g_Player.move);

		//差分のローカル変数
		float fDes;
		float frac;

		//キーを進める！
		if (g_nCntTimePlayer % g_Player.nAnimfram[g_Player.nAnimnow][g_Player.nAnimKeynow] == 0)
		{
			g_nCntTimePlayer = 0;
			g_Player.nAnimKeynow = (g_Player.nAnimKeynow + 1) % g_Player.nAnimKey[g_Player.nAnimnow];
		}

		//差分の計算
		frac = (g_Player.nAnimfram[g_Player.nAnimnow][g_Player.nAnimKeynow] - g_nCntTimePlayer) * 1.0f;

		//アニメーション
		for (int nCntPlayerAnim = 0; nCntPlayerAnim < g_Player.nMaxPartsNum; nCntPlayerAnim++)
		{
			//===================
			// Xの角度
			//===================

			//目的の角度をしらべる
			g_Player.aModel[nCntPlayerAnim].rotDest = g_Player.aModel[nCntPlayerAnim].rotAnim[g_Player.nAnimnow][g_Player.nAnimKeynow];

			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].rotDest.x > D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].rotDest.x -= D3DX_PI * 2.0f;
			}
			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].rotDest.x < -D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].rotDest.x += D3DX_PI * 2.0f;
			}

			//
			fDes = g_Player.aModel[nCntPlayerAnim].rotDest.x - g_Player.aModel[nCntPlayerAnim].InitRot.x;

			//差分の調節
			if (fDes > D3DX_PI)
			{
				fDes -= D3DX_PI * 2.0f;
			}
			if (fDes > D3DX_PI)
			{
				fDes += D3DX_PI * 2.0f;
			}

			//現在の向きの設定
			g_Player.aModel[nCntPlayerAnim].InitRot.x += fDes / frac;

			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].InitRot.x > D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].InitRot.x -= D3DX_PI * 2.0f;
			}
			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].InitRot.x < -D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].InitRot.x += D3DX_PI * 2.0f;
			}

			//===================
			// Yの角度
			//===================

			//y目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].rotDest.y > D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].rotDest.y -= D3DX_PI * 2.0f;
			}
			//y目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].rotDest.y < -D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].rotDest.y += D3DX_PI * 2.0f;
			}

			//
			fDes = g_Player.aModel[nCntPlayerAnim].rotDest.y - g_Player.aModel[nCntPlayerAnim].InitRot.y;

			//差分の調節
			if (fDes > D3DX_PI)
			{
				fDes -= D3DX_PI * 2.0f;
			}
			if (fDes > D3DX_PI)
			{
				fDes += D3DX_PI * 2.0f;
			}

			//現在の向きの設定
			g_Player.aModel[nCntPlayerAnim].InitRot.y += fDes / frac;

			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].InitRot.y > D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].InitRot.y -= D3DX_PI * 2.0f;
			}
			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].InitRot.y < -D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].InitRot.y += D3DX_PI * 2.0f;
			}

			//===================
			// Zの角度
			//===================

			//z目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].rotDest.z > D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].rotDest.z -= D3DX_PI * 2.0f;
			}
			//z目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].rotDest.z < -D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].rotDest.z += D3DX_PI * 2.0f;
			}

			//
			fDes = g_Player.aModel[nCntPlayerAnim].rotDest.z - g_Player.aModel[nCntPlayerAnim].InitRot.z;

			//差分の調節
			if (fDes > D3DX_PI)
			{
				fDes -= D3DX_PI * 2.0f;
			}
			if (fDes > D3DX_PI)
			{
				fDes += D3DX_PI * 2.0f;
			}

			//現在の向きの設定
			g_Player.aModel[nCntPlayerAnim].InitRot.z += fDes / frac;

			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].InitRot.z > D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].InitRot.z -= D3DX_PI * 2.0f;
			}
			//x目的の位置の調整
			if (g_Player.aModel[nCntPlayerAnim].InitRot.z < -D3DX_PI)
			{
				g_Player.aModel[nCntPlayerAnim].InitRot.z += D3DX_PI * 2.0f;
			}
		}
	}

	//範囲内に入ったら火を出す
	if (pEnemy->pos.x - 1800 < g_Player.pos.x && pEnemy->pos.x + 1800 > g_Player.pos.x && pEnemy->pos.z - 1800 < g_Player.pos.z && pEnemy->pos.z + 1800 > g_Player.pos.z)
	{
		if (g_Player.bDistance == false)
		{
			g_Player.nCntDistance = 600;
			PlaySound(SOUND_LABEL_NEAR);
		}
		g_Player.bDistance = true;
	}
	else { g_Player.bDistance = false; }

	if (g_Player.bDistance == true)
	{
		SetParticleEffect(D3DXVECTOR3(g_Player.pos.x, 50.0f, g_Player.pos.z), EFFECTTYPE_FIRE, 6, 30, 20, 2);

		g_Player.nCntDistance++;
		if (pEnemy->pos.x - 1500 < g_Player.pos.x && pEnemy->pos.x + 1500 > g_Player.pos.x && pEnemy->pos.z - 1500 < g_Player.pos.z && pEnemy->pos.z + 1500 > g_Player.pos.z)
		{ 
			g_Player.nCntDistance++;
		}
		if (pEnemy->pos.x - 1200 < g_Player.pos.x && pEnemy->pos.x + 1200 > g_Player.pos.x && pEnemy->pos.z - 1200 < g_Player.pos.z && pEnemy->pos.z + 1200 > g_Player.pos.z) { g_Player.nCntDistance++; }
		if (pEnemy->pos.x - 900 < g_Player.pos.x && pEnemy->pos.x + 900 > g_Player.pos.x && pEnemy->pos.z - 900 < g_Player.pos.z && pEnemy->pos.z + 900 > g_Player.pos.z) { g_Player.nCntDistance++; }
		if (pEnemy->pos.x - 600 < g_Player.pos.x && pEnemy->pos.x + 600 > g_Player.pos.x && pEnemy->pos.z - 600 < g_Player.pos.z && pEnemy->pos.z + 600 > g_Player.pos.z) { g_Player.nCntDistance++; }

		if (g_Player.nCntDistance > 80)
		{
			g_Player.nCntDistance = 0;
			//プレイサウンド
			PlaySound(SOUND_LABEL_SE_HART);
			SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 2, 5, 4, 1, ANIMATION_LOOP, EXPLOSIONSTATE_DELETE, D3DX_PI, 0);
			SetExplosion(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT * 0.75f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 2, 5, 4, 0, ANIMATION_LOOP, EXPLOSIONSTATE_DELETE, D3DX_PI, 0);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DMATERIAL9 matDef;						//現在のマテリアルを保存
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ
	D3DXMATRIX mtxParent;						//

	if (g_Player.bUse == true)
	{
		{//プレイヤー
		 // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
			D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
			D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);
		}
		for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
		{
			if (g_Player.aModel[nCntParts].nIdxModelParent < 0)
			{//親モデル
				mtxParent = g_Player.mtxWorldPlayer;
			}
			else
			{//子モデル
				mtxParent = g_Player.aModel[g_Player.aModel[nCntParts].nIdxModelParent].mtxWorldModel;
			}
			{//親モデル
			 // ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Player.aModel[nCntParts].mtxWorldModel);
				// 回転を反映
				D3DXMatrixRotationYawPitchRoll
				(
					&mtxRot,
					g_Player.aModel[nCntParts].InitRot.y,
					g_Player.aModel[nCntParts].InitRot.x,
					g_Player.aModel[nCntParts].InitRot.z
				);
				D3DXMatrixMultiply
				(
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&mtxRot
				);
				// 位置を反映
				D3DXMatrixTranslation
				(
					&mtxTrans,
					g_Player.aModel[nCntParts].InitPos.x,
					g_Player.aModel[nCntParts].InitPos.y,
					g_Player.aModel[nCntParts].InitPos.z
				);
				D3DXMatrixMultiply
				(
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&mtxTrans
				);

				D3DXMatrixMultiply
				(
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&g_Player.aModel[nCntParts].mtxWorldModel,
					&mtxParent
				);
				// ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntParts].mtxWorldModel);

				// 現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_Player.aModel[nCntParts].pBuffMatModel->GetBufferPointer();

				// ポリゴンの描画
				if (g_Player.bUse == true)
				{
					for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntParts].nNumMatModel; nCntMat++)
					{
						// マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

						// テクスチャをNULLにする
						pDevice->SetTexture(0, NULL);

						//pDevice->SetTexture(0, g_Player.nNumMatPlayer);

						// プレイヤー(パーツ)の描画
						g_Player.aModel[nCntParts].pMeshModel->DrawSubset(nCntMat);
					}
				}
				// マテリアルをデフォルトに戻す
				pDevice->SetMaterial(&matDef);
			}
		}
	}
}
//=========================================================================================================================
// プレイヤーの取得処理
//=========================================================================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}
