//==================================================================================================================
//
// �Q�[���p�b�h���� [inputGamepad.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================

//==================================================================================================================
//�C���N���[�h
//==================================================================================================================
#include "inputGamepad.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
int CInputGamepad::m_nCntPad = 0;
LPDIRECTINPUTDEVICE8 CInputGamepad::m_apDIDevGamepad[NUM_JOYPAD_MAX] = {};

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CInputGamepad::CInputGamepad()
{
	m_nCntPad = 0;

	//DEffect�̊J��
	m_pDIEffect = NULL;

	// �W���C�p�b�h�̏I������
	for (int nCntPad = 0; nCntPad < NUM_JOYPAD_MAX; nCntPad++)
	{
		m_apDIDevGamepad[nCntPad] = NULL;
	}
}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CInputGamepad::~CInputGamepad()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
HRESULT CInputGamepad::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		MessageBox(hWnd, "InputInit���s", "�x��", MB_ICONWARNING);
		return E_FAIL;
	}


	for (m_nCntPad = 0; m_nCntPad < NUM_JOYPAD_MAX; m_nCntPad++)
	{
		//�W���C�p�b�h��T��
		hr = m_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallbackGamepad, NULL, DIEDFL_FORCEFEEDBACK | DIEDFL_ATTACHEDONLY);
		if (FAILED(hr) || m_apDIDevGamepad[m_nCntPad] == NULL)
		{
			//MessageBox(hWnd, "�W���C�p�b�h������܂���", "�x��", MB_ICONWARNING);
			return hr;
		}

		// �f�[�^�t�H�[�}�b�g��ݒ�
		hr = m_apDIDevGamepad[m_nCntPad]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr))
		{

			MessageBox(hWnd, "�W���C�p�b�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
			return hr;
		}

		// �������[�h��ݒ�i�t�H�A�O���E���h���r�����[�h�j
		hr = m_apDIDevGamepad[m_nCntPad]->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�W���C�p�b�h�̋������[�h��ݒ�ł��܂���ł����B", "�x��", MB_ICONWARNING);
			return hr;
		}

		hr = m_apDIDevGamepad[m_nCntPad]->EnumObjects(EnumAxesCallbackGamepad, (VOID*)&m_dwNumForceFeedbackAxis, DIDFT_AXIS);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�W���C�p�b�h��������܂���ł���", "�x��", MB_ICONWARNING);
			return hr;
		}

		if (m_dwNumForceFeedbackAxis > 2)
		{
			m_dwNumForceFeedbackAxis = 2;
		}

		//�G�t�F�N�g�̐���
		hr = CreateEffect(hWnd);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�G�t�F�N�g�������ł��܂���ł���", "�x��", MB_ICONWARNING);
			return hr;
		}
	}
	return TRUE;
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CInputGamepad::Uninit(void)
{
	//DEffect�̊J��
	if (m_pDIEffect != NULL)
	{
		m_pDIEffect->Release();
		m_pDIEffect = NULL;
	}

	// �W���C�p�b�h�̏I������
	for (int nCntPad = 0; nCntPad < NUM_JOYPAD_MAX; nCntPad++)
	{
		if (m_apDIDevGamepad[nCntPad] != NULL)
		{// �f�o�C�X�I�u�W�F�N�g�̊J��
			m_apDIDevGamepad[nCntPad]->Release();
			m_apDIDevGamepad[nCntPad] = NULL;
		}
	}
	CInput::Uninit();
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CInputGamepad::Update(void)
{
	HRESULT hr;
	bool aKeyStateOld[JOYPADKEY_MAX];

	// �p�b�h�̍ő吔�܂ŃJ�E���g
	for (int nCntPad = 0; nCntPad < NUM_JOYPAD_MAX; nCntPad++)
	{
		if (m_apDIDevGamepad[nCntPad] == NULL)
		{
			return;
		}
		// �O��̃f�[�^��ۑ�
		for (int nCntKey = 0; nCntKey < JOYPADKEY_MAX; nCntKey++)
		{
			aKeyStateOld[nCntKey] = m_aKeyStateGamepad[nCntPad][nCntKey];
		}

		// �f�o�C�X����f�[�^���擾
		hr = m_apDIDevGamepad[nCntPad]->GetDeviceState(sizeof(m_aGamepadState[nCntPad]), &m_aGamepadState[nCntPad]);
		if (SUCCEEDED(hr))
		{
			// �L�[���ݒ�
			SetKeyStateGamepad(nCntPad);

			// �L�[�̍ő吔�܂ŃJ�E���g
			for (int nCntKey = 0; nCntKey < JOYPADKEY_MAX; nCntKey++)
			{
				// �g���K�[�E�����[�X���̍쐬
				m_aKeyStateTriggerGamepad[nCntPad][nCntKey] = (aKeyStateOld[nCntKey] ^ m_aKeyStateGamepad[nCntPad][nCntKey]) & m_aKeyStateGamepad[nCntPad][nCntKey];
				m_aKeyStateReleaseGamepad[nCntPad][nCntKey] = (aKeyStateOld[nCntKey] ^ m_aKeyStateGamepad[nCntPad][nCntKey]) & !m_aKeyStateGamepad[nCntPad][nCntKey];
			}
		}
		else
		{
			m_apDIDevGamepad[nCntPad]->Acquire();
		}
	}
}

//==================================================================================================================
// �W���C�X�e�B�b�N�₢���킹�p�R�[���o�b�N�֐�
//==================================================================================================================
BOOL CInputGamepad::EnumJoyCallbackGamepad(const DIDEVICEINSTANCE * lpddi, VOID * pvRef)
{
	static GUID pad_discrimination[NUM_JOYPAD_MAX];	// �e�f�o�C�X�̎��ʎq���i�[
	DIDEVCAPS	diDevCaps;				// �f�o�C�X���
	HRESULT		hRes;


	// �W���C�X�e�B�b�N�p�f�o�C�X�I�u�W�F�N�g���쐬
	hRes = m_pInput->CreateDevice(lpddi->guidInstance, &m_apDIDevGamepad[m_nCntPad], NULL);
	if (FAILED(hRes))
	{
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}

	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hRes = m_apDIDevGamepad[m_nCntPad]->GetCapabilities(&diDevCaps);
	if (FAILED(hRes))
	{
		m_apDIDevGamepad[m_nCntPad]->Release();
		m_apDIDevGamepad[m_nCntPad] = NULL;
		// �񋓂𑱂���
		return DIENUM_CONTINUE;
	}

	// �f�o�C�X�̎��ʎq��ۑ�
	pad_discrimination[0] = lpddi->guidInstance;

	// ���̃f�o�C�X���g���̂ŗ񋓂��I������
	return DIENUM_STOP;
}

//==================================================================================================================
// �W���C�X�e�B�b�N�₢���킹�p�R�[���o�b�N�֐�
//==================================================================================================================
BOOL CInputGamepad::EnumAxesCallbackGamepad(const DIDEVICEOBJECTINSTANCE  *pdidoi, VOID * pvRef)
{
	HRESULT hr;

	for (int nCntPad = 0; nCntPad < NUM_JOYPAD_MAX; nCntPad++)
	{
		DIPROPRANGE diprg;

		// �X�e�B�b�N���̒l�͈̔͂�ݒ�i-32768�`32767�j
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = pdidoi->dwType;
		diprg.diph.dwHow = DIPH_BYID;
		diprg.lMin = -32768;
		diprg.lMax = 32767;

		hr = m_apDIDevGamepad[nCntPad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		if (FAILED(hr))
		{
			return DIENUM_STOP;
		}

		//�t�H�[�X�t�B�[�h�o�b�N
		DWORD *pdwNumForceFeedbackAxis = (DWORD*)pvRef;
		if ((pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0)
		{
			(*pdwNumForceFeedbackAxis)++;
		}
	}

	return DIENUM_CONTINUE;
}

//==================================================================================================================
// �G�t�F�N�g����
//==================================================================================================================
BOOL CInputGamepad::CreateEffect(HWND hWnd)
{
	DWORD           rgdwAxes[2] = { DIJOFS_X , DIJOFS_Y };
	LONG            rglDirection[2] = { 1 , 1 };
	DICONSTANTFORCE cf;
	DIEFFECT        eff;
	HRESULT         hr;

	//�G�t�F�N�g�ݒ�
	ZeroMemory(&eff, sizeof(eff));
	eff.dwSize = sizeof(DIEFFECT);
	eff.dwFlags = DIEFF_CARTESIAN | DIEFF_OBJECTOFFSETS;
	eff.dwDuration = INFINITE;
	eff.dwSamplePeriod = 0;
	eff.dwGain = DI_FFNOMINALMAX;
	eff.dwTriggerButton = DIEB_NOTRIGGER;
	eff.dwTriggerRepeatInterval = 0;
	eff.cAxes = m_dwNumForceFeedbackAxis;
	eff.rgdwAxes = rgdwAxes;
	eff.rglDirection = rglDirection;
	eff.lpEnvelope = 0;
	eff.cbTypeSpecificParams = sizeof(DICONSTANTFORCE);
	eff.lpvTypeSpecificParams = &cf;
	eff.dwStartDelay = 0;

	//�G�t�F�N�g�̃N���G�C�g
	hr = m_apDIDevGamepad[m_nCntPad]->CreateEffect(GUID_ConstantForce, &eff, &m_pDIEffect, NULL);
	if (FAILED(hr)) {
		MessageBox(hWnd, "�G�t�F�N�g�̃N���G�C�g�Ɏ��s", "Error", MB_OK);
		return FALSE;
	}

	return TRUE;
}

//==================================================================================================================
// �W���C�p�b�h�̃L�[���ݒ�
//==================================================================================================================
void CInputGamepad::SetKeyStateGamepad(int nIDPad)
{
	if (m_aGamepadState[nIDPad].rgdwPOV[0] >= 225 * 100 && m_aGamepadState[nIDPad].rgdwPOV[0] <= 315 * 100)
	{// �\���L�[[��]��������Ă���
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_LEFT] = true;
	}
	else
	{
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_LEFT] = false;
	}

	if (m_aGamepadState[nIDPad].rgdwPOV[0] >= 45 * 100 && m_aGamepadState[nIDPad].rgdwPOV[0] <= 135 * 100)
	{// �\���L�[[�E]��������Ă���
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_RIGHT] = true;
	}
	else
	{
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_RIGHT] = false;
	}

	if ((m_aGamepadState[nIDPad].rgdwPOV[0] >= 315 * 100 && m_aGamepadState[nIDPad].rgdwPOV[0] <= 360 * 100)
		|| (m_aGamepadState[nIDPad].rgdwPOV[0] >= 0 * 100 && m_aGamepadState[nIDPad].rgdwPOV[0] <= 45 * 100))
	{// �\���L�[[��]��������Ă���
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_UP] = true;
	}
	else
	{
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_UP] = false;
	}

	if (m_aGamepadState[nIDPad].rgdwPOV[0] >= 135 * 100 && m_aGamepadState[nIDPad].rgdwPOV[0] <= 225 * 100)
	{// �\���L�[[��]��������Ă���
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_DOWN] = true;
	}
	else
	{
		m_aKeyStateGamepad[nIDPad][JOYPADKEY_DOWN] = false;
	}

	for (int nKey = JOYPADKEY_X; nKey <= JOYPADKEY_START; nKey++)
	{
		if (m_aGamepadState[nIDPad].rgbButtons[nKey])
		{// �{�^����������Ă���
			m_aKeyStateGamepad[nIDPad][nKey] = true;
		}
		else
		{
			m_aKeyStateGamepad[nIDPad][nKey] = false;
		}
	}
}

