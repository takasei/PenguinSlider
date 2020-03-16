//==================================================================================================================
//
// ���b�V���t�B�[���h����[meshField.cpp]
// Author : Seiya Takahashi
//
//==================================================================================================================
#include "renderer.h"
#include "meshField.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "player.h"
#include "tutorial.h"
#include "game.h"
#include "title.h"

//==================================================================================================================
// �}�N����`
//==================================================================================================================
#define MASS_WIDTH 15										// ���̃}�X
#define TUTORIAL_MASS_WIDTH 25								// �`���[�g���A�����̉��̃}�X
#define MASS_DEPTH 200										// �c�̃}�X
#define CURVE_NUMBER 16										// �J�[�u���炩��
#define FIELD_ALPHA 0.1f									// ���b�V���t�B�[���h�A���t�@
#define START_NUMBER0 0										// 0�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER0 35									// 0�Ԗڂ̏I���ԍ�
#define START_NUMBER1 FINISH_NUMBER0 + 1					// 1�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER1 43									// 1�Ԗڂ̏I���ԍ�
#define START_NUMBER2 FINISH_NUMBER1 + 1					// 2�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER2 150									// 2�Ԗڂ̏I���ԍ�
#define START_NUMBER3 FINISH_NUMBER2 + 1					// 3�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER3 158									// 3�Ԗڂ̏I���ԍ�
#define START_NUMBER4 FINISH_NUMBER3 + 1					// 4�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER4 198									// 4�Ԗڂ̏I���ԍ�
#define START_NUMBER5 FINISH_NUMBER4 + 1					// 5�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER5 214									// 5�Ԗڂ̏I���ԍ�
#define START_NUMBER6 FINISH_NUMBER5 + 1					// 6�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER6 314									// 6�Ԗڂ̏I���ԍ�
#define START_NUMBER7 FINISH_NUMBER6 + 1					// 7�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER7 317									// 7�Ԗڂ̏I���ԍ�
#define START_NUMBER8 FINISH_NUMBER7 + 1					// 8�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER8 392									// 8�Ԗڂ̏I���ԍ�
#define START_NUMBER9 FINISH_NUMBER8 + 1					// 9�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER9 400									// 9�Ԗڂ̏I���ԍ�
#define START_NUMBER10 FINISH_NUMBER9 + 1					// 10�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER10 415									// 10�Ԗڂ̏I���ԍ�
#define START_NUMBER11 FINISH_NUMBER10 + 1					// 11�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER11 435									// 11�Ԗڂ̏I���ԍ�
#define START_NUMBER12 START_NUMBER11 + 1					// 12�Ԗڂ̎n�܂�ԍ�
#define FINISH_NUMBER12 570									// 12�Ԗڂ̏I���ԍ�

//==================================================================================================================
// �ÓI�����o�ϐ��̏�����
//==================================================================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;			// �e�N�X�`���ϐ�
CMeshField *CMeshField::m_pMeshField = NULL;				// ���b�V���t�B�[���h�̏��
CPlayer *CMeshField::m_pPlayer = NULL;						// �v���C���[�̏��

//==================================================================================================================
// �R���X�g���N�^
//==================================================================================================================
CMeshField::CMeshField(PRIORITY type = CScene::PRIORITY_FIELD) : CScene(type)
{

}

//==================================================================================================================
// �f�X�g���N�^
//==================================================================================================================
CMeshField::~CMeshField()
{

}

