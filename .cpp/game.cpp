//==================================================================================================================
//
// Game�̕`�� [game.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS											// �x�����

//==================================================================================================================
//	�C���N���[�h�t�@�C��
//==================================================================================================================
#include "game.h"
#include "player.h"
#include "number.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "meshField.h"
#include "scene3D.h"
#include "camera.h"
#include "light.h"
#include "time.h"
#include "renderer.h"
#include "logo.h"
#include "rankingNum.h"
#include "motionModel.h"
#include "model.h"
#include "pause.h"
#include "inputGamepad.h"
#include "intervalFade.h"
#include "meshSphere.h"

//==================================================================================================================
//	�}�N����`
//==================================================================================================================
#define PLAYER_START_POS_X 390.0f									// �v���C���[�̏����ʒuX
#define PLAYER_START_POS_Z -585.0f									// �v���C���[�̏����ʒuZ
#define RESPAWN_SIZE 1.0f											// ���X�|�[�����f���̑傫��

//==================================================================================================================
//	�ÓI�����o�ϐ��錾
//==================================================================================================================
CPlayer *CGame::m_pPlayer = NULL;									// �v���C���[���
CMeshField *CGame::m_pMeshField = NULL;								// ���b�V���t�B�[���h���
CCamera *CGame::m_pCamera = NULL;									// �J�������
CLight *CGame::m_pLight = NULL;										// ���C�g���
CLogo *CGame::m_pLogo = NULL;										// ���S���
CPause *CGame::m_pPause = NULL;										// �|�[�Y���
CIntervalFade *CGame::m_pIntervalFade = NULL;						// �C���^�[�o���t�F�[�h���
CMeshSphere *CGame::m_pMeshSphere = NULL;							// ���b�V�����̏��
CGame::GAMESTATE CGame::m_gameState = CGame::GAMESTATE_NONE;		// �Q�[�����
int CGame::m_nCounterGameState = NULL;								// �Q�[���̏�ԊǗ��J�E���^�[

//==================================================================================================================
//	�R���X�g���N�^
//==================================================================================================================
CGame::CGame()
{

}

//==================================================================================================================
//	�f�X�g���N�^
//==================================================================================================================
CGame::~CGame()
{
}

//==================================================================================================================
//	����������
//==================================================================================================================
void CGame::Init(void)
{
	CNumber::Load();						// �����e�N�X�`�����[�h
	CMeshField::Load();						// ���e�N�X�`�����[�h
	CNumber::Load();						// �����e�N�X�`�����[�h
	CLogo::Load();							// ���S�e�N�X�`�����[�h
	CMotionModel::Load();					// ���[�V�����p���f�����[�h
	CModel::Load();							// ���f�����[�h
	CPause::Load();							// �|�[�Y�e�N�X�`�����[�h
	CIntervalFade::Load();					// �C���^�[�o���t�F�[�h�e�N�X�`�����[�h
	CMeshSphere::Load();					// ���b�V�����̃e�N�X�`�����[�h

	// �J�����̐�������
	m_pCamera = CCamera::Create();

	// ���C�g�̐�������
	m_pLight = CLight::Create();

	// �v���C���[��������
	m_pPlayer = CPlayer::Create();
	// �ʒu�ݒ�
	m_pPlayer->SetPos(D3DXVECTOR3(PLAYER_START_POS_X, WhileY, PLAYER_START_POS_Z));
	// ��]�ݒ�
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));

	// �G�̐ݒ�
	//SetEnemy();

	// ���b�V���t�B�[���h����
	m_pMeshField = CMeshField::Create();

	// ���f���̐ݒ菈��
	SetModel();

	// ���b�V��������
	m_pMeshSphere = CMeshSphere::Create();

	// �C���^�[�o���t�F�[�h�̐�������
	m_pIntervalFade = CIntervalFade::Create();
	// �傫���ݒ�
	m_pIntervalFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
	// �ʒu�ݒ�
	m_pIntervalFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	// �F�ݒ�
	m_pIntervalFade->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	// ���S����
	m_pLogo = CLogo::Create();

	// �^�C���̐���
	CTime::Create();

	// �����L���O�X�R�A����
	CRankingNum *pRankingNum = CRankingNum::Create();
	// �����L���O�����ݒ�
	pRankingNum->AddRankingNum();

	// �|�[�Y�̐�������
	m_pPause = CPause::Create();

	SetGameState(GAMESTATE_NORMAL);			// �ʏ��Ԃɐݒ�
	m_nCounterGameState = 0;				// �Q�[���̏�ԊǗ��J�E���^�[��0�ɂ���
}

