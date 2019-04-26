//=============================================================================
//
// �|���S������ [SceneAnim3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"SceneAnim3D.h"
#include"Renderer.h"
#include "manager.h"
#include "camera.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// ����������
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
// �X�V����
//=============================================================================
void CSceneAnim3D::Update(void)
{//�A�j���[�V����
	VERTEX_3D *pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXVECTOR3 &pos = GetPosition();	D3DXVECTOR3 &rot = GetRotation();	D3DXCOLOR	&col = GetColor();
	D3DXVECTOR3 &length = GetLength();
	STATE &m_state = GetState();

	if (m_state == STATE_STOP)
	{
		float &m_fCntState = GetfCntState();
		D3DXCOLOR &m_col = GetColor();
		m_col.r -= m_fCntState;
		if (m_col.r < 0.0f) { m_col.r = 1.0f; m_col.a = 1.0f; m_state = STATE_NORMAL; }
		return;
	}

 //���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV�ύX
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//�摜�͈̔͊O
			if (m_animation == ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}

		//UV�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[1].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[2].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
		pVtx[3].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
	}

	CScene3D::Update();

	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneAnim3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, bool bBillBoard,
	DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state)
{
	CScene3D::Set(pos, rot, col, length, CScene3D::TEX_MAX, nPtnAnim, nPtnWide, nPtnHeight, bBillBoard, DrawType);
	BindTexture(Load(nType));
	m_animation = animation;
	GetState() = state;
	GetfCntState() = 0.0f;
	m_nCntAnim = -1;
	m_nPtnAnim = nPtnAnim;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
	m_nPtnWide = nPtnWide;
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneAnimEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, bool bBillBoard,
	DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CSceneAnim3D::Set(pPos[0], rot, col, length, nType, bBillBoard, DrawType, nPtnAnim, nPtnWide, nPtnHeight, nPtnSpeed, animation, state);
	m_pPos = pPos;
	m_pScene = pScene;
	m_Distance = pos;
}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneAnimEffect::Update()
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition() = m_pPos[0] + m_Distance; SetMtx(); }
	CSceneAnim3D::Update();
}
