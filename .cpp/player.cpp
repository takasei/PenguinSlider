//==================================================================================================================
//
// �v���C���[����[player.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "inputKeyboard.h"
#include "renderer.h"
#include "player.h"
#include "debugProc.h"
#include "camera.h"
#include "meshField.h"
#include "motionModel.h"
#include "model.h"
#include "time.h"
#include "record.h"
#include "title.h"
#include <initializer_list>
#include "tutorial.h"
#include "game.h"
#include "inputGamepad.h"
#include "particle.h"
#include "titleFade.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CCamera *CPlayer::m_pCamera = NULL;				// �J�������
CMeshOrbit *CPlayer::m_pMeshOrbit = NULL;		// �O�Տ��
CRecord *CPlayer::m_pRecord = NULL;				// �L�^���
CModel *CPlayer::m_pModel = NULL;				// ���f�����
CParticle *CPlayer::m_pParticle = NULL;			// �p�[�e�B�N�����
CEnemy *CPlayer::m_pEnemy = NULL;				// �G���

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MOTION_FILE_NAME "data/TEXT/C++3DMotion.txt"// �ǂݍ��ރe�L�X�g�f�[�^�̃\�[�X��
#define TITLE_PLAYER_MOVE 0.15f		// �^�C�g���̃v���C���[�̈ړ���
#define PLAYER_MOVE 0.25f			// �v���C���[�̈ړ���
#define PLAYER_TURNING_MOVE 0.01f	// �v���C���[�̃W�����v���̉��̈ړ���
#define PLAYER_INERTIA 3.0f			// �����X�s�[�h
#define PLAYER_SPEED_DOWN -0.2f		// �X�s�[�h�_�E�����x
#define JUMP_SPEED 0.2f				// �W�����v�����Ƃ��̐i�s�X�s�[�h
#define JUMP_MOVE 11.0f				// �W�����v����Ƃ��̈ړ���
#define MAX_JAMP_SPEED 0.05f		// �ő�W�����v�X�s�[�h
#define ROT_JUMP_TURNING 0.8f		// �W�����v���̃v���C���[�̉�]����
#define MAX_GRAVITY -6.0f			// �d�͂̍ő�l
#define GRAVITY -0.4f				// �d��
#define ROT_LIMIT 1.0f				// ��]����
#define ROT_SPEED 0.4f				// ��]���x
#define ROT_AMOUNT 0.05f			// ��]�̍������炵�Ă�����
#define REDUCE_SPEED 0.06f			// �����X�s�[�h
#define RAND_COUNT 130				// ���n�J�E���g
#define JUMP_COUNT1 40				// �^�C�g�����̃W�����v�J�E���g1
#define JUMP_COUNT2 60				// �^�C�g�����̃W�����v�J�E���g2
#define COLLISION_RADIUS1 20		// �X�|�[���̓����蔻�蔼�a
#define COLLISION_RADIUS_PLAYER 50	// �v���C���[�̓����蔻�蔼�a
#define GOAL_COUNT 2				// �S�[�������J�E���g
#define JOY_MIN_RANGE_V	20000.0f	// �R���g���[���[�̏c�X�e�B�b�N�����ŏ��l
#define GAME_MAX_PARTICLE 50		// �p�[�e�B�N���̍ő吔
#define INTERVAL 10					// �C���^�[�o���̍ő吔
#define INTERVAL_COUNT_MAX1 90		// �C���^�[�o���J�E���g�̍ő吔1
#define INTERVAL_COUNT_MAX2 150		// �C���^�[�o���J�E���g�̍ő吔2
#define PLAYER_MOVE_SPEED 0.1f		// �C���^�[�o�����̃v���C���[�̃X�s�[�h
#define LANDING_CAUNT 10			// ���n�J�E���g

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CPlayer::CPlayer(PRIORITY type = CScene::PRIORITY_PLAYER) :CScene(type)
{
	m_pModel = nullptr;				// ���f����񏉊���
}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CPlayer::~CPlayer()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CPlayer::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, WhileY, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ړ���
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �傫��
	m_RespownPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���X�|�[���ʒu
	m_RespownRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���X�|�[����]
	m_nCntRand = 0;											// ���n���Ă��Ȃ��J�E���g
	m_nCntGravity = 0;										// �d�͗p�J�E���g
	m_nCntTitle = 0;										// �^�C�g���p�J�E���g
	m_nNumPlace = 0;										// ���X�|�[���ԍ�
	m_nCntGoal = 0;											// �S�[�������J�E���g
	m_fStickMove = 0.0f;									// �R���g���[���[�̃X�e�B�b�N�̈ړ���
	m_nCntInterval = 0;										// ���X�|�[���̃C���^�[�o������
	m_nInterval = 0;										// �p�[�e�B�N���̃C���^�[�o������
	m_nCntTitleFade = 0;									// �^�C�g���t�F�[�h�̃J�E���g
	m_bRand = false;										// ���n���Ă��邩
	m_bRange = false;										// �͈͓��ɂ��邩�ǂ���
	m_bRespawn = false;										// ���X�|�[�����Ă��邩�ǂ���
	m_bGoal = false;										// �L�^�����邩�ǂ���
	m_bStart = false;										// �X�^�[�g�������ǂ���
	m_bTitleLogo = false;									// �^�C�g�����S��\�����Ă������ǂ���
	m_bJump = false;										// �W�����v�������ǂ���
	m_bStop = false;										// �~�܂��Ă��邩�ǂ���
	m_bInterval = false;									// �C���^�[�o�����邩�ǂ���
	m_bTitleFade = false;									// �^�C�g���t�F�[�h���邩�ǂ���

	// �^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);			// ��]
		m_difference = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// ��]�̖ڕW�n�_
	}
	else if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{// �`���[�g���A���̂Ƃ�
		m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);			// ��]
		m_difference = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);	// ��]�̖ڕW�n�_

		m_nCntGoal = 1;										// �S�[�������J�E���g
	}
	else if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		m_rot = D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f);		// ��]
		m_difference = D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f);// ��]�̖ڕW�n�_
	}
	else
	{
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]
		m_difference = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]�̖ڕW�n�_
	}

	//���[�V�����̏�����
	for (int nCntMotion = 0; nCntMotion < PLAYER_MOTION_MAX; nCntMotion++)
	{
		m_PlayerMotion[nCntMotion].nLoop = 0;										// ���[�v
		m_PlayerMotion[nCntMotion].nNumKey = 0;										// �L�[���̐�
		m_PlayerMotion[nCntMotion].Collision_nParts = 0;							// �p�[�c�ԍ�
		m_PlayerMotion[nCntMotion].CollisionOfset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �I�t�Z�b�g
		m_PlayerMotion[nCntMotion].CollisionRadius = 0.0f;							// �~�̔��a
		m_PlayerMotion[nCntMotion].CollisionStartFram = 0;							// �J�n�t���[��
		m_PlayerMotion[nCntMotion].CollisionEndFram = 0;							// �I���t���[��
		m_PlayerMotion[nCntMotion].Collision_Damage = 0;							// �_���[�W��

		// �L�[�̑������J�E���g
		for (int nCntKeySet = 0; nCntKeySet < 10; nCntKeySet++)
		{
			m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram = 0;				// �e�L�[�̃t���[��

			for (int nCntKey = 0; nCntKey < 11; nCntKey++)
			{
				m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�p�[�c�̊e�L�[�̈ʒu
				m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�p�[�c�̊e�L�[�̉�]
			}
		}
	}

	//=================================���f���̐ݒ�=================================//
	//�� 0
	m_MotionModel[0] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_BODY);		// �̐���
	m_MotionModel[0]->SetPos(D3DXVECTOR3(0, -2.0f, 0));										// �ʒu�ݒ�
	m_MotionModel[0]->SetRot(D3DXVECTOR3(0.0f, -1.5f, 0.0f));								// ��]�ݒ�
	m_MotionModel[0]->SetParent(NULL);														// �e�ݒ�
	//�� 1
	m_MotionModel[1] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_HEAD);		// ���p�[�c����
	m_MotionModel[1]->SetPos(D3DXVECTOR3(-11.0f, 5.0f, -0.44f));							// �ʒu�ݒ�
	m_MotionModel[1]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//���r 2
	m_MotionModel[2] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_LARM);		// ���r����
	m_MotionModel[2]->SetPos(D3DXVECTOR3(-5.0f, 3.0f, -4.0f));								// �ʒu�ݒ�
	m_MotionModel[2]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//�E�r 3
	m_MotionModel[3] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_RARM);		// �E�r����
	m_MotionModel[3]->SetPos(D3DXVECTOR3(-5.0f, 3.0f, 4.0f));								// �ʒu�ݒ�
	m_MotionModel[3]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//���� 4
	m_MotionModel[4] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_LLEG);		// ��������
	m_MotionModel[4]->SetPos(D3DXVECTOR3(6.0f, 0.0f, -3.0f));								// �ʒu�ݒ�
	m_MotionModel[4]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�
	//�E�� 5
	m_MotionModel[5] = CMotionModel::CreateObject(CMotionModel::MODEL_PENGUIN_RLEG);		// �E������
	m_MotionModel[5]->SetPos(D3DXVECTOR3(6.0f, 0.0f, 3.0f));								// �ʒu�ݒ�
	m_MotionModel[5]->SetParent(m_MotionModel[CMotionModel::MODEL_PENGUIN_BODY]);			// �e�ݒ�

	// ���[�V�����̓ǂݍ���
	LoadMotion();

	// �p�[�e�B�N���e�N�X�`�����[�h
	CParticle::Load();

	// �p�[�e�B�N���̐�������
	m_pParticle = CParticle::Create(GAME_MAX_PARTICLE, m_pos);
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CPlayer::Uninit(void)
{
	// �p�[�e�B�N���e�N�X�`���A�����[�h
	CParticle::Unload();

	// �v���C���[���f���̍ő�p�[�c�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// ���f���̏I������
		m_MotionModel[nCnt]->Uninit();

		// �������폜
		delete m_MotionModel[nCnt];

		// �|�C���^�pNULL
		m_MotionModel[nCnt] = nullptr;
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CPlayer::Update(void)
{
	// �t�F�[�h�擾
	CFade::FADE fade = CFade::GetFade();

	// �C���^�[�o���t�F�[�h�̎擾
	CIntervalFade::INTERVAL_FADE intervalFade = CIntervalFade::GetIntervalFade();

	// MeshField���擾
	CMeshField *pMeshField = CMeshField::GetMeshField();

	// �^�C�g���ł̃v���C���[�X�V����
	TitleUpdate();

	// �`���[�g���A���ł̃v���C���[�X�V����
	TutorialUpdate();

	// �Q�[���ł̃v���C���[�X�V����
	GameUpdate();

	float height = WhileY;				// �v���C���[�̍���
	m_bRand = GetbRand();				// �v���C���[�̒��n����擾
	m_bRange = GetbRange();				// �v���C���[�͈͓̔�����擾
	m_MotionOld = m_MotionType;			// �O�̃��[�V�����̑��
	m_posOld = m_pos;					// ���̈ʒu��O��̈ʒu�ɂ���

	// �v���C���[���ł̃X�^�[�g�̍X�V����
	bStartUpdate(fade);

	// �v���C���[���ł̃��b�V���t�B�[���h�̍X�V����
	height = MeshFieldUpdate(pMeshField);

	// �v���C���[���ł͈͓̔��ɂ���Ƃ��̍X�V����
	bRangeUpdate(height);

	// �v���C���[���ł̒��n����̍X�V����
	bRandUpdate(height);

	// ���[�V����
	Moation();

	// �v���C���[���ł̒��n�J�E���g�̍X�V����
	nCntRandUpdate(pMeshField, intervalFade);

	// �v���C���[���ł̃��f���̍X�V����
	PlayerModelUpdate();

	// ���X�|�[������ݒ�
	SetRespawn(m_bRespawn);

	// �p�[�e�B�N���̃C���^�[�o���J�E���g���Z
	m_nInterval++;

	// �C���^�[�o���J�E���g���K��l���傫���Ȃ����Ƃ�
	if (m_nInterval >= INTERVAL)
	{
		// �p�[�e�B�N���̐�������
		m_pParticle = CParticle::Create(GAME_MAX_PARTICLE, m_pos);

		// �p�[�e�B�N���̃C���^�[�o���J�E���g������
		m_nInterval = 0;
	}

	// �C���^�[�o�������Ԃ̂Ƃ�
	if (m_bInterval)
	{
		// �C���^�[�o���J�E���g���Z
		m_nCntInterval++;

		// �v���C���[�̈ړ��ʎ~�߂�
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// �C���^�[�o���J�E���g���K��l�ȏ�̂Ƃ�
		if (m_nCntInterval >= INTERVAL_COUNT_MAX1)
		{
			// �t�F�[�h�C������
			CIntervalFade::FadeIN();
		}

		// �C���^�[�o���J�E���g���K��l�ȏ�̂Ƃ�
		if (m_nCntInterval >= INTERVAL_COUNT_MAX2)
		{
			// �C���^�[�o�������Ȃ���Ԃɂ���
			m_bInterval = false;

			// �C���^�[�o���J�E���g������
			m_nCntInterval = 0;
		}
	}

#ifdef _DEBUG
	// �f�o�b�O�\��
	CDebugProc::Print("�v���C���[�̈ʒu : %.2f, %.2f, %.2f\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print("�v���C���[�̈ړ��� : %.2f, %.2f, %.2f\n", m_move.x, m_move.y, m_move.z);
	CDebugProc::Print("�v���C���[�̉�] : %.2f, %.2f, %.2f\n", m_rot.x, m_rot.y, m_rot.z);
	CDebugProc::Print("���������ꏊ : %d\n", m_nNumPlace);
#endif // _DEBUG
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;			// �v�Z�p�i�[�ϐ�

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���f���̕`��
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// ���S�̃}�g���b�N�X�ݒ�
		m_MotionModel[nCnt]->SetMtxCenter(m_mtxWorld);

		// �`�揈��
		m_MotionModel[nCnt]->Draw();
	}
}

//==================================================================================================================
// ��������
//==================================================================================================================
CPlayer *CPlayer::Create(void)
{
	// �V�[�����I�Ɋm��
	CPlayer *pPlayer = new CPlayer(CScene::PRIORITY_PLAYER);

	pPlayer->Init();			// �v���C���[�̏�����

	// �l��Ԃ�
	return pPlayer;
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CPlayer::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// ��]�ݒ�
//==================================================================================================================
void CPlayer::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==================================================================================================================
// ���X�|�[���ꏊ�ݒ�
//==================================================================================================================
void CPlayer::SetnNumPlace(int nNumPlace)
{
	m_nNumPlace = nNumPlace;
}

//==================================================================================================================
// ���쏈��
//==================================================================================================================
void CPlayer::OperationMove(CInputKeyboard *pInputKeyboard, CInputGamepad *pInputGamepad)
{
	D3DXVECTOR3 Diff;	// �v�Z�p�i�[�ϐ�

	// �R���g���[���[
	float fValueH = 0.0f;		// �c
	float fValueV = 0.0f;		// ��
	float fMove = 0.0f;			// �R���g���[���[�X�e�B�b�N�ړ���

	// �ړ����� ���X�e�B�b�N
	pInputGamepad->GetStickLeft(0, &fValueV, &fValueH);

	// ���n���Ă���Ƃ�
	if (m_bRand == true)
	{
		// �L�[�{�[�h�̈ړ��L�[��������Ă��Ȃ��Ƃ�
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			// ���X�e�B�b�N ���� �c�X�e�B�b�N��0����Ȃ��Ƃ�
			if (fValueH != 0 || fValueV != 0)
			{
				// ���ɃX�e�B�b�N���|�ꂽ�Ƃ�
				if (fValueV >= -JOY_MAX_RANGE && fValueV < 0)
				{
					// �ړ��ʌv�Z
					fMove = fValueV * -PLAYER_MOVE / JOY_MAX_RANGE;

					// �X�e�B�b�N�̌X���x�ňړ�������
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

					// ��]�̖ڕW�n�_�����߂�
					m_difference.z = -ROT_LIMIT;

					// ��]�̖ڕW�n�_����
					m_difference.y = m_rot.y - ROT_SPEED;

					// ���[�V����������
					m_MotionType = PLAYER_MOTION_WALK;
				}
				else if (fValueV <= JOY_MAX_RANGE && fValueV > 0)
				{// �E�ɃX�e�B�b�N���|�ꂽ�Ƃ�
					// �ړ��ʌv�Z
					fMove = fValueV * PLAYER_MOVE / JOY_MAX_RANGE;

					// �X�e�B�b�N�̌X���x�ňړ�������
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

					// ��]�̖ڕW�n�_�����߂�
					m_difference.z = ROT_LIMIT;

					// ��]�̖ڕW�n�_����
					m_difference.y = m_rot.y + ROT_SPEED;

					// ���[�V����������
					m_MotionType = PLAYER_MOTION_WALK;
				}
			}
		}

		// �R���g���[���[�̍��X�e�B�b�N���|����Ă��Ȃ��Ƃ�
		if (fValueV == 0)
		{
			// �L�[�{�[�h��[A]�������ꂽ�Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_A))
			{// ��
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = -ROT_LIMIT;

				// ��]�̖ڕW�n�_����
				m_difference.y = m_rot.y - ROT_SPEED;

				// ���[�V����������
				m_MotionType = PLAYER_MOTION_WALK;
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_D))
			{// �L�[�{�[�h��[D]�������ꂽ�Ƃ�
			 // �E
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = ROT_LIMIT;

				// ��]�̖ڕW�n�_����
				m_difference.y = m_rot.y + ROT_SPEED;

				// ���[�V����������
				m_MotionType = PLAYER_MOTION_WALK;
			}
		}

		// �R���g���[���[��[A]��������Ă��Ȃ��Ƃ�
		if (!pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_A))
		{
			// �L�[�{�[�h��[S]�������ꂽ�Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_S))
			{// ��
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = 0.0f;

				// ���[�V����������
				m_MotionType = PLAYER_MOTION_WALK;
			}
		}

		// �L�[�{�[�h��[S]��������Ă��Ȃ��Ƃ�
		if (!pInputKeyboard->GetKeyboardPress(DIK_S))
		{
			// �R���g���[���[��[A]�������ꂽ�Ƃ�
			if (pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_A))
			{
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;
				m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_SPEED_DOWN;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = 0.0f;

				// ���[�V����������
				m_MotionType = PLAYER_MOTION_WALK;
			}
		}

		// �ړ��L�[��������Ă��Ȃ��Ƃ�
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A) && fValueV == 0)
		{
			// ��]�̖ڕW�n�_�����߂�
			m_difference.z = 0.0f;

			// ��]�̖ڕW�n�_����
			m_difference.y = m_rot.y;

			// �L�[�{�[�h��[SPACE] ���� �R���g���[���[��[B]��������Ă��Ȃ��Ƃ�
			if (!pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || !pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_B))
			{
				// �^�C�g���̂Ƃ�
				if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
				{
					// ��ɑO�֐i�ނ悤�ɂ���
					m_move.x += sinf(D3DX_PI + m_rot.y) * TITLE_PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * TITLE_PLAYER_MOVE;
				}
				else
				{
					// ��ɑO�֐i�ނ悤�ɂ���
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
				}
			}
		}
	}
	else
	{// ���n���Ă��Ȃ��Ƃ�
		// �ړ��L�[��������Ă��Ȃ��Ƃ�
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A) && fValueV == 0)
		{
			// ��]�̖ڕW�n�_�����߂�
			m_difference.z = 0.0f;

			// ��]�̖ڕW�n�_����
			m_difference.y = m_rot.y;
		}

		// �R���g���[���[�̍��X�e�B�b�N��|���Ă��Ȃ��Ƃ�
		if (fValueV == 0)
		{
			// �L�[�{�[�h��[A]�������ꂽ�Ƃ�
			if (pInputKeyboard->GetKeyboardPress(DIK_A))
			{// ��
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
				m_move.z += 0.0f;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = -ROT_LIMIT;

				// ��]�̖ڕW�n�_����
				m_difference.y = m_rot.y - ROT_SPEED;
			}
			else if (pInputKeyboard->GetKeyboardPress(DIK_D))
			{// �L�[�{�[�h��[D]�������ꂽ�Ƃ�
				// �E
				m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
				m_move.z += 0.0f;

				// ��]�̖ڕW�n�_�����߂�
				m_difference.z = ROT_LIMIT;

				// ��]�̖ڕW�n�_����
				m_difference.y = m_rot.y + ROT_SPEED;
			}
		}

		// �L�[�{�[�h�̈ړ��L�[��������Ă��Ȃ��Ƃ�
		if (!pInputKeyboard->GetKeyboardPress(DIK_D) && !pInputKeyboard->GetKeyboardPress(DIK_A))
		{
			// ���X�e�B�b�N ���� �c�X�e�B�b�N��0����Ȃ��Ƃ�(�X�e�B�b�N���|��Ă���Ƃ�)
			if (fValueH != 0 || fValueV != 0)
			{
				// ���ɃX�e�B�b�N���|�ꂽ�Ƃ�
				if (fValueV >= -JOY_MAX_RANGE && fValueV < 0)
				{
					// �ړ��ʌv�Z
					fMove = fValueV * -PLAYER_TURNING_MOVE / JOY_MAX_RANGE;

					// �X�e�B�b�N�̌X���x�ňړ�������
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;

					// ��]�̖ڕW�n�_�����߂�
					m_difference.z = -ROT_LIMIT;

					// ��]�̖ڕW�n�_����
					m_difference.y = m_rot.y - ROT_SPEED;
				}
				else if (fValueV <= JOY_MAX_RANGE && fValueV > 0)
				{// �E�ɃX�e�B�b�N���|�ꂽ�Ƃ�
					// �ړ��ʌv�Z
					fMove = fValueV * PLAYER_TURNING_MOVE / JOY_MAX_RANGE;

					// �X�e�B�b�N�̌X���x�ňړ�������
					m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;
					m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_TURNING_MOVE;

					// ��]�̖ڕW�n�_�����߂�
					m_difference.z = ROT_LIMIT;

					// ��]�̖ڕW�n�_����
					m_difference.y = m_rot.y + ROT_SPEED;
				}
			}
		}
	}

	// �v���C���[�̉�]�ƖڕW�n�_�̍����i�[
	Diff.y = m_rot.y - m_difference.y;
	Diff.z = m_rot.z - m_difference.z;

	// D3DX_PI���傫���Ƃ�
	if (Diff.y > D3DX_PI)
	{
		Diff.y -= D3DX_PI * 2;
	}
	else if (Diff.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ƃ�
		Diff.y += D3DX_PI * 2;
	}

	// �v���C���[�����X�ɉ�]�����Ă���
	m_rot.y -= Diff.y * ROT_AMOUNT;
	m_rot.z -= Diff.z * ROT_AMOUNT;

	// �v���C���[�̉�]Z�������ȏゾ�����Ƃ�
	if (m_rot.z < -ROT_LIMIT)
	{
		// �ő吧���ɂ���
		m_rot.z = -ROT_LIMIT;
	}

	// �v���C���[�̉�]Z�������ȏゾ������
	if (m_rot.z > ROT_LIMIT)
	{
		// �ő吧���ɂ���
		m_rot.z = ROT_LIMIT;
	}
}

