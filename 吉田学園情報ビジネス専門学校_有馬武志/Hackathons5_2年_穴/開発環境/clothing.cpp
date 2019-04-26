//=============================================================================
//
// 衣服処理 [clothing.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "motion.h"
#include "clothing.h"
#include "wind.h"
#include "mesh.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//==================================================================================================//
//    * セット関数 *
//==================================================================================================//
void CClothing::Set(CCharacter *pChar)	//ゲージセット処理
{
	m_pChar = pChar;
	m_fWind = 0.0f;
}
//=============================================================================
// 頂点の設定処理
//=============================================================================
void CClothing::SetVtx(int &nCount)	//後々バッファのやつも引数に
{
	int nParts = (int)GetModel()[nCount];
	CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(nParts);

	if (m_partsAll->pPos != NULL)
	{//位置情報の頂点を生成
		CWind_Manager *&pWind = CManager::GetWind();
		BYTE *pVtxBuff;
		int nNumVtx = GetpMeshModel()[nCount]->GetNumVertices();
		DWORD sizeFvF;	//頂点フォーマットのサイズ
		D3DXVECTOR3 Value;
		float		fRot;

		m_fWind += sqrtf(powf(m_pChar->Getmove().x, 2) + powf(m_pChar->Getmove().z, 2) + powf(m_pChar->Getmove().y, 2)) * 0.0025f;
		sizeFvF = D3DXGetFVFVertexSize(GetpMeshModel()[nCount]->GetFVF());

		GetpMeshModel()[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			((D3DXVECTOR3*)pVtxBuff)[0] = m_partsAll->pPos[nCntVtx];
			Value = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			fRot = atan2f(m_partsAll->pPos[nCntVtx].x * 0.25f, m_partsAll->pPos[nCntVtx].z);
			Value.y = cosf(pWind->GetfRot() + fRot * 2.0f) * ((D3DXVECTOR3*)pVtxBuff)[0].y * 0.25f;
			{//風を受けた場合
				Value = D3DXVECTOR3(sinf(fRot), 1.0f, cosf(fRot)) * -Value.y;
				Value.x -= sinf(fRot) * m_partsAll->pPos[nCntVtx].y * 0.25f;
				Value.z -= cosf(fRot) * m_partsAll->pPos[nCntVtx].y * 0.25f;
				Value.y -= ((D3DXVECTOR3*)pVtxBuff)[0].y * 0.5f * 0.25f;

				Value += D3DXVECTOR3(sinf(fRot), 1.0f, cosf(fRot)) * ((D3DXVECTOR3*)pVtxBuff)[0].y * -m_fWind;

				((D3DXVECTOR3*)pVtxBuff)[0] += Value;
			}

			pVtxBuff += sizeFvF;
		}

		m_fWind *= 0.9f;
		GetpMeshModel()[nCount]->UnlockVertexBuffer();
	}
}

