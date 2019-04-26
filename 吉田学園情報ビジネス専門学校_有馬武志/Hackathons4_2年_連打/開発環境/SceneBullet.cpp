//=============================================================================
//
// ポリゴン処理 [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "camera.h"
#include"SceneModel.h"
#include"Renderer.h"
#include "dungeon.h"
#include "manager.h"
#include "SceneBullet.h"
#include "ScenePlayer.h"
#include "SceneEnemy.h"
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
LPDIRECT3DTEXTURE9	CSceneBullet::m_pTexture[TEXTURE_MAX] = {};		// テクスチャへのポインタ

//=============================================================================
// 画像の読み込み
//=============================================================================
LPDIRECT3DTEXTURE9	*CSceneBullet::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//範囲確認
		if (m_pTexture[tex] == NULL)
		{//読み込んでないなら
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//読み込み
			case TEX_BULLET:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Shot_All301.png", &m_pTexture[tex]);	break;
			//case TEX_BULLET2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Shot_All101.png", &m_pTexture[tex]);	break;
			case TEX_BULLET_S:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Shot_All301_S.png", &m_pTexture[tex]); break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// 画像の解放
//=============================================================================
void	CSceneBullet::UnLoad(void)
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
// 寿命の更新処理
//=============================================================================
bool CSceneBullet::LifeUpdate(void)
{
	D3DXCOLOR	*col = GetColor();
	float *fCntState = GetfCntState();

	fCntState[0] += 1.0f;					//生存時間カウント

	if (fCntState[0] > 0.0f)
	{
		if (fCntState[0] > SHOT_LIFE)
		{
			if (col[0].a < 0.0f) { Uninit(); }
			else
			{//透明化
				col[0].a -= 0.05f;
				SetColor(col[0]);
			}
			return false;
		}
		else if (col[0].a < 1.0f && m_ObjType == CScene::OBJTYPE_BULLET)
		{
			col[0].a += 0.05f;
			if (col[0].a > 1.0f) { col[0].a = 1.0f; }
			SetColor(col[0]);
			return false;
		}
	}
	else if (fCntState[0] < 0.0f) { return false; }

	return true;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneNorBullet::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXVECTOR3 *pos = GetPosition(); D3DXVECTOR3 *rot = GetRotation(); D3DXCOLOR	*col = GetColor();
	float *fCntState = GetfCntState();
	float fSlow = 1.0f;
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();

	if (LifeUpdate())
	{
		int nChange = m_nChange;	//効果付与
		while (nChange > 0)
		{//桁が残っているなら
			switch (nChange % 10)
			{//チェンジ効果付与
			case CHANGE_SPDUP:		//加速
				if (m_fAccelerator < 0.1f) { m_fAccelerator += 0.005f * fSlow; } 
				break;
			case CHANGE_SPDDOWN:	//減速
				if(fCntState[0] > SHOT_LIFE * 0.12 * fSlow){ m_move *= 0.85f; }
				break;
			case CHANGE_BACK:	//Spd少しずつ反転
				if (m_fSpeed > -0.1f) { m_fSpeed -= 0.1f * fSlow; }
				break;
			case CHANGE_BACK2:	//Spd少しずつ反転
				if (fCntState[0] == 60.0f) { m_fSpeed *= -1.0f; }
				break;
			case CHANGE_STRAIGHT:	//回転値(*)
				m_fTurning *= 1.0f - (1.0f - 0.98f) * fSlow;
				break;
			case CHANGE_SPINUP:
				if (fCntState[0] == 60.0f)
				{
					if (m_fTurning > 0.0f) { m_fTurning += D3DX_PI; }
					else { m_fTurning -= D3DX_PI; }
				}
				break;
			case CHANGE_SLOW:		//全体スピードダウン
				fSlow = 0.98f;
				break;
				//	CHANGE_SPINUP,		//回転値 (+)
				//	CHANGE_SPINDOWN,	//回転値 (-)
				//	CHANGE_HOMING,		//途中でいきなり敵方向を向く
				//	CHANGE_HOMINGS,		//途中でいきなり敵方向を向き数F止まる
			}
			nChange /= 10;	//桁を一つ削る
		}
		//毎F処理
		//一定値範囲内なら
		m_fSpeed += m_fAccelerator * fSlow;		//加速
		rot[0].y += m_fTurning * fSlow;			//旋回
		//移動
		pos[0] += m_move * fSlow;
		m_move += (D3DXVECTOR3(sinf(rot[0].y), 0.0f, cosf(rot[0].y)) * m_fSpeed) * fSlow;
		m_move *= m_fSlip * fSlow;	//慣性

		if (fCntState[0] > SHOT_LIFE * 0.5 * fSlow){ m_fTurning *= 0.95f; }
		else if (fCntState[0] > SHOT_LIFE * 0.6 * fSlow){ m_fAccelerator = 0.0f; }
		else if (fCntState[0] > SHOT_LIFE * 0.7 * fSlow) { m_move *= 0.85f; }

		CDungeon *pDungeon = CManager::GetDungeon();
		if (pDungeon != NULL && m_ObjType == CScene::OBJTYPE_BULLET && !m_bDestroy) { pDungeon->ShotCollision((CSceneBullet*)this); }
	}

}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneSetBullet::Update(void)
{
	float *fCntState = GetfCntState();
	if (fCntState[0] < SHOT_LIFE)
	{
		m_fAngleSet += m_fAnglePlus;
		if (((int)fCntState[0] + 1) % m_nInterval == 0)
		{//セット処理
			if (SetAttack(m_SetType, fCntState[0], m_fAngleSet, m_nNumSet, m_move, m_nUV,m_nInterval)) { return; }
		}
	}
	CSceneNorBullet::Update();
}
//=============================================================================
// 更新処理
//=============================================================================
void CScenePairBullet::Update(void)
{
	float	*fCntState = GetfCntState();
	bool	bLife = false;
	bool	bWallX = false, bWallZ = false;

	if (fCntState[0] < 0) { fCntState[0] = 10; bLife = true; }
	GetPosition()[0] = m_pos2;	//場所の更新
	CSceneNorBullet::Update();//弾の更新

	if (fCntState[0] >= 0.0f)
	{
		D3DXVECTOR3 *pos = GetPosition(), *rot = GetRotation(), WKpos;

		//砲塔の向き変更
		if (rot[0].y > D3DX_PI) { rot[0].y -= D3DX_PI * 2; }
		if (rot[0].y < -D3DX_PI) { rot[0].y += D3DX_PI * 2; }

		////角度補正
		if ((pos[0].x < -m_fXWall && rot[0].y < 0.0f) || (pos[0].x > m_fXWall && rot[0].y >= 0.0f)) { bWallX = true; }
		if ((pos[0].z > m_fZWall && rot[0].y <= D3DX_PI / 2 && rot[0].y >= -D3DX_PI / 2) ||
			(pos[0].z < -m_fZWall && (rot[0].y >= D3DX_PI / 2 || rot[0].y <= -D3DX_PI / 2))) {
			bWallZ = true;
		}

		if (bWallX)
		{//壁に当たった -> X壁ならZrand(), Z壁ならXrand() から角度再取得 
			WKpos = pos[0] + D3DXVECTOR3(sinf(rot[0].y) * -1.0f, 0.0f, 1.0f * (cosf(rot[0].y) * 1.0f) + (-m_fRangeZ + ((rand() % (int)(m_fRangeZ  * 2000.0f + 1)) * 0.001f)) * (sinf(rot[0].y)));
			GetRotation()[0].y = atan2f(WKpos.x - pos[0].x, WKpos.z - pos[0].z);
		}
		if (bWallZ)
		{//壁に当たった -> X壁ならZrand(), Z壁ならXrand() から角度再取得 
			WKpos = pos[0] + D3DXVECTOR3((sinf(rot[0].y) * 1.0f) + (-m_fRangeX + ((rand() % (int)(m_fRangeX  * 2000.0f + 1)) * 0.001f)) * (cosf(rot[0].y)), 0.0f, cosf(rot[0].y) * -1.0f);
			GetRotation()[0].y = atan2f(WKpos.x - pos[0].x, WKpos.z - pos[0].z);
		}

		m_pos2 = pos[0];		//場所の保存
		m_pos3 += (m_pPos[0] - m_pos3) * 0.1f;
		pos[0] += m_pos3;	//描画用に親と合成

		m_nNumCount++;
		//角度の更新
		if (m_pRot != NULL) { m_fAngleSet = m_pRot[0]; } //親角度が有効なら
		else { m_fAngleSet += m_fAnglePlus; }

		if (m_nNumCount % m_nInterval == 0)
		{//セット処理
			if (!CScenePlayer::GetbShop())
			{//ショップじゃないなら
				if (SetAttack(m_SetType, m_fMaxLife, m_fAngleSet, m_nNumSet, m_move, m_nUV, m_nInterval)) { return; }
			}
		}
		if (bLife) { fCntState[0] = -1; }
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CScenePairBullet2::Update(void)
{
	float	*fCntState = GetfCntState();
	bool	bLife = true;	//生命時間の有無
	if (fCntState[0] < 0) { fCntState[0] = 10.0f; bLife = false; }

	if(LifeUpdate())
	{//動いていい
		float	*fCntState = GetfCntState();
		bool	bWallX = false, bWallZ = false;

		D3DXVECTOR3 *pos = GetPosition(), *rot = GetRotation(), WKpos;
		
		rot[0].y += m_fTurning;

		//砲塔の向き変更
		if (rot[0].y > D3DX_PI) { rot[0].y -= D3DX_PI * 2; }
		if (rot[0].y < -D3DX_PI) { rot[0].y += D3DX_PI * 2; }

		m_pos3 += (m_pPos[0] - m_pos3) * m_fGMagnification;
		pos[0] = m_pos3 + D3DXVECTOR3(sinf(rot[0].y), 0.0f, cosf(rot[0].y)) * m_fDistance;

		CDungeon *pDungeon = CManager::GetDungeon();
		if (pDungeon != NULL && m_ObjType == CScene::OBJTYPE_BULLET && !m_bDestroy) { pDungeon->ShotCollision((CSceneBullet*)this); }
	}

	if (!bLife) { fCntState[0] = -10.0f; }
}
//=============================================================================
// 更新処理
//=============================================================================
void CScenePairBulletSet::Update(void)
{
	float	*fCntState = GetfCntState();

	CScenePairBullet2::Update();

	if (fCntState[0] < SHOT_LIFE)
	{
		m_nNumCount++;
		//角度の更新
		if (m_pRot != NULL) { m_fAngleSet = m_pRot[0]; }//親角度が有効なら
		else { m_fAngleSet += m_fAnglePlus; }
		if (m_nNumCount % m_nInterval == 0)
		{//セット処理
			if (!CScenePlayer::GetbShop())
			{//ショップじゃないなら
				if (SetAttack(m_SetType, m_fMaxLife, m_fAngleSet, m_nNumSet, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_nUV, m_nInterval)) { return; }
			}
		}
	}
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneBullet::Draw(void)
{
	D3DXVECTOR3 *pos = GetPosition();
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();

	if (pos[0].x - fLengthX[0] < CCamera::camera.m_posR.x + SHOT_DROW_X && pos[0].x + fLengthX[0] > CCamera::camera.m_posR.x - SHOT_DROW_X &&
		pos[0].z - fLengthZ[0] < CCamera::camera.m_posR.z + SHOT_DROW_Z && pos[0].z + fLengthZ[0] > CCamera::camera.m_posR.z - SHOT_DROW_Z)
	{//範囲内なら
		float fPosY = PLAYER_Y;
		LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得
		if (m_shot <= SHOT_PLAYER2 && CManager::GetMode()[0] == CManager::MODE_GAME) { fPosY -= 0.5f; }

		////影の描画//***********************************************************************
		//アルファテスト処理(透明化による画像の切り取り現象を有効にする)
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 50);//REF = Reference:参照
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:機能 //GREATER = ～より大きい

		CScene::DrawPrepare(CScene::DRAW_TYPE_NORMAL, pD3DDevice);
		//テクスチャの設定
		pD3DDevice->SetTexture(0, m_pTexture[TEX_BULLET_S]);
		DrawParts(fPosY, pD3DDevice);	//ポリゴンの描画
		//DrawParts(pos[0].y - 0.3f, pD3DDevice);	//ポリゴンの描画

		//弾の描画//***********************************************************************
			CScene::DrawPrepare(CScene::DRAW_TYPE_ADD, pD3DDevice);
			//アルファテスト処理(透明化による画像の切り取り現象を有効にする)
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 100);//REF = Reference:参照
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:機能 //GREATER = ～より大きい
			//テクスチャの設定
			pD3DDevice->SetTexture(0, m_pTexture[TEX_BULLET]);
			DrawParts(fPosY + 0.3f, pD3DDevice);	//ポリゴンの描画

			//α切り取り無効化
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//テクスチャをNULLに
		pD3DDevice->SetTexture(0, NULL);
		//pD3DDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
	}
}
//=============================================================================
// 描画補助処理
//=============================================================================
void CSceneBullet::DrawParts(float fPosY, LPDIRECT3DDEVICE9& pD3DDevice)
{
	D3DXVECTOR3 *pos = GetPosition();
	D3DXVECTOR3 *rot = GetRotation();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//計算用マトリックス
	D3DXMATRIX	mtxWorld;		//ワールドマトリックス

	//pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	////ビルボード
	//pD3DDevice->GetTransform(D3DTS_VIEW, &mtxView);

	////逆行列を設定
	//mtxWorld._11 = mtxView._11;
	//mtxWorld._12 = mtxView._21;
	//mtxWorld._13 = mtxView._31;
	//mtxWorld._21 = mtxView._12;
	//mtxWorld._22 = mtxView._22;
	//mtxWorld._23 = mtxView._32;
	//mtxWorld._31 = mtxView._13;
	//mtxWorld._32 = mtxView._23;
	//mtxWorld._33 = mtxView._33;

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot[0].y, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos[0].x, fPosY, pos[0].z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// 頂点バッファをデータストリームに設定
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pD3DDevice->SetFVF(FVF_VERTEX_3D);
	//ポリゴンの描画
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

}
//=============================================================================
// 頂点情報設定処理
//=============================================================================
void CSceneBullet::SetVtx(int nUV)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXCOLOR	*col = GetColor();
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();

	//プレイヤー以外の弾ならひとつずらす
	if (m_shot > SHOT_PLAYER2) { nUV++; }

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++) { pVtx[nCount].col = col[0]; }

	pVtx[0].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, fLengthZ[0]);
	pVtx[1].pos = D3DXVECTOR3(fLengthX[0], 0.1f, fLengthZ[0]);
	pVtx[2].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, -fLengthZ[0]);
	pVtx[3].pos = D3DXVECTOR3(fLengthX[0], 0.1f, -fLengthZ[0]);
	//UVの設定
	pVtx[0].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + SHOT_UV_SMALL);
	pVtx[1].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X) + (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + SHOT_UV_SMALL);
	pVtx[2].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + (1.0f / SHOT_UV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X) + (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + (1.0f / SHOT_UV_Y));

	//頂点バッファのアンロック
	pVtxBuff->Unlock();

	if (m_shot == SHOT_PLAYER1 && CManager::GetPlayer(0) != NULL) { m_fAtk *= CManager::GetPlayer(0)->GetAtkUP() * PLUS_ATK + 1.0f; }
	else if (m_shot == SHOT_PLAYER2 && CManager::GetPlayer(1) != NULL) { m_fAtk *= CManager::GetPlayer(1)->GetAtkUP() * PLUS_ATK + 1.0f; }
}
//=============================================================================
// 設定処理
//=============================================================================
void CSceneNorBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//基本設定
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//頂点情報

	//弾情報
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fAtk = fAtk; m_bDestroy = bDestroy; m_bShotDelete = bShotDelete;
	m_move = move;
	
	//画像割り当て
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//他情報の設定
	SetVtx(nUV);
	SetMove(change);
}
//=============================================================================
// 設定処理
//=============================================================================
void CSceneSetBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete,
	SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//基本設定
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//頂点情報
	m_move = move;

	//弾情報
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_SetType = SetType; m_nNumSet = nNumSet; m_nInterval = nInterval;	//Set情報代入
	m_fAtk = fAtk; m_bDestroy = bDestroy; m_bShotDelete = bShotDelete;
	m_fAngleSet = fAngleSet; m_fAnglePlus = fAnglePlus;
	//画像割り当て
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//他情報の設定
	m_nUV = nUV;
	SetVtx(nUV);
	SetMove(change);
}