//==================================================================================================================
// �^�C�g���ł̃v���C���[�X�V����
//==================================================================================================================
void CPlayer::TitleUpdate(void)
{
	// �^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		// �^�C�g���t�F�[�h�̎擾
		CTitleFade::TITLE_FADE titleFade = CTitleFade::GetTitleFade();

		// �J�������擾
		CCamera *pCamera = CTitle::GetCamera();

		// �J�����̎��_�ʒu�擾
		D3DXVECTOR3 CameraposV = pCamera->GetPosV();

		// �^�C�g���̂Ƃ��͓����Ă�����Ԃɂ���
		m_bStart = true;

		// �v���C���[�̈ʒuZ���J�����̈ʒuZ�𒴂�����
		if (m_pos.z > CameraposV.z)
		{
			// �t�F�[�h���Ȃ��Ƃ�
			if (titleFade == CTitleFade::FADE_NONE)
			{
				// �t�F�[�h�A�E�g������
				CTitleFade::FadeOUT();

				// �t�F�[�h���Ă�����Ԃɂ���
				m_bTitleFade = true;

				// �t�F�[�h����ݒ菈��
				SetbTitleFade(m_bTitleFade);
			}
		}

		// �t�F�[�h���Ă�����Ԃ̂Ƃ�
		if (m_bTitleFade)
		{
			// �C���^�[�o���J�E���g���Z
			m_nCntTitleFade++;

			// �C���^�[�o���J�E���g���K��l�ȏ�̂Ƃ�
			if (m_nCntTitleFade >= INTERVAL_COUNT_MAX1)
			{
				// �t�F�[�h�C������
				CTitleFade::FadeIN();
			}

			// ��ɑO�֐i�ނ悤�ɂ���
			m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE_SPEED;
			m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE_SPEED;

		}
		else
		{
			// ��ɑO�֐i�ނ悤�ɂ���
			m_move.x += sinf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
			m_move.z += cosf(D3DX_PI + m_rot.y) * PLAYER_MOVE;
		}

	}
}

