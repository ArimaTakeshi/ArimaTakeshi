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
		SOUND_LABEL_TITLEBGM000 = 0,		// タイトルのBGM
		SOUND_LABEL_TUTORIALBGM000,			// チュートリアルのBGM
		SOUND_LABEL_GAMEBGM000,				// ゲームのBGM
		SOUND_LABEL_GAMEBGM001,				// 波のBGM
		SOUND_LABEL_PLAYERBGM000,			// 船の音のBGM
		SOUND_LABEL_GAMEOVER,				// ゲームオーバーのBGM
		SOUND_LABEL_WINERBGM,				// 勝った場合のBGM
		SOUND_LABEL_ENTERSE,				// 決定音
		SOUND_LABEL_PAUSE000,				// ポーズを開く音
		SOUND_LABEL_PAUSE001,				// ポーズを閉じる音
		SOUND_LABEL_PAUSE002,				// ポーズのメニューを移動する音
		SOUND_LABEL_CHANGEWEAPON,			// 武器の切り替えの音
		SOUND_LABEL_PLAYERCANNON,			// プレイヤー大砲音
		SOUND_LABEL_ENEMYCANNON,			// 敵大砲音
		SOUND_LABEL_SKYCANNON,				// 対空砲音
		SOUND_LABEL_TORPEDO,				// 魚雷砲音
		SOUND_LABEL_EXPLOSION000,			// 轟沈音
		SOUND_LABEL_GO,						// さあ！いくぞ！
		SOUND_LABEL_LOSE,					// くっこんなはずでは
		SOUND_LABEL_MIZUBASIRA,				// 水柱Cooperation
		SOUND_LABEL_COOPERATION,			// 文字の協調
		SOUND_LABEL_HIKOUKI,				// 戦闘機の通過音
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
	IXAudio2SourceVoice	*m_apSourceVoice[SOUND_LABEL_MAX];			// ソースボイスへのポインタ
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX];		// オーディオデータへのポインタ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX];			// オーディオデータサイズ

	// 各音素材のパラメータ
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		//-1はループ　　0は単発
		//BGM一覧
		{ "data/BGM/title000BGM.wav", -1 },
		{ "data/BGM/tutorial000BGM.wav", -1 },
		{ "data/BGM/game000BGM.wav", -1 },	
		{ "data/BGM/game001BGM.wav", -1 },
		{ "data/BGM/shipmoveBGM.wav", -1 },
		{ "data/BGM/gameoverBGM.wav", -1 },
		{ "data/BGM/winerBGM.wav", -1 },
		//SE一覧
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