//==================================================================================================================
// ����������
//==================================================================================================================
void CMeshField::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();		// �����_���[���擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();	// �f�o�C�X�̎擾

	// �^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		m_nDepth = 300;									// �c�̃u���b�N��
		m_nWidth = MASS_WIDTH;							// ���̃u���b�N��
	}

	// �`���[�g���A���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		m_nDepth = MASS_DEPTH;							// �c�̃u���b�N��
		m_nWidth = TUTORIAL_MASS_WIDTH;					// ���̃u���b�N��
	}

	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		m_nDepth = FINISH_NUMBER12;						// �c�̃u���b�N��
		m_nWidth = MASS_WIDTH;							// ���̃u���b�N��
	}

	// �ʒu�E��]�̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ��]
	m_nNumVertex = ((m_nWidth + 1) * m_nDepth * 2) + (m_nDepth - 1) * 2;// �����_��
	m_nNumIndex = (m_nDepth + 1) * (m_nWidth + 1);						// ���C���f�b�N�X��
	m_nNumPolygon = m_nNumVertex - 2;									// �O�p�`�̐�
	m_aVecA[m_nDepth * m_nWidth] = {};									// �@���x�N�g����ʂ̐����ꎞ�I�Ɋi�[
	m_aVecB[m_nDepth * m_nWidth] = {};									// �@���x�N�g����ʂ̐����ꎞ�I�Ɋi�[
	m_vectorA = D3DXVECTOR3(0, 0, 0);									// ��ڂ̊O�ϗp�ϐ�
	m_vectorB = D3DXVECTOR3(0, 0, 0);									// ��ڂ̊O�ϗp�ϐ�
	m_vectorC = D3DXVECTOR3(0, 0, 0);									// �O�ڂ̊O�ϗp�ϐ�
	m_nNumber = 0;														// �z��̔ԍ�
	m_nStartBox = m_nWidth + 1;											// �n�܂锠
	m_nEndBox = 0;														// ������锠
	fDivide = 0;														// sin�̒��g������ϐ�

	// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * m_nNumVertex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// ���_���W�̐ݒ�
			m_pVtx[0].pos.x = (-WhileX * m_nWidth) / 2 + WhileX * nWide;
			m_pVtx[0].pos.y = 0.0f;
			m_pVtx[0].pos.z = (WhileZ / 2 * m_nDepth) - WhileZ * nDepth;

			// ���_�J���[
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, FIELD_ALPHA);

			// �e�N�X�`���`�ʂ̈ʒu
			m_pVtx[0].tex = D3DXVECTOR2(1.0f * nWide, 1.0f * nDepth);

			// ���_�ԍ����Z
			m_pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//////////////////////////////�@���x�N�g��//////////////////////////////
	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// �C���f�b�N�X�ԍ�
			int nIdx = nDepth * (m_nWidth + 1) + nWide;

			// �[�͌v�Z�����Ȃ�
			if (nWide != m_nWidth && nDepth != m_nDepth)
			{
				m_vectorA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;								// ��ڂ̃x�N�g��
				m_vectorB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;							// ��ڂ̃x�N�g��
				m_vectorC = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;								// �O�ڂ̃x�N�g��
				D3DXVec3Cross(&m_aVecA[m_nNumber], &m_vectorA, &m_vectorB);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecA[m_nNumber], &m_aVecA[m_nNumber]);								// ���K������
				D3DXVec3Cross(&m_aVecB[m_nNumber], &m_vectorB, &m_vectorC);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecB[m_nNumber], &m_aVecB[m_nNumber]);								// ���K������

				// �z��̔ԍ�1�v���X����
				m_nStartBox++;
				m_nEndBox++;
				m_nNumber++;
			}

			// �E�ゾ�����Ƃ�
			if (nIdx == m_nWidth)
			{
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecB[m_nWidth - 1];
			}
			else if (nIdx == m_nDepth * (m_nWidth + 1))
			{// �����������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecA[(m_nDepth - 1) * m_nWidth];
			}
			else if (nIdx == 0)
			{// ���ゾ�����Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[nIdx] + m_aVecB[nIdx]) / 2;
			}
			else if (nIdx == (m_nDepth + 1) * (m_nWidth + 1) - 1)
			{// �E���������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[m_nDepth * m_nWidth - 1] + m_aVecB[m_nDepth * m_nWidth - 1]) / 2;
			}
			else if (nWide != 0 && nWide != m_nWidth)
			{// ���̗񂪒[����Ȃ��Ƃ�
				// �c�����ڂ������Ƃ�
				if (nDepth == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[nWide - 1] + m_aVecA[nWide] + m_aVecB[nWide]) / 3;
				}
				else if (nDepth == m_nDepth)
				{// �c���Ō���������Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[(m_nDepth - 1) * m_nWidth - 1 + nWide] +
						m_aVecA[(m_nDepth - 1) * m_nWidth + nWide] +
						m_aVecB[(m_nDepth - 1) * m_nWidth + nWide]) / 3;
				}
				else
				{// ����ȊO
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1]) / 6;
				}
			}
			else if (nDepth != 0 && nDepth != m_nDepth)
			{// �c�̗񂪒[����Ȃ��Ƃ�
				// �擪�̂Ƃ�
				if (nWide == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nDepth - 1) * m_nWidth] +
						m_aVecB[m_nWidth + (nDepth - 1) * m_nWidth] +
						m_aVecA[m_nWidth + (nDepth - 1) * m_nWidth]) / 3;
				}
				else if (nWide == m_nWidth)
				{// �Ō���̂Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[m_nWidth - 1 + m_nWidth * (nDepth - 1)] +
						m_aVecA[m_nWidth - 1 + m_nWidth * (nDepth - 1)] +
						m_aVecB[m_nWidth - 1 + m_nWidth * nDepth]) / 3;
				}
			}
		}
		// �z��̔ԍ�1�v���X����
		m_nStartBox++;
		m_nEndBox++;
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	WORD *pIdx;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �c���J�E���g
	for (int nCntY = 0; nCntY < m_nDepth; nCntY++)
	{
		// ��s�ڂ���Ȃ��Ƃ�
		if (nCntY != 0)
		{
			pIdx[0] = (m_nWidth + 1) + nCntY * (m_nWidth + 1);
			pIdx++;
		}

		// �����J�E���g
		for (int nCntX = 0; nCntX < m_nWidth + 1; nCntX++)
		{
			pIdx[0] = (m_nWidth + 1) + nCntX + nCntY * (m_nWidth + 1);
			pIdx[1] = nCntX + nCntY * (m_nWidth + 1);
			pIdx += 2;
		}

		// �k�ރ|���S��
		if (nCntY + 1 < m_nDepth)
		{
			pIdx[0] = m_nWidth + nCntY * (m_nWidth + 1);
			pIdx++;
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//==================================================================================================================
// �I������
//==================================================================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@��NULL����Ȃ��Ƃ�
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();				// ���_�o�b�t�@�̊J��
		m_pVtxBuff = NULL;					// NULL�ɂ���
	}

	// �C���f�b�N�X�o�b�t�@��NULL����Ȃ��Ƃ�
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();				// �C���f�b�N�X�o�b�t�@�̊J��
		m_pIdxBuff = NULL;					// NULL�ɂ���
	}
}