//==================================================================================================================
// �`���[�g���A���ł̃v���C���[�X�V����
//==================================================================================================================
void CPlayer::TutorialUpdate(void)
{
	// �L�[�{�[�h�̏��擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �R���g���[���[�̏��擾
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// �`���[�g���A���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		// ���f���̍ő��ރJ�E���g
		for (int nCnt = 0; nCnt < TUTORIAL_MAX_MODEL; nCnt++)
		{
			// ���f�����擾
			m_pModel = (CModel*)CScene::GetScene(PRIORITY_MODEL, nCnt);
		}

		// �L�[�{�[�h��[SPACE] ���� �Q�[���p�b�h��[B]�������ꂽ�Ƃ�
		if (pInputKeyboard->GetKeyboardPress(DIK_SPACE) || pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_B))
		{
			// �`���[�g���A���̂Ƃ��͓����Ă�����Ԃɂ���
			m_bStart = true;
		}
	}
}

//==================================================================================================================
// �Q�[���ł̃v���C���[�X�V����
//==================================================================================================================
void CPlayer::GameUpdate(void)
{
	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// ���f���̍ő吔�܂ŃJ�E���g
		for (int nCnt = 0; nCnt < GAME_MAX_MODEL; nCnt++)
		{
			// ���f�����擾
			m_pModel = (CModel*)CScene::GetScene(PRIORITY_MODEL, nCnt);
		}
	}
}

