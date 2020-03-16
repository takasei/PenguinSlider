//==================================================================================================================
//
// X�t�@�C���̕`��[sceneX.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
//
// �`��X�N���X�̒�`
//
//==================================================================================================================
class CSceneX : public CScene
{
public:
	CSceneX(PRIORITY type);															// �R���X�g���N�^
	~CSceneX();																		// �f�X�g���N�^
	void Init(void);																// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��

	static CSceneX *Create(void);													// ��������

	void BindTex(LPDIRECT3DTEXTURE9 tex);											// �e�N�X�`����������
	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);			// ���f����������
	void SetPos(D3DXVECTOR3 pos);													// �ʒu�ݒ菈��
	void SetSize(D3DXVECTOR3 size);													// �傫���ݒ菈��
	void SetMove(D3DXVECTOR3 move);													// �ړ��ʐݒ菈��
	void SetRot(D3DXVECTOR3 rot);													// ��]�ݒ菈��
	void SetVecAxis(D3DXVECTOR3 vecAxis);											// ��]���ݒ菈��
	void SetValueRot(float ValueRot);												// ��]�p�ݒ菈��

	bool SetCollisionBox(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld);	// ��`�̓����蔻�菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }										// �ʒu�擾����
	D3DXVECTOR3 GetSize(void) { return m_size; }									// �傫���擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }									// �ړ��ʎ擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }										// ��]�擾����
	D3DXVECTOR3 GetVecAxis(void) { return m_vecAxis; }								// ��]���擾����

	float GetValueRot(void) { return m_fValueRot; }									// ��]�p�擾����

protected:

private:
	static CSceneX *m_pSceneX;					// CSceneX�̏��|�C���^

	LPD3DXMESH m_pMesh;							// ���b�V�����̃|�C���^
	LPD3DXBUFFER m_pBuffMat;					// �}�e���A�����̃|�C���^
	LPD3DXBUFFER m_pBuffShadow;					// �e���̃|�C���^
	DWORD m_nNumMat;							// �}�e���A�����̐�
	LPDIRECT3DTEXTURE9 m_pTexture;				// �e�N�X�`���̃|�C���^
	D3DXMATRIX m_mtxRot;						// ��]�}�g���b�N�X�i�ۑ��p�j
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXQUATERNION m_quat;						// �N�H�[�^�j�I��

	D3DXVECTOR3 m_vecAxis;						// ��]��
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_size;							// �傫��
	D3DXVECTOR3 m_move;							// �ړ���
	D3DXVECTOR3 m_rot;							// ��]

	float m_fValueRot;							// ��]�p�i��]�ʁj
	float m_fAngle;								// �p�x
	float m_fLength;							// ����
};
#endif