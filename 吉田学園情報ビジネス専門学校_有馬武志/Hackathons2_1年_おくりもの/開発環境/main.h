#pragma once
//=========================================================================================================//
//
// DirectX���^���� [main.h]
// Author : Ryo Sugimoto
//
//=========================================================================================================//
#ifndef _MAIN_H_
#define _MAIN_H_

//*********************************************************************************************************//
// �C���N���[�h�t�@�C��
//*********************************************************************************************************//
#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	//�r���h���̌x���Ώ��p�}�N��
#include "dinput.h"					//���͏����ɕK�v
#include "xaudio2.h"				//�T�E���h�����ŕK�v

//*********************************************************************************************************//
// ���C�u�����̃����N
//*********************************************************************************************************//
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_GAMEX			(800)

//*********************************************************************************************************//
// �\���̒�`
//*********************************************************************************************************//
typedef enum
{//���[�h�̏��
	MODE_TITLE = 0,	//�^�C�g��
	MODE_RANKING,	//�����L���O
	MODE_WATCH,		//�Q�[���ϐ���
	MODE_TUTORIAL,	//�`���[�g���A��
	MODE_GAME,		//�Q�[�����C��
	MODE_RESULT,	//���U���g
	MODE_MAX

}MODE;

typedef enum
{//window�̕\�����
	WINDOWSTATE_NORMAL = 0,			//�����X�V���Ȃ�
	WINDOWSTATE_VIBRATION,			//�U��
	WINDOWSTATE_LEVELUP,			//���x���A�b�v
	WINDOWSTATE_STEALTH,			//���񂾂�s������->�ʏ�ɂȂ�
	WINDOWSTATE_FADEIN,				//
	WINDOWSTATE_FADEOUT,			//
	WINDOWSTATE_FLASH,				//�_��
	WINDOWSTATE_FLASH2,				//���_��
	WINDOWSTATE_SCROLL0,			//�c�X�N���[��
	WINDOWSTATE_SCROLL1,			//�΃X�N���[�� ������
	WINDOWSTATE_SCROLL2,			//��SCROLL
	WINDOWSTATE_SELECTON,			//�I������Ă�����
	WINDOWSTATE_SELECTOFF,			//�I������Ă��Ȃ����
	WINDOWSTATE_WALL,				//��
	WINDOWSTATE_BG,					//�X�N���[���ɂ����W�ύX
	WINDOWSTATE_FIELD,				//�n��
	WINDOWSTATE_LIFEGAGE,				//�E���獶�֌���Q�[�W
	WINDOWSTATE_MAXLIFEGAGE,			//�Q�[�W�g
	WINDOWSTATE_AUTOLIFEGAGE,			//�ォ�瑝�����Ă���GAGE
	WINDOWSTATE_MAXEXPGAGE,			//�ォ�瑝�����Ă���GAGE
	WINDOWSTATE_AUTOEXPGAGE,			//�ォ�瑝�����Ă���GAGE
	WINDOWSTATE_EXPGAGE,			//GAGE
	WINDOWSTATE_PLAYER,				//���@�̃p�^�[���ɂ��ύX
	WINDOWSTATE_MAX,

}WINDOWSTATE;

typedef enum
{//window�̎g�p���
	WINDOWUSE_NORMAL = 0,
	WINDOWUSE_RESIDUALAIRPORT,	//�c�@
	WINDOWUSE_SELECT,			//�I��
	WINDOWUSE_GUARD,			//GUARD
	WINDOWUSE_LOAD,				//�ǂݍ��݉�ʂ�
	WINDOWUSE_FONT,				//�������͎� ����
	WINDOWUSE_RANKING,			//RANKING�̎��Ɏg�p�@��Փx�̃��S
	WINDOWUSE_RANKNUMBER,		//RANKING�̎��Ɏg�p�@����
	WINDOWUSE_PLAYER,			//�v���C���[�̏ꍇ
	WINDOWUSE_ENEMY,			//BOSS�G�l�~�[�̏ꍇ
	WINDOWUSE_MAX,

}WINDOWUSE;