//==================================================================================================================
// �v���C���[���ł̃X�^�[�g�̍X�V����
//==================================================================================================================
void CPlayer::bStartUpdate(CFade::FADE fade)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �R���g���[���[�擾
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// �X�^�[�g���Ă��Ȃ��Ƃ�
	if (m_bStart == false)
	{
		// �X�^�[�g���͈ړ��X�s�[�h��0�ɂ���
		m_move.x = 0.0f;
		m_move.z = 0.0f;

		// ���n���Ă����Ԃɂ���
		m_bRand = true;
	}
	else
	{// �X�^�[�g�����Ƃ�
		// ���n���Ă���Ƃ�
		if (m_bRand)
		{
			// �^�C�g���̂Ƃ�
			if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
			{
				// �^�C�g���p�J�E���g���Z
				m_nCntTitle++;

				// �J�E���g���K��l�̂Ƃ�
				if (m_nCntTitle == JUMP_COUNT1)
				{
					// ���n���Ă��Ȃ���Ԃɂ���
					m_bRand = false;

					// ��Ɉړ��ʂ𑝂₷
					m_move.y += JUMP_MOVE;

					// �W�����v���Ă����Ԃɂ���
					m_bJump = true;

					// ���[�V����������
					m_MotionType = PLAYER_MOTION_JUMP;
				}
				else if (m_nCntTitle == JUMP_COUNT2)
				{// �J�E���g���K��l�̂Ƃ�
					// ���n���Ă��Ȃ���Ԃɂ���
					m_bRand = false;

					// ��Ɉړ��ʂ𑝂₷
					m_move.y += JUMP_MOVE;

					// �W�����v���Ă����Ԃɂ���
					m_bJump = true;

					// ���[�V����������
					m_MotionType = PLAYER_MOTION_JUMP;
				}
			}

			// �`���[�g���A�� ���� �Q�[���̂Ƃ�
			if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL || CRenderer::GetMode() == CRenderer::MODE_GAME)
			{
				// �L�[�{�[�h��[SPACE] ���� �R���g���[���[��B�������ꂽ�Ƃ�
				if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_B))
				{
					// ���n���Ă��Ȃ���Ԃɂ���
					m_bRand = false;

					// ��Ɉړ��ʂ𑝂₷
					m_move.y += JUMP_MOVE;

					// ���[�V����������
					m_MotionType = PLAYER_MOTION_JUMP;

					// �W�����v������Ԃɂ���
					m_bJump = true;
				}
			}

			// ���n�J�E���g��0�ɂ���
			m_nCntRand = 0;
		}
		else
		{// ���n���Ă��Ȃ��Ƃ�
		 // �W�����v�X�s�[�h���K��l�𒴂�����
			if (m_move.y > MAX_JAMP_SPEED)
			{
				// �W�����v�X�s�[�h���K��l�ɂ���
				m_move.y += MAX_JAMP_SPEED;
			}

			// ���n�J�E���g���K��l�͈͓��̂Ƃ�
			if (m_nCntRand >= 1 && m_nCntRand <= LANDING_CAUNT)
			{
				// �W�����v���Ă��Ȃ��Ƃ�
				if (m_bJump == false)
				{
					// �L�[�{�[�h��[SPACE] ���� �R���g���[���[��B�������ꂽ�Ƃ�
					if (pInputKeyboard->GetKeyboardTrigger(DIK_SPACE) || pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_B))
					{
						// ��Ɉړ��ʂ��K��l���₷
						m_move.y += JUMP_MOVE;

						// ���[�V����������
						m_MotionType = PLAYER_MOTION_JUMP;

						// �W�����v������Ԃɂ���
						m_bJump = true;
					}
				}
			}
		}

		// �ʒu�X�V
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		m_pos.z += m_move.z;

		// ����
		m_move.x += (0 - m_move.x) * REDUCE_SPEED;
		m_move.z += (0 - m_move.z) * REDUCE_SPEED;

		// ���f��������Ƃ�
		if (m_pModel != NULL)
		{
			// ���f�����w��̃��f���ɓ��������Ƃ�
			if ((m_pModel->CollisionBlock(m_pos, m_size, m_posOld, CModel::MODEL_GOAL_CIRCLE)) == true)
			{
				// �S�[�������J�E���g���Z
				m_nCntGoal++;

				// �S�[�������J�E���g���K��l�ȏゾ�����Ƃ�
				if (m_nCntGoal >= GOAL_COUNT)
				{
					// �L�^���s���Ă��Ȃ��Ƃ�
					if (m_bGoal == false)
					{
						// �`���[�g���A���̂Ƃ�
						if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
						{
							// �t�F�[�h�������Ȃ���
							if (fade == CFade::FADE_NONE)
							{
								// �t�F�[�h�̐ݒ�
								CFade::SetFade(CRenderer::MODE_GAME);
							}
						}

						// �Q�[���̂Ƃ�
						if (CRenderer::GetMode() == CRenderer::MODE_GAME)
						{
							// ���Ԏ擾
							int nTime = CTime::GetTime();

							// �L�^�̃Z�[�u
							m_pRecord->SaveData(nTime);

							// �L�^�̃��[�h
							m_pRecord->LoadData();
						}

						// �L�^������Ԃɂ���
						m_bGoal = true;

						// �S�[��������Ԃɂ���
						SetbGoal(m_bGoal);
					}
				}
			}
			else if ((m_pModel->CollisionBlockReturn(m_pos, m_size, m_posOld, CModel::MODEL_GOAL_CIRCLE)) == true)
			{// ���f�����w��̃��f���ɓ��������Ƃ�
				// �S�[�������J�E���g���Z
				m_nCntGoal--;

				// �S�[���J�E���g���K��l�ȉ��̂Ƃ�
				if (m_nCntGoal < 0)
				{
					// �S�[���J�E���g�K��l�ɂ���
					m_nCntGoal = 0;
				}
			}

			// �Q�[���̂Ƃ�
			if (CRenderer::GetMode() == CRenderer::MODE_GAME)
			{
				// �񋓌^��for��
				for (auto nCnt : { CModel::MODEL_RESPOWN0, CModel::MODEL_RESPOWN1, CModel::MODEL_RESPOWN2, CModel::MODEL_RESPOWN3, CModel::MODEL_RESPOWN4,
					CModel::MODEL_RESPOWN5, CModel::MODEL_RESPOWN6, CModel::MODEL_RESPOWN7, CModel::MODEL_RESPOWN8,
					CModel::MODEL_RESPOWN9, CModel::MODEL_RESPOWN10,CModel::MODEL_RESPOWN11, CModel::MODEL_RESPOWN12 })
				{
					// ���f�����擾
					m_pModel = (CModel*)CScene::GetScene(CScene::PRIORITY_MODEL, nCnt);

					// ���Ƌ������������Ƃ�
					if (m_pModel->CollisionSphere(m_pos, COLLISION_RADIUS1, COLLISION_RADIUS_PLAYER, nCnt) == true)
					{
						// ���X�|�[���ԍ��ݒ�
						m_nNumPlace = nCnt - CModel::MODEL_RESPOWN0;

						// ���X�|�[���ʒu�擾
						m_RespownPos = m_pModel->GetPos();

						// ���X�|�[����]�擾
						m_RespownRot = m_pModel->GetRot();

						// ���X�|�[���ꏊ�ݒ�
						SetnNumPlace(m_nNumPlace);
					}
				}
			}
		}

		// �S�[�����Ă���Ƃ�
		if (m_bGoal == true)
		{
			// �S�[�����͈ړ��X�s�[�h�����炵�Ă���
			m_move.x += sinf(D3DX_PI + m_rot.y) * -JUMP_SPEED;
			m_move.z += cosf(D3DX_PI + m_rot.y) * -JUMP_SPEED;

			// �ړ���X���K��l�ȉ��ɂȂ����Ƃ�
			if (m_move.x <= 0)
			{
				// �ړ��ʂȂ���
				m_move.x = 0;
			}

			// �ړ���Z���K��l�ȉ��ɂȂ����Ƃ�
			if (m_move.z <= 0)
			{
				// �ړ��ʂȂ���
				m_move.z = 0;
			}
		}

		// �`���[�g���A�� ���� �Q�[���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL || CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			// �ړ�����
			OperationMove(pInputKeyboard, pInputGamepad);
		}
	}
}

