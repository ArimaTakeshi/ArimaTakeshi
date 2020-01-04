//=============================================================================
//
// 地面処理 [ground.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "ground.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "mesh.h"
#include "scene3D.h"
#include "game.h"
#include "player.h"
#include "sound.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define GROUND_TEX_1		"data\\TEXTURE\\トラップ\\ゾーン.jpg"		// トラップゾーン用テクスチャ
#define GROUND_TEX_2		"data\\TEXTURE\\トラップ\\yazirusi000.png"	// トラップゾーン用テクスチャ
#define GROUND_TEX_3		"data\\TEXTURE\\トラップ\\next.png"			// トラップゾーン用テクスチャ
#define GROUND_TEX_4		"data\\TEXTURE\\トラップ\\break.png"		// トラップゾーン用テクスチャ
#define GROUND_MOVE_SPEED	(0.002f)									// テクスチャの移動速度の調整用

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CGround::m_pTexture[MAX_GROUND_TEX] = {};
LPDIRECT3DVERTEXBUFFER9	CGround::m_pVtxBuff = NULL;
bool CGround::m_bTrap = false;
bool CGround::m_bSafety = false;

//=============================================================================
// コンストラクタ
//=============================================================================
CGround::CGround() : CScene3D(GROUND_PRIOTITY, CScene::OBJTYPE_GROUND)
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_fTexMoveSpeed = 0.0f;
	m_bLight = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CGround::~CGround()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGround::Init()
{
	CScene3D::Init();

	//種類の設定
	SetTypeNumber(TYPE_GROUND);
	m_fTexMoveSpeed = GROUND_MOVE_SPEED;

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CGround::Uninit(void)
{
	m_bTrap = false;

	CScene3D::Uninit();
}
//=============================================================================
// 更新処理
//=============================================================================
void CGround::Update(void)
{
	CScene3D::Update();

	//変数
	D3DXVECTOR2 UV[4];
	D3DXCOLOR col[4];

	m_nCnt++;

	if (m_rot.x != 0.0f)
	{
		UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * 0.025f), 1.0f);
		UV[1] = D3DXVECTOR2(0.0f - (m_nCnt * 0.025f), 0.0f);
		UV[2] = D3DXVECTOR2(1.0f - (m_nCnt * 0.025f), 1.0f);
		UV[3] = D3DXVECTOR2(1.0f - (m_nCnt * 0.025f), 0.0f);

		CScene3D::SetNor(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	else if (m_rot.z != 0.0f)
	{
		UV[0] = D3DXVECTOR2(0.0f + (m_nCnt * 0.025f), 0.0f);
		UV[1] = D3DXVECTOR2(1.0f + (m_nCnt * 0.025f), 0.0f);
		UV[2] = D3DXVECTOR2(0.0f + (m_nCnt * 0.025f), 1.0f);
		UV[3] = D3DXVECTOR2(1.0f + (m_nCnt * 0.025f), 1.0f);
	}
	else
	{
		if (m_move.x != 0.0f)
		{// テクスチャ設定　左右に流れる
			UV[0] = D3DXVECTOR2(0.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 0.0f);
			UV[1] = D3DXVECTOR2(1.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 0.0f);
			UV[2] = D3DXVECTOR2(0.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 1.0f);
			UV[3] = D3DXVECTOR2(1.0f - (m_nCnt * (m_move.x * m_fTexMoveSpeed)), 1.0f);
		}
		if (m_move.z != 0.0f)
		{// テクスチャ設定 上下に流れる
			UV[0] = D3DXVECTOR2(0.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 1.0f);
			UV[1] = D3DXVECTOR2(0.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 0.0f);
			UV[2] = D3DXVECTOR2(1.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 1.0f);
			UV[3] = D3DXVECTOR2(1.0f + (m_nCnt * (m_move.z * m_fTexMoveSpeed)), 0.0f);
		}
		if (m_move.z == 0.0f && m_move.x == 0.0f)
		{// テクスチャ設定 動きなし
			UV[0] = D3DXVECTOR2(0.0f, 0.0f);
			UV[1] = D3DXVECTOR2(1.0f, 0.0f);
			UV[2] = D3DXVECTOR2(0.0f, 1.0f);
			UV[3] = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	//レットゾーンの色変更
	if (m_nType == 0)
	{
		//点滅処理
		//選択しているカラーの値を減らしていく
		m_fColorCount -= 0.009f;

		if (m_fColorCount < 0.5f)
		{//信託しているカラーが0.5を切ったらカラーの値が増えてく
			m_fColorCount = 0.9f;
		}

		//センサーにかかったかどうかで色を変える
		if (m_bTrap == false)
		{//緑
			col[0] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
			col[1] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
			col[2] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
			col[3] = D3DXCOLOR(0.0f, 1.0f, 0.0f, m_fColorCount);
		}
		else  if (m_bTrap == true)
		{//赤
			col[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
			col[1] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
			col[2] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
			col[3] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		}
	}
	//セーフティーゾーンの色変更
	if (m_nType == 1)
	{
		//点滅処理
		//選択しているカラーの値を減らしていく
		m_fColorCount -= 0.009f;

		if (m_fColorCount < 0.5f)
		{//信託しているカラーが0.5を切ったらカラーの値が増えてく
			m_fColorCount = 0.9f;
		}

		col[0] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
		col[1] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
		col[2] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
		col[3] = D3DXCOLOR(0.0f, 0.0f, 1.0f, m_fColorCount);
	}
	//セーフティーゾーンの色変更
	if (m_nType == 2)
	{
		m_fColorCount = 0.7f;

		col[0] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);
		col[1] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);
		col[2] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);
		col[3] = D3DXCOLOR(1.0f, 1.0f, 0.0f, m_fColorCount);

		if (m_nLightCounter > 320)
		{
			m_nLightCounter = 0;
		}
		else if (m_nLightCounter > 260)
		{
			m_pos.z += 0.0f;
		}
		else if (m_nLightCounter > 160)
		{
			m_pos.z -= 5.0f;
		}
		else if (m_nLightCounter > 100)
		{
			m_pos.z += 0.0f;
		}
		else if (m_nLightCounter >= 0)
		{
			m_pos.z += 5.0f;
		}

		m_nLightCounter++;
	}

	//セーフティーゾーンの色変更
	if (m_nType == 3)
	{
		//点滅処理
		//選択しているカラーの値を減らしていく
		m_fColorCount -= 0.009f;

		if (m_fColorCount < 0.5f)
		{//信託しているカラーが0.5を切ったらカラーの値が増えてく
			m_fColorCount = 0.9f;
		}


		col[0] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		col[1] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		col[2] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
		col[3] = D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fColorCount);
	}

	//背景のUV
	CScene3D::SetUV(&UV[0]);
	CScene3D::SetColor(&col[0]);
	CScene3D::SetPosition(m_pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CGround::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//プレイヤーの位置情報
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();
	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	if (m_nType == 3)
	{
		//フォグを使用しない
		pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}

	CScene3D::Draw();
	
	if (m_nType == 3)
	{
		//フォグを使用しない
		pDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
}
//===============================================================================
//　クリエイト
//===============================================================================
CGround * CGround::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR2 size, int nType, int nTextureType)
{
	CGround *pGround = NULL;

	//NULLチェック
	if (pGround == NULL)
	{//メモリの動的確保

		pGround = new CGround;

		if (pGround != NULL)
		{
			//初期化処理
			pGround->Init();
			//当たり判定用
			pGround->m_size = size;
			//種類の設定
			pGround->m_nType = nType;
			//テクスチャの種類
			pGround->SetTexType(0);
			//位置と大きさの設定
			pGround->SetGroundPosSize(pos, size);
			pGround->m_pos = pos;
			// 移動量の設定
			pGround->SetMove(move);
			pGround->m_move = move;
			// 角度の設定
			pGround->SetRotation(rot * D3DX_PI);
			pGround->m_rot = rot;
			//テクスチャの設定
			pGround->BindTexture(m_pTexture[nTextureType]);
		}
	}

	return pGround;
}
//=============================================================================
// 床の当たり判定
//=============================================================================
void CGround::CollisionGround(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	// posを取得
	D3DXVECTOR3 GroundPos = CScene3D::GetPosition();
	D3DXVECTOR3 GroundRot = CScene3D::GetRotation();
	D3DXVECTOR3 GroundMove = CScene3D::GetMove();
	D3DXVECTOR2 GroundSize = CScene3D::GetSize();

	//サウンドの情報
	CSound *pSound = CManager::GetSound();

	CScene *pScene;

	if (pPos->x <= GroundPos.x + GroundSize.x
		&& pPos->x >= GroundPos.x - GroundSize.x)
	{// 床と同じz軸に存在している
		if (pPos->z <= GroundPos.z + GroundSize.y
			&& pPos->z >= GroundPos.z - GroundSize.y)
		{// 床と同じx軸に存在している
			if (GroundRot == D3DXVECTOR3(0.0f, 0.0f, 0.0f) && pPos->y < GroundPos.y)
			{// 床に触れている
				/*pMove->x += GroundMove.x;
				pMove->y += GroundMove.y;
				pMove->z += GroundMove.z;*/

				//if (pPosOld->y > GroundPos.y)
				{
					if (m_nType == 0)
					{
						if (CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SNEAK && m_bTrap == false || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SQUAT && m_bTrap == false || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_TIRED && m_bTrap == false)
						{
							m_bTrap = false;
						}
						else if (CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SNEAK || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SQUAT || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_TIRED)
						{
							m_bTrap = true;

							//プライオリティーチェック
							pScene = CScene::GetTop(2);

							//NULLチェック
							while (pScene != NULL)
							{
								//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
								CScene *pSceneNext = pScene->GetNext();

								if (pScene->GetDeath() == false)
								{//タイプが壁だったら
									if (pScene->GetObjType() == OBJTYPE_ENEMY)
									{
										//敵に発見させる
										((CEnemy*)pScene)->SetPattern(2);

										//発見時の音
										pSound->PlaySound(CSound::SOUND_LABEL_SE_TRAP);
									}
								}
								//Nextに次のSceneを入れる
								pScene = pSceneNext;
							}
						}
					}
					else if (m_nType == 1)
					{//セーフティゾーン
						if (CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SNEAK || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_SQUAT || CGame::GetPlayer()->GetAnim() == CPlayer::PLAYERANIM_TIRED)
						{
							m_bSafety = true;
						}
						else if (CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SNEAK || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_SQUAT || CGame::GetPlayer()->GetAnim() != CPlayer::PLAYERANIM_TIRED)
						{
							m_bSafety = false;
						}
					}
					else if (m_nType == 2)
					{//ライト
						
						m_bLight = true;

						if (m_bSafety == false)
						{
							//プライオリティーチェック
							pScene = CScene::GetTop(2);

							//NULLチェック
							while (pScene != NULL)
							{
								//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
								CScene *pSceneNext = pScene->GetNext();

								if (pScene->GetDeath() == false)
								{//タイプが壁だったら
									if (pScene->GetObjType() == OBJTYPE_ENEMY)
									{
										//敵に発見させる
										((CEnemy*)pScene)->SetPattern(2);

										//発見時の音
										pSound->PlaySound(CSound::SOUND_LABEL_SE_TRAP);
									}
								}
								//Nextに次のSceneを入れる
								pScene = pSceneNext;
							}
						}
						else if(m_bSafety == true)
						{
							m_bLight = false;
						}
						else if (m_bSafety == false || m_bLight == true)
						{
							//プライオリティーチェック
							pScene = CScene::GetTop(2);

							//NULLチェック
							while (pScene != NULL)
							{
								//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
								CScene *pSceneNext = pScene->GetNext();

								if (pScene->GetDeath() == false)
								{//タイプが壁だったら
									if (pScene->GetObjType() == OBJTYPE_ENEMY)
									{
										//敵に発見させる
										((CEnemy*)pScene)->SetPattern(2);

										//発見時の音
										pSound->PlaySound(CSound::SOUND_LABEL_SE_TRAP);
									}
								}
								//Nextに次のSceneを入れる
								pScene = pSceneNext;
							}
						}
					}
				}

				CDebugProc::Print("bTrap = %s\n", m_bTrap ? "true": "false");
				CDebugProc::Print("m_bSafety = %s\n", m_bSafety ? "true" : "false");

				//CDebugProc::Print("GroundMove.x = %.1f ,GroundMove.y = %.1f, GroundMove.z = %.1f\n", GroundMove.x, GroundMove.y, GroundMove.z);
				//CDebugProc::Print("GroundSize.x = %.1f ,GroundSize.y = %.1f\n\n", GroundSize.x, GroundSize.y);
			}
		}
	}
}
//=============================================================================
// マップ移動の際の削除
//=============================================================================
void CGround::DeleteGround(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(GROUND_PRIOTITY);

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//タイプが壁だったら
			if (pScene->GetObjType() == OBJTYPE_GROUND)
			{
				pScene->Uninit();
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}
//=============================================================================
// 読み込み処理
//=============================================================================
HRESULT CGround::Load(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ生成
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_1, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_2, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_3, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, GROUND_TEX_4, &m_pTexture[3]);

	return S_OK;
}

//=============================================================================
// 開放処理
//=============================================================================
void CGround::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_GROUND_TEX; nCount++)
	{
		// テクスチャ破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}