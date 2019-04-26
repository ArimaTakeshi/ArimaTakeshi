//=============================================================================
//
// �X�R�A���� [score.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXNUMBER (8)

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CNumber;

//=====================
//  CScene�̔h���N���X
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
	static CNumber *m_apNumber[MAX_TEXNUMBER]; //�X�R�A�̌���
	LPDIRECT3DVERTEXBUFFER9		  m_pVtxBuff;
	D3DXVECTOR3 m_pos;
	static int m_nScore;

};
#endif