//==================================================================================================================
// �v���C���[���ł͈͓̔��ɂ���Ƃ��̍X�V����
//==================================================================================================================
void CPlayer::bRangeUpdate(float height)
{
	// ���b�V���t�B�[���h�͈͓̔��ɂ���Ƃ�
	if (m_bRange)
	{
		// �v���C���[���f���̈�ԉ��ʒuy��GetHeight���������Ƃ�
		if (m_pos.y < WhileY + height && m_pos.y >= height)
		{
			// ���n���Ă����Ԃɂ���
			m_bRand = true;

			// ���[�V����������
			m_MotionType = PLAYER_MOTION_LANDING;
		}
	}
	else
	{// ���b�V���t�B�[���h�͈̔͊O�ɂ���Ƃ�
		// �v���C���[�̈ʒuY���K��l�ȉ��̂Ƃ�
		if (m_pos.y <= CALCULATION_POS_Y)
		{
			// �W�����v���Ă��Ȃ��Ƃ�
			if (m_bJump == false)
			{
				// �d�͏���
				m_move.y += GRAVITY;

				// �����X�s�[�h���K��l�𒴂�����
				if (m_move.y < MAX_GRAVITY)
				{
					// �����X�s�[�h���K��l�ɂ���
					m_move.y = MAX_GRAVITY;
				}
			}
		}

		// ���n���Ă��Ȃ���Ԃɂ���
		m_bRand = false;
	}
}

