//==================================================================================================================
//
// �L�[�{�[�h[inputKeyboard.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "input.h"

//==================================================================================================================
//
// �L�[�{�[�h�N���X�̒�`
//
//==================================================================================================================
class CInputKeyboard : public CInput
{
public:

	CInputKeyboard();								// �R���X�g���N�^
	~CInputKeyboard();								// �f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����

	static bool GetKeyboardPress(int nKey);			// �v���X��Ԏ擾�֐�
	static bool GetKeyboardTrigger(int nKey);		// �g���K�[��Ԏ擾�֐�

protected:

private:
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;			// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
	static BYTE m_aKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏�񃏁[�N
	static BYTE m_aKeyStateTngger[NUM_KEY_MAX];		// �L�[�{�[�h�g���K�[�̓��͏�񃏁[�N
};
#endif