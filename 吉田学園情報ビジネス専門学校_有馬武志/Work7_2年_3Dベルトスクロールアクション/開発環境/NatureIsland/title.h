//=============================================================================
//
// メイン処理 [title.h]
// Author : 有馬 武志 & 荒谷 由朗
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "sound.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"

#define TITLEWORD_INITPOS_Y (350.0f)		// タイトル文字の初期高さ
#define SUBTITLE_INITSIZE (1000.0f)			// サブタイトルの初期サイズ
#define ISLAND_STERT (600)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;

//=====================
// 基本クラス
//=====================
class CTitle
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_SKIP,
		TYPE_MAX
	}TYPE;

	CTitle();								// コンストラクタ
	~CTitle();								// デストラクタ
	HRESULT Init();							// 初期化処理
	void	Uninit(void);					// 終了処理
	void	Update(void);					// 更新処理
	void	Draw(void);						// 描画処理
	void	Set(void);						// 最初のCreate

	void	CreateStage(void);				// ステージ				の 生成を一括管理
	void	CreateObject(void);				// ステージ上			の オブジェクト生成を一括管理
	static TYPE GetType(void);				// タイプ				の 取得

private:
	static TYPE			m_pType;			// タイトル画面			の タイプ

	static CPolygon3D	*m_pPolygon3D;		// ３Dポリゴン			の ポインタ
	static CModel		*m_pModel;			// モデル				の ポインタ
	static CMeshField	*m_pMeshField;		// メッシュフィールド	の ポインタ
	static CObject		*m_pObject;			// オブジェクト			の ポインタ
	static CBillBoord	*m_pBillBoord;		// ビルボード			の ポインタ
	static CEffect		*m_pEffect;			// エフェクト			の ポインタ
	static CWall		*m_pWall;			// 壁					の ポインタ
	static CGround		*m_pGround;			// 地面					の ポインタ

	int					m_nCount;			// 落ち葉				の カウンター
	int					m_nCnt;				// テクスチャ			の カウンター
	int					m_nLagCnt;
	int				m_nLeafposY;			// 落ち葉				の 生成座標
	int				m_nLeafsize;			// 落ち葉				の サイズ
	bool			m_bOnOff;
};
#endif