//==================================================================================================================
// �v���C���[���ł̒��n���Ă��锻��̍X�V����
//==================================================================================================================
void CPlayer::bRandUpdate(float height)
{
	// ���n���Ă���Ƃ�
	if (m_bRand)
	{
		// ���[�V����������
		m_MotionType = PLAYER_MOTION_WALK;

		// �ʒu�ݒ�
		SetPos(D3DXVECTOR3(m_pos.x, height, m_pos.z));

		// �ړ���y�Ȃ���
		m_move.y = 0.0f;

		// �W�����v���Ă��Ȃ���Ԃɂ���
		m_bJump = false;
	}
	else
	{// ���n���Ă��Ȃ��Ƃ�
	 // �d�͏���
		m_move.y += GRAVITY;

		// �����X�s�[�h���K��l�𒴂�����
		if (m_move.y < MAX_GRAVITY)
		{
			// �����X�s�[�h���K��l�ɂ���
			m_move.y = MAX_GRAVITY;
		}

		// �W�����v���͈ړ��X�s�[�h��������������
		m_move.x += sinf(D3DX_PI + m_rot.y) * JUMP_SPEED;
		m_move.z += cosf(D3DX_PI + m_rot.y) * JUMP_SPEED;

		// ���n�J�E���g�����Z����
		m_nCntRand++;

		// �ʒu�ݒ�
		SetPos(D3DXVECTOR3(m_pos));
	}
}

