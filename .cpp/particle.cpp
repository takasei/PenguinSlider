//==================================================================================================================
//
// �p�[�e�B�N������[particle.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "debugProc.h"
#include "particle.h"
#include "renderer.h"
#include "manager.h"
#include "math.h"
#include <time.h>
#include "player.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "inputKeyboard.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define PARTICLE_TEXTURE "data/TEXTURE/shadow000.jpg"	// �ǂݍ��ރe�N�X�`���̃\�[�X��
#define PARTICLE_SIZE 7									// �p�[�e�B�N���̑傫��
#define RANDOM_RANGE 50									// �����_���̍ő�͈�
#define PARTICLE_LIFE 20								// �p�[�e�B�N���̃��C�t
#define PARTICLE_GRAVITY 0.2f							// �p�[�e�B�N���̏d��
#define PARTICLE_FRICTION 0.95f							// �p�[�e�B�N���̖��C
#define PARTICLE_DECREASE 0.01f							// �p�[�e�B�N���̑傫��������
#define RARTICLE_RAND 400								// �p�[�e�B�N���̃����_���͈�

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;	// �e�N�X�`���ϐ�
CParticle *CParticle::m_pParticle[MAX_PARTICLE] = {};// �p�[�e�B�N�����

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CParticle::CParticle(PRIORITY type = CScene::PRIORITY_EFFECT) :CScene(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CParticle::~CParticle()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CParticle::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾

	// �ʒu�E��]�̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);												// ��]
	m_move.x = (float(rand() % RARTICLE_RAND) - float(rand() % RARTICLE_RAND)) / 100;	// X�ړ���
	m_move.y = (float(rand() % RARTICLE_RAND) - float(rand() % RARTICLE_RAND)) / 100;	// Y�ړ���
	m_move.z = (float(rand() % RARTICLE_RAND) - float(rand() % RARTICLE_RAND)) / 100;	// Z�ړ���
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);												// �傫��
	m_nLife = PARTICLE_LIFE;															// ���C�t

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//���_���W�̐ݒ�(�E���Őݒ肷��)
	m_pVtx[0].pos = D3DXVECTOR3(-PARTICLE_SIZE / 2, +PARTICLE_SIZE / 2, 0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(+PARTICLE_SIZE / 2, +PARTICLE_SIZE / 2, 0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(-PARTICLE_SIZE / 2, -PARTICLE_SIZE / 2, 0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(+PARTICLE_SIZE / 2, -PARTICLE_SIZE / 2, 0.0f);

	//�@���x�N�g���̐ݒ�
	m_pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	m_pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//�F�̐ݒ�
	m_pVtx[0].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);
	m_pVtx[1].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);
	m_pVtx[2].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);
	m_pVtx[3].col = D3DXCOLOR(0.4980f, 1.0f, 0.8313f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	m_pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CParticle::Uninit(void)
{
	// ���_�o�b�t�@��NULL����Ȃ��Ƃ�
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();				// ���_�o�b�t�@�̊J��
		m_pVtxBuff = NULL;					// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CParticle::Update(void)
{
	// ������
	srand((unsigned)time(NULL));

	// �傫���擾
	m_size = GetSize();

	// ���C�t��1������
	m_nLife--;

	// ���C�t�������Ȃ�����
	if (m_nLife <= 0)
	{
		// ����
		Release();
		return;
	}

	// �ʒu�X�V
	m_pos += m_move;

	// ���C�v�Z
	m_move.x *= PARTICLE_FRICTION;
	m_move.y *= PARTICLE_FRICTION;
	m_move.z *= PARTICLE_FRICTION;

	// �傫�������񂾂񏬂�������
	m_size.x -= PARTICLE_DECREASE;
	m_size.y -= PARTICLE_DECREASE;

	// �d��
	m_move.y -= PARTICLE_GRAVITY;

	// �傫���ݒ�
	SetSize(m_size);

	// �ړ��ʐݒ�
	SetMove(m_move);
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CParticle::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxView;			// �v�Z�p�}�g���b�N�X

	// ���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);		// ���݂̃r���[�}�g���b�N�X���擾
	m_mtxWorld._11 = mtxView._11;						// �t�s���ݒ�
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//���e�X�g
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//���e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 220);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CParticle::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// �傫���ݒ�
//==================================================================================================================
void CParticle::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//==================================================================================================================
// �ړ��ʐݒ�
//==================================================================================================================
void CParticle::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//==================================================================================================================
// �|���S������
//==================================================================================================================
CParticle *CParticle::Create(int number, D3DXVECTOR3 pos)
{
	// �ϐ�������
	CParticle *pParticle = NULL;

	// �p�[�e�B�N���̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < number; nCnt++)
	{
		// �������𓮓I�Ɋm��
		pParticle = new CParticle(CScene::PRIORITY_EFFECT);

		// �O�Օϐ��̏�������
		pParticle->Init();

		// �ʒu�ݒ�
		pParticle->SetPos(pos);

		// �z��ɕۑ�
		m_pParticle[nCnt] = pParticle;
	}

	// �l��Ԃ�
	return pParticle;
}

//==================================================================================================================
// �e�N�X�`����񃍁[�h
//==================================================================================================================
HRESULT CParticle::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X���擾����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
		PARTICLE_TEXTURE,					// �t�@�C���̖��O
		&m_pTexture);						// �ǂݍ��ރ������[

	return S_OK;
}

//==================================================================================================================
// �e�N�X�`�����j��
//==================================================================================================================
void CParticle::Unload(void)
{
	// �e�N�X�`������NULL����Ȃ��Ƃ�
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();					// �e�N�X�`�����J��
		m_pTexture = NULL;						// NULL�ɂ���
	}
}