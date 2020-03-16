//==================================================================================================================
//
// ���f���^�C�v�ʕ`��[motionModel.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "motionModel.h"
#include "debugProc.h"
#include "game.h"
#include "player.h"

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CMotionModel::m_pTex[MODEL_MAX] = {};		// �e�N�X�`�����
LPD3DXMESH CMotionModel::m_pMesh[MODEL_MAX] = {};				// ���b�V�����
LPD3DXBUFFER CMotionModel::m_pBuffMat[MODEL_MAX] = {};			// �o�b�t�@���
DWORD CMotionModel::m_nNumMat[MODEL_MAX] = {};					// �}�e���A�����̐�
CMotionModel *CMotionModel::m_pMotionModel[MODEL_MAX] = {};		// ���f�����
CPlayer *CMotionModel::m_pPlayer = NULL;						// �v���C���[���
char *CMotionModel::m_apFileName[MODEL_MAX] =					// �ǂݍ��ރ��f���̃\�[�X��
{
	{ "data/MODEL/PenguinBody.x" },								// �y���M����
	{ "data/MODEL/PenguinHead.x" },								// �y���M����
	{ "data/MODEL/PenguinLArm.x" },								// �y���M�����r
	{ "data/MODEL/PenguinRArm.x" },								// �y���M���E�r
	{ "data/MODEL/PenguinLLeg.x" },								// �y���M������
	{ "data/MODEL/PenguinRLeg.x" },								// �y���M���E��
};

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CMotionModel::CMotionModel()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CMotionModel::~CMotionModel()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CMotionModel::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// �傫��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ��]
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
	m_pParent = NULL;									// �e���f���ԍ�
	m_type = MODEL_PENGUIN_BODY;						// ���f���^�C�v
	m_bRespawn = false;									// ���X�|�[���������ǂ���
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CMotionModel::Uninit(void)
{
	// �S�Ẵ��f���J�E���g
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// ���b�V��������Ƃ�
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();				// �J��
			m_pMesh[nCnt] = NULL;					// NULL�ɂ���
		}

		// �}�e���A��������Ƃ�
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();			// �J��
			m_pBuffMat[nCnt] = NULL;				// NULL�ɂ���
		}
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CMotionModel::Update(void)
{
	m_rot = GetRot();				// ��]���擾
	m_size = GetSize();				// �傫���擾
	m_pos = GetPos();				// �ʒu�擾
	m_move = GetMove();				// �ړ��ʎ擾

	SetRot(m_rot);					// ��]���ݒ�
	SetSize(m_size);				// �傫���ݒ�
	SetPos(m_pos);					// �ʒu�ݒ�
	SetMove(m_move);				// �ړ��ʐݒ�
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CMotionModel::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;					// �v�Z�p�i�[�ϐ�
	D3DXMATERIAL *pMat;										// ���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;									// �}�e���A�����|�C���^

	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// �v���C���[�̏��擾
		m_pPlayer = CGame::GetPlayer();

		// �v���C���[������Ƃ�
		if (m_pPlayer != NULL)
		{
			// �v���C���[�̃��X�|�[������擾
			m_bRespawn = m_pPlayer->GetRespawn();
		}
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScale, m_size.x, m_size.y, m_size.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	// 2�̍s��̐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X���
	m_pos.x = m_mtxWorld._41;
	m_pos.y = m_mtxWorld._42;
	m_pos.z = m_mtxWorld._43;

	//�e�q�֌W
	if (m_pParent == NULL)
	{
		// 2�̍s��̐�
		D3DXMatrixMultiply(&m_mtxWorld,	&m_mtxWorld, &m_mtxWorldCenter);
	}
	else
	{// �e��NULL����Ȃ��Ƃ�
		// 2�̍s��̐�
		D3DXMatrixMultiply(&m_mtxWorld,	&m_mtxWorld, &m_pParent->m_mtxWorld);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat[m_type]->GetBufferPointer();

	// ���f���̕`��
	for (int nCnt = 0; nCnt < (int)m_nNumMat[m_type]; nCnt++)
	{
		// �Q�[���̂Ƃ�
		if (CRenderer::GetMode() == CRenderer::MODE_GAME)
		{
			// ���X�|�[�������Ƃ�
			if (m_bRespawn == true)
			{
				// ���f���_�ŗp�J�E���^
				for (int nCntCol = 0; nCntCol < 20; nCntCol++)
				{
					// �}�e���A���̐F�ݒ�
					pMat[nCnt].MatD3D.Diffuse.a = (nCntCol % 2) * 1.0f;
				}

				// ���X�|�[�����Ă��Ȃ���Ԃɂ���
				m_bRespawn = false;

				// ���X�|�[������ݒ�
				m_pPlayer->SetRespawn(m_bRespawn);
			}
		}

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCnt].MatD3D);

		// �`��
		m_pMesh[m_type]->DrawSubset(nCnt);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// ��������
//==================================================================================================================
CMotionModel *CMotionModel::CreateObject(CHARA_MODEL type)
{
	// �V�[�����I�Ɋm��
	m_pMotionModel[type] = new CMotionModel();

	// ���f��������Ƃ�
	if (m_pMotionModel[type] != NULL)
	{
		m_pMotionModel[type]->Init();				// ���f���̏�����
		m_pMotionModel[type]->m_type = type;		// ���f���^�C�v�ݒ�
	}

	// �l��Ԃ�
	return m_pMotionModel[type];
}

//==================================================================================================================
// ���f�����擾
//==================================================================================================================
CMotionModel * CMotionModel::GetModel(CHARA_MODEL type)
{
	return m_pMotionModel[type];
}

//==================================================================================================================
// ���f���̃��[�h
//==================================================================================================================
HRESULT CMotionModel::Load(void)
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
void CMotionModel::Unload(void)
{
	for (int nCnt = 0; nCnt < MODEL_MAX; nCnt++)
	{
		// �e�N�X�`��������Ƃ�
		if (m_pTex[nCnt] != NULL)
		{
			m_pTex[nCnt]->Release();					// �e�N�X�`�����
			m_pTex[nCnt] = NULL;						// NULL�ɂ���
		}

		// ���b�V��������Ƃ�
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();					// ���b�V���̊J��
			m_pMesh[nCnt] = NULL;						// NULL�ɂ���
		}

		// �o�b�t�@������Ƃ�
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();				// �}�e���A���̊J��
			m_pBuffMat[nCnt] = NULL;					// NULL�ɂ���
		}
	}
}

