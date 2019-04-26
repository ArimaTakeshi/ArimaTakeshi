//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"Renderer.h"
#include "SceneEnemy.h"
#include "SceneBoss.h"
#include "ScenePlayer.h"
#include "dungeon.h"
#include "collision.h"
#include "manager.h"
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
LPDIRECT3DTEXTURE9	CScene3D::m_pTexture[TEXTURE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	*CScene3D::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ���
			 //���r�����X//***********************************************************************
			case TEX_ITEM:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Item_All2.jpg", &m_pTexture[tex]);			break;
			case TEX_TRAP:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/MAP/ITEM/Trap_All.jpg", &m_pTexture[tex]);			break;
			case TEX_HEART:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Nuclear000.png", &m_pTexture[tex]);	break;
			case TEX_BOMB000:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Guard000.jpg", &m_pTexture[tex]);		break;
			case TEX_CHARGE:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/Effect000.jpg", &m_pTexture[tex]);	break;
			case TEX_MARKER:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/marker100.jpg", &m_pTexture[tex]);		break;
			case TEX_MATTE:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/PATTERN/Pattern_100.jpg", &m_pTexture[tex]);		break;
			case TEX_BG000:		D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/EFFECT/BG001.jpg", &m_pTexture[tex]);		break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	CScene3D::UnLoad(void)
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
//=============================================================================
// ����������
//=============================================================================
HRESULT CScene3D::Init(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	m_pVtxBuff = NULL;
	m_pTex = NULL;

	// ���_���̍쐬
	MakeVertex(pD3DDevice);

	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��;
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene3D::Update(void)
{
	if (m_state != STATE_NORMAL)
	{
		switch (m_state)
		{
		case STATE_UVFLOW_1:
			m_fCntState += 0.01f;
		case STATE_UVFLOW_0:
			m_fCntState += 0.02f;
			//UV�̐ݒ�
			VERTEX_3D *pVtx;

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			pVtx[0].tex = D3DXVECTOR2(0.0f + m_fCntState, 0.0f + m_fCntState);
			pVtx[1].tex = D3DXVECTOR2(1.0f + m_fCntState, 0.0f + m_fCntState);
			pVtx[2].tex = D3DXVECTOR2(0.0f + m_fCntState, 1.0f + m_fCntState);
			pVtx[3].tex = D3DXVECTOR2(1.0f + m_fCntState, 1.0f + m_fCntState);

			//���_�o�b�t�@�̃A�����b�N
			m_pVtxBuff->Unlock();
		case STATE_FADESPIN:
			m_fCntState += 0.05f;
			m_rot.y += D3DX_PI * 0.03f;
			if (m_fCntState >= 1.0f) { Uninit(); return; }
			m_col.a = 1.0f - m_fCntState;//�����x�ύX
			m_fLengthX *= 1.0f + ((1.0f - m_fCntState) * 0.25f);
			m_fLengthZ *= 1.0f + ((1.0f - m_fCntState) * 0.25f);
			SetColor(m_col);
			SetSize(m_fLengthX, m_fLengthZ);
			break;
		case STATE_FADEIN:
			m_col.a += 0.05f;//�����x�ύX
			if (m_col.a > 1.0f) { m_col.a = 1.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_FADEOUT:
			m_fCntState += 0.05f;
			m_col.a = 1.0f - m_fCntState;//�����x�ύX
			if (m_col.a < 0.0f) { m_col.a = 0.0f; }
			SetColor(m_col);
			if (m_fCntState >= 1.0f) { Uninit(); return; }
			break;
		case STATE_FADEOUT2:
			m_col.a -= 0.05f;//�����x�ύX
			if (m_col.a < 0.0f) { m_col.a = 0.0f; m_state = STATE_NORMAL; }
			SetColor(m_col);
			break;
		case STATE_BFLOW_IN:
			if (m_col.a != 1.0f)
			{//�����x������Ȃ��I
				m_col.a += 0.01f;//�����x�ύX
				if (m_col.a >= 1.0f) { m_col.a = 1.0f; }
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.002f, 0.001f));
			break;
		case STATE_BFLOW_OUT:
			if (m_col.a != 0.0f)
			{//�����x������Ȃ��I
				m_col.a -= 0.01f;//�����x�ύX
				if (m_col.a <= 0.0f)
				{
					m_col.a = 0.0f;
					m_state = STATE_NORMAL;
					return;
				}
				SetColor(m_col);
			}
			PlusUV(D3DXVECTOR2(0.02f, 0.01f));
			break;
		}

		if (m_state >= STATE_EXPLOSION0 && m_state <= STATE_S_PAIR1)
		{//�A�C�e���܂��̓g���b�v
			if (m_state < (int)STATE_S_HEEL0)
			{//���蕨�łȂ�
				if (m_state < STATE_HEEL0)
				{//�g���b�v�Ȃ�
					if (m_col.r < 1.0f)
					{//�ғ���
						m_col.r += 0.01f;
						if (m_col.r >= 1.0f)
						{
							m_col.r = 1.0f;
							SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
						}
					}
				}
				CScenePlayer *pPlayer;
				D3DXVECTOR3 *pPlayer_pos;
				D3DXVECTOR3 *pos = GetPosition();
				float *fLengthX = GetfLengthX();
				float *fLengthZ = GetfLengthZ();

				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{//�v���C���[����]
					pPlayer = CManager::GetPlayer(nCount);
					if (pPlayer != NULL)
					{//��������Ă���Ȃ�
						pPlayer_pos = pPlayer->GetPosition();
						if (pPlayer_pos[0].x > pos[0].x - fLengthX[0] && pPlayer_pos[0].x < pos[0].x + fLengthX[0] &&
							pPlayer_pos[0].z > pos[0].z - fLengthZ[0] && pPlayer_pos[0].z < pos[0].z + fLengthZ[0] && pPlayer->GetfLife()[0] > 0.0f)
						{//�͈͓� && �������Ă���
							if (m_state < STATE_HEEL0)
							{//�g���b�v�Ȃ�
								if (m_col.r == 1.0f)
								{
									SetColor(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));
									m_col.r = 0.0f;
									ItemEffect(pPlayer); return;
								}
								return;
							}
							else
							{//�A�C�e���Ȃ�
								ItemEffect(pPlayer);
								Uninit(); return;
							}
						}
					}
				}
			}
			else
			{//���蕨
				CScenePlayer *pPlayer;
				D3DXVECTOR3 pos;
				float fLengthX, fLengthZ;

				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{//�v���C���[����]
					pPlayer = CManager::GetPlayer(nCount);
					if (pPlayer != NULL)
					{//�����蔻��
						CSceneModel::GetLength(pPlayer->GetModel()[0], fLengthX, fLengthZ);
						Collision(pPlayer->GetPosition()[0], pPlayer->GetPositionOld()[0], fLengthX, fLengthZ);

						//������
						pos = pPlayer->GetPosition()[0];
						if (m_pos.x + m_fLengthX * 2.0f > pos.x && m_pos.x - m_fLengthX * 2.0f < pos.x &&
							m_pos.z + m_fLengthZ * 2.0f > pos.z && m_pos.z - m_fLengthZ * 2.0f < pos.z && pPlayer->GetfLife()[0] > 0.0f)
						{//�͈͓� && �������Ă���
							if (pPlayer->GetScore()->GetnNumber() >= m_fCntState)
							{//������@�X�R�A������Ă���
								CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
								CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(pPlayer->GetPlayerID());	//�W���C�p�b�h���l��

								if (pInputKey->GetTrigger(DIK_A) || pInputPad->GetTrigger(INPUT_B))
								{//������
									ItemBuy();	//�X������
									pPlayer->GetScore()->AddNumber(-(int)m_fCntState);
									m_state = (STATE)((int)m_state - ((int)STATE_S_HEEL0 - (int)STATE_HEEL0));
									CCollision::DestroyRange(m_pos, m_fLengthX * 1.5f, m_fLengthZ * 2.0f, CScene::OBJTYPE_NUMBER);
									ItemEffect(pPlayer);
									Uninit(); return;
								}
							}
						}
					}
				}
			}
		}//if(�A�C�e�� || �g���b�v)
	}//if(!=STATE_NORMAL)
}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���b�N�X

	if (CScene::DrawPrepare(m_DrawType, pD3DDevice)) { return; }

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	if (m_pTex != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, m_pTex[0]);
	}//�e�N�X�`���폜

	// �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->SetTexture(0, NULL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CScene3D::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �����蔻��
