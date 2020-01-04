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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME_1	"data\\MODEL\\saku000.x"			//読み込むテクスチャファイル
#define MODEL_NAME_2	"data\\MODEL\\saku001.x"			//読み込むテクスチャファイル
#define MODEL_NAME_3	"data\\MODEL\\wall000.x"			//読み込むテクスチャファイル
#define MODEL_NAME_4	"data\\MODEL\\wall001.x"			//読み込むテクスチャファイル
#define MODEL_NAME_5	"data\\MODEL\\bed.x"				//読み込むテクスチャファイル
#define MODEL_NAME_6	"data\\MODEL\\peple.x"				//読み込むテクスチャファイル
#define MODEL_NAME_7	"data\\MODEL\\stair.x"				//読み込むテクスチャファイル
#define MODEL_NAME_8	"data\\MODEL\\自販機.x"				//読み込むテクスチャファイル
#define MODEL_NAME_9	"data\\MODEL\\柱.x"					//読み込むテクスチャファイル
#define MODEL_NAME_10	"data\\MODEL\\grass.x"				//読み込むテクスチャファイル
#define MODEL_NAME_11	"data\\MODEL\\TreeU.x"				//読み込むテクスチャファイル
#define MODEL_NAME_12	"data\\MODEL\\TreeD.x"				//読み込むテクスチャファイル
#define MODEL_NAME_13	"data\\MODEL\\saku003.x"			//読み込むテクスチャファイル
#define MODEL_NAME_14	"data\\MODEL\\WoodenDesk.x"			//読み込むテクスチャファイル
#define MODEL_NAME_15	"data\\MODEL\\WoodenChair.x"		//読み込むテクスチャファイル
#define MODEL_NAME_16	"data\\MODEL\\段ボール.x"			//読み込むテクスチャファイル
#define MODEL_NAME_17	"data\\MODEL\\Extinguisher.x"		//読み込むテクスチャファイル
#define MODEL_NAME_18	"data\\MODEL\\locker.x"				//読み込むテクスチャファイル
#define MODEL_NAME_19	"data\\MODEL\\door.x"				//読み込むテクスチャファイル
#define MODEL_NAME_20	"data\\MODEL\\SmallWoodenDesk.x"	//読み込むテクスチャファイル
#define MODEL_NAME_21	"data\\MODEL\\ゴミ箱.x"				//読み込むテクスチャファイル
#define MODEL_NAME_22	"data\\MODEL\\counter.x"			//読み込むテクスチャファイル
#define MODEL_NAME_23	"data\\MODEL\\fence.x"				//読み込むテクスチャファイル
#define MODEL_NAME_24	"data\\MODEL\\security.x"			//読み込むテクスチャファイル
#define MODEL_NAME_25	"data\\MODEL\\floor.x"				//読み込むテクスチャファイル
#define MODEL_NAME_26	"data\\MODEL\\smallfence.x"			//読み込むテクスチャファイル
#define MODEL_NAME_27	"data\\MODEL\\ArmoredCar.x"			//読み込むテクスチャファイル
#define MODEL_NAME_28	"data\\MODEL\\gate.x"				//読み込むテクスチャファイル
#define MODEL_NAME_29	"data\\MODEL\\prison.x"				//読み込むテクスチャファイル
#define MODEL_NAME_30	"data\\MODEL\\tower.x"				//読み込むテクスチャファイル
#define MODEL_NAME_31	"data\\MODEL\\cone.x"				//読み込むテクスチャファイル
#define MODEL_NAME_32	"data\\MODEL\\Generator.x"			//読み込むテクスチャファイル

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(25)			// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(100.0f)		// プレイヤーの背の高さ

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

