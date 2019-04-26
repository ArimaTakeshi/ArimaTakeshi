//=============================================================================
//
// ポリゴン処理 [SceneAnim3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"SceneAnim3D.h"
#include"Renderer.h"
#include "manager.h"
#include "ScenePlayer.h"
#include "dungeon.h"
#include "camera.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	CSceneAnim3D::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CSceneAnim3D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			 //ラビリンス//***********************************************************************
			case TEX_EXPLOSION:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/pipo-btleffect022.jpg", &m_pTexture[tex]);	break;
			case TEX_FIRE_EXPLOSION:D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/fireball00011.jpg", &m_pTexture[tex]);		break;
			case TEX_FIRE:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/pipo-btleffect103a.jpg", &m_pTexture[tex]);	break;
			case TEX_ICE:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/pipo-btleffect159.jpg", &m_pTexture[tex]);	break;
			case TEX_LIGHTNING:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/pipo-btleffect160.jpg", &m_pTexture[tex]);	break;
			case TEX_BARRIER:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/barrier000.jpg", &m_pTexture[tex]);			break;
			case TEX_BEFFECT:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/pipo-btleffect192_640.jpg", &m_pTexture[tex]);	break;
			case TEX_GOAL:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/GOAL.jpg", &m_pTexture[tex]);					break;
			case TEX_CHARGE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Effect100.jpg", &m_pTexture[tex]);			break;
			case TEX_CHARGE2:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Effect300.jpg", &m_pTexture[tex]);			break;
			case TEX_CHARGE3:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Guard100.jpg", &m_pTexture[tex]);				break;
			case TEX_BREAK:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/pipo-btleffect078.jpg", &m_pTexture[tex]);	break; 
			case TEX_HIT:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/pipo-btleffect135.jpg", &m_pTexture[tex]);		break;
			case TEX_BOOST:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Effect_DASH000.jpg", &m_pTexture[tex]);		break;
			case TEX_STATUS_UP:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/StatusUp.png", &m_pTexture[tex]);				break;
			case TEX_APPEAR:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Appear.jpg", &m_pTexture[tex]);							break; 
			case TEX_HEEL:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Heel.jpg", &m_pTexture[tex]);							break;
			case TEX_SHIELD:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Shield001.jpg", &m_pTexture[tex]);						break; 
			case TEX_DRIFT:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Drift000.jpg", &m_pTexture[tex]);						break; 
			case TEX_MAGIC:			D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/pipo-btleffect007.jpg", &m_pTexture[tex]);				break;
			case TEX_WEAPON:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/Weapon.jpg", &m_pTexture[tex]);							break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CSceneAnim3D::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//全画像破棄
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//=============================================================================
// 状態分岐で破壊処理
//=============================================================================
void	CSceneAnim3D::BreakPolygon(STATE state)
{
	CScene **PSceneTarget = NULL;

	PSceneTarget = CScene::GetScene(SAnim3D_PRIORITY);
	for (int nCntTarget = 0; nCntTarget < CScene::GetnMemoryAll(SAnim3D_PRIORITY); nCntTarget++)
	{
		if (PSceneTarget[nCntTarget] != NULL)
		{
			if (PSceneTarget[nCntTarget]->GetObjType() >= CScene::OBJTYPE_ANIM3D)
			{//モデルなら
				if (((CSceneAnim3D*)PSceneTarget[nCntTarget])->GetState()[0] == state)
				{
					((CSceneAnim3D*)PSceneTarget[nCntTarget])->GetState()[0] = STATE_FADEOUTN;
				}
			}
		}//if(NULL)
	}//for()
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneAnim3D::Init(void)
{
	CScene3D::Init();
	m_animation = ANIMATION_NORMAL;
	m_nCntAnim = -1;
	m_nPtnAnim = 0;
	m_nPtnWide = 1;
	m_nPtnHeight = 1;
	m_nPtnSpeed = 1;
	return S_OK;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneAnim3D::Update(void)
{//アニメーション
	VERTEX_3D *pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXVECTOR3 *pos = GetPosition();	D3DXVECTOR3 *rot = GetRotation();	D3DXCOLOR	*col = GetColor();
	float *fLengthX = GetfLengthX();	float *fLengthZ = GetfLengthZ();
	STATE *state = GetState();			float *fCntState = GetfCntState();
	CScenePlayer *pPlayer;
	D3DXVECTOR3 *pPlayer_pos;

 //頂点バッファをロックし、頂点データへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV変更
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//画像の範囲外
			if (m_animation == ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}

		//UVの設定
		pVtx[0].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[1].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[2].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
		pVtx[3].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
	}

	switch (state[0])
	{
	case STATE_GOAL://次階層への判定
		fCntState[0] += 1.0f;
		if ((int)fCntState[0] % 100 == 1)
		{//エフェクト
			CSceneAnim3D *pSceneAnim3D = NULL; 
			if(SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
			{
				pSceneAnim3D->Set(pos[0], rot[0], col[0], fLengthX[0], fLengthZ[0], TEX_GOAL, CScene::DRAW_TYPE_SUBTRACT, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_FADE);
			}
		}
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{//プレイヤー分回転
			pPlayer = CManager::GetPlayer(nCount);
			if (pPlayer != NULL)
			{//生成されているなら
				pPlayer_pos = pPlayer->GetPosition();
				if (pPlayer_pos[0].x > pos[0].x - fLengthX[0] && pPlayer_pos[0].x < pos[0].x + fLengthX[0] &&
					pPlayer_pos[0].z > pos[0].z - fLengthZ[0] && pPlayer_pos[0].z < pos[0].z + fLengthZ[0])
				{//範囲内なら
					pPlayer->GetnStage()++;
					fCntState[0] = 0;
					CScenePlayer::GetbCamera() = false;
					state[0] = STATE_GOAL2;

					CSceneAnim2D *pAnim2D;
					if(SceneCreate(pAnim2D, SAnim3DF_PRIORITY + 2))
					{//切り替えエフェクト
						pAnim2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 8, 3,
							1.0f / (16.0f * 3.0f), CScene2D::STATE_FADE, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Fade000);
					}
					break;
				}
			}
		}
		break;
	case STATE_GOAL2://次階層へ　カメラ操作
		CCamera::camera.m_posR += ((pos[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f)) - CCamera::camera.m_posR) * 0.25f;
		CCamera::camera.m_posV += ((pos[0] + D3DXVECTOR3(0.0f, 20.0f, 0.0f)) - CCamera::camera.m_posV) * 0.25f;
		CCamera::camera.m_posV.z -= 0.01f;
		fCntState[0] += 1.0f;
		if (fCntState[0] == 30) 
		{ 
			CScenePlayer::GetbCamera() = true;
			pVtxBuff->Unlock(); //頂点バッファのアンロック
			CManager::GetDungeon()->SetDungeon(pPlayer->GetnStage());
			return;
		}
		break;
	case STATE_SHOP:
		fCntState[0] += 1.0f;
		if ((int)fCntState[0] % 100 == 1)
		{
			CSceneAnim3D *pSceneAnim3D = NULL;
			if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
			{
				pSceneAnim3D->Set(pos[0],
					rot[0], col[0], fLengthX[0], fLengthZ[0], TEX_GOAL, CScene::DRAW_TYPE_ADD, 0, 5, 2, 3, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_FADE);
			}
		}
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{//プレイヤー分回転
			pPlayer = CManager::GetPlayer(nCount);
			if (pPlayer != NULL)
			{//生成されているなら
				pPlayer_pos = pPlayer->GetPosition();
				if (pPlayer_pos[0].x > pos[0].x - fLengthX[0] && pPlayer_pos[0].x < pos[0].x + fLengthX[0] &&
					pPlayer_pos[0].z > pos[0].z - fLengthZ[0] && pPlayer_pos[0].z < pos[0].z + fLengthZ[0])
				{//範囲内なら ショップへ移動
					fCntState[0] = 0;
					CScenePlayer::GetbCamera() = false;
					state[0] = STATE_SHOP2;

					CSceneAnim2D *pAnim2D;
					if (SceneCreate(pAnim2D, SAnim3DF_PRIORITY + 2))
					{//切り替えエフェクト
						pAnim2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 8, 3,
							1.0f / (16.0f * 3.0f), CScene2D::STATE_FADE, CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Fade000);
					}
					break;
				}
			}
		}
		break;
	case STATE_SHOP2:
		CCamera::camera.m_posR += ((pos[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f)) - CCamera::camera.m_posR) * 0.25f;
		CCamera::camera.m_posV += ((pos[0] + D3DXVECTOR3(0.0f, 20.0f, 0.0f)) - CCamera::camera.m_posV) * 0.25f;
		CCamera::camera.m_posV.z -= 0.01f;
		fCntState[0] += 1.0f;
		if (fCntState[0] == 30)
		{
			CScenePlayer::GetbCamera() = true;
			pVtxBuff->Unlock(); //頂点バッファのアンロック
			CManager::GetDungeon()->SetDungeon_Shop(pPlayer->GetnStage());
			return;
		}
		break;
	case STATE_FADE:
		fCntState[0] += 0.03f;
		col[0].a = fCntState[0];//透明度変更
		fLengthX[0] *= 1.0f + (fCntState[0] * 0.075f); fLengthZ[0] *= 1.0f + (fCntState[0] * 0.075f);

		if (fCntState[0] >= 0.5f)
		{ 
			col[0].a = 0.5f;
			fCntState[0] = 0.5f; state[0] = STATE_FADEOUT;
		}
		break;
	case STATE_FADEOUT:
		fCntState[0] += 0.03f;
		if (fCntState[0] >= 1.0f) { Uninit(); return; }
		col[0].a = 1.0f - fCntState[0];//透明度変更
		fLengthX[0] *= 1.0f + (fCntState[0] * 0.075f); fLengthZ[0] *= 1.0f + (fCntState[0] * 0.075f);
		break;
	case STATE_FADEOUT2:
		fCntState[0] += 0.05f;
		rot[0].y += D3DX_PI * 0.03f;
		if (fCntState[0] >= 1.0f) { Uninit(); return; }
		col[0].a = 1.0f - fCntState[0];//透明度変更
		fLengthX[0] *= 1.0f - ((1.0f - fCntState[0]) * 0.1f);
		fLengthZ[0] *= 1.0f - ((1.0f - fCntState[0]) * 0.1f);
		SetColor(col[0]);
		SetSize(fLengthX[0], fLengthZ[0]);
		break;
	case STATE_FADEOUTN:
		col[0].a -= 0.03f;//透明度変更
		if (col[0].a <= 0.0f) { Uninit(); return; }
		break;
	}
	for (int nCount = 0; nCount < 4; nCount++) { pVtx[nCount].col = col[0]; }
	pVtx[0].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, fLengthZ[0]);
	pVtx[1].pos = D3DXVECTOR3(fLengthX[0], 0.1f, fLengthZ[0]);
	pVtx[2].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, -fLengthZ[0]);
	pVtx[3].pos = D3DXVECTOR3(fLengthX[0], 0.1f, -fLengthZ[0]);

	//頂点バッファのアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// 設定処理
//=============================================================================
void CSceneAnim3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
	TEXTURE nType, DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state)
{
	CScene3D::Set(pos, rot, col, fLengthX, fLengthZ, CScene3D::TEXTURE_MAX, nPtnAnim, nPtnWide, nPtnHeight, DrawType);
	BindTexture(Load(nType));
	m_animation = animation;
	GetState()[0] = state;
	GetfCntState()[0] = 0.0f;
	m_nCntAnim = -1;
	m_nPtnAnim = nPtnAnim;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
	m_nPtnWide = nPtnWide;

	if (state == STATE_SHOP || state == STATE_GOAL) { SetObjType(CScene::OBJTYPE_ANIM3D); }
}
//=============================================================================
// 設定処理
//=============================================================================
void CSceneAnimEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
	TEXTURE nType, DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CSceneAnim3D::Set(pos, rot, col, fLengthX, fLengthZ, nType, DrawType, nPtnAnim, nPtnWide, nPtnHeight, nPtnSpeed, animation, state);
	m_pPos = pPos;
	m_pScene = pScene;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneAnimEffect::Update()
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition()[0] = m_pPos[0]; }
	CSceneAnim3D::Update();
}
