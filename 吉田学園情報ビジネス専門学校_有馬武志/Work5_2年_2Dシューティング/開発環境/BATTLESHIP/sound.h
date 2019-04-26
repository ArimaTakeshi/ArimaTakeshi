//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �L�n ���u
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//=====================
//  ��{�N���X
//=====================
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_TITLEBGM000 = 0,		// �^�C�g����BGM
		SOUND_LABEL_TUTORIALBGM000,			// �`���[�g���A����BGM
		SOUND_LABEL_GAMEBGM000,				// �Q�[����BGM
		SOUND_LABEL_GAMEBGM001,				// �g��BGM
		SOUND_LABEL_PLAYERBGM000,			// �D�̉���BGM
		SOUND_LABEL_GAMEOVER,				// �Q�[���I�[�o�[��BGM
		SOUND_LABEL_WINERBGM,				// �������ꍇ��BGM
		SOUND_LABEL_ENTERSE,				// ���艹
		SOUND_LABEL_PAUSE000,				// �|�[�Y���J����
		SOUND_LABEL_PAUSE001,				// �|�[�Y����鉹
		SOUND_LABEL_PAUSE002,				// �|�[�Y�̃��j���[���ړ����鉹
		SOUND_LABEL_CHANGEWEAPON,			// ����̐؂�ւ��̉�
		SOUND_LABEL_PLAYERCANNON,			// �v���C���[��C��
		SOUND_LABEL_ENEMYCANNON,			// �G��C��
		SOUND_LABEL_SKYCANNON,				// �΋�C��
		SOUND_LABEL_TORPEDO,				// �����C��
		SOUND_LABEL_EXPLOSION000,			// ������
		SOUND_LABEL_GO,						// �����I�������I
		SOUND_LABEL_LOSE,					// ��������Ȃ͂��ł�
		SOUND_LABEL_MIZUBASIRA,				// ����Cooperation
		SOUND_LABEL_COOPERATION,			// �����̋���
		SOUND_LABEL_HIKOUKI,				// �퓬�@�̒ʉ߉�
		SOUND_LABEL_MAX
	}SOUND_LABEL;
	
	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label); //�Q�[���̏������߂��@
	void StopSound(SOUND_LABEL label);	  //�������O�������ăX�g�b�v��������
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	typedef struct
	{
		char *m_pFilename;		// �t�@�C����
		int m_nCntLoop;			// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	IXAudio2				*m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice	*m_pMasteringVoice;						// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice	*m_apSourceVoice[SOUND_LABEL_MAX];			// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX];		// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX];			// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		//-1�̓��[�v�@�@0�͒P��
		//BGM�ꗗ
		{ "data/BGM/title000BGM.wav", -1 },
		{ "data/BGM/tutorial000BGM.wav", -1 },
		{ "data/BGM/game000BGM.wav", -1 },	
		{ "data/BGM/game001BGM.wav", -1 },
		{ "data/BGM/shipmoveBGM.wav", -1 },
		{ "data/BGM/gameoverBGM.wav", -1 },
		{ "data/BGM/winerBGM.wav", -1 },
		//SE�ꗗ
		{ "data/SE/kettei000SE.wav", 0 },
		{ "data/SE/pause000SE.wav", 0 },
		{ "data/SE/pause001SE.wav", 0 },
		{ "data/SE/pause002SE.wav", 0 },
		{ "data/SE/changeweaponSE.wav", 0 },
		{ "data/SE/cannonplayerSE.wav", 0 },
		{ "data/SE/cannonenemySE.wav", 0 },
		{ "data/SE/skycannonSE.wav", 0 },
		{ "data/SE/torpedoSE.wav", 0 },
		{ "data/SE/explosion000SE.wav", 0 },
		{ "data/SE/goSE.wav", 0 },
		{ "data/SE/loseSE.wav", 0 },
		{ "data/SE/mizubesiraSE.wav", 0 },
		{ "data/SE/cooperationSE.wav", 0 },
		{ "data/SE/hikouki1.wav", 0 },
	};
};

#endif