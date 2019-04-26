//=============================================================================
//
// アイテム処理 [item.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "model3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ITEM_TYPE		(2)
#define MAX_TEXTURE_TYPE	(1)

//=====================
//  CSceneの派生クラス
//=====================
class CItem : public CModel3D
{
public://誰でも扱える
	typedef enum
	{
		ITEMTYPE_APPLE = 0,		//リンゴ
		ITEMTYPE_BANANA,		//バナナ
		ITEMTYPE_MAX			//状態の総数
	}ITEMTYPE;					//アイテムの種類の列挙型

	typedef struct
	{
		int nType;				//アイテムの種類 int型
		ITEMTYPE ItemType;		//アイテムの種類
	} ITEM;						//アイテムの構造体

	CItem();
	~CItem();
	static HRESULT Load(void);								//オブジェクト読み込み
	static void UnLoad(void);								//オブジェクトのマテリアル情報破棄
	HRESULT Init(void);										//初期化
	void Uninit(void);										//終了
	void Update(void);										//更新
	void Draw(void);										//描画
	static CItem *Create(D3DXVECTOR3 pos, int type);		//オブジェクト生成

	ITEM *GetItem(void);
	bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);	//当たり判定

private://個人でのみ使う
		static LPD3DXMESH			m_pMesh[MAX_ITEM_TYPE];				//メッシュ情報へのポインタ
		static LPD3DXBUFFER			m_pBuffMat[MAX_ITEM_TYPE];			//マテリアル情報へのポインタ
		static DWORD				m_nNumMat[MAX_ITEM_TYPE];			//マテリアルの情報数
		static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ITEM_TYPE];			//テクスチャへのポインタ

		D3DXVECTOR3	 m_pos;						//位置
		D3DXVECTOR3	 m_posold;					//前回の位置
		D3DXVECTOR3	 m_move;					//移動量
		D3DXVECTOR3	 m_rot;						//向き
		ITEM		 m_aItem;					//アイテム構造体の変数
		int			 m_nMoveTimer;				//移動時間

};

#endif