//=============================================================================
//
// モーション処理 [motion.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS			//Fire Wall突破
#include <stdio.h>						//インクルドファイル
#include "main.h"
#include "motion.h"
#include "clothing.h"
#include "player.h"
#include "SceneModel.h"
#include "3DGage.h"
#include "mesh.h"
#include "Effect.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_ATKCHECK	(200.0f * 200.0f)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CVtxInfo					*CCharParts::m_pVtxInfo[CCharParts::PARTS_MAX] = {};			//頂点情報
CCharacter::MODEL_PARTS		*CCharacter::m_partsAll[CCharParts::PARTS_MAX] = {};	//パーツ情報
int							CMotion::m_nNumMotion = 0;				//モーション数
CMotion						**CMotion::m_pMotion = NULL;				//モーション情報

//=============================================================================
// モーションの初期化
//=============================================================================
void	CMotion::Load(void)
{
	FILE *pFile;
	char aStr[8][32];
	m_nNumMotion = 0;
	int nNumMotion = 0;
	m_pMotion = NULL;

	//モーションの読み込み----------------------------------------------------------
	int nCntMotion[3];
	CKey *pKey;
	CAtkKey *pAtkKey;
	COneMotion *pMotion;

	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)//Load
	{//成功
		fscanf(pFile, "%d", &nCntMotion[0]);//ファイル数
		m_nNumMotion = nCntMotion[0];
		m_pMotion = new CMotion*[m_nNumMotion];	//モーション全体個数生成
		for (int nCntP = 0; nCntP < m_nNumMotion; nCntP++) { m_pMotion[nCntP] = new CMotion; }

		for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
		{
			fscanf(pFile, "%s", &aStr[nCntChar][0]);//ファイル名
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "%s 読み込み\n", &aStr[nCntChar][0]);
		}

		fclose(pFile);
	}
	else
	{//失敗
		MessageBox(0, "モーション", "motion.txt無し！", MB_OK);
	}

	for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
	{
		pFile = fopen(&aStr[nCntChar][0], "r");
		if (pFile != NULL)//Load
		{//モーションファイルLoad
			fscanf(pFile, "%d %d\n", &nNumMotion, &m_pMotion[nCntChar]->m_nMaxParts);//モーション数 パーツ数
			m_pMotion[nCntChar]->m_nMaxMotion = nNumMotion;
			//生成
			m_pMotion[nCntChar]->GetOneMotion() = new COneMotion[nNumMotion];

			for (int nCnt0 = 0; nCnt0 < nNumMotion; nCnt0++)
			{//モーション数回転
				pMotion = &m_pMotion[nCntChar]->GetOneMotion()[nCnt0];
				fscanf(pFile, "%d", &pMotion->GetnMaxKey());

				//キー生成
				pMotion->GetKey() = new CKey*[pMotion->GetnMaxKey()];

				//キーTYPE生成
				pMotion->GetType() = new CKey::TYPE[pMotion->GetnMaxKey()];

				fscanf(pFile, "%d %d %d %d %d %d %d %d %f\n", 
					&pMotion->GetnNorBranch(),
					&pMotion->GetnLandBranch(),
					&pMotion->GetnStartCancel(0),
					&pMotion->GetnStartCancel(1),
					&pMotion->GetnEndCancel(0),
					&pMotion->GetnEndCancel(1),
					&pMotion->GetnOtherCancel(0),
					&pMotion->GetnOtherCancel(1),
					&pMotion->GetfWaitTime()
				);
				pMotion->GetfWaitTime() *= FRAME_SPEED;	//待ち時間を補正
				for (int nCnt1 = 0; nCnt1 < pMotion->GetnMaxKey(); nCnt1++)
				{//キー数回転
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d", &pMotion->GetType()[nCnt1]);//モーション数 パーツ数

					switch (pMotion->GetType()[nCnt1])
					{//キーTYPE　生成したけど中身入ってない
					case CKey::TYPE_NORMAL: pMotion->GetKey()[nCnt1] = new CKey;  break;
					case CKey::TYPE_ATTACK: pMotion->GetKey()[nCnt1] = new CAtkKey;  break;
					}
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d %d %d %d %f %f\n",
						&pKey->GetnMoveType(),
						&pKey->GetnFloating(),
						&pKey->GetnFrame(),
						&pKey->GetnMaxEffect(),
						&pKey->GetfMove(),
						&pKey->GetfSlip()
					);//モーション数 パーツ数

					  //エフェクト枠生成
					pKey->GetpEffect() = new int[pKey->GetnMaxEffect()];

					  //角度枠生成
					pKey->GetpRot() = new D3DXVECTOR3[m_pMotion[nCntChar]->m_nMaxParts];

					fscanf(pFile, "%f %f %f\n", &pKey->GetMove().x,
						&pKey->GetMove().y,
						&pKey->GetMove().z);
					for (int nCnt2 = 0; nCnt2 < m_pMotion[nCntChar]->m_nMaxParts; nCnt2++)
					{//パーツ数回転
						fscanf(pFile, "%f %f %f\n", &pKey->GetpRot()[nCnt2].x,
							&pKey->GetpRot()[nCnt2].y,
							&pKey->GetpRot()[nCnt2].z);
					}
					{//パーツ数回転
						fscanf(pFile, "%f %f %f\n", &pKey->GetPos().x,
							&pKey->GetPos().y,
							&pKey->GetPos().z);
					}

					for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
					{//パーツ数回転
						fscanf(pFile, "%d ", &pKey->GetpEffect()[nCount]);
					}

					if (pMotion->GetType()[nCnt1] == CKey::TYPE_ATTACK)
					{
						pAtkKey = (CAtkKey*)pKey;
						fscanf(pFile, "%d %d %d %d %d\n", 
							&pAtkKey->GetnAtkType(),
							&pAtkKey->GetnAtkParts(),
							&pAtkKey->GetnCntAtk(),
							&pAtkKey->GetnHitFrame(0),
							&pAtkKey->GetnHitFrame(1));

						fscanf(pFile, "%f %f\n", &pAtkKey->GetfRange(),
							&pAtkKey->GetfAtkplus()
						);
					}
				}
			}
			fclose(pFile);
		}
		else
		{//失敗
			MessageBox(0, "モーションデータ", "無いよ!?", MB_OK);
		}
	}
	CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "モーション読み込み完了 読み込んだモーション数:%d\n", m_nNumMotion);
}
//=============================================================================
// モーションの全終了
//=============================================================================
void CMotion::UnLoad(void)
{
	if (m_pMotion != NULL)
	{//モーションが読み込まれているなら
		for (int nCount = 0; nCount < m_nNumMotion; nCount++)
		{//生成されたモーション分回転
			if (m_pMotion[nCount] != NULL)
			{//モーションが生成されていれば解放
				m_pMotion[nCount]->Uninit();
			}
		}//初期化
		m_nNumMotion = 0;
		delete[] m_pMotion;
		m_pMotion = NULL;
	}
}
//=============================================================================
// モーションの終了
//=============================================================================
void CMotion::Uninit(void)
{
	if (m_OneMotion != NULL)
	{//モーションのが生成されていれば
		for (int nCount = 0; nCount < m_nMaxMotion; nCount++)
		{//モーション分回転
			m_OneMotion[nCount].Uninit();
		}//初期化
		m_nMaxMotion = 0;
		delete[] m_OneMotion;
		m_OneMotion = NULL;
	}
}
//=============================================================================
// 一つのモーション終了
//=============================================================================
void COneMotion::Uninit(void)
{
	if (m_Key != NULL)
	{//キーが生成されていれば
		for (int nCount = 0; nCount < m_nMaxKey; nCount++)
		{//キー分回転
			if (m_Key[nCount] != NULL)
			{//生成されていれば削除
				m_Key[nCount]->Uninit();
			}
		}//初期化
		m_nMaxKey = 0;
		delete[] m_Key;
		m_Key = NULL;
	}
}
//=============================================================================
// キーの終了
//=============================================================================
void CKey::Uninit(void)
{
	if (m_pRot != NULL)
	{//角度が生成されていれば
		delete[] m_pRot;		//1つだったらやばいかも
		m_pRot = NULL;
	}
	if (m_pEffect != NULL)
	{//効果が生成されていれば
		delete[] m_pEffect;		//1つだったらやばいかも
		m_pEffect = NULL;
	}
}