//===============================================================================
//　デフォルトコンストラクタ
//===============================================================================
CObject::CObject() : CModel3D(OBJECT_PRIOTITY,CScene::OBJTYPE_OBJECT)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStageCount = 0;
	m_bStageNext = false;
}
//===============================================================================
//　デストラクタ
//===============================================================================
CObject::~CObject()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3DモデルのInit
	CModel3D::Init();
	
	// 位置の初期化
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_nType == 13)
	{
		//影の描画
		//m_pShadow = CShadow::Create(pos, 50.0f, 50.0f, 0);
	}
	else if (m_nType == 14)
	{
		//影の描画
		//m_pShadow = CShadow::Create(pos, 50.0f, 50.0f, 0);
	}


	//位置の代入
	CModel3D::SetPosition(pos);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject::Uninit(void)
{
	if (m_nType == 13 && m_nType == 14)
	{
		//影を破棄
		//m_pShadow->Uninit();
	}

	//3DモデルのUninit
	CModel3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject::Update(void)
{
	//入力情報
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	//3DモデルのUpdate
	CModel3D::Update();
	//位置の初期化
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの代入
	D3DXVECTOR3 &rot = CModel3D::GetRot();
	// MOVETYPEの設定
	MOVETYPE MoveType = CModel3D::GetMoveType();
	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	//半径
	float fRadius = 10.0f;
	//円周
	float fCircumference = (((D3DX_PI * 2.0f) * fRadius));

	//影の高さを保持しておく
	//float fMeshHeight = m_pShadow->GetShadowHeight();

	switch (MoveType)
	{
	case MOVETYPE_X_MOVE:
		// X軸移動
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Y_MOVE:
		// Y軸移動
		if (m_nCount <= 120)
		{
			move.y += m_move.y;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.y -= m_move.y;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Z_MOVE:
		// Z軸移動
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		break;

	case MOVETYPE_ROTATION_X:
		// X軸で回転しながらZ軸移動
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.x += 0.1f;
		break;

	case MOVETYPE_ROTATION_Z:
		// Z軸で回転しながらX軸移動
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.z += 0.1f;
		break;
	case MOVETYPE_CONT:
		//移動処理
		if (pCInputKeyBoard->GetKeyboardPress(DIK_D) == true)
		{
			//回転の割合から距離を出す
			m_Spin.z += -0.005f * D3DX_PI;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_A) == true)
		{
			//回転の割合から距離を出す
			m_Spin.z += 0.005f * D3DX_PI;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_W) == true)
		{
			//回転の割合から距離を出す
			m_Spin.x += 0.005f * D3DX_PI;
		}
		else if (pCInputKeyBoard->GetKeyboardPress(DIK_S) == true)
		{
			//回転の割合から距離を出す
			m_Spin.x += -0.005f * D3DX_PI;
		}
		else
		{
			m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		//角度に
		rot.z += m_Spin.z;
		rot.x += m_Spin.x;

		pos.x -= (m_Spin.z / (D3DX_PI * 2.0f)) * fCircumference;
		pos.z -= (-m_Spin.x / (D3DX_PI * 2.0f)) * fCircumference;

		//慣性
		m_Spin.x *= 0.95f;
		m_Spin.z *= 0.95f;

		break;
	}

	//ステージ遷移が発動したとき
	if (m_bStageNext == true)
	{
		//1秒後にフェード
		if (m_nStageCount == 60)
		{
			//ステージ移動
			if (pStageNum == CGame::STAGENUM_1)
			{
				CFade::Create(CGame::STAGENUM_2);
			}
			else if (pStageNum == CGame::STAGENUM_2)
			{
				CFade::Create(CGame::STAGENUM_3);
			}
			else if (pStageNum == CGame::STAGENUM_3)
			{
				CFade::Create(CGame::STAGENUM_4);
			}
			else if (pStageNum == CGame::STAGENUM_4)
			{
				CFade::Create(CGame::STAGENUM_5);
			}
			else if (pStageNum == CGame::STAGENUM_5)
			{
				CFade::Create(CGame::STAGENUM_6);
			}

			//ステージ遷移をしていない状態にする
			m_bStageNext = false;
			//カウントを初期化する
			m_nStageCount = 0;

		}
		//カウントを増す
		m_nStageCount++;
	}

	// 移動量の代入
	pos += move;


	// 各種情報の代入
	CModel3D::SetPosition(pos);
	CModel3D::SetMove(move);
	CModel3D::SetMoveType(MoveType);
}
//=============================================================================
// 描画処理
//=============================================================================
void CObject::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//位置の初期化
	D3DXVECTOR3 Modelpos = CModel3D::GetPosition();
	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	//マップ移動時専用のオブジェクト以外を描画する
	if (m_nType != 2)
	{
		CModel3D::Draw();
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CObject * CObject::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, float move, int nTexType,int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObject *pObject = NULL;

	// NULLチェック
	if (pObject == NULL)
	{// メモリの動的確保

		pObject = new CObject;

		if (pObject != NULL)
		{
			// 種類の設定
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// オブジェクトごとの設定用タイプ
			pObject->m_nType = nObjectType;
			// オブジェクトクラスの生成
			pObject->Init();
			// 位置を代入
			pObject->SetPosition(pos);
			// 回転を反映
			pObject->SetRot(rot);
			// 動きの種類と移動量を設定
			pObject->SetMoveType(nMovetype);
			pObject->m_move = D3DXVECTOR3(move, move, move);
			// コリジョンをONOFF
			pObject->m_nCollision = nCollision;
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

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	//使っているテクスチャ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\iron000.jpg", &m_pMeshTextures[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall003.jpg", &m_pMeshTextures[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall\\wall001.jpg", &m_pMeshTextures[2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cona.jpg", &m_pMeshTextures[3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\si-tu.jpg", &m_pMeshTextures[4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bender.jpg", &m_pMeshTextures[5]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\grass.png", &m_pMeshTextures[6]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\葉っぱ.jpg", &m_pMeshTextures[7]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bark-texture.png", &m_pMeshTextures[8]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\木の板テクスチャ.jpg", &m_pMeshTextures[9]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\gerador3.jpg", &m_pMeshTextures[10]);

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
// 当たり判定
//===============================================================================
bool CObject::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;
	//あたっているかあたってないか
	bool bLand = false;
	//当たり判定の保存
	int nCollision = m_nCollision;
	//モードの情報
	CManager::MODE pMode = CManager::GetMode();
	//カメラの情報
	CCamera *pCamera = CManager::GetCamera();
	//ステージ情報
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	switch (m_nCollision)
	{
	case 1:

		// 各種情報の取得
		D3DXVECTOR3 Playerpos = *pPos;						// プレイヤーの初期位置
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// 位置
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();		// 移動量
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// 動きのタイプ
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();			// モデルの最大値
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();			// モデルの最小値

		D3DXVECTOR3 ModelMax = CModel3D::VtxMax();	// 位置込みの最大値
		D3DXVECTOR3 ModelMin = CModel3D::VtxMin();	// 位置込みの最小値

		//計算前用
		D3DXVECTOR3 WkMax = ModelMax;
		D3DXVECTOR3 WkMin = ModelMin;

		//角度
		D3DXVECTOR3 rot = CModel3D::GetRot();
		bool		bHit = false;

		// 移動量の保持
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		//モデルの向きによって当たり判定のMAXとMINを変える
		if (rot.y == 1.57f)
		{//右向き
			ModelMin.z = WkMax.x * -1.0f;
			ModelMax.z = WkMin.x * -1.0f;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -1.57f)
		{
			ModelMax.z = WkMax.x;
			ModelMin.z = WkMin.x;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -3.14f || rot.y == 3.14f)
		{
			ModelMin.x = WkMax.x * -1.0f;
			ModelMax.x = WkMin.x * -1.0f;
			ModelMin.z = WkMax.z * -1.0f;
			ModelMax.z = WkMin.z * -1.0f;
		}
		ModelMax += ModelPos;
		ModelMin += ModelPos;

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
			}
		}

		if (pPos->y - PLAYER_HEIGHT <= ModelMax.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
		{// オブジェクト横との当たり判定
			if (pPos->x - PLAYER_DEPTH <= ModelMax.x && pPos->x + PLAYER_DEPTH >= ModelMin.x)
			{// オブジェクト横との当たり判定
				if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
				{//MAX 縦上
					pPos->z = ModelMax.z + PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
				{//MIN 縦下
					pPos->z = ModelMin.z - PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
			}
			if (pPos->z - PLAYER_DEPTH <= ModelMax.z && pPos->z + PLAYER_DEPTH >= ModelMin.z)
			{// オブジェクト横との当たり判定 
				if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
				{//MAX 横右
					pPos->x = ModelMax.x + PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
				{//MIN 横左
					pPos->x = ModelMin.x - PLAYER_DEPTH;

					//プライオリティーチェック
					pScene = CScene::GetTop(2);

					//NULLチェック
					while (pScene != NULL)
					{
						//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//タイプが壁だったら
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Nextに次のSceneを入れる
						pScene = pSceneNext;
					}
				}
			}
		}


		if (m_nType == 2 && bHit == true)
		{// マップ移動時専用オブジェクト
			if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(59.0f, 146.0f, 568.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-199.0f, 0.0f, 140.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_3)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(905.0f, 190.0f, 540.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(635.0f, 0.0f, 680.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_4)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(470.0f, 240.0f, 660.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(845.0f, 0.0f, -160.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_5)
			{
				//カメラアングルを階段を上るときの目線
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(-1040.0f, 170.0f, 400.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-740.0f, 0.0f, 280.0f));

				//ステージ遷移の際のスキルキャンセル
				CPlayer::SetCancelStageNext(true);

				//ステージ遷移中
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_6)
			{
				if (CFade::GetFade() == CFade::FADE_NONE)
				{//Pキーが押されたら
					//新規追加
					CManager::SetGameScore(CTime::GetTime());
					CManager::RankingScore(CTime::GetTime());

					//ステージ遷移の際のスキルキャンセル
					CPlayer::SetCancelStageNext(true);

					CGame::SetGameState(CGame::GAMESTATE_CLEAR);
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