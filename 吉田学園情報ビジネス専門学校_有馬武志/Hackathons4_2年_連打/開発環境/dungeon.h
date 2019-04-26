//=============================================================================
//
// �V�[������ [scene.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _DUNGEON_H_
#define _DUNGEON_H_

#include "main.h"
#include "scene.h"
#include "sound.h"
#include "manager.h"
#include "SceneBullet.h"
#include "2DPolygon.h"
#include "3DPolygon.h"
#include "SceneModel.h"
#include "Number.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAP_MAX_EFFECT	(3)
#define MAP_MAX_EFFECT2	(2)
#define BOSSMAP_SIZEX	(13.0f)
#define BOSSMAP_SIZEZ	(8.0f)

#define BOSS_STAGE		(4)
#define DRAW_NumChipX	(8)
#define DRAW_NumChipZ	(5)
#define CHIP_SIZE		(20.0f)
#define ITEM_SIZE		(CHIP_SIZE * 0.2f)
#define NUMBER_SIZE		(2.0f)
#define DBG_PRIORYITY	(3)
#define DUNGEON_PRIORYITY	(0)
#define DUNGEON_CENTER		(D3DXVECTOR3((BOSSMAP_SIZEX / 2) * CHIP_SIZE - CHIP_SIZE, 20.1f, (BOSSMAP_SIZEZ / 2) * -CHIP_SIZE + CHIP_SIZE))

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSceneDungeonBG : public CScene
{
public:

	CSceneDungeonBG(int nPrioryity = DBG_PRIORYITY) : CScene::CScene(nPrioryity) { for (int nCnt = 0; nCnt < MAP_MAX_EFFECT2; nCnt++) { m_pBG[nCnt] = NULL; } };
	~CSceneDungeonBG() {};

	HRESULT	Init(void);
	void	Update(void);
	void	Draw(void);
	void	Uninit(void);

protected://*****************************************************************************
private://*****************************************************************************
	C2DCameraBG		*m_pBG[MAP_MAX_EFFECT2];		//�e�̌��w�i
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CDungeon : public CScene
{
public:
	typedef enum
	{
		MODEL_FIELD = 0,
		MODEL_WALL,
		MODEL_MAX
	}MODEL;
	typedef enum
	{
		/*�n��*/	TEX_FIELD_0, TEX_FIELD_1,
		/*��*/		TEX_WALL_0, TEX_WALL_1, TEX_WALL_2,
		/*��*/		TEX_RIVER_0, TEX_RIVER_1,
		TEXTURE_MAX
	}TEXTURE;
	CDungeon(int nPrioryity = DUNGEON_PRIORYITY) : CScene::CScene(nPrioryity) { m_nMapChip = NULL; m_p3DBG = NULL; };
	~CDungeon() {};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DrawEffect(void);
	void SetVersus(int nSelect);
	void SetDungeon(int nStage);
	void SetDungeon_Shop(int nStatge);
	bool Collision(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float fLengthX, float fLengthZ, bool &bRiver);
	void	InitBossBG(CScene3D::TEXTURE tex);
	void SetPractice(void);

	static	LPDIRECT3DTEXTURE9	*Load(TEXTURE tex);			//�e�N�X�`���̐���
	static void					UnLoad(void);				//�e�N�X�`���̔j��
	static void					LoadModel(MODEL model);		//���f���̐���
	static void					UnLoadModel(void);			//Model���
	void ShotCollision(CSceneBullet *pBullet);
	int GetShop(void) { return m_nShop; }
	void SetQuake(int nTime) { m_nQuake = nTime - (int)((float)m_nQuake / (float)(m_nQuake + nTime)); }
	void SetColBG(D3DXCOLOR col);
	void SetDamageBG(CScene::DRAW_TYPE shield, float fPerLife, bool bHit, int nID);

	CSceneDungeonBG *&GetpBG(void) { return m_pBG; }
	CScene3D		*&Getp3D(void) { return m_p3DBG; }
	bool			&GetbManager(void) { return m_bManager; }
private://*****************************************************************************
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTURE_MAX];		// �e�N�X�`���ւ̃|�C���^
		//���f��//*********************************************************************
	static MODEL_DRAW *m_Model_Draw[MODEL_MAX];					//���f���ւ̃|�C���^

	void InitDungeon(int nMemory);
	void SetDungeon_Rand(int nStatge);
	void SetDungeon_Boss(int nStatge);
	void SetShop_Item(D3DXVECTOR3 pos, int nPlus);

	void SetVersus0(void);
	void SetVersus1(void);
	void SetVersus2(void);

	void CDungeon::DrawChip(int& nVtx, CScene::DRAW_TYPE& DrawType, TEXTURE& Texture, D3DXVECTOR3& pos);
	void CDungeon::DrawChipModel(MODEL& model, CScene::DRAW_TYPE& DrawType, TEXTURE& Texture, D3DXVECTOR3& pos);
	void ChipPrepare(int nChip, D3DXVECTOR3 &pos0);
	void SetField(int nCheck);
	void SetExpand(int nCheck, int nType, int nAngle);
	void ConvertField(void);
	void SetObject(int nCount, CSceneModel::MODEL model);
	void SetEnemy(int nCount);
	void SetTrap(int nCount, int nType);
	
	//�ϐ��錾//***********************************************************************
	static	C2DAnim			*m_pFrontBG[MAP_MAX_EFFECT];	//�O���̔w�i�@�È�
	static	CNumber			*m_pTimer;		//�^�C�}�[
	static	CSceneDungeonBG	*m_pBG;			//�w�i�@�_
	CScene3D				*m_p3DBG;				//�{�X�w�i

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = {};		// ���_�o�b�t�@�ւ̃|�C���^
	TEXTURE					m_WallTex;				//�ǂ̉摜

	CSound::LABEL			m_BGM;					//���݂������Ă���BGM�̃��x��

	bool					m_bManager;				//�X���̐���
	int						m_nQuake;				//�n�k��F��
	int						m_nShop;				//�V���b�v�𐶐����邩�ǂ���
	int						m_nMaxX;				//���s�p
	int						m_nMemory;				//���v�̗e��
	int						**m_nMapChip;			//�`�b�v�^�C�v
};
#endif
