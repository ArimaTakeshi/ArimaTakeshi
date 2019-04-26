//=============================================================================
//
// �|���S������ [Scene3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "camera.h"
#include"SceneModel.h"
#include"Renderer.h"
#include "dungeon.h"
#include "manager.h"
#include "SceneBullet.h"
#include "ScenePlayer.h"
#include "SceneEnemy.h"
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
LPDIRECT3DTEXTURE9	CSceneBullet::m_pTexture[TEXTURE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

//=============================================================================
// �摜�̓ǂݍ���
//=============================================================================
LPDIRECT3DTEXTURE9	*CSceneBullet::Load(TEXTURE tex)
{
	if (tex < TEXTURE_MAX)
	{//�͈͊m�F
		if (m_pTexture[tex] == NULL)
		{//�ǂݍ���łȂ��Ȃ�
			LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();
			switch (tex)
			{//�ǂݍ���
			case TEX_BULLET:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Shot_All301.png", &m_pTexture[tex]);	break;
			//case TEX_BULLET2:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Shot_All101.png", &m_pTexture[tex]);	break;
			case TEX_BULLET_S:	D3DXCreateTextureFromFile(pD3DDevice, "data/TEXTURE/BATTLE/JUDGE/Shot_All301_S.png", &m_pTexture[tex]); break;
			}
		}
		return &m_pTexture[tex];
	}
	return NULL;
}
//=============================================================================
// �摜�̉��
//=============================================================================
void	CSceneBullet::UnLoad(void)
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
// �����̍X�V����
//=============================================================================
bool CSceneBullet::LifeUpdate(void)
{
	D3DXCOLOR	*col = GetColor();
	float *fCntState = GetfCntState();

	fCntState[0] += 1.0f;					//�������ԃJ�E���g

	if (fCntState[0] > 0.0f)
	{
		if (fCntState[0] > SHOT_LIFE)
		{
			if (col[0].a < 0.0f) { Uninit(); }
			else
			{//������
				col[0].a -= 0.05f;
				SetColor(col[0]);
			}
			return false;
		}
		else if (col[0].a < 1.0f && m_ObjType == CScene::OBJTYPE_BULLET)
		{
			col[0].a += 0.05f;
			if (col[0].a > 1.0f) { col[0].a = 1.0f; }
			SetColor(col[0]);
			return false;
		}
	}
	else if (fCntState[0] < 0.0f) { return false; }

	return true;
}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneNorBullet::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXVECTOR3 *pos = GetPosition(); D3DXVECTOR3 *rot = GetRotation(); D3DXCOLOR	*col = GetColor();
	float *fCntState = GetfCntState();
	float fSlow = 1.0f;
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();

	if (LifeUpdate())
	{
		int nChange = m_nChange;	//���ʕt�^
		while (nChange > 0)
		{//�����c���Ă���Ȃ�
			switch (nChange % 10)
			{//�`�F���W���ʕt�^
			case CHANGE_SPDUP:		//����
				if (m_fAccelerator < 0.1f) { m_fAccelerator += 0.005f * fSlow; } 
				break;
			case CHANGE_SPDDOWN:	//����
				if(fCntState[0] > SHOT_LIFE * 0.12 * fSlow){ m_move *= 0.85f; }
				break;
			case CHANGE_BACK:	//Spd���������]
				if (m_fSpeed > -0.1f) { m_fSpeed -= 0.1f * fSlow; }
				break;
			case CHANGE_BACK2:	//Spd���������]
				if (fCntState[0] == 60.0f) { m_fSpeed *= -1.0f; }
				break;
			case CHANGE_STRAIGHT:	//��]�l(*)
				m_fTurning *= 1.0f - (1.0f - 0.98f) * fSlow;
				break;
			case CHANGE_SPINUP:
				if (fCntState[0] == 60.0f)
				{
					if (m_fTurning > 0.0f) { m_fTurning += D3DX_PI; }
					else { m_fTurning -= D3DX_PI; }
				}
				break;
			case CHANGE_SLOW:		//�S�̃X�s�[�h�_�E��
				fSlow = 0.98f;
				break;
				//	CHANGE_SPINUP,		//��]�l (+)
				//	CHANGE_SPINDOWN,	//��]�l (-)
				//	CHANGE_HOMING,		//�r���ł����Ȃ�G����������
				//	CHANGE_HOMINGS,		//�r���ł����Ȃ�G������������F�~�܂�
			}
			nChange /= 10;	//��������
		}
		//��F����
		//���l�͈͓��Ȃ�
		m_fSpeed += m_fAccelerator * fSlow;		//����
		rot[0].y += m_fTurning * fSlow;			//����
		//�ړ�
		pos[0] += m_move * fSlow;
		m_move += (D3DXVECTOR3(sinf(rot[0].y), 0.0f, cosf(rot[0].y)) * m_fSpeed) * fSlow;
		m_move *= m_fSlip * fSlow;	//����

		if (fCntState[0] > SHOT_LIFE * 0.5 * fSlow){ m_fTurning *= 0.95f; }
		else if (fCntState[0] > SHOT_LIFE * 0.6 * fSlow){ m_fAccelerator = 0.0f; }
		else if (fCntState[0] > SHOT_LIFE * 0.7 * fSlow) { m_move *= 0.85f; }

		CDungeon *pDungeon = CManager::GetDungeon();
		if (pDungeon != NULL && m_ObjType == CScene::OBJTYPE_BULLET && !m_bDestroy) { pDungeon->ShotCollision((CSceneBullet*)this); }
	}

}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneSetBullet::Update(void)
{
	float *fCntState = GetfCntState();
	if (fCntState[0] < SHOT_LIFE)
	{
		m_fAngleSet += m_fAnglePlus;
		if (((int)fCntState[0] + 1) % m_nInterval == 0)
		{//�Z�b�g����
			if (SetAttack(m_SetType, fCntState[0], m_fAngleSet, m_nNumSet, m_move, m_nUV,m_nInterval)) { return; }
		}
	}
	CSceneNorBullet::Update();
}
//=============================================================================
// �X�V����
//=============================================================================
void CScenePairBullet::Update(void)
{
	float	*fCntState = GetfCntState();
	bool	bLife = false;
	bool	bWallX = false, bWallZ = false;

	if (fCntState[0] < 0) { fCntState[0] = 10; bLife = true; }
	GetPosition()[0] = m_pos2;	//�ꏊ�̍X�V
	CSceneNorBullet::Update();//�e�̍X�V

	if (fCntState[0] >= 0.0f)
	{
		D3DXVECTOR3 *pos = GetPosition(), *rot = GetRotation(), WKpos;

		//�C���̌����ύX
		if (rot[0].y > D3DX_PI) { rot[0].y -= D3DX_PI * 2; }
		if (rot[0].y < -D3DX_PI) { rot[0].y += D3DX_PI * 2; }

		////�p�x�␳
		if ((pos[0].x < -m_fXWall && rot[0].y < 0.0f) || (pos[0].x > m_fXWall && rot[0].y >= 0.0f)) { bWallX = true; }
		if ((pos[0].z > m_fZWall && rot[0].y <= D3DX_PI / 2 && rot[0].y >= -D3DX_PI / 2) ||
			(pos[0].z < -m_fZWall && (rot[0].y >= D3DX_PI / 2 || rot[0].y <= -D3DX_PI / 2))) {
			bWallZ = true;
		}

		if (bWallX)
		{//�ǂɓ������� -> X�ǂȂ�Zrand(), Z�ǂȂ�Xrand() ����p�x�Ď擾 
			WKpos = pos[0] + D3DXVECTOR3(sinf(rot[0].y) * -1.0f, 0.0f, 1.0f * (cosf(rot[0].y) * 1.0f) + (-m_fRangeZ + ((rand() % (int)(m_fRangeZ  * 2000.0f + 1)) * 0.001f)) * (sinf(rot[0].y)));
			GetRotation()[0].y = atan2f(WKpos.x - pos[0].x, WKpos.z - pos[0].z);
		}
		if (bWallZ)
		{//�ǂɓ������� -> X�ǂȂ�Zrand(), Z�ǂȂ�Xrand() ����p�x�Ď擾 
			WKpos = pos[0] + D3DXVECTOR3((sinf(rot[0].y) * 1.0f) + (-m_fRangeX + ((rand() % (int)(m_fRangeX  * 2000.0f + 1)) * 0.001f)) * (cosf(rot[0].y)), 0.0f, cosf(rot[0].y) * -1.0f);
			GetRotation()[0].y = atan2f(WKpos.x - pos[0].x, WKpos.z - pos[0].z);
		}

		m_pos2 = pos[0];		//�ꏊ�̕ۑ�
		m_pos3 += (m_pPos[0] - m_pos3) * 0.1f;
		pos[0] += m_pos3;	//�`��p�ɐe�ƍ���

		m_nNumCount++;
		//�p�x�̍X�V
		if (m_pRot != NULL) { m_fAngleSet = m_pRot[0]; } //�e�p�x���L���Ȃ�
		else { m_fAngleSet += m_fAnglePlus; }

		if (m_nNumCount % m_nInterval == 0)
		{//�Z�b�g����
			if (!CScenePlayer::GetbShop())
			{//�V���b�v����Ȃ��Ȃ�
				if (SetAttack(m_SetType, m_fMaxLife, m_fAngleSet, m_nNumSet, m_move, m_nUV, m_nInterval)) { return; }
			}
		}
		if (bLife) { fCntState[0] = -1; }
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CScenePairBullet2::Update(void)
{
	float	*fCntState = GetfCntState();
	bool	bLife = true;	//�������Ԃ̗L��
	if (fCntState[0] < 0) { fCntState[0] = 10.0f; bLife = false; }

	if(LifeUpdate())
	{//�����Ă���
		float	*fCntState = GetfCntState();
		bool	bWallX = false, bWallZ = false;

		D3DXVECTOR3 *pos = GetPosition(), *rot = GetRotation(), WKpos;
		
		rot[0].y += m_fTurning;

		//�C���̌����ύX
		if (rot[0].y > D3DX_PI) { rot[0].y -= D3DX_PI * 2; }
		if (rot[0].y < -D3DX_PI) { rot[0].y += D3DX_PI * 2; }

		m_pos3 += (m_pPos[0] - m_pos3) * m_fGMagnification;
		pos[0] = m_pos3 + D3DXVECTOR3(sinf(rot[0].y), 0.0f, cosf(rot[0].y)) * m_fDistance;

		CDungeon *pDungeon = CManager::GetDungeon();
		if (pDungeon != NULL && m_ObjType == CScene::OBJTYPE_BULLET && !m_bDestroy) { pDungeon->ShotCollision((CSceneBullet*)this); }
	}

	if (!bLife) { fCntState[0] = -10.0f; }
}
//=============================================================================
// �X�V����
//=============================================================================
void CScenePairBulletSet::Update(void)
{
	float	*fCntState = GetfCntState();

	CScenePairBullet2::Update();

	if (fCntState[0] < SHOT_LIFE)
	{
		m_nNumCount++;
		//�p�x�̍X�V
		if (m_pRot != NULL) { m_fAngleSet = m_pRot[0]; }//�e�p�x���L���Ȃ�
		else { m_fAngleSet += m_fAnglePlus; }
		if (m_nNumCount % m_nInterval == 0)
		{//�Z�b�g����
			if (!CScenePlayer::GetbShop())
			{//�V���b�v����Ȃ��Ȃ�
				if (SetAttack(m_SetType, m_fMaxLife, m_fAngleSet, m_nNumSet, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_nUV, m_nInterval)) { return; }
			}
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CSceneBullet::Draw(void)
{
	D3DXVECTOR3 *pos = GetPosition();
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();

	if (pos[0].x - fLengthX[0] < CCamera::camera.m_posR.x + SHOT_DROW_X && pos[0].x + fLengthX[0] > CCamera::camera.m_posR.x - SHOT_DROW_X &&
		pos[0].z - fLengthZ[0] < CCamera::camera.m_posR.z + SHOT_DROW_Z && pos[0].z + fLengthZ[0] > CCamera::camera.m_posR.z - SHOT_DROW_Z)
	{//�͈͓��Ȃ�
		float fPosY = PLAYER_Y;
		LPDIRECT3DDEVICE9	pD3DDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
		if (m_shot <= SHOT_PLAYER2 && CManager::GetMode()[0] == CManager::MODE_GAME) { fPosY -= 0.5f; }

		////�e�̕`��//***********************************************************************
		//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ�L���ɂ���)
		pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 50);//REF = Reference:�Q��
		pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��

		CScene::DrawPrepare(CScene::DRAW_TYPE_NORMAL, pD3DDevice);
		//�e�N�X�`���̐ݒ�
		pD3DDevice->SetTexture(0, m_pTexture[TEX_BULLET_S]);
		DrawParts(fPosY, pD3DDevice);	//�|���S���̕`��
		//DrawParts(pos[0].y - 0.3f, pD3DDevice);	//�|���S���̕`��

		//�e�̕`��//***********************************************************************
			CScene::DrawPrepare(CScene::DRAW_TYPE_ADD, pD3DDevice);
			//�A���t�@�e�X�g����(�������ɂ��摜�̐؂��茻�ۂ�L���ɂ���)
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 100);//REF = Reference:�Q��
			pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//FUNC = Function:�@�\ //GREATER = �`���傫��
			//�e�N�X�`���̐ݒ�
			pD3DDevice->SetTexture(0, m_pTexture[TEX_BULLET]);
			DrawParts(fPosY + 0.3f, pD3DDevice);	//�|���S���̕`��

			//���؂��薳����
			pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//�e�N�X�`����NULL��
		pD3DDevice->SetTexture(0, NULL);
		//pD3DDevice->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
	}
}
//=============================================================================
// �`��⏕����
//=============================================================================
void CSceneBullet::DrawParts(float fPosY, LPDIRECT3DDEVICE9& pD3DDevice)
{
	D3DXVECTOR3 *pos = GetPosition();
	D3DXVECTOR3 *rot = GetRotation();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���b�N�X

	//pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	////�r���{�[�h
	//pD3DDevice->GetTransform(D3DTS_VIEW, &mtxView);

	////�t�s���ݒ�
	//mtxWorld._11 = mtxView._11;
	//mtxWorld._12 = mtxView._21;
	//mtxWorld._13 = mtxView._31;
	//mtxWorld._21 = mtxView._12;
	//mtxWorld._22 = mtxView._22;
	//mtxWorld._23 = mtxView._32;
	//mtxWorld._31 = mtxView._13;
	//mtxWorld._32 = mtxView._23;
	//mtxWorld._33 = mtxView._33;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot[0].y, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos[0].x, fPosY, pos[0].z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pD3DDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pD3DDevice->SetFVF(FVF_VERTEX_3D);
	//�|���S���̕`��
	pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	//pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

}
//=============================================================================
// ���_���ݒ菈��
//=============================================================================
void CSceneBullet::SetVtx(int nUV)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXCOLOR	*col = GetColor();
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();

	//�v���C���[�ȊO�̒e�Ȃ�ЂƂ��炷
	if (m_shot > SHOT_PLAYER2) { nUV++; }

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCount = 0; nCount < 4; nCount++) { pVtx[nCount].col = col[0]; }

	pVtx[0].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, fLengthZ[0]);
	pVtx[1].pos = D3DXVECTOR3(fLengthX[0], 0.1f, fLengthZ[0]);
	pVtx[2].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, -fLengthZ[0]);
	pVtx[3].pos = D3DXVECTOR3(fLengthX[0], 0.1f, -fLengthZ[0]);
	//UV�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + SHOT_UV_SMALL);
	pVtx[1].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X) + (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + SHOT_UV_SMALL);
	pVtx[2].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + (1.0f / SHOT_UV_Y));
	pVtx[3].tex = D3DXVECTOR2((nUV % SHOT_UV_X) * (1.0f / SHOT_UV_X) + (1.0f / SHOT_UV_X), (nUV / SHOT_UV_X) * (1.0f / SHOT_UV_Y) + (1.0f / SHOT_UV_Y));

	//���_�o�b�t�@�̃A�����b�N
	pVtxBuff->Unlock();

	if (m_shot == SHOT_PLAYER1 && CManager::GetPlayer(0) != NULL) { m_fAtk *= CManager::GetPlayer(0)->GetAtkUP() * PLUS_ATK + 1.0f; }
	else if (m_shot == SHOT_PLAYER2 && CManager::GetPlayer(1) != NULL) { m_fAtk *= CManager::GetPlayer(1)->GetAtkUP() * PLUS_ATK + 1.0f; }
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneNorBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//��{�ݒ�
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//���_���

	//�e���
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fAtk = fAtk; m_bDestroy = bDestroy; m_bShotDelete = bShotDelete;
	m_move = move;
	
	//�摜���蓖��
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//�����̐ݒ�
	SetVtx(nUV);
	SetMove(change);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CSceneSetBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, CHANGE change, float fAtk, bool bDestroy, bool *bShotDelete,
	SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//��{�ݒ�
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//���_���
	m_move = move;

	//�e���
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_SetType = SetType; m_nNumSet = nNumSet; m_nInterval = nInterval;	//Set�����
	m_fAtk = fAtk; m_bDestroy = bDestroy; m_bShotDelete = bShotDelete;
	m_fAngleSet = fAngleSet; m_fAnglePlus = fAnglePlus;
	//�摜���蓖��
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//�����̐ݒ�
	m_nUV = nUV;
	SetVtx(nUV);
	SetMove(change);
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CScenePairBullet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fXWall, float fZWall, float fRangeX, float fRangeZ,
	SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//��{�ݒ�
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//���_���
	m_pos2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f); m_pos3 = pos;
	//�e���
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fLife = fCntState; m_fMaxLife = fCntState;
	m_fSpeed = fSpeed; 
	m_fXWall = fXWall; m_fZWall = fZWall; m_fRangeX = fRangeX; m_fRangeZ = fRangeZ;
	m_SetType = SetType; m_bShotDelete = bShotDelete; m_pPos = pPos; m_pRot = pRot;	//Set�����
	m_fAnglePlus = fAnglePlus; m_fAngleSet = fAngleSet; m_nNumSet = nNumSet;
	m_nInterval = nInterval;
	m_fAtk = fAtk; m_bDestroy = false;
	m_nUV = nUV;
	//�摜���蓖��
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//�����̐ݒ�
	SetVtx(nUV);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CScenePairBullet2::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
	D3DXVECTOR3 *pPos, float *pRot, bool bDestroy, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//��{�ݒ�
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//���_���
	m_pos3 = pos;
	//�e���
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fLife = fCntState; m_fMaxLife = fCntState;
	m_fSpeed = fSpeed; m_fAtk = fAtk;
	m_fDistance = fDistance; m_fAngle = fAngle; m_fGMagnification = fGMagnification;

	m_bShotDelete = bShotDelete; m_pPos = pPos; m_pRot = pRot;	//Set�����
	m_bDestroy = bDestroy;

	//�摜���蓖��
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//�����̐ݒ�
	SetVtx(nUV);
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CScenePairBulletSet::Set(SHOT shot, D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXCOLOR col, float fLengthX, float fLengthZ, int nUV,
	float fCntState, int nChange, float fSpeed, float fAccelerator, float fTurning, float fSlip, float fAtk, float fAngle, float fDistance, float fGMagnification,
	SET SetType, float fAngleSet, float	fAnglePlus, int nNumSet, int nInterval, D3DXVECTOR3 *pPos, float *pRot, bool *bShotDelete)
{
	m_shot = shot;		GetfLengthX()[0] = fLengthX;	GetfLengthZ()[0] = fLengthZ;	//��{�ݒ�
	GetPosition()[0] = pos;		GetRotation()[0] = rot;			GetColor()[0] = col;			//���_���
	m_pos3 = pos;
	//�e���
	m_fSpeed = fSpeed;	m_fTurning = fTurning;	m_fAccelerator = fAccelerator;
	GetfCntState()[0] = fCntState;	m_nChange = nChange;	m_fSlip = fSlip;
	m_fLife = fCntState; m_fMaxLife = fCntState;
	m_fSpeed = fSpeed;
	m_fDistance = fDistance; m_fAngle = fAngle; m_fGMagnification = fGMagnification;

	m_SetType = SetType; m_bShotDelete = bShotDelete; m_pPos = pPos; m_pRot = pRot;	//Set�����
	m_fAnglePlus = fAnglePlus; m_fAngleSet = fAngleSet; m_nNumSet = nNumSet;
	m_nInterval = nInterval;
	m_fAtk = fAtk; m_bDestroy = false;
	m_nUV = nUV;

	//�摜���蓖��
	BindDrawType(CScene::DRAW_TYPE_ADD);

	//�����̐ݒ�
	SetVtx(nUV);
}
//=============================================================================
// �������x�ݒ菈��
//=============================================================================
void CSceneNorBullet::SetMove(CHANGE& change)
{
	D3DXVECTOR3 rot = GetRotation()[0];

	switch (change)
	{
	case CHANGE_FAST:		//��������
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * (m_fSpeed * 3.0f);
		break;
	case CHANGE_FAST2:		//��������
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * (m_fSpeed * 50.0f);
		break;
	case CHANGE_GRAVITY:	//�t�����Ƀu���A��60
		rot.y += D3DX_PI - D3DX_PI * ((1.0f * 0.33f) * 0.5f);
		rot.y += D3DX_PI * ((rand() % (int)((1.0f * 0.33f) * 1000.0f)) * 0.001f);
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * ((rand() % 800) * 0.001f + 0.3f);
		m_fSpeed *= (rand() % 1000) * 0.0005f + 1.0f;
		break;
	case CHANGE_GRAVITY2:	//�t�����Ƀu���A��120
		rot.y += D3DX_PI - D3DX_PI * ((1.0f * 0.66f) * 0.5f);
		rot.y += D3DX_PI * ((rand() % (int)((1.0f * 0.66f) * 1000.0f)) * 0.001f);
		m_move += D3DXVECTOR3(sinf(rot.y), 0.0f, cosf(rot.y)) * ((rand() % 800) * 0.001f + 0.3f);
		m_fSpeed *= (rand() % 1000) * 0.0005f + 1.0f;
		break;
	}

}
//=============================================================================
// ���C����
//=============================================================================
void CSceneBullet::ShotAttack(SHOT Shot, ATTACK Atk, D3DXVECTOR3 pos, D3DXVECTOR3 move, float fRotU, bool bFirst, 
	float fSpd, float fSlip, float fLife, float fTurning, float fAccelerator, float fLengthX, float fLengthZ,
	float fRange, float fDistance, int nNumBullet, int nChange, CHANGE Change, float fAtk, bool bDestroy, bool *bShotDelete, int nUV)
{
	CSound *pSound = CManager::GetSound();
	CSceneNorBullet *bulletNor = NULL;
	CSceneSetBullet *bulletSet = NULL;
	CSceneBullet::SET set;

	fRotU += D3DX_PI * 2;
	float	fWKAngle = fRotU;	//�p�x�v�Z�p
	float	fAngle = 0.0;		//���C�p�x

	float	fWKAnglePlus = 0.0f;
	int		nWKSet = 60, nWKNumSet = 1;

	//switch (Atk)
	//{
	//case ATK_PTN00:		fRange = D3DX_PI * 0.5f;	nNumBullet = 8;		break;
	//case ATK_PTN01:		fRange = D3DX_PI * 0.5f;	nNumBullet = 8;		break;
	//	//�{�X�p//***********************************************************************
	//case BATK_CROSS:	fRange = D3DX_PI; 			nNumBullet = 4;		break;
	//case BATK_BRANCH:	fRange = D3DX_PI;			nNumBullet = 4;		break;
	//case BATK_SPIN_0:	fRange = D3DX_PI;			nNumBullet = 8;		break;
	//case BATK_SPIN_1:	fRange = D3DX_PI;			nNumBullet = 8;		break;
	//}
	if (!bFirst) { fAngle += (float)((D3DX_PI * 2) / (float)nNumBullet); }
	for (int nCount = (bFirst ? 0 : 1); nCount < nNumBullet; nCount++, fAngle += (float)((D3DX_PI * 2) / (float)nNumBullet))
	{//��]�l�v���X
		//if (nCount == nNumBullet / 2) {}
		if ((D3DX_PI * 2) - fRange < fAngle || fRange > fAngle)
		{//�͈͓��Ȃ�
			switch (Atk)
			{
			case ATK_PTN00:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					fWKAngle = fAngle;
					if (fWKAngle > D3DX_PI) { fWKAngle -= D3DX_PI * 2; }
					fWKAngle = fWKAngle * 0.5f + fRotU;
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf((fAngle + fRotU)) * fDistance, 0.0f, cosf((fAngle + fRotU)) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
				}
				else { return; } break;
			case ATK_PTN01:
				if (nCount != 0)
				{
					if (SceneCreate(bulletNor, BULLET_PRIORITY))
					{//�����ł����Ȃ�
						fWKAngle = (fRotU - fAngle) * 0.95f;
						bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * fDistance, 0.0f, cosf(fAngle) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, (fAngle + fWKAngle), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
							fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
					}
					else { return; }
				}break;
			case ATK_PTN02:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					fWKAngle = (fRotU - fAngle) * 0.5f;
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * fDistance, 0.0f, cosf(fAngle) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, (fAngle + fWKAngle), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
				} else { return; } break;
			case ATK_PTN03:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf((fAngle + fRotU)) * fDistance, 0.0f, cosf((fAngle + fRotU)) * fDistance), move * 0.1f, D3DXVECTOR3(0.0f, (fAngle + fRotU), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete);
				} else { return; } break;
			case ATK_PTN_FIRE:
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					fWKAngle = (fRotU - fAngle) * 0.95f;
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.5f, 5.0f, 50,
						SHOT_LIFE - 30.0f, nChange, 0.025f, 0.0f, 0.0f, 0.97f, Change, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_FIRE0, fAngle, 0.0f, 1, 1);
				} else { return; } break;
			case ATK_PTN_FIRE2:
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					fWKAngle = fRotU + fAngle;
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fWKAngle) * fDistance, 0.0f, cosf(fWKAngle) * fDistance) + D3DXVECTOR3(sinf(fRotU), 0.0f, cosf(fRotU)) * 10.0f,
						move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_FIRE0, fAngle, 0.0f, 1, 1);
				} else { return; } break;
				break;
			case ATK_BEAM00:
			case ATK_BEAM01:
			case ATK_BEAM02:
			case ATK_BEAM10:
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					fWKAngle = fRotU + fAngle;
					set = CSceneBullet::SET_EFFECT;
					switch (Atk)
					{
					case ATK_BEAM00: fWKAngle = fRotU + fAngle; break;	//���̂܂�
					case ATK_BEAM01: //�񂹂�
						fWKAngle = fAngle;
						if (fWKAngle > D3DX_PI) { fWKAngle -= D3DX_PI * 2; }
						fWKAngle = fWKAngle * 0.5f + fRotU;	
						break;
					case ATK_BEAM02: fWKAngle = fRotU; break;	//�����Ă����
					case ATK_BEAM10: set = CSceneBullet::SET_EFFECT0;
					}
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fRotU + fAngle) * fDistance, 0.0f, cosf(fRotU + fAngle) * fDistance),
						move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete, set, fWKAngle, 0.0f, 1, 1);
				} else { return; } break;
				break;
			case ATK_SETTING0:
			case ATK_SETTING1:
			case ATK_PDIFFUSION:
			case ATK_PDIFFUSION2:
			case ATK_DIFFUSION: fWKAngle = fRotU + fAngle;
				switch (Atk)
				{
				case ATK_SETTING0:		set = SET_TURN;			nWKSet = 1; nWKNumSet = 1;	fWKAnglePlus = D3DX_PI * 0.12f;	break;
				case ATK_SETTING1:		set = SET_TURN;			nWKSet = 1; nWKNumSet = 1;	fWKAnglePlus = D3DX_PI * 0.12f;	break;
				case ATK_PDIFFUSION:	set = SET_PDIFFUSION;	nWKSet = 60; nWKNumSet = 5; break;
				case ATK_DIFFUSION:		set = SET_DIFFUSION;	nWKSet = 60; nWKNumSet = 5; break;
				case ATK_PDIFFUSION2:	set = SET_PDIFFUSION2;	nWKSet = 60; nWKNumSet = 5; break;
				}
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fWKAngle) * fDistance, 0.0f, cosf(fWKAngle) * fDistance), move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX, fLengthZ, nUV,
						fLife, nChange, fSpd * 0.85f, fAccelerator, fTurning, fSlip, Change, fAtk, bDestroy, bShotDelete, set, fWKAngle, fWKAnglePlus, nWKNumSet, nWKSet);
				}
				else { return; } break;
			case BATK_CROSS://BOSS�p�@�\��****************************************************************
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 4.0f, 50,
						0.0f, 0, 0.01f, 0.0f, 0.0f, 0.97f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_AROUND, fAngle, 0.0f, 2, 60);
				}
				else { return; } break;
			case BATK_BRANCH://BOSS�p�@�}������****************************************************************
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�					
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 0, 0.01f, 0.0f, 0.01f, 0.97f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_BRANCHES, fAngle, 0.0f, 2, 20);
				}
				else { return; }
				if (SceneCreate(bulletSet, BULLET_PRIORITY))
				{//�����ł����Ȃ�							
					bulletSet->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle + D3DX_PI * 0.25f), 0.0f, cosf(fAngle + D3DX_PI * 0.25f)) * 1.0f, move, D3DXVECTOR3(0.0f, fAngle + D3DX_PI * 0.25f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 0, 0.01f, 0.0f, -0.01f, 0.97f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete, CSceneBullet::SET_BRANCHES, fAngle + D3DX_PI * 0.25f, 0.0f, 2, 20);
				}
				else { return; } break;
			case BATK_SPIN_0:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�		
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 2257, 0.5f, -0.0f, 0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; }
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�							
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 2257, 0.5f, -0.0f, -0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; } break;
			case BATK_SPIN_1:
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�	
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 62257, 0.5f, -0.0f, 0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; }
				if (SceneCreate(bulletNor, BULLET_PRIORITY))
				{//�����ł����Ȃ�	
					bulletNor->Set(Shot, pos + D3DXVECTOR3(sinf(fAngle) * -5.0f, 0.0f, cosf(fAngle) * -5.0f), move * 0.1f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, 50,
						0.0f, 62257, 0.5f, -0.0f, -0.5f, 0.95f, CSceneBullet::CHANGE_FAST, fAtk, bDestroy, bShotDelete);
				}
				else { return; } break;
			}//switch()
		}//if()
	}//for()
}
//=============================================================================
// �������x�ݒ菈��
//=============================================================================
bool CSceneBullet::SetAttack(SET SetType , float fMaxLife, float fAngleSet, int nNumSet, D3DXVECTOR3 move, int nUV, int& nInterval)
{
	CSound *pSound = CManager::GetSound();
	D3DXVECTOR3 *rot = GetRotation();
	float *fLengthX = GetfLengthX();
	float *fLengthZ = GetfLengthZ();
	float fWKLengthX = fLengthX[0], fWKLengthZ = fLengthZ[0];
	float fCntState = GetfCntState()[0];
	float fWKAngle = rot[0].y;
	//if (fCntState < 0) { 0.0f; }
	CScenePairBulletSet *pPairBulletSet = NULL;
	CSceneNorBullet *bulletNor = NULL;
	CSceneSetBullet *bulletSet = NULL;

	float	fInitAngle = fAngleSet;
	float	fAngle = fAngleSet;
	float	fWKAngleU = fAngleSet;
	float	fWKLife;
	SET		WKset;
	CSceneBullet::CHANGE WKChange;

	switch (SetType)
	{
	case SET_NONE:	//�u������//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					-SHOT_LIFE + fCntState, 0, 0.0f, 0.01f, 0.0f, 0.5f, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		}break;
	case SET_TURN:	//��]���u������//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move * 0.0f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					-SHOT_LIFE + fCntState, 2, 0.0f, 0.005f, 0.0f, 0.5f, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete);
			}else { return false; }
		}break;
	case SET_EFFECT:	//�u������//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�				
				bulletNor->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], 16 * 6 + (nUV % 16),
					SHOT_LIFE * 0.98f, 0, 0.0f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_NO, m_fAtk * 0.0625f, false, m_bShotDelete);
			}
			else { return false; }
		}break;
	case SET_EFFECT0:	//�u������//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�				
				bulletNor->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], 16 * 6 + (nUV % 16),
					SHOT_LIFE - (SHOT_LIFE - fMaxLife) * 0.3f, 0, 0.0f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_NO, m_fAtk * 0.0625f, false, m_bShotDelete);
			}
			else { return false; }
		} break;
	case SET_SHOT:	//����//***********************************************************************
	case SET_SHOT2:	//����//***********************************************************************
	case SET_NEEDLE:	//����//***********************************************************************
		switch (SetType)
		{
		case SET_SHOT:		fWKLife = SHOT_LIFE * 0.25f; WKChange = CSceneBullet::CHANGE_FAST2; break;
		case SET_SHOT2:		fWKLife = SHOT_LIFE * 0.25f; WKChange = CSceneBullet::CHANGE_FAST; break;
		case SET_NEEDLE:	fWKLife = SHOT_LIFE * 0.25f; WKChange = CSceneBullet::CHANGE_FAST2; fWKLengthZ *= 1.5f;	break;
		}
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWKLengthX, fWKLengthZ, nUV,
					fWKLife, 0, 0.01f, 0.0f, 0.0f, 0.97f, WKChange, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_BEAM:	//����//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletSet->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move * 0.0f, D3DXVECTOR3(0.0f, fInitAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					SHOT_LIFE * 0.85f, 0, m_fSpeed, 0.0f, 0.0f, m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete, CSceneBullet::SET_EFFECT, fAngle, 0.0f, 1, 1);
			}
			else { return false; }
		}break;
	case SET_RELEASE:	//����//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, nUV,
					-(SHOT_LIFE - fMaxLife), 0, m_fSpeed, 0.0f, 0.0f, m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_RANDSHOT:	//����//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				fWKAngleU = fAngle;
				fWKAngleU += -D3DX_PI * ((1.0f * 0.33f) * 0.5f);
				fWKAngleU += D3DX_PI * ((rand() % (int)((1.0f * 0.33f) * 1000.0f)) * 0.001f);
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fWKAngleU, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 2.0f, 2.0f, nUV,
					SHOT_LIFE * 0.5f, 0, 0.01f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		}break;
	case SET_BACK_G://�^���d��//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++)
		{//�񐔕�
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f),D3DXVECTOR3(0.0f, fInitAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					0.0f, 0, 0.02f, 0.0f, m_fTurning, 0.98f, CSceneBullet::CHANGE_GRAVITY, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_BACK_G2://�^���d��//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++)
		{//�񐔕�
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, fInitAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], nUV,
					0.0f, 0, 0.02f, 0.0f, 0.0f, 0.98f, CSceneBullet::CHANGE_GRAVITY2, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
	case SET_FIRE0:
		if (SceneCreate(bulletSet, BULLET_PRIORITY))
		{//�����ł����Ȃ�
			bulletSet->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * 1.0f, move * 0.0f, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0], fLengthZ[0], 48 + (nUV % 16),
				fCntState, 0, 0.0f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_NO, m_fAtk * 0.5f, false, m_bShotDelete, CSceneBullet::SET_FIRE, fAngle, 0.0f, 1, 20);
		} else { return false; }
	case SET_FIRE:
		for (int nCount = 0; nCount < nNumSet; nCount++)
		{//�񐔕�
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				fWKAngle = rot[0].y +  D3DX_PI - D3DX_PI * ((1.0f * 0.2f) * 0.5f);
				fWKAngle += D3DX_PI * ((rand() % (int)((1.0f * 0.2f) * 1000.0f)) * 0.001f);
				bulletNor->Set(m_shot, GetPosition()[0] + D3DXVECTOR3(sinf(rot[0].y), 0.0f, cosf(rot[0].y)) * (fLengthZ[0] * 0.5f) + D3DXVECTOR3(sinf(fWKAngle), 0.0f, cosf(fWKAngle)) * (fLengthZ[0] * 0.5f)
					, move, D3DXVECTOR3(0.0f, fWKAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fLengthX[0] * 0.5f, fLengthX[0] * 1.0f, 48 + (nUV % 16),
					SHOT_LIFE - 60, 0, 0.01f + ((rand() % 100) * 0.01f) * 0.005f, 0.0f, 0.0f, 0.95f, CSceneBullet::CHANGE_FAST2, m_fAtk * 0.25f, false, m_bShotDelete);
			} else { return false; }
		}break;
	case SET_CROSS:	//�\������//***********************************************************************
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, 4.0f, nUV,
					0.0f, 0, 0.01f, 0.0f, 0.0f, 0.97f, CSceneBullet::CHANGE_FAST, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		}
	case SET_AROUND:	//���E//***********************************************************************
		fAngle = rot[0].y - D3DX_PI * 0.5f;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], 50,
					fCntState + 1, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete);
			} else { return false; }
		} break;
		//=============================================================================
		// �N��������
		//=============================================================================
	case SET_DIFFUSION:	//�΂�T���ĎU��//***********************************************************************
	case SET_DIFFUSION2:	//�΂�T���ĎU��//***********************************************************************
		if (SET_DIFFUSION2 == SetType) { fWKLife = SHOT_LIFE * 0.5f; }
		else { fWKLife = SHOT_LIFE * 0.75f; }
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletNor, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletNor->Set(m_shot, GetPosition()[0], move * 0.0f, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], nUV,
					fWKLife, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete);
			}
			else { return false; }
		}GetfCntState()[0] = SHOT_LIFE;
	case SET_PDIFFUSION:	//�΂�T���ĎU��//***********************************************************************
	case SET_PDIFFUSION2:	//�΂�T���ĎU��//***********************************************************************
		fAngle = rot[0].y;
		if (SET_PDIFFUSION2 == SetType) { fWKLife = SHOT_LIFE * 0.5f; WKset = SET_DIFFUSION2; }
		else { fWKLife = SHOT_LIFE * 0.75f; WKset = SET_DIFFUSION; }
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletSet->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], nUV,
					fWKLife, 0, m_fSpeed, 0.0f, m_fTurning + D3DX_PI * 0.05f * ((nCount % 2) * 2 - 1), m_fSlip, CSceneBullet::CHANGE_FAST2, m_fAtk, false, m_bShotDelete, WKset, fAngle, 0.0f, 5, 60);
			}
			else { return false; }
		}
	case SET_BRANCH:	//�\������//***********************************************************************
		fAngle = rot[0].y;
		for (int nCount = 0; nCount < nNumSet; nCount++, fAngle += (D3DX_PI * 2) / nNumSet)
		{//��]�l�v���X
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletSet->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], 50,
					fCntState + 1, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete, SET_BRANCHES, fAngle, 0.0f, 2, 60);
			} else { return false; }
		}
	case SET_BRANCHES:	//�}������//***********************************************************************
		if (fCntState < SHOT_LIFE * 0.5f)
		{
			nInterval *= 5;
			rot[0].y -= D3DX_PI * 0.2f;
			if (SceneCreate(bulletSet, BULLET_PRIORITY))
			{//�����ł����Ȃ�
				bulletSet->Set(m_shot, GetPosition()[0], move, D3DXVECTOR3(0.0f, fAngle, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), fLengthX[0], fLengthZ[0], 50,
					fCntState + 1, 0, m_fSpeed, m_fAccelerator, m_fTurning, m_fSlip, CSceneBullet::CHANGE_NO, m_fAtk, false, m_bShotDelete, SET_BRANCHES, fAngle, 0.0f, 2, 60);
			} else { return false; }
		}
	}

	return false;
}
//=============================================================================
// �e�폜����
//=============================================================================
void	CSceneBullet::BreakBullet(bool bAll)
{
	CScene **PScene = CScene::GetScene(BULLET_PRIORITY);
	for (int nCount = 0; nCount < CScene::GetnMemoryAll(BULLET_PRIORITY); nCount++)
	{
		if (PScene[nCount] != NULL)
		{
			if (PScene[nCount]->GetObjType() >= CScene::OBJTYPE_BULLET && PScene[nCount]->GetObjType() <= CScene::OBJTYPE_BULLET3)
			{
				CSceneBullet* pBullet = (CSceneBullet*)PScene[nCount];
				if (!bAll)
				{//�S���łȂ�
					if (pBullet->GetbShotDelete() != NULL)
					{//NULL�łȂ�
						if (!pBullet->GetbShotDelete()[0])
						{//�e��false�Ȃ�
							pBullet->GetfCntState()[0] = SHOT_LIFE - 1;
						}
					}
				}
				else
				{//�S�������I
					if (pBullet->GetObjType() != CScene::OBJTYPE_BULLET3)
					{
						pBullet->GetfCntState()[0] = SHOT_LIFE - 1;
					}
				}
			}
		}//if(!=NULL)
	}//for()
}
//=============================================================================
// �~�`�e�폜����
//=============================================================================
void	CSceneBullet::CircleBreak(D3DXVECTOR3 pos, float fLength, SHOT shot1, SHOT shot2)
{
	CScene **PScene = CScene::GetScene(BULLET_PRIORITY);
	for (int nCount = 0; nCount < CScene::GetnMemoryAll(BULLET_PRIORITY); nCount++)
	{
		if (PScene[nCount] != NULL)
		{
			if (PScene[nCount]->GetObjType() == CScene::OBJTYPE_BULLET)
			{
				CSceneBullet* pBullet = (CSceneBullet*)PScene[nCount];
				if (pBullet->GetShot()[0] != shot1 && pBullet->GetShot()[0] != shot2)
				{//�����̒e�łȂ��Ȃ�
					D3DXVECTOR3 *Bulletpos = pBullet->GetPosition();
					float		fBulletX = pBullet->GetfLengthX()[0], fBulletZ = pBullet->GetfLengthZ()[0];
					float fAngle;
					float fWKAngle;
					float fRangeBullet;
					float fDistance;
					float fPercentX, fPercentY;

					//�����v�Z
					fDistance = powf(pos.x - Bulletpos[0].x, 2) + powf(pos.z - Bulletpos[0].z, 2);

					//�e�͈̔͌v�Z
					fAngle = atan2f(pos.x - Bulletpos[0].x, pos.z - Bulletpos[0].z);//�p�x�v�Z
					fWKAngle = fAngle - pBullet->GetRotation()[0].y;
					fPercentX = (sinf(fWKAngle) * 1.0f) * (fBulletZ / fBulletX);
					fPercentY = (cosf(fWKAngle) * 1.0f);
					fAngle = atan2f(fPercentX, fPercentY);

					fRangeBullet = powf(sinf(fAngle) * fBulletX, 2) + powf(cosf(fAngle) * fBulletZ, 2);

					if (fDistance < fRangeBullet + (fLength * fLength))
					{//�͈͓��Ȃ�폜
						pBullet->GetfCntState()[0] = SHOT_LIFE;
					}
				}
			}
		}//if(!=NULL)
	}//for()
}