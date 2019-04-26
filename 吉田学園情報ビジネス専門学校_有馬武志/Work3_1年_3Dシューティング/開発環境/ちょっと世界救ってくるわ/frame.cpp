//-----------------------------------------------------------------------------
//
//���L���̏���[frame.cpp]
//Author : �L�n���u
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "frame.h"
#include "camera.h"
#include "game.h"
#include "score.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define	TEXTURE_FRAME1 "data/TEXTURE/�g.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME2 "data/TEXTURE/�e�e.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME3 "data/TEXTURE/�N���X�w�A.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME4 "data/TEXTURE/kill.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME5 "data/TEXTURE/time.png"			//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME6 "data/TEXTURE/�G���W���g.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME7 "data/TEXTURE/Engine.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME8 "data/TEXTURE/zonnbi1.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME9 "data/TEXTURE/zonnbi2.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME10 "data/TEXTURE/tumeato.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define FRAME_SIZE_X	(1280)							//�g�̉���
#define FRAME_SIZE_Y	(70)							//�g�̏c��
#define BULE_SIZE		(70)							//�e�e����
#define XHER_SIZE		(50)							//�N���X�w�A
#define KILL_SIZE_X		(50)							//�L���̉���
#define KILL_SIZE_Y		(30)							//�L���̏c��
#define TIME_SIZE_X		(50)							//���Ԃ̉���
#define TIME_SIZE_Y		(30)							//���Ԃ̏c��
#define TIME_ENGINE_FRAME_X		(440)					//�G���W���̘g�̉���
#define TIME_ENGINE_FRAME_Y		(30)					//�G���W���̘g�̏c��
#define TIME_ENGINE_X	(70)							//�G���W���̉���
#define TIME_ENGINE_Y	(30)							//�G���W���̏c��
#define KILL_100_X		(70)							//kill�̉���
#define KILL_100_Y		(30)							//kill�̏c��
#define ZONNBI1_X		(120)							//zonbi1�̉���
#define ZONNBI1_Y		(250)							//zonbi1�̏c��
#define ZONNBI2_X		(100)							//zonbi1�̉���
#define ZONNBI2_Y		(250)							//zonbi1�̏c��
#define TUMEATO_X		(200)							//tumeato�̉���
#define TUMEATO_Y		(240)							//tumeato�̏c��
#define TIZU_X			(100)							//�s�X�n�̉���
#define TIZU_Y			(100)							//�s�X�n�̏c��
#define MAX_TEXTURE		(10)							//�e�N�X�`���̍ő吔

//-----------------------------------------------------------------------------
//�O���[�o���ϐ��錾
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9		g_pTextureFrame[MAX_TEXTURE] = {};		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame			  = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int						g_nFrame;								//�g�̐��l
D3DXVECTOR3				g_posBulletCount;						//�e�̒��S���W
D3DXVECTOR3				g_posFrame;								//�t���[���̒��S���W
D3DXVECTOR3				g_posXher;								//�N���X�w�A�̒��S���W
D3DXVECTOR3				g_posKill;								//�L���̒��S���W
D3DXVECTOR3				g_posTime;								//�^�C���̒��S���W
D3DXVECTOR3				g_posEngineFrame;						//�G���W���̘g�̒��S���W
D3DXVECTOR3				g_posEngine;							//�G���W���̒��S���W
D3DXVECTOR3				g_pos100kill;
D3DXVECTOR3				g_posZonnbi1;
D3DXVECTOR3				g_posZonnbi2;
D3DXVECTOR3				g_posTumeato;
float					g_Xhetrot;

