//==================================================================================================================
//
// �^�C�g���t�F�[�h����[titleFade.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _TITLEFADE_H
#define _TITLEFADE_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene2D.h"

//==================================================================================================================
//
// �^�C�g���t�F�[�h�N���X�̒�`
//
//==================================================================================================================
class CTitleFade : public CScene2D
{
public:
	// ==========================================================
	// �t�F�[�h�̏��
	// ==========================================================
	typedef enum
	{
		FADE_NONE = 0,							// �����Ȃ����
		FADE_IN,								// �t�F�[�h�C������
		FADE_OUT,								// �t�F�[�h�A�E�g����
		FADE_MAX								// �ő吔
	} TITLE_FADE;

	CTitleFade(PRIORITY type);					// �R���X�g���N�^
	~CTitleFade();								// �f�X�g���N�^
	void Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static TITLE_FADE GetTitleFade(void);	// �t�F�[�h�̎擾����
	static CTitleFade *Create(void);			// ��������
	static HRESULT Load(void);					// �t�F�[�h�̏�񃍁[�h
	static void Unload(void);					// �t�F�[�h�̏��A�����[�h
	static void FadeIN(void);					// �t�F�[�h�C�������鏈��
	static void FadeOUT(void);					// �t�F�[�h�A�E�g�����鏈��

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`�����
	static TITLE_FADE m_fade;					// �t�F�[�h�̏��
	static D3DXCOLOR m_colorFade;				// �t�F�[�h�̐F���

	D3DXVECTOR3 m_pos;							// �ʒu
};
#endif