//=============================================================================
// パーツの読み込み 列挙
//=============================================================================
LPD3DXMESH CCharacter::Load(CCharParts::PARTS parts)
{
	if (m_partsAll[parts] != NULL)
	{
		int nLength = (int)strlen(&m_partsAll[parts]->aText[0]);		//文字数確認

		if (nLength > 1)
		{
			D3DXLoadMeshFromX(&m_partsAll[parts]->aText[0],
				D3DXMESH_SYSTEMMEM, CManager::GetRenderer()->GetDevice(), NULL, &m_partsAll[parts]->pBuffMatModel, NULL, &m_partsAll[parts]->nNumMatModel, &m_partsAll[parts]->MeshModel);
			
			BYTE *pVtxBuff;
			int nNumVtx = m_partsAll[parts]->MeshModel->GetNumVertices();
			DWORD sizeFvF;	//頂点フォーマットのサイズ
			sizeFvF = D3DXGetFVFVertexSize(m_partsAll[parts]->MeshModel->GetFVF());

			if (m_partsAll[parts]->pPos == NULL)
			{//位置情報の頂点を生成
				m_partsAll[parts]->pPos = new D3DXVECTOR3[nNumVtx];

				m_partsAll[parts]->MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{
					m_partsAll[parts]->pPos[nCntVtx] = ((D3DXVECTOR3*)pVtxBuff)[0];
					pVtxBuff += sizeFvF;
				}
				m_partsAll[parts]->MeshModel->UnlockVertexBuffer();
			}

			strcpy(&m_partsAll[parts]->aText[0], "");

			//テクスチャ確認
			CScene::Load(m_partsAll[parts]->tex);
		}
	}
	switch (parts)
	{//パーツごとに頂点情報読み込み
	case CCharParts::TEST_000:	CCharParts::LoadVtx(CCharParts::TEST_000, "data/TEXT/Vtx/Vtx_Box.txt"); break;
	case CCharParts::BOX_100:	CCharParts::LoadVtx(CCharParts::BOX_100, "data/TEXT/Vtx/Vtx_Box100.txt"); break;
	}
	return m_partsAll[parts]->MeshModel;
}
//=============================================================================
// パーツの読み込み 文字列
//=============================================================================
void CCharacter::Load(void)
{
	FILE	*pFile;
	int		nNumParts = 0;
	//int nLength;		//文字数確認

	pFile = fopen("data/TEXT/model.txt", "r");

	if (pFile != NULL)//Load
	{//成功
		for (int nCountData = 0; nCountData < CCharParts::PARTS_MAX; nCountData++)
		{// Xファイルの読み込み
			if (m_partsAll[nCountData] == NULL) { m_partsAll[nCountData] = new CCharacter::MODEL_PARTS; }
			//nLength = (int)strlen(&m_partsAll[nCountData]->aText[0]);
			//if (nLength < 5)
			{
				fscanf(pFile, "%s\n", &m_partsAll[nCountData]->aText[0]);	//ファイル名
				fscanf(pFile, "%d\n", &m_partsAll[nCountData]->tex);		//画像
				//fscanf(pFile, "%f %f %f", &m_partsAll[nCountData]->addPos.x, &m_partsAll[nCountData]->addPos.y, &m_partsAll[nCountData]->addPos.z);//場所
				m_partsAll[nCountData]->pPos = NULL;
				if (m_partsAll[nCountData]->tex == -1) { m_partsAll[nCountData]->tex = CScene::TEX_MAX; }
				else { m_partsAll[nCountData]->tex = (CScene::TEXTURE)((int)TEX_CHAR + (int)m_partsAll[nCountData]->tex); }
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// パーツの終了
//=============================================================================
void CCharacter::UnLoad(void)
{
	for (int nCount = 0; nCount < CCharParts::PARTS_MAX; nCount++)
	{//パーツ分回る
		if (m_partsAll[nCount] != NULL)
		{//パーツが生成されていれば解放
				
			if (m_partsAll[nCount]->MeshModel != NULL)
			{// メッシュの開放
				m_partsAll[nCount]->MeshModel->Release();
				m_partsAll[nCount]->MeshModel = NULL;
			}

			if (m_partsAll[nCount]->pBuffMatModel != NULL)
			{// マテリアルの開放
				m_partsAll[nCount]->pBuffMatModel->Release();
				m_partsAll[nCount]->pBuffMatModel = NULL;
			}

			if (m_partsAll[nCount]->pPos != NULL)
			{//頂点情報解放
				delete[] m_partsAll[nCount]->pPos;
			}

			delete m_partsAll[nCount];
			m_partsAll[nCount] = NULL;
		}
	}
}
//=============================================================================
//攻撃チェック 全体から
//=============================================================================
void CCharacter::AtkCollision(void)
{
	CScene *pSceneAtk;
	CScene *pSceneDef;

	pSceneAtk = CScene::GetTop(CHAR_PRIORITY);
	while (pSceneAtk != NULL)
	{//終わるまで
		if (pSceneAtk->GetObjType() == OBJTYPE_PLAYER || pSceneAtk->GetObjType() == OBJTYPE_ENEMY)
		{//キャラ発見
			CCharacter *pAtk = (CCharacter*)pSceneAtk;
			COneMotion	*pOneMotion = &CMotion::GetMotion(pAtk->GetType())->GetOneMotion()[pAtk->GetnNumMotion(0)];
			if (pOneMotion->GetType()[pAtk->GetnNumMotion(2)] == CKey::TYPE_ATTACK)
			{//攻撃のキーである
				CAtkKey		*pKey = (CAtkKey*)pOneMotion->GetKey()[pAtk->GetnNumMotion(2)];

				if (pAtk->m_fFrame - (pAtk->m_fSumFrame / FRAME_SPEED) == 0.0f)
				{//攻撃開始時
					bool bOrbit = true;

					if (pAtk->GetnNumMotion(2) > 0) 
					{//前のキーがある
						if (pOneMotion->GetType()[pAtk->GetnNumMotion(2) - 1] == CKey::TYPE_ATTACK)
						{//前のキーが攻撃モーションなら
							bOrbit = false;	//軌跡生成ダメ
						}
					}

					if (bOrbit)
					{//軌跡が生成しても良いなら
						CManager::GetSound()->Play(CSound::LABEL_ATTACK000);
						CMeshOrbit *pOrbit;
						D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
						pAtk->AtkVoice();

						if (SceneCreate(pOrbit, ORBIT_PRIORITY))
						{//メッシュオービット生成
							pOrbit->Set(pAtk->GetpParts()[0]->GetBone()[20].GetMtx(), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, (pKey->GetfRange() * 0.5f) * pKey->GetnCntAtk(), 0.0f), pAtk->GetbOrbit(), col, CScene::TEX_Orbit);
							pOrbit->GetDrawType() = CScene::DRAW_TYPE_SUBTRACT;
						}
						CLineEffect *pEffect;
						if (SceneCreate(pEffect, SLEffect_PRIORITY))
						{
							pEffect->Set(pAtk->GetpParts()[0]->GetBone()[20].GetMtx(), D3DXVECTOR3(0.0f, (pKey->GetfRange() * 0.5f) * pKey->GetnCntAtk(), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, pAtk->m_bOrbit, CLineEffect::TYPE_FIRE);
						}
					}
				}

				if ((float)pKey->GetnHitFrame(0) <= pAtk->m_fFrame && (float)pKey->GetnHitFrame(1) >= pAtk->m_fFrame)
				{//攻撃の判定フレームである
					pSceneDef = CScene::GetTop(CHAR_PRIORITY);
					while (pSceneDef != NULL)
					{//終わるまで
						if (pSceneAtk != pSceneDef)
						{//同じキャラ出ない
							if (pSceneDef->GetObjType() == OBJTYPE_PLAYER || pSceneDef->GetObjType() == OBJTYPE_ENEMY)
							{//キャラ発見
								HitCheck(pSceneAtk, pSceneDef);	//お互いにヒットチェック
							}
						}
						pSceneDef = pSceneDef->GetpNext();
					}//判定
				}//if(攻撃F範囲内)
			}//if(攻撃)
		}//if(キャラ)
		pSceneAtk = pSceneAtk->GetpNext();
	}//while(NULL)

	//弾判定

	//ヒットチェック
	HitMotionAll();
}
//=============================================================================
//攻撃チェック 単体から
//=============================================================================
void CCharacter::HitCheck(CScene *&pAtkChar, CScene *&pDefChar)
{
	//キャラクター型に変換
	CCharacter *pAtk = (CCharacter*)pAtkChar;
	CCharacter *pDef = (CCharacter*)pDefChar;
	
	if(pDef->m_nInvincible == 0 && (pAtk->m_Team != pDef->m_Team || pAtk->m_Team == TEAM_IGNORED))
	{//無敵、チーム確認
		//攻撃状態確認　違うならリターン
		COneMotion *pMotion = &CMotion::GetMotion(pAtk->GetType())->GetOneMotion()[pAtk->GetnNumMotion(0)];
		if (pMotion->GetType()[pAtk->GetnNumMotion(2)] != CKey::TYPE_ATTACK) { return; }

		//位置取得
		D3DXVECTOR3 &Atkpos = pAtk->Getpos();
		D3DXVECTOR3 &Defpos = pDef->Getpos();

		//距離チェック
		if (powf(Atkpos.x - Defpos.x, 2) + powf(Atkpos.z - Defpos.z, 2) < MAX_ATKCHECK)
		{//範囲内
			CAtkKey		*pKey = (CAtkKey*)pMotion->GetKey()[pAtk->GetnNumMotion(2)];	//キー取得
			D3DXMATRIX	mtxTrans, mtxWK;		//計算用マトリックス
			D3DXVECTOR3	&length = pDef->Getlength();
			float		&fRange = pKey->GetfRange();
			float		fValid = 1.0f;
			float		fRot;

			//状態によってY有効値変更
			if (pDef->GetnNumMotion(MOTION_BLOW)) { fValid = 1.25f; }
			else if (!pDef->GetbJump()) { fValid = 0.5f; }

			mtxWK = pAtk->GetpParts()[0]->GetmtxWorld(pKey->GetnAtkParts());	//親のマトリックスを取得
			D3DXMatrixTranslation(&mtxTrans, 0.0f, fRange * 2.0f, 0.0f);	//範囲分移動値計算

			for (int nCntAtk = 0; nCntAtk < pKey->GetnCntAtk(); nCntAtk++)
			{//for(攻撃回数分回転)
				if (nCntAtk != 0)
				{// 移動を反映
					D3DXMatrixMultiply(&mtxTrans, &mtxTrans, &mtxWK);
					mtxWK = mtxTrans;
				}

				if (mtxWK._42 - fRange < Defpos.y + length.y * fValid && mtxWK._42 + fRange > Defpos.y - length.y * fValid)
				{//if(Yが範囲内)
					if (powf(mtxWK._41 - Defpos.x, 2) + powf(mtxWK._43 - Defpos.z, 2) < fRange * fRange)
					{//if(XZが範囲内)
						if (pAtk->CheckHitChar(pDefChar))
						{//ヒット確認
							CSound *&pSound = CManager::GetSound();

							int nHitType = 0;
							float fHit = 1.0f;
							float fDamage;
							bool  bMotion = false;
							bool  bHit = true;

							CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "ヒット\n");

							//ヒット時情報
							if (pDef->m_nNumMotion[0] == MOTION_DOWN) 
							{
								bMotion = true;
								fHit *= 1.3f; nHitType = 1;
								pSound->Play(CSound::LABEL_CRITICAL);
							}
							else
							{//相手がダウンでない
								switch (pDef->m_state)
								{//状態によってヒット時処理変更
								case STATE_NONE:  bMotion = true; pDef->m_col.a = 0.0f; pSound->Play(CSound::LABEL_HIT000); break;
								case STATE_ARMOR: nHitType = 2; pDef->m_col.a = 0.75f; break;
								case STATE_AVOID: nHitType = 5; fHit = 0.0f; bHit = false; break;
								case STATE_GUARD:
									pDef->UseStamina(10.0f * pKey->GetfAtkplus());
									if (pDef->m_fStamina >= 0)
									{//ガード成功
										pSound->Play(CSound::LABEL_GUARD);
										nHitType = 3; fHit = 0.2f;
										pDef->m_state = STATE_CANCEL;
										pDef->SetNextMotion(MOTION_GUARD2);
									}
									else
									{//ガードブレイク
										bMotion = true; pDef->m_col.a = 0.0f; pSound->Play(CSound::LABEL_HIT000);
									}
									break;
								case STATE_PARIS:
									pSound->Play(CSound::LABEL_PARIS);
									nHitType = 4; fHit = 0.0f;
									pDef->m_state = STATE_CANCEL;
									pAtk->m_state = STATE_CANCEL;
									pDef->SetNextMotion(MOTION_NEUTRAL);
									pAtk->SetNextMotion(MOTION_PARIS2);
									break;
								}
							}//else 相手がダウンでない

							if (bHit)
							{//通常通りのヒット判定なら
								CSceneAnim3D	*pAnim;
								//CScene3D		*p3D;
								//ヒット時受け側の角度補正
								fRot = pAtk->Getrot().y + D3DX_PI;
								if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2; }
								if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2; }
								pDef->Getrot().y = fRot;
								pDef->m_fFramePlus = 1.0f;
								pDef->m_fFramePlus2 = 0.0f;
								pAtk->m_fFramePlus = 0.0f;
								if (fHit >= 1.0f) { pDef->DefVoice(); }
								//エフェクト
								if (SceneCreate(pAnim, S3D_PRIORITY))
								{
									pAnim->Set(pDef->Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f),
										D3DXVECTOR3(15.0f, 15.0f, 0.0f), CScene::TEX_HIT0, true, CScene::DRAW_TYPE_ZADD, 0, 5, 2, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
								}
								if (SceneCreate(pAnim, S3D_PRIORITY))
								{
									pAnim->Set(pDef->Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f),
										D3DXVECTOR3(80.0f, 80.0f, 0.0f), CScene::TEX_HIT1, true, CScene::DRAW_TYPE_ZOVERLAY, 0, 5, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
								}
								//if (SceneCreate(p3D, S3D_PRIORITY + 2))
								//{
								//	p3D->Set(pDef->Getpos() + D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								//		D3DXVECTOR3(75.0f, 30.0f, 0.0f), CScene::TEX_HitLogo, nHitType, 1, 7, true, CScene::DRAW_TYPE_NORMAL);
								//	p3D->GetState() = CScene3D::STATE_HIT; p3D->GetfCntState() = 0.01f;
								//}
								pDef->SetLightCol(D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f));
								pAtk->SetLightStr( 0.5f, 30.0f);
							}
							fDamage = pAtk->m_fAtk * pKey->GetfAtkplus() * fHit;
							pDef->m_fLife -= fDamage;
							pAtk->m_fSP += (fDamage * 0.05f) * fHit;

							if (pAtk->m_fSP > pAtk->m_fMaxSP) { pAtk->m_fSP = pAtk->m_fMaxSP; }
							Atkpos.y += (Defpos.y - Atkpos.y) * 0.05f;
							if (pDef->m_fLife <= 0.0f)
							{//死んだ
								pDef->Dead();
								pDef->SetNextMotion(MOTION_DOWN);
								pDef->m_state = STATE_CANCEL;
								//経験値等
							}
							else if (bMotion)
							{//状態でモーション変更が可能なら
								if (pKey->GetnAtkType() == CAtkKey::ATK_TYPE_SMASH) 
								{ pDef->SetNextMotion(MOTION_BLOW); pDef->m_state = STATE_CANCEL; }
								else if (pDef->m_nNumMotion[0] != MOTION_BLOW && pDef->m_nNumMotion[0] != MOTION_DOWN)
								{//吹っ飛びでもダウンでもない
									if (pDef->m_nCntDamage > 0 || !pDef->GetbJump()) { pDef->SetNextMotion(MOTION_BLOW); pDef->m_state = STATE_CANCEL; }
									else { pDef->SetNextMotion(MOTION_DESPONDENCY); pDef->m_state = STATE_CANCEL; }

									if (pKey->GetnAtkType() == CAtkKey::ATK_TYPE_NORMAL) { pDef->m_nCntDamage = 120 * FRAME_SPEED; }
								}
							}
							//else if (pDef->m_nNumMotion[0] == MOTION_BLOW) { pDef->Getmove().y = 2.0f; }
						}//if(ヒット確認)
					}//if(XZが範囲内)
				}//if(Yが範囲内)
			}//for(攻撃回数分回転)
		}//if(距離チェック)
	}//if(無敵でないなら)
}
//=============================================================================
//ヒット後モーション更新
//=============================================================================
void CCharacter::HitMotionAll(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_PLAYER || pScene->GetObjType() == OBJTYPE_ENEMY)
		{//キャラ発見
			((CCharacter*)pScene)->HitMotion();	//ヒットしたか確認
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//ヒット後モーション更新
//=============================================================================
void CCharacter::HitMotion(void)
{
	if (m_state == STATE_CANCEL)
	{//ヒットした
		SetCancelMotion(m_nNumMotion[1]);	//怯みやダウン等に変更
	}
	m_state = STATE_NONE;
}
//=============================================================================
//ヒットしていないか確認更新
//=============================================================================
bool CCharacter::CheckHitChar(CScene *&pChar)
{
	if (m_nCntHit < MAX_HITCHAR)
	{//まだヒットキャラを保存できるなら
		for (int nCount = 0; nCount < m_nCntHit; nCount++)
		{//保存されたキャラ分確認
			if (m_pHit[nCount] == pChar) { return false; }
		}

		if (m_nCntHit < MAX_HITCHAR)
		{//まだ保存できる
			m_pHit[m_nCntHit] = pChar;
			m_nCntHit++;
		}
		return true;
	}
	return false;
}
//=============================================================================
//ヒットしたキャラをリセット
//=============================================================================
void CCharacter::ReSetHitChar(void) 
{ 
	if (m_nCntHit > 0)
	{
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "リセット%d\n", m_nCntHit);
	}
	for (int nCount = 0; nCount < m_nCntHit; nCount++)
	{//保存分だけ削除
		m_pHit[nCount] = NULL;
	}
	m_nCntHit = 0;
}