//=============================================================================
void CScene3D::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLengthX, float &fLengthZ)
{
	if (m_pos.x + m_fLengthX > pos.x - fLengthX && m_pos.x - m_fLengthX < pos.x + fLengthX)
	{//�������͈͓� //�㉺Hit
		if (m_pos.z + m_fLengthZ > pos.z - fLengthZ && m_pos.z + m_fLengthZ <= posold.z - fLengthZ)
		{//��
			pos.z = m_pos.z + m_fLengthZ + fLengthZ;
		}
		else if (m_pos.z - m_fLengthZ < pos.z + fLengthZ && m_pos.z - m_fLengthZ >= posold.z + fLengthZ)
		{//��
			pos.z = m_pos.z - m_fLengthZ - fLengthZ;
		}
	}
	if (m_pos.z + m_fLengthZ > pos.z - fLengthZ && m_pos.z - m_fLengthZ < pos.z + fLengthZ)
	{//�c�����͈͓� //��Hit
		if (m_pos.x + m_fLengthX > pos.x - fLengthX && m_pos.x + m_fLengthX <= posold.x - fLengthX)
		{//�E
			pos.x = m_pos.x + m_fLengthX + fLengthX;
		}
		else if (m_pos.x - m_fLengthX < pos.x + fLengthX && m_pos.x - m_fLengthX >= posold.x + fLengthX)
		{//��
			pos.x = m_pos.x - m_fLengthX - fLengthX;
		}
	}
}
//=============================================================================
// �ݒ�
//=============================================================================
void CScene3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, TEXTURE nType, int nUV, int nUV_X, int nUV_Y, DRAW_TYPE DrawType)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_pTex == NULL) { m_pTex = Load(nType); };
			m_col = col;

			m_pos = pos;
			m_rot = rot;
			m_fLengthX = fLengthX;
			m_fLengthZ = fLengthZ;
			m_DrawType = DrawType;

			pVtx[0].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, m_fLengthZ);
			pVtx[1].pos = D3DXVECTOR3(m_fLengthX, 0.1f, m_fLengthZ);
			pVtx[2].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, -m_fLengthZ);
			pVtx[3].pos = D3DXVECTOR3(m_fLengthX, 0.1f, -m_fLengthZ);

			//���_�J���[�̐ݒ�
			pVtx[0].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[1].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[2].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			pVtx[3].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
			//UV�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[1].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y));
			pVtx[2].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X)				 , (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));
			pVtx[3].tex = D3DXVECTOR2((nUV % nUV_X) * (1.0f / nUV_X) + (1.0f / nUV_X), (nUV / nUV_X) * (1.0f / nUV_Y) + (1.0f / nUV_Y));

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void	CScene3D::SetColor(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_col = col;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[1].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[2].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j
	pVtx[3].col = m_col;  //�F�̎w��i0.0f �` 1.0f�j&�����x�i0.0f�@�`�@1.0f�j

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �F�̐ݒ�
//=============================================================================
void	CScene3D::SetSize(float fLengthX, float fLengthZ)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�l����
	m_fLengthX = fLengthX;
	m_fLengthZ = fLengthZ;

	pVtx[0].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, m_fLengthZ);
	pVtx[1].pos = D3DXVECTOR3(m_fLengthX, 0.1f, m_fLengthZ);
	pVtx[2].pos = D3DXVECTOR3(-m_fLengthX, 0.1f, -m_fLengthZ);
	pVtx[3].pos = D3DXVECTOR3(m_fLengthX, 0.1f, -m_fLengthZ);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//==================================================================================================//
