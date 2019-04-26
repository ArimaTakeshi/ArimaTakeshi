//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���{��
//
//=============================================================================
#include "camera.h"
#include "mesh.h"
#include "SceneModel.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "light.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define		DISTANCE		(250)			//�����_�Ǝ��_�̋���
#define		CAMERA_MOVE		(0.8f)			//�J�����̈ړ����x
#define		ROTPOOR_RY		(80)			//�����_�㉺ +��, -��
#define		ROTPOOR_VY		(80)				//�J�����{�� +��, -��

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
CCamera_Manager::Info CCamera_Manager::m_info;			//�J�������

//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::Init(void)
{
	m_Type = CCamera::CAMERA_TYPE_OBJ;

	m_posV = D3DXVECTOR3(0.0f, 200.0f, 200.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.1f);				//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//�i�j�R��(��)
	m_rot = D3DXVECTOR3(D3DX_PI * 0.035f, D3DX_PI, 0.0f);	//�p�x
	m_targetpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�Ǐ]����J�����̏ꏊ
	m_fDistance = DISTANCE;									//���_�ƒ����_�̋���

	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;
	SetViewport(0, 0, 0, 0);
}
//=============================================================================
// �J�����̕`�揈��
//=============================================================================
void CCamera::Draw(void)
{
	SetCamera(m_posV);
	//CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);
	CScene::DrawObj(CManager::GetRenderer()->GetDevice());
}
//=============================================================================
// �J�����̃Z�b�g����
//=============================================================================
void CCamera::SetCamera(D3DXVECTOR3 WKposV)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&m_viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),	//��p
		(float)m_viewport.Width /
		(float)m_viewport.Height,
		10.0f,
		24800.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView, &WKposV, &m_posR, &m_vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(100, 0, 0, 0), 1.0f, 0);

	CCamera_Manager::GetInfo().pCamera = this;
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "posV %.1f�@%.1f�@%.1f\n", WKposV.x, WKposV.y, WKposV.z);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "posR %.1f�@%.1f�@%.1f\n", m_posR.x, m_posR.y, m_posR.z);

}
//=============================================================================
// 3D�̕`�揈�������΍􏈗�
//=============================================================================
bool CCamera::DrawCheck(D3DXVECTOR3 &pos, float fLength)
{//�����_���猩�Ĉ��͈͓��Ȃ�`��
	D3DXVECTOR3 WKpos = m_posV + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * fLength;
	float fAngle = atan2f(WKpos.x - pos.x, WKpos.z - pos.z) - m_rot.y;

	if (fAngle > D3DX_PI) { fAngle -= D3DX_PI * 2.0f; }
	if (fAngle < -D3DX_PI) { fAngle += D3DX_PI * 2.0f; }

	if (fAngle >= -D3DX_PI * (DRAW_ANGLEP / 180) && fAngle <= +D3DX_PI * (DRAW_ANGLEP / 180))
	{//�J�����̌����ʂ�Ȃ�
		float fDistance = powf(m_posR.x - pos.x, 2) + powf(m_posR.z - pos.z, 2);
		if (fDistance < fLength + DRAW_DISTANCE) { return true; }
	}

	return false;
}
//=============================================================================
// 3D�̕`�揈�������΍􏈗�
//=============================================================================
void CCamera::SetViewport(int left, int up, int right, int bottom)
{
	m_viewport.X = (DWORD)left;
	m_viewport.Y = (DWORD)up;
	m_viewport.Width = (DWORD)right;
	m_viewport.Height = (DWORD)bottom;
}

