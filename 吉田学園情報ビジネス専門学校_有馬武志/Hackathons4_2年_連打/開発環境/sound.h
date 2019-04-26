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
		LABEL_TITLE000	, LABEL_GAME000	, LABEL_RESULT000,
		LABEL_CLEAR000	, LABEL_OVER000		, 
		LABEL_EXPLOSION001, LABEL_HIT999, 

		/* *** SE *** */
		LABEL_ENTER,
		LABEL_SHOT,
		LABEL_DAMAGE,
		LABEL_ICE,
		LABEL_FLAME,
		LABEL_STAN,
		LABEL_WALK,
		LABEL_WAVE,

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
		{ "data/BGM/MODE/Game.wav", -1, 0 }, 						// �Q�[��BGM

		{ "data/BGM/MODE/Result.wav", -1, 0 },						// ���U���gBGM

		{ "data/BGM/MODE/GameClear.wav", -1, 0 },					// �N���ABGM
		{ "data/BGM/MODE/GameOver.wav", -1, 0 },					// �I�[�o�[BGM

		{ "data/SE/BATTLE/HIT/Explosion.wav", 0, 10 },				// �{�X���j��������1

		{ "data/SE/BATTLE/HIT/scream1.wav", 0, 5 },					// ���ѐ�

		{ "data/SE/enter2.wav", 0, 5 },								// �G���^�[
		{ "data/SE/shot.wav", 0, 5 },								// �G���^�[
		{ "data/SE/damage.wav", 0, 5 },								// �G���^�[
		{ "data/SE/ice.wav", 0, 5 },								// �G���^�[
		{ "data/SE/flame.wav", 0, 5 },								// �G���^�[
		{ "data/SE/stan.wav", 0, 5 },								// �G���^�[
		{ "data/SE/walk.wav", 0, 5 },								// �G���^�[
		{ "data/SE/wave.wav", 0, 5 },								// �G���^�[
	};
};

#endif
