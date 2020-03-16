//==================================================================================================================
//
// �����_���[[renderer.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "scene.h"
#include "debugProc.h"
#include "camera.h"
#include "light.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "ranking.h"
#include "record.h"
#include "sound.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CFade *CRenderer::m_pFade = NULL;						// Fade�̏��
CDebugProc *CRenderer::m_pDebugProc = NULL;				// �f�o�b�O�\�����
CCamera *CRenderer::m_pCamera = NULL;					// �J�����̏��
CLight *CRenderer::m_pLight = NULL;						// ���C�g�̏��
CGame *CRenderer::m_pGame = NULL;						// �Q�[�����
CTitle *CRenderer::m_pTitle = NULL;						// �^�C�g�����
CResult *CRenderer::m_pResult = NULL;					// ���U���g���
CRanking *CRenderer::m_pRanking = NULL;					// �����L���O���
CTutorial *CRenderer::m_pTutorial = NULL;				// �`���[�g���A�����
CSound *CRenderer::m_pSound = NULL;						// �����
CRenderer::MODE CRenderer::m_mode = MODE_TITLE;		// �ŏ��̉��

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CRenderer::CRenderer()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CRenderer::~CRenderer()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��(VSync��҂��ĕ`��)
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �N���C�A���g�̈�𒼂��ɍX�V����

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,											// �f�o�C�X�^�C�v
		hWnd,													// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,													// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&m_pD3DDevice)))										// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
#ifdef _DEBUG
	//�f�o�b�O���S�̏���������
	m_pDebugProc->Init();
#endif

	// �t�F�[�h�̃��[�h
	CFade::Load();

	// �t�F�[�h��������
	m_pFade = CFade::Create(m_mode);

	// ���I�m��
	m_pSound = new CSound;

	// ��������
	m_pSound->Init(hWnd);

	// �L�^�̓ǂݍ���
	m_pRecord->InitLoad();

	// �L�^�̕ۑ�
	m_pRecord->InitSave();

	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@(�J�����ƃI�u�W�F�N�g�̋������L��)���g�p
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�B�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	switch (m_mode)
	{
		// �^�C�g���̂Ƃ�
	case MODE_TITLE:
		// �^�C�g���̐���
		m_pTitle = CTitle::Create();
		// BGM�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMTITLE);
		break;

		// �`���[�g���A���̂Ƃ�
	case MODE_TUTORIAL:
		// �`���[�g���A���̐���
		m_pTutorial = CTutorial::Create();
		// BGM�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMTUTORIAL);
		break;

		// �Q�[���̂Ƃ�
	case MODE_GAME:
		// �Q�[���̐���
		m_pGame = CGame::Create();
		// BGM�Đ�
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMGAME);
		break;

		// �����L���O�̂Ƃ�
	case MODE_RANKING:
		// �����L���O�̐���
		m_pRanking = CRanking::Create();
		break;
	}

	// �l��Ԃ�
	return S_OK;
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	// �f�o�b�O���S�̏I������
	m_pDebugProc->Uninit();
