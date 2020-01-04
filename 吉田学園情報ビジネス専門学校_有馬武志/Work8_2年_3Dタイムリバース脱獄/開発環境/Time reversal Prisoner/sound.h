//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//=====================
//  基本クラス
//=====================
class CSound
{
public:
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,		// タイトルのBGM
		SOUND_LABEL_BGM_GAME,			// ゲームのBGM
		SOUND_LABEL_BGM_RESULT,			// リザルトのBGM
		SOUND_LABEL_SE_SKILL,			// スキル発動
		SOUND_LABEL_SE_INTRODUCTION,	// 案内
		SOUND_LABEL_SE_SKILLCANCEL,		// スキルキャンセル
		SOUND_LABEL_SE_SHOOT,			// 銃を撃つ
		SOUND_LABEL_SE_DAMAGE,			// ダメージ
		SOUND_LABEL_SE_PAUSE_SELECT,	// ポーズの選択
		SOUND_LABEL_SE_PAUSE_OPEN,		// ポーズを開く
		SOUND_LABEL_SE_PAUSE_CLOSE,		// ポーズを閉じる
		SOUND_LABEL_SE_PAUSE_MOVE,		// ポーズを動かす
		SOUND_LABEL_SE_TRAP,			// トラップに当たった際
		SOUND_LABEL_MAX
	}SOUND_LABEL;
	
	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label); //ゲームの初期化近く　
	void StopSound(SOUND_LABEL label);	  //同じ名前を書いてストップさせっる
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	typedef struct
	{
		char *m_pFilename;		// ファイル名
		int m_nCntLoop;			// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	IXAudio2				*m_pXAudio2;							// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice	*m_pMasteringVoice;						// マスターボイスへのポインタ
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX];		// ソースボイスへのポインタ
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX];		// オーディオデータへのポインタ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX];			// オーディオデータサイズ

	// 各音素材のパラメータ
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		//-1はループ　　0は単発
		//BGM一覧
		{ "data/SOUND/BGM/TitleBGM.wav", -1 },
		{ "data/SOUND/BGM/GameBGM.wav", -1 },
		{ "data/SOUND/BGM/ResultBGM.wav", -1 },
		//SE一覧
		{ "data/SOUND/SE/Skill.wav", 0 },
		{ "data/SOUND/SE/IntroductionSE.wav", 0 },
		{ "data/SOUND/SE/SkillCancellationSE.wav", 0 },
		{ "data/SOUND/SE/ShootSE.wav", 0 },
		{ "data/SOUND/SE/Damage.wav", 0 },
		{ "data/SOUND/SE/pause_select.wav", 0 },
		{ "data/SOUND/SE/pause_open.wav", 0 },
		{ "data/SOUND/SE/pause_close.wav", 0 },
		{ "data/SOUND/SE/pause_move.wav", 0 },
		{ "data/SOUND/SE/TrapSE.wav", 0 },
	};
};

#endif