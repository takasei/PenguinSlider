//==================================================================================================================
//
// �v���C���[[player.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "sceneX.h"
#include "intervalFade.h"
#include "fade.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define TEXTURE_PLAYER "data/TEXTURE/field000.jpg"		// �ǂݍ��ރe�N�X�`���̃\�[�X��
#define PLAYER_MODEL "data/MODEL/testmodel.x"			// �ǂݍ��ރ��f���̃\�[�X��
#define PLAYERSIZE_X	(100)							// �v���C���[��X�T�C�Y
#define PLAYERSIZE_Y	(100)							// �v���C���[��Y�T�C�Y
#define PLAYER_MAX_MODEL (6)							// player.cpp���̃��f���̃p�[�c��
#define CALCULATION_POS_Y 120							// �v�Z����ʒuY

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CMeshOrbit;
class CMotionModel;
class CRecord;
class CModel;
class CMeshField;
class CInputKeyboard;
class CInputGamepad;
class CFade;
class CParticle;
class CEnemy;

//==================================================================================================================
//
// �v���C���[�N���X�̒�`
//
//==================================================================================================================
class CPlayer : public CScene
{
public:
	//=============================================================================
	// �\���̒�`
	//=============================================================================
	// �L�[�v�f
	typedef struct
	{
		D3DXVECTOR3 pos;				// �L�[�v�f�̈ʒu
		D3DXVECTOR3 rot;				// �L�[�v�f�̉�]
	}KEY;

	// �L�[���
	typedef struct
	{
		KEY key[PLAYER_MAX_MODEL];		// �p�[�c��
		int nFram;						// �t���[��
	}KEY_INFO;

	// �v���C���[�̃��[�V����
	typedef struct
	{
		KEY_INFO key_info[10];				// �L�[�����Z�b�g���邩
		D3DXVECTOR3 CollisionOfset;			// �I�t�Z�b�g
		int nLoop;							// ���[�v
		int nNumKey;						// �L�[���̐�
		int Collision_nParts;				// �p�[�c�ԍ�
		int CollisionStartFram;				// �J�n�t���[��
		int CollisionEndFram;				// �I���t���[��
		int Collision_Damage;				// �_���[�W��
		float CollisionRadius;				// �~�̔��a
	}MOTION_PLAYER;

	// ���[�V�����̃^�C�v
	typedef enum
	{
		PLAYER_MOTION_NORMAL = 0,			// �j���[�g����
		PLAYER_MOTION_WALK,					// ����
		PLAYER_MOTION_ACTION,				// �A�N�V����
		PLAYER_MOTION_JUMP,					// �W�����v
		PLAYER_MOTION_LANDING,				// ���n
		PLAYER_MOTION_DAMAGE,				// �_���[�W
		PLAYER_MOTION_MAX					// ���[�V�����̍ő吔
	}PLAYER_MOTION_STATE;

	CPlayer(PRIORITY type);							// �R���X�g���N�^
	~CPlayer();										// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CPlayer *Create(void);					// ��������

	void SetPos(D3DXVECTOR3 pos);					// �ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);					// ��]�ݒ菈��
	void SetnNumPlace(int nNumPlace);				// ���X�|�[���ꏊ�ݒ菈��
	void SetbRand(bool bRand);						// ���n����ݒ菈��
	void SetbRange(bool bRange);					// �͈͓�����ݒ菈��
	void SetRespawn(bool bRespawn);					// ���X�|�[������ݒ菈��
	void SetbGoal(bool bGoal);						// �S�[������ݒ菈��
	void SetbStart(bool bStart);					// �X�^�[�g����ݒ菈��
	void SetbTitleLogo(bool bTitleLogo);			// �^�C�g�����S����ݒ菈��
	void SetbTitleFade(bool bTitleFade);			// �^�C�g���t�F�[�h�ݒ菈��

	D3DXVECTOR3 GetPos(void) { return m_pos; }		// �ʒu�擾����
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// ��]�擾����
	D3DXVECTOR3 GetMove(void) { return m_move; }	// �ړ��ʎ擾����

	int GetnNumPlace(void) {return m_nNumPlace; }	// ���X�|�[���ꏊ�擾����

