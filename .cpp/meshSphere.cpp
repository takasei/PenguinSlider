//==================================================================================================================
//
// ���b�V�����`��[meshSphere.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "manager.h"
#include "renderer.h"
#include "meshSphere.h"
#include "debugProc.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define RADIUS 4000.0f;				// ���a
#define WIDTH 30					// ���̃}�X�̐�
#define DEPTH 15					// �c�̃}�X�̐�

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CMeshSphere::m_pTexture = NULL;			// �e�N�X�`���ϐ�
CMeshSphere *CMeshSphere::m_pMeshShere = NULL;				// ���b�V�����̏��

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CMeshSphere::CMeshSphere(PRIORITY type = CScene::PRIORITY_MESH_SPHERE) :CScene(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CMeshSphere::~CMeshSphere()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CMeshSphere::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();		// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾

	// �ʒu�E��]�̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_nNumVertex = 2 * DEPTH * (WIDTH + 1);			// ���ۂ̒��_��
	m_nNumIndex = (WIDTH + 1) * (DEPTH + 1);		// �����ڂ̒��_��
	m_nNumPolygon = m_nNumVertex - 2;				// �O�p�`�̐�
	m_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �x�N�g��
	m_Nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �@��

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �c���J�E���g
	for (int nDepth = 0; nDepth < DEPTH + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWidth = 0; nWidth < WIDTH + 1; nWidth++)
		{
			float theta = D3DX_PI / DEPTH * nDepth;		// ���W�A���l�v�Z
			float phi = 2 * D3DX_PI / WIDTH * nWidth;	// ���W�A���l�v�Z
			float x = sinf(theta) * cosf(phi) * RADIUS;	// X���W�Z�o
			float y = cosf(theta) * RADIUS;				// Y���W�Z�o
			float z = sinf(theta) * sinf(phi) *RADIUS;	// Z���W�Z�o
			float fLength = 0.0f;						// �x�N�g���̑傫��

			// ���_���W�̐ݒ�
			m_pVtx[0].pos = D3DXVECTOR3(x, y, z);

			m_vector = m_pVtx[0].pos - m_pos;			// �~����̍��W - ���S���W
			fLength = sqrtf((m_vector.x * m_vector.x) + // �����Z�o
				(m_vector.y * m_vector.y) + (m_vector.z * m_vector.z));
			m_Nor.x = m_vector.x / fLength;				// ���K��
			m_Nor.y = m_vector.y / fLength;				// ���K��
			m_Nor.z = m_vector.z / fLength;				// ���K��

			m_Nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_���ɖ@���̌v�Z���ʑ��
			m_pVtx[0].nor = m_Nor;

			// �e�N�X�`���`�ʂ̈ʒu
			m_pVtx[0].tex = D3DXVECTOR2(1.0f / WIDTH * nWidth, 1.0f / DEPTH * nDepth);

			// ���_�J���[
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_�ԍ����Z
			m_pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	WORD *pIdx;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	int nNumber = 0;		// �C���f�b�N�X�ԍ�

	// �C���f�b�N�X�o�b�t�@�����b�N���C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �c���J�E���g
	for (int nDepth = 0; nDepth < DEPTH; nDepth++)
	{
		// �����J�E���g
		for (int nWidth = 0; nWidth < WIDTH + 1; nWidth++)
		{
			// ���ɃC���f�b�N�X�i�[
			pIdx[nNumber++] = nDepth * (WIDTH + 1) + nWidth;
			pIdx[nNumber++] = pIdx[nNumber - 1] + WIDTH + 1;

		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CMeshSphere::Uninit(void)
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
void CMeshSphere::Update(void)
{

}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CMeshSphere::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;									// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	// �������͓����|���S���ɕ����e�N�X�`����\��ꍇ�Ɏg�p����
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CMeshSphere::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// ���b�V��������
//==================================================================================================================
CMeshSphere *CMeshSphere::Create(void)
{
	// �������𓮓I�Ɋm��
	m_pMeshShere = new CMeshSphere(CScene::PRIORITY_MESH_SPHERE);

	// ���b�V����������Ƃ�
	if (m_pMeshShere != NULL)
	{
		// ����������
		m_pMeshShere->Init();
	}

	// �l��Ԃ�
	return m_pMeshShere;
}

//==================================================================================================================
// �e�N�X�`����񃍁[�h
//==================================================================================================================
HRESULT CMeshSphere::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X���擾����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		SKY_TEXTUE,								// �t�@�C���̖��O
		&m_pTexture);							// �ǂݍ��ރ������[

	// �l��Ԃ�
	return S_OK;
}

//==================================================================================================================
// �e�N�X�`�����j��
//==================================================================================================================
void CMeshSphere::Unload(void)
{
	// �e�N�X�`����񂪂���Ƃ�
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();			// �e�N�X�`�����̊J��
		m_pTexture = NULL;				// NULL�ɂ���
	}
}