//==================================================================================================================
// �v���C���[���ł̒��n�J�E���g�̍X�V����
//==================================================================================================================
void CPlayer::nCntRandUpdate(CMeshField *pMeshField, CIntervalFade::INTERVAL_FADE intervalFade)
{
	// ���n�J�E���g���K��l�𒴂����Ƃ�
	if (m_nCntRand >= RAND_COUNT - 20)
	{
		// �t�F�[�h���Ȃ��Ƃ�
		if (intervalFade == CIntervalFade::FADE_NONE)
		{
			// �t�F�[�h�A�E�g������
			CIntervalFade::FadeOUT();

			// �C���^�[�o���������Ԃɂ���
			m_bInterval = true;
		}
	}

	// ���n�J�E���g���K��l�𒴂����Ƃ�
	if (m_nCntRand >= RAND_COUNT)
	{
		// ���b�V���t�B�[���h������Ƃ�
		if (pMeshField != NULL)
		{
			// �`���[�g���A���̂Ƃ�
			if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
			{
				// �v���C���[��X�ʒu�����b�V���t�B�[���h��X�ʒu�ɂ���
				m_pos.x = pMeshField->GetPos().x;

				// �v���C���[��Y�ʒu�����b�V���t�B�[���h��Y�ʒu�ɂ���
				m_pos.y = WhileY;

				// �v���C���[�̉�]��i�s�����ɂ���
				m_rot.y = D3DX_PI;
			}
			else
			{// �Q�[���̂Ƃ�
				// �v���C���[�̈ʒu�����X�|�[���̈ʒu�ɂ���
				m_pos = m_RespownPos;

				// �v���C���[�̉�]�����X�|�[����]�ɂ���
				m_rot = m_RespownRot;
			}
		}

		// ���n���Ă����Ԃɂ���
		m_bRand = true;

		// ���X�|�[���J�E���g������
		m_nCntRand = 0;

		// ���X�|�[�����Ă����Ԃɂ���
		m_bRespawn = true;
	}
}

//==================================================================================================================
// �v���C���[���ł̃��f���̍X�V����
//==================================================================================================================
void CPlayer::PlayerModelUpdate(void)
{
	// �v���C���[���f���̍ő�p�[�c�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// ���f���̏I������
		m_MotionModel[nCnt]->Update();
	}
}

//==================================================================================================================
// �v���C���[���ł̃��b�V���t�B�[���h�̍X�V����
//==================================================================================================================
float CPlayer::MeshFieldUpdate(CMeshField * pMeshField)
{
	// �ϐ��̏�����
	float fHeight = 0.0f;

	// ���b�V���t�B�[���h������Ƃ�
	if (pMeshField != NULL)
	{
		// �������Z�o
		fHeight = pMeshField->GetHeight(m_pos);
	}

	// �l��Ԃ�
	return fHeight;
}

//==================================================================================================================
// ���n����擾
//==================================================================================================================
bool CPlayer::GetbRand(void)
{
	return m_bRand;
}

//==================================================================================================================
// �͈͓�����擾
//==================================================================================================================
bool CPlayer::GetbRange(void)
{
	return m_bRange;
}

//==================================================================================================================
// ���X�|�[������擾
//==================================================================================================================
bool CPlayer::GetRespawn(void)
{
	return m_bRespawn;
}

//==================================================================================================================
// �S�[������擾
//==================================================================================================================
bool CPlayer::GetbGoal(void)
{
	return m_bGoal;
}

//==================================================================================================================
// �X�^�[�g����擾
//==================================================================================================================
bool CPlayer::GetStart(void)
{
	return m_bStart;
}

//==================================================================================================================
// �^�C�g�����S����擾
//==================================================================================================================
bool CPlayer::GetbTitleLogo(void)
{
	return m_bTitleLogo;
}

//==================================================================================================================
// �^�C�g���t�F�[�h����擾
//==================================================================================================================
bool CPlayer::GetbTitleFade(void)
{
	return m_bTitleFade;
}

