//==================================================================================================================
//
// ���f���N���X[model.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _MOTIONMODEL_H_
#define _MOTIONMODEL_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "sceneX.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MODEL_SIZE_X	(100)								// X�T�C�Y
#define MODEL_SIZE_Y	(100)								// Y�T�C�Y

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CPlayer;

//==================================================================================================================
//
// �A�j���[�V�������f���N���X�̒�`
//
//==================================================================================================================
class CMotionModel
{
public:

	//=============================================================================
	// �I�u�W�F�N�g�̎��
	//=============================================================================
	typedef enum
	{
		MODEL_PENGUIN_BODY = 0,			// �v���C���[�̑�
		MODEL_PENGUIN_HEAD,				// �v���C���[�̓�
		MODEL_PENGUIN_LARM,				// �v���C���[�̍��r
		MODEL_PENGUIN_RARM,				// �v���C���[�̉E�r
		MODEL_PENGUIN_LLEG,				// �v���C���[�̍���
		MODEL_PENGUIN_RLEG,				// �v���C���[�̉E��
		MODEL_MAX						// �ő吔
	}CHARA_MODEL;

	CMotionModel();												// �R���X�g���N�^
	~CMotionModel();											// �f�X�g���N�^
	void Init(void);											// ����������
	void Uninit(void);											// �I������
	void Update(void);											// �X�V����
	void Draw(void);											// �`�揈��

	static CMotionModel *CreateObject(CHARA_MODEL type);		// ��������
	static CMotionModel *GetModel(CHARA_MODEL type);			// ���f�����擾����
	static HRESULT Load(void);									// �e�N�X�`���ƃ��f���̏�񃍁[�h
	static void Unload(void);									// �e�N�X�`���ƃ��f���̏��A�����[�h

	void SetParent(CMotionModel *pMotionModel);						// �e�ݒ菈��
	void SetMtxCenter(D3DXMATRIX mtxWorld);						// ���S�̃}�g���b�N�X�ݒ菈��
	void SetPos(D3DXVECTOR3 pos);								// �ʒu�ݒ菈��
	void SetRot(D3DXVECTOR3 rot);								// ��]�ݒ菈��
	void SetSize(D3DXVECTOR3 size);								// �傫���ݒ菈��
	void SetMove(D3DXVECTOR3 move);								// �ړ��ʐݒ菈��

	D3DXVECTOR3 GetPos(void);									// �ʒu�擾����
	D3DXVECTOR3 GetRot(void);									// ��]�擾����
	D3DXVECTOR3 GetSize(void);									// �傫���擾����
	D3DXVECTOR3 GetMove(void);									// �ړ��ʎ擾����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex[MODEL_MAX];				// �e�N�X�`�����
	static LPD3DXMESH m_pMesh[MODEL_MAX];						// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[MODEL_MAX];					// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat[MODEL_MAX];							// �}�e���A�����̐�
	static CMotionModel *m_pMotionModel[MODEL_MAX];				// ���f���̏��|�C���^
	static CPlayer *m_pPlayer;									// �v���C���[���|�C���^
	static char *m_apFileName[MODEL_MAX];						// ���f���̃t�@�C����

	D3DXMATRIX m_mtxWorld;										// �}�g���b�N�X
	D3DXMATRIX m_mtxWorldCenter;								// ���S�̃}�g���b�N�X
	CMotionModel *m_pParent;									// �e�̃|�C���^
	CHARA_MODEL m_type;											// ���f���̎��

	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_rot;											// ��]
	D3DXVECTOR3 m_size;											// �傫��
	D3DXVECTOR3 m_move;											// �ړ���

	bool m_bRespawn;											// ���X�|�[���������ǂ���
};
#endif