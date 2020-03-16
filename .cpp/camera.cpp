//==================================================================================================================
//
// �J����[camera.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "camera.h"
#include "scene.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "title.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define camera_move 3.1f							// �J�����̈ړ��X�s�[�h
#define CAMERA_ROT_SPEED 0.05f						// �J�����̉�]�X�s�[�h
#define cameraLength 100.0f							// �J��������̋���
#define posR_Length 3.0f							// ���f���ƒ����_�̈ʒu
#define posR_distance 80.0f							// ���f���ƒ����_�̋���
#define coefficient 0.05f							// �W��
#define posV_distance 100.0f						// ���f���Ǝ��_�̋���
#define posV_Height 70.0f							// ���_�̍���
#define SHRINK_SPEED_Y 0.2f							// posV��Y�̏k�߂鑬�x
#define ROT_SHRINK 0.1f								// ��]�̏k�߂鑬�x
#define TITLE_FADE_COUNT 60							// �^�C�g���t�F�[�h�J�E���g
#define TITLE_POSV_X 200.0f							// �^�C�g���ł̃J�������_�ʒuX
#define TITLE_POSV_Y 20.0f							// �^�C�g���ł̃J�������_�ʒuY
#define TITLE_POSV_Z 650.0f							// �^�C�g���ł̃J�������_�ʒuZ
#define TITLE_POSR_X 0.0f							// �^�C�g���ł̃J���������_�ʒuX
#define TITLE_POSR_Y 1.0f							// �^�C�g���ł̃J���������_�ʒuY
#define TITLE_POSR_Z 650.0f							// �^�C�g���ł̃J���������_�ʒuZ
#define DISTANCE 100.0f								// ���_�ƒ����_�̋���
#define ROT_COUNT 5									// ��]���n�߂�J�E���g

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CCamera *CCamera::m_pCamera = NULL;					// �J�������
CPlayer *CCamera::m_pPlayer = NULL;					// �v���C���[���

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CCamera::CCamera()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CCamera::~CCamera()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CCamera::Init(void)
{
	// �ϐ��̏�����
	m_posV = D3DXVECTOR3(0.0f, 35.0f, -100.0f);			// ���_
	m_posVDest = D3DXVECTOR3(0.0f, 50.0f, -100.0f);		// ���_�̖ڕW�n�_
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// �����_
	m_posRDest = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			// �����_�̖ڕW�n�_
	m_posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ��]�̖ڕW�n�_
	m_fDistance = DISTANCE;								// ���_�ƒ����_�̋���
	nCntRot = 0;										// ��]���n�߂�J�E���^
	m_nCntTitleFade = 0;								// �^�C�g���t�F�[�h�J�E���^

	// �Q�[�����[�h���^�C�g�� ���� �`���[�g���A�� ���� �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE || CRenderer::GetMode() == CRenderer::MODE_TUTORIAL || CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ��]
	}
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CCamera::Uninit(void)
{

}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CCamera::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[�����[�h���^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{	
		D3DXVECTOR3 fDiff;								// �v�Z�p�i�[�ϐ�
		D3DXVECTOR3 rot;								// �v���C���[�p��]�ϐ�
		D3DXVECTOR3 pos;								// �v���C���[�p�ʒu�ϐ�
		D3DXVECTOR3 move;								// �v���C���[�p�ړ��ʕϐ�
		bool bTitleFade;								// �^�C�g���t�F�[�h����ϐ�

		m_pPlayer = CTitle::GetPlayer();				// �v���C���[���擾

		// �v���C���[������Ƃ�
		if (m_pPlayer != NULL)
		{
			rot = m_pPlayer->GetRot();					// �v���C���[�̉�]���擾
			pos = m_pPlayer->GetPos();					// �v���C���[�̈ʒu���擾
			move = m_pPlayer->GetMove();				// �v���C���[�̈ړ��ʏ��擾
			bTitleFade = m_pPlayer->GetbTitleFade();	// �^�C�g���t�F�[�h����擾
		}

		// �^�C�g���t�F�[�h��false�̂Ƃ�
		if (!bTitleFade)
		{
			// ��]�̍ŏI�ړI�n
			m_rotDest.y = rot.y;

			// ��]���̍����i�[
			fDiff.y = m_rot.y - m_rotDest.y;

			// ����D3DX_PI���傫���Ƃ�
			if (fDiff.y > D3DX_PI)
			{
				// ����߂�
				fDiff.y -= D3DX_PI * 2;
			}
			else if (fDiff.y < -D3DX_PI)
			{// ����-D3DX_PI��菬�����Ƃ�
				// ������₷
				fDiff.y += D3DX_PI * 2;
			}

			// ��Βl��0.0f��菬�����Ƃ�
			if (fabsf(fDiff.y) < 0.0f)
			{
				// �����Ȃ���
				fDiff.y = 0.0f;
			}

			// ���_�̍ŏI�ړI���W�̌v�Z
			m_posVDest.x = pos.x + sinf(m_rot.y) * m_fDistance;
			m_posVDest.y = pos.y + cosf(D3DX_PI + m_rot.x) * (-m_fDistance + posV_Height);
			m_posVDest.z = pos.z + cosf(m_rot.y) * m_fDistance;

			// �����_�̍ŏI�ړI���W�̌v�Z
			m_posRDest.x = pos.x + sinf(m_rot.y);
			m_posRDest.y = pos.y + sinf(D3DX_PI + m_rot.x);
			m_posRDest.z = pos.z + cosf(D3DX_PI + m_rot.y) * posR_Length;

			// �v���C���[�̈ʒuZ���J�����̈ʒuZ��菬�����Ƃ�
			if (pos.z <= m_posV.z)
			{
				m_posR += (m_posRDest - m_posR) * 1.0f;
			}
		}
		else
		{// �^�C�g���t�F�[�h��true�̂Ƃ�
			// �^�C�g���t�F�[�h�J�E���^���Z
			m_nCntTitleFade++;

			// �^�C�g���t�F�[�h�J�E���^���K��l�𒴂����Ƃ�
			if (m_nCntTitleFade >= TITLE_FADE_COUNT)
			{
				// ���_�̍ŏI�ړI���W�̌v�Z
				m_posVDest.x = TITLE_POSV_X;
				m_posVDest.y = TITLE_POSV_Y;
				m_posVDest.z = TITLE_POSV_Z;

				// �����_�̍ŏI�ړI���W�̌v�Z
				m_posRDest.x = TITLE_POSR_X;
				m_posRDest.y = TITLE_POSR_Y;
				m_posRDest.z = TITLE_POSR_Z;

				// �J�����̈ʒu�K��
				m_posV.x += (m_posVDest.x - m_posV.x) * 1.0f;
				m_posV.y += (m_posVDest.y - m_posV.y) * SHRINK_SPEED_Y;
				m_posV.z += (m_posVDest.z - m_posV.z) * 1.0f;
				m_posR += (m_posRDest - m_posR) * 1.0f;
			}
		}
	}
	
	// �Q�[�����[�h���Q�[���̂Ƃ� ���� �`���[�g���A���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME || CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		D3DXVECTOR3 fDiff;									// �v�Z�p�i�[�ϐ�
		D3DXVECTOR3 rot;									// �v���C���[�p��]�ϐ�
		D3DXVECTOR3 pos;									// �v���C���[�p�ʒu�ϐ�
		D3DXVECTOR3 move;									// �v���C���[�p�ړ��ʕϐ�

		// �Q�[�����[�h���`���[�g���A���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
		{
			m_pPlayer = CTutorial ::GetPlayer();			// �v���C���[���擾
		}

		// �Q�[�����[�h���Q�[���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			m_pPlayer = CGame::GetPlayer();					// �v���C���[���擾
		}

		// �v���C���[������Ƃ�
		if (m_pPlayer != NULL)
		{
			rot = m_pPlayer->GetRot();						// �v���C���[�̉�]���擾
			pos = m_pPlayer->GetPos();						// �v���C���[�̈ʒu���擾
			move = m_pPlayer->GetMove();					// �v���C���[�̈ړ��ʏ��擾
		}

		// ��]�̍ŏI�ړI�n
		m_rotDest.y = rot.y;

		// ��]���̍����i�[
		fDiff.y = m_rot.y - m_rotDest.y;

		// ����D3DX_PI���傫���Ƃ�
		if (fDiff.y > D3DX_PI)
		{
			// ����߂�
			fDiff.y -= D3DX_PI * 2;
		}
		else if (fDiff.y < -D3DX_PI)
		{// ����-D3DX_PI��菬�����Ƃ�
			// ������₷
			fDiff.y += D3DX_PI * 2;
		}

		// ��Βl��0.0f��菬�����Ƃ�
		if (fabsf(fDiff.y) < 0.0f)
		{
			// �����Ȃ���
			fDiff.y = 0.0f;
		}

		// ���_�̍ŏI�ړI���W�̌v�Z
		m_posVDest.x = pos.x + sinf(m_rot.y) * m_fDistance;
		m_posVDest.y = pos.y + cosf(D3DX_PI + m_rot.x) * (-m_fDistance + posV_Height);
		m_posVDest.z = pos.z + cosf(m_rot.y) * m_fDistance;

		// �����_�̍ŏI�ړI���W�̌v�Z
		m_posRDest.x = pos.x + sinf(m_rot.y);
		m_posRDest.y = pos.y + sinf(D3DX_PI + m_rot.x);
		m_posRDest.z = pos.z + cosf(D3DX_PI + m_rot.y) * posR_Length;

		// �J�����̈ʒu�K��
		m_posV.x += (m_posVDest.x - m_posV.x) * 1.0f;
		m_posV.y += (m_posVDest.y - m_posV.y) * SHRINK_SPEED_Y;
		m_posV.z += (m_posVDest.z - m_posV.z) * 1.0f;
		m_posR += (m_posRDest - m_posR) * 1.0f;

		// �L�[�{�[�h��[A]�܂���[D]���������Ƃ�
		if (pInputKeyboard->GetKeyboardPress(DIK_A) || pInputKeyboard->GetKeyboardPress(DIK_D))
		{
			// ��]���n�߂�J�E���g�����Z
			nCntRot++;
		}
		else if (!pInputKeyboard->GetKeyboardPress(DIK_A) && !pInputKeyboard->GetKeyboardPress(DIK_D))
		{// �L�[�{�[�h��[A]��[D]��������Ă��Ȃ��Ƃ�
			// ��]���n�߂�J�E���^������
			nCntRot = 0;

			// �������X�ɏk�߂Ă���
			m_rot.y -= fDiff.y * ROT_SHRINK;
		}

		// ��]���n�߂�J�E���^���K��l�𒴂����Ƃ�
		if (nCntRot >= ROT_COUNT)
		{
			// �������X�ɏk�߂Ă���
			m_rot.y -= fDiff.y * ROT_SHRINK;
		}
	}

