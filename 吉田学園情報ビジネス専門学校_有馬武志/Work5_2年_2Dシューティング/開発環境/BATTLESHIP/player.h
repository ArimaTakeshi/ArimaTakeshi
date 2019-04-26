//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_TYPE	(10)

//=====================
//  CScene2Dの派生クラス
//=====================
class CPlayer : public CScene2D
{
public://誰でも扱える
	typedef enum
	{
		PLAYERSTATE_NORMAL = 0,		//通常状態
		PLAYERSTATE_DAMAGE,			//ダメージ状態
		PLAYERSTATE_DEAHT,			//死亡状態	
		PLAYERSTATE_MAX				//状態の最大数
	}PLAYERSTATE;

	CPlayer();
	~CPlayer();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, float fLife);
	D3DXVECTOR2 *GetSize(void) { return &m_Size; }
	void SetLife(float life) { m_fLife = life; }
	void HitPlayer(float fDamage);
	static float GetLife(void) { return m_fLife; }
	static float GetMaxLife(void) { return m_fMaxLife; }

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	static float			  m_fLife;					//体力
	int						  m_nCounterState;			//状態管理のカウンター
	PLAYERSTATE				  m_state;					//プレイヤーの状態
	int						  m_nCount;					//カウンター
	D3DXVECTOR2				  m_Size;					//サイズ
	static float			  m_fMaxLife;				//最大の体力
	float					  m_fLength;				//距離
	float					  m_fAngle;					//角度
	D3DXVECTOR3			      m_rot;					//向き

};
#endif