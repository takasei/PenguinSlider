//==================================================================================================================
//
// �t�F�[�h����[fade.h]
// Author  :Seiya Takahashi
//
//==================================================================================================================
#ifndef _FADE_H
#define _FADE_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "renderer.h"

//==================================================================================================================
//
// �t�F�[�h�N���X�̒�`
//
//==================================================================================================================
class CFade
{
public:
	// ==========================================================
	// �t�F�[�h�̏��
	// ==========================================================
	typedef enum
	{
		FADE_NONE = 0,								// �����Ȃ����
		FADE_IN,									// �t�F�[�h�C������
		FADE_OUT,									// �t�F�[�h�A�E�g����
		FADE_MAX									// �ő吔
	} FADE;

	CFade();										// �R���X�g���N�^
	~CFade();										// �f�X�g���N�^
	void Init(CRenderer::MODE modeNext);			// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static void SetFade(CRenderer::MODE modeNext);	// �t�F�[�h�̐ݒ菈��
	static FADE GetFade(void);						// �t�F�[�h�̎擾����
	static CFade *Create(CRenderer::MODE modeNext);	// ��������
	static HRESULT Load(void);						// �t�F�[�h�̏�񃍁[�h
	static void Unload(void);						// �t�F�[�h�̏��A�����[�h
	static void FadeIN(void);						// �t�F�[�h�C�������鏈��
	static void FadeOUT(void);						// �t�F�[�h�A�E�g�����鏈��

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`�����
	static CRenderer::MODE m_modeNext;				// ���̃��[�h�ϐ�
	static FADE m_fade;								// �t�F�[�h�̏��
	static D3DXCOLOR m_colorFade;					// �t�F�[�h�̐F���
	static float m_nCntFade;								// �t�F�[�h�J�E���g

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuff;			// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;								// �ʒu

	int m_nCntTest;									// �e�X�g�p�J�E���^
	int m_nMode;									// ���[�h�p�J�E���^

	bool m_bTest;									// �e�X�g�����邩�ǂ���
};
#endif