//==================================================================================================================
//	�I������
//==================================================================================================================
void CGame::Uninit(void)
{
	// �Q�[����Ԃ�ʏ�ɂ���
	m_gameState = GAMESTATE_NORMAL;

	CScene2D::ReleaseAll();				// 2D�̂��̑S�Ĕj��
	CScene3D::ReleaseAll();				// 3D�̂��̑S�Ĕj��

	CNumber::Unload();					// �����e�N�X�`���A�����[�h
	CMeshField::Unload();				// ���e�N�X�`���A�����[�h
	CLogo::Unload();					// ���S�A�����[�h
	CMotionModel::Unload();				// ���[�V�����p���f���A�����[�h
	CModel::Unload();					// ���f���A�����[�h
	CIntervalFade::Unload();			// �C���^�[�o���t�F�[�h�e�N�X�`���A�����[�h
	CMeshSphere::Unload();				// ���b�V�����̃e�N�X�`���A�����[�h

	// �|�[�Y�̏I������
	m_pPause->Uninit();

	delete m_pPause;					// �������폜
	m_pPause = nullptr;					// �|�C���^NULL

	delete m_pCamera;					// �������폜
	m_pCamera = nullptr;				// �|�C���^NULL

	delete m_pLight;					// �������폜
	m_pLight = nullptr;					// �|�C���^NULL
}

