//==================================================================================================================
//
// �|�[�Y����[pause.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PAUSE_H
#define _PAUSE_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
//
// �|�[�Y�N���X�̒�`
//
//==================================================================================================================
class CPause
{
public:
	// ==========================================================
	// �\���̒�`
	// ==========================================================
	// �e�N�X�`���̎��
	typedef enum
	{
		PAUSETEXTURE_BG = 0,		// �|�[�Y�w�i
		PAUSETEXTURE_FRAME,			// �|�[�Y�t���[��
		PAUSETEXTURE_SELECT,		// �I��
		PAUSETEXTURE_CONTINUE,		// ������
		PAUSETEXTURE_START,			// �X�^�[�g�����蒼��
		PAUSETEXTURE_TITLE,			// �^�C�g���ɂ���
		PAUSETEXTURE_MAX			// �ő吔
	} PAUSETEXTURE;					// �|�[�Y�e�N�X�`��

	CPause();						// �R���X�g���N�^
	~CPause();						// �f�X�g���N�^
	void Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	static CPause *Create(void);	// ��������
	static HRESULT Load(void);		// �t�F�[�h�̏�񃍁[�h
	static void Unload(void);		// �t�F�[�h�̏��A�����[�h

	void SetPause(bool bPause);		// �|�[�Y��Ԃ̐ݒ菈��

	bool GetPause(void);			// �|�[�Y�̏�Ԏ擾

protected:

private:
	void SetVertexPause(PAUSETEXTURE number, D3DXVECTOR3 pos,
		D3DXCOLOR col, float fWidth, float fHeight);		// �|�[�Y�̃e�N�X�`���ݒ菈��
	static LPDIRECT3DTEXTURE9 m_pTexture[PAUSETEXTURE_MAX];	// �e�N�X�`�����
	static char *m_apFileName[PAUSETEXTURE_MAX];			// �e�N�X�`���̃t�@�C����

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuff;					// ���_�o�b�t�@
	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXCOLOR m_color;										// �F���

	int m_nSelect;											// �I��ԍ�

	bool m_bPause;											// �|�[�Y�����ǂ���
};
#endif