//==================================================================================================================
// ���[�V�����ǂݍ���
//==================================================================================================================
void CPlayer::LoadMotion(void)
{
	FILE *pFile;			// �t�@�C���|�C���g
	int nCntMotion = 0;		// ���[�V�����̐�
	int nCntModel = 0;		// ���f���̃J�E���g
	int nCntKeySet = 0;		// �t���[���̕�����
	int nCntKey = 0;		// �p�[�c�̔ԍ�
	char cReadText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����p
	char cDie[128];			// �s�v�ȕ���

	// �t�@�C�����J��
	pFile = fopen(MOTION_FILE_NAME, "r");

	// �t�@�C��������Ƃ�
	if (pFile != NULL)
	{
		// �ǂݍ��񂾕�����[SCRIPT]�܂ŌJ��Ԃ�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);						// �ꕶ��ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);							// ��r�p�e�L�X�g�ɕ�������
		}

		// �ǂݍ��񂾕�����[SCRIPT]�̂Ƃ�
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);					// �ꕶ��ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);						// ��r�p�e�L�X�g�ɕ�������

				// ���[�V�����Z�b�g��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// �t���[���������̏�����
					nCntKeySet = 0;

					// �G���h���[�V�����Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);			// �ꕶ��ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);				// ��r�p�e�L�X�g�ɕ�������

						// �ǂݍ��񂾕�����[LOOP]�̂Ƃ�
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nLoop);			// ���[�v�ϐ��ɒl����
						}
						// �ǂݍ��񂾕�����[NUM_KEY]�̂Ƃ�
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nNumKey);		// �L�[���̐��ɒl����
						}
						// �ǂݍ��񂾕�����[KEYSET]�̂Ƃ�
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							nCntKey = 0;									// �L�[��񏉊���

							// �ǂݍ��񂾕�����[END_KEYSET]�܂ŌJ��Ԃ�
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);							// �ꕶ��ǂݍ���
								sscanf(cReadText, "%s", &cHeadText);								// ��r�p�e�L�X�g�ɕ�������

								// �ǂݍ��񂾕�����[FRAME]�̂Ƃ�
								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie,
										&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram);	// �t���[���ɒl����
								}
								// �ǂݍ��񂾕�����[KEY]�̂Ƃ�
								else if (strcmp(cHeadText, "KEY") == 0)
								{
									// �ǂݍ��񂾕�����[END_KEY]�܂ŌJ��Ԃ�
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);				// �ꕶ��ǂݍ���
										sscanf(cReadText, "%s", &cHeadText);					// ��r�p�e�L�X�g�ɕ�������

										// �ǂݍ��񂾕�����[POS]�̂Ƃ�
										if (strcmp(cHeadText, "POS") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",					// �ʒu�ɒl����
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.z);

											//m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos += m_Model[nCntKey]->GetPosition();
										}
										// �ǂݍ��񂾕�����[ROT]�̂Ƃ�
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",					// ��]�ɒl����
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.z);
										}
									}

									// �p�[�c�ԍ����Z
									nCntKey++;
								}
							}

							// �t���[���̕��������Z
							nCntKeySet++;
						}
					}
					// ���[�V�����̐����Z
					nCntMotion++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	// �t�@�C���������Ƃ�
	else
	{
		// ���b�Z�[�W�Œm�点��
		MessageBox(NULL, "���[�V�����f�[�^�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

//==================================================================================================================
// ���[�V����������
//==================================================================================================================
void CPlayer::Moation(void)
{
	// �O�̃��[�V�����ƍ��̃��[�V�������Ⴄ�Ƃ�
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;					// �t���[���������l�ɖ߂�
		m_nCntKeySet = 0;			// ���[�V�������������l�ɖ߂�
	}

	// �v���C���[�̃��f���̍ő�p�[�c���܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PLAYER_MAX_MODEL; nCnt++)
	{
		// �t���[����0�̂Ƃ�
		if (m_Fram == 0)
		{
			// ���[�V�������̃t���[����0����Ȃ��Ƃ�
			if (m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram != 0)
			{
				// �ړ���ROT�̌v�Z
				rotBET[nCnt] = (m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].key[nCnt].rot - m_MotionModel[nCnt]->GetRot()) /
					(float)m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram;
			}
			else
			{
				//m_MotionModel[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[mCntKeySet].key[nCnt].pos;
				m_MotionModel[nCnt]->GetRot() = m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].key[nCnt].rot;
				posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		// �t���[���ړ�
		if (m_Fram <= m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram)
		{
			m_MotionModel[nCnt]->SetPos(m_MotionModel[nCnt]->GetPos() + posBET[nCnt]);
			m_MotionModel[nCnt]->SetRot(m_MotionModel[nCnt]->GetRot() + rotBET[nCnt]);
		}
	}

	// �t���[�������[�V�������̃t���[���Ɠ����ł���Ƃ�
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram)
	{
		m_nCntKeySet++;
		m_Fram = 0;

		// �L�[�Z�b�g�����K��l�Ɠ����ɂȂ�����
		if (m_nCntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			// ���[�v���Ȃ��Ƃ�
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_nCntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_nCntKeySet].nFram;
				//g_Player.bAttack = false;
			}
			// ���[�v����Ƃ�
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_nCntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}
	// �t���[�������K��l�Ɠ����ł͂Ȃ��Ƃ�
	else
	{
		// �t���[�����Z
		m_Fram++;
	}
}

//==================================================================================================================
// ���n����ݒ�
//==================================================================================================================
void CPlayer::SetbRand(bool bRand)
{
	m_bRand = bRand;
}

//==================================================================================================================
// �͈͓�����ݒ�
//==================================================================================================================
void CPlayer::SetbRange(bool bRange)
{
	m_bRange = bRange;
}

//==================================================================================================================
// ���X�|�[������ݒ�
//==================================================================================================================
void CPlayer::SetRespawn(bool bRespawn)
{
	m_bRespawn = bRespawn;
}

//==================================================================================================================
// �S�[������ݒ�
//==================================================================================================================
void CPlayer::SetbGoal(bool bGoal)
{
	m_bGoal = bGoal;
}

//==================================================================================================================
// �X�^�[�g����ݒ�
//==================================================================================================================
void CPlayer::SetbStart(bool bStart)
{
	m_bStart = bStart;
}

//==================================================================================================================
// �^�C�g�����S����ݒ�
//==================================================================================================================
void CPlayer::SetbTitleLogo(bool bTitleLogo)
{
	m_bTitleLogo = bTitleLogo;
}

//==================================================================================================================
// �^�C�g���t�F�[�h����ݒ�
//==================================================================================================================
void CPlayer::SetbTitleFade(bool bTitleFade)
{
	m_bTitleFade = bTitleFade;
}
