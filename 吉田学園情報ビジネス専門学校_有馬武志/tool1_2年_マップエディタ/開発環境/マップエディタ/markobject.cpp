//=============================================================================
//
// 印のオブジェクトの処理 [markobject.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "markobject.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "object.h"
#include "imgui_arima.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MARK_MODEL_NAME_1	"data\\MODEL\\saku000.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_2	"data\\MODEL\\saku001.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_3	"data\\MODEL\\wall000.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_4	"data\\MODEL\\wall001.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_5	"data\\MODEL\\bed.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_6	"data\\MODEL\\peple.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_7	"data\\MODEL\\stair.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_8	"data\\MODEL\\自販機.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_9	"data\\MODEL\\柱.x"					//読み込むテクスチャファイル
#define MARK_MODEL_NAME_10	"data\\MODEL\\grass.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_11	"data\\MODEL\\TreeU.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_12	"data\\MODEL\\TreeD.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_13	"data\\MODEL\\saku003.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_14	"data\\MODEL\\WoodenDesk.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_15	"data\\MODEL\\WoodenChair.x"		//読み込むテクスチャファイル
#define MARK_MODEL_NAME_16	"data\\MODEL\\段ボール.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_17	"data\\MODEL\\Extinguisher.x"		//読み込むテクスチャファイル
#define MARK_MODEL_NAME_18	"data\\MODEL\\locker.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_19	"data\\MODEL\\door.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_20	"data\\MODEL\\SmallWoodenDesk.x"	//読み込むテクスチャファイル
#define MARK_MODEL_NAME_21	"data\\MODEL\\ゴミ箱.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_22	"data\\MODEL\\counter.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_23	"data\\MODEL\\fence.x"				//読み込むテクスチャファイル
#define MARK_MODEL_NAME_24	"data\\MODEL\\security.x"			//読み込むテクスチャファイル
#define MARK_MODEL_NAME_25	"data\\MODEL\\floor.x"			    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_26	"data\\MODEL\\smallfence.x"		    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_27	"data\\MODEL\\ArmoredCar.x"		    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_28	"data\\MODEL\\gate.x"			    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_29	"data\\MODEL\\prison.x"			    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_30	"data\\MODEL\\tower.x"			    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_31	"data\\MODEL\\cone.x"			    //読み込むテクスチャファイル
#define MARK_MODEL_NAME_32	"data\\MODEL\\Generator.x"			  //読み込むテクスチャファイル

