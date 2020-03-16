//==================================================================================================================
//
// ������ [sound.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
//
// �N���X�̒�`
//
//==================================================================================================================
class CSound
{
public:
	// ==========================================================
	// ���̎��
	// ==========================================================
	typedef enum
	{
		SOUND_LABEL_BGMTITLE = 0,	// �^�C�g��
		SOUND_LABEL_BGMTUTORIAL,	// �`���[�g���A��
		SOUND_LABEL_BGMGAME,		// �Q�[��
		SOUND_LABEL_BGMRESULT,		// ���U���g
		SOUND_LABEL_SE_DECISION,	// ����
		SOUND_LABEL_SE_COUNT,		// �J�E���g�_�E��
		SOUND_LABEL_SE_WATER,		// ��
		SOUND_LABEL_MAX,			// �ő�
	} SOUND_LABEL;					// ���̎��

	CSound();									// �R���X�g���N�^
	~CSound();									// �f�X�g���N�^
	HRESULT Init(HWND nWnd);					// ����������
	void Uninit(void);							// �I������
	void StopSound(SOUND_LABEL label);			// �w�肵�������~�߂鏈��
	void StopSound(void);						// �S�Ẳ����~�߂鏈��

	HRESULT PlaySound(SOUND_LABEL label);															// ����炷����
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);	// �`�����N�`�F�b�N����
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^���[�h����

protected:

private:
	IXAudio2 *m_pXAudio2;											// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;						// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];			// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];							// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];							// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif
