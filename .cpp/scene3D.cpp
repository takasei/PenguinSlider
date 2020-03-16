//==================================================================================================================
//
// �`��3D[scene3D.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "manager.h"
#include "scene3D.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "debugProc.h"

//==================================================================================================================
// �ÓI�����o�[�ϐ��̏�����
//==================================================================================================================
CScene3D *CScene3D::m_pScene3D = NULL;			// Scene3D�̏��

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define SHADOW_SIZE 20.0f		// �e�̃T�C�Y

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CScene3D::CScene3D(PRIORITY type) : CScene(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CScene3D::~CScene3D()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CScene3D::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X�̎擾

	// ������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// ��]
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);							// �傫��
	m_fAngle = atan2f(POLGON_X, POLGON_Y);							// �p�x
	m_fLength = sqrtf(POLGON_X * POLGON_X + POLGON_Y * POLGON_Y);	// ����
	D3DXVECTOR3 vectorA = D3DXVECTOR3(0, 0, 0);						// A�x�N�g��
	D3DXVECTOR3 vectorB = D3DXVECTOR3(0, 0, 0);						// B�x�N�g��
	D3DXVECTOR3 vectorC = D3DXVECTOR3(0, 0, 0);						// C�x�N�g��
	D3DXVECTOR3 vectorD = D3DXVECTOR3(0, 0, 0);						// D�x�N�g��
	m_NorA = D3DXVECTOR3(0, 0, 0);									// A�@��
	m_NorB = D3DXVECTOR3(0, 0, 0);									// B�@��
	m_Height = 0.0f;												// �ڒn�ʂ̍���

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// ���W�̐ݒ�
	// [0]���_
	m_pVtx[0].pos.x = m_pos.x + (-SHADOW_SIZE / 2);
	m_pVtx[0].pos.y = 0;
	m_pVtx[0].pos.z = m_pos.z + (SHADOW_SIZE / 2);

	// [1]���_
	m_pVtx[1].pos.x = m_pos.x + (SHADOW_SIZE / 2);
	m_pVtx[1].pos.y = 0;
	m_pVtx[1].pos.z = m_pos.z + (SHADOW_SIZE / 2);

	// [2]���_
	m_pVtx[2].pos.x = m_pos.x + (-SHADOW_SIZE / 2);
	m_pVtx[2].pos.y = 0;
	m_pVtx[2].pos.z = m_pos.z + (-SHADOW_SIZE / 2);

	// [3]���_
	m_pVtx[3].pos.x = m_pos.x + (SHADOW_SIZE / 2);
	m_pVtx[3].pos.y = 0;
	m_pVtx[3].pos.z = m_pos.z + (-SHADOW_SIZE / 2);

	vectorA = m_pVtx[1].pos - m_pVtx[2].pos;		// A�x�N�g���Z�o
	vectorB = m_pVtx[0].pos - m_pVtx[1].pos;		// B�x�N�g���Z�o
	D3DXVec3Cross(&m_NorA, &vectorA, &vectorB);		// �����x�N�g���Z�o
	D3DXVec3Normalize(&m_NorA, &m_NorA);			// ���K������

	vectorC = m_pVtx[2].pos - m_pVtx[1].pos;		// C�x�N�g���Z�o
	vectorD = m_pVtx[3].pos - m_pVtx[2].pos;		// D�x�N�g���Z�o
	D3DXVec3Cross(&m_NorB, &vectorC, &vectorD);		// �����x�N�g���Z�o
	D3DXVec3Normalize(&m_NorB, &m_NorB);			// ���K������

	// �@���x�N�g���̐ݒ�
	m_pVtx[0].nor = m_NorA;							// ���̂܂ܑ��
	m_pVtx[1].nor = (m_NorA + m_NorB) / 2;			// �O�p�`���d�Ȃ��Ă���Ƃ���͊���2
	m_pVtx[2].nor = (m_NorA + m_NorB) / 2;			// �O�p�`���d�Ȃ��Ă���Ƃ���͊���2
	m_pVtx[3].nor = m_NorB;							// ���̂܂ܑ��

	// ���_�J���[
	m_pVtx[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);
	m_pVtx[1].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);
	m_pVtx[2].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);
	m_pVtx[3].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);

	// �e�N�X�`�����W�̐ݒ�
	m_pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@������Ƃ�
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();		// �J��
		m_pVtxBuff = NULL;			// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CScene3D::Update(void)
{
	// �ʒu�擾
	m_pos = GetPos();

	// �傫���擾
	m_size = GetSize();

	// �ʒu�ݒ�
	SetPos(m_pos);
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CScene3D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;					// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

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
	pDevice->SetTexture(0, m_pTexturePolygon);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// �e�N�X�`������
//==================================================================================================================
void CScene3D::BindTex(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexturePolygon = tex;
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CScene3D::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// �傫���ݒ�
//==================================================================================================================
void CScene3D::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//==================================================================================================================
// �F�ݒ�
//==================================================================================================================
void CScene3D::SetCol(D3DXCOLOR col)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// ���_�J���[
	m_pVtx[0].col = col;
	m_pVtx[1].col = col;
	m_pVtx[2].col = col;
	m_pVtx[3].col = col;

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// ��������
//==================================================================================================================
CScene3D *CScene3D::Create(void)
{
	// �V�[�����I�Ɋm��
	m_pScene3D = new CScene3D(CScene::PRIORITY_FIELD);

	// �V�[��������
	m_pScene3D->Init();

	// �l��Ԃ�
	return m_pScene3D;
}

//==================================================================================================================
// CScene3D�̎擾
//==================================================================================================================
CScene3D *CScene3D::GetScene3D(void)
{
	return m_pScene3D;
}