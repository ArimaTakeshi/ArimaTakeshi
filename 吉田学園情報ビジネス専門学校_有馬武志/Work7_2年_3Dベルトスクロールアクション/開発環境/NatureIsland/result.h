//=============================================================================
//
// リザルト処理 [result.h]
// Author : 有馬 武志 & 荒谷 由朗
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "meshfield.h"
#include "object.h"
#include "model.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
class CSerect;
class CObject;
class CModel;
class CMeshField;
class CPolygon3D;
class CBillBoord;
class CEffect;
class CWall;
class CGround;
class CItem;
class CShadow;

//=====================
// 基本クラス
//=====================
class CResult
{
public:
	CResult();								// コンストラクタ
	~CResult();								// デストラクタ
	HRESULT Init();							// 初期化処理
	void	Uninit(void);					// 終了処理
	void	Update(void);					// 更新処理
	void	Draw(void);						// 描画処理

	void	CreateStage(void);				// ステージ				の 生成を一括管理
	void	CreateObject(void);				// ステージ上			の オブジェクト生成を一括管理
	void	SetTree(D3DXVECTOR3 pos);		// 木					の 生成
private:
	static CSerect		*m_pSerect;			// セレクト				の ポインタ
	static CPlayer		*m_pPlayer;			// プレイヤー			の ポインタ
	static CPolygon3D	*m_pPolygon3D;		// ３Dポリゴン			の ポインタ
	static CModel		*m_pModel;			// モデル				の ポインタ
	static CMeshField	*m_pMeshField;		// メッシュフィールド	の ポインタ
	static CObject		*m_pObject;			// オブジェクト			の ポインタ
	static CBillBoord	*m_pBillBoord;		// ビルボード			の ポインタ
	static CEffect		*m_pEffect;			// エフェクト			の ポインタ
	static CWall		*m_pWall;			// 壁					の ポインタ
	static CGround		*m_pGround;			// 地面					の ポインタ
	static CItem		*m_pItem;			// アイテム				の ポインタ
	static CShadow		*m_pShadow;			//影

	int					m_nCnt;				// カウンター
};
#endif