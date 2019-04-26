//=============================================================================
//
// ���[�V�������� [motion.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS			//Fire Wall�˔j
#include <stdio.h>						//�C���N���h�t�@�C��
#include "main.h"
#include "motion.h"
#include "clothing.h"
#include "player.h"
#include "SceneModel.h"
#include "3DGage.h"
#include "mesh.h"
#include "Effect.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_ATKCHECK	(200.0f * 200.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
CVtxInfo					*CCharParts::m_pVtxInfo[CCharParts::PARTS_MAX] = {};			//���_���
CCharacter::MODEL_PARTS		*CCharacter::m_partsAll[CCharParts::PARTS_MAX] = {};	//�p�[�c���
int							CMotion::m_nNumMotion = 0;				//���[�V������
CMotion						**CMotion::m_pMotion = NULL;				//���[�V�������

//=============================================================================
// ���[�V�����̏�����
//=============================================================================
void	CMotion::Load(void)
{
	FILE *pFile;
	char aStr[8][32];
	m_nNumMotion = 0;
	int nNumMotion = 0;
	m_pMotion = NULL;

	//���[�V�����̓ǂݍ���----------------------------------------------------------
	int nCntMotion[3];
	CKey *pKey;
	CAtkKey *pAtkKey;
	COneMotion *pMotion;

	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)//Load
	{//����
		fscanf(pFile, "%d", &nCntMotion[0]);//�t�@�C����
		m_nNumMotion = nCntMotion[0];
		m_pMotion = new CMotion*[m_nNumMotion];	//���[�V�����S�̌�����
		for (int nCntP = 0; nCntP < m_nNumMotion; nCntP++) { m_pMotion[nCntP] = new CMotion; }

		for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
		{
			fscanf(pFile, "%s", &aStr[nCntChar][0]);//�t�@�C����
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "%s �ǂݍ���\n", &aStr[nCntChar][0]);
		}

		fclose(pFile);
	}
	else
	{//���s
		MessageBox(0, "���[�V����", "motion.txt�����I", MB_OK);
	}

	for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
	{
		pFile = fopen(&aStr[nCntChar][0], "r");
		if (pFile != NULL)//Load
		{//���[�V�����t�@�C��Load
			fscanf(pFile, "%d %d\n", &nNumMotion, &m_pMotion[nCntChar]->m_nMaxParts);//���[�V������ �p�[�c��
			m_pMotion[nCntChar]->m_nMaxMotion = nNumMotion;
			//����
			m_pMotion[nCntChar]->GetOneMotion() = new COneMotion[nNumMotion];

			for (int nCnt0 = 0; nCnt0 < nNumMotion; nCnt0++)
			{//���[�V��������]
				pMotion = &m_pMotion[nCntChar]->GetOneMotion()[nCnt0];
				fscanf(pFile, "%d", &pMotion->GetnMaxKey());

				//�L�[����
				pMotion->GetKey() = new CKey*[pMotion->GetnMaxKey()];

				//�L�[TYPE����
				pMotion->GetType() = new CKey::TYPE[pMotion->GetnMaxKey()];

				fscanf(pFile, "%d %d %d %d %d %d %d %d %f\n", 
					&pMotion->GetnNorBranch(),
					&pMotion->GetnLandBranch(),
					&pMotion->GetnStartCancel(0),
					&pMotion->GetnStartCancel(1),
					&pMotion->GetnEndCancel(0),
					&pMotion->GetnEndCancel(1),
					&pMotion->GetnOtherCancel(0),
					&pMotion->GetnOtherCancel(1),
					&pMotion->GetfWaitTime()
				);
				pMotion->GetfWaitTime() *= FRAME_SPEED;	//�҂����Ԃ�␳
				for (int nCnt1 = 0; nCnt1 < pMotion->GetnMaxKey(); nCnt1++)
				{//�L�[����]
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d", &pMotion->GetType()[nCnt1]);//���[�V������ �p�[�c��

					switch (pMotion->GetType()[nCnt1])
					{//�L�[TYPE�@�����������ǒ��g�����ĂȂ�
					case CKey::TYPE_NORMAL: pMotion->GetKey()[nCnt1] = new CKey;  break;
					case CKey::TYPE_ATTACK: pMotion->GetKey()[nCnt1] = new CAtkKey;  break;
					}
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d %d %d %d %f %f\n",
						&pKey->GetnMoveType(),
						&pKey->GetnFloating(),
						&pKey->GetnFrame(),
						&pKey->GetnMaxEffect(),
						&pKey->GetfMove(),
						&pKey->GetfSlip()
					);//���[�V������ �p�[�c��

					  //�G�t�F�N�g�g����
					pKey->GetpEffect() = new int[pKey->GetnMaxEffect()];

					  //�p�x�g����
					pKey->GetpRot() = new D3DXVECTOR3[m_pMotion[nCntChar]->m_nMaxParts];

					fscanf(pFile, "%f %f %f\n", &pKey->GetMove().x,
						&pKey->GetMove().y,
						&pKey->GetMove().z);
					for (int nCnt2 = 0; nCnt2 < m_pMotion[nCntChar]->m_nMaxParts; nCnt2++)
					{//�p�[�c����]
						fscanf(pFile, "%f %f %f\n", &pKey->GetpRot()[nCnt2].x,
							&pKey->GetpRot()[nCnt2].y,
							&pKey->GetpRot()[nCnt2].z);
					}
					{//�p�[�c����]
						fscanf(pFile, "%f %f %f\n", &pKey->GetPos().x,
							&pKey->GetPos().y,
							&pKey->GetPos().z);
					}

					for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
					{//�p�[�c����]
						fscanf(pFile, "%d ", &pKey->GetpEffect()[nCount]);
					}

					if (pMotion->GetType()[nCnt1] == CKey::TYPE_ATTACK)
					{
						pAtkKey = (CAtkKey*)pKey;
						fscanf(pFile, "%d %d %d %d %d\n", 
							&pAtkKey->GetnAtkType(),
							&pAtkKey->GetnAtkParts(),
							&pAtkKey->GetnCntAtk(),
							&pAtkKey->GetnHitFrame(0),
							&pAtkKey->GetnHitFrame(1));

						fscanf(pFile, "%f %f\n", &pAtkKey->GetfRange(),
							&pAtkKey->GetfAtkplus()
						);
					}
				}
			}
			fclose(pFile);
		}
		else
		{//���s
			MessageBox(0, "���[�V�����f�[�^", "������!?", MB_OK);
		}
	}
	CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "���[�V�����ǂݍ��݊��� �ǂݍ��񂾃��[�V������:%d\n", m_nNumMotion);
}
//=============================================================================
// ���[�V�����̑S�I��
//=============================================================================
void CMotion::UnLoad(void)
{
	if (m_pMotion != NULL)
	{//���[�V�������ǂݍ��܂�Ă���Ȃ�
		for (int nCount = 0; nCount < m_nNumMotion; nCount++)
		{//�������ꂽ���[�V��������]
			if (m_pMotion[nCount] != NULL)
			{//���[�V��������������Ă���Ή��
				m_pMotion[nCount]->Uninit();
			}
		}//������
		m_nNumMotion = 0;
		delete[] m_pMotion;
		m_pMotion = NULL;
	}
}
//=============================================================================
// ���[�V�����̏I��
//=============================================================================
void CMotion::Uninit(void)
{
	if (m_OneMotion != NULL)
	{//���[�V�����̂���������Ă����
		for (int nCount = 0; nCount < m_nMaxMotion; nCount++)
		{//���[�V��������]
			m_OneMotion[nCount].Uninit();
		}//������
		m_nMaxMotion = 0;
		delete[] m_OneMotion;
		m_OneMotion = NULL;
	}
}
//=============================================================================
// ��̃��[�V�����I��
//=============================================================================
void COneMotion::Uninit(void)
{
	if (m_Key != NULL)
	{//�L�[����������Ă����
		for (int nCount = 0; nCount < m_nMaxKey; nCount++)
		{//�L�[����]
			if (m_Key[nCount] != NULL)
			{//��������Ă���΍폜
				m_Key[nCount]->Uninit();
			}
		}//������
		m_nMaxKey = 0;
		delete[] m_Key;
		m_Key = NULL;
	}
}
//=============================================================================
// �L�[�̏I��
//=============================================================================
void CKey::Uninit(void)
{
	if (m_pRot != NULL)
	{//�p�x����������Ă����
		delete[] m_pRot;		//1���������΂�����
		m_pRot = NULL;
	}
	if (m_pEffect != NULL)
	{//���ʂ���������Ă����
		delete[] m_pEffect;		//1���������΂�����
		m_pEffect = NULL;
	}
}

