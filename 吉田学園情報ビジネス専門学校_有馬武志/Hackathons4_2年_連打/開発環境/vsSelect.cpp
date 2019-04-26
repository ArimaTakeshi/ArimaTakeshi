//=============================================================================
//
// �^�C�g������ [Title.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include <stdio.h>				//�Z�[�u���[�h�̈�
#include"Scene.h"
#include"ScenePlayer.h"
#include "SceneAnim3D.h"
#include "Font.h"
#include "manager.h"
#include "sound.h"
#include "vsSelect.h"
#include "camera.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TYPE		(8)
#define VsSelect_Tank_Interval	(15.0f)
#define VsSelect_Interval	(50.0f)
#define VsSelect_InfoY		(SCREEN_HEIGHT / 2 - 50.0f)

//=============================================================================
// VS�Z���N�gUI�̃Z�b�g����
//=============================================================================
void CvsSelectUI::Set(int &nID, CvsSelect *pvsSelect)
{
	int nWKData = 0;
	float fPos = nID * (SCREEN_WIDTH * 0.5f);
	m_nCost = 0;

	if (SceneCreate(m_pCost, UI_PRIORITY - 2))
	{//�R�X�g�̕\�L
		m_pCost->Set(RECT{ 0, 10, nID * (SCREEN_WIDTH / 2) + SCREEN_WIDTH / 2 - 100 , SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "COST : 0 / 100", 1, DT_RIGHT, -1, true, CFont::STATE_NONE);
	}

	for (int nCount = 0; nCount < MAX_VS_CFont; nCount++)
	{//�X�e�[�^�X���Ƃ̃R�X�g�\�L
		if (nCount > 2) { nWKData = 1; }
		if (SceneCreate(m_pCostS[nCount], UI_PRIORITY - 2))
		{//�R�X�g�̕\�L
			m_pCostS[nCount]->Set(RECT{ 0, (int)(VsSelect_InfoY + VsSelect_Interval * (nCount + nWKData)) - 20, nID * (SCREEN_WIDTH / 2) + SCREEN_WIDTH / 2 - 120 , SCREEN_HEIGHT }, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), "", 1, DT_RIGHT, -1, true, CFont::STATE_NONE);
		}
	}

	if (Create(m_p2DComLevel))
	{//COMLevel
		m_p2DComLevel->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 8, 50.0f, 0.0f), 50.0f, 50.0f, D3DX_PI, nID, 2, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_PIcon);
	}
	if (SceneCreate(m_pTank, MODEL_PRIORITY))
	{//���
		m_pTank->Set(D3DXVECTOR3(-VsSelect_Tank_Interval * 0.5f - nID * VsSelect_Tank_Interval + VsSelect_Tank_Interval, 4.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			CSceneModel::MODEL_TANKD, CSceneModel::MODEL_TANKU, CSceneModel::TEX_PTN_01, CSceneModel::TEX_PTN_01, CScene::DRAW_TYPE_NORMAL);
	}
	for (int nCount = 0; nCount < MAX_VS_WEAPON; nCount++)
	{
		if (Create(m_p2DTank[nCount]))
		{//��ԑ���
			m_p2DTank[nCount]->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4, VsSelect_InfoY + VsSelect_Interval * nCount, 0.0f), 150.0f, VsSelect_Interval * 0.45f, D3DX_PI, 0, 1, MAX_TYPE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_Type);
		}
	}
	if (Create(m_pItem))
	{//�A�C�e��
		m_pItem->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4 + 100.0f, VsSelect_InfoY + VsSelect_Interval * 2, 0.0f), VsSelect_Interval * 0.45f, VsSelect_Interval * 0.45f, D3DX_PI, 13, 5, 4, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEXTURE_MAX);
		m_pItem->BindTexture(CScene3D::Load(CScene3D::TEX_ITEM));
		m_pItem->BindDrawType(CScene::DRAW_TYPE_NO);
	}
	if (Create(m_p2DColBullet))
	{//�e�̐F
		m_p2DColBullet->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4 + 180.0f, VsSelect_InfoY + VsSelect_Interval * 3, 0.0f), VsSelect_Interval * 0.45f, VsSelect_Interval * 0.45f, D3DX_PI, 50 + nID * 10, 16, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEXTURE_MAX);
		m_p2DColBullet->BindTexture(CSceneBullet::Load(CSceneBullet::TEX_BULLET));
	}

	float *pfGage[MAX_VS_GAGE] = { &pvsSelect->GetfLife(nID), &pvsSelect->GetfDef(nID), &pvsSelect->GetfAtk(nID) };
	for (int nCount = 0; nCount < MAX_VS_GAGE; nCount++)
	{
		if (Create(m_pGage[nCount]))
		{//�Q�[�W
			m_pGage[nCount]->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4 - 100.0f, VsSelect_InfoY + VsSelect_Interval * (4 + nCount), 0.0f), 250.0f, VsSelect_Interval * 0.45f, pfGage[nCount], &pvsSelect->GetfMaxGage(), true, C2DGage::STATE_STATUS);
		}
		if (Create(m_p2DGage[nCount]))
		{//�A�C�R��
			m_p2DGage[nCount]->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4 - 150.0f, VsSelect_InfoY + VsSelect_Interval * (4 + nCount), 0.0f), VsSelect_Interval * 0.45f, VsSelect_Interval * 0.45f, D3DX_PI, nCount, 3, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_UI001);
		}
	}
	if (Create(m_p2DReady))
	{//����
		m_p2DReady->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 5 - 5.0f, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), C2D::TEXTURE_MAX);
		m_p2DReady->BindDrawType(CScene::DRAW_TYPE_NO);
	}
	if (Create(m_p2DReadyLogo))
	{//����
		m_p2DReadyLogo->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4, VsSelect_InfoY + VsSelect_Interval * 7 + 15.0f, 0.0f), 200.0f, VsSelect_Interval * 0.45f, D3DX_PI, 2, 1, 6, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEXTURE_MAX);
		m_p2DReadyLogo->BindTexture(CScene2D::Load(CScene2D::TEXTURE_LogoVersus));
	}
	if (Create(m_p2DSelect))
	{//�I��g
		m_p2DSelect->Set(D3DXVECTOR3(fPos + SCREEN_WIDTH / 4, VsSelect_InfoY, 0.0f), SCREEN_WIDTH / 5 - 5.0f, VsSelect_Interval * 0.5f, D3DX_PI, 0, 1, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEX_VsSelect);
	}
}
//=============================================================================
// VS�Z���N�gUI �����l�ݒ菈��
//=============================================================================
void CvsSelectUI::SetSelect(CvsSelect *pvsSelect, int &nID)
{
	m_pTank->BindTexture(CSceneModel::Load(pvsSelect->GetTex(nID, 0)));
	m_p2DTank[0]->SetUV((int)pvsSelect->GetTex(nID, 0) - (int)CSceneModel::TEX_PTN_01, 1, 8);

	m_pTank->GetTextureU() = (CSceneModel::Load(pvsSelect->GetTex(nID, 1)));
	m_pTank->GetpEffectU()->SetUV(pvsSelect->GetTex(nID, 1) - (int)CSceneModel::TEX_PTN_01, 8, 1);
	m_p2DTank[1]->SetUV((int)pvsSelect->GetTex(nID, 1) - (int)CSceneModel::TEX_PTN_01, 1, 8);

	m_pItem->SetUV(pvsSelect->GetItem(nID) + 13, 5, 4);
	if (pvsSelect->GetItem(nID) == ITEM::TYPE_MAX) { m_pItem->BindDrawType(CScene::DRAW_TYPE_NO); }
	else { m_pItem->BindDrawType(CScene::DRAW_TYPE_NORMAL); }

	m_p2DColBullet->SetUV(48 + pvsSelect->GetnUV(nID) * 2, 16, 10);
}
//=============================================================================
// VS�Z���N�gUI �I������
//=============================================================================
void CvsSelectUI::Select(SELECT &select, bool bChange, CvsSelect *pvsSelect, int &nID)
{
	if (select != SELECT_READY)
	{
		switch (select)
		{
		case SELECT_TANK0:
			if (bChange) { pvsSelect->GetTex(nID, 0) = (CSceneModel::TEXTURE)(((int)pvsSelect->GetTex(nID, 0) - (int)CSceneModel::TEX_PTN_01 + 1) % 8 + (int)CSceneModel::TEX_PTN_01); }
			else { pvsSelect->GetTex(nID, 0) = (CSceneModel::TEXTURE)(((int)pvsSelect->GetTex(nID, 0) - (int)CSceneModel::TEX_PTN_01 + 7) % 8 + (int)CSceneModel::TEX_PTN_01); }
			m_pTank->BindTexture(CSceneModel::Load(pvsSelect->GetTex(nID, 0)));
			m_p2DTank[0]->SetUV((int)pvsSelect->GetTex(nID, 0) - (int)CSceneModel::TEX_PTN_01, 1, 8);
			SpinTank(bChange);
			break;
		case SELECT_TANK1:
			if (bChange) { pvsSelect->GetTex(nID, 1) = (CSceneModel::TEXTURE)(((int)pvsSelect->GetTex(nID, 1) - (int)CSceneModel::TEX_PTN_01 + 1) % 8 + (int)CSceneModel::TEX_PTN_01); }
			else { pvsSelect->GetTex(nID, 1) = (CSceneModel::TEXTURE)(((int)pvsSelect->GetTex(nID, 1) - (int)CSceneModel::TEX_PTN_01 + 7) % 8 + (int)CSceneModel::TEX_PTN_01); }
			m_pTank->GetTextureU() = (CSceneModel::Load(pvsSelect->GetTex(nID, 1)));
			m_pTank->GetpEffectU()->SetUV(pvsSelect->GetTex(nID, 1) - (int)CSceneModel::TEX_PTN_01, 8, 1);
			m_p2DTank[1]->SetUV((int)pvsSelect->GetTex(nID, 1) - (int)CSceneModel::TEX_PTN_01, 1, 8);
			SpinTank(bChange);
			break;
		case SELECT_ITEM:
			if (bChange) { pvsSelect->GetItem(nID) = (ITEM::TYPE)(((int)pvsSelect->GetItem(nID) + 1) % ((int)ITEM::TYPE_MAX + 1)); }
			else { pvsSelect->GetItem(nID) = (ITEM::TYPE)(((int)pvsSelect->GetItem(nID) + (int)ITEM::TYPE_MAX) % ((int)ITEM::TYPE_MAX + 1)); }
			m_pItem->SetUV(pvsSelect->GetItem(nID) + 13, 5, 4);
			if (pvsSelect->GetItem(nID) == ITEM::TYPE_MAX) { m_pItem->BindDrawType(CScene::DRAW_TYPE_NO); }
			else { m_pItem->BindDrawType(CScene::DRAW_TYPE_NORMAL); }
			break;
		case SELECT_BULLET:
			while (1)
			{//	�F�����Ԃ��Ă���΃��[�v
				if (bChange) { pvsSelect->GetnUV(nID) = (pvsSelect->GetnUV(nID) + 1) % 8; }
				else { pvsSelect->GetnUV(nID) = (pvsSelect->GetnUV(nID) + 7) % 8; }
				if (pvsSelect->GetnUV(nID ^ 1) != pvsSelect->GetnUV(nID)) { break; }
			}
			m_p2DColBullet->SetUV(48 + pvsSelect->GetnUV(nID) * 2, 16, 10);
			break;
		case SELECT_LIFE:
			if (bChange) { if (pvsSelect->GetfLife(nID) < 50.0f) { pvsSelect->GetfLife(nID) += 1.0f; } else { return; } }
			else { if (pvsSelect->GetfLife(nID) > 0.0f) { pvsSelect->GetfLife(nID) -= 1.0f; } else { return; } }
			break;
		case SELECT_DEF:
			if (bChange) { if (pvsSelect->GetfDef(nID) < 50.0f) { pvsSelect->GetfDef(nID) += 1.0f; } else { return; } }
			else { if (pvsSelect->GetfDef(nID) > 0.0f) { pvsSelect->GetfDef(nID) -= 1.0f; } else { return; } }
			break;
		case SELECT_ATK:
			if (bChange) { if (pvsSelect->GetfAtk(nID) < 50.0f) { pvsSelect->GetfAtk(nID) += 1.0f; } else { return; } }
			else { if (pvsSelect->GetfAtk(nID) > 0.0f) { pvsSelect->GetfAtk(nID) -= 1.0f; } else { return; } }
			break;
		}

	}
}
//=============================================================================
// VS�Z���N�gUI �J�[�\���擾�̏���
//=============================================================================
void CvsSelectUI::Cursor(SELECT &select)
{

	float fPosY;
	switch (select)
	{
	case SELECT_TANK0:	fPosY = m_p2DTank[0]->GetPosition().y;	break;
	case SELECT_TANK1:	fPosY = m_p2DTank[1]->GetPosition().y;	break;
	case SELECT_ITEM:	fPosY = m_pItem->GetPosition().y;		break;
	case SELECT_BULLET:	fPosY = m_p2DColBullet->GetPosition().y;	break;
	case SELECT_LIFE:	fPosY = m_p2DGage[0]->GetPosition().y;	break;
	case SELECT_DEF:	fPosY = m_p2DGage[1]->GetPosition().y;	break;
	case SELECT_ATK:	fPosY = m_p2DGage[2]->GetPosition().y;	break;
	case SELECT_READY:	fPosY = m_p2DReadyLogo->GetPosition().y;	break;
	}
	m_p2DSelect->GetPosition().y = fPosY;
	m_p2DSelect->SetPosition(D3DX_PI);
}
//=============================================================================
// VS�Z���N�gUI //�R�X�g���I�[�o�[���Ă��邩����
//=============================================================================
bool CvsSelectUI::OverCost(CvsSelect *pvsSelect, int &nID)
{
	bool bOver = true;
	int	 nValue = 0;
	char aStr[64];

	nValue = SumCost(pvsSelect, nID);
	if (nValue > 100)
	{//�I�[�o�[�\�L�ɕύX
		m_p2DReadyLogo->SetUV(4, 1, 6);
		bOver = false;
		FontOver(D3DXCOLOR(1.0f, 0.1f, 0.02f, 1.0f));
	}
	else
	{//�ʏ�\�L�ɕύX
		m_p2DReadyLogo->SetUV(2, 1, 6);
		FontOver(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	wsprintf(&aStr[0], "COST : %d / 100", nValue);
	m_pCost->SetFont(&aStr[0], -1);

	return bOver;
}
//=============================================================================
// VS�Z���N�gUI //�R�X�g�̍��v�l��Ԃ�
//=============================================================================
int CvsSelectUI::SumCost(CvsSelect *pvsSelect, int &nID)
{
	int nWKData;
	int nFont = 0;
	int nSumCost = 0;
	char aStr[64];

	for (int nCount = 0; nCount < SELECT_READY; nCount++)
	{
		nWKData = GetCost((CvsSelectUI::SELECT)nCount, pvsSelect, nID);
		if (nWKData >= 0)
		{//�R�X�g�̍X�V
			nSumCost += nWKData;
			wsprintf(&aStr[0], "%d", nWKData);
			m_pCostS[nFont]->SetFont(&aStr[0],-1);
			nFont++;
		}

	}
	return nSumCost;
}
//=============================================================================
// VS�Z���N�gUI //�w�肳�ꂽ�R�X�g��Ԃ��@�����ɕ\�L�̍X�V
//=============================================================================
int CvsSelectUI::GetCost(SELECT select, CvsSelect *pvsSelect, int &nID)
{
	switch (select)
	{
	case SELECT_TANK0:	
		switch (pvsSelect->GetTex(nID, 0))
		{
		case CSceneModel::TEX_PTN_01: return 0;
		case CSceneModel::TEX_PTN_02: return 0;
		case CSceneModel::TEX_PTN_03: return 0;
		case CSceneModel::TEX_PTN_04: return 0;
		case CSceneModel::TEX_PTN_05: return 0;
		case CSceneModel::TEX_PTN_06: return 0;
		case CSceneModel::TEX_PTN_07: return 5;
		case CSceneModel::TEX_PTN_08: return 5;
		}
	case SELECT_TANK1:	
		switch (pvsSelect->GetTex(nID, 1))
		{
		case CSceneModel::TEX_PTN_01: return 0;
		case CSceneModel::TEX_PTN_02: return 15;
		case CSceneModel::TEX_PTN_03: return 30;
		case CSceneModel::TEX_PTN_04: return 20;
		case CSceneModel::TEX_PTN_05: return 15;
		case CSceneModel::TEX_PTN_06: return 30;
		case CSceneModel::TEX_PTN_07: return 40;
		case CSceneModel::TEX_PTN_08: return 40;
		}
	case SELECT_ITEM:	
		switch (pvsSelect->GetItem(nID))
		{
		case ITEM::TYPE_SPDUP:		return 8;
		case ITEM::TYPE_PAIR0:		return 15;
		case ITEM::TYPE_NORIVER:	return 25;
		case ITEM::TYPE_NOSTOP:		return 20;
		case ITEM::TYPE_CHARGEUP:	return 70;
		case ITEM::TYPE_SCOREUP:	return 100;
		case ITEM::TYPE_PAIR1:		return 50;
		case ITEM::TYPE_MAX:		return 0;
		}
	case SELECT_LIFE:	return (int)pvsSelect->GetfLife(nID);
	case SELECT_ATK:	return (int)pvsSelect->GetfAtk(nID);
	case SELECT_DEF:	return (int)pvsSelect->GetfDef(nID);
	}

	return -1;
}
//=============================================================================
// VS�Z���N�gUI �R�X�g���I�[�o�[���Ă���Ε����Ԃ�
//=============================================================================
void CvsSelectUI::FontOver(D3DXCOLOR col)
{
	m_pCost->GetCollar() = col;
	//for (int nCount = 0; nCount < MAX_VS_CFont; nCount++)
	//{
	//	m_pCostS[nCount]->GetCollar() = col;
	//}
}
//=============================================================================
// VS�Z���N�gUI ��������
//=============================================================================
void CvsSelectUI::Ready(bool bReady)
{
	if (bReady)
	{
		m_p2DReady->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_p2DReadyLogo->SetUV(3, 1, 6);
	}
	else
	{
		m_p2DReady->BindDrawType(CScene::DRAW_TYPE_NO);
		m_p2DReadyLogo->SetUV(2, 1, 6);
	}
}
//=============================================================================
// VS�Z���N�gUI ��ԉ�]����
//=============================================================================
void CvsSelectUI::SpinTank(bool bSpin)
{
	m_pTank->GetRotation()[0].y = D3DX_PI * (bSpin ? 2.0f : -2.0f);
	m_pTank->GetRotationU()[0].y = D3DX_PI * (bSpin ? 2.0f : -2.0f);
	CSceneAnim3D *pSceneAnim3D;
	if (SceneCreate(pSceneAnim3D, SAnim3D_PRIORITY))
	{
		pSceneAnim3D->Set(m_pTank->GetPosition()[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 10.0f, 10.0f, CSceneAnim3D::TEX_WEAPON, CScene::DRAW_TYPE_ADD, 0, 5, 2, 6, CSceneAnim3D::ANIMATION_LOOP, CSceneAnim3D::STATE_FADE);
	}
}
//=============================================================================
// VS�Z���N�gUI �I������
//=============================================================================
void CvsSelectUI::Uninit(void)
{
	m_p2DSelect->Uninit();
	m_p2DComLevel->Uninit();
	m_pItem->Uninit();
	m_p2DColBullet->Uninit();
	m_p2DReady->Uninit();
	m_p2DReadyLogo->Uninit();
	for (int nCount = 0; nCount < MAX_VS_WEAPON; nCount++)
	{
		m_p2DTank[nCount]->Uninit();
	}
	for (int nCount = 0; nCount < MAX_VS_GAGE; nCount++)
	{
		m_pGage[nCount]->Uninit();
		m_p2DGage[nCount]->Uninit();
	}
}
//=============================================================================
// VS�Z���N�gUI �X�V����
//=============================================================================
void CvsSelectUI::Update(void)
{
	for (int nCount = 0; nCount < MAX_VS_GAGE; nCount++)
	{
		if (m_pGage[nCount] != NULL) { m_pGage[nCount]->Update(); }
	}
	if (m_pTank != NULL)
	{
		m_pTank->GetpEfect()->BindDrawType(CScene::DRAW_TYPE_NO);
		m_pTank->GetRotation()[0].y *= 0.9f;
		m_pTank->GetRotationU()[0].y *= 0.9f;
		m_pTank->EffectUpdate();
	}
}
//=============================================================================
// VS�Z���N�gUI �`�揈��
//=============================================================================
void CvsSelectUI::Draw(void)
{
	m_p2DComLevel->Draw();
	m_pItem->Draw();
	m_p2DColBullet->Draw();
	for (int nCount = 0; nCount < MAX_VS_WEAPON; nCount++)
	{
		m_p2DTank[nCount]->Draw();
	}
	for (int nCount = 0; nCount < MAX_VS_GAGE; nCount++)
	{
		m_pGage[nCount]->Draw();
		m_p2DGage[nCount]->Draw();
	}
	m_p2DSelect->Draw();
	m_p2DReady->Draw();
	m_p2DReadyLogo->Draw();
}

//=============================================================================
// VS�Z���N�g�X�e�[�W �ݒ菈��
//=============================================================================
void CvsSelectStage::Set(void)
{
	if (Create(m_pReady[0]))
	{//Ready�g�̐���
		m_pReady[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH * 2, SCREEN_HEIGHT / 6, D3DX_PI, 0, 1, 1, 0.0f, C2DPolygon::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2DPolygon::TEXTURE_MAX);
		m_pReady[0]->BindTexture(CScene2D::Load(CScene2D::TEX_UIWindow));
		m_pReady[0]->BindDrawType(CScene::DRAW_TYPE_NO);
	}
	if (Create(m_pReady[1]))
	{//Ready�̐���
		m_pReady[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 7, D3DX_PI, 2, 1, 6, 0.0f, C2DPolygon::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2DPolygon::TEXTURE_MAX);
		m_pReady[1]->BindTexture(CScene2D::Load(CScene2D::TEXTURE_LogoVersus));
		m_pReady[1]->BindDrawType(CScene::DRAW_TYPE_NO);
	}

	for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++)
	{
		if (Create(m_pStage[nCount]))
		{//Stage�̐���
			m_pStage[nCount]->Set(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SCREEN_WIDTH * 0.25f + (SCREEN_WIDTH * 0.25f) * nCount, SCREEN_HEIGHT / 2, 0.0f), SCREEN_HEIGHT / 6, SCREEN_HEIGHT / 9, D3DX_PI, nCount, 1, MAX_VS_STAGE, 100.0f, C2DPolygon::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2DPolygon::TEX_Stage);
			m_pStage[nCount]->BindDrawType(CScene::DRAW_TYPE_NO);
		}
	}

	if (Create(m_pStageLogo))
	{//Stage�̐���
		m_pStageLogo->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 120.0f, 0.0f), SCREEN_WIDTH / 6, SCREEN_HEIGHT / 15, D3DX_PI, 5, 1, 6, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), C2D::TEXTURE_MAX);
		m_pStageLogo->BindTexture(CScene2D::Load(CScene2D::TEXTURE_LogoVersus));
		m_pStageLogo->BindDrawType(CScene::DRAW_TYPE_NO);
	}
}
//=============================================================================
// VS�Z���N�g�X�e�[�W �������������ύX
//=============================================================================
void CvsSelectStage::ChangeReady(bool bDraw)
{
	if (bDraw)
	{
		m_pReady[0]->BindDrawType(CScene::DRAW_TYPE_MULTIPLY);
		m_pReady[1]->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}
	else
	{
		m_pReady[0]->BindDrawType(CScene::DRAW_TYPE_NO);
		m_pReady[1]->BindDrawType(CScene::DRAW_TYPE_NO);
	}
}
//=============================================================================
// VS�Z���N�g�X�e�[�W �X�e�[�W�����`��ύX
//=============================================================================
void CvsSelectStage::ChangeStage(bool bDraw)
{
	if (bDraw)
	{
		m_pReady[1]->BindDrawType(CScene::DRAW_TYPE_NO);
		m_pStageLogo->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_pStage[0]->GetfCntState() = 100.0f; m_pStage[0]->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_pStage[1]->GetfCntState() = 100.0f; m_pStage[1]->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_pStage[2]->GetfCntState() = 100.0f; m_pStage[2]->BindDrawType(CScene::DRAW_TYPE_NORMAL);

		CSceneAnim2D *p2DAnim;
		if (SceneCreate(p2DAnim, S2D_PRIORITY))
		{
			p2DAnim->Set(GetpStage(GetnSelect())->GetPosition(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI * 0.5f, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
				CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Slashing0);
			p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
		}
	}
	else
	{
		m_pStageLogo->BindDrawType(CScene::DRAW_TYPE_NO);
		m_pReady[1]->BindDrawType(CScene::DRAW_TYPE_NORMAL);
		m_pStage[0]->BindDrawType(CScene::DRAW_TYPE_NO);
		m_pStage[1]->BindDrawType(CScene::DRAW_TYPE_NO);
		m_pStage[2]->BindDrawType(CScene::DRAW_TYPE_NO);
	}
}
//=============================================================================
// VS�Z���N�g�X�e�[�W �X�e�[�W�X�V����
//=============================================================================
void CvsSelectStage::UpdateStage(void)
{
	for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++)
	{
		if (nCount == m_nSelect) { m_pStage[nCount]->GetState()[0] = C2DPolygon::STATE_BIG; }
		else { m_pStage[nCount]->GetState()[0] = C2DPolygon::STATE_SMALL; }
	}
}
//=============================================================================
// VS�Z���N�g�X�e�[�W �I������
//=============================================================================
void CvsSelectStage::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_VS_READY; nCount++) { m_pReady[nCount]->Uninit(); }
	for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++) { m_pStage[nCount]->Uninit(); }
	m_pStageLogo->Uninit();
}
//=============================================================================
// VS�Z���N�g�X�e�[�W �X�V����
//=============================================================================
void CvsSelectStage::Update(void)
{
	for (int nCount = 0; nCount < MAX_VS_READY; nCount++) { m_pReady[nCount]->Update(); }
	for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++) { m_pStage[nCount]->Update(); }
}
//=============================================================================
// VS�Z���N�g�X�e�[�W �`�揈��
//=============================================================================
void CvsSelectStage::Draw(void)
{
	for (int nCount = 0; nCount < MAX_VS_READY; nCount++) { m_pReady[nCount]->Draw(); }
	for (int nCount = 0; nCount < MAX_VS_STAGE; nCount++) { m_pStage[nCount]->Draw(); }
	m_pStageLogo->Draw();
}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CvsSelect::Init(void)
{
	//�{�̘̂g����
	CScene::CreateAll(0, 32);
	CScene::CreateAll(1, 32);
	CScene::CreateAll(2, 32);
	CScene::CreateAll(3, 32);
	CScene::CreateAll(4, 32);
	CScene::CreateAll(5, 32);
	CScene::CreateAll(6, 128);
	CScene::CreateAll(7, 32);

	CScene2D::Load(CScene2D::TEXTURE_Slashing0);

	m_bStage = false;
	m_bGo = false;

	//BGM�̍Đ�
	CSound *pSound = CManager::GetSound();

	//�ϐ��̏�����
	m_fMaxGage = 50.0f;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_bReady[nCount] = false;
		m_Select[nCount] = CvsSelectUI::SELECT_TANK0;
		m_tex[nCount][0] = CSceneModel::TEX_PTN_01;
		m_tex[nCount][1] = CSceneModel::TEX_PTN_01;
		m_item[nCount] = ITEM::TYPE_MAX;
		m_fLife[nCount] = 0;
		m_fAtk[nCount] = 0;
		m_fDef[nCount] = 0;
		m_nUV[nCount] = 0;
		m_nComLevel[nCount] = -1;
	}

	//�|���S���̐���
	CScene2D *pScene2D;

	if (SceneCreate(pScene2D, 0))
	{//BG�̐���
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_ZCLEAR, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_VsSelect);
	}

	if (SceneCreate(pScene2D, 6))
	{//�g�̐���
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 33.0f, SCREEN_HEIGHT / 2, 0.0f), 33.0f, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 1, 0.0f, CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_VsSelect2);
	}
	if (SceneCreate(pScene2D, 6))
	{//�g�̐���
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 33.0f, SCREEN_HEIGHT / 2, 0.0f), 33.0f, SCREEN_HEIGHT / 2, D3DX_PI, 1, 2, 1, 0.0f, CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_VsSelect2);
	}
	if (SceneCreate(pScene2D, 6))
	{//�g�̐���
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH - 33.0f, SCREEN_HEIGHT / 2, 0.0f), 33.0f, SCREEN_HEIGHT / 2, D3DX_PI, 1, 2, 1, 0.0f, CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_VsSelect2);
	}
	if (SceneCreate(pScene2D, 6))
	{//�g�̐���
		pScene2D->Set(D3DXVECTOR3(33.0f, SCREEN_HEIGHT / 2, 0.0f), 33.0f, SCREEN_HEIGHT / 2, D3DX_PI, 0, 2, 1, 0.0f, CScene2D::STATE_FLOW2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_VsSelect2);
	}

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (SceneCreate(pScene2D, 2))
		{//���~���̐���
			pScene2D->Set(D3DXVECTOR3(nCount * (SCREEN_WIDTH * 0.5f) + SCREEN_WIDTH / 4, 15, 0.0f), SCREEN_WIDTH / 4, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEX_UIWindow);
			pScene2D->BindDrawType(CScene::DRAW_TYPE_MULTIPLY);
		}
		if (SceneCreate(pScene2D, 5))
		{//Item���S�̐���
			pScene2D->Set(D3DXVECTOR3(nCount * (SCREEN_WIDTH * 0.5f) + SCREEN_WIDTH / 4 - 100.0f, VsSelect_InfoY + VsSelect_Interval * 2, 0.0f), 100.0f, VsSelect_Interval * 0.45f, D3DX_PI, 0, 1, 6, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoVersus);
		}
		if (SceneCreate(pScene2D, 5))
		{//BulletCollar���S�̐���
			pScene2D->Set(D3DXVECTOR3(nCount * (SCREEN_WIDTH * 0.5f) + SCREEN_WIDTH / 4 - 100.0f, VsSelect_InfoY + VsSelect_Interval * 3, 0.0f), 100.0f, VsSelect_Interval * 0.45f, D3DX_PI, 1, 1, 6, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_LogoVersus);
		}
	}

	//�X�e�[�W�I���|���S��������
	if (SceneCreate(m_pStage, 6))
	{
		m_pStage->Set();
	}

	Load();	//�O��I�����Ă�����Ԃ�

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++) 
	{ 
		if (m_pUI[nCount] == NULL)
		{//NULL�Ȃ�
			if (SceneCreate(m_pUI[nCount], 5))
			{//����
				m_pUI[nCount]->Set(nCount, this);
				m_pUI[nCount]->SetSelect(this, nCount);
			}
		}
	}

	//�J������Y���␳
	CCamera::camera.m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CCamera::camera.m_posV = D3DXVECTOR3(0.0f, 30.0f, 60.0f);

	return S_OK;
}
//=============================================================================
//  VS�Z���N�g�̍X�V����
//=============================================================================
void CvsSelect::Update(void)
{
	CSound *pSound = CManager::GetSound();
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
	int nStage = 0;

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(nCount);	//�W���C�p�b�h���l��

		if (!m_bStage)
		{//��������ւ�
			if (m_bReady[0] && m_bReady[1])
			{//�S���������ł���
				m_pStage->ChangeReady(true);
				if (pInputPad->GetTrigger(INPUT_START) || pInputPad->GetTrigger(INPUT_A) || pInputKey->GetTrigger(DIK_RETURN))
				{//�X�e�[�W�I����
					m_bStage = true;
					m_pStage->ChangeStage(true);
					break;
				}
			}
			WeaponSelect(nCount);
		}
		else
		{//�X�e�[�W�I��
			if (StageSelect(nCount)) { break; }
		}
	}

	if (CManager::GetFade()->GetState() != CFade::STATE_FADE_NOW)
	{
		if (m_bGo)
		{//�X�e�[�W�����܂�����
			Save();
			CManager::SetFade(CManager::MODE_VERSUS, 0);
		}
	}
}
//=============================================================================
// VS�Z���N�g�̏I������
//=============================================================================
void	CvsSelect::Uninit(void)
{
}
//=============================================================================
// VS�Z���N�g�̑����I������
//=============================================================================
void	CvsSelect::WeaponSelect(int &nCount)
{
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(nCount);	//�W���C�p�b�h���l��
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��

	if (!m_bReady[nCount])
	{
		if (pInputKey->GetTPress(DIK_BACK) || pInputPad->GetTrigger(INPUT_B))
		{//�߂�
			CManager::SetFade(CManager::MODE_SELECT, 0);
		}

		if (pInputKey->GetTPress(DIK_W) || pInputKey->GetTPress(DIK_UP) || 
			pInputPad->GetTPress(INPUT_UP) || pInputPad->GetTPress(INPUT_LS_U))
		{//���
			m_Select[nCount] = (CvsSelectUI::SELECT)(((int)m_Select[nCount] + (int)CvsSelectUI::SELECT_MAX - 1) % (int)CvsSelectUI::SELECT_MAX);
			m_pUI[nCount]->Cursor(m_Select[nCount]);
		}
		if (pInputKey->GetTPress(DIK_S) || pInputKey->GetTPress(DIK_DOWN) || 
			pInputPad->GetTPress(INPUT_DOWN) || pInputPad->GetTPress(INPUT_LS_D))
		{//����
			m_Select[nCount] = (CvsSelectUI::SELECT)(((int)m_Select[nCount] + 1) % (int)CvsSelectUI::SELECT_MAX);
			m_pUI[nCount]->Cursor(m_Select[nCount]);
		}

		if (pInputKey->GetTPress(DIK_D) || pInputKey->GetTPress(DIK_RIGHT) ||
			pInputPad->GetTPress(INPUT_RIGHT) || pInputPad->GetTPress(INPUT_LS_R))
		{//�E(��)
			m_pUI[nCount]->Select(m_Select[nCount], true, this, nCount);
		}
		if (pInputKey->GetTPress(DIK_A) || pInputKey->GetTPress(DIK_LEFT) || 
			pInputPad->GetTPress(INPUT_LEFT) || pInputPad->GetTPress(INPUT_LS_L))
		{//��(�O)
			m_pUI[nCount]->Select(m_Select[nCount], false, this, nCount);
		}

		if (m_pUI[nCount]->OverCost(this, nCount))
		{//�R�X�g���I�[�o�[���Ă��Ȃ�
			if (m_Select[nCount] == CvsSelectUI::SELECT_READY)
			{//�I�����ڂ�����OK�Ȃ�
				if (pInputKey->GetTrigger(DIK_RETURN) ||
					pInputPad->GetTrigger(INPUT_START) || pInputPad->GetTrigger(INPUT_A))
				{
					m_bReady[nCount] = true;
					m_pUI[nCount]->Ready(true);
				}
			}
		}
		else
		{//�R�X�g�I�[�o�[
			if (m_Select[nCount] == CvsSelectUI::SELECT_READY)
			{//�I�����ڂ�����OK�Ȃ�
				if (pInputKey->GetTrigger(DIK_RETURN) ||
					pInputPad->GetTrigger(INPUT_START) || pInputPad->GetTrigger(INPUT_A))
				{
				}
			}
		}
	}
	else if(pInputKey->GetTrigger(DIK_BACK) || pInputPad->GetTrigger(INPUT_B))
	{//�߂�
		m_bReady[nCount] = false;
		m_pUI[nCount]->Ready(false);
		m_pStage->ChangeReady(false);
	}
}
//=============================================================================
// VS�Z���N�g�̃X�e�[�W�I������
//=============================================================================
bool	CvsSelect::StageSelect(int &nCount)
{
	CInputJoyPad	*pInputPad = CManager::GetInputJoyPad(nCount);	//�W���C�p�b�h���l��
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//�L�[�{�[�h���l��
	bool bEffect = false;

	if (pInputKey->GetTrigger(DIK_BACK) || pInputPad->GetTrigger(INPUT_B))
	{//�߂�
		m_bStage = false;
		m_pStage->ChangeStage(false);
		m_pStage->ChangeReady(false);
		m_pUI[nCount]->Ready(false);
		m_bReady[nCount] = false;
		return true;
	}

	if (pInputKey->GetTPress(DIK_D) || pInputKey->GetTPress(DIK_RIGHT) ||
		pInputPad->GetTPress(INPUT_RIGHT) || pInputPad->GetTPress(INPUT_LS_R))
	{//�E(��)
		m_pStage->GetnSelect() = (m_pStage->GetnSelect() + 1) % MAX_VS_STAGE;
		bEffect = true;
	}
	if (pInputKey->GetTPress(DIK_A) || pInputKey->GetTPress(DIK_LEFT) ||
		pInputPad->GetTPress(INPUT_LEFT) || pInputPad->GetTPress(INPUT_LS_L))
	{//��(�O)
		m_pStage->GetnSelect() = (m_pStage->GetnSelect() + MAX_VS_STAGE - 1) % MAX_VS_STAGE;
		bEffect = true;
	}

	m_pStage->UpdateStage();	//�|���S���̍X�V

	if (pInputKey->GetTrigger(DIK_RETURN) ||
		pInputPad->GetTrigger(INPUT_START) || pInputPad->GetTrigger(INPUT_A))
	{//�X�e�[�W����
		m_bGo = true;
		return true;
	}
	else if(bEffect)
	{
		CSceneAnim2D *p2DAnim;
		if (SceneCreate(p2DAnim, S2D_PRIORITY))
		{
			p2DAnim->Set(m_pStage->GetpStage(m_pStage->GetnSelect())->GetPosition(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, D3DX_PI * 0.5f, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
				CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene2D::TEXTURE_Slashing0);
			p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
		}
		return true;
	}
	return false;
}
//=============================================================================
// VS�Z���N�g�̕ۑ�����
//=============================================================================
void	CvsSelect::Save(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/Versus.bin", "wb");

	if (pFile != NULL)
	{//Save�@����
		fwrite(&m_pStage->GetnSelect(), sizeof(int), 1, pFile);

		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			fwrite(&m_tex[nCount][0], sizeof(CSceneModel::TEXTURE), 2, pFile);
			fwrite(&m_item[nCount], sizeof(ITEM), 1, pFile);
			fwrite(&m_fLife[nCount], sizeof(float), 1, pFile);
			fwrite(&m_fAtk[nCount], sizeof(float), 1, pFile);
			fwrite(&m_fDef[nCount], sizeof(float), 1, pFile);
			fwrite(&m_nUV[nCount], sizeof(int), 1, pFile);
			fwrite(&m_nComLevel[nCount], sizeof(int), 1, pFile);
		}
		fclose(pFile);
	}
	else
	{//���s

	}
}
//=============================================================================
// VS�Z���N�g�̓ǂݍ��ݏ���
//=============================================================================
void	CvsSelect::Load(void)
{
	FILE *pFile;

	pFile = fopen("data/TEXT/Versus.bin", "rb");

	if (pFile != NULL)
	{//���[�h�@����
		fread(&m_pStage->GetnSelect(), sizeof(int), 1, pFile);

		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			fread(&m_tex[nCount][0], sizeof(CSceneModel::TEXTURE), 2, pFile);
			fread(&m_item[nCount], sizeof(ITEM::TYPE), 1, pFile);
			fread(&m_fLife[nCount], sizeof(float), 1, pFile);
			fread(&m_fAtk[nCount], sizeof(float), 1, pFile);
			fread(&m_fDef[nCount], sizeof(float), 1, pFile);
			fread(&m_nUV[nCount], sizeof(int), 1, pFile);
			fread(&m_nComLevel[nCount], sizeof(int), 1, pFile);
		}
		fclose(pFile);
	}
	else
	{//���s

	}
}
//=============================================================================
// VS�̎��̓ǂݍ��ݏ���
//=============================================================================
void CvsSelect::LoadVS(int &nStage)
{
	//���[�h�p�ϐ�
	CScenePlayer *pPlayer;
	CSceneModel::TEXTURE tex[2];
	ITEM::TYPE	Item;
	float	fLife, fAtk, fDef;
	int		nUV;
	int		nComLevel;

	FILE *pFile;

	pFile = fopen("data/TEXT/Versus.bin", "rb");

	if (pFile != NULL)
	{//���[�h�@����
	 fread(&nStage, sizeof(int), 1, pFile);

	 for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	 {
		 fread(&tex[0], sizeof(CSceneModel::TEXTURE), 2, pFile);
		 fread(&Item, sizeof(ITEM::TYPE), 1, pFile);
		 fread(&fLife, sizeof(float), 1, pFile);
		 fread(&fAtk, sizeof(float), 1, pFile);
		 fread(&fDef, sizeof(float), 1, pFile);
		 fread(&nUV, sizeof(int), 1, pFile);
		 fread(&nComLevel, sizeof(int), 1, pFile);

		 if (SceneCreate(pPlayer, MODEL_PRIORITY)) {
			 pPlayer->Set(D3DXVECTOR3(0.0f, PLAYER_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CSceneModel::MODEL_TANKD, CSceneModel::MODEL_TANKU, 
				 tex[0], tex[1], CScene::DRAW_TYPE_NORMAL);
			 pPlayer->PlusLifeUP((int)fLife);
			 pPlayer->PlusAtkUP((int)fAtk);
			 pPlayer->PlusDefUP((int)fDef);
			 pPlayer->GetnUV() = nUV;
			 pPlayer->PlusLevel(49);
			 if (Item < ITEM::TYPE_MAX) { pPlayer->SetItem(Item); }
		 }
	 }
		fclose(pFile);
	}
	else
	{//���s

	}
}

