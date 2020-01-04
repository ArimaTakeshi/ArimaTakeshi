//=============================================================================
//
// �Q�[�W�̏��� [gauge.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_GAUGE			(200)		//���C�t�̏��
#define BAR_WIDTH_GAUGE		(300)		//����
#define BAR_HEIGHT_GAUGE	(20)		//�c��
#define NUM_TEXTURE_GAUGE	(1)			//�g�p�e�N�X�`������
#define NUM_POLYGON_GAUGE	(4)			//���_��
#define GAUGE_SUBTRACT_TIME	(10)		//���炷�J�E���g����
#define GAUGE_DIAMOND		(15)		//�Q�[�W�̊p�x

//=====================
//  CScene�̔h���N���X
//=====================
class CGauge : CScene
{
public://�N�ł�������
	CGauge();
	~CGauge();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGauge *Create(D3DXVECTOR3 pos);
	void MakeVertexGauge(LPDIRECT3DDEVICE9 pDevice);
	static void AddGauge(float fValue);
	float GetGauge(void) { return m_aGauge[3].fGauge; }
	static void SetGaugeOnOff(bool bGaugeOnOff) { m_bGaugeOnOff = bGaugeOnOff; }
	static bool GetGaugeOnOff(void) { return m_bGaugeOnOff; }
	static bool GetGaugeDownOn(void) { return m_bGaugeDownOn; }
	static void SetGaugeDownOn(bool bGaugeDownOn) { m_bGaugeDownOn = bGaugeDownOn; }
	static void SetRecastTime(int nGageRecastTime) { m_nGaugeRecastTime = nGageRecastTime; }
	static bool GetGaugeActionFade(void) { return m_bGaugeActionFade; }
	static void SetGaugeActionFade(bool bGaugeActionFade) { m_bGaugeActionFade = bGaugeActionFade; }

	//��ꂽ��Ԃ�n���֐�
	static bool GetTired(void) { return m_bTired; }
	static void SetTired(bool bTired) { m_bTired = bTired; }

	//�J���[�ύX�p
	void ColorUpdate(float fCntColor);
	void ColorInit(void);

private:
	typedef struct 
	{
		D3DXVECTOR3 pos;		// ����̈ʒu
		D3DXCOLOR col;			// �F
		float fGauge;			// ���݂̃��C�t
		float fLength;			// �o�[�̒���	[0:���݂̃��C�t�@1:�_���[�W�Ō�������]
		int nType;				// �e�N�X�`���̎�ށi-1�łȂ��j
	}Gauge;

	static LPDIRECT3DTEXTURE9		m_pTexture[NUM_TEXTURE_GAUGE];		//���L�e�N�X�`���̃|�C���^
	static LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;							//���_�o�b�t�@�̃|�C���^
	static int						m_nCntSubtraction;					//�o�[�����炵�n�߂�J�E���^
	static Gauge					m_aGauge[NUM_POLYGON_GAUGE];		//�̗�
	static int						m_nMaxGauge;						//�Q�[�W�̍ő�
	D3DXVECTOR3						m_pos;								//�ʒu
	static bool						m_bGaugeOnOff;						//�Q�[�W�������Ă�����
	static bool						m_bGaugeDownOn;						//�Q�[�W�����炷���߂�ONoFF
	static int						m_nGaugeRecastTime;					//�Q�[�W�̃��L���X�g�^�C��
	static bool						m_bGaugeActionFade;					//�Q�[�W�����A�N�V�����t�F�[�h
	float							m_fCntColor;						//�J���[��_�ł�����Ƃ��̂���
	static bool						m_bTired;							//��ꂽ���

};
#endif