//    * ����������UV���W�ύX *
//==================================================================================================//
void CScene3D::SetUV(int nUV, int nUV_X, int nUV_Y)
{
	//Vtx�̕ύX
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

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
//=============================================================================
// UV�p�^�[�����ݒ�
//=============================================================================
void	CScene3D::SetUVPattern(float fUV_X, float fUV_Y)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

	//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	//pVtx[0].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[1].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);
	//pVtx[2].tex = D3DXVECTOR2((m_pos.x + m_fLengthX) * fUV_X, (m_pos.z - m_fLengthZ) * fUV_Y);
	//pVtx[3].tex = D3DXVECTOR2((m_pos.x - m_fLengthX) * fUV_X, (m_pos.z + m_fLengthZ) * fUV_Y);

	pVtx[0].tex = D3DXVECTOR2((m_pos.x / m_fLengthX) * fUV_X, (m_pos.z / m_fLengthZ) * fUV_Y);
	pVtx[1].tex = D3DXVECTOR2(((m_pos.x + m_fLengthX) / m_fLengthX) * fUV_X, ((m_pos.z / m_fLengthZ) * fUV_Y));
	pVtx[2].tex = D3DXVECTOR2((m_pos.x / m_fLengthX) * fUV_X, ((m_pos.z + m_fLengthZ) / m_fLengthZ) * fUV_Y);
	pVtx[3].tex = D3DXVECTOR2(((m_pos.x + m_fLengthX) / m_fLengthX) * fUV_X, ((m_pos.z + m_fLengthZ) / m_fLengthZ) * fUV_Y);

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// UV���Z����
//=============================================================================
void	CScene3D::PlusUV(D3DXVECTOR2 uv)
{
	VERTEX_3D *pVtx;		//���_���ւ̃|�C���^

							//���_BUFFER�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�ݒ�
	pVtx[0].tex += uv;
	pVtx[1].tex += uv;
	pVtx[2].tex += uv;
	pVtx[3].tex += uv;

	//���_BUFFER���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// �A�C�e���̌���
//=============================================================================
void	CScene3D::ItemEffect(CScenePlayer *&pPlayer)
{
	CSound *pSound = CManager::GetSound();	//�T�E���h�̃|�C���^���擾
	CSceneEnemy *pSceneEnemy;
	CSceneAnim3D	*pSceneAnim3D;
	float	fRand;
	int		nRand;
	bool	bSEffect = false;	//�X�e�[�^�X�A�b�v�G�t�F�N�g

	switch (m_state)
	{
	//case STATE_EXPLOSION0:
	//	pSound->Play(CSound::LABEL_EXPLOSION000);
	//	CSceneBullet::ShotAttack(CSceneBullet::SHOT_TROP, CSceneBullet::ATK_PTN03, D3DXVECTOR3(GetPosition()[0].x, PLAYER_Y, GetPosition()[0].z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (rand() % (int)(D3DX_PI * 100.0f)) * 0.01f,
	//		true, -0.05f, 0.98f, SHOT_LIFE - 6.0f, 0.1f, 0.0f,
	//		CHIP_SIZE / 2, CHIP_SIZE / 2, D3DX_PI, 0.0f, 1, 0, CSceneBullet::CHANGE_NO,CScenePlayer::GetnStage() * 15.0f + 500.0f, true, NULL, 16 * 4 + 2);
	//	break;
	//case STATE_EXPLOSION1:
	//	pSound->Play(CSound::LABEL_EXPLOSION001);
	//	CSceneBullet::ShotAttack(CSceneBullet::SHOT_TROP, CSceneBullet::ATK_PTN03, D3DXVECTOR3(GetPosition()[0].x, PLAYER_Y, GetPosition()[0].z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), (rand() % (int)(D3DX_PI * 100.0f)) * 0.01f,
	//		true, -0.05f, 0.98f, SHOT_LIFE - 6.0f, 0.1f, 0.0f,
	//		CHIP_SIZE, CHIP_SIZE, D3DX_PI, 0.0f, 1, 0, CSceneBullet::CHANGE_NO, CScenePlayer::GetnStage() * 20.0f + 1000.0f, true, NULL, 16 * 4 + 2);	
	//	break;
	//case STATE_ICE:
	//	pSound->Play(CSound::LABEL_ICE);
	//	pPlayer->GetnIce() = 601;
	//	if (SceneCreate(pSceneAnim3D, DUNGEON_PRIORYITY))
	//	{//�����ł����Ȃ�@//�Ή�
	//		pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_ICE, CScene::DRAW_TYPE_ADD,
	//			0, 5, 2, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
	//	}
	//	break;
	//case STATE_LIGHTNING:
	//	pSound->Play(CSound::LABEL_SPARK);
	//	pPlayer->GetnLightning() = 601;
	//	if (SceneCreate(pSceneAnim3D, DUNGEON_PRIORYITY))
	//	{//�����ł����Ȃ�@//�Ή�
	//		pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_LIGHTNING, CScene::DRAW_TYPE_ADD,
	//			0, 5, 2, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
	//	}
	//	break;
	//case STATE_FIRE:
	//	pSound->Play(CSound::LABEL_FIRE);
	//	pPlayer->GetnFire() = 601;
	//	if (SceneCreate(pSceneAnim3D, DUNGEON_PRIORYITY))
	//	{//�����ł����Ȃ�@//�Ή�
	//		pSceneAnim3D->Set(GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_FIRE, CScene::DRAW_TYPE_ADD,
	//			0, 10, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
	//	}
	//	break;
	//case STATE_WIND: 
	//	pSound->Play(CSound::LABEL_WIND);
	//	pPlayer->GetMove()[0] *= 10.0f;
	//	pPlayer->GetfSlip() = 1.2f;
	//	break;
	case STATE_MONSTER:
		fRand = (rand() % (int)(D3DX_PI * 100)) * 0.01f;
		nRand = (rand() % 2) * 2 + 2;
		for (int nCount = 0; nCount < nRand; nCount++)
		{
			if (SceneCreate(pSceneEnemy, MODEL_PRIORITY))
			{//�G�o��
				pSceneEnemy->Set(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + ((D3DX_PI * 2 / nRand) * nCount)), 0.0f, cosf(fRand + ((D3DX_PI * 2 / nRand) * nCount))) * 15.0f,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TANKD, CSceneModel::MODEL_TANKU,
					(CSceneModel::TEXTURE)(rand() % 8 + (int)CSceneModel::TEX_PTN_01), (CSceneModel::TEXTURE)(rand() % 8 + (int)CSceneModel::TEX_PTN_01), CScene::DRAW_TYPE_NORMAL);
			}
			if (SceneCreate(pSceneAnim3D, S3D_PRIORITY))
			{//�����ł����Ȃ�@//��
				pSceneAnim3D->Set(GetPosition()[0] + D3DXVECTOR3(sinf(fRand + ((D3DX_PI * 2 / nRand) * nCount)), 0.0f, cosf(fRand + ((D3DX_PI * 2 / nRand) * nCount))) * 15.0f,
					D3DXVECTOR3(0.0f, (rand() % (int)(D3DX_PI * 200.0f)) * 0.01f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_APPEAR, CScene::DRAW_TYPE_SUBTRACT,
					0, 10, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
			}
		}
		Uninit();
		break;
	//�A�C�e��
	//case STATE_HEEL0:	pPlayer->Heel(0.075f, true); pSound->Play(CSound::LABEL_HEEL); break;
	//case STATE_HEEL1:	pPlayer->Heel(0.1f, true); pSound->Play(CSound::LABEL_HEEL); break;
	//case STATE_HEEL2:	pPlayer->Heel(0.125f, true); pSound->Play(CSound::LABEL_HEEL); break;
	//case STATE_HEEL3:	pPlayer->Heel(0.25f, true); pSound->Play(CSound::LABEL_HEEL); break;
	//case STATE_HEEL4:	pPlayer->Heel(0.5f, true); pSound->Play(CSound::LABEL_HEEL); break;
	//case STATE_SCORE0:	
	//	if (pPlayer->GetItem() != NULL) 
	//	{ if (pPlayer->GetItem()->GetType() == ITEM::TYPE_SCOREUP) { pPlayer->GetScore()->AddNumber(3000); } }
	//	pPlayer->GetScore()->AddNumber(3000); pSound->Play(CSound::LABEL_SCORE);
	//	break;
	//case STATE_SCORE1:	
	//	if (pPlayer->GetItem() != NULL)
	//	{ if (pPlayer->GetItem()->GetType() == ITEM::TYPE_SCOREUP) { pPlayer->GetScore()->AddNumber(20000); } }
	//	pPlayer->GetScore()->AddNumber(20000); pSound->Play(CSound::LABEL_SCORE);
	//	break;
	case STATE_LIFE:	pPlayer->PlusLifeUP(1);	pPlayer->PlusLevel(0); pPlayer->Heel(0.25f, true);	bSEffect = true; break;
	case STATE_DEFENSE:	pPlayer->PlusDefUP(1);	pPlayer->PlusLevel(0);	bSEffect = true; break;
	case STATE_ATTACK:	pPlayer->PlusAtkUP(1);	pPlayer->PlusLevel(0);	bSEffect = true; break;
	case STATE_LIFEUP:	pPlayer->PlusLifeUP(10);	pPlayer->PlusLevel(0); pPlayer->Heel(1.0f, true);	bSEffect = true; break;
	case STATE_DEFUP:	pPlayer->PlusDefUP(10);	pPlayer->PlusLevel(0);	bSEffect = true; break;
	case STATE_ATKUP:	pPlayer->PlusAtkUP(10);	pPlayer->PlusLevel(0);	bSEffect = true; break;
	//case STATE_SPDUP:	pPlayer->SetItem(ITEM::TYPE_SPDUP);		pSound->Play(CSound::LABEL_ITEM);	break;
	//case STATE_PAIR0:	pPlayer->SetItem(ITEM::TYPE_PAIR0);		pSound->Play(CSound::LABEL_ITEM);	break;
	//case STATE_NORIVER:	pPlayer->SetItem(ITEM::TYPE_NORIVER);	pSound->Play(CSound::LABEL_ITEM);	break;
	//case STATE_NOSTOP:	pPlayer->SetItem(ITEM::TYPE_NOSTOP);	pSound->Play(CSound::LABEL_ITEM);	break;
	//case STATE_CHARGEUP:pPlayer->SetItem(ITEM::TYPE_CHARGEUP);	pSound->Play(CSound::LABEL_ITEM);	break;
	//case STATE_SCOREUP:	pPlayer->SetItem(ITEM::TYPE_SCOREUP);	pSound->Play(CSound::LABEL_ITEM);	break;
	//case STATE_PAIR1:	pPlayer->SetItem(ITEM::TYPE_PAIR1);		pSound->Play(CSound::LABEL_ITEM);	break;
	}

	if (bSEffect)
	{
		CSceneAnimEffect *pSceneAnim3DE;
		if (SceneCreate(pSceneAnim3DE, S3DF_PRIORITY))
		{//�����ł����Ȃ�@//�p���[�A�b�v
			pSceneAnim3DE->Set(pPlayer->GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_STATUS_UP, CScene::DRAW_TYPE_NORMAL,
				0, 10, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL, pPlayer->GetPosition(), pPlayer->GetThisScene());
		}
	}
}
//=============================================================================
// �A�C�e���̌���
//=============================================================================
void	CScene3D::BreakSale(void)
{
	CScene **PScene = CScene::GetScene(S3DF_PRIORITY);

	for (int nCntScene = 0; nCntScene < CScene::GetnMemoryAll(S3DF_PRIORITY); nCntScene++)
	{//�S�V�[�������
		if (PScene[nCntScene] != NULL)
		{//���g��NULL�łȂ�
			if (PScene[nCntScene]->GetObjType() == CScene::OBJTYPE_SALE)
			{//���蕨����
				((CScene3D*)PScene[nCntScene])->GetState()[0] = (CScene3D::STATE)((int)((CScene3D*)PScene[nCntScene])->GetState()[0] - ((int)CScene3D::STATE_S_HEEL0 - (int)CScene3D::STATE_HEEL0));
				((CScene3D*)PScene[nCntScene])->SetObjType((CScene::OBJTYPE_NONE));
			}//if(BOSS)
		}//if(!= NULL)
	}//for()
}
//=============================================================================
// �A�C�e���̌���
//=============================================================================
void	CScene3D::ItemBuy(void)
{
	CScene **PScene = CScene::GetScene(1);

	for (int nCntScene = 0; nCntScene < CScene::GetnMemoryAll(1); nCntScene++)
	{//�S�V�[�������
		if (PScene[nCntScene] != NULL)
		{//���g��NULL�łȂ�
			if (PScene[nCntScene]->GetObjType() == CScene::OBJTYPE_BOSS)
			{//�{�X�Ō���
				if (((CSceneBoss*)PScene[nCntScene])->GetTexture() == CSceneBoss::TEX_MANAGER)
				{//�X���Ȃ�
					if (((CSceneManager*)PScene[nCntScene])->GetManager() < CSceneManager::MANAGER_DAMAGE)
					{//��e���Ă��Ȃ�
						((CSceneManager*)PScene[nCntScene])->GetManager() = CSceneManager::MANAGER_BUY;
					}
				}//if(�X��)
			}//if(BOSS)
		}//if(!= NULL)
	}//for()
}
//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void CSceneEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ,
	TEXTURE nType, int nUV, int nUV_X, int nUV_Y, DRAW_TYPE DrawType, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CScene3D::Set(pos, rot, col, fLengthX, fLengthZ, nType, nUV, nUV_X, nUV_Y, DrawType);
	m_pPos = pPos;
	m_pScene = pScene;
}
//=============================================================================
// �G�t�F�N�g�̍X�V
//=============================================================================
void CSceneEffect::Update(void)
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition()[0] = m_pPos[0]; }
	CScene3D::Update();
}
//=============================================================================
// �`�揈��
//=============================================================================
void CSceneEffect::Draw(void)
{
	LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	if (CScene::DrawPrepare(GetDrawType(), pD3DDevice)) { return; }

	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos = GetPosition()[0];
	D3DXVECTOR3 m_rot = GetRotation()[0];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	if (GetTexture() != NULL)
	{//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, GetTexture()[0]);
	}//�e�N�X�`���폜

	 // �|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pD3DDevice->SetTexture(0, NULL);
}
