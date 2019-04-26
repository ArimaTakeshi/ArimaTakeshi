//=============================================================================
//
// プレイヤー処理 [enemy.h]
// Author : 有馬武志
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\enemy.txt"	//読み込むtxtファイルの名前

//=====================
//  CScene2Dの派生クラス
//=====================
class CEnemy : public CScene2D
{
public://誰でも扱える
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,		//通常状態
		ENEMYSTATE_DAMAGE,			//ダメージ状態
		ENEMYSTATE_DEAHT,			//死亡状態	
		ENEMYSTATE_MAX				//状態の最大数
	}ENEMYSTATE;

	typedef enum
	{
		ENEMYTYPE_SHIP = 0,			//戦艦
		ENEMYTYPE_DIGHTER,			//戦闘機
		ENEMYTYPE_SUBMARINE,		//潜水艦
		ENEMTTYPE_CARRIER,			//空母
		ENEMYTYPE_MAX				//状態の最大数
	}ENEMYTYPE;

	CEnemy();
	~CEnemy();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void CreateEnemy(void);
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,D3DXVECTOR2 size, ENEMYTYPE type,int nLife,int nOnOffAttak,int nChase);
	D3DXVECTOR2 *GetSize(void) { return &m_Size; }
	ENEMYTYPE &GetType(void) { return m_type; }
	void HitEnemy(int nDamage);

private:
	typedef struct
	{
		int					  nCntGo;					//出るタイミング
		D3DXVECTOR3			  InitPos;					//Posの初期値
		D3DXVECTOR3			  InitMove;					//Moveの初期値
		D3DXVECTOR2			  InitSize;					//Sizeの初期値
		ENEMYTYPE			  EnemyType;				//Typeの初期値
		int					  nLife;					//Lifeの初期値
		int					  nAttack;					//Attackする初期化処理
		int					  nChase;					//追尾するかしないか
	}Enemy;

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//共有テクスチャのポインタ
	int						  m_nLife;					//体力
	int						  m_nCounterState;			//状態管理のカウンター
	ENEMYSTATE				  m_state;					//プレイヤーの状態
	ENEMYTYPE				  m_type;					//敵の種類
	int						  m_nCount;					//攻撃カウンター
	D3DXVECTOR2				  m_Size;					//サイズ
	static int				  m_nNumEnemy;				//敵の総数カウンター
	D3DXVECTOR3				  m_move;					//移動量
	float					  m_fAngle;					//角度
	static int				  m_nNumMaxEnemy;			//敵の使う数
	static int				  m_nCntEnemy;				//敵が出るタイミングのフレーム
	static Enemy			  m_Enemy[MAX_DATA];		//敵のファイルからの情報を確保してる場所	
	int						  m_nOnOffAttack;			//攻撃をするかしないか
	int						  m_nChase;					//追尾するかしない
	float					  m_fRot;					//角度
};
#endif