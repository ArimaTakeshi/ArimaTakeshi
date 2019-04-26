//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSound
{// �T�E���h�N���X
public:
	typedef enum
	{// �T�E���h�t�@�C��
		/* *** BGM *** */
		LABEL_TITLE000	, LABEL_SELECT000	, LABEL_PRACTICE000	,
		LABEL_CLEAR000	, LABEL_OVER000		, LABEL_RESULT000	,
		LABEL_FIELD000	, LABEL_BOSS000		,
		/* *** SE *** */
		LABEL_ATTACK000	, LABEL_BOOST000	, LABEL_CHARGE000	,
		LABEL_CRITICAL	, LABEL_DOWN		, LABEL_GUARD		,
		LABEL_HIT000	, LABEL_LANDING		, LABEL_LOCKCANSEL	, LABEL_LOCKON	,
		LABEL_PARIS		, LABEL_STEP		, LABEL_DEAD		, LABEL_OVER	,

		LABEL_RETURN	, 

		LABEL_Correct	, LABEL_Damage		, LABEL_Incorrect	, LABEL_Question,
		LABEL_Stab0		, LABEL_Stab1, LABEL_Stab2, LABEL_Stab3,
		LABEL_StabMiss	,
		LABEL_MAX	// ����
	} LABEL;

	CSound();
	~CSound() {};
	HRESULT Init(HWND hWnd);
	void	Uninit(void);
	HRESULT Play(LABEL label);
	void	Stop(LABEL label);
	void	Stop(void);
	void	CountUp(void);
	void	CountReset(LABEL label) { m_aSoundParam[label].nCntFrame = 0; };
private:
	typedef struct
	{// �p�����[�^
		char *pFilename;	// �t�@�C����
		int  nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
		int  nPlayNext;		//���̍Đ��܂łɕK�v��F��
		int  nCntFrame;		//���݂�F�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice	*m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	PARAM m_aSoundParam[LABEL_MAX] =
	{
		/* *** BGM *** */
		{ "data/BGM/MODE/Title.wav", -1, 0 },						// �^�C�g��BGM
		{ "data/BGM/MODE/Select.wav", -1, 0 },						// �Z���N�gBGM
		{ "data/BGM/MODE/Tutorial.wav", -1, 0 },					// �`���[�g���A��BGM

		{ "data/BGM/MODE/GameClear.wav", -1, 0 },					// �N���ABGM
		{ "data/BGM/MODE/GameOver.wav", -1, 0 },					// �I�[�o�[BGM
		{ "data/BGM/MODE/GameOver.wav", -1, 0 },					// �I�[�o�[BGM

		{ "data/BGM/MODE/Field.wav", -1, 0 },						// �t�B�[���hBGM
		{ "data/BGM/MODE/Boss.wav", -1, 0 },						// �{�XBGM

		/* *** SE *** */
		{ "data/SE/BATTLE/Attack.wav", 0, 5 },						// �U��
		{ "data/SE/BATTLE/Boost.wav", 0, 30 },						// �u�[�X�g
		{ "data/SE/Alert.wav", 0, 5 },						// �`���[�W
		{ "data/SE/BATTLE/Critical.wav", 0, 5 },					// �N���e�B�J��
		{ "data/SE/BATTLE/Down.wav", 0, 5 },						// �_�E��
		{ "data/SE/BATTLE/Guard.wav", 0, 5 },						// �K�[�h
		{ "data/SE/BATTLE/Hit.wav", 0, 5 },							// �q�b�g
		{ "data/SE/BATTLE/landing.wav", 0, 5 },						// ���n
		{ "data/SE/BATTLE/LockCancel.wav", 0, 10 },					// ���b�N�L�����Z��
		{ "data/SE/BATTLE/LockOn.wav", 0, 10 },						// ���b�N�I��
		{ "data/SE/BATTLE/Paris.wav", 0, 5 },						// �p���B
		{ "data/SE/BATTLE/Step.wav", 0, 5 },						// �X�e�b�v
		{ "data/SE/BATTLE/Dead.wav", 0, 5 },						// ���S
		{ "data/SE/BATTLE/Over.wav", 0, 5 },						// ����
		{ "data/SE/SELECT/Return.wav", 0, 5 },						// ����

		{ "data/SE/Correct.wav", 0, 5 },						// ����
		{ "data/SE/VOICE/Sword/23_nekketsu_down.wav", 0, 5 },						// ����
		{ "data/SE/Incorrect.wav", 0, 5 },						// ����
		{ "data/SE/Question.wav", 0, 5 },						// ����
		{ "data/SE/VOICE/Sword/07_nekketsu_attack.wav", 0, 5 },						// ����
		{ "data/SE/VOICE/Sword/08_nekketsu_attack.wav", 0, 5 },						// ����
		{ "data/SE/VOICE/Sword/09_nekketsu_attack.wav", 0, 5 },						// ����
		{ "data/SE/VOICE/Sword/11_nekketsu_attack.wav", 0, 5 },						// ����

		{ "data/SE/VOICE/Sword/15_nekketsu_damage.wav", 0, 5 },						// ����

	};
};

#endif
