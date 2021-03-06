//=============================================================================
//
// オブジェクトの処理 [object.cpp]
// Author : 有馬武志
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "object.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "shadow.h"
#include "effectmgr.h"
#include "loadEffect.h"
#include "tutorial.h"
#include "objbillboad.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define MODEL_NAME_1	"data\\MODEL\\壊れるもの\\自販機.x"			// 読み込むモデルファイル
#define MODEL_NAME_2	"data\\MODEL\\壊れるもの\\grass.x"			// 読み込むモデルファイル
#define MODEL_NAME_3	"data\\MODEL\\壊れないもの\\TreeU.x"		// 読み込むモデルファイル
#define MODEL_NAME_4	"data\\MODEL\\壊れないもの\\TreeD.x"		// 読み込むモデルファイル
#define MODEL_NAME_5	"data\\MODEL\\飛ばせるもの\\段ボール.x"		// 読み込むモデルファイル
#define MODEL_NAME_6	"data\\MODEL\\飛ばせるもの\\cone.x"			// 読み込むモデルファイル
#define MODEL_NAME_7	"data\\MODEL\\壊れないもの\\ビル200.x"		// 読み込むモデルファイル
#define MODEL_NAME_8	"data\\MODEL\\壊れないもの\\ビル400.x"		// 読み込むモデルファイル
#define MODEL_NAME_9	"data\\MODEL\\壊れないもの\\ビル600.x"		// 読み込むモデルファイル
#define MODEL_NAME_10	"data\\MODEL\\壊れるもの\\街灯.x"			// 読み込むモデルファイル
#define MODEL_NAME_11	"data\\MODEL\\壊れるもの\\信号機2.x"		// 読み込むモデルファイル
#define MODEL_NAME_12	"data\\MODEL\\壊れるもの\\信号機3.x"		// 読み込むモデルファイル
#define MODEL_NAME_13	"data\\MODEL\\飛ばせるもの\\ベンチ.x"		// 読み込むモデルファイル
#define MODEL_NAME_14	"data\\MODEL\\壊れないもの\\テレビ塔.x"		// 読み込むモデルファイル
#define MODEL_NAME_15	"data\\MODEL\\壊れるもの\\tree.x"			// 読み込むモデルファイル
#define MODEL_NAME_16	"data\\MODEL\\壊れるもの\\公衆電話.x"		// 読み込むモデルファイル
#define MODEL_NAME_17	"data\\MODEL\\壊れるもの\\草壇.x"			// 読み込むモデルファイル
#define MODEL_NAME_18	"data\\MODEL\\壊れないもの\\花壇.x"			// 読み込むモデルファイル
#define MODEL_NAME_19	"data\\MODEL\\壊れないもの\\狸小路屋根.x"	// 読み込むモデルファイル
#define MODEL_NAME_20	"data\\MODEL\\当たり判定用\\box.x"			// 読み込むモデルファイル
#define MODEL_NAME_21	"data\\MODEL\\飛ばせるもの\\看板.x"			// 読み込むモデルファイル
#define MODEL_NAME_22	"data\\MODEL\\飛ばせるもの\\ビールケース.x"	// 読み込むモデルファイル
#define MODEL_NAME_23	"data\\MODEL\\壊れないもの\\時計台.x"		// 読み込むモデルファイル
#define MODEL_NAME_24	"data\\MODEL\\壊れないもの\\赤レンガ.x"		// 読み込むモデルファイル
#define MODEL_NAME_25	"data\\MODEL\\壊れないもの\\コーン.x"		//読み込むモデルファイル
#define MODEL_NAME_26	"data\\MODEL\\壊れないもの\\札幌駅.x"		//読み込むモデルファイル
#define MODEL_NAME_27	"data\\MODEL\\壊れないもの\\エスタ.x"		//読み込むモデルファイル
#define MODEL_NAME_28	"data\\MODEL\\壊れないもの\\大丸.x"			//読み込むモデルファイル
#define MODEL_NAME_29	"data\\MODEL\\壊れないもの\\アピアドーム.x"	//読み込むテクスチャファイル
#define MODEL_NAME_30	"data\\MODEL\\壊れないもの\\JRタワー.x"		//読み込むテクスチャファイル
#define MODEL_NAME_31	"data\\MODEL\\壊れないもの\\噴水.x"			//読み込むテクスチャファイル
#define MODEL_NAME_32	"data\\MODEL\\壊れるもの\\指示看板.x"		//読み込むテクスチャファイル
#define MODEL_NAME_33	"data\\MODEL\\飛ばせるもの\\柵.x"			//読み込むテクスチャファイル
#define MODEL_NAME_34	"data\\MODEL\\壊れるもの\\fire_hydrant.x"	//読み込むテクスチャファイル
#define MODEL_NAME_35	"data\\MODEL\\壊れないもの\\観覧車.x"		//読み込むテクスチャファイル
#define MODEL_NAME_36	"data\\MODEL\\壊れないもの\\タピオカカー.x"	//読み込むテクスチャファイル
#define MODEL_NAME_37	"data\\MODEL\\壊れないもの\\北大病院.x"		//読み込むテクスチャファイル
#define MODEL_NAME_38	"data\\MODEL\\壊れないもの\\LCDpanel.x"		//読み込むテクスチャファイル

