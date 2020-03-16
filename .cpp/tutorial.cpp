//==================================================================================================================
//
// tutorial�̕`�� [tutorial.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS											// �x�����

//==================================================================================================================
//	�C���N���[�h�t�@�C��
//==================================================================================================================
#include "tutorial.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "sound.h"
#include "scene2D.h"
#include "scene3D.h"
#include "camera.h"
#include "light.h"
#include "logo.h"
#include "meshField.h"
#include "player.h"
#include "motionModel.h"
#include "model.h"
#include "inputGamepad.h"
#include "meshSphere.h"
#include "intervalFade.h"

//==================================================================================================================
//	�ÓI�����o�ϐ��錾
//==================================================================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;			// �e�N�X�`�����
CCamera *CTutorial::m_pCamera = NULL;						// �J�������
CLight *CTutorial::m_pLight = NULL;							// ���C�g���
CPolygon *CTutorial::m_pPolygon = NULL;						// �|���S�����
CMeshField *CTutorial::m_pMeshField = NULL;					// ���b�V���t�B�[���h���
CPlayer *CTutorial::m_pPlayer = NULL;						// �v���C���[���
CLogo *CTutorial::m_pLogo = NULL;							// ���S���
CMeshSphere *CTutorial::m_pMeshSphere = NULL;				// ���b�V�������
CIntervalFade *CTutorial::m_pIntervalFade = NULL;			// �C���^�[�o���t�F�[�h���
CModel *CTutorial::m_pModel[TUTORIAL_MAX_MODEL] = {};		// ���f�����

//==================================================================================================================
//	�R���X�g���N�^
//==================================================================================================================
CTutorial::CTutorial()
{

}

//==================================================================================================================
//	�f�X�g���N�^
//==================================================================================================================
CTutorial::~CTutorial()
{

}

//==================================================================================================================
//	����������
//==================================================================================================================
void CTutorial::Init(void)
{
	CMeshField::Load();				// ���b�V���t�B�[���h�e�N�X�`�����[�h
	CMotionModel::Load();			// ���f�����[�h
	CLogo::Load();					// ���S���[�h
	CModel::Load();					// ���f�����[�h
	CMeshSphere::Load();			// ���b�V�����e�N�X�`�����[�h
	CIntervalFade::Load();			// �C���^�[�o���t�F�[�h�e�N�X�`�����[�h

	// �J�����̐�������
	m_pCamera = CCamera::Create();

	// ���C�g�̐�������
	m_pLight = CLight::Create();

	// �v���C���[����
	m_pPlayer = CPlayer::Create();
	// �v���C���ʒu�ݒ�
	m_pPlayer->SetPos(D3DXVECTOR3(0, 10, -900));

	// ���b�V���t�B�[���h����
	m_pMeshField = CMeshField::Create();

	// �S�[���ւ������f���̐�������
	m_pModel[0] = CModel::Create(CModel::MODEL_GOAL_CIRCLE);
	m_pModel[0]->SetPos(D3DXVECTOR3(0.0f, 10.0f, 500.0f));
	m_pModel[0]->SetSize(D3DXVECTOR3(5.0f, 5.0f, 5.0f));

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
}

//==================================================================================================================
//	�I������
//==================================================================================================================
void CTutorial::Uninit(void)
{
	// scene2D�̔j������
	CScene2D::ReleaseAll();

	// scene3D�̔j������
	CScene3D::ReleaseAll();

	CMeshField::Unload();			// ���b�V���t�B�[���h�e�N�X�`���A�����[�h
	CMotionModel::Unload();			// �v���C���[�e�N�X�`�����f���A�����[�h
	CLogo::Unload();				// ���S�A�����[�h
	CModel::Unload();				// ���f���A�����[�h
	CMeshSphere::Unload();			// ���b�V�����e�N�X�`���A�����[�h
	CIntervalFade::Unload();		// �C���^�[�o���t�F�[�h�e�N�X�`���A�����[�h

	delete m_pLight;				// �������폜
	m_pLight = nullptr;				// �|�C���^NULL

	delete m_pCamera;				// �������폜
	m_pCamera = nullptr;			// �|�C���^NULL
}

//==================================================================================================================
//	�X�V����
//==================================================================================================================
void CTutorial::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���p�b�h�̎擾
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// �t�F�[�h�擾
	CFade::FADE fade = CFade::GetFade();

	// �J�����̍X�V����
	m_pCamera->Update();

	// ���C�g�̍X�V����
	m_pLight->Update();

	// �L�[�{�[�h��[Enter] ���� �R���g���[���[��[START]���������Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_RETURN) || pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_START))
	{
		// �t�F�[�h�������Ȃ���
		if (fade == CFade::FADE_NONE)
		{
			// �t�F�[�h�̐ݒ�
			CFade::SetFade(CRenderer::MODE_GAME);
		}
	}
}

//==================================================================================================================
//	�`�揈��
//==================================================================================================================
void CTutorial::Draw(void)
{
	// �J�����̐ݒ�
	m_pCamera->SetCamera();

	// �J�����̕`�揈��
	m_pCamera->Draw();
}

//==================================================================================================================
// �I�u�W�F�N�g�̐���
//==================================================================================================================
CTutorial * CTutorial::Create(void)
{
	CTutorial *pTutorial = NULL;		// �`���[�g���A������NULL�ɂ���

	pTutorial = new CTutorial;			// ���I�Ɋm��
	pTutorial->Init();					// ����������

	return pTutorial;					// �l��Ԃ�
}

//==================================================================================================================
// �v���C���[���擾����
//==================================================================================================================
CPlayer * CTutorial::GetPlayer(void)
{
	return m_pPlayer;
}