//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera_Char::Init(void)
{
	CCamera::Init();
	m_pChar = NULL;
	m_pMove = NULL;
	m_fGMagnification = 0.1f;
	GetType() = CCamera::CAMERA_TYPE_CHAR;
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Char::Update(void)
{
	if (m_pChar != NULL && m_pMove != NULL)
	{//�Ǐ]�̏ꏊ�̍X�V
		CInputKeyboard *pInputKey = CManager::GetInputKey();
		D3DXVECTOR3		&m_posV = GetposV();
		D3DXVECTOR3		&m_posR = GetposR();
		D3DXVECTOR3		&m_rot = GetRot();
		D3DXVECTOR3		&m_targetpos = Gettargetpos();
		float			&m_fDistance = GetfDistance();

		if (pInputKey->GetPress(DIK_U)) { m_rot.y += D3DX_PI * 0.0125f; }
		if (pInputKey->GetPress(DIK_O)) { m_rot.y -= D3DX_PI * 0.0125f; }
		if (pInputKey->GetPress(DIK_Y)) { m_rot.x += D3DX_PI * 0.0125f; }
		if (pInputKey->GetPress(DIK_H)) { m_rot.x -= D3DX_PI * 0.0125f; }
		if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
		if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 0.3f; }
		m_targetpos += (m_pChar[0] - m_targetpos) * 0.08f;

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos;	//����ꏊ + �����ړ���
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//���_�@���� + (�p�x * ����) + �����ړ���
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X��
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y��
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z��
		m_posV += (m_goal - m_posV) * m_fGMagnification;
		//m_posV.y = fY;
	}
}
//=============================================================================
// �J�����̕`�揈��
//=============================================================================
void CCamera_Char::Draw(void)
{
	SetCamera();
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	CManager::GetRenderer()->GetDevice()->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(150, 150, 150, 0), 1.0f, 0);
	CScene::Draw3D(CManager::GetRenderer()->GetDevice());
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Char::Reset(void)
{
	if (m_pChar != NULL)
	{//�Ǐ]�̏ꏊ�̍X�V
		D3DXVECTOR3		&m_posV = GetposV();
		D3DXVECTOR3		&m_posR = GetposR();
		D3DXVECTOR3		&m_rot = GetRot();
		D3DXVECTOR3		&m_targetpos = Gettargetpos();
		float			&m_fDistance = GetfDistance();

		if (m_pDistance != NULL) { m_fDistance += (m_pDistance[0] - m_fDistance) * 1.0f; }
		m_targetpos = m_pChar[0];

		m_posR = D3DXVECTOR3(0.0f, 0.0f + ROTPOOR_RY, 0.0f) + m_targetpos;	//����ꏊ + �����ړ���
		//m_posR +=D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -50.0f;

		//���_�@���� + (�p�x * ����) + �����ړ���
		m_goal = D3DXVECTOR3(
			m_targetpos.x + (sinf(m_rot.y) * m_fDistance) * cosf(m_rot.x),	//X��
			m_targetpos.y + sinf(m_rot.x) * m_fDistance + ROTPOOR_VY,		//Y��
			m_targetpos.z + (cosf(m_rot.y) * m_fDistance) * cosf(m_rot.x));	//Z��
		m_posV += (m_goal - m_posV) * 1.0f;
	}

}
//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera_Char::SetCamera(void)
{
	D3DXVECTOR3		&m_posV = GetposV();
	D3DXVECTOR3		&m_posR = GetposR();
	D3DXVECTOR3		&m_vecU = GetvecU();
	D3DXVECTOR3		&m_rot = GetRot();
	D3DXVECTOR3		&m_targetpos = Gettargetpos();
	float			&m_fDistance = GetfDistance();

	D3DXVECTOR3 WKValue, WKmove;
	D3DXVECTOR3	WKlength = D3DXVECTOR3(1.0f, 10.0f, 1.0f);
	D3DXVECTOR3	WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	WKposV = m_posV;
	float		fDistance0, fDistance1;
	bool bWKJump = false;

	fDistance0 = powf(m_posV.x - m_posR.x, 2) + powf(m_posV.z - m_posR.z, 2);
	WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * -30.0f;
	WKmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int		nCount = 0;
	//CMesh::MeshCollisionCeiling(WKposV, WKValue, WKlength);
	CMesh::MeshCollisionWall(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	//CMesh::MeshCollisionField(WKposV, WKValue, WKmove, WKlength, WKnor, bWKJump);
	//WKValue = m_posR + D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y)) * + 80.0f;
	//CSceneObjct::CollisionAll(WKposV, WKValue, WKmove, WKlength, WKnor, nCount, bWKJump, false);
	fDistance1 = powf(WKposV.x - m_posR.x, 2) + powf(WKposV.z - m_posR.z, 2);
	WKposV.y = m_posR.y + (WKposV.y - m_posR.y) * ((fDistance1) / fDistance0);
	CCamera::SetCamera(WKposV);
}

//=============================================================================
// �v���C���[�J�����̏���������
//=============================================================================
void CCamera_Play::Init(void)
{
	Create(m_pCamera_Obj);
	Create(m_pCamera_Char);
}
//=============================================================================
// �v���C���[�J�����̏I������
//=============================================================================
void CCamera_Play::Uninit(void)
{
	if (m_pCamera_Char != NULL) { delete m_pCamera_Char; }
	if (m_pCamera_Obj != NULL) { delete m_pCamera_Obj; }
}
//=============================================================================
// �v���C���[�J�����̍X�V����
//=============================================================================
void CCamera_Play::Update(void)
{
	if (m_pCamera_Char != NULL) { m_pCamera_Char->Update(); }
}
//=============================================================================
// �v���C���[�J�����̕`�揈��
//=============================================================================
void CCamera_Play::Draw(void)
{
	if (m_pCamera_Char != NULL) { m_pCamera_Char->Draw(); }
	//if (m_pCamera_Obj != NULL) { m_pCamera_Obj->Draw(); }
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Manager::Init(void)
{
	m_pEvent = NULL;
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_pPlay[nCount] = NULL;
	}

	CManager::GetCamera() = this;
}
//=============================================================================
// �J�����Ǘ��@�S�X�V����
//=============================================================================
void CCamera_Manager::Update(void)
{
	if (m_pEvent != NULL) { m_pEvent->Update(); }
	else
	{//�C�x���g���X�V���łȂ��Ȃ�
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Update(); }
		}
	}
}
//=============================================================================
// �J�����Ǘ�(�C�x���g)�̏I������
//=============================================================================
void CCamera_Manager::Uninit_Event(void)
{
	if (m_pEvent != NULL) { m_pEvent->Uninit(); m_pEvent = NULL; }
}
//=============================================================================
// �J�����Ǘ��̏I������
//=============================================================================
void CCamera_Manager::Uninit(void)
{
	Uninit_Event();
	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		if (m_pPlay[nCount] != NULL) 
		{ 
			//m_pPlay[nCount]->Uninit();
			delete m_pPlay[nCount];
			m_pPlay[nCount] = NULL;
		}
	}

	delete this;
	CManager::GetCamera() = NULL;
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Manager::Draw(void)
{
	if (m_pEvent != NULL) 
	{ 
		if (CManager::GetLight() != NULL) { CManager::GetLight()->Set(0); }
		m_pEvent->Draw(); 
	}
	else
	{//�C�x���g���X�V���łȂ��Ȃ�
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (CManager::GetLight() != NULL) { CManager::GetLight()->Set(nCount + 1); }
			if (m_pPlay[nCount] != NULL) { m_pPlay[nCount]->Draw(); }
		}
	}
}
//=============================================================================
// �J�����̕`��`�F�b�N����
//=============================================================================
bool CCamera_Manager::DrawCheck(D3DXVECTOR3 &pos, float fLength)
{
	switch (m_info.pCamera->GetType())
	{
	case CCamera::CAMERA_TYPE_CHAR:
		//if (!m_info.pCamera->DrawCheck(pos, fLength)) { return false; };
		break;
	case CCamera::CAMERA_TYPE_EVENT:
	case CCamera::CAMERA_TYPE_OBJ: break;
	}
	return true;
}
//=============================================================================
// �v���C���[�J������������
//=============================================================================
CCamera_Play *&CCamera_Manager::Create_Play(int nCount)
{
	CCamera_Play *pPlay;
	CCamera_Manager *&pManager = CManager::GetCamera();

	if (pManager == NULL)
	{
		Create(pManager);
	}

	if (pManager->GetPlay(nCount) != NULL) { return pManager->GetPlay(nCount); }

	if (Create(pPlay))
	{//�����ŗ�����|�C���^���g�ɑ��
		pPlay->GetChar()->GetnNumCamera() = nCount;
		pManager->GetPlay(nCount) = pPlay;
	}
	return pManager->GetPlay(nCount);
}
//=============================================================================
// �v���C���[�J������������
//=============================================================================
CCamera_Char *&CCamera_Manager::Create_Event(void)
{
	CCamera_Char *pChar;
	CCamera_Manager *&pManager = CManager::GetCamera();

	if (pManager == NULL)
	{
		Create(pManager);
	}

	if (pManager->GetEvent() != NULL) { return pManager->GetEvent(); }

	if (Create(pChar))
	{//�����ŗ�����|�C���^���g�ɑ��
		pChar->GetType() = CCamera::CAMERA_TYPE_EVENT;
		pManager->GetEvent() = pChar;
	}
	return pManager->GetEvent();
}
//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera_Manager::SetScene(CCamera_Manager::SCENE_TYPE type)
{
	m_info.nCntState = 0;
	m_info.nCntTime = 0;
	m_info.state = STATE_MOVIE;
	m_info.scene = type;
}
//=============================================================================
// �V�[���Đ�����
//=============================================================================
void CCamera_Manager::UpdateScene(void)
{
	if (m_info.state == STATE_MOVIE)
	{//�V�[���Đ�
		switch (m_info.scene)
		{
		case SCENE_TYPE_NO:	//�G���[�����p
			//Init();
			break;

		case SCENE_TYPE_BOSS:	//�{�X�O
			//Scene_BOSS();
			break;
		}
	}
}
