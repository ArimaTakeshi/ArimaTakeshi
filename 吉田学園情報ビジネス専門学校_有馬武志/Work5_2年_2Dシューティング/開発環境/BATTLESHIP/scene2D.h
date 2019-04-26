//=============================================================================
//
// ���C������ [scene2D.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TEXTURE	(32)

//=====================
//  CScene�̔h���N���X
//=====================
class CScene2D : public CScene
{
public://�N�ł�������
	CScene2D(int nPriority = 3);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 Texture);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	D3DXVECTOR2 GetSize(void) { return m_nSize; }
	static CScene2D *Create(void);
	void SetRadius(D3DXVECTOR3 pos, float fRadius);
	void SetMove(D3DXVECTOR3 m_move) { m_Move = m_move; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void Set(D3DXVECTOR3 pos, D3DXVECTOR2 nSize);
	void SetAnim(D3DXVECTOR2 nTex_UV, int nAnimPatteun);
	void SetBg(D3DXVECTOR2 *nTex_UV);
	void SetVtxPos(D3DXVECTOR3 *VxtPos);
	void SetColor(D3DXCOLOR *Color);
	void SetCol(D3DXCOLOR color);
	void SetLifeVtx(D3DXVECTOR3 pos,D3DXVECTOR2 size);
	void SetDamageLife(D3DXVECTOR2 *UV,float nDamage);
	void SetRot(float fAngle, D3DXVECTOR2 size);
	void SetSpin(D3DXVECTOR3 pos, float fAngle, float fLength, D3DXVECTOR3 rot);

private://�l�ł̂ݎg��
	LPDIRECT3DTEXTURE9		m_pTexture;						// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_pos;							// �ʒu
	D3DXVECTOR3				m_Move;							// ����
	D3DXVECTOR3				m_rot;							// ����
	float					m_fLength;						// ����
	float					m_fAngle;						// �p�x
	float					m_fRadius;						// ���a
	D3DXVECTOR2				m_nSize;						// �T�C�Y
};
#endif