#define MODEL_SPEED     (5.0f)
#define MAX_LSHIFTSPEED (0.5f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH CMarkObject::m_pMeshMarkModel[MAX_MARKOBJECT] = {};						//メッシュ情報へのポインタ
LPD3DXBUFFER CMarkObject::m_pBuffMatMarkModel[MAX_MARKOBJECT] = {};					//マテリアルの情報へのポインタ
DWORD CMarkObject::m_nNumMatMarkModel[MAX_MARKOBJECT] = {};							//マテリアルの情報数
LPDIRECT3DTEXTURE9 CMarkObject::m_pMeshMarkTextures[MAX_MARKOBJECT_TEXTURE] = {};	//テクスチャの情報
CObject *CMarkObject::m_pObject = NULL;
int CMarkObject::m_nMarkObjNum = 0;
bool CMarkObject::m_bCraftDelete = false;

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CMarkObject::CMarkObject() : CModel3D(MARKOBJECT_PRIOTITY,CScene::OBJTYPE_MARKOBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 3.0f;
	m_nSelectCollision = 1;
	m_nTexType = 0;
	m_nCraftDeleteNumber = 0;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CMarkObject::~CMarkObject()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMarkObject::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3DモデルのInit
	CModel3D::Init();
	
	//オブジェクトのテクスチャの読み込み
	m_pObject->Load();

	// 位置の初期化
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//位置の代入
	CModel3D::SetPosition(pos);

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CMarkObject::Uninit(void)
{
	//3DモデルのUninit
	CModel3D::Uninit();

	//オブジェクトのテクスチャの破棄
	m_pObject->UnLoad();

}
//=============================================================================
// 更新処理
//=============================================================================
void CMarkObject::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	//3DモデルのUpdate
	CModel3D::Update();
	//位置の初期化
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	//向きの代入
	D3DXVECTOR3 &rot = CModel3D::GetRot();

	//設置モード
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 0)
	{
		//-------------------------------------
		//        Imguiから値を貰う
		//-------------------------------------
		m_move = CImgui_Arima::GetObjectPos();
		rot = CImgui_Arima::GetObjectRot();
		m_nSelectCollision = CImgui_Arima::GetObjectCollition();
		m_nSelectNum = CImgui_Arima::GetObjectType();
		m_bSetObject = CImgui_Arima::GetObjectSet();

		//置いた状態かどうか
		bool bOnOff = false;

		//位置を保存
		if (CImgui_Arima::GetObjectClidked() % 2 == 1)
		{
			CDebugProc::Print("保存！");
			m_pObject->TextSave();
		}

		//オブジェクトの生成
		if (m_bSetObject == true)
		{
			//オブジェクトの生成
			m_pObject = CObject::Create(pos, rot, 0.0f, m_nTexType, m_nSelectNum, CObject::MOVETYPE_NOT, m_nSelectCollision);
			//置いた状態
			bOnOff = true;
			//置いた数の計算
			m_nMarkObjNum += 1;
		}

		switch (m_nSelectNum)
		{
		case 0:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト柵000
			CMarkObject::BindModel(m_pMeshMarkModel[0], m_pBuffMatMarkModel[0], m_nNumMatMarkModel[0], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[0], m_pBuffMatMarkModel[0], m_nNumMatMarkModel[0], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 1:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト柵001
			CMarkObject::BindModel(m_pMeshMarkModel[1], m_pBuffMatMarkModel[1], m_nNumMatMarkModel[1], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[1], m_pBuffMatMarkModel[1], m_nNumMatMarkModel[1], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 2:
			//テクスチャの種類
			m_nTexType = 1;
			// オブジェクト壁000
			CMarkObject::BindModel(m_pMeshMarkModel[2], m_pBuffMatMarkModel[2], m_nNumMatMarkModel[2], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[2], m_pBuffMatMarkModel[2], m_nNumMatMarkModel[2], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 3:
			//テクスチャの種類
			m_nTexType = 2;
			// オブジェクト壁001
			CMarkObject::BindModel(m_pMeshMarkModel[3], m_pBuffMatMarkModel[3], m_nNumMatMarkModel[3], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[3], m_pBuffMatMarkModel[3], m_nNumMatMarkModel[3], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 4:
			//テクスチャの種類
			m_nTexType = 4;
			// オブジェクトベッド
			CMarkObject::BindModel(m_pMeshMarkModel[4], m_pBuffMatMarkModel[4], m_nNumMatMarkModel[4], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[4], m_pBuffMatMarkModel[4], m_nNumMatMarkModel[4], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 5:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト人
			CMarkObject::BindModel(m_pMeshMarkModel[5], m_pBuffMatMarkModel[5], m_nNumMatMarkModel[5], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[5], m_pBuffMatMarkModel[5], m_nNumMatMarkModel[5], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 6:
			//テクスチャの種類
			m_nTexType = 3;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[6], m_pBuffMatMarkModel[6], m_nNumMatMarkModel[6], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[6], m_pBuffMatMarkModel[6], m_nNumMatMarkModel[6], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 7:
			//テクスチャの種類
			m_nTexType = 5;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[7], m_pBuffMatMarkModel[7], m_nNumMatMarkModel[7], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[7], m_pBuffMatMarkModel[7], m_nNumMatMarkModel[7], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 8:
			//テクスチャの種類
			m_nTexType = 3;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[8], m_pBuffMatMarkModel[8], m_nNumMatMarkModel[8], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[8], m_pBuffMatMarkModel[8], m_nNumMatMarkModel[8], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 9:
			//テクスチャの種類
			m_nTexType = 6;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[9], m_pBuffMatMarkModel[9], m_nNumMatMarkModel[9], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[9], m_pBuffMatMarkModel[9], m_nNumMatMarkModel[9], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 10:
			//テクスチャの種類
			m_nTexType = 7;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[10], m_pBuffMatMarkModel[10], m_nNumMatMarkModel[10], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[10], m_pBuffMatMarkModel[10], m_nNumMatMarkModel[10], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 11:
			//テクスチャの種類
			m_nTexType = 8;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[11], m_pBuffMatMarkModel[11], m_nNumMatMarkModel[11], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[11], m_pBuffMatMarkModel[11], m_nNumMatMarkModel[11], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
		case 12:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[12], m_pBuffMatMarkModel[12], m_nNumMatMarkModel[12], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[12], m_pBuffMatMarkModel[12], m_nNumMatMarkModel[12], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 13:
			//テクスチャの種類
			m_nTexType = 9;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[13], m_pBuffMatMarkModel[13], m_nNumMatMarkModel[13], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[13], m_pBuffMatMarkModel[13], m_nNumMatMarkModel[13], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 14:
			//テクスチャの種類
			m_nTexType = 9;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[14], m_pBuffMatMarkModel[14], m_nNumMatMarkModel[14], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[14], m_pBuffMatMarkModel[14], m_nNumMatMarkModel[14], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 15:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[15], m_pBuffMatMarkModel[15], m_nNumMatMarkModel[15], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[15], m_pBuffMatMarkModel[15], m_nNumMatMarkModel[15], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 16:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[16], m_pBuffMatMarkModel[16], m_nNumMatMarkModel[16], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[16], m_pBuffMatMarkModel[16], m_nNumMatMarkModel[16], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 17:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[17], m_pBuffMatMarkModel[17], m_nNumMatMarkModel[17], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[17], m_pBuffMatMarkModel[17], m_nNumMatMarkModel[17], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 18:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[18], m_pBuffMatMarkModel[18], m_nNumMatMarkModel[18], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態
				m_pObject->BindModel(m_pMeshMarkModel[18], m_pBuffMatMarkModel[18], m_nNumMatMarkModel[18], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 19:
			//テクスチャの種類
			m_nTexType = 9;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[19], m_pBuffMatMarkModel[19], m_nNumMatMarkModel[19], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[19], m_pBuffMatMarkModel[19], m_nNumMatMarkModel[19], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 20:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[20], m_pBuffMatMarkModel[20], m_nNumMatMarkModel[20], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[20], m_pBuffMatMarkModel[20], m_nNumMatMarkModel[20], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 21:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[21], m_pBuffMatMarkModel[21], m_nNumMatMarkModel[21], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[21], m_pBuffMatMarkModel[21], m_nNumMatMarkModel[21], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 22:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[22], m_pBuffMatMarkModel[22], m_nNumMatMarkModel[22], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[22], m_pBuffMatMarkModel[22], m_nNumMatMarkModel[22], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 23:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[23], m_pBuffMatMarkModel[23], m_nNumMatMarkModel[23], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[23], m_pBuffMatMarkModel[23], m_nNumMatMarkModel[23], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 24:
			//テクスチャの種類
			m_nTexType = 3;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[24], m_pBuffMatMarkModel[24], m_nNumMatMarkModel[24], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[24], m_pBuffMatMarkModel[24], m_nNumMatMarkModel[24], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 25:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[25], m_pBuffMatMarkModel[25], m_nNumMatMarkModel[25], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[25], m_pBuffMatMarkModel[25], m_nNumMatMarkModel[25], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 26:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[26], m_pBuffMatMarkModel[26], m_nNumMatMarkModel[26], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[26], m_pBuffMatMarkModel[26], m_nNumMatMarkModel[26], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 27:
			//テクスチャの種類
			m_nTexType = 0;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[27], m_pBuffMatMarkModel[27], m_nNumMatMarkModel[27], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[27], m_pBuffMatMarkModel[27], m_nNumMatMarkModel[27], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 28:
			//テクスチャの種類
			m_nTexType = 3;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[28], m_pBuffMatMarkModel[28], m_nNumMatMarkModel[28], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[28], m_pBuffMatMarkModel[28], m_nNumMatMarkModel[28], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 29:
			//テクスチャの種類
			m_nTexType = 3;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[29], m_pBuffMatMarkModel[29], m_nNumMatMarkModel[29], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[29], m_pBuffMatMarkModel[29], m_nNumMatMarkModel[29], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 30:
			//テクスチャの種類
			m_nTexType = 3;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[30], m_pBuffMatMarkModel[30], m_nNumMatMarkModel[30], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[30], m_pBuffMatMarkModel[30], m_nNumMatMarkModel[30], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		case 31:
			//テクスチャの種類
			m_nTexType = 10;
			// オブジェクト階段
			CMarkObject::BindModel(m_pMeshMarkModel[31], m_pBuffMatMarkModel[31], m_nNumMatMarkModel[31], m_pMeshMarkTextures[m_nTexType]);
			if (bOnOff == true)
			{//置いた状態展示会
				m_pObject->BindModel(m_pMeshMarkModel[31], m_pBuffMatMarkModel[31], m_nNumMatMarkModel[31], m_pMeshMarkTextures[m_nTexType]);
				bOnOff = false;
			}
			break;
		}

		// 移動量の代入
		pos = m_move;

		// 各種情報の代入
		CModel3D::SetPosition(pos);
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CMarkObject::Draw(void)
{
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	//マテリアルを透明化する
	for (int nCount = 0; nCount < MAX_MARKOBJECT; nCount++)
	{
		pMat = (D3DXMATERIAL*)m_pBuffMatMarkModel[nCount]->GetBufferPointer();
		pMat->MatD3D.Diffuse.a = 0.4f;
	}

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//位置の初期化
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//設置モード
	int nSetMode = CImgui_Arima::GetSetMode();

	if (nSetMode == 0)
	{
		//3DモデルのDraw
		CModel3D::Draw();
	}

	//マテリアルの値を初期化する
	for (int nCount = 0; nCount < MAX_MARKOBJECT; nCount++)
	{
		pMat = (D3DXMATERIAL*)m_pBuffMatMarkModel[nCount]->GetBufferPointer();
		pMat->MatD3D.Diffuse.a = 1.0f;
	}

}
//===============================================================================
//　クリエイト
//===============================================================================
CMarkObject * CMarkObject::Create(D3DXVECTOR3 pos,int nTexType,int nObjectType)
{
	CMarkObject *pMarkObject = NULL;

	// NULLチェック
	if (pMarkObject == NULL)
	{// メモリの動的確保

		pMarkObject = new CMarkObject;

		if (pMarkObject != NULL)
		{
			// 種類の設定
			pMarkObject->BindModel(m_pMeshMarkModel[nObjectType], m_pBuffMatMarkModel[nObjectType], m_nNumMatMarkModel[nObjectType], m_pMeshMarkTextures[nTexType]);
			// オブジェクトクラスの生成
			pMarkObject->Init();
			// オブジェクトごとの設定用タイプ
			pMarkObject->m_nType = nObjectType;
			// 位置を代入
			pMarkObject->SetPosition(pos);
		}
	}

	return pMarkObject;
}
//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CMarkObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();				

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MARK_MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[0], NULL, &m_nNumMatMarkModel[0], &m_pMeshMarkModel[0]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_2, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[1], NULL, &m_nNumMatMarkModel[1], &m_pMeshMarkModel[1]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_3, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[2], NULL, &m_nNumMatMarkModel[2], &m_pMeshMarkModel[2]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_4, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[3], NULL, &m_nNumMatMarkModel[3], &m_pMeshMarkModel[3]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_5, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[4], NULL, &m_nNumMatMarkModel[4], &m_pMeshMarkModel[4]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_6, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[5], NULL, &m_nNumMatMarkModel[5], &m_pMeshMarkModel[5]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_7, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[6], NULL, &m_nNumMatMarkModel[6], &m_pMeshMarkModel[6]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_8, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[7], NULL, &m_nNumMatMarkModel[7], &m_pMeshMarkModel[7]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_9, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[8], NULL, &m_nNumMatMarkModel[8], &m_pMeshMarkModel[8]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_10, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[9], NULL, &m_nNumMatMarkModel[9], &m_pMeshMarkModel[9]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_11, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[10], NULL, &m_nNumMatMarkModel[10], &m_pMeshMarkModel[10]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_12, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[11], NULL, &m_nNumMatMarkModel[11], &m_pMeshMarkModel[11]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_13, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[12], NULL, &m_nNumMatMarkModel[12], &m_pMeshMarkModel[12]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_14, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[13], NULL, &m_nNumMatMarkModel[13], &m_pMeshMarkModel[13]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_15, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[14], NULL, &m_nNumMatMarkModel[14], &m_pMeshMarkModel[14]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_16, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[15], NULL, &m_nNumMatMarkModel[15], &m_pMeshMarkModel[15]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_17, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[16], NULL, &m_nNumMatMarkModel[16], &m_pMeshMarkModel[16]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_18, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[17], NULL, &m_nNumMatMarkModel[17], &m_pMeshMarkModel[17]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_19, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[18], NULL, &m_nNumMatMarkModel[18], &m_pMeshMarkModel[18]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_20, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[19], NULL, &m_nNumMatMarkModel[19], &m_pMeshMarkModel[19]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_21, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[20], NULL, &m_nNumMatMarkModel[20], &m_pMeshMarkModel[20]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_22, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[21], NULL, &m_nNumMatMarkModel[21], &m_pMeshMarkModel[21]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_23, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[22], NULL, &m_nNumMatMarkModel[22], &m_pMeshMarkModel[22]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_24, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[23], NULL, &m_nNumMatMarkModel[23], &m_pMeshMarkModel[23]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_25, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[24], NULL, &m_nNumMatMarkModel[24], &m_pMeshMarkModel[24]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_26, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[25], NULL, &m_nNumMatMarkModel[25], &m_pMeshMarkModel[25]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_27, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[26], NULL, &m_nNumMatMarkModel[26], &m_pMeshMarkModel[26]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_28, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[27], NULL, &m_nNumMatMarkModel[27], &m_pMeshMarkModel[27]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_29, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[28], NULL, &m_nNumMatMarkModel[28], &m_pMeshMarkModel[28]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_30, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[29], NULL, &m_nNumMatMarkModel[29], &m_pMeshMarkModel[29]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_31, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[30], NULL, &m_nNumMatMarkModel[30], &m_pMeshMarkModel[30]);
	D3DXLoadMeshFromX(MARK_MODEL_NAME_32, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatMarkModel[31], NULL, &m_nNumMatMarkModel[31], &m_pMeshMarkModel[31]);

	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice,"data\\TEXTURE\\iron000.jpg",&m_pMeshMarkTextures[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall002.jpg", &m_pMeshMarkTextures[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall001.jpg", &m_pMeshMarkTextures[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cona.jpg", &m_pMeshMarkTextures[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\si-tu.jpg", &m_pMeshMarkTextures[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bender.jpg", &m_pMeshMarkTextures[5]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\grass.png", &m_pMeshMarkTextures[6]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\葉っぱ.jpg", &m_pMeshMarkTextures[7]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bark-texture.jpg", &m_pMeshMarkTextures[8]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\木の板テクスチャ.jpg", &m_pMeshMarkTextures[9]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gerador3.jpg", &m_pMeshMarkTextures[10]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CMarkObject::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_MARKOBJECT; nCount++)
	{
		// メッシュの開放
		if (m_pMeshMarkModel[nCount] != NULL)
		{
			m_pMeshMarkModel[nCount]->Release();
			m_pMeshMarkModel[nCount] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMatMarkModel[nCount] != NULL)
		{
			m_pBuffMatMarkModel[nCount]->Release();
			m_pBuffMatMarkModel[nCount] = NULL;
		}
	}
	//テクスチャ
	for (int nCntTex = 0; nCntTex < MAX_MARKOBJECT_TEXTURE; nCntTex++)
	{
		if (m_pMeshMarkTextures[nCntTex] != NULL)
		{
			m_pMeshMarkTextures[nCntTex]->Release();
			m_pMeshMarkTextures[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//	オブジェクトの当たり判定
//=============================================================================
void CMarkObject::CollisitionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがメッシュだったら
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				//オブジェクトのあたる判定
				((CObject*)pScene)->CollisionObject(pPos, pPosOld, pMove);

				CDebugProc::Print("あたった\n");
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}