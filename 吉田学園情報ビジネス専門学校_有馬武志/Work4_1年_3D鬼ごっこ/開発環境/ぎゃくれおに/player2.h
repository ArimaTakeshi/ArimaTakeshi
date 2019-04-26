//=============================================================================
//
// モデル処理 [player2.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _PLAYERL2_H_
#define _PLAYERL2_H_

#include "main.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
#define MAX_TEXT_NAME			(255)							//ファイル名の名前の最大数
#define FILE_NAME_PLAYER2		"data\\TEXT\\Player2.txt"		//読み込むtxtファイルの名前
#define MAX_PARTS				(15)							//パーツ数
#define MODEL_SPEED				(1.0f)							//プレイヤースピード
#define MAX_PLAYER2ANIM			(8)								//アニメーション数
#define MAX_PLAYER2KEY			(8)								//キーフレーム数

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef enum
{
	PLAYER2ANIM_NEUTRAL = 0,
	PLAYER2ANIM_WALK,
	PLAYER2ANIM_ATTACK,
	PLAYER2_MAX
}Player2Anim;

typedef struct
{
	char			FileName[MAX_TEXT_NAME];						//Xファイル名
	LPD3DXMESH		pMeshModelPlayer2 = NULL;						//メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffMatModelPlayer2 = NULL;					//マテリアルの情報へのポインタ
	DWORD			nNumMatModelPlayer2 = 0;						//マテリアルの情報数
	D3DXMATRIX		mtxWorldModelPlayer2;							//ワールドマトリックス
	D3DXVECTOR3		posModelPlayer2;								//位置
	D3DXVECTOR3		InitPos;										//初期位置
	D3DXVECTOR3		posAnim[MAX_PLAYER2ANIM][MAX_PLAYER2KEY];		//アニメーションpos
	D3DXVECTOR3		rotModelPlayer2;								//向き
	D3DXVECTOR3		InitRot;										//初期向き
	D3DXVECTOR3		rotAnim[MAX_PLAYER2ANIM][MAX_PLAYER2KEY];		//アニメーションrot
	D3DXVECTOR3		rotDest;										//目的の位置
	int				nIdxModelPlayer2Parent = 0;						//親モデルのインデックス　-1が親
}ModelPlayer2;

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
	ModelPlayer2	aModelPlayer2[MAX_PARTS];						//[〇]ここにはパーツ数が入る
	int				nMaxAnimNum;									//アニメーションの最大数
	int				nAnimloop[MAX_PLAYER2ANIM];						//ループ
	int				nAnimKey[MAX_PLAYER2ANIM];						//キー数
	int				nAnimfram[MAX_PLAYER2ANIM][MAX_PLAYER2KEY];		//フレーム数
	Player2Anim		nAnimnow;										//現在のアニメーション
	int				nAnimKeynow;									//現在のキー
	bool			bAttack;										//使用しているかどうか
	bool			bUse;											//使用しているかどうか
	bool			bLand;											//捕まっているかどうか
	int				nIdxShadow2;									//どの影を使っているか
	int				nCntPlayer2;
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
