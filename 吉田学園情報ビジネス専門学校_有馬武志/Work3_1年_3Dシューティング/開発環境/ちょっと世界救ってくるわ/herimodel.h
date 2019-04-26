//=============================================================================
//
// モデル処理 [herimodel.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _HERIMODEL_H_
#define _HERIMODEL_H_

#include "main.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
#define MAX_HERITEXT_NAME			(255)							//ファイル名の名前の最大数
#define HERIFILE_NAME				"data\\TEXT\\herimodel.txt"		//読み込むtxtファイルの名前
#define MAX_HERIPARTS				(2)								//パーツ数
#define HERIMODEL_SPEED				(1.0f)							//プレイヤースピード
#define MAX_HERIANIM				(12)							//アニメーション数
#define MAX_HERIKEY					(10)							//キーフレーム数

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	HERIANIM_NEUTRAL = 0,
	HERIANIM_WALK,
	HERIANIM_ATTACK
}Player2Anim;

typedef struct
{
	char			FileName[MAX_HERITEXT_NAME];						//Xファイル名
	LPD3DXMESH		pMeshHeri = NULL;								//メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffMatHeri = NULL;							//マテリアルの情報へのポインタ
	DWORD			nNumMatHeri = 0;								//マテリアルの情報数
	D3DXMATRIX		mtxWorldHeri;									//ワールドマトリックス
	D3DXVECTOR3		posHeri;										//位置
	D3DXVECTOR3		InitHeriPos;										//初期位置
	D3DXVECTOR3		posHeriAnim[MAX_HERIANIM][MAX_HERIKEY];			//アニメーションpos
	D3DXVECTOR3		rotHeri;										//向き
	D3DXVECTOR3		InitHeriRot;										//初期向き
	D3DXVECTOR3		rotAnim[MAX_HERIANIM][MAX_HERIKEY];			//アニメーションrot
	int				nIdxHeriParent = 0;							//親モデルのインデックス　-1が親
}Heri;

typedef struct
{
		
	D3DXMATRIX		mtxWorldPlayer2;								//ワールドマトリックス
	LPD3DXMESH		pMeshPlayer2 = NULL;							//メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffMatPlayer2 = NULL;							//マテリアルの情報へのポインタ
	DWORD			nNumMatPlayer2 = 0;								//マテリアルの情報数
	D3DXVECTOR3		posOld;											//過去の位置
	D3DXVECTOR3		pos;											//位置
	D3DXVECTOR3		move;											//移動
	D3DXVECTOR3		rot;											//向き
	int				nMaxPartsNum;									//パーツの最大数
	Heri			aModel[MAX_HERIPARTS];							//[〇]ここにはパーツ数が入る
	int				nMaxAnimNum;									//アニメーションの最大数
	int				nAnimloop[MAX_HERIANIM];						//ループ
	int				nAnimKey[MAX_HERIANIM];							//キー数
	int				nAnimfram[MAX_HERIANIM][MAX_HERIKEY];			//フレーム数
	Player2Anim		nAnimnuw;										//現在のアニメーション
	int				nAnimKeynuw;									//現在のキー
	bool			bAttack;										//使用しているかどうか
	bool			bUse;											//使用しているかどうか
}Player2;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPlayer2(void);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
Player2 *GetPlayer2(void);

#endif