#ifdef _DEBUG
	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_LEFTARROW))
	{
		// ���_�����ɓ�����
		m_posV.x += sinf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posV.z += cosf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;

		// ���_�����ɓ�����
		m_posR.x += sinf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posR.z += cosf(-D3DX_PI * 0.5f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_RIGHTARROW))
	{
		// ���_���E�ɓ�����
		m_posV.x += sinf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posV.z += cosf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
		// ���_���E�ɓ�����
		m_posR.x += sinf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
		m_posR.z += cosf(D3DX_PI * 0.5f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_UP))
	{
		// ���_��O�ɓ�����
		m_posV.x += sinf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		m_posV.z += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		// ���_��O�ɓ�����
		m_posR.x += sinf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		m_posR.z += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_DOWN))
	{
		// ���_�����ɓ�����
		m_posV.x += sinf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
		m_posV.z += cosf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
		// ���_�����ɓ�����
		m_posR.x += sinf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
		m_posR.z += cosf(-D3DX_PI * 1.0f + m_rot.y) * camera_move;
	}

	if (pInputKeyboard->GetKeyboardPress(DIK_1))
	{// �L�[�{�[�h��[1]�������ꂽ�Ƃ�
		// ���_����ɓ�����
		m_posV.y += cosf(D3DX_PI * 1.0f + m_rot.y) * camera_move;
		// ���_����ɓ�����
		m_posR.y += cosf(D3DX_PI * 1.0f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[2]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_2))
	{
		// ���_�����ɓ�����
		m_posV.y += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
		// ���_�����ɓ�����
		m_posR.y += cosf(D3DX_PI * 0.0f + m_rot.y) * camera_move;
	}

	// �L�[�{�[�h��[Q]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_Q))
	{
		// ���_�𒆐S�ɉ�]����(�����)
		m_rot.y -= CAMERA_ROT_SPEED;

		// ��]���-D3DX_PI��菬�����Ȃ����Ƃ�
		if (m_rot.y < -D3DX_PI)
		{
			// �����]������
			m_rot.y += D3DX_PI * 2;
		}
	}

	// �L�[�{�[�h��[E]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_E))
	{
		// ���_�𒆐S�ɉ�]����(�E���)
		m_rot.y += CAMERA_ROT_SPEED;

		// ��]���D3DX_PI���傫���Ȃ����Ƃ�
		if (m_rot.y > D3DX_PI)
		{
			// ����߂�
			m_rot.y -= D3DX_PI * 2;
		}
	}

	// �L�[�{�[�h��[C]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_C))
	{
		// �����_�𒆐S�ɉ�]����(�E���)
		m_rot.y -= CAMERA_ROT_SPEED;

		// ��]���-D3DX_PI��菬�����Ȃ����Ƃ�
		if (m_rot.y < -D3DX_PI)
		{
			// �����]������
			m_rot.y += D3DX_PI * 2;
		}
	}

	// �L�[�{�[�h��[Z]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_Z))
	{
		// �����_�𒆐S�ɉ�]����(�����)
		m_rot.y += CAMERA_ROT_SPEED;

		// ��]���D3DX_PI���傫���Ȃ����Ƃ�
		if (m_rot.y > D3DX_PI)
		{
			// ����߂�
			m_rot.y -= D3DX_PI * 2;
		}
	}
