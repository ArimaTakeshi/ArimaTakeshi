//=============================================================================
//
// 対戦処理 [Versus.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _VS_SELECT_H_
#define _VS_SELECT_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "Versus.h"
#include "manager.h"
#include"ScenePlayer.h"
class CFont;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_VS_GAGE		(3)
#define MAX_VS_WEAPON	(2)
#define MAX_VS_READY	(2)
#define MAX_VS_STAGE	(3)

#define MAX_VS_COST		(100)
#define MAX_VS_CFont	(6)
//*****************************************************************************
// クラスの定義 VSセレクト用UI
//*****************************************************************************
class CvsSelectUI : public CScene
{
public:
	typedef enum
	{
		SELECT_TANK0,
		SELECT_TANK1,
		SELECT_ITEM,
		SELECT_BULLET,
		SELECT_LIFE,
		SELECT_DEF,
		SELECT_ATK,
		SELECT_READY,
		SELECT_MAX
	}SELECT;
	CvsSelectUI(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity) 
	{ 
		m_p2DComLevel = NULL;
		m_pTank = NULL;
		for (int nCount = 0; nCount < MAX_VS_WEAPON; nCount++) { m_p2DTank[nCount] = NULL; }
		m_pItem = NULL;
		m_p2DColBullet = NULL;
		for (int nCount = 0; nCount < MAX_VS_GAGE; nCount++) { m_pGage[nCount] = NULL; m_p2DGage[nCount] = NULL; }
		m_p2DReady = NULL;
		m_p2DReadyLogo = NULL;
	};
	~CvsSelectUI() {};

	void Set(int &nID, CvsSelect *pvsSelect);	//セット処理
	void SetSelect(CvsSelect *pvsSelect, int &nID);
	void Select(SELECT &select, bool bChange, CvsSelect *pvsSelect, int &nID);
	void Cursor(SELECT &select);
	bool OverCost(CvsSelect *pvsSelect, int &nID);				//コストがオーバーしているか判定
	void FontOver(D3DXCOLOR col);								//コストがオーバーしていれば文字赤く
	int SumCost(CvsSelect *pvsSelect, int &nID);				//コストの合計値を返す
	int GetCost(SELECT select, CvsSelect *pvsSelect, int &nID);	//指定されたコストを返す　同時に表記の更新
	void Ready(bool bReady);
	void SpinTank(bool bSpin);
	void Uninit(void);	//削除
	void Update(void);	//更新
	void Draw(void);	//描画

private:
	C2D				*m_p2DSelect;				//選択
	
	int				m_nCost;					//コストの数値
	CFont			*m_pCost;					//コストの表記
	CFont			*m_pCostS[MAX_VS_CFont];	//STATUSごとのコストの表記
	C2D				*m_p2DComLevel;				//COMLevel
	CSceneTank		*m_pTank;					//戦車
	C2D				*m_p2DTank[MAX_VS_WEAPON];	//戦車装備
	C2D				*m_pItem;					//アイテム
	C2D				*m_p2DColBullet;			//弾の色
	C2DGage			*m_pGage[MAX_VS_GAGE];		//ゲージ
	C2D				*m_p2DGage[MAX_VS_GAGE];	//アイコン
	C2D				*m_p2DReady;				//準備
	C2D				*m_p2DReadyLogo;			//準備ロゴ
};
//*****************************************************************************
// クラスの定義 ボス用UI
//*****************************************************************************
class CvsSelectStage : public CScene
{
public:
	CvsSelectStage(int nPrioryity = UI_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_nSelect = 0;
		for (int nCount = 0; nCount < MAX_VS_READY; nCount++) { m_pReady[nCount] = NULL; }
		for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++) { m_pStage[nCount] = NULL; }
	};
	~CvsSelectStage() {};

	void Uninit(void);	//削除
	void Update(void);	//更新
	void Draw(void);	//描画

	void Set(void);	//セット処理
	void ChangeReady(bool bDraw);
	void ChangeStage(bool bDraw);
	void UpdateStage(void);

	C2DPolygon	*&GetpStage(int nID) { return m_pStage[nID]; }
	int  &GetnSelect(void) { return m_nSelect; };
	
private:
	int			m_nSelect;
	C2D			*m_pStageLogo;
	C2DPolygon	*m_pReady[MAX_VS_READY];
	C2DPolygon	*m_pStage[MAX_VS_STAGE];
};
//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CvsSelect
{
public:
	CvsSelect() { for (int nCount = 0; nCount < MAX_PLAYER; nCount++) { m_pUI[nCount] = NULL; } };
	~CvsSelect() {};

	HRESULT Init(void);
	void	Update(void);
	void	Uninit(void);
	void	WeaponSelect(int &nCount);
	bool	StageSelect(int &nCount);
	void	Save(void);
	void	Load(void);
	static void LoadVS(int &nStage);

	CSceneModel::TEXTURE	&GetTex(int nID, int nCount) { return m_tex[nID][nCount]; }
	ITEM::TYPE	&GetItem(int nID)	{ return m_item[nID]; }
	float		&GetfLife(int nID)	{ return m_fLife[nID]; }
	float		&GetfAtk(int nID)	{ return m_fAtk[nID]; }
	float		&GetfDef(int nID)	{ return m_fDef[nID]; }
	int			&GetnUV(int nID)	{ return m_nUV[nID]; }
	int			&GetnComLevel(int nID) { return m_nComLevel[nID]; }

	float		&GetfMaxGage(void) { return m_fMaxGage; }

private://*****************************************************************************
	//変数宣言//***********************************************************************
	CvsSelectStage	*m_pStage;
	CvsSelectUI		*m_pUI[MAX_PLAYER];
	float			m_fMaxGage;

	//選択系//***********************************************************************
	CvsSelectUI::SELECT	m_Select[MAX_PLAYER];	//プレイヤーごとの選択用
	bool m_bReady[MAX_PLAYER];	//準備判定
	bool m_bStage;				//ステージ選択画面
	bool m_bGo;					//選択が終了したかどうか

	CSceneModel::TEXTURE m_tex[MAX_PLAYER][2];	//テクスチャ　車体　砲塔
	ITEM::TYPE	m_item[MAX_PLAYER];						//アイテム
	float		m_fLife[MAX_PLAYER];					//体力
	float		m_fAtk[MAX_PLAYER];						//攻撃力
	float		m_fDef[MAX_PLAYER];						//防御力
	int			m_nUV[MAX_PLAYER];						//弾の色
	int			m_nComLevel[MAX_PLAYER];						//COUの場合の強さ
};

#endif
