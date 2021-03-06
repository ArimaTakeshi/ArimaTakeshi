//=============================================================================
//
// シェーダー管理処理 [shadermgr.cpp]
// Author : 佐藤安純 Sato_Asumi
//
//=============================================================================
#include "shadermgr.h"
#include "rotationshader.h"

//=============================================================================
// 生成処理
//=============================================================================
CShaderMgr * CShaderMgr::Create()
{
	CShaderMgr * pShaderMgr = new CShaderMgr;
	pShaderMgr->Init();

	return pShaderMgr;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CShaderMgr::CShaderMgr(){}

//=============================================================================
// デストラクタ
//=============================================================================
CShaderMgr::~CShaderMgr(){}

//=============================================================================
// 初期化処理
//=============================================================================
void CShaderMgr::Init(void)
{
	//変数の初期化
	m_pRotationShader = NULL;

	//ローテーションシェーダーの生成
	if (m_pRotationShader == NULL) { m_pRotationShader = CRotationShader::Create(); }
}

//=============================================================================
// 終了処理
//=============================================================================
void CShaderMgr::Uninit(void)
{
	//ローテーションシェーダーの破棄
	if (m_pRotationShader != NULL)
	{
		m_pRotationShader->Uninit();
		delete m_pRotationShader;
		m_pRotationShader = NULL;
	}
}
