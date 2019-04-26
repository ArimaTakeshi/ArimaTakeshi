//=============================================================================
//
// スコア処理 [score.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TEXNUMBER (8)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CNumber;

//=====================
//  CSceneの派生クラス
//=====================
class CScore : CScene
{
public:
	CScore();			
	~CScore();							
	HRESULT Init(void);		
	void Uninit(void);						
	void Update(void);						
	void Draw(void);						
	static void AddScore(int nValue);
	int GetScore(void);
	static CScore *Create(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	static CNumber *m_apNumber[MAX_TEXNUMBER]; //スコアの桁数
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	static int m_nScore;

};
#endif