//=============================================================================
// �p�[�c�̓ǂݍ��� ��
//=============================================================================
LPD3DXMESH CCharacter::Load(CCharParts::PARTS parts)
{
	if (m_partsAll[parts] != NULL)
	{
		int nLength = (int)strlen(&m_partsAll[parts]->aText[0]);		//�������m�F

		if (nLength > 1)
		{
			D3DXLoadMeshFromX(&m_partsAll[parts]->aText[0],
				D3DXMESH_SYSTEMMEM, CManager::GetRenderer()->GetDevice(), NULL, &m_partsAll[parts]->pBuffMatModel, NULL, &m_partsAll[parts]->nNumMatModel, &m_partsAll[parts]->MeshModel);
			
			BYTE *pVtxBuff;
			int nNumVtx = m_partsAll[parts]->MeshModel->GetNumVertices();
			DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
			sizeFvF = D3DXGetFVFVertexSize(m_partsAll[parts]->MeshModel->GetFVF());

			if (m_partsAll[parts]->pPos == NULL)
			{//�ʒu���̒��_�𐶐�
				m_partsAll[parts]->pPos = new D3DXVECTOR3[nNumVtx];

				m_partsAll[parts]->MeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
				for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
				{
					m_partsAll[parts]->pPos[nCntVtx] = ((D3DXVECTOR3*)pVtxBuff)[0];
					pVtxBuff += sizeFvF;
				}
				m_partsAll[parts]->MeshModel->UnlockVertexBuffer();
			}

			strcpy(&m_partsAll[parts]->aText[0], "");

			//�e�N�X�`���m�F
			CScene::Load(m_partsAll[parts]->tex);
		}
	}
	switch (parts)
	{//�p�[�c���Ƃɒ��_���ǂݍ���
	case CCharParts::TEST_000:	CCharParts::LoadVtx(CCharParts::TEST_000, "data/TEXT/Vtx/Vtx_Box.txt"); break;
	case CCharParts::BOX_100:	CCharParts::LoadVtx(CCharParts::BOX_100, "data/TEXT/Vtx/Vtx_Box100.txt"); break;
	}
	return m_partsAll[parts]->MeshModel;
}
//=============================================================================
// �p�[�c�̓ǂݍ��� ������
//=============================================================================
void CCharacter::Load(void)
{
	FILE	*pFile;
	int		nNumParts = 0;
	//int nLength;		//�������m�F

	pFile = fopen("data/TEXT/model.txt", "r");

	if (pFile != NULL)//Load
	{//����
		for (int nCountData = 0; nCountData < CCharParts::PARTS_MAX; nCountData++)
		{// X�t�@�C���̓ǂݍ���
			if (m_partsAll[nCountData] == NULL) { m_partsAll[nCountData] = new CCharacter::MODEL_PARTS; }
			//nLength = (int)strlen(&m_partsAll[nCountData]->aText[0]);
			//if (nLength < 5)
			{
				fscanf(pFile, "%s\n", &m_partsAll[nCountData]->aText[0]);	//�t�@�C����
				fscanf(pFile, "%d\n", &m_partsAll[nCountData]->tex);		//�摜
				//fscanf(pFile, "%f %f %f", &m_partsAll[nCountData]->addPos.x, &m_partsAll[nCountData]->addPos.y, &m_partsAll[nCountData]->addPos.z);//�ꏊ
				m_partsAll[nCountData]->pPos = NULL;
				if (m_partsAll[nCountData]->tex == -1) { m_partsAll[nCountData]->tex = CScene::TEX_MAX; }
				else { m_partsAll[nCountData]->tex = (CScene::TEXTURE)((int)TEX_CHAR + (int)m_partsAll[nCountData]->tex); }
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// �p�[�c�̏I��
//=============================================================================
void CCharacter::UnLoad(void)
{
	for (int nCount = 0; nCount < CCharParts::PARTS_MAX; nCount++)
	{//�p�[�c�����
		if (m_partsAll[nCount] != NULL)
		{//�p�[�c����������Ă���Ή��
				
			if (m_partsAll[nCount]->MeshModel != NULL)
			{// ���b�V���̊J��
				m_partsAll[nCount]->MeshModel->Release();
				m_partsAll[nCount]->MeshModel = NULL;
			}

			if (m_partsAll[nCount]->pBuffMatModel != NULL)
			{// �}�e���A���̊J��
				m_partsAll[nCount]->pBuffMatModel->Release();
				m_partsAll[nCount]->pBuffMatModel = NULL;
			}

			if (m_partsAll[nCount]->pPos != NULL)
			{//���_�����
				delete[] m_partsAll[nCount]->pPos;
			}

			delete m_partsAll[nCount];
			m_partsAll[nCount] = NULL;
		}
	}
}
//=============================================================================
//�U���`�F�b�N �S�̂���
//=============================================================================
void CCharacter::AtkCollision(void)
{
	CScene *pSceneAtk;
	CScene *pSceneDef;

	pSceneAtk = CScene::GetTop(CHAR_PRIORITY);
	while (pSceneAtk != NULL)
	{//�I���܂�
		if (pSceneAtk->GetObjType() == OBJTYPE_PLAYER || pSceneAtk->GetObjType() == OBJTYPE_ENEMY)
		{//�L��������
			CCharacter *pAtk = (CCharacter*)pSceneAtk;
			COneMotion	*pOneMotion = &CMotion::GetMotion(pAtk->GetType())->GetOneMotion()[pAtk->GetnNumMotion(0)];
			if (pOneMotion->GetType()[pAtk->GetnNumMotion(2)] == CKey::TYPE_ATTACK)
			{//�U���̃L�[�ł���
				CAtkKey		*pKey = (CAtkKey*)pOneMotion->GetKey()[pAtk->GetnNumMotion(2)];

				if (pAtk->m_fFrame - (pAtk->m_fSumFrame / FRAME_SPEED) == 0.0f)
				{//�U���J�n��
					bool bOrbit = true;

					if (pAtk->GetnNumMotion(2) > 0) 
					{//�O�̃L�[������
						if (pOneMotion->GetType()[pAtk->GetnNumMotion(2) - 1] == CKey::TYPE_ATTACK)
						{//�O�̃L�[���U�����[�V�����Ȃ�
							bOrbit = false;	//�O�Ր����_��
						}
					}

					if (bOrbit)
					{//�O�Ղ��������Ă��ǂ��Ȃ�
						CManager::GetSound()->Play(CSound::LABEL_ATTACK000);
						CMeshOrbit *pOrbit;
						D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f);
						pAtk->AtkVoice();

						if (SceneCreate(pOrbit, ORBIT_PRIORITY))
						{//���b�V���I�[�r�b�g����
							pOrbit->Set(pAtk->GetpParts()[0]->GetBone()[20].GetMtx(), D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(0.0f, (pKey->GetfRange() * 0.5f) * pKey->GetnCntAtk(), 0.0f), pAtk->GetbOrbit(), col, CScene::TEX_Orbit);
							pOrbit->GetDrawType() = CScene::DRAW_TYPE_SUBTRACT;
						}
						CLineEffect *pEffect;
						if (SceneCreate(pEffect, SLEffect_PRIORITY))
						{
							pEffect->Set(pAtk->GetpParts()[0]->GetBone()[20].GetMtx(), D3DXVECTOR3(0.0f, (pKey->GetfRange() * 0.5f) * pKey->GetnCntAtk(), 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 30.0f, pAtk->m_bOrbit, CLineEffect::TYPE_FIRE);
						}
					}
				}

				if ((float)pKey->GetnHitFrame(0) <= pAtk->m_fFrame && (float)pKey->GetnHitFrame(1) >= pAtk->m_fFrame)
				{//�U���̔���t���[���ł���
					pSceneDef = CScene::GetTop(CHAR_PRIORITY);
					while (pSceneDef != NULL)
					{//�I���܂�
						if (pSceneAtk != pSceneDef)
						{//�����L�����o�Ȃ�
							if (pSceneDef->GetObjType() == OBJTYPE_PLAYER || pSceneDef->GetObjType() == OBJTYPE_ENEMY)
							{//�L��������
								HitCheck(pSceneAtk, pSceneDef);	//���݂��Ƀq�b�g�`�F�b�N
							}
						}
						pSceneDef = pSceneDef->GetpNext();
					}//����
				}//if(�U��F�͈͓�)
			}//if(�U��)
		}//if(�L����)
		pSceneAtk = pSceneAtk->GetpNext();
	}//while(NULL)

	//�e����

	//�q�b�g�`�F�b�N
	HitMotionAll();
}
//=============================================================================
//�U���`�F�b�N �P�̂���
//=============================================================================
void CCharacter::HitCheck(CScene *&pAtkChar, CScene *&pDefChar)
{
	//�L�����N�^�[�^�ɕϊ�
	CCharacter *pAtk = (CCharacter*)pAtkChar;
	CCharacter *pDef = (CCharacter*)pDefChar;
	
	if(pDef->m_nInvincible == 0 && (pAtk->m_Team != pDef->m_Team || pAtk->m_Team == TEAM_IGNORED))
	{//���G�A�`�[���m�F
		//�U����Ԋm�F�@�Ⴄ�Ȃ烊�^�[��
		COneMotion *pMotion = &CMotion::GetMotion(pAtk->GetType())->GetOneMotion()[pAtk->GetnNumMotion(0)];
		if (pMotion->GetType()[pAtk->GetnNumMotion(2)] != CKey::TYPE_ATTACK) { return; }

		//�ʒu�擾
		D3DXVECTOR3 &Atkpos = pAtk->Getpos();
		D3DXVECTOR3 &Defpos = pDef->Getpos();

		//�����`�F�b�N
		if (powf(Atkpos.x - Defpos.x, 2) + powf(Atkpos.z - Defpos.z, 2) < MAX_ATKCHECK)
		{//�͈͓�
			CAtkKey		*pKey = (CAtkKey*)pMotion->GetKey()[pAtk->GetnNumMotion(2)];	//�L�[�擾
			D3DXMATRIX	mtxTrans, mtxWK;		//�v�Z�p�}�g���b�N�X
			D3DXVECTOR3	&length = pDef->Getlength();
			float		&fRange = pKey->GetfRange();
			float		fValid = 1.0f;
			float		fRot;

			//��Ԃɂ����Y�L���l�ύX
			if (pDef->GetnNumMotion(MOTION_BLOW)) { fValid = 1.25f; }
			else if (!pDef->GetbJump()) { fValid = 0.5f; }

			mtxWK = pAtk->GetpParts()[0]->GetmtxWorld(pKey->GetnAtkParts());	//�e�̃}�g���b�N�X���擾
			D3DXMatrixTranslation(&mtxTrans, 0.0f, fRange * 2.0f, 0.0f);	//�͈͕��ړ��l�v�Z

			for (int nCntAtk = 0; nCntAtk < pKey->GetnCntAtk(); nCntAtk++)
			{//for(�U���񐔕���])
				if (nCntAtk != 0)
				{// �ړ��𔽉f
					D3DXMatrixMultiply(&mtxTrans, &mtxTrans, &mtxWK);
					mtxWK = mtxTrans;
				}

				if (mtxWK._42 - fRange < Defpos.y + length.y * fValid && mtxWK._42 + fRange > Defpos.y - length.y * fValid)
				{//if(Y���͈͓�)
					if (powf(mtxWK._41 - Defpos.x, 2) + powf(mtxWK._43 - Defpos.z, 2) < fRange * fRange)
					{//if(XZ���͈͓�)
						if (pAtk->CheckHitChar(pDefChar))
						{//�q�b�g�m�F
							CSound *&pSound = CManager::GetSound();

							int nHitType = 0;
							float fHit = 1.0f;
							float fDamage;
							bool  bMotion = false;
							bool  bHit = true;

							CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�q�b�g\n");

							//�q�b�g�����
							if (pDef->m_nNumMotion[0] == MOTION_DOWN) 
							{
								bMotion = true;
								fHit *= 1.3f; nHitType = 1;
								pSound->Play(CSound::LABEL_CRITICAL);
							}
							else
							{//���肪�_�E���łȂ�
								switch (pDef->m_state)
								{//��Ԃɂ���ăq�b�g�������ύX
								case STATE_NONE:  bMotion = true; pDef->m_col.a = 0.0f; pSound->Play(CSound::LABEL_HIT000); break;
								case STATE_ARMOR: nHitType = 2; pDef->m_col.a = 0.75f; break;
								case STATE_AVOID: nHitType = 5; fHit = 0.0f; bHit = false; break;
								case STATE_GUARD:
									pDef->UseStamina(10.0f * pKey->GetfAtkplus());
									if (pDef->m_fStamina >= 0)
									{//�K�[�h����
										pSound->Play(CSound::LABEL_GUARD);
										nHitType = 3; fHit = 0.2f;
										pDef->m_state = STATE_CANCEL;
										pDef->SetNextMotion(MOTION_GUARD2);
									}
									else
									{//�K�[�h�u���C�N
										bMotion = true; pDef->m_col.a = 0.0f; pSound->Play(CSound::LABEL_HIT000);
									}
									break;
								case STATE_PARIS:
									pSound->Play(CSound::LABEL_PARIS);
									nHitType = 4; fHit = 0.0f;
									pDef->m_state = STATE_CANCEL;
									pAtk->m_state = STATE_CANCEL;
									pDef->SetNextMotion(MOTION_NEUTRAL);
									pAtk->SetNextMotion(MOTION_PARIS2);
									break;
								}
							}//else ���肪�_�E���łȂ�

							if (bHit)
							{//�ʏ�ʂ�̃q�b�g����Ȃ�
								CSceneAnim3D	*pAnim;
								//CScene3D		*p3D;
								//�q�b�g���󂯑��̊p�x�␳
								fRot = pAtk->Getrot().y + D3DX_PI;
								if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2; }
								if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2; }
								pDef->Getrot().y = fRot;
								pDef->m_fFramePlus = 1.0f;
								pDef->m_fFramePlus2 = 0.0f;
								pAtk->m_fFramePlus = 0.0f;
								if (fHit >= 1.0f) { pDef->DefVoice(); }
								//�G�t�F�N�g
								if (SceneCreate(pAnim, S3D_PRIORITY))
								{
									pAnim->Set(pDef->Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f),
										D3DXVECTOR3(15.0f, 15.0f, 0.0f), CScene::TEX_HIT0, true, CScene::DRAW_TYPE_ZADD, 0, 5, 2, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
								}
								if (SceneCreate(pAnim, S3D_PRIORITY))
								{
									pAnim->Set(pDef->Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f),
										D3DXVECTOR3(80.0f, 80.0f, 0.0f), CScene::TEX_HIT1, true, CScene::DRAW_TYPE_ZOVERLAY, 0, 5, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_FADESPIN);
								}
								//if (SceneCreate(p3D, S3D_PRIORITY + 2))
								//{
								//	p3D->Set(pDef->Getpos() + D3DXVECTOR3(0.0f, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								//		D3DXVECTOR3(75.0f, 30.0f, 0.0f), CScene::TEX_HitLogo, nHitType, 1, 7, true, CScene::DRAW_TYPE_NORMAL);
								//	p3D->GetState() = CScene3D::STATE_HIT; p3D->GetfCntState() = 0.01f;
								//}
								pDef->SetLightCol(D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f));
								pAtk->SetLightStr( 0.5f, 30.0f);
							}
							fDamage = pAtk->m_fAtk * pKey->GetfAtkplus() * fHit;
							pDef->m_fLife -= fDamage;
							pAtk->m_fSP += (fDamage * 0.05f) * fHit;

							if (pAtk->m_fSP > pAtk->m_fMaxSP) { pAtk->m_fSP = pAtk->m_fMaxSP; }
							Atkpos.y += (Defpos.y - Atkpos.y) * 0.05f;
							if (pDef->m_fLife <= 0.0f)
							{//����
								pDef->Dead();
								pDef->SetNextMotion(MOTION_DOWN);
								pDef->m_state = STATE_CANCEL;
								//�o���l��
							}
							else if (bMotion)
							{//��ԂŃ��[�V�����ύX���\�Ȃ�
								if (pKey->GetnAtkType() == CAtkKey::ATK_TYPE_SMASH) 
								{ pDef->SetNextMotion(MOTION_BLOW); pDef->m_state = STATE_CANCEL; }
								else if (pDef->m_nNumMotion[0] != MOTION_BLOW && pDef->m_nNumMotion[0] != MOTION_DOWN)
								{//������тł��_�E���ł��Ȃ�
									if (pDef->m_nCntDamage > 0 || !pDef->GetbJump()) { pDef->SetNextMotion(MOTION_BLOW); pDef->m_state = STATE_CANCEL; }
									else { pDef->SetNextMotion(MOTION_DESPONDENCY); pDef->m_state = STATE_CANCEL; }

									if (pKey->GetnAtkType() == CAtkKey::ATK_TYPE_NORMAL) { pDef->m_nCntDamage = 120 * FRAME_SPEED; }
								}
							}
							//else if (pDef->m_nNumMotion[0] == MOTION_BLOW) { pDef->Getmove().y = 2.0f; }
						}//if(�q�b�g�m�F)
					}//if(XZ���͈͓�)
				}//if(Y���͈͓�)
			}//for(�U���񐔕���])
		}//if(�����`�F�b�N)
	}//if(���G�łȂ��Ȃ�)
}
//=============================================================================
//�q�b�g�ヂ�[�V�����X�V
//=============================================================================
void CCharacter::HitMotionAll(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_PLAYER || pScene->GetObjType() == OBJTYPE_ENEMY)
		{//�L��������
			((CCharacter*)pScene)->HitMotion();	//�q�b�g�������m�F
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//�q�b�g�ヂ�[�V�����X�V
//=============================================================================
void CCharacter::HitMotion(void)
{
	if (m_state == STATE_CANCEL)
	{//�q�b�g����
		SetCancelMotion(m_nNumMotion[1]);	//���݂�_�E�����ɕύX
	}
	m_state = STATE_NONE;
}
//=============================================================================
//�q�b�g���Ă��Ȃ����m�F�X�V
//=============================================================================
bool CCharacter::CheckHitChar(CScene *&pChar)
{
	if (m_nCntHit < MAX_HITCHAR)
	{//�܂��q�b�g�L������ۑ��ł���Ȃ�
		for (int nCount = 0; nCount < m_nCntHit; nCount++)
		{//�ۑ����ꂽ�L�������m�F
			if (m_pHit[nCount] == pChar) { return false; }
		}

		if (m_nCntHit < MAX_HITCHAR)
		{//�܂��ۑ��ł���
			m_pHit[m_nCntHit] = pChar;
			m_nCntHit++;
		}
		return true;
	}
	return false;
}
//=============================================================================
//�q�b�g�����L���������Z�b�g
//=============================================================================
void CCharacter::ReSetHitChar(void) 
{ 
	if (m_nCntHit > 0)
	{
		CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "���Z�b�g%d\n", m_nCntHit);
	}
	for (int nCount = 0; nCount < m_nCntHit; nCount++)
	{//�ۑ��������폜
		m_pHit[nCount] = NULL;
	}
	m_nCntHit = 0;
}

