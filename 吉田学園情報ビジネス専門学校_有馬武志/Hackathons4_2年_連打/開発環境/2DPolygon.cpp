//=============================================================================
//
// 2DPolygon���� [2DPolygon.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "scene.h"
#include "2DPolygon.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SLIDE_SPEED	(10.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	C2D::m_pTexture[TEXTURE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	*C2D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ���
			case TEX_SCORE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/number000.png", &m_pTexture[tex]);					break;
			case TEX_PIcon:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/PIcon.png", &m_pTexture[tex]);						break;
			case TEX_Darkness:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/frameeffects003s.jpg", &m_pTexture[tex]);	break;
			case TEX_Cloud1:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/pipo-fog018.jpg", &m_pTexture[tex]);			break;
			case TEX_Cloud2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/pipo-fog017.jpg", &m_pTexture[tex]);			break;
			case TEX_UI000:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/UI_000.png", &m_pTexture[tex]);						break;
			case TEX_UI001:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/UI_001.png", &m_pTexture[tex]);						break; 
			case TEX_Blood000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/EFFECT/blood.jpg", &m_pTexture[tex]);				break; 
			case TEX_BossLabel:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BOSS/Boss_Label.jpg", &m_pTexture[tex]);				break; 
			case TEX_Versus:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/UI/VS.png", &m_pTexture[tex]);							break;
			case TEX_VsSelect:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/Window.png", &m_pTexture[tex]);					break;
			case TEX_Type:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/TYPE.png", &m_pTexture[tex]);					break; 
			case TEX_Stage:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/VERSUS/Stage000.jpg", &m_pTexture[tex]);				break;
			case TEX_Icon:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/Player_Icon.png", &m_pTexture[tex]);				break;

			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	C2D::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_MAX; nCount++)
	{//�S�摜�j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}
//==================================================================================================//
//    * ���͊֐� *
//==================================================================================================//
void C2D::Set(D3DXVECTOR3 pos, float fLengthX, float fLengthY, float fRot, int nUV, int nUV_X, int nUV_Y, D3DXCOLOR col, TEXTURE Texture)
{
	m_pos = pos;
		m_pTex = Load(Texture);
		m_fLengthX = fLengthX;
		m_fLengthY = fLengthY;
		m_DrawType = CScene::DRAW_TYPE_NORMAL;
		
		//Vtx�̕ύX
		VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

								//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);

		//�J���[�ݒ�
		pVtx[0].col = col;	// A = �����x
		pVtx[1].col = col;
		pVtx[2].col = col;
		pVtx[3].col = col;

		//�e�N�X�`�����W�ݒ�
		pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
		pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
		pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
		pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

		//���_BUFFER���A�����b�N����
		m_pVtxBuff->Unlock();
}
//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT  C2D::Init(void)
{
	// �|���S���̈ʒu��ݒ�
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);
	m_fLengthX = 50;
	m_fLengthY = 50;
	CManager::GetRenderer();

	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	// ���_�o�b�t�@�̐���
	pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//�m�ۂ���BUFFER�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	float fRot = 0.0f;

	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void C2D::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{// ���_�o�b�t�@�̔j��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	delete this;
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void C2D::Update(void)
{

}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void C2D::Draw(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
	if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; };

	//���_BUFFER���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pD3DDevice->SetFVF(FVF_VERTEX_2D);	// ���_�t�H�[�}�b�g�̐ݒ�

										//�e�N�X�`���̐ݒ�
	if (m_pTex != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, m_pTex[0]);
	}//�e�N�X�`���폜

	//�|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->SetTexture(0, NULL);

}
//=============================================================================
// ���_���̐ݒ�
//=============================================================================
void C2D::SetPosition(float fRot)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) + (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) + (cosf(fRot) * m_fLengthX), m_pos.y - (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * m_fLengthY) - (cosf(fRot) * m_fLengthX), m_pos.y + (sinf(fRot) * m_fLengthX) - (cosf(fRot) * m_fLengthY), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�{���̐ݒ�
//=============================================================================
void C2D::SetPosition2(float fSize)
{
	VERTEX_2D *pVtx;
	float fLengthX = m_fLengthX * fSize;
	float fLengthY = m_fLengthY * fSize;
	float fRot = D3DX_PI;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * fLengthY) + (cosf(fRot) * fLengthX), m_pos.y - (sinf(fRot) * fLengthX) + (cosf(fRot) * fLengthY), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (sinf(fRot) * fLengthY) - (cosf(fRot) * fLengthX), m_pos.y + (sinf(fRot) * fLengthX) + (cosf(fRot) * fLengthY), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * fLengthY) + (cosf(fRot) * fLengthX), m_pos.y - (sinf(fRot) * fLengthX) - (cosf(fRot) * fLengthY), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x - (sinf(fRot) * fLengthY) - (cosf(fRot) * fLengthX), m_pos.y + (sinf(fRot) * fLengthX) - (cosf(fRot) * fLengthY), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * UV�ύX *
//==================================================================================================//
void C2D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtx�̕ύX
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
	pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * UV�ύX *