#define TEXTURE_NAME_1	"data\\TEXTURE\\modeltex\\bender.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_2	"data\\TEXTURE\\modeltex\\grass.png"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_3	"data\\TEXTURE\\modeltex\\葉っぱ.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_4	"data\\TEXTURE\\modeltex\\tree.jpg"			// 読み込むテクスチャファイル
#define TEXTURE_NAME_5	"data\\TEXTURE\\modeltex\\ビル200正面.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_6	"data\\TEXTURE\\modeltex\\ビル200側面.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_7	"data\\TEXTURE\\modeltex\\ビル400正面.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_8	"data\\TEXTURE\\modeltex\\ビル400側面.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_9	"data\\TEXTURE\\modeltex\\ビル600正面.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_10	"data\\TEXTURE\\modeltex\\ビル600側面.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_11	"data\\TEXTURE\\modeltex\\街灯.jpg"			// 読み込むテクスチャファイル
#define TEXTURE_NAME_12	"data\\TEXTURE\\modeltex\\信号機2.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_13	"data\\TEXTURE\\modeltex\\信号機3.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_14	"data\\TEXTURE\\modeltex\\ベンチ.png"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_15	"data\\TEXTURE\\modeltex\\テレビ塔.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_16	"data\\TEXTURE\\modeltex\\leaf.png"			// 読み込むテクスチャファイル
#define TEXTURE_NAME_17 "data\\TEXTURE\\modeltex\\公衆電話.png"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_18 "data\\TEXTURE\\modeltex\\草壇.jpg"			// 読み込むテクスチャファイル
#define TEXTURE_NAME_19 "data\\TEXTURE\\modeltex\\花壇.jpg"			// 読み込むテクスチャファイル
#define TEXTURE_NAME_20 "data\\TEXTURE\\modeltex\\狸小路.png"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_21 "data\\TEXTURE\\modeltex\\看板.jpg"			// 読み込むテクスチャファイル
#define TEXTURE_NAME_22 "data\\TEXTURE\\modeltex\\ビールケース.png"	// 読み込むテクスチャファイル
#define TEXTURE_NAME_23 "data\\TEXTURE\\modeltex\\時計台.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_24 "data\\TEXTURE\\modeltex\\赤レンガ.jpg"		// 読み込むテクスチャファイル
#define TEXTURE_NAME_25 "data\\TEXTURE\\modeltex\\コーン.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_26 "data\\TEXTURE\\modeltex\\札幌駅.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_27 "data\\TEXTURE\\modeltex\\エスタ.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_28 "data\\TEXTURE\\modeltex\\大丸.jpg"			//読み込むテクスチャファイル
#define TEXTURE_NAME_29 "data\\TEXTURE\\modeltex\\アピアドーム.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_30 "data\\TEXTURE\\modeltex\\JRタワー.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_31 "data\\TEXTURE\\modeltex\\噴水.jpg"			//読み込むテクスチャファイル
#define TEXTURE_NAME_32 "data\\TEXTURE\\modeltex\\指示看板.jpg"		//読み込むテクスチャファイル
#define TEXTURE_NAME_33 "data\\TEXTURE\\modeltex\\柵.png"			//読み込むテクスチャファイル
#define TEXTURE_NAME_34 "data\\TEXTURE\\modeltex\\.jpg"				//読み込むテクスチャファイル
#define TEXTURE_NAME_35 "data\\TEXTURE\\modeltex\\観覧車2.png"		//読み込むテクスチャファイル
#define TEXTURE_NAME_36 "data\\TEXTURE\\modeltex\\セーコーマートビル.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_37 "data\\TEXTURE\\modeltex\\ローソンビル.jpg"			//読み込むテクスチャファイル
#define TEXTURE_NAME_38 "data\\TEXTURE\\modeltex\\セブンイレブンビル.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_39 "data\\TEXTURE\\modeltex\\ファミリーマートビル.jpg"	//読み込むテクスチャファイル
#define TEXTURE_NAME_40 "data\\TEXTURE\\modeltex\\タピオカカー.png"	//読み込むテクスチャファイル
#define TEXTURE_NAME_41 "data\\TEXTURE\\modeltex\\北大病院.jpg"		//読み込むテクスチャファイル