#endif // _DEBUG

	// ��]���ݒ�
	SetRot(m_rot);

	// ���_�ʒu�ݒ�
	SetPosV(m_posV);
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CCamera::Draw(void)
{
#ifdef _DEBUG
	// �f�o�b�O�\��
	CDebugProc::Print("�����_�ʒu�F%.2f, %.2f, %.2f\n", m_posR.x, m_posR.y, m_posR.z);
	CDebugProc::Print("���_�ʒu �F%.2f, %.2f, %.2f\n", m_posV.x, m_posV.y, m_posV.z);
	CDebugProc::Print("�J������] �F%.2f, %.2f, %.2f\n", m_rot.x, m_rot.y, m_rot.z);
#endif // _DEBUG
}

//==================================================================================================================
// �J�����̐ݒ�
//==================================================================================================================
void CCamera::SetCamera(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X���擾����

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(
		&m_mtxProjection,
		D3DXToRadian(45.0f),										// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,					// �A�X�y�N�g��
		10.0f,														// NearZ�l
		6000.0f);													// FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(
		&m_mtxView,
		&m_posV,													// �J�����̎��_
		&m_posR,													// �J�����̒����_
		&m_posU);													// �J�����̏�����x�N�g��

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//==================================================================================================================
// �J�����̉�]���ݒ�
//==================================================================================================================
void CCamera::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==================================================================================================================
// ���_�ʒu�ݒ菈��
//==================================================================================================================
void CCamera::SetPosV(D3DXVECTOR3 posV)
{
	m_posV = posV;
}

//==================================================================================================================
// �J�����̉�]���擾
//==================================================================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//==================================================================================================================
// ���_�ʒu�擾
//==================================================================================================================
D3DXVECTOR3 CCamera::GetPosV(void)
{
	return m_posV;
}

//==================================================================================================================
// �J�����̐���
//==================================================================================================================
CCamera * CCamera::Create(void)
{
	// �������𓮓I�Ɋm��
	m_pCamera = new CCamera();

	// �J�����̏�����
	m_pCamera->Init();

	// �l��Ԃ�
	return m_pCamera;
}