//==================================================================================================//
void C2D::SetUV_Camera(float fUV_X, float fUV_Y, float fDiameter)
{
	//Vtx�̕ύX
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	D3DXVECTOR3 pos = CCamera::camera.m_posV;
							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2((pos.x * fDiameter) + fUV_X, (pos.z * (-fDiameter * 1.65f)) + fUV_Y);
	pVtx[1].tex = D3DXVECTOR2((pos.x * fDiameter) + 1.0f + fUV_X, (pos.z * (-fDiameter * 1.65f)) + fUV_Y);
	pVtx[2].tex = D3DXVECTOR2((pos.x * fDiameter) + fUV_X, (pos.z * (-fDiameter * 1.65f)) + 1.0f + fUV_Y);
	pVtx[3].tex = D3DXVECTOR2((pos.x * fDiameter) + 1.0f + fUV_X, (pos.z * (-fDiameter * 1.65f)) + 1.0f + fUV_Y);


	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * UV���Q�[�W�^�ɕύX *
//==================================================================================================//
void	C2D::SetGageUV(float fMaxLengthX)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^
	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_fLengthX / fMaxLengthX), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_fLengthX / fMaxLengthX), 1.0f);


	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * �Q�[�W�^�ɕύX *
//==================================================================================================//
void C2D::SetGage(float fLengthX, bool bDirection)
{
	//Vtx�̕ύX
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	m_fLengthX = fLengthX;

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX)	,-m_fLengthY, 0.0f) + m_pos;
	pVtx[1].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f)	,-m_fLengthY, 0.0f) + m_pos;
	pVtx[2].pos = D3DXVECTOR3((bDirection ? 0.0f : -fLengthX)	,m_fLengthY, 0.0f)	+ m_pos;
	pVtx[3].pos = D3DXVECTOR3((bDirection ? fLengthX : 0.0f)	,m_fLengthY, 0.0f)	+ m_pos;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void C2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�J���[�����x(���E)�̐ݒ�
//=============================================================================
void	C2D::SetSideAlpha(float fCol, float fMinCol, int nID)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	D3DXCOLOR col = pVtx[0 + nID].col;
	col.a += fCol;
	if (col.a >= 1.0f) { col.a = 1.0f; }
	if (col.a <= fMinCol) { col.a = fMinCol; }

	pVtx[0 + nID].col = col;
	pVtx[2 + nID].col = col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void C2D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	for (int nCount = 0; nCount < 4; nCount++) { pVtx[nCount].tex += uv; }

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �A�j���[�V�����|���S���̐ݒ�
//=============================================================================
void	C2DAnim::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed,
	CSceneAnim3D::ANIMATION animation, D3DXCOLOR col, C2D::TEXTURE Texture)
{
	C2D::Set(pos, fLengthX, flengthY, fRot, nPtnAnim, nPtnWide, nPtnHeight, col, Texture);
	m_animation = animation;
	m_nCntAnim = 0;
	m_nPtnAnim = nPtnAnim;
	m_nPtnWide = nPtnWide;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
}
//=============================================================================
// �A�j���[�V�����|���S���̍X�V����
//=============================================================================
void	C2DAnim::Update(void)
{
	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV�ύX
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//�摜�͈̔͊O
			if (m_animation == CSceneAnim3D::ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}//�A�j���[�V�����X�V
		SetUV(m_nPtnAnim, m_nPtnWide, m_nPtnHeight);
	}
}

//=============================================================================
// �J�����t���Y���|���S���̐ݒ菈��
//=============================================================================
void C2DCameraBG::Set(D3DXVECTOR3 pos, float fLengthX, float flengthY, float fRot, float fUV_X, float fUV_Y, float fDiameter, D3DXCOLOR col, C2D::TEXTURE Texture)
{
	C2D::Set(pos, fLengthX, flengthY, fRot, 0, 1, 1, col, Texture);
	m_fUV_X = 0.0f;
	m_fUV_Y = 0.0f;
	m_fUV_XPlus = fUV_X;
	m_fUV_YPlus = fUV_Y;
	m_fDiameter = fDiameter;
}
//=============================================================================
// �J�����t���Y���|���S���̍X�V����
//=============================================================================
void	C2DCameraBG::Update(void)
{
	m_fUV_X += m_fUV_XPlus;
	m_fUV_Y += m_fUV_YPlus;
	SetUV_Camera(m_fUV_X, m_fUV_Y, m_fDiameter);
}

//==================================================================================================//
//    * ���͊֐� *
//==================================================================================================//
void C2DPolygon::Set(D3DXVECTOR3 pos, float fLengthX, float fLengthY, float fRot, int nUV, int nUV_X, int nUV_Y, float fCntState, STATE state, D3DXCOLOR col, TEXTURE Texture)
{
	m_col = col;
	m_fCntState = fCntState;
	m_state = state;
	C2D::Set(pos, fLengthX, fLengthY, fRot, nUV, nUV_X, nUV_Y, col, Texture);
}
//=============================================================================
// �ʏ�|���S���̍X�V����
//=============================================================================
void	C2DPolygon::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		switch (m_state)
		{
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADEIN:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADE:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_FADEOUT; }
			SetColor(m_col);
			break;
		case STATE_SLIDEIN:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * (1.0f - m_col.a), 2), 0.0f, 0.0f);
			SetPosition(D3DX_PI);
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDEOUT:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * m_col.a, 2), 0.0f, 0.0f);
			SetPosition(D3DX_PI);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDEIN2:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * (1.0f - m_col.a), 2), powf(SLIDE_SPEED * (1.0f - m_col.a), 2), 0.0f);
			SetPosition(D3DX_PI);
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_SLIDEOUT2:
			GetPosition() += D3DXVECTOR3(powf(SLIDE_SPEED * m_col.a, 2), powf(SLIDE_SPEED * m_col.a, 2), 0.0f);
			SetPosition(D3DX_PI);
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_BIG:
			if (m_fCntState < 120.0f)
			{
				m_fCntState += 8.0f;
				if (m_fCntState >= 120.0f) { m_fCntState = 120.0f; }
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		case STATE_SMALL:
			if (m_fCntState > 80.0f)
			{
				m_fCntState -= 8.0f;
				if (m_fCntState <= 80.0f) { m_fCntState = 80.0f; }
				SetPosition2(m_fCntState * 0.01f);
			}
			break;
		}
	}
}