//=============================================================================
//
// メイン処理 [scene.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_DATA		(500)		//出すものの最大数
#define NUM_PRIORITY	(8)			//優先順位の最大数

//=====================
//	   基本クラス
//=====================
class CScene
{
public://誰でも扱える
	typedef enum
	{
		OBJTYPE_NONE = 0,		//使っていない状態
		OBJTYPE_PLAYER,			//プレイヤー
		OBJTYPE_ENEMY,			//敵
		OBJTYPE_BULLET,			//弾
		OBJTYPE_EXPLOSION,		//爆発
		OBJTYPE_BG,				//背景
		OBJTYPE_FRAM,			//枠
		OBJTYPE_GAN,			//武器
		OBJTYPE_DAMAGE,			//ダメージ
		OBJTYPE_SCORE,			//スコア
		OBJTYPE_2DOBJECT,		//オブジェクト
		OBJTYPR_LIFE,			//体力
		OBJTYPE_FADE,			//フェード
		OBJTYPE_MAX,			//最大数
	}OBJTYPE;

	CScene(int nPriority = 3);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void ReleseAll(void);
	static void UpdateAll(void);
	static void DrawAll(void);
	void SetObjType(OBJTYPE ObjType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nPriNumber, int nIdx);
	static void SetUpdatePri(int nUpdatePri);

private://個人でのみ使う
	static CScene *	m_apScene[NUM_PRIORITY][MAX_DATA];
	static int		m_nNumAll;				//敵の総数
	int				m_nID;					//番号
	OBJTYPE			m_ObjType;				//オブジェクトの種類
	int				m_nPriority;			//優先順位の番号
	static int      m_nUpdatePri;

protected:
	void Release(void);
};
#endif