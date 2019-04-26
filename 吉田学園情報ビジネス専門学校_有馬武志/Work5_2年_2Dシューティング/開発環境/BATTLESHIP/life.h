//=============================================================================
//
// �̗͂̏��� [life.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _LIFE_H_
#define _LIFE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_LIFE			(200)		//���C�t�̏��
#define BAR_WIDTH_LIFE		(260)		//����
#define BAR_HEIGHT_LIFE		(50)		//�c��
#define NUM_TEXTURE_LIFE	(1)			//�g�p�e�N�X�`������
#define NUM_POLYGON_LIFE	(4)			//���_��
#define SUBTRACT_TIME		(25)		//���炷�J�E���g����

//=====================
//  CScene�̔h���N���X
//=====================
class CLife : CScene
{
public://�N�ł�������
	CLife();
	~CLife();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLife *Create();
	void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);
	static void AddLife(int nValue);
	int GetLife(void) { return m_Life[3].nLife; }
	
private:
	typedef struct 
	{
		D3DXVECTOR3 pos;		// ����̈ʒu
		D3DXCOLOR col;			// �F
		int nLife;				// ���݂̃��C�t
		float fLength;			// �o�[�̒���	[0:���݂̃��C�t�@1:�_���[�W�Ō�������]
		int nType;				// �e�N�X�`���̎�ށi-1�łȂ��j
	}Life;

	static LPDIRECT3DTEXTURE9 m_pTexture[NUM_TEXTURE_LIFE];	//���L�e�N�X�`���̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;
	static int m_nCntSubtraction;							//�o�[�����炵�n�߂�J�E���^
	static Life		m_Life[NUM_POLYGON_LIFE];				//�̗�
	static int m_nMaxLife;
};
#endif