typedef enum
{//�X�R�A�̏��
	SCORESTATE_NONE = 0,
	SCORESTATE_FADE,
	SCORESTATE_DELETE,
	SCORESTATE_RANKDOWN,
	SCORESTATE_SET,
	SCORESTATE_RANKSET,			//�����L���O���E���獶�֗���ăZ�b�g
	SCORESTATE_Damage,

}SCORESTATE;
typedef struct
{//�X�R�A�̍\����
	D3DXVECTOR3 pos;			//�ꏊ
	D3DXCOLOR	col;			//�J���[
	int			g_nScore;		// �X�R�A
	SCORESTATE	state;			//���
	float		fCntstate;		//��ԊǗ��p
	bool		bUse;			//�g���Ă邩�g���ĂȂ���

}SCORE;

typedef struct
{
	D3DXVECTOR3 pos;			//���_���W
	float		rhw;			//1.0f�ŌŒ�
	D3DCOLOR	col;			//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W

}VERTEX_2D;

typedef enum
{//�����̏��
	FONTSTATE_NONE = 0,
	FONTSTATE_DELETE,
	FONTSTATE_RANKDOWN,
	FONTSTATE_RANKSET,		//�����L���O���̃Z�b�g
	FONTSTATE_RANKDELETE,	//�����L���O���̃f���[�g

}FONTSTATE;
typedef struct
{
	FONTSTATE	state;		//�����̏��
	D3DCOLOR	col;		//�J���[
	RECT		rect;		//�����̕\���͈�
	int			nWide;
	int			nHeight;
	int		fCntState;	//��ԊǗ��p
	char		aStr[256];	//�����̗�
	bool		bUse;		//�g�por���g�p

}Font;

typedef struct
{//���U���g�Ŏg��
	int nCntScore;		//for�ŉ񂳂Ȃ����߃��[�J�����Ə������ɍ���
	int nCntResult;		//���ԃJ�E���g
	int nRankin;		//�n�C�X�R�A���̏��ʕۑ� ���O���͎��g�p
	int nWideFont;		//50���\�̉��I�𕔕�
	int nHightFont;		//50���\�̏c�I�𕔕�
	char aStr[25];		//���O���͂̂���

}Result;

typedef struct
{
	int colR;
	int colG;
	int colB;
	int colA;
}COLLAR;

//*********************************************************************************************************//
// �v���g�^�C�v�錾
//*********************************************************************************************************//
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE *GetMode(void);
HWND *GethWnd(void);

//*********************************************************************************************************//
// �v���g�^�C�v�錾
//*********************************************************************************************************//
void InitFont(void);
void UninitFont(void);
void UpdateFont(void);
void DrawFont(void);
void SetFont(RECT rect, D3DCOLOR col, char *aStr, int nNumber, int nWide, int nHeight, FONTSTATE state);
void ChangeFont(bool bUse, char *aStr, int nNumber, FONTSTATE state, D3DCOLOR col);
void BreakFont(void);
int *GetSetFont(void);
void SetFontDamage(RECT rect, D3DCOLOR col, char *aStr, int nWide, int nHeight, FONTSTATE state);
void FontScroll(D3DXVECTOR3 move);

//*********************************************************************************************************//
// �v���g�^�C�v�錾 �`���[�g���A��
//*********************************************************************************************************//
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

//*********************************************************************************************************//
// �v���g�^�C�v�錾 ���U���g
//*********************************************************************************************************//
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�w�i
//*********************************************************************************************************//
void InitWindow(void);
void UninitWindow(void);
void UpdateWindow(void);
void DrawWindow(void);
void SetWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntUse, int nEnemy, WINDOWSTATE state, WINDOWUSE use);
void BreakWindow(void);
bool BreakAirport(void);
void SelectWindow(int nNumber);
void BackWindow(int nNumber);
void FontWindowMove(int nWide, int nHeight);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�w�i
//*********************************************************************************************************//
void InitBGWindow(void);
void UninitBGWindow(void);
void UpdateBGWindow(void);
void DrawBGWindow(void);
void SetBGWindow(D3DXVECTOR3 pos, COLLAR col, float fSpeed, float fPos, int nLengthX, int nLengthY, int nType, WINDOWSTATE state);
void BreakBGWindow(void);
void BGScroll(D3DXVECTOR3 move);

//*********************************************************************************************************//
// �v���g�^�C�v�錾�@�t�F�[�h�̃|���S���\������
//*********************************************************************************************************//
void InitFadeWindow(void);
void UninitFadeWindow(void);
void UpdateFadeWindow(void);
void DrawFadeWindow(void);
void SetFadeWindow(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, int nCntUse, WINDOWSTATE state, WINDOWUSE use);
void LoadBreakWindow(void);

#endif