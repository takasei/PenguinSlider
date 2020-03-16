//==================================================================================================================
//
// �`��3D[scene3D.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define POLGON_X (100)																// �e�N�X�`����X���W
#define POLGON_Y (100)																// �e�N�X�`����Y���W
#define CENTERPOS_NORMAL (2)														

//==================================================================================================================
//
// �`��3D�N���X�̒�`
//
//==================================================================================================================
class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY type);							// �R���X�g���N�^
	~CScene3D();										// �f�X�g���N�^
	void Init(void);									// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static CScene3D *Create(void);						// ��������
	static CScene3D *GetScene3D(void);					// Scene3D���擾����

	void BindTex(LPDIRECT3DTEXTURE9 tex);				// �e�N�X�`����������
	void SetCol(D3DXCOLOR col);							// �F�ݒ菈��
	void SetPos(D3DXVECTOR3 pos);						// �ʒu�ݒ菈��
	void SetSize(D3DXVECTOR3 size);						// �傫���ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }			// �ʒu�擾����
	D3DXVECTOR3 GetSize(void) { return m_size; }		// �傫���擾����

protected:

private:
	static CScene3D *m_pScene3D;

	LPDIRECT3DTEXTURE9 m_pTexturePolygon;				// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// �o�b�t�@
	VERTEX_3D *m_pVtx;									// ���_�i�[
	D3DXMATRIX m_mtxWorld;								// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;									// �ʒu
	D3DXVECTOR3 m_rot;									// ��]
	D3DXVECTOR3 m_size;									// �傫��
	D3DXVECTOR3 m_NorA;									// ��ڂ̎O�p�`�̖@��
	D3DXVECTOR3 m_NorB;									// ��ڂ̎O�p�`�̖@��

	float m_fAngle;										// �p�x
	float m_fLength;									// ����
	float m_Height;										// ����
};
#endif