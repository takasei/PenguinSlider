//==================================================================================================================
//
// �Q�[������[game.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _GAME_H
#define _GAME_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define GAME_MAX_MODEL 35		// game.cpp���̃��f���̃p�[�c��

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CPlayer;
class CMeshField;
class CCamera;
class CLight;
class CLogo;
class CModel;
class CPause;
class CIntervalFade;
class CMeshSphere;

//==================================================================================================================
//
// �Q�[���N���X�̒�`
//
//==================================================================================================================
class CGame
{
public:
	// ==========================================================
	// �Q�[���̏��
	// ==========================================================
	typedef enum
	{
		GAMESTATE_NONE = 0,		// �������Ă��Ȃ����
		GAMESTATE_NORMAL,		// �ʏ���
		GAMESTATE_PAUSE,		// �|�[�Y���
		GAMESTATE_START_OVER,	// ���߂����蒼��
		GAMESTATE_BREAK,		// �Q�[�����f
		GAMESTATE_END,			// �Q�[���̏I��
		GAMESTATE_MAX			// �ő�
	} GAMESTATE;				// �Q�[���̏��

	CGame();									// �R���X�g���N�^
	~CGame();									// �f�X�g���N�^
	void Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��
	static CGame *Create(void);					// ��������

	static void SetGameState(GAMESTATE state);	// �Q�[���̏�Ԑݒ�
	static GAMESTATE GetGameState(void);		// �Q�[���̏�Ԏ擾
	static CPlayer *GetPlayer(void);			// �v���C���[�̏��擾����

protected:

private:
	void SetModel(void);						// ���f���̐ݒ�

	static GAMESTATE m_gameState;				// �Q�[�����
	static CPlayer *m_pPlayer;					// �v���C���[�̏��|�C���^
	static CMeshField *m_pMeshField;			// ���b�V���t�B�[���h�̏��|�C���^
	static CCamera *m_pCamera;					// �J�����̏��|�C���^
	static CLight *m_pLight;					// ���C�g�̏��|�C���^
	static CLogo *m_pLogo;						// ���S�̏��|�C���^
	static CPause *m_pPause;					// �|�[�Y�̏��|�C���^
	static CIntervalFade *m_pIntervalFade;		// �C���^�[�o���t�F�[�h���|�C���^
	static CMeshSphere *m_pMeshSphere;			// ���b�V�����̏��|�C���^
	static int m_nCounterGameState;				// �Q�[���̏�ԊǗ��J�E���^�[

	D3DXMATRIX  m_mtxWorld;						// �}�g���b�N�X
	CModel *m_pModel[GAME_MAX_MODEL];			// ���f���̏��
};
#endif
