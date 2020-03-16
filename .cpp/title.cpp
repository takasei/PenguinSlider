//==================================================================================================================
//
// title�̕`�� [title.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS			// �x�����

//==================================================================================================================
//	�C���N���[�h�t�@�C��
//==================================================================================================================
#include "title.h"
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
#include "motionModel.h"
#include "player.h"
#include "inputGamepad.h"
#include "meshSphere.h"
#include "model.h"
#include "titleFade.h"

//==================================================================================================================
//	�}�N����`
//==================================================================================================================
#define MAX_FADE_COUNT 800			// �t�F�[�h�̂̃J�E���g�̍ő吔

//==================================================================================================================
//	�ÓI�����o�ϐ��錾
//==================================================================================================================
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;		// �e�N�X�`�����
CCamera *CTitle::m_pCamera = NULL;					// �J�������
CLight *CTitle::m_pLight = NULL;					// ���C�g���
CPolygon *CTitle::m_pPolygon = NULL;				// �|���S�����
CMeshField *CTitle::m_pMeshField = NULL;			// ���b�V���t�B�[���h���
CLogo *CTitle::m_pLogo = NULL;						// ���S���
CPlayer *CTitle::m_pPlayer = NULL;					// �v���C���[���
CMeshSphere *CTitle::m_pMeshSphere = NULL;			// ���b�V�������
CModel *CTitle::m_pModel[MAX_TITLE_MODEL] = {};		// ���f�����
CTitleFade *CTitle::m_pTitleFade = NULL;			// �^�C�g���t�F�[�h���

//==================================================================================================================
//	�R���X�g���N�^
//==================================================================================================================
CTitle::CTitle()
{

}

//==================================================================================================================
//	�f�X�g���N�^
//==================================================================================================================
CTitle::~CTitle()
{

}

//==================================================================================================================
//	����������
//==================================================================================================================
void CTitle::Init(void)
{
	//�ϐ��̏�����
	m_nCntRanking = 0;			// �����L���O�ւ̃J�E���^

	CMeshField::Load();			// ���b�V���t�B�[���h���[�h
	CLogo::Load();				// ���S���[�h
	CMotionModel::Load();		// ���[�V�����p���f�����[�h
	CMeshSphere::Load();		// ���b�V�����̃e�N�X�`�����[�h
	CModel::Load();				// ���f���̃��[�h

	// ���C�g�̐�������
	m_pLight = CLight::Create();

	// �J�����̐�������
	m_pCamera = CCamera::Create();

	// ���b�V��������
	m_pMeshSphere = CMeshSphere::Create();

	// �C���^�[�o���t�F�[�h�̐�������
	m_pTitleFade = CTitleFade::Create();
	// �傫���ݒ�
	m_pTitleFade->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
	// �ʒu�ݒ�
	m_pTitleFade->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	// �F�ݒ�
	m_pTitleFade->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	// �v���C���[����
	m_pPlayer = CPlayer::Create();
	// �v���C���ʒu�ݒ�
	m_pPlayer->SetPos(D3DXVECTOR3(0, 10, -900));

	// ���b�V���t�B�[���h����
	m_pMeshField = CMeshField::Create();

	// ���f���̐ݒ�
	SetModel();

	// ���S����
	m_pLogo = CLogo::Create();
}

//==================================================================================================================
//	�I������
//==================================================================================================================
void CTitle::Uninit(void)
{
	// scene2D�̔j������
	CScene2D::ReleaseAll();

	// scene3D�̔j������
	CScene3D::ReleaseAll();

	CMeshField::Unload();			// ���e�N�X�`���A�����[�h
	CLogo::Unload();				// ���S�A�����[�h
	CMotionModel::Unload();			// ���[�V�����p���f���A�����[�h
	CMeshSphere::Unload();			// ���b�V�����̃e�N�X�`���A�����[�h
	CModel::Unload();				// ���f���̃A�����[�h

	delete m_pLight;				// �������폜
	m_pLight = nullptr;				// �|�C���^NULL

	delete m_pCamera;				// �������폜
	m_pCamera = nullptr;			// �|�C���^NULL
}

//==================================================================================================================
//	�X�V����
//==================================================================================================================
void CTitle::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	//�R���g���[���[�̎擾
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
			CFade::SetFade(CRenderer::MODE_TUTORIAL);
		}
	}

	// �����L���O�ւ̃J�E���^���Z
	m_nCntRanking++;

	// �����L���O�J�E���^���K��l�𒴂�����
	if (m_nCntRanking >= MAX_FADE_COUNT)
	{
		// �t�F�[�h�������Ȃ���
		if (fade == CFade::FADE_NONE)
		{
			// �t�F�[�h�̐ݒ�
			CFade::SetFade(CRenderer::MODE_RANKING);
		}
	}
}

//==================================================================================================================
//	�`�揈��
//==================================================================================================================
void CTitle::Draw(void)
{
	// �J����������Ƃ�
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();			// �J�����̐ݒ�
		m_pCamera->Draw();				// �J�����̕`�揈��
	}
}

//==================================================================================================================
// �I�u�W�F�N�g�̐���
//==================================================================================================================
CTitle * CTitle::Create(void)
{
	CTitle *pTitle = NULL;			// �`���[�g���A������NULL�ɂ���

	pTitle = new CTitle;			// ���I�Ɋm��
	pTitle->Init();					// ����������

	return pTitle;					// �l��Ԃ�
}

//==================================================================================================================
// �v���C���[���擾
//==================================================================================================================
CPlayer * CTitle::GetPlayer(void)
{
	return m_pPlayer;
}

//==================================================================================================================
// �J�������擾
//==================================================================================================================
CCamera * CTitle::GetCamera(void)
{
	return m_pCamera;
}

//==================================================================================================================
// ���f���̐ݒ�
//==================================================================================================================
void CTitle::SetModel(void)
{
	int nNumber = 0;		// ���f���̔ԍ�

	// �y�䃂�f��
	m_pModel[nNumber] = CModel::Create(CModel::MODEL_FAUNDATIOIN0);	// ��������
	m_pModel[nNumber]->SetPos(D3DXVECTOR3(0.0f, 3.5f, 800.0f));	// �ʒu�ݒ�
	m_pModel[nNumber]->SetSize(D3DXVECTOR3(3.3f, 3.0f, 10.7f));		// �傫���ݒ�
	nNumber++;														// ���f���̔ԍ����Z
}
