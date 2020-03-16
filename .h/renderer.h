//==================================================================================================================
//
// �����_���[[renderer.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "manager.h"

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CFade;
class CDebugProc;
class CCamera;
class CLight;
class CGame;
class CTitle;
class CResult;
class CRanking;
class CTutorial;
class CRecord;
class CSound;

//==================================================================================================================
//
// �����_���[�N���X�̒�`
//
//==================================================================================================================
class CRenderer
{
public:
	// ==========================================================
	// ��ʃ��[�h�̎��
	// ==========================================================
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,				// �^�C�g��
		MODE_TUTORIAL,			// �`���[�g���A��
		MODE_GAME,				// �Q�[��
		MODE_RANKING,			// �����L���O
		MODE_MAX				// �ő吔
	} MODE;						// ���[�h

	CRenderer();										// �R���X�g���N�^
	~CRenderer();										// �f�X�g���N�^
	HRESULT Init(HWND hWnd, BOOL bWindow);				// ����������
	void Uninit(void);									// �I������
	void Update(void);									// �X�V����
	void Draw(void);									// �`�揈��

	static void SetMode(MODE mode);						// ���[�h�̐ݒ�
	static MODE GetMode(void);							// ���[�h�̎擾
	static CGame *GetGame(void);						// �Q�[���̎擾
	static CSound *GetSound(void);						// ���̎擾

	LPDIRECT3DDEVICE9 GetDevice(void);					// �f�o�C�X�擾�֐�

protected:

private:
	static CFade *m_pFade;								// �t�F�[�h�̏��|�C���^
	static CDebugProc *m_pDebugProc;					// �f�o�b�O���O�̏��|�C���^
	static CCamera *m_pCamera;							// �J�����̏��|�C���^
	static CLight *m_pLight;							// ���C�g�̏��|�C���^
	static CTitle *m_pTitle;							// �^�C�g�����̃|�C���^
	static CGame *m_pGame;								// �Q�[�����̃|�C���^
	static CResult *m_pResult;							// ���U���g���̃|�C���^
	static CRanking *m_pRanking;						// �����L���O���̃|�C���^
	static CTutorial *m_pTutorial;						// �`���[�g���A�����̃|�C���^
	static MODE m_mode;									// ���[�h���̃|�C���^
	static CSound *m_pSound;							// �����̃|�C���^

	LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;
	LPDIRECT3D9 m_pD3D = NULL;
	LPD3DXFONT	m_pFont = NULL;							// �t�H���g�ւ̃|�C���^
	CRecord *m_pRecord;									// �L�^�̏��|�C���^

	int			m_nCountFPS = 0;						// FPS�J�E���^
};
#endif