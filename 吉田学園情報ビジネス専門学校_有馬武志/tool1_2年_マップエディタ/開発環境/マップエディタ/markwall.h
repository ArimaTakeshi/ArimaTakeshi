//=============================================================================
//
// ��̕Ǐ��� [markwall.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _MARKWALL_H_
#define _MARKWALL_H_

#include "main.h"
#include "scene3D.h"
#include "wall.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MARKWALL_PRIOTITY		(2)
#define	MAX_MARKWALL_TEX		(9)

//=============================================================================
// �N���X��`
//=============================================================================
class CMarkWall : public CScene3D
{
public:
	CMarkWall();
	~CMarkWall();

	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMarkWall *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nType);
	void UninitCreate(D3DXVECTOR3 pos);
	static int GetWallNum(void) { return m_nWallNum; }
	static void SetWallNum(int nNum) { m_nWallNum = nNum; }

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_MARKWALL_TEX];	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;							// �ʒu
	D3DXVECTOR3					m_rot;							// ����
	D3DXVECTOR2					m_size;							// �傫��
	int							m_nType;						// �ǂ̕���
	int							m_nWallTextureNumber;			// �e�N�X�`���̎�ޕύX
	int							m_nTexType;						// �e�N�X�`���ԍ�
	float						m_fHightLength;					// �c�̃T�C�Y�̕ύX
	float						m_fWidthLength;					// ���̃T�C�Y�̕ύX
	static int					m_nWallNum;						// �ǂ̐�
	bool						m_bSetWall;						// �ǂ̐ݒu
	static CWall				*m_pWall;						// �ǂ̃|�C���^
};
#endif