//==================================================================================================================
// �X�V����
//==================================================================================================================
void CMeshField::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	VERTEX_3D *m_pVtx;									// ���_���

	// �ď�����
	m_nNumber = 0;										// �z��̔ԍ�
	m_nStartBox = m_nWidth + 1;							// �n�܂锠
	m_nEndBox = 0;										// ������锠

	// ������
	fDivide -= 0.05f;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// �Q�[���̂Ƃ�
			if (CRenderer::GetMode() == CRenderer::MODE_GAME)
			{
				// �c�̃u���b�N���K��l�͈͓��̂Ƃ�
				if (nDepth >= START_NUMBER0 && nDepth <= FINISH_NUMBER0)
				{// �S�[����O�̃W�����v������
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = -200 + WhileX * nWide;												// X���W
					m_pVtx[0].pos.y = (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;				// Y���W
					m_pVtx[0].pos.z = -WhileZ * (nDepth + 5.5f);											// Z���W
				}
				else if (nDepth >= START_NUMBER1 && nDepth <= FINISH_NUMBER1)
				{// �c�̗�u���b�N���K��͈͓��̂Ƃ�
					// �W�����v������̃S�[����O�̃J�[�u
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16))) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						60 + 110 * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16)));									// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
					m_pVtx[0].pos.y = (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;											// Y���W
					m_pVtx[0].pos.z = (m_nWidth - nWide) * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16))) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						-420 + 90 * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER1 - 16)));									// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
				}
				else if (nDepth >= START_NUMBER2 && nDepth <= FINISH_NUMBER2)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// �S�[���ƃX�^�[�g�̒�������
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = -435 + WhileZ * (nDepth + 5.5f);									// X���W
					m_pVtx[0].pos.y = (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;			// Y���W
					m_pVtx[0].pos.z = -660 + WhileX * nWide;											// Z���W
				}
				else if (nDepth >= START_NUMBER3 && nDepth <= FINISH_NUMBER3)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// �X�^�[�g��̍ŏ��̃J�[�u
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth)) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						1125 + 60 * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth));						// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
					m_pVtx[0].pos.y = (nDepth - FINISH_NUMBER2) * 2 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;// Y���W
					m_pVtx[0].pos.z = nWide * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth)) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						-720 + 60 * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER3 + 7 - nDepth));						// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
				}
				else if (nDepth >= START_NUMBER4 && nDepth <= FINISH_NUMBER4)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// �ŏ��J�[�u������̒Z������
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = 1185 + WhileX * nWide;																		// X���W
					m_pVtx[0].pos.y = 16 + (nDepth - FINISH_NUMBER3) * 2 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y���W
					m_pVtx[0].pos.z = 860 + -WhileZ * nDepth;																		// Z���W
				}
				else if (nDepth >= START_NUMBER5 && nDepth <= FINISH_NUMBER5)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// 1��ڂ�180�x�J�[�u
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth)) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						1100 + 86 * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth));						// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
					m_pVtx[0].pos.y = 96 + (nDepth - FINISH_NUMBER4) * 3 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;// Y���W
					m_pVtx[0].pos.z = nWide * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth)) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						-1120 + 86 * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER5 - 1 - nDepth));						// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
				}
				else if (nDepth >= START_NUMBER6 && nDepth <= FINISH_NUMBER6)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// 180�x�J�[�u��̒���
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = 865 + (WhileX * m_nWidth) - WhileX * nWide;													// X���W
					m_pVtx[0].pos.y = 144 + (nDepth - FINISH_NUMBER5) + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y���W
					m_pVtx[0].pos.z = -3260 + WhileZ * nDepth;																		// Z���W
				}
				else if (nDepth >= START_NUMBER7 && nDepth <= FINISH_NUMBER7)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// ������̂�����Ƃ����J�[�u
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1))) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						805 + 60 * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1)));										// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;									// Y���W
					m_pVtx[0].pos.z = (m_nWidth - nWide) * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1))) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						-120 + 60 * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER7 - 1)));									// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
				}
				else if (nDepth >= START_NUMBER8 && nDepth <= FINISH_NUMBER8)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// �΂ߒ���
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = 845 + (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * 3) - (nDepth - (START_NUMBER8)) * 10;		// X���W
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;												// Y���W
					m_pVtx[0].pos.z = -75 + (m_nWidth - nWide) * WhileZ  * sinf((D3DX_PI / CURVE_NUMBER) * 3) + (nDepth - (START_NUMBER8)) * 10;	// Z���W
				}
				else if (nDepth >= START_NUMBER9 && nDepth <= FINISH_NUMBER9)
				{// �c�̗�u���b�N���K��͈͓��̂Ƃ�
					// �΂ߒ�����J�[�u
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth)) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						324 + 120 * cosf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth));						// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;					// Y���W
					m_pVtx[0].pos.z = nWide * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth)) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						800 + 80 * sinf((D3DX_PI / CURVE_NUMBER) * (START_NUMBER9 + 19 - nDepth));						// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
				}
				else if (nDepth >= START_NUMBER10 && nDepth <= FINISH_NUMBER10)
				{// �c�̗�u���b�N���K��l�͈͓��̂Ƃ�
					// ���ڂ̎΂ߒ���
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = 247 + nWide * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * 12) + (nDepth - (START_NUMBER10)) * 10;	// X���W
					m_pVtx[0].pos.y = 244 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;									// Y���W
					m_pVtx[0].pos.z = 865 + nWide * WhileZ  * sinf((D3DX_PI / CURVE_NUMBER) * 12) + (nDepth - (START_NUMBER10)) * 10;	// Z���W
				}
				else if (nDepth >= START_NUMBER11 && nDepth <= FINISH_NUMBER11)
				{// �c�̗�u���b�N���K��͈͓��̂Ƃ�
					// �傫���J�[�u
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = (m_nWidth - nWide) * WhileX * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4))) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						150 + 200 * cosf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4)));									// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
					m_pVtx[0].pos.y = 244 - (nDepth - FINISH_NUMBER10) * 3 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y���W
					m_pVtx[0].pos.z = (m_nWidth - nWide) * WhileX * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4))) +	// �O���Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
						1293 + 245 * sinf((D3DX_PI / CURVE_NUMBER) * (nDepth - (START_NUMBER11 + 4)));									// �����Ȑ�(�ʒu+���a*sinf(������*�Ԗ�))
				}
				else if (nDepth >= START_NUMBER12 && nDepth <= FINISH_NUMBER12)
				{// �c�̗�u���b�N���K��͈͓��̂Ƃ�
					// �W�����v��܂ł̒�������
					// ���_���W�̐ݒ�
					m_pVtx[0].pos.x = -197 + WhileX * nWide;											// X���W
					m_pVtx[0].pos.y = 184 + (sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY;	// Y���W
					m_pVtx[0].pos.z = 5660 + -WhileZ * nDepth;											// Z���W
				}
			}
			else
			{
				///////////////////////////////////////////////�i�~�i�~///////////////////////////////////////////////
				// ���_���W�̐ݒ�
				m_pVtx[0].pos = D3DXVECTOR3((-WhileX * m_nWidth) / 2 + WhileX * nWide,				// X���W
					(sinf(D3DX_PI / 6 * nDepth + fDivide) + 1) / 2 * WhileY / 2,					// Y���W
					(WhileZ / 2 * m_nDepth) - WhileZ * nDepth);										// Z���W
			}

			// ���_�J���[
			m_pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, FIELD_ALPHA);

			// ���_�����Z
			m_pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	//////////////////////////////�@���x�N�g��//////////////////////////////
	// �c���J�E���g
	for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
	{
		// �����J�E���g
		for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
		{
			// �C���f�b�N�X�ԍ�
			int nIdx = nDepth * (m_nWidth + 1) + nWide;

			// �[�͌v�Z�����Ȃ�
			if (nWide != m_nWidth && nDepth != m_nDepth)
			{
				m_vectorA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;								// ��ڂ̃x�N�g��
				m_vectorB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;							// ��ڂ̃x�N�g��
				m_vectorC = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;								// �O�ڂ̃x�N�g��
				D3DXVec3Cross(&m_aVecA[m_nNumber], &m_vectorA, &m_vectorB);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecA[m_nNumber], &m_aVecA[m_nNumber]);								// ���K������
				D3DXVec3Cross(&m_aVecB[m_nNumber], &m_vectorB, &m_vectorC);									// ��̃x�N�g���̒����x�N�g��
				D3DXVec3Normalize(&m_aVecB[m_nNumber], &m_aVecB[m_nNumber]);								// ���K������

				// �z��̔ԍ�1�v���X����
				m_nStartBox++;
				m_nEndBox++;
				m_nNumber++;
			}

			// �E�ゾ�����Ƃ�
			if (nIdx == m_nWidth)
			{
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecB[m_nWidth - 1];
			}
			else if (nIdx == m_nDepth * (m_nWidth + 1))
			{// �����������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = m_aVecA[(m_nDepth - 1) * m_nWidth];
			}
			else if (nIdx == 0)
			{// ���ゾ�����Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[nIdx] + m_aVecB[nIdx]) / 2;
			}
			else if (nIdx == (m_nDepth + 1) * (m_nWidth + 1) - 1)
			{// �E���������Ƃ�
				// �@���x�N�g��
				m_pVtx[nIdx].nor = (m_aVecA[m_nDepth * m_nWidth - 1] + m_aVecB[m_nDepth * m_nWidth - 1]) / 2;
			}
			else if (nWide != 0 && nWide != m_nWidth)
			{// ���̗񂪒[����Ȃ��Ƃ�
				// �c�����ڂ������Ƃ�
				if (nDepth == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[nWide - 1] + m_aVecA[nWide] + m_aVecB[nWide]) / 3;
				}
				else if (nDepth == m_nDepth)
				{// �c���Ō���������Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[(m_nDepth - 1) * m_nWidth - 1 + nWide] +
						m_aVecA[(m_nDepth - 1) * m_nWidth + nWide] +
						m_aVecB[(m_nDepth - 1) * m_nWidth + nWide]) / 3;
				}
				else
				{// ����ȊO
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth] +
						m_aVecA[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1] +
						m_aVecB[(nWide - 1) + (nDepth - 1) * m_nWidth + m_nWidth + 1]) / 6;
				}
			}
			else if (nDepth != 0 && nDepth != m_nDepth)
			{// �c�̗񂪒[����Ȃ��Ƃ�
				 // �擪�̂Ƃ�
				if (nWide == 0)
				{
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecA[(nDepth - 1) * m_nWidth] +
						m_aVecA[m_nWidth + (nDepth - 1) * m_nWidth] +
						m_aVecB[m_nWidth + (nDepth - 1) * m_nWidth]) / 3;
				}
				else if (nWide == m_nWidth)
				{// �Ō���̂Ƃ�
					// �@���x�N�g��
					m_pVtx[nIdx].nor = (m_aVecB[(m_nWidth - 1) + m_nWidth * nDepth] +
						m_aVecA[(m_nWidth - 1) + m_nWidth * nDepth] +
						m_aVecB[m_nWidth - 1 + m_nWidth * nDepth]) / 3;
				}
			}
		}
		// �z��̔ԍ���1�v���X����
		m_nStartBox++;
		m_nEndBox++;
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//==================================================================================================================
// �`�揈��
//==================================================================================================================
void CMeshField::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer = CManager::GetRenderer();			// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();		// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;							// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);
}

