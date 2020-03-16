//==================================================================================================================
//
// ���S[logo.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CScene2D;

//==================================================================================================================
//
// ���S�N���X�̒�`
//
//==================================================================================================================
class CLogo : public CScene
{
public:
	//=============================================================================
	// �񋓌^��`
	//=============================================================================
	typedef enum
	{
		LOGOTYPE_TITLE = 0,				// �^�C�g��
		LOGOTYPE_ENTER,					// �G���^�[���S
		LOGOTYPE_TIMEFRAME,				// �^�C�}�[�t���[��
		LOGOTYPE_TUTORIAL0,				// �`���[�g���A�����S
		LOGOTYPE_TUTORIAL1,				// �`���[�g���A�����S
		LOGOTYPE_TUTORIALENTER,			// �`���[�g���A���G���^�[���S
		LOGOTYPE_DE,					// �Ń��S
		LOGOTYPE_SKIP,					// �X�L�b�v���S
		LOGOTYPE_PRESSJUMP,				// �W�����v�{�^����
		LOGOTYPE_PLAYSWIM,				// �����j�����S
		LOGOTYPE_A,						// �L�[�{�[�h��A
		LOGOTYPE_LEFT,					// �����񃍃S
		LOGOTYPE_D,						// �L�[�{�[�h��D
		LOGOTYPE_RIGHT,					// �E����
		LOGOTYPE_S,						// �L�[�{�[�h��S
		LOGOTYPE_REDUCE_SPEED,			// �������S
		LOGOTYPE_SPACE,					// �L�[�{�[�h�̃X�y�[�X
		LOGOTYPE_JUMP,					// �W�����v���S
		LOGOTYPE_NOW_TIME,				// ���݂̃^�C��
		LOGOTYPE_BEST_TIME,				// �ō��̃^�C��
		LOGOTYPE_DOT0,					// �^�C���ƃ^�C���̊Ԃ̓_0
		LOGOTYPE_DOT1,					// �^�C���ƃ^�C���̊Ԃ̓_1
		LOGOTYPE_DOT2,					// �^�C���ƃ^�C���̊Ԃ̓_2
		LOGOTYPE_DOT3,					// �^�C���ƃ^�C���̊Ԃ̓_3
		LOGOTYPE_PAUSE,					// �|�[�Y���S
		LOGOTYPE_GOAL,					// �S�[��
		LOGOTYPE_START,					// �X�^�[�g
		LOGOTYPE_ONE,					// �J�E���g1
		LOGOTYPE_TWO,					// �J�E���g2
		LOGOTYPE_THREE,					// �J�E���g3
		LOGOTYPE_RANK,					// �����N
		LOGOTYPE_RANKING_LOGO,			// �����L���O���S
		LOGOTYPE_DOT4,					// �^�C���ƃ^�C���̊Ԃ̓_4
		LOGOTYPE_DOT5,					// �^�C���ƃ^�C���̊Ԃ̓_5
		LOGOTYPE_DOT6,					// �^�C���ƃ^�C���̊Ԃ̓_6
		LOGOTYPE_DOT7,					// �^�C���ƃ^�C���̊Ԃ̓_7
		LOGOTYPE_DOT8,					// �^�C���ƃ^�C���̊Ԃ̓_8
		LOGOTYPE_DOT9,					// �^�C���ƃ^�C���̊Ԃ̓_9
		LOGOTYPE_MAX					// �ő�
	} LOGOTYPE;

	//=============================================================================
	// �񋓌^��`
	//=============================================================================
	typedef enum
	{
		STARTCOUNT_NONE = 0,			// �����Ȃ�
		STARTCOUNT_ONE,					// �J�E���g1
		STARTCOUNT_TWO,					// �J�E���g2
		STARTCOUNT_THREE,				// �J�E���g3
		STARTCOUNT_MAX					// �ő�
	} STARTCOUNT;

	CLogo(PRIORITY type);																// �R���X�g���N�^
	~CLogo();																			// �f�X�g���N�^
	void Init(void);																	// ����������
	void Uninit(void);																	// �I������
	void Update(void);																	// �X�V����
	void Draw(void);																	// �`�揈��

	static CLogo *Create(void);															// ��������
	static HRESULT Load(void);															// �e�N�X�`����񃍁[�h����
	static void Unload(void);															// �e�N�X�`�����A�����[�h����
	static void SetEnter(bool bEnter);													// �G���^�[�ݒ菈��

	void SetPos(D3DXVECTOR3 pos);														// �ʒu�ݒ菈��
	void SetLogo(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nCnt, D3DXCOLOR col);	// ���S�ݒ菈��

	LOGOTYPE GetType(void);																// ���S�^�C�v�擾����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[LOGOTYPE_MAX];		// �e�N�X�`�����
	static char *m_apFileName[LOGOTYPE_MAX];				// ���S�̃t�@�C����
	static bool m_bEnter;									// �G���^�[�L�[�������ꂽ���ǂ���

	LOGOTYPE m_type;										// ���S�^�C�v�ϐ�
	STARTCOUNT m_StartCount;								// �X�^�[�g���̃J�E���g���
	CScene2D *m_pScene2D[LOGOTYPE_MAX];						// scene2D�̏��

	D3DXVECTOR3 m_pos;										// �ʒu

	int m_nCounterAnim;										// �J�E���^�[
	int m_nPatternAnim;										// �p�^�[��No
	int m_nCountGoal;										// �S�[���������̃J�E���g
	int m_nCountStart;										// �X�^�[�g����Ƃ��̃J�E���g
	int m_nGoalTime;										// �S�[���������̃^�C���J�E���g

	float m_fWidth;											// �c��
	float m_fSize;											// ����
	float m_posX;											// �X�N���[���p�v�Z�ϐ�
	float m_TitlePosX;										// �^�C�g���p�ʒuX�ϐ�
	float m_TitlePosY;										// �^�C�g���p�ʒuY�ϐ�

	bool m_bStartLogo;										// �X�^�[�g���S���\�����ꂽ���ǂ���
};
#endif