//=============================================================================
// 設定処理
//=============================================================================
void CScenePairBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fXWall, float fZWall, float fRangeX, float fRangeZ,
	SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//基本設定
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//頂点情報
	m_pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f); m_pos3 = pos;
	//弾情報
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fLife = fCntState; m_fMaxLife = fCntState;
	m_fSpeed = fSpeed; 
	m_fXWall = fXWall; m_fZWall = fZWall; m_fRangeX = fRangeX; m_fRangeZ = fRangeZ;
	m_SetType = SetType; m_bShotDelete = bShotDelete; m_pPos = pPos; m_pRot = pRot;	//Set情報代入
	m_fAnglePlus = fAnglePlus; m_fAngleSet = fAngleSet; m_nNumSet = nNumSet;
	m_nInterval = nInterval;
	m_fAtk = fAtk; m_bDestroy = false;
	m_nUV = nUV;
	//画像割り当て
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//他情報の設定
	SetVtx(nUV);
}
//=============================================================================
// 設定処理
//=============================================================================
void CScenePairBullet2::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
	D3DXVECTOR3 *pPos, float *pRot, bool bDestroy, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//基本設定
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//頂点情報
	m_pos3 = pos;
	//弾情報
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fLife = fCntState; m_fMaxLife = fCntState;
	m_fSpeed = fSpeed; m_fAtk = fAtk;
	m_fDistance = fDistance; m_fAngle = fAngle; m_fGMagnification = fGMagnification;

	m_bShotDelete = bShotDelete; m_pPos = pPos; m_pRot = pRot;	//Set情報代入
	m_bDestroy = bDestroy;

	//画像割り当て
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//他情報の設定
	SetVtx(nUV);
}
//=============================================================================
// 設定処理
//=============================================================================
void CScenePairBulletSet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
	SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//基本設定
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//頂点情報
	m_pos3 = pos;
	//弾情報
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fLife = fCntState; m_fMaxLife = fCntState;
	m_fSpeed = fSpeed;
	m_fDistance = fDistance; m_fAngle = fAngle; m_fGMagnification = fGMagnification;

	m_SetType = SetType; m_bShotDelete = bShotDelete; m_pPos = pPos; m_pRot = pRot;	//Set情報代入
	m_fAnglePlus = fAnglePlus; m_fAngleSet = fAngleSet; m_nNumSet = nNumSet;
	m_nInterval = nInterval;
	m_fAtk = fAtk; m_bDestroy = false;
	m_nUV = nUV;

	//画像割り当て
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//他情報の設定
	SetVtx(nUV);
}
//=============================================================================
// 初期速度設定処理
//=============================================================================
void CSceneNorBullet::SetMove(CHANGE& change)
{
	D3DXVECTOR3 rot = GetRotation()[0];

	switch (change)
	{
	case CHANGE_FAST:		//初期加速
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * (m_fSpeed * 3.0f);
		break;
	case CHANGE_FAST2:		//初期加速
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * (m_fSpeed * 50.0f);
		break;
	case CHANGE_GRAVITY:	//逆方向にブレアリ60
		rot.y += D3DX_PI - D3DX_PI * ((1.0f * 0.33f) * 0.5f);
		rot.y += D3DX_PI * ((rand() % (int)((1.0f * 0.33f) * 1000.0f)) * 0.001f);
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * ((rand() % 800) * 0.001f + 0.3f);
		m_fSpeed *= (rand() % 1000) * 0.0005f + 1.0f;
		break;
	case CHANGE_GRAVITY2:	//逆方向にブレアリ120
		rot.y += D3DX_PI - D3DX_PI * ((1.0f * 0.66f) * 0.5f);
		rot.y += D3DX_PI * ((rand() % (int)((1.0f * 0.66f) * 1000.0f)) * 0.001f);
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * ((rand() % 800) * 0.001f + 0.3f);
		m_fSpeed *= (rand() % 1000) * 0.0005f + 1.0f;
		break;
	}

}
//=============================================================================
// 発砲処理
//=============================================================================
void CSceneBullet::ShotAttack(SHOT Shot, ATTACK Atk, D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRotU, bool bFirst, 
	float fSpd, float fSlip, float fLife, float fTurning, float fAccelerator, float fLengthX, float fLengthZ,
	float fRange, float fDistance, int nNumBullet, int nChange, CHANGE Change, float fAtk, bool bDestroy, bool *bShotDelete, int nUV)
{
	CSound *pSound = CManager::GetSound();
	CSceneNorBullet *bulletNor = NULL;
	CSceneSetBullet *bulletSet = NULL;
	CSceneBullet::SET set;

	fRotU += D3DX_PI * 2;
	float	fWKAngle = fRotU;	//角度計算用
	float	fAngle = 0.0;		//発砲角度

	float	fWKAnglePlus = 0.0f;
	int		nWKSet = 60, nWKNumSet = 1;

	//switch (Atk)
	//{
	//case ATK_PTN00:		fRange = D3DX_PI * 0.5f;	nNumBullet = 8;		break;
	//case ATK_PTN01:		fRange = D3DX_PI * 0.5f;	nNumBullet = 8;		break;
	//	//ボス用//***********************************************************************
	//case BATK_CROSS:	fRange = D3DX_PI; 			nNumBullet = 4;		break;
	//case BATK_BRANCH:	fRange = D3DX_PI;			nNumBullet = 4;		break;
	//case BATK_SPIN_0:	fRange = D3DX_PI;			nNumBullet = 8;		break;
	//case BATK_SPIN_1:	fRange = D3DX_PI;			nNumBullet = 8;		break;
	//}
	if (!bFirst) { fAngle += (float)((D3DX_PI * 2) / (float)nNumBullet); }
	for (int nCount = (bFirst ? 0 : 1); nCount < nNumBullet; nCount++, fAngle += (float)((D3DX_PI * 2) / (float)nNumBullet))
	{//回転値プラス
		//if (nCount == nNumBullet / 2) {}
		if ((D3DX_PI * 2) - fRange < fAngle || fRange > fAngle)
		{//範囲内なら
			switch (Atk)
			{
			case ATK_PTN00:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら
					fWKAngle = fAngle;
					if (fWKAngle > D3DX_PI) { fWKAngle -= D3DX_PI * 2; }
					fWKAngle = fWKAngle * 0.5f + fRotU;
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf((fAngle + fRotU)) * fDistance, 0.0f, cosf((fAngle + fRotU)) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
				}
				else { return; } break;
			case ATK_PTN01:
				if (nCount != 0)
				{
					if (SceneCreate(bulletNor, BULLET_PRIORITY))
					{//生成できたなら
						fWKAngle = (fRotU - fAngle) * 0.95f;
						bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * fDistance, 0.0f, cosf(fAngle) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, (fAngle + fWKAngle), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
							fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
					}
					else { return; }
				}break;
			case ATK_PTN02:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら
					fWKAngle = (fRotU - fAngle) * 0.5f;
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * fDistance, 0.0f, cosf(fAngle) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, (fAngle + fWKAngle), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
				} else { return; } break;
			case ATK_PTN03:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf((fAngle + fRotU)) * fDistance, 0.0f, cosf((fAngle + fRotU)) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, (fAngle + fRotU), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
				} else { return; } break;
			case ATK_PTN_FIRE:
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら
					fWKAngle = (fRotU - fAngle) * 0.95f;
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.5f, 5.0f, 50,
						SHOT_LIFE - 30.0f, nChange, 0.025f, 0.0f, 0.0f, 0.97f, Change, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_FIRE0, fAngle, 0.0f, 1, 1);
				} else { return; } break;
			case ATK_PTN_FIRE2:
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら
					fWKAngle = fRotU + fAngle;
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fWKAngle) * fDistance, 0.0f, cosf(fWKAngle) * fDistance) + D3DXVECTOR3(sinf(fRotU), 0.0f, cosf(fRotU)) * 10.0f,
						move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_FIRE0, fAngle, 0.0f, 1, 1);
				} else { return; } break;
				break;
			case ATK_BEAM00:
			case ATK_BEAM01:
			case ATK_BEAM02:
			case ATK_BEAM10:
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら
					fWKAngle = fRotU + fAngle;
					set = CSceneBullet::SET_EFFECT;
					switch (Atk)
					{
					case ATK_BEAM00: fWKAngle = fRotU + fAngle; break;	//そのまま
					case ATK_BEAM01: //寄せる
						fWKAngle = fAngle;
						if (fWKAngle > D3DX_PI) { fWKAngle -= D3DX_PI * 2; }
						fWKAngle = fWKAngle * 0.5f + fRotU;	
						break;
					case ATK_BEAM02: fWKAngle = fRotU; break;	//向いてる方向
					case ATK_BEAM10: set = CSceneBullet::SET_EFFECT0;
					}
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fRotU + fAngle) * fDistance, 0.0f, cosf(fRotU + fAngle) * fDistance),
						move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete, set, fWKAngle, 0.0f, 1, 1);
				} else { return; } break;
				break;
			case ATK_SETTING0:
			case ATK_SETTING1:
			case ATK_PDIFFUSION:
			case ATK_PDIFFUSION2:
			case ATK_DIFFUSION: fWKAngle = fRotU + fAngle;
				switch (Atk)
				{
				case ATK_SETTING0:		set = SET_TURN;			nWKSet = 1; nWKNumSet = 1;	fWKAnglePlus = D3DX_PI * 0.12f;	break;
				case ATK_SETTING1:		set = SET_TURN;			nWKSet = 1; nWKNumSet = 1;	fWKAnglePlus = D3DX_PI * 0.12f;	break;
				case ATK_PDIFFUSION:	set = SET_PDIFFUSION;	nWKSet = 60; nWKNumSet = 5; break;
				case ATK_DIFFUSION:		set = SET_DIFFUSION;	nWKSet = 60; nWKNumSet = 5; break;
				case ATK_PDIFFUSION2:	set = SET_PDIFFUSION2;	nWKSet = 60; nWKNumSet = 5; break;
				}
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fWKAngle) * fDistance, 0.0f, cosf(fWKAngle) * fDistance), move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd * 0.85f, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete, set, fWKAngle, fWKAnglePlus, nWKNumSet, nWKSet);
				}
				else { return; } break;
			case BATK_CROSS://BOSS用　十字****************************************************************
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 4.0f, 50,
						0.0f, 0, 0.01f, 0.0f, 0.0f, 0.97f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_AROUND, fAngle, 0.0f, 2, 60);
				}
				else { return; } break;
			case BATK_BRANCH://BOSS用　枝分かれ****************************************************************
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら					
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 0, 0.01f, 0.0f, 0.01f, 0.97f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_BRANCHES, fAngle, 0.0f, 2, 20);
				}
				else { return; }
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//生成できたなら							
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle + D3DX_PI * 0.25f), 0.0f, cosf(fAngle + D3DX_PI * 0.25f)) * 1.0f, move, D3DXVECTOR3(0.0f, fAngle + D3DX_PI * 0.25f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 0, 0.01f, 0.0f, -0.01f, 0.97f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_BRANCHES, fAngle + D3DX_PI * 0.25f, 0.0f, 2, 20);
				}
				else { return; } break;
			case BATK_SPIN_0:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら		
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 2257, 0.5f, -0.0f, 0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; }
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら							
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 2257, 0.5f, -0.0f, -0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; } break;
			case BATK_SPIN_1:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら	
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 62257, 0.5f, -0.0f, 0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; }
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//生成できたなら	
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 62257, 0.5f, -0.0f, -0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; } break;
			}//switch()
		}//if()
	}//for()
}
//=============================================================================
// 初期速度設定処理
//=============================================================================
bool CSceneBullet::SetAttack(SET SetType , float fMaxLife, float fAngleSet, int nNumSet, D3DXVECTOR3 move, int nUV, int& nInterval)
{
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 *rot = GetRotation();
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();
	float fWKLengthX = fLengthX[0], fWKLengthZ = fLengthZ[0];
	float fCntState = GetfCntState()[0];
	float fWKAngle = rot[0].y;
	//if (fCntState < 0) { 0.0f; }
	CScenePairBulletSet *pPairBulletSet = NULL;
	CSceneNorBullet *bulletNor = NULL;
	CSceneSetBullet *bulletSet = NULL;

	float	fInitAngle = fAngleSet;
	float	fAngle = fAngleSet;
	float	fWKAngleU = fAngleSet;
	float	fWKLife;
	SET		WKset;
	CSceneBullet::CHANGE WKChange;

	switch (SetType)
	{
	case SET_NONE:	//置くだけ//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					-SHOT_LIFE + fCntState, 0, 0.0f, 0.01f, 0.0f, 0.5f, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		}break;
	case SET_TURN:	//回転込置くだけ//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move * 0.0f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					-SHOT_LIFE + fCntState, 2, 0.0f, 0.005f, 0.0f, 0.5f, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete);
			}else { return false; }
		}break;
	case SET_EFFECT:	//置くだけ//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら				
				bulletNor->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], 16 * 6 + (nUV % 16),
					SHOT_LIFE * 0.98f, 0, 0.0f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_NO, m_fAtk * 0.0625f, false, m_bShotDelete);
			}
			else { return false; }
		}break;
	case SET_EFFECT0:	//置くだけ//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら				
				bulletNor->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], 16 * 6 + (nUV % 16),
					SHOT_LIFE - (SHOT_LIFE - fMaxLife) * 0.3f, 0, 0.0f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_NO, m_fAtk * 0.0625f, false, m_bShotDelete);
			}
			else { return false; }
		} break;
	case SET_SHOT:	//発射//***********************************************************************
	case SET_SHOT2:	//発射//***********************************************************************
	case SET_NEEDLE:	//発射//***********************************************************************
		switch (SetType)
		{
		case SET_SHOT:		fWKLife = SHOT_LIFE * 0.25f; WKChange = CSceneBullet::CHANGE_FAST2; break;
		case SET_SHOT2:		fWKLife = SHOT_LIFE * 0.25f; WKChange = CSceneBullet::CHANGE_FAST; break;
		case SET_NEEDLE:	fWKLife = SHOT_LIFE * 0.25f; WKChange = CSceneBullet::CHANGE_FAST2; fWKLengthZ *= 1.5f;	break;
		}
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWKLengthX, fWKLengthZ, nUV,
					fWKLife, 0, 0.01f, 0.0f, 0.0f, 0.97f, WKChange, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_BEAM:	//発射//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//生成できたなら
				bulletSet->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move * 0.0f, D3DXVECTOR3(0.0f, fInitAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					SHOT_LIFE * 0.85f, 0, m_fSpeed, 0.0f, 0.0f, m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete, CSceneBullet::SET_EFFECT, fAngle, 0.0f, 1, 1);
			}
			else { return false; }
		}break;
	case SET_RELEASE:	//発射//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, nUV,
					-(SHOT_LIFE - fMaxLife), 0, m_fSpeed, 0.0f, 0.0f, m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_RANDSHOT:	//発射//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				fWKAngleU = fAngle;
				fWKAngleU += -D3DX_PI * ((1.0f * 0.33f) * 0.5f);
				fWKAngleU += D3DX_PI * ((rand() % (int)((1.0f * 0.33f) * 1000.0f)) * 0.001f);
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fWKAngleU, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, nUV,
					SHOT_LIFE * 0.5f, 0, 0.01f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		}break;
	case SET_BACK_G://真後ろ重力//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++)
		{//回数分
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, fInitAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					0.0f, 0, 0.02f, 0.0f, m_fTurning, 0.98f, CSceneBullet::CHANGE_GRAVITY, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_BACK_G2://真後ろ重力//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++)
		{//回数分
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fInitAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					0.0f, 0, 0.02f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_GRAVITY2, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_FIRE0:
		if (SceneCreate(bulletSet, BULLET_PRIORITY))
		{//生成できたなら
			bulletSet->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move * 0.0f, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], 48 + (nUV % 16),
				fCntState, 0, 0.0f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_NO, m_fAtk * 0.5f, false, m_bShotDelete, CSceneBullet::SET_FIRE, fAngle, 0.0f, 1, 20);
		} else { return false; }
	case SET_FIRE:
		for (int nCount = 0; nCount < nNumSet; nCount++)
		{//回数分
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				fWKAngle = rot[0].y +  D3DX_PI - D3DX_PI * ((1.0f * 0.2f) * 0.5f);
				fWKAngle += D3DX_PI * ((rand() % (int)((1.0f * 0.2f) * 1000.0f)) * 0.001f);
				bulletNor->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(rot[0].y), 0.0f, cosf(rot[0].y)) * (fLengthZ[0] * 0.5f) + D3DXVECTOR3(sinf(fWKAngle), 0.0f, cosf(fWKAngle)) * (fLengthZ[0] * 0.5f)
					, move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0] * 0.5f, fLengthX[0] * 1.0f, 48 + (nUV % 16),
					SHOT_LIFE - 60, 0, 0.01f + ((rand() % 100) * 0.01f) * 0.005f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_FAST2, m_fAtk * 0.25f, false, m_bShotDelete);
			} else { return false; }
		}break;
	case SET_CROSS:	//十字発射//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, 4.0f, nUV,
					0.0f, 0, 0.01f, 0.0f, 0.0f, 0.97f, CSceneBullet::CHANGE_FAST, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		}
	case SET_AROUND:	//左右//***********************************************************************
		fAngle = rot[0].y - D3DX_PI * 0.5f;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], 50,
					fCntState + 1, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
		//=============================================================================
		// 起動時消滅
		//=============================================================================
	case SET_DIFFUSION:	//ばら撒いて散る//***********************************************************************
	case SET_DIFFUSION2:	//ばら撒いて散る//***********************************************************************
		if (SET_DIFFUSION2 == SetType) { fWKLife = SHOT_LIFE * 0.5f; }
		else { fWKLife = SHOT_LIFE * 0.75f; }
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//生成できたなら
				bulletNor->Set(m_shot, GetPosition()[0], move * 0.0f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], nUV,
					fWKLife, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete);
			}
			else { return false; }
		}GetfCntState()[0] = SHOT_LIFE;
	case SET_PDIFFUSION:	//ばら撒いて散る//***********************************************************************
	case SET_PDIFFUSION2:	//ばら撒いて散る//***********************************************************************
		fAngle = rot[0].y;
		if (SET_PDIFFUSION2 == SetType) { fWKLife = SHOT_LIFE * 0.5f; WKset = SET_DIFFUSION2; }
		else { fWKLife = SHOT_LIFE * 0.75f; WKset = SET_DIFFUSION; }
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//生成できたなら
				bulletSet->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], nUV,
					fWKLife, 0, m_fSpeed, 0.0f, m_fTurning + D3DX_PI * 0.05f * ((nCount % 2) * 2 - 1), m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete, WKset, fAngle, 0.0f, 5, 60);
			}
			else { return false; }
		}
	case SET_BRANCH:	//十字発射//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//回転値プラス
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//生成できたなら
				bulletSet->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], 50,
					fCntState + 1, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete, SET_BRANCHES, fAngle, 0.0f, 2, 60);
			} else { return false; }
		}
	case SET_BRANCHES:	//枝分かれ//***********************************************************************
		if (fCntState < SHOT_LIFE * 0.5f)
		{
			nInterval *= 5;
			rot[0].y -= D3DX_PI * 0.2f;
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//生成できたなら
				bulletSet->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], 50,
					fCntState + 1, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete, SET_BRANCHES, fAngle, 0.0f, 2, 60);
			} else { return false; }
		}
	}

	return false;
}
//=============================================================================
// 弾削除処理
//=============================================================================
void	CSceneBullet::BreakBullet(bool bAll)
{
	CScene **PScene = CScene::GetScene(BULLET_PRIORITY);
	for (int nCount = 0; nCount < CScene::GetnMemoryAll(BULLET_PRIORITY); nCount++)
	{
		if (PScene[nCount] != NULL)
		{
			if (PScene[nCount]->GetObjType() >= CScene::OBJTYPE_BULLET && PScene[nCount]->GetObjType() <= CScene::OBJTYPE_BULLET3)
			{
				CSceneBullet* pBullet = (CSceneBullet*)PScene[nCount];
				if (!bAll)
				{//全部でない
					if (pBullet->GetbShotDelete() != NULL)
					{//NULLでない
						if (!pBullet->GetbShotDelete()[0])
						{//親がfalseなら
							pBullet->GetfCntState()[0] = SHOT_LIFE - 1;
						}
					}
				}
				else
				{//全部消す！
					if (pBullet->GetObjType() != CScene::OBJTYPE_BULLET3)
					{
						pBullet->GetfCntState()[0] = SHOT_LIFE - 1;
					}
				}
			}
		}//if(!=NULL)
	}//for()
}
//=============================================================================
// 円形弾削除処理
//=============================================================================
void	CSceneBullet::CircleBreak(D3DXVECTOR3 pos, float fLength, SHOT shot1, SHOT shot2)
{
	CScene **PScene = CScene::GetScene(BULLET_PRIORITY);
	for (int nCount = 0; nCount < CScene::GetnMemoryAll(BULLET_PRIORITY); nCount++)
	{
		if (PScene[nCount] != NULL)
		{
			if (PScene[nCount]->GetObjType() == CScene::OBJTYPE_BULLET)
			{
				CSceneBullet* pBullet = (CSceneBullet*)PScene[nCount];
				if (pBullet->GetShot()[0] != shot1 && pBullet->GetShot()[0] != shot2)
				{//自分の弾でないなら
					D3DXVECTOR3 *Bulletpos = pBullet->GetPosition();
					float		fBulletX = pBullet->GetfLengthX()[0], fBulletZ = pBullet->GetfLengthZ()[0];
					float fAngle;
					float fWKAngle;
					float fRangeBullet;
					float fDistance;
					float fPercentX, fPercentY;

					//距離計算
					fDistance = powf(pos.x - Bulletpos[0].x, 2) + powf(pos.z - Bulletpos[0].z, 2);

					//弾の範囲計算
					fAngle = atan2f(pos.x - Bulletpos[0].x, pos.z - Bulletpos[0].z);//角度計算
					fWKAngle = fAngle - pBullet->GetRotation()[0].y;
					fPercentX = (sinf(fWKAngle) * 1.0f) * (fBulletZ / fBulletX);
					fPercentY = (cosf(fWKAngle) * 1.0f);
					fAngle = atan2f(fPercentX, fPercentY);

					fRangeBullet = powf(sinf(fAngle) * fBulletX, 2) + powf(cosf(fAngle) * fBulletZ, 2);

					if (fDistance < fRangeBullet + (fLength * fLength))
					{//範囲内なら削除
						pBullet->GetfCntState()[0] = SHOT_LIFE;
					}
				}
			}
		}//if(!=NULL)
	}//for()
}