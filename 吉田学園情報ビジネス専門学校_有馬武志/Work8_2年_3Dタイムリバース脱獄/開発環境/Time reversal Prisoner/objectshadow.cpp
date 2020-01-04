//=============================================================================
//
// �I�u�W�F�N�g�̏��� [objectshadow.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "model3D.h"
#include "manager.h"
#include "objectshadow.h"
#include "meshfield.h"
#include "player.h"
#include "fade.h"
#include "shadow.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_WALK			(0.2f)
#define MODEL_RAN			(1.0f)
#define MODEL_SQUAT			(0.1f)
#define MODEL_SNEAK			(0.1f)

#define MODEL_NAME_1	"data\\MODEL\\shadow001.x"			//�ǂݍ��ރe�N�X�`���t�@�C��

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(25)			// �v���C���[�̕������p
#define PLAYER_HEIGHT	(100.0f)		// �v���C���[�̔w�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPD3DXMESH CObjectShadow::m_pMeshModel[MAX_OBJECTSHADOW] = {};						//���b�V�����ւ̃|�C���^
LPD3DXBUFFER CObjectShadow::m_pBuffMatModel[MAX_OBJECTSHADOW] = {};					//�}�e���A���̏��ւ̃|�C���^
DWORD CObjectShadow::m_nNumMatModel[MAX_OBJECTSHADOW] = {};							//�}�e���A���̏��
LPDIRECT3DTEXTURE9 CObjectShadow::m_pMeshTextures[MAX_OBJECTSHADOW_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CObjectShadow::CObjectShadow() : CModel3D(OBJECTSHADOW_PRIOTITY,CScene::OBJTYPE_SHADOWMODEL)
{
	m_ModelMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nStageCount = 0;
	m_bStageNext = false;
	m_pVtxBuff = NULL;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CObjectShadow::~CObjectShadow()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CObjectShadow::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//3D���f����Init
	CModel3D::Init();
	
	// �ʒu�̏�����
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//�ʒu�̑��
	CModel3D::SetPosition(pos);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL
	);

	// ���_����ݒ�
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//1.0f�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//���_�J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);
	//�e�N�X�`���ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObjectShadow::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CLogo::UnLoad();

	//3D���f����Uninit
	CModel3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObjectShadow::Update(void)
{
	//���͏��
	CInputKeyBoard *pCInputKeyBoard = CManager::GetInput();
	CInputJoypad *pCInputJoyPad = CManager::GetInputJoyPad();
	//3D���f����Update
	CModel3D::Update();
	//�ʒu�̏�����
	D3DXVECTOR3 pos = CModel3D::GetPosition();
	// �ړ��ʂ̏�����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//�����̑��
	D3DXVECTOR3 &rot = CModel3D::GetRot();
	// MOVETYPE�̐ݒ�
	MOVETYPE MoveType = CModel3D::GetMoveType();
	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	CCamera *pCamera = CManager::GetCamera();

	//���a
	float fRadius = 10.0f;
	//�~��
	float fCircumference = (((D3DX_PI * 2.0f) * fRadius));

	// �e����̑��
	if (CGame::GetPlayer() != NULL)
	{
		CModel3D::SetPosition(CGame::GetPlayer()->GetPos());
	}

	CModel3D::SetMove(move);
	CModel3D::SetMoveType(MoveType);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CObjectShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�X�e���V���e�X�g��L����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//��ʂɂ͕`�悵�Ȃ�
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0);		//�f�t�H���g��0x0000000f

	//�X�e���V���o�b�t�@�̐ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);			//�S��OK
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g��Z�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);		//�X�e���V���e�X�g�����i�ƕs���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g���s���i
	
	//�\�ʃJ�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�e�̃��f���`��
	CModel3D::Draw();

	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						//�ΏۂƔ�r
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);		//1�Ԗڂ��L�[�v
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);		//�X�e���V���e�X�g��Z�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g�����i��Z�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);		//�X�e���V���e�X�g���s���i
	
	//���ʃJ�����O
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	//�e�̃��f���`��
	CModel3D::Draw();

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);		//�f�t�H���g��0x0000000f

	//�X�e���V����߂�
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						//�ΏۂƔ�r
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL);		//�S��OK
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g��Z�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g�����i��Z�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);		//�X�e���V���e�X�g���s���i

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�X�e���V���e�X�g�𖳌���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CObjectShadow * CObjectShadow::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, float move, int nTexType,int nObjectType, MOVETYPE nMovetype, int nCollision)
{
	CObjectShadow *pObject = NULL;

	// NULL�`�F�b�N
	if (pObject == NULL)
	{// �������̓��I�m��

		pObject = new CObjectShadow;

		if (pObject != NULL)
		{
			// ��ނ̐ݒ�
			pObject->BindModel(m_pMeshModel[nObjectType], m_pBuffMatModel[nObjectType], m_nNumMatModel[nObjectType], m_pMeshTextures[nTexType]);
			// �I�u�W�F�N�g���Ƃ̐ݒ�p�^�C�v
			pObject->m_nType = nObjectType;
			// �I�u�W�F�N�g�N���X�̐���
			pObject->Init();
			// �ʒu����
			pObject->SetPosition(pos);
			// ��]�𔽉f
			pObject->SetRot(rot);
			// �����̎�ނƈړ��ʂ�ݒ�
			pObject->SetMoveType(nMovetype);
			pObject->m_move = D3DXVECTOR3(move, move, move);
			// �R���W������ONOFF
			pObject->m_nCollision = nCollision;
		}
	}

	return pObject;
}
//===============================================================================
// X�t�@�C���̓ǂݍ���
//===============================================================================
HRESULT CObjectShadow::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL *pMat;							

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME_1, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMatModel[0], NULL, &m_nNumMatModel[0], &m_pMeshModel[0]);

	for (int nCount = 0; nCount < MAX_OBJECTSHADOW; nCount++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMatModel[nCount]->GetBufferPointer();
	}

	//�g���Ă���e�N�X�`��
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\.jpg", &m_pMeshTextures[0]);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CObjectShadow::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_OBJECTSHADOW; nCount++)
	{
		// ���b�V���̊J��
		if (m_pMeshModel[nCount] != NULL)
		{
			m_pMeshModel[nCount]->Release();
			m_pMeshModel[nCount] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMatModel[nCount] != NULL)
		{
			m_pBuffMatModel[nCount]->Release();
			m_pBuffMatModel[nCount] = NULL;
		}
	}
	//�e�N�X�`��
	for (int nCntTex = 0; nCntTex < MAX_OBJECTSHADOW_TEXTURE; nCntTex++)
	{
		if (m_pMeshTextures[nCntTex] != NULL)
		{
			m_pMeshTextures[nCntTex]->Release();
			m_pMeshTextures[nCntTex] = NULL;
		}
	}
}
//=============================================================================
//	�X�e�[�W�ړ����ɏ��������邽��
//=============================================================================
void CObjectShadow::DeleteObject(void)
{
	CScene *pScene;

	//�v���C�I���e�B�[�`�F�b�N
	pScene = CScene::GetTop(OBJECT_PRIOTITY);

	//NULL�`�F�b�N
	while (pScene != NULL)
	{
		//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{//�^�C�v���ǂ�������
			if (pScene->GetObjType() == OBJTYPE_OBJECT)
			{
				pScene->Uninit();
			}
		}
		//Next�Ɏ���Scene������
		pScene = pSceneNext;
	}
}
//===============================================================================
// �����蔻��
//===============================================================================
bool CObjectShadow::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;
	//�������Ă��邩�������ĂȂ���
	bool bLand = false;
	//�����蔻��̕ۑ�
	int nCollision = m_nCollision;
	//���[�h�̏��
	CManager::MODE pMode = CManager::GetMode();
	//�J�����̏��
	CCamera *pCamera = CManager::GetCamera();
	//�X�e�[�W���
	CGame::STAGENUM pStageNum = CGame::GetNumState();

	switch (m_nCollision)
	{
	case 1:

		// �e����̎擾
		D3DXVECTOR3 Playerpos = *pPos;						// �v���C���[�̏����ʒu
		D3DXVECTOR3 ModelPos = CModel3D::GetPosition();		// �ʒu
		D3DXVECTOR3 ModelMove = CModel3D::GetMove();		// �ړ���
		MOVETYPE ModelMoveType = CModel3D::GetMoveType();	// �����̃^�C�v
		D3DXVECTOR3 VtxMax = CModel3D::VtxMax();			// ���f���̍ő�l
		D3DXVECTOR3 VtxMin = CModel3D::VtxMin();			// ���f���̍ŏ��l

		D3DXVECTOR3 ModelMax = CModel3D::VtxMax();	// �ʒu���݂̍ő�l
		D3DXVECTOR3 ModelMin = CModel3D::VtxMin();	// �ʒu���݂̍ŏ��l

		//�v�Z�O�p
		D3DXVECTOR3 WkMax = ModelMax;
		D3DXVECTOR3 WkMin = ModelMin;

		//�p�x
		D3DXVECTOR3 rot = CModel3D::GetRot();
		bool		bHit = false;

		// �ړ��ʂ̕ێ�
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		//���f���̌����ɂ���ē����蔻���MAX��MIN��ς���
		if (rot.y == 1.57f)
		{//�E����
			ModelMin.z = WkMax.x * -1.0f;
			ModelMax.z = WkMin.x * -1.0f;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -1.57f)
		{
			ModelMax.z = WkMax.x;
			ModelMin.z = WkMin.x;
			ModelMax.x = WkMax.z;
			ModelMin.x = WkMin.z;
		}
		if (rot.y == -3.14f || rot.y == 3.14f)
		{
			ModelMin.x = WkMax.x * -1.0f;
			ModelMax.x = WkMin.x * -1.0f;
			ModelMin.z = WkMax.z * -1.0f;
			ModelMax.z = WkMin.z * -1.0f;
		}
		ModelMax += ModelPos;
		ModelMin += ModelPos;

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Z�͈͓̔��ɂ���		
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// X�͈͓̔��ɂ���
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// �I�u�W�F�N�g�̏ォ�瓖����ꍇ
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X�ړ�����
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z�ړ�����
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// �I�u�W�F�N�g�̉����瓖����ꍇ
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}
			}
		}

		if (pPos->y - PLAYER_HEIGHT <= ModelMax.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
		{// �I�u�W�F�N�g���Ƃ̓����蔻��
			if (pPos->x - PLAYER_DEPTH <= ModelMax.x && pPos->x + PLAYER_DEPTH >= ModelMin.x)
			{// �I�u�W�F�N�g���Ƃ̓����蔻��
				if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
				{//MAX �c��
					pPos->z = ModelMax.z + PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
				{//MIN �c��
					pPos->z = ModelMin.z - PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
			}
			if (pPos->z - PLAYER_DEPTH <= ModelMax.z && pPos->z + PLAYER_DEPTH >= ModelMin.z)
			{// �I�u�W�F�N�g���Ƃ̓����蔻�� 
				if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
				{//MAX ���E
					pPos->x = ModelMax.x + PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
				else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
				{//MIN ����
					pPos->x = ModelMin.x - PLAYER_DEPTH;

					//�v���C�I���e�B�[�`�F�b�N
					pScene = CScene::GetTop(2);

					//NULL�`�F�b�N
					while (pScene != NULL)
					{
						//Update��Uninit����Ă��܂��ꍇ�@Next��������\�������邩��Next�Ƀf�[�^���c���Ă���
						CScene *pSceneNext = pScene->GetNext();

						if (pScene->GetDeath() == false)
						{//�^�C�v���ǂ�������
							if (pScene->GetObjType() == OBJTYPE_PLAYER)
							{
								bHit = true;
							}
						}
						//Next�Ɏ���Scene������
						pScene = pSceneNext;
					}
				}
			}
		}


		if (m_nType == 2 && bHit == true)
		{// �}�b�v�ړ�����p�I�u�W�F�N�g
			if (pStageNum == CGame::STAGENUM_1 || pStageNum == CGame::STAGENUM_2)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(59.0f, 146.0f, 568.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-199.0f, 0.0f, 140.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_3)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(905.0f, 190.0f, 540.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(635.0f, 0.0f, 680.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_4)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(470.0f, 240.0f, 660.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(845.0f, 0.0f, -160.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_5)
			{
				//�J�����A���O�����K�i�����Ƃ��̖ڐ�
				pPos[0] = Playerpos;
				pCamera->SetCameraPosV(D3DXVECTOR3(-1040.0f, 170.0f, 400.0f));
				pCamera->SetCameraPosR(D3DXVECTOR3(-740.0f, 0.0f, 280.0f));

				//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
				CPlayer::SetCancelStageNext(true);

				//�X�e�[�W�J�ڒ�
				m_bStageNext = true;
			}
			else if (pStageNum == CGame::STAGENUM_6)
			{
				if (CFade::GetFade() == CFade::FADE_NONE)
				{//P�L�[�������ꂽ��
					//�V�K�ǉ�
					CManager::SetGameScore(CTime::GetTime());
					CManager::RankingScore(CTime::GetTime());

					//�X�e�[�W�J�ڂ̍ۂ̃X�L���L�����Z��
					CPlayer::SetCancelStageNext(true);

					CGame::SetGameState(CGame::GAMESTATE_CLEAR);
				}
			}
		}

		// �ʒu�̑��
		CModel3D::SetPosition(ModelPos);
		// �ړ��ʂ̑��
		m_ModelMove = ModelMove;

		break;
	}

	return bLand;
}