//==================================================================================================================
// �ʒu�ݒ�
//==================================================================================================================
void CMeshField::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//==================================================================================================================
// �|���S������
//==================================================================================================================
CMeshField *CMeshField::Create(void)
{
	// �������𓮓I�Ɋm��
	m_pMeshField = new CMeshField(CScene::PRIORITY_FIELD);

	// ���b�V����������Ƃ�
	if (m_pMeshField != NULL)
	{
		// �V�[��������
		m_pMeshField->Init();
	}

	// �l��Ԃ�
	return m_pMeshField;
}

//==================================================================================================================
// �e�N�X�`����񃍁[�h
//==================================================================================================================
HRESULT CMeshField::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();						// �����_���[�̏��擾
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();					// �f�o�C�X���擾����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,			// �f�o�C�X�ւ̃|�C���^
		FIELD_TEXTUE,							// �t�@�C���̖��O
		&m_pTexture);							// �ǂݍ��ރ������[

	// �l��Ԃ�
	return S_OK;
}

//==================================================================================================================
// �e�N�X�`�����j��
//==================================================================================================================
void CMeshField::Unload(void)
{
	// �e�N�X�`����񂪂���Ƃ�
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();			// �e�N�X�`�����̊J��
		m_pTexture = NULL;				// NULL�ɂ���
	}
}

