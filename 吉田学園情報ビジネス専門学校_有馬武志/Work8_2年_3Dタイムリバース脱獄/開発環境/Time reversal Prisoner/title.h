//=============================================================================
//
// メイン処理 [title.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "sound.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "enemy.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MAP_NUM		(1000)
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
class CShadow;
class CSpotLight;
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

	void	CreateStage(void);				// ステージの生成を一括管理
	void	CreateObject(void);				// ステージ上のオブジェクト生成を一括管理
	static TYPE GetType(void);				// タイプの取得

	//ファイルを読み込む
	void TextLoad(int nLoadNumber);
	void MeshTextLoad(int nLoadNumber);
	void WallTextLoad(int nLoadNumber);
	char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	char *GetLineTop(char *pStr);				//行の先頭を取得
	int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

private:
	//テキストの値を管理する場所
	typedef struct
	{
		int					m_nType;			// 種類
		int					m_nTexType;			// テクスチャの種類
		int					m_nCollision;		// 当たり判定のONOFF
		D3DXVECTOR3			m_pos;				// 位置
		D3DXVECTOR3			m_rot;				// 回転
	}Map;

	//テキストの値を管理する場所
	typedef struct
	{
		int								m_nTexType;						// テクスチャの種類
		int								m_nWidthDivide;					// 横の分割数を入れる
		int								m_nDepthDivide;					// 奥の分割数を入れる
		float							m_fWidthLength;					// 横の長さ
		float							m_fDepthLength;					// 奥の長さ
		float							m_fVtxHeight_No0;				// 頂点番号0を操作
		float							m_fVtxHeight_No1;				// 頂点番号1を操作
		float							m_fVtxHeight_No2;				// 頂点番号2を操作
		float							m_fVtxHeight_No3;				// 頂点番号3を操作
		D3DXVECTOR3						m_pos;							// 位置
	}Mesh;

	//テキストの値を管理する場所
	typedef struct
	{
		D3DXVECTOR3			m_pos;				// 位置
		D3DXVECTOR3			m_rot;				// 回転
		float				m_fWidthDivide;		// 横幅
		float				m_fHightDivide;		// 縦幅
		int					m_nTexType;			// テクスチャの種類
	}Wall;

	static TYPE			m_pType;			// タイトル画面の タイプ

	static CPolygon3D	*m_pPolygon3D;		// ３Dポリゴンの ポインタ
	static CModel		*m_pModel;			// モデルの ポインタ
	static CMeshField	*m_pMeshField;		// メッシュフィールドの ポインタ
	static CObject		*m_pObject;			// オブジェクトの ポインタ
	static CBillBoord	*m_pBillBoord;		// ビルボードの ポインタ
	static CEffect		*m_pEffect;			// エフェクトの ポインタ
	static CWall		*m_pWall;			// 壁の ポインタ
	static CGround		*m_pGround;			// 地面の ポインタ
	static CPlayer		*m_pPlayer;			//プレイヤーのポインタ
	static CEnemy		*m_pEnemy;			//敵のポインタ
	static CShadow		*m_pShadow;			//影のポインタ
	static CSpotLight	*m_pSpotLight;		//スポットライトのポインタ

	int					m_nCount;			// 落ち葉の カウンター
	int					m_nCnt;				// テクスチャの カウンター
	int					m_nLagCnt;
	int					m_nLeafposY;		// 落ち葉の 生成座標
	int					m_nLeafsize;		// 落ち葉の サイズ
	bool				m_bOnOff;

	int m_nSetObjectNum;					//オブジェクトを置いた数
	int m_nSetMeshFieldNum;					//メッシュフィールドを置いた数
	int	m_nSetWallNum;						//壁の置いた数
	Map m_Map[MAX_MAP_NUM];					//設置するオブジェクトの構造体
	Mesh m_Mesh[MAX_MAP_NUM];				//設置するメッシュフィールドの構造体
	Wall m_aWall[MAX_MAP_NUM];				//設置する壁の構造体
};
#endif