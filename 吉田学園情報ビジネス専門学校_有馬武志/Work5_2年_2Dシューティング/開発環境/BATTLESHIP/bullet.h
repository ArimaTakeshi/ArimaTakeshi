//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2Dの派生クラス
//=====================
class CBullet : public CScene2D
{
public://誰でも扱える
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,		//プレイヤー
		BULLETTYPE_ENEMY,			//敵
		BULLETTYPE_MAX				//最大数
	}BULLETTYPE;

	typedef enum
	{
		GAN_CANNON = 0,				//大砲弾
		GAN_SKYCANNON,				//対空砲弾
		GAN_TORPEDO,				//魚雷弾
		GAN_MAX						//最大数
	}GANTYPE_BULLET;

	typedef enum
	{
		PLAYER_SHIP = 0,			//プレイヤー戦艦
		ENEMY_SHIP,					//敵戦艦
		ENEMY_DIGHTER,				//敵戦闘機
		ENEMY_SUBMARINE,			//敵潜水艦
		ENEMT_CARRIER,				//敵空母
	}PETYPE;

	CBullet();
	~CBullet();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet *Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size, BULLETTYPE type, GANTYPE_BULLET bullettype, PETYPE petype,int nBulletType);
	GANTYPE_BULLET GetBulletType(void) { return m_gantype; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	D3DXVECTOR3				  m_move;					//移動量
	int						  m_nType;					//種類
	int						  m_nDamage;				//ダメージ
	int						  m_nBulletType;			//銃の弾の種類
	D3DXVECTOR2				  m_Size;					//サイズ
	PETYPE					  m_Petype;					//敵が自分か
	GANTYPE_BULLET            m_gantype;				//弾の種類
};

#endif