//==================================================================================================================
// ���b�V���t�B�[���h���擾
//==================================================================================================================
CMeshField * CMeshField::GetMeshField(void)
{
	return m_pMeshField;
}

//==================================================================================================================
// �ʒu�擾
//==================================================================================================================
D3DXVECTOR3 CMeshField::GetPos(void)
{
	return m_pos;
}

//==================================================================================================================
// �ړ��ʎ擾
//==================================================================================================================
D3DXVECTOR3 CMeshField::GetMove(void)
{
	return m_move;
}

//==================================================================================================================
// �����Z�o�p�֐�
//==================================================================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 playerPos;			// �v���C���[�̈ʒu
	int nNumPlace = 0;				// ���X�|�[���ꏊ
	float Height = 0.0f;			// �����v�Z�p�ϐ�
	bool bRange = false;			// �͈͂ɂ��邩�ǂ���

	// �^�C�g���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TITLE)
	{
		// �v���C���[�̏��擾
		m_pPlayer = CTitle::GetPlayer();
	}

	// �`���[�g���A���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_TUTORIAL)
	{
		// �v���C���[�̏��擾
		m_pPlayer = CTutorial::GetPlayer();
	}

	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// �v���C���[�̏��擾
		m_pPlayer = CGame::GetPlayer();

		// ���X�|�[���ꏊ�擾
		nNumPlace = m_pPlayer->GetnNumPlace();

		// �v���C���[�̈ʒu�擾
		playerPos = m_pPlayer->GetPos();
	}

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^�擾
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �Q�[���̂Ƃ�
	if (CRenderer::GetMode() == CRenderer::MODE_GAME)
	{
		// ���X�|�[���ꏊ��0 ���� 1�̂Ƃ�
		if (nNumPlace == 0 || nNumPlace == 1)
		{
			// �ď�����
			m_nNumber = (START_NUMBER2 - 1) * m_nWidth;							// �z��̔ԍ�
			m_nStartBox = (START_NUMBER2)* m_nWidth + START_NUMBER2;			// �n�܂锠
			m_nEndBox = (START_NUMBER2 - 1) * m_nWidth + (START_NUMBER2 - 1);	// ������锠

			// �����x�N�g���p�ϐ�
			D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

			// �c���J�E���g
			for (int nDepth = 44; nDepth < FINISH_NUMBER3 + 1; nDepth++)
			{
				// �����J�E���g
				for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
				{
					// �͈͊O�ɂ���Ƃ�
					if (!bRange)
					{
						// ���_���[����Ȃ��Ƃ��[�͌v�Z�����Ȃ�
						if (nWide != m_nWidth && nDepth != m_nDepth)
						{
							// �S�Ẵx�N�g�����o��
							D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

							// ������pos���璸�_�܂ł��x�N�g���ɂ���
							D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
							D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

							//////�����x�N�g���Z�o//////
							// ��ڂ̎O�p�`
							D3DXVec3Cross(&norA, &vecA, &vec0);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norB, &vec0, &vecB);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norC, &vecC, &vec2);					// �����x�N�g���Z�o

							// ��ڂ̎O�p�`
							D3DXVec3Cross(&norD, &vecB, &vec0);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norE, &vec0, &vecD);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norF, &vec1, &vecE);					// �����x�N�g���Z�o

							// �@�����ʂ̕\���ゾ�����Ƃ�
							if (m_aVecA[m_nNumber] >= 0)
							{
								// �O�p�`�̒��ɂ���Ƃ�
								if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
								{
									// ���b�V���t�B�[���h�̒��ɂ���
									bRange = true;

									// ������pos�����_�Ɠ����ł���Ƃ�
									if (pos == m_pVtx[m_nStartBox].pos)
									{
										// �ʂȒ��_���g���č������Z�o
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
									}
									else
									{
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
									}
								}
							}

							// �@�����ʂ̕\���ゾ�����Ƃ�
							if (m_aVecB[m_nNumber] >= 0)
							{
								// �O�p�`�̒��ɂ���Ƃ�
								if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
								{
									// ���b�V���t�B�[���h�̒��ɂ���
									bRange = true;

									// ������pos�����_�Ɠ����ł���Ƃ�
									if (pos == m_pVtx[m_nEndBox + 1].pos)
									{
										// �ʂȒ��_���g���č������Z�o
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
									}
									else
									{
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
									}
								}
							}

							// �z��̔ԍ�1�v���X����
							m_nStartBox++;
							m_nEndBox++;
							m_nNumber++;
						}
					}
				}

				// ���I�������z��̔ԍ���1�v���X����
				m_nStartBox++;
				m_nEndBox++;
			}
		}
		else if (playerPos.y > CALCULATION_POS_Y)
		{// ���X�|�[���ꏊ���K��l�̂Ƃ�
			// �ď�����
			m_nNumber = (START_NUMBER5 - 1) * m_nWidth;							// �z��̔ԍ�
			m_nStartBox = (START_NUMBER5) * m_nWidth + START_NUMBER5;			// �n�܂锠
			m_nEndBox = (START_NUMBER5 - 1) * m_nWidth + (START_NUMBER5 - 1);	// ������锠

			// �����x�N�g���p�ϐ�
			D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

			// �c���J�E���g
			for (int nDepth = 199; nDepth < FINISH_NUMBER12 + 1; nDepth++)
			{
				// �����J�E���g
				for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
				{
					// �͈͊O�ɂ���Ƃ�
					if (!bRange)
					{
						// ���_���[����Ȃ��Ƃ��[�͌v�Z�����Ȃ�
						if (nWide != m_nWidth && nDepth != m_nDepth)
						{
							// �S�Ẵx�N�g�����o��
							D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

							// ������pos���璸�_�܂ł��x�N�g���ɂ���
							D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
							D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

							//////�����x�N�g���Z�o//////
							// ��ڂ̎O�p�`
							D3DXVec3Cross(&norA, &vecA, &vec0);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norB, &vec0, &vecB);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norC, &vecC, &vec2);					// �����x�N�g���Z�o

							// ��ڂ̎O�p�`
							D3DXVec3Cross(&norD, &vecB, &vec0);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norE, &vec0, &vecD);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norF, &vec1, &vecE);					// �����x�N�g���Z�o

							// �@�����ʂ̕\���ゾ�����Ƃ�
							if (m_aVecA[m_nNumber] >= 0)
							{
								// �O�p�`�̒��ɂ���Ƃ�
								if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
								{
									// ���b�V���t�B�[���h�̒��ɂ���
									bRange = true;

									// ������pos�����_�Ɠ����ł���Ƃ�
									if (pos == m_pVtx[m_nStartBox].pos)
									{
										// �ʂȒ��_���g���č������Z�o
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
									}
									else
									{
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
									}
								}
							}

							// �@�����ʂ̕\���ゾ�����Ƃ�
							if (m_aVecB[m_nNumber] >= 0)
							{
								// �O�p�`�̒��ɂ���Ƃ�
								if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
								{
									// ���b�V���t�B�[���h�̒��ɂ���
									bRange = true;

									// ������pos�����_�Ɠ����ł���Ƃ�
									if (pos == m_pVtx[m_nEndBox + 1].pos)
									{
										// �ʂȒ��_���g���č������Z�o
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
									}
									else
									{
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
									}
								}
							}

							// �z��̔ԍ�1�v���X����
							m_nStartBox++;
							m_nEndBox++;
							m_nNumber++;
						}
					}
				}

				// ���I�������z��̔ԍ���1�v���X����
				m_nStartBox++;
				m_nEndBox++;
			}
		}
		else
		{// ����ȊO
			// �ď�����
			m_nNumber = 0;										// �z��̔ԍ�
			m_nStartBox = m_nWidth + 1;							// �n�܂锠
			m_nEndBox = 0;										// ������锠

			// �����x�N�g���p�ϐ�
			D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
			D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

			// �c���J�E���g
			for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
			{
				// �����J�E���g
				for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
				{
					// �͈͊O�ɂ���Ƃ�
					if (!bRange)
					{
						// ���_���[����Ȃ��Ƃ��[�͌v�Z�����Ȃ�
						if (nWide != m_nWidth && nDepth != m_nDepth)
						{
							// �S�Ẵx�N�g�����o��
							D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

							// ������pos���璸�_�܂ł��x�N�g���ɂ���
							D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
							D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
							D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
							D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

							//////�����x�N�g���Z�o//////
							// ��ڂ̎O�p�`
							D3DXVec3Cross(&norA, &vecA, &vec0);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norB, &vec0, &vecB);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norC, &vecC, &vec2);					// �����x�N�g���Z�o

							// ��ڂ̎O�p�`
							D3DXVec3Cross(&norD, &vecB, &vec0);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norE, &vec0, &vecD);					// �����x�N�g���Z�o
							D3DXVec3Cross(&norF, &vec1, &vecE);					// �����x�N�g���Z�o

							// �@�����ʂ̕\���ゾ�����Ƃ�
							if (m_aVecA[m_nNumber] >= 0)
							{
								// �O�p�`�̒��ɂ���Ƃ�
								if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
								{
									// ���b�V���t�B�[���h�̒��ɂ���
									bRange = true;

									// ������pos�����_�Ɠ����ł���Ƃ�
									if (pos == m_pVtx[m_nStartBox].pos)
									{
										// �ʂȒ��_���g���č������Z�o
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
									}
									else
									{
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
									}
								}
							}

							// �@�����ʂ̕\���ゾ�����Ƃ�
							if (m_aVecB[m_nNumber] >= 0)
							{
								// �O�p�`�̒��ɂ���Ƃ�
								if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
								{
									// ���b�V���t�B�[���h�̒��ɂ���
									bRange = true;

									// ������pos�����_�Ɠ����ł���Ƃ�
									if (pos == m_pVtx[m_nEndBox + 1].pos)
									{
										// �ʂȒ��_���g���č������Z�o
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
									}
									else
									{
										// �w�肳�ꂽ�ʒu�ł̍������Z�o
										Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
									}
								}
							}

							// �z��̔ԍ�1�v���X����
							m_nStartBox++;
							m_nEndBox++;
							m_nNumber++;
						}
					}
				}
				// ���I�������z��̔ԍ���1�v���X����
				m_nStartBox++;
				m_nEndBox++;
			}
		}
	}
	else
	{// �^�C�g�� ���� �`���[�g���A���̂Ƃ�
		// �ď�����
		m_nNumber = 0;										// �z��̔ԍ�
		m_nStartBox = m_nWidth + 1;							// �n�܂锠
		m_nEndBox = 0;										// ������锠

		// �c���J�E���g
		for (int nDepth = 0; nDepth < m_nDepth + 1; nDepth++)
		{
			// �����J�E���g
			for (int nWide = 0; nWide < m_nWidth + 1; nWide++)
			{
				// �͈͊O�ɂ���Ƃ�
				if (!bRange)
				{
					// ���_���[����Ȃ��Ƃ��[�͌v�Z�����Ȃ�
					if (nWide != m_nWidth && nDepth != m_nDepth)
					{
						// �S�Ẵx�N�g�����o��
						D3DXVECTOR3 vecA = m_pVtx[m_nStartBox].pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vecB = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vecC = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nStartBox].pos;
						D3DXVECTOR3 vecD = m_pVtx[m_nEndBox + 1].pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vecE = m_pVtx[m_nStartBox + 1].pos - m_pVtx[m_nEndBox + 1].pos;

						// ������pos���璸�_�܂ł��x�N�g���ɂ���
						D3DXVECTOR3 vec0 = pos - m_pVtx[m_nEndBox].pos;
						D3DXVECTOR3 vec1 = pos - m_pVtx[m_nEndBox + 1].pos;
						D3DXVECTOR3 vec2 = pos - m_pVtx[m_nStartBox].pos;
						D3DXVECTOR3 vec3 = pos - m_pVtx[m_nStartBox + 1].pos;

						// �����x�N�g���p�ϐ�
						D3DXVECTOR3 norB = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norA = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norC = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norD = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norE = D3DXVECTOR3(0, 0, 0);
						D3DXVECTOR3 norF = D3DXVECTOR3(0, 0, 0);

						//////�����x�N�g���Z�o//////
						// ��ڂ̎O�p�`
						D3DXVec3Cross(&norA, &vecA, &vec0);					// �����x�N�g���Z�o
						D3DXVec3Cross(&norB, &vec0, &vecB);					// �����x�N�g���Z�o
						D3DXVec3Cross(&norC, &vecC, &vec2);					// �����x�N�g���Z�o

						// ��ڂ̎O�p�`
						D3DXVec3Cross(&norD, &vecB, &vec0);					// �����x�N�g���Z�o
						D3DXVec3Cross(&norE, &vec0, &vecD);					// �����x�N�g���Z�o
						D3DXVec3Cross(&norF, &vec1, &vecE);					// �����x�N�g���Z�o

						// �@�����ʂ̕\���ゾ�����Ƃ�
						if (m_aVecA[m_nNumber] >= 0)
						{
							// �O�p�`�̒��ɂ���Ƃ�
							if (norA.y <= 0 && norB.y <= 0 && norC.y <= 0)
							{
								// ���b�V���t�B�[���h�̒��ɂ���
								bRange = true;

								// ������pos�����_�Ɠ����ł���Ƃ�
								if (pos == m_pVtx[m_nStartBox].pos)
								{
									// �ʂȒ��_���g���č������Z�o
									// �w�肳�ꂽ�ʒu�ł̍������Z�o
									Height = m_pVtx[m_nStartBox + 1].pos.y + (-m_aVecA[m_nNumber].x * vec3.x - m_aVecA[m_nNumber].z * vec3.z) / m_aVecA[m_nNumber].y;
								}
								else
								{
									// �w�肳�ꂽ�ʒu�ł̍������Z�o
									Height = m_pVtx[m_nStartBox].pos.y + (-m_aVecA[m_nNumber].x * vec2.x - m_aVecA[m_nNumber].z * vec2.z) / m_aVecA[m_nNumber].y;
								}
							}
						}

						// �@�����ʂ̕\���ゾ�����Ƃ�
						if (m_aVecB[m_nNumber] >= 0)
						{
							// �O�p�`�̒��ɂ���Ƃ�
							if (norD.y <= 0 && norE.y <= 0 && norF.y <= 0)
							{
								// ���b�V���t�B�[���h�̒��ɂ���
								bRange = true;

								// ������pos�����_�Ɠ����ł���Ƃ�
								if (pos == m_pVtx[m_nEndBox + 1].pos)
								{
									// �ʂȒ��_���g���č������Z�o
									// �w�肳�ꂽ�ʒu�ł̍������Z�o
									Height = m_pVtx[m_nEndBox].pos.y + (-m_aVecB[m_nNumber].x * (vec0.x) - m_aVecB[m_nNumber].z * (vec0.z)) / m_aVecB[m_nNumber].y;
								}
								else
								{
									// �w�肳�ꂽ�ʒu�ł̍������Z�o
									Height = m_pVtx[m_nEndBox + 1].pos.y + (-m_aVecB[m_nNumber].x * (vec1.x) - m_aVecB[m_nNumber].z * (vec1.z)) / m_aVecB[m_nNumber].y;
								}
							}
						}

						// �z��̔ԍ�1�v���X����
						m_nStartBox++;
						m_nEndBox++;
						m_nNumber++;
					}
				}
			}
			// ���I�������z��̔ԍ���1�v���X����
			m_nStartBox++;
			m_nEndBox++;
		}
	}

	// ���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	// �v���C���[�͈͓̔��󋵐ݒ�
	m_pPlayer->SetbRange(bRange);

	return Height;
}

//==================================================================================================================
// �ړ��ʐݒ�
//==================================================================================================================
void CMeshField::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}