//==================================================================================================================
// �L�[���擾�i�v���X�j
//==================================================================================================================
bool CInputGamepad::GetPress(int nIDPad, JOYPADKEY key)
{
	return m_aKeyStateGamepad[nIDPad][key];
}

//==================================================================================================================
// �L�[���擾�i�g���K�[�j
//==================================================================================================================
bool CInputGamepad::GetTrigger(int nIDPad, JOYPADKEY key)
{
	return m_aKeyStateTriggerGamepad[nIDPad][key];
}

//==================================================================================================================
// �L�[���擾�i�����[�X�j
//==================================================================================================================
bool CInputGamepad::GetRelease(int nIDPad, JOYPADKEY key)
{
	return m_aKeyStateReleaseGamepad[nIDPad][key];
}

//==================================================================================================================
// �L�[�擾�����i���g���K�[�j
//==================================================================================================================
int CInputGamepad::GetTriggerLeft(int nIDPad)
{
	return m_aGamepadState[nIDPad].rgbButtons[JOYPADKEY_L2];
}

//==================================================================================================================
// �L�[���擾�i�E�g���K�[�j
//==================================================================================================================
int CInputGamepad::GetTriggerRight(int nIDPad)
{
	return m_aGamepadState[nIDPad].rgbButtons[JOYPADKEY_R2];
}
//==================================================================================================================
// �L�[���擾�i���X�e�B�b�N�j
//==================================================================================================================
void CInputGamepad::GetStickLeft(int nIDPad, float * pValueH, float * pValueV)
{
	*pValueH = (float)m_aGamepadState[nIDPad].lX;
	*pValueV = (float)-m_aGamepadState[nIDPad].lY;
}

