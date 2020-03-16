//==================================================================================================================
//
// �|�[�Y�̕`�� [pause.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#define _CRT_SECURE_NO_WARNINGS							// �x�����

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "pause.h"
#include "renderer.h"
#include "manager.h"
#include "inputKeyboard.h"
#include "inputGamepad.h"
#include "game.h"
#include "fade.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MAX_SELECT_TEXTURE 3	// �I���ł���e�N�X�`���̐�
#define SIZE_X 250.0f			// �e�N�X�`���̃T�C�YX
#define SIZE_Y 130.0f			// �e�N�X�`���̃T�C�YY
#define POS_X 640.0f			// �e�N�X�`����X���W�̈ʒu
#define POS_Y 100.0f			// ��ԏ�̃e�N�X�`��Y���W�Ɉʒu
#define SPACE_TEXTURE 150.0f	// �e�N�X�`���ƃe�N�X�`���̊Ԋu
#define FREAME_POSY 300.0f		// �t���[���e�N�X�`���ʒuY
#define FREAME_SIZEX 700.0f		// �t���[���e�N�X�`���傫��X
#define FREAME_SIZEY 720.0f		// �t���[���e�N�X�`���傫��Y
#define SELECT_SIZEX 500.0f		// �I���e�N�X�`���傫��X
#define SELECT_SIZEY 100.0f		// �I���e�N�X�`���傫��Y
#define SELECT_POSY 200.0f		// �I���e�N�X�`���ʒuY

//==================================================================================================================
// �ÓI�����o�ϐ��錾
//==================================================================================================================
LPDIRECT3DTEXTURE9 CPause::m_pTexture[PAUSETEXTURE_MAX] = {};			// �e�N�X�`�����
char *CPause::m_apFileName[PAUSETEXTURE_MAX] =							// �ǂݍ��ރ��f���̃\�[�X��
{
	{ "data/TEXTURE/pause.pn" },		// �|�[�Y�w�i
	{ "data/TEXTURE/pause.png" },		// �|�[�Y�t���[��
	{ "data/TEXTURE/select.png" },		// �I��
	{ "data/TEXTURE/continue.png" },	// ������
	{ "data/TEXTURE/restart.png" },		// �X�^�[�g�����蒼��
	{ "data/TEXTURE/title_go.png" },	// �^�C�g���ɂ���
};

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CPause::CPause()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CPause::~CPause()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CPause::Init(void)
{
	// ������
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);	// �ʒu
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);					// �F���
	m_nSelect = PAUSETEXTURE_CONTINUE;								// �I��ԍ�
	m_bPause = false;												// �|�[�Y�����ǂ���

	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X���擾����

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSETEXTURE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVertexBuff,
		NULL);

	// �w�i�̃e�N�X�`���ݒ�
	SetVertexPause(PAUSETEXTURE_BG, D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), SCREEN_WIDTH, SCREEN_HEIGHT);

	// �|�[�Y�t���[���̃e�N�X�`���ݒ�
	SetVertexPause(PAUSETEXTURE_FRAME, D3DXVECTOR3(SCREEN_WIDTH / 2, FREAME_POSY, 0), m_color, FREAME_SIZEX, FREAME_SIZEY);

	// �I���̃e�N�X�`���ݒ�
	SetVertexPause(PAUSETEXTURE_SELECT, D3DXVECTOR3(POS_X, SELECT_POSY, 0), m_color, SELECT_SIZEX, SELECT_SIZEY);

	// �񋓌^��for��
	for (auto nCnt : { PAUSETEXTURE_CONTINUE, PAUSETEXTURE_START, PAUSETEXTURE_TITLE })
	{
		// �e�N�X�`���ݒ�
		SetVertexPause(nCnt, D3DXVECTOR3(POS_X, POS_Y + SPACE_TEXTURE * (nCnt - 2), 0), m_color, SIZE_X, SIZE_Y);
	}
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CPause::Uninit(void)
{
	// �e�N�X�`�����p��
	Unload();

	// ���_�o�b�t�@������Ƃ�
	if (m_pVertexBuff != NULL)
	{
		m_pVertexBuff->Release();		// ���_�o�b�t�@�̊J��
		m_pVertexBuff = NULL;			// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CPause::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �R���g���[���[�擾
	CInputGamepad *pInputGamepad = CManager::GetInputGamepad();

	// �Q�[�����擾
	CGame *pGame = CRenderer::GetGame();

	// �t�F�[�h�擾
	CFade::FADE fade = CFade::GetFade();

	// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardTrigger(DIK_UPARROW))
	{// �I������
		m_nSelect--;
	}
	else if (pInputKeyboard->GetKeyboardTrigger(DIK_DOWNARROW))
	{// �L�[�{�[�h��[��]�������ꂽ�Ƃ�
		m_nSelect++;
	}

	// �R���g���[���[��[�\���L�[��]�������ꂽ�Ƃ�
	if (pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_UP))
	{//�I������
		m_nSelect--;
	}
	else if (pInputGamepad->GetTrigger(0, CInputGamepad::JOYPADKEY_DOWN))
	{// �R���g���[���[��[�\���L�[��]�������ꂽ�Ƃ�
		m_nSelect++;
	}

	// �I��ԍ����\������e�N�X�`���ԍ��𒴂�����
	if (m_nSelect == PAUSETEXTURE_MAX)
	{// �I�����̌J��Ԃ�����
		// 0�̖߂�
		m_nSelect = PAUSETEXTURE_CONTINUE;
	}
	else if (m_nSelect < PAUSETEXTURE_CONTINUE)
	{// �I��ԍ���PAUSETEXTURE_CONTINUE��菬�����Ȃ�����
		// �I��ԍ����ő�ɂ���
		m_nSelect = PAUSETEXTURE_TITLE;
	}

	// �I�����̕\������
	if (m_nSelect == PAUSETEXTURE_CONTINUE)
	{// �I��ԍ���0�̂Ƃ�
		// �I���e�N�X�`���̐ݒ�
		SetVertexPause(PAUSETEXTURE_SELECT, D3DXVECTOR3(POS_X, 250.0f, 0), m_color, SELECT_SIZEX, SIZE_Y);
	}
	else if (m_nSelect == PAUSETEXTURE_START)
	{// �I��ԍ���1�̂Ƃ�
		SetVertexPause(PAUSETEXTURE_SELECT, D3DXVECTOR3(POS_X, 400.0f, 0), m_color, SELECT_SIZEX, SIZE_Y);
	}
	else if (m_nSelect == PAUSETEXTURE_TITLE)
	{// �I��ԍ���2�̂Ƃ�
		SetVertexPause(PAUSETEXTURE_SELECT, D3DXVECTOR3(POS_X, 550.0f, 0), m_color, SELECT_SIZEX, SIZE_Y);
	}

	// �L�[�{�[�h��[�G���^�[] ���� �R���g���[���[��[B]�������ꂽ�Ƃ�
	if (pInputKeyboard->GetKeyboardPress(DIK_RETURN) || pInputGamepad->GetPress(0, CInputGamepad::JOYPADKEY_B))
	{
		// �I��ԍ����X�^�[�g�����蒼���ԍ��̂Ƃ�
		if (m_nSelect == PAUSETEXTURE_START)
		{
			// �Q�[���̏�Ԃ��X�^�[�g�����蒼���ɂ���
			pGame->SetGameState(CGame::GAMESTATE_START_OVER);
		}
		else if (m_nSelect == PAUSETEXTURE_TITLE)
		{// �I��ԍ����^�C�g���ւ����ԍ��̂Ƃ�
			// �Q�[����Ԃ𒆒f�ɂ���
			pGame->SetGameState(CGame::GAMESTATE_BREAK);
		}
		else
		{
			// �|�[�Y���false
			m_bPause = false;

			// �Q�[���̏�Ԃ�NORMAL�ɂ���
			pGame->SetGameState(CGame::GAMESTATE_NORMAL);
		}
	}
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CPause::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X���擾����

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVertexBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|�[�Y��Ԃ̂Ƃ�
	if (m_bPause == true)
	{
		// �e�N�X�`���̍ő吔�܂ŃJ�E���g
		for (int nCnt = 0; nCnt < PAUSETEXTURE_MAX; nCnt++)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCnt]);

			// �|���S���`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
		}
	}
}

//==================================================================================================================
// �I�u�W�F�N�g�̐���
//==================================================================================================================
CPause * CPause::Create(void)
{
	CPause *pPause = NULL;		// �|�[�Y�ϐ���NULL�ɂ���

	pPause = new CPause;		// ���I�Ɋm��
	pPause->Init();				// ����������

	return pPause;				// �l��Ԃ�
}

//==================================================================================================================
// �e�N�X�`����񃍁[�h
//==================================================================================================================
HRESULT CPause::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X���擾����

	//==============================�e�N�X�`���̓ǂݍ���==============================//
	// �e�N�X�`���̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PAUSETEXTURE_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, m_apFileName[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;		// �l��Ԃ�
}

//==================================================================================================================
// �e�N�X�`�����j��
//==================================================================================================================
void CPause::Unload(void)
{
	// �e�N�X�`���̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < PAUSETEXTURE_MAX; nCnt++)
	{
		// �e�N�X�`��������Ƃ�
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();	// �e�N�X�`���̊J��
			m_pTexture[nCnt] = NULL;		// NULL�ɂ���
		}
	}
}

//==================================================================================================================
// �|�[�Y��Ԑݒ菈��
//==================================================================================================================
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}

//==================================================================================================================
// �|�[�Y��Ԏ擾����
//==================================================================================================================
bool CPause::GetPause(void)
{
	return m_bPause;
}

//==================================================================================================================
// �|�[�Y�e�N�X�`���ݒ菈��
//==================================================================================================================
void CPause::SetVertexPause(PAUSETEXTURE number, D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight)
{
	VERTEX_2D *pVtx;					// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVertexBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += number * 4;

	// ���_���̐ݒ�
	// ���_���W�̐ݒ�(���x���W + �Ԋu * nCntScore (+ ��), ���y���W)
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth / 2, pos.y - fHeight / 2, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth / 2, pos.y - fHeight / 2, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth / 2, pos.y + fHeight / 2, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth / 2, pos.y + fHeight / 2, 0);

	// 1.0�ŌŒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �J���[�`���[�g�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// �e�N�X�`���`�ʂ̈ʒu
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^�̃A�����b�N
	m_pVertexBuff->Unlock();
}