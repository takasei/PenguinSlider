//==================================================================================================================
//
// �`��[scene.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"

//==================================================================================================================
//
// �V�[���N���X�̒�`
//
//==================================================================================================================
class CScene
{
public:

	//=============================================================================
	// �`�揇��
	//=============================================================================
	typedef enum
	{
		PRIORITY_MESH_SPHERE = 0,		// ���b�V����
		PRIORITY_PLAYER,				// �v���C���[
		PRIORITY_ENEMY,					// �G
		PRIORITY_MODEL,					// ���f��
		PRIORITY_FIELD,					// �t�B�[���h
		PRIORITY_SHADOW,				// �e
		PRIORITY_EFFECT,				// �G�t�F�N�g
		PRIORITY_GAME_FADE,				// �Q�[���t�F�[�h
		PRIORITY_UI,					// UI
		PRIORITY_MAX					// �ő�
	} PRIORITY;							// �`�揇��

	CScene(PRIORITY type = PRIORITY_FIELD);					// �R���X�g���N�^
	virtual~CScene();										// �f�X�g���N�^
	virtual void Init(void) = 0;							// ����������
	virtual void Uninit(void) = 0;							// �I������
	virtual void Update(void) = 0;							// �X�V����
	virtual void Draw(void) = 0;							// �`�揈��
	//virtual void SetPos(D3DXVECTOR3 pos) = 0;				// �ʒu�ݒ菈��

	static void UpdateAll(void);							// �S�Ă̍X�V����
	static void DrawAll(void);								// �S�Ă̕`�揈��
	static void ReleaseAll(void);							// �S�ĂɎ��S�t���O���Ă鏈��

	void Deleate(CScene *pScene, int type);					// �폜����

	CScene *GetScene(PRIORITY nPriority, int nCntScene);	// �V�[���擾

protected:
	void Release(void);

private:
	static CScene *m_pTop[PRIORITY_MAX];					// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CScene *m_pCur[PRIORITY_MAX];					// ����(�Ō��)�ւ̃|�C���^

	CScene *m_pPrev;										// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CScene *m_pNext;										// ���̃I�u�W�F�N�g�ւ̃|�C���^

	bool m_bDeth;											// ���S�t���O
};
#endif