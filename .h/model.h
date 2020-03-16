//==================================================================================================================
//
// ���f���N���X[model.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "sceneX.h"

//==================================================================================================================
//
// ���f���N���X�̒�`
//
//==================================================================================================================
class CModel : public CSceneX
{
public:

	//=============================================================================
	// �I�u�W�F�N�g�̎��
	//=============================================================================
	typedef enum
	{
		MODEL_GOAL_CIRCLE,			// �S�[���ւ���
		MODEL_RESPOWN0,				// ���X�|�[���n�_���f��0
		MODEL_RESPOWN1,				// ���X�|�[���n�_���f��1
		MODEL_RESPOWN2,				// ���X�|�[���n�_���f��2
		MODEL_RESPOWN3,				// ���X�|�[���n�_���f��3
		MODEL_RESPOWN4,				// ���X�|�[���n�_���f��4
		MODEL_RESPOWN5,				// ���X�|�[���n�_���f��5
		MODEL_RESPOWN6,				// ���X�|�[���n�_���f��6
		MODEL_RESPOWN7,				// ���X�|�[���n�_���f��7
		MODEL_RESPOWN8,				// ���X�|�[���n�_���f��8
		MODEL_RESPOWN9,				// ���X�|�[���n�_���f��9
		MODEL_RESPOWN10,			// ���X�|�[���n�_���f��10
		MODEL_RESPOWN11,			// ���X�|�[���n�_���f��11
		MODEL_RESPOWN12,			// ���X�|�[���n�_���f��12
		MODEL_FAUNDATIOIN0,			// �y�䃂�f��0
		MODEL_FAUNDATIOIN_CURVE0,	// �y��J�[�u���f��0
		MODEL_FAUNDATIOIN_CURVE1,	// �y��J�[�u���f��1
		MODEL_FAUNDATIOIN_CURVE2,	// �y��J�[�u���f��2
		MODEL_FAUNDATIOIN_CURVE3,	// �y��J�[�u���f��3
		MODEL_FAUNDATIOIN_CURVE4,	// �y��J�[�u���f��4
		MODEL_FAUNDATIOIN_CURVE5,	// �y��J�[�u���f��5
		MODEL_POLE0,				// �|�[��
		MODEL_SIGNBOARD,			// �Ŕ�
		MODEL_MAX					// �ő吔
	} MODEL;

	CModel(PRIORITY type);							// �R���X�g���N�^
	~CModel();										// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CModel *Create(MODEL type);				// ��������
	static HRESULT Load(void);						// �e�N�X�`���ƃ��f���̏�񃍁[�h
	static void Unload(void);						// �e�N�X�`���ƃ��f���̏��A�����[�h

	bool CollisionBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model);// ���Ɠ_�̓����蔻�菈��
	bool CollisionBlockReturn(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model);// �t����̐��Ɠ_�̓����蔻�菈��
	bool CollisionSphere(D3DXVECTOR3 pos2, float radius1, float radius2, MODEL model);// ���Ƌ��̓����蔻�菈��

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex[MODEL_MAX];				// �e�N�X�`�����
	static LPD3DXMESH m_pMesh[MODEL_MAX];						// ���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat[MODEL_MAX];					// �}�e���A�����ւ̃|�C���^
	static DWORD m_nNumMat[MODEL_MAX];							// �}�e���A�����̐�
	static CModel *m_pModel[MODEL_MAX];							// ���f���̏��|�C���^
	static char *m_apFileName[MODEL_MAX];						// ���f���̃t�@�C����

	D3DXVECTOR3 m_pos;											// �ʒu
	D3DXVECTOR3 m_rot;											// ��]
	D3DXVECTOR3 m_size;											// �傫��
	D3DXVECTOR3 m_RotGoal;										// �S�[���̉�]
	D3DXVECTOR3 m_RespownPos;									// ���X�|�[���ʒu
};
#endif