//-----------------------------------------------------------------------------
//���L���̏���������
//-----------------------------------------------------------------------------
void InitFrame(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	Camera pCamera = *GetCamera();				//�J�����̃f�o�C�X�̎擾
	MODE pMode = *GetMode();					//���[�h�̃|�C���^
	int				  nCntFrame;				//���L���̃J�E���g
	VERTEX_2D		  *pVtx;					//���_����ݒ�
	Score *pScore = GetScore();

	//���L���̏�����
	g_posBulletCount = D3DXVECTOR3(1160, SCREEN_HEIGHT - 90, 0.0f);				//�e�̏������W
	g_posFrame = D3DXVECTOR3(0, 5, 0.0f);										//�g�̏������W
	g_posKill = D3DXVECTOR3(1000, 35, 0.0f);									//�L�����̏������W
	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2 + 50, 35, 0.0f);					//���Ԑ��̏������W
	g_posEngineFrame = D3DXVECTOR3(460, 35, 0.0f);								//�G���W���̘g�̏������W
	g_posEngine = D3DXVECTOR3(90, 35, 0.0f);									//�G���W���̏������W
	g_posZonnbi1 = D3DXVECTOR3(150, 400, 0.0f);
	g_posZonnbi2 = D3DXVECTOR3(1100, 400, 0.0f);
	g_posTumeato = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60, 0.0f);
	//g_posTizu = D3DXVECTOR3(120, 600, 0.0f);
	g_Xhetrot = 0.0f;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�g
		pDevice,
		TEXTURE_FRAME1,
		&g_pTextureFrame[0]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�e�e
		pDevice,
		TEXTURE_FRAME2,
		&g_pTextureFrame[1]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�N���X�w�A
		pDevice,
		TEXTURE_FRAME3,
		&g_pTextureFrame[2]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�L��
		pDevice,
		TEXTURE_FRAME4,
		&g_pTextureFrame[3]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//����
		pDevice,
		TEXTURE_FRAME5,
		&g_pTextureFrame[4]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�G���W���̘g
		pDevice,
		TEXTURE_FRAME6,
		&g_pTextureFrame[5]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//�G���W��
		pDevice,
		TEXTURE_FRAME7,
		&g_pTextureFrame[6]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//zonnbi1
		pDevice,
		TEXTURE_FRAME8,
		&g_pTextureFrame[7]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//zonnbi2
		pDevice,
		TEXTURE_FRAME9,
		&g_pTextureFrame[8]
	);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile
	(//tumeato
		pDevice,
		TEXTURE_FRAME10,
		&g_pTextureFrame[9]
	);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFrame,
		NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		if (pMode != MODE_TITLE)
		{
			if (nCntFrame == 0)
			{//�g
				//�g�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posFrame.x - (FRAME_SIZE_X), g_posFrame.y - (FRAME_SIZE_Y), 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posFrame.x + (FRAME_SIZE_X), g_posFrame.y - (FRAME_SIZE_Y), 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posFrame.x - (FRAME_SIZE_X), g_posFrame.y + (FRAME_SIZE_Y), 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posFrame.x + (FRAME_SIZE_X), g_posFrame.y + (FRAME_SIZE_Y), 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (nCntFrame == 1)
			{//�e
				//�e�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posBulletCount.x - BULE_SIZE, g_posBulletCount.y - BULE_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posBulletCount.x + BULE_SIZE, g_posBulletCount.y - BULE_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posBulletCount.x - BULE_SIZE, g_posBulletCount.y + BULE_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posBulletCount.x + BULE_SIZE, g_posBulletCount.y + BULE_SIZE, 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				//���L���̂̌��̕�
				g_posBulletCount.x += 50;
			}
			else if (nCntFrame == 2)
			{//�e
			 //�e�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posXher.x - XHER_SIZE, g_posXher.y - XHER_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posXher.x + XHER_SIZE, g_posXher.y - XHER_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posXher.x - XHER_SIZE, g_posXher.y + XHER_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posXher.x + XHER_SIZE, g_posXher.y + XHER_SIZE, 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (nCntFrame == 3)
			{//�e
			 //�e�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posKill.x - KILL_SIZE_X, g_posKill.y - KILL_SIZE_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posKill.x + KILL_SIZE_X, g_posKill.y - KILL_SIZE_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posKill.x - KILL_SIZE_X, g_posKill.y + KILL_SIZE_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posKill.x + KILL_SIZE_X, g_posKill.y + KILL_SIZE_Y, 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			//else if (nCntFrame == 4)
			//{//�e
			// //�e�̒��_�ݒ�
			//	pVtx[0].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE_X, g_posTime.y - TIME_SIZE_Y, 0.0f);
			//	pVtx[1].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE_X, g_posTime.y - TIME_SIZE_Y, 0.0f);
			//	pVtx[2].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE_X, g_posTime.y + TIME_SIZE_Y, 0.0f);
			//	pVtx[3].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE_X, g_posTime.y + TIME_SIZE_Y, 0.0f);

			//	//1.0f�ŌŒ�
			//	pVtx[0].rhw = 1.0f;
			//	pVtx[1].rhw = 1.0f;
			//	pVtx[2].rhw = 1.0f;
			//	pVtx[3].rhw = 1.0f;

			//	//���_�J���[
			//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	//�e�N�X�`�����W
			//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			//}
			else if (nCntFrame == 5)
			{//�e
			 //�e�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posEngineFrame.x - TIME_ENGINE_FRAME_X, g_posEngineFrame.y - TIME_ENGINE_FRAME_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posEngineFrame.x + TIME_ENGINE_FRAME_X, g_posEngineFrame.y - TIME_ENGINE_FRAME_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posEngineFrame.x - TIME_ENGINE_FRAME_X, g_posEngineFrame.y + TIME_ENGINE_FRAME_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posEngineFrame.x + TIME_ENGINE_FRAME_X, g_posEngineFrame.y + TIME_ENGINE_FRAME_Y, 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			else if (nCntFrame == 6)
			{//�G���W��
				//�e�̒��_�ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_posEngine.x - TIME_ENGINE_X, g_posEngine.y - TIME_ENGINE_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_posEngine.x + TIME_ENGINE_X, g_posEngine.y - TIME_ENGINE_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_posEngine.x - TIME_ENGINE_X, g_posEngine.y + TIME_ENGINE_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_posEngine.x + TIME_ENGINE_X, g_posEngine.y + TIME_ENGINE_Y, 0.0f);

				//1.0f�ŌŒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}
			//else if (nCntFrame == 10)
			//{//�n�}
			// //�e�̒��_�ݒ�
			//	pVtx[0].pos = D3DXVECTOR3(g_posTizu.x - TIZU_X, g_posTizu.y - TIZU_Y, 0.0f);
			//	pVtx[1].pos = D3DXVECTOR3(g_posTizu.x + TIZU_X, g_posTizu.y - TIZU_Y, 0.0f);
			//	pVtx[2].pos = D3DXVECTOR3(g_posTizu.x - TIZU_X, g_posTizu.y + TIZU_Y, 0.0f);
			//	pVtx[3].pos = D3DXVECTOR3(g_posTizu.x + TIZU_X, g_posTizu.y + TIZU_Y, 0.0f);

			//	//1.0f�ŌŒ�
			//	pVtx[0].rhw = 1.0f;
			//	pVtx[1].rhw = 1.0f;
			//	pVtx[2].rhw = 1.0f;
			//	pVtx[3].rhw = 1.0f;

			//	//���_�J���[
			//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//	//�e�N�X�`�����W
			//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			//}
		}
		else if (nCntFrame == 7)
		{//�G���W��
		 //�e�̒��_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posZonnbi1.x - ZONNBI1_X, g_posZonnbi1.y - ZONNBI1_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posZonnbi1.x + ZONNBI1_X, g_posZonnbi1.y - ZONNBI1_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posZonnbi1.x - ZONNBI1_X, g_posZonnbi1.y + ZONNBI1_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posZonnbi1.x + ZONNBI1_X, g_posZonnbi1.y + ZONNBI1_Y, 0.0f);

			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if (nCntFrame == 8)
		{//�G���W��
		 //�e�̒��_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posZonnbi2.x - ZONNBI2_X, g_posZonnbi2.y - ZONNBI2_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posZonnbi2.x + ZONNBI2_X, g_posZonnbi2.y - ZONNBI2_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posZonnbi2.x - ZONNBI2_X, g_posZonnbi2.y + ZONNBI2_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posZonnbi2.x + ZONNBI2_X, g_posZonnbi2.y + ZONNBI2_Y, 0.0f);

			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else if (nCntFrame == 9)
		{//�G���W��
		 //�e�̒��_�ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posTumeato.x - TUMEATO_X, g_posTumeato.y - TUMEATO_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTumeato.x + TUMEATO_X, g_posTumeato.y - TUMEATO_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTumeato.x - TUMEATO_X, g_posTumeato.y + TUMEATO_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTumeato.x + TUMEATO_X, g_posTumeato.y + TUMEATO_Y, 0.0f);

			//1.0f�ŌŒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		pVtx += 4; //���_�f�[�^�̃|�C���^��4�i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFrame->Unlock();
}

//-----------------------------------------------------------------------------
//���L���̏I������
//-----------------------------------------------------------------------------
void UninitFrame(void)
{
	//���[�J���ϐ��錾
	int nCntFrame; //�J�E���g

	//�e�N�X�`���̔j��
	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffFrame != NULL)
	{
		g_pVtxBuffFrame->Release();
		g_pVtxBuffFrame = NULL;
	}
}

//-----------------------------------------------------------------------------
//���L���̍X�V����
//-----------------------------------------------------------------------------
void UpdateFrame(void)
{
	//�}�E�X�̏��
	DIMOUSESTATE2 pMouse = GetMousePointer();

	Camera *pCamera = GetCamera();

	Score *pScore = GetScore();

	g_Xhetrot += -pMouse.lY / 30.0f;

	g_posXher = pCamera->posR;

	//���f�����J�����ɑ��
	g_posXher = pCamera->posV;

	//�J�����̌������I�u�W�F�N�g�ɑ��
	g_posXher = pCamera->rot;
	g_Xhetrot += (pMouse.lY / 500.0f);
	g_posXher.y += (g_Xhetrot);
}

//-----------------------------------------------------------------------------
//���L���̕`�揈��
//-----------------------------------------------------------------------------
void DrawFrame(void)
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice		  = GetDevice();	//�f�o�C�X�̎擾
	MODE pMode = *GetMode();
	int				  nCntFrame;						//���L���̃J�E���g

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntFrame = 0; nCntFrame < MAX_TEXTURE; nCntFrame++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureFrame[nCntFrame]);

		//�e�N�X�`���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntFrame, 2);
	}
}