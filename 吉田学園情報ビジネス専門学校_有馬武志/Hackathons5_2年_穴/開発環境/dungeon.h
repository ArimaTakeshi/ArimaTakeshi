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
#include "2DPolygon.h"
#include "3DPolygon.h"
#include "Number.h"
#include "motion.h"
#include "enemy.h"
class	CMesh;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define DUNGEON_PRIORYITY	(0)
#define MAP_SIZE		(80)
#define FIELD_SPLIT		(3)
#define FIELD_STRDOWN	(2)
#define FIELD_NUMDOWN	(1 + FIELD_STRDOWN)
#define FIELD_DOWN		(-50.0f)
#define CHIP_SIZE		(300.0f)
#define FIELD_SIZE		((float)(CHIP_SIZE / FIELD_SPLIT))
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CDungeon : public CScene
{
public:
	typedef enum
	{
		TYPE_RAND,
		TYPE_BOSS,
		TYPE_MAX
	}TYPE;
	CDungeon(int nPrioryity = DUNGEON_PRIORYITY) : CScene::CScene(nPrioryity) { };
	~CDungeon() {};

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
	void SetDungeon_Rand(void);
	void SetDungeon_Boss(void);
	void InitDungeon(void);
	void ChangeMap(TYPE type);

private://*****************************************************************************
	//void SetDungeon_Boss(int nStatge);

	void SetMesh(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLength, float fHeight, CMesh *pField, CMesh *pCeiling);
	void SetDig(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLengthX, int nLengthZ, float fHeight, float fPHeight, int nChip, CMesh *pField, CMesh *pCeiling);
	void SpinDig(int &nRot, int &nLengthZ, int &nLengthX);
	void SetRoom(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling);
	void SetRoad(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling);
	void SettingRoom(float *fRoomC, int *nCntRoom, float fPos, float fRot, float fHeight, float fState);
	void SettingRoad(float *fRoadC, int *nCntRoad, float fPos, float fRot, float fHeight);

	float ChangeRot(int &nRot);
	int SetWall(int *nMap);

	void SetPpos(D3DXVECTOR3 pos);					//�v���C���[�̈ʒu�ύX
	void SetGpos(D3DXVECTOR3 pos);					//�S�[���n�_�ݒu
	void SetObjRoom(D3DXVECTOR3 pos);				//������
	void SetObjRoom2(D3DXVECTOR3 pos, float fRot);	//������
	void SetObjRoad(D3DXVECTOR3 pos);				//�ʘH�p
	void SetObjEntrance(D3DXVECTOR3 pos);			//����
	void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE Mtype, CEnemy::TYPE Etype);					//�G�l�~�[�̔z�u
	
	//�ϐ��錾//***********************************************************************
	bool			m_bEnd;		//����������I���������ǂ���
	CSound::LABEL	m_BGM;		//���݂������Ă���BGM�̃��x��
	int				m_nLevel;
	int				m_nQuake;	//�n�k��F��

	TYPE			m_Type;			//�؂�ւ�����}�b�v
	float			m_fCntPlus;		//�}�b�v�؂�ւ��p�J�E���g
	float			m_fCntState;	//�}�b�v�؂�ւ��p�J�E���g
};
#endif