//=============================================================================
// �L�����N�^�[�̏�����
//=============================================================================
HRESULT CCharacter::Init(void)
{
	m_Team = TEAM_IGNORED;
	m_state = STATE_NONE;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_addpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addPosmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_length = D3DXVECTOR3(30.0f, 85.0f, 30.0f);
	m_FNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxParts = 0;
	m_pParts = NULL;
	m_bJump = false;
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_fFramePlus = 1.0f;
	m_fInitFrame = 0.0f;
	m_nLeg = 0;
	m_nCntReUse = -1;
	m_nCntDamage = 0;
	m_nInvincible = 0;
	m_fFrame = 0.0f;
	m_fMotionFrame = 0.0f;
	m_fKeepFrame = 0.0f;

	m_bOrbit = false;
	m_bBoost = false;
	m_pLockChar = NULL;
	m_pWaitMotion = NULL;
	m_pUseMotion = NULL;

	//�q�b�g�����L���������Z�b�g
	m_nCntHit = MAX_HITCHAR;
	ReSetHitChar();
	m_Voice = CSound::LABEL_MAX;

	//�X�e�[�^�X��������
	m_fMaxStamina = 200.0f;
	m_nLevel = 1;
	SetStatus();
	m_fCntStamina = 0.0f;

	//if (m_pGage == NULL)
	//{
	//	if (Create(m_pGage))
	//	{
	//		m_pGage->Set(m_pos, 50.0f, 1.5f, m_fLife, m_fMaxLife, C3DGage::STATE_LIFE);
	//	}
	//}
	return S_OK;
}
//=============================================================================
// �L�����N�^�[�̏I��
//=============================================================================
void CCharacter::Uninit(void)
{
	if (m_pGage != NULL) { m_pGage->Uninit(); m_pGage = NULL; }
	
	delete[] m_pWaitMotion;
	delete[] m_pUseMotion;
	if (m_pParts != NULL)
	{
		for (int nCount = 0; nCount < m_nMaxParts; nCount++)
		{
			m_pParts[nCount]->Uninit();
		}
		delete[] m_pParts; m_pParts = NULL;
	}
	CScene::Uninit();
}
//=============================================================================
// ���[�V�����ւ̎w��
//=============================================================================
void CCharacter::DirectMotion(DIRECT Direct)
{
	if (Direct != DIRECT_NO)
	{
		if (Direct == DIRECT_ATTACK || Direct == DIRECT_ATTACK2)
		{//�����ɉ����Ďw���ύX
			if (GetObjType() == OBJTYPE_PLAYER)
			{
				//���͕����ɂ����
				CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(0);	//�W���C�p�b�h���l��
				int nAttack = (int)MOTION_ATTACK;

				if (Direct == DIRECT_ATTACK2) { nAttack += 3; }
				if (!m_bJump) { nAttack += 6; }
				if (Direct == DIRECT_ATTACK2 && !m_bJump) { nAttack += 1; }
				if (pInputPad->GetStickDefeat(0))
				{
					CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(((CPlayer*)this)->GetnID())->GetChar();

					float fRotPad = pInputPad->GetfStickAngle(0);
					float fRotCamera = pCamera->GetRot().y;

					if (Direct == DIRECT_ATTACK2)
					{//�X�L���Ȃ�X�e�B�b�N��Ԃɂ���čU���̕���
						if (D3DX_PI * 0.5f >= fRotPad && -D3DX_PI * 0.5f <= fRotPad)
						{
							int nData = pInputPad->GetnPress(INPUT_LS_D);
							int nData2 = pInputPad->GetnRelease(INPUT_LS_D);
							if (pInputPad->GetnRelease(INPUT_LS_D) > -20 &&
								pInputPad->GetnPress(INPUT_LS_D) < 0 && pInputPad->GetnPress(INPUT_LS_D) > -20) { SetNextMotion(MOTION_ATTACK + 13); return; }
						}
						else
						{
							if (pInputPad->GetnRelease(INPUT_LS_U) > -20 && 
								pInputPad->GetnPress(INPUT_LS_U) < 0 && pInputPad->GetnPress(INPUT_LS_U) > -20) { SetNextMotion(MOTION_ATTACK + 14); return; }
						}
					}

					if (D3DX_PI * 0.5f >= fRotPad && -D3DX_PI * 0.5f <= fRotPad) { SetNextMotion(nAttack + 1); pInputPad->NoInput(INPUT_LS_U); }
					else 
					{ AtkRot(m_fRot, ((CPlayer*)this)->GetnID()); SetNextMotion(nAttack + 2); pInputPad->NoInput(INPUT_LS_D); }
				}
				else { SetNextMotion(nAttack); }
				pInputPad->ReSetPress();
			}
		}
		else
		{//�U���łȂ�
			switch (Direct)
			{
			case DIRECT_SKILL1:	SetNextMotion(MOTION_ATTACK); break;
			case DIRECT_SKILL2:	SetNextMotion(MOTION_ATTACK); break;
			case DIRECT_JUMP:	SetNextMotion(MOTION_JUMP); break;
			case DIRECT_BOOST:	SetNextMotion(MOTION_BOOST); m_bBoost = true; break;
			case DIRECT_GUARD:	SetNextMotion(MOTION_GUARD); break;
			case DIRECT_PARIS:	SetNextMotion(MOTION_PARIS); break;
			}
		}
	}//if(�w���L��)
}
//=============================================================================
// �j���[�g�����U�����@�p�x�̕ύX����
//=============================================================================
void	CCharacter::AtkRot(float &fRot, int &nID)
{
	CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(nID)->GetChar();
	float fAngle = fRot - pCamera->GetRot().y;

	if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	if (fAngle < -D3DX_PI * 0.55f || fAngle > D3DX_PI * 0.55f)
	{//�J�����̌����ʂ�Ȃ�
		fRot += D3DX_PI;
		if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2.0f; }
		if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2.0f; }
	}
}
//=============================================================================
// �L�����N�^�[�̍X�V
//=============================================================================
void CCharacter::Update(bool bMove)
{
	CMotion::TYPE &nType = m_pParts[0]->GetMotion();
	D3DXVECTOR3 Vec2;
	//float fTilt;
	//float fRot;
	float fMove = 1.0f;
	bool bSpin = false;
	m_fSumFrame = m_fFramePlus + m_fFramePlus2;
	if (m_fStamina <= 0) { fMove = 0.3f; }

	//if (m_bJump == true)
	//{
	//	Vec2 = D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y));
	//	fTilt = (m_FNor.x * Vec2.x) + (m_FNor.y * Vec2.y) + (m_FNor.z * Vec2.z) /
	//		(sqrtf(powf(m_FNor.x, 2) + powf(m_FNor.y, 2) + powf(m_FNor.z, 2)) * sqrtf(powf(Vec2.x, 2) + powf(Vec2.y, 2) + powf(Vec2.z, 2)));
	//	fRot = acosf(fTilt);
	//	fTilt = (fTilt * -1.0f) * 2.0f;
	//	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�X�� %f\n", fTilt);
	//	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�p�x %f\n", fRot);
	//	//if (fTilt < 0.8f && fTilt < 1.2f) { fTilt = 0.0f; }
	//	//else { fTilt *= fTilt; }
	//}

	if (m_nNumMotion[0] <= MOTION_S_NEUTRAL)
	{//�ړ������Ƀ��f���̌��������킹��
		float fRotPoor = m_fRot - m_rot.y;
		if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
		else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
		m_rot.y += fRotPoor * 0.15f;
		if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
		if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
	}

	if (CManager::GetInputKey()->GetTrigger(DIK_Z)){ CCharacter::ResetMotion(); }
	if (CManager::GetInputKey()->GetTrigger(DIK_B)) { CancelLock(); }
	if (CManager::GetInputKey()->GetTrigger(DIK_N)) { SetPlusFrame(0.5f, 120.0f); }

	//���[�V�����L�����Z���̍X�V
	CancelUpdate();
	CMotion		*pMotion = CMotion::GetMotion(nType);
	COneMotion	*pOneMotion = &CMotion::GetMotion(nType)->GetOneMotion()[m_nNumMotion[0]];
	CKey		*pKey = pOneMotion->GetKey()[m_nNumMotion[2]];
	CKey		*pKeyold;
	int			&nMaxParts = pMotion->GetnMaxParts();

	if (bMove)
	{//�ړ�
		if (m_nNumMotion[1] == -1 && m_bJump)
		{//���[�V�����̗\�񂪂Ȃ�
			COneMotion *pMotion = &CMotion::GetMotion(nType)->GetOneMotion()[m_nNumMotion[0]];
			if (pMotion->GetnOtherCancel(0) < m_fMotionFrame && m_fMotionFrame < pMotion->GetnOtherCancel(1))
			{
				m_nNumMotion[1] = MOTION_WALK;
			}
		}
		m_move += D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * -0.2f * m_fSumFrame * pKey->GetfMove() * fMove;
	}
	else if(m_nNumMotion[1] == -1)
	{//�ړ�����
		if (m_nNumMotion[0] == MOTION_WALK)
		{//�����Ȃ�@���ɍ��킹�ăj���[�g������
			if(m_nNumMotion[2] % 3 == 0 && m_fFrame <= 2.0f){ m_nNumMotion[1] = MOTION_NEUTRAL; }
		}
	}

	//���[�V����
	if (nType != CMotion::TYPE_MAX)
	{
		D3DXVECTOR3 Move;
		ResetUpdate();		//�U�����[�V���� ���Z�b�g�X�V

		while (1)
		{
			if (m_fFrame < (float)pKey->GetnFrame())
			{//�t���[�����͈͓��Ȃ�
				m_move.x += (0.0f - m_move.x) * (0.3f * pKey->GetfSlip());
				m_move.z += (0.0f - m_move.z) * (0.3f * pKey->GetfSlip());
				SetEffect(pKey);	//�L�[����

				//�ړ��l���Z�L���t���[���Ȃ�
				//if (m_fFrame < (float)pKey->GetnMoveType() * m_fSumFrame)
				//{
				//	float fRot = m_rot.y;
				//	Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//	Move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -pKey->GetMove().z;
				//	Move += D3DXVECTOR3(sinf(fRot + D3DX_PI * 0.5f), 0.0f, cosf(fRot + D3DX_PI * 0.5f)) * -pKey->GetMove().x;
				//	Move += Move * ((m_fSumFrame - 1.0f) * 0.35f);
				//	float fWKData = (float)pKey->GetnMoveType() / m_fSumFrame;
				//	if (fWKData < 1.0f) { fWKData = 1.0f; }
				//	else if (fWKData > m_fSumFrame) { fWKData = m_fSumFrame; }
				//	Move.y += pKey->GetMove().y * fWKData;
				//	
				//	if (pKey->GetMove().y > 0.0f)
				//	{
				//		m_bJump = false;
				//	}
				//	m_move += Move * fMove;
				//}

				m_addpos += m_addPosmove * m_fSumFrame;		//�{�̂̈ړ�
				for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
				{//�ۑ����ꂽmove��������
				D3DXVECTOR3 &addRot = m_pParts[0]->GetBone()[nCntModel].GetaddRot();
				 //rot�̈ړ��l���Z
					addRot += m_pParts[0]->GetBone()[nCntModel].GetaddRotMove() * m_fSumFrame;
					//���b�g�m�F
					if (addRot.x > D3DX_PI) { addRot.x -= D3DX_PI * 2; }
					else if (addRot.x < -D3DX_PI) { addRot.x += D3DX_PI * 2; }
					if (addRot.y > D3DX_PI) { addRot.y -= D3DX_PI * 2; }
					else if (addRot.y < -D3DX_PI) { addRot.y += D3DX_PI * 2; }
					if (addRot.z > D3DX_PI) { addRot.z -= D3DX_PI * 2; }
					else if (addRot.z < -D3DX_PI) { addRot.z += D3DX_PI * 2; }
				}
				//�i���̃t���[��
				m_fFrame += m_fSumFrame / FRAME_SPEED;//�t���[���̐i�s
				m_fMotionFrame += m_fSumFrame / FRAME_SPEED; //���[�V�����S�̃t���[���̐i�s
				m_fKeepFrame += m_fSumFrame / FRAME_SPEED; //���[�V�����p���t���[���̐i�s
				break;
			}
			else
			{//�L�[�̏I��
				m_fFrame = 0.0f;	//�t���[���̏�����
				SetRotMotion();
				m_nNumMotion[2]++;		//�L�[�̐i��

				if (m_nNumMotion[2] >= pOneMotion->GetnMaxKey())
				{//���̃��[�V�������I��
					if (pOneMotion->GetnNorBranch() > -1)
					{
						m_fRot = m_rot.y;		//���ȉ�]�h�~
						m_fMotionFrame = 0.0f;	//�S�t���[���̏�����
						m_fKeepFrame = 0.0f;	//�p��F�̏�����
						m_nNumMotion[2] = 0;	//�L�[�̏�����
						ReSetHitChar();			//�q�b�g�L�����̃��Z�b�g

						if (m_nNumMotion[0] != pOneMotion->GetnNorBranch())
						{//���[�v����Ȃ����
							m_nNumMotion[0] = pOneMotion->GetnNorBranch();	//���̃��[�V�����̕t�^
							if (m_nNumMotion[0] == MOTION_NEUTRAL) 
							{ 
								if (!GetbJump()) { m_nNumMotion[0] = MOTION_S_NEUTRAL; }//�󒆃j���[�g������
							}
							//if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_GETUP) { g_model_Info[nCount].set.nAirTime = 90; }	//�N���オ��Ȃ�
						}
						else { m_nNumMotion[0] = pOneMotion->GetnNorBranch(); }//���̃��[�V�����̕t�^}
						m_nNumMotion[3] = m_nNumMotion[0]; //���̃��[�V�����Ɍ��݂̃��[�V����������
					}
					else
					{//���̃L�[�ݒ肪����Ă��Ȃ��Ȃ炻�̂܂ܕ��u
						m_fMotionFrame -= pOneMotion->GetKey()[pOneMotion->GetnMaxKey() - 1]->GetnFrame();	//���[�V�����t���[����߂�
						m_nNumMotion[2]--;																	//�L�[��߂�
						m_fFrame = 0.0f;
					}
				}
				pOneMotion = &CMotion::GetMotion(nType)->GetOneMotion()[m_nNumMotion[0]];
				pKeyold = pKey;
				pKey = pOneMotion->GetKey()[m_nNumMotion[2]];

				m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
				for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
				{//move���v�Z���đ��
					D3DXVECTOR3 &addRot = m_pParts[0]->GetBone()[nCntModel].GetaddRot();
					D3DXVECTOR3 &addRotMove = m_pParts[0]->GetBone()[nCntModel].GetaddRotMove();
					addRot = pKeyold->GetpRot()[nCntModel];
					addRotMove = (pKey->GetpRot()[nCntModel] - addRot);

					//�p�x�m�F
					if (addRotMove.x > D3DX_PI) { addRotMove.x -= D3DX_PI * 2; }
					else if (addRotMove.x < -D3DX_PI) { addRotMove.x += D3DX_PI * 2; }
					if (addRotMove.y > D3DX_PI) { addRotMove.y -= D3DX_PI * 2; }
					else if (addRotMove.y < -D3DX_PI) { addRotMove.y += D3DX_PI * 2; }
					if (addRotMove.z > D3DX_PI) { addRotMove.z -= D3DX_PI * 2; }
					else if (addRotMove.z < -D3DX_PI) { addRotMove.z += D3DX_PI * 2; }

					addRotMove /= (float)pKey->GetnFrame() * FRAME_SPEED;
				}
			}//�L�[�I��
		}//�X�Vwhile
		m_fFramePlus += (1.0f - m_fFramePlus) * 0.1f;
		m_fInitFrame -= m_fFramePlus / FRAME_SPEED;
		if (m_fInitFrame < 0.0f)
		{//���Ԍo�߂���������
			m_fInitFrame = 0.0f;
			m_fFramePlus2 += (0.0f - m_fFramePlus2) * 0.05f;
		}
	}

	//�ʒu���̍X�V
	m_posold = m_pos;
	m_pos += m_move;
	//if (pKey->GetnFloating() < 2) { m_move.y -= 0.3f; }
	//if (pKey->GetnFloating() == 2) 
	//{ m_move.y = 0.0f; }

	int		nCount = 0;
	bool bLand = m_bJump;
	CMesh::MeshCollisionCeiling(m_pos, m_posold, m_length);											//���b�V������
	CCharacter::CollisionAll(this);//�L�������m�����蔻��
	CSceneObjct::CollisionAll(m_pos, m_posold, m_move, m_length, m_FNor, nCount, bLand, true);	//�I�u�W�F�N�g
	nCount = 0;
	CMesh::MeshCollisionWall(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, false);	//���b�V����
	CMesh::MeshCollisionField(m_pos, m_posold, m_move, m_length, m_FNor, bLand);					//���b�V����

	if (!m_bJump && bLand && pKey->GetnFloating() == 0)
	{//���n
		SetCancelMotion(pOneMotion->GetnLandBranch());
	}
		m_bJump = true;

	//���̑��̍X�V
	m_bBoost = false;
	m_bVtx = false;
	if (m_fLife <= 0)
	{//����ł���Ȃ�
		m_nInvincible++;
		if (m_nInvincible > 180)
		{
			//���g�ւ̃��b�N�I�����O��
			CancelLock();
			Over();
			return;
		}
	}
	else
	{//����ł��Ȃ��Ȃ�
		if (m_col.a < 1.0f)
		{
			m_col.a += 0.005f;
			if (m_col.a > 1.0f) { m_col.a = 1.0f; }
		}
		if (m_nCntDamage > 0) { m_nCntDamage--; }		//�_���[�W�㐁����т܂ŃJ�E���g
		if (m_nInvincible > 0) { m_nInvincible--; }		//���G���Ԍ���
	}
	if (m_pGage != NULL) { m_pGage->Update(); }
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "P�t���[���F%.3f\n", m_fSumFrame);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "���[�V���� ���݁F%d�@���F%d �L�[�F%d �t���[���F%.1f\n", m_nNumMotion[0], m_nNumMotion[1], m_nNumMotion[2], m_fFrame);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�@�� %.1f�@%.1f�@%.1f\n", m_FNor.x, m_FNor.y, m_FNor.z);
}
//=============================================================================
// �L�����N�^�[�̕`��
//=============================================================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXVECTOR3 pos = m_pos + m_addpos;
	D3DXMATRIX			mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	CScene::DRAW_TYPE DType = m_DrawType;
	bool				bShadow = false;
	if (m_nInvincible > 0) { DType = CScene::DRAW_TYPE_AER; }

		 // ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_Mtx);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_Mtx, &m_Mtx, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&m_Mtx, &m_Mtx, &mtxTrans);

		if (m_nInvincible > 0) { pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); bShadow = true; }

		for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
		{//�p�[�c��������]
			m_pParts[nCntModel]->Draw(this);
		}
		m_bVtx = true;
}
//=============================================================================
// ���S����
//=============================================================================
void CCharacter::Dead(void)
{
	//�G�t�F�N�g
	CSceneAnim3D	*pAnim;
	if (SceneCreate(pAnim, S3D_PRIORITY))
	{
		pAnim->Set(Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(20.0f, 20.0f, 0.0f), CScene::TEX_Dead, true, CScene::DRAW_TYPE_ZOVERLAY, 0, 5, 2, 4, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_FADESPIN);
	}
	//���ʉ�
	CManager::GetSound()->Play(CSound::LABEL_DEAD);

	DeadVoice();
}
//=============================================================================
// ���S����
//=============================================================================
void CCharacter::Over(void)
{
	//�G�t�F�N�g
	CSceneAnim3D	*pAnim;
	if (SceneCreate(pAnim, S3D_PRIORITY))
	{
		pAnim->Set(Getpos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(150.0f, 150.0f, 0.0f), CScene::TEX_Over, true, CScene::DRAW_TYPE_ZOVERLAY, 0, 10, 1, 4, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
	}
	//���ʉ�
	CManager::GetSound()->Play(CSound::LABEL_OVER);
	Uninit();
}
//=============================================================================
// �U������������
//=============================================================================
void CCharacter::AtkVoice(void)
{

}
//=============================================================================
// ��_������������
//=============================================================================
void CCharacter::DefVoice(void)
{

}
//=============================================================================
// ���S����������
//=============================================================================
void CCharacter::DeadVoice(void)
{

}
//=============================================================================
// ���[�V�����̃L�����Z���X�V
//=============================================================================
void CCharacter::CancelUpdate(void)
{
	if (m_nNumMotion[1] != -1)
	{//�\�񂪓����Ă��� && ���݂̃��[�V�����łȂ�
		if (CheckAtkNumber(m_nNumMotion[1]))
		{
			if (m_nNumMotion[0] != m_nNumMotion[1] || m_nNumMotion[1] == MOTION_GUARD)
			{
				COneMotion *pMotion = &CMotion::GetMotion(m_pParts[0]->GetMotion())->GetOneMotion()[m_nNumMotion[0]];
				bool bCancel = false;
				bool bStart = false;

				if (m_nNumMotion[1] == MOTION_BLOW || m_nNumMotion[1] == MOTION_DESPONDENCY)
				{//���݁A�_�E���͖���
					bCancel = true;
				}
				if (m_nNumMotion[0] == MOTION_GUARD)
				{//�K�[�h�� �K�[�h�A�p���B�͖���
					if (m_nNumMotion[1] == MOTION_GUARD || m_nNumMotion[1] == MOTION_PARIS) { bCancel = true; }
				}

				if (pMotion->GetnOtherCancel(0) < m_fMotionFrame && m_fMotionFrame < pMotion->GetnOtherCancel(1))
				{//�L�����Z���\
					bCancel = true;
				}
				else if (MOTION_BOOST <= m_nNumMotion[1])
				{//�\�񂪃u�[�X�g�ȏ�Ȃ�
					if ((pMotion->GetnStartCancel(0) <= m_fMotionFrame && m_fMotionFrame < pMotion->GetnStartCancel(1)) ||
						(pMotion->GetnEndCancel(0) <= m_fMotionFrame && m_fMotionFrame < pMotion->GetnEndCancel(1)))
					{//�L�����Z���\
						bCancel = true;
						bStart = true;		//�X�^�[�g�L�����Z���K�p
					}
				}
				if (bCancel)
				{//�L�����Z�����\
					SetCancelMotion(m_nNumMotion[1]);	//���[�V�����̃L�����Z��
					m_nCancelFrame = -1;				//���[�V�����L�����Z���ێ��t���[��������
				}
			}//if(���Z�łȂ�)
		}//if(�O��s�����U�����[�V�����łȂ�)
		else { m_nCancelFrame = -1; }
		//���e���ێ�
		m_nCancelFrame--;
		if (m_nCancelFrame < 0) { m_nNumMotion[1] = -1; m_nCancelFrame = 0; }//�����[�V����������
	}//if(���[�V�����̗\��L)
}
//=============================================================================
// ���[�V�����̃L�����Z���ݒ�
//=============================================================================
void CCharacter::SetCancelMotion(int nNumber)
{
	CMotion::TYPE &m_Type = m_pParts[0]->GetMotion();

	//SP�m�F
	if (!UseSP(nNumber)) { m_nNumMotion[1] = -1; return; }

	//�_�E��2�A���m�F
	if (m_nNumMotion[0] == MOTION_DOWN && m_nNumMotion[1] == MOTION_BLOW) { m_nInvincible = 500; }

	//���̓���ւ�
	if (m_nNumMotion[0] == MOTION_WALK && m_nNumMotion[1] == MOTION_NEUTRAL) { m_nLeg = m_nNumMotion[2]; }
	m_pWaitMotion[nNumber] = CMotion::GetMotion(m_Type)->GetOneMotion()[nNumber].GetfWaitTime();
	m_nNumMotion[3] = m_nNumMotion[0];	//�O���[�V�������
	m_nNumMotion[0] = nNumber;			//���[�V�����̃L�����Z��
	m_nNumMotion[2] = 0;
	m_nNumMotion[1] = -1;				//�����[�V�����̏�����
	m_fFrame = 0.0f;			//�t���[����������
	m_fMotionFrame = 0.0f;		//���[�V�����S�̃t���[����������
	m_fKeepFrame = 0.0f;

	COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];

	if (m_nNumMotion[0] == MOTION_WALK)	  { m_nNumMotion[2] = m_nLeg; }		//�����Ȃ�O��̓r������
	if (m_nNumMotion[3] >= MOTION_ATTACK && m_nNumMotion[0] >= MOTION_ATTACK) { m_fFramePlus = 2.0f; UseStamina(10.0f); }			//�L�[�ɃL�����Z��������
	if (m_nNumMotion[0] >= MOTION_ATTACK) { m_rot.y = m_fARot; }			//�U�����[�V�����Ȃ�ړ������ɍ��킹��
	CKey *pKey = pMotion->GetKey()[m_nNumMotion[2]];
	int nMaxParts = CMotion::GetMotion(m_Type)->GetnMaxParts();
	if (m_nNumMotion[2] > 0)
	{
		for (int nCount = 0; nCount < m_nNumMotion[2]; nCount++)
		{//���[�V�����S�̃t���[�����L�[���i�߂�
			m_fMotionFrame += (float)pMotion->GetKey()[nCount]->GetnFrame();
		}
	}

	m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
	for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
	{//move���v�Z���đ��
		D3DXVECTOR3 &addRotMove = m_pParts[0]->GetBone()[nCntModel].GetaddRotMove();
		addRotMove = (pKey->GetpRot()[nCntModel] - m_pParts[0]->GetBone()[nCntModel].GetaddRot()) / FRAME_SPEED;

		//�p�x�m�F
		if (addRotMove.x > D3DX_PI) { addRotMove.x -= D3DX_PI * 2; }
		else if (addRotMove.x < -D3DX_PI) { addRotMove.x += D3DX_PI * 2; }
		if (addRotMove.y > D3DX_PI) { addRotMove.y -= D3DX_PI * 2; }
		else if (addRotMove.y < -D3DX_PI) { addRotMove.y += D3DX_PI * 2; }
		if (addRotMove.z > D3DX_PI) { addRotMove.z -= D3DX_PI * 2; }
		else if (addRotMove.z < -D3DX_PI) { addRotMove.z += D3DX_PI * 2; }

		addRotMove /= (float)pKey->GetnFrame();
	}

	switch (m_nNumMotion[0])
	{//���[�V��������������
	case MOTION_BLOW:	m_move = D3DXVECTOR3(0.0f, 3.5f, 0.0f); m_bJump = false;	break;
	case MOTION_RETURN:	m_nCntDamage = 0; m_nInvincible = 120 * FRAME_SPEED;		break;
	}
	SetAtkNumber(m_nNumMotion[0]);		//�U�����[�V�����̕ۑ�
	m_bOrbit = true; CMeshOrbit::Delete(); CLineEffect::Delete(); m_bOrbit = false;	//�I�[�r�b�g�̍폜
	ReSetHitChar();						//�q�b�g�L�����̃��Z�b�g
}
//=============================================================================
//�@���̃��[�V�����ւ̗\��
//=============================================================================
void CCharacter::SetNextMotion(int nNumber)
{
	m_nNumMotion[1] = nNumber;
	m_nCancelFrame = 20;
	m_fARot = m_fRot;
}
//=============================================================================
// ���[�V�����̃��Z�b�g
//=============================================================================
void CCharacter::ResetMotion(void)
{
	m_nNumMotion[0] = 0;
	m_nNumMotion[1] = -1;
	m_nNumMotion[2] = 0;
	m_nNumMotion[3] = 0;
	m_fFrame = 99999.0f;
	SetRotMotion();
}
//=============================================================================
//���[�V�����̔ԍ��̕ۑ�
//=============================================================================
void CCharacter::SetAtkNumber(int nNumber)					//���[�V�����̔ԍ��L�^
{
	if (nNumber >= MOTION_ATTACK)
	{
		m_pUseMotion[nNumber] = true;
	}
}
//=============================================================================
//���[�V�����̔ԍ��̃��Z�b�g�X�V
//=============================================================================
void CCharacter::ResetUpdate(void)
{
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();

	for (int nCount = 0; nCount < nMaxMotion; nCount++)
	{//���[�V�������Ƃ̑҂����Ԋm�F
		if (m_pWaitMotion[nCount] > 0)
		{//�҂����Ԃ�����Ȃ�
			m_pWaitMotion[nCount]--;
		}
	}

	if (m_nNumMotion[0] < MOTION_ATTACK)
	{//���݂��U�����[�V�����łȂ�
		if (m_nCntReUse > 0)
		{//�ۑ������U���̉�����K�v
			m_nCntReUse--;
			if (m_nCntReUse == 0)
			{//�҂����Ԃ̌���
				ResetAtkNumber();
			}
		}
	}
	else { m_nCntReUse = 30; }

	if (m_nNumMotion[0] < MOTION_JUMP || m_nNumMotion[0] == MOTION_APPEAL)
	{//�j���[�g�����������Ȃ�
		if (m_fCntStamina > 0) { m_fCntStamina -= 1.0f; }
		else if (m_fStamina < m_fMaxStamina)
		{//�񕜉\
			if (m_fStamina < 0.0f) { m_fCntStamina -= 0.5f; }
			m_fStamina += 4.0f;
		}
	}
	else { m_fCntStamina = 90.0f; }
}
//=============================================================================
//���[�V�����̔ԍ��̃��Z�b�g
//=============================================================================
void CCharacter::ResetAtkNumber(void)
{
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();
	for (int nCount = 0; nCount < nMaxMotion; nCount++)
	{
		m_pUseMotion[nCount] = false;
	}
}
//=============================================================================
//���[�V�����̔ԍ��̊m�F
//=============================================================================
bool CCharacter::CheckAtkNumber(int nNumber)
{
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();
	if(nNumber < nMaxMotion)
	{//�s�����U���Ƒ҂����Ԋm�F
		if (m_pWaitMotion[nNumber] > 0.0f)		{ return false; }
		if (m_pUseMotion[nNumber] == true)	{ return false; }
	}
	return true;
}
//=============================================================================
//�p�x�Ɗp�x�̃`�F�b�N����
//=============================================================================
float CCharacter::AngleCheck(float fAngle0, float fAngle1)
{
	fAngle1 -= fAngle0;
	if (fAngle1 > D3DX_PI) { fAngle1 -= D3DX_PI * 2.0f; }
	if (fAngle1 < -D3DX_PI) { fAngle1 += D3DX_PI * 2.0f; }
	return fAngle1;
}
//=============================================================================
//�X�^�~�i�̎g�p����
//=============================================================================
void CCharacter::UseStamina(float fValue)
{
	m_fStamina -= fValue;
	if (m_fStamina < 0) { m_fStamina = -60.0f; }
}
//=============================================================================
//SP�̎g�p����
//=============================================================================
bool CCharacter::UseSP(int nNumber)
{
	CKey  *pKey = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetOneMotion()[nNumber].GetKey()[0];
	float fValue = 0.0f;
	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		fValue += GetEffect_SP(pKey->GetpEffect()[nCount]);
	}

	if (m_fSP >= fValue) { m_fSP -= fValue; }
	else { return false; }
	return true;
}
//=============================================================================
//SP�̎g�p����
//=============================================================================
bool CCharacter::CheckSP(CMotion::TYPE type, int nNumber, float &fValue)
{
	CKey  *pKey = CMotion::GetMotion(type)->GetOneMotion()[nNumber].GetKey()[0];
	float fUse = 0.0f;
	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		fUse += GetEffect_SP(pKey->GetpEffect()[nCount]);
	}

	if (fValue < fUse) { return false; }
	return true;
}
//=============================================================================
//�ԍ�����g�p����SP��Ԃ�
//=============================================================================
float CCharacter::GetEffect_SP(int nNumber)
{
	switch (nNumber)
	{
	case 30: return 250.0f;
	case 31: return 30.0f;
	case 32: return 50.0f;
	case 33: return 200.0f;
	case 34: return 55.0f;
	case 35: return 60.0f;
	}
	return 0.0f;
}
//=============================================================================
//�L���������b�N
//=============================================================================
CScene *CCharacter::LockChar(LOCK lock)
{
	CCamera_Char *&pCamera = CManager::GetCamera()->GetPlay(((CPlayer*)this)->GetnID())->GetChar();
	CPlayer_UI *&pUI = ((CPlayer*)this)->GetpUI();
	CScene *pScene;
	CScene *pSceneLock = NULL;
	CScene *pSceneOld = NULL;
	CScene *pSceneNear = NULL;
	float	fDistance;	//����
	float	fWKData = D3DX_PI * 2.0f;	//�p�x
	float	fWKData2 = 0.0f;//������p�x
	float	fBaseAngle = pCamera->GetRot().y + D3DX_PI;		//���̊p�x
	float	fWKAngle;		//��r�p�̊p�x

	if		(fBaseAngle > D3DX_PI)	{ fBaseAngle -= D3DX_PI * 2.0f; }
	else if (fBaseAngle < -D3DX_PI) { fBaseAngle += D3DX_PI * 2.0f; }

	if (lock == LOCK_LEFT)	 { fWKData *= -1; }					//�������b�N�Ȃ��r�p�����l���]
	if (lock == LOCK_NEAR)	 { fWKData = 1500.0f * 1500.0f; }	//�������b�N�Ȃ��r�p�����l���]
	else if (m_pLockChar != NULL) { pSceneOld = m_pLockChar; }	//�߂����̃��b�N�łȂ�
	if (m_pLockChar != NULL) { pSceneNear = m_pLockChar; }		//�ŏI�m�F�p���b�N�Ώۂ�ۑ�
	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_PLAYER || pScene->GetObjType() == OBJTYPE_ENEMY)
		{
			CCharacter *pChar = (CCharacter*)pScene;
			if (pScene != this && pScene != pSceneOld && (m_Team != pChar->m_Team || m_Team == TEAM_IGNORED))
			{//�L��������
				D3DXVECTOR3 &pos = ((CCharacter*)pScene)->Getpos();

				fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);
				if (fDistance < 1500.0f * 1500.0f)
				{
					switch (lock)
					{
					case LOCK_NO:
					case LOCK_FIRST:
						fWKAngle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);	//�L�������m�̊p�x�擾
						fWKData2 = AngleCheck(fBaseAngle, fWKAngle);			//���b�N�p�x�Ƃ̍������擾
						if (fWKData2 < 0) { fWKData2 *= -1.0f; }				//�}�C�i�X�Ȃ�v���X��

						if (fWKData > fWKData2)
						{//���߂��p�x��
							fWKData = fWKData2;
							pSceneLock = pScene;
						}
						break;
					case LOCK_NEAR:
						if (fWKData > fDistance)
						{//���߂��p�x��
							fWKData = fDistance;
							pSceneLock = pScene;
						}
						break;
					case LOCK_LEFT:
					case LOCK_RIGHT:
						fWKAngle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);					//�L�������m�̊p�x�擾
						fWKData2 = AngleCheck(fBaseAngle, fWKAngle);							//���b�N�p�x�Ƃ̍������擾
						if (fWKData2 > 0 && lock == LOCK_LEFT) { fWKData2 -= D3DX_PI * 2; }	//��Ver�␳
						if (fWKData2 < 0 && lock == LOCK_RIGHT) { fWKData2 += D3DX_PI * 2; }	//�EVer�␳

						if ((lock == LOCK_LEFT ? fWKData < fWKData2 : fWKData > fWKData2))
						{//��/�E�@���Ŕ�r
							fWKData = fWKData2;
							pSceneLock = pScene;
						}
						break;
					}
				}//if(�͈͊m�F)
			}//if(���b�N��Ԃƃ`�[���m�F)
		}//if(�L�����m�F)
		pScene = pScene->GetpNext();
	}

	if (pSceneLock != NULL)
	{
		if (m_pLockChar)
		{//���Ƀ��b�N�L����������
			//�؂�ւ�
			pUI->SetLockOn(CPlayer_UI::LOCK_ON, pSceneLock->Getpos());
		}
		else
		{
			if (lock == LOCK_NO) { pUI->SetLockOn(CPlayer_UI::LOCK_NO, pSceneLock->Getpos()); }
			else { pUI->SetLockOn(CPlayer_UI::LOCK_START, pSceneLock->Getpos()); }
		}
	}
	else if (lock == LOCK_NO) { pUI->GetpLockOn()->BindDrawType(CScene::DRAW_TYPE_NO); }
	return pSceneLock;
}
//=============================================================================
//�L�������b�N������
//=============================================================================
void CCharacter::LockCancel(void)
{
	m_pLockChar = NULL;
	if (GetObjType() == OBJTYPE_PLAYER)
	{
		//��
		((CPlayer*)this)->GetpUI()->GetpLockOn()->BindDrawType(CScene::DRAW_TYPE_NO);
	}
}
//=============================================================================
//���S���A���g�ւ̃��b�N���O��
//=============================================================================
void CCharacter::CancelLock(void)
{
	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_ENEMY || pScene->GetObjType() == OBJTYPE_PLAYER)
		{//�L��������
			if (((CCharacter*)pScene)->m_pLockChar == this)
			{ 
				((CCharacter*)pScene)->LockCancel();
				//if (pScene->GetObjType() == OBJTYPE_PLAYER)
				//{
				//	((CPlayer*)pScene)->LockCancel();
				//}
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//���݂̃��x���ŃX�e�[�^�X�v�Z
//=============================================================================
void CCharacter::SetStatus(void)
{
	m_fMaxLife	= 100.0f;	m_fLife = m_fMaxLife;
	m_fMaxSP	= 500.0f * (((m_nLevel * 2) + 100) * 0.01f);	m_fSP = m_fMaxSP;
	m_fAtk		= 350.0f * (((m_nLevel * 2) + 100) * 0.01f);
	m_fStamina	= m_fMaxStamina;
}
//=============================================================================
// ���݂̃L�[�Ɋp�x�����S�ɍ��킹��
//=============================================================================
void CCharacter::SetRotMotion(void)
{
	int nMaxParts = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxParts();
	CKey *pKey = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetOneMotion()[m_nNumMotion[0]].GetKey()[m_nNumMotion[2]];

	for (int nCntModel = 0; nCntModel < nMaxParts; nCntModel++)
	{//move���v�Z���đ��
		m_pParts[0]->GetBone()[nCntModel].GetaddRot() = pKey->GetpRot()[nCntModel];
	}
}
//=============================================================================
// �t���[���̐i�s���x�ݒ�
//=============================================================================
void CCharacter::SetPlusFrame(float fPFrame, float fCount)
{
	m_fFramePlus2 = fPFrame;
	m_fInitFrame = fCount;
}
//=============================================================================
//	�S�L�����̂����蔻��
//=============================================================================
void CCharacter::CollisionAll(CScene *pChar)	//�L�������m�̂����蔻��
{
	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_ENEMY || pScene->GetObjType() == OBJTYPE_PLAYER)
		{//���b�V������
			if (pChar != pScene)
			{//�����łȂ��Ȃ�
				((CCharacter*)pScene)->Collision(pChar);
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//	�L�������m�̂����蔻��
//=============================================================================
void CCharacter::Collision(CScene *pChar)
{
	CCharacter *PChar = (CCharacter*)pChar;
	D3DXVECTOR3 &length = PChar->Getlength();
	D3DXVECTOR3 &pos = PChar->Getpos();
	D3DXVECTOR3 WKpos = pos;
	bool &bJump = PChar->GetbJump();

	float fDistance, fAngle;

	//�U�����Ȃ�Y����
	if ((m_pos.y > pos.y - length.y && m_pos.y < pos.y + length.y) || 
		PChar->m_nNumMotion[0] >= MOTION_ATTACK)
	{
		//���S�ђʑ΍�


		//�~�`�͈͓��Ȃ�
		fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);
		if (fDistance < powf(length.x + m_length.x, 2))
		{//���g���猩���p�x�ň��l����
			if (PChar->GetnNumMotion(0) >= MOTION_ATTACK) 
			{//�U�����Ȃ�
				WKpos = PChar->Getposold();
				PChar->Getmove().x = 0.0f;
				PChar->Getmove().z = 0.0f;
			}
			fAngle = atan2f(WKpos.x - m_pos.x, WKpos.z - m_pos.z);
			pos = D3DXVECTOR3(m_pos.x, pos.y, m_pos.z) + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * (length.x + m_length.x);
		}
	}
}
//=============================================================================
//	�L�[���̌���
//=============================================================================
void CCharacter::SetEffect(CKey *&pKey)
{
	float fRotPoor;
	CSound *&pSound = CManager::GetSound();

	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		switch (pKey->GetpEffect()[nCount])
		{
		case 0:	if (m_fFrame == 0.0f) { m_rot.y = m_fRot; } break;	//�p�x�����킹��
		case 1:	if (m_fFrame == 0.0f) { m_move.y = 0.0f; }	break;	//�p�x�����킹��
		case 2:	if (!m_bJump)		  { m_move.y = 0.0f; }	break;	//�󒆂Ȃ畂�V
		case 3:	if (m_fFrame == 0.0f) { SetPlusFrame(0.5f, 180.0f); m_fStamina = m_fMaxStamina; pSound->Play(CSound::LABEL_CHARGE000); }	break;	//���[�V�����̉���
		case 4:	if (m_fFrame == 0.0f) { ReSetHitChar(); }	break;	//�q�b�g���̃��Z�b�g
		case 5:	if (m_fFrame == 0.0f) { UseStamina(25.0f); pSound->Play(CSound::LABEL_STEP); }	break;	//�X�e�b�v�ɂ��X�^�~�i����
		case 6:	if (m_fFrame == 0.0f) { UseStamina(20.0f); pSound->Play(CSound::LABEL_STEP); }	break;	//�W�����v�ɂ��X�^�~�i����
		case 7://�u�[�X�g�̎d�l
			pSound->Play(CSound::LABEL_BOOST000);
			UseStamina(0.25f); 
			if ((!m_bBoost || m_fKeepFrame > 80.0f) && m_fKeepFrame > 20.0f) { SetCancelMotion(MOTION_BOOST_END); }

			//���������킹��
			fRotPoor = m_fRot - m_rot.y;
			if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
			else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
			m_rot.y += fRotPoor * 0.025f;
			if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
			if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
			break;	//�W�����v�ɂ��X�^�~�i����
		case 8:
			if(m_fMotionFrame > 200)
			{
				SetCancelMotion(MOTION_RETURN);
			}
		case 10:
			if (m_fFrame == 0.0f)
			{ 
				m_bOrbit = true; 
				CMeshOrbit::Delete();
				CLineEffect::Delete();
				m_bOrbit = false;
			}	break;	//�I�[�r�b�g�폜
		case 11: m_move.y += 0.24f; break;	//�������
		case 20: m_state = STATE_GUARD; break;
		case 21: m_state = STATE_PARIS; break;
		case 22: m_state = STATE_AVOID; break;
		case 23: m_state = STATE_ARMOR; break;
		}
	}
}
//=============================================================================
// �L�����N�^�[�̐ݒ�
//=============================================================================
void CCharacter::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)
{
	m_pos = pos; m_posold = pos;
	m_rot = rot;
	m_fRot = rot.y;

	switch (type)
	{
	case CMotion::TYPE_BOX_Sword:	CCharParts::SetBox_100(this); m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, m_col.a);	break;
	case CMotion::TYPE_BOX_Stick:	CCharParts::SetBox_Stick(this); m_col = D3DXCOLOR(0.75f, 0.75f, 0.75f, m_col.a);	break;
	}

	//���[�V�������҂����ԗp��
	int &nMaxMotion = CMotion::GetMotion(m_pParts[0]->GetMotion())->GetnMaxMotion();
	m_pWaitMotion = new float[nMaxMotion];
	if (m_pWaitMotion != NULL)
	{
		for (int nCount = 0; nCount < nMaxMotion; nCount++) { m_pWaitMotion[nCount] = 0.0f; }
	}
	m_pUseMotion = new bool[nMaxMotion];
	if (m_pUseMotion != NULL)
	{
		ResetAtkNumber();
	}
}
//=============================================================================
// ���_�̐ݒ�
//=============================================================================
void CCharParts::SetVtx(int &nCount)
{
	int nParts = (int)GetModel()[nCount];
	CVtxInfo *&VtxInfo = GetVtxInfo(nParts);
	
	if (VtxInfo != NULL)
	{
		CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(nParts);
		D3DXMATRIX			Drawmtx, WKmtx, WKmtx2, mtxTrans, mtxRot;		//�v�Z�p�}�g���b�N�X
		D3DXVECTOR3 WKpos;
		BYTE *pVtxBuff;
		int nNumVtx = m_pMeshModel[nCount]->GetNumVertices();
		DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y

		sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel[nCount]->GetFVF());
		m_pMeshModel[nCount]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//���_��������
		 //((D3DXVECTOR3*)pVtxBuff)[0] = m_partsAll->pPos[nCntVtx];
			WKpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			if (VtxInfo[nCntVtx].GetnMaxBone() > 0)
			{
				Drawmtx = m_pDrawMtx[nCount][0];
				for (int nCntBone = 0; nCntBone < 1; nCntBone++)
				{
					int nBone = VtxInfo[nCntVtx].GetnBone()[nCntBone];
					float &fWeight = VtxInfo[nCntVtx].GetfWeight()[nCntBone];

					//�`�掞�}�g���b�N�X�ƖڕW�{�[���}�g���b�N�X���w��
					WKmtx = m_pBone[nBone].GetMtx();
					////�����v�Z
					D3DXVECTOR3 pos = m_partsAll->pPos[nCntVtx];

					//�{�[���̃}�g���b�N�X�ƍ��Ōv�Z
					pos = VtxInfo[nCntVtx].Getpos()[nCntBone];

					D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
					D3DXMatrixMultiply(&mtxTrans, &mtxTrans, &WKmtx);
					WKmtx = mtxTrans;
					//�����l�߂�
					WKpos += (D3DXVECTOR3(WKmtx._41, WKmtx._42, WKmtx._43) - WKpos) * (nCntBone == 0 ? 1.0f : fWeight);
				}
				//�`��p�{�[���Ƃ̍�����
				Drawmtx = m_pDrawMtx[nCount][0];
				((D3DXVECTOR3*)pVtxBuff)[0] = WKpos - D3DXVECTOR3(Drawmtx._41, Drawmtx._42, Drawmtx._43);
			}
			pVtxBuff += sizeFvF;
		}
		m_pMeshModel[nCount]->UnlockVertexBuffer();

	}
}
//=============================================================================
// �p�[�c�i�{�[���j�̐ݒ�
//=============================================================================
void CCharParts::SetBone(int nNumber, D3DXMATRIX *pPair, D3DXVECTOR3 pos)
{
	m_pBone[nNumber].GetaddPos() = pos;
	m_pBone[nNumber].GetaddPosMove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBone[nNumber].GetaddRot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBone[nNumber].GetaddRotMove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pBone[nNumber].GetPairMtx() = pPair;
}
//=============================================================================
// �p�[�c�̐ݒ�
//=============================================================================
void CCharParts::Set(int nNumber, D3DXMATRIX *pDraw, PARTS model)
{
	m_pDrawMtx[nNumber] = pDraw;
	GetModel()[nNumber] = model;
	CCharacter::Load(model)->CloneMesh(D3DXMESH_SYSTEMMEM, NULL, CManager::GetRenderer()->GetDevice(), &m_pMeshModel[nNumber]);
}
//=============================================================================
// �{�[���̍쐬
//=============================================================================
void	CCharParts::NewBone(int nMax)
{
	if (m_pBone != NULL)
	{//���������Ă���΍폜
		delete[] m_pBone;
		m_pBone = NULL;
	}

	if (nMax > 0)
	{//1�ȏ㐶���Ȃ�
		m_nMaxBone = nMax;
		m_pBone = new CBone[nMax];
	}
}
//=============================================================================
// ���f���̍쐬
//=============================================================================
void	CCharParts::NewModel(int nMax)
{
	if (m_pModel != NULL)
	{//���������Ă���΍폜
		delete[] m_pModel;
		m_pModel = NULL;
	}
	if (m_pDrawMtx != NULL)
	{//���������Ă���΍폜
		delete[] m_pDrawMtx;
		m_pDrawMtx = NULL;
	}
	if (m_pMeshModel != NULL)
	{
		for (int nCount = 0; nCount < m_nMaxModel; nCount++) { m_pMeshModel[nCount]->Release(); }
		delete m_pMeshModel;
		m_pMeshModel = NULL;
	}
	m_nMaxModel = nMax;
	m_pMeshModel = new LPD3DXMESH[nMax];
	m_pModel = new CCharParts::PARTS[nMax];
	m_pDrawMtx = new D3DXMATRIX*[nMax];
}
//=============================================================================
// �p�[�c�̏I��
//=============================================================================
void CCharParts::Uninit(void)
{
	if (m_pModel != NULL)
	{//���������Ă���΍폜
		delete[] m_pModel;
		m_pModel = NULL;
	}
	if (m_pDrawMtx != NULL)
	{//���������Ă���΍폜
		delete[] m_pDrawMtx;
		m_pDrawMtx = NULL;
	}
	if (m_pMeshModel != NULL)
	{
		for (int nCount = 0; nCount < m_nMaxModel; nCount++) { m_pMeshModel[nCount]->Release(); }
		delete m_pMeshModel;
		m_pMeshModel = NULL;
	}
}
//=============================================================================
// �p�[�c�̐ݒ�
//=============================================================================
void CCharParts::Draw(CCharacter *pChar)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX			WKmtx, mtxRot, mtxTrans;		//�v�Z�p�}�g���b�N�X
	CScene::DRAW_TYPE DType = pChar->GetDrawType();
	int nCount;
	bool bTex = true;
	if (pChar->GetnInvincible() > 0) { DType = CScene::DRAW_TYPE_AER; }

	//�{�[���̌v�Z
	if (!pChar->GetbVtx())
	{//���_�ݒ�����Ă��Ȃ�
		for (nCount = 0; nCount < m_nMaxBone; nCount++)
		{//�{�[���̌v�Z
			D3DXMATRIX &mtx = m_pBone[nCount].GetMtx();
			D3DXVECTOR3 &addRot = m_pBone[nCount].GetaddRot();
			D3DXVECTOR3 &addPos = m_pBone[nCount].GetaddPos();
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtx);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, addRot.y, addRot.x, addRot.z);
			D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, addPos.x, addPos.y, addPos.z);
			D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

			//�e�{�[���Ɗ|�����킹
			if (m_pBone[nCount].GetPairMtx() != NULL)
			{//�e�̈ʒu�Ɗp�x���v���X
				D3DXMatrixMultiply(&mtx, &mtx, m_pBone[nCount].GetPairMtx());
			}
		}
	}
	//���f���̕`��
	for (nCount = 0; nCount < m_nMaxModel; nCount++)
	{//���f���̕`��
		WKmtx = m_pDrawMtx[nCount][0];
		CVtxInfo *&VtxInfo = GetVtxInfo(m_pModel[nCount]);

		if (VtxInfo != NULL)
		{//���_��񂪂���Ȃ�
			D3DXMATRIX &DMtx = m_pDrawMtx[nCount][0];
			D3DXMatrixIdentity(&WKmtx);
			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, DMtx._41, DMtx._42, DMtx._43);
			D3DXMatrixMultiply(&WKmtx, &WKmtx, &mtxTrans);
		}
		//���_�̐ݒ�
		if (!pChar->GetbVtx()) { SetVtx(nCount); }

		//���[���h�}�g���b�N�X�ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &WKmtx);

		//�`��
		if (pChar->GetnInvincible() > 0) { pDevice->SetRenderState(D3DRS_LIGHTING, FALSE); bTex = false; }
		CScene::DrawPrepare(DType, pDevice);
		DrawModel(pChar, nCount, bTex);

		CSceneModel::SetShadow();
		CScene::DrawPrepare(CScene::DRAW_TYPE_SUBTRACT, pDevice);
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		DrawModel(pChar, nCount, false);
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
}
//=============================================================================
// ���f���̕`��
//=============================================================================
void CCharParts::DrawModel(CCharacter *pChar, int &nCount, bool bTex)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATERIAL		*pMat;					//�}�e���A���f�[�^�ւ̃|�C���^
	D3DMATERIAL9		matDef;					//���݂̃}�e���A���ۑ��p
	CCharParts::PARTS &Parts = GetModel()[nCount];
	CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(Parts);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	pMat = (D3DXMATERIAL*)m_partsAll->pBuffMatModel->GetBufferPointer();

	//�e�N�X�`���̐ݒ�
	if (bTex)
	{//�摜�𒣂��Ă����Ȃ�
		if (m_partsAll->tex != CScene::TEX_MAX)
		{//�摜���w�肵�Ă��邩�m�F
			if (CScene::GetTexture(m_partsAll->tex) != NULL)
			{//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, CScene::GetTexture(m_partsAll->tex));
			}//�e�N�X�`���폜
		}
		else if (Parts == CCharParts::BOX_100)
		{
			switch (m_pChar->GetType())
			{
			case CMotion::TYPE_BOX_Sword: pDevice->SetTexture(0, CScene::Load(CScene::TEX_TAKASHI)); break;
			case CMotion::TYPE_BOX_Stick: pDevice->SetTexture(0, CScene::Load(CScene::TEX_BSword)); break;

			}
		}
	}
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	for (int nCountData = 0; nCountData < (int)m_partsAll->nNumMatModel; nCountData++)
	{
		// �}�e���A���̐ݒ�
		pMat = (D3DXMATERIAL*)m_partsAll->pBuffMatModel->GetBufferPointer();
		if (Cloak_000 > Parts) { pMat[nCountData].MatD3D.Diffuse = pChar->GetCollar(); } //�����x�ݒ�
		pMat[nCountData].MatD3D.Diffuse.a = pChar->GetCollar().a;
		pDevice->SetMaterial(&pMat[nCountData].MatD3D);

		// ���f��(�p�[�c)�̕`��
		m_pMeshModel[nCount]->DrawSubset(nCountData);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
	pDevice->SetTexture(0, NULL);
}
//=============================================================================
// �L�����N�^�[�̐ݒ�
//=============================================================================
void CCharParts::SetBox_Sword(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;

	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;
		//Parts[1] = new CClothing;
		//((CClothing*)Parts[1])->Set(pChar);
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Sword;
	//Parts[1]->m_Motion = CMotion::TYPE_MAX;

	//����
	Parts[0]->LoadChar(0, "data/TEXT/Bone/Bone_Rig.txt");
	//Parts[0]->NewBone(21);
	Parts[0]->NewModel(20);
	//Parts[1]->NewBone(0);
	//Parts[1]->NewModel(1);

	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), BRIG_hip);
	Parts[0]->Set(1, &Parts[0]->GetBone()[1].GetMtx(), BRIG_hara);
	Parts[0]->Set(2, &Parts[0]->GetBone()[2].GetMtx(), BRIG_mune);
	Parts[0]->Set(3, &Parts[0]->GetBone()[3].GetMtx(), BRIG_head);
	Parts[0]->Set(4, &Parts[0]->GetBone()[4].GetMtx(), BRIG_armUR);
	Parts[0]->Set(5, &Parts[0]->GetBone()[5].GetMtx(), BRIG_armD);
	Parts[0]->Set(6, &Parts[0]->GetBone()[6].GetMtx(), BRIG_hand);
	Parts[0]->Set(7, &Parts[0]->GetBone()[7].GetMtx(), BRIG_handR2);
	Parts[0]->Set(8, &Parts[0]->GetBone()[8].GetMtx(), BRIG_handR3);
	Parts[0]->Set(9, &Parts[0]->GetBone()[9].GetMtx(), BRIG_armUL);
	Parts[0]->Set(10, &Parts[0]->GetBone()[10].GetMtx(), BRIG_armD);
	Parts[0]->Set(11, &Parts[0]->GetBone()[11].GetMtx(), BRIG_hand);
	Parts[0]->Set(12, &Parts[0]->GetBone()[12].GetMtx(), BRIG_handL2);
	Parts[0]->Set(13, &Parts[0]->GetBone()[13].GetMtx(), BRIG_handL3);
	Parts[0]->Set(14, &Parts[0]->GetBone()[14].GetMtx(), BRIG_legUR);
	Parts[0]->Set(15, &Parts[0]->GetBone()[15].GetMtx(), BRIG_legD);
	Parts[0]->Set(16, &Parts[0]->GetBone()[16].GetMtx(), BRIG_foot);
	Parts[0]->Set(17, &Parts[0]->GetBone()[17].GetMtx(), BRIG_legUL);
	Parts[0]->Set(18, &Parts[0]->GetBone()[18].GetMtx(), BRIG_legD);
	Parts[0]->Set(19, &Parts[0]->GetBone()[19].GetMtx(), BRIG_foot);
	//Parts[0]->Set(20, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Sword0);
	//Parts[0]->Set(21, &Parts[0]->GetBone()[2].GetMtx(), &Parts[0]->GetBone()[2].GetMtx(), Cloak_000);

	//Parts[1]->GetDrawMtx()[0] = &Parts[0]->GetBone()[3].GetMtx();
	//Parts[1]->GetModel()[0] = Cloak_000;
	//CCharacter::Load(Cloak_000)->CloneMesh(D3DXMESH_SYSTEMMEM, NULL,CManager::GetRenderer()->GetDevice(), &Parts[1]->m_pMeshModel[0]);
}
//=============================================================================
// �L�����N�^�[�̐ݒ� ���_
//=============================================================================
void CCharParts::SetBox_Stick(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;
	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Stick;
	pChar->GetpParts()[0]->LoadChar(0, "data/TEXT/Bone/Bone_Box100.txt");

	//Parts[0]->GetBone()[0].GetPairMtx() = &pChar->GetMtx();

	Parts[0]->NewModel(2);
	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), BOX_100);
	Parts[0]->Set(1, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Stick);
}
//=============================================================================
// �L�����N�^�[�̐ݒ� �e�X�g�^�X�L�����b�V����Y
//=============================================================================
void CCharParts::SetTEST_000(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;
	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Sword;
	pChar->GetpParts()[0]->LoadChar(0, "data/TEXT/Bone/Bone_Box.txt");

	//Parts[0]->GetBone()[0].GetPairMtx() = &pChar->GetMtx();

	Parts[0]->NewModel(2);

	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), TEST_000);
	Parts[0]->Set(1, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Sword0);
}
//=============================================================================
// �L�����N�^�[�̐ݒ� ���^�X�L�����b�V��
//=============================================================================
void CCharParts::SetBox_100(CCharacter *pChar)
{
	int &nMaxParts = pChar->GetnMaxParts();
	CCharParts **&Parts = pChar->GetpParts();

	nMaxParts = 1;
	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		Parts[0] = new CCharParts;

		//Parts[1] = new CClothing;
		//((CClothing*)Parts[1])->Set(pChar);
		//Parts[1]->m_Motion = CMotion::TYPE_MAX;
	}
	for (int nCount = 0; nCount < nMaxParts; nCount++) { Parts[nCount]->GetpChar() = pChar; }
	Parts[0]->m_Motion = CMotion::TYPE_BOX_Sword;
	pChar->GetpParts()[0]->LoadChar(0, "data/TEXT/Bone/Bone_Box100.txt");

	//Parts[0]->GetBone()[0].GetPairMtx() = &pChar->GetMtx();

	Parts[0]->NewModel(1);
	Parts[0]->Set(0, &Parts[0]->GetBone()[0].GetMtx(), BOX_100);
	//Parts[0]->Set(1, &Parts[0]->GetBone()[20].GetMtx(), BRIG_Sword0);
	//Parts[0]->Set(2, &Parts[0]->GetBone()[3].GetMtx(), Face_000);

	//Parts[1]->NewModel(1);
	//Parts[1]->Set(0, &Parts[0]->GetBone()[3].GetMtx(), Cloak_000);
}
//=============================================================================
// ���_�̃��[�h
//=============================================================================
void CCharParts::LoadVtx(int nNumber, char *aStr)
{
	if (m_pVtxInfo[nNumber] != NULL) { return; }

	CCharacter::MODEL_PARTS *m_partsAll = CCharacter::GetpartsAll(nNumber);
	int nNumVtx, nWk;
	FILE *pFile;
	pFile = fopen(&aStr[0], "r");

	if (pFile != NULL)//Load
	{//����
	 //���_���E�_
		fscanf(pFile, "%d\n", &nNumVtx);
		m_pVtxInfo[nNumber] = new CVtxInfo[nNumVtx + 1];
		for (int nVtx = 0; nVtx <= nNumVtx; nVtx++)
		{
			fscanf(pFile, "%d", &m_pVtxInfo[nNumber][nVtx].GetnMaxBone());
			m_pVtxInfo[nNumber][nVtx].GetnBone() = new int[32];
			m_pVtxInfo[nNumber][nVtx].GetfWeight() = new float[32];
			m_pVtxInfo[nNumber][nVtx].Getpos() = new D3DXVECTOR3[32];

			nWk = m_pVtxInfo[nNumber][nVtx].GetnMaxBone();
			for (int nCount = 0; nCount < m_pVtxInfo[nNumber][nVtx].GetnMaxBone(); nCount++)
			{
				D3DXVECTOR3 &pos = m_pVtxInfo[nNumber][nVtx].Getpos()[nCount];
				fscanf(pFile, "%d ", &m_pVtxInfo[nNumber][nVtx].GetnBone()[nCount]);
				fscanf(pFile, "%f ", &m_pVtxInfo[nNumber][nVtx].GetfWeight()[nCount]);
				fscanf(pFile, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// �{�[���̃��[�h
//=============================================================================
void CCharParts::LoadChar(int nNumber, char *aStr)
{
	FILE *pFile;
	int &nMaxParts = m_pChar->GetnMaxParts();
	CCharParts **&Parts = m_pChar->GetpParts();
	CCharParts *&parts = m_pChar->GetpParts()[nNumber];

	int			nData;
	D3DXVECTOR3 pos;
	D3DXMATRIX  *mtx;

	pFile = fopen(&aStr[0], "r");

	if (pFile != NULL)//Load
	{//����
		fscanf(pFile, "%d\n", &parts->GetnMaxBone());//�{�[���̐��A���f���̐�
		Parts[0]->NewBone(parts->GetnMaxBone());
		for (int nCount = 0; nCount < parts->GetnMaxBone(); nCount++)
		{
			D3DXVECTOR3 &rot = parts->GetBone()[nCount].GetaddRot();

			fscanf(pFile, "%f %f %f\n", &pos.x, &pos.y, &pos.z);//�{�[���̐��A���f���̐�
			fscanf(pFile, "%d\n", &nData);			//�{�[���̐e�ԍ�

			if (nData == -1) { mtx = &m_pChar->GetMtx(); }
			else { mtx = &parts->GetBone()[nData].GetMtx(); }
			parts->SetBone(nCount, mtx, pos);
		}
		fclose(pFile);
	}
}
