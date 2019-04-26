//=============================================================================
//
// �Ǐ��� [wall.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"
#include "scene3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WALL_NAME			"data\\TEXT\\�X�e�[�W�t���b�g\\wall.txt"	//�ǂݍ���txt�t�@�C���̖��O
#define WALL_PRIOTITY		(3)
#define	MAX_WALL_TEX		(9)

//=============================================================================
// �N���X��`
//=============================================================================
class CWall : public CScene3D
{
public:
	CWall();
	~CWall();

	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR3 rot, int nType);
	void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fDepth);
	void TextSave(void);

private:
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_WALL_TEX];	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_rot;						// ��]
	D3DXVECTOR2					m_size;						// �傫��
	int							m_nType;					// �ǂ̕���
	float						m_fWidthDivide;				// ����
	float						m_fHightDivide;				// �c��
	int							m_nTexType;					// �e�N�X�`���̎��
};
#endif