//=============================================================================
// キャラクターの初期化
//=============================================================================
HRESULT CCharacter::Init(void)
{
	m_Team = TEAM_IGNORED;
	m_state = STATE_NONE;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_addpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addPosmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_length = D3DXVECTOR3(30.0f, 85.0f, 30.0f);
	m_FNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxParts = 0;
	m_pParts = NULL;
	m_bJump = false;
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_fFramePlus = 1.0f;
	m_fInitFrame = 0.0f;
	m_nLeg = 0;
	m_nCntReUse = -1;
	m_nCntDamage = 0;
	m_nInvincible = 0;
	m_fFrame = 0.0f;
	m_fMotionFrame = 0.0f;
	m_fKeepFrame = 0.0f;

	m_bOrbit = false;
	m_bBoost = false;
	m_pLockChar = NULL;
	m_pWaitMotion = NULL;
	m_pUseMotion = NULL;

	//ヒットしたキャラをリセット
	m_nCntHit = MAX_HITCHAR;
	ReSetHitChar();
	m_Voice = CSound::LABEL_MAX;

	//ステータスを初期化
	m_fMaxStamina = 200.0f;
	m_nLevel = 1;
	SetStatus();
	m_fCntStamina = 0.0f;

	//if (m_pGage == NULL)
	//{
	//	if (Create(m_pGage))
	//	{
	//		m_pGage->Set(m_pos, 50.0f, 1.5f, m_fLife, m_fMaxLife, C3DGage::STATE_LIFE);
	//	}
	//}
	return S_OK;
}
//=============================================================================
// キャラクターの終了
//=============================================================================
void CCharacter::Uninit(void)
{
	if (m_pGage != NULL) { m_pGage->Uninit(); m_pGage = NULL; }
	
	delete[] m_pWaitMotion;
	delete[] m_pUseMotion;
	if (m_pParts != NULL)
	{
		for (int nCount = 0; nCount < m_nMaxParts; nCount++)
		{
			m_pParts[nCount]->Uninit();
		}
		delete[] m_pParts; m_pParts = NULL;
	}
	CScene::Uninit();
}
//=============================================================================
// モーションへの指示
//=============================================================================
void CCharacter::DirectMotion(DIRECT Direct)
{
	if (Direct != DIRECT_NO)
	{
		if (Direct == DIRECT_ATTACK || Direct == DIRECT_ATTACK2)
		{//向きに応じて指示変更
			if (GetObjType() == OBJTYPE_PLAYER)
			{
				//入力方向によって
				CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
				int nAttack = (int)MOTION_ATTACK;

				if (Direct == DIRECT_ATTACK2) { nAttack += 3; }
				if (!m_bJump) { nAttack += 6; }
				if (Direct == DIRECT_ATTACK2 && !m_bJump) { nAttack += 1; }
				if (pInputPad->GetStickDefeat(0))
				{
					CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(((CPlayer*)this)->GetnID())->GetChar();

					float fRotPad = pInputPad->GetfStickAngle(0);
					float fRotCamera = pCamera->GetRot().y;

					if (Direct == DIRECT_ATTACK2)
					{//スキルならスティック状態によって攻撃の分岐
						if (D3DX_PI * 0.5f >= fRotPad && -D3DX_PI * 0.5f <= fRotPad)
						{
							int nData = pInputPad->GetnPress(INPUT_LS_D);
							int nData2 = pInputPad->GetnRelease(INPUT_LS_D);
							if (pInputPad->GetnRelease(INPUT_LS_D) > -20 &&
								pInputPad->GetnPress(INPUT_LS_D) < 0 && pInputPad->GetnPress(INPUT_LS_D) > -20) { SetNextMotion(MOTION_ATTACK + 13); return; }
						}
						else
						{
							if (pInputPad->GetnRelease(INPUT_LS_U) > -20 && 
								pInputPad->GetnPress(INPUT_LS_U) < 0 && pInputPad->GetnPress(INPUT_LS_U) > -20) { SetNextMotion(MOTION_ATTACK + 14); return; }
						}
					}

					if (D3DX_PI * 0.5f >= fRotPad && -D3DX_PI * 0.5f <= fRotPad) { SetNextMotion(nAttack + 1); pInputPad->NoInput(INPUT_LS_U); }
					else 
					{ AtkRot(m_fRot, ((CPlayer*)this)->GetnID()); SetNextMotion(nAttack + 2); pInputPad->NoInput(INPUT_LS_D); }
				}
				else { SetNextMotion(nAttack); }
				pInputPad->ReSetPress();
			}
		}
		else
		{//攻撃でない
			switch (Direct)
			{
			case DIRECT_SKILL1:	SetNextMotion(MOTION_ATTACK); break;
			case DIRECT_SKILL2:	SetNextMotion(MOTION_ATTACK); break;
			case DIRECT_JUMP:	SetNextMotion(MOTION_JUMP); break;
			case DIRECT_BOOST:	SetNextMotion(MOTION_BOOST); m_bBoost = true; break;
			case DIRECT_GUARD:	SetNextMotion(MOTION_GUARD); break;
			case DIRECT_PARIS:	SetNextMotion(MOTION_PARIS); break;
			}
		}
	}//if(指示有無)
}
//=============================================================================
// ニュートラル攻撃時　角度の変更処理
//=============================================================================
void	CCharacter::AtkRot(float &fRot, int &nID)
{
	CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(nID)->GetChar();
	float fAngle = fRot - pCamera->GetRot().y;

	if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	if (fAngle < -D3DX_PI * 0.55f || fAngle > D3DX_PI * 0.55f)
	{//カメラの向き通りなら
		fRot += D3DX_PI;
		if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
		if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2.0f; }
	}
}
//=============================================================================
// キャラクターの更新
//=============================================================================
void CCharacter::Update(bool bMove)
{
	CMotion::TYPE &nType = m_pParts[0]->GetMotion();
	D3DXVECTOR3 Vec2;
	//float fTilt;
	//float fRot;
	float fMove = 1.0f;
	bool bSpin = false;
	m_fSumFrame = m_fFramePlus + m_fFramePlus2;
	if (m_fStamina <= 0) { fMove = 0.3f; }

	//if (m_bJump == true)
	//{
	//	Vec2 = D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y));
	//	fTilt = (m_FNor.x * Vec2.x) + (m_FNor.y * Vec2.y) + (m_FNor.z * Vec2.z) /
	//		(sqrtf(powf(m_FNor.x, 2) + powf(m_FNor.y, 2) + powf(m_FNor.z, 2)) * sqrtf(powf(Vec2.x, 2) + powf(Vec2.y, 2) + powf(Vec2.z, 2)));
	//	fRot = acosf(fTilt);
	//	fTilt = (fTilt * -1.0f) * 2.0f;
	//	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "傾斜 %f\n", fTilt);
	//	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "角度 %f\n", fRot);
	//	//if (fTilt < 0.8f && fTilt < 1.2f) { fTilt = 0.0f; }
	//	//else { fTilt *= fTilt; }
	//}

	if (m_nNumMotion[0] <= MOTION_S_NEUTRAL)
	{//移動方向にモデルの向きを合わせる
		float fRotPoor = m_fRot - m_rot.y;
		if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
		else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
		m_rot.y += fRotPoor * 0.15f;
		if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
		if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
	}

	if (CManager::GetInputKey()->GetTrigger(DIK_Z)){ CCharacter::ResetMotion(); }
	if (CManager::GetInputKey()->GetTrigger(DIK_B)) { CancelLock(); }
	if (CManager::GetInputKey()->GetTrigger(DIK_N)) { SetPlusFrame(0.5f, 120.0f); }

	//モーションキャンセルの更新
	CancelUpdate();
	CMotion		*pMotion = CMotion::GetMotion(nType);
	COneMotion	*pOneMotion = &CMotion::GetMotion(nType)->GetOneMotion()[m_nNumMotion[0]];
	CKey		*pKey = pOneMotion->GetKey()[m_nNumMotion[2]];
	CKey		*pKeyold;
	int			&nMaxParts = pMotion->GetnMaxParts();

	if (bMove)
	{//移動
		if (m_nNumMotion[1] == -1 && m_bJump)
		{//モーションの予約がない
			COneMotion *pMotion = &CMotion::GetMotion(nType)->GetOneMotion()[m_nNumMotion[0]];
			if (pMotion->GetnOtherCancel(0) < m_fMotionFrame && m_fMotionFrame < pMotion->GetnOtherCancel(1))
			{
				m_nNumMotion[1] = MOTION_WALK;
			}
		}
		m_move += D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * -0.2f * m_fSumFrame * pKey->GetfMove() * fMove;
	}
	else if(m_nNumMotion[1] == -1)
	{//移動無し
		if (m_nNumMotion[0] == MOTION_WALK)
		{//歩きなら　足に合わせてニュートラルへ
			if(m_nNumMotion[2] % 3 == 0 && m_fFrame <= 2.0f){ m_nNumMotion[1] = MOTION_NEUTRAL; }
		}
	}

	//モーション
	if (nType != CMotion::TYPE_MAX)
	{
		D3DXVECTOR3 Move;
		ResetUpdate();		//攻撃モーション リセット更新

		while (1)
		{
			if (m_fFrame < (float)pKey->GetnFrame())
			{//フレームが範囲内なら
				m_move.x += (0.0f - m_move.x) * (0.3f * pKey->GetfSlip());
				m_move.z += (0.0f - m_move.z) * (0.3f * pKey->GetfSlip());
				SetEffect(pKey);	//キー効果

				//移動値加算有効フレームなら
				//if (m_fFrame < (float)pKey->GetnMoveType() * m_fSumFrame)
				//{
				//	float fRot = m_rot.y;
				//	Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//	Move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -pKey->GetMove().z;
				//	Move += D3DXVECTOR3(sinf(fRot + D3DX_PI * 0.5f), 0.0f, cosf(fRot + D3DX_PI * 0.5f)) * -pKey->GetMove().x;
				//	Move += Move * ((m_fSumFrame - 1.0f) * 0.35f);
				//	float fWKData = (float)pKey->GetnMoveType() / m_fSumFrame;
				//	if (fWKData < 1.0f) { fWKData = 1.0f; }
				//	else if (fWKData > m_fSumFrame) { fWKData = m_fSumFrame; }
				//	Move.y += pKey->GetMove().y * fWKData;
				//	
				//	if (pKey->GetMove().y > 0.0f)
				//	{
				//		m_bJump = false;
				//	}
				//	m_move += Move * fMove;
				//}

				m_addpos += m_addPosmove * m_fSumFrame;		//本体の移動
				for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
				{//保存されたmove分動かす
				D3DXVECTOR3 &addRot = m_pParts[0]->GetBone()[nCntModel].GetaddRot();
				 //rotの移動値加算
					addRot += m_pParts[0]->GetBone()[nCntModel].GetaddRotMove() * m_fSumFrame;
					//ロット確認
					if (addRot.x > D3DX_PI) { addRot.x -= D3DX_PI * 2; }
					else if (addRot.x < -D3DX_PI) { addRot.x += D3DX_PI * 2; }
					if (addRot.y > D3DX_PI) { addRot.y -= D3DX_PI * 2; }
					else if (addRot.y < -D3DX_PI) { addRot.y += D3DX_PI * 2; }
					if (addRot.z > D3DX_PI) { addRot.z -= D3DX_PI * 2; }
					else if (addRot.z < -D3DX_PI) { addRot.z += D3DX_PI * 2; }
				}
				//進撃のフレーム
				m_fFrame += m_fSumFrame / FRAME_SPEED;//フレームの進行
				m_fMotionFrame += m_fSumFrame / FRAME_SPEED; //モーション全体フレームの進行
				m_fKeepFrame += m_fSumFrame / FRAME_SPEED; //モーション継続フレームの進行
				break;
			}
			else
			{//キーの終了
				m_fFrame = 0.0f;	//フレームの初期化
				SetRotMotion();
				m_nNumMotion[2]++;		//キーの進撃

				if (m_nNumMotion[2] >= pOneMotion->GetnMaxKey())
				{//そのモーションが終了
					if (pOneMotion->GetnNorBranch() > -1)
					{
						m_fRot = m_rot.y;		//妙な回転防止
						m_fMotionFrame = 0.0f;	//全フレームの初期化
						m_fKeepFrame = 0.0f;	//継続Fの初期化
						m_nNumMotion[2] = 0;	//キーの初期化
						ReSetHitChar();			//ヒットキャラのリセット

						if (m_nNumMotion[0] != pOneMotion->GetnNorBranch())
						{//ループじゃなければ
							m_nNumMotion[0] = pOneMotion->GetnNorBranch();	//次のモーションの付与
							if (m_nNumMotion[0] == MOTION_NEUTRAL) 
							{ 
								if (!GetbJump()) { m_nNumMotion[0] = MOTION_S_NEUTRAL; }//空中ニュートラルへ
							}
							//if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_GETUP) { g_model_Info[nCount].set.nAirTime = 90; }	//起き上がりなら
						}
						else { m_nNumMotion[0] = pOneMotion->GetnNorBranch(); }//次のモーションの付与}
						m_nNumMotion[3] = m_nNumMotion[0]; //今のモーションに現在のモーションを入れる
					}
					else
					{//次のキー設定がされていないならそのまま放置
						m_fMotionFrame -= pOneMotion->GetKey()[pOneMotion->GetnMaxKey() - 1]->GetnFrame();	//モーションフレームを戻す
						m_nNumMotion[2]--;																	//キーを戻す
						m_fFrame = 0.0f;
					}
				}
				pOneMotion = &CMotion::GetMotion(nType)->GetOneMotion()[m_nNumMotion[0]];
				pKeyold = pKey;
				pKey = pOneMotion->GetKey()[m_nNumMotion[2]];

				m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
				for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
				{//moveを計算して代入
					D3DXVECTOR3 &addRot = m_pParts[0]->GetBone()[nCntModel].GetaddRot();
					D3DXVECTOR3 &addRotMove = m_pParts[0]->GetBone()[nCntModel].GetaddRotMove();
					addRot = pKeyold->GetpRot()[nCntModel];
					addRotMove = (pKey->GetpRot()[nCntModel] - addRot);

					//角度確認
					if (addRotMove.x > D3DX_PI) { addRotMove.x -= D3DX_PI * 2; }
					else if (addRotMove.x < -D3DX_PI) { addRotMove.x += D3DX_PI * 2; }
					if (addRotMove.y > D3DX_PI) { addRotMove.y -= D3DX_PI * 2; }
					else if (addRotMove.y < -D3DX_PI) { addRotMove.y += D3DX_PI * 2; }
					if (addRotMove.z > D3DX_PI) { addRotMove.z -= D3DX_PI * 2; }
					else if (addRotMove.z < -D3DX_PI) { addRotMove.z += D3DX_PI * 2; }

					addRotMove /= (float)pKey->GetnFrame() * FRAME_SPEED;
				}
			}//キー終了
		}//更新while
		m_fFramePlus += (1.0f - m_fFramePlus) * 0.1f;
		m_fInitFrame -= m_fFramePlus / FRAME_SPEED;
		if (m_fInitFrame < 0.0f)
		{//時間経過が完了した
			m_fInitFrame = 0.0f;
			m_fFramePlus2 += (0.0f - m_fFramePlus2) * 0.05f;
		}
	}

	//位置等の更新
	m_posold = m_pos;
	m_pos += m_move;
	//if (pKey->GetnFloating() < 2) { m_move.y -= 0.3f; }
	//if (pKey->GetnFloating() == 2) 
	//{ m_move.y = 0.0f; }

	int		nCount = 0;
	bool bLand = m_bJump;
	CMesh::MeshCollisionCeiling(m_pos, m_posold, m_length);											//メッシュ屋根
	CCharacter::CollisionAll(this);//キャラ同士当たり判定
	CSceneObjct::CollisionAll(m_pos, m_posold, m_move, m_length, m_FNor, nCount, bLand, true);	//オブジェクト
	nCount = 0;
	CMesh::MeshCollisionWall(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, false);	//メッシュ壁
	CMesh::MeshCollisionField(m_pos, m_posold, m_move, m_length, m_FNor, bLand);					//メッシュ床

	if (!m_bJump && bLand && pKey->GetnFloating() == 0)
	{//着地
		SetCancelMotion(pOneMotion->GetnLandBranch());
	}
		m_bJump = true;

	//その他の更新
	m_bBoost = false;
	m_bVtx = false;
	if (m_fLife <= 0)
	{//死んでいるなら
		m_nInvincible++;
		if (m_nInvincible > 180)
		{
			//自身へのロックオンを外す
			CancelLock();
			Over();
			return;
		}
	}
	else
	{//死んでいないなら
		if (m_col.a < 1.0f)
		{
			m_col.a += 0.005f;
			if (m_col.a > 1.0f) { m_col.a = 1.0f; }
		}
		if (m_nCntDamage > 0) { m_nCntDamage--; }		//ダメージ後吹っ飛びまでカウント
		if (m_nInvincible > 0) { m_nInvincible--; }		//無敵時間減少
	}
	if (m_pGage != NULL) { m_pGage->Update(); }
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "Pフレーム：%.3f\n", m_fSumFrame);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "モーション 現在：%d　次：%d キー：%d フレーム：%.1f\n", m_nNumMotion[0], m_nNumMotion[1], m_nNumMotion[2], m_fFrame);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "法線 %.1f　%.1f　%.1f\n", m_FNor.x, m_FNor.y, m_FNor.z);
}
//=============================================================================
// キャラクターの描画
//=============================================================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
	D3DXVECTOR3 pos = m_pos + m_addpos;
	D3DXMATRIX			mtxRot, mtxTrans;		//計算用マトリックス
	CScene::DRAW_TYPE DType = m_DrawType;
	bool				bShadow = false;
	if (m_nInvincible > 0) { DType = CScene::DRAW_TYPE_AER; }

		 // ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_Mtx);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_Mtx, &m_Mtx, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&m_Mtx, &m_Mtx, &mtxTrans);

		if (m_nInvincible > 0) { pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); bShadow = true; }

		for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
		{//パーツ分だけ回転
			m_pParts[nCntModel]->Draw(this);
		}
		m_bVtx = true;
}
//=============================================================================
// 死亡処理
//=============================================================================
void CCharacter::Dead(void)
{
	//エフェクト
	CSceneAnim3D	*pAnim;
	if (SceneCreate(pAnim, S3D_PRIORITY))
	{
		pAnim->Set(Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(20.0f, 20.0f, 0.0f), CScene::TEX_Dead, true, CScene::DRAW_TYPE_ZOVERLAY, 0, 5, 2, 4, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_FADESPIN);
	}
	//効果音
	CManager::GetSound()->Play(CSound::LABEL_DEAD);

	DeadVoice();
}
//=============================================================================
// 死亡処理
//=============================================================================
void CCharacter::Over(void)
{
	//エフェクト
	CSceneAnim3D	*pAnim;
	if (SceneCreate(pAnim, S3D_PRIORITY))
	{
		pAnim->Set(Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(150.0f, 150.0f, 0.0f), CScene::TEX_Over, true, CScene::DRAW_TYPE_ZOVERLAY, 0, 10, 1, 4, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
	}
	//効果音
	CManager::GetSound()->Play(CSound::LABEL_OVER);
	Uninit();
}
//=============================================================================
// 攻撃時発声処理
//=============================================================================
void CCharacter::AtkVoice(void)
{

}
//=============================================================================
// 被ダメ時発声処理
//=============================================================================
void CCharacter::DefVoice(void)
{

}
//=============================================================================
// 死亡時発声処理
//=============================================================================
void CCharacter::DeadVoice(void)
{

}
//=============================================================================
// モーションのキャンセル更新
//=============================================================================
void CCharacter::CancelUpdate(void)
{
	if (m_nNumMotion[1] != -1)
	{//予約が入っている && 現在のモーションでない
		if (CheckAtkNumber(m_nNumMotion[1]))
		{
			if (m_nNumMotion[0] != m_nNumMotion[1] || m_nNumMotion[1] == MOTION_GUARD)
			{
				COneMotion *pMotion = &CMotion::GetMotion(m_pParts[0]->GetMotion())->GetOneMotion()[m_nNumMotion[0]];
				bool bCancel = false;
				bool bStart = false;

				if (m_nNumMotion[1] == MOTION_BLOW || m_nNumMotion[1] == MOTION_DESPONDENCY)
				{//怯み、ダウンは無視
					bCancel = true;
				}
				if (m_nNumMotion[0] == MOTION_GUARD)
				{//ガード中 ガード、パリィは無視
					if (m_nNumMotion[1] == MOTION_GUARD || m_nNumMotion[1] == MOTION_PARIS) { bCancel = true; }
				}

				if (pMotion->GetnOtherCancel(0) < m_fMotionFrame && m_fMotionFrame < pMotion->GetnOtherCancel(1))
				{//キャンセル可能
					bCancel = true;
				}
				else if (MOTION_BOOST <= m_nNumMotion[1])
				{//予約がブースト以上なら
					if ((pMotion->GetnStartCancel(0) <= m_fMotionFrame && m_fMotionFrame < pMotion->GetnStartCancel(1)) ||
						(pMotion->GetnEndCancel(0) <= m_fMotionFrame && m_fMotionFrame < pMotion->GetnEndCancel(1)))
					{//キャンセル可能
						bCancel = true;
						bStart = true;		//スタートキャンセル適用
					}
				}
				if (bCancel)
				{//キャンセルが可能
					SetCancelMotion(m_nNumMotion[1]);	//モーションのキャンセル
					m_nCancelFrame = -1;				//モーションキャンセル保持フレーム初期化
				}
			}//if(同技でない)
		}//if(前回行った攻撃モーションでない)
		else { m_nCancelFrame = -1; }
		//一定Ｆ数保持
		m_nCancelFrame--;
		if (m_nCancelFrame < 0) { m_nNumMotion[1] = -1; m_nCancelFrame = 0; }//次モーション初期化
	}//if(モーションの予約有)
}
//=============================================================================
// モーションのキャンセル設定
//=============================================================================
void CCharacter::SetCancelMotion(int nNumber)
{
	CMotion::TYPE &m_Type = m_pParts[0]->GetMotion();

	//SP確認
	if (!UseSP(nNumber)) { m_nNumMotion[1] = -1; return; }

	//ダウン2連続確認
	if (m_nNumMotion[0] == MOTION_DOWN && m_nNumMotion[1] == MOTION_BLOW) { m_nInvincible = 500; }

	//足の入れ替え
	if (m_nNumMotion[0] == MOTION_WALK && m_nNumMotion[1] == MOTION_NEUTRAL) { m_nLeg = m_nNumMotion[2]; }
	m_pWaitMotion[nNumber] = CMotion::GetMotion(m_Type)->GetOneMotion()[nNumber].GetfWaitTime();
	m_nNumMotion[3] = m_nNumMotion[0];	//前モーション代入
	m_nNumMotion[0] = nNumber;			//モーションのキャンセル
	m_nNumMotion[2] = 0;
	m_nNumMotion[1] = -1;				//次モーションの初期化
	m_fFrame = 0.0f;			//フレーム数初期化
	m_fMotionFrame = 0.0f;		//モーション全体フレーム数初期化
	m_fKeepFrame = 0.0f;

	COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];

	if (m_nNumMotion[0] == MOTION_WALK)	  { m_nNumMotion[2] = m_nLeg; }		//歩きなら前回の途中から
	if (m_nNumMotion[3] >= MOTION_ATTACK && m_nNumMotion[0] >= MOTION_ATTACK) { m_fFramePlus = 2.0f; UseStamina(10.0f); }			//キーにキャンセル時を代入
	if (m_nNumMotion[0] >= MOTION_ATTACK) { m_rot.y = m_fARot; }			//攻撃モーションなら移動方向に合わせる
	CKey *pKey = pMotion->GetKey()[m_nNumMotion[2]];
	int nMaxParts = CMotion::GetMotion(m_Type)->GetnMaxParts();
	if (m_nNumMotion[2] > 0)
	{
		for (int nCount = 0; nCount < m_nNumMotion[2]; nCount++)
		{//モーション全体フレームをキー分進める
			m_fMotionFrame += (float)pMotion->GetKey()[nCount]->GetnFrame();
		}
	}

	m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
	for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
	{//moveを計算して代入
		D3DXVECTOR3 &addRotMove = m_pParts[0]->GetBone()[nCntModel].GetaddRotMove();
		addRotMove = (pKey->GetpRot()[nCntModel] - m_pParts[0]->GetBone()[nCntModel].GetaddRot()) / FRAME_SPEED;

		//角度確認
		if (addRotMove.x > D3DX_PI) { addRotMove.x -= D3DX_PI * 2; }
		else if (addRotMove.x < -D3DX_PI) { addRotMove.x += D3DX_PI * 2; }
		if (addRotMove.y > D3DX_PI) { addRotMove.y -= D3DX_PI * 2; }
		else if (addRotMove.y < -D3DX_PI) { addRotMove.y += D3DX_PI * 2; }
		if (addRotMove.z > D3DX_PI) { addRotMove.z -= D3DX_PI * 2; }
		else if (addRotMove.z < -D3DX_PI) { addRotMove.z += D3DX_PI * 2; }

		addRotMove /= (float)pKey->GetnFrame();
	}

	switch (m_nNumMotion[0])
	{//モーション発動時効果
	case MOTION_BLOW:	m_move = D3DXVECTOR3(0.0f, 3.5f, 0.0f); m_bJump = false;	break;
	case MOTION_RETURN:	m_nCntDamage = 0; m_nInvincible = 120 * FRAME_SPEED;		break;
	}
	SetAtkNumber(m_nNumMotion[0]);		//攻撃モーションの保存
	m_bOrbit = true; CMeshOrbit::Delete(); CLineEffect::Delete(); m_bOrbit = false;	//オービットの削除
	ReSetHitChar();						//ヒットキャラのリセット
}
//=============================================================================
//　次のモーションへの予約
//=============================================================================
void CCharacter::SetNextMotion(int nNumber)
{
	m_nNumMotion[1] = nNumber;
	m_nCancelFrame = 20;
	m_fARot = m_fRot;
}
//=============================================================================
// モーションのリセット
//=============================================================================
void CCharacter::ResetMotion(void)
{
	m_nNumMotion[0] = 0;
	m_nNumMotion[1] = -1;
	m_nNumMotion[2] = 0;
	m_nNumMotion[3] = 0;
	m_fFrame = 99999.0f;
	SetRotMotion();
}
//=============================================================================
//モーションの番号の保存
//=============================================================================
void CCharacter::SetAtkNumber(int nNumber)					//モーションの番号記録
{
	if (nNumber >= MOTION_ATTACK)
	{
		m_pUseMotion[nNumber] = true;
	}
}
//=============================================================================
//モーションの番号のリセット更新
//=============================================================================
void CCharacter::ResetUpdate(void)
{
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();

	for (int nCount = 0; nCount < nMaxMotion; nCount++)
	{//モーションごとの待ち時間確認
		if (m_pWaitMotion[nCount] > 0)
		{//待ち時間があるなら
			m_pWaitMotion[nCount]--;
		}
	}

	if (m_nNumMotion[0] < MOTION_ATTACK)
	{//現在が攻撃モーションでない
		if (m_nCntReUse > 0)
		{//保存した攻撃の解放が必要
			m_nCntReUse--;
			if (m_nCntReUse == 0)
			{//待ち時間の後解放
				ResetAtkNumber();
			}
		}
	}
	else { m_nCntReUse = 30; }

	if (m_nNumMotion[0] < MOTION_JUMP || m_nNumMotion[0] == MOTION_APPEAL)
	{//ニュートラルか歩きなら
		if (m_fCntStamina > 0) { m_fCntStamina -= 1.0f; }
		else if (m_fStamina < m_fMaxStamina)
		{//回復可能
			if (m_fStamina < 0.0f) { m_fCntStamina -= 0.5f; }
			m_fStamina += 4.0f;
		}
	}
	else { m_fCntStamina = 90.0f; }
}
//=============================================================================
//モーションの番号のリセット
//=============================================================================
void CCharacter::ResetAtkNumber(void)
{
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();
	for (int nCount = 0; nCount < nMaxMotion; nCount++)
	{
		m_pUseMotion[nCount] = false;
	}
}
//=============================================================================
//モーションの番号の確認
//=============================================================================
bool CCharacter::CheckAtkNumber(int nNumber)
{
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();
	if(nNumber < nMaxMotion)
	{//行った攻撃と待ち時間確認
		if (m_pWaitMotion[nNumber] > 0.0f)		{ return false; }
		if (m_pUseMotion[nNumber] == true)	{ return false; }
	}
	return true;
}
//=============================================================================
//角度と角度のチェック判定
//=============================================================================
float CCharacter::AngleCheck(float fAngle0, float fAngle1)
{
	fAngle1 -= fAngle0;
	if (fAngle1 > D3DX_PI) { fAngle1 -= D3DX_PI * 2.0f; }
	if (fAngle1 < -D3DX_PI) { fAngle1 += D3DX_PI * 2.0f; }
	return fAngle1;
}
//=============================================================================
//スタミナの使用処理
//=============================================================================
void CCharacter::UseStamina(float fValue)
{
	m_fStamina -= fValue;
	if (m_fStamina < 0) { m_fStamina = -60.0f; }
}
//=============================================================================
//SPの使用処理
//=============================================================================
bool CCharacter::UseSP(int nNumber)
{
	CKey  *pKey = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetOneMotion()[nNumber].GetKey()[0];
	float fValue = 0.0f;
	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		fValue += GetEffect_SP(pKey->GetpEffect()[nCount]);
	}

	if (m_fSP >= fValue) { m_fSP -= fValue; }
	else { return false; }
	return true;
}
//=============================================================================
//SPの使用処理
//=============================================================================
bool CCharacter::CheckSP(CMotion::TYPE type, int nNumber, float &fValue)
{
	CKey  *pKey = CMotion::GetMotion(type)->GetOneMotion()[nNumber].GetKey()[0];
	float fUse = 0.0f;
	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		fUse += GetEffect_SP(pKey->GetpEffect()[nCount]);
	}

	if (fValue < fUse) { return false; }
	return true;
}
//=============================================================================
//番号から使用するSPを返す
//=============================================================================
float CCharacter::GetEffect_SP(int nNumber)
{
	switch (nNumber)
	{
	case 30: return 250.0f;
	case 31: return 30.0f;
	case 32: return 50.0f;
	case 33: return 200.0f;
	case 34: return 55.0f;
	case 35: return 60.0f;
	}
	return 0.0f;
}
//=============================================================================
//キャラをロック
//=============================================================================
CScene *CCharacter::LockChar(LOCK lock)
{
	CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(((CPlayer*)this)->GetnID())->GetChar();
	CPlayer_UI *&pUI = ((CPlayer*)this)->GetpUI();
	CScene *pScene;
	CScene *pSceneLock = NULL;
	CScene *pSceneOld = NULL;
	CScene *pSceneNear = NULL;
	float	fDistance;	//距離
	float	fWKData = D3DX_PI * 2.0f;	//角度
	float	fWKData2 = 0.0f;//距離や角度
	float	fBaseAngle = pCamera->GetRot().y + D3DX_PI;		//元の角度
	float	fWKAngle;		//比較用の角度

	if		(fBaseAngle > D3DX_PI)	{ fBaseAngle -= D3DX_PI * 2.0f; }
	else if (fBaseAngle < -D3DX_PI) { fBaseAngle += D3DX_PI * 2.0f; }

	if (lock == LOCK_LEFT)	 { fWKData *= -1; }					//左側ロックなら比較用初期値反転
	if (lock == LOCK_NEAR)	 { fWKData = 1500.0f * 1500.0f; }	//左側ロックなら比較用初期値反転
	else if (m_pLockChar != NULL) { pSceneOld = m_pLockChar; }	//近いものロックでない
	if (m_pLockChar != NULL) { pSceneNear = m_pLockChar; }		//最終確認用ロック対象を保存
	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_PLAYER || pScene->GetObjType() == OBJTYPE_ENEMY)
		{
			CCharacter *pChar = (CCharacter*)pScene;
			if (pScene != this && pScene != pSceneOld && (m_Team != pChar->m_Team || m_Team == TEAM_IGNORED))
			{//キャラ発見
				D3DXVECTOR3 &pos = ((CCharacter*)pScene)->Getpos();

				fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);
				if (fDistance < 1500.0f * 1500.0f)
				{
					switch (lock)
					{
					case LOCK_NO:
					case LOCK_FIRST:
						fWKAngle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);	//キャラ同士の角度取得
						fWKData2 = AngleCheck(fBaseAngle, fWKAngle);			//ロック角度との差分を取得
						if (fWKData2 < 0) { fWKData2 *= -1.0f; }				//マイナスならプラスへ

						if (fWKData > fWKData2)
						{//より近い角度へ
							fWKData = fWKData2;
							pSceneLock = pScene;
						}
						break;
					case LOCK_NEAR:
						if (fWKData > fDistance)
						{//より近い角度へ
							fWKData = fDistance;
							pSceneLock = pScene;
						}
						break;
					case LOCK_LEFT:
					case LOCK_RIGHT:
						fWKAngle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);					//キャラ同士の角度取得
						fWKData2 = AngleCheck(fBaseAngle, fWKAngle);							//ロック角度との差分を取得
						if (fWKData2 > 0 && lock == LOCK_LEFT) { fWKData2 -= D3DX_PI * 2; }	//左Ver補正
						if (fWKData2 < 0 && lock == LOCK_RIGHT) { fWKData2 += D3DX_PI * 2; }	//右Ver補正

						if ((lock == LOCK_LEFT ? fWKData < fWKData2 : fWKData > fWKData2))
						{//左/右　側で比較
							fWKData = fWKData2;
							pSceneLock = pScene;
						}
						break;
					}
				}//if(範囲確認)
			}//if(ロック状態とチーム確認)
		}//if(キャラ確認)
		pScene = pScene->GetpNext();
	}

	if (pSceneLock != NULL)
	{
		if (m_pLockChar)
		{//既にロックキャラがいる
			//切り替え
			pUI->SetLockOn(CPlayer_UI::LOCK_ON, pSceneLock->Getpos());
		}
		else
		{
			if (lock == LOCK_NO) { pUI->SetLockOn(CPlayer_UI::LOCK_NO, pSceneLock->Getpos()); }
			else { pUI->SetLockOn(CPlayer_UI::LOCK_START, pSceneLock->Getpos()); }
		}
	}
	else if (lock == LOCK_NO) { pUI->GetpLockOn()->BindDrawType(CScene::DRAW_TYPE_NO); }
	return pSceneLock;
}
//=============================================================================
//キャラロックを解除
//=============================================================================
void CCharacter::LockCancel(void)
{
	m_pLockChar = NULL;
	if (GetObjType() == OBJTYPE_PLAYER)
	{
		//音
		((CPlayer*)this)->GetpUI()->GetpLockOn()->BindDrawType(CScene::DRAW_TYPE_NO);
	}
}
//=============================================================================
//死亡時、自身へのロックを外す
//=============================================================================
void CCharacter::CancelLock(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_ENEMY || pScene->GetObjType() == OBJTYPE_PLAYER)
		{//キャラ発見
			if (((CCharacter*)pScene)->m_pLockChar == this)
			{ 
				((CCharacter*)pScene)->LockCancel();
				//if (pScene->GetObjType() == OBJTYPE_PLAYER)
				//{
				//	((CPlayer*)pScene)->LockCancel();
				//}
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//現在のレベルでステータス計算
//=============================================================================
void CCharacter::SetStatus(void)
{
	m_fMaxLife	= 100.0f;	m_fLife = m_fMaxLife;
	m_fMaxSP	= 500.0f * (((m_nLevel * 2) + 100) * 0.01f);	m_fSP = m_fMaxSP;
	m_fAtk		= 350.0f * (((m_nLevel * 2) + 100) * 0.01f);
	m_fStamina	= m_fMaxStamina;
}
//=============================================================================
// 現在のキーに角度を完全に合わせる
//=============================================================================
void CCharacter::SetRotMotion(void)
{
	int nMaxParts = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxParts();
	CKey *pKey = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetOneMotion()[m_nNumMotion[0]].GetKey()[m_nNumMotion[2]];

	for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
	{//moveを計算して代入
		m_pParts[0]->GetBone()[nCntModel].GetaddRot() = pKey->GetpRot()[nCntModel];
	}
}
//=============================================================================
// フレームの進行速度設定
//=============================================================================
void CCharacter::SetPlusFrame(float fPFrame, float fCount)
{
	m_fFramePlus2 = fPFrame;
	m_fInitFrame = fCount;
}
//=============================================================================
//	全キャラのあたり判定
//=============================================================================
void CCharacter::CollisionAll(CScene *pChar)	//キャラ同士のあたり判定
{
	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_ENEMY || pScene->GetObjType() == OBJTYPE_PLAYER)
		{//メッシュ発見
			if (pChar != pScene)
			{//自分でないなら
				((CCharacter*)pScene)->Collision(pChar);
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//	キャラ同士のあたり判定
//=============================================================================
void CCharacter::Collision(CScene *pChar)
{
	CCharacter *PChar = (CCharacter*)pChar;
	D3DXVECTOR3 &length = PChar->Getlength();
	D3DXVECTOR3 &pos = PChar->Getpos();
	D3DXVECTOR3 WKpos = pos;
	bool &bJump = PChar->GetbJump();

	float fDistance, fAngle;

	//攻撃中ならY無視
	if ((m_pos.y > pos.y - length.y && m_pos.y < pos.y + length.y) || 
		PChar->m_nNumMotion[0] >= MOTION_ATTACK)
	{
		//中心貫通対策


		//円形範囲内なら
		fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);
		if (fDistance < powf(length.x + m_length.x, 2))
		{//自身から見た角度で一定値離す
			if (PChar->GetnNumMotion(0) >= MOTION_ATTACK) 
			{//攻撃中なら
				WKpos = PChar->Getposold();
				PChar->Getmove().x = 0.0f;
				PChar->Getmove().z = 0.0f;
			}
			fAngle = atan2f(WKpos.x - m_pos.x, WKpos.z - m_pos.z);
			pos = D3DXVECTOR3(m_pos.x, pos.y, m_pos.z) + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * (length.x + m_length.x);
		}
	}
}
//=============================================================================
//	キー事の効果
//=============================================================================
void CCharacter::SetEffect(CKey *&pKey)
{
	float fRotPoor;
	CSound *&pSound = CManager::GetSound();

	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		switch (pKey->GetpEffect()[nCount])
		{
		case 0:	if (m_fFrame == 0.0f) { m_rot.y = m_fRot; } break;	//角度を合わせる
		case 1:	if (m_fFrame == 0.0f) { m_move.y = 0.0f; }	break;	//角度を合わせる
		case 2:	if (!m_bJump)		  { m_move.y = 0.0f; }	break;	//空中なら浮遊
		case 3:	if (m_fFrame == 0.0f) { SetPlusFrame(0.5f, 180.0f); m_fStamina = m_fMaxStamina; pSound->Play(CSound::LABEL_CHARGE000); }	break;	//モーションの加速
		case 4:	if (m_fFrame == 0.0f) { ReSetHitChar(); }	break;	//ヒット情報のリセット
		case 5:	if (m_fFrame == 0.0f) { UseStamina(25.0f); pSound->Play(CSound::LABEL_STEP); }	break;	//ステップによるスタミナ減少
		case 6:	if (m_fFrame == 0.0f) { UseStamina(20.0f); pSound->Play(CSound::LABEL_STEP); }	break;	//ジャンプによるスタミナ減少
		case 7://ブーストの仕様
			pSound->Play(CSound::LABEL_BOOST000);
			UseStamina(0.25f); 
			if ((!m_bBoost || m_fKeepFrame > 80.0f) && m_fKeepFrame > 20.0f) { SetCancelMotion(MOTION_BOOST_END); }

			//向きを合わせる
			fRotPoor = m_fRot - m_rot.y;
			if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
			else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
			m_rot.y += fRotPoor * 0.025f;
			if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
			if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
			break;	//ジャンプによるスタミナ減少
		case 8:
			if(m_fMotionFrame > 200)
			{
				SetCancelMotion(MOTION_RETURN);
			}
		case 10:
			if (m_fFrame == 0.0f)
			{ 
				m_bOrbit = true; 
				CMeshOrbit::Delete();
				CLineEffect::Delete();
				m_bOrbit = false;
			}	break;	//オービット削除
		case 11: m_move.y += 0.24f; break;	//ゆっくり
		case 20: m_state = STATE_GUARD; break;
		case 21: m_state = STATE_PARIS; break;
		case 22: m_state = STATE_AVOID; break;
		case 23: m_state = STATE_ARMOR; break;
		}
	}
}
//=============================================================================
// キャラクターの設定
//=============================================================================
void CCharacter::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)
{
	m_pos = pos; m_posold = pos;
	m_rot = rot;
	m_fRot = rot.y;

	switch (type)
	{
	case CMotion::TYPE_BOX_Sword:	CCharParts::SetBox_100(this); m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a);	break;
	case CMotion::TYPE_BOX_Stick:	CCharParts::SetBox_Stick(this); m_col = D3DXCOLOR(0.75f, 0.75f, 0.75f, m_col.a);	break;
	}

	//モーション数待ち時間用意
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();
	m_pWaitMotion = new float[nMaxMotion];
	if (m_pWaitMotion != NULL)
	{
		for (int nCount = 0; nCount < nMaxMotion; nCount++) { m_pWaitMotion[nCount] = 0.0f; }
	}
	m_pUseMotion = new bool[nMaxMotion];
	if (m_pUseMotion != NULL)
	{
		ResetAtkNumber();
	}
}
//=============================================================================
// 頂点の設定
//=============================================================================
void CCharParts::SetVtx(int &nCount)
{
	int nParts = (int)GetModel()[nCount];
	CVtxInfo *&VtxInfo = GetVtxInfo(nParts);
	
	if (VtxInfo != NULL)
	{
		CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(nParts);
		D3DXMATRIX			Drawmtx, WKmtx, WKmtx2, mtxTrans, mtxRot;		//計算用マトリックス
		D3DXVECTOR3 WKpos;
		BYTE *pVtxBuff;
		int nNumVtx = m_pMeshModel[nCount]->GetNumVertices();
		DWORD sizeFvF;	//頂点フォーマットのサイズ

		sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel[nCount]->GetFVF());
		m_pMeshModel[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//頂点をいじる
		 //((D3DXVECTOR3*)pVtxBuff)[0] = m_partsAll->pPos[nCntVtx];
			WKpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (VtxInfo[nCntVtx].GetnMaxBone() > 0)
			{
				Drawmtx = m_pDrawMtx[nCount][0];
				for (int nCntBone = 0; nCntBone < 1; nCntBone++)
				{
					int nBone = VtxInfo[nCntVtx].GetnBone()[nCntBone];
					float &fWeight = VtxInfo[nCntVtx].GetfWeight()[nCntBone];

					//描画時マトリックスと目標ボーンマトリックスを指定
					WKmtx = m_pBone[nBone].GetMtx();
					////差分計算
					D3DXVECTOR3 pos = m_partsAll->pPos[nCntVtx];

					//ボーンのマトリックスと差で計算
					pos = VtxInfo[nCntVtx].Getpos()[nCntBone];

					D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
					D3DXMatrixMultiply(&mtxTrans, &mtxTrans, &WKmtx);
					WKmtx = mtxTrans;
					//差分詰める
					WKpos += (D3DXVECTOR3(WKmtx._41, WKmtx._42, WKmtx._43) - WKpos) * (nCntBone == 0 ? 1.0f : fWeight);
				}
				//描画用ボーンとの差を代入
				Drawmtx = m_pDrawMtx[nCount][0];
				((D3DXVECTOR3*)pVtxBuff)[0] = WKpos - D3DXVECTOR3(Drawmtx._41, Drawmtx._42, Drawmtx._43);
			}
			pVtxBuff += sizeFvF;
		}
		m_pMeshModel[nCount]->UnlockVertexBuffer();

	}
}
//=============================================================================
// パーツ（ボーン）の設定
//=============================================================================
void CCharParts::SetBone(int nNumber, D3DXMATRIX *pPair, D3DXVECTOR3 pos)
{
	m_pBone[nNumber].GetaddPos() = pos;
	m_pBone[nNumber].GetaddPosMove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBone[nNumber].GetaddRot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBone[nNumber].GetaddRotMove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBone[nNumber].GetPairMtx() = pPair;
}
//=============================================================================
// パーツの設定
//=============================================================================
void CCharParts::Set(int nNumber, D3DXMATRIX *pDraw, PARTS model)
{
	m_pDrawMtx[nNumber] = pDraw;
	GetModel()[nNumber] = model;
	CCharacter::Load(model)->CloneMesh(D3DXMESH_SYSTEMMEM, NULL, CManager::GetRenderer()->GetDevice(), &m_pMeshModel[nNumber]);
}
//=============================================================================
// ボーンの作成
//=============================================================================
void	CCharParts::NewBone(int nMax)
{
	if (m_pBone != NULL)
	{//何か入っていれば削除
		delete[] m_pBone;
		m_pBone = NULL;
	}

	if (nMax > 0)
	{//1以上生成なら
		m_nMaxBone = nMax;
		m_pBone = new CBone[nMax];
	}
}
//=============================================================================
// モデルの作成
//=============================================================================
void	CCharParts::NewModel(int nMax)
{
	if (m_pModel != NULL)
	{//何か入っていれば削除
		delete[] m_pModel;
		m_pModel = NULL;
	}
	if (m_pDrawMtx != NULL)
	{//何か入っていれば削除
		delete[] m_pDrawMtx;
		m_pDrawMtx = NULL;
	}
	if (m_pMeshModel != NULL)
	{
		for (int nCount = 0; nCount < m_nMaxModel; nCount++) { m_pMeshModel[nCount]->Release(); }
		delete m_pMeshModel;
		m_pMeshModel = NULL;
	}
	m_nMaxModel = nMax;
	m_pMeshModel = new LPD3DXMESH[nMax];
	m_pModel = new CCharParts::PARTS[nMax];
	m_pDrawMtx = new D3DXMATRIX*[nMax];
}
//=============================================================================
// パーツの終了
//=============================================================================
void CCharParts::Uninit(void)
{
	if (m_pModel != NULL)
	{//何か入っていれば削除
		delete[] m_pModel;
		m_pModel = NULL;
	}
	if (m_pDrawMtx != NULL)
	{//何か入っていれば削除
		delete[] m_pDrawMtx;
		m_pDrawMtx = NULL;
	}
	if (m_pMeshModel != NULL)
	{
		for (int nCount = 0; nCount < m_nMaxModel; nCount++) { m_pMeshModel[nCount]->Release(); }
		delete m_pMeshModel;
		m_pMeshModel = NULL;
	}
}
//=============================================================================
// パーツの設定
//=============================================================================
void CCharParts::Draw(CCharacter *pChar)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX			WKmtx, mtxRot, mtxTrans;		//計算用マトリックス
	CScene::DRAW_TYPE DType = pChar->GetDrawType();
	int nCount;
	bool bTex = true;
	if (pChar->GetnInvincible() > 0) { DType = CScene::DRAW_TYPE_AER; }

	//ボーンの計算
	if (!pChar->GetbVtx())
	{//頂点設定をしていない
		for (nCount = 0; nCount < m_nMaxBone; nCount++)
		{//ボーンの計算
			D3DXMATRIX &mtx = m_pBone[nCount].GetMtx();
			D3DXVECTOR3 &addRot = m_pBone[nCount].GetaddRot();
			D3DXVECTOR3 &addPos = m_pBone[nCount].GetaddPos();
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&mtx);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, addRot.y, addRot.x, addRot.z);
			D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, addPos.x, addPos.y, addPos.z);
			D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

			//親ボーンと掛け合わせ
			if (m_pBone[nCount].GetPairMtx() != NULL)
			{//親の位置と角度をプラス
				D3DXMatrixMultiply(&mtx, &mtx, m_pBone[nCount].GetPairMtx());
			}
		}
	}
	//モデルの描画
	for (nCount = 0; nCount < m_nMaxModel; nCount++)
	{//モデルの描画
		WKmtx = m_pDrawMtx[nCount][0];
		CVtxInfo *&VtxInfo = GetVtxInfo(m_pModel[nCount]);

		if (VtxInfo != NULL)
		{//頂点情報があるなら
			D3DXMATRIX &DMtx = m_pDrawMtx[nCount][0];
			D3DXMatrixIdentity(&WKmtx);
			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, DMtx._41, DMtx._42, DMtx._43);
			D3DXMatrixMultiply(&WKmtx, &WKmtx, &mtxTrans);
		}
		//頂点の設定
		if (!pChar->GetbVtx()) { SetVtx(nCount); }

		//ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &WKmtx);

		//描画
		if (pChar->GetnInvincible() > 0) { pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); bTex = false; }
		CScene::DrawPrepare(DType, pDevice);
		DrawModel(pChar, nCount, bTex);

		CSceneModel::SetShadow();
		CScene::DrawPrepare(CScene::DRAW_TYPE_SUBTRACT, pDevice);
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawModel(pChar, nCount, false);
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//=============================================================================
// モデルの描画
//=============================================================================
void CCharParts::DrawModel(CCharacter *pChar, int &nCount, bool bTex)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATERIAL		*pMat;					//マテリアルデータへのポインタ
	D3DMATERIAL9		matDef;					//現在のマテリアル保存用
	CCharParts::PARTS &Parts = GetModel()[nCount];
	CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(Parts);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_partsAll->pBuffMatModel->GetBufferPointer();

	//テクスチャの設定
	if (bTex)
	{//画像を張っていいなら
		if (m_partsAll->tex != CScene::TEX_MAX)
		{//画像を指定しているか確認
			if (CScene::GetTexture(m_partsAll->tex) != NULL)
			{//テクスチャの設定
				pDevice->SetTexture(0, CScene::GetTexture(m_partsAll->tex));
			}//テクスチャ削除
		}
		else if (Parts == CCharParts::BOX_100)
		{
			switch (m_pChar->GetType())
			{
			case CMotion::TYPE_BOX_Sword: pDevice->SetTexture(0, CScene::Load(CScene::TEX_TAKASHI)); break;
			case CMotion::TYPE_BOX_Stick: pDevice->SetTexture(0, CScene::Load(CScene::TEX_BSword)); break;

			}
		}
	}
	// マテリアルデータへのポインタを取得
	for (int nCountData = 0; nCountData < (int)m_partsAll->nNumMatModel; nCountData++)
	{
		// マテリアルの設定
		pMat = (D3DXMATERIAL*)m_partsAll->pBuffMatModel->GetBufferPointer();
		if (Cloak_000 > Parts) { pMat[nCountData].MatD3D.Diffuse = pChar->GetCollar(); } //透明度設定
		pMat[nCountData].MatD3D.Diffuse.a = pChar->GetCollar().a;
		pDevice->SetMaterial(&pMat[nCountData].MatD3D);

		// モデル(パーツ)の描画
		m_pMeshModel[nCount]->DrawSubset(nCountData);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
	pDevice->SetTexture(0, NULL);
}
//=============================================================================
// キャラクターの設定
//=============================================================================
void CCharParts::SetBox_Sword(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;

	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;
		//Parts[1] = new CClothing;
		//((CClothing*)Parts[1])->Set(pChar);
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Sword;
	//Parts[1]->m_Motion = CMotion::TYPE_MAX;

	//生成
	Parts[0]->LoadChar(0, "data/TEXT/Bone/Bone_Rig.txt");
	//Parts[0]->NewBone(21);
	Parts[0]->NewModel(20);
	//Parts[1]->NewBone(0);
	//Parts[1]->NewModel(1);

	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), BRIG_hip);
	Parts[0]->Set(1, &Parts[0]->GetBone()[1].GetMtx(), BRIG_hara);
	Parts[0]->Set(2, &Parts[0]->GetBone()[2].GetMtx(), BRIG_mune);
	Parts[0]->Set(3, &Parts[0]->GetBone()[3].GetMtx(), BRIG_head);
	Parts[0]->Set(4, &Parts[0]->GetBone()[4].GetMtx(), BRIG_armUR);
	Parts[0]->Set(5, &Parts[0]->GetBone()[5].GetMtx(), BRIG_armD);
	Parts[0]->Set(6, &Parts[0]->GetBone()[6].GetMtx(), BRIG_hand);
	Parts[0]->Set(7, &Parts[0]->GetBone()[7].GetMtx(), BRIG_handR2);
	Parts[0]->Set(8, &Parts[0]->GetBone()[8].GetMtx(), BRIG_handR3);
	Parts[0]->Set(9, &Parts[0]->GetBone()[9].GetMtx(), BRIG_armUL);
	Parts[0]->Set(10, &Parts[0]->GetBone()[10].GetMtx(), BRIG_armD);
	Parts[0]->Set(11, &Parts[0]->GetBone()[11].GetMtx(), BRIG_hand);
	Parts[0]->Set(12, &Parts[0]->GetBone()[12].GetMtx(), BRIG_handL2);
	Parts[0]->Set(13, &Parts[0]->GetBone()[13].GetMtx(), BRIG_handL3);
	Parts[0]->Set(14, &Parts[0]->GetBone()[14].GetMtx(), BRIG_legUR);
	Parts[0]->Set(15, &Parts[0]->GetBone()[15].GetMtx(), BRIG_legD);
	Parts[0]->Set(16, &Parts[0]->GetBone()[16].GetMtx(), BRIG_foot);
	Parts[0]->Set(17, &Parts[0]->GetBone()[17].GetMtx(), BRIG_legUL);
	Parts[0]->Set(18, &Parts[0]->GetBone()[18].GetMtx(), BRIG_legD);
	Parts[0]->Set(19, &Parts[0]->GetBone()[19].GetMtx(), BRIG_foot);
	//Parts[0]->Set(20, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Sword0);
	//Parts[0]->Set(21, &Parts[0]->GetBone()[2].GetMtx(), &Parts[0]->GetBone()[2].GetMtx(), Cloak_000);

	//Parts[1]->GetDrawMtx()[0] = &Parts[0]->GetBone()[3].GetMtx();
	//Parts[1]->GetModel()[0] = Cloak_000;
	//CCharacter::Load(Cloak_000)->CloneMesh(D3DXMESH_SYSTEMMEM, NULL,CManager::GetRenderer()->GetDevice(), &Parts[1]->m_pMeshModel[0]);
}
//=============================================================================
// キャラクターの設定 棍棒
//=============================================================================
void CCharParts::SetBox_Stick(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;
	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Stick;
	pChar->GetpParts()[0]->LoadChar(0, "data/TEXT/Bone/Bone_Box100.txt");

	//Parts[0]->GetBone()[0].GetPairMtx() = &pChar->GetMtx();

	Parts[0]->NewModel(2);
	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), BOX_100);
	Parts[0]->Set(1, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Stick);
}
//=============================================================================
// キャラクターの設定 テスト型スキンメッシュ野郎
//=============================================================================
void CCharParts::SetTEST_000(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;
	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Sword;
	pChar->GetpParts()[0]->LoadChar(0, "data/TEXT/Bone/Bone_Box.txt");

	//Parts[0]->GetBone()[0].GetPairMtx() = &pChar->GetMtx();

	Parts[0]->NewModel(2);

	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), TEST_000);
	Parts[0]->Set(1, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Sword0);
}
//=============================================================================
// キャラクターの設定 箱型スキンメッシュ
//=============================================================================
void CCharParts::SetBox_100(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;
	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;

		//Parts[1] = new CClothing;
		//((CClothing*)Parts[1])->Set(pChar);
		//Parts[1]->m_Motion = CMotion::TYPE_MAX;
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Sword;
	pChar->GetpParts()[0]->LoadChar(0, "data/TEXT/Bone/Bone_Box100.txt");

	//Parts[0]->GetBone()[0].GetPairMtx() = &pChar->GetMtx();

	Parts[0]->NewModel(1);
	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), BOX_100);
	//Parts[0]->Set(1, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Sword0);
	//Parts[0]->Set(2, &Parts[0]->GetBone()[3].GetMtx(), Face_000);

	//Parts[1]->NewModel(1);
	//Parts[1]->Set(0, &Parts[0]->GetBone()[3].GetMtx(), Cloak_000);
}
//=============================================================================
// 頂点のロード
//=============================================================================
void CCharParts::LoadVtx(int nNumber, char *aStr)
{
	if (m_pVtxInfo[nNumber] != NULL) { return; }

	CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(nNumber);
	int nNumVtx, nWk;
	FILE *pFile;
	pFile = fopen(&aStr[0], "r");

	if (pFile != NULL)//Load
	{//成功
	 //頂点分界点
		fscanf(pFile, "%d\n", &nNumVtx);
		m_pVtxInfo[nNumber] = new CVtxInfo[nNumVtx + 1];
		for (int nVtx = 0; nVtx <= nNumVtx; nVtx++)
		{
			fscanf(pFile, "%d", &m_pVtxInfo[nNumber][nVtx].GetnMaxBone());
			m_pVtxInfo[nNumber][nVtx].GetnBone() = new int[32];
			m_pVtxInfo[nNumber][nVtx].GetfWeight() = new float[32];
			m_pVtxInfo[nNumber][nVtx].Getpos() = new D3DXVECTOR3[32];

			nWk = m_pVtxInfo[nNumber][nVtx].GetnMaxBone();
			for (int nCount = 0; nCount < m_pVtxInfo[nNumber][nVtx].GetnMaxBone(); nCount++)
			{
				D3DXVECTOR3 &pos = m_pVtxInfo[nNumber][nVtx].Getpos()[nCount];
				fscanf(pFile, "%d ", &m_pVtxInfo[nNumber][nVtx].GetnBone()[nCount]);
				fscanf(pFile, "%f ", &m_pVtxInfo[nNumber][nVtx].GetfWeight()[nCount]);
				fscanf(pFile, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// ボーンのロード
//=============================================================================
void CCharParts::LoadChar(int nNumber, char *aStr)
{
	FILE *pFile;
	int &nMaxParts = m_pChar->GetnMaxParts();
	CCharParts **&Parts = m_pChar->GetpParts();
	CCharParts *&parts = m_pChar->GetpParts()[nNumber];

	int			nData;
	D3DXVECTOR3 pos;
	D3DXMATRIX  *mtx;

	pFile = fopen(&aStr[0], "r");

	if (pFile != NULL)//Load
	{//成功
		fscanf(pFile, "%d\n", &parts->GetnMaxBone());//ボーンの数、モデルの数
		Parts[0]->NewBone(parts->GetnMaxBone());
		for (int nCount = 0; nCount < parts->GetnMaxBone(); nCount++)
		{
			D3DXVECTOR3 &rot = parts->GetBone()[nCount].GetaddRot();

			fscanf(pFile, "%f %f %f\n", &pos.x, &pos.y, &pos.z);//ボーンの数、モデルの数
			fscanf(pFile, "%d\n", &nData);			//ボーンの親番号

			if (nData == -1) { mtx = &m_pChar->GetMtx(); }
			else { mtx = &parts->GetBone()[nData].GetMtx(); }
			parts->SetBone(nCount, mtx, pos);
		}
		fclose(pFile);
	}
}
