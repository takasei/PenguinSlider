//==================================================================================================================
//
// �C���^�[�o���t�F�[�h����[intervalFade.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _INTERVALFADE_H
#define _INTERVALFADE_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene2D.h"

//==================================================================================================================
//
// �C���^�[�o���t�F�[�h�N���X�̒�`
//
//==================================================================================================================
class CIntervalFade : public CScene2D
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
	} INTERVAL_FADE;

	CIntervalFade(PRIORITY type);				// �R���X�g���N�^
	~CIntervalFade();							// �f�X�g���N�^
	void Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static INTERVAL_FADE GetIntervalFade(void);	// �t�F�[�h�̎擾����
	static CIntervalFade *Create(void);			// ��������
	static HRESULT Load(void);					// �t�F�[�h�̏�񃍁[�h
	static void Unload(void);					// �t�F�[�h�̏��A�����[�h
	static void FadeIN(void);					// �t�F�[�h�C�������鏈��
	static void FadeOUT(void);					// �t�F�[�h�A�E�g�����鏈��

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`�����
	static INTERVAL_FADE m_fade;				// �t�F�[�h�̏��
	static D3DXCOLOR m_colorFade;				// �t�F�[�h�̐F���

	D3DXVECTOR3 m_pos;							// �ʒu
};
#endif
