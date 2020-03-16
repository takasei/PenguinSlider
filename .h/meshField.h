//==================================================================================================================
//
// ���b�V���t�B�[���h[meshField.h]
// Author : Seiya Takahashi
//
//==================================================================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//==================================================================================================================
// �C���N���[�h�t�@�C��
//==================================================================================================================
#include "main.h"
#include "scene.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define Depth 570									// �c�̃|���S����
#define Width 20									// ���̃u���b�N��
#define WhileX 10.0f								// �C�`�}�X�̒�����
#define WhileY 6.0f									// �C�`�}�X�̒�������
#define WhileZ 10.0f								// �C�`�}�X�̒����c
#define FIELD_TEXTUE "data/TEXTURE/water4.png"		// �ǂݍ��ރe�N�X�`���̃\�[�X��

//==================================================================================================================
// �O���錾
//==================================================================================================================
class CPlayer;

//==================================================================================================================
//
// ���b�V���t�B�[���h�N���X�̒�`
//
//==================================================================================================================
class CMeshField : public CScene
{
public:
	CMeshField(PRIORITY type);								// �R���X�g���N�^
	~CMeshField();											// �f�X�g���N�^
	void Init(void);										// ����������
	void Uninit(void);										// �I������
	void Update(void);										// �X�V����
	void Draw(void);										// �`�揈��

	static CMeshField *Create(void);						// ��������
	static CMeshField *GetMeshField(void);					// ���b�V���t�B�[���h���擾
	static HRESULT Load(void);								// �e�N�X�`����񃍁[�h
	static void Unload(void);								// �e�N�X�`�����A�����[�h

	void SetPos(D3DXVECTOR3 pos);							// �ʒu�ݒ菈��
	void SetMove(D3DXVECTOR3 move);							// �ړ��ʐݒ菈��

	D3DXVECTOR3 GetPos(void);								// �ʒu�擾����
	D3DXVECTOR3 GetMove(void);								// �ړ��ʎ擾����

	float GetHeight(D3DXVECTOR3 pos);						// �����Z�o����

protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	static CMeshField *m_pMeshField;						// ���b�V���t�B�[���h�̃|�C���^
	static CPlayer *m_pPlayer;								// �v���C���[�̏��|�C���^

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;						// �o�b�t�@
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;						// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	VERTEX_3D *m_pVtx;										// ���_�i�[
	D3DXMATRIX m_mtxWorld;									// ���[���h�}�g���b�N�X

	D3DXVECTOR3 m_pos;										// �ʒu
	D3DXVECTOR3 m_rot;										// ��]
	D3DXVECTOR3 m_move;										// �ړ�
	D3DXVECTOR3 m_aVecA[Depth * Width];						// �@���x�N�g����ʂ̐����ꎞ�I�Ɋi�[
	D3DXVECTOR3 m_aVecB[Depth * Width];						// �@���x�N�g����ʂ̐����ꎞ�I�Ɋi�[
	D3DXVECTOR3 m_vectorA;									// A�x�N�g��
	D3DXVECTOR3 m_vectorB;									// B�x�N�g��
	D3DXVECTOR3 m_vectorC;									// C�x�N�g��

	int m_nDepth;											// �c�̃u���b�N��
	int m_nWidth;											// ���̃u���b�N��
	int m_nNumVertex;										// �����_��
	int m_nNumIndex;										// ���C���f�b�N�X��
	int m_nNumPolygon;										// ���|���S����
	int m_nNumber;											// �O�p�`�̔z��̔ԍ�
	int m_nStartBox;										// �n�܂锠
	int m_nEndBox;											// ������锠

	float fDivide;											// sin�̒��g������ϐ�
};
#endif