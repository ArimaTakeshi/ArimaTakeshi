//=============================================================================
//
// ���b�V������ [mesh.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MESH_H_
#define _MESH_H_

#include "main.h"
#include "scene.h"
#include "motion.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define WALL_PLUS					(2.0f)		//�ǂ̔���̃v���X�l
#define MESH_PRIORITY				(1)			//���b�V���̗D�揇��
#define ORBIT_PRIORITY				(3)			//���b�V���̗D�揇��

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMesh : public CScene
{
public:
	typedef enum
	{
		TYPE_FIELD,		//�n��
		TYPE_WALL,		//��
		TYPE_CEILING,	//�V��
		TYPE_ORBIT,	//�I�[�r�b�g
		TYPE_MAX
	}TYPE;
	CMesh(int nPrioryity = 0) : CScene::CScene(nPrioryity) {};
	~CMesh() {};

	void	Set(TYPE type, D3DXVECTOR3 pos, int nVertical, int nCorss, bool bMesh);	//�Z�b�g����
	void	SetNor(void);	//�@���̃Z�b�g����

	void	SetWall(D3DXVECTOR3 *vtx);							//�ǃZ�b�g����
	bool	SetField(int *nDig, int nMaxDig, float *fHeight, bool bRoom);	//���Z�b�g����
	void	UpField(int *nMap, float fHeight);	//���v���X����
	HRESULT Init(void);
	void	Uninit(void);
	void	Draw(void);

	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }
	CScene::DRAW_TYPE &GetDrawType(void) { return m_DrawType; }

	static void MeshCollisionCeiling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &length);
	static bool MeshCollisionField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, bool &bJump);
	static void MeshCollisionWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection);
	static float FieldCollision(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3 WKpos, D3DXVECTOR3& pos, D3DXVECTOR3 &FNor);
	static int WallCollision(D3DXVECTOR3 Wall0, D3DXVECTOR3 Wall1, D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection);
	static bool FieldCheck(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3& pos);
	static int AngleCheck(float fAngle0, float fAngle1);
	void MeshCeling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLength);
	bool MeshField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &FNor, float& fLength, bool &bJump);
	void MeshWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection);

	int &GetnCross(void) { return m_nCross; }
	int &GetnVertical(void) { return m_nVertical; }
protected://*****************************************************************************
	LPDIRECT3DVERTEXBUFFER9 &GetVtxBuff(void) { return m_pVtxBuff; }
private://*****************************************************************************
	void WallPlus(D3DXVECTOR3& pos0, D3DXVECTOR3 &pos1, float& fLengthX, float& fLengthZ);
	void PlusNor(VERTEX_3D *pVtx, VERTEX_3D *pVtxL, VERTEX_3D *pVtxR);	//�@���̃Z�b�g����

		//�ϐ��錾//***********************************************************************
	CScene::DRAW_TYPE		m_DrawType;		// �`�悷����@(���Z�����Ȃ�)
	TYPE					m_Type;			//�^�C�v
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTex;		//�摜
	D3DXVECTOR3				m_pos;			//�ʒu
	D3DXVECTOR3				m_rot;			//����
	int						m_nVertical;	//�c�̕�����
	int						m_nCross;		//���̕�����
	int						m_nNumVertex;	//���_��
	int						m_nNumIdx;		//�C���f�b�N�X��
	int						m_nNumPolygon;	//�|���S����
	bool					m_bMesh;		//�����Ă���ʂ��������O����(����肩�E��肩)
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMeshOrbit : public CScene
{
public:
	CMeshOrbit(int nPrioryity = ORBIT_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_pmtxWorld = NULL;
		m_bDelete = NULL;
	};
	~CMeshOrbit() {};

	void	Set(D3DXMATRIX &mtxWorld, D3DXVECTOR3 length0, D3DXVECTOR3 length1, bool &bDelete, D3DXCOLOR col, CScene::TEXTURE tex);
	void	Update(void);
	void	Draw(void);
	void	ReSet(void);
	static void	ReSetAll(void);
	static void	Delete(void);
	void		BindTexture(LPDIRECT3DTEXTURE9 pTex) { m_pTex = pTex; }
	CScene::DRAW_TYPE &GetDrawType(void) { return m_DrawType; }

private://*****************************************************************************
	void	SetVtx(bool bAll);		//�ŐV�̒��_���v�Z���đ��
	void	SwapVtx(void);		//���_�̓���ւ�
	//�ϐ��錾//***********************************************************************
	CScene::DRAW_TYPE		m_DrawType;		// �`�悷����@(���Z�����Ȃ�)
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@
	LPDIRECT3DTEXTURE9		m_pTex;		//�摜
	int						m_nNumPolygon;	//�|���S����

	D3DXMATRIX		*m_pmtxWorld;	//�e�̃��[���h�}�g���b�N�X
	D3DXMATRIX		m_mtxWorld[2];	//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_posold;		//�O�̈ʒu
	D3DXCOLOR		m_col;			//�F
	int				m_nCross;		//���̕�����
	int				m_nReset;		//���Z�b�g���ꂽ�ꍇ�̃J�E���g�p
	float			m_fPlusCol;		//����䂭�F
	float			m_fUV;			//����䂭�F
	float			m_fEnd;			//�j���܂ł̌o�ߎ���
	bool			*m_bDelete;		//�����锻��
};
#endif