//==================================================================================================================
//
// ���f���^�C�v�ʕ`��[tpy.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "model.h"
#include "debugProc.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define COLLISION_SIZE 100.0f								// �����蔻��̑傫��
#define TUTORIAL_COLLISION_SIZE 150.0f						// �`���[�g���A�����̓����蔻��̑傫��

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CModel::m_pTex[MODEL_MAX] = {};			// �e�N�X�`�����
LPD3DXMESH CModel::m_pMesh[MODEL_MAX] = {};					// ���b�V�����
LPD3DXBUFFER CModel::m_pBuffMat[MODEL_MAX] = {};			// �o�b�t�@���
DWORD CModel::m_nNumMat[MODEL_MAX] = {};					// �}�e���A�����̐�
CModel *CModel::m_pModel[MODEL_MAX] = {};					// ���f�����
char *CModel::m_apFileName[MODEL_MAX] =						// �ǂݍ��ރ��f���̃\�[�X��
{
	{ "data/MODEL/GoalCircle2.x" },							// �S�[���ւ���
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��0
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��1
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��2
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��3
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��4
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��5
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��6
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��7
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��8
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��9
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��10
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��11
	{ "data/MODEL/arrow.x" },								// ���X�|�[�����f��12
	{ "data/MODEL/foundation.x" },							// �y�䃂�f��0
	{ "data/MODEL/faudationCurve.x" },						// �y��J�[�u���f��0
	{ "data/MODEL/faudationCurve1.x" },						// �y��J�[�u���f��1
	{ "data/MODEL/faudationCurve2.x" },						// �y��J�[�u���f��2
	{ "data/MODEL/faudationCurve3.x" },						// �y��J�[�u���f��3
	{ "data/MODEL/faudationCurve4.x" },						// �y��J�[�u���f��4
	{ "data/MODEL/faudationCurve5.x" },						// �y��J�[�u���f��5
	{ "data/MODEL/pole.x" },								// �|�[��
	{ "data/MODEL/signboard.x" },							// �Ŕ�
};

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CModel::CModel(PRIORITY type = CScene::PRIORITY_MODEL) :CSceneX(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CModel::~CModel()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CModel::Init(void)
{
	// sceneX�̏���������
	CSceneX::Init();

	// �ϐ��̏�����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ��]
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �傫��
	m_RotGoal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �S�[���̉�]
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CModel::Uninit(void)
{
	// sceneX�̏I������
	CSceneX::Uninit();
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CModel::Update(void)
{
	// �`���[�g���A���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		m_RotGoal = m_pModel[MODEL_GOAL_CIRCLE]->GetRot();	// �S�[���ւ������f����]�擾

		// ��]���Z
		m_RotGoal.z += 0.011f;

		m_pModel[MODEL_GOAL_CIRCLE]->SetRot(m_RotGoal);		// �S�[���ւ������f����]�ݒ�
	}
	else if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{// �Q�[���̂Ƃ�
		m_RotGoal = m_pModel[MODEL_GOAL_CIRCLE]->GetRot();	// �S�[���ւ������f����]�擾

		// ��]���Z
		m_RotGoal.z += 0.0005f;

		m_pModel[MODEL_GOAL_CIRCLE]->SetRot(m_RotGoal);		// �S�[���ւ������f����]�ݒ�
	}
	m_size = GetSize();									// �傫���擾
	m_pos = GetPos();									// �ʒu�擾

	SetSize(m_size);									// �傫���ݒ�
	SetPos(m_pos);										// �ʒu�ݒ�

	// sceneX�̍X�V����
	CSceneX::Update();
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CModel::Draw(void)
{
	// sceneX�̕`�揈��
	CSceneX::Draw();
}

//==================================================================================================================
// ��������
//==================================================================================================================
CModel *CModel::Create(MODEL type)
{
	// ���f�����𓮓I�Ɋm��
	m_pModel[type] = new CModel(CScene::PRIORITY_MODEL);

	// ���f��������Ƃ�
	if (m_pModel[type] != NULL)
	{
		m_pModel[type]->Init();																// ���f���̏�����
		m_pModel[type]->BindModel(m_pBuffMat[type], m_nNumMat[type], m_pMesh[type]);		// ���f���̕ϐ�������������
		m_pModel[type]->BindTex(m_pTex[type]);												// �e�N�X�`���̕ϐ�������������
	}

	// �l��Ԃ�
	return m_pModel[type];
}

//==================================================================================================================
// �e�N�X�`���ƃ��f�����[�h
//==================================================================================================================
HRESULT CModel::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();				// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();			// �f�o�C�X�̎擾

	// ���f���̍ő吔�܂ŃJ�E���g
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice, "", &m_pTex[nCnt]);

		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			m_apFileName[nCnt],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCnt],
			NULL,
			&m_nNumMat[nCnt],
			&m_pMesh[nCnt]);
	}

	// �l��Ԃ�
	return S_OK;
}

