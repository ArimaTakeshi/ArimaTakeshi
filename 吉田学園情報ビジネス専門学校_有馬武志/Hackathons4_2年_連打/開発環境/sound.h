//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CSound
{// サウンドクラス
public:
	typedef enum
	{// サウンドファイル
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

		LABEL_MAX	// 総数
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
	{// パラメータ
		char *pFilename;	// ファイル名
		int  nCntLoop;		// ループカウント(-1でループ再生)
		int  nPlayNext;		//次の再生までに必要なF数
		int  nCntFrame;		//現在のFカウント
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイスへのポインタ
	IXAudio2SourceVoice	*m_apSourceVoice[LABEL_MAX];	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[LABEL_MAX];						// オーディオデータへのポインタ
	DWORD m_aSizeAudio[LABEL_MAX];						// オーディオデータサイズ

	// 各音素材のパラメータ
	PARAM m_aSoundParam[LABEL_MAX] =
	{
		/* *** BGM *** */
		{ "data/BGM/MODE/Title.wav", -1, 0 },						// タイトルBGM
		{ "data/BGM/MODE/Game.wav", -1, 0 }, 						// ゲームBGM

		{ "data/BGM/MODE/Result.wav", -1, 0 },						// リザルトBGM

		{ "data/BGM/MODE/GameClear.wav", -1, 0 },					// クリアBGM
		{ "data/BGM/MODE/GameOver.wav", -1, 0 },					// オーバーBGM

		{ "data/SE/BATTLE/HIT/Explosion.wav", 0, 10 },				// ボス撃破時爆発音1

		{ "data/SE/BATTLE/HIT/scream1.wav", 0, 5 },					// 叫び声

		{ "data/SE/enter2.wav", 0, 5 },								// エンター
		{ "data/SE/shot.wav", 0, 5 },								// エンター
		{ "data/SE/damage.wav", 0, 5 },								// エンター
		{ "data/SE/ice.wav", 0, 5 },								// エンター
		{ "data/SE/flame.wav", 0, 5 },								// エンター
		{ "data/SE/stan.wav", 0, 5 },								// エンター
		{ "data/SE/walk.wav", 0, 5 },								// エンター
		{ "data/SE/wave.wav", 0, 5 },								// エンター
	};
};

#endif