#endif

	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();						// �J��
		m_pD3DDevice = NULL;							// NULL�ɂ���
	}
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();								// �J��
		m_pD3D = NULL;									// NULL�ɂ���
	}

	// �t�F�[�h������Ƃ�
	if (m_pFade != NULL)
	{
		// �I������
		m_pFade->Uninit();

		// �������폜
		delete m_pFade;

		// �|�C���^NULL
		m_pFade = nullptr;
	}

	// ��������Ƃ�
	if (m_pSound != NULL)
	{
		// ���̏I������
		m_pSound->Uninit();

		// �������폜
		delete m_pSound;

		// �|�C���^NULL
		m_pSound = nullptr;
	}

	switch (m_mode)
	{
		// �^�C�g���̂Ƃ�
	case MODE_TITLE:
		// �^�C�g���̏I������
		m_pTitle->Uninit();
		delete m_pTitle;		// �������̍폜
		m_pTitle = nullptr;		// �|�C���^NULL
		break;

		// �`���[�g���A���̂Ƃ�
	case MODE_TUTORIAL:
		// �`���[�g���A���̏I������
		m_pTutorial->Uninit();
		delete m_pTutorial;		// �������̍폜
		m_pTutorial = nullptr;	// �|�C���^NULL
		break;

		// �Q�[���̂Ƃ�
	case MODE_GAME:
		// �Q�[���̏I������
		m_pGame->Uninit();
		delete m_pGame;			// �������̍폜
		m_pGame = nullptr;		// �|�C���^NULL
		break;

		// �����L���O�̂Ƃ�
	case MODE_RANKING:
		// �����L���O�̏I������
		m_pRanking->Uninit();
		delete m_pRanking;		// �������̍폜
		m_pRanking = nullptr;	// �|�C���^NULL
		break;
	}

}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CRenderer::Update(void)
{
	// �Q�[���̏�Ԏ擾
	CGame::GAMESTATE gameState = CGame::GetGameState();

	// �Q�[����Ԃ��|�[�Y����Ȃ��Ƃ�
	if (gameState != CGame::GAMESTATE_PAUSE)
	{
		// Scene�ŊǗ����邷�ׂĂ̍X�V����
		CScene::UpdateAll();
	}

	// �t�F�[�h�̍X�V����
	m_pFade->Update();

	switch (m_mode)
	{
		// �^�C�g���̂Ƃ�
	case MODE_TITLE:
		// �X�V����
		m_pTitle->Update();
		break;

		// �`���[�g���A���̂Ƃ�
	case MODE_TUTORIAL:
		// �X�V����
		m_pTutorial->Update();
		break;

		// �Q�[���̂Ƃ�
	case MODE_GAME:
		// �X�V����
		m_pGame->Update();
		break;

		// �����L���O�̂Ƃ�
	case MODE_RANKING:
		// �X�V����
		m_pRanking->Update();
		break;
	}
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direc3D�ɂ��`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// Scene�ŊǗ����邷�ׂĂ̕`�揈��
		CScene::DrawAll();

		switch (m_mode)
		{
			// �^�C�g���̂Ƃ�
		case MODE_TITLE:
			// �`�揈��
			m_pTitle->Draw();
			break;

			// �`���[�g���A���̂Ƃ�
		case MODE_TUTORIAL:
			// �`�揈��
			m_pTutorial->Draw();
			break;

			// �Q�[���̂Ƃ�
		case MODE_GAME:
			// �`�揈��
			m_pGame->Draw();
			break;

			// �����L���O�̂Ƃ�
		case MODE_RANKING:
			// �`�揈��
			m_pRanking->Draw();
			break;
		}

		// �t�F�[�h������Ƃ�
		if (m_pFade != NULL)
		{
			// �t�F�[�h�̕`�揈��
			m_pFade->Draw();
		}

#ifdef _DEBUG
		// FPS�J�E���^�擾
		m_nCountFPS = GetFPS();

		// FPS�\��
		m_pDebugProc->Print("FPS:%d\n", m_nCountFPS);

		// �f�o�b�O���S�̕`��
		m_pDebugProc->Draw();
#endif

		// �J�n���ꂽ�V�[���̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==================================================================================================================
// ���[�h�̐ݒ�
//==================================================================================================================
void CRenderer::SetMode(MODE mode)
{
	// �w�肵�������~�߂�
	switch (mode)
	{
		// �^�C�g���̂Ƃ�
	case MODE_TITLE:
		// �����~�߂�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGMRESULT);
		m_pSound->StopSound(CSound::SOUND_LABEL_BGMGAME);
		break;

		// �`���[�g���A���̂Ƃ�
	case MODE_TUTORIAL:
		// �����~�߂�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGMTITLE);
		break;

		// �Q�[���Ƃ�
	case MODE_GAME:
		// �����~�߂�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGMTUTORIAL);
		break;

		// �����L���O�̂Ƃ�
	case MODE_RANKING:
		// �����~�߂�
		m_pSound->StopSound(CSound::SOUND_LABEL_BGMGAME);
		m_pSound->StopSound(CSound::SOUND_LABEL_BGMTITLE);

		break;
	}

	switch (m_mode)
	{
		// �^�C�g���̂Ƃ�
	case MODE_TITLE:
		// �I������
		m_pTitle->Uninit();
		// �j��
		delete m_pTitle;
		// NULL�ɂ���
		m_pTitle = nullptr;
		break;

		// �`���[�g���A���̂Ƃ�
	case MODE_TUTORIAL:
		// �I������
		m_pTutorial->Uninit();
		// �j��
		delete m_pTutorial;
		// NULL�ɂ���
		m_pTutorial = nullptr;
		break;

		// �Q�[���̂Ƃ�
	case MODE_GAME:
		// �I������
		m_pGame->Uninit();
		// �j��
		delete m_pGame;
		// NULL�ɂ���
		m_pGame = nullptr;
		break;

		// �����L���O�̂Ƃ�
	case MODE_RANKING:
		// �I������
		m_pRanking->Uninit();
		// �j��
		delete m_pRanking;
		// NULL�ɂ���
		m_pRanking = nullptr;
		break;
	}

	// ���[�h�ϐ�����
	m_mode = mode;

	switch (mode)
	{
		// �^�C�g���̂Ƃ�
	case MODE_TITLE:
		// ��������
		m_pTitle = CTitle::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMTITLE);
		break;

		// �`���[�g���A���̂Ƃ�
	case MODE_TUTORIAL:
		// ��������
		m_pTutorial = CTutorial::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMTUTORIAL);
		break;

		// �Q�[���̂Ƃ�
	case MODE_GAME:
		// ��������
		m_pGame = CGame::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMGAME);
		break;

		// �����L���O�̂Ƃ�
	case MODE_RANKING:
		// ��������
		m_pRanking = CRanking::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGMRESULT);
		break;
	}
}

//==================================================================================================================
// ���[�h�̎擾
//==================================================================================================================
CRenderer::MODE CRenderer::GetMode(void)
{
	return m_mode;
}

//==================================================================================================================
// �Q�[�����擾
//==================================================================================================================
CGame * CRenderer::GetGame(void)
{
	return m_pGame;
}

//==================================================================================================================
// �����擾
//==================================================================================================================
CSound * CRenderer::GetSound(void)
{
	return m_pSound;
}

//==================================================================================================================
// �f�o�C�X�擾
//==================================================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	// �l��Ԃ�
	return m_pD3DDevice;
}