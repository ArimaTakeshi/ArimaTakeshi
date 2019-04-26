//=============================================================================
//
// シーン処理 [scene2D.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SLEffect_PRIORITY		(2)

//*****************************************************************************
// クラスの定義
//*****************************************************************************
class CLineEffect : public CScene
{
public:
	typedef enum
	{
		TYPE_FIRE,
		TYPE_MAX
	}TYPE;
	CLineEffect(int nPrioryity = SLEffect_PRIORITY) : CScene::CScene(nPrioryity)
	{
		m_pmtxWorld = NULL;
		m_bDelete = NULL;
	};
	~CLineEffect() {};

	void	Set(D3DXMATRIX &mtxWorld, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fInterval, bool &bDelete, TYPE type);
	HRESULT Init(void);
	void	Update(void);
	D3DXVECTOR3	ChangePos(void);
	void MoveSet(D3DXVECTOR3 &pos);
	void SetEffect(void);
	void StartEffect(void);
	void EndEffect(void);
	static void Delete(void);

protected://*****************************************************************************
private://*****************************************************************************
	D3DXVECTOR3 SetMtxWorld(void);
		//変数宣言//***********************************************************************
	TYPE			m_Type;			// セット情報
	D3DXMATRIX		*m_pmtxWorld;	//ワールドマトリックス
	D3DXVECTOR3		m_posold;		// 自身前の位置
	D3DXVECTOR3		m_pos;			// 原点からの角度プラス値
	D3DXVECTOR3		m_rot;			// 原点からの角度プラス値
	float			m_fLength;		//進んだ距離保存
	float			m_fInterval;	//セットまでの間隔
	bool			*m_bDelete;		//消える判定
};

#endif
