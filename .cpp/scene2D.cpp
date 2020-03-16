//==================================================================================================================
//
// �`��2D[scene2D.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "manager.h"
#include "scene2D.h"
#include "renderer.h"
#include "inputKeyboard.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CScene2D *CScene2D::m_pScene2D;				// pScene2D�̏��

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CScene2D::CScene2D(PRIORITY type = CScene::PRIORITY_UI) : CScene(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CScene2D::~CScene2D()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CScene2D::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X�̎擾

	// ������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);							// �ʒu
	m_size = GetSize();												// �傫���擾
	m_fAngle = atan2f(POLGON_X, POLGON_Y);							// �p�x
	m_fLength = sqrtf(POLGON_X * POLGON_X + POLGON_Y * POLGON_Y);	// ����

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);
	
	// ���W�̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0);
	m_pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0);
	m_pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0);
	m_pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0);

	// 1.0�ŌŒ�A�������W
	m_pVtx[0].rhw = 1.0f;
	m_pVtx[1].rhw = 1.0f;
	m_pVtx[2].rhw = 1.0f;
	m_pVtx[3].rhw = 1.0f;

	// ���_�J���[
	m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
void CScene2D::Uninit(void)
{
	// ���_�o�b�t�@������Ƃ�
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();				// �J��
		m_pVtxBuff = NULL;					// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CScene2D::Update(void)
{

}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexturePolygon);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// �e�N�X�`����\��
//==================================================================================================================
void CScene2D::BindTex(LPDIRECT3DTEXTURE9 tex)
{
	m_pTexturePolygon = tex;
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �ʒu�擾
	m_pos = pos;

	// �ړ����W�̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0);
	m_pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0);
	m_pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0);
	m_pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0);

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �傫���ݒ�
//==================================================================================================================
void CScene2D::SetSize(D3DXVECTOR3 size)
{
	// �傫���擾
	m_size = size;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �ړ����W�̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), 0);
	m_pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y - (m_size.y / 2), 0);
	m_pVtx[2].pos = D3DXVECTOR3(m_pos.x - (m_size.x / 2), m_pos.y + (m_size.y / 2), 0);
	m_pVtx[3].pos = D3DXVECTOR3(m_pos.x + (m_size.x / 2), m_pos.y + (m_size.y / 2), 0);

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �A�j���[�V�����ݒ�
//==================================================================================================================
void CScene2D::SetAnimation(float fTexX, float fTexY, float fTexY2, int nPatternAnim)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	m_pVtx[0].tex = D3DXVECTOR2(0.0f + nPatternAnim * fTexX, fTexY2);
	m_pVtx[1].tex = D3DXVECTOR2(fTexX + nPatternAnim * fTexX, fTexY2);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f + nPatternAnim * fTexX, fTexY);
	m_pVtx[3].tex = D3DXVECTOR2(fTexX + nPatternAnim * fTexX, fTexY);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �X�N���[���ݒ�
//==================================================================================================================
void CScene2D::SetMove(float fTexX, float fTexY, float fMoveX)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);
	
	// �e�N�X�`�����W�̐ݒ�
	m_pVtx[0].tex = D3DXVECTOR2(0.0f + fMoveX, 0.0f);
	m_pVtx[1].tex = D3DXVECTOR2(fTexX + fMoveX, 0.0f);
	m_pVtx[2].tex = D3DXVECTOR2(0.0f + fMoveX, fTexY);
	m_pVtx[3].tex = D3DXVECTOR2(fTexX + fMoveX, fTexY);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �F�ݒ�
//==================================================================================================================
void CScene2D::SetCol(D3DXCOLOR col)
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
// 2D����
//==================================================================================================================
CScene2D *CScene2D::Create(void)
{
	// �V�[�����I�Ɋm��
	m_pScene2D = new CScene2D(CScene::PRIORITY_UI);

	// �V�[��������
	m_pScene2D->Init();

	// �l��Ԃ�
	return m_pScene2D;
}

//==================================================================================================================
// �����蔻��ݒ�
//==================================================================================================================
bool CScene2D::SetCollision(D3DXVECTOR3 posDo, int sizeX, int sizeY, D3DXVECTOR3 posDone)
{
	bool bCollide = false;			// �����蔻��p�ϐ�

	//�e�N�X�`�����ɓ�������
	if ((posDone.x - sizeX / 2 <= posDo.x) &&
		(posDone.x + sizeX / 2 >= posDo.x) &&
		(posDone.y - sizeY / 2 <= posDo.y) &&
		(posDone.y + sizeY / 2 >= posDo.y))
	{
		bCollide = true;			// �������Ă���
	}

	// �l��Ԃ�
	return bCollide;
}

//==================================================================================================================
// ��]�ݒ�
//==================================================================================================================
void CScene2D::SetRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngle, float fLength)
{
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �ʒu����
	m_pos = pos;

	// �ړ����W�̐ݒ�
	m_pVtx[0].pos = D3DXVECTOR3(pos.x - sinf(fAngle + rot.x) * fLength, pos.y - cosf(fAngle) * fLength, 0.0f);
	m_pVtx[1].pos = D3DXVECTOR3(pos.x + sinf(fAngle + rot.x) * fLength, pos.y - cosf(fAngle) * fLength, 0.0f);
	m_pVtx[2].pos = D3DXVECTOR3(pos.x - sinf(fAngle + rot.x) * fLength, pos.y + cosf(fAngle) * fLength, 0.0f);
	m_pVtx[3].pos = D3DXVECTOR3(pos.x + sinf(fAngle + rot.x) * fLength, pos.y + cosf(fAngle) * fLength, 0.0f);

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}