//=============================================================================
//
// �v���C���[���� [enemy.h]
// Author : �L�n���u
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FILE_NAME				"data\\TEXT\\enemy.txt"	//�ǂݍ���txt�t�@�C���̖��O

//=====================
//  CScene2D�̔h���N���X
//=====================
class CEnemy : public CScene2D
{
public://�N�ł�������
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,		//�ʏ���
		ENEMYSTATE_DAMAGE,			//�_���[�W���
		ENEMYSTATE_DEAHT,			//���S���	
		ENEMYSTATE_MAX				//��Ԃ̍ő吔
	}ENEMYSTATE;

	typedef enum
	{
		ENEMYTYPE_SHIP = 0,			//���
		ENEMYTYPE_DIGHTER,			//�퓬�@
		ENEMYTYPE_SUBMARINE,		//������
		ENEMTTYPE_CARRIER,			//���
		ENEMYTYPE_MAX				//��Ԃ̍ő吔
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
		int					  nCntGo;					//�o��^�C�~���O
		D3DXVECTOR3			  InitPos;					//Pos�̏����l
		D3DXVECTOR3			  InitMove;					//Move�̏����l
		D3DXVECTOR2			  InitSize;					//Size�̏����l
		ENEMYTYPE			  EnemyType;				//Type�̏����l
		int					  nLife;					//Life�̏����l
		int					  nAttack;					//Attack���鏉��������
		int					  nChase;					//�ǔ����邩���Ȃ���
	}Enemy;

	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	//���L�e�N�X�`���̃|�C���^
	int						  m_nLife;					//�̗�
	int						  m_nCounterState;			//��ԊǗ��̃J�E���^�[
	ENEMYSTATE				  m_state;					//�v���C���[�̏��
	ENEMYTYPE				  m_type;					//�G�̎��
	int						  m_nCount;					//�U���J�E���^�[
	D3DXVECTOR2				  m_Size;					//�T�C�Y
	static int				  m_nNumEnemy;				//�G�̑����J�E���^�[
	D3DXVECTOR3				  m_move;					//�ړ���
	float					  m_fAngle;					//�p�x
	static int				  m_nNumMaxEnemy;			//�G�̎g����
	static int				  m_nCntEnemy;				//�G���o��^�C�~���O�̃t���[��
	static Enemy			  m_Enemy[MAX_DATA];		//�G�̃t�@�C������̏����m�ۂ��Ă�ꏊ	
	int						  m_nOnOffAttack;			//�U�������邩���Ȃ���
	int						  m_nChase;					//�ǔ����邩���Ȃ�
	float					  m_fRot;					//�p�x
};
#endif