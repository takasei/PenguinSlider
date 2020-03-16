//==================================================================================================================
//
// fade�̕`�� [fade.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS							// �x�����

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "fade.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "sound.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MAX_TEST_COUNT 40		// �e�X�g�p�J�E���^�̍ő�l

//==================================================================================================================
// �ÓI�����o�ϐ��錾
//==================================================================================================================
LPDIRECT3DTEXTURE9 CFade::m_pTexture = NULL;					// �e�N�X�`�����
CRenderer::MODE CFade::m_modeNext = CRenderer::MODE_TITLE;		// ���̃��[�h
CFade::FADE CFade::m_fade = FADE_NONE;							// �t�F�[�h�̏��
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0, 0.0, 0.0, 1.0);	// �F���
float CFade::m_nCntFade = 0.05f;								// �t�F�[�h�J�E���g

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CFade::CFade()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CFade::~CFade()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CFade::Init(CRenderer::MODE modeNext)
{
	// ������
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0);			// �ʒu
	m_fade = FADE_IN;														// �t�F�[�h�̏��
	m_modeNext = modeNext;													// ���̃��[�h
	m_nCntTest = 0;															// �e�X�g�p�J�E���^
	m_nMode = CRenderer::MODE_TITLE;										// ���[�h�p�J�E���^
	m_bTest = false;														// �e�X�g�����邩�ǂ���

	CRenderer *pRenderer = CManager::GetRenderer();							// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();						// �f�o�C�X���擾����

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVertexBuff,
		NULL);

	VERTEX_2D *pVtx;														// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVertexBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�(�E���Őݒ肷��)
	pVtx[0].pos.x = m_pos.x + (-SCREEN_WIDTH / 2);
	pVtx[0].pos.y = m_pos.y + (-SCREEN_HEIGHT / 2);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + (+SCREEN_WIDTH / 2);
	pVtx[1].pos.y = m_pos.y + (-SCREEN_HEIGHT / 2);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + (-SCREEN_WIDTH / 2);
	pVtx[2].pos.y = m_pos.y + (+SCREEN_HEIGHT / 2);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + (+SCREEN_WIDTH / 2);
	pVtx[3].pos.y = m_pos.y + (+SCREEN_HEIGHT / 2);
	pVtx[3].pos.z = 0.0f;

	// �������W(1.0�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �F�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N
	m_pVertexBuff->Unlock();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CFade::Uninit(void)
{
	// �e�N�X�`�����p��
	Unload();

	// ���_�o�b�t�@������Ƃ�
	if (m_pVertexBuff != NULL)
	{
		m_pVertexBuff->Release();					// ���_�o�b�t�@�̊J��
		m_pVertexBuff = NULL;						// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;									// ���_���ւ̃|�C���^

	// �e�X�g������Ƃ�
	if (m_bTest)
	{
		// �e�X�g�p�J�E���^���Z
		m_nCntTest++;
	}

	// �J�E���^���K��l�𒴂����Ƃ�
	if (m_nCntTest >= MAX_TEST_COUNT)
	{
		// ���݂̃��[�h�ɂ���Đ؂�ւ���
		switch (m_modeNext)
		{
			// �^�C�g���̂Ƃ�
		case CRenderer::MODE_TITLE:
			m_modeNext = CRenderer::MODE_TUTORIAL;
			break;

			// �`���[�g���A���̂Ƃ�
		case CRenderer::MODE_TUTORIAL:
			m_modeNext = CRenderer::MODE_GAME;
			break;

			// �Q�[���̂Ƃ�
		case CRenderer::MODE_GAME:
			m_modeNext = CRenderer::MODE_RANKING;
			break;

			// �����L���O�̂Ƃ�
		case CRenderer::MODE_RANKING:
			m_modeNext = CRenderer::MODE_TITLE;
			break;
		}

		// �J�E���^�̏�����
		m_nCntTest = 0;

		// �t�F�[�h�̐ݒ�
		SetFade(m_modeNext);
	}

	// �t�F�[�h������Ƃ�
	if (m_fade != FADE_NONE)
	{
		// �t�F�[�h��Ԃ��C���̂Ƃ�
		if (m_fade == FADE_IN)
		{
			// �t�F�[�h�C������
			m_colorFade.a -= m_nCntFade;				// �����x���炵�Ă���

			// �����x��0�ȉ��������Ƃ�
			if (m_colorFade.a <= 0.0f)
			{
				// �t�F�[�h�����I��
				m_colorFade.a = 0.0f;					// �����x��0�ɂ���
				m_fade = FADE_NONE;						// �t�F�[�h��Ԃ������Ȃ���Ԃɂ���
			}
		}
		else if (m_fade == FADE_OUT)
		{// �t�F�[�h��Ԃ��A�E�g�̂Ƃ�
			//�t�F�[�h�A�E�g����
			m_colorFade.a += m_nCntFade;				// ��ʂ�s�����ɂ��Ă���

			// �����x��1���傫���Ȃ����Ƃ�
			if (m_colorFade.a >= 1.0f)
			{
				//�t�F�[�h�C�������ɐ؂�ւ�
				m_colorFade.a = 1.0f;					// �����x��1�ɂ���

				m_fade = FADE_IN;					// �t�F�[�h��Ԃ��C���̏�Ԃɂ���

				// ���[�h��ݒ�
				CRenderer::SetMode(m_modeNext);
			}
		}

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVertexBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		// ���_�f�[�^���A�����b�N����
		m_pVertexBuff->Unlock();
	}
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CFade::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();							// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();						// �f�o�C�X���擾����

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVertexBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// �t�F�[�h�̐ݒ�
//==================================================================================================================
void CFade::SetFade(CRenderer::MODE modeNext)
{
	// ���擾
	CSound *pSound = CRenderer::GetSound();

	m_fade = FADE_OUT;									// �t�F�[�h��Ԃ��A�E�g�ɂ���
	m_modeNext = modeNext;								// ���[�h�����̃��[�h�ɂ���
	pSound->PlaySound(CSound::SOUND_LABEL_SE_DECISION);	// ����{�^��
}

//==================================================================================================================
// �t�F�[�h�̎擾
//==================================================================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

//==================================================================================================================
// �I�u�W�F�N�g�̐���
//==================================================================================================================
CFade * CFade::Create(CRenderer::MODE modeNext)
{
	CFade *pFade = NULL;					// �t�F�[�h��NULL�ɂ���

	pFade = new CFade;						// ���I�Ɋm��
	pFade->Init(modeNext);					// ����������

	return pFade;							// �l��Ԃ�
}

//==================================================================================================================
// �e�N�X�`����񃍁[�h
//==================================================================================================================
HRESULT CFade::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X���擾����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,						// �f�o�C�X�ւ̃|�C���^
		"data/TEXTURE/",									// �t�@�C���̖��O
		&m_pTexture);										// �ǂݍ��ރ������[

	return S_OK;											// �l��Ԃ�
}

//==================================================================================================================
// �e�N�X�`�����j��
//==================================================================================================================
void CFade::Unload(void)
{
	// �e�N�X�`��������Ƃ�
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();					// �e�N�X�`���̊J��
		m_pTexture = NULL;						// NULL�ɂ���
	}
}

//==================================================================================================================
// �t�F�[�h�C������
//==================================================================================================================
void CFade::FadeIN(void)
{
	m_fade = FADE_IN;
}

//==================================================================================================================
// �t�F�[�h�A�E�g����
//==================================================================================================================
void CFade::FadeOUT(void)
{
	m_fade = FADE_OUT;
	m_colorFade = D3DXCOLOR(0.0, 0.0, 0.0, 0.0);	// �F������
}
