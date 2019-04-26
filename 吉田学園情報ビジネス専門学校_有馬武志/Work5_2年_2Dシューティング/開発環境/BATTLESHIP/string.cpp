//=============================================================================
//
// �t�H���g�̏��� [string.cpp]
// Author : �L�n�@���u
//
//=============================================================================
#include "string.h"
#include "main.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STRING_FILE	"data/string.txt"		// ������̏����i�[����t�@�C��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CString::CString()
{
	m_aString[MAX_STRING];			// ������̏��
	m_cSymbol;						// �L���u:�v�p
	m_aButton[TYPE_MAX];			// �Ή��L�[��\��

	// ������̏��̏�����
	for (int nCntString = 0; nCntString < MAX_STRING; nCntString++)
	{
		m_aString[nCntString].m_cString[0] = {};
		m_aString[nCntString].m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aString[nCntString].m_nFont = 0;
		m_aString[nCntString].m_rect = { 0,0,0,0 };	// { x, y, ����, �� }
		m_aString[nCntString].m_bUse = false;
		m_aString[nCntString].m_bDisplay = false;
		m_aButton[nCntString] = m_aString[nCntString];
		m_pFont[nCntString] = {};			// �t�H���g�ւ̃|�C���^
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CString::~CString()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CString::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ������̏��̏�����
	for (int nCntString = 0; nCntString < MAX_STRING; nCntString++)
	{
		m_aString[nCntString].m_cString[0] = '\0';
		m_aString[nCntString].m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_aString[nCntString].m_nFont = 0;
		m_aString[nCntString].m_rect = { 0,0,0,0 };	// { x, y, ����, �� }
		m_aString[nCntString].m_bUse = false;
		m_aString[nCntString].m_bDisplay = false;
	}
	
	for (int nCntString = 0; nCntString < TYPE_MAX; nCntString++)
	{
		m_aButton[nCntString] = m_aString[0];
	}

	m_cSymbol = m_aString[0];
	m_cSymbol.m_cString[0] = ':';
	m_cSymbol.m_bUse = true;

	//������t�H���g�̏�����
	for (int nCntString = 0; nCntString < MAX_FONT; nCntString++)
	{
		D3DXCreateFont(pDevice,
			18,                     // ��������
			8,                      // ������
			0,						// �t�H���g�X�^�C��(����)
			0,						// �~�b�v�}�b�v���f���̐�
			FALSE,                  // �Α̂ɂ��邩�ǂ���
			MONO_FONT,				// �����Z�b�g(����)
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH,
			"Arial Black",          //�t�H���g�̎��
			&m_pFont[nCntString]);

	}

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CString::Uninit(void)
{
	for (int nCntString = 0; nCntString < MAX_FONT; nCntString++)
	{// �J��
		if (NULL != m_pFont[nCntString])
		{
			m_pFont[nCntString]->Release();
			m_pFont[nCntString] = NULL;
		}
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CString::Update(void)
{
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void CString::Draw(void)
{
	for (int nCntString = 0; nCntString < MAX_STRING; nCntString++)
	{// �ő吔��
		if (true == m_aString[nCntString].m_bUse)
		{
			m_cSymbol.m_rect = { 140, 10 + (nCntString * 20), 0, 0 };

			//������T�C�Y���v�Z
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aString[nCntString].m_cString[0],	// �\�����镶����
				-1,										// �\���T�C�Y(-1�őS��)
				&m_aString[nCntString].m_rect,			// �\���͈�
				DT_CALCRECT,							// �\���͈͂ɒ���
				NULL);									// �F

			//���̃T�C�Y�Ń����_�����O
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aString[nCntString].m_cString[0],
				-1,										//�\���T�C�Y(-1�őS��)
				&m_aString[nCntString].m_rect,			//�\���͈�
				DT_LEFT | DT_BOTTOM,					//���l�߂ŗ��[����
				m_aString[nCntString].m_col);			//�F

//�L��������-----------------------------------------------------------------------------------
			//������T�C�Y���v�Z
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_cSymbol.m_cString[0],				// �\�����镶����
				-1,										// �\���T�C�Y(-1�őS��)
				&m_cSymbol.m_rect,						// �\���͈�
				DT_CALCRECT,							// �\���͈͂ɒ���
				NULL);									// �F

			//���̃T�C�Y�Ń����_�����O
			m_pFont[m_aString[nCntString].m_nFont]->DrawText(
				NULL,
				&m_cSymbol.m_cString[0],
				-1,										//�\���T�C�Y(-1�őS��)
				&m_cSymbol.m_rect,						//�\���͈�
				DT_LEFT | DT_BOTTOM,					//���l�߂ŗ��[����
				m_cSymbol.m_col);						//�F
		}
		if (true == m_aButton[nCntString].m_bUse)
		{
			//������T�C�Y���v�Z
			m_pFont[m_aButton[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aButton[nCntString].m_cString[0],	// �\�����镶����
				-1,										// �\���T�C�Y(-1�őS��)
				&m_aButton[nCntString].m_rect,			// �\���͈�
				DT_CALCRECT,							// �\���͈͂ɒ���
				NULL);									// �F

			//���̃T�C�Y�Ń����_�����O
			m_pFont[m_aButton[nCntString].m_nFont]->DrawText(
				NULL,
				&m_aButton[nCntString].m_cString[0],
				-1,										//�\���T�C�Y(-1�őS��)
				&m_aButton[nCntString].m_rect,			//�\���͈�
				DT_LEFT | DT_BOTTOM,					//���l�߂ŗ��[����
				m_aButton[nCntString].m_col);			//�F
		}
	}
}
//=============================================================================
// ������̐ݒ�
//=============================================================================
void CString::SetString(char *str, RECT rect, int nFont, D3DXCOLOR col)
{
	/***********************************************************
	*
	*	�K���u�`�揈���v�ŌĂ�ł�������
	*
	************************************************************/

	//������T�C�Y���v�Z
	m_pFont[nFont]->DrawText(
		NULL,
		&str[0],				//�\�����镶����
		-1,						//�\���T�C�Y(-1�őS��)
		&rect,					//�\���͈�
		DT_CALCRECT,			//�\���͈͂ɒ���
		NULL);					//�F

								//���̃T�C�Y�Ń����_�����O
	m_pFont[nFont]->DrawText(
		NULL,
		&str[0],				//�\�����镶����
		-1,						//�\���T�C�Y(-1�őS��)
		&rect,					//�\���͈�
		DT_LEFT | DT_BOTTOM,	//���l�߂ŗ��[����
		col);					//�F
}
