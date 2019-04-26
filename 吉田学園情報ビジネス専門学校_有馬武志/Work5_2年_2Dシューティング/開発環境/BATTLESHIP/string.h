//=============================================================================
//
// ���C������ [string.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _STRING_H_
#define _STRING_H_

#include "main.h"
#include <string.h>		// ��������R�s�[����̂ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_FONT	(1)						// �t�H���g�̐ݒ�
#define MAX_STRING	(32)					// ������̍ő吔

//=====================
// ��{�N���X
//=====================
class CString
{
public:
	typedef enum
	{
		TYPE_MODE = 0,
		TYPE_SAVE_FILE,
		TYPE_NUM,
		TYPE_SELECT,
		TYPE_MAX
	}STRIG_TYPE;

	CString();										//�R���X�g���N�^
	~CString();										//�f�X�g���N�^
	HRESULT Init();									//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
	void SetString(char *str, RECT rect, int nFont, D3DXCOLOR col);		// �`�揈���ŌĂ�

private:
	typedef struct
	{
		char			m_cString[64];				//�\�����镶����
		D3DXCOLOR		m_col;						//�F
		RECT			m_rect;						//�����̕\���͈�
		int				m_nFont;					//�g���t�H���g
		bool			m_bUse;						//�g���Ă��邩���Ȃ���
		bool			m_bDisplay;					//�\������\��
	}String;

	String			m_aString[MAX_STRING];			//������̏��
	String			m_cSymbol;						//�L���u:�v�p
	String			m_aButton[TYPE_MAX];			//�Ή��L�[��\��
	LPD3DXFONT		m_pFont[MAX_FONT];			//�t�H���g�ւ̃|�C���^

};
#endif