//==================================================================================================================
// �L�[���擾�i�E�X�e�B�b�N�j
//==================================================================================================================
void CInputGamepad::GetStickRight(int nIDPad, float * pValueH, float * pValueV)
{
	*pValueH = (float)m_aGamepadState[nIDPad].lZ;
	*pValueV = (float)-m_aGamepadState[nIDPad].lRz;
}

//==================================================================================================================
// �t�H�[�X�t�B�[�h�o�b�N�X�^�[�g
//==================================================================================================================
void CInputGamepad::StartForeFeedback()
{
	//
	cout << "GPAD�U���֐��ɓ�����\n";

	if (m_pDIEffect != NULL)
	{
		//
		cout << "GPAD�U���Ăяo���ɓ�����\n";

		HRESULT hr = m_pDIEffect->Start(1, DIES_SOLO);

		if (FAILED(hr))
		{
			cout << "�U�����s\n";
		}
		else
		{
			cout << "�U������\n";
			cout << hr;
		}
	}
}

//==================================================================================================================
// �t�H�[�X�t�B�[�h�o�b�N�X�g�b�v
//==================================================================================================================
void CInputGamepad::StopForeFeedback()
{
	if (m_pDIEffect != NULL)
	{
		m_pDIEffect->Stop();
	}
}
