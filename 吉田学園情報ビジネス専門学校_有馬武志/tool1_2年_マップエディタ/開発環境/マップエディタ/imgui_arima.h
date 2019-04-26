//=============================================================================
//
// imgui�̏��� [imgui.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _IMGUI_ARIMA_H_
#define _IMGUI_ARIMA_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=====================
//  ��{�N���X
//=====================
class CImgui_Arima
{
public://�N�ł�������
	CImgui_Arima();
	~CImgui_Arima();
	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DeviceObjects(HRESULT hResult, LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS d3dpp);

	//�E�B���h�E
	static IMGUI_API void	ShowObjectWindow(bool * p_open = NULL);		//�ڍאݒ�I�u�W�F�N�g�E�B���h�E
	static IMGUI_API void	ShowFieldWindow(bool * p_open = NULL);		//�ڍאݒ�I�u�W�F�N�g�E�B���h�E
	static IMGUI_API void	ShowWallWindow(bool * p_open = NULL);		//�ڍאݒ�I�u�W�F�N�g�E�B���h�E
	
	//���[�h�ύX���̒l
	static int			GetFillMode(void) { return m_nFillMode; }
	static int			GetPlayerMode(void) { return m_nPlayerMode; }
	static int			GetSetMode(void) { return m_nSetMode; }

	static void			SetFillMode(int nFillMode) { m_nFillMode = nFillMode; }
	static void			SetPlayerMode(int nPlayerMode) { m_nPlayerMode = nPlayerMode; }
	static void			SetSetMode(int nSetMode) { m_nSetMode = nSetMode; }

	//�I�u�W�F�N�g�̏���n��
	static D3DXVECTOR3	GetObjectPos(void) { return m_ObjectPos; }
	static D3DXVECTOR3	GetObjectRot(void) { return m_ObjectRot; }
	static int			GetObjectType(void) { return m_nObjectType; }
	static int			GetObjectClidked(void) { return m_nObjectClicked; }
	static bool			GetObjectCollition(void) { return m_bObjectCollition; }
	static bool			GetObjectSet(void) { return m_bSetObject; }
	//�t�B�[���h�̏���n��
	static D3DXVECTOR3	GetFieldPos(void) { return m_FieldPos; }
	static D3DXVECTOR4	GetFieldVtx(void) { return m_FieldVtxHeight; }
	static int			GetFieldWD(void) { return m_nFieldWidthDivide; }
	static int			GetFieldHD(void) { return m_nFieldHeightDivide; }
	static int			GetFieldType(void) { return m_nFieldTextureType; }
	static int			GetFieldWL(void) { return m_nFieldWidthLength; }
	static int			GetFieldHL(void) { return m_nFieldHeightLength; }
	static int			GetFieldClidked(void) { return m_nFieldClicked; }
	static bool			GetFeildSet(void) { return m_bSetField; }
	//�E�H�[���̏���n��
	static D3DXVECTOR3	GetWallPos(void) { return m_WallPos; }
	static D3DXVECTOR3	GetWallRot(void) { return m_WallRot; }
	static int			GetWallWL(void) { return m_nWallWidthLength; }
	static int			GetWallHL(void) { return m_nWallHeightLength; }
	static int			GetWallType(void) { return m_nWallTextureType; }
	static int			GetWallClicked(void) { return m_nWallClicked; }
	static bool			GetWallSet(void) { return m_bSetWall; }

private:
	//�I�u�W�F�N�g�̐ݒ�
	static D3DXVECTOR3	m_ObjectPos;			//��Q���̈ʒu
	static D3DXVECTOR3	m_ObjectRot;			//��Q���̌���
	static int			m_nObjectType;			//��Q���̎��
	static int			m_nObjectClicked;		//�ۑ��̍ۂɎg��
	static bool			m_bObjectCollition;		//��Q���̓����蔻��
	static bool			m_bSetObject;			//��Q����ݒu����Ƃ�

	//�t�B�[���h�̐ݒ�
	static D3DXVECTOR3	m_FieldPos;				//�n�ʂ̈ʒu
	static D3DXVECTOR4	m_FieldVtxHeight;		//�n�ʂ̒��_�̍���
	static int			m_nFieldWidthDivide;	//���̕�����
	static int			m_nFieldHeightDivide;	//�c�̕�����
	static int			m_nFieldTextureType;	//���
	static int			m_nFieldWidthLength;	//���̒���
	static int			m_nFieldHeightLength;	//�c�̍���
	static int			m_nFieldClicked;		//�ۑ��̍ۂɎg��
	static bool			m_bSetField;			//�n�ʂ�ݒu����Ƃ�

	//�E�H�[���̐ݒ�
	static D3DXVECTOR3	m_WallPos;				//�ǂ̈ʒu
	static D3DXVECTOR3	m_WallRot;				//�ǂ̌���
	static int			m_nWallWidthLength;		//���̒���
	static int			m_nWallHeightLength;	//�c�̒���
	static int			m_nWallTextureType;		//���
	static int			m_nWallClicked;			//�ۑ��̍ۂɎg��
	static bool			m_bSetWall;				//�n�ʂ�ݒu����Ƃ�

protected:
	//���[�h�ύX���̒l
	static int			m_nFillMode;
	static int			m_nPlayerMode;
	static int			m_nSetMode;
};
#endif