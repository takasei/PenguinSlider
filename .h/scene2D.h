//==================================================================================================================
//
// �`��2D[scene2D.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define POLGON_X (100)																	// �e�N�X�`����X���W
#define POLGON_Y (100)																	// �e�N�X�`����Y���W
#define CENTERPOS_NORMAL (2)															// ���S���߂�

//==================================================================================================================
//
// �`��2D�N���X�̒�`
//
//==================================================================================================================
class CScene2D : public CScene
{
public:
	CScene2D(PRIORITY type);															// �R���X�g���N�^
	~CScene2D();																		// �f�X�g���N�^
	void Init(void);																	// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �X�V����
	void Draw(void);																	// �`�揈��

	static CScene2D *Create(void);														// ��������

	void BindTex(LPDIRECT3DTEXTURE9 tex);												// �e�N�X�`����������
	void SetAnimation(float fTexX, float fTexY,float fTexY2, int nPatternAnim);			// �A�j���[�V�����ݒ菈��
	void SetMove(float fTexX, float fTexY, float fMoveX);								// �w�i�X�N���[���ݒ菈��
	void SetCol(D3DXCOLOR col);															// �F�ݒ菈��
	void SetPos(D3DXVECTOR3 pos);														// �ʒu�ݒ菈��
	void SetSize(D3DXVECTOR3 size);														// �傫���ݒ菈��
	void SetRot(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fAngle, float fLength);			// ��]�ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }											// �ʒu�擾����
	D3DXVECTOR3 GetSize(void) { return m_size; }										// �傫���擾����

	bool SetCollision(D3DXVECTOR3 posDo, int sizeX, int sizeY, D3DXVECTOR3 posDone);	// �����蔻�菈��

protected:

private:
	static CScene2D *m_pScene2D;														// scene2D���

	LPDIRECT3DTEXTURE9 m_pTexturePolygon;												// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;													// �o�b�t�@
	VERTEX_2D *m_pVtx;																	// ���_�i�[

	D3DXVECTOR3 m_pos;																	// �ʒu
	D3DXVECTOR3 m_size;																	// �傫��
	D3DXVECTOR3 m_rot;																	// ��]

	float m_fAngle;																		// �p�x
	float m_fLength;																	// ����
};
#endif