	bool GetbRand(void);							// ���n����擾����
	bool GetbRange(void);							// �͈͓�����擾����
	bool GetRespawn(void);							// ���X�|�[������擾����
	bool GetbGoal(void);							// �S�[������擾����
	bool GetStart(void);							// �X�^�[�g����擾����
	bool GetbTitleLogo(void);						// �^�C�g�����S����擾����
	bool GetbTitleFade(void);						// �^�C�g���t�F�[�h���菈��

protected:

private:
	void LoadMotion(void);							// ���[�V�����ǂݍ���
	void Moation(void);								// ���[�V����������
	void OperationMove(CInputKeyboard *pInputKeyboard, 
		CInputGamepad *pInputGamepad);				// ���쏈��
	void TitleUpdate(void);							// �^�C�g���ł̃v���C���[�X�V����
	void TutorialUpdate(void);						// �`���[�g���A���ł̃v���C���[�X�V����
	void GameUpdate(void);							// �Q�[���ł̃v���C���[�X�V����
	void bStartUpdate(CFade::FADE fade);			// �v���C���[���ł̃X�^�[�g�̍X�V����
	void bRangeUpdate(float height);				// �v���C���[���ł͈͓̔��ɂ���Ƃ��̍X�V����
	void bRandUpdate(float height);					// �v���C���[���ł̒��n���Ă���Ƃ��̍X�V����
	void nCntRandUpdate(CMeshField *pMeshField, 
		CIntervalFade::INTERVAL_FADE intervalFade);	// �v���C���[���ł̒��n�J�E���g�̍X�V����
	void PlayerModelUpdate(void);					// �v���C���[���ł̃��f���̍X�V����

	float MeshFieldUpdate(CMeshField *pMeshField);	// �v���C���[���ł̃��b�V���t�B�[���h�̍X�V����

	CMotionModel *m_MotionModel[PLAYER_MAX_MODEL];	// ���f�����
	MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];// ���[�V�������
	D3DXMATRIX  m_mtxWorld;							// �}�g���b�N�X

	static CCamera *m_pCamera;				// �J�����̏��|�C���^
	static CMeshOrbit *m_pMeshOrbit;		// �O�Ղ̏��|�C���^
	static CRecord *m_pRecord;				// �L�^���|�C���^
	static CModel *m_pModel;				// ���f�����|�C���^
	static CParticle *m_pParticle;			// �p�[�e�B�N�����|�C���^
	static CEnemy *m_pEnemy;				// �G���|�C���^

	D3DXVECTOR3 m_pos;						// �ʒu
	D3DXVECTOR3 m_posOld;					// �O��̈ʒu
	D3DXVECTOR3 m_rot;						// ��]
	D3DXVECTOR3 m_move;						// �ړ�
	D3DXVECTOR3 m_size;						// �傫��
	D3DXVECTOR3 m_difference;				// ��]�̖ڕW�n�_
	D3DXVECTOR3 posBET[PLAYER_MAX_MODEL];	// �e�p�[�c�̈ʒu
	D3DXVECTOR3 rotBET[PLAYER_MAX_MODEL];	// �e�p�[�c�̉�]
	D3DXVECTOR3 m_RespownPos;				// ���X�|�[���ʒu
	D3DXVECTOR3 m_RespownRot;				// ���X�|�[����]

	int m_MotionType;						// ���[�V�����̎��
	int m_MotionOld;						// �O�̃��[�V����
	int m_Fram;								// �t���[��
	int m_nCntKeySet;						// �L�[�Z�b�g�̃J�E���g
	int m_nCntState;						// �X�e�[�^�X�̃J�E���g
	int m_nCntRand;							// ���n���Ă��Ȃ��J�E���g
	int m_nCntGravity;						// �d�͗p�J�E���g
	int m_nCntTitle;						// �^�C�g���p�J�E���g
	int m_nCntGoal;							// �S�[�������J�E���g
	int m_nNumPlace;						// ���X�|�[���ԍ�
	int m_nCntInterval;						// ���X�|�[���̃C���^�[�o������
	int m_nInterval;						// �p�[�e�B�N���̏o��Ԋu
	int m_nCntTitleFade;					// �^�C�g���t�F�[�h�̃J�E���g

	float m_RotModel;						// ���f���̉�]���
	float m_fStickMove;						// �R���g���[���[�̃X�e�B�b�N�̈ړ���

	bool m_bRand;							// ���n���Ă��邩�ǂ���
	bool m_bRange;							// �͈͓��ɂ��邩�ǂ���
	bool m_bRespawn;						// ���X�|�[���������ǂ���
	bool m_bGoal;							// �L�^�����邩�ǂ���
	bool m_bStart;							// �X�^�[�g�������ǂ���
	bool m_bTitleLogo;						// �^�C�g�����S��\�����Ă������ǂ���
	bool m_bJump;							// �W�����v�������ǂ���
	bool m_bStop;							// �~�܂��Ă��邩�ǂ���
	bool m_bInterval;						// �C���^�[�o�����邩�ǂ���
	bool m_bTitleFade;						// �^�C�g���t�F�[�h���邩�ǂ���
};
#endif