//==================================================================================================================
// �ʒu�擾
//==================================================================================================================
D3DXVECTOR3 CMotionModel::GetPos(void)
{
	return m_pos;
}

//==================================================================================================================
// ��]�擾
//==================================================================================================================
D3DXVECTOR3 CMotionModel::GetRot(void)
{
	return m_rot;
}

//==================================================================================================================
// �傫���擾
//==================================================================================================================
D3DXVECTOR3 CMotionModel::GetSize(void)
{
	return m_size;
}

//==================================================================================================================
// �ړ��ʎ擾
//==================================================================================================================
D3DXVECTOR3 CMotionModel::GetMove(void)
{
	return m_move;
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CMotionModel::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// ��]�ݒ�
//==================================================================================================================
void CMotionModel::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//==================================================================================================================
// �傫���ݒ�
//==================================================================================================================
void CMotionModel::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//==================================================================================================================
// �ړ��ʐݒ�
//==================================================================================================================
void CMotionModel::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}

//==================================================================================================================
// �e�̃��f���ݒ�
//==================================================================================================================
void CMotionModel::SetParent(CMotionModel * pMotionModel)
{
	m_pParent = pMotionModel;
}

//==================================================================================================================
// ���S�̃}�g���b�N�X�ݒ�
//==================================================================================================================
void CMotionModel::SetMtxCenter(D3DXMATRIX mtxWorld)
{
	m_mtxWorldCenter = mtxWorld;
}
