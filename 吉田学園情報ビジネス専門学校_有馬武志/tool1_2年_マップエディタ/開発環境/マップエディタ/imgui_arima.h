//=============================================================================
//
// imguiの処理 [imgui.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _IMGUI_ARIMA_H_
#define _IMGUI_ARIMA_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=====================
//  基本クラス
//=====================
class CImgui_Arima
{
public://誰でも扱える
	CImgui_Arima();
	~CImgui_Arima();
	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DeviceObjects(HRESULT hResult, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp);

	//ウィンドウ
	static IMGUI_API void	ShowObjectWindow(bool * p_open = NULL);		//詳細設定オブジェクトウィンドウ
	static IMGUI_API void	ShowFieldWindow(bool * p_open = NULL);		//詳細設定オブジェクトウィンドウ
	static IMGUI_API void	ShowWallWindow(bool * p_open = NULL);		//詳細設定オブジェクトウィンドウ
	
	//モード変更時の値
	static int			GetFillMode(void) { return m_nFillMode; }
	static int			GetPlayerMode(void) { return m_nPlayerMode; }
	static int			GetSetMode(void) { return m_nSetMode; }

	static void			SetFillMode(int nFillMode) { m_nFillMode = nFillMode; }
	static void			SetPlayerMode(int nPlayerMode) { m_nPlayerMode = nPlayerMode; }
	static void			SetSetMode(int nSetMode) { m_nSetMode = nSetMode; }

	//オブジェクトの情報を渡す
	static D3DXVECTOR3	GetObjectPos(void) { return m_ObjectPos; }
	static D3DXVECTOR3	GetObjectRot(void) { return m_ObjectRot; }
	static int			GetObjectType(void) { return m_nObjectType; }
	static int			GetObjectClidked(void) { return m_nObjectClicked; }
	static bool			GetObjectCollition(void) { return m_bObjectCollition; }
	static bool			GetObjectSet(void) { return m_bSetObject; }
	//フィールドの情報を渡す
	static D3DXVECTOR3	GetFieldPos(void) { return m_FieldPos; }
	static D3DXVECTOR4	GetFieldVtx(void) { return m_FieldVtxHeight; }
	static int			GetFieldWD(void) { return m_nFieldWidthDivide; }
	static int			GetFieldHD(void) { return m_nFieldHeightDivide; }
	static int			GetFieldType(void) { return m_nFieldTextureType; }
	static int			GetFieldWL(void) { return m_nFieldWidthLength; }
	static int			GetFieldHL(void) { return m_nFieldHeightLength; }
	static int			GetFieldClidked(void) { return m_nFieldClicked; }
	static bool			GetFeildSet(void) { return m_bSetField; }
	//ウォールの情報を渡す
	static D3DXVECTOR3	GetWallPos(void) { return m_WallPos; }
	static D3DXVECTOR3	GetWallRot(void) { return m_WallRot; }
	static int			GetWallWL(void) { return m_nWallWidthLength; }
	static int			GetWallHL(void) { return m_nWallHeightLength; }
	static int			GetWallType(void) { return m_nWallTextureType; }
	static int			GetWallClicked(void) { return m_nWallClicked; }
	static bool			GetWallSet(void) { return m_bSetWall; }

private:
	//オブジェクトの設定
	static D3DXVECTOR3	m_ObjectPos;			//障害物の位置
	static D3DXVECTOR3	m_ObjectRot;			//障害物の向き
	static int			m_nObjectType;			//障害物の種類
	static int			m_nObjectClicked;		//保存の際に使う
	static bool			m_bObjectCollition;		//障害物の当たり判定
	static bool			m_bSetObject;			//障害物を設置するとき

	//フィールドの設定
	static D3DXVECTOR3	m_FieldPos;				//地面の位置
	static D3DXVECTOR4	m_FieldVtxHeight;		//地面の頂点の高さ
	static int			m_nFieldWidthDivide;	//横の分割数
	static int			m_nFieldHeightDivide;	//縦の分割数
	static int			m_nFieldTextureType;	//種類
	static int			m_nFieldWidthLength;	//横の長さ
	static int			m_nFieldHeightLength;	//縦の高さ
	static int			m_nFieldClicked;		//保存の際に使う
	static bool			m_bSetField;			//地面を設置するとき

	//ウォールの設定
	static D3DXVECTOR3	m_WallPos;				//壁の位置
	static D3DXVECTOR3	m_WallRot;				//壁の向き
	static int			m_nWallWidthLength;		//横の長さ
	static int			m_nWallHeightLength;	//縦の長さ
	static int			m_nWallTextureType;		//種類
	static int			m_nWallClicked;			//保存の際に使う
	static bool			m_bSetWall;				//地面を設置するとき

protected:
	//モード変更時の値
	static int			m_nFillMode;
	static int			m_nPlayerMode;
	static int			m_nSetMode;
};
#endif