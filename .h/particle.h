//==================================================================================================================
//
// �p�[�e�B�N��[particle.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MAX_PARTICLE 400		// �p�[�e�B�N���̍ő吔

//==================================================================================================================
//
// �p�[�e�B�N���N���X�̒�`
//
//==================================================================================================================
class CParticle : public CScene
{
public:

	CParticle(PRIORITY type);				// �R���X�g���N�^
	~CParticle();							// �f�X�g���N�^
	void Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

	static CParticle *Create(int number, D3DXVECTOR3 pos);	// ��������
	static HRESULT Load(void);				// �e�N�X�`����񃍁[�h
	static void Unload(void);				// �e�N�X�`�����A�����[�h

	void SetPos(D3DXVECTOR3 pos);			// �ʒu�ݒ菈��
	void SetSize(D3DXVECTOR3 size);			// �傫���ݒ菈��
	void SetMove(D3DXVECTOR3 move);			// �ړ��ʐݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu�擾����
	D3DXVECTOR3 GetSize(void) { return m_size; }	// �傫���擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ��ʎ擾����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���ւ̃|�C���^
	static CParticle *m_pParticle[MAX_PARTICLE];// �p�[�e�B�N�����̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// �o�b�t�@
	VERTEX_3D *m_pVtx;						// ���_�i�[
	D3DXMATRIX m_mtxWorld;					// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_rot;						// ��]
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_size;						// �傫��

	int m_nLife;							// ���C�t
};
#endif