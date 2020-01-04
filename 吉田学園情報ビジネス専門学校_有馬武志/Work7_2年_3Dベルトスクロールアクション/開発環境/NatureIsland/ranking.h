//=============================================================================
//
// ランキング処理 [ranking.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "input.h"
#include "sound.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "time.h"
#include "scene2D.h"
#include "number.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_RANKING			(5)							//ランキングの数
#define MAX_TIME			(3)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CPlayer;
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

//*********************************************************************
//ランキングクラスの定義
//*********************************************************************
class CRanking : public CScene //基本クラス
{
public:
	CRanking(int nPriority = 7, CScene::OBJTYPE objType = CScene::OBJTYPE_FADE);
	~CRanking();
	static CRanking *Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void	CreateStage(void);				// ステージ				の 生成を一括管理
	void	CreateObject(void);				// ステージ上			の オブジェクト生成を一括管理
	void	SetTree(D3DXVECTOR3 pos);		// 木					の 生成

	//メンバ変数
private:
	CScene2D			*m_pScene2DLogo;				//シーン2Dを使ったロゴ
	LPDIRECT3DTEXTURE9	m_pTexture[1];					//テクスチャへのポインタ
	CScene2D			*m_pScene2DRank[MAX_RANKING];	//シーン2Dを使ったランクのロゴ
	LPDIRECT3DTEXTURE9	m_pTextureRank[MAX_RANKING];	//テクスチャへのポインタ
	CNumber				*m_RankTime[MAX_RANKING][MAX_TIME];	//ランキングの数分ナンバーを用意
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
	static CShadow		*m_pShadow;			// 影

	int					m_nCntTimer;					//フェードまでのカウント
	int					m_nCntCor;						//色変えカウント
};

#endif