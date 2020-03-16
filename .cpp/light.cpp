//==================================================================================================================
//
// ���C�g����[light.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "light.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "debugProc.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define LIGHT_MOVE 0.1f			// ���C�g�̈ړ���

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
CLight *CLight::m_pLight = NULL;									//���C�g�̏��

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CLight::CLight()
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CLight::~CLight()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CLight::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X���擾����

	// ���C�g���N���A����
	ZeroMemory(&m_alight[0], sizeof(D3DLIGHT9));
	ZeroMemory(&m_alight[1], sizeof(D3DLIGHT9));
	ZeroMemory(&m_alight[2], sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	m_alight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_alight[1].Type = D3DLIGHT_DIRECTIONAL;
	m_alight[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_alight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_alight[1].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 0.0f);
	m_alight[2].Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.0f);

	// ���C�g�̕����̐ݒ�
	m_avecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);				// �ʒu
	D3DXVec3Normalize(&m_avecDir[0], &m_avecDir[0]);				// ���K������
	m_alight[0].Position = m_avecDir[0];

	// ���C�g�̕����̐ݒ�
	m_avecDir[1] = D3DXVECTOR3(-0.18f, 0.87f, -0.44f);				// �ʒu
	D3DXVec3Normalize(&m_avecDir[1], &m_avecDir[1]);				// ���K������
	m_alight[1].Direction = m_avecDir[1];

	// ���C�g�̕����̐ݒ�
	m_avecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);				// �ʒu
	D3DXVec3Normalize(&m_avecDir[2], &m_avecDir[2]);				// ���K������
	m_alight[2].Direction = m_avecDir[2];

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_alight[0]);
	pDevice->SetLight(1, &m_alight[1]);
	pDevice->SetLight(2, &m_alight[2]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CLight::Uninit(void)
{

}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CLight::Update(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();					// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();				// �f�o�C�X���擾����

	// ���C�g�̕����̐ݒ�
	D3DXVec3Normalize(&m_avecDir[0], &m_avecDir[0]);				// ���K������
	m_alight[0].Direction = m_avecDir[0];

	// ���C�g�̕����̐ݒ�
	D3DXVec3Normalize(&m_avecDir[1], &m_avecDir[1]);				// ���K������
	m_alight[1].Direction = m_avecDir[1];

	// ���C�g�̕����̐ݒ�
	D3DXVec3Normalize(&m_avecDir[2], &m_avecDir[2]);				// ���K������
	m_alight[2].Direction = m_avecDir[2];

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_alight[0]);
	pDevice->SetLight(1, &m_alight[1]);
	pDevice->SetLight(2, &m_alight[2]);
}

//==================================================================================================================
// ���C�g�̐���
//==================================================================================================================
CLight * CLight::Create(void)
{
	// �������𓮓I�Ɋm��
	m_pLight = new CLight();

	// ���C�g�̏�����
	m_pLight->Init();

	// �l��Ԃ�
	return m_pLight;
}

