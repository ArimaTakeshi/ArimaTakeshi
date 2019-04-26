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
		{ "data/BGM/MODE/Select.wav", -1, 0 },						// セレクトBGM
		{ "data/BGM/MODE/Tutorial.wav", -1, 0 },					// チュートリアルBGM

		{ "data/BGM/MODE/GameClear.wav", -1, 0 },					// クリアBGM
		{ "data/BGM/MODE/GameOver.wav", -1, 0 },					// オーバーBGM
		{ "data/BGM/MODE/GameOver.wav", -1, 0 },					// オーバーBGM

		{ "data/BGM/MODE/Field.wav", -1, 0 },						// フィールドBGM
		{ "data/BGM/MODE/Boss.wav", -1, 0 },						// ボスBGM

		/* *** SE *** */
		{ "data/SE/BATTLE/Attack.wav", 0, 5 },						// 攻撃
		{ "data/SE/BATTLE/Boost.wav", 0, 30 },						// ブースト
		{ "data/SE/Alert.wav", 0, 5 },						// チャージ
		{ "data/SE/BATTLE/Critical.wav", 0, 5 },					// クリティカル
		{ "data/SE/BATTLE/Down.wav", 0, 5 },						// ダウン
		{ "data/SE/BATTLE/Guard.wav", 0, 5 },						// ガード
		{ "data/SE/BATTLE/Hit.wav", 0, 5 },							// ヒット
		{ "data/SE/BATTLE/landing.wav", 0, 5 },						// 着地
		{ "data/SE/BATTLE/LockCancel.wav", 0, 10 },					// ロックキャンセル
		{ "data/SE/BATTLE/LockOn.wav", 0, 10 },						// ロックオン
		{ "data/SE/BATTLE/Paris.wav", 0, 5 },						// パリィ
		{ "data/SE/BATTLE/Step.wav", 0, 5 },						// ステップ
		{ "data/SE/BATTLE/Dead.wav", 0, 5 },						// 死亡
		{ "data/SE/BATTLE/Over.wav", 0, 5 },						// 消失
		{ "data/SE/SELECT/Return.wav", 0, 5 },						// 消失

		{ "data/SE/Correct.wav", 0, 5 },						// 消失
		{ "data/SE/VOICE/Sword/23_nekketsu_down.wav", 0, 5 },						// 消失
		{ "data/SE/Incorrect.wav", 0, 5 },						// 消失
		{ "data/SE/Question.wav", 0, 5 },						// 消失
		{ "data/SE/VOICE/Sword/07_nekketsu_attack.wav", 0, 5 },						// 消失
		{ "data/SE/VOICE/Sword/08_nekketsu_attack.wav", 0, 5 },						// 消失
		{ "data/SE/VOICE/Sword/09_nekketsu_attack.wav", 0, 5 },						// 消失
		{ "data/SE/VOICE/Sword/11_nekketsu_attack.wav", 0, 5 },						// 消失

		{ "data/SE/VOICE/Sword/15_nekketsu_damage.wav", 0, 5 },						// 消失

	};
};

#endif