//==================================================================================================================
//	�X�V����
//==================================================================================================================
void CGame::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �R���g���[���[�擾
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// �t�F�[�h�擾
	CFade::FADE fade = CFade::GetFade();

	// �Q�[���̏�Ԏ擾
	m_gameState = GetGameState();

	// �Q�[����Ԃ��|�[�Y�̂Ƃ�
	if (m_gameState == GAMESTATE_PAUSE)
	{
		// �|�[�Y�̍X�V����
		m_pPause->Update();

		// �Q�[����Ԃ����߂����蒼���Ƃ�
		if (m_gameState == GAMESTATE_START_OVER)
		{
			// �t�F�[�h��ݒ肷��
			CFade::SetFade(CRenderer::MODE_GAME);
		}
		else if (m_gameState == GAMESTATE_BREAK)
		{// �Q�[����Ԃ����f�̂Ƃ�
			// �t�F�[�h��ݒ肷��
			CFade::SetFade(CRenderer::MODE_TITLE);
		}
	}
	else
	{
		// �J�����̍X�V����
		m_pCamera->Update();

		// ���C�g�̍X�V����
		m_pLight->Update();
	}

	// �L�[�{�[�h��[P] ���� �R���g���[���[��[START]�{�^���������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_P) || pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_START))
	{// �|�[�Y�؂�ւ�
		// �Q�[����Ԃ��|�[�Y�̂Ƃ�
		if (m_gameState == GAMESTATE_PAUSE)
		{
			// �Q�[����Ԃ�NORMAL�ɂ���
			m_gameState = GAMESTATE_NORMAL;

			// �|�[�Y��Ԃ̐ݒ�
			m_pPause->SetPause(false);
		}
		else
		{// �Q�[����Ԃ��|�[�Y����Ȃ��Ƃ�
			// �Q�[����Ԃ��|�[�Y�ɂ���
			m_gameState = GAMESTATE_PAUSE;

			// �|�[�Y��Ԃ̐ݒ�
			m_pPause->SetPause(true);
		}
	}
#ifdef _DEBUG
	// �L�[�{�[�h��[0]���������Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_0))
	{
		// �t�F�[�h�������Ȃ���
		if (fade == CFade::FADE_NONE)
		{
			// �t�F�[�h��ݒ肷��
			CFade::SetFade(CRenderer::MODE_RANKING);
		}
	}
#endif // _DEBUG
}

//==================================================================================================================
//	�`�揈��
//==================================================================================================================
void CGame::Draw(void)
{
	// �J�����̐ݒ�
	m_pCamera->SetCamera();

	// �J�����̕`�揈��
	m_pCamera->Draw();

	// �|�[�Y��Ԃ�true�̂Ƃ�
	if (m_pPause->GetPause() == true)
	{
		// �|�[�Y�̍X�V����
		m_pPause->Draw();
	}
}

//==================================================================================================================
//	��������
//==================================================================================================================
CGame * CGame::Create(void)
{
	CGame *pGame = NULL;		// �Q�[���ϐ�NULL

	pGame = new CGame;			// ���I�Ɋm��
	pGame->Init();				// ����������

	return pGame;				// �l��Ԃ�
}

//==================================================================================================================
//	�Q�[���̏�Ԑݒ�
//==================================================================================================================
void CGame::SetGameState(GAMESTATE state)
{
	m_gameState = state;
}

//==================================================================================================================
//	�Q�[���̏�Ԏ擾
//==================================================================================================================
CGame::GAMESTATE CGame::GetGameState(void)
{
	return m_gameState;
}

//==================================================================================================================
//	�v���C���[���擾
//==================================================================================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//==================================================================================================================
//	���f���̐ݒ�
//==================================================================================================================
void CGame::SetModel(void)
{
	// �z��ԍ�������
	int nNumber = 0;

	// �S�[���ւ������f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_GOAL_CIRCLE);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(470.0f, 10.0f, -585.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.0f, 3.0f, 3.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z1

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN0);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(520.0f, 10.0f, -585.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z2

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN1);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(870.0f, 10.0f, -585.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z3

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN2);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1050.0f, 18.0f, -585.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z4

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN3);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1250.0f, 80.0f, -1000.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	nNumber++;															// �z��ԍ����Z5

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN4);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(940.0f, 150.0f, -1100.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z6

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN5);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(940.0f, 250.0f, -200.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z7

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN6);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(750.0f, 250.0f, 125.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 4 * 3, 0.0f));// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z8

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN7);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(180.0f, 250.0f, 690.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 4 * 3, 0.0f));// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z9

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN8);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(250.0f, 250.0f, 960.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 4 * 3, 0.0f));// ��]�ݒ�10

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN9);			// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-120.0f, 200.0f, 1145.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	nNumber++;															// �z��ԍ����Z11

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN10);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-120.0f, 200.0f, 300.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	nNumber++;															// �z��ԍ����Z12

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN11);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-125.0f, 20.0f, -150.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	nNumber++;															// �z��ԍ����Z13

	// ���X�|�[�����f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_RESPOWN12);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(170.0f, 10.0f, -585.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(RESPAWN_SIZE, RESPAWN_SIZE, RESPAWN_SIZE));	// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z14

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(590.0f, 3.5f, -585.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 6.7f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z15

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-123.0f, 3.5f, -230.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.35f, 3.0f, 2.2f));			// �傫���ݒ�
	nNumber++;															// �z��ԍ����Z16

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1260.0f, 59.0f, -920.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 2.7f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.19f, 0.0f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z17

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(938.0f, 195.0f, -620.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 6.4f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(-0.1f, 0.0f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z18

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(530.0f, 246.0f, 346.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 6.9f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 2.36f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z19

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(262.0f, 246.0f, 986.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.4f, 3.0f, 1.5f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.8f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z20

	// �y�䃂�f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-120.0f, 184.0f, 620.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 8.4f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -0.01f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z21

	// �y��J�[�u���f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE0);// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-113.0f, 3.5f, -570.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z22

	// �y��J�[�u���f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE1);// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1260.0f, 3.5f, -600.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// �傫���ݒ�
	nNumber++;															// �z��ԍ����Z23

	// �y��J�[�u���f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE2);// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1247.0f, 99.0f, -1280.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z24

	// �y��J�[�u���f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE3);// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1001.0f, 248.0f, -134.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.75f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z25

	// �y��J�[�u���f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE4);// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(95.0f, 248.0f, 810.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -2.3f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z26

	// �y��J�[�u���f���̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN_CURVE5);// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-105.0f, 184.0f, 1450.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.5f, 3.0f, 3.5f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -1.55f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z27

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1340.0f, 30.0f, -585.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f));	// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z28

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1250.0f, 130.0f, -1385.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z29

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(1050.0f, 140.0f, -1385.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -2.5f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z30

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(900.0f, 150.0f, -1335.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -2.0f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z31

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(940.0f, 280.0f, 70.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z32

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(60.0f, 280.0f, 880.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -1.0f, 0.0f));			// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z33

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(530.0f, 260.0f, 1480.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, 0.5f, D3DX_PI));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z34

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-50.0f, 220.0f, 1650.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, -1.0f, D3DX_PI));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z35

	// �Ŕ̐�������
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_SIGNBOARD);		// ����
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(-50.0f, 40.0f, -620.0f));		// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(2.0f, 2.0f, 2.0f));			// �傫���ݒ�
	m_pModel[nNumber]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI));		// ��]�ݒ�
	nNumber++;															// �z��ԍ����Z36
}

