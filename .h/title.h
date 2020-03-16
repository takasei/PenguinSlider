//==================================================================================================================
//
// �^�C�g������[title.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _TITLE_H
#define _TITLE_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MAX_TITLE_MODEL 1		// �^�C�g���Ŏg�����f���̐�

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CLight;
class CPolygon;
class CMeshField;
class CLogo;
class CPlayer;
class CMeshSphere;
class CModel;
class CTitleFade;

//==================================================================================================================
//
// �^�C�g���N���X�̒�`
//
//==================================================================================================================
class CTitle
{
public:
	
	CTitle();									// �R���X�g���N�^
	~CTitle();									// �f�X�g���N�^
	void Init(void);							// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	static CTitle *Create(void);				// ��������
	static CPlayer *GetPlayer(void);			// �v���C���[�̏��擾����
	static CCamera *GetCamera(void);			// �J�����̏��擾����

protected:

private:
	void SetModel(void);						// ���f���̐ݒ菈��

	static LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`�����
	static CCamera *m_pCamera;					// �J�����̏��
	static CLight *m_pLight;					// ���C�g�̏��
	static CPolygon *m_pPolygon;				// �|���S�����
	static CMeshField *m_pMeshField;			// ���b�V���t�B�[���h�̏��
	static CLogo *m_pLogo;						// ���S�̏��
	static CPlayer *m_pPlayer;					// �v���C���[�̏��|�C���^
	static CMeshSphere *m_pMeshSphere;			// ���b�V�����̏��|�C���^
	static CModel *m_pModel[MAX_TITLE_MODEL];	// ���f���̏��|�C���^
	static CTitleFade *m_pTitleFade;			// �^�C�g���t�F�[�h�̏��|�C���^

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuff;		// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;							// �ʒu

	int m_nCntRanking;							// �����L���O�ւ̃J�E���^
};

#endif
