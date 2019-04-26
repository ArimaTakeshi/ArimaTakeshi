//=============================================================================
//
// �o���b�g�̏��� [bullet.cpp]
// Author : �L�n���u
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "bullet.h"
#include "manager.h"
#include "renderer.h"
#include "explosion.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
#include "damage.h"
#include "2Dobject.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME_1	"data\\TEXTURE\\Bullet0000.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_2	"data\\TEXTURE\\Bullet0001.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_3	"data\\TEXTURE\\Bullet0002.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define TEXTURE_NAME_4	"data\\TEXTURE\\Bullet0003.png"			//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULLET_X		(2)										//���̑傫��
#define	BULLET_Y		(10)									//�c�̑傫��
#define DAMAGE			(1)										//�_���[�W��
#define CANNON			(5)										//��C�̃_���[�W��
#define SKYCANNON		(1)										//�΋�C�̃_���[�W��
#define TORPEDO			(50)									//�����̃_���[�W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture[MAX_TEXTURE] = {};

//===============================================================================
//�@�f�t�H���g�R���X�g���N�^
//===============================================================================
CBullet::CBullet() : CScene2D(3)//�D��D�ʃC�j�V�����C�Y
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nType = 0;
	m_nBulletType = 0;
	m_nDamage = 0;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_Petype = PLAYER_SHIP;
}
//===============================================================================
//�@�f�X�g���N�^
//===============================================================================
CBullet::~CBullet()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBullet::Init(void)
{
	CScene2D::Init();

	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BULLET);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	//�����������������ĂȂ����̔���
	bool bHit;

	//�G�̏��
	CEnemy *pEnemy = CGame::GetEnemy();

	//m_pos����
	D3DXVECTOR3 Bulletpos = CScene2D::GetPosition();

	//�ړ��ʂ̑��
	Bulletpos += m_move;

	//�e�̈ʒu�ƃT�C�Y
	Set(Bulletpos,m_Size);

	//�v���C���[�������ꍇ
	if (m_nType == BULLETTYPE_PLAYER || m_nType == BULLETTYPE_ENEMY)
	{
		//�_���[�W�̕ύX
     	if (m_nBulletType == CBullet::GAN_CANNON)
		{//��C�e
			m_nDamage = CANNON;
		}
		else if (m_nBulletType == CBullet::GAN_SKYCANNON)
		{//�΋�C
			m_nDamage = SKYCANNON;
		}
		else if (m_nBulletType == CBullet::GAN_TORPEDO)
		{//�����e
			m_nDamage = TORPEDO;
		}
	}

	//�_���[�W�̑��
	int nDamage = m_nDamage;

	//���ʂ��m�F
	for (int nCnPri = 0; nCnPri < NUM_PRIORITY; nCnPri++)
	{
		//�I�u�W�F�N�g�̑������m�F
		for (int nCntScene = 0; nCntScene < MAX_DATA; nCntScene++)
		{
			CScene2D *pScene;

			pScene = (CScene2D*)CScene::GetScene(nCnPri, nCntScene);

			if (pScene != NULL)
			{//NULL�`�F�b�N
				//���[�J���ō��
				CScene::OBJTYPE ObjType;

				//�I�u�W�F�N�g�̃V�[�����擾
				ObjType = pScene->GetObjType();

				//�����蔻��
				if (ObjType == CScene::OBJTYPE_PLAYER && m_nType == BULLETTYPE_ENEMY)
				{//���������G�̒e�̏�����������

					//�^���G�l�~�[�ɓ����
					CPlayer *pPlayer = (CPlayer*)pScene;

					//�G�̒e�̔���
					if (m_nBulletType == CBullet::GAN_CANNON && m_nType == BULLETTYPE_ENEMY || m_nBulletType == CBullet::GAN_TORPEDO && m_nType == BULLETTYPE_ENEMY || m_nBulletType == CBullet::GAN_SKYCANNON && m_nType == BULLETTYPE_ENEMY)
					{
						if (pScene->GetPosition().x - pPlayer->GetSize()->x < Bulletpos.x && pScene->GetPosition().x + pPlayer->GetSize()->x > Bulletpos.x &&
							pScene->GetPosition().y - pPlayer->GetSize()->y < Bulletpos.y && pScene->GetPosition().y + pPlayer->GetSize()->y > Bulletpos.y)
						{//�����蔻��

							//�e�̏I������
							CBullet::Uninit();

							if (m_nBulletType == CBullet::GAN_TORPEDO)
							{
								//�����̐���
								CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 5);
							}
							else
							{
								//�����̐���
								CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 0);
							}
							//�v���C���[�ւ̃_���[�W�̏���
							pPlayer->HitPlayer(nDamage * 1.0f);
						}
					} 
				}
				else if (ObjType == CScene::OBJTYPE_ENEMY && m_nType == BULLETTYPE_PLAYER)
				{//���������v���C���[�̒e�̏�����������
				
					bHit = true;

					//�^���G�l�~�[�ɓ����
					CEnemy *pEnemy = (CEnemy*)pScene;

 					switch (m_nBulletType)
					{//�@�̂ƒe�𔻕�
					case GANTYPE_BULLET::GAN_CANNON:		//��C�̏ꍇ
						if (pEnemy->GetType() == CEnemy::ENEMYTYPE_SUBMARINE)
						{//�����͂ɂ͓�����Ȃ�
							bHit = false;
						}
						break;
					case GANTYPE_BULLET::GAN_SKYCANNON:		//�΋�C�̏ꍇ
						if (pEnemy->GetType() == CEnemy::ENEMYTYPE_SUBMARINE)
						{//�����͂ɂ͓�����Ȃ�
							bHit = false;
						}
						break;
					case GANTYPE_BULLET::GAN_TORPEDO:		//�����̏ꍇ
						if (pEnemy->GetType() == CEnemy::ENEMYTYPE_DIGHTER)
						{//�퓬�@�ɂ͂�����Ȃ�
							bHit = false;
						}
						break;
					}

					if (bHit)
					{//�������Ă����@�̂Ȃ�
						if (pScene->GetPosition().x - pEnemy->GetSize()->x < Bulletpos.x && pScene->GetPosition().x + pEnemy->GetSize()->x > Bulletpos.x &&
							pScene->GetPosition().y - pEnemy->GetSize()->y < Bulletpos.y && pScene->GetPosition().y + pEnemy->GetSize()->y > Bulletpos.y)
						{//�����蔻��

							//�e�̏I������
							CBullet::Uninit();

							//�����̐���
							//CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 0);

							//�G�ւ̃_���[�W�̏���
							pEnemy->HitEnemy(nDamage);
						}
					}
				}
				else if (ObjType == CScene2D::OBJTYPE_2DOBJECT)
				{//���������I�u�W�F�N�g�̏�����������

					 //�^���I�u�W�F�N�g�ɓ����
					C2DObject *p2DObject = (C2DObject*)pScene;

					if (pScene->GetPosition().x - p2DObject->GetSize()->x < Bulletpos.x && pScene->GetPosition().x + p2DObject->GetSize()->x > Bulletpos.x &&
						pScene->GetPosition().y - p2DObject->GetSize()->y < Bulletpos.y && pScene->GetPosition().y + p2DObject->GetSize()->y > Bulletpos.y)
					{//�����蔻��

						//�e�̏I������
						CBullet::Uninit();

						//�����̐���
						CExplosion::Create(Bulletpos, D3DXVECTOR2(20, 20), 0);

						//�I�u�W�F�N�g�ւ̃_���[�W
						p2DObject->HitObject(nDamage);
					}
				}
			}
		}
	}

	if (Bulletpos.y < m_Size.y || Bulletpos.y > SCREEN_HEIGHT - m_Size.y || Bulletpos.x < 300 + m_Size.x || Bulletpos.x > SCREEN_WIDTH - 300 - m_Size.x)
	{//��ʊO�̏ꍇ
		//�e�̏I������
		CBullet::Uninit();

		//�����̐���
		CExplosion::Create(Bulletpos,D3DXVECTOR2(20, 20), 0);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
{
	CScene2D::Draw();
}
//===============================================================================
//�@�N���G�C�g
//===============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXVECTOR2 size, BULLETTYPE type, GANTYPE_BULLET bullettype , PETYPE petype,int nBulletType)
{
	CBullet *pBullet = NULL;

	//NULL�`�F�b�N
	if (pBullet == NULL)
	{//�������̓��I�m��

		pBullet = new CBullet;

		if (pBullet != NULL)
		{
			//�I�u�W�F�N�g�N���X�̐���
			pBullet->Init();
			//�e�N�X�`�������蓖�Ă�
			pBullet->BindTexture(m_pTexture[nBulletType]);
			//��ނ����蓖�Ă�
			pBullet->m_nType = type;
			//�T�C�Y�̊��蓖��
			pBullet->m_Size = size;
			//�ړ��ʂ̊��蓖��
			pBullet->m_move = move;
			//�e�̔���
			pBullet->m_nBulletType = bullettype;
			//�G���������̔���
			pBullet->m_Petype = petype;
			//�e��ݒu
			pBullet->SetPosition(pos);
		}
	}
	return pBullet;
}
//===============================================================================
// �e�N�X�`���̓ǂݍ���
//===============================================================================
HRESULT CBullet::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_1,
		&m_pTexture[0]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_2,
		&m_pTexture[1]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_3,
		&m_pTexture[2]
	);
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile
	(
		pDevice,
		TEXTURE_NAME_4,
		&m_pTexture[3]
	);

	return S_OK;
}
//===============================================================================
// �e�N�X�`���̔j��
//===============================================================================
void CBullet::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//�e�N�X�`���[�̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}