//==================================================================================================================
// �e�N�X�`���ƃ��f���j��
//==================================================================================================================
void CModel::Unload(void)
{
	// ���f���̍ő��ނ܂ŃJ�E���g
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// �e�N�X�`��������Ƃ�
		if (m_pTex[nCnt] != NULL)
		{
			m_pTex[nCnt]->Release();			// �e�N�X�`�����
			m_pTex[nCnt] = NULL;				// NULL�ɂ���
		}

		// ���b�V��������Ƃ�
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();			// ���b�V���̊J��
			m_pMesh[nCnt] = NULL;				// NULL�ɂ���
		}

		// �o�b�t�@������Ƃ�
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();		// �}�e���A���̊J��
			m_pBuffMat[nCnt] = NULL;			// NULL�ɂ���
		}
	}
}

//==================================================================================================================
// ���Ɠ_�̓����蔻��
//==================================================================================================================
bool CModel::CollisionBlock(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model)
{
	// �����蔻��p�ϐ�
	bool bHit = false;
	m_pos = m_pModel[model]->GetPos();			// ���f���̈ʒu�擾

	// ���f���̎�ނɂ���Đ؂�ւ���
	switch (model)
	{
		// �S�[���ւ����̂Ƃ�
	case MODEL_GOAL_CIRCLE:
		// �`���[�g���A���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
		{
			// ���f���̉����͈͓̔��ɂ���Ƃ�
			if (m_pos.x - TUTORIAL_COLLISION_SIZE < posOld.x && m_pos.x + TUTORIAL_COLLISION_SIZE > posOld.x)
			{
				// �����烂�f���̂Ԃ�����
				if (m_pos.z - 1.0f > posOld.z && m_pos.z - 1.0f <= pos.z)
				{
					// �����������Ƃɂ���
					bHit = true;
				}
			}
		}
		else if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{// �Q�[���̂Ƃ�
			// ���f���̉����͈͓̔��ɂ���Ƃ�
			if (m_pos.z - COLLISION_SIZE < posOld.z && m_pos.z + COLLISION_SIZE > posOld.z)
			{
				// �����烂�f���̂Ԃ�����
				if (m_pos.x - 1.0f > posOld.x && m_pos.x - 1.0f <= pos.x)
				{
					// �����������Ƃɂ���
					bHit = true;
				}
			}
		}
		break;
	}

	// �l��Ԃ�
	return bHit;
}

//==================================================================================================================
// �t����̐��Ɠ_�̓����蔻��
//==================================================================================================================
bool CModel::CollisionBlockReturn(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 posOld, MODEL model)
{
	// �����蔻��p�ϐ�
	bool bHit = false;
	m_pos = m_pModel[model]->GetPos();			// ���f���̈ʒu�擾

	// ���f���̎�ނɂ���Đ؂�ւ���
	switch (model)
	{
		// �S�[���ւ����̂Ƃ�
	case MODEL_GOAL_CIRCLE:
		// �Q�[���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			// ���f���̉����͈͓̔��ɂ���Ƃ�
			if (m_pos.z - COLLISION_SIZE < posOld.z && m_pos.z + COLLISION_SIZE > posOld.z)
			{
				// �����烂�f���̂Ԃ�����
				if (m_pos.x + 1.0f < posOld.x && m_pos.x + 1.0f >= pos.x)
				{
					// �����������Ƃɂ���
					bHit = true;
				}
			}
		}
		break;
	}

	// �l��Ԃ�
	return bHit;
}

//==================================================================================================================
// ���Ƌ��̓����蔻��
//==================================================================================================================
bool CModel::CollisionSphere(D3DXVECTOR3 pos2, float radius1, float radius2, MODEL model)
{
	// �����蔻��p�ϐ�
	bool bHit = false;

	// ���f���̈ʒu�擾
	m_pos = m_pModel[model]->GetPos();

	// ���ꂼ��̎��̍������߂�
	float XDistance = m_pos.x - pos2.x;
	float YDistance = m_pos.y - pos2.y;
	float ZDistance = m_pos.z - pos2.z;
	float fRadius = radius1 + radius2;

	// ���Ƌ����Ԃ������Ƃ�
	if (XDistance * XDistance + YDistance * YDistance + ZDistance * ZDistance <= fRadius * fRadius)
	{
		// �����������Ƃɂ���
		bHit = true;
	}

	// �l��Ԃ�
	return bHit;
}