#define MODEL_SPEED				(5.0f)
#define PLAYER_DEPTH			(50)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT			(100.0f)	// プレイヤーの背の高さ
#define OBJCT_ANGLE_REVISION	(0.2f)		// 角度補正
#define EFFECT_HIGHT			(250.0f)	// エミッターの高さ
#define FOUNTAIN_UP				(20.0f)		// 噴水の上昇させる値

//更新範囲
#define FOUNTAIN_LENGTH			(15000)		//噴水の更新範囲
#define LEAF_LENGTH				(10500)		//葉の更新処理
#define WOOD_LENGTH				(8000)		//木をビルボードに入れ替える距離
#define FLOWER_LENGTH			(5500)		//花壇の描画範囲

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数:
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPD3DXMESH CObject::m_pMeshModel[MAX_OBJECT] = {};						//メッシュ情報へのポインタ
LPD3DXBUFFER CObject::m_pBuffMatModel[MAX_OBJECT] = {};					//マテリアルの情報へのポインタ
DWORD CObject::m_nNumMatModel[MAX_OBJECT] = {};							//マテリアルの情報数
LPDIRECT3DTEXTURE9 CObject::m_pMeshTextures[MAX_OBJECT_TEXTURE] = {};
D3DXVECTOR3 CObject::m_LoadVtxMaxModel[MAX_OBJECT] = {};
D3DXVECTOR3 CObject::m_LoadVtxMinModel[MAX_OBJECT] = {};

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CObject::CObject() : CModel3D(OBJECT_PRIOTITY, CScene::OBJTYPE_OBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStageCount = 0;
	m_bStageNext = false;
	m_pLoadEffect = NULL;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CObject::~CObject(){}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject::Init(void)
{
	//アップデートを通さないオブジェクトのタイプ
	int anUpdateType[UPDATE_TYPE_NUM] = { TYPE_TREE00, TYPE_TREE01, TYPE_BILL00, TYPE_BILL01,
										  TYPE_BILL02, TYPE_TVBILL, TYPE_TANUKI,
										  TYPE_OCLOCK, TYPE_REDBILL, TYPE_CORN2,
										  TYPE_STATION, TYPE_ESTA, TYPE_DAIMAL, TYPE_APIA,
										  TYPE_TOWER, TYPE_FOUNTAIN, TYPE_FERRISWGEEL, TYPE_TAPIOCA, TYPE_HOSPITAL, TYPE_LCDPANEL };

	//小さいオブジェクトのタイプ
	int anSmallObjType[SMALL_OBJ_NUM] = { TYPE_DRINKMACHINE, TYPE_GRASS, TYPE_CARDBORD, TYPE_CORN,
										  TYPE_BENCH, TYPE_PHONEBOX, TYPE_LEAF, TYPE_SIGNBOARD, TYPE_BEERBOX, TYPE_FENCE};

	//高いオブジェクトのタイプ
	int anHightObjType[HIGHT_OBJ_NUM] = { TYPE_STREETLIGHT, TYPE_TRAFFICLIGHT00, TYPE_TRAFFICLIGHT01, TYPE_ROAD};

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3DモデルのInit
	CModel3D::Init();

	// 位置の初期化
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//テクスチャ番号の初期化
	m_nTex = -1;

	//位置の代入
	CModel3D::SetPosition(pos);

	// 各種情報の代入
	CModel3D::SetScale(m_scale);

	//アップデートを通すかどうかの判定
	bool bUpdate = false;
	for (int nCntType = 0; nCntType < UPDATE_TYPE_NUM; nCntType++)
	{
		if (m_nType == anUpdateType[nCntType])
		{
			CModel3D::SetUpdate(false);
			bUpdate = true;
			break;
		}
	}

	//距離だけを求めるタイプ
	if (m_nType == TYPE_TREE02 || m_nType == TYPE_FLOWER)
	{
		CModel3D::SetOnlyLength(true);
	}

	if (!bUpdate)
	{
		bool bSmallObj = false;
		for (int nCntType = 0; nCntType < SMALL_OBJ_NUM; nCntType++)
		{// 小さいオブジェクトかどうかの判定
			if (m_nType == anSmallObjType[nCntType])
			{
				CModel3D::SetSmallObj(true);
				bSmallObj = true;
				break;
			}
		}

		for (int nCntType = 0; nCntType < HIGHT_OBJ_NUM; nCntType++)
		{// 高いオブジェクトのタイプかどうかの判定
			if(m_nType == anHightObjType[nCntType])
			{
				CModel3D::SetHightObj(true);
				break;
			}
		}
	}

	if (m_nType == 30 && CManager::GetMode() == CManager::MODE_GAME)
	{// 噴水にエフェクトをつける
		m_pLoadEffect = CLoadEffect::Create(6, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	}
	else if (m_nType == 33 && CManager::GetMode() == CManager::MODE_GAME)
	{// 消火栓エフェクト
		CModel3D::SetBoolRoll(false);
		m_pLoadEffect = CLoadEffect::Create(5, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);
	}

	//変数の初期化
	m_pEffectMgr = NULL;
	m_pObjBill = NULL;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject::Uninit(void)
{
	//エフェクトマネージャーの破棄
	if (m_pEffectMgr != NULL)
	{
		m_pEffectMgr->Uninit();
		delete m_pEffectMgr;
		m_pEffectMgr = NULL;
	}

	//ツールで作成したエフェクトを破棄
	if (m_pLoadEffect != NULL)
	{
		m_pLoadEffect->Uninit();
		delete m_pLoadEffect;
		m_pLoadEffect = NULL;
	}

	//オブジェクトビルボード
	m_pObjBill = NULL;

	//3DモデルのUninit
	CModel3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject::Update(void)
{
	CModel3D::Update();

	//距離の取得
	float fLength = CModel3D::GetLength();

	// 噴水のときエフェクトを出す
	FountainEffect();

	//葉のエフェクトの更新処理
	LeafEffect(fLength);

	//花壇の描画範囲判定
	if ((m_nType == TYPE_FLOWER) && (CModel3D::GetDraw() != false))
	{
		if (fLength > FLOWER_LENGTH)
		{//描画しない
			SetDraw(false);
		}
		else
		{
			SetDraw(true);
		}
	}

	if (CModel3D::GetDelete() == true) { Uninit(); }
}
//=============================================================================
// 描画処理
//=============================================================================
void CObject::Draw(void)
{
	if (m_nType == 19) { return; }

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//位置の初期化
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//頂点法線の自動正規化
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	//描画処理
	CModel3D::Draw();

	//頂点法線の自動正規化
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}
//===============================================================================
//　クリエイト
//===============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, float move, int nTexType, int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObject *pObject = NULL;

	// NULLチェック
	if (pObject == NULL)
	{// メモリの動的確保

		pObject = new CObject;

		if (pObject != NULL)
		{
			// 種類の設定
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType],
							   m_LoadVtxMaxModel[nObjectType], m_LoadVtxMinModel[nObjectType]);
			// オブジェクトごとの設定用タイプ
			pObject->m_nType = nObjectType;
			// サイズを代入
			pObject->m_scale = scale;
			// サイズを親クラスに代入
			pObject->SetScale(scale);
			// オブジェクトクラスの生成
			pObject->Init();
			//テクスチャ番号を代入
			pObject->m_nTex = nTexType;
			// 位置を代入
			pObject->SetPosition(pos);
			// 回転を反映
			pObject->SetRot(rot);
			// 動きの種類と移動量を設定
			pObject->SetMoveType(nMovetype);
			//pObject->m_move = D3DXVECTOR3(move, move, move);
			// コリジョンをONOFF
			pObject->m_nCollision = nCollision;

			//エフェクトマネージャーの生成
			pObject->CreateEffectMgr(pos);
		}
	}

	return pObject;
}
//===============================================================================
// Xファイルの読み込み
//===============================================================================
HRESULT CObject::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[0], NULL, &m_nNumMatModel[0], &m_pMeshModel[0]);
	D3DXLoadMeshFromX(MODEL_NAME_2, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[1], NULL, &m_nNumMatModel[1], &m_pMeshModel[1]);
	D3DXLoadMeshFromX(MODEL_NAME_3, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[2], NULL, &m_nNumMatModel[2], &m_pMeshModel[2]);
	D3DXLoadMeshFromX(MODEL_NAME_4, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[3], NULL, &m_nNumMatModel[3], &m_pMeshModel[3]);
	D3DXLoadMeshFromX(MODEL_NAME_5, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[4], NULL, &m_nNumMatModel[4], &m_pMeshModel[4]);
	D3DXLoadMeshFromX(MODEL_NAME_6, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[5], NULL, &m_nNumMatModel[5], &m_pMeshModel[5]);
	D3DXLoadMeshFromX(MODEL_NAME_7, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[6], NULL, &m_nNumMatModel[6], &m_pMeshModel[6]);
	D3DXLoadMeshFromX(MODEL_NAME_8, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[7], NULL, &m_nNumMatModel[7], &m_pMeshModel[7]);
	D3DXLoadMeshFromX(MODEL_NAME_9, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[8], NULL, &m_nNumMatModel[8], &m_pMeshModel[8]);
	D3DXLoadMeshFromX(MODEL_NAME_10, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[9], NULL, &m_nNumMatModel[9], &m_pMeshModel[9]);
	D3DXLoadMeshFromX(MODEL_NAME_11, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[10], NULL, &m_nNumMatModel[10], &m_pMeshModel[10]);
	D3DXLoadMeshFromX(MODEL_NAME_12, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[11], NULL, &m_nNumMatModel[11], &m_pMeshModel[11]);
	D3DXLoadMeshFromX(MODEL_NAME_13, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[12], NULL, &m_nNumMatModel[12], &m_pMeshModel[12]);
	D3DXLoadMeshFromX(MODEL_NAME_14, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[13], NULL, &m_nNumMatModel[13], &m_pMeshModel[13]);
	D3DXLoadMeshFromX(MODEL_NAME_15, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[14], NULL, &m_nNumMatModel[14], &m_pMeshModel[14]);
	D3DXLoadMeshFromX(MODEL_NAME_16, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[15], NULL, &m_nNumMatModel[15], &m_pMeshModel[15]);
	D3DXLoadMeshFromX(MODEL_NAME_17, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[16], NULL, &m_nNumMatModel[16], &m_pMeshModel[16]);
	D3DXLoadMeshFromX(MODEL_NAME_18, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[17], NULL, &m_nNumMatModel[17], &m_pMeshModel[17]);
	D3DXLoadMeshFromX(MODEL_NAME_19, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[18], NULL, &m_nNumMatModel[18], &m_pMeshModel[18]);
	D3DXLoadMeshFromX(MODEL_NAME_20, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[19], NULL, &m_nNumMatModel[19], &m_pMeshModel[19]);
	D3DXLoadMeshFromX(MODEL_NAME_21, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[20], NULL, &m_nNumMatModel[20], &m_pMeshModel[20]);
	D3DXLoadMeshFromX(MODEL_NAME_22, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[21], NULL, &m_nNumMatModel[21], &m_pMeshModel[21]);
	D3DXLoadMeshFromX(MODEL_NAME_23, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[22], NULL, &m_nNumMatModel[22], &m_pMeshModel[22]);
	D3DXLoadMeshFromX(MODEL_NAME_24, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[23], NULL, &m_nNumMatModel[23], &m_pMeshModel[23]);
	D3DXLoadMeshFromX(MODEL_NAME_25, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[24], NULL, &m_nNumMatModel[24], &m_pMeshModel[24]);
	D3DXLoadMeshFromX(MODEL_NAME_26, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[25], NULL, &m_nNumMatModel[25], &m_pMeshModel[25]);
	D3DXLoadMeshFromX(MODEL_NAME_27, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[26], NULL, &m_nNumMatModel[26], &m_pMeshModel[26]);
	D3DXLoadMeshFromX(MODEL_NAME_28, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[27], NULL, &m_nNumMatModel[27], &m_pMeshModel[27]);
	D3DXLoadMeshFromX(MODEL_NAME_29, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[28], NULL, &m_nNumMatModel[28], &m_pMeshModel[28]);
	D3DXLoadMeshFromX(MODEL_NAME_30, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[29], NULL, &m_nNumMatModel[29], &m_pMeshModel[29]);
	D3DXLoadMeshFromX(MODEL_NAME_31, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[30], NULL, &m_nNumMatModel[30], &m_pMeshModel[30]);
	D3DXLoadMeshFromX(MODEL_NAME_32, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[31], NULL, &m_nNumMatModel[31], &m_pMeshModel[31]);
	D3DXLoadMeshFromX(MODEL_NAME_33, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[32], NULL, &m_nNumMatModel[32], &m_pMeshModel[32]);
	D3DXLoadMeshFromX(MODEL_NAME_34, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[33], NULL, &m_nNumMatModel[33], &m_pMeshModel[33]);
	D3DXLoadMeshFromX(MODEL_NAME_35, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[34], NULL, &m_nNumMatModel[34], &m_pMeshModel[34]);
	D3DXLoadMeshFromX(MODEL_NAME_36, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[35], NULL, &m_nNumMatModel[35], &m_pMeshModel[35]);
	D3DXLoadMeshFromX(MODEL_NAME_37, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[36], NULL, &m_nNumMatModel[36], &m_pMeshModel[36]);
	D3DXLoadMeshFromX(MODEL_NAME_38, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[37], NULL, &m_nNumMatModel[37], &m_pMeshModel[37]);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//モデルの最大値・最小値を取得する
	for (int nCntModel = 0; nCntModel < MAX_OBJECT; nCntModel++)
	{
		m_LoadVtxMaxModel[nCntModel] = D3DXVECTOR3(-10000, -10000, -10000);	//最大値
		m_LoadVtxMinModel[nCntModel] = D3DXVECTOR3(10000, 10000, 10000);	//最小値

		//頂点数を取得
		nNumVtx = m_pMeshModel[nCntModel]->GetNumVertices();

		//頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(m_pMeshModel[nCntModel]->GetFVF());

		//頂点バッファのロック
		m_pMeshModel[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;		//頂点座標の代入

			//最大値
			if (vtx.x > m_LoadVtxMaxModel[nCntModel].x)
			{
				m_LoadVtxMaxModel[nCntModel].x = vtx.x;
			}
			if (vtx.y > m_LoadVtxMaxModel[nCntModel].y)
			{
				m_LoadVtxMaxModel[nCntModel].y = vtx.y;
			}
			if (vtx.z > m_LoadVtxMaxModel[nCntModel].z)
			{
				m_LoadVtxMaxModel[nCntModel].z = vtx.z;
			}
			//最小値
			if (vtx.x < m_LoadVtxMinModel[nCntModel].x)
			{
				m_LoadVtxMinModel[nCntModel].x = vtx.x;
			}
			if (vtx.y < m_LoadVtxMinModel[nCntModel].y)
			{
				m_LoadVtxMinModel[nCntModel].y = vtx.y;
			}
			if (vtx.z < m_LoadVtxMinModel[nCntModel].z)
			{
				m_LoadVtxMinModel[nCntModel].z = vtx.z;
			}

			//サイズ文のポインタを進める
			pVtxBuff += sizeFVF;
		}

		//頂点バッファのアンロック
		m_pMeshModel[nCntModel]->UnlockVertexBuffer();
	}

	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_1, &m_pMeshTextures[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_2, &m_pMeshTextures[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_3, &m_pMeshTextures[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_4, &m_pMeshTextures[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_5, &m_pMeshTextures[4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_6, &m_pMeshTextures[5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_7, &m_pMeshTextures[6]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_8, &m_pMeshTextures[7]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_9, &m_pMeshTextures[8]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_10, &m_pMeshTextures[9]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_11, &m_pMeshTextures[10]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_12, &m_pMeshTextures[11]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_13, &m_pMeshTextures[12]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_14, &m_pMeshTextures[13]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_15, &m_pMeshTextures[14]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_16, &m_pMeshTextures[15]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_17, &m_pMeshTextures[16]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_18, &m_pMeshTextures[17]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_19, &m_pMeshTextures[18]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_20, &m_pMeshTextures[19]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_21, &m_pMeshTextures[20]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_22, &m_pMeshTextures[21]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_23, &m_pMeshTextures[22]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_24, &m_pMeshTextures[23]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_25, &m_pMeshTextures[24]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_26, &m_pMeshTextures[25]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_27, &m_pMeshTextures[26]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_28, &m_pMeshTextures[27]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_29, &m_pMeshTextures[28]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_30, &m_pMeshTextures[29]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_31, &m_pMeshTextures[30]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_32, &m_pMeshTextures[31]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_33, &m_pMeshTextures[32]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_34, &m_pMeshTextures[33]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_35, &m_pMeshTextures[34]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_36, &m_pMeshTextures[35]);//セコマ
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_37, &m_pMeshTextures[36]);//ローソン
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_38, &m_pMeshTextures[37]);//セブン
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_39, &m_pMeshTextures[38]);//ファミマ
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_40, &m_pMeshTextures[39]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_41, &m_pMeshTextures[40]);

	return S_OK;
}
//===============================================================================
// テクスチャの破棄
//===============================================================================
void CObject::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		// メッシュの開放
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
	//テクスチャ
	for (int nCntTex = 0; nCntTex < MAX_OBJECT_TEXTURE; nCntTex++)
	{
		if (m_pMeshTextures[nCntTex] != NULL)
		{
			m_pMeshTextures[nCntTex]->Release();
			m_pMeshTextures[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//	ステージ移動時に初期化するため
//=============================================================================
void CObject::DeleteObject(void)
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
		{//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				pScene->Uninit();
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//===============================================================================
// エフェクトマネージャーの生成
//===============================================================================
void CObject::CreateEffectMgr(D3DXVECTOR3 pos)
{
	if ((m_nType != TYPE_TREE00) && (m_nType != TYPE_TREE01) && (m_nType != TYPE_TREE02)) { return; }

	if ((m_pEffectMgr == NULL) && (CManager::MODE_GAME == CManager::GetMode()))
	{ //エフェクトマネージャーの生成
		m_pEffectMgr = CEffectMgr::Create(D3DXVECTOR3(pos.x, pos.y + EFFECT_HIGHT, pos.z), CEffectMgr::TYPE_SUMMER);
	}
}

//=============================================================================
// 噴水による移動量の変化
//=============================================================================
D3DXVECTOR3 CObject::Fountain(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	D3DXVECTOR3 posObj = CModel3D::GetPosition();	// 位置の取得
	D3DXVECTOR3 vec = pos - posObj;					// 自分から相手方向へのベクトル

	// ベクトルの長さを求める
	float fLengthVec = D3DXVec3Length(&vec);		// 自分から相手方向へのベクトルの長さ
	float fLengthMove = D3DXVec3Length(&move);		// 相手の移動量の長さ

	D3DXVECTOR3 vecMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 角度を求める
	float fAngle = acosf(move.x / sqrt(move.x * move.x + move.z * move.z));
	if (move.z < 0.0f)fAngle = 2.0f * D3DX_PI - fAngle;
	if (isnan(fAngle))return vecMove;

	D3DXVECTOR3 vtxMax = CModel3D::GetVtxMax();		// 頂点座標の最大値の取得

	int nDigit = (int)log10f(vtxMax.x) + 1;
	if (6 < nDigit)return move;

	nDigit = (int)log10f(vtxMax.z) + 1;
	if (6 < nDigit)return move;

	// 移動量の計算
	if (m_nType == 33)
	{// 消火栓
		vecMove = D3DXVECTOR3(0.8f * (move.x + (cosf(fAngle) * vtxMax.x)), FOUNTAIN_UP * 0.4f, 0.8f * (move.z + (sinf(fAngle) * vtxMax.z)));
	}
	else
	{// 噴水
		vecMove = D3DXVECTOR3(0.05f * (move.x + (cosf(fAngle) * vtxMax.x)), FOUNTAIN_UP, 0.05f * (move.z + (sinf(fAngle) * vtxMax.z)));
	}

	return vecMove;
}

//=============================================================================
// 噴水のエフェクトの生成
//=============================================================================
void CObject::FountainEffect(void)
{
	if ((m_nType == 30 || (m_nType == 33 && CModel3D::GetBoolBlow())) && NULL != m_pLoadEffect)
	{// 噴水にエフェクトをつける
		CManager::MODE mode = CManager::GetMode();
		D3DXVECTOR3 PlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//モードごとに取得
		if (mode == CManager::MODE_GAME)
		{
			PlayerPos = CGame::GetPlayer()->GetPos();
		}
		else if (mode == CManager::MODE_TUTORIAL)
		{
			PlayerPos = CTutorial::GetPlayer()->GetPos();
		}

		//距離を求める
		D3DXVECTOR3 Distance = PlayerPos - CModel3D::GetPosition();
		float fLength = sqrtf((Distance.x * Distance.x) + (Distance.z * Distance.z));

		if (fLength < FOUNTAIN_LENGTH)
		{//噴水の更新範囲
			if(m_nType == 30){ m_pLoadEffect->SetPos(CModel3D::GetPosition() + D3DXVECTOR3(0.0f, CModel3D::GetVtxMax().y, 0.0f)); }
			else if (m_nType == 33) { m_pLoadEffect->SetPos(CModel3D::GetPosition()); }

			m_pLoadEffect->Update();
		}
	}
}

//=============================================================================
// 葉のエフェクト更新処理
//=============================================================================
void CObject::LeafEffect(float fLength)
{
	if (m_pEffectMgr != NULL)
	{
		//葉っぱのエフェクト処理を更新
		if(fLength < LEAF_LENGTH)
		{
			m_pEffectMgr->Update();
		}

		if (fLength > WOOD_LENGTH)
		{
			//ビルボードの生成
			if (m_pObjBill == NULL)
			{
				m_pObjBill = CObjBillboad::Create(CModel3D::GetPosition(), m_nType);
				m_pObjBill->SetModelInfo(m_scale, m_nTex, m_nCollision);
			}
			else if (m_pObjBill != NULL)
			{
				m_pObjBill->SetDraw(true);
				CModel3D::SetDraw(false);
			}
		}
		else
		{
			CModel3D::SetDraw(true);
		}
	}
}

//===============================================================================
// 当たり判定
//===============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//19以外はこの処理に入らない
	if (m_nType != 19) return false;

	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();

	//あたっているかあたってないか
	bool bLand = false;

	switch (m_nCollision)
	{
	case 1:

		// 各種情報の取得
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// 位置
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();		// 移動量
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// 動きのタイプ
		D3DXVECTOR3 VtxMax = CModel3D::GetVtxMax();			// モデルの最大値
		D3DXVECTOR3 VtxMin = CModel3D::GetVtxMin();			// モデルの最小値
		D3DXVECTOR3 rot = CModel3D::GetRot();

		D3DXVECTOR3 ModelMax = CModel3D::GetPosition() + CModel3D::GetVtxMax();	// 位置込みの最大値
		D3DXVECTOR3 ModelMin = CModel3D::GetPosition() + CModel3D::GetVtxMin();	// 位置込みの最小値

		// 移動量の保持
		if (ModelMove.x == 0.0f) ModelMove.x = m_ModelMove.x;
		if (ModelMove.y == 0.0f) ModelMove.y = m_ModelMove.y;
		if (ModelMove.z == 0.0f) ModelMove.z = m_ModelMove.z;

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Zの範囲内にいる
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// Xの範囲内にいる
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// オブジェクトの上から当たる場合
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X移動同期
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z移動同期
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// オブジェクトの下から当たる場合
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}

				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{// オブジェクト横との当たり判定
					if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x + rot.x && pPos->x - PLAYER_DEPTH < ModelMax.x + rot.x)
					{// 右から抜けた場合
						pPos->x = ModelMax.x + PLAYER_DEPTH;
					}
					else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
					{// 左から抜けた場合
						pPos->x = ModelMin.x - PLAYER_DEPTH;
					}

					if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
					{// 奥から抜けた場合
						pPos->z = ModelMax.z + PLAYER_DEPTH + 0.1f;
					}
					else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
					{// 手前から抜けた場合
						pPos->z = ModelMin.z - PLAYER_DEPTH - 0.1f;
					}
				}
			}
		}

		// 位置の代入
		CModel3D::SetPosition(ModelPos);
		// 移動量の代入
		m_ModelMove = ModelMove;

		break;
	}

	return bLand;
}
