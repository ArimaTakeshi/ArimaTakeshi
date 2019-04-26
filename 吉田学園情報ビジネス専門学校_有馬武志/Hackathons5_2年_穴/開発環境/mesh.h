//=============================================================================
//
// メッシュ処理 [mesh.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MESH_H_
#define _MESH_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// マクロの定義
//*****************************************************************************
#define WALL_PLUS					(2.0f)		//壁の判定のプラス値
#define MESH_PRIORITY				(1)			//メッシュの優先順位
#define ORBIT_PRIORITY				(3)			//メッシュの優先順位

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMesh : public CScene
{
public:
	typedef enum
	{
		TYPE_FIELD,		//地面
		TYPE_WALL,		//壁
		TYPE_CEILING,	//天井
		TYPE_ORBIT,	//オービット
		TYPE_MAX
	}TYPE;
	CMesh(int nPrioryity = 0) : CScene::CScene(nPrioryity) {};
	~CMesh() {};

	void	Set(TYPE type, D3DXVECTOR3 pos, int nVertical, int nCorss, bool bMesh);	//セット処理
	void	SetNor(void);	//法線のセット処理

	void	SetWall(D3DXVECTOR3 *vtx);							//壁セット処理
	bool	SetField(int *nDig, int nMaxDig, float *fHeight, bool bRoom);	//床セット処理
	void	UpField(int *nMap, float fHeight);	//床プラス処理
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);

	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }
	CScene::DRAW_TYPE &GetDrawType(void) { return m_DrawType; }

	static void MeshCollisionCeiling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &length);
	static bool MeshCollisionField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, bool &bJump);
	static void MeshCollisionWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static float FieldCollision(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3 WKpos, D3DXVECTOR3& pos, D3DXVECTOR3 &FNor);
	static int WallCollision(D3DXVECTOR3 Wall0, D3DXVECTOR3 Wall1, D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection);
	static bool FieldCheck(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3& pos);
	static int AngleCheck(float fAngle0, float fAngle1);
	void MeshCeling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLength);
	bool MeshField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &FNor, float& fLength, bool &bJump);
	void MeshWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection);

	int &GetnCross(void) { return m_nCross; }
	int &GetnVertical(void) { return m_nVertical; }
protected://*****************************************************************************
	LPDIRECT3DVERTEXBUFFER9 &GetVtxBuff(void) { return m_pVtxBuff; }
private://*****************************************************************************
	void WallPlus(D3DXVECTOR3& pos0, D3DXVECTOR3 &pos1, float& fLengthX, float& fLengthZ);
	void PlusNor(VERTEX_3D *pVtx, VERTEX_3D *pVtxL, VERTEX_3D *pVtxR);	//法線のセット処理

		//変数宣言//***********************************************************************
	CScene::DRAW_TYPE		m_DrawType;		// 描画する方法(加算合成など)
	TYPE					m_Type;			//タイプ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;		//インデックスバッファのポインタ
	LPDIRECT3DTEXTURE9		m_pTex;		//画像
	D3DXVECTOR3				m_pos;			//位置
	D3DXVECTOR3				m_rot;			//向き
	int						m_nVertical;	//縦の分割数
	int						m_nCross;		//横の分割数
	int						m_nNumVertex;	//頂点数
	int						m_nNumIdx;		//インデックス数
	int						m_nNumPolygon;	//ポリゴン数
	bool					m_bMesh;		//張っている面が内側か外側か(左回りか右回りか)
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CMeshOrbit : public CScene
{
public:
	CMeshOrbit(int nPrioryity = ORBIT_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_pmtxWorld = NULL;
		m_bDelete = NULL;
	};
	~CMeshOrbit() {};

	void	Set(D3DXMATRIX &mtxWorld, D3DXVECTOR3 length0, D3DXVECTOR3 length1, bool &bDelete, D3DXCOLOR col, CScene::TEXTURE tex);
	void	Update(void);
	void	Draw(void);
	void	ReSet(void);
	static void	ReSetAll(void);
	static void	Delete(void);
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }
	CScene::DRAW_TYPE &GetDrawType(void) { return m_DrawType; }

private://*****************************************************************************
	void	SetVtx(bool bAll);		//最新の頂点を計算して代入
	void	SwapVtx(void);		//頂点の入れ替え
	//変数宣言//***********************************************************************
	CScene::DRAW_TYPE		m_DrawType;		// 描画する方法(加算合成など)
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファ
	LPDIRECT3DTEXTURE9		m_pTex;		//画像
	int						m_nNumPolygon;	//ポリゴン数

	D3DXMATRIX		*m_pmtxWorld;	//親のワールドマトリックス
	D3DXMATRIX		m_mtxWorld[2];	//ワールドマトリックス
	D3DXVECTOR3		m_posold;		//前の位置
	D3DXCOLOR		m_col;			//色
	int				m_nCross;		//横の分割数
	int				m_nReset;		//リセットされた場合のカウント用
	float			m_fPlusCol;		//薄れゆく色
	float			m_fUV;			//薄れゆく色
	float			m_fEnd;			//破棄までの経過時間
	bool			*m_bDelete;		//消える判定
};
#endif