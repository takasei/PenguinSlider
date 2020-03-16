//==================================================================================================================
//
// �`���[�g���A������[tutorial.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define TUTORIAL_MAX_MODEL 1				// �`���[�g���A���̃��f���̍ő吔

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CCamera;
class CLight;
class CPolygon;
class CMeshField;
class CPlayer;
class CLogo;
class CModel;
class CMeshSphere;
class CIntervalFade;

//==================================================================================================================
//
// �`���[�g���A���N���X�̒�`
//
//==================================================================================================================
class CTutorial
{
public:
	CTutorial();									// �R���X�g���N�^
	~CTutorial();									// �f�X�g���N�^
	void Init(void);								// ����������
	void Uninit(void);								// �I������
	void Update(void);								// �X�V����
	void Draw(void);								// �`�揈��

	static CTutorial *Create(void);					// ��������
	static CPlayer *GetPlayer(void);				// �v���C���[�̏��擾����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̏��|�C���^
	static CCamera *m_pCamera;						// �J�����̂̏��|�C���^
	static CLight *m_pLight;						// ���C�g�̂̏��|�C���^
	static CPolygon *m_pPolygon;					// �|���S���̏��|�C���^
	static CMeshField *m_pMeshField;				// ���b�V���t�B�[���h�̏��|�C���^
	static CPlayer *m_pPlayer;						// �v���C���[�̏��|�C���^
	static CLogo *m_pLogo;							// ���S�̏��|�C���^
	static CModel *m_pModel[TUTORIAL_MAX_MODEL];	// ���f���̏��|�C���^
	static CMeshSphere *m_pMeshSphere;				// ���b�V�����̏��|�C���^
	static CIntervalFade *m_pIntervalFade;			// �C���^�[�o���t�F�[�h�̏��|�C���^

	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuff;			// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;								// �ʒu

};
#endif
