//==================================================================================================================
//
// �J����[camera.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CPlayer;

//==================================================================================================================
//
// �J�����N���X�̒�`
//
//==================================================================================================================
class CCamera
{
public:
	CCamera();							// �R���X�g���N�^
	~CCamera();							// �f�X�g���N�^
	void Init();						// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static CCamera *Create(void);		// ��������

	void SetCamera(void);				// �J�����̐ݒ菈��
	void SetRot(D3DXVECTOR3 rot);		// ��]�ݒ菈��
	void SetPosV(D3DXVECTOR3 posV);		// ���_�ʒu�ݒ菈��

	D3DXVECTOR3 GetRot(void);			// ��]�擾����
	D3DXVECTOR3 GetPosV(void);			// ���_�ʒu�ݒ菈��

protected:

private:
	static CCamera *m_pCamera;			// �J�������
	static CPlayer *m_pPlayer;			// �v���C���[���

	D3DXMATRIX m_mtxProjection;			// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;				// �r���[�}�g���b�N�X

	D3DXVECTOR3 m_posV;					// ���_
	D3DXVECTOR3 m_posVDest;				// ���_�̖ڕW�n�_
	D3DXVECTOR3 m_posR;					// �����_(�Q�Ɠ_)
	D3DXVECTOR3 m_posRDest;				// �����_(�Q�Ɠ_)�̖ڕW�n�_
	D3DXVECTOR3 m_posU;					// ������x�N�g��
	D3DXVECTOR3 m_rot;					// ��]
	D3DXVECTOR3 m_rotDest;				// ��]�̖ڕW�n�_

	int nCntRot;						// ��]���n�߂�J�E���^
	int m_nCntTitleFade;				// �^�C�g���t�F�[�h�̃J�E���^

	float m_fDistance;					// ����
};
#endif