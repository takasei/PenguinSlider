//==================================================================================================================
//
// �Q�[���p�b�h���� [inputGamepad.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "input.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define NUM_JOYPAD_MAX 1			// �p�b�h�ő吔
#define JOY_MAX_RANGE 32768.0f		// �p�b�h�L���͈�

//==================================================================================================================
// �Q�[���p�b�h�N���X��`
//==================================================================================================================
class CInputGamepad : public CInput
{
public:
	//=============================================================================
	// �񋓌^��`
	//=============================================================================
	// �L�[�̎��
	typedef enum
	{
		JOYPADKEY_X = 0,			// [0] X�{�^��
		JOYPADKEY_Y,				// [1] Y�{�^��
		JOYPADKEY_A,				// [2] A�{�^��
		JOYPADKEY_B,				// [3] B�{�^��
		JOYPADKEY_L1,				// [4] ����O�{�^��
		JOYPADKEY_R1,				// [5] �E��O�{�^��
		JOYPADKEY_L2,				// [6] ���g���K�[
		JOYPADKEY_R2,				// [7] �E�g���K�[
		JOYPADKEY_LEFT_THUMB,		// [8] ���X�e�B�b�N�{�^��
		JOYPADKEY_RIGHT_THUMB,		// [9] �E�X�e�B�b�N�{�^��
		JOYPADKEY_BACK,				// [10] �o�b�N�{�^��
		JOYPADKEY_START,			// [11] �X�^�[�g�{�^��
		JOYPADKEY_LEFT,				// [12] �����L�[[��]
		JOYPADKEY_RIGHT,			// [13] �����L�[[�E]
		JOYPADKEY_UP,				// [14] �����L�[[��]
		JOYPADKEY_DOWN,				// [15] �����L�[[��]
		JOYPADKEY_MAX				// �ő吔
	} JOYPADKEY;

	CInputGamepad();
	~CInputGamepad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit(void);								//�I��
	void Update(void);								//�X�V

	bool GetPress(int nIDPad, JOYPADKEY key);							//�v���X����
	bool GetTrigger(int nIDPad, JOYPADKEY key);							//�g���K�[����
	bool GetRelease(int nIDPad, JOYPADKEY key);							//�����[�X����
	void GetStickLeft(int nIDPad, float *pValueH, float *pValueV);		//���X�e�B�b�N�l�擾
	void GetStickRight(int nIDPad, float *pValueH, float *pValueV);		//�E�X�e�B�b�N�l�擾
	void StartForeFeedback();											//�U���J�n
	void StopForeFeedback();											//�U����~

private:
	static LPDIRECTINPUTDEVICE8	m_apDIDevGamepad[NUM_JOYPAD_MAX];						// IDirectInputDevice8�ւ̃|�C���^(�W���C�p�b�h)
	LPDIRECTINPUTEFFECT		m_pDIEffect = NULL;											// �U���p
	DIJOYSTATE				m_aGamepadState[NUM_JOYPAD_MAX];							// �W���C�p�b�h��Ԃ��󂯎�郏�[�N
	bool					m_aKeyStateGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];			// �W���C�p�b�h�̉�����Ԃ�ێ����郏�[�N
	bool					m_aKeyStateTriggerGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// �W���C�p�b�h�̃g���K�[��Ԃ�ێ����郏�[�N
	bool					m_aKeyStateReleaseGamepad[NUM_JOYPAD_MAX][NUM_KEY_MAX];		// �W���C�p�b�h�̃����[�X��Ԃ�ێ����郏�[�N
	D3DXVECTOR3             m_aKeyStateAxis[NUM_JOYPAD_MAX];
	DWORD					m_dwNumForceFeedbackAxis;									//�t�H�[�X�t�B�[�h�o�b�N�i�U���j

	static int				m_nCntPad;

	void SetKeyStateGamepad(int nIDPad);		
	int GetTriggerLeft(int nIDPad);				
	int GetTriggerRight(int nIDPad);			
	static BOOL CALLBACK EnumJoyCallbackGamepad(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);
	static BOOL CALLBACK EnumAxesCallbackGamepad(const DIDEVICEOBJECTINSTANCE  *pdidoi, VOID* pvRef);
	BOOL CreateEffect(